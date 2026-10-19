/* Campaign map, part 1 of 3: the campaign system and its events (Taku_*, TkCamp_*). */

#include "common.h"
#include "campaign.h"

struct DotrCampSystemSpot {
    float x;
    float unknown_04;
    float y;
    unsigned char unknown_0c[8];
    short list[2][4];           
    short n;                    
    unsigned char unknown_26[14];
};
extern struct DotrCampSystemSpot campaignPlaces[]; /* original: model_data */
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
struct DotrCampSystemList {
    unsigned char unknown_00[70];
    short cell;                 
    short unknown_48[2];
};
extern struct DotrCampSystemList campaignRoutes[2][16]; /* original: root_no */
extern int campaignAct2Lock; /* original: ACT2_Rock */
extern int func_00229140_b(int a, int b, int limit);
extern int func_002294B0_b(int side, int pick);
extern void func_00217980_b(int n, int b);
extern void func_00228940_b(int a, int b);
extern void func_00228660_b(int side, int row, int value, short *list, int count);
extern int func_00228F50_b(int side, int row);
#define COPY(K) n = spot[K].n; for (i = 0; i < n; i++) { buf[i] = spot[K].list[sd][i]; }
#define FLOATS campaignWork.cameraTarget[0] = campaignWork.shipPos[0]; campaignWork.cameraTarget[2] = campaignWork.shipPos[2];
#define NAG(C, K, F) case C: COPY(K) Taku_Flow2_set(side, K, buf, n, F); break;
#define NAG1(C, K) case C: buf[0] = spot[K].list[sd][0]; Taku_Flow2_set(side, K, buf, 1, 0); break;
#define KM(C, K) case C: func_002294B0_b(side, K); break;
#define spot campaignPlaces

/* Runs one frame of the campaign map: the cursor, moving between places, the flows and routes, the windows, the
   events. */
