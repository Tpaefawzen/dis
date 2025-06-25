#pragma once

#include "Assert.h"
#include "DisInt.h"

typedef enum {
   DisStepOk,
   DisStepOkWritten,
   DisStepOkRead,
   DisStepHalt,
   DisStepWantRead,
   DisStepWantWrite,
} DisStepResult;

static DisInt rot(DisInt);
static DisInt opr(DisInt, DisInt);

static DisStepResult dis_step(DisInt *a, DisInt *c, DisInt *d, DisInt mem[59049],
      _Bool can_write, unsigned char *outc,
      _Bool is_eof, _Bool can_read, unsigned char in_ch)
{
   DisStepResult r = DisStepOk;

   assertIsDis(*a); assertIsDis(*c); assertIsDis(*d);
   assertIsDis(mem[*c]);
   assertIsDis(mem[*d]);

   DisInt x = mem[*c];
   if (x == 33) {
      return DisStepHalt;
   } else if (x == 42) {
      *d = mem[*d];
   } else if (x == 62) {
      *a = mem[*d] = rot(mem[*d]);
   } else if (x == 94) {
      *c = mem[*d];
   } else if (x == 123) {
      if (*a == 59048) {
	 return DisStepHalt;
      }
      if (can_write) {
	 *outc = (unsigned char)*a;
	 r = DisStepOkWritten;
      } else {
	 return DisStepWantWrite;
      }
   } else if (x == 124) {
      *a = mem[*d] = opr(*a, mem[*d]);
   } else if (x == 125) {
      if (is_eof) {
	 *a = 59048;
      } else if (can_read) {
	 *a = (unsigned char)in_ch;
	 r = DisStepOkRead;
      } else {
	 return DisStepWantRead;
      }
   }

   *c = (*c + 1) % 59049;
   *d = (*d + 1) % 59049;

   return DisStepOk;
}

static DisInt rot(DisInt x) {
   assertIsDis(x);
   return x/3+(x%3*19683);
}

static DisInt digopr(DisInt, DisInt);
static DisInt opr(DisInt x, DisInt y) {
   assertIsDis(x); assertIsDis(y);
   DisInt r = 0;
   for (DisInt w = 19683; w; w/=3)
      r += w*digopr((x/w)%3, (y/w)%3);
   return r;
}

static DisInt digopr(DisInt x, DisInt y) {
   return (3+x-y)%3;
}
