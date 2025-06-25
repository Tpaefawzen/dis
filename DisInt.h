#pragma once

typedef unsigned short DisInt;
static void assertIsDis(DisInt x) {
   if (x >= 59049)
      __builtin_trap();
}
