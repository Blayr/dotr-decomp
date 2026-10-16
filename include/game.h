#ifndef GAME_H
#define GAME_H

#include "common.h"

/* Declarations collected by `dk accept`. Move them into topic headers as the
 * game's structure becomes clear. */











extern s32 *D_0030FF40;




extern u8 D_1FE0000;


typedef struct Duel_00317490_s {
    u8 players[2][0x350];          /* 0x000: one record per player (callers use their own views) */
    u8 pad6A0[0x6D0 - 0x6A0];
    struct {
        u8 pad00[0x20];
        u16 ids[3];                /* 0x20: the three cards picked */
    } *pick;                       /* 0x6D0 */
    u8 pad6D4[0x6D8 - 0x6D4];
    u16 *list;                     /* 0x6D8: the trunk list */
    u16 *list2;                    /* 0x6DC: the deck list (40) */
    u8 pad6E0[0xC58 - 0x6E0];
    s32 depth;                     /* 0xC58: GS z of the duel screen sprites */
    u8 padC5C[0xC86 - 0xC5C];
    u16 wave1;                     /* 0xC86 */
    u16 wave2;                     /* 0xC88 */
    u16 offset;                    /* 0xC8A */
    u16 count;                     /* 0xC8C */
    u16 offset2;                   /* 0xC8E */
    u16 count2;                    /* 0xC90 */
    s16 scroll;                    /* 0xC92 */
    s16 scrollTo;                  /* 0xC94 */
    u16 idle;                      /* 0xC96 */
    u8 padC98[0xCB6 - 0xC98];
    u8 sort[3];                    /* 0xCB6 */
    u8 sort2[3];                   /* 0xCB9 */
    u8 sort3;                      /* 0xCBC */
    u8 sort4;                      /* 0xCBD */
    u8 pstate[4];                  /* 0xCBE: per-player state bytes, [player] */
    char code[8];                  /* 0xCC2: password digits */
    u8 padCCA[0xD32 - 0xCCA];
    u8 dirty;                      /* 0xD32 */
    u8 padD33[0xD35 - 0xD33];
    u8 prevMode;                   /* 0xD35 */
    u8 sel;                        /* 0xD36 */
    u8 padD37[0xD57 - 0xD37];
    u8 step;                       /* 0xD57 */
    u8 padD58[0xD5C - 0xD58];
    u8 player;                     /* 0xD5C */
    u8 mode;                       /* 0xD5D */
    u8 row;                        /* 0xD5E */
    u8 row2;                       /* 0xD5F */
    u8 digit[3];                   /* 0xD60 */
    u8 hold;                       /* 0xD63 */
    struct {
        s8 dir1 : 2;               /* bits 0-1 */
        s8 dir2 : 2;               /* bits 2-3 */
        s8 b4 : 1;
        s8 b5 : 1;
        s8 b6 : 1;
        s8 b7 : 1;
    } dirs;                        /* 0xD64 */
    struct {
        s8 b0 : 1;
        s8 b1 : 1;
        s8 b2 : 1;
        s8 b3 : 1;
        s8 b4 : 1;
        s8 b5 : 1;
        s8 b6 : 1;
        s8 b7 : 1;
    } f65;                         /* 0xD65: one-bit flags (bit 0 first) */
    struct {
        s8 b0 : 1;
        u8 b1 : 1;                 /* read unsigned (lbu/dsrl32) */
        s8 b2 : 1;
        s8 b3 : 1;
        s8 b4 : 1;
        s8 b5 : 1;
        s8 b6 : 1;
        s8 b7 : 1;                 /* SzDuel_GetWindowDisp returns it */
    } f66;                         /* 0xD66 */
    struct {
        s8 b0 : 1;
        s8 b1 : 1;
        s8 b2 : 1;
        s8 b3 : 1;
        s8 b4 : 1;
        s8 b5 : 1;
        s8 b6 : 1;
        s8 b7 : 1;
    } f67;                         /* 0xD67 */
    u8 padD68[0xD70 - 0xD68];
} Duel_00317490_s;

