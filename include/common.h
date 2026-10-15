#ifndef COMMON_H
#define COMMON_H

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;

#ifndef NULL
#define NULL 0
#endif

/* Sony's SDK libraries (config/gcc_files.txt) build with an EE GCC 2.9, which has no
 * __int128; its 128-bit integer is the TI machine mode. */
#if defined(__GNUC__) && !defined(__MWERKS__) && !defined(M2CTX) && !defined(PERMUTER)
typedef int dk_int128 __attribute__((mode(TI)));
#define __int128 dk_int128
#endif

/* MW_ALIGN(n): an aligned home for a spilled Metrowerks parameter (OVERLAYS-COMPILER.md, "parameter home
 * slots"). The prototype dk writes into functions.h keeps it, and GCC rejects alignment on a parameter, so it
 * is empty outside Metrowerks. */
#if defined(__MWERKS__)
#define MW_ALIGN(n) __attribute__((aligned(n)))
#else
#define MW_ALIGN(n)
#endif

#include "dk_asm.h"
#include "structs.h"
#include "game.h"
#include "functions.h"

#endif