void Taku_Camp_System(void)
{
    extern void Taku_Flow2_set(int side, int row, short *list, int count, int flag);
    struct DotrCampSystemBoard *b = &D_00299E10_b;
    int side = b->b0;
    short sd;
    short i;
    short n;
    short buf[8];

    if (campaignWork.unk018C != 0) {
        if (b->h194 < 200) {
            campaignWork.unk537A = 0;
            campaignWork.talkStep = 0;
            func_00229140_b(side, 0, 0);
        } else if (b->h194 < 300) {
            func_002294B0_b(side, b->b198);
        } else if (b->h194 < 400) {
            func_002294B0_b(side, b->b198);
        }
        campaignWork.unk53B4 = 0;
        campaignWork.unk53B5 = 0;
        campaignWork.duelistSlide[0] = 0;
        campaignWork.duelistSlide[1] = 0;
        if (campaignWork.unk546C == 0) {
            func_00217980_b(4, 1);
            campaignWork.unk546C = 1;
        }
        campaignAct2Lock = 0;
        return;
    }
    if (b->h194 >= 100 && b->h194 < 200) {
        campaignWork.unk537A = 0;
        campaignAct2Lock = 0;
    }
    if (b->h194 < 10000) {
        switch (b->h194) {
        case 104:
            break;
        default:
            if (campaignWork.unk546C == 0) {
                func_00217980_b(4, 1);
                campaignWork.unk546C = 1;
            }
            break;
        }
    }
    Taku_Camp_Event();
    sd = side;
    if (sd == 0) {
        switch (b->h194) {
        case 0:
            campaignWork.unk537A = 0;
            func_00229140_b(side, 0, 0);
            campaignAct2Lock = 0;
            break;
        case 100:
            COPY(11)
            b->lv[11] = 1;
            switch (campaignWork.eventStep) {
            case 0:
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                func_00228940_b(0, 0);
                func_00228660_b(side, 0, 0, buf, 1);
                b->b199 = 11;
                campaignWork.eventStep++;
                break;
            case 1:
                if (My_LeaderModel_a_set(0) && Taku_Focus_move() && campaignWork.cinemaState == 2) {
                    func_00228940_b(1, 0);
                    campaignWork.eventStep++;
                }
                break;
            case 2:
                FLOATS
                if (campaignWork.shipState == 3) {
                    func_00217980_b(27, 0);
                    campaignWork.eventStep++;
                    campaignWork.talkStep++;
                    campaignWork.talkPage = 1;
                }
                break;
            case 3:
                FLOATS
                if (b->lv[0] != 0) {
                    if (My_LeaderModel_a_set(1)) {
                        campaignWork.cinemaState = 1;
                        campaignWork.cinemaMode = 3;
                        campaignWork.eventStep++;
                    }
                }
                break;
            case 4:
                if (campaignWork.talkStep == 4) {
                    campaignWork.talkStep++;
                }
                if (campaignWork.talkStep == 12 && campaignWork.cinemaState == 2) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    b->h194 = 11020;
                    campaignWork.eventStep = 0;
                }
                break;
            }
            b->lv[11] = 0;
            break;
        case 101:
            COPY(0)
            b->lv[0] = 1;
            switch (campaignWork.eventStep) {
            case 0:
                campaignWork.cameraTarget[0] = spot[0].x;
                campaignWork.cameraTarget[2] = spot[0].y;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                func_00228940_b(0, 1);
                buf[0] = 0;
                func_00228660_b(side, 0, 3, buf, 1);
                buf[0] = 1;
                buf[1] = 2;
                func_00228660_b(side, 1, 0, buf, 2);
                b->lv[0] = 0;
                campaignWork.eventStep++;
                return;
            case 1:
                if (My_LeaderModel_a_set(0) && Taku_Focus_move() && campaignWork.cinemaState == 2) {
                    func_00228940_b(1, 1);
                    campaignWork.eventStep++;
                }
                return;
            case 2:
                FLOATS
                if (campaignWork.shipState == 3) {
                    campaignWork.eventStep++;
                }
                return;
            case 3:
                FLOATS
                if (b->lv[1] != 0) {
                    if (My_LeaderModel_a_set(1)) {
                        campaignWork.cinemaState = 1;
                        campaignWork.cinemaMode = 0;
                        b->h194++;
                        campaignWork.eventStep = 0;
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
            campaignWork.unk537A = 0;
            func_00229140_b(side, 0, 0);
            campaignAct2Lock = 0;
            break;
        case 100:
            buf[0] = spot[11].list[sd][0];
            Taku_Flow2_set(side, 11, buf, 1, 0);
            b->lv[11] = 0;
            break;
        NAG1(101, 12)
        NAG1(102, 13)
        NAG1(103, 14)
        case 104:
            buf[0] = spot[15].list[sd][0];
            b->lv[15] = 3;
            switch (campaignWork.eventStep) {
            case 0:
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 1;
                campaignWork.leaderShow = 0;
                campaignWork.talkStep = 0;
                campaignWork.unk53A0 = 0;
                campaignWork.unk5375 = 0;
                func_00228940_b(0, 2);
                func_00228660_b(side, 15, 3, buf, 1);
                campaignWork.eventStep++;
                return;
            case 1:
                if (My_LeaderModel_a_set(0) && Taku_Focus_move() && campaignWork.cinemaState == 2) {
                    func_00228940_b(1, 2);
                    campaignWork.eventStep++;
                }
                return;
            case 2:
                FLOATS
                if (campaignWork.shipState == 3) {
                    campaignWork.eventStep = 0;
                    b->h194 = 12041;
                    b->b199 = 16;
                }
                return;
            case 3:
                FLOATS
                if (b->lv[spot[15].list[sd][buf[0]]] != 0) {
                    if (My_LeaderModel_a_set(1)) {
                        campaignWork.cinemaState = 1;
                        campaignWork.cinemaMode = 0;
                        campaignWork.routes[sd][buf[0]].state = 1;
                        campaignWork.eventStep++;
                    }
                }
                return;
            }
            break;
        case 105:
            buf[0] = spot[16].list[sd][0];
            buf[1] = spot[17].list[sd][0];
            b->lv[16] = 3;
            switch (campaignWork.eventStep) {
            case 0:
                campaignWork.cinemaState = 0;
                campaignWork.cinemaMode = 2;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 1;
                campaignWork.leaderShow = 0;
                campaignWork.talkStep = 0;
                campaignWork.unk53A0 = 0;
                campaignWork.unk5375 = 0;
                func_00228940_b(0, 3);
                func_00228660_b(side, 16, 3, buf, 2);
                func_00228660_b(side, 17, 0, buf, 2);
                func_00217980_b(35, 1);
                b->b199 = 16;
                campaignWork.eventStep++;
                return;
            case 1:
                if (campaignWork.windowOpen == 0) {
                    campaignWork.cinemaState = 1;
                    campaignWork.eventStep++;
                }
                return;
            case 2:
                if (My_LeaderModel_a_set(0) && Taku_Focus_move() && campaignWork.cinemaState == 2) {
                    func_00228940_b(1, 3);
                    campaignWork.eventStep++;
                }
                return;
            case 3:
                FLOATS
                if (campaignWork.shipState == 3) {
                    campaignWork.eventStep++;
                    campaignWork.talkStep++;
                    campaignWork.talkPage = 1;
                    b->b199 = 17;
                }
                return;
            case 4:
                FLOATS
                if (b->lv[campaignRoutes[sd][buf[0]].cell] != 0) {
                    if (My_LeaderModel_a_set(1)) {
                        campaignWork.cinemaState = 1;
                        campaignWork.cinemaMode = 0;
                        campaignWork.routes[sd][buf[0]].state = 1;
                        b->h194++;
                        campaignWork.eventStep = 0;
                    }
                }
                return;
            }
            break;
        case 106:
            buf[0] = spot[17].list[sd][0];
            Taku_Flow2_set(side, 17, buf, 1, 0);
            if (campaignWork.unk546C == 0) {
                func_00217980_b(4, 1);
                campaignWork.unk546C = 1;
            }
            break;
        NAG1(107, 18)
        NAG1(108, 19)
        NAG1(109, 20)
        NAG1(110, 21)
        case 111:
            buf[0] = spot[0].list[sd][0];
            switch (campaignWork.eventStep) {
            case 0:
                campaignWork.cinemaState = 0;
                campaignWork.cinemaMode = 2;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 1;
                campaignWork.leaderShow = 0;
                campaignWork.talkStep = 0;
                campaignWork.unk53A0 = 0;
                campaignWork.unk5375 = 0;
                func_00228940_b(0, 4);
                func_00228660_b(side, 0, 3, buf, 1);
                b->lv[0] = 3;
                campaignWork.eventStep++;
                return;
            case 1:
                if (campaignWork.windowOpen == 0) {
                    campaignWork.cinemaState = 1;
                    campaignWork.eventStep++;
                }
                return;
            case 2:
                if (campaignWork.cinemaState == 2) {
                    campaignWork.talkStep++;
                    campaignWork.talkPage = 1;
                    campaignWork.unk5375 = 1;
                    campaignWork.eventStep++;
                }
                return;
            case 3:
                if (campaignWork.talkStep == 14) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventStep++;
                }
                return;
            case 4:
                if (My_LeaderModel_a_set(0) && Taku_Focus_move()) {
                    func_00228940_b(1, 4);
                    campaignWork.eventStep++;
                }
                return;
            case 5:
                FLOATS
                if (campaignWork.shipState == 3) {
                    b->b199 = 11;
                    campaignWork.eventStep++;
                }
                return;
            case 6:
                FLOATS
                if (b->lv[11] != 0) {
                    if (My_LeaderModel_a_set(1)) {
                        campaignWork.cinemaState = 1;
                        campaignWork.cinemaMode = 0;
                        campaignWork.eventStep++;
                    }
                }
                return;
            case 7:
                if (campaignWork.moveStep == 0) {
                    campaignWork.moveFromX = campaignWork.cameraTarget[0];
                    campaignWork.moveFromZ = campaignWork.cameraTarget[2];
                }
                campaignWork.cameraTarget[0] = campaignWork.moveFromX * (float)(256 - campaignWork.moveStep) / 256.0f + spot[11].x * (float)campaignWork.moveStep / 256.0f;
                campaignWork.cameraTarget[2] = campaignWork.moveFromZ * (float)(256 - campaignWork.moveStep) / 256.0f + spot[11].y * (float)campaignWork.moveStep / 256.0f;
                campaignWork.moveStep += 16;
                if (campaignWork.moveStep > 256) {
                    campaignWork.moveStep = 0;
                    campaignWork.moveFromX = campaignWork.cameraTarget[0];
                    campaignWork.moveFromZ = campaignWork.cameraTarget[2];
                    campaignWork.unk5372 = 0;
                    campaignWork.unk5375 = 0;
                    campaignWork.eventStep++;
                }
                return;
            case 8:
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep++;
                return;
            case 9:
                if (campaignWork.cinemaState == 2) {
                    campaignWork.eventStep = 0;
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
#undef COPY
#undef FLOATS
#undef NAG
#undef NAG1
#undef KM
#undef spot

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrGlideBoard {
    signed char mode;
    signed char unknown_01[2];
    signed char seen[59];
    short wins[2];
    short row_wins[2][32];
    short ticks;
    short unknown_c4;
    signed char kind[3];
    signed char unknown_c9;
    signed char streak;
};
struct DotrGlideSpot_228150 {
    float x;
    float unknown_04;
    float y;
    float unknown_0c[6];
    unsigned char unknown_24[2];
    short marks[7];
};
extern struct DotrGlideBoard D_00299E10_228150;
extern struct DotrGlideSpot_228150 D_00298BA0_228150[];
/* Whether the campaign result counts towards the place's score. */
static inline short may_score(struct DotrGlideBoard *board)
{
    if (board->unknown_01[0] != 0 && board->unknown_01[1] != 0) {
        board->ticks = 0;
        return 0;
    }
    if (board->seen[board->kind[0]] < 3) {
        return 1;
    }
    if (board->mode == 0 && board->kind[0] == 11) {
        if (board->unknown_c9 == 1) {
            return 1;
        }
        board->ticks = 0;
        return 0;
    }
    board->ticks = 0;
    return 0;
}

/* Records a campaign duel's result (win if `side` is set): the win counts, the streak, and the place's new state. (original: Taku_Camp_What_KATIMAKE) */
void Taku_Camp_What_WINLOSE(int side)
{
    struct DotrGlideBoard *board = &D_00299E10_228150;

    D_00299E10_228150.kind[1] = D_00299E10_228150.kind[2];
    D_00299E10_228150.kind[0] = D_00299E10_228150.kind[2];
    D_00299E10_228150.streak++;
    if (D_00299E10_228150.streak >= 5) {
        board->streak = 5;
    }
    if (side != 0) {
        board->wins[0]++;
        if (board->wins[0] >= 9999) {
            board->wins[0] = 9999;
        }
        board->row_wins[0][board->unknown_c4]++;
        if (board->row_wins[0][board->unknown_c4] >= 9999) {
            board->row_wins[0][board->unknown_c4] = 9999;
        }
    } else {
        board->wins[1]++;
        if (board->wins[1] >= 9999) {
            board->wins[1] = 9999;
        }
        board->row_wins[1][board->unknown_c4]++;
        if (board->row_wins[1][board->unknown_c4] >= 9999) {
            board->row_wins[1][board->unknown_c4] = 9999;
        }
    }
    if (may_score(board)) {
        if (side != 0) {
            switch (board->kind[0]) {
            case 11:
                switch (board->unknown_c9) {
                case 0:
                    board->ticks = D_00298BA0_228150[board->kind[0]].marks[4];
                    break;
                default:
                    board->ticks = 313;
                    break;
                }
                break;
            default:
                board->ticks = D_00298BA0_228150[board->kind[0]].marks[4];
                break;
            }
        } else if ((signed char)side == 0) {
            switch (board->kind[0]) {
            case 11:
                switch (board->unknown_c9) {
                case 0:
                    board->ticks = D_00298BA0_228150[board->kind[0]].marks[5];
                    break;
                default:
                    board->ticks = 213;
                    break;
                }
                break;
            default:
                board->ticks = D_00298BA0_228150[board->kind[0]].marks[5];
                break;
            }
        }
    }
    campaignAct2Lock = 1;
}

/* Taku_Flow2_set at optimisation level 3: the shape from the dotr_decomp project's near-miss drop
 * (dotr-big/dev/near-misses-2026-10-16, CC0), in this project's names. */

typedef struct {
    u8 pad[0x26];
    s16 slots[7];
} Side_00228460;
#pragma optimization_level 3

/* Sets up the next flow (nagare) of the campaign for `player` on `side`: the places it opens. (original: Taku_Nagare2_set) */
void Taku_Flow2_set(s16 player, s16 side, s16 *items, s16 count) {
    extern Side_00228460 campaignPlaces_2[];
    CampaignWork *work;
    s16 i;

    switch (campaignWork.eventStep) {
    case 0:
        campaignWork.cinemaState = 1;
        campaignWork.cinemaMode = 0;
        Taku_RouteMarks_init(player, side, 3, items, count);
        (campaignWork.eventStep)++;
    case 1:
        if (campaignWork.cinemaState == 2) {
            if (player == 0) {
                work = &campaignWork;
                for (i = 0; i < count; i++) {
                    if (work->routes[player][items[i]].state != 3) {
                        work->routes[player][items[i]].state = campaignPlaces_2[side].slots[i];
                    } else {
                        work->routes[player][items[i]].state = 3;
                    }
                }
            } else {
                s16 n = items[0];
                if (campaignWork.routes[player][n].state != 3) {
                    campaignWork.routes[player][n].state = 1;
                } else {
                    campaignWork.routes[player][n].state = 3;
                }
            }
            (campaignWork.eventStep)++;
        }
        break;
    }
    Taku_Focus_move0(player, side, items, count);
    Taku_Focus_move_decide(player, side, 2);
}

typedef struct {
    u8 pad[0x46];
    s16 normal;
    s16 pad48;
    s16 special;
} Card_00228660;

typedef struct {
    u8 pad[0x26];
    s16 slots[7];
} Side_00228660;

extern Card_00228660 campaignRoutes_2[][16]; /* original: root_no */
extern s8 YugiArenaMapFlags[];
extern s8 LastPlayedArena;
#pragma optimization_level reset

/* Sets up the route marks (dodai) between campaign places for `player` on `side`. (original: Taku_Dodai_Root_init) */
void Taku_RouteMarks_init(s16 player, s16 side, s8 state, s16 *items, s16 count) {
    extern Side_00228660 campaignPlaces_2[];
    CampaignWork *work = &campaignWork;
    s8 *status = &campaignState;
    s16 i;
    s16 item;
    s16 id;

    campaignWork.moveStep = 0;
    campaignWork.unk5372 = 1;
    campaignWork.leaderShow = 0;
    campaignWork.talkStep = 0;
    campaignWork.unk53A0 = 0;
    campaignWork.unk5375 = 1;
    LastPlayedArena = side;
    campaignWork.leaderT = 0;
    campaignWork.leaderPoint = 0;
    campaignWork.leaderMoveState = 0;
    campaignWork.unk546C = 0;
    YugiArenaMapFlags[side] = state;

    for (i = 0; i < count; i++) {
        item = items[i];
        if (player == 0 && campaignPlaces_2[side].slots[i] == 2) {
            id = campaignRoutes_2[player][item].special;
        } else {
            id = campaignRoutes_2[player][item].normal;
        }
        if (status[id + 3] == 0) {
            s16 j;

            work->placeReached[id] = 0;
            work->placeBlink[id] = 0;
            status[id + 3] = 0;
            work->routes[player][item].state = 0;
            work->routeDrawn[player][item] = 0;
            for (j = 0; j < 64; j++) {
                work->routePointRise[player][item][j] = 0;
            }
        }
    }

    if (player == 0 && work->routes[player][12].state == 0) {
        s16 total = 0;
        s16 index;

        for (index = 2; index <= 10; index++) {
            if (status[index + 3] >= 3) {
                total++;
                if (total >= 8) {
                    work->savedCutScene = *(s16 *)(status + 0xC2);
                    *(s16 *)(status + 0xC2) = 0x2B70;
                }
            }
        }
    }
}

/* Starts the ship (fune) moving from place `from` to place `to` on the campaign map. (original: Taku_Fune_init) */
void Taku_Ship_init(s16 from, s16 to) {
    campaignWork.shipState = from;
    campaignWork.shipTo = to;
    campaignWork.shipPoint = 0;
    campaignWork.shipT = 0;
    campaignWork.shipOn = 1;
}

/* Moves the campaign camera's focus (tyumoku) towards its target by one step; 1 when it got there. (original: Taku_Tyumoku_ido) */
s32 Taku_Focus_move(void) {
    s16 step;
    s16 step2;

    if (campaignWork.moveStep == 0) {
        campaignWork.moveFromX = campaignWork.cameraTarget[0];
        campaignWork.moveFromZ = campaignWork.cameraTarget[2];
    }
    campaignWork.moveStep += 0x10;
    if (campaignWork.moveStep >= 0x100) {
        campaignWork.moveStep = 0x100;
    }
    step = campaignWork.moveStep;
    campaignWork.cameraTarget[0] = ((campaignWork.moveFromX * (f32)(0x100 - step)) / 256.0f) + ((campaignWork.shipPos[0] * (f32)step) / 256.0f);
    step2 = campaignWork.moveStep;
    campaignWork.cameraTarget[2] = ((campaignWork.moveFromZ * (f32)(0x100 - step2)) / 256.0f) + ((campaignWork.shipPos[2] * (f32)step2) / 256.0f);
    if (campaignWork.moveStep >= 0x100) {
        campaignWork.moveStep = 0;
        campaignWork.moveFromX = campaignWork.cameraTarget[0];
        campaignWork.moveFromZ = campaignWork.cameraTarget[2];
        campaignWork.unk5372 = 0;
        campaignWork.unk5375 = 0;
        return 1;
    }
    return 0;
}

/* Moves the campaign camera's focus along the route from place `from` (first move). (original: Taku_Tyumoku_ido0) */
s32 Taku_Focus_move0(s16 player, s16 from, s16 *route, s16 count) {
    extern f32 campaignPlaces_2[];
    extern f32 D_00298BA8[];
    s16 *state;
    f32 divisor;
    f32 sum_x;
    f32 sum_z;
    s16 progress;
    s16 entry;
    s16 location;
    s32 offset;
    s16 side;
    s16 selected;
    s16 i;
    s16 skipped;
    u8 *point;
    Side_00228660 *pt;

    state = (s16 *)&campaignState;
    switch (campaignWork.unk5372) {
    case 1:
        if (campaignWork.moveStep == 0) {
            campaignWork.moveFromX = campaignWork.cameraTarget[0];
            campaignWork.moveFromZ = campaignWork.cameraTarget[2];
        }
        campaignWork.moveStep += 0x10;
        if (campaignWork.moveStep >= 0x100) {
            campaignWork.moveStep = 0x100;
        }
        progress = campaignWork.moveStep;
        campaignWork.cameraTarget[0] =
            (campaignWork.moveFromX * (f32)(0x100 - progress)) / 256.0f +
            ((f32)progress * campaignPlaces_2[from * 13]) / 256.0f;
        progress = campaignWork.moveStep;
        campaignWork.cameraTarget[2] =
            (campaignWork.moveFromZ * (f32)(0x100 - progress)) / 256.0f +
            ((f32)progress * D_00298BA8[from * 13]) / 256.0f;
        if (campaignWork.moveStep >= 0x100) {
            campaignWork.moveStep = 0;
            campaignWork.moveFromX = campaignWork.cameraTarget[0];
            campaignWork.moveFromZ = campaignWork.cameraTarget[2];
            campaignWork.unk5372 += 1;
        }
        break;
    case 2:
        if (campaignWork.moveStep == 0) {
            sum_x = 0.0f;
            sum_z = 0.0f;
            side = (s16)player;
            campaignWork.moveFromX = campaignWork.cameraTarget[0];
            skipped = 0;
            i = 0;
            pt = &((Side_00228660 *)campaignPlaces_2)[(s16)from];
            campaignWork.moveFromZ = campaignWork.cameraTarget[2];
            for (; i < count; i++) {
                entry = *route;
                if (side == 0 && pt->slots[i] == 2) {
                    location = campaignRoutes_2[side][(s16)entry].special;
                } else {
                    location = campaignRoutes_2[side][(s16)entry].normal;
                }
                selected = (s16)location;
                if (selected != 7) {
                    point = (u8 *)campaignPlaces_2 + selected * 0x34;
                    sum_x += *(f32 *)point;
                    sum_z += *(f32 *)(point + 8);
                } else {
                    skipped = (s16)1;
                }
                route++;
            }
            if (skipped) {
                count = (s16)(count - 1);
            }
            divisor = (f32)count;
            campaignWork.leaderAimX = sum_x / divisor;
            campaignWork.leaderAimZ = sum_z / divisor;
        }
        progress = campaignWork.moveStep;
        campaignWork.cameraTarget[0] =
            (campaignWork.moveFromX * (f32)(0x100 - progress)) / 256.0f +
            (campaignWork.leaderAimX * (f32)progress) / 256.0f;
        progress = campaignWork.moveStep;
        campaignWork.cameraTarget[2] =
            (campaignWork.moveFromZ * (f32)(0x100 - progress)) / 256.0f +
            (campaignWork.leaderAimZ * (f32)progress) / 256.0f;
        campaignWork.moveStep += 8;
        if (campaignWork.moveStep > 0x100) {
            campaignWork.moveStep = 0;
            campaignWork.moveFromX = campaignWork.cameraTarget[0];
            campaignWork.moveFromZ = campaignWork.cameraTarget[2];
            campaignWork.unk5372 = 0;
            campaignWork.unk5375 = 0;
            state[0x61] = 0;
            return 1;
        }
        break;
    }
    return 0;
}

/* Moves the campaign camera's focus to place `place` of `player`; 1 when it got there. (original: Taku_Tyumoku_ido1) */
s32 Taku_Focus_move1(s16 player, s16 place) {
    extern f32 campaignPlaces_2[];
    extern f32 D_00298BA8[];
    s16 routeCount;
    s8 mode;

    routeCount = 0;
    mode = campaignWork.unk5372;
    switch (mode) {
    case 0:
        if (campaignWork.eventStep == 0) {
            Taku_RouteMarks_init(player, place, 3, &routeCount, 0);
            campaignWork.eventStep += 1;
        }
        break;
    case 1:
        if (campaignWork.moveStep == 0) {
            campaignWork.moveFromX = campaignWork.cameraTarget[0];
            campaignWork.moveFromZ = campaignWork.cameraTarget[2];
        }
        campaignWork.cameraTarget[0] = (campaignWork.moveFromX * (f32)(0x100 - campaignWork.moveStep) / 256.0f) +
                             ((f32)campaignWork.moveStep * campaignPlaces_2[place * 13] / 256.0f);
        campaignWork.cameraTarget[2] = (campaignWork.moveFromZ * (f32)(0x100 - campaignWork.moveStep) / 256.0f) +
                             ((f32)campaignWork.moveStep * D_00298BA8[place * 13] / 256.0f);
        campaignWork.moveStep += 0x10;
        if (campaignWork.moveStep > 0x100) {
            campaignWork.moveStep = 0;
            campaignWork.moveFromX = campaignWork.cameraTarget[0];
            campaignWork.moveFromZ = campaignWork.cameraTarget[2];
            campaignWork.unk5372 = 0;
            campaignWork.unk5375 = 0;
            return 1;
        }
        break;
    case 2:
    default:
        break;
    }
    return 0;
}

typedef struct State_00229140 {
    s8 pad0[3];
    s8 levels[17];
    u8 pad14[0xAE];
    s16 fieldC2;
    u8 padC4[2];
    s8 selection;
    s8 padC7;
    s8 previous;
    s8 snapshot;
} State_00229140;

extern f32 campaignPlaces_2[]; /* original: model_data */
extern f32 D_00298BA8[];

/* The player chose a place (kettei): moves the focus there, then starts its duel; 1 when the move ended. (original: Taku_Tyumoku_ido_kettei) */
s32 Taku_Focus_move_decide(s16 player, s16 place, s16 wait) {
    State_00229140 *state = (State_00229140 *)&campaignState;
    f32 startX;
    f32 startZ;
    s32 index;

    if ((campaignWork.unk5372 == 0 &&
         wait <= campaignWork.eventStep &&
         campaignWork.talkStep != 0) ||
        state->levels[state->selection] >= 2 ||
        (state->selection == 15 && state->levels[16] == 0)) {
        switch (campaignWork.leaderShow) {
        case 1:
            state->previous = state->selection;
            campaignWork.moveFromX = campaignWork.cameraTarget[0];
            campaignWork.moveFromZ = campaignWork.cameraTarget[2];
            campaignWork.cursorFromX = campaignWork.cursorX;
            campaignWork.cursorFromY = campaignWork.cursorY;
            campaignWork.moveStep = 0;
            campaignWork.leaderShow += 1;
            campaignWork.leaderT = 0;
            campaignWork.leaderPoint = 0;
            campaignWork.leaderMoveState = 1;
            state->snapshot = campaignWork.duelMenuChoice;
            break;
        case 2:
            campaignWork.moveStep += 8;
            startX = campaignWork.moveFromX;
            campaignWork.cameraTarget[0] = startX +
                ((f32)campaignWork.moveStep *
                 (campaignPlaces_2[state->selection * 13] - startX)) / 256.0f;
            startZ = campaignWork.moveFromZ;
            campaignWork.cameraTarget[2] = startZ +
                ((f32)campaignWork.moveStep *
                 (D_00298BA8[state->selection * 13] - startZ)) / 256.0f;
            index = state->selection * 13;
            if (campaignWork.cameraTarget[0] == campaignPlaces_2[index]) {
                if (campaignWork.cameraTarget[2] == D_00298BA8[index]) {
                    campaignWork.moveStep = 256;
                }
            }
            if (campaignWork.moveStep >= 256) {
                campaignWork.moveStep = 0;
                campaignWork.cameraTarget[0] = campaignPlaces_2[state->selection * 13];
                campaignWork.cameraTarget[2] = D_00298BA8[state->selection * 13];
                campaignWork.leaderShow = 3;
                if (state->selection == 15 && state->levels[16] == 0) {
                    state->fieldC2 = 0x2F08;
                }
                return 1;
            }
            break;
        case 3:
            if (campaignWork.unk53A0 <= 0 && campaignWork.leaderMoveState == 3) {
                Taku_Camp_Set_Go_Duel();
            }
            break;
        }
    }
    return 0;
}

/* Whether the chosen place is a special one. */
static inline s16 isSpecial_002294B0(State_00229140 *state) {
    s16 result = 0;

    if (state->pad0[0] == 0) {
        switch (state->selection) {
        case 2:
        case 4:
        case 5:
        case 6:
        case 8:
        case 9:
        case 10:
            result = 1;
            break;
        case 11:
            if (state->snapshot == 0) {
                result = 1;
            }
            break;
        }
    } else {
        switch (state->selection) {
        case 12:
        case 13:
        case 14:
        case 18:
        case 19:
        case 20:
        case 21:
        case 0:
            result = 1;
            break;
        }
    }
    return result;
}

/* Moves the campaign camera's focus after a duel's result (katimake: win or lose). (original: Taku_Tyumoku_ido_katimake) */
s32 Taku_Focus_move_winlose(s32 won, s16 place) {
    State_00229140 *state = (State_00229140 *)&campaignState;

    campaignWork.unk53C0 = place;
    switch (campaignWork.unk537A) {
    case 0:
        if (state->levels[place] == 0) {
            state->levels[place] = 1;
        }
        campaignWork.unk5375 = 1;
        campaignWork.cameraTarget[0] = campaignPlaces_2[place * 13];
        campaignWork.cameraTarget[2] = D_00298BA8[place * 13];
        campaignWork.cursorX = 0x140;
        campaignWork.cursorY = 0xBE;
        campaignWork.iconSlide = 0;
        campaignWork.windowOpen = 0;
        campaignWork.talkStep = 0;
        campaignWork.talkPage = 0;
        campaignWork.unk5440 = 100;
        state->selection = place;
        state->padC7 = place;
        state->previous = place;
        campaignWork.leaderT = 0;
        campaignWork.leaderPoint = 0;
        campaignWork.leaderMoveState = 0;
        campaignWork.unk5406 = 0;
        campaignWork.unk53AB = 0;
        campaignWork.unk5472 = 0;
        campaignWork.unk537A = 1;
        break;
    case 1:
        if (campaignWork.windowOpen >= 0x100) {
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.unk5478 = 0;
            if (state->fieldC2 >= 300) {
                if (isSpecial_002294B0(state)) {
                    campaignWork.unk537A = 2;
                } else {
                    campaignWork.unk537A = 3;
                }
            } else {
                campaignWork.unk537A = 3;
            }
        }
        break;
    case 2:
        if (campaignWork.unk5440 <= 0) {
            campaignWork.unk5472 = 1;
            campaignWork.unk5474 += 0x1000;
            if (campaignWork.unk5478 < 0x1000) {
                campaignWork.unk5478 += 0x20;
                if (campaignWork.unk5478 >= 0x1000) {
                    campaignWork.unk5478 = 0x1000;
                    campaignWork.unk537A = 3;
                    campaignWork.unk5472 = 0;
                }
            }
        }
        break;
    }
    return 0;
}

/* Draws the campaign map's 2D parts: place marks, routes, the cursor, the ship and the windows. */
void *Taku_Camp_2D(s32 packet) {
    extern u8 te_data[];
    extern u8 D_002964C6[];
    extern u8 D_002964EC[];
    extern s32 campaignTextures[];
    extern s32 window_TextureAddr_UIElements;
    extern s16 CutSceneNumber;
    extern s32 func_00202BF0();
    extern s32 func_00202E00();
    extern s32 func_00217CB0();
    s32 *cards = campaignTextures;
    u8 *state = (u8 *)&campaignState;
    s32 sp7C;
    s32 temp_s2;
    s16 var_s3;
    s32 temp_s4;
    s32 var_s0;
    s32 temp_s5;
    u16 temp_v1;
    s32 result;

    temp_s2 = func_001D9EF0();
    sp7C = func_00209E50();
    var_s3 = 0;
    temp_s4 = func_001AEFC0(packet);
    campaignTextures[0] = func_001AF140(7);
    window_TextureAddr_UIElements = func_001AF140(6);
    switch (CutSceneNumber) {                           /* irregular */
    case 0x2B0C:
        cards[2] = func_00202BF0(8, 0);
        cards[3] = func_00202BF0(8, 1);
        cards[4] = (s32) cards[2];
        cards[5] = (s32) cards[3];
        var_s3 = 8;
        break;
    case 0x2B72:
        cards[2] = func_00202BF0(8, 3);
        cards[3] = (s32) cards[2];
        cards[4] = func_00202BF0(8, 2);
        cards[5] = (s32) cards[4];
        var_s3 = 8;
        break;
    case 0x2B86:
        cards[2] = func_00202BF0(8, 5);
        cards[3] = (s32) cards[2];
        cards[4] = func_00202BF0(8, 4);
        cards[5] = (s32) cards[4];
        var_s3 = 8;
        break;
    case 0x2B88:
        cards[2] = func_00202BF0(8, 6);
        cards[3] = func_00202BF0(8, 7);
        cards[4] = (s32) cards[2];
        cards[5] = (s32) cards[3];
        var_s3 = 8;
        break;
    case 0x2B8A:
        cards[2] = func_00202BF0(8, 8);
        cards[3] = (s32) cards[2];
        cards[4] = (s32) cards[2];
        cards[5] = (s32) cards[2];
        var_s3 = 8;
        break;
    case 0x2BAE:
        cards[2] = func_00202BF0(8, 10);
        cards[3] = func_00202BF0(8, 12);
        cards[4] = func_00202BF0(8, 9);
        cards[5] = func_00202BF0(8, 11);
        var_s3 = 8;
        break;
    case 0x2F7A:
        cards[2] = func_00202BF0(8, 14);
        cards[3] = func_00202BF0(8, 16);
        cards[4] = func_00202BF0(8, 13);
        cards[5] = func_00202BF0(8, 15);
        var_s3 = 8;
        break;
    }
    campaignWork.unk5436 = 0;
    if ((*(s16 *)(state + 0xC2) >= 0x2724) && (*(s16 *)(state + 0xC2) < 0x2738) && (campaignWork.talkPage >= 3)) {
        cards[6] = func_00202BF0(8, 20);
        cards[7] = func_00202BF0(8, 22);
        cards[8] = func_00202BF0(8, 19);
        cards[9] = func_00202BF0(8, 18);
        cards[10] = func_00202BF0(8, 21);
        campaignWork.unk5436 = 1;
        var_s3 = 8;
    }
    if ((*(s16 *)(state + 0xC2) >= 0x2738) && (*(s16 *)(state + 0xC2) < 0x276B)) {
        cards[6] = func_00202BF0(8, 17);
        cards[7] = func_00202BF0(8, 18);
        campaignWork.unk5436 = 1;
        var_s3 = 8;
    }
    if ((*(s16 *)(state + 0xC2) == 0x2AF8) ||
        (*(s16 *)(state + 0xC2) == 0x2EE0)) {
        cards[6] = func_00202BF0(8, 17);
        cards[7] = func_00202BF0(8, 18);
        campaignWork.unk5436 = 1;
        var_s3 = 8;
    }
    if ((*(s16 *)(state + 0xC2) >= 0x2B84) && (*(s16 *)(state + 0xC2) < 0x2B86)) {
        cards[6] = func_00202BF0(8, 20);
        cards[7] = func_00202BF0(8, 19);
        campaignWork.unk5436 = 1;
        var_s3 = 8;
    }
    if (*(s16 *)(state + 0xC2) == 0x2B8C) {
        cards[6] = func_00202BF0(8, 22);
        cards[7] = func_00202BF0(8, 19);
        campaignWork.unk5436 = 1;
        var_s3 = 8;
    }
    if ((*(s16 *)(state + 0xC2) >= 0x2B98) && (*(s16 *)(state + 0xC2) < 0x2B9B)) {
        cards[6] = func_00202BF0(8, 18);
        cards[7] = func_00202BF0(8, 23);
        campaignWork.unk5436 = 1;
        var_s3 = 8;
    }
    if (*(s16 *)(state + 0xC2) == 0x2BAC) {
        cards[6] = func_00202BF0(8, 18);
        cards[7] = func_00202BF0(8, 23);
        campaignWork.unk5436 = 1;
        var_s3 = 8;
    }
    if ((*(s16 *)(state + 0xC2) >= 0x2F62) && (*(s16 *)(state + 0xC2) < 0x2F65)) {
        cards[6] = func_00202BF0(8, 18);
        cards[7] = func_00202BF0(8, 23);
        campaignWork.unk5436 = 1;
        var_s3 = 8;
    }
    if (*(s16 *)(state + 0xC2) == 0x2F76) {
        cards[6] = func_00202BF0(8, 18);
        cards[7] = func_00202BF0(8, 23);
        campaignWork.unk5436 = 1;
        var_s3 = 8;
    }
    if (*(s16 *)(state + 0xC2) == 0x2F78) {
        cards[6] = func_00202BF0(8, 18);
        campaignWork.unk5436 = 1;
        var_s3 = 8;
    }
    if (var_s3) {
        temp_s2 += func_00202E00(temp_s2, 2);
        temp_s5 = (s16)var_s3;
        packet = func_00202B00(temp_s4, temp_s5, temp_s2, &sp7C);
        var_s0 = 0;
        while (1) {
            func_00202D60(temp_s5, var_s0);
            var_s0++;
            if (var_s0 > 23) break;
        }
        temp_s4 = func_0020F290(packet);
    }
    result = (s32)func_002351A0((void *)temp_s4);
    if ((campaignWork.unk5374 == 0) && (campaignWork.unk5481 != 0) &&
        (func_001F5240(-1, -1) == 0) && (campaignWork.routesIdle != 0) &&
        (campaignWork.placesReached == 0)) {
        temp_v1 = campaignWork.unk0004;
        if (temp_v1 == 0) {
            result = func_00217CB0(result, te_data, campaignWork.cursorX, campaignWork.cursorY);
        } else if (temp_v1 == 1) {
            result = func_00217CB0(result, D_002964C6, campaignWork.cursorX, campaignWork.cursorY);
        } else {
            result = func_00217CB0(result, D_002964C6, campaignWork.cursorX, campaignWork.cursorY);
            result = func_00217CB0(result, D_002964EC, campaignWork.cursorX, campaignWork.cursorY);
        }
    }
    if (*(s16 *)(state + 0xC2) >= 0x2710) {
        result = func_00224E40(func_0022F3C0(result));
    }
    result = func_002347D0(result);
    result = func_002354A0(result);
    result = func_00236C50(result);
    if (campaignWork.iconUnderCursor == 3) {
        result = Taku_Camp_Help_Window(result);
    }
    result = Taku_Camp_CINEMA_CUT(result, 0);
    result = func_002311D0(result);
    if (campaignWork.unk53B4 != 0 || campaignWork.unk53B5 != 0) {
        result = Taku_Camp_TEXT_WHO_b(result, campaignWork.talkSpeaker);
    }
    return (void *)func_0022A140(func_001AF110(Taku_Camp_BUTTON_WAIT_b(result)));
}

typedef union {
    __int128 value;
    s32 axis[4];
} Rotation_0022A020;

extern Rotation_0022A020 D_0029ABB0;

/* Draws the stone in the middle of the campaign map, turning. (original: Taku_Camp_STON) */
s32 Taku_Camp_STONE(s32 packet) {
    Rotation_0022A020 rotation;
    CampaignWork *state = &campaignWork;
    s16 i;

    rotation = D_0029ABB0;
    rotation.axis[1] = campaignWork.stoneSpin;
    for (i = 0; i <= 9; i++) {
        switch (state->cameraMode) {
        case 1:
            packet = SzModel_Draw_Pipe(packet, i + 0x22, 0, (s32)&rotation, 0, 0, 0);
            break;
        default:
            packet = SzModel_Draw_Pipe(packet, i + 0x22, 0, 0, 0, 0, 0);
            break;
        }
    }
    for (i = 0; i < 2; i++) {
        SzModel_SetDrawFlag(i + 0x1E, 0);
    }
    return packet;
}

extern s16 CutSceneNumber;

/* Draws the campaign's deck-card display. */
s32 Taku_DECK_CARD_DISP(s32 packetIn) {
    s32 texture[24];
    s32 draw[36];
    CampaignWork *progress; /* walks 2 bytes per card, so progress->deckCardSlide[0] is deckCardSlide[i] */
    s32 index;
    s32 packet;
    CampaignWork *state = &campaignWork;
    s16 i;
    s16 id;
    s16 offset;
    s16 slot;
    s8 *context = &campaignState;

    extern s32 SzDuel_StartCardSession_Pipe();
    extern void SzDuel_ClearDrawCard();

    if (CutSceneNumber >= 0x2756 &&
        *(s16 *)(context + 0xC2) < 0x2761 &&
        state->deckShowPhase < 4) {
        packet = SzDuel_StartCardSession_Pipe();
        SzDuel_SetCardDefPrioZ(0xFFFFF8);
        SzDuel_ClearDrawCard(draw);
        draw[12] = 0x3EF00000;
        draw[13] = 0x3EFA6F4E;
        draw[14] = 0x3F800000;
        draw[15] = 0;
        i = 0;
        progress = state;
        for (; (index = i) < 3; i++) {
            s8 selection = state->eventWindowChoice;
            s8 direction = state->deckChoiceTurn;
            slot = (selection + 2 - index) % 3;
            if (direction != 0) {
                if ((s8)direction == 1) {
                    switch (index) {
                    case 0:
                        slot = selection % 3;
                        offset = state->deckChoiceSlide * 36 / 100;
                        break;
                    case 1:
                        slot = (selection + 2) % 3;
                        offset = 36 - state->deckChoiceSlide * 18 / 100;
                        break;
                    case 2:
                        slot = (selection + 1) % 3;
                        offset = 18 - state->deckChoiceSlide * 18 / 100;
                        break;
                    }
                } else {
                    switch (index) {
                    case 0:
                        offset = 36 - state->deckChoiceSlide * 36 / 100;
                        break;
                    case 1:
                        offset = 18 + state->deckChoiceSlide * 18 / 100;
                        break;
                    case 2:
                        offset = state->deckChoiceSlide * 18 / 100;
                        break;
                    }
                }
            } else {
                switch (index) {
                case 0:
                    offset = 36;
                    break;
                case 1:
                    offset = 18;
                    break;
                case 2:
                    offset = 0;
                    break;
                }
            }
            id = *(s16 *)&state->deckChoiceCards[slot];
            SzDuel_GetCardNodeOnScreen(draw, 0,
                         -10.0f + (f32)offset +
                             (f32)(progress->deckCardSlide[0] * 640 / 100 - 640),
                         10.0f);
            SzDuel_InitCardInfo(texture, id);
            packet = SzDuel_DrawCard_Pipe(SzDuel_SetupCard2_Pipe(packet, (s32)texture, draw), (s32)draw);
            if (state->eventWindowState < 2) {
                state->deckShowDone = 0;
            }
            if (state->eventWindowState == 2 && state->deckShowPhase == 0) {
                progress->deckCardSlide[0] += 18;
                if (0 < progress->deckCardSlide[0] &&
                    state->deckShowSound[index] == 0) {
                    SzSound_PlaySE(0, 9);
                    state->deckShowSound[index] = 1;
                }
                if (progress->deckCardSlide[0] >= 100) {
                    state->deckShowDone = i;
                    progress->deckCardSlide[0] = 100;
                    if (index == 2) {
                        state->deckShowPhase = 1;
                    }
                }
            } else if (state->eventWindowState == 2) {
                progress->deckCardSlide[0] = 100;
            } else if (state->eventWindowState >= 3) {
                if (index == 2) {
                    if (state->deckShowPhase == 3) {
                        progress->deckCardSlide[0] -= 6;
                        if (progress->deckCardSlide[0] <= 0) {
                            progress->deckCardSlide[0] = 0;
                            if (state->deckShowPhase < 4) {
                                state->deckShowPhase = 4;
                            }
                        }
                    } else {
                        progress->deckCardSlide[0] = 100;
                    }
                } else {
                    progress->deckCardSlide[0] += 6;
                    if (progress->deckCardSlide[0] >= 400) {
                        progress->deckCardSlide[0] = 400;
                        if (state->deckShowPhase < 3) {
                            state->deckShowPhase = 3;
                        }
                    }
                }
            }
            progress = (CampaignWork *)((u8 *)progress + 2);
        }
        packetIn = SzDuel_FinishCardSessionX_Pipe(packet);
    }
    return packetIn;
}

typedef struct Item_0022A710 {
    f32 x, y, z;
    s32 pad0C;
    s16 draw0, draw1;
    u8 pad14[0x20];
} Item_0022A710;

typedef struct Vector_0022A710 {
    f32 x, y, z, w;
} Vector_0022A710;

extern s16 D_00298BB0;
extern s16 D_00298BB2;
extern Item_0022A710 D_00298BD4;
extern Vector_0022A710 D_00298DDC;
extern s16 D_00298DEC;
extern s16 D_00298DEE;
extern Item_0022A710 D_00298E10;

/* Draws the campaign map in 3D: the ground, the castles, the leaders' models. */
void Taku_Camp_3D(s32 packet) {
    extern s32 SzModel_Draw_Pipe();
    extern f32 campaignPlaces_2[];
    s16 side;
    s16 choice;
    s16 kind;
    s16 animating;
    Vector_0022A710 positions[32];
    s8 *control = &campaignState;
    s16 i;
    Item_0022A710 *src;
    Vector_0022A710 *dst;
    CampaignWork *row; /* walks 2 bytes per place: row->placeReached[0] is placeReached[i], likewise placeBlink */
    CampaignWork *state = &campaignWork;
    s8 *sound;
    f32 height;

    animating = 0;
    packet = SzModel_Draw_Pipe(packet, 0x22, 0, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, 0x23, 0, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, 0x24, 0, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, 0x25, 0, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, 0x26, 0, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, 0x27, 0, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, D_00298DEC + 0x22, &D_00298DDC, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, D_00298DEE + 0x22, &D_00298DDC, 0, 0, 0, 0);
    src = (Item_0022A710 *)campaignPlaces_2;
    dst = positions;
    i = 0;
    row = state;
    for (; i <= 21; i++, src++, dst++, row = (CampaignWork *)((u8 *)row + 2)) {
        height = 12.0f;
        if (i == 16) {
            height = 18.0f;
        }
        if (control[i + 3] != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else if (row->placeReached[0] != 0) {
            animating = 1;
            dst->x = 0.4f * (f32)((row->placeBlink[0] >> 2) % 2) + src->x;
            dst->y = (src->y - height) + height * (f32)row->placeBlink[0] / 256.0f;
            dst->z = src->z;
            sound = &state->placeSound[i];
            if (*sound == 0 && row->placeBlink[0] != 0 && i != 11) {
                SzEffect_Entry(0, 0x194, i, 0, 0);
                *sound = 1;
            }
        } else {
            dst->x = src->x;
            dst->y = src->y - height;
            dst->z = src->z;
        }
        if (control[0] == 0) {
            if (row->placeReached[0] != 0) {
                row->placeBlink[0] += 4;
                if (row->placeBlink[0] >= 256) {
                    row->placeBlink[0] = 0;
                    control[i + 3] = 1;
                    row->placeReached[0] = 0;
                    state->shipState = 0;
                }
            }
        } else if (i == 16) {
            if (row->placeReached[0] == 2) {
                row->placeBlink[0] += 4;
                if (row->placeBlink[0] >= 256) {
                    row->placeBlink[0] = 0;
                    control[i + 3] = 1;
                    row->placeReached[0] = 0;
                    state->shipState = 0;
                }
            }
        } else if (row->placeReached[0] != 0) {
            row->placeBlink[0] += 4;
            if (row->placeBlink[0] >= 256) {
                row->placeBlink[0] = 0;
                control[i + 3] = 1;
                row->placeReached[0] = 0;
                state->shipState = 0;
            }
        }
    }
    if (state->unk018C != 0) {
        state->unk006E = 1;
    } else if (*(s16 *)(control + 0xC2) >= 10000) {
        state->unk006E = 0;
    } else if (animating == 0 && state->unk5481 != 0 && SzEffect_IsUse2(-1, -1) == 0 && state->routesIdle != 0 && state->placesReached == 0) {
        if (control[0] == 0) {
            if (state->unk5372 == 0) {
                switch (*(s16 *)(control + 0xC2)) {
                case 100:
                case 101:
                    state->unk006E = 0;
                    break;
                default:
                    state->unk006E = 1;
                    break;
                }
            } else {
                state->unk006E = 0;
            }
        } else if (state->unk5372 == 0) {
            switch (*(s16 *)(control + 0xC2)) {
            case 104:
            case 105:
            case 111:
                state->unk006E = 0;
                break;
            default:
                state->unk006E = 1;
                break;
            }
        } else {
            state->unk006E = 0;
        }
    } else {
        if (*(s16 *)(control + 0xC2) != 0) {
            goto disabled;
        }
        if (state->unk5481 == 0 || SzEffect_IsUse2(-1, -1) != 0 || state->routesIdle == 0 || state->placesReached != 0) {
            goto disabled;
        }
        state->unk006E = 1;
        goto control_updated;
disabled:
        state->unk006E = 0;
    }
control_updated:
    packet = SzModel_Draw_Pipe(packet, D_00298BB0 + 0x22, positions, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, D_00298BB2 + 0x22, positions, 0, 0, 0, 0);
    if (state->unk018C != 0) {
        s32 first = 1;
        Vector_0022A710 *firstPos = &positions[1];
        Item_0022A710 *firstSrc = &D_00298BD4;
        while (1) {
            packet = SzModel_Draw_Pipe(packet, firstSrc->draw0 + 0x22, firstPos, 0, 0, 0, 0);
            packet = SzModel_Draw_Pipe(packet, firstSrc->draw1 + 0x22, firstPos, 0, 0, 0, 0);
            first++;
            firstPos++;
            firstSrc++;
            if (first <= 10) {
                continue;
            }
            break;
        }
        {
        Vector_0022A710 *secondPos;
        Item_0022A710 *secondSrc;
        s32 second;
        second = 12;
        secondPos = &positions[12];
        secondSrc = &D_00298E10;
        while (1) {
            packet = SzModel_Draw_Pipe(packet, secondSrc->draw0 + 0x22, secondPos, 0, 0, 0, 0);
            packet = SzModel_Draw_Pipe(packet, secondSrc->draw1 + 0x22, secondPos, 0, 0, 0, 0);
            second++;
            secondPos++;
            secondSrc++;
            if (second <= 21) {
                continue;
            }
            break;
        }
        }
    } else if (control[0] == 0) {
        Vector_0022A710 *firstPos;
        Item_0022A710 *firstSrc;
        s32 first;
        first = 1;
        firstPos = &positions[1];
        firstSrc = &D_00298BD4;
        while (1) {
            packet = SzModel_Draw_Pipe(packet, firstSrc->draw0 + 0x22, firstPos, 0, 0, 0, 0);
            packet = SzModel_Draw_Pipe(packet, firstSrc->draw1 + 0x22, firstPos, 0, 0, 0, 0);
            first++;
            firstPos++;
            firstSrc++;
            if (first <= 10) {
                continue;
            }
            break;
        }
    } else if (control[0] == 1) {
        Vector_0022A710 *secondPos;
        Item_0022A710 *secondSrc;
        s32 second;
        second = 12;
        secondPos = &positions[12];
        secondSrc = &D_00298E10;
        while (1) {
            packet = SzModel_Draw_Pipe(packet, secondSrc->draw0 + 0x22, secondPos, 0, 0, 0, 0);
            packet = SzModel_Draw_Pipe(packet, secondSrc->draw1 + 0x22, secondPos, 0, 0, 0, 0);
            second++;
            secondPos++;
            secondSrc++;
            if (second <= 21) {
                continue;
            }
            break;
        }
    }
    packet = Taku_Camp_3D_POLE(packet);
    switch (state->shipTo) {
    case 0:
        choice = 15;
        side = 0;
        kind = 27;
        break;
    case 1:
        side = 0;
        choice = 0;
        kind = 27;
        break;
    case 2:
        choice = 4;
        side = 1;
        kind = 30;
        break;
    case 3:
        side = 1;
        choice = 5;
        kind = 30;
        break;
    case 4:
        side = 1;
        choice = 11;
        kind = 27;
        break;
    }
    if (kind == 27) {
        state->unk01AC = 0;
    } else {
        state->unk01AC = 1;
    }
    packet = Taku_Camp_3D_SHIP(packet, side, choice, kind);
    packet = SzModel_Draw_Pipe(packet, 0x29, 0, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, 0x28, 0, 0, 0, 0, 0);
    Taku_Camp_3D_LeaderModel(packet);
}

struct DotrLeaderModelSpot {
    float x, y, z, w;
    char unknown_10[36];
};
extern struct DotrLeaderModelSpot D_00298BA0_22b060[22];
struct DotrLeaderModelBoard {
    signed char pad[199];
    signed char from;
    signed char to;
};
extern struct DotrLeaderModelBoard D_00299E10_b_2;
#define DOTR_LEADER_FROM w[199]
#define DOTR_LEADER_TO w[200]
extern signed char cardModelHeights[]; /* original: Taku_Model_Y */
struct DotrLeaderModelVec {
    float x, y, z, w;
};
struct DotrLeaderModelRot {
    int x, y, z, w;
};
struct DotrLeaderModelScale {
    float x, y, z, w;
};
extern int func_001A22C0_b(float value);
extern void *func_001F9AD0_b(int index);
extern int func_001F2AD0_b(int index, int value);
extern int func_001F2800_b(int index, int value);
#define DOTR_LEADER_X(k) (*(campaignWork.routes[a][b].x + idx + (k)))
#define DOTR_LEADER_Z(k) (*(campaignWork.routes[a][b].z + idx + (k)))
#define DOTR_LEADER_N campaignWork.routes[a][b].count
#define DOTR_LEADER_ANGLE(x, z) (func_001A22C0_b(65536.0f * (func_001A6C18(x, z) / 6.2831855f)) % 65536)
#define DOTR_LEADER_SPOT D_00298BA0_22b060

/* Draws the leaders' 3D models on the campaign map. */
int Taku_Camp_3D_LeaderModel(int cursor)
{
    struct DotrLeaderModelRot rot;
    struct DotrLeaderModelScale scale;
    struct DotrLeaderModelVec p;
    struct DotrLeaderModelVec q;
    struct DotrLeaderModelVec out;
    signed char *w = (signed char *)&D_00299E10_b_2;
    short a, b, fwd, rev;
    short idx;
    float *x0;
    float *z0;
    float h;
    float dx2, dz2, dx, dz;
    float px, pz;
    signed char from;
    int lv;

    a = 0;
    b = 5;
    fwd = 0;
    rev = 0;
    lv = cardModelHeights[SzData_GetLeader(0, (short)SzData_GetCurrentDeck(0))];
    scale.x = 0.5f;
    scale.y = 0.5f;
    scale.z = 0.5f;
    h = (float)lv;
    from = DOTR_LEADER_FROM;
    switch (from) {
    case 1:
        switch (DOTR_LEADER_TO) {
        case 2:
            b = 1;
            a = 0;
            fwd = 1;
            break;
        case 8:
            b = 2;
            a = 0;
            fwd = 1;
            break;
        }
        break;
    case 2:
        switch (DOTR_LEADER_TO) {
        case 3:
            b = 3;
            fwd = 1;
            break;
        case 5:
            b = 4;
            fwd = 1;
            break;
        case 7:
            b = 12;
            fwd = 1;
            break;
        }
        break;
    case 3:
        switch (DOTR_LEADER_TO) {
        case 2:
            b = 3;
            fwd = 1;
            rev = 1;
            break;
        }
        break;
    case 5:
        switch (DOTR_LEADER_TO) {
        case 2:
            rev = 1;
            b = 4;
            fwd = 1;
            break;
        case 6:
            rev = 1;
            b = 10;
            fwd = 1;
            break;
        case 7:
            b = 13;
            fwd = 1;
            break;
        }
        break;
    case 6:
        switch (DOTR_LEADER_TO) {
        case 5:
            b = 10;
            fwd = 1;
            break;
        }
        break;
    case 7:
        switch (DOTR_LEADER_TO) {
        case 11:
            b = 14;
            fwd = 1;
            break;
        }
        break;
    case 8:
        switch (DOTR_LEADER_TO) {
        case 6:
            b = 5;
            fwd = 1;
            break;
        case 7:
            b = 11;
            fwd = 1;
            break;
        }
        break;
    case 9:
        switch (DOTR_LEADER_TO) {
        case 8:
            rev = 1;
            b = 6;
            fwd = 1;
            break;
        }
        break;
    case 11:
        switch (DOTR_LEADER_TO) {
        case 7:
            rev = 1;
            b = 14;
            fwd = 1;
            break;
        }
        break;
    }
    if (rev == 0 && campaignWork.leaderMoveState != 0 && fwd && 0 < campaignWork.leaderShow && campaignWork.leaderT <= 1024) {
        idx = campaignWork.leaderPoint;
        dx2 = DOTR_LEADER_X(2) - DOTR_LEADER_X(1);
        dz2 = DOTR_LEADER_Z(2) - DOTR_LEADER_Z(1);
        func_001A6C18(dx2, dz2);
        dx = DOTR_LEADER_X(1) - DOTR_LEADER_X(0);
        dz = DOTR_LEADER_Z(1) - DOTR_LEADER_Z(0);
        campaignWork.leaderAngle = DOTR_LEADER_ANGLE(dx, dz);
        if (campaignWork.leaderMoveState == 3) {
            campaignWork.leaderPos[0] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].x;
            campaignWork.leaderPos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_TO].y;
            campaignWork.leaderPos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].z;
        } else {
            px = DOTR_LEADER_X(0);
            campaignWork.leaderPos[0] = px + dx * (float)campaignWork.leaderT / 1024.0f;
            campaignWork.leaderPos[1] = DOTR_LEADER_SPOT[0].y + h;
            pz = DOTR_LEADER_Z(0);
            campaignWork.leaderPos[2] = pz + dz * (float)campaignWork.leaderT / 1024.0f;
        }
        if (DOTR_LEADER_N <= idx) {
            campaignWork.leaderAngle = DOTR_LEADER_ANGLE(DOTR_LEADER_X(0) - DOTR_LEADER_X(-1), DOTR_LEADER_Z(0) - DOTR_LEADER_Z(-1));
        } else if (DOTR_LEADER_N - 1 <= idx) {
        } else {
            short t = campaignWork.leaderT;
            campaignWork.leaderAngle = DOTR_LEADER_ANGLE(dx * (float)(1024 - t) / 1024.0f + dx2 * (float)t / 1024.0f,
                             dz * (float)(1024 - t) / 1024.0f + dz2 * (float)t / 1024.0f);
        }
        if (campaignWork.leaderT < 1024 && campaignWork.leaderPoint < DOTR_LEADER_N) {
            campaignWork.leaderT += 256;
            if (campaignWork.leaderT >= 1024) {
                campaignWork.leaderPoint++;
                if (DOTR_LEADER_N <= campaignWork.leaderPoint) {
                    campaignWork.leaderT = 0;
                    campaignWork.leaderMoveState = 3;
                    campaignWork.leaderPoint = DOTR_LEADER_N;
                } else {
                    campaignWork.leaderT = 0;
                }
            }
        }
        if (DOTR_LEADER_FROM == DOTR_LEADER_TO) {
            campaignWork.leaderT = 0;
            campaignWork.leaderMoveState = 3;
            campaignWork.leaderPoint = DOTR_LEADER_N;
        }
    } else if (rev && campaignWork.leaderMoveState != 0 && fwd && 0 < campaignWork.leaderShow && campaignWork.leaderT <= 1024) {
        if ((short)campaignWork.leaderMoveState == 1) {
            campaignWork.leaderPoint = DOTR_LEADER_N - 1;
            campaignWork.leaderMoveState = 2;
        }
        idx = campaignWork.leaderPoint;
        dx2 = DOTR_LEADER_X(1) - DOTR_LEADER_X(2);
        dz2 = DOTR_LEADER_Z(1) - DOTR_LEADER_Z(2);
        func_001A6C18(dx2, dz2);
        x0 = &DOTR_LEADER_X(0);
        z0 = &DOTR_LEADER_Z(0);
        dx = *x0 - DOTR_LEADER_X(1);
        dz = *z0 - DOTR_LEADER_Z(1);
        campaignWork.leaderAngle = DOTR_LEADER_ANGLE(dx, dz);
        if (campaignWork.leaderMoveState == 3) {
            campaignWork.leaderPos[0] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].x;
            campaignWork.leaderPos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_TO].y;
            campaignWork.leaderPos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].z;
        } else {
            px = DOTR_LEADER_X(1);
            campaignWork.leaderPos[0] = px + dx * (float)campaignWork.leaderT / 1024.0f;
            campaignWork.leaderPos[1] = DOTR_LEADER_SPOT[0].y + h;
            pz = DOTR_LEADER_Z(1);
            campaignWork.leaderPos[2] = pz + dz * (float)campaignWork.leaderT / 1024.0f;
        }
        if (DOTR_LEADER_N <= idx) {
            campaignWork.leaderAngle = DOTR_LEADER_ANGLE(*x0 - DOTR_LEADER_X(-1), *z0 - DOTR_LEADER_Z(-1));
        } else if (DOTR_LEADER_N - 1 <= idx) {
        } else {
            short t = campaignWork.leaderT;
            campaignWork.leaderAngle = DOTR_LEADER_ANGLE(dx2 * (float)(1024 - t) / 1024.0f + dx * (float)t / 1024.0f,
                             dz2 * (float)(1024 - t) / 1024.0f + dz * (float)t / 1024.0f);
        }
        if (campaignWork.leaderMoveState < 3 && campaignWork.leaderT < 1024 && 0 <= campaignWork.leaderPoint) {
            campaignWork.leaderT += 256;
            if (campaignWork.leaderT >= 1024) {
                campaignWork.leaderPoint--;
                if (campaignWork.leaderPoint < 0) {
                    campaignWork.leaderT = 0;
                    campaignWork.leaderMoveState = 3;
                    campaignWork.leaderPoint = 0;
                } else {
                    campaignWork.leaderT = 0;
                }
            }
        }
        if (DOTR_LEADER_FROM == DOTR_LEADER_TO) {
            campaignWork.leaderT = 0;
            campaignWork.leaderMoveState = 3;
            campaignWork.leaderPoint = 0;
        }
    } else if (campaignWork.leaderMoveState != 0 && 0 < campaignWork.leaderShow && campaignWork.leaderT <= 1024) {
        dz = DOTR_LEADER_SPOT[DOTR_LEADER_TO].x - DOTR_LEADER_SPOT[from].x;
        dx = DOTR_LEADER_SPOT[DOTR_LEADER_TO].z - DOTR_LEADER_SPOT[from].z;
        campaignWork.leaderAngle = DOTR_LEADER_ANGLE(dz, dx);
        if (campaignWork.leaderMoveState == 3) {
            campaignWork.leaderPos[0] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].x;
            campaignWork.leaderPos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_TO].y;
            campaignWork.leaderPos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].z;
        } else {
            campaignWork.leaderPos[0] = DOTR_LEADER_SPOT[DOTR_LEADER_FROM].x + dz * (float)campaignWork.leaderT / 1024.0f;
            campaignWork.leaderPos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_FROM].y;
            campaignWork.leaderPos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_FROM].z + dx * (float)campaignWork.leaderT / 1024.0f;
        }
        campaignWork.leaderT += 16;
        if (campaignWork.leaderT >= 1024) {
            campaignWork.leaderT = 0;
            campaignWork.leaderMoveState = 3;
            campaignWork.leaderPoint = 0;
            campaignWork.leaderPos[0] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].x;
            campaignWork.leaderPos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_TO].y;
            campaignWork.leaderPos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].z;
        }
        if (DOTR_LEADER_FROM == DOTR_LEADER_TO) {
            campaignWork.leaderT = 0;
            campaignWork.leaderMoveState = 3;
            campaignWork.leaderPoint = 0;
        }
    } else {
        campaignWork.leaderPos[0] = DOTR_LEADER_SPOT[from].x;
        campaignWork.leaderPos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_FROM].y;
        campaignWork.leaderPos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_FROM].z;
        p.x = (float)(campaignWork.cursorX - 320);
        p.y = (float)(campaignWork.cursorY - 224);
        p.z = 1.0f;
        p.w = 1.0f;
        q.x = (float)(campaignWork.cursorX - 320);
        q.y = (float)(campaignWork.cursorY - 224);
        q.z = 100.0f;
        q.w = 1.0f;
        Ex3d_GetPointOnScreen(&p, p.x, p.y);
        q = *(struct DotrLeaderModelVec *)func_001F9AD0_b(0);
        Ex3d_IntersectP(campaignWork.groundPlane, &p, &q, &out);
        campaignWork.leaderAngle += DOTR_LEADER_ANGLE(out.x - campaignWork.leaderPos[0], out.z - campaignWork.leaderPos[2]);
    }
    SzModel_SetDeform(30, 1);
    func_001F2AD0_b(30, 32);
    SzModel_SetScale(30, &scale);
    SzModel_SetPos(30, campaignWork.leaderPos);
    rot.x = 0;
    rot.y = campaignWork.leaderAngle + 32767 + 1;
    rot.z = 0;
    SzModel_SetRotC(30, &rot);
    func_001F2800_b(30, (*(u8 *)&campaignWork.leaderAlpha));
    campaignWork.leaderAngle = 0;
    SzModel_SetDrawFlag(30, 1);
    return cursor;
}
#undef DOTR_LEADER_FROM
#undef DOTR_LEADER_TO
#undef DOTR_LEADER_X
#undef DOTR_LEADER_Z
#undef DOTR_LEADER_N
#undef DOTR_LEADER_ANGLE
#undef DOTR_LEADER_SPOT

