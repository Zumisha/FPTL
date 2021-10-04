#pragma once

#define BUILD_DATE __DATE__ " " __TIME__
#define fromNano(x) (static_cast<double>(x)/1000000000)

#define fptlDebugBuild 1
#define disableExceptionHandling 0