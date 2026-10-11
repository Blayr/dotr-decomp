#ifndef GAME_H
#define GAME_H

#include "common.h"

/* Declarations collected by `dk accept`. Move them into topic headers as the
 * game's structure becomes clear. */

s32 func_00183E10();                            /* extern */

s32 func_0024E410();                            /* extern */
s32 func_00172370();                            /* extern */
s32 func_00158810();                            /* extern */

s32 func_00197C18();                            /* extern */
s32 func_001A2E60();                                /* extern */
s32 func_00193808();                            /* extern */
s32 func_0017B790(s32);                     /* extern */
s32 func_0018E200();                            /* extern */
s32 func_0019A5C8();                            /* extern */
s32 func_002038F0();                            /* extern */
s32 func_00202BF0(s32);                         /* extern */
s32 func_001DE540();                                /* extern */
s32 func_001ACC80(s32);                             /* extern */
s32 func_00209D20();                                /* extern */
s32 func_00209D30(s32);                         /* extern */
s32 func_001AEEB0(s32);                             /* extern */
s32 func_001AF7E0(s32);                             /* extern */
s32 func_001B11C0(s32);                             /* extern */
s32 func_001B8210(s32);                             /* extern */
s32 func_001B83F0(s32);                             /* extern */
s32 func_001BAEA0(s32);                             /* extern */
s32 func_001C1B00(s32);                             /* extern */
s32 func_001C35A0(s32);                             /* extern */
s32 func_001C7460(s32);                             /* extern */
s32 func_001CCBB0(s32);                             /* extern */
s32 func_001CD710(s32);                             /* extern */
s32 func_001CE430(s32);                             /* extern */
s32 func_001D9A20(s32);                             /* extern */
s32 func_001E78C0(s32);                             /* extern */
s32 func_00213FC0(s32);                             /* extern */
s32 func_00246340(s32);                             /* extern */
s32 func_001DF540();                                /* extern */
s32 func_0024FDD0(s32);                         /* extern */
s32 func_001E7E70(s32, s32, s32);   /* extern */
s32 func_001F9940(s32, s32, s32);   /* extern */
s32 func_001E01F0(s32);                             /* extern */
s32 func_001EDFD0(s32, s32);                        /* extern */
s32 func_001F9170(s32, s32, s32);       /* extern */

s32 func_001F9230(s32, s32, s32);       /* extern */
s32 func_001F9310(s32, s32, s32);       /* extern */
s32 func_001F9770(s32, s32, s32);       /* extern */
s32 func_001F6E10(s32, s32);                /* extern */
s32 func_0020A0B0(s32, s32);                        /* extern */
s32 func_002085E0(s32, s32);                        /* extern */
s32 func_0010A160(s32, s32);            /* extern */
s32 func_001DA7F0(s32, s32, s32);                   /* extern */
s32 func_001FD320(s32, s32, s32, s32 *);            /* extern */
s32 func_001FF360(s32, s32);                    /* extern */
s32 func_00202B00(s32, s32, s32, s32 *);            /* extern */
s32 func_001FAFB0(s32, s32);                /* extern */
s32 func_00190810(s32, s32, s32, s32); /* extern */
s32 func_0026FA80(s32, s32);                        /* extern */

u8 *func_001DD0E0();                                /* extern */
s32 func_001DF110();                                /* extern */
f32 func_001F9A20(s32);                         /* extern */
s32 func_001DF470();                                /* extern */
s32 func_00147EB0(s32);                             /* extern */
s32 func_0014C9D0(s32);                             /* extern */
s32 func_0015ED90(s32);                             /* extern */
s32 func_002084D0(s32, s32);                        /* extern */
s32 func_00208680(s32, s32);                /* extern */
s32 func_0020A9E0();                            /* extern */

