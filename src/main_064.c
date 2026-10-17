#include "common.h"

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

/* Records a campaign duel's result (win if `side` is set): the win counts, the streak, and the place's new state. */
void Taku_Camp_What_KATIMAKE(int side)
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

/* Taku_Nagare2_set at optimisation level 3: the shape from the dotr_decomp project's near-miss drop
 * (dotr-big/dev/near-misses-2026-10-16, CC0), in this project's names. */

typedef struct {
    u8 pad[0x26];
    s16 slots[7];
} Side_00228460;

typedef struct {
    f32 x[64];
    f32 z[64];
    s16 count;
    s16 value;
} Path_00228460;

typedef struct {
    u8 pad0[0x22C];
    Path_00228460 paths[2][16];
} Work_00228460;

#pragma optimization_level 3

/* Sets up the next flow (nagare) of the campaign for `player` on `side`: the places it opens. */
void Taku_Nagare2_set(s16 player, s16 side, s16 *items, s16 count) {
    extern Side_00228460 campaignPlaces[];
    Work_00228460 *work;
    s16 i;

    switch (*(s16 *)0x01ED536C) {
    case 0:
        *(s16 *)0x01ED001C = 1;
        *(s16 *)0x01ED001A = 0;
        Taku_Dodai_Root_init(player, side, 3, items, count);
        (*(s16 *)0x01ED536C)++;
    case 1:
        if (*(s16 *)0x01ED001C == 2) {
            if (player == 0) {
                work = (Work_00228460 *)0x01ED0000;
                for (i = 0; i < count; i++) {
                    if (work->paths[player][items[i]].value != 3) {
                        work->paths[player][items[i]].value = campaignPlaces[side].slots[i];
                    } else {
                        work->paths[player][items[i]].value = 3;
                    }
                }
            } else {
                s16 n = items[0];
                if (((Work_00228460 *)0x01ED0000)->paths[player][n].value != 3) {
                    ((Work_00228460 *)0x01ED0000)->paths[player][n].value = 1;
                } else {
                    ((Work_00228460 *)0x01ED0000)->paths[player][n].value = 3;
                }
            }
            (*(s16 *)0x01ED536C)++;
        }
        break;
    }
    Taku_Tyumoku_ido0(player, side, items, count);
    Taku_Tyumoku_ido_kettei(player, side, 2);
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

typedef struct {
    f32 x[64];
    f32 z[64];
    s16 count;
    s16 value;
} Path_00228660;

typedef struct {
    u8 pad0[0x22C];
    Path_00228660 paths[2][16];
    s16 values[2][16];
    s16 rows[2][16][64];
    s16 countA[32];
    s16 countB[32];
    u8 pad536C[4];
    s16 saved;
} Work_00228660;

extern Card_00228660 campaignRoutes[][16]; /* original: root_no */
extern s8 D_00299E13[];
extern s8 D_00299ED7;

/* Sets up the route marks (dodai) between campaign places for `player` on `side`. */
void Taku_Dodai_Root_init(s16 player, s16 side, s8 state, s16 *items, s16 count) {
    extern Side_00228660 campaignPlaces[];
    Work_00228660 *work = (Work_00228660 *)0x01ED0000;
    s8 *status = &campaignState;
    s16 i;
    s16 item;
    s16 id;

    *(s16 *)0x01ED0060 = 0;
    *(s8 *)0x01ED5372 = 1;
    *(s8 *)0x01ED5373 = 0;
    *(s8 *)0x01ED537B = 0;
    *(s8 *)0x01ED53A0 = 0;
    *(s8 *)0x01ED5375 = 1;
    D_00299ED7 = side;
    *(s16 *)0x01ED01DA = 0;
    *(s16 *)0x01ED01DE = 0;
    *(s16 *)0x01ED01D8 = 0;
    *(s8 *)0x01ED546C = 0;
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

            work->countA[id] = 0;
            work->countB[id] = 0;
            status[id + 3] = 0;
            work->paths[player][item].value = 0;
            work->values[player][item] = 0;
            for (j = 0; j < 64; j++) {
                work->rows[player][item][j] = 0;
            }
        }
    }

    if (player == 0 && work->paths[player][12].value == 0) {
        s16 total = 0;
        s16 index;

        for (index = 2; index <= 10; index++) {
            if (status[index + 3] >= 3) {
                total++;
                if (total >= 8) {
                    work->saved = *(s16 *)(status + 0xC2);
                    *(s16 *)(status + 0xC2) = 0x2B70;
                }
            }
        }
    }
}

/* Starts the ship (fune) moving from place `from` to place `to` on the campaign map. */
void Taku_Fune_init(s16 from, s16 to) {
    *(s16 *)0x01ED01A4 = from;
    *(s16 *)0x01ED01B2 = to;
    *(s16 *)0x01ED01B0 = 0;
    *(s16 *)0x01ED01A6 = 0;
    *(s8 *)0x01ED01B4 = 1;
}

/* Moves the campaign camera's focus (tyumoku) towards its target by one step; 1 when it got there. */
s32 Taku_Tyumoku_ido(void) {
    s16 step;
    s16 step2;

    if (*(s16 *)0x01ED0060 == 0) {
        *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
        *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
    }
    *(s16 *)0x01ED0060 += 0x10;
    if (*(s16 *)0x01ED0060 >= 0x100) {
        *(s16 *)0x01ED0060 = 0x100;
    }
    step = *(s16 *)0x01ED0060;
    *(f32 *)0x01ED0040 = ((*(f32 *)0x01ED0050 * (f32)(0x100 - step)) / 256.0f) + ((*(f32 *)0x01ED01B8 * (f32)step) / 256.0f);
    step2 = *(s16 *)0x01ED0060;
    *(f32 *)0x01ED0048 = ((*(f32 *)0x01ED0058 * (f32)(0x100 - step2)) / 256.0f) + ((*(f32 *)0x01ED01C0 * (f32)step2) / 256.0f);
    if (*(s16 *)0x01ED0060 >= 0x100) {
        *(s16 *)0x01ED0060 = 0;
        *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
        *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
        *(s8 *)0x01ED5372 = 0;
        *(s8 *)0x01ED5375 = 0;
        return 1;
    }
    return 0;
}

