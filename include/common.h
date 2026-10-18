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

/* The campaign work area (its layout: include/campaign.h). Other screens borrow the same memory as scratch
 * while the campaign map is not running: deck building, trade, the duel, effects, the AI's search tree, the
 * slot machine. */
#define CAMPAIGN_WORK_ADDR 0x01ED0000

/* The custom-duel settings, fixed memory past the program (main_041, main_042). Per side (+ 0 or 1): +0x2 the
 * side's menu state (high nibble) and duelist (low nibble), +0x6 a number shown in digits, +0x8, +0xA, +0xC,
 * +0xE on/off options; +0x10 the two sides' life points (s16 each); +0x18 a list of u16 entries. +0x88: 0 when
 * side 1 has a menu of its own (two players); +0x89/+0x8A and +0x8C/+0x8D the top and length of two lists;
 * +0x8F/+0x90 the map editor's cursor (column, row), +0x91 its key-repeat timer, +0x92 flags. */
#define CUSTOM_DUEL_ADDR 0xA9C000

/* Where the duel effects' code overlays are copied and linked (mwOverlayInit); +0x1C holds the overlay's end. */
#define OVERLAY_ADDR 0x01E00000

/* A copy of the game data (SzData_GetData(0)): the save file is read into it (main_037), and the campaign's
 * help screen keeps the data there while it runs (main_068, main_062). */
#define GAME_DATA_COPY_ADDR 0x01E301E0

#include "ee_regs.h"
#include "dk_asm.h"
#include "structs.h"
#include "game.h"
#include "functions.h"

#endif
