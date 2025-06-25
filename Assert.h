#pragma once

#ifndef NDEBUG
#  if __GNUC__
#    define Assert(c) if (!(c)) __builtin_trap()
#  elif _MSC_VER
#    define Assert(c) if (!(c)) __debugbreak()
#  else
#    define Assert(c) if (!(c)) *(volatile int *)0 = 0
#  endif
#else
#  define Assert(c)
#endif