/* Picks the player's leader model. (original: My_LedarModel_a_set) */
s32 My_LeaderModel_a_set(s32 leader) {
    switch (leader) {
    case 0:
        campaignWork.leaderAlpha -= 4;
        if (campaignWork.leaderAlpha <= 0) {
            campaignWork.leaderAlpha = 0;
            return 1;
        }
        break;
    case 1:
        campaignWork.leaderAlpha += 4;
        if (campaignWork.leaderAlpha >= 0x80) {
            campaignWork.leaderAlpha = 0x80;
            return 1;
        }
        break;
    }
    return 0;
}

typedef struct PointList_0022C450 {
    s16 coordinates[32];
    s16 count;
    s16 mode;
    u8 padding[8];
} PointList_0022C450;

/* Builds the smooth paths (splines) between the campaign places. */
void Taku_spline_init(void) {
    f32 positions[64][2];
    f32 weights[64];
    s32 item;
    s32 bank;
    PointList_0022C450 *list;
    u8 *output;
    PointList_0022C450 *bankLists;
    u8 *bankOutput;
    s32 count;
    s32 point;
    s16 *source;
    f32 *position;
    f32 *weight;

    bankLists = (PointList_0022C450 *)campaignRoutes_2;
    bank = 0;
    bankOutput = (u8 *)&campaignWork; /* output + 0x22C / 0x32C / 0x42C below are routes[bank][item].x, .z and .count */
    do {
        item = 0;
        list = bankLists;
        output = bankOutput;
        do {
            count = list->count;
            point = 0;
            if (point < count) {
                position = &positions[0][0];
                weight = weights;
                source = list->coordinates;
                do {
                    position[0] = (f32)source[0];
                    position[1] = (f32)source[1];
                    *weight = 1.0f;
                    source += 2;
                    position += 2;
                    weight++;
                    point++;
                } while (point < count);
            }
            Taku_spline2((f32 *)(output + 0x22C), (f32 *)(output + 0x32C), (s16 *)(output + 0x42C),
                          &positions[0][0], weights, count, list->mode, 4.0f);
            item++;
            list++;
            output += 0x204;
        } while (item < 16);
        bank++;
        bankLists += 16;
        bankOutput += 0x2040;
    } while (bank < 2);
}

