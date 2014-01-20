#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <memory>

#include "FScheme.h"
#include "FSchemeGenerator.h"
#include "Run.h"
#include "../Parser/Support.h"
#include "../Parser/Tokenizer.h"

using namespace boost::python;

namespace FPTL
{
namespace Interop
{

class FunctionalProgram
{
public:
	FunctionalProgram(const std::string & aText)
		: mText(aText)
	{
	}

	bool translate()
	{
		Parser::Support support;
		Parser::Tokenizer tokenizer(mText);

		mAstRoot.reset(support.getInternalForm(&tokenizer));

		if (!mAstRoot.get())
		{
			support.getErrorList(std::cout);
			return false;
		}

		// Генерируем внутренне представление.		
		mSchemeGenerator.process(mAstRoot.get());

		return true;
	}

	bool execute(int numProcessors)
	{
		if (!getScheme())
		{
			return false;
		}

		Runtime::SchemeEvaluator evaluator;
		evaluator.runScheme(getScheme(), getData(), numProcessors);

		return true;
	}

	Runtime::FSchemeNode * getScheme()
	{
		return mSchemeGenerator.getFScheme();
	}

	Runtime::FSchemeNode * getData()
	{
		return mSchemeGenerator.getSchemeInput();
	}

	dict getConsructors() const
	{
		// TODO:
	}

private:
	Runtime::FSchemeGenerator mSchemeGenerator;

	std::auto_ptr<Parser::ASTNode> mAstRoot;

	std::string mText;
};

// Обертка для абстрактного класса.
class FSchemeNodeWrapper : public Runtime::FSchemeNode, public wrapper<Runtime::FSchemeNode>
{
public:
	virtual void execute(Runtime::SExecutionContext & aCtx) const
	{
	}

	virtual void accept(Runtime::FSchemeVisitor * aVisitor) const
	{
	}
};

// Вспомогательные функции.
namespace
{

void setType(Runtime::FSchemeNode * aNode, list aTypeList)
{
	// TODO:
}

dict getTypeParameters(const Runtime::TypeInfo & aTypeInfo)
{
	dict parameters;

	for (auto it = aTypeInfo.Parameters.begin(); it != aTypeInfo.Parameters.end(); ++it)
	{
		parameters[it->first] = it->second;
	}

	return parameters;
}

Runtime::TypeInfo createTypeInfo(const std::string & aName, const dict & aParameters)
{
	Runtime::TypeInfo info(aName);

	list keys = aParameters.keys();

	for (int i = 0; i < len(keys); ++i)
	{
		extract<std::string> key(keys[i]);
		extract<Runtime::TypeInfo> value(aParameters[keys[i]]);

		if (key.check() && value.check())
		{
			info.Parameters.insert(std::pair<std::string, Runtime::TypeInfo>(key, value));
		}
	}

	return info;
}

}

BOOST_PYTHON_MODULE(fptl)
{
	// Типы данных.
	class_<Runtime::TypeInfo>("TypeInfo")
		.def_readonly("type_name", &Runtime::TypeInfo::TypeName);

	def("createTypeInfo", &createTypeInfo);
	def("getTypeParameters", &getTypeParameters);
	def("setType", &setType);

	class_<std::vector<std::string>>("StringArray")
		.def(vector_indexing_suite<std::vector<std::string>>());

	// Функциональная схема.
	class_<FSchemeNodeWrapper, boost::noncopyable>("FSchemeNode", no_init);

	class_<Runtime::FSequentialNode, bases<Runtime::FSchemeNode>>("FSequentialNode", no_init)
		.def("first", &Runtime::FSequentialNode::first, return_internal_reference<>())
		.def("second", &Runtime::FSequentialNode::second, return_internal_reference<>());

	class_<Runtime::FParallelNode, bases<Runtime::FSchemeNode>>("FParallelNode", no_init)
		.def("left", &Runtime::FParallelNode::left, return_internal_reference<>())
		.def("right", &Runtime::FParallelNode::right, return_internal_reference<>());

	class_<Runtime::FConditionNode, bases<Runtime::FSchemeNode>>("FConditionNode", no_init)
		.def("condition", &Runtime::FConditionNode::condition, return_internal_reference<>())
		.def("then", &Runtime::FConditionNode::trueBranch, return_internal_reference<>())
		.def("else", &Runtime::FConditionNode::falseBranch, return_internal_reference<>());

	class_<Runtime::FFunctionNode, bases<Runtime::FSchemeNode>>("FFunctionNode", no_init)
		.def("name", &Runtime::FFunctionNode::name)
		.def("column", &Runtime::FFunctionNode::col)
		.def("line", &Runtime::FFunctionNode::line);

	class_<Runtime::FConstantNode, bases<Runtime::FSchemeNode>>("FConstantNode", no_init)
		.def("type", &Runtime::FConstantNode::type);

	class_<Runtime::FTakeNode, bases<Runtime::FSchemeNode>>("FTakeNode", no_init)
		.def("index", &Runtime::FTakeNode::index)
		.def("column", &Runtime::FTakeNode::col)
		.def("line", &Runtime::FTakeNode::line);

	class_<Runtime::FScheme, bases<Runtime::FSchemeNode>>("FScheme", no_init)
		.def("scheme", &Runtime::FScheme::firstNode, return_internal_reference<>())
		.def("name", &Runtime::FScheme::name)
		.def("definitions", &Runtime::FScheme::definitions)
		.def("definition", &Runtime::FScheme::definition, return_internal_reference<>());

	// Управление интерпретатором.
	class_<FunctionalProgram, boost::noncopyable>("FunctionalProgram", init<std::string>())
		.def("translate", &FunctionalProgram::translate)
		.def("execute", &FunctionalProgram::execute)
		.def("scheme", &FunctionalProgram::getScheme, return_internal_reference<>())
		.def("data", &FunctionalProgram::getData, return_internal_reference<>());
}


} // Interop
} // FPTL