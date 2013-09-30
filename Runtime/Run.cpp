#include <assert.h>

#include <iostream>
#include <hash_set>
#include <boost/timer.hpp>

#include "Run.h"
#include "FScheme.h"
#include "WorkStealingQueue.h"

#undef max

namespace FPTL { namespace Runtime {

//-----------------------------------------------------------------------------
SExecutionContext::SExecutionContext()
	: Parent(0),
	mEvaluatorUnit(0),
	arity(0),
	argPos(0),
	numCollected(std::numeric_limits<int>::max()),
	Ready(0)
{
	stack.reserve(10);
}

SExecutionContext * SExecutionContext::fork(FSchemeNode * aScheme)
{
	SExecutionContext * fork = new SExecutionContext();
	fork->Scheme = aScheme;
	fork->Parent = this;

	// Копируем стек.
	for (int i = argPos; i < stack.size(); i++)
	{
		fork->stack.push_back(stack.at(i));
	}
	
	// Добавляем в очередь новое задание.
	mEvaluatorUnit->addJob(fork);

	return fork;
}

void SExecutionContext::run(EvaluatorUnit * aEvaluatorUnit)
{
	assert(!mEvaluatorUnit);
	mEvaluatorUnit = aEvaluatorUnit;

	// Для отключения JIT.
	Scheme->execute(*this);

	//Scheme->mCompiledProc(this);

	// Сообщаем о готовности задания.
	Ready.store(1, boost::memory_order_release);
}

void SExecutionContext::yield()
{
	mEvaluatorUnit->schedule();
}

const DataValue & SExecutionContext::getArg(int aIndex) const
{
	return stack.at(argPos + aIndex);
}

void SExecutionContext::push(const DataValue & aData)
{
	stack.push_back(aData);
	++arity;
}

void SExecutionContext::advance()
{
	argPos = stack.size() - arity;
	arity = 0;
}

void SExecutionContext::unwind(int aArgPosOld, int aArity, int aPos)
{
	for (int i = 0; i < arity; ++i)
	{
		stack[aPos + i] = stack[stack.size() - arity + i];
	}

	argPos = aArgPosOld;
	stack.resize(aPos + arity);
	arity += aArity;
}

//-----------------------------------------------------------------------------
void * SExecutionContext::alloc(size_t aSize)
{
	void * ptr = operator new (aSize);
	allocatedMemory.push_front(ptr);
	return ptr;
}

int SExecutionContext::collect()
{
	std::stack<Collectable *> markStack;
	std::hash_set<void *> marked;

	// Помечаем корни.
	for (auto i = stack.begin(); i < stack.end(); ++i)
	{
		i->getOps()->mark(*i, markStack);
	}

	// Помечаем транзитивное замыкание.
	while (!markStack.empty())
	{
		auto ptr = markStack.top();
		markStack.pop();

		// Циклических ссылок нет.
		marked.insert(ptr);
		ptr->mark(markStack);
	}

	// Освобождаем непомеченную память.
	std::list<void *> sweeped;

	int numCollected = 0;

	for (auto i = allocatedMemory.begin(); i != allocatedMemory.end(); ++i)
	{
		if (marked.find(*i) != marked.end())
		{
			sweeped.push_back(*i);
		}
		else
		{
			delete *i;
			++numCollected;
		}
	}

	allocatedMemory.swap(sweeped);
	return numCollected;
}

void SExecutionContext::tryCollect()
{
	int allocated = allocatedMemory.size();

	if (allocated > 100000)
	{
		if (float(numCollected / allocated) > 0.75)
		{
			numCollected = collect();
		}
	}
}

//-----------------------------------------------------------------------------
EvaluatorUnit::EvaluatorUnit(SchemeEvaluator * aSchemeEvaluator)
	: mEvaluator(aSchemeEvaluator),
	  mJobsCompleted(0),
	  mJobsCreated(0),
	  mJobsStealed(0)
{
}

void EvaluatorUnit::addJob(SExecutionContext * aContext)
{
	mJobsCreated++;
	mJobQueue.push(aContext);
}

SExecutionContext * EvaluatorUnit::stealJob()
{
	SExecutionContext * elem = 0;
	mJobQueue.steal(elem);

	if (elem)
	{
		mJobsStealed++;
	}

	return elem;
}

void EvaluatorUnit::evaluateScheme()
{
	while (!boost::this_thread::interruption_requested())
	{
		schedule();
	}

	// Выводим статистику.
	std::stringstream ss;
	ss << "\nJobs processed by thread id = " << boost::this_thread::get_id() << " " << mJobsCompleted << " stealed " << mJobsStealed;
	std::cout << ss.str();
}

void EvaluatorUnit::schedule()
{
	// Берем задание из своей очереди.
	SExecutionContext * context = 0;
		
	if (mJobQueue.pop(context))
	{
		context->run(this);
		mJobsCompleted++;
		return;
	}

	// Если это не удалось, берем у кого-нибудь другого.
	context = mEvaluator->findJob(this);
	
	if (context)
	{
		context->run(this);
		mJobsCompleted++;
	}
}

//-----------------------------------------------------------------------------
SchemeEvaluator::SchemeEvaluator()
{
}

void SchemeEvaluator::stop()
{
	mThreadGroup.interrupt_all();
}

SExecutionContext * SchemeEvaluator::findJob(const EvaluatorUnit * aUnit)
{
	for (size_t i = 0; i < mEvaluatorUnits.size(); i++)
	{
		if (mEvaluatorUnits[i] != aUnit)
		{
			SExecutionContext * job = mEvaluatorUnits[i]->stealJob();
			if (job)
			{
				return job;
			}
		}
	}

	return 0;
}

void SchemeEvaluator::runScheme(const FSchemeNode * aScheme, const FSchemeNode * aInput, int aNumEvaluators)
{
	if (aNumEvaluators <= 0 || aNumEvaluators >= 32)
	{
		std::cerr << "Number of evaluation units is incorrect. Using default value (1).\n";
		aNumEvaluators = 1;
	}

	int evaluatorUnits = aNumEvaluators;

	// Создаем юниты выполнения.
	for (int i = 0; i < evaluatorUnits; i++)
	{
		mEvaluatorUnits.push_back(new EvaluatorUnit(this));
	}

	// Создаем задание и назначем его первому вычислителю.

	SExecutionContext * context = new SExecutionContext();

	///
	FFunctionNode startNode(
		[this, aScheme, aInput, context](SExecutionContext & aCtx)
		{
			if (aInput)
			{
				//aInput->mCompiledProc(context);
				aInput->execute(aCtx);
			}

			aCtx.advance();

			boost::timer timer;

			//aScheme->mCompiledProc(context);
			aScheme->execute(aCtx);

			// TEST: собираем всю память.
			//aCtx.collect();

			stop();

			std::cout << "\nTime : " << timer.elapsed() << "\n\n";
		}
	);
	///

	context->Scheme = &startNode;

	mEvaluatorUnits[0]->addJob(context);

	// Создаем потоки.
	for (int i = 0; i < evaluatorUnits; i++)
	{
		mThreadGroup.create_thread(boost::bind(&EvaluatorUnit::evaluateScheme, mEvaluatorUnits[i]));
	}

	// Ждем завершения вычислений.
	mThreadGroup.join_all();

	int stop = 0;

	// TODO: освобождаем всю память, выделенную под скомпилированный в рантайме код.
}

//-----------------------------------------------------------------------------

}} // FPTL::Runtime