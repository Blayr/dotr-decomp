#include "common.h"
#include "campaign.h"

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
extern int campaignAct2Lock; /* original: ACT2_Rock */
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
    extern Side_00228460 campaignPlaces[];
    CampaignWork *work;
    s16 i;

    switch (campaignWork.eventStep) {
    case 0:
        campaignWork.cinemaState = 1;
        campaignWork.cinemaMode = 0;
        Taku_Base_Route_init(player, side, 3, items, count);
        (campaignWork.eventStep)++;
    case 1:
        if (campaignWork.cinemaState == 2) {
            if (player == 0) {
                work = &campaignWork;
                for (i = 0; i < count; i++) {
                    if (work->routes[player][items[i]].state != 3) {
                        work->routes[player][items[i]].state = campaignPlaces[side].slots[i];
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
#pragma optimization_level reset

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


extern Card_00228660 campaignRoutes[][16]; /* original: root_no */
extern s8 D_00299E13[];
extern s8 D_00299ED7;

/* Sets up the route marks (dodai) between campaign places for `player` on `side`. (original: Taku_Dodai_Root_init) */
void Taku_Base_Route_init(s16 player, s16 side, s8 state, s16 *items, s16 count) {
    extern Side_00228660 campaignPlaces[];
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
    D_00299ED7 = side;
    campaignWork.leaderT = 0;
    campaignWork.leaderPoint = 0;
    campaignWork.leaderMoveState = 0;
    campaignWork.unk546C = 0;
    D_00299E13[side] = state;

    for (i = 0; i < count; i++) {
        item = items[i];
        if (player == 0 && campaignPlaces[side].slots[i] == 2) {
            id = campaignRoutes[player][item].special;
        } else {
            id = campaignRoutes[player][item].normal;
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
    extern f32 campaignPlaces[];
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
            ((f32)progress * campaignPlaces[from * 13]) / 256.0f;
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
            pt = &((Side_00228660 *)campaignPlaces)[(s16)from];
            campaignWork.moveFromZ = campaignWork.cameraTarget[2];
            for (; i < count; i++) {
                entry = *route;
                if (side == 0 && pt->slots[i] == 2) {
                    location = campaignRoutes[side][(s16)entry].special;
                } else {
                    location = campaignRoutes[side][(s16)entry].normal;
                }
                selected = (s16)location;
                if (selected != 7) {
                    point = (u8 *)campaignPlaces + selected * 0x34;
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
    extern f32 campaignPlaces[];
    extern f32 D_00298BA8[];
    s16 routeCount;
    s8 mode;

    routeCount = 0;
    mode = campaignWork.unk5372;
    switch (mode) {
    case 0:
        if (campaignWork.eventStep == 0) {
            Taku_Base_Route_init(player, place, 3, &routeCount, 0);
            campaignWork.eventStep += 1;
        }
        break;
    case 1:
        if (campaignWork.moveStep == 0) {
            campaignWork.moveFromX = campaignWork.cameraTarget[0];
            campaignWork.moveFromZ = campaignWork.cameraTarget[2];
        }
        campaignWork.cameraTarget[0] = (campaignWork.moveFromX * (f32)(0x100 - campaignWork.moveStep) / 256.0f) +
                             ((f32)campaignWork.moveStep * campaignPlaces[place * 13] / 256.0f);
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

extern f32 campaignPlaces[]; /* original: model_data */
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
                 (campaignPlaces[state->selection * 13] - startX)) / 256.0f;
            startZ = campaignWork.moveFromZ;
            campaignWork.cameraTarget[2] = startZ +
                ((f32)campaignWork.moveStep *
                 (D_00298BA8[state->selection * 13] - startZ)) / 256.0f;
            index = state->selection * 13;
            if (campaignWork.cameraTarget[0] == campaignPlaces[index]) {
                if (campaignWork.cameraTarget[2] == D_00298BA8[index]) {
                    campaignWork.moveStep = 256;
                }
            }
            if (campaignWork.moveStep >= 256) {
                campaignWork.moveStep = 0;
                campaignWork.cameraTarget[0] = campaignPlaces[state->selection * 13];
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
        campaignWork.cameraTarget[0] = campaignPlaces[place * 13];
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
    extern u8 D_002964A0[];
    extern u8 D_002964C6[];
    extern u8 D_002964EC[];
    extern s32 campaignTextures[];
    extern s32 D_00299DD4;
    extern s16 D_00299ED2;
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
    D_00299DD4 = func_001AF140(6);
    switch (D_00299ED2) {                           /* irregular */
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
            result = func_00217CB0(result, D_002964A0, campaignWork.cursorX, campaignWork.cursorY);
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

extern s16 D_00299ED2;


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

    if (D_00299ED2 >= 0x2756 &&
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
    extern f32 campaignPlaces[];
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
    src = (Item_0022A710 *)campaignPlaces;
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
extern struct DotrLeaderModelBoard D_00299E10_b;
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
    signed char *w = (signed char *)&D_00299E10_b;
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

    bankLists = (PointList_0022C450 *)campaignRoutes;
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
