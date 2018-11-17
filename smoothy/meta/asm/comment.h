#pragma once
#ifndef SMOOTHY_META_ASM_COMMENT_H
#define SMOOTHY_META_ASM_COMMENT_H

#include <smoothy/meta/preprocessor/cat.h>

#ifndef _MSC_VER
#ifdef __GNUC__
// extended asm
#define NASM_COMMENT(X) asm(CAT("#", #X) : : );
#else
#define NASM_COMMENT(X) __asm__(CAT("#", #X));
#endif
#else
#define NASM_COMMENT(X) X;
#endif

#define NASM_STATEMENT(X)           \
    NASM_COMMENT("START " #X)       \
    X;                              \
    NASM_COMMENT("END " #X)

#endif