/* The duel state: old code reads it as bytes (.b), new code by field (.s) */
typedef union Duel_00317490 {
    u8 b[0xD70];
    Duel_00317490_s s;
} Duel_00317490;

extern Duel_00317490 D_00317490;


typedef __int128 Q128_0020F290;
extern u8 D_0032A5E0[];
extern Q128_0020F290 D_0032A600;

extern u8 D_003506C8[];





extern u8 D_00325E80[];
extern u8 D_00325F50[];
extern s32 D_003261BC;


extern char D_002B90DA[];
extern char D_002B9102[];
extern char D_002B9112[];
extern char D_002B9127[];
extern char D_002B9135[];

extern s32 D_00317250;

extern s32 D_00317254;

extern s32 D_00317B68;

extern s32 D_00317B6C;


extern s32 D_0031BE98;

extern u8 D_003259C0[];

extern s32 D_0032618C;
extern s32 D_00326190;

extern s32 D_003261B0;
extern s32 D_003261B4;


extern s32 D_00350340;
extern s32 D_003505F8;




extern s32 D_0031BE9C;


extern u8 D_002D0655[];

extern volatile s32 D_00351170;

extern u8 D_0029D1F0[];

extern s16 D_00322990;
extern u16 D_00322992;
extern s16 D_00322994;

extern u8 D_00325CC0[];

extern u8 D_00325D38[];

extern s32 D_0032A240;

extern s32 D_0032F780;
extern s32 D_0032F784;
extern s32 D_0032F788;
extern s32 D_0032F78C;

extern char D_0030F8E9;



extern u8 D_0029D586[];


extern u8 D_0031A7C0[];
extern u16 D_002CE4A4[];





extern s64 D_002D0830[];


extern s8 D_0034F710;
extern s32 D_0029B2F0;
extern u8 D_00350620[];



extern u8 D_003193C0[];


extern s32 D_0030FF48;


extern s32 D_0031BEB0[];








typedef void (*Callback_00286910)(void);











extern u8 D_00350600[];
extern volatile s32 D_0035060C;


extern u16 D_002CD8A0[];
extern u8 D_00318E60[];







extern u8 D_0029D580[];








extern char D_0030F354[];
extern s32 D_003503B8;
extern s32 D_003505F0;
extern u8 D_00350680[];
extern u8 D_00350740[];
extern s32 D_00350788;

extern u16 D_0029CF32[];


extern u16 D_002D0970[51][41];

extern u8 D_00299F90[];


extern u8 D_002B90B0[];



extern char D_002BF002[];


extern char D_002BF040;


extern u32 D_0029E830[];







extern u64 D_00293EE0[];




extern s32 D_00292468;

extern u8 D_003181EC;

extern s8 D_00299E10;
extern s16 D_00299ED4;














extern char D_002B90C0[];
extern s32 D_0030FF58;
typedef struct { s32 src; s32 offset; s32 size; s32 position; s32 left; } cdstream_t;
extern cdstream_t D_0030FFA0;




extern s32 D_00325DD0;
extern s32 D_00325E2C;



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



extern f32 D_00294050[];


extern u8 D_00318280[];









extern s8 D_0034F700;
extern s8 D_0034F708;



extern s32 D_003180E8;

extern u8 D_0031747A;
extern s32 D_003180E4;
extern s32 D_0031810C;
extern s8 D_0031747B;


extern u8 D_003181E4;
extern u8 D_003181E2;

extern u8 D_003181E3;
extern s8 D_00318144;
extern s8 D_00318145;
extern s32 D_0031AB90;
extern s8 D_00318142;

extern s32 D_0031BB10;




extern s8 D_0031BEA2;

extern u8 D_0031BEA0;
extern s32 D_0031C2E4;
extern s32 D_003261D0;


extern s8 D_0031BEA1;
extern s32 D_0032A220;

