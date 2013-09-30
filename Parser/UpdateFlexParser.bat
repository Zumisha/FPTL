cd /D %FLEX_PATH%

flex.exe %FPTL_INTERP_PATH%\Parser\tokenizer.flex
copy /Y FlexScanner.cpp %FPTL_INTERP_PATH%\Parser\Generated\Flex\

pause