struct DotrGlideSpot {
    float x;
    float unknown_04;
    float y;
    float unknown_0c[6];
    unsigned char unknown_24[2];
    short marks[7];
};
struct DotrGlideVector3 {
    float x;
    float y;
    float z;
};
struct DotrGlideList {
    unsigned char unknown_00[70];
    short cell;
    short unknown_48;
    short other_cell;
};
extern struct DotrGlideSpot D_00298BA0_22c570[];
extern struct DotrGlideList D_00299020_22c570[2][16];
int func_001EE4B0_b(int cursor, int index, struct DotrGlideVector3 *position, void *d, int e, int f, int g);

/* Draws the place markers (bou: poles) on the campaign map. (original: Taku_Camp_3D_BOU) */
int Taku_Camp_3D_POLE(int cursor)
{
    struct DotrGlideVector3 pos;
    CampaignWork *bank = &campaignWork;
    int row;
    int n;
    int side;
    short model;
    short kind;
    short count;
    short state;
    int i;
    int k;
    int j;

    bank->routesIdle = 1;
    for (side = 0; side < 2; side++) {
        if (side == 0) {
            model = 28;
            n = 16;
        } else {
            model = 29;
            n = 12;
        }
        for (row = 0; row < n; row++) {
            count = bank->routes[side][row].count;
            state = bank->routes[side][row].state;
            kind = 0;
            if (side == 0) {
                switch (row) {
                case 0:
                case 15:
                    kind = 0;
                    break;
                default:
                    switch (state) {
                    case 1:
                        kind = 1;
                        bank->routesIdle = 0;
                        break;
                    case 2:
                        kind = 2;
                        bank->routesIdle = 0;
                        bank->routeDrawn[side][row] = count;
                        break;
                    case 3:
                        kind = 3;
                        break;
                    }
                    break;
                }
            } else {
                switch (row) {
                case 4:
                case 5:
                case 11:
                    kind = 0;
                    break;
                default:
                    if (state == 1) {
                        kind = 1;
                        bank->routesIdle = 0;
                    } else if (state == 2) {
                        kind = 2;
                        bank->routesIdle = 0;
                    } else if (state == 3) {
                        kind = 3;
                    } else {
                        
                        kind = 0;
                    }
                    break;
                }
            }
            if (kind == 1) {
                for (i = 0; i <= bank->routeDrawn[side][row]; i++) {
                    if (bank->routePointRise[side][row][i] < 256) {
                        pos.x = bank->routes[side][row].x[i];
                        pos.y = D_00298BA0_22c570[0].unknown_04 - 10.0f + 10.0f * (float)bank->routePointRise[side][row][i] / 256.0f;
                        pos.z = bank->routes[side][row].z[i];
                    } else {
                        pos.x = bank->routes[side][row].x[i];
                        pos.y = D_00298BA0_22c570[0].unknown_04;
                        pos.z = bank->routes[side][row].z[i];
                    }
                    cursor = func_001EE4B0_b(cursor, model + 34, &pos, 0, 0, 0, 0);
                    if (i == bank->routeDrawn[side][row] && bank->routePointRise[side][row][i] >= 64) {
                        if (bank->routeDrawn[side][row] < count) {
                            bank->routeDrawn[side][row]++;
                        } else {
                            bank->routeDrawn[side][row] = count;
                        }
                    }
                    if (bank->routePointRise[side][row][i] < 256) {
                        bank->routePointRise[side][row][i] += 16;
                        if (bank->routePointRise[side][row][i] >= 256) {
                            bank->routePointRise[side][row][i] = 256;
                        }
                    }
                    if (count == bank->routeDrawn[side][row]) {
                        if (bank->routePointRise[side][row][count] >= 256) {
                            bank->placeReached[D_00299020_22c570[side][row].cell] = 1;
                            bank->routes[side][row].state = 3;
                            bank->routeDrawn[side][row] = 0;
                            for (j = 0; j < 64; j++) {
                                bank->routePointRise[side][row][j] = 0;
                            }
                        }
                    }
                }
            } else if (kind == 2) {
                for (i = count; i >= bank->routeDrawn[side][row]; i--) {
                    if (bank->routePointRise[side][row][i] < 256) {
                        pos.x = bank->routes[side][row].x[i];
                        pos.y = D_00298BA0_22c570[0].unknown_04 - 10.0f + 10.0f * (float)bank->routePointRise[side][row][i] / 256.0f;
                        pos.z = bank->routes[side][row].z[i];
                    } else {
                        pos.x = bank->routes[side][row].x[i];
                        pos.y = D_00298BA0_22c570[0].unknown_04;
                        pos.z = bank->routes[side][row].z[i];
                    }
                    cursor = func_001EE4B0_b(cursor, model + 34, &pos, 0, 0, 0, 0);
                    if (i == bank->routeDrawn[side][row] && bank->routePointRise[side][row][i] >= 64) {
                        if (0 < bank->routeDrawn[side][row]) {
                            bank->routeDrawn[side][row]--;
                        } else {
                            bank->routeDrawn[side][row] = 0;
                        }
                    }
                    if (bank->routePointRise[side][row][i] < 256) {
                        bank->routePointRise[side][row][i] += 16;
                        if (bank->routePointRise[side][row][i] >= 256) {
                            bank->routePointRise[side][row][i] = 256;
                        }
                    }
                    if (bank->routeDrawn[side][row] == 0) {
                        if (bank->routePointRise[side][row][0] >= 256) {
                            bank->placeReached[D_00299020_22c570[side][row].other_cell] = 1;
                            bank->routes[side][row].state = 3;
                            bank->routeDrawn[side][row] = 0;
                            for (k = 0; k < 64; k++) {
                                bank->routePointRise[side][row][k] = 0;
                            }
                        }
                    }
                }
            } else if (kind == 3) {
                for (i = 0; i <= count; i++) {
                    pos.x = bank->routes[side][row].x[i];
                    pos.y = D_00298BA0_22c570[0].unknown_04;
                    pos.z = bank->routes[side][row].z[i];
                    cursor = func_001EE4B0_b(cursor, model + 34, &pos, 0, 0, 0, 0);
                }
            }
        }
    }
    return cursor;
}

