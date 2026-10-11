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
s32 func_00202BF0(s32);                         /* extern */
s32 func_001ACC80(s32);                             /* extern */
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
s32 func_001E78C0(s32);                             /* extern */
s32 func_00246340(s32);                             /* extern */
s32 func_001DF540();                                /* extern */
s32 func_001F9940(s32, s32, s32);   /* extern */
s32 func_001E01F0(s32);                             /* extern */
s32 func_001EDFD0(s32, s32);                        /* extern */

s32 func_0020A0B0(s32, s32);                        /* extern */
s32 func_0010A160(s32, s32);            /* extern */
s32 func_001DA7F0(s32, s32, s32);                   /* extern */
s32 func_001FD320(s32, s32, s32, s32 *);            /* extern */
s32 func_00202B00(s32, s32, s32, s32 *);            /* extern */
s32 func_001FAFB0(s32, s32);                /* extern */
s32 func_00190810(s32, s32, s32, s32); /* extern */

u8 *func_001DD0E0();                                /* extern */
s32 func_001DF110();                                /* extern */
s32 func_001DF470();                                /* extern */
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

s32 func_00278250(s32, s32, s32, s32);          /* extern */


s32 func_00155520(s32, s32);


extern s32 *D_0030FF40;
void func_0017BB60(s32);
s32 func_0017BCA0(s32 *, s32);



void func_0027DE20(s32, s32, s32, s32, s32, s32, s32, s32, s32, u16, s32, s32, u8, s32, s32, s32);

s32 func_00197BC0(s32);
extern u8 D_1FE0000;

s32 func_001F6620();
void func_001F66A0(s32, s32);
f32 func_001F67C0(s32, s32);
void func_001F6840(s32, f32);

s64 func_001A22C0(f32);
void func_001D89F0(s32, s32, s32, s32, s32, s32, s32);
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

void func_00244250(void *);
extern u8 D_003506C8[];

s32 func_0024CA40(s32, s32, s32, s32, s32, s32);

void func_001F3190(s32, s32);

s32 func_0027DD20(s32, s32, s32);

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

void func_0020BB50(void);
extern u8 D_00325D38[];

extern s32 D_0032A240;

extern s32 D_0032F780;
extern s32 D_0032F784;
extern s32 D_0032F788;
extern s32 D_0032F78C;

extern char D_0030F8E9;


void func_00244680(u8 *);

extern u8 D_0029D586[];

void func_00100780(void);
void func_00209F60(void (*)(void));

f32 func_001A1F18(s64);
void func_001CD560(void);
extern u8 D_0031A7C0[];
extern u16 D_002CE4A4[];

void func_001E53C0(s32, s32);
void func_002073D0(u8 *, s32, s32);
void func_0020BAF0(s32);

s32 func_001F1370(u8);


void func_001FECB0(s32, s32, s32, s32, s32, s32, s32, s32, s64);

extern s64 D_002D0830[];

void func_0020BC00(s32, void *);
void func_0020C750(void *);

s32 func_0021DDA0(s32);
extern s8 D_0034F710;
extern s32 D_0029B2F0;
extern u8 D_00350620[];

void func_00182A28(s32);

s32 func_001E2100(s32, s32, s32);
u32 func_0026FBB0(u16);
void func_0027ACB0(s32, s32 *, u8 *, s32, s32, s32, s32, s32);

extern u8 D_003193C0[];

void func_001AAFA0(s32);
s32 func_001AE5F0(s32);

extern s32 D_0030FF48;

s32 func_001E55E0(s32);

extern s32 D_0031BEB0[];

s32 func_001FF420(void);

void func_0020B380(void *, void *, s32);

extern s32 func_001A1E70(u64);
extern s32 func_001A2858(s32, s32);


s32 func_00275E80(void *);                          /* extern */
s32 func_0027F830(s32);                             /* extern */


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


s32 func_001E3850(s32, s32, s32);
s32 func_001E3D30(s32, s32, s32);


void func_0020BDE0(void *, void *);
void func_0020CDD0(void *, void *, void *);

s32 func_001E3A20(s32, s32, s32);

s32 func_0018EE68(void *);

void func_00245340(void *);
extern u8 D_00350600[];
extern volatile s32 D_0035060C;

s32 func_0010BCC0(void);

extern u16 D_002CD8A0[];
extern u8 D_00318E60[];
void func_001DF5F0(s32, s32, s32, void *, s32);

s32 func_001FE8F0(s32, s32, s32, s32, s32);
s32 func_001FD680(s32, s32, s32, s32, s32);


void *func_00197990(s32, s32);
char *func_0019BDD8(char *, const char *);
s32 func_0019BEF0(const char *);