extern s8 D_00299EDA;

extern s16 D_00299E4E;
extern char D_0030F3AE[];


extern s32 D_0031C048;


extern u8 D_003181CA;


s32 lSzDuel_DrawWindow_Frame_Pipe(s32, s32, s32, s32, s32, s32, s32, s32, s64);
extern char D_002BF00B;

extern s32 D_0028FF10[];
extern u8 D_002BE809[];
extern u8 D_002BE80F[];





extern char D_002BEF67[];















extern char D_002BEF98[];
extern char D_002BEF6F[];
extern char D_002BEF73[];
extern char D_002BE944[];
extern u8 D_003181C6;






extern u8 D_00325F00[];
extern Q128_0020F290 D_00325EF0;
extern u64 D_00326180;











extern f32 D_00291000;
extern f32 D_0029100C;
extern f32 D_00291020;
extern f32 D_002910B0;
extern f32 D_002910B8;




extern s32 (*D_00291330[])(s32, s32);

extern u8 D_002CCB48[];
extern u8 D_002CD1F4[];

extern u8 D_002909B8[];
extern u8 D_003181CC;





extern f32 D_00298BA4;


extern u8 D_0032A730[];


extern u8 D_0032A784[];


extern f32 D_00325D50;
extern f32 D_00325D54;
extern f32 D_00325D58;
extern f32 D_00325D60;
extern f32 D_00325D64;
extern f32 D_00325D68;
extern f32 D_00325D70;
extern f32 D_00325D74;
extern f32 D_00325D78;
extern f32 D_00325D90;
extern f32 D_00325D94;
extern f32 D_00325D98;
extern f32 D_00325DA0;
extern f32 D_00325DA4;
extern f32 D_00325DA8;
extern f32 D_00325DB0;
extern f32 D_00325DB4;
extern f32 D_00325DB8;

extern s16 D_00298260[];
extern s16 D_002982F8[];
extern s16 D_00298B50[];
extern s16 D_00298B76[];
extern s8 D_0030F102[];
extern s8 D_0030F107[];
extern s8 D_0030F10C[];
extern s8 D_0030F113[];
extern s8 D_0030F118[];




extern char D_0028C230[];



extern s32 D_0028FA98;

extern s32 D_0028D958;

extern s8 D_002BCA98;

extern s32 D_0028DC90;

extern s32 D_00310E98;

extern s32 D_0028D8F0;

extern s32 D_002BD230;




extern s32 D_0028CAA4;

extern u8 D_002BCB08[];

extern u8 D_002BCB38[];


extern u8 D_002BCB50[];


extern u8 D_002BCB88[];





















extern s32 D_0028F790;
extern s32 D_0028F794;
extern s32 D_00315C40;
extern s32 D_00317200;

extern s32 D_0028CA10;
extern s32 D_00310E94;

extern s32 D_0028CAA0;
extern s32 D_00313BA8;


extern s32 D_0028CAC0;
extern s32 D_00314028;


extern s32 D_0028D108;








extern s32 *D_00315C68;
extern s32 *D_00315C6C;
extern s32 *D_00315C70;



extern s32 D_0028CDF0;
extern s32 func_00184080;


extern s32 D_00315500;

extern s32 D_002BC900;
extern s32 D_002BC920;

extern s32 D_0028CA18;

extern s8 D_002BD0A0;
extern s32 D_00315CC0;



extern s32 D_0028DCE8;
extern s32 D_0028DD40;
extern s32 D_0028EE90;
extern s32 D_0028DCEC;
extern s32 D_0028EEC0;
extern s32 D_0028F708;


extern s32 D_002BC8A8;
extern s32 D_002BC8D0;

extern PadSlot_00192A88 D_003159D0[2][4];
extern s32 D_00315BC0;

extern s32 D_00310FC0;
extern s32 D_0028DA50;



typedef union { f32 value; u32 word; } fshape;

