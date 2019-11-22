
"%flex%" tokenizer.flex
rm ./Generated/Flex/FlexScanner.cpp
cp FlexScanner.cpp ./Generated/Flex/
rm FlexScanner.cpp

pause