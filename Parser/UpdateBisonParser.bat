cd /D %BISON_PATH%

bison.exe -L C++ --verbose %FPTL_INTERP_PATH%\Parser\parser.yy
copy /Y /V Parser.tab.cc %FPTL_INTERP_PATH%\Parser\Generated
copy /Y /V Parser.tab.hh %FPTL_INTERP_PATH%\Parser\Generated
copy /Y /V location.hh   %FPTL_INTERP_PATH%\Parser\Generated
copy /Y /V position.hh   %FPTL_INTERP_PATH%\Parser\Generated

pause