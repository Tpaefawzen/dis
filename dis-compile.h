#pragma once

#include "DisInt.h"

typedef enum {
   CompileStatusOutComment,
   CompileStatusInComment,
} DisCompileStatus;

typedef enum {
   CompileResultDoneOk,
   CompileResultWipOk,
   CompileResultErrInvalidChar,
   CompileResultErrTooLong,
   CompileResultErrUnclosedComment,
} DisCompileResult;

static _Bool isCntrl(unsigned short c) {
   return 0<=c && c<=32 || c == 127;
}

static DisCompileResult dis_compileAppendOne(
      /// memory to write
      DisInt mem[59049],
      /// Please init with (*len) == 0
      DisInt *len,
      /// Please init with (*status) == CompileStatusOutComment
      DisCompileStatus *status,
      _Bool is_eof, unsigned char c)
{
   assertIsDis(*len);

   if (*status == CompileStatusOutComment) {
      if (is_eof) return CompileResultDoneOk;

      switch (c) {
	 case 33: case 42: case 62: case 94: case 95:
	 case 123: case 124: case 125:
	    if (*len >= 59049) return CompileResultErrTooLong;
	    mem[*len] = c;
	    (*len)++;
	    return CompileResultWipOk;

	 case '(':
	    *status = CompileStatusInComment;
	    return CompileResultWipOk;

	 default:
	    if (isCntrl(c)) return CompileResultWipOk;
	    return CompileResultErrInvalidChar;
      }
   }

   if (is_eof) return CompileResultErrUnclosedComment;
   if (c == ')') *status = CompileStatusOutComment;
   return CompileResultWipOk;
}
