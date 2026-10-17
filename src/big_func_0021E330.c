#include "common.h"
#include "game.h"
#include "m2c_macros.h"

extern s16 D_00298C32;
extern s16 D_00298CD0;
extern f32 D_00298D0C;
extern f32 D_00298D14;
extern s16 D_00298D6A;
extern f32 D_00298DDC;
extern f32 D_00298DE4;
extern s16 D_00299ED2;
extern s8 D_0033F72C;

void Taku_Camp_Ivent(void) {
    u8 *ctx = (u8 *)&save_data;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_a1_3;
    s16 temp_a1_4;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_a2_3;
    s16 temp_a2_4;
    s16 temp_a2_5;
    s16 temp_a2_6;
    s16 temp_a2_7;
    s16 temp_a2_8;
    s16 temp_a2_9;
    s16 temp_v1;
    s16 temp_v1_10;
    s16 temp_v1_11;
    s16 temp_v1_12;
    s16 temp_v1_13;
    s16 temp_v1_14;
    s16 temp_v1_15;
    s16 temp_v1_16;
    s16 temp_v1_17;
    s16 temp_v1_18;
    s16 temp_v1_19;
    s16 temp_v1_20;
    s16 temp_v1_21;
    s16 temp_v1_22;
    s16 temp_v1_23;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 temp_v1_5;
    s16 temp_v1_6;
    s16 temp_v1_7;
    s16 temp_v1_8;
    s16 temp_v1_9;

    switch (D_00299ED2) {
        case 0x2724:                                /* switch 2 */
            temp_v1 = *(s16 *)0x01ED536C;
            switch (temp_v1) {                      /* switch 3 */
            case 0:                                 /* switch 3 */
                func_001F48F0(0, 0x190, 0, 0, 0);
                func_00217980(0x18, 1);
                *(f32 *)0x01ED0040 = 0;
                *(f32 *)0x01ED0048 = 0;
                *(s32 *)0x01ED004C = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 2;
                *(s8 *)0x01ED53B3 = 1;
                *(s8 *)0x01ED0062 = 0;
                *(s16 *)0x01ED0064 = 0x1000;
                *(s16 *)0x01ED53A2 = 1;
                *(s16 *)0x01ED53A4 = 0x1000;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s8 *)0x01ED53B4 = 0;
                *(s8 *)0x01ED53B5 = 0;
                *(s8 *)0x01ED53A6 = 0;
                *(s8 *)0x01ED53A7 = 0;
                *(s8 *)0x01ED546C = 0;
                *(s8 *)0x01ED546D = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            case 1:                                 /* switch 3 */
                if (*(s16 *)0x01ED001C == 2) {
                    *(s8 *)0x01ED537B = 1;
                    *(s8 *)0x01ED537D = 1;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            default:                                /* switch 3 */
dflt_3:
                goto end_0021E330;
            case 2:                                 /* switch 3 */
                if (*(s8 *)0x01ED537B == 0xC) {
                    *(s8 *)0x01ED537B = 0;
                    *(s8 *)0x01ED537D = 0;
                    *(s16 *)0x01ED53A2 = 2;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 3:                                 /* switch 3 */
                *(s8 *)0x01ED0062 = 2;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            case 4:                                 /* switch 3 */
                *(s16 *)0x01ED53A2 = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            case 5:                                 /* switch 3 */
                if (*(s16 *)0x01ED0064 < 0x7D0) {
                    if (*(s8 *)0x01ED546C == 0) {
                        func_00217980(0x19, 0);
                        *(s8 *)0x01ED546C = 1;
                    }
                }
                if (*(s16 *)0x01ED0064 < 0x50) {
                    *(s16 *)0x01ED53A2 = 0xA;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 6:                                 /* switch 3 */
                if (*(s16 *)0x01ED53A2 == 0xB) {
                    (*(s16 *)(ctx + 0xC2)) = 0x2738;
                    *(s16 *)0x01ED536C = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x2738:                                /* switch 2 */
            temp_v1_2 = *(s16 *)0x01ED536C;
            switch (temp_v1_2) {                    /* switch 4 */
            case 0:                                 /* switch 4 */
                func_001F48F0(0, 0x191, 0, 0, 0);
                *(f32 *)0x01ED0040 = 0;
                *(f32 *)0x01ED0048 = 0;
                *(s32 *)0x01ED004C = 0;
                func_00233F50(2);
                *(s8 *)0x01ED53B3 = 2;
                *(s8 *)0x01ED0062 = 0;
                *(s16 *)0x01ED0064 = 0x1000;
                *(s16 *)0x01ED53A2 = 0x14;
                *(s16 *)0x01ED53A4 = 0x1000;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s8 *)0x01ED53A6 = 0;
                *(s8 *)0x01ED53A7 = 0;
                *(s8 *)0x01ED546C = 0;
                *(s8 *)0x01ED5437 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            case 1:                                 /* switch 4 */
                if (*(s16 *)0x01ED53A2 == 0x15) {
                    func_00217710(0, 0x22);
                    func_00217710(0, 0x23);
                    *(s8 *)0x01ED0062 = 2;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 4 */
                if (*(s8 *)0x01ED0062 == 0) {
                    *(s16 *)0x01ED53A2 = 0x1E;
                    *(s16 *)0x01ED53A4 = 0;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 3:                                 /* switch 4 */
                if (*(s16 *)0x01ED53A2 == 0x1F) {
                    *(s16 *)0x01ED53A2 = 0x20;
                    *(s16 *)0x01ED53A4 = 0x1000;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 4:                                 /* switch 4 */
                if (*(s16 *)0x01ED53A2 == 0x21) {
                    func_00217980(0x19, 1);
                    *(s8 *)0x01ED537B = 1;
                    *(s8 *)0x01ED537D = 1;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 5:                                 /* switch 4 */
                if (*(s8 *)0x01ED537B == 0xC) {
                    *(s8 *)0x01ED537B = 0xD;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 6:                                 /* switch 4 */
                if (*(s8 *)0x01ED537B == 0xE) {
                    *(s16 *)0x01ED001C = 1;
                    *(s16 *)0x01ED001A = 0;
                    *(s8 *)0x01ED53B3 = 3;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 7:                                 /* switch 4 */
                if (*(s16 *)0x01ED001C == 2) {
                    *(s8 *)0x01ED537B = 0;
                    *(s8 *)0x01ED537D = 0;
                    *(s8 *)0x01ED53A6 = 1;
                    *(s8 *)0x01ED53A7 = 0;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 8:                                 /* switch 4 */
                if (*(s8 *)0x01ED53A6 == 4) {
                    *(s8 *)0x01ED53A6 = 0;
                    *(s16 *)0x01ED001C = 1;
                    *(s16 *)0x01ED001A = 2;
                    *(s8 *)0x01ED53B3 = 3;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 9:                                 /* switch 4 */
                if (*(s16 *)0x01ED001C == 2) {
                    *(s8 *)0x01ED537B = 0;
                    *(s8 *)0x01ED537D = 0;
                    *(s8 *)0x01ED53A6 = 0;
                    *(s8 *)0x01ED53A7 = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2739;
                    *(s16 *)0x01ED536C = 0;
                    goto end_0021E330;
                }
                break;
            default:                                    /* switch 4 */
                goto dflt_3;
            }
            break;
        case 0x2739:                                /* switch 2 */
            temp_a0 = *(s16 *)0x01ED536C;
            switch (temp_a0) {                      /* switch 5; irregular */
            case 0:                                 /* switch 5 */
                func_00233F50(2);
                *(s8 *)0x01ED53B3 = 3;
                *(s8 *)0x01ED0062 = 0;
                *(s16 *)0x01ED0064 = 0;
                *(s16 *)0x01ED53A2 = 0;
                *(s16 *)0x01ED53A4 = 0;
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s8 *)0x01ED53A6 = 0;
                *(s8 *)0x01ED53A7 = 0;
                *(s8 *)0x01ED5437 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            case 1:                                 /* switch 5 */
                if (*(s8 *)0x01ED537B == 0xC) {
                    *(s8 *)0x01ED537B = 0;
                    *(s8 *)0x01ED537D = 0;
                    *(s8 *)0x01ED53A6 = 0;
                    *(s8 *)0x01ED53A7 = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2742;
                    *(s16 *)0x01ED536C = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x2742:                                /* switch 2 */
            temp_v1_3 = *(s16 *)0x01ED536C;
            switch (temp_v1_3) {                    /* switch 6; irregular */
            case 0:                                 /* switch 6 */
                func_00233F50(2);
                *(s8 *)0x01ED53B3 = 3;
                *(s8 *)0x01ED0062 = 0;
                *(s16 *)0x01ED0064 = 0;
                *(s16 *)0x01ED53A2 = 0;
                *(s16 *)0x01ED53A4 = 0;
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s8 *)0x01ED53A6 = 0;
                *(s8 *)0x01ED53A7 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            case 1:                                 /* switch 6 */
                if (*(s8 *)0x01ED537B == 0xC) {
                    *(s8 *)0x01ED537B = 0;
                    *(s8 *)0x01ED537D = 0;
                    *(s8 *)0x01ED53A6 = 1;
                    *(s8 *)0x01ED53A7 = 0;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 6 */
                if (*(s8 *)0x01ED53A6 == 4) {
                    *(s8 *)0x01ED53A6 = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x274C;
                    *(s16 *)0x01ED536C = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x274C:                                /* switch 2 */
            temp_v1_4 = *(s16 *)0x01ED536C;
            switch (temp_v1_4) {                    /* switch 7; irregular */
            case 0:                                 /* switch 7 */
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 2;
                *(s8 *)0x01ED53B3 = 3;
                *(s8 *)0x01ED0062 = 0;
                *(s16 *)0x01ED0064 = 0;
                *(s16 *)0x01ED53A2 = 0;
                *(s16 *)0x01ED53A4 = 0;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s8 *)0x01ED53A6 = 0;
                *(s8 *)0x01ED53A7 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            case 1:                                 /* switch 7 */
                if (*(s16 *)0x01ED001C == 2) {
                    *(s8 *)0x01ED537B = 1;
                    *(s8 *)0x01ED537D = 1;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 7 */
                if (*(s8 *)0x01ED537B == 0xC) {
                    *(s8 *)0x01ED537B = 0;
                    *(s8 *)0x01ED537D = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2756;
                    *(s16 *)0x01ED536C = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x2756:                                /* switch 2 */
            temp_v1_5 = *(s16 *)0x01ED536C;
            switch (temp_v1_5) {                    /* switch 8; irregular */
            case 0:                                 /* switch 8 */
                func_00233F50(2);
                *(s8 *)0x01ED53B3 = 3;
                *(s8 *)0x01ED0062 = 0;
                *(s16 *)0x01ED0064 = 0;
                *(s16 *)0x01ED53A2 = 0;
                *(s16 *)0x01ED53A4 = 0;
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s8 *)0x01ED53A6 = 0;
                *(s8 *)0x01ED53A7 = 0;
                *(s8 *)0x01ED5494 = 0;
                *(s8 *)0x01ED5495 = 0;
                *(s16 *)0x01ED549A = 0;
                *(s16 *)0x01ED549C = -0x64;
                *(s16 *)0x01ED549E = -0xC8;
                *(s8 *)0x01ED5496 = 0;
                *(s8 *)0x01ED5497 = 0;
                *(s8 *)0x01ED5498 = 0;
                *(s8 *)0x01ED53A8 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            case 1:                                 /* switch 8 */
                if (*(s8 *)0x01ED537B == 0xC) {
                    *(s8 *)0x01ED537B = 0;
                    *(s8 *)0x01ED537D = 0;
                    *(s8 *)0x01ED53A6 = 1;
                    *(s8 *)0x01ED53A7 = 0;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 8 */
                if (*(s8 *)0x01ED53A6 == 4) {
                    *(s8 *)0x01ED53A6 = 4;
                    (*(s16 *)(ctx + 0xC2)) = 0x2757;
                    *(s16 *)0x01ED536C = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
    case 0x2757:
        temp_a0_2 = *(s16 *)0x01ED536C;
        switch (temp_a0_2) {
        case 0:
            func_00233F50(2);
            *(s8 *)0x01ED53B3 = 3;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s8 *)0x01ED53A6 = 4;
            *(s8 *)0x01ED53A7 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2760;
                *(s16 *)0x01ED536C = 0;
                func_00217980(0x1A, 0);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2760:                                    /* switch 1 */
        temp_v1_6 = *(s16 *)0x01ED536C;
        switch (temp_v1_6) {                        /* switch 9; irregular */
        case 0:                                     /* switch 9 */
            func_00233F50(2);
            *(s8 *)0x01ED53B3 = 3;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED546D = 0;
            *(s8 *)0x01ED546C = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 9 */
            if (*(s8 *)0x01ED537D == 3) {
                if ((*(s8 *)0x01ED537B == 5) && (*(s8 *)0x01ED546C == 0)) {
                    func_00217980(0x1A, 1);
                    *(s8 *)0x01ED546C = 1;
                }
            }
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s8 *)0x01ED53A8 = 1;
                (*(s16 *)(ctx + 0xC2)) = 0x276A;
                *(s16 *)0x01ED536C = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x276A:                                    /* switch 1 */
        temp_a2 = *(s16 *)0x01ED536C;
        switch (temp_a2) {                          /* switch 10; irregular */
        case 0:                                     /* switch 10 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            func_00217980(0x1A, 1);
            *(s8 *)0x01ED53B3 = 3;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            func_00217980(0x1A, 1);
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 10 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 10 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s8 *)0x01ED53A6 = 1;
                *(s8 *)0x01ED53A7 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 10 */
            if (*(s8 *)0x01ED53A6 == 4) {
                *(s8 *)0x01ED53A6 = 0;
                if (*(s8 *)0x01ED53A8 == 0) {
                    (*(s8 *)(ctx + 0)) = 1;
                    (*(s16 *)(ctx + 0xC2)) = 0x2EE0;
                    (*(s8 *)(ctx + 0xC9)) = 2;
                } else {
                    (*(s8 *)(ctx + 0)) = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2AF8;
                    (*(s8 *)(ctx + 0xC9)) = 0;
                }
                *(s16 *)0x01ED536C = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2AF8:                                    /* switch 1 */
        temp_a1 = *(s16 *)0x01ED536C;
        switch (temp_a1) {                          /* switch 11; irregular */
        case 0:                                     /* switch 11 */
            func_00233F50(2);
            *(s8 *)0x01ED53B3 = 3;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 11 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 11 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED53A2 = 0x16;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 11 */
            if (*(s16 *)0x01ED53A2 == 0x17) {
                func_00233F50(3);
                *(s8 *)0x01ED0062 = 0;
                *(s16 *)0x01ED0064 = 0;
                *(s16 *)0x01ED53A2 = 0;
                *(s16 *)0x01ED53A4 = 0;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s8 *)0x01ED53A6 = 0;
                *(s8 *)0x01ED53A7 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                func_001E7F70(3, 2, 0);
                func_001F93F0(0, 7, 0, NULL);
                func_001F6E80(7, 1.0f);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 11 */
            if (func_001FF300() == 0) {
                *(s8 *)0x01ED53B3 = 0;
                *(f32 *)0x01ED0040 = D_00298DDC;
                *(f32 *)0x01ED0048 = D_00298DE4;
                *(s16 *)0x01ED536C = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x64;
                func_00217980(4, 1);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B02:
        break;
    case 0x2B0C:                                    /* switch 1 */
        temp_v1_7 = *(s16 *)0x01ED536C;
        switch (temp_v1_7) {                        /* switch 12 */
        case 0:                                     /* switch 12 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 1;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED53AC = 1;
            *(s8 *)0x01ED5437 = 0;
            func_00217980(0x1B, 1);
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 12 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s16 *)0x01ED53AE = (s16) (*(s16 *)0x01ED53AE - 4);
                if (*(s16 *)0x01ED53AE < -0x280) {
                    *(s16 *)0x01ED53AE = -0x280;
                    if (*(s8 *)0x01ED53AC < 3) {
                        *(s8 *)0x01ED53AC = 2;
                        *(s8 *)0x01ED537E = 2;
                    }
                }
                if (*(s8 *)0x01ED53AC == 3) {
                    *(s16 *)0x01ED001C = 1;
                    *(s16 *)0x01ED001A = 2;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 12 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 12 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 12 */
            if (*(s8 *)0x01ED537B == 0xE) {
                func_00217980(4, 0);
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 12 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x65;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED53AC = 0;
                *(s16 *)0x01ED53AE = 0;
                *(s16 *)0x01ED53B0 = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 12 */
            goto dflt_3;
        }
        break;
    case 0x2B70:                                    /* switch 1 */
        temp_v1_8 = *(s16 *)0x01ED536C;
        switch (temp_v1_8) {                        /* switch 13; irregular */
        case 0:                                     /* switch 13 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED5483 = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            func_00217980(0x1C, 0);
            goto end_0021E330;
        case 1:                                     /* switch 13 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED5483 = 1;
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 13 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED5483 = 0;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 13 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B72;
                *(s16 *)0x01ED536C = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B72:                                    /* switch 1 */
        temp_a2_2 = *(s16 *)0x01ED536C;
        switch (temp_a2_2) {                        /* switch 14; irregular */
        case 0:                                     /* switch 14 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 1;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53B4 = 0;
            *(s8 *)0x01ED53B5 = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = -0x1C0;
            *(s8 *)0x01ED53AC = 1;
            func_00217980(0x1C, 1);
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 14 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s16 *)0x01ED53B0 = (s16) (*(s16 *)0x01ED53B0 + 4);
                if (*(s16 *)0x01ED53B0 > -0x50) {
                    *(s16 *)0x01ED53B0 = -0x50;
                    if (*(s8 *)0x01ED53AC < 3) {
                        *(s8 *)0x01ED53AC = 2;
                        *(s8 *)0x01ED537E = 2;
                    }
                }
                if (*(s8 *)0x01ED53AC == 3) {
                    *(s16 *)0x01ED001C = 1;
                    *(s16 *)0x01ED001A = 2;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 14 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 14 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 14 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B74;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED53AC = 0;
                *(s16 *)0x01ED53AE = 0;
                *(s16 *)0x01ED53B0 = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B74:                                    /* switch 1 */
        temp_a2_3 = *(s16 *)0x01ED536C;
        switch (temp_a2_3) {                        /* switch 15; irregular */
        case 0:                                     /* switch 15 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(f32 *)0x01ED0040 = D_00298D0C;
            *(f32 *)0x01ED0048 = D_00298D14;
            *(s16 *)0x01ED52FA = 0;
            *(s8 *)0x01ED5483 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 15 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED5483 = 1;
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 15 */
            if (*(s8 *)0x01ED537B == 0xC) {
                func_00217980(4, 0);
                *(s8 *)0x01ED5483 = 0;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 15 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s16 *)0x01ED1C5E = D_00298C32;
                *(s16 *)0x01ED1E62 = D_00298CD0;
                *(s16 *)0x01ED1A5A = D_00298D6A;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 15 */
            if (*(s16 *)0x01ED52FA == 1) {
                (*(s16 *)(ctx + 0xC2)) = 0;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED5374 = 0;
                *(s8 *)0x01ED5375 = 0;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED0060 = 0;
                *(s8 *)0x01ED5372 = 0;
                *(s8 *)0x01ED5373 = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B84:                                    /* switch 1 */
        temp_v1_9 = *(s16 *)0x01ED536C;
        switch (temp_v1_9) {                        /* switch 16 */
        case 0:                                     /* switch 16 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED5437 = 0;
            *(s8 *)0x01ED546C = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 16 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 16 */
            if (*(s8 *)0x01ED537D == 4) {
                if (*(s8 *)0x01ED546C == 0) {
                    func_00217980(0x1D, 0);
                    *(s8 *)0x01ED546C = 1;
                }
            }
            if (*(s8 *)0x01ED537D == 6) {
                if (*(s8 *)0x01ED546C < 2) {
                    func_00217980(0x1D, 1);
                    *(s8 *)0x01ED546C = 2;
                }
            }
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 16 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 16 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 16 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B86;
                *(s16 *)0x01ED536C = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 16 */
            goto dflt_3;
        }
        break;
    case 0x2B86:                                    /* switch 1 */
        temp_a2_4 = *(s16 *)0x01ED536C;
        switch (temp_a2_4) {                        /* switch 17; irregular */
        case 0:                                     /* switch 17 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 1;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53B4 = 0;
            *(s8 *)0x01ED53B5 = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED53AC = 1;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 17 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s16 *)0x01ED53B0 = (s16) (*(s16 *)0x01ED53B0 - 4);
                if (*(s16 *)0x01ED53B0 < -0x1C0) {
                    *(s16 *)0x01ED53B0 = -0x1C0;
                    if (*(s8 *)0x01ED53AC < 3) {
                        *(s8 *)0x01ED53AC = 2;
                        *(s8 *)0x01ED537E = 2;
                    }
                }
                if (*(s8 *)0x01ED53AC == 3) {
                    *(s16 *)0x01ED001C = 1;
                    *(s16 *)0x01ED001A = 2;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 17 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 17 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 17 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B87;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED53AC = 0;
                *(s16 *)0x01ED53AE = 0;
                *(s16 *)0x01ED53B0 = 0;
                func_00217980(0x1E, 0);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B87:                                    /* switch 1 */
        temp_v1_10 = *(s16 *)0x01ED536C;
        switch (temp_v1_10) {                       /* switch 18; irregular */
        case 0:                                     /* switch 18 */
            func_00233F50(3);
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s8 *)0x01ED53B4 = 0;
            *(s8 *)0x01ED53B5 = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 18 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2B88;
                *(s16 *)0x01ED536C = 0;
                func_00217980(0x1E, 1);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B88:                                    /* switch 1 */
        temp_v1_11 = *(s16 *)0x01ED536C;
        switch (temp_v1_11) {                       /* switch 19 */
        case 0:                                     /* switch 19 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 1;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53B4 = 0;
            *(s8 *)0x01ED53B5 = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED53AC = 1;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 19 */
            if (*(s16 *)0x01ED001C == 2) {
                if (*(s8 *)0x01ED53AC < 3) {
                    *(s8 *)0x01ED53AC = 2;
                    *(s8 *)0x01ED537E = 2;
                }
                if (*(s8 *)0x01ED53AC == 3) {
                    *(s16 *)0x01ED001C = 1;
                    *(s16 *)0x01ED001A = 2;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 19 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 19 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 1;
                *(s8 *)0x01ED53AC = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 19 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED54A0 = 1;
                *(s16 *)0x01ED54A2 = 0x80;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 19 */
            if (*(s8 *)0x01ED54A0 == 0xA) {
                if (*(s8 *)0x01ED53AC < 3) {
                    *(s8 *)0x01ED53AC = 2;
                    *(s8 *)0x01ED537E = 2;
                }
            }
            if (*(s8 *)0x01ED53AC == 3) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 19 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B8A;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED53AC = 0;
                *(s16 *)0x01ED53AE = 0;
                *(s16 *)0x01ED53B0 = 0;
                *(s16 *)0x01ED54A2 = 0x80;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 19 */
            goto dflt_3;
        }
        break;
    case 0x2B8A:                                    /* switch 1 */
        temp_a2_5 = *(s16 *)0x01ED536C;
        switch (temp_a2_5) {                        /* switch 20; irregular */
        case 0:                                     /* switch 20 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 1;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53B4 = 0;
            *(s8 *)0x01ED53B5 = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED53AC = 1;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 20 */
            if (*(s16 *)0x01ED001C == 2) {
                if (*(s8 *)0x01ED53AC < 3) {
                    *(s8 *)0x01ED53AC = 2;
                    *(s8 *)0x01ED537E = 2;
                }
                if (*(s8 *)0x01ED53AC == 3) {
                    *(s16 *)0x01ED001C = 1;
                    *(s16 *)0x01ED001A = 2;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 20 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 20 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 20 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B8B;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED53AC = 0;
                *(s16 *)0x01ED53AE = 0;
                *(s16 *)0x01ED53B0 = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B8B:                                    /* switch 1 */
        temp_a0_2 = *(s16 *)0x01ED536C;
        switch (temp_a0_2) {                        /* switch 21; irregular */
        case 0:                                     /* switch 21 */
            func_00233F50(3);
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 21 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2B8C;
                *(s16 *)0x01ED536C = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B8C:                                    /* switch 1 */
        temp_a2_6 = *(s16 *)0x01ED536C;
        switch (temp_a2_6) {                        /* switch 22; irregular */
        case 0:                                     /* switch 22 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED5483 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 22 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 22 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 22 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                (*(s16 *)(ctx + 0xC2)) = (s16) ((*(s16 *)(ctx + 0xC2)) + 1);
                *(s16 *)0x01ED536C = 0;
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 22 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x6C;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED53AC = 0;
                *(s16 *)0x01ED53AE = 0;
                *(s16 *)0x01ED53B0 = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B8D:                                    /* switch 1 */
        temp_v1_12 = *(s16 *)0x01ED536C;
        switch (temp_v1_12) {                       /* switch 23; irregular */
        case 0:                                     /* switch 23 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED5483 = 1;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 23 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED5483 = 0;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                func_00217980(4, 0);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 23 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x6C;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED53AC = 0;
                *(s16 *)0x01ED53AE = 0;
                *(s16 *)0x01ED53B0 = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B98:                                    /* switch 1 */
        temp_v1_13 = *(s16 *)0x01ED536C;
        switch (temp_v1_13) {                       /* switch 24 */
        case 0:                                     /* switch 24 */
            func_00217980(0x1F, 0);
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 3;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED546C = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 24 */
            if (*(s16 *)0x01ED001C == 2) {
                func_001E7F70(3, 0, 0);
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 24 */
            if (func_001FF300() == 0) {
                *(s8 *)0x01ED53B3 = 3;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 2;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 24 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 24 */
            if (*(s8 *)0x01ED537D == 3) {
                if (*(s8 *)0x01ED546C == 0) {
                    func_00217980(0x1F, 1);
                    *(s8 *)0x01ED546C = 1;
                }
            }
            if (*(s8 *)0x01ED537D == 0xD) {
                if (*(s8 *)0x01ED546C < 2) {
                    func_00217980(0x20, 1);
                    *(s8 *)0x01ED546C = 2;
                    *(s8 *)0x01ED547F = 1;
                    *(s8 *)0x01ED5480 = 0;
                }
            }
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 24 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 24 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B9A;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED53AC = 0;
                *(s16 *)0x01ED53AE = 0;
                *(s16 *)0x01ED53B0 = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 24 */
            goto dflt_3;
        }
        break;
    case 0x2B9A:                                    /* switch 1 */
        temp_v1_14 = *(s16 *)0x01ED536C;
        switch (temp_v1_14) {                       /* switch 25 */
        case 0:                                     /* switch 25 */
            func_001F48F0(0, 0x191, 0, 0, 0);
            *(f32 *)0x01ED0040 = 0;
            *(f32 *)0x01ED0048 = 0;
            *(s32 *)0x01ED004C = 0;
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            *(s8 *)0x01ED53B3 = 2;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0x1000;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED546E = 0;
            *(s16 *)0x01ED5470 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 25 */
            if (*(s16 *)0x01ED001C == 2) {
                func_00217710(0, 0x22);
                func_00217710(0, 0x23);
                *(s8 *)0x01ED0062 = 2;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 25 */
            if (*(s8 *)0x01ED0062 == 0) {
                *(s16 *)0x01ED53A2 = 0x1E;
                *(s16 *)0x01ED53A4 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 25 */
            if (*(s16 *)0x01ED53A2 == 0x1F) {
                *(s16 *)0x01ED53A2 = 0x20;
                *(s16 *)0x01ED53A4 = 0x1000;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 25 */
            if (*(s16 *)0x01ED53A2 == 0x21) {
                *(s8 *)0x01ED5437 = (s8) (*(s8 *)0x01ED5437 - 4);
                if (*(s8 *)0x01ED5437 < -0x63) {
                    *(s8 *)0x01ED5437 = -0x64;
                    *(s8 *)0x01ED546E = 1;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 5:                                     /* switch 25 */
            if ((*(s8 *)0x01ED546E == 5) && (*(s8 *)0x01ED547F == 4)) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                func_00217980(0x21, 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 25 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 7:                                     /* switch 25 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                func_00217980(4, 0);
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 8:                                     /* switch 25 */
            if (*(s16 *)0x01ED001C == 2) {
                func_001E7F70(3, 2, 0);
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 9:                                     /* switch 25 */
            if (func_001FF300() == 0) {
                *(s8 *)0x01ED53B3 = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                (*(s8 *)(ctx + 0xC9)) = 1;
                *(f32 *)0x01ED0040 = D_00298DDC;
                *(f32 *)0x01ED0048 = D_00298DE4;
                goto end_0021E330;
            }
            break;
        case 10:                                    /* switch 25 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s8 *)(ctx + 0xC9)) = 1;
                *(f32 *)0x01ED0040 = D_00298DDC;
                *(f32 *)0x01ED0048 = D_00298DE4;
                (*(s16 *)(ctx + 0xC2)) = 0x70;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED5374 = 1;
                *(s8 *)0x01ED5375 = 0;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED0060 = 0;
                *(s8 *)0x01ED5372 = 0;
                *(s8 *)0x01ED5373 = 0;
                *(s8 *)0x01ED546C = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 25 */
            goto dflt_3;
        }
        break;
    case 0x2BAC:                                    /* switch 1 */
        temp_v1_15 = *(s16 *)0x01ED536C;
        switch (temp_v1_15) {                       /* switch 26 */
        case 0:                                     /* switch 26 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 3;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED546E = 0;
            *(s16 *)0x01ED5470 = 0;
            *(s8 *)0x01ED547F = 0;
            *(s8 *)0x01ED5480 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 26 */
            if (*(s16 *)0x01ED001C == 2) {
                func_001E7F70(3, 0, 0);
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 26 */
            if (func_001FF300() == 0) {
                *(s8 *)0x01ED53B3 = 3;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 2;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 26 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 26 */
            if (*(s8 *)0x01ED537D == 3) {
                if ((*(s8 *)0x01ED537B == 3) && (*(s8 *)0x01ED546E == 0) && (*(s8 *)0x01ED5437 < -0x63)) {
                    *(s8 *)0x01ED546E = 1;
                    *(s16 *)0x01ED5470 = 0;
                    *(s8 *)0x01ED547F = 1;
                }
            }
            if ((*(s8 *)0x01ED537B == 0xC) && (*(s8 *)0x01ED546E == 5) && (*(s8 *)0x01ED547F == 4)) {
                *(s8 *)0x01ED537B = 0xD;
                *(s8 *)0x01ED547F = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 26 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s8 *)0x01ED546E = 0;
                *(s16 *)0x01ED5470 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 26 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2BAE;
                *(s16 *)0x01ED536C = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 26 */
            goto dflt_3;
        }
        break;
    case 0x2BAE:                                    /* switch 1 */
        temp_v1_16 = *(s16 *)0x01ED536C;
        switch (temp_v1_16) {                       /* switch 27 */
        case 0:                                     /* switch 27 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 1;
            *(s8 *)0x01ED53B3 = 3;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53B4 = 0;
            *(s8 *)0x01ED53B5 = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = -0x180;
            *(s8 *)0x01ED53AC = 1;
            func_00217980(0x22, 1);
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 27 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s16 *)0x01ED53AE = (s16) (*(s16 *)0x01ED53AE - 2);
                if (*(s16 *)0x01ED53AE < -0xC0) {
                    *(s16 *)0x01ED53AE = -0xC0;
                    if (*(s8 *)0x01ED53AC < 3) {
                        *(s8 *)0x01ED53AC = 2;
                        *(s8 *)0x01ED537E = 2;
                    }
                }
                temp_a1_2 = *(s16 *)0x01ED53AE;
                *(s16 *)0x01ED53B0 = (-temp_a1_2 * 0x180) / 384 - 0x180;
                if (*(s8 *)0x01ED53AC == 3) {
                    *(s16 *)0x01ED001C = 1;
                    *(s16 *)0x01ED001A = 2;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 27 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 27 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 1;
                *(s8 *)0x01ED53AC = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 27 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s16 *)0x01ED53AE = (s16) (*(s16 *)0x01ED53AE - 2);
                if (*(s16 *)0x01ED53AE < -0x180) {
                    *(s16 *)0x01ED53AE = -0x180;
                    if (*(s8 *)0x01ED53AC < 3) {
                        *(s8 *)0x01ED53AC = 2;
                        *(s8 *)0x01ED537E = 2;
                    }
                }
                temp_a1_3 = *(s16 *)0x01ED53AE;
                *(s16 *)0x01ED53B0 = (-temp_a1_3 * 0x180) / 384 - 0x180;
                if (*(s8 *)0x01ED53AC == 3) {
                    *(s16 *)0x01ED001C = 1;
                    *(s16 *)0x01ED001A = 3;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 5:                                     /* switch 27 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2BB0;
                *(s16 *)0x01ED536C = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 27 */
            goto dflt_3;
        }
        break;
    case 0x2BB0:                                    /* switch 1 */
        temp_v1_17 = *(s16 *)0x01ED536C;
        switch (temp_v1_17) {                       /* switch 28; irregular */
        case 0:                                     /* switch 28 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            *(s8 *)0x01ED53B3 = 1;
            *(f32 *)0x01ED0040 = 0;
            *(f32 *)0x01ED0048 = 0;
            *(s32 *)0x01ED004C = 0;
            *(s8 *)0x01ED0062 = 1;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53B4 = 0;
            *(s8 *)0x01ED53B5 = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = 0;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED5447 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto block_534;
        case 1:                                     /* switch 28 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            }
            goto block_534;
        case 2:                                     /* switch 28 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                (*(s16 *)(ctx + 0x3C)) = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            }
            goto block_534;
        case 3:                                     /* switch 28 */
            if (*(s16 *)0x01ED001C == 2) {
                if (*(s8 *)0x01ED543C == 0) {
                    (*(s8 *)(ctx + 1)) = 1;
                    if ((*(s8 *)(ctx + 1)) != 0) {
                        if ((*(s8 *)(ctx + 2)) != 0) {
                            func_00217230(0, 1);
                        }
                    }
                    func_001AAFA0(2);
                    *(s8 *)0x01ED543C = 1;
                }
                if (0 > func_001AB1D0()) {
                    *(s8 *)0x01ED543C = 0;
                    func_001A8360(2, 1, 0);
                    Move_END_flg = 1;
                    func_001A8320(0xA, 1);
                    func_001A8920();
                    goto block_534;
                }
            } else {
                goto block_534;
            }
            break;
        default:                                    /* switch 28 */
block_534:
            if (*(s16 *)0x01ED0064 > 0xBB8) {
                *(s16 *)0x01ED53A2 = 4;
            }
            if ((*(s16 *)0x01ED0064 > 0x7D0) && (*(s8 *)0x01ED5447 == 0)) {
                func_001F48F0(0, 0x192, 0, 0, 0);
                *(s8 *)0x01ED5447 = 1;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2EE0:                                    /* switch 1 */
        temp_v1_18 = *(s16 *)0x01ED536C;
        switch (temp_v1_18) {                       /* switch 29; irregular */
        case 0:                                     /* switch 29 */
            func_00233F50(2);
            *(s8 *)0x01ED53B3 = 3;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED546E = 0;
            *(s16 *)0x01ED5470 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 29 */
            if (*(s8 *)0x01ED537D == 4) {
                if ((*(s8 *)0x01ED537B == 3) && (*(s8 *)0x01ED546E == 0)) {
                    *(s8 *)0x01ED546E = 1;
                    *(s16 *)0x01ED5470 = 0;
                }
            }
            if ((*(s8 *)0x01ED537B == 0xC) && (*(s8 *)0x01ED546E == 5)) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 29 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED53A2 = 0x16;
                *(s8 *)0x01ED546E = 0;
                *(s16 *)0x01ED5470 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 29 */
            if (*(s16 *)0x01ED53A2 == 0x17) {
                func_00233F50(3);
                *(s8 *)0x01ED0062 = 0;
                *(s16 *)0x01ED0064 = 0;
                *(s16 *)0x01ED53A2 = 0;
                *(s16 *)0x01ED53A4 = 0;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s8 *)0x01ED53A6 = 0;
                *(s8 *)0x01ED53A7 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                func_001E7F70(3, 2, 0);
                func_001F93F0(0, 7, 0, NULL);
                func_001F6E80(7, 1.0f);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 29 */
            if (func_001FF300() == 0) {
                *(s8 *)0x01ED53B3 = 0;
                *(f32 *)0x01ED0040 = D_00298DDC;
                *(f32 *)0x01ED0048 = D_00298DE4;
                *(s16 *)0x01ED536C = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x64;
                func_00217980(4, 1);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F08:                                    /* switch 1 */
        temp_v1_19 = *(s16 *)0x01ED536C;
        switch (temp_v1_19) {                       /* switch 30; irregular */
        case 0:                                     /* switch 30 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            func_00217980(0x23, 1);
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 30 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 30 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED536C = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x68;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F09:                                    /* switch 1 */
        temp_a1_4 = *(s16 *)0x01ED536C;
        switch (temp_a1_4) {                        /* switch 31; irregular */
        case 0:                                     /* switch 31 */
            func_00233F50(2);
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 31 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 31 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED530C = 2;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 31 */
            if ((*(s16 *)0x01ED530C == 0) && (func_0022C3C0(1) != 0)) {
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 31 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0;
                *(s16 *)0x01ED536C = 0;
                *(s8 *)0x01ED5374 = 0;
                *(s8 *)0x01ED5375 = 0;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED0060 = 0;
                *(s8 *)0x01ED5372 = 0;
                *(s8 *)0x01ED5373 = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F62:                                    /* switch 1 */
        temp_v1_20 = *(s16 *)0x01ED536C;
        switch (temp_v1_20) {                       /* switch 32 */
        case 0:                                     /* switch 32 */
            func_00233F50(3);
            *(s8 *)0x01ED53B3 = 3;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            func_00217980(0x24, 1);
            func_001E7F70(3, 0, 0);
            *(s8 *)0x01ED547F = 0;
            *(s8 *)0x01ED5480 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 32 */
            if (func_001FF300() == 0) {
                *(s8 *)0x01ED53B3 = 3;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 2;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 32 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 32 */
            if (*(s8 *)0x01ED537D == 2) {
                if (*(s8 *)0x01ED537B == 3) {
                    *(s8 *)0x01ED547F = 1;
                }
            }
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 32 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 32 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s16 *)0x01ED536C = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2F64;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 32 */
            goto dflt_3;
        }
        break;
    case 0x2F64:                                    /* switch 1 */
        temp_v1_21 = *(s16 *)0x01ED536C;
        switch (temp_v1_21) {                       /* switch 33 */
        case 0:                                     /* switch 33 */
            func_001F48F0(0, 0x191, 0, 0, 0);
            *(f32 *)0x01ED0040 = 0;
            *(f32 *)0x01ED0048 = 0;
            *(s32 *)0x01ED004C = 0;
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            *(s8 *)0x01ED53B3 = 2;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0x1000;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED546E = 0;
            *(s16 *)0x01ED5470 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 33 */
            if (*(s16 *)0x01ED001C == 2) {
                func_00217710(0, 0x22);
                func_00217710(0, 0x23);
                *(s8 *)0x01ED0062 = 2;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 33 */
            if (*(s8 *)0x01ED0062 == 0) {
                *(s16 *)0x01ED53A2 = 0x1E;
                *(s16 *)0x01ED53A4 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 33 */
            if (*(s16 *)0x01ED53A2 == 0x1F) {
                *(s16 *)0x01ED53A2 = 0x20;
                *(s16 *)0x01ED53A4 = 0x1000;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 33 */
            if (*(s16 *)0x01ED53A2 == 0x21) {
                *(s8 *)0x01ED5437 = (s8) (*(s8 *)0x01ED5437 - 4);
                if (*(s8 *)0x01ED5437 < -0x63) {
                    *(s8 *)0x01ED5437 = -0x64;
                    *(s8 *)0x01ED546E = 1;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 5:                                     /* switch 33 */
            if ((*(s8 *)0x01ED546E == 5) && (*(s8 *)0x01ED547F == 4)) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                func_00217980(0x21, 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 33 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 7:                                     /* switch 33 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                func_00217980(4, 0);
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 8:                                     /* switch 33 */
            if (*(s16 *)0x01ED001C == 2) {
                func_001E7F70(3, 2, 0);
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 9:                                     /* switch 33 */
            if (func_001FF300() == 0) {
                *(s8 *)0x01ED53B3 = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 0;
                *(f32 *)0x01ED0040 = D_00298DDC;
                *(f32 *)0x01ED0048 = D_00298DE4;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 10:                                    /* switch 33 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s16 *)0x01ED536C = 0;
                (*(s16 *)(ctx + 0xC2)) = 0;
                *(s8 *)0x01ED5374 = 0;
                *(s8 *)0x01ED5375 = 0;
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED0060 = 0;
                *(s8 *)0x01ED5372 = 0;
                *(s8 *)0x01ED5373 = 0;
                *(s8 *)0x01ED546C = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 33 */
            goto dflt_3;
        }
        break;
    case 0x2F76:                                    /* switch 1 */
        temp_a2_7 = *(s16 *)0x01ED536C;
        switch (temp_a2_7) {                        /* switch 34; irregular */
        case 0:                                     /* switch 34 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 3;
            *(s8 *)0x01ED53B3 = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED546E = 0;
            *(s16 *)0x01ED5470 = 0;
            *(s8 *)0x01ED547F = 0;
            *(s8 *)0x01ED5480 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 34 */
            if (*(s16 *)0x01ED001C == 2) {
                func_001E7F70(3, 0, 0);
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 34 */
            if (func_001FF300() == 0) {
                *(s8 *)0x01ED53B3 = 3;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 2;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 34 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 34 */
            if (*(s8 *)0x01ED537D == 2) {
                if ((*(s8 *)0x01ED546E == 0) && (*(s8 *)0x01ED5437 < -0x63)) {
                    *(s8 *)0x01ED546E = 1;
                    *(s16 *)0x01ED5470 = 0;
                    *(s8 *)0x01ED547F = 1;
                }
            }
            if ((*(s8 *)0x01ED537B == 0xC) && (*(s8 *)0x01ED546E == 5) && (*(s8 *)0x01ED547F == 4)) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED536C = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2F78;
                *(s8 *)0x01ED546E = 0;
                *(s16 *)0x01ED5470 = 0;
                *(s8 *)0x01ED547F = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F78:                                    /* switch 1 */
        temp_a2_8 = *(s16 *)0x01ED536C;
        switch (temp_a2_8) {                        /* switch 35; irregular */
        case 0:                                     /* switch 35 */
            func_00233F50(2);
            *(s8 *)0x01ED53B3 = 3;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            func_00217980(0x25, 1);
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 35 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 35 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 35 */
            if (*(s16 *)0x01ED001C == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2F7A;
                *(s16 *)0x01ED536C = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F7A:                                    /* switch 1 */
        temp_v1_22 = *(s16 *)0x01ED536C;
        switch (temp_v1_22) {                       /* switch 36 */
        case 0:                                     /* switch 36 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 1;
            *(s8 *)0x01ED53B3 = 1;
            *(f32 *)0x01ED0040 = 0;
            *(f32 *)0x01ED0048 = 0;
            *(s32 *)0x01ED004C = 0;
            *(s8 *)0x01ED0062 = 0;
            *(s16 *)0x01ED0064 = 0;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED53AC = 0;
            *(s16 *)0x01ED53AE = -0x180;
            *(s16 *)0x01ED53B0 = 0;
            *(s8 *)0x01ED53AC = 1;
            *(s8 *)0x01ED54A0 = 0;
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto end_0021E330;
        case 1:                                     /* switch 36 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s16 *)0x01ED53AE = (s16) (*(s16 *)0x01ED53AE + 2);
                if (0 < *(s16 *)0x01ED53AE) {
                    *(s16 *)0x01ED53AE = 0;
                    if (*(s8 *)0x01ED53AC < 3) {
                        *(s8 *)0x01ED53AC = 2;
                        *(s8 *)0x01ED537E = 2;
                    }
                }
                temp_a2_9 = *(s16 *)0x01ED53AE;
                *(s16 *)0x01ED53B0 = (-temp_a2_9 * 0x19C) / 384 - 0x19C;
                if (*(s8 *)0x01ED53AC == 3) {
                    *(s16 *)0x01ED001C = 1;
                    *(s16 *)0x01ED001A = 2;
                    *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 36 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 36 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0xD;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 36 */
            if (*(s8 *)0x01ED537B == 0xE) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s8 *)0x01ED54A0 = 1;
                *(s16 *)0x01ED54A2 = 0x80;
                *(s8 *)0x01ED0062 = 1;
                *(s16 *)0x01ED0064 = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 36 */
            if (*(s8 *)0x01ED54A0 == 0xA) {
                (*(s16 *)(ctx + 0xC2)) = 0x2F7C;
                *(s16 *)0x01ED536C = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 36 */
            goto dflt_3;
        }
        break;
    case 0x2F7C:                                    /* switch 1 */
        temp_v1_23 = *(s16 *)0x01ED536C;
        switch (temp_v1_23) {                       /* switch 37; irregular */
        case 0:                                     /* switch 37 */
            *(s16 *)0x01ED001C = 1;
            *(s16 *)0x01ED001A = 2;
            *(s8 *)0x01ED53B3 = 1;
            *(f32 *)0x01ED0040 = 0;
            *(f32 *)0x01ED0048 = 0;
            *(s32 *)0x01ED004C = 0;
            *(s8 *)0x01ED0062 = 1;
            *(s16 *)0x01ED53A2 = 0;
            *(s16 *)0x01ED53A4 = 0;
            *(s8 *)0x01ED537B = 0;
            *(s8 *)0x01ED537D = 0;
            *(s8 *)0x01ED53B4 = 0;
            *(s8 *)0x01ED53B5 = 0;
            *(s8 *)0x01ED53A6 = 0;
            *(s8 *)0x01ED53A7 = 0;
            *(s8 *)0x01ED5447 = 0;
            func_00217980(0x26, 1);
            *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            goto block_727;
        case 1:                                     /* switch 37 */
            if (*(s16 *)0x01ED001C == 2) {
                *(s8 *)0x01ED537B = 1;
                *(s8 *)0x01ED537D = 1;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            }
            goto block_727;
        case 2:                                     /* switch 37 */
            if (*(s8 *)0x01ED537B == 0xC) {
                *(s8 *)0x01ED537B = 0;
                *(s8 *)0x01ED537D = 0;
                *(s16 *)0x01ED001C = 1;
                *(s16 *)0x01ED001A = 3;
                (*(s16 *)(ctx + 0x3C)) = 0;
                *(s16 *)0x01ED536C = (s16) (*(s16 *)0x01ED536C + 1);
            }
            goto block_727;
        case 3:                                     /* switch 37 */
            if (*(s16 *)0x01ED001C == 2) {
                if (*(s8 *)0x01ED543C == 0) {
                    (*(s8 *)(ctx + 2)) = 1;
                    if ((*(s8 *)(ctx + 1)) != 0) {
                        if ((*(s8 *)(ctx + 2)) != 0) {
                            func_00217230(0, 1);
                        }
                    }
                    func_001AAFA0(2);
                    *(s8 *)0x01ED543C = 1;
                }
                if (0 > func_001AB1D0()) {
                    *(s8 *)0x01ED543C = 0;
                    func_001A8360(3, 1, 0);
                    Move_END_flg = 1;
                    func_001A8320(0xA, 1);
                    func_001A8920();
                    (*(s16 *)(ctx + 0xC2)) = 0;
                    goto block_727;
                }
            } else {
                goto block_727;
            }
            break;
        default:                                    /* switch 37 */
block_727:
            if (*(s16 *)0x01ED0064 > 0xBB8) {
                *(s16 *)0x01ED53A2 = 4;
            }
            if ((*(s16 *)0x01ED0064 > 0x7D0) && (*(s8 *)0x01ED5447 == 0)) {
                func_001F48F0(0, 0x192, 0, 0, 0);
                *(s8 *)0x01ED5447 = 1;
                goto end_0021E330;
            }
            break;
        }
        break;
    default:
        *(s8 *)0x01ED53B3 = 0;
        break;
    }
end_0021E330:;
}
