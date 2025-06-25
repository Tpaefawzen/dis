#include "dis-compile.h"

#define Assert(c) if (!(c)) __builtin_trap();

int main(void) {
   DisInt mem1[59049] = {0}, len1 = 0;
   DisCompileStatus s = CompileStatusOutComment;

   Assert(dis_compileAppendOne(mem1, &len1, &s, 0, 'A') == CompileResultErrInvalidChar);

   char src1[] = "(   This is a test \n"
	 "   (() *^^^{{}}{}}}||{}^^^|>>>________>>>!!!*\n"
	 "   ( nn) \t\x7f\x01{{\x00\x1e\x1f\n"
	 " _" ;
   char expected1[] = "*^^^{{}}{}}}||{}^^^|>>>________>>>!!!*"
	"{{"
	 "_";

   for (int i=0; i<(sizeof(src1)-1); i++) {
      Assert(dis_compileAppendOne(mem1, &len1, &s, 0, src1[i]) == CompileResultWipOk);
   }
   Assert(dis_compileAppendOne(mem1, &len1, &s, 1, 0) == CompileResultDoneOk);
   Assert(len1 == sizeof(expected1)-1);

   for (int i=0; i<sizeof(expected1)-1; i++)
      Assert(mem1[i] == expected1[i]);
}
