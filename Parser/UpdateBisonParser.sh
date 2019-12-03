bison -L C++ --verbose parser.yy
mv parser.tab.cc ./Generated
mv parser.tab.hh ./Generated
mv stack.hh ./Generated