#include <stddef.h>
#include "dis-step.h"

#define Assert(c) if(!(c)) __builtin_trap()

int main(void) {
   DisInt a,c,d,mem[59049]={0};
   a = c = d = 0;
   DisStepResult r;

   mem[0] = 33;
   

   r = dis_step(&a, &c, &d, mem,
	 0, NULL,
	 0, 0, 0);
   Assert(r == DisStepHalt);
   Assert(a == 0); Assert(c == 0); Assert(d == 0);
}