/* libgcc fp-bit.c (main_036): Cygnus built it for the r5900 with US_SOFTWARE_GOFAST and
   FLOAT_BIT_ORDER_MISMATCH, once for float (NO_NANS) and once for double. */
typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;
typedef struct { fp_class_type class; u32 sign; s32 normal_exp; u32 fraction; } fp_number_f;
typedef struct { fp_class_type class; u32 sign; s32 normal_exp; u64 fraction; } fp_number_d;
typedef union {
    f32 value;
    u32 value_raw;
#if defined(__GNUC__) && !defined(__MWERKS__) && !defined(M2CTX) && !defined(PERMUTER)
    struct {
        u32 fraction : 23 __attribute__((packed));
        u32 exp : 8 __attribute__((packed));
        u32 sign : 1 __attribute__((packed));
    } bits;
#endif
} fp_union_f;
typedef union {
    double value;
    u64 value_raw;
#if defined(__GNUC__) && !defined(__MWERKS__) && !defined(M2CTX) && !defined(PERMUTER)
    struct {
        u64 fraction : 52 __attribute__((packed));
        u32 exp : 11 __attribute__((packed));
        u32 sign : 1 __attribute__((packed));
    } bits;
#endif
} fp_union_d;
extern fp_number_d D_002BDF30; /* __thenan_df */
#if defined(__GNUC__) && !defined(__MWERKS__) && !defined(M2CTX) && !defined(PERMUTER)
/* fp-bit's INLINE predicates: a test of their int result compiles to xori/beqz */
static __inline__ s32 fp_isnan_f(fp_number_f *x) { return x->class == CLASS_SNAN || x->class == CLASS_QNAN; }
static __inline__ s32 fp_isinf_f(fp_number_f *x) { return x->class == CLASS_INFINITY; }
static __inline__ s32 fp_iszero_f(fp_number_f *x) { return x->class == CLASS_ZERO; }
static __inline__ s32 fp_isnan_d(fp_number_d *x) { return x->class == CLASS_SNAN || x->class == CLASS_QNAN; }
static __inline__ s32 fp_isinf_d(fp_number_d *x) { return x->class == CLASS_INFINITY; }
static __inline__ s32 fp_iszero_d(fp_number_d *x) { return x->class == CLASS_ZERO; }
#endif


extern s32 D_00310980;


extern s32 D_0028CAA8;
extern s32 D_0028CAAC;

extern s32 D_00310920;
extern s32 D_002BC1E8;
extern s32 D_0028F730;
extern s32 D_00315958;
extern s32 D_0028DCD0;
extern s32 D_002BCE58;
extern s32 D_002BCE88;

extern s32 D_002BCE70;

extern s32 D_00313E00;
extern s32 D_00314000;
extern s32 D_002BC9F8;
extern s32 D_0028F748;


extern char D_002BCA18[];

extern s32 D_001842C0;
extern s32 D_0028CDF8;

extern s32 D_0028D930;

extern s32 D_0028F750;
extern u8 D_002BD000;
extern s32 D_0028F770;

extern s32 D_0028F300;

extern s32 D_0028C24C;
extern s32 *D_0028CAC4;



typedef struct { void (*fn)(s32); s32 arg; } hcall_t;
extern s32 *D_0028D11C;

extern void (*D_0028CA0C)(s32);

extern s32 D_00316200;


typedef struct { u8 a; u8 b; } ringent_t;
typedef struct { s32 x0; u32 count; ringent_t e[0x200]; } ring_t;
extern s32 D_0028CA00;
extern s32 D_00310510;
extern s32 D_00310518;


extern s32 *D_0028CAB0;
extern s32 D_0028DCFC;
extern s32 D_003156C4;
extern s32 D_003156C8;
extern s32 D_0028DCE4;

extern s32 D_0028C254;

extern s32 D_003512F8;