/* Moves the campaign camera's focus along the route from place `from` (first move). */
s32 Taku_Tyumoku_ido0(s16 player, s16 from, s16 *route, s16 count) {
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
    switch (*(s8 *)0x01ED5372) {
    case 1:
        if (*(s16 *)0x01ED0060 == 0) {
            *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
            *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
        }
        *(s16 *)0x01ED0060 += 0x10;
        if (*(s16 *)0x01ED0060 >= 0x100) {
            *(s16 *)0x01ED0060 = 0x100;
        }
        progress = *(s16 *)0x01ED0060;
        *(f32 *)0x01ED0040 =
            (*(f32 *)0x01ED0050 * (f32)(0x100 - progress)) / 256.0f +
            ((f32)progress * campaignPlaces[from * 13]) / 256.0f;
        progress = *(s16 *)0x01ED0060;
        *(f32 *)0x01ED0048 =
            (*(f32 *)0x01ED0058 * (f32)(0x100 - progress)) / 256.0f +
            ((f32)progress * D_00298BA8[from * 13]) / 256.0f;
        if (*(s16 *)0x01ED0060 >= 0x100) {
            *(s16 *)0x01ED0060 = 0;
            *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
            *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
            *(s8 *)0x01ED5372 += 1;
        }
        break;
    case 2:
        if (*(s16 *)0x01ED0060 == 0) {
            sum_x = 0.0f;
            sum_z = 0.0f;
            side = (s16)player;
            *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
            skipped = 0;
            i = 0;
            pt = &((Side_00228660 *)campaignPlaces)[(s16)from];
            *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
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
            *(f32 *)0x01ED01C8 = sum_x / divisor;
            *(f32 *)0x01ED01D0 = sum_z / divisor;
        }
        progress = *(s16 *)0x01ED0060;
        *(f32 *)0x01ED0040 =
            (*(f32 *)0x01ED0050 * (f32)(0x100 - progress)) / 256.0f +
            (*(f32 *)0x01ED01C8 * (f32)progress) / 256.0f;
        progress = *(s16 *)0x01ED0060;
        *(f32 *)0x01ED0048 =
            (*(f32 *)0x01ED0058 * (f32)(0x100 - progress)) / 256.0f +
            (*(f32 *)0x01ED01D0 * (f32)progress) / 256.0f;
        *(s16 *)0x01ED0060 += 8;
        if (*(s16 *)0x01ED0060 > 0x100) {
            *(s16 *)0x01ED0060 = 0;
            *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
            *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
            *(s8 *)0x01ED5372 = 0;
            *(s8 *)0x01ED5375 = 0;
            state[0x61] = 0;
            return 1;
        }
        break;
    }
    return 0;
}

