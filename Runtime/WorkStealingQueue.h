#ifndef WORK_STEALING_QUEUE_H
#define WORK_STEALING_QUEUE_H

#include <vector>
#include <boost/thread.hpp>
#include <boost/atomic.hpp>

namespace FPTL {
namespace Runtime {

// Очередь для хранения заданий.
// Имеется у каждого потока. Добавление/удаление для своего потока - неблокирующая операции.
// Взятие из чужого потока с блокировкой.
template <typename T>
class WorkStealingQueue
{
public:

	WorkStealingQueue() : WorkStealingQueue(32) {}

	explicit WorkStealingQueue(const size_t size) : mQueue(size), mSize(size), mHeadPos(0), mTailPos(0) {}

	void push(const T & aElem)
	{
		auto tailPos = mTailPos;
		if (tailPos < mSize)
		{
			mQueue[tailPos] = aElem;
			mTailPos = tailPos + 1;
		}
		else
		{
			/// Увеличиваем размер очереди.
			boost::lock_guard<boost::mutex> lock(mAccessMutex);

			const auto numJobs = mTailPos - mHeadPos;

			if (mHeadPos > 0)
			{
				for (int i = 0; i < numJobs; i++)
				{
					mQueue[i] = mQueue[i + mHeadPos];
				}

				mTailPos = numJobs;
				mHeadPos = 0;
			}

			// Увеличиваем размер очереди.
			mSize *= 2;
			mQueue.resize(mSize);

			// Добавляем элемент.
			mQueue[mTailPos] = aElem;
			mTailPos++;
		}
	}

	bool pop(T & aElem)
	{
		auto tailPos = mTailPos;
		if (tailPos <= mHeadPos)
		{
			return false;
		}

		tailPos--;
		mTailPos = tailPos;

		boost::atomic_thread_fence(boost::memory_order_seq_cst);

		if (tailPos >= mHeadPos)
		{
			aElem = mQueue[tailPos];
			mQueue[tailPos] = nullptr;
			return true;
		}
		else
		{
			boost::lock_guard<boost::mutex> lock(mAccessMutex);

			if (tailPos >= mHeadPos)
			{
				// Поток, крадущий задания, понял наши намерения и вернул задание обратно.
				aElem = mQueue[tailPos];
				mQueue[tailPos] = nullptr;
				return true;
			}
			else
			{
				// Не вернул
				tailPos++;
				mTailPos = tailPos;

				return false;
			}
		}
	}

	bool steal(T & aElem)
	{
		auto result = false;

		if (mAccessMutex.try_lock())
		{
			auto headPos = mHeadPos;

			mHeadPos++;

			boost::atomic_thread_fence(boost::memory_order_seq_cst);

			// Если задание не было взято своим потоком, то берем его.
			if (headPos < mTailPos)
			{
				//assert(headPos < mTailPos);
				aElem = mQueue[headPos];
				mQueue[headPos] = nullptr;
				result = true;
			}
			else
			{
				// Возвращаем задание.
				mHeadPos = headPos;
				result = false;
			}

			mAccessMutex.unlock();
		}

		return result;
	}

private:
	boost::mutex mAccessMutex;
	std::vector<T> mQueue;
	volatile int mSize;
	volatile int mHeadPos;
	volatile int mTailPos;
};

}}

#endif