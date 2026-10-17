#include "common.h"

struct DotrCampSystemSpot {
    float x;
    float unknown_04;
    float y;
    unsigned char unknown_0c[8];
    short list[2][4];           
    short n;                    
    unsigned char unknown_26[14];
};
extern struct DotrCampSystemSpot model_data[];
struct DotrCampSystemBoard {
    signed char b0;             
    signed char b1;
    signed char b2;
    signed char lv[63];         
    short h66[32];
    short h130[32];
    short h194;                 
    short h196;
    signed char b198;
    signed char b199;
    signed char b200;
    signed char b201;
};
extern struct DotrCampSystemBoard D_00299E10_b;
struct DotrCampSystemRecord {
    float x[64];
    float y[64];
    short count;
    short flag;                 
};
struct DotrCampSystemBank {
    unsigned char unknown_0000[0x22c];
    struct DotrCampSystemRecord records[2][16];     
};
struct DotrCampSystemList {
    unsigned char unknown_00[70];
    short cell;                 
    short unknown_48[2];
};
extern struct DotrCampSystemList root_no[2][16];
extern int ACT2_Rock;
#define DOTR_CAMP_SYSTEM_BASE 0x1ed0000
#define DOTR_CAMP_SYSTEM_BANK ((struct DotrCampSystemBank *)0x1ed0000)
extern int func_00229140_b(int a, int b, int limit);
extern int func_002294B0_b(int side, int pick);
extern void func_00217980_b(int n, int b);
extern void func_00228940_b(int a, int b);
extern void func_00228660_b(int side, int row, int value, short *list, int count);
extern int func_00228F50_b(int side, int row);
#define WB(o) (*(signed char *)(DOTR_CAMP_SYSTEM_BASE + (o)))
#define WH(o) (*(short *)(DOTR_CAMP_SYSTEM_BASE + (o)))
#define WF(o) (*(float *)(DOTR_CAMP_SYSTEM_BASE + (o)))
#define BANK DOTR_CAMP_SYSTEM_BANK
#define COPY(K) n = spot[K].n; for (i = 0; i < n; i++) { buf[i] = spot[K].list[sd][i]; }
#define FLOATS WF(0x40) = WF(0x1b8); WF(0x48) = WF(0x1c0);
#define NAG(C, K, F) case C: COPY(K) Taku_Nagare2_set(side, K, buf, n, F); break;
#define NAG1(C, K) case C: buf[0] = spot[K].list[sd][0]; Taku_Nagare2_set(side, K, buf, 1, 0); break;
#define KM(C, K) case C: func_002294B0_b(side, K); break;
#define spot model_data

