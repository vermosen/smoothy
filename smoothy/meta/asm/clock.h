#pragma once
#ifndef SMOOTHY_META_ASM_CLOCK_H
#define SMOOTHY_META_ASM_CLOCK_H

#ifdef __GNUC__
#define CLOCK_PRE(X, Y)                         \
asm volatile (                                  \
    "CPUID\n\t"                                 \
    "RDTSC\n\t"                                 \
    "mov %%edx, %0\n\t"                         \
    "mov %%eax, %1\n\t": "=r" (X), "=r" (Y)::   \
    "%rax", "%rbx", "%rcx", "%rdx");

#define CLOCK_POST(X, Y)                        \
asm volatile(                                   \
    "RDTSCP\n\t"                                \
    "mov %%edx, %0\n\t"                         \
    "mov %%eax, %1\n\t"                         \
    "CPUID\n\t": "=r" (X), "=r" (Y)::           \
    "%rax", "%rbx", "%rcx", "%rdx");

#endif // __GNUC__
#endif // SMOOTHY_META_ASM_CLOCK_H
