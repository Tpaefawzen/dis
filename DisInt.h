#pragma once
#include "Assert.h"

typedef unsigned short DisInt;
#define assertIsDis(x) Assert(0<=(x) && (x)<=59048)