void func_0020BCF0(s32, s32);


s32 func_002670F0(s32, s32);
s32 func_002626F0(s32, s32, s32);

s32 func_00249040(s32, s32);
extern u8 D_0029D580[];
s32 func_00250A60(s32, u8, u8);

void func_002798C0(s32, s32, s32, s32, s32, s32);

s32 func_001F51D0(s32 arg0);
void *func_0019C2B8(void *, const void *, u32);

s32 func_001E1B70();                                /* extern */

void func_001DFBB0(s32, s32);
void func_001CDEB0(void *arg0);


s32 func_001FE7D0(s32, s32, s32, s32, s32, s32);

s32 func_00208110(s32, s32, s32, s32, s32, s32);

void func_00242600(void *, s32, void *);
void func_00242950(s32);
void func_00242C20(void);
extern char D_0030F354[];
extern s32 D_003503B8;
extern s32 D_003505F0;
extern u8 D_00350680[];
extern u8 D_00350740[];
extern s32 D_00350788;

extern u16 D_0029CF32[];

s32 func_002509E0(s32, s32, s32, s32);              /* extern */
s32 func_00250B40(s32, s32, s32, s32);              /* extern */

s32 func_001E0700(s32, s32);
s32 func_0026FE70(void);
s32 func_00270030(void);
s32 func_00270260(void);
void func_00279CC0(s32, s32, s32, s32, s32, s32, s32);
extern u16 D_002D0970[51][41];
s32 func_002660E0(s32, s32, s32, s32);

void func_001FA810(s32, s32);
void func_001FA8A0(s32, s32, s32, s32, s32, void *);
f32 func_00108030(s32, s32, s32);
s32 func_00205440(s32, void *, u16 *, s32 *);
extern u8 D_00299F90[];

void func_001F5620(s32, u8, s32);

void func_0019B648(void *, void *, s32);
extern u8 D_002B90B0[];
s32 func_0017BC80(s32);
void func_0010B3C0(void);
void func_0010B490(void);

s32 func_0017E8B0(void *, s32, s32);

s32 func_001EFDC0(s32, s32, s32, s32, s32, s32, s32);

void func_001B0CE0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern char D_002BF002[];

void func_001F7550(s32);

extern char D_002BF040;

void func_0017B8F0(s32);
void func_001843E0(void);
void func_00184428(void);

extern u32 D_0029E830[];

void func_00241840(u8 *, s32, s32, s32, s32, s32);

void func_002792C0(s32, s32, s32, s32, s32, s32, s32, u8);
s32 func_00271830(s32);

f32 func_001A6A88(f32);

void func_0027B290(s32, s32, s32, s32, s32, s32, s32, u8);

void func_001E3070(s32, s32, s32, s32, s32, s32);


extern u64 D_00293EE0[];

void func_001F6160(s32, void *);

s32 func_001A2EB0(s32);                             /* extern */
s32 func_001A2F68(s32);                             /* extern */
s32 func_001A6BE8(s64, s32);                        /* extern */

void func_0027F5B0(void);
f32 func_001A6B70(f32);
f32 func_001A6C48(f32, f32);
void func_00100850(void);
void func_001A8770(s32);
s32 func_001A87A0(void);
void func_001AA260(void);
void func_001FA220(s32, s32);
void func_00203320(void);
s32 func_002099D0(void);
void func_00217550(void);
void func_0027A130(s32, s32, s32, s32, s32, s32, s32, s32, u8, u16);
void func_00109A90(void);
void *func_00198948(void *, s32, u32);

extern s32 D_00292468;

s32 func_00216920(s32, s32);
extern u8 D_003181EC;

void func_001A8870(s32, s32);
extern s8 D_00299E10;
extern s16 D_00299ED4;
s64 func_00215D30(u8, s32);

s32 func_0024F830(s32, s32, s32, s32, s32);
s32 func_0024FD10(s32, s32, s32);

void func_00217710(s32, s32);

s32 func_00271950(s32, s32, s32, s32, s32);


s32 func_001F3910(s32, s16, s32, void *);

void func_001EE570(void);
s32 func_001EE6C0(s32, s32, s32, s32, s32, s32, s32, void (*)(void), s64);
s32 func_001FE660(s32, s32, s64, s64, f32, f32, s32, void (*)(void));
void func_001FEAB0(s32);
void func_001FDFE0(void);

void func_00278420(s32, s32, s32, s32);
void func_002130A0(s32);
u8 *func_002131D0(u8 *, s32, s32);
void func_00213D00(u8 *, u8 *);
s32 func_002134D0(s32, s32 *);
s32 func_002138D0(s32, s32 *);

void func_001DFD50(s32, s32, s32, s32);

void func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);