void Taku_Camp_System(void)
{
    extern void Taku_Nagare2_set(int side, int row, short *list, int count, int flag);
    struct DotrCampSystemBoard *b = &D_00299E10_b;
    int side = b->b0;
    short sd;
    short i;
    short n;
    short buf[8];

    if (WB(0x18c) != 0) {
        if (b->h194 < 200) {
            WB(0x537a) = 0;
            WB(0x537b) = 0;
            func_00229140_b(side, 0, 0);
        } else if (b->h194 < 300) {
            func_002294B0_b(side, b->b198);
        } else if (b->h194 < 400) {
            func_002294B0_b(side, b->b198);
        }
        WB(0x53b4) = 0;
        WB(0x53b5) = 0;
        WH(0x53b6) = 0;
        WH(0x53b8) = 0;
        if (WB(0x546c) == 0) {
            func_00217980_b(4, 1);
            WB(0x546c) = 1;
        }
        ACT2_Rock = 0;
        return;
    }
    if (b->h194 >= 100 && b->h194 < 200) {
        WB(0x537a) = 0;
        ACT2_Rock = 0;
    }
    if (b->h194 < 10000) {
        switch (b->h194) {
        case 104:
            break;
        default:
            if (WB(0x546c) == 0) {
                func_00217980_b(4, 1);
                WB(0x546c) = 1;
            }
            break;
        }
    }
    Taku_Camp_Ivent();
    sd = side;
    if (sd == 0) {
        switch (b->h194) {
        case 0:
            WB(0x537a) = 0;
            func_00229140_b(side, 0, 0);
            ACT2_Rock = 0;
            break;
        case 100:
            COPY(11)
            b->lv[11] = 1;
            switch (WH(0x536c)) {
            case 0:
                WH(0x1c) = 1;
                WH(0x1a) = 2;
                func_00228940_b(0, 0);
                func_00228660_b(side, 0, 0, buf, 1);
                b->b199 = 11;
                WH(0x536c)++;
                break;
            case 1:
                if (My_LedarModel_a_set(0) && Taku_Tyumoku_ido() && WH(0x1c) == 2) {
                    func_00228940_b(1, 0);
                    WH(0x536c)++;
                }
                break;
            case 2:
                FLOATS
                if (WH(0x1a4) == 3) {
                    func_00217980_b(27, 0);
                    WH(0x536c)++;
                    WB(0x537b)++;
                    WB(0x537d) = 1;
                }
                break;
            case 3:
                FLOATS
                if (b->lv[0] != 0) {
                    if (My_LedarModel_a_set(1)) {
                        WH(0x1c) = 1;
                        WH(0x1a) = 3;
                        WH(0x536c)++;
                    }
                }
                break;
            case 4:
                if (WB(0x537b) == 4) {
                    WB(0x537b)++;
                }
                if (WB(0x537b) == 12 && WH(0x1c) == 2) {
                    WB(0x537b) = 0;
                    WB(0x537d) = 0;
                    b->h194 = 11020;
                    WH(0x536c) = 0;
                }
                break;
            }
            b->lv[11] = 0;
            break;
        case 101:
            COPY(0)
            b->lv[0] = 1;
            switch (WH(0x536c)) {
            case 0:
                WF(0x40) = spot[0].x;
                WF(0x48) = spot[0].y;
                WH(0x1c) = 1;
                WH(0x1a) = 2;
                func_00228940_b(0, 1);
                buf[0] = 0;
                func_00228660_b(side, 0, 3, buf, 1);
                buf[0] = 1;
                buf[1] = 2;
                func_00228660_b(side, 1, 0, buf, 2);
                b->lv[0] = 0;
                WH(0x536c)++;
                return;
            case 1:
                if (My_LedarModel_a_set(0) && Taku_Tyumoku_ido() && WH(0x1c) == 2) {
                    func_00228940_b(1, 1);
                    WH(0x536c)++;
                }
                return;
            case 2:
                FLOATS
                if (WH(0x1a4) == 3) {
                    WH(0x536c)++;
                }
                return;
            case 3:
                FLOATS
                if (b->lv[1] != 0) {
                    if (My_LedarModel_a_set(1)) {
                        WH(0x1c) = 1;
                        WH(0x1a) = 0;
                        b->h194++;
                        WH(0x536c) = 0;
                    }
                }
                return;
            }
            break;
        NAG(102, 1, 0)
        NAG(103, 2, 1)
        NAG(104, 3, 1)
        NAG(105, 4, 1)
        NAG(106, 5, 1)
        NAG(107, 6, 1)
        NAG(108, 7, 0)
        NAG(109, 8, 1)
        case 110: func_00228F50_b(side, 9); func_00229140_b(0, 9, 0); break;
        case 111: func_00228F50_b(side, 10); func_00229140_b(0, 10, 0); break;
        case 112: func_00228F50_b(side, 11); func_00229140_b(0, 11, 0); break;
        case 113: func_00228F50_b(side, 11); func_00229140_b(0, 11, 0); break;
        KM(203, 2) KM(204, 3) KM(205, 4) KM(206, 5) KM(207, 6) KM(208, 7) KM(209, 8) KM(210, 9) KM(211, 10)
        case 212: b->b201 = 0; func_002294B0_b(side, 11); break;
        case 213: b->b201 = 1; func_002294B0_b(side, 11); break;
        KM(303, 2) KM(304, 3) KM(305, 4) KM(306, 5) KM(307, 6) KM(308, 7) KM(309, 8) KM(310, 9) KM(311, 10)
        case 312: b->b201 = 0; func_002294B0_b(side, 11); break;
        case 313: b->b201 = 1; func_002294B0_b(side, 11); break;
        }
    } else {
        switch (b->h194) {
        case 0:
            WB(0x537a) = 0;
            func_00229140_b(side, 0, 0);
            ACT2_Rock = 0;
            break;
        case 100:
            buf[0] = spot[11].list[sd][0];
            Taku_Nagare2_set(side, 11, buf, 1, 0);
            b->lv[11] = 0;
            break;
        NAG1(101, 12)
        NAG1(102, 13)
        NAG1(103, 14)
        case 104:
            buf[0] = spot[15].list[sd][0];
            b->lv[15] = 3;
            switch (WH(0x536c)) {
            case 0:
                WH(0x1c) = 1;
                WH(0x1a) = 2;
                WH(0x60) = 0;
                WB(0x5372) = 1;
                WB(0x5373) = 0;
                WB(0x537b) = 0;
                WB(0x53a0) = 0;
                WB(0x5375) = 0;
                func_00228940_b(0, 2);
                func_00228660_b(side, 15, 3, buf, 1);
                WH(0x536c)++;
                return;
            case 1:
                if (My_LedarModel_a_set(0) && Taku_Tyumoku_ido() && WH(0x1c) == 2) {
                    func_00228940_b(1, 2);
                    WH(0x536c)++;
                }
                return;
            case 2:
                FLOATS
                if (WH(0x1a4) == 3) {
                    WH(0x536c) = 0;
                    b->h194 = 12041;
                    b->b199 = 16;
                }
                return;
            case 3:
                FLOATS
                if (b->lv[spot[15].list[sd][buf[0]]] != 0) {
                    if (My_LedarModel_a_set(1)) {
                        WH(0x1c) = 1;
                        WH(0x1a) = 0;
                        BANK->records[sd][buf[0]].flag = 1;
                        WH(0x536c)++;
                    }
                }
                return;
            }
            break;
        case 105:
            buf[0] = spot[16].list[sd][0];
            buf[1] = spot[17].list[sd][0];
            b->lv[16] = 3;
            switch (WH(0x536c)) {
            case 0:
                WH(0x1c) = 0;
                WH(0x1a) = 2;
                WH(0x60) = 0;
                WB(0x5372) = 1;
                WB(0x5373) = 0;
                WB(0x537b) = 0;
                WB(0x53a0) = 0;
                WB(0x5375) = 0;
                func_00228940_b(0, 3);
                func_00228660_b(side, 16, 3, buf, 2);
                func_00228660_b(side, 17, 0, buf, 2);
                func_00217980_b(35, 1);
                b->b199 = 16;
                WH(0x536c)++;
                return;
            case 1:
                if (WH(0x6c) == 0) {
                    WH(0x1c) = 1;
                    WH(0x536c)++;
                }
                return;
            case 2:
                if (My_LedarModel_a_set(0) && Taku_Tyumoku_ido() && WH(0x1c) == 2) {
                    func_00228940_b(1, 3);
                    WH(0x536c)++;
                }
                return;
            case 3:
                FLOATS
                if (WH(0x1a4) == 3) {
                    WH(0x536c)++;
                    WB(0x537b)++;
                    WB(0x537d) = 1;
                    b->b199 = 17;
                }
                return;
            case 4:
                FLOATS
                if (b->lv[root_no[sd][buf[0]].cell] != 0) {
                    if (My_LedarModel_a_set(1)) {
                        WH(0x1c) = 1;
                        WH(0x1a) = 0;
                        BANK->records[sd][buf[0]].flag = 1;
                        b->h194++;
                        WH(0x536c) = 0;
                    }
                }
                return;
            }
            break;
        case 106:
            buf[0] = spot[17].list[sd][0];
            Taku_Nagare2_set(side, 17, buf, 1, 0);
            if (WB(0x546c) == 0) {
                func_00217980_b(4, 1);
                WB(0x546c) = 1;
            }
            break;
        NAG1(107, 18)
        NAG1(108, 19)
        NAG1(109, 20)
        NAG1(110, 21)
        case 111:
            buf[0] = spot[0].list[sd][0];
            switch (WH(0x536c)) {
            case 0:
                WH(0x1c) = 0;
                WH(0x1a) = 2;
                WH(0x60) = 0;
                WB(0x5372) = 1;
                WB(0x5373) = 0;
                WB(0x537b) = 0;
                WB(0x53a0) = 0;
                WB(0x5375) = 0;
                func_00228940_b(0, 4);
                func_00228660_b(side, 0, 3, buf, 1);
                b->lv[0] = 3;
                WH(0x536c)++;
                return;
            case 1:
                if (WH(0x6c) == 0) {
                    WH(0x1c) = 1;
                    WH(0x536c)++;
                }
                return;
            case 2:
                if (WH(0x1c) == 2) {
                    WB(0x537b)++;
                    WB(0x537d) = 1;
                    WB(0x5375) = 1;
                    WH(0x536c)++;
                }
                return;
            case 3:
                if (WB(0x537b) == 14) {
                    WB(0x537b) = 0;
                    WB(0x537d) = 0;
                    WH(0x536c)++;
                }
                return;
            case 4:
                if (My_LedarModel_a_set(0) && Taku_Tyumoku_ido()) {
                    func_00228940_b(1, 4);
                    WH(0x536c)++;
                }
                return;
            case 5:
                FLOATS
                if (WH(0x1a4) == 3) {
                    b->b199 = 11;
                    WH(0x536c)++;
                }
                return;
            case 6:
                FLOATS
                if (b->lv[11] != 0) {
                    if (My_LedarModel_a_set(1)) {
                        WH(0x1c) = 1;
                        WH(0x1a) = 0;
                        WH(0x536c)++;
                    }
                }
                return;
            case 7:
                if (WH(0x60) == 0) {
                    WF(0x50) = WF(0x40);
                    WF(0x58) = WF(0x48);
                }
                WF(0x40) = WF(0x50) * (float)(256 - WH(0x60)) / 256.0f + spot[11].x * (float)WH(0x60) / 256.0f;
                WF(0x48) = WF(0x58) * (float)(256 - WH(0x60)) / 256.0f + spot[11].y * (float)WH(0x60) / 256.0f;
                WH(0x60) += 16;
                if (WH(0x60) > 256) {
                    WH(0x60) = 0;
                    WF(0x50) = WF(0x40);
                    WF(0x58) = WF(0x48);
                    WB(0x5372) = 0;
                    WB(0x5375) = 0;
                    WH(0x536c)++;
                }
                return;
            case 8:
                WH(0x1c) = 1;
                WH(0x1a) = 3;
                WH(0x536c)++;
                return;
            case 9:
                if (WH(0x1c) == 2) {
                    WH(0x536c) = 0;
                    b->h194 = 12130;
                }
                return;
            }
            break;
        case 112: func_00228F50_b(side, 11); func_00229140_b(1, 11, 0); break;
        KM(201, 12) KM(202, 13) KM(203, 14) KM(205, 16) KM(207, 18) KM(208, 19) KM(209, 20) KM(210, 21) KM(211, 0)
        case 212: KM(213, 11)
        KM(301, 12) KM(302, 13) KM(303, 14) KM(305, 16) KM(307, 18) KM(308, 19) KM(309, 20) KM(310, 21) KM(311, 0)
        case 312: KM(313, 11)
        }
    }
}
#undef DOTR_CAMP_SYSTEM_BASE
#undef DOTR_CAMP_SYSTEM_BANK
#undef WB
#undef WH
#undef WF
#undef BANK
#undef COPY
#undef FLOATS
#undef NAG
#undef NAG1
#undef KM
#undef spot