/* Draws the ship (fune) moving between two places. (original: Taku_Camp_3D_FUNE) */
s32 Taku_Camp_3D_SHIP(s32 packet, s16 arg1, s16 arg2, s16 arg3) {
    extern s32 func_001A22C0(f32);
    extern s16 D_00299066[][16][38];
    /* The routes as rows of 129 floats (a CampaignRoute is 0x204 bytes), as the original reads them:
       xData[a][b][i] is routes[a][b].x[i], zData the .z, countData[a][b][0] the .count. */
    f32 (*xData)[16][129] = (f32 (*)[16][129])campaignWork.routes[0][0].x;
    f32 (*zData)[16][129] = (f32 (*)[16][129])campaignWork.routes[0][0].z;
    s16 (*countData)[16][258] = (s16 (*)[16][258])&campaignWork.routes[0][0].count;
    s32 rotation[3];
    f32 dx1;
    f32 dz1;
    f32 dx0;
    f32 dz0;
    s16 point;
    f32 *x;
    f32 *z;
    s32 angle;

    point = campaignWork.shipPoint;
    dx1 = xData[arg1][arg2][point + 2] - xData[arg1][arg2][point + 1];
    dz1 = zData[arg1][arg2][point + 2] - zData[arg1][arg2][point + 1];
    func_001A6C18(dx1, dz1);
    dx0 = xData[arg1][arg2][point + 1] - xData[arg1][arg2][point];
    dz0 = zData[arg1][arg2][point + 1] - zData[arg1][arg2][point];
    x = &xData[arg1][arg2][point];
    z = &zData[arg1][arg2][point];
    angle = func_001A22C0(65536.0f * (func_001A6C18(dx0, dz0) / 6.2831855f)) % 65536;
    campaignWork.shipPos[0] = *x + dx0 * (f32)campaignWork.shipT / 1024.0f;
    campaignWork.shipPos[1] = D_00298BA4;
    campaignWork.shipPos[2] = *z + dz0 * (f32)campaignWork.shipT / 1024.0f;
    if (countData[arg1][arg2][0] <= point) {
        s32 previousAngle = func_001A22C0(65536.0f * (func_001A6C18(
            *x - xData[arg1][arg2][point - 1],
            *z - zData[arg1][arg2][point - 1]) / 6.2831855f)) % 65536;
        rotation[0] = 0;
        rotation[1] = previousAngle;
        rotation[2] = 0;
    } else if (countData[arg1][arg2][0] - 1 <= point) {
        rotation[0] = 0;
        rotation[1] = angle;
        rotation[2] = 0;
    } else {
        s16 progress = campaignWork.shipT;
        rotation[0] = 0;
        rotation[1] = func_001A22C0(65536.0f * (func_001A6C18(
            dx0 * (f32)(1024 - progress) / 1024.0f
                + dx1 * (f32)progress / 1024.0f,
            dz0 * (f32)(1024 - progress) / 1024.0f
                + dz1 * (f32)progress / 1024.0f) / 6.2831855f)) % 65536;
        rotation[2] = 0;
    }
    campaignWork.shipAngle = rotation[1];
    if (campaignWork.shipOn != 0) {
        packet = SzModel_Draw_Pipe(packet, arg3 + 0x22, (s32)campaignWork.shipPos, (s32)rotation, 0, 0, 0);
    }
    if (campaignWork.shipState > 0) {
        if (campaignWork.shipT < 1024 && campaignWork.shipPoint < countData[arg1][arg2][0]) {
            if (campaignWork.shipState == 1) {
                SzEffect_Entry(0, 0x193, 0, 0, 0);
                campaignWork.shipState = 2;
            }
            if (campaignWork.shipState == 2) {
                campaignWork.shipT += 256;
                if (campaignWork.shipT >= 1024) {
                    campaignWork.shipPoint += 1;
                    if (countData[arg1][arg2][0] <= campaignWork.shipPoint) {
                        campaignWork.shipT = 0;
                        campaignWork.shipState = 3;
                        campaignWork.shipPoint = countData[arg1][arg2][0];
                        (campaignWork.placeReached)[D_00299066[arg1][arg2][0]] = 1;
                    } else {
                        campaignWork.shipT = 0;
                    }
                }
            }
        }
    }
    return packet;
}