s32 func_0027BBC0(s32, s32, s32);

s32 func_001DE020(s32);


void func_001F34A0(s32, s32);

void func_0010C580(void);
s32 func_00200510(s32, s32, s32, s32, void (*)(void), s32, s32);
extern char D_002B90C0[];
extern s32 D_0030FF58;
extern s32 D_0030FFA0;
extern s32 D_0030FFA4;
extern s32 D_0030FFA8;
extern s32 D_0030FFAC;
extern s32 D_0030FFB0;

s32 func_001DDAC0(s32, s32, u8, u8);

void func_0016DDA0(u16 *, ...);
void func_0016E0E0(u16 *, s32);


extern s32 D_00325DD0;
extern s32 D_00325E2C;

s32 func_0018EB08(void *, s32, s32);
s32 func_0018EF20(void *, s32, s32 (*)(), s32);

void func_001F9D80(s32, f32 *);
void func_001FB360(s32, f32 *);

void func_001851E8(void *, s32, s32, s32, s32, s32, s32);
void func_00241C20(s32, s32, s32, s32, s32);
extern s32 D_00350368;
extern s32 D_00350370;
extern s32 D_00350378;
extern s32 D_00350380;
extern s32 D_00350388;
extern s32 D_00350390;
extern s32 D_00350398;
extern s32 D_003503A0;
extern s32 D_003503A8;
extern s32 D_003503B0;
extern u8 D_003503C0[];

s32 func_0026AC90(s32, s32, s32);

f32 func_001A6898(f32);

extern f32 D_00294050[];


void func_001ADD00(s32, s32, s32);
extern u8 D_00318280[];

s32 func_0027C670(void *);

s32 func_00271E40(s32, s32, s32);

s32 func_0010F850(s32, s32);

void func_001E3FB0(s32, s32, s32);

s32 func_00122970(s32);                             /* extern */

void func_0017B900(s32);
void func_0017B920(s32);

s32 func_00100350(void);
void func_001A6C80(void);
void func_001A89C0(s32, s32);
void func_001E4E90(void);
void func_001E7A60(void);
void func_001FCC70(s32, s32, s32, s32, s32, s32);
void func_001FD2B0(void);
void func_002007D0(void);
void func_002031F0(void);
void func_00203CD0(void);
s32 func_00209510(s32, s32, s32, s32, s32, s32, s32);
void func_00209E90(s32, s32, s32, s32);
void func_00214290(void);
void func_00217410(void);

s32 func_0024EA70(s32, s32);                        /* extern */
s32 func_00267560(s32);                             /* extern */

void func_001A87C0(s32, s32);
void func_00214990(s32, s32);
extern s8 D_0034F700;
extern s8 D_0034F708;

void func_001E42C0(s32, s32, s32, s32);
void func_00260490(s32, s32, s32, s32, s32, s32, s32);

s32 func_0024EFB0(s32);

extern s32 D_003180E8;

extern u8 D_0031747A;
extern s32 D_003180E4;
extern s32 D_0031810C;
extern s8 D_0031747B;
s32 func_001D9A30(s32, s32);

void func_001B6CA0(s32, s32, s32, s32, s32, s32, s32, s32);

s32 func_001AEFD0(s32, s32);
void func_001B65F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_003181E4;
extern u8 D_003181E2;

extern u8 D_003181E3;
extern s8 D_00318144;
extern s8 D_00318145;
extern s32 D_0031AB90;
extern s8 D_00318142;

extern s32 D_0031BB10;

s32 func_001F16C0(s32 arg0, s32 arg1);
void func_001F1C50(s32 arg0, s32 arg1);

void func_001F4900(s32, s32, s32, s32, s32, s32, s32);
void func_001F5860(s32);
void func_001F57C0(s32 arg0, s32 arg1);
s32 func_001F1A90(s32 arg0, s32 arg1);
void func_001F63F0(s32, s32, s32);
s32 func_001F1B60(s32, s32);

void func_001F6210(s32, s32);
void func_001F53C0(s32, s32, s32);
void func_001F60D0(s32, s32);

extern s8 D_0031BEA2;

extern u8 D_0031BEA0;
extern s32 D_0031C2E4;
extern s32 D_00325C80;
extern s32 D_00325C84;
extern s32 D_003261D0;

void func_001FFCC0(void *arg0, s32 arg1);
void func_00200230(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001FB1D0(s32, s32);

extern s8 D_0031BEA1;
void func_001FB0B0(s32, s32);
extern s32 D_0032A220;

extern s8 D_00299EDA;

extern s16 D_00299E4E;
extern char D_0030F3AE[];

void func_00260AF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002435A0(void *);

extern s32 D_0031C048;

#endif