typedef struct { u8 pad0[0xC]; s16 _flags; u8 pad1[0x58 - 0xE]; } nl_FILE;
typedef struct nl_glue { struct nl_glue *_next; s32 _niobs; nl_FILE *_iobs; } nl_glue;
typedef struct { u8 pad0[0x58]; } nl_mFILE;
typedef struct nl_mglue { struct nl_mglue *_next; s32 _niobs; nl_mFILE *_iobs; } nl_mglue;

extern s8 D_002BD0C1[];


typedef union { double value; struct { u32 lsw; u32 msw; } parts; } nl_dshape;

extern s32 D_002BC828;

extern s32 D_002BC9D0;

extern f32 D_002BE5D0[]; /* fdlibm kf_tan.c T[13] */

extern s32 D_002BC7C0;
extern s32 D_002BC7E8;

extern s32 D_002BE4C4[];  /* fdlibm ef_rem_pio2.c npio2_hw[] - 1 */
extern s32 D_002BE1B0[];  /* two_over_pi[] */

extern s32 D_00315CA0;
extern s32 D_00315CF0;


extern f32 D_002BE120[]; /* fdlibm ef_fmod.c Zero[] = { 0.0, -0.0 } */

extern s32 D_00316140;

extern f32 D_002BE608[]; /* fdlibm sf_atan.c atanhi[4] */
extern f32 D_002BE618[]; /* atanlo[4] */
extern f32 D_002BE628[]; /* aT[11] */

extern s32 D_0028DCD4;
extern s32 D_0028DCE0;
extern volatile s32 D_0028DCF0;
extern s32 D_0028DD14;
extern volatile s32 D_0028DD18;
extern char D_002BCBE8[];
extern void (*D_003156C0)(s32);
extern s32 D_003156CC;




extern f32 D_002BE128[]; /* fdlibm ef_pow.c bp[2] = { 1.0, 1.5 } */
extern f32 D_002BE130[]; /* dp_h[2] */
extern f32 D_002BE138[]; /* dp_l[2] */
extern f32 D_002BE1AC;   /* huge * huge, folded (the compiler kept it in rodata) */

extern s32 D_002BE570[]; /* fdlibm kf_rem_pio2.c init_jk[] = { 4, 7, 9 } */
extern f32 D_002BE580[]; /* PIo2[11] */


typedef struct i2b_Bigint { struct i2b_Bigint *next; s32 k, maxwds, sign, wds; u32 x[1]; } i2b_Bigint;


extern hcall_t D_00313C00;

extern s32 D_0028FF04;
extern s32 D_0028FF00;
extern s32 D_0028D114;

extern s32 D_002BCA78;

typedef struct mcmp_Bigint { struct mcmp_Bigint *next; s32 k, maxwds, sign, wds; u32 x[1]; } mcmp_Bigint;

extern double D_002BD288[]; /* mprec tens[] */

typedef struct vf_reent { u8 pad[0x38]; s32 __sdidinit; } vf_reent;
typedef struct vf_FILE { u8 pad[0x54]; vf_reent *_data; } vf_FILE;

typedef struct sread_FILE { u8 pad0[0xC]; s16 _flags; s16 _file; u8 pad1[0x40]; s32 _offset; s32 *_data; } sread_FILE;

typedef struct sseek_FILE { u8 pad0[0xC]; s16 _flags; s16 _file; u8 pad1[0x40]; s32 _offset; s32 *_data; } sseek_FILE;

typedef struct sprr_FILE { u8 *_p; s32 _r; s32 _w; s16 _flags; s16 _file; u8 *_bf_base; s32 _bf_size; s32 _lbfsize; void *_cookie; void *_read; void *_write; void *_seek; void *_close; u8 *_ub_base; s32 _ub_size; u8 *_up; s32 _ur; u8 _ubuf[3]; u8 _nbuf[1]; u8 *_lb_base; s32 _lb_size; s32 _blksize; s32 _offset; void *_data; } sprr_FILE;

