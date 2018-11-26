#pragma once
#ifndef SMOOTHY_META_ASM_COMMENT_H
#define SMOOTHY_META_ASM_COMMENT_H

#include <smoothy/meta/preprocessor/cat.h>

#ifdef __GNUC__
#define NASM_COMMENT(X) asm(CAT("#", #X) : : );
#else
#define NASM_COMMENT(X) __asm__(CAT("#", #X));
#endif

//#ifdef __GNUC__
//#ifdef DEBUG_ASM
//#define NASM_COMMENT(X) asm(CAT("#", #X) : : );
//#else
//#define NASM_COMMENT(X)
//#endif
//#else
//#ifdef DEBUG_ASM
//#define NASM_COMMENT(X) __asm__(CAT("#", #X));
//#else
//#define NASM_COMMENT(X)
//#endif
//#endif

#define NASM_STATEMENT(X)           \
    NASM_COMMENT("START " #X)       \
    X;                              \
    NASM_COMMENT("END "   #X)
#endif
