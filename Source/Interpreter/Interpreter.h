#pragma once

namespace FPTL 
{
	namespace Runtime 
	{
		class Interpreter
		{
		public:
			Interpreter() = default;
			int Eval(int argc, const char ** argv, const std::string& programText = "") const;
		};
	}	
}