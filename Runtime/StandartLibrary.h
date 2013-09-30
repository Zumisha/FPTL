// Встроенные функции.

#ifndef STANDART_LIBRARY_H
#define STANDART_LIBRARY_H

#include "Functions.h"

namespace FPTL {
namespace Runtime {

class StandartLibrary : public FunctionLibrary
{
public:
	StandartLibrary();
};

}} // FPTL::Runtime

#endif