/* Moves the campaign camera's focus to place `place` of `player`; 1 when it got there. */
s32 Taku_Tyumoku_ido1(s16 player, s16 place) {
    extern f32 campaignPlaces[];
    extern f32 D_00298BA8[];
    s16 routeCount;
    s8 mode;

    routeCount = 0;
    mode = *(s8 *)0x01ED5372;
    switch (mode) {
    case 0:
        if (*(s16 *)0x01ED536C == 0) {
            Taku_Dodai_Root_init(player, place, 3, &routeCount, 0);
            *(s16 *)0x01ED536C += 1;
        }
        break;
    case 1:
        if (*(s16 *)0x01ED0060 == 0) {
            *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
            *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
        }
        *(f32 *)0x01ED0040 = (*(f32 *)0x01ED0050 * (f32)(0x100 - *(s16 *)0x01ED0060) / 256.0f) +
                             ((f32)*(s16 *)0x01ED0060 * campaignPlaces[place * 13] / 256.0f);
        *(f32 *)0x01ED0048 = (*(f32 *)0x01ED0058 * (f32)(0x100 - *(s16 *)0x01ED0060) / 256.0f) +
                             ((f32)*(s16 *)0x01ED0060 * D_00298BA8[place * 13] / 256.0f);
        *(s16 *)0x01ED0060 += 0x10;
        if (*(s16 *)0x01ED0060 > 0x100) {
            *(s16 *)0x01ED0060 = 0;
            *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
            *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
            *(s8 *)0x01ED5372 = 0;
            *(s8 *)0x01ED5375 = 0;
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

/* The player chose a place (kettei): moves the focus there, then starts its duel; 1 when the move ended. */
s32 Taku_Tyumoku_ido_kettei(s16 player, s16 place, s16 wait) {
    State_00229140 *state = (State_00229140 *)&campaignState;
    f32 startX;
    f32 startZ;
    s32 index;

    if ((*(s8 *)0x01ED5372 == 0 &&
         wait <= *(s16 *)0x01ED536C &&
         *(s8 *)0x01ED537B != 0) ||
        state->levels[state->selection] >= 2 ||
        (state->selection == 15 && state->levels[16] == 0)) {
        switch (*(s8 *)0x01ED5373) {
        case 1:
            state->previous = state->selection;
            *(f32 *)0x01ED0050 = *(f32 *)0x01ED0040;
            *(f32 *)0x01ED0058 = *(f32 *)0x01ED0048;
            *(s16 *)0x01ED0076 = *(s16 *)0x01ED0000;
            *(s16 *)0x01ED0078 = *(s16 *)0x01ED0002;
            *(s16 *)0x01ED0060 = 0;
            *(s8 *)0x01ED5373 += 1;
            *(s16 *)0x01ED01DA = 0;
            *(s16 *)0x01ED01DE = 0;
            *(s16 *)0x01ED01D8 = 1;
            state->snapshot = *(s8 *)0x01ED53C2;
            break;
        case 2:
            *(s16 *)0x01ED0060 += 8;
            startX = *(f32 *)0x01ED0050;
            *(f32 *)0x01ED0040 = startX +
                ((f32)*(s16 *)0x01ED0060 *
                 (campaignPlaces[state->selection * 13] - startX)) / 256.0f;
            startZ = *(f32 *)0x01ED0058;
            *(f32 *)0x01ED0048 = startZ +
                ((f32)*(s16 *)0x01ED0060 *
                 (D_00298BA8[state->selection * 13] - startZ)) / 256.0f;
            index = state->selection * 13;
            if (*(f32 *)0x01ED0040 == campaignPlaces[index]) {
                if (*(f32 *)0x01ED0048 == D_00298BA8[index]) {
                    *(s16 *)0x01ED0060 = 256;
                }
            }
            if (*(s16 *)0x01ED0060 >= 256) {
                *(s16 *)0x01ED0060 = 0;
                *(f32 *)0x01ED0040 = campaignPlaces[state->selection * 13];
                *(f32 *)0x01ED0048 = D_00298BA8[state->selection * 13];
                *(s8 *)0x01ED5373 = 3;
                if (state->selection == 15 && state->levels[16] == 0) {
                    state->fieldC2 = 0x2F08;
                }
                return 1;
            }
            break;
        case 3:
            if (*(s8 *)0x01ED53A0 <= 0 && *(s16 *)0x01ED01D8 == 3) {
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

/* Moves the campaign camera's focus after a duel's result (katimake: win or lose). */
s32 Taku_Tyumoku_ido_katimake(s32 won, s16 place) {
    State_00229140 *state = (State_00229140 *)&campaignState;

    *(s8 *)0x01ED53C0 = place;
    switch (*(s8 *)0x01ED537A) {
    case 0:
        if (state->levels[place] == 0) {
            state->levels[place] = 1;
        }
        *(s8 *)0x01ED5375 = 1;
        *(f32 *)0x01ED0040 = campaignPlaces[place * 13];
        *(f32 *)0x01ED0048 = D_00298BA8[place * 13];
        *(s16 *)0x01ED0000 = 0x140;
        *(s16 *)0x01ED0002 = 0xBE;
        *(s16 *)0x01ED0070 = 0;
        *(s16 *)0x01ED006C = 0;
        *(s8 *)0x01ED537B = 0;
        *(s8 *)0x01ED537D = 0;
        *(s8 *)0x01ED5440 = 100;
        state->selection = place;
        state->padC7 = place;
        state->previous = place;
        *(s16 *)0x01ED01DA = 0;
        *(s16 *)0x01ED01DE = 0;
        *(s16 *)0x01ED01D8 = 0;
        *(s8 *)0x01ED5406 = 0;
        *(s8 *)0x01ED53AB = 0;
        *(s8 *)0x01ED5472 = 0;
        *(s8 *)0x01ED537A = 1;
        break;
    case 1:
        if (*(s16 *)0x01ED006C >= 0x100) {
            *(s8 *)0x01ED537B = 1;
            *(s8 *)0x01ED537D = 1;
            *(s16 *)0x01ED5478 = 0;
            if (state->fieldC2 >= 300) {
                if (isSpecial_002294B0(state)) {
                    *(s8 *)0x01ED537A = 2;
                } else {
                    *(s8 *)0x01ED537A = 3;
                }
            } else {
                *(s8 *)0x01ED537A = 3;
            }
        }
        break;
    case 2:
        if (*(s8 *)0x01ED5440 <= 0) {
            *(s8 *)0x01ED5472 = 1;
            *(s32 *)0x01ED5474 += 0x1000;
            if (*(s16 *)0x01ED5478 < 0x1000) {
                *(s16 *)0x01ED5478 += 0x20;
                if (*(s16 *)0x01ED5478 >= 0x1000) {
                    *(s16 *)0x01ED5478 = 0x1000;
                    *(s8 *)0x01ED537A = 3;
                    *(s8 *)0x01ED5472 = 0;
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
    *(s8 *)0x01ED5436 = 0;
    if ((*(s16 *)(state + 0xC2) >= 0x2724) && (*(s16 *)(state + 0xC2) < 0x2738) && (*(s8 *)0x01ED537D >= 3)) {
        cards[6] = func_00202BF0(8, 20);
        cards[7] = func_00202BF0(8, 22);
        cards[8] = func_00202BF0(8, 19);
        cards[9] = func_00202BF0(8, 18);
        cards[10] = func_00202BF0(8, 21);
        *(s8 *)0x01ED5436 = 1;
        var_s3 = 8;
    }
    if ((*(s16 *)(state + 0xC2) >= 0x2738) && (*(s16 *)(state + 0xC2) < 0x276B)) {
        cards[6] = func_00202BF0(8, 17);
        cards[7] = func_00202BF0(8, 18);
        *(s8 *)0x01ED5436 = 1;
        var_s3 = 8;
    }
    if ((*(s16 *)(state + 0xC2) == 0x2AF8) ||
        (*(s16 *)(state + 0xC2) == 0x2EE0)) {
        cards[6] = func_00202BF0(8, 17);
        cards[7] = func_00202BF0(8, 18);
        *(s8 *)0x01ED5436 = 1;
        var_s3 = 8;
    }
    if ((*(s16 *)(state + 0xC2) >= 0x2B84) && (*(s16 *)(state + 0xC2) < 0x2B86)) {
        cards[6] = func_00202BF0(8, 20);
        cards[7] = func_00202BF0(8, 19);
        *(s8 *)0x01ED5436 = 1;
        var_s3 = 8;
    }
    if (*(s16 *)(state + 0xC2) == 0x2B8C) {
        cards[6] = func_00202BF0(8, 22);
        cards[7] = func_00202BF0(8, 19);
        *(s8 *)0x01ED5436 = 1;
        var_s3 = 8;
    }
    if ((*(s16 *)(state + 0xC2) >= 0x2B98) && (*(s16 *)(state + 0xC2) < 0x2B9B)) {
        cards[6] = func_00202BF0(8, 18);
        cards[7] = func_00202BF0(8, 23);
        *(s8 *)0x01ED5436 = 1;
        var_s3 = 8;
    }
    if (*(s16 *)(state + 0xC2) == 0x2BAC) {
        cards[6] = func_00202BF0(8, 18);
        cards[7] = func_00202BF0(8, 23);
        *(s8 *)0x01ED5436 = 1;
        var_s3 = 8;
    }
    if ((*(s16 *)(state + 0xC2) >= 0x2F62) && (*(s16 *)(state + 0xC2) < 0x2F65)) {
        cards[6] = func_00202BF0(8, 18);
        cards[7] = func_00202BF0(8, 23);
        *(s8 *)0x01ED5436 = 1;
        var_s3 = 8;
    }
    if (*(s16 *)(state + 0xC2) == 0x2F76) {
        cards[6] = func_00202BF0(8, 18);
        cards[7] = func_00202BF0(8, 23);
        *(s8 *)0x01ED5436 = 1;
        var_s3 = 8;
    }
    if (*(s16 *)(state + 0xC2) == 0x2F78) {
        cards[6] = func_00202BF0(8, 18);
        *(s8 *)0x01ED5436 = 1;
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
    if ((*(s8 *)0x01ED5374 == 0) && (*(s8 *)0x01ED5481 != 0) &&
        (func_001F5240(-1, -1) == 0) && (*(s8 *)0x01ED5376 != 0) &&
        (*(s8 *)0x01ED5482 == 0)) {
        temp_v1 = *(u16 *)0x01ED0004;
        if (temp_v1 == 0) {
            result = func_00217CB0(result, D_002964A0, *(s16 *)0x01ED0000, *(s16 *)0x01ED0002);
        } else if (temp_v1 == 1) {
            result = func_00217CB0(result, D_002964C6, *(s16 *)0x01ED0000, *(s16 *)0x01ED0002);
        } else {
            result = func_00217CB0(result, D_002964C6, *(s16 *)0x01ED0000, *(s16 *)0x01ED0002);
            result = func_00217CB0(result, D_002964EC, *(s16 *)0x01ED0000, *(s16 *)0x01ED0002);
        }
    }
    if (*(s16 *)(state + 0xC2) >= 0x2710) {
        result = func_00224E40(func_0022F3C0(result));
    }
    result = func_002347D0(result);
    result = func_002354A0(result);
    result = func_00236C50(result);
    if (*(s16 *)0x01ED0080 == 3) {
        result = Taku_Camp_Help_Window(result);
    }
    result = Taku_Camp_SINEMA_CUT(result, 0);
    result = func_002311D0(result);
    if (*(s8 *)0x01ED53B4 != 0 || *(s8 *)0x01ED53B5 != 0) {
        result = Taku_Camp_BUN_DARE_b(result, *(s8 *)0x01ED537E);
    }
    return (void *)func_0022A140(func_001AF110(Taku_Camp_BOTAN_MATI_b(result)));
}

typedef union {
    __int128 value;
    s32 axis[4];
} Rotation_0022A020;

extern Rotation_0022A020 D_0029ABB0;

/* Draws the stone in the middle of the campaign map, turning. */
s32 Taku_Camp_STON(s32 packet) {
    Rotation_0022A020 rotation;
    s8 *state = (s8 *)0x01ED0000;
    s16 i;

    rotation = D_0029ABB0;
    rotation.axis[1] = *(s16 *)0x01ED53F4;
    for (i = 0; i <= 9; i++) {
        switch (state[0x53B3]) {
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

typedef struct State_0022A140 {
    u8 pad_0000[0x53A6];
    s8 mode;
    u8 pad_53A7;
    s8 selection;
    s8 transition;
    s8 direction;
    u8 pad_53AB[0x53];
    s16 ids[3];
    u8 pad_5404[0x90];
    s8 phase;
    s8 completed;
    s8 sound[3];
    u8 pad_5499;
    s16 value;
} State_0022A140;

/* Draws the campaign's deck-card display. */
s32 Taku_DECK_CARD_DISP(s32 packetIn) {
    s32 texture[24];
    s32 draw[36];
    State_0022A140 *progress;
    s32 index;
    s32 packet;
    State_0022A140 *state = (State_0022A140 *)0x01ED0000;
    s16 i;
    s16 id;
    s16 offset;
    s16 slot;
    s8 *context = &campaignState;

    extern s32 SzDuel_StartCardSession_Pipe();
    extern void SzDuel_ClearDrawCard();

    if (D_00299ED2 >= 0x2756 &&
        *(s16 *)(context + 0xC2) < 0x2761 &&
        state->phase < 4) {
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
            s8 selection = state->selection;
            s8 direction = state->direction;
            slot = (selection + 2 - index) % 3;
            if (direction != 0) {
                if ((s8)direction == 1) {
                    switch (index) {
                    case 0:
                        slot = selection % 3;
                        offset = state->transition * 36 / 100;
                        break;
                    case 1:
                        slot = (selection + 2) % 3;
                        offset = 36 - state->transition * 18 / 100;
                        break;
                    case 2:
                        slot = (selection + 1) % 3;
                        offset = 18 - state->transition * 18 / 100;
                        break;
                    }
                } else {
                    switch (index) {
                    case 0:
                        offset = 36 - state->transition * 36 / 100;
                        break;
                    case 1:
                        offset = 18 + state->transition * 18 / 100;
                        break;
                    case 2:
                        offset = state->transition * 18 / 100;
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
            id = state->ids[slot];
            SzDuel_GetCardNodeOnScreen(draw, 0,
                         -10.0f + (f32)offset +
                             (f32)(progress->value * 640 / 100 - 640),
                         10.0f);
            SzDuel_InitCardInfo(texture, id);
            packet = SzDuel_DrawCard_Pipe(SzDuel_SetupCard2_Pipe(packet, (s32)texture, draw), (s32)draw);
            if (state->mode < 2) {
                state->completed = 0;
            }
            if (state->mode == 2 && state->phase == 0) {
                progress->value += 18;
                if (0 < progress->value &&
                    state->sound[index] == 0) {
                    SzSound_PlaySE(0, 9);
                    state->sound[index] = 1;
                }
                if (progress->value >= 100) {
                    state->completed = i;
                    progress->value = 100;
                    if (index == 2) {
                        state->phase = 1;
                    }
                }
            } else if (state->mode == 2) {
                progress->value = 100;
            } else if (state->mode >= 3) {
                if (index == 2) {
                    if (state->phase == 3) {
                        progress->value -= 6;
                        if (progress->value <= 0) {
                            progress->value = 0;
                            if (state->phase < 4) {
                                state->phase = 4;
                            }
                        }
                    } else {
                        progress->value = 100;
                    }
                } else {
                    progress->value += 6;
                    if (progress->value >= 400) {
                        progress->value = 400;
                        if (state->phase < 3) {
                            state->phase = 3;
                        }
                    }
                }
            }
            progress = (State_0022A140 *)((u8 *)progress + 2);
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

typedef struct State_0022A710 {
    u8 pad00[0x6E];
    s8 enabled;
    u8 pad6F[0x11D];
    s8 all;
    u8 pad18D[0x17];
    s16 active;
    u8 pad1A6[6];
    s8 kind;
    u8 pad1AD[5];
    s16 mode;
    u8 pad1B4[0x5138];
    s16 anim[0x20];
    s16 time[0x20];
    u8 pad536C[6];
    s8 busy;
    u8 pad5373[3];
    s8 ready;
    u8 pad5377[0xD1];
    s8 sound[0x20];
    u8 pad5468[0x19];
    s8 shown;
    s8 hidden;
} State_0022A710;

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
    State_0022A710 *row;
    State_0022A710 *state = (State_0022A710 *)0x01ED0000;
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
    for (; i <= 21; i++, src++, dst++, row = (State_0022A710 *)((u8 *)row + 2)) {
        height = 12.0f;
        if (i == 16) {
            height = 18.0f;
        }
        if (control[i + 3] != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else if (row->anim[0] != 0) {
            animating = 1;
            dst->x = 0.4f * (f32)((row->time[0] >> 2) % 2) + src->x;
            dst->y = (src->y - height) + height * (f32)row->time[0] / 256.0f;
            dst->z = src->z;
            sound = &state->sound[i];
            if (*sound == 0 && row->time[0] != 0 && i != 11) {
                SzEffect_Entry(0, 0x194, i, 0, 0);
                *sound = 1;
            }
        } else {
            dst->x = src->x;
            dst->y = src->y - height;
            dst->z = src->z;
        }
        if (control[0] == 0) {
            if (row->anim[0] != 0) {
                row->time[0] += 4;
                if (row->time[0] >= 256) {
                    row->time[0] = 0;
                    control[i + 3] = 1;
                    row->anim[0] = 0;
                    state->active = 0;
                }
            }
        } else if (i == 16) {
            if (row->anim[0] == 2) {
                row->time[0] += 4;
                if (row->time[0] >= 256) {
                    row->time[0] = 0;
                    control[i + 3] = 1;
                    row->anim[0] = 0;
                    state->active = 0;
                }
            }
        } else if (row->anim[0] != 0) {
            row->time[0] += 4;
            if (row->time[0] >= 256) {
                row->time[0] = 0;
                control[i + 3] = 1;
                row->anim[0] = 0;
                state->active = 0;
            }
        }
    }
    if (state->all != 0) {
        state->enabled = 1;
    } else if (*(s16 *)(control + 0xC2) >= 10000) {
        state->enabled = 0;
    } else if (animating == 0 && state->shown != 0 && SzEffect_IsUse2(-1, -1) == 0 && state->ready != 0 && state->hidden == 0) {
        if (control[0] == 0) {
            if (state->busy == 0) {
                switch (*(s16 *)(control + 0xC2)) {
                case 100:
                case 101:
                    state->enabled = 0;
                    break;
                default:
                    state->enabled = 1;
                    break;
                }
            } else {
                state->enabled = 0;
            }
        } else if (state->busy == 0) {
            switch (*(s16 *)(control + 0xC2)) {
            case 104:
            case 105:
            case 111:
                state->enabled = 0;
                break;
            default:
                state->enabled = 1;
                break;
            }
        } else {
            state->enabled = 0;
        }
    } else {
        if (*(s16 *)(control + 0xC2) != 0) {
            goto disabled;
        }
        if (state->shown == 0 || SzEffect_IsUse2(-1, -1) != 0 || state->ready == 0 || state->hidden != 0) {
            goto disabled;
        }
        state->enabled = 1;
        goto control_updated;
disabled:
        state->enabled = 0;
    }
control_updated:
    packet = SzModel_Draw_Pipe(packet, D_00298BB0 + 0x22, positions, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, D_00298BB2 + 0x22, positions, 0, 0, 0, 0);
    if (state->all != 0) {
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
    packet = Taku_Camp_3D_BOU(packet);
    switch (state->mode) {
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
        state->kind = 0;
    } else {
        state->kind = 1;
    }
    packet = Taku_Camp_3D_FUNE(packet, side, choice, kind);
    packet = SzModel_Draw_Pipe(packet, 0x29, 0, 0, 0, 0, 0);
    packet = SzModel_Draw_Pipe(packet, 0x28, 0, 0, 0, 0, 0);
    Taku_Camp_3D_LeaderModel(packet);
}

struct DotrLeaderModelRoute {
    float x[64];
    float z[64];
    short n;
    short pad;
};
struct DotrLeaderModelWork {
    short mx;                   
    short my;                   
    unsigned char pad4[0x190 - 4];
    float plane[4];             
    unsigned char pad1a0[472 - 0x1a0];
    short state;                
    short t;                    
    short pad476;
    short idx;                  
    unsigned char pad480[16];
    float pos[3];               
    unsigned char pad508[4];
    int angle;                  
    unsigned char pad516[0x22c - 516];
    struct DotrLeaderModelRoute route[2][16];   
    unsigned char pad17068[21363 - 17068];
    signed char show;           
    unsigned char pad21364[21628 - 21364];
    unsigned char alpha;        
};
#define DOTR_LEADER_WORK ((struct DotrLeaderModelWork *)0x1ed0000)
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
#define DOTR_LEADER_X(k) (*(DOTR_LEADER_WORK->route[a][b].x + idx + (k)))
#define DOTR_LEADER_Z(k) (*(DOTR_LEADER_WORK->route[a][b].z + idx + (k)))
#define DOTR_LEADER_N DOTR_LEADER_WORK->route[a][b].n
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
    if (rev == 0 && DOTR_LEADER_WORK->state != 0 && fwd && 0 < DOTR_LEADER_WORK->show && DOTR_LEADER_WORK->t <= 1024) {
        idx = DOTR_LEADER_WORK->idx;
        dx2 = DOTR_LEADER_X(2) - DOTR_LEADER_X(1);
        dz2 = DOTR_LEADER_Z(2) - DOTR_LEADER_Z(1);
        func_001A6C18(dx2, dz2);
        dx = DOTR_LEADER_X(1) - DOTR_LEADER_X(0);
        dz = DOTR_LEADER_Z(1) - DOTR_LEADER_Z(0);
        DOTR_LEADER_WORK->angle = DOTR_LEADER_ANGLE(dx, dz);
        if (DOTR_LEADER_WORK->state == 3) {
            DOTR_LEADER_WORK->pos[0] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].x;
            DOTR_LEADER_WORK->pos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_TO].y;
            DOTR_LEADER_WORK->pos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].z;
        } else {
            px = DOTR_LEADER_X(0);
            DOTR_LEADER_WORK->pos[0] = px + dx * (float)DOTR_LEADER_WORK->t / 1024.0f;
            DOTR_LEADER_WORK->pos[1] = DOTR_LEADER_SPOT[0].y + h;
            pz = DOTR_LEADER_Z(0);
            DOTR_LEADER_WORK->pos[2] = pz + dz * (float)DOTR_LEADER_WORK->t / 1024.0f;
        }
        if (DOTR_LEADER_N <= idx) {
            DOTR_LEADER_WORK->angle = DOTR_LEADER_ANGLE(DOTR_LEADER_X(0) - DOTR_LEADER_X(-1), DOTR_LEADER_Z(0) - DOTR_LEADER_Z(-1));
        } else if (DOTR_LEADER_N - 1 <= idx) {
        } else {
            short t = DOTR_LEADER_WORK->t;
            DOTR_LEADER_WORK->angle = DOTR_LEADER_ANGLE(dx * (float)(1024 - t) / 1024.0f + dx2 * (float)t / 1024.0f,
                             dz * (float)(1024 - t) / 1024.0f + dz2 * (float)t / 1024.0f);
        }
        if (DOTR_LEADER_WORK->t < 1024 && DOTR_LEADER_WORK->idx < DOTR_LEADER_N) {
            DOTR_LEADER_WORK->t += 256;
            if (DOTR_LEADER_WORK->t >= 1024) {
                DOTR_LEADER_WORK->idx++;
                if (DOTR_LEADER_N <= DOTR_LEADER_WORK->idx) {
                    DOTR_LEADER_WORK->t = 0;
                    DOTR_LEADER_WORK->state = 3;
                    DOTR_LEADER_WORK->idx = DOTR_LEADER_N;
                } else {
                    DOTR_LEADER_WORK->t = 0;
                }
            }
        }
        if (DOTR_LEADER_FROM == DOTR_LEADER_TO) {
            DOTR_LEADER_WORK->t = 0;
            DOTR_LEADER_WORK->state = 3;
            DOTR_LEADER_WORK->idx = DOTR_LEADER_N;
        }
    } else if (rev && DOTR_LEADER_WORK->state != 0 && fwd && 0 < DOTR_LEADER_WORK->show && DOTR_LEADER_WORK->t <= 1024) {
        if ((short)DOTR_LEADER_WORK->state == 1) {
            DOTR_LEADER_WORK->idx = DOTR_LEADER_N - 1;
            DOTR_LEADER_WORK->state = 2;
        }
        idx = DOTR_LEADER_WORK->idx;
        dx2 = DOTR_LEADER_X(1) - DOTR_LEADER_X(2);
        dz2 = DOTR_LEADER_Z(1) - DOTR_LEADER_Z(2);
        func_001A6C18(dx2, dz2);
        x0 = &DOTR_LEADER_X(0);
        z0 = &DOTR_LEADER_Z(0);
        dx = *x0 - DOTR_LEADER_X(1);
        dz = *z0 - DOTR_LEADER_Z(1);
        DOTR_LEADER_WORK->angle = DOTR_LEADER_ANGLE(dx, dz);
        if (DOTR_LEADER_WORK->state == 3) {
            DOTR_LEADER_WORK->pos[0] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].x;
            DOTR_LEADER_WORK->pos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_TO].y;
            DOTR_LEADER_WORK->pos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].z;
        } else {
            px = DOTR_LEADER_X(1);
            DOTR_LEADER_WORK->pos[0] = px + dx * (float)DOTR_LEADER_WORK->t / 1024.0f;
            DOTR_LEADER_WORK->pos[1] = DOTR_LEADER_SPOT[0].y + h;
            pz = DOTR_LEADER_Z(1);
            DOTR_LEADER_WORK->pos[2] = pz + dz * (float)DOTR_LEADER_WORK->t / 1024.0f;
        }
        if (DOTR_LEADER_N <= idx) {
            DOTR_LEADER_WORK->angle = DOTR_LEADER_ANGLE(*x0 - DOTR_LEADER_X(-1), *z0 - DOTR_LEADER_Z(-1));
        } else if (DOTR_LEADER_N - 1 <= idx) {
        } else {
            short t = DOTR_LEADER_WORK->t;
            DOTR_LEADER_WORK->angle = DOTR_LEADER_ANGLE(dx2 * (float)(1024 - t) / 1024.0f + dx * (float)t / 1024.0f,
                             dz2 * (float)(1024 - t) / 1024.0f + dz * (float)t / 1024.0f);
        }
        if (DOTR_LEADER_WORK->state < 3 && DOTR_LEADER_WORK->t < 1024 && 0 <= DOTR_LEADER_WORK->idx) {
            DOTR_LEADER_WORK->t += 256;
            if (DOTR_LEADER_WORK->t >= 1024) {
                DOTR_LEADER_WORK->idx--;
                if (DOTR_LEADER_WORK->idx < 0) {
                    DOTR_LEADER_WORK->t = 0;
                    DOTR_LEADER_WORK->state = 3;
                    DOTR_LEADER_WORK->idx = 0;
                } else {
                    DOTR_LEADER_WORK->t = 0;
                }
            }
        }
        if (DOTR_LEADER_FROM == DOTR_LEADER_TO) {
            DOTR_LEADER_WORK->t = 0;
            DOTR_LEADER_WORK->state = 3;
            DOTR_LEADER_WORK->idx = 0;
        }
    } else if (DOTR_LEADER_WORK->state != 0 && 0 < DOTR_LEADER_WORK->show && DOTR_LEADER_WORK->t <= 1024) {
        dz = DOTR_LEADER_SPOT[DOTR_LEADER_TO].x - DOTR_LEADER_SPOT[from].x;
        dx = DOTR_LEADER_SPOT[DOTR_LEADER_TO].z - DOTR_LEADER_SPOT[from].z;
        DOTR_LEADER_WORK->angle = DOTR_LEADER_ANGLE(dz, dx);
        if (DOTR_LEADER_WORK->state == 3) {
            DOTR_LEADER_WORK->pos[0] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].x;
            DOTR_LEADER_WORK->pos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_TO].y;
            DOTR_LEADER_WORK->pos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].z;
        } else {
            DOTR_LEADER_WORK->pos[0] = DOTR_LEADER_SPOT[DOTR_LEADER_FROM].x + dz * (float)DOTR_LEADER_WORK->t / 1024.0f;
            DOTR_LEADER_WORK->pos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_FROM].y;
            DOTR_LEADER_WORK->pos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_FROM].z + dx * (float)DOTR_LEADER_WORK->t / 1024.0f;
        }
        DOTR_LEADER_WORK->t += 16;
        if (DOTR_LEADER_WORK->t >= 1024) {
            DOTR_LEADER_WORK->t = 0;
            DOTR_LEADER_WORK->state = 3;
            DOTR_LEADER_WORK->idx = 0;
            DOTR_LEADER_WORK->pos[0] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].x;
            DOTR_LEADER_WORK->pos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_TO].y;
            DOTR_LEADER_WORK->pos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_TO].z;
        }
        if (DOTR_LEADER_FROM == DOTR_LEADER_TO) {
            DOTR_LEADER_WORK->t = 0;
            DOTR_LEADER_WORK->state = 3;
            DOTR_LEADER_WORK->idx = 0;
        }
    } else {
        DOTR_LEADER_WORK->pos[0] = DOTR_LEADER_SPOT[from].x;
        DOTR_LEADER_WORK->pos[1] = h + DOTR_LEADER_SPOT[DOTR_LEADER_FROM].y;
        DOTR_LEADER_WORK->pos[2] = DOTR_LEADER_SPOT[DOTR_LEADER_FROM].z;
        p.x = (float)(DOTR_LEADER_WORK->mx - 320);
        p.y = (float)(DOTR_LEADER_WORK->my - 224);
        p.z = 1.0f;
        p.w = 1.0f;
        q.x = (float)(DOTR_LEADER_WORK->mx - 320);
        q.y = (float)(DOTR_LEADER_WORK->my - 224);
        q.z = 100.0f;
        q.w = 1.0f;
        Ex3d_GetPointOnScreen(&p, p.x, p.y);
        q = *(struct DotrLeaderModelVec *)func_001F9AD0_b(0);
        Ex3d_IntersectP(DOTR_LEADER_WORK->plane, &p, &q, &out);
        DOTR_LEADER_WORK->angle += DOTR_LEADER_ANGLE(out.x - DOTR_LEADER_WORK->pos[0], out.z - DOTR_LEADER_WORK->pos[2]);
    }
    SzModel_SetDeform(30, 1);
    func_001F2AD0_b(30, 32);
    SzModel_SetScale(30, &scale);
    SzModel_SetPos(30, DOTR_LEADER_WORK->pos);
    rot.x = 0;
    rot.y = DOTR_LEADER_WORK->angle + 32767 + 1;
    rot.z = 0;
    SzModel_SetRotC(30, &rot);
    func_001F2800_b(30, DOTR_LEADER_WORK->alpha);
    DOTR_LEADER_WORK->angle = 0;
    SzModel_SetDrawFlag(30, 1);
    return cursor;
}
#undef DOTR_LEADER_WORK
#undef DOTR_LEADER_FROM
#undef DOTR_LEADER_TO
#undef DOTR_LEADER_X
#undef DOTR_LEADER_Z
#undef DOTR_LEADER_N
#undef DOTR_LEADER_ANGLE
#undef DOTR_LEADER_SPOT

/* Picks the player's leader model. */
s32 My_LedarModel_a_set(s32 leader) {
    switch (leader) {
    case 0:
        *(s16 *)0x01ED547C -= 4;
        if (*(s16 *)0x01ED547C <= 0) {
            *(s16 *)0x01ED547C = 0;
            return 1;
        }
        break;
    case 1:
        *(s16 *)0x01ED547C += 4;
        if (*(s16 *)0x01ED547C >= 0x80) {
            *(s16 *)0x01ED547C = 0x80;
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
    bankOutput = (u8 *)0x1ED0000;
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
struct DotrGlideRecord {
    float x[64];
    float y[64];
    short count;
    short unknown_202;
};
struct DotrGlideBank {
    unsigned char unknown_0000[0x22c];
    struct DotrGlideRecord records[2][16];
    short unknown_42ac[2][16];
    short unknown_42ec[2][16][64];
    short unknown_52ec[32];
    short unknown_532c[32];
    short limit;
    short unknown_536e;
    short saved_ticks;
    unsigned char unknown_5372[4];
    signed char idle;
};
struct DotrGlideList {
    unsigned char unknown_00[70];
    short cell;
    short unknown_48;
    short other_cell;
};
#define DOTR_GLIDE_BANK ((struct DotrGlideBank *)0x1ed0000)
extern struct DotrGlideSpot D_00298BA0_22c570[];
extern struct DotrGlideList D_00299020_22c570[2][16];
int func_001EE4B0_b(int cursor, int index, struct DotrGlideVector3 *position, void *d, int e, int f, int g);

/* Draws the place markers (bou: poles) on the campaign map. */
int Taku_Camp_3D_BOU(int cursor)
{
    struct DotrGlideVector3 pos;
    struct DotrGlideBank *bank = DOTR_GLIDE_BANK;
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

    bank->idle = 1;
    for (side = 0; side < 2; side++) {
        if (side == 0) {
            model = 28;
            n = 16;
        } else {
            model = 29;
            n = 12;
        }
        for (row = 0; row < n; row++) {
            count = bank->records[side][row].count;
            state = bank->records[side][row].unknown_202;
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
                        bank->idle = 0;
                        break;
                    case 2:
                        kind = 2;
                        bank->idle = 0;
                        bank->unknown_42ac[side][row] = count;
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
                        bank->idle = 0;
                    } else if (state == 2) {
                        kind = 2;
                        bank->idle = 0;
                    } else if (state == 3) {
                        kind = 3;
                    } else {
                        
                        kind = 0;
                    }
                    break;
                }
            }
            if (kind == 1) {
                for (i = 0; i <= bank->unknown_42ac[side][row]; i++) {
                    if (bank->unknown_42ec[side][row][i] < 256) {
                        pos.x = bank->records[side][row].x[i];
                        pos.y = D_00298BA0_22c570[0].unknown_04 - 10.0f + 10.0f * (float)bank->unknown_42ec[side][row][i] / 256.0f;
                        pos.z = bank->records[side][row].y[i];
                    } else {
                        pos.x = bank->records[side][row].x[i];
                        pos.y = D_00298BA0_22c570[0].unknown_04;
                        pos.z = bank->records[side][row].y[i];
                    }
                    cursor = func_001EE4B0_b(cursor, model + 34, &pos, 0, 0, 0, 0);
                    if (i == bank->unknown_42ac[side][row] && bank->unknown_42ec[side][row][i] >= 64) {
                        if (bank->unknown_42ac[side][row] < count) {
                            bank->unknown_42ac[side][row]++;
                        } else {
                            bank->unknown_42ac[side][row] = count;
                        }
                    }
                    if (bank->unknown_42ec[side][row][i] < 256) {
                        bank->unknown_42ec[side][row][i] += 16;
                        if (bank->unknown_42ec[side][row][i] >= 256) {
                            bank->unknown_42ec[side][row][i] = 256;
                        }
                    }
                    if (count == bank->unknown_42ac[side][row]) {
                        if (bank->unknown_42ec[side][row][count] >= 256) {
                            bank->unknown_52ec[D_00299020_22c570[side][row].cell] = 1;
                            bank->records[side][row].unknown_202 = 3;
                            bank->unknown_42ac[side][row] = 0;
                            for (j = 0; j < 64; j++) {
                                bank->unknown_42ec[side][row][j] = 0;
                            }
                        }
                    }
                }
            } else if (kind == 2) {
                for (i = count; i >= bank->unknown_42ac[side][row]; i--) {
                    if (bank->unknown_42ec[side][row][i] < 256) {
                        pos.x = bank->records[side][row].x[i];
                        pos.y = D_00298BA0_22c570[0].unknown_04 - 10.0f + 10.0f * (float)bank->unknown_42ec[side][row][i] / 256.0f;
                        pos.z = bank->records[side][row].y[i];
                    } else {
                        pos.x = bank->records[side][row].x[i];
                        pos.y = D_00298BA0_22c570[0].unknown_04;
                        pos.z = bank->records[side][row].y[i];
                    }
                    cursor = func_001EE4B0_b(cursor, model + 34, &pos, 0, 0, 0, 0);
                    if (i == bank->unknown_42ac[side][row] && bank->unknown_42ec[side][row][i] >= 64) {
                        if (0 < bank->unknown_42ac[side][row]) {
                            bank->unknown_42ac[side][row]--;
                        } else {
                            bank->unknown_42ac[side][row] = 0;
                        }
                    }
                    if (bank->unknown_42ec[side][row][i] < 256) {
                        bank->unknown_42ec[side][row][i] += 16;
                        if (bank->unknown_42ec[side][row][i] >= 256) {
                            bank->unknown_42ec[side][row][i] = 256;
                        }
                    }
                    if (bank->unknown_42ac[side][row] == 0) {
                        if (bank->unknown_42ec[side][row][0] >= 256) {
                            bank->unknown_52ec[D_00299020_22c570[side][row].other_cell] = 1;
                            bank->records[side][row].unknown_202 = 3;
                            bank->unknown_42ac[side][row] = 0;
                            for (k = 0; k < 64; k++) {
                                bank->unknown_42ec[side][row][k] = 0;
                            }
                        }
                    }
                }
            } else if (kind == 3) {
                for (i = 0; i <= count; i++) {
                    pos.x = bank->records[side][row].x[i];
                    pos.y = D_00298BA0_22c570[0].unknown_04;
                    pos.z = bank->records[side][row].y[i];
                    cursor = func_001EE4B0_b(cursor, model + 34, &pos, 0, 0, 0, 0);
                }
            }
        }
    }
    return cursor;
}
#undef DOTR_GLIDE_BANK

/* Draws the ship (fune) moving between two places. */
s32 Taku_Camp_3D_FUNE(s32 packet, s16 arg1, s16 arg2, s16 arg3) {
    extern s32 func_001A22C0(f32);
    extern s16 D_00299066[][16][38];
    f32 (*xData)[16][129] = (f32 (*)[16][129])0x01ED022C;
    f32 (*zData)[16][129] = (f32 (*)[16][129])0x01ED032C;
    s16 (*countData)[16][258] = (s16 (*)[16][258])0x01ED042C;
    s32 rotation[3];
    f32 dx1;
    f32 dz1;
    f32 dx0;
    f32 dz0;
    s16 point;
    f32 *x;
    f32 *z;
    s32 angle;

    point = *(s16 *)0x01ED01B0;
    dx1 = xData[arg1][arg2][point + 2] - xData[arg1][arg2][point + 1];
    dz1 = zData[arg1][arg2][point + 2] - zData[arg1][arg2][point + 1];
    func_001A6C18(dx1, dz1);
    dx0 = xData[arg1][arg2][point + 1] - xData[arg1][arg2][point];
    dz0 = zData[arg1][arg2][point + 1] - zData[arg1][arg2][point];
    x = &xData[arg1][arg2][point];
    z = &zData[arg1][arg2][point];
    angle = func_001A22C0(65536.0f * (func_001A6C18(dx0, dz0) / 6.2831855f)) % 65536;
    *(f32 *)0x01ED01B8 = *x + dx0 * (f32)*(s16 *)0x01ED01A6 / 1024.0f;
    *(f32 *)0x01ED01BC = D_00298BA4;
    *(f32 *)0x01ED01C0 = *z + dz0 * (f32)*(s16 *)0x01ED01A6 / 1024.0f;
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
        s16 progress = *(s16 *)0x01ED01A6;
        rotation[0] = 0;
        rotation[1] = func_001A22C0(65536.0f * (func_001A6C18(
            dx0 * (f32)(1024 - progress) / 1024.0f
                + dx1 * (f32)progress / 1024.0f,
            dz0 * (f32)(1024 - progress) / 1024.0f
                + dz1 * (f32)progress / 1024.0f) / 6.2831855f)) % 65536;
        rotation[2] = 0;
    }
    *(s32 *)0x01ED01A8 = rotation[1];
    if (*(s8 *)0x01ED01B4 != 0) {
        packet = SzModel_Draw_Pipe(packet, arg3 + 0x22, 0x01ED01B8, (s32)rotation, 0, 0, 0);
    }
    if (*(s16 *)0x01ED01A4 > 0) {
        if (*(s16 *)0x01ED01A6 < 1024 && *(s16 *)0x01ED01B0 < countData[arg1][arg2][0]) {
            if (*(s16 *)0x01ED01A4 == 1) {
                SzEffect_Entry(0, 0x193, 0, 0, 0);
                *(s16 *)0x01ED01A4 = 2;
            }
            if (*(s16 *)0x01ED01A4 == 2) {
                *(s16 *)0x01ED01A6 += 256;
                if (*(s16 *)0x01ED01A6 >= 1024) {
                    *(s16 *)0x01ED01B0 += 1;
                    if (countData[arg1][arg2][0] <= *(s16 *)0x01ED01B0) {
                        *(s16 *)0x01ED01A6 = 0;
                        *(s16 *)0x01ED01A4 = 3;
                        *(s16 *)0x01ED01B0 = countData[arg1][arg2][0];
                        ((s16 *)0x01ED52EC)[D_00299066[arg1][arg2][0]] = 1;
                    } else {
                        *(s16 *)0x01ED01A6 = 0;
                    }
                }
            }
        }
    }
    return packet;
}
