#pragma once
#ifndef SMOOTHY_META_ASM_CLOCK_H
#define SMOOTHY_META_ASM_CLOCK_H

#ifdef _MSC_VER
#include <intrin.h>
#else
//#include <x86intrin.h>        // TODO: use intrinsics
#include <cpuid.h>
#endif

#include <cstdint>

// references: https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf

#ifdef __GNUC__
namespace smoothy   {
namespace meta      {
namespace details   {
    enum class order {
          pre
        , post
    };
}

    inline int cpuid(unsigned i = 0) {

        std::uint32_t regs[4];
        asm volatile(
            "CPUID\n\t" :
                  "=a" (regs[0])
                , "=b" (regs[1])
                , "=c" (regs[2])
                , "=d" (regs[3])
                : "a" (i), "c" (0)
        );
    }

    template <details::order>
    inline std::uint64_t timestamp();

    template <>
    inline std::uint64_t timestamp<details::order::pre>() {

        unsigned hi, lo;

        asm volatile (
            "CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (hi), "=r" (lo)::
            "%rax", "%rbx", "%rcx", "%rdx"
        );

        return ((uint64_t)hi << 32) | lo;
    }

    template <>
    inline std::uint64_t timestamp<details::order::post>() {

        unsigned hi, lo;

        asm volatile(
            "RDTSCP\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t": "=r" (hi), "=r" (lo)::
            "%rax", "%rbx", "%rcx", "%rdx"
        );

        return ((uint64_t)hi << 32) | lo;
    }
}}

#endif // __GNUC__

#endif // SMOOTHY_META_ASM_CLOCK_H