typedef struct spr_FILE { u8 *_p; s32 _r; s32 _w; s16 _flags; s16 _file; u8 *_bf_base; s32 _bf_size; s32 _lbfsize; void *_cookie; void *_read; void *_write; void *_seek; void *_close; u8 *_ub_base; s32 _ub_size; u8 *_up; s32 _ur; u8 _ubuf[3]; u8 _nbuf[1]; u8 *_lb_base; s32 _lb_size; s32 _blksize; s32 _offset; void *_data; } spr_FILE;

typedef struct ssc_FILE { u8 *_p; s32 _r; s32 _w; s16 _flags; s16 _file; u8 *_bf_base; s32 _bf_size; s32 _lbfsize; void *_cookie; void *_read; void *_write; void *_seek; void *_close; u8 *_ub_base; s32 _ub_size; u8 *_up; s32 _ur; u8 _ubuf[3]; u8 _nbuf[1]; u8 *_lb_base; s32 _lb_size; s32 _blksize; s32 _offset; void *_data; } ssc_FILE;

extern char D_002BD270[]; /* "C" */
extern char D_002BD260[]; /* "" */


extern char ***D_0028FF08; /* p_environ */

typedef struct cal_chunk { u32 prev_size; u32 size; } cal_chunk;

extern s32 D_00312840;
extern s32 D_00313E08;
extern s32 D_00315D04;

typedef union { double d; u32 i[2]; } ratio_du;

typedef union { double d; u32 i[2]; } ulp_du;

extern s32 D_0028D970;

typedef struct fr_FILE { u8 *_p; s32 _r; } fr_FILE;



extern s32 D_0028DB80;
extern s32 D_0028DBC0;
extern s32 D_002BCAA8;


typedef struct p5_reent { u8 pad0[0x48]; i2b_Bigint *_p5s; } p5_reent;
extern s32 D_002BD274[];


typedef union b2d_du { double d; u32 i[2]; } b2d_du;

extern s32 D_002BC7A0;

typedef union cvt_du { double d; u32 i[2]; } cvt_du;





extern s32 D_002BCCD0;

extern s32 D_002BCCC0;


extern s32 D_002BC940;


extern s32 D_002BCAC0;
extern s32 D_002BCAE8;

extern s32 D_002BC808;

extern s8 D_002BC2D8;



extern s32 D_0028D118;


extern s32 D_0028CAB8;
extern s32 D_00313C40;
extern s32 D_00313C80;
extern s32 D_00313CC0;

extern s32 D_00313500;
extern s32 D_00313B80;




extern s32 D_0028CA08;
extern char D_00310D40[];

extern __int128 D_0028D9F0[];


extern s32 D_0028C250;
typedef struct { void *func; void *data; } SifCmdHandlerData;
extern SifCmdHandlerData *D_00310EA4;
extern SifCmdHandlerData *D_00310EAC;

extern const char D_002BD0C0[];
typedef struct su_reent { s32 _errno; } su_reent;

typedef struct sl_reent { s32 _errno; } sl_reent;

extern u32 D_0028DA78[];

extern s32 D_0028F74C;
extern char D_002BCEE0[];

extern char D_002BC670[];

extern s32 D_00317240;
extern char **D_0028F79C;

extern char D_002B9141[];
extern char D_002B9168[];
extern char D_0030FF60[];

extern u8 D_003261F0;

extern u8 D_00318200[];

extern s32 D_00350350;

extern s32 D_00326A20;


extern s32 D_00295060;

extern f32 D_01E01A80_b505;
extern f32 D_01E01A88_b505;

extern f32 D_01E01E00_b350;
extern f32 D_01E01E08_b350;

extern f32 D_01E03D00_b267;
extern f32 D_01E03D08_b267;
extern f32 D_01E02400_b850;
extern f32 D_01E02408_b850;

extern f32 D_01E03C00_b378;
extern f32 D_01E03C08_b378;
extern f32 D_01E03780_b195;
extern f32 D_01E03788_b195;
extern f32 D_01E03580_b266;
extern f32 D_01E03588_b266;
extern f32 D_01E02780_b294;
extern f32 D_01E02788_b294;

