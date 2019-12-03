cmake_minimum_required(VERSION 3.0)

# Source Files
set(SRC_FILES
  Main.cpp
  Tests.cpp
  
  DataTypes/TypeInfo.cpp
  
  DataTypes/Ops/ADTOps.cpp
  DataTypes/Ops/ArrayOps.cpp
  DataTypes/Ops/BooleanOps.cpp
  DataTypes/Ops/DoubleOps.cpp
  DataTypes/Ops/IntegerOps.cpp
  DataTypes/Ops/Ops.cpp
  DataTypes/Ops/StringOps.cpp
  DataTypes/Ops/UndefinedOps.cpp
  
  Evaluator/Context.cpp
  Evaluator/EvaluatorUnit.cpp
  Evaluator/Run.cpp
  
  FScheme/ConstructorGenerator.cpp 
  FScheme/FScheme.cpp
  FScheme/FSchemeGenerator.cpp
  FScheme/NodeDeleter.cpp
  
  InternalForm/Generator.cpp
  InternalForm/InternalForm.cpp
  
  Libraries/FunctionLibrary.cpp
  Libraries/StandardLibrary.cpp
  
  GC/CollectedHeap.cpp
  GC/GarbageCollector.cpp
  
  Parser/Nodes.cpp
  Parser/NodeVisitor.cpp
  Parser/Semantic.cpp
  Parser/Support.cpp
  Parser/Tokenizer.cpp
  
  Parser/Generated/Parser.tab.cc
  Parser/Generated/Flex/FlexScanner.cpp
)
source_group("Sources" FILES ${SRC_FILES})

# Header Files
set(HEADERS_FILES
Macros.h

DataTypes/TypeInfo.h

DataTypes/Ops/ADTOps.h
DataTypes/Ops/ArrayOps.h
DataTypes/Ops/Ops.h
DataTypes/Ops/StringOps.h

Evaluator/Context.h
Evaluator/LockFreeWorkStealingQueue.h
Evaluator/Run.h

FScheme/ConstructorGenerator.h
FScheme/FScheme.h
FScheme/FSchemeGenerator.h
FScheme/FSchemeVisitor.h
FScheme/NodeDeleter.h

InternalForm/ControlValue.h
InternalForm/Generator.h
InternalForm/InternalForm.h

Libraries/FunctionLibrary.h
Libraries/StandardLibrary.h
  
GC/BlockingQueue.h
GC/CollectedHeap.h
GC/GarbageCollector.h
GC/GcAwarePtr.h  

Parser/AST.h
Parser/FlexTokenizer.h
Parser/Ident.h
Parser/Nodes.h
Parser/NodeVisitor.h
Parser/SemanticCheck.h
Parser/Support.h

Parser/Generated/Parser.tab.hh
Parser/Generated/stack.hh
Parser/Generated/Flex/FlexLexer.h

Utils/FormattedOutput.h
)
source_group("Headers" FILES ${HEADERS_FILES})

add_library(Source ${SRC_FILES} ${HEADERS_FILES})
#add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADERS_FILES})