/* Works out which campaign text (bun) to show next and when it ends (hantei: judgement). (original: Taku_Camp_BUN_HANTEI) */
s32 Taku_Camp_TEXT_PICK(void) {
    extern s16 CutSceneNumber;
    s32 player;
    s32 ret;
    s8 *context;
    s8 temp_a0;
    s8 temp_a1;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_a0_2;
    s8 temp_a0_3;
    s16 temp_a0_4;
    s8 temp_a0_5;
    s8 temp_v1_4;
    s16 temp_v1_5;
    s16 temp_a0_6;

    player = campaignState;
    context = &campaignState;
    if (CutSceneNumber < 0xC8) {
        campaignWork.talkSpeaker = 0;
        if ((s16)player == 0) {
            switch (context[0xC6]) {
            case 2:
                campaignWork.talkMessage = 0x887;
                campaignWork.talkMessageCount = 1;
                break;
            case 3:
                campaignWork.talkMessage = campaignWork.talkPage + 0x89E;
                campaignWork.talkMessageCount = 6;
                break;
            case 4:
                campaignWork.talkMessage = campaignWork.talkPage + 0x88D;
                campaignWork.talkMessageCount = 2;
                break;
            case 5:
                campaignWork.talkMessage = 0x895;
                campaignWork.talkMessageCount = 1;
                break;
            case 6:
                campaignWork.talkMessage = 0x898;
                campaignWork.talkMessageCount = 1;
                break;
            case 7:
                campaignWork.talkMessage = campaignWork.talkPage + 0x8AD;
                campaignWork.talkMessageCount = 7;
                break;
            case 8:
                campaignWork.talkMessage = 0x88A;
                campaignWork.talkMessageCount = 1;
                break;
            case 9:
                campaignWork.talkMessage = 0x892;
                campaignWork.talkMessageCount = 1;
                break;
            case 10:
                campaignWork.talkMessage = campaignWork.talkPage + 0x89A;
                campaignWork.talkMessageCount = 2;
                break;
            case 11:
                if (context[0xE] == 1 || context[0xE] == 2) {
                    campaignWork.talkMessageCount = 9;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8DF;
                } else if (context[0xE] >= 3) {
                    if (campaignWork.duelMenuChoice == 1) {
                        campaignWork.talkMessageCount = 1;
                        campaignWork.talkMessage = 0x902;
                    } else {
                        campaignWork.talkMessageCount = 9;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x8DF;
                    }
                }
                break;
            }
            if (*(s16 *)(context + 0xC2) != 0x64) {
                return ret;
            }
            campaignWork.talkMessageCount = 1;
            campaignWork.talkMessage = 0x86C;
            campaignWork.talkSpeaker = 1;
            return ret;
        }
        switch (context[0xC6]) {
        case 12:
            campaignWork.talkMessage = campaignWork.talkPage + 0x935;
            campaignWork.talkMessageCount = 2;
            break;
        case 13:
            campaignWork.talkMessage = campaignWork.talkPage + 0x939;
            campaignWork.talkMessageCount = 2;
            break;
        case 14:
            campaignWork.talkMessage = campaignWork.talkPage + 0x93D;
            campaignWork.talkMessageCount = 2;
            break;
        case 16:
            campaignWork.talkMessage = 0x94A;
            campaignWork.talkMessageCount = 1;
            break;
        case 18:
            campaignWork.talkMessage = campaignWork.talkPage + 0x94E;
            campaignWork.talkMessageCount = 3;
            break;
        case 19:
            campaignWork.talkMessageCount = 4;
            campaignWork.talkMessage = campaignWork.talkPage + 0x953;
            break;
        case 20:
            campaignWork.talkMessage = 0x95C;
            campaignWork.talkMessageCount = 1;
            break;
        case 21:
            campaignWork.talkMessageCount = 5;
            campaignWork.talkMessage = campaignWork.talkPage + 0x95E;
            break;
        case 0:
            campaignWork.talkMessageCount = 2;
            campaignWork.talkMessage = campaignWork.talkPage + 0x968;
            break;
        case 11:
            campaignWork.talkMessageCount = 1;
            campaignWork.talkMessage = 0x983;
            break;
        }
        switch (*(s16 *)(context + 0xC2)) {
        case 0x69:
            campaignWork.talkMessageCount = 1;
            campaignWork.talkMessage = 0x94E;
            campaignWork.talkSpeaker = 1;
            return ret;
        case 0x6F:
            campaignWork.talkMessageCount = 1;
            campaignWork.talkMessage = 0x970;
            campaignWork.talkSpeaker = 2;
            campaignWork.duelistName[1] = 0xC5;
            campaignWork.duelistSide[1] = 1;
            campaignWork.unk53B5 = 1;
            return ret;
        }
    } else if (*(s16 *)(context + 0xC2) >= 0xC8 && *(s16 *)(context + 0xC2) < 0x12C) {
            {
                campaignWork.talkSpeaker = 0;
                if ((s16)player == 0) {
                    switch (context[0xC6]) {
                    case 2:
                        campaignWork.talkMessage = 0x888;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 3:
                        campaignWork.talkMessage = campaignWork.talkPage + 0x8A4;
                        campaignWork.talkMessageCount = 2;
                        return ret;
                    case 4:
                        campaignWork.talkMessage = 0x890;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 5:
                        campaignWork.talkMessage = 0x896;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 6:
                        campaignWork.talkMessage = 0x899;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 7:
                        campaignWork.talkMessageCount = 1;
                        campaignWork.talkMessage = 0x8B5;
                        return ret;
                    case 8:
                        campaignWork.talkMessage = campaignWork.talkPage + 0x88A;
                        campaignWork.talkMessageCount = 2;
                        return ret;
                    case 9:
                        campaignWork.talkMessage = 0x893;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 10:
                        campaignWork.talkMessage = 0x89D;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 11:
                        if (*(s16 *)(context + 0xC2) == 0xD4) {
                            campaignWork.talkMessageCount = 1;
                            campaignWork.talkMessage = 0x8E9;
                            return ret;
                        }
                        if (*(s16 *)(context + 0xC2) == 0xD5) {
                            campaignWork.talkMessageCount = 2;
                            campaignWork.talkMessage = campaignWork.talkPage + 0x902;
                            return ret;
                        }
                        break;
                    }
                } else {
                    switch (context[0xC6]) {
                    case 12:
                        campaignWork.talkMessage = 0x938;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 13:
                        campaignWork.talkMessage = 0x93C;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 14:
                        campaignWork.talkMessage = 0x940;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 16:
                        campaignWork.talkMessage = 0x94B;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 18:
                        campaignWork.talkMessage = 0x952;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 19:
                        campaignWork.talkMessageCount = 1;
                        campaignWork.talkMessage = 0x958;
                        return ret;
                    case 20:
                        campaignWork.talkMessage = 0x95D;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 21:
                        campaignWork.talkMessageCount = 3;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x963;
                        return ret;
                    case 0:
                        campaignWork.talkMessageCount = 2;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x96A;
                        return ret;
                    case 11:
                        campaignWork.talkMessageCount = 2;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x983;
                        return ret;
                    }
                }
            }
    } else if (*(s16 *)(context + 0xC2) >= 0x12C && *(s16 *)(context + 0xC2) < 0x190) {
            {
                campaignWork.talkSpeaker = 0;
                if ((s16)player == 0) {
                    switch (context[0xC6]) {
                    case 2:
                        campaignWork.talkMessageCount = 1;
                        campaignWork.talkMessage = 0x889;
                        return ret;
                    case 3:
                        campaignWork.talkMessageCount = 4;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x8A6;
                        return ret;
                    case 4:
                        campaignWork.talkMessage = 0x891;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 5:
                        campaignWork.talkMessage = 0x897;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 6:
                        campaignWork.talkMessage = 0x89A;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 7:
                        campaignWork.talkMessageCount = 1;
                        campaignWork.talkMessage = 0x8B6;
                        return ret;
                    case 8:
                        campaignWork.talkMessage = 0x88D;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 9:
                        campaignWork.talkMessage = 0x894;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 10:
                        campaignWork.talkMessage = 0x89E;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 11:
                        if (*(s16 *)(context + 0xC2) == 0x138) {
                            campaignWork.talkMessageCount = 1;
                            campaignWork.talkMessage = 0x8EA;
                            return ret;
                        }
                        if (*(s16 *)(context + 0xC2) == 0x139) {
                            campaignWork.talkMessageCount = 1;
                            campaignWork.talkMessage = 0x905;
                            return ret;
                        }
                        break;
                    }
                } else {
                    switch (context[0xC6]) {
                    case 12:
                        campaignWork.talkMessage = 0x939;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 13:
                        campaignWork.talkMessage = 0x93D;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 14:
                        campaignWork.talkMessage = campaignWork.talkPage + 0x940;
                        campaignWork.talkMessageCount = 2;
                        return ret;
                    case 16:
                        campaignWork.talkMessageCount = 2;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x94B;
                        return ret;
                    case 18:
                        campaignWork.talkMessage = 0x953;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 19:
                        campaignWork.talkMessageCount = 3;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x958;
                        return ret;
                    case 20:
                        campaignWork.talkMessage = 0x95E;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 21:
                        campaignWork.talkMessageCount = 2;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x966;
                        return ret;
                    case 0:
                        campaignWork.talkMessageCount = 3;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x96C;
                        return ret;
                    case 11:
                        campaignWork.talkMessageCount = 3;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x985;
                        return ret;
                    }
                }
            }
    } else {
            {
                switch (*(s16 *)(context + 0xC2)) {
                case 0x2724:
                    temp_a0 = campaignWork.talkPage;
                    if (temp_a0 == 0xA) {
                        campaignWork.talkPage = temp_a0 + 1;
                    }
                    campaignWork.talkMessageCount = 0xF;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x7EC;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 0;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2738:
                    campaignWork.talkMessageCount = 8;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x7FB;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2739:
                    campaignWork.talkMessageCount = 0xF;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x803;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2742:
                    campaignWork.talkMessageCount = 8;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x812;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x274C:
                    campaignWork.talkMessageCount = 7;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x81A;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2756:
                    campaignWork.talkMessageCount = 2;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x821;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2757:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x823;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2760:
                    campaignWork.talkMessageCount = 0x3E;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x824;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    switch (campaignWork.talkMessage) {
                    case 0x825:
                    case 0x826:
                    case 0x828:
                    case 0x82A:
                    case 0x82B:
                    case 0x82C:
                    case 0x82D:
                    case 0x82E:
                    case 0x82F:
                    case 0x830:
                    case 0x832:
                    case 0x833:
                    case 0x834:
                    case 0x835:
                    case 0x83D:
                    case 0x83E:
                    case 0x83F:
                    case 0x840:
                    case 0x841:
                    case 0x842:
                    case 0x844:
                    case 0x845:
                    case 0x846:
                    case 0x847:
                    case 0x84C:
                    case 0x84E:
                    case 0x84F:
                    case 0x850:
                    case 0x851:
                    case 0x853:
                    case 0x854:
                    case 0x857:
                    case 0x858:
                    case 0x859:
                    case 0x85A:
                    case 0x85B:
                    case 0x85C:
                    case 0x85D:
                    case 0x85F:
                    case 0x860:
                    case 0x861:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xC5;
                        campaignWork.duelistSide[0] = 1;
                        if (campaignWork.talkPage >= 4) {
                            campaignWork.unk53B4 = 1;
                            return ret;
                        }
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC4;
                        campaignWork.duelistSide[1] = 0;
                        campaignWork.unk53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x276A:
                    campaignWork.talkMessageCount = 4;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x862;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    temp_a1 = campaignWork.talkPage;
                    switch (temp_a1) {
                    case 1:
                    case 2:
                    case 4:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xC5;
                        campaignWork.duelistSide[0] = 1;
                        campaignWork.unk53B4 = 1;
                        return ret;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC4;
                        campaignWork.duelistSide[1] = 0;
                        campaignWork.unk53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x2AF8:
                    campaignWork.talkMessageCount = 5;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x866;
                    campaignWork.talkSpeaker = 3;
                    campaignWork.duelistName[0] = 0xC5;
                    campaignWork.duelistSide[0] = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B02:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x86B;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B0C:
                    campaignWork.talkMessageCount = 0x18;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x86C;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    temp_v1_2 = campaignWork.talkMessage;
                    switch (temp_v1_2) {
                    case 0x870:
                    case 0x872:
                    case 0x873:
                    case 0x874:
                    case 0x875:
                    case 0x876:
                    case 0x877:
                    case 0x878:
                    case 0x879:
                    case 0x87C:
                    case 0x87D:
                    case 0x87E:
                    case 0x87F:
                    case 0x880:
                    case 0x881:
                    case 0x882:
                    case 0x883:
                    case 0x884:
                    case 0x885:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xD7;
                        campaignWork.duelistSide[0] = 0;
                        campaignWork.unk53B4 = 1;
                        return ret;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC4;
                        campaignWork.duelistSide[1] = 0;
                        campaignWork.unk53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x2B70:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8AA;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B72:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8AB;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B74:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8AC;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B84:
                    campaignWork.talkMessageCount = 0x16;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8B6;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    temp_v1_3 = campaignWork.talkMessage;
                    switch (temp_v1_3) {
                    case 0x8BB:
                    case 0x8BD:
                    case 0x8BF:
                    case 0x8C0:
                    case 0x8C1:
                    case 0x8C3:
                    case 0x8C5:
                    case 0x8C6:
                    case 0x8C7:
                    case 0x8C8:
                    case 0x8C9:
                    case 0x8CB:
                    case 0x8CC:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xCD;
                        campaignWork.duelistSide[0] = 1;
                        if (campaignWork.talkPage >= 6) {
                            campaignWork.unk53B4 = 1;
                            return ret;
                        }
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xCE;
                        campaignWork.duelistSide[1] = 1;
                        campaignWork.unk53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x2B86:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8CC;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B87:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8CD;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B88:
                    campaignWork.talkMessageCount = 3;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8CE;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B8A:
                    campaignWork.talkMessageCount = 3;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8D1;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B8B:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8D4;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B8C:
                    campaignWork.talkMessageCount = 9;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8D5;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    temp_a0_2 = campaignWork.talkMessage;
                    switch (temp_a0_2) {
                    case 0x8D9:
                    case 0x8DB:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xCD;
                        campaignWork.duelistSide[0] = 1;
                        campaignWork.unk53B4 = 1;
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xD7;
                        campaignWork.duelistSide[1] = 0;
                        campaignWork.unk53B5 = 1;
                        break;
                    }
                    if (campaignWork.talkPage >= 0xA) {
                        campaignWork.unk53B4 = 0;
                        campaignWork.unk53B5 = 0;
                        return ret;
                    }
                    break;
                case 0x2B8D:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = 0x8DF;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 0;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B98:
                    campaignWork.talkMessageCount = 0x11;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8EA;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC5;
                    campaignWork.duelistSide[1] = 1;
                    campaignWork.unk53B5 = 1;
                    temp_a0_3 = campaignWork.talkPage;
                    switch (temp_a0_3) {
                    case 1:
                        campaignWork.duelist0Look = 0;
                        campaignWork.duelist1Look = 2;
                        return ret;
                    case 2:
                        campaignWork.duelist1Look = 2;
                        return ret;
                    case 3:
                        campaignWork.duelist1Look = 1;
                        return ret;
                    }
                    break;
                case 0x2B9A:
                    campaignWork.talkMessageCount = 6;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8FB;
                    temp_a0_4 = campaignWork.talkMessage;
                    switch (temp_a0_4) {
                    case 0x8FC:
                    case 0x900:
                    case 0x901:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xD8;
                        campaignWork.duelistSide[0] = 1;
                        campaignWork.unk53B4 = 1;
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC5;
                        campaignWork.duelistSide[1] = 1;
                        campaignWork.unk53B5 = 1;
                        break;
                    }
                    temp_a0_5 = campaignWork.talkPage;
                    switch (temp_a0_5) {
                    case 0x8FC:
                        campaignWork.duelist0Look = 0;
                        campaignWork.duelist1Look = 0;
                        return ret;
                    case 0x8FD:
                    case 0x8FE:
                    case 0x8FF:
                        campaignWork.duelist1Look = 1;
                        return ret;
                    }
                    break;
                case 0x2BAC:
                    campaignWork.talkMessageCount = 3;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x905;
                    switch (campaignWork.talkPage) {
                    case 1:
                    case 3:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xD8;
                        campaignWork.duelistSide[0] = 1;
                        campaignWork.unk53B4 = 1;
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC5;
                        campaignWork.duelistSide[1] = 1;
                        campaignWork.unk53B5 = 1;
                        break;
                    }
                    if (campaignWork.talkPage != 1) {
                        return ret;
                    }
                    campaignWork.duelist0Look = 2;
                    campaignWork.duelist1Look = 2;
                    return ret;
                case 0x2BAE:
                    campaignWork.talkMessageCount = 4;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x908;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2BB0:
                    campaignWork.talkMessageCount = 0x11;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x90C;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2EE0:
                    campaignWork.talkMessageCount = 0x17;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x91D;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    switch (campaignWork.talkPage) {
                    case 4:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC4;
                        campaignWork.duelistSide[1] = 0;
                        campaignWork.unk53B4 = 1;
                        campaignWork.duelist1Look = 2;
                        break;
                    default:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xC5;
                        campaignWork.duelistSide[0] = 1;
                        campaignWork.unk53B5 = 1;
                        if (campaignWork.talkPage >= 4) {
                            campaignWork.duelist1Look = 2;
                        }
                        break;
                    }
                    if (campaignWork.talkPage >= 5) {
                        campaignWork.unk53B5 = 0;
                        return ret;
                    }
                    break;
                case 0x2F08:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x942;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xD2;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2F09:
                    campaignWork.talkMessageCount = 6;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x943;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xD2;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2F62:
                    campaignWork.talkMessageCount = 3;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x970;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC5;
                    campaignWork.duelistSide[1] = 1;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2F64:
                    campaignWork.talkMessageCount = 0xF;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x973;
                    temp_v1_5 = campaignWork.talkMessage;
                    switch (temp_v1_5) {
                    case 0x974:
                    case 0x975:
                    case 0x976:
                    case 0x977:
                    case 0x978:
                    case 0x979:
                    case 0x97B:
                    case 0x97C:
                    case 0x97D:
                    case 0x982:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xD8;
                        campaignWork.duelistSide[0] = 0;
                        campaignWork.unk53B4 = 1;
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC5;
                        campaignWork.duelistSide[1] = 1;
                        campaignWork.unk53B5 = 1;
                        break;
                    }
                    temp_a0_6 = campaignWork.talkMessage;
                    switch (temp_a0_6) {
                    case 0x974:
                        campaignWork.duelist0Look = 0;
                        campaignWork.duelist1Look = 0;
                        return ret;
                    case 0x97A:
                        campaignWork.duelist0Look = 0;
                        campaignWork.duelist1Look = 2;
                        return ret;
                    }
                    break;
                case 0x2F76:
                    campaignWork.talkMessageCount = 2;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x988;
                    campaignWork.talkSpeaker = 3;
                    campaignWork.duelistName[0] = 0xD8;
                    campaignWork.duelistSide[0] = 0;
                    campaignWork.unk53B4 = 1;
                    if (campaignWork.talkPage != 1) {
                        return ret;
                    }
                    campaignWork.duelist0Look = 2;
                    campaignWork.duelist1Look = 2;
                    return ret;
                case 0x2F78:
                    campaignWork.talkMessageCount = 0x11;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x98A;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC5;
                    campaignWork.duelistSide[1] = 1;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    if (campaignWork.talkPage != 1) {
                        return ret;
                    }
                    campaignWork.duelist0Look = 2;
                    campaignWork.duelist1Look = 2;
                    return ret;
                case 0x2F7A:
                    campaignWork.talkMessageCount = 6;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x99B;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC5;
                    campaignWork.duelistSide[1] = 1;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2F7C:
                    campaignWork.talkMessageCount = 0xE;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x9A1;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                }
            }
    }
    return ret;
}

typedef struct State_0022F1C0 {
    u16 halves[18];
    s16 field_24;
} State_0022F1C0;

extern State_0022F1C0 D_0029ABC0;

/* Draws the "press a button" (botan mati) prompt. (original: Taku_Camp_BOTAN_MATI) */
s32 Taku_Camp_BUTTON_WAIT(s32 packet, s32 arg1, s16 arg2, s16 arg3) {
    extern s32 Taku_Obj_Set(s32, void *, s16, s16);
    s8 *slide = &campaignState;
    State_0022F1C0 local;
    s32 flag;
    s32 step;

    local = D_0029ABC0;
    flag = 1;
    switch (campaignWork.talkSpeaker) {
    case 0:
        arg2 = 0x1CC;
        arg3 = 0x68;
        break;
    case 1:
        arg2 = 0x258;
        arg3 = 0x198;
        break;
    case 2:
        arg2 = 0x258;
        arg3 = 0x198;
        break;
    case 3:
        arg2 = 0x1CC;
        arg3 = 0x68;
        break;
    }
    step = *(u8 *)&campaignWork.unk53B2 % 15;
    if (step < 5) {
        local.field_24 = 0x98;
    } else if (step < 10) {
        local.field_24 = 0x99;
    } else if (step < 15) {
        local.field_24 = 0x9A;
    }
    if (slide[0] == 0 && *(s16 *)(slide + 0xC2) == 0x64) {
        flag = 0;
    }
    if (slide[0] == 1 && *(s16 *)(slide + 0xC2) == 0x69) {
        flag = 0;
    }
    if (slide[0] == 1 && *(s16 *)(slide + 0xC2) == 0x6A) {
        flag = 0;
    }
    if ((campaignWork.talkStep == 4 || campaignWork.eventPictureState == 2) && flag != 0) {
        packet = Taku_Obj_Set(packet, &local, arg2, arg3);
        *(u8 *)&campaignWork.unk53B2 += 1;
    }
    return packet;
}

/* Camp event screen overlays: fade frames, bars, lamps and page pieces for the current camp event. */

typedef struct TakuObj_0022F3C0 {
    s16 w[8];
    u8 col[4][4];
    s16 pad20[2];
    u16 code;
} TakuObj_0022F3C0;

typedef struct TakuObj4_0022F3C0 {
    TakuObj_0022F3C0 o[4];
} TakuObj4_0022F3C0;

typedef struct TakuObj5_0022F3C0 {
    TakuObj_0022F3C0 o[5];
} TakuObj5_0022F3C0;

typedef struct TakuTex_0022F3C0 {
    s16 f[10];
} TakuTex_0022F3C0;

typedef struct TakuPair_0022F3C0 {
    s16 x;
    s16 y;
} TakuPair_0022F3C0;

extern TakuTex_0022F3C0 campaignSprites[]; /* original: tex_uv_data */
extern TakuObj_0022F3C0 D_0029ABF0;
extern TakuObj4_0022F3C0 D_0029AC20;
extern TakuObj4_0022F3C0 D_0029ACC0;
extern TakuObj5_0022F3C0 D_0029AD60;
extern TakuObj_0022F3C0 D_0029AE20;
extern TakuObj_0022F3C0 D_0029AE50;
extern TakuObj_0022F3C0 D_0029AE80;
extern TakuPair_0022F3C0 D_0029AEA8;

extern s32 Taku_G4_Set_b(s32 cursor, void *src, s16 x, s16 y);
extern s32 Taku_GT4_Set_b(s32 cursor, void *src, s16 x, s16 y, s16 dx, s16 dy);
extern s32 Taku_Obj_Set_b(s32 cursor, void *src, s16 dx, s16 dy);

/* Draws one campaign sprite. */
static inline s32 obj_0022F3C0(s32 cursor, void *src, s32 x, s32 y) {
    return Taku_Obj_Set_b(cursor, src, x, y);
}
#define H16(a) (*(s16 *)(a))

/* Draws the campaign event pictures (ga). (original: Taku_Camp_Ivent_Ga) */
s32 Taku_Camp_Event_Picture(s32 cursor) {
    f32 fv;
    u8 *ctx = (u8 *)&campaignState;
    s32 x13;
    CampaignWork *wk = &campaignWork;
    TakuObj_0022F3C0 base = D_0029ABF0;
    TakuObj4_0022F3C0 bars = D_0029AC20;
    TakuObj4_0022F3C0 frame = D_0029ACC0;
    TakuObj5_0022F3C0 page = D_0029AD60;
    TakuObj_0022F3C0 bar;
    TakuObj_0022F3C0 lamp;
    TakuObj_0022F3C0 lamp2;
    TakuPair_0022F3C0 size;
    s16 w;
    s16 h;
    s16 off;
    s16 i;
    s16 x;
    s16 y;
    s16 xa;
    s16 ya;
    s32 fya;
    TakuObj_0022F3C0 *pa;
    s16 ja;
    s16 ia;
    s16 yb;
    s32 fyb;
    s16 jb;
    s16 n1;
    s16 *tp1;
    s32 mm1;
    s16 m1;
    s16 x1p;
    s16 y1p;
    s16 t1;
    TakuTex_0022F3C0 *tex1;
    u16 idx1;
    s16 r2;
    s16 g2;
    s16 b2;
    s16 a2;
    s16 n2;
    s16 px2;
    TakuTex_0022F3C0 *tex2;
    s16 i3;
    s16 r3;
    s16 g3;
    TakuObj_0022F3C0 *pb;
    s32 x23;
    s16 b3;
    s16 px3;
    s16 c33;
    s16 xb;
    s16 k3;
    s32 q3;
    s32 dt3;
    TakuTex_0022F3C0 *tex3;
    s16 cnt4;
    f32 fx4;
    f32 fz4;
    s16 alpha4;
    s16 iq;

    off = 0;
    w = 0;
    h = 0;
    switch (CutSceneNumber) {
    case 0x2B0C:
        w = 0x280;
        h = 0x1C0;
        break;
    case 0x2B72:
        w = 0x280;
        h = 0x180;
        off = 0x40;
        break;
    case 0x2B86:
        w = 0x280;
        h = 0x180;
        off = 0x40;
        break;
    case 0x2B88:
        w = 0x280;
        h = 0x1C0;
        break;
    case 0x2B8A:
        w = 0x280;
        h = 0x1C0;
        break;
    case 0x2BAE:
        w = 0x200;
        h = 0x180;
        off = 0x40;
        break;
    case 0x2F7A:
        w = 0x200;
        h = 0x180;
        off = 0x40;
        break;
    }
    for (i = 0; i < 4; i++) {
        switch (i) {
        case 0:
            frame.o[i].w[0] = 0;
            frame.o[i].w[1] = 0;
            break;
        case 1:
            frame.o[i].w[0] = w;
            frame.o[i].w[1] = 0;
            break;
        case 2:
            frame.o[i].w[0] = 0;
            frame.o[i].w[1] = h;
            break;
        case 3:
            frame.o[i].w[0] = w;
            frame.o[i].w[1] = h;
            break;
        }
        frame.o[i].w[2] = w + frame.o[i].w[0];
        frame.o[i].w[3] = h + frame.o[i].w[1];
        campaignSprites[i + 0x94].f[0] = 0;
        campaignSprites[i + 0x94].f[1] = 0;
        campaignSprites[i + 0x94].f[2] = w;
        campaignSprites[i + 0x94].f[3] = h;
    }
    if (campaignWork.eventPictureState != 0) {
        switch (H16(ctx + 0xC2)) {
        case 0x2B88:
            for (ia = 0; ia < 2; ia++) {
                frame.o[ia].w[0] = frame.o[0].w[0];
                frame.o[ia].w[1] = frame.o[0].w[1];
                frame.o[ia].w[2] = frame.o[0].w[2];
                frame.o[ia].w[3] = frame.o[0].w[3];
            }
            xa = campaignWork.eventPictureX;
            ya = campaignWork.eventPictureY;
            if (campaignWork.eventPictureFade != 0) {
                frame.o[0].col[0][3] = *(u8 *)&campaignWork.eventPictureAlpha;
                base.col[3][3] = 0x80;
                frame.o[3].col[0][3] = 0x80;
                base.col[2][3] = 0x80;
                frame.o[2].col[0][3] = 0x80;
                base.col[1][3] = 0x80;
                frame.o[1].col[0][3] = 0x80;
                base.col[0][3] = 0x80;
            }
            cursor = Taku_G4_Set_b(cursor, &base, 0, 0);
            fya = ya + off;
            pa = &frame.o[1];
            for (ja = 1; ja >= 0; ja--) {
                cursor = obj_0022F3C0(cursor, pa, xa, fya);
                pa--;
            }
            switch (campaignWork.eventPictureFade) {
            case 1:
                if (0 < campaignWork.eventPictureAlpha) {
                    campaignWork.eventPictureAlpha -= 2;
                    if (campaignWork.eventPictureAlpha <= 0) {
                        campaignWork.eventPictureAlpha = 0;
                        campaignWork.eventPictureFade = 10;
                    }
                }
                break;
            }
            break;
        case 0x2B0C:
        case 0x2B72:
        case 0x2B86:
        case 0x2B8A:
        case 0x2BAE:
        case 0x2F7A:
            xb = campaignWork.eventPictureX;
            yb = campaignWork.eventPictureY;
            if (campaignWork.eventPictureFade != 0) {
                base.col[0][3] = frame.o[0].col[0][3] = base.col[1][3] = frame.o[1].col[0][3] =
                    base.col[2][3] = frame.o[2].col[0][3] = base.col[3][3] = frame.o[3].col[0][3] =
                        *(u8 *)&campaignWork.eventPictureAlpha;
            }
            cursor = Taku_G4_Set_b(cursor, &base, 0, 0);
            fyb = yb + off;
            for (jb = 0; jb < 4; jb++) {
                cursor = obj_0022F3C0(cursor, &frame.o[jb], xb, fyb);
            }
            switch (campaignWork.eventPictureFade) {
            case 1:
                if (0 < campaignWork.eventPictureAlpha) {
                    campaignWork.eventPictureAlpha -= 2;
                    if (campaignWork.eventPictureAlpha <= 0) {
                        campaignWork.eventPictureAlpha = 0;
                        campaignWork.eventPictureFade = 10;
                    }
                }
                break;
            }
            break;
        }
    }
    for (iq = 0xAB; iq < 0xAF; iq++) {
        campaignSprites[iq].f[2] = 0x100;
        campaignSprites[iq].f[3] = 0x100;
    }

    if (H16(ctx + 0xC2) == 0x2724) {
        if (campaignWork.unk5436 != 0) {
        for (m1 = 0, tp1 = (s16 *)&campaignWork; (mm1 = m1) < 5; m1++, tp1++) {
            for (n1 = 0; n1 < 2; n1++) {
                bar = D_0029AE20;

                idx1 = bar.code;
                campaignSprites[idx1].f[4] = 0;
                campaignSprites[idx1].f[3] = 0;
                campaignSprites[idx1].f[1] = 0;
                campaignSprites[idx1].f[0] = 0;
                campaignSprites[idx1].f[7] = 0x100;
                campaignSprites[idx1].f[6] = 0x100;
                campaignSprites[idx1].f[5] = 0x100;
                campaignSprites[idx1].f[2] = 0x100;
                if (n1 == 0) {
                    campaignSprites[idx1].f[3] = 0;
                    campaignSprites[idx1].f[1] = 0;
                    campaignSprites[idx1].f[7] = 0xB8;
                    campaignSprites[idx1].f[5] = 0xB8;
                    bar.w[7] = 0xB8;
                    bar.w[5] = 0xB8;
                } else {
                    campaignSprites[idx1].f[3] = 0xB8;
                    campaignSprites[idx1].f[1] = 0xB8;
                    campaignSprites[idx1].f[7] = 0x100;
                    campaignSprites[idx1].f[5] = 0x100;
                    bar.w[3] = 0xB8;
                    bar.w[1] = 0xB8;
                    bar.w[7] = 0x100;
                    bar.w[5] = 0x100;
                    bar.col[1][3] = 0x40;
                    bar.col[0][3] = 0x40;
                    bar.col[3][3] = 0;
                    bar.col[2][3] = 0;
                }
                switch (mm1) {
                case 0:
                    t1 = tp1[0x2A16];
                    x1p = 0x280 - t1 * 0x200 / 100;
                    y1p = t1 * 300 / 100 - 200;
                    tex1 = &campaignSprites[bar.code];
                    tex1->f[6] = 0x180;
                    tex1->f[2] = 0x180;
                    tex1->f[8] = 6;
                    bar.w[6] = 0x180;
                    bar.w[2] = 0x180;
                    break;
                case 1:
                    t1 = tp1[0x2A16];
                    x1p = t1 * 448 / 100 - 0x100;
                    y1p = t1 * 200 / 100 - 100;
                    campaignSprites[bar.code].f[8] = 7;
                    break;
                case 2:
                    t1 = tp1[0x2A16];
                    x1p = 0x280 - t1 * 448 / 100;
                    y1p = 300 - t1 * 200 / 100;
                    campaignSprites[bar.code].f[8] = 8;
                    break;
                case 3:
                    x1p = 0x40;
                    y1p = 100;
                    tex1 = &campaignSprites[bar.code];
                    tex1->f[6] = 0x200;
                    tex1->f[2] = 0x200;
                    tex1->f[8] = 9;
                    bar.w[0] = 0x100 - tp1[0x2A16] * 256 / 100;
                    bar.w[1] = tp1[0x2A16] * (campaignSprites[bar.code].f[3] - 0x80) / 100 + 0x80;
                    bar.w[2] = tp1[0x2A16] * 256 / 100 + 0x100;
                    bar.w[3] = tp1[0x2A16] * (campaignSprites[bar.code].f[3] - 0x80) / 100 + 0x80;
                    bar.w[4] = 0x100 - tp1[0x2A16] * 256 / 100;
                    bar.w[5] = tp1[0x2A16] * (campaignSprites[bar.code].f[7] - 0x80) / 100 + 0x80;
                    bar.w[6] = tp1[0x2A16] * 256 / 100 + 0x100;
                    bar.w[7] = tp1[0x2A16] * (campaignSprites[bar.code].f[7] - 0x80) / 100 + 0x80;
                    if (tp1[0x2A16] > 100) {
                        switch (n1) {
                        case 0:
                            bar.col[2][3] = bar.col[3][3] = 0x40 - (tp1[0x2A16] - 100) * 64 / 100;
                            break;
                        }
                        bar.col[0][3] = bar.col[1][3] = 0x40 - (tp1[0x2A16] - 100) * 64 / 100;
                    }
                    break;
                case 4:
                    t1 = tp1[0x2A16];
                    x1p = t1 * 448 / 100 - 0x100;
                    y1p = 300 - t1 * 200 / 100;
                    campaignSprites[bar.code].f[8] = 10;
                    break;
                }
                cursor = Taku_GT4_Set_b(cursor, &bar, x1p, y1p, 0, 0);
            }
        }
        }
    } else if (H16(ctx + 0xC2) == 0x2B9A || H16(ctx + 0xC2) == 0x2F64) {
        a2 = b2 = g2 = r2 = 0x80;
        for (n2 = 0; n2 < 2; n2++) {
            lamp = D_0029AE50;

            tex2 = &campaignSprites[lamp.code];
            tex2->f[4] = 0;
            tex2->f[3] = 0;
            tex2->f[1] = 0;
            tex2->f[0] = 0;
            tex2->f[6] = 0x200;
            tex2->f[2] = 0x200;
            tex2->f[7] = 0x100;
            tex2->f[5] = 0x100;
            switch (n2) {
            case 0:
                tex2->f[8] = 6;
                px2 = wk->eventPictureZoom * 576 / 100 - 0x200;
                break;
            case 1:
                switch (wk->unk546E) {
                case 0:
                    r2 = 0;
                    g2 = 0;
                    b2 = 0;
                    a2 = 0;
                    break;
                case 1:
                    r2 = 0;
                    g2 = 0;
                    b2 = 0;
                    a2 = wk->unk5470 * 128 / 100;
                    break;
                case 2:
                    r2 = 0;
                    g2 = 0;
                    b2 = wk->unk5470 * 128 / 100;
                    a2 = 0x80;
                    break;
                case 3:
                    r2 = 0;
                    g2 = wk->unk5470 * 128 / 100;
                    b2 = 0x80;
                    a2 = b2;
                    break;
                case 4:
                    r2 = wk->unk5470 * 128 / 100;
                    g2 = 0x80;
                    b2 = g2;
                    a2 = g2;
                    break;
                case 5:
                    r2 = 0x80;
                    g2 = r2;
                    b2 = r2;
                    a2 = r2;
                    break;
                }
                if (0 < wk->unk546E && wk->unk546E < 5) {
                    wk->unk5470 += 2;
                    if (wk->unk5470 >= 100) {
                        wk->unk5470 = 0;
                        if (wk->unk546E < 5) {
                            wk->unk546E += 1;
                            if (wk->unk546E >= 5) {
                                wk->unk546E = 5;
                                wk->unk5484 = 0;
                                wk->unk5486 = 0;
                            }
                        }
                    }
                }
                lamp.col[0][0] = lamp.col[0][1] = lamp.col[0][2] = lamp.col[1][0] = lamp.col[1][1] = lamp.col[1][2] = r2;
                lamp.col[0][3] = lamp.col[1][3] = b2;
                lamp.col[2][0] = lamp.col[2][1] = lamp.col[2][2] = lamp.col[3][0] = lamp.col[3][1] = lamp.col[3][2] = g2;
                lamp.col[2][3] = lamp.col[3][3] = a2;
                tex2 = &campaignSprites[lamp.code];
                tex2->f[6] = 0x180;
                tex2->f[2] = 0x180;
                tex2->f[8] = 7;
                lamp.w[6] = 0x180;
                lamp.w[2] = 0x180;
                px2 = wk->eventPictureZoom * 512 / 100 + 0x280;
                break;
            }
            if (wk->unk5436 != 0) {
                fv = px2;
                cursor = Taku_GT4_Set_b(cursor, &lamp, (s16)(fv + wk->eventPictureMapX), (s16)(100.0f + wk->eventPictureMapZ), 0, 0);
            }
        }
    } else if (H16(ctx + 0xC2) == 0x2F76 || H16(ctx + 0xC2) == 0x2BAC) {
        r3 = 0x80;
        g3 = r3;
        b3 = r3;
        c33 = r3;
        for (k3 = 0; k3 < 2; k3++) {
            lamp2 = D_0029AE80;

            tex3 = &campaignSprites[lamp2.code];
            tex3->f[4] = 0;
            tex3->f[3] = 0;
            tex3->f[1] = 0;
            tex3->f[0] = 0;
            tex3->f[6] = 0x200;
            tex3->f[2] = 0x200;
            tex3->f[7] = 0x100;
            tex3->f[5] = 0x100;
            switch (k3) {
            case 0:
                tex3->f[8] = 6;
                px3 = wk->eventPictureZoom * 576 / 100 - 0x200;
                break;
            case 1:
                switch (wk->unk546E) {
                case 0:
                    r3 = 0x80;
                    g3 = r3;
                    b3 = r3;
                    c33 = r3;
                    break;
                case 1:
                    r3 = 0x80;
                    b3 = r3;
                    c33 = r3;
                    g3 = 0x80 - wk->unk5470 * 128 / 100;
                    break;
                case 2:
                    g3 = 0;
                    r3 = 0x80 - wk->unk5470 * 128 / 100;
                    b3 = 0x80;
                    c33 = b3;
                    break;
                case 3:
                    r3 = 0;
                    g3 = 0;
                    b3 = 0x80;
                    c33 = 0x80 - wk->unk5470 * 128 / 100;
                    break;
                case 4:
                    r3 = 0;
                    g3 = 0;
                    c33 = 0;
                    b3 = 0x80 - wk->unk5470 * 128 / 100;
                    break;
                case 5:
                    r3 = 0;
                    g3 = 0;
                    b3 = 0;
                    c33 = 0;
                    break;
                }
                if (0 < wk->unk546E && wk->unk546E < 5) {
                    wk->unk5470 += 2;
                    if (wk->unk5470 >= 100) {
                        wk->unk5470 = 0;
                        if (wk->unk546E < 5) {
                            wk->unk546E += 1;
                            if (wk->unk546E >= 5) {
                                wk->unk546E = 5;
                                wk->unk5484 = 0;
                                wk->unk5486 = 0;
                            }
                        }
                    }
                }
                if (wk->unk546E < 2) {
                    wk->unk5484 = 0;
                    wk->unk5486 = 0;
                }
                if (wk->unk546E == 2 && 0x32 < wk->unk5470) {
                    wk->unk5484 = 1;
                }
                lamp2.col[0][0] = lamp2.col[0][1] = lamp2.col[0][2] = lamp2.col[1][0] = lamp2.col[1][1] = lamp2.col[1][2] = r3;
                lamp2.col[0][3] = lamp2.col[1][3] = b3;
                lamp2.col[2][0] = lamp2.col[2][1] = lamp2.col[2][2] = lamp2.col[3][0] = lamp2.col[3][1] = lamp2.col[3][2] = g3;
                lamp2.col[2][3] = lamp2.col[3][3] = c33;
                tex3 = &campaignSprites[lamp2.code];
                tex3->f[6] = 0x180;
                tex3->f[2] = 0x180;
                tex3->f[8] = 7;
                lamp2.w[6] = 0x180;
                lamp2.w[2] = 0x180;
                px3 = wk->eventPictureZoom * 512 / 100 + 0x280;
                break;
            }
            if (wk->unk5436 != 0) {
                fv = px3;
                cursor = Taku_GT4_Set_b(cursor, &lamp2, (s16)(fv + wk->eventPictureMapX), (s16)(100.0f + wk->eventPictureMapZ), 0, 0);
                if (k3 == 1 && wk->unk5484 != 0) {
                    x13 = px3 + 0xB2;
                    x23 = px3 + 0xC6;

                    for (i3 = 0, pb = &bars.o[0]; i3 < 4; i3++, pb++) {
                        if (i3 < 2) {
                            if (wk->unk5486 % 2 != 0) {
                                for (q3 = 0; q3 < 8; q3++) {
                                    pb->w[q3] >>= 1;
                                }
                            }
                        }
                        switch (i3) {
                        case 2:
                            pb->w[0] = pb->w[4] = wk->unk5486 * -3 * 128 >> 5;
                            break;
                        case 3:
                            pb->w[2] = pb->w[6] = wk->unk5486 * 3 * 128 >> 5;
                            break;
                        }
                        if (wk->unk5486 > 0x18) {
                            dt3 = wk->unk5486 - 0x18;
                            pb->col[0][3] = pb->col[0][3] - (dt3 * pb->col[0][3] >> 3);
                            pb->col[1][3] = pb->col[1][3] - (dt3 * pb->col[1][3] >> 3);
                            pb->col[2][3] = pb->col[2][3] - (dt3 * pb->col[2][3] >> 3);
                            pb->col[3][3] = pb->col[3][3] - (dt3 * pb->col[3][3] >> 3);
                        }
                        cursor = Taku_G4_Set_b(cursor, pb, x13, 0xC8);
                        cursor = Taku_G4_Set_b(cursor, pb, x23, 0xC8);
                    }
                    wk->unk5486 += 1;
                    if (wk->unk5486 >= 0x20) {
                        wk->unk5486 = 0x20;
                    }
                }
            }
        }
    } else {
        size = D_0029AEA8;
        cnt4 = 2;
        alpha4 = 0x80;
        campaignSprites[page.o[0].code].f[2] = campaignSprites[page.o[0].code].f[6] = campaignSprites[page.o[1].code].f[2] =
            campaignSprites[page.o[1].code].f[6] = 0x100;
        if ((H16(ctx + 0xC2) >= 0x2760 && H16(ctx + 0xC2) <= 0x2AF8) || H16(ctx + 0xC2) == 0x2EE0) {
            page.o[1].w[2] = page.o[1].w[6] = 0x200;
            campaignSprites[page.o[1].code].f[2] = campaignSprites[page.o[1].code].f[6] = 0x200;
            size.y = 0x100;
        }
        if (H16(ctx + 0xC2) >= 0x2B84 && H16(ctx + 0xC2) < 0x2B86) {
            page.o[0].w[2] = page.o[0].w[6] = 0x180;
            campaignSprites[page.o[0].code].f[2] = campaignSprites[page.o[0].code].f[6] = 0x180;
            size.x = 0x80;
        }
        if (H16(ctx + 0xC2) >= 0x2B98 && H16(ctx + 0xC2) < 0x2B9B) {
            page.o[0].w[2] = page.o[0].w[6] = 0x200;
            campaignSprites[page.o[0].code].f[2] = campaignSprites[page.o[0].code].f[6] = 0x200;
            page.o[1].w[2] = page.o[1].w[6] = 0x180;
            size.x = 0x100;
            campaignSprites[page.o[1].code].f[2] = campaignSprites[page.o[1].code].f[6] = 0x180;
            size.y = 0x80;
        }
        if (H16(ctx + 0xC2) >= 0x2F62 && H16(ctx + 0xC2) < 0x2F65) {
            page.o[0].w[2] = page.o[0].w[6] = 0x200;
            campaignSprites[page.o[0].code].f[2] = campaignSprites[page.o[0].code].f[6] = 0x200;
            page.o[1].w[2] = page.o[1].w[6] = 0x180;
            size.x = 0x100;
            campaignSprites[page.o[1].code].f[2] = campaignSprites[page.o[1].code].f[6] = 0x180;
            size.y = 0x80;
        }
        if (H16(ctx + 0xC2) == 0x2F78) {
            page.o[0].w[2] = page.o[0].w[6] = 0x200;
            campaignSprites[page.o[0].code].f[2] = campaignSprites[page.o[0].code].f[6] = 0x200;
            size.x = 0x100;
            cnt4 = 1;
            page.o[1].w[6] = 0x180;
            page.o[1].w[2] = 0x180;
            campaignSprites[page.o[1].code].f[6] = 0x180;
            campaignSprites[page.o[1].code].f[2] = 0x180;
            size.y = 0x80;
        }
        if (H16(ctx + 0xC2) == 0x2EE0) {
            switch (campaignWork.unk546E) {
            case 0:
                alpha4 = 0x80;
                break;
            case 1:
                alpha4 = 0x80 - campaignWork.unk5470 * 128 / 100;
                break;
            case 5:
                alpha4 = 0;
                break;
            }
            if (0 < campaignWork.unk546E && campaignWork.unk546E < 5) {
                campaignWork.unk5470 += 2;
                if (campaignWork.unk5470 >= 100) {
                    campaignWork.unk5470 = 0;
                    if (campaignWork.unk546E < 5) {
                        campaignWork.unk546E += 1;
                        if (campaignWork.unk546E >= 2) {
                            campaignWork.unk546E = 5;
                        }
                    }
                }
            }
            page.o[0].col[0][3] = alpha4;
        }
        if (campaignWork.unk5436 != 0) {
            fx4 = 0.0f;
            fz4 = fx4;
            if (H16(ctx + 0xC2) == 0x2F62 || H16(ctx + 0xC2) == 0x2B98) {
                fx4 = campaignWork.eventPictureMapX;
                fz4 = campaignWork.eventPictureMapZ;
            }
            cursor = Taku_Obj_Set_b(cursor, &page.o[0],
                                    (s16)(fx4 + (f32)((-0x100 - size.x) + (s16)(((size.x >> 1) + 0x1C0) * campaignWork.eventPictureZoom / 100))),
                                    (s16)(100.0f + fz4));
            if (cnt4 == 2) {
                cursor = Taku_Obj_Set_b(cursor, &page.o[1], (s16)((s16)(((size.y >> 1) + 0x1C0) * campaignWork.eventPictureZoom / 100) + 0x280), 100);
            }
        }
    }
    return cursor;
}

typedef struct {
    s16 x0, y0, x1, y1;
    s16 kind;
} BunWin;

typedef struct {
    s32 x, y, w, h;
} BunBox;

typedef struct {
    s32 id;
    BunBox box;
} BunInfo;

typedef struct {
    s32 v[4];
} __attribute__((aligned(16))) BunRect;

typedef struct {
    s16 v[19];
} BunG4;

extern s32 func_00218970_b(s32, void *, s16, s16);
extern s32 SzMsg_DrawRatioX_Pipe_b(s32, s32, s32, s32, f32, f32, void *, void *);
extern void SzMsg_DrawRect_Pipe_b(void);
extern s32 func_001FE7D0_b(s32, s32, s32, s32, void *, void *);
extern BunRect worldMapDialogueTextXOffset;
extern BunG4 D_00298AF6 __attribute__((aligned(2)));
extern BunWin D_00297B72 __attribute__((aligned(2)));

/* Draws (hyouji) the campaign text window: the speaker's face and the text line by line. (original: Taku_Camp_BUN_HYOUJI) */
s32 Taku_Camp_TEXT_SHOW(s32 p) {
    s16 flagB;
    s16 i;
    CampaignWork *w;
    s8 *ctx;
    s16 j;
    s16 count;
    u8 col[4][4];
    BunBox box;
    BunRect rect;
    BunG4 g4;
    BunBox box2;
    BunWin win;
    BunWin win2;
    s32 msg;
    s16 flagA;

    w = &campaignWork;
    msg = 0;
    flagB = 0;
    flagA = 0;
    ctx = &campaignState;
    rect = worldMapDialogueTextXOffset;
    for (i = 0; i < 4; i++) {
        col[i][0] = col[i][1] = col[i][2] = 0x80;
        col[i][3] = 0x80;
    }
    w->opponentLook = 0;
    if (w->talkStep != 0) {
        if (w->talkSpeaker == 0) {
            BunInfo *info;
            s32 x;
            s16 n;
            s32 ty;
            s32 y;

            g4 = D_00298AF6;
            p = SzMsg_LoadFont_Pipe(p, 1, w->talkMessage, 0, 0x16);
            p = RhText_SetTextureFlush(p);
            info = SzMsg_GetInfo(1);
            box = info->box;
            rect.v[2] = box.w;
            count = box.h / 22;
            if (count > 3) {
                count = 3;
            }
            if (*(s16 *)(ctx + 0xC2) < 200) {
                w->opponentLook = 0;
            } else if (*(s16 *)(ctx + 0xC2) < 300) {
                w->opponentLook = 1;
            } else {
                w->opponentLook = 2;
                if (*(s16 *)(ctx + 0xC4) == 14 && w->talkPage == 1) {
                    w->opponentLook = 3;
                }
            }
            switch (w->talkStep) {
            case 1:
                w->unk53A0 = 0;
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 4; i++) {
                        w->unk5380[j + 1][i] = 0;
                    }
                }
                w->talkStep++;
                break;
            case 2:
                w->unk53A0 += 20;
                if (w->unk53A0 >= 100) {
                    w->unk53A0 = 100;
                    w->talkStep++;
                }
                break;
            case 3:
                w->opponentFaceState = 10;
                for (j = 0; j < count; j++) {
                    for (i = 0; i < 4; i++) {
                        switch (i) {
                        case 1:
                            if (w->unk5380[j + 1][2] >= 0x80) {
                                w->unk5380[j + 1][i] += 0x20;
                            }
                            break;
                        case 2:
                            if (w->unk5380[j + 1][0] > 0x40) {
                                w->unk5380[j + 1][i] += 0x20;
                            }
                            break;
                        case 3:
                            if (w->unk5380[j + 1][1] > 0x20) {
                                w->unk5380[j + 1][i] += 0x20;
                            }
                            break;
                        default:
                            if (j == 0) {
                                w->unk5380[j + 1][i] += 0x20;
                            } else if (w->unk5380[j][1] >= 0x80) {
                                w->unk5380[j + 1][i] += 0x20;
                            }
                            break;
                        }
                        if (w->unk5380[j + 1][i] >= 0x80) {
                            w->unk5380[j + 1][i] = 0x80;
                        }
                    }
                }
                if (w->unk5380[count][3] >= 0x80) {
                    w->talkStep++;
                }
                break;
            case 4:
                break;
            case 5:
                if (w->talkPage < w->talkMessageCount) {
                    for (j = 0; j < count; j++) {
                        for (i = 0; i < 4; i++) {
                            w->unk5380[j + 1][i] -= 0x10;
                            if (w->unk5380[j + 1][i] <= 0) {
                                w->unk5380[j + 1][i] = 0;
                            }
                        }
                    }
                    if (w->unk5380[count][3] <= 0) {
                        for (j = 0; j < 3; j++) {
                            for (i = 0; i < 4; i++) {
                                w->unk5380[j + 1][i] = 0;
                            }
                        }
                        w->talkStep = 2;
                        w->talkPage++;
                        Taku_Camp_TEXT_PICK();
                    }
                } else {
                    w->talkStep = 11;
                }
                break;
            case 11:
                for (j = 0; j < count; j++) {
                    for (i = 0; i < 4; i++) {
                        w->unk5380[j + 1][i] -= 0x10;
                        if (w->unk5380[j + 1][i] <= 0) {
                            w->unk5380[j + 1][i] = 0;
                        }
                    }
                }
                if (w->unk5380[count][3] <= 0) {
                    for (j = 0; j < 3; j++) {
                        for (i = 0; i < 4; i++) {
                            w->unk5380[j + 1][i] = 0;
                        }
                    }
                    w->talkStep = 12;
                }
                break;
            case 12:
                if (0 <= w->unk53A0) {
                    w->unk53A0 -= 20;
                    if (w->unk53A0 <= 0) {
                        s16 ok;

                        w->unk53A0 = 0;
                        if (w->unk018C != 0 && *(s16 *)(ctx + 0xC2) >= 200) {
                            w->talkPage = 0;
                            w->talkStep = 0;
                            w->unk537A = 0;
                            *(s16 *)(ctx + 0xC2) = 0;
                            w->eventStep = 0;
                            w->moveStep = 0;
                            w->unk5372 = 0;
                            w->leaderShow = 0;
                            w->unk5375 = 0;
                            break;
                        }
                        w->unk53AB = 0;
                        ok = 1;
                        if (*(s16 *)(ctx + 0xC2) >= 300 && *(s16 *)(ctx + 0xC2) < 10000) {
                            if (w->unk537A == 3) {
                                ok = 1;
                            } else {
                                ok = 0;
                            }
                        }
                        if (w->unk5440 <= 0 && ok) {
                            w->unk5440 = 0;
                            if (ctx[0] == 0 && *(s16 *)(ctx + 0xC2) == 0x139 &&
                                ctx[3 + w->unk53C0] != 0 && *(s16 *)(ctx + 0xC2) >= 300 &&
                                *(s16 *)(ctx + 0xC2) < 10000) {
                                *(s16 *)(ctx + 0xC2) = 0x2BAC;
                                ctx[0xE] = 5;
                                break;
                            }
                            if (ctx[3 + w->unk53C0] < 3 && *(s16 *)(ctx + 0xC2) >= 300 &&
                                *(s16 *)(ctx + 0xC2) < 10000) {
                                if (ctx[0] == 0) {
                                    if (*(s16 *)(ctx + 0xC2) == 0x134) {
                                        *(s16 *)(ctx + 0xC2) = 0x2B84;
                                        ctx[3 + ctx[0xC6]] = 3;
                                    } else if (*(s16 *)(ctx + 0xC2) == 0x138) {
                                        *(s16 *)(ctx + 0xC2) = 0x2B98;
                                        ctx[0xE] = 3;
                                    } else if (*(s16 *)(ctx + 0xC2) == 0x139) {
                                        *(s16 *)(ctx + 0xC2) = 0x2BAC;
                                        ctx[0xE] = 5;
                                    } else {
                                        *(s16 *)(ctx + 0xC2) -= 200;
                                        ctx[3 + ctx[0xC6]] = 3;
                                    }
                                } else if (*(s16 *)(ctx + 0xC2) == 0x138 || ((s16 *)ctx)[0x61] == 0x139) {
                                    *(s16 *)(ctx + 0xC2) = 0x2F76;
                                    ctx[0xE] = 3;
                                } else {
                                    *(s16 *)(ctx + 0xC2) -= 200;
                                    ctx[3 + ctx[0xC6]] = 3;
                                }
                                w->talkPage = 0;
                                w->talkStep = 0;
                                w->unk537A = 0;
                                w->eventStep = 0;
                                w->moveStep = 0;
                                w->unk5372 = 1;
                                w->leaderShow = 0;
                                w->unk5375 = 1;
                            } else if (*(s16 *)(ctx + 0xC2) >= 200) {
                                if (ctx[0] == 0 && *(s16 *)(ctx + 0xC2) == 0xD5) {
                                    ctx[0xE] = 4;
                                } else if (ctx[3 + ctx[0xC6]] == 1 && *(s16 *)(ctx + 0xC2) >= 200) {
                                    ctx[3 + ctx[0xC6]] = 2;
                                }
                                w->talkPage = 0;
                                w->talkStep = 0;
                                w->unk537A = 0;
                                *(s16 *)(ctx + 0xC2) = 0;
                                w->eventStep = 0;
                                w->moveStep = 0;
                                w->unk5372 = 0;
                                w->leaderShow = 0;
                                w->unk5375 = 0;
                            }
                        }
                    }
                }
                break;
            }
            g4.v[5] = D_00298AF6.v[1] + w->unk53A0 * (D_00298AF6.v[5] - D_00298AF6.v[1]) / 100;
            g4.v[7] = g4.v[5];
            p = func_00218970_b(p, &g4, 0, 0);
            for (i = 0; i < 4; i++) {
                col[i][0] = col[i][1] = col[i][2] = 0x80;
                col[i][3] = w->unk5380[0][i];
            }
            n = count;
            x = D_00298AF6.v[0] + 6;
            ty = D_00298AF6.v[1] + 6;
            for (i = 0, y = 0; i < n; i++) {
                s16 yy = y;

                for (j = 0; j < 4; j++) {
                    col[j][3] = w->unk5380[i + 1][j];
                }
                info->box.y = box.y + i * 0x16;
                info->box.h = 0x16;
                p = SzMsg_DrawRectG_Pipe(p, 1, x, ty + yy, &rect, col[0]);
                y = (s16)(y + 0x16);
            }
            SzMsg_Free(1);
        } else if (w->talkSpeaker == 1) {
            s16 done;

            done = 0;
            if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                if (w->talkMessage > 0x7F0) {
                    w->unk542C[0] += 2;
                    if (w->unk542C[0] >= 200) {
                        w->unk542C[0] = 200;
                    }
                }
                if (w->talkMessage > 0x7F2) {
                    w->unk542C[1] += 2;
                    if (w->unk542C[1] >= 200) {
                        w->unk542C[1] = 200;
                    }
                }
                if (w->talkMessage > 0x7F3) {
                    w->unk542C[2] += 2;
                    if (w->unk542C[2] >= 200) {
                        w->unk542C[2] = 200;
                    }
                }
                if (w->talkMessage > 0x7F5) {
                    w->unk542C[3] += 2;
                    if (w->unk542C[3] >= 200) {
                        w->unk542C[3] = 200;
                    }
                }
                if (w->talkMessage >= 0x7FB) {
                    w->unk542C[4] += 2;
                    if (w->unk542C[4] >= 200) {
                        w->unk542C[4] = 200;
                        done = 1;
                    }
                }
            }
            switch (w->talkStep) {
            case 1:
                w->unk53A0 = 0;
                for (j = 0; j < 4; j++) {
                    w->unk5380[0][j] = 0;
                }
                w->talkStep++;
                break;
            case 2:
            case 3:
                if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                    switch (w->talkMessage) {
                    case 0x7F0:
                        w->unk542C[0] += 2;
                        if (w->unk542C[0] >= 100) {
                            w->unk542C[0] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7F1:
                        w->unk542C[1] += 2;
                        if (w->unk542C[1] >= 100) {
                            w->unk542C[1] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7F3:
                        w->unk542C[2] += 2;
                        if (w->unk542C[2] >= 100) {
                            w->unk542C[2] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7F4:
                        w->unk542C[3] += 2;
                        if (w->unk542C[3] >= 100) {
                            w->unk542C[3] = 100;
                            flagA = 1;
                        }
                        break;
                    case 0x7FA:
                        w->unk542C[4] += 2;
                        if (w->unk542C[4] >= 100) {
                            w->unk542C[4] = 100;
                            flagA = 1;
                        }
                        break;
                    default:
                        flagA = 1;
                        break;
                    }
                }
                for (j = 0; j < 4; j++) {
                    switch (j) {
                    case 1:
                    case 2:
                        if (w->unk5380[0][0] > 0x40) {
                            w->unk5380[0][j] += 0x20;
                        }
                        break;
                    case 3:
                        if (w->unk5380[0][1] > 0x40) {
                            w->unk5380[0][j] += 0x20;
                        }
                        break;
                    default:
                        w->unk5380[0][j] += 0x20;
                        break;
                    }
                    if (w->unk5380[0][j] >= 0x80) {
                        w->unk5380[0][j] = 0x80;
                    }
                }
                if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                    if (flagA && w->unk5380[0][3] >= 0x80) {
                        w->talkStep++;
                    }
                } else if (w->unk5380[0][3] >= 0x80) {
                    w->talkStep++;
                }
                break;
            case 4:
                break;
            case 5:
                if (*(s16 *)(ctx + 0xC2) == 0x2724 && w->talkMessage == 0x7F6) {
                    w->unk542C[3] += 2;
                    if (w->unk542C[3] >= 200) {
                        w->unk542C[3] = 200;
                        flagA = 1;
                    }
                }
                if (w->talkPage < w->talkMessageCount) {
                    for (j = 0; j < 4; j++) {
                        switch (j) {
                        case 1:
                        case 2:
                            if (w->unk5380[0][0] < 0x40) {
                                w->unk5380[0][j] -= 0x20;
                            }
                            break;
                        case 3:
                            if (w->unk5380[0][1] < 0x40) {
                                w->unk5380[0][j] -= 0x20;
                            }
                            break;
                        default:
                            w->unk5380[0][j] -= 0x20;
                            break;
                        }
                        if (w->unk5380[0][j] <= 0) {
                            w->unk5380[0][j] = 0;
                            if (*(s16 *)(ctx + 0xC2) == 0x2724 && w->talkMessage == 0x7F6) {
                                if (j == 3 && flagA) {
                                    w->talkStep = 3;
                                    w->talkPage++;
                                    Taku_Camp_TEXT_PICK();
                                }
                            } else if (j == 3) {
                                w->talkStep = 3;
                                w->talkPage++;
                                Taku_Camp_TEXT_PICK();
                            }
                        }
                    }
                } else {
                    w->talkStep = 11;
                }
                break;
            case 11:
                for (j = 0; j < 4; j++) {
                    switch (j) {
                    case 1:
                    case 2:
                        if (w->unk5380[0][0] < 0x40) {
                            w->unk5380[0][j] -= 0x20;
                        }
                        break;
                    case 3:
                        if (w->unk5380[0][1] < 0x40) {
                            w->unk5380[0][j] -= 0x20;
                        }
                        break;
                    default:
                        w->unk5380[0][j] -= 0x20;
                        break;
                    }
                    if (w->unk5380[0][j] <= 0) {
                        w->unk5380[0][j] = 0;
                        if (j == 3) {
                            if (*(s16 *)(ctx + 0xC2) == 0x2724) {
                                if (done) {
                                    w->talkStep = 12;
                                }
                            } else {
                                w->talkStep = 12;
                            }
                        }
                    }
                }
                break;
            }
            for (i = 0; i < 4; i++) {
                col[i][0] = col[i][1] = col[i][2] = 0x80;
                col[i][3] = w->unk5380[0][i];
            }
            p = SzMsg_LoadFont_Pipe(p, 1, w->talkMessage, 0, 0x16);
            p = RhText_SetTextureFlush(p);
            p = func_001FE7D0_b(p, 1, 0x59, 0x150, col, SzMsg_DrawRectG_Pipe);
            SzMsg_Free(1);
        } else {
            s32 y;
            BunInfo *info;
            s32 n;
            s32 x;
            s32 ty;

            p = SzMsg_LoadFont_Pipe(p, 1, w->talkMessage, 0, 0x16);
            p = RhText_SetTextureFlush(p);
            info = SzMsg_GetInfo(1);
            box2 = info->box;
            rect.v[2] = box2.w;
            count = box2.h / 22;
            if (count > 3) {
                count = 3;
            }
            switch (w->talkStep) {
            case 1:
                w->unk53A0 = 0;
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 4; i++) {
                        w->unk5380[j + 1][i] = 0;
                    }
                }
                w->talkStep++;
                break;
            case 2:
                if (w->unk53B4 != 0) {
                    if (w->duelistState[0] == 0) {
                        w->duelistState[0] = 1;
                    }
                    if (w->duelistSlide[0] < 0x400) {
                        w->duelistSlide[0] += 0x40;
                    }
                    if (w->duelistSlide[0] >= 0x400) {
                        w->duelistSlide[0] = 0x400;
                    }
                } else {
                    if (0 < w->duelistSlide[0]) {
                        w->duelistSlide[0] -= 0x40;
                    }
                    if (w->duelistSlide[0] <= 0) {
                        w->duelistSlide[0] = 0;
                    }
                }
                if (w->unk53B5 != 0) {
                    if (w->duelistState[1] == 0) {
                        w->duelistState[1] = 1;
                    }
                    if (w->duelistSlide[1] < 0x400) {
                        w->duelistSlide[1] += 0x40;
                    }
                    if (w->duelistSlide[1] >= 0x400) {
                        w->duelistSlide[1] = 0x400;
                    }
                } else {
                    if (0 < w->duelistSlide[1]) {
                        w->duelistSlide[1] -= 0x40;
                    }
                    if (w->duelistSlide[1] <= 0) {
                        w->duelistSlide[1] = 0;
                    }
                }
                if (w->unk53B4 != 0 && w->unk53B5 != 0) {
                    if (w->duelistSlide[0] >= 0x400 && w->duelistSlide[1] >= 0x400) {
                        w->talkStep++;
                    }
                } else if (w->unk53B4 != 0 && w->unk53B5 == 0) {
                    if (w->duelistSlide[0] >= 0x400 && w->duelistSlide[1] <= 0) {
                        w->talkStep++;
                    }
                } else if ((s8)w->unk53B4 == 0 && w->unk53B5 != 0) {
                    if (w->duelistSlide[0] <= 0 && w->duelistSlide[1] >= 0x400) {
                        w->talkStep++;
                    }
                } else if (w->duelistSlide[0] <= 0 && w->duelistSlide[1] <= 0) {
                    w->talkStep++;
                }
                break;
            case 3:
                if (w->talkSpeaker == 2) {
                    if (w->unk53B5 != 0) {
                        w->eventPictureZoom += 10;
                        if (w->eventPictureZoom >= 100) {
                            w->eventPictureZoom = 100;
                            w->duelistState[1] = 10;
                            flagB = 1;
                        }
                    } else if (w->eventPictureZoom <= 0) {
                        w->eventPictureZoom += 10;
                        if (0 <= w->eventPictureZoom) {
                            flagB = 1;
                            w->eventPictureZoom = 0;
                        }
                    } else {
                        w->eventPictureZoom -= 10;
                        if (w->eventPictureZoom <= 0) {
                            flagB = 1;
                            w->eventPictureZoom = 0;
                        }
                    }
                }
                if (w->talkSpeaker == 3) {
                    if (w->unk53B4 != 0) {
                        w->eventPictureZoom -= 10;
                        if (w->eventPictureZoom < -100) {
                            w->eventPictureZoom = -100;
                            w->duelistState[0] = 10;
                            flagB = 1;
                        }
                    } else if (w->eventPictureZoom <= 0) {
                        w->eventPictureZoom += 10;
                        if (0 <= w->eventPictureZoom) {
                            flagB = 1;
                            w->eventPictureZoom = 0;
                        }
                    } else {
                        w->eventPictureZoom -= 10;
                        if (w->eventPictureZoom <= 0) {
                            flagB = 1;
                            w->eventPictureZoom = 0;
                        }
                    }
                }
                if (flagB) {
                    for (j = 0; j < count; j++) {
                        for (i = 0; i < 4; i++) {
                            switch (i) {
                            case 1:
                                if (w->unk5380[j + 1][2] >= 0x80) {
                                    w->unk5380[j + 1][i] += 0x20;
                                }
                                break;
                            case 2:
                                if (w->unk5380[j + 1][0] > 0x40) {
                                    w->unk5380[j + 1][i] += 0x20;
                                }
                                break;
                            case 3:
                                if (w->unk5380[j + 1][1] > 0x20) {
                                    w->unk5380[j + 1][i] += 0x20;
                                }
                                break;
                            default:
                                if (j == 0) {
                                    w->unk5380[j + 1][i] += 0x20;
                                } else if (w->unk5380[j][1] >= 0x80) {
                                    w->unk5380[j + 1][i] += 0x20;
                                }
                                break;
                            }
                            if (w->unk5380[j + 1][i] >= 0x80) {
                                w->unk5380[j + 1][i] = 0x80;
                            }
                        }
                    }
                }
                if (w->unk5380[count][3] >= 0x80) {
                    w->talkStep++;
                }
                break;
            case 4:
                break;
            case 5:
                if (w->talkPage < w->talkMessageCount) {
                    for (j = 0; j < count; j++) {
                        for (i = 0; i < 4; i++) {
                            w->unk5380[j + 1][i] -= 0x10;
                            if (w->unk5380[j + 1][i] <= 0) {
                                w->unk5380[j + 1][i] = 0;
                            }
                        }
                    }
                    if (w->unk5380[count][3] <= 0) {
                        for (j = 0; j < 3; j++) {
                            for (i = 0; i < 4; i++) {
                                w->unk5380[j + 1][i] = 0;
                            }
                        }
                        w->talkStep = 2;
                        w->talkPage++;
                        Taku_Camp_TEXT_PICK();
                    }
                } else {
                    w->talkStep = 11;
                }
                break;
            case 11:
                for (j = 0; j < count; j++) {
                    for (i = 0; i < 4; i++) {
                        w->unk5380[j + 1][i] -= 0x10;
                        if (w->unk5380[j + 1][i] <= 0) {
                            w->unk5380[j + 1][i] = 0;
                        }
                    }
                }
                if (w->unk5380[count][3] <= 0) {
                    for (j = 0; j < 3; j++) {
                        for (i = 0; i < 4; i++) {
                            w->unk5380[j + 1][i] = 0;
                        }
                    }
                    w->talkStep = 12;
                }
                break;
            case 13:
                if (w->eventPictureZoom <= 0) {
                    w->eventPictureZoom += 10;
                    if (0 <= w->eventPictureZoom) {
                        flagB = 1;
                        w->eventPictureZoom = 0;
                    }
                } else {
                    w->eventPictureZoom -= 10;
                    if (w->eventPictureZoom <= 0) {
                        flagB = 1;
                        w->eventPictureZoom = 0;
                    }
                }
                if (flagB) {
                    if (0 < w->duelistSlide[0]) {
                        w->duelistSlide[0] -= 0x40;
                    }
                    if (0 < w->duelistSlide[1]) {
                        w->duelistSlide[1] -= 0x40;
                    }
                    if (w->duelistSlide[0] <= 0) {
                        w->duelistSlide[0] = 0;
                        if (w->duelistState[0] != 0) {
                            ShFace_Close((u8 *)&w->duelistFace[0]);
                            w->duelistState[0] = 0;
                        }
                    }
                    if (w->duelistSlide[1] <= 0) {
                        w->duelistSlide[1] = 0;
                        if (w->duelistState[1] != 0) {
                            ShFace_Close((u8 *)&w->duelistFace[1]);
                            w->duelistState[1] = 0;
                        }
                    }
                    if (w->duelistSlide[0] <= 0 && w->duelistSlide[1] <= 0) {
                        w->talkStep = 14;
                        w->unk53B4 = 0;
                        w->unk53B5 = 0;
                    }
                }
                break;
            }
            if (w->talkSpeaker == 2) {
                x = 0xA0;
                ty = 0x160;
            } else {
                x = 0x18;
                ty = 0x30;
            }
            n = count;
            for (i = 0, y = 0; i < n; i++) {
                s16 yy = y;

                for (j = 0; j < 4; j++) {
                    col[j][3] = w->unk5380[i + 1][j];
                }
                info->box.y = box2.y + i * 0x16;
                info->box.h = 0x16;
                if (w->unk5483 == 0) {
                    p = SzMsg_DrawRectG_Pipe(p, 1, x, ty + yy, &rect, col[0]);
                }
                y = (s16)(y + 0x16);
            }
            SzMsg_Free(1);
        }
    }
    if (w->unk006E != 0 && w->windowOpen == 0 && w->unk5374 == 0 && w->unk0004 == 0 &&
        w->unk0072 == 0 && w->cursorOnIcon == 0 && w->unk5481 != 0 && SzEffect_IsUse2(-1, -1) == 0 &&
        w->routesIdle != 0 && w->placesReached == 0) {
        BunInfo *info;
        f32 sy;
        f32 sx;

        win = D_00297B72;
        msg = 0x886;
        p = SzMsg_LoadFont_Pipe(p, 1, msg, 0, 0x16);
        p = RhText_SetTextureFlush(p);
        info = SzMsg_GetInfo(1);
        win.x1 = (s16)info->box.w + 12;
        win.y1 = (s16)info->box.h + 12;
        p = Taku_Window_Set(p, &win, 2, 0, 0xC4, 0x30, 0, 0x80, 0x40);
        for (i = 0; i < 4; i++) {
            col[i][0] = col[i][1] = col[i][2] = 0x80;
            col[i][3] = 0x80;
        }
        sy = sx = 1.0f;
        p = SzMsg_DrawRatioX_Pipe_b(p, 1, 0xCA, 0x36, sx, sy, col, SzMsg_DrawRect_Pipe_b);
        SzMsg_Free(1);
    }
    switch (*(s16 *)(ctx + 0xC2)) {
    case 0x2B70:
        msg = 0x8AB;
        break;
    case 0x2B74:
        msg = 0x8AD;
        break;
    case 0x2B8D:
        msg = 0x8DF;
        break;
    }
    if (w->unk5483 != 0) {
        BunInfo *info;
        s32 x;

        win2 = D_00297B72;
        p = SzMsg_LoadFont_Pipe(p, 1, msg, 0, 0x16);
        p = RhText_SetTextureFlush(p);
        info = SzMsg_GetInfo(1);
        win2.x1 = (s16)info->box.w + 12;
        win2.y1 = (s16)info->box.h + 12;
        x = 0x140 - (info->box.w >> 1);
        p = Taku_Window_Set(p, &win2, 2, 0, x, 0xE0, 0, 0x80, 0x40);
        for (i = 0; i < 4; i++) {
            col[i][0] = col[i][1] = col[i][2] = 0x80;
            col[i][3] = 0x80;
        }
        p = SzMsg_DrawRatioX_Pipe_b(p, 1, x + 6, 0xE6, 1.0f, 1.0f, col, SzMsg_DrawRect_Pipe_b);
        SzMsg_Free(1);
    }
    return p;
}