extern f32 D_01E02C80_b484;
extern f32 D_01E02C88_b484;

extern f32 D_01E02D00_b477;
extern f32 D_01E02D08_b477;
extern f32 D_01E03180_b397;
extern f32 D_01E03188_b397;

extern f32 D_01E02E00_b284;
extern f32 D_01E02E08_b284;

extern f32 D_01E03C00_b192;
extern f32 D_01E03C08_b192;
extern f32 D_01E03000_b566;
extern f32 D_01E03008_b566;
extern f32 D_01E03380_b513;
extern f32 D_01E03388_b513;
extern f32 D_01E02E00_b552;
extern f32 D_01E02E08_b552;
extern f32 D_01E03180_b297;
extern f32 D_01E03188_b297;

extern f32 D_01E03B80_b052;
extern f32 D_01E03B88_b052;

extern f32 D_01E03D00_b567;
extern f32 D_01E03D08_b567;
extern f32 D_01E04000_b555;
extern f32 D_01E04008_b555;

extern f32 D_01E03E80_b018;
extern f32 D_01E03E88_b018;
extern f32 D_01E03E80_b019;
extern f32 D_01E03E88_b019;
extern f32 D_01E04000_b080;
extern f32 D_01E04008_b080;
extern f32 D_01E04480_b734;
extern f32 D_01E04488_b734;
extern f32 D_01E04F00_b430;
extern f32 D_01E04F08_b430;

extern f32 D_01E03F80_b393;
extern f32 D_01E03F88_b393;

extern f32 D_01E04300_b046;
extern f32 D_01E04308_b046;

extern f32 D_01E05100_b225;
extern f32 D_01E05108_b225;

extern f32 D_01E04680_b527;
extern f32 D_01E04688_b527;
extern f32 D_01E04580_b257;
extern f32 D_01E04588_b257;
extern f32 D_01E05780_b582;
extern f32 D_01E05788_b582;
extern f32 D_01E04800_b476;
extern f32 D_01E04808_b476;

extern f32 D_01E05B80_b258;
extern f32 D_01E05B88_b258;
extern f32 D_01E05480_b573;
extern f32 D_01E05488_b573;
extern f32 D_01E05C80_b218;
extern f32 D_01E05C88_b218;

extern f32 D_01E04B00_b207;
extern f32 D_01E04B08_b207;

extern f32 D_01E05600_b718;
extern f32 D_01E05608_b718;

extern f32 D_01E05600_b383;
extern f32 D_01E05608_b383;
extern f32 D_01E05600_b148;
extern f32 D_01E05608_b148;
extern f32 D_01E06100_b709;
extern f32 D_01E06108_b709;
extern f32 D_01E05A00_b417;
extern f32 D_01E05A08_b417;
extern f32 D_01E06A00_b357;
extern f32 D_01E06A08_b357;

extern u8 D_912000[];
extern char D_002B8F00[], D_002B8F05[], D_002B8F07[], D_002B8F0D[], D_002B8F13[], D_002B8F18[];
extern char D_002B8F1F[], D_002B8F27[], D_002B8F2C[], D_002B8F32[];

extern s32 D_002BC768;

s32 func_00224E40(s32);
s32 func_0022F3C0(s32);
s32 func_002311D0(s32);
s32 func_002347D0(s32);
s32 func_002354A0(s32);
s32 func_00236C50(s32);
s32 Taku_Camp_BUN_DARE_b(s32, s8);
s32 Taku_Camp_BOTAN_MATI_b(s32);

extern s32 D_002BC858;

typedef struct { f32 x, y, z, w; } Vec4_00109830;

extern s32 D_00315640[];
extern s32 D_00315680;
extern s32 D_0028DCA4;
extern s32 D_0028DCA8;
extern s32 D_0028DCAC;
extern s32 D_0028DCB0;
extern s32 D_0028DCB4;
extern s32 D_0028DCB8;

extern char D_002BE940[];


#endif