s32 func_001F7350(s32, s32);                /* extern */
s32 func_001FA770(s32, s32, s32);       /* extern */
s32 func_001FCF90(s32, s32, s32, s32);              /* extern */
s32 func_00202FB0(s32, s32, s32, s32);              /* extern */
s32 func_00207650(s32, s32, s32, s32);              /* extern */

s32 func_00208030(s32, s32, s32, s32);              /* extern */
s32 func_00278250(s32, s32, s32, s32);          /* extern */
s32 func_00248F60(s32, s32);                    /* extern */

s32 func_0010F220(s32 arg0);

s32 func_00155520(s32, s32);

void func_001F6D00(s32);

extern s32 *D_0030FF40;
void func_0017BB60(s32);
s32 func_0017BCA0(s32 *, s32);

void func_0015A180(s32, s32, u16 *);

s32 func_001E0C00(s32, s32, s32, s32);
s32 func_00266F70(s32, s32);

void func_0027DE20(s32, s32, s32, s32, s32, s32, s32, s32, s32, u16, s32, s32, u8, s32, s32, s32);

s32 func_00197BC0(s32);
extern u8 D_1FE0000;

s32 func_001F6620();
void func_001F66A0(s32, s32);
f32 func_001F67C0(s32, s32);
void func_001F6840(s32, f32);

s64 func_001A22C0(f32);
void func_001D89F0(s32, s32, s32, s32, s32, s32, s32);
s32 func_001DED30(s32);
void func_001DF130(s32, s32);
void func_001DF1E0(void);
s32 func_0026F690(s32, u16 *, s16 *, s32);
extern u8 D_00317490[];

void func_001F1E10(s32, f32 *);
void func_001F1EE0(s32, f32 *);

typedef __int128 Q128_0020F290;
extern u8 D_0032A5E0[];
extern Q128_0020F290 D_0032A600;
extern void func_001875F8(void *, s32);
extern s32 func_00187608(void *);
extern void func_00187660(void *, s32);
extern void func_001876B8(void *, Q128_0020F290);
extern void func_001876D0(void *);
extern void func_00187778(void *, s32, s32);
extern void func_001877F8(void *, s32);
extern void func_00187828(void *, s32, s32);
extern void func_00187858(void *, s32);
extern void func_001878B0(void *);

void func_00242900(void);
void func_00244250(void *);
extern u8 D_003506C8[];

s32 func_0024CA40(s32, s32, s32, s32, s32, s32);

s32 func_001EE4B0(s32, s32, s32, s32, s32, s32, s32);
void func_001F3190(s32, s32);
s32 func_001F3210(s32);

s32 func_0024E300(s32, s32, s32);
s32 func_0027DD20(s32, s32, s32);

s32 func_001E1090(s32, s32);
s32 func_0027B650(u16 *);
void func_0027C070(s32, u16 *, s32, s32);
void func_0027C2C0(s32, u16 *, s32, s32, s32);

void func_00185578(s32, s32);
void func_00185890(void *, s16, s32, s32, s32, s32, s32, s32);
void func_001859D0(void *, u64);
extern u8 D_00325E80[];
extern u8 D_00325F50[];
extern s32 D_003261BC;

void func_0010F290(s32, void *, s32, s32);
s32 func_0023C160(void);
void func_0026FD30(s32, s32 *);

void func_00198790(void *, const void *, s32);
void func_00199B50(const char *, ...);
s32 func_00200360(s32);
void func_002003E0(s32, s32, s32, s32);
void func_002004C0(s32);
extern char D_002B90DA[];
extern char D_002B9102[];
extern char D_002B9112[];
extern char D_002B9127[];
extern char D_002B9135[];

extern s32 D_00317250;

extern s32 D_00317254;

void func_00199BC0(s32, s32, s32, void (*)(void));
void func_001BA630(void);
extern s32 D_00317B68;

void func_001BA710(void);
extern s32 D_00317B6C;

void func_0010A280(s32, s32, s32, s32, s32, s32);

