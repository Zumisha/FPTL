
bison -L C++ --verbose parser.yy
cp parser.tab.cc ./Generated
cp parser.tab.hh ./Generated
cp stack.hh   ./Generated

rm parser.tab.cc
rm parser.tab.hh
rm stack.hh

pause