void func_001F6590(s32, s32, s32);
extern s32 D_0031BE98;

void func_0020B400(void *, s32, s32);
extern u8 D_003259C0[];

extern s32 D_0032618C;
extern s32 D_00326190;

extern s32 D_003261B0;
extern s32 D_003261B4;

f32 func_001A6C60(f32);

extern s32 D_00350340;
extern s32 D_003505F8;

void func_00195108(s32 arg0, s16 arg1);


s32 func_001F64C0();                                /* extern */

s32 func_001F70A0(s32, s32, s32, s32, s32, s32);
extern s32 D_0031BE9C;

s32 func_001F71A0(s32, s32, s32, s32, s32, s32);

u8 *func_00197548(void);
extern u8 D_002D0655[];

extern volatile s32 D_00351170;

extern u8 D_0029D1F0[];

extern s16 D_00322990;
extern u16 D_00322992;
extern s16 D_00322994;

extern u8 D_00325CC0[];
void func_00206D30(s32, void *, s32, s32, s32, s32, s32);

void func_00207510(void *);
void func_0020BB50(void);
extern u8 D_00325D38[];

extern s32 D_0032A240;

extern s32 D_0032F780;
extern s32 D_0032F784;
extern s32 D_0032F788;
extern s32 D_0032F78C;

extern char D_0030F8E9;

void func_00244530(u8 *);

void func_00244680(u8 *);

extern u8 D_0029D586[];

void func_00100560(void);
void func_00100780(void);
void func_001F73C0(void);
void func_00209F60(void (*)(void));

s32 func_0013A870(s32);                             /* extern */
f32 func_001A1F18(s64);
void func_001CD560(void);
extern u8 D_0031A7C0[];
extern u16 D_002CE4A4[];

void func_001E53C0(s32, s32);
void func_002073D0(u8 *, s32, s32);
void func_0020BAF0(s32);

s32 func_001F1370(u8);

void func_001FCDE0(s32);

void func_001FECB0(s32, s32, s32, s32, s32, s32, s32, s32, s64);

extern s64 D_002D0830[];

void func_0020BC00(s32, void *);
void func_0020C750(void *);

s32 func_0021DDA0(s32);
extern s8 D_0034F710;
extern s32 D_0029B2F0;
extern u8 D_00350620[];

void func_00182A28(s32);
void func_002439D0(s32);

s32 func_001E2100(s32, s32, s32);
u32 func_0026FBB0(u16);
void func_0027ACB0(s32, s32 *, u8 *, s32, s32, s32, s32, s32);

extern u8 D_003193C0[];

s32 func_001E36E0(s32, s32);
void func_001AAFA0(s32);
void func_001F30B0(s32, s32);
void func_001CDD90(u8 *);
s32 func_001AE5F0(s32);
s32 func_001F3130(s32);

s32 func_00136060(void *arg0);
extern s32 D_0030FF48;

s32 func_001E55E0(s32);

extern s32 D_0031BEB0[];

s32 func_001FF420(void);

void func_0020B380(void *, void *, s32);

extern s32 func_001A1E70(u64);
extern s32 func_001A2858(s32, s32);

void *func_00250740(s32, s32, s32);

s32 func_00275E80(void *);                          /* extern */
s32 func_0027F830(s32);                             /* extern */

s32 func_0026AB80(s32, s32);

void func_001DCD70(void *, s32);

void func_001E7DE0(s32);
void func_001F7720(s32);
typedef void (*Callback_00286910)(void);
f32 func_001A6C18(f32, f32);                        /* extern */
void func_001F62B0(s32, f32 *);

s32 func_0024DF80(s32 arg0, void *arg1);
s32 func_001A23B0(f32);
s32 func_00205630(s32, s32, s32, s32, f32 *);

s32 func_00254890(s32 *, s32);
void func_00254C90(s32 *, s32);

void *func_001DD130(void);

void func_001E23A0(s32, s32, s32);

#endif
