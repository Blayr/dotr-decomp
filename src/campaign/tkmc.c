/* Memory card: save, load, check, trade files (TkMc_*, TakuSave_*, TakuLoad_*, TakuTrade_*). */

#include "common.h"
#include "campaign.h"

typedef struct State_0023C170 {
    u8 pad00[0x8];
    s32 field08;
    s32 field0C;
    s32 field10;
    s32 field14;
    s32 field18;
    s32 field1C;
    s32 field20;
    s32 field24;
    u8 pad28[4];
    s16 field2C;
    s16 field2E;
    s16 field30;
    u8 pad32[2];
    s16 field34;
    s16 field36;
    s16 field38;
    s16 field3A;
    s16 field3C;
    s16 field3E;
    s16 field40;
    s16 field42;
    u8 pad44[4];
    s32 field48;
    s32 field4C;
    s16 field50;
    s16 field52;
    s16 field54;
    s16 field56;
    u8 pad58[4];
    s32 field5C;
    s32 field60;
    s32 field64;
    s32 field68;
    u8 pad6C[0x214];
    s16 field280;
    u8 pad282[2];
    s32 field284;
    s32 field288;
    s32 field28C;
    s32 field290;
    s16 field294;
    s16 field296;
    u8 pad298[0x10];
    s16 field2A8;
    s16 field2AA;
    s16 field2AC;
    s16 field2AE;
    s16 field2B0;
    s16 field2B2;
    s16 field2B4;
    s16 field2B6;
    s16 field2B8;
    u8 pad2BA[4];
    s16 field2BE;
    u8 pad2C0[0x580];
} State_0023C170;

typedef struct State_0023C3F0 {
    u8 pad0[0x30];
    s16 mode;
    u8 pad32[2];
    s16 field34;
    u8 pad36[0xA];
    s16 field40;
    u8 pad42[0x27C];
    s16 result;
} State_0023C3F0;

typedef struct State_0023E610 {
    s32 result;
    u8 pad04[0x1C];
    s32 command;
    s32 status;
    u8 pad28[8];
    s16 field30;
    u8 pad32[2];
    s16 field34;
    u8 pad36[0xA];
    s16 field40;
} State_0023E610;

extern struct State_0023E610 D_0034FB00;

/* Runs one frame of the memory-card check (`start` 1 starts it); returns its status, 0x100 when it is done. */
s32 TkMc_Check_Main(s32 start) {
    State_0023C3F0 *state = (State_0023C3F0 *)&D_0034FB00;
    s32 result;

    result = 0;
    if (start == 1) {
        TakuCard_init(0);
        state->result = 0;
    }
    switch (state->mode) {
    case 0:
    case 14:
    case 11:
        result = TakuSave_card_watch(1);
        break;
    case 1:
        result = TakuSave_card_filename_check(1);
        break;
    case 3:
        result = TakuSave_card_watch(1);
        break;
    }
    if (start == 1) {
        state->field34 = 0;
        state->field40 = 0;
        state->mode = 0;
    }
    switch (result) {
    case 2:
    case 3:
    case 14:
    case 6:
    case 8:
    case 10:
        result = 0x100;
        break;
    case 0:
        break;
    }
    if (result != 0) {
        state->result = result;
    }
    if (result == 0x100) {
        return 0x100;
    }
    return state->result;
}

/* Runs one frame of saving the game to the memory card (`start` 1 starts it, 2 = the player confirmed); returns
   its status (0x100 when done). */
s16 TkMc_Save_Main(s32 start) {
    State_0023C170 *state = (State_0023C170 *)&D_0034FB00;
    s32 result;

    result = 0;
    if (start == 1) {
        TakuCard_init(0);
        state->field2BE = 0;
    }
    switch (state->field30) {
    case 0:
        result = TakuSave_card_watch(0);
        if (result == 2) {
            state->field30 = 0;
        }
        break;
    case 1:
        result = TakuSave_card_filename_check(0);
        break;
    case 2:
        result = TakuSave_card_file_open();
        break;
    case 3:
        result = TakuSave_card_watch(0);
        break;
    case 4:
        result = TakuSave_make_file();
        break;
    case 5:
        result = TakuSave_card_file_write();
        break;
    case 10:
        result = TakuSave_card_format();
        break;
    case 15:
        result = TakuSave_card_unformat();
        break;
    case 11:
        result = TakuSave_card_watch(0);
        if (state->field2BE == 0xE && start == 2) {
            state->field30 = 0xA;
            state->field34 = 0;
            result = 0xB;
            state->field40 = 0;
        }
        break;
    case 13:
        result = TakuSave_card_watch(0);
        if (state->field2BE == 1 && start == 2) {
            state->field30 = 5;
            state->field34 = 0;
            result = 9;
            state->field40 = 0;
        }
        break;
    case 14:
        result = TakuSave_card_watch(0);
        if (result == 2) {
            result = 0xA;
        }
        if (start == 2) {
            state->field30 = 0;
            state->field34 = 0;
            result = 0x700;
            state->field40 = 0;
        }
        break;
    }
    if (start == 1) {
        state->field34 = 0;
        state->field40 = 0;
        state->field30 = 0;
    }
    if (result != 0) {
        state->field2BE = result;
    }
    if (result == 0x100) {
        return 0x100;
    }
    return state->field2BE;
}

typedef struct State_0023C770 {
    u8 pad_00[0x30];
    s16 state;
    u8 pad_32[2];
    s16 field_34;
    u8 pad_36[0xA];
    s16 field_40;
    u8 pad_42[0x27C];
    s16 result;
} State_0023C770;

/* Runs one frame of loading the game from the memory card (`start` 1 starts it); returns its status (0x100 when
   done). */
s32 TkMc_Load_Main(s32 start) {
    State_0023C770 *data = (State_0023C770 *)&D_0034FB00;
    s32 result;

    result = 0;
    if (start == 1) {
        TakuCard_init(0);
        data->result = 0;
    }
    switch (data->state) {
    case 0:
        result = TakuLoad_card_watch(start);
        if (result == 2) {
            data->state = 0;
        }
        break;
    case 1:
        result = TakuLoad_card_filename_check();
        break;
    case 2:
        result = TakuLoad_card_file_open();
        break;
    case 3:
        result = TakuLoad_card_watch(start);
        if (result == 2) {
            result = 0xA;
        }
        break;
    }
    if (start == 1) {
        data->field_34 = 0;
        data->field_40 = 0;
        result = 0x10;
        data->state = 0;
    }
    if (result == 3) {
        result = 7;
    }
    if (result != 0) {
        data->result = result;
    }
    if (result == 0x100) {
        return 0x100;
    }
    return data->result;
}

typedef struct State_0023C8B0 {
    u8 pad0[8];
    s32 field8;
    s32 fieldC;
    u8 pad10[0x20];
    s16 field30;
    u8 pad32[2];
    s16 field34;
    u8 pad36[0xA];
    s16 field40;
    u8 pad42[0x27C];
    s16 field2BE;
} State_0023C8B0;

/* Runs one frame of loading a trade partner's save from the memory card; returns its status (0x100 when done). */
s32 TkMc_Trade_Load_Main(s32 start) {
    State_0023C8B0 *state = (State_0023C8B0 *)&D_0034FB00;
    s32 result;

    result = 0;
    if (start == 1) {
        TakuCard_init(0);
        state->field2BE = 0;
    }
    switch (state->field30) {
    case 0:
        result = TakuLoad_card_watch(start);
        if (result == 2) {
            state->field30 = 0;
        }
        break;
    case 1:
        result = TakuLoad_card_filename_check();
        break;
    case 2:
        result = TakuCustom_card_file_open();
        break;
    case 3:
        result = TakuLoad_card_watch(start);
        if (result == 2) {
            result = 0xA;
        }
        break;
    }
    if (start == 1) {
        state->field34 = 0;
        state->field40 = 0;
        state->field30 = 0;
        result = 0x10;
        state->fieldC = 0;
    }
    if (result == 3) {
        result = 7;
    }
    if (result != 0) {
        state->field2BE = result;
    }
    if (result == 0x100) {
        return 0x100;
    }
    if (state->field8 == 1) {
        state->field2BE = state->field2BE | 0x80;
    }
    return state->field2BE;
}

typedef struct State_0023CA10 {
    u8 pad0[8];
    s32 field8;
    u8 padC[0x24];
    s16 field30;
    u8 pad32[2];
    s16 field34;
    u8 pad36[0xA];
    s16 field40;
    u8 pad42[0x16];
    s16 field58;
    u8 pad5A[0x264];
    s16 field2BE;
} State_0023CA10;

/* Runs one frame of saving after a trade; returns its status (0x100 when done). */
s16 TkMc_Trade_Save_Main(s32 start) {
    State_0023CA10 *state = (State_0023CA10 *)&D_0034FB00;
    s32 result;

    result = 0;
    if (start == 1) {
        if (TakuCard_init(1) != 0) {
            state->field58 = 1;
            return 0x600;
        }
        state->field2BE = 0;
    }
    if (state->field58 != 0) {
        return 0x600;
    }
    switch (state->field30) {
    case 0:
        result = TakuTrade_Save_card_watch(start);
        if (result == 2) {
            state->field30 = 0;
        }
        break;
    case 1:
        result = TakuSave_card_filename_check(0);
        break;
    case 2:
        result = TakuSave_card_file_open();
        break;
    case 3:
        result = TakuSave_card_watch(0);
        break;
    case 4:
        result = TakuSave_make_file();
        break;
    case 5:
        result = TakuTrade_Save_card_file_write_Ver2();
        break;
    case 10:
        result = TakuSave_card_format();
        break;
    case 11:
        result = TakuTrade_Save_card_watch(start);
        if (state->field2BE == 0xE && start == 2) {
            state->field30 = 0xA;
            state->field34 = 0;
            result = 0xB;
            state->field40 = 0;
        }
        break;
    case 13:
        result = TakuTrade_Save_card_watch(start);
        if (state->field2BE == 1 && start == 2) {
            state->field30 = 5;
            state->field34 = 0;
            result = 9;
            state->field40 = 0;
        }
        break;
    case 14:
        result = TakuTrade_Save_card_watch(start);
        if (result == 2) {
            result = 0xA;
        }
        if (start == 2) {
            state->field30 = 0;
            state->field34 = 0;
            result = 0x700;
            state->field40 = 0;
        }
        break;
    }
    if (start == 1) {
        state->field34 = 0;
        state->field40 = 0;
        state->field30 = 0;
    }
    if (result != 0) {
        state->field2BE = result;
    }
    if (result == 0x100) {
        return 0x100;
    }
    if (state->field8 == 1) {
        state->field2BE = state->field2BE | 0x80;
    }
    return state->field2BE;
}

/* Runs one frame of loading the custom-duel opponent's save; returns its status (0x100 when done). */
s16 TkMc_Custom_Main(s32 start) {
    extern struct State_0023E610 D_0034FB00;
    u8 *state = (u8 *)&D_0034FB00;
    s32 result;

    result = 0;
    if (start == 1) {
        TakuCard_init(0);
        *(s16 *)(state + 0x2BE) = 0;
    }

    switch (*(s16 *)(state + 0x30)) {
    case 0:
        result = TakuCustom_card_watch(start);
        if (result == 2) {
            *(s16 *)(state + 0x30) = 0;
        }
        break;
    case 1:
        result = TakuLoad_card_filename_check();
        break;
    case 2:
        result = TakuCustom_card_file_open();
        break;
    case 3:
        result = TakuCustom_card_watch(start);
        if (result == 2) {
            result = 0xA;
        }
        break;
    }

    if (start == 1) {
        *(s16 *)(state + 0x34) = 0;
        *(s16 *)(state + 0x40) = 0;
        *(s16 *)(state + 0x30) = 0;
        result = 0x10;
        *(s32 *)(state + 0xC) = 0;
    }

    if (result != 0) {
        if (*(s32 *)(state + 8) == 1) {
            switch (result) {
            case 2:
                result = 0x200;
                break;
            case 3:
            case 5:
            case 6:
            case 8:
            case 10:
            case 7:
                result = 0x300;
                break;
            }
        } else if (result == 3) {
            result = 7;
        }
        *(s16 *)(state + 0x2BE) = result;
    }

    if (result == 0x100) {
        return 0x100;
    }
    if (*(s32 *)(state + 8) == 1) {
        *(s16 *)(state + 0x2BE) |= 0x80;
    }
    return *(s16 *)(state + 0x2BE);
}

typedef struct State_0023CE40 {
    s32 result;
    s32 status;
    s32 arg0;
    s32 arg1;
    s32 mode;
    s32 size;
    s32 connected;
    u8 pad1C[4];
    s32 ready;
    s32 error;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 timer;
    u8 pad36[10];
    s16 retries;
} State_0023CE40;

/* Watches the memory card in slot 1 for the save job: is it there, formatted, with room (`checkOnly` for the boot
   check). (original: TakuSave_card_kansi) */
s32 TakuSave_card_watch(s32 checkOnly) {
    extern struct State_0023E610 D_0034FB00;
    extern s32 D_0034FB04;
    extern s32 D_0034FB08;
    extern s32 D_0034FB0C;
    extern s32 D_0034FB10;
    extern s32 D_0034FB14;
    extern s32 D_0034FB18;
    extern s32 D_0034FB20;
    extern s32 D_0034FB24;

    s32 result;
    State_0023CE40 *state = (State_0023CE40 *)&D_0034FB00;

    D_0034FB00.result = func_00194380(D_0034FB08, D_0034FB0C, &D_0034FB10, &D_0034FB14, &D_0034FB18);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1 && state->ready == 1) {
        switch (state->error) {
        case 0:
            break;
        case -1:
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 0x700;
        case -2:
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 0x700;
        default:
            if (checkOnly != 1) {
                state->state = 14;
                state->timer = 0;
                state->retries = 0;
            }
            break;
        }
        switch (state->mode) {
        case 0:
            if (checkOnly == 1 && state->state == 14) {
                state->state = 14;
                state->timer = 0;
                state->retries = 0;
                return 0;
            }
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 2;
        case 1:
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 4;
        case 2:
            break;
        case 3:
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 4;
        default:
            state->state = 14;
            state->timer = 0;
            state->retries = 0;
            return 2;
        }
        if (state->mode == 2) {
                switch (state->connected) {
                case 0:
                    state->retries++;
                    if (state->retries >= 3) {
                        state->state = 11;
                        state->timer = 0;
                        state->retries = 3;
                        if (state->state == 11) {
                            result = 14;
                        } else {
                            result = 3;
                        }
                        return result;
                    }
                    break;
                case 1:
                    state->retries = 0;
                    if (state->state == 0) {
                        state->state = 1;
                    } else if (state->state == 3) {
                        if (state->size < 250) {
                            state->state = 14;
                            state->timer = 0;
                            state->retries = 0;
                            return 5;
                        }
                        if (checkOnly == 1) {
                            state->timer = 0;
                            state->retries = 0;
                            state->state = 0;
                            return 0x100;
                        }
                        state->state = 4;
                        return 9;
                    }
                    break;
                default:
                    state->state = 14;
                    state->timer = 0;
                    state->retries = 0;
                    return 2;
                }
        }
    }
    switch (state->state) {
    case 3:
        return 17;
    case 11:
        return 14;
    case 13:
        return 1;
    default:
        return 0;
    }
}

struct State_0023E610;

typedef struct State_0023D170 {
    s32 result;
    s32 sync;
    s32 port;
    s32 slot;
    u8 pad10[0x10];
    s32 command;
    s32 status;
    u8 pad28[8];
    s16 error;
    s16 pad32;
    s16 state;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[0x1E];
    s32 mode;
    u8 pad64[0x1C];
    u8 entries[0x240];
    u8 info[1];
} State_0023D170;

extern u8 D_0029B100[];
extern u8 D_0029B1BE[];
extern s16 D_0034FB34;

/* Looks for the game's save file on the memory card. */
s32 TakuSave_card_filename_check(s32 checkOnly) {
    extern struct State_0023E610 D_0034FB00;
    State_0023D170 *s = (State_0023D170 *)&D_0034FB00;

    switch (D_0034FB34) {
    case 0:
        s->result = func_00194758(s->port, s->slot, D_0029B100, s->info);
        s->sync = func_00194248(1, &s->command, &s->status);
        if (s->sync == 1 && s->command == 0xC) {
                switch (s->status) {
                case 0:
                    s->state = 1;
                    s->retries = 0;
                    return 0;
                case -2:
                    s->retries++;
                    if (s->retries >= 3) {
                        s->state = 0;
                        s->retries = 3;
                        s->error = 0xB;
                        return 3;
                    }
                    return 0;
                case -4:
                    s->error = 3;
                    s->state = 0;
                    s->retries = 0;
                    return 0x11;
                default:
                    s->state = 0;
                    s->error = 0xE;
                    s->retries = 0;
                    return 2;
                }
        } else {
            return 0;
        }
        break;
    case 1:
        s->result = func_00194578(s->port, s->slot, D_0029B1BE, s->mode, 1, s->entries);
        s->sync = func_00194248(1, &s->command, &s->status);
        if (s->sync == 1 && s->command == 0xD) {
                if (s->status < 0) {
                    switch (s->status) {
                    case -2:
                        s->retries++;
                        if (s->retries >= 3) {
                            s->state = 0;
                            s->retries = 3;
                            s->error = 0xB;
                            return 3;
                        }
                        return 0;
                    case -4:
                        s->error = 0xE;
                        s->state = 0;
                        s->retries = 0;
                        return 0xA;
                    default:
                        s->state = 0;
                        s->error = 0xE;
                        s->retries = 0;
                        return 2;
                    }
                } else {
                    if (checkOnly == 1) {
                        s->state = 0;
                        s->retries = 0;
                        s->error = 0;
                        return 0x100;
                    }
                    s->retries = 0;
                    s->state = 0;
                    s->error = 2;
                    return 0x10;
                }
        } else {
            return 0;
        }
        break;
    default:
        return 0;
    }
}

typedef struct State_0023D400 {
    s32 request;
    s32 ready;
    s32 slot;
    s32 mode;
    u8 pad10[0x10];
    s32 command;
    s32 result;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 phase;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[6];
    s32 handles[2];
    u8 pad50[0x266];
    s16 field2B6;
    s16 field2B8;
} State_0023D400;

/* Opens (or creates) the save file on the memory card. */
s32 TakuSave_card_file_open(void) {
    State_0023D400 *p = (State_0023D400 *)&D_0034FB00;

    switch (D_0034FB34) {
    case 0:
        p->request = func_00193BA8(p->slot, p->mode, D_0029B1BE, 1);
        p->ready = func_00194248(1, &p->command, &p->result);
        if ((p->ready == 1) && (p->command == 2)) {
                if (p->result < 0) {
                    switch (p->result) {
                    case -2:
                        p->retries++;
                        if (p->retries >= 3) {
                            p->phase = 0;
                            p->retries = 3;
                            p->state = 11;
                            return 3;
                        }
                        return 0;
                    case -3:
                        p->state = 14;
                        p->phase = 0;
                        p->retries = 0;
                        return 5;
                    case -4:
                        p->state = 14;
                        p->phase = 0;
                        p->retries = 0;
                        return 10;
                    case -5:
                        p->state = 14;
                        p->phase = 0;
                        p->retries = 0;
                        return 10;
                    case -7:
                        p->state = 14;
                        p->phase = 0;
                        p->retries = 0;
                        return 10;
                    default:
                        p->phase = 0;
                        p->state = 14;
                        p->retries = 0;
                        return 2;
                    }
                } else {
                    p->handles[p->slot] = p->result;
                    p->retries = 0;
                    p->phase = 1;
                    return 0;
                }
        } else {
            return 0;
        }
        break;
    case 1:
        p->request = func_00193DD0(p->handles[p->slot], p->field2B6, p->field2B8, 1);
        p->ready = func_00194248(1, &p->command, &p->result);
        if ((p->ready == 1) && (p->command == 4)) {
                switch (p->result) {
                case 0:
                    p->retries = 0;
                    p->phase = 2;
                    return 0;
                case -2:
                    p->retries++;
                    if (p->retries >= 3) {
                        p->phase = 0;
                        p->retries = 3;
                        p->state = 11;
                        return 3;
                    }
                    break;
                case -4:
                    p->state = 14;
                    p->phase = 0;
                    p->retries = 0;
                    return 10;
                default:
                    p->phase = 0;
                    p->state = 14;
                    p->retries = 0;
                    return 2;
                }
        } else {
            return 0;
        }
        break;
    case 2:
        FlushCache(0);
        p->request = func_00193F38(p->handles[p->slot], (u8 *)0x1E10000 + p->slot * 0x100F0, 0x100F0);
        p->ready = func_00194248(1, &p->command, &p->result);
        if ((p->ready == 1) && (p->command == 5)) {
                if (p->result < 0) {
                    switch (p->result) {
                    case -2:
                        p->retries++;
                        if (p->retries >= 3) {
                            p->phase = 0;
                            p->retries = 3;
                            p->state = 11;
                            return 3;
                        }
                        return 0;
                    case -4:
                        p->state = 14;
                        p->phase = 0;
                        p->retries = 0;
                        return 10;
                    default:
                        p->phase = 0;
                        p->state = 14;
                        p->retries = 0;
                        return 2;
                    }
                } else {
                    p->retries = 0;
                    p->phase = 3;
                    return 0;
                }
        } else {
            return 0;
        }
        break;
    case 3:
        p->request = sceMcClose(p->handles[p->slot]);
        p->ready = func_00194248(1, &p->command, &p->result);
        if ((p->ready == 1) && (p->command == 3)) {
            switch (p->result) {
            case 0:
                p->phase = 0;
                p->retries = 0;
                p->state = 13;
                return 1;
            case -2:
                p->retries++;
                if (p->retries >= 3) {
                    p->state = 11;
                    p->phase = 0;
                    p->retries = 3;
                    return 3;
                }
                break;
            case -4:
                p->state = 14;
                p->phase = 0;
                p->retries = 0;
                return 10;
            default:
                p->state = 14;
                p->phase = 0;
                p->retries = 0;
                return 2;
            }
        } else {
            return 0;
        }
        break;
    }
    return 0;
}

typedef struct State_0023D920 {
    s32 result;
    s32 status;
    s32 port;
    s32 slot;
    u8 pad10[0x10];
    s32 command;
    s32 code;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 phase;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[6];
    s32 handles[158];
    u8 buffer[1];
} State_0023D920;

/* Builds the save file in memory: the header, the icon, both profiles. */
s32 TakuSave_make_file(void) {
    extern struct State_0023E610 D_0034FB00;
    State_0023D920 *state = (State_0023D920 *)&D_0034FB00;
    s32 result;

    switch (D_0034FB34) {
    case 0:
        state->result = sceMcMkdir(state->port, state->slot, D_0029B100);
        state->status = func_00194248(1, &state->command, &state->code);
        if (state->status == 1) {
            if (state->command == 0xB) {
                if (state->code != 0) {
                    switch (state->code) {
                    case -2:
                        state->retries++;
                        if (state->retries >= 3) {
                            state->state = 0xB;
                            state->phase = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 5;
                    case -4:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 0xA;
                    default:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->phase = 1;
                    state->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    case 1:
        state->result = func_00194758(state->port, state->slot, D_0029B100, state->buffer);
        state->status = func_00194248(1, &state->command, &state->code);
        if (state->status == 1) {
            if (state->command == 0xC) {
                switch (state->code) {
                case 0:
                    state->phase = 2;
                    state->retries = 0;
                    return 0;
                case -2:
                    state->retries++;
                    if (state->retries >= 3) {
                        state->state = 0xB;
                        state->phase = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 0xE;
                    state->phase = 0;
                    state->retries = 0;
                    return 0xA;
                default:
                    state->state = 0xE;
                    state->phase = 0;
                    state->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 2:
        result = card_icon_make();
        if (result == 1) {
            state->retries = 0;
            state->phase = 3;
        } else if (result == 0xA) {
            return 0xA;
        }
        break;
    case 3:
        state->result = func_00193BA8(state->port, state->slot, D_0029B1BE, 0x200);
        state->status = func_00194248(1, &state->command, &state->code);
        if (state->status == 1) {
            if (state->command == 2) {
                if (state->code < 0) {
                    switch (state->code) {
                    case -2:
                        state->retries++;
                        if (state->retries >= 3) {
                            state->state = 0xB;
                            state->phase = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 5;
                    case -4:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 0xA;
                    case -5:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 0xA;
                    case -7:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 0xA;
                    default:
                        state->state = 0xE;
                        state->phase = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->handles[state->port] = state->code;
                    state->phase = 4;
                    state->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    case 4:
        state->result = sceMcClose(state->handles[state->port]);
        state->status = func_00194248(1, &state->command, &state->code);
        if (state->status == 1) {
            if (state->command == 3) {
                switch (state->code) {
                case 0:
                    state->state = 5;
                    state->retries = 0;
                    state->phase = 0;
                    return 9;
                case -2:
                    state->retries++;
                    if (state->retries >= 3) {
                        state->state = 0xB;
                        state->phase = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 0xE;
                    state->phase = 0;
                    state->retries = 0;
                    return 0xA;
                default:
                    state->state = 0xE;
                    state->phase = 0;
                    state->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    default:
        break;
    }
    return 0;
}

typedef struct Data_0023DE90 {
    s32 ret;
    s32 status;
    s32 port;
    s32 slot;
    u8 pad10[0x10];
    s32 command;
    s32 result;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 stage;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[6];
    s32 handles[2];
    u8 pad50[0x266];
    s16 format0;
    s16 format1;
} Data_0023DE90;

typedef struct Pair_0023DE90 {
    s32 first;
    s32 second;
} Pair_0023DE90;

typedef struct Header_0023DE90 {
    s16 first;
    s16 second;
} Header_0023DE90;

typedef struct Buffer_0023DE90 {
    Header_0023DE90 header;
    Pair_0023DE90 pairs[0x1FF4];
    s32 table[0x53];
} Buffer_0023DE90;

typedef struct Tail_0023DE90 {
    s32 words[0x53];
} Tail_0023DE90;

/* Writes the save file to the memory card. (original: TakuSave_card_file_kakikomi) */
s32 TakuSave_card_file_write(void) {
    extern struct State_0023E610 D_0034FB00;
    extern s32 *memCardTrunkData;
    extern Header_0023DE90 saveFileHeader;
    Data_0023DE90 *data = (Data_0023DE90 *)&D_0034FB00;
    Header_0023DE90 *header;
    s32 *saveData;

    saveData = (s32 *)&campaignState;
    switch (D_0034FB34) {
    case 0:
        data->ret = func_00193BA8(data->port, data->slot, D_0029B1BE, 2);
        data->status = func_00194248(1, &data->command, &data->result);
        if (data->status == 1) {
            if (data->command == 2) {
                if (data->result < 0) {
                    switch (data->result) {
                    case -2:
                        data->retries = (s16) (data->retries + 1);
                        if (data->retries >= 3) {
                            data->state = 0xB;
                            data->stage = 0;
                            data->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 5;
                    case -4:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 0xA;
                    case -5:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 0xA;
                    case -7:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 0xA;
                    default:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 2;
                    }
                } else {
                    data->handles[data->port] = (s32) data->result;
                    data->stage = 1;
                    data->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    case 1:
        data->ret = func_00193DD0(data->handles[data->port], data->format0, data->format1, 2);
        data->status = func_00194248(1, &data->command, &data->result);
        if (data->status == 1) {
            if (data->command == 4) {
                switch (data->result) {
                case 0:
                    data->stage = 2;
                    data->retries = 0;
                    return 0;
                case -2:
                    data->retries = (s16) (data->retries + 1);
                    if (data->retries >= 3) {
                        data->state = 0xB;
                        data->stage = 0;
                        data->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    data->state = 0xE;
                    data->stage = 0;
                    data->retries = 0;
                    return 0xA;
                default:
                    data->state = 0xE;
                    data->stage = 0;
                    data->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 2: {
        s32 second;
        s32 first;
        s32 count;
        s32 *dst;
        s32 *src;

        src = memCardTrunkData;
        count = 0x1FF4;
        dst = (s32 *)((Buffer_0023DE90 *)0x01E10000)[data->port].pairs;
        do {
            first = *src++;
            second = *src++;
            count--;
            dst[0] = first;
            dst[1] = second;
            dst += 2;
        } while (count > 0);
        header = &((Buffer_0023DE90 *)0x01E10000)[data->port].header;
        *header = saveFileHeader;
        *(Tail_0023DE90 *)((Buffer_0023DE90 *)0x01E10000)[data->port].table = *(Tail_0023DE90 *)saveData;
        LkCheckData((u16 *)&((Buffer_0023DE90 *)0x01E10000)[data->port]);
        FlushCache(0);
        data->ret = func_00194058(data->handles[data->port], &((Buffer_0023DE90 *)0x01E10000)[data->port], 0x100F0);
        data->status = func_00194248(1, &data->command, &data->result);
        if (data->status == 1) {
            if (data->command == 6) {
                if (data->result < 0) {
                    switch (data->result) {
                    case -2:
                        data->retries = (s16) (data->retries + 1);
                        if (data->retries >= 3) {
                            data->state = 0xB;
                            data->stage = 0;
                            data->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 5;
                    case -4:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 0xA;
                    case -5:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 0xA;
                    default:
                        data->state = 0xE;
                        data->stage = 0;
                        data->retries = 0;
                        return 2;
                    }
                } else {
                    data->stage = 4;
                    data->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    }
    case 3:
        data->ret = sceMcFlush(data->handles[data->port]);
        data->status = func_00194248(1, &data->command, &data->result);
        if (data->status == 1) {
            if (data->command == 0xA) {
                switch (data->result) {
                case 0:
                    data->stage = 4;
                    data->retries = 0;
                    return 0;
                case -2:
                    data->retries = (s16) (data->retries + 1);
                    if (data->retries >= 3) {
                        data->state = 0xB;
                        data->stage = 0;
                        data->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    data->state = 0xE;
                    data->stage = 0;
                    data->retries = 0;
                    return 0xA;
                default:
                    data->state = 0xE;
                    data->stage = 0;
                    data->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 4:
        data->ret = sceMcClose(data->handles[data->port]);
        data->status = func_00194248(1, &data->command, &data->result);
        if (data->status == 1) {
            if (data->command == 3) {
                switch (data->result) {
                case 0:
                    data->stage = 0;
                    data->retries = 0;
                    data->state = 0;
                    return 0x100;
                case -2:
                    data->retries = (s16) (data->retries + 1);
                    if (data->retries >= 3) {
                        data->state = 0xB;
                        data->stage = 0;
                        data->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    data->state = 0xE;
                    data->retries = 0;
                    data->stage = 0;
                    return 0xA;
                default:
                    data->state = 0xE;
                    data->retries = 0;
                    data->stage = 0;
                    return 2;
                }
            }
        }
        return 0;
    }
    return 0;
}

extern State_0023E610 D_0034FB00;
extern s32 D_0034FB04;
extern s32 D_0034FB08;
extern s32 D_0034FB0C;
extern s32 D_0034FB20;
extern s32 D_0034FB24;

/* Formats the memory card. */
s32 TakuSave_card_format(void) {
    State_0023E610 *state = &D_0034FB00;

    D_0034FB00.result = func_001948A8(D_0034FB08, D_0034FB0C);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1) {
        if (state->command == 0x10) {
            if (state->status == 0) {
                state->field30 = 0xE;
                state->field40 = 0;
                state->field34 = 0;
                return 0xC;
            }
            return 0xD;
        }
    }
    return 0;
}

/* Unformats the memory card (debug). */
s32 TakuSave_card_unformat(void) {
    State_0023E610 *state = &D_0034FB00;

    D_0034FB00.result = func_00194E90(D_0034FB08, D_0034FB0C);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1) {
        if (state->command == 0x11) {
            if (state->status == 0) {
                state->field30 = 0xE;
                state->field40 = 0;
                state->field34 = 0;
                return 0xC;
            }
            state->field30 = 0xE;
            state->field40 = 0;
            state->field34 = 0;
            return 0xD;
        }
    }
    return 0;
}

typedef struct State_0023E7A0 {
    s32 ret;
    s32 sync;
    s32 port;
    s32 slot;
    u8 pad10[0x10];
    s32 command;
    s32 result;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 phase;
    s16 sub;
    u8 pad38[8];
    s16 retries;
    s16 index;
    u8 pad44[4];
    s32 handles[2];
} State_0023E7A0;

/* Builds the memory card icon files (icon.sys and the 3D icon). (original: card_icon_tukuru) */
s32 card_icon_make(void) {
    extern struct State_0023E610 D_0034FB00;
    extern s16 D_0034FB36;
    extern u8 D_0034F720[];
    extern char D_0034F7E0[];
    extern u16 D_0034F726;
    extern u32 D_0034F72C;
    extern u8 D_0034F730[];
    extern u8 D_0034F770[];
    extern u8 D_0034F7A0[];
    extern u8 D_0034F7D0[];
    extern char D_0034F824[];
    extern char D_0034F864[];
    extern char D_0034F8A4[];
    extern char *D_0029B06C;
    extern char *D_0029B070;
    extern u8 D_0029B100[];
    extern char D_0030F321[];
    extern char D_0030F32B[];
    extern char D_0030F330[];
    extern u8 D_0029B200[];
    extern u8 lightdir[];
    extern u8 lightcol[];
    extern u8 D_0029B2A0[];
    extern char *iconName[];
    extern u32 anOfs_ICON[];
    extern u32 D_0029B054[];
    State_0023E7A0 *s;
    char path[0x40];
    char *end;

    s = (State_0023E7A0 *)&D_0034FB00;
    func_0019BDD8(path, D_0029B100);
    end = path + func_0019BEF0(path);
    func_0019BDD8(end, D_0030F321);
    switch (D_0034FB36) {
    case 0:
        s->ret = func_00193BA8(s->port, s->slot, path, 0x203);
        s->sync = func_00194248(0, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 2) {
                if (0 <= s->result) {
                    s->handles[s->port] = s->result;
                    s->retries = 0;
                    s->sub = 1;
                } else {
                    switch (s->result) {
                    case -2:
                        s->retries++;
                        if (s->retries >= 3) {
                            s->phase = 0;
                            s->sub = 0;
                            s->retries = 3;
                            s->state = 0xB;
                        }
                        break;
                    case -3:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -4:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -5:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -7:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    default:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    }
                }
            }
        }
        break;
    case 1:
        func_00198948(D_0034F720, 0, 0x3C4);
        func_0019BDD8((char *)D_0034F720, D_0030F32B);
        func_0019BDD8(D_0034F7E0, D_0030F330);
        D_0034F726 = 0x1E;
        D_0034F72C = 0x60;
        func_00198790(D_0034F730, D_0029B200, 0x40);
        func_00198790(D_0034F770, lightdir, 0x30);
        func_00198790(D_0034F7A0, lightcol, 0x30);
        func_00198790(D_0034F7D0, D_0029B2A0, 0x10);
        func_0019BDD8(D_0034F824, iconName[0]);
        func_0019BDD8(D_0034F864, D_0029B06C);
        func_0019BDD8(D_0034F8A4, D_0029B070);
        s->ret = func_00194058(s->handles[s->port], D_0034F720, 0x3C4);
        s->sync = func_00194248(0, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 6) {
                if (0 <= s->result) {
                    s->retries = 0;
                    s->sub = 2;
                } else {
                    switch (s->result) {
                    case -2:
                        s->retries++;
                        if (s->retries >= 3) {
                            s->phase = 0;
                            s->sub = 0;
                            s->retries = 3;
                            s->state = 0xB;
                        }
                        break;
                    case -3:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -4:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -5:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    default:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    }
                }
            }
        }
        break;
    case 2:
        s->ret = func_00193D18(s->handles[s->port]);
        s->sync = func_00194248(0, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 3) {
                switch (s->result) {
                case 0:
                    s->sub = 3;
                    s->retries = 0;
                    break;
                case -2:
                    s->retries++;
                    if (s->retries >= 3) {
                        s->phase = 0;
                        s->sub = 0;
                        s->retries = 3;
                        s->state = 0xB;
                    }
                    break;
                case -4:
                    s->phase = 0;
                    s->sub = 0;
                    s->state = 0xE;
                    s->retries = 0;
                    return 0xA;
                default:
                    s->phase = 0;
                    s->sub = 0;
                    s->state = 0xE;
                    s->retries = 0;
                    return 0xA;
                }
            }
        }
        break;
    case 3:
        *end = '/';
        func_0019BDD8(end + 1, iconName[s->index]);
        s->ret = func_00193BA8(s->port, s->slot, path, 0x203);
        s->sync = func_00194248(1, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 2) {
                if (0 <= s->result) {
                    s->handles[s->port] = s->result;
                    s->retries = 0;
                    s->sub = 4;
                } else {
                    switch (s->result) {
                    case -2:
                        s->retries++;
                        if (s->retries >= 3) {
                            s->phase = 0;
                            s->sub = 0;
                            s->retries = 3;
                            s->state = 0xB;
                        }
                        break;
                    case -3:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -4:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -5:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -7:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    default:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    }
                }
            }
        }
        break;
    case 4:
        {
            s32 size = D_0029B054[s->index] - anOfs_ICON[s->index];
            s->ret = func_00194058(s->handles[s->port], (u8 *)GAME_DATA_COPY_ADDR + anOfs_ICON[s->index], size);
        }
        s->sync = func_00194248(1, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 6) {
                if (0 <= s->result) {
                    s->retries = 0;
                    s->sub = 5;
                } else {
                    switch (s->result) {
                    case -2:
                        s->retries++;
                        if (s->retries >= 3) {
                            s->phase = 0;
                            s->sub = 0;
                            s->retries = 3;
                            s->state = 0xB;
                        }
                        break;
                    case -3:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -4:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    case -5:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    default:
                        s->phase = 0;
                        s->sub = 0;
                        s->state = 0xE;
                        s->retries = 0;
                        return 0xA;
                    }
                }
            }
        }
        break;
    case 5:
        s->ret = func_00193D18(s->handles[s->port]);
        s->sync = func_00194248(1, &s->command, &s->result);
        if (s->sync == 1) {
            if (s->command == 3) {
                switch (s->result) {
                case 0:
                    s->index++;
                    if (s->index >= 3) {
                        s->sub = 0;
                        s->retries = 0;
                        return 1;
                    }
                    s->sub = 3;
                    s->retries = 0;
                    break;
                case -2:
                    s->retries++;
                    if (s->retries >= 3) {
                        s->state = 0xB;
                        s->phase = 0;
                        s->sub = 0;
                        s->retries = 3;
                    }
                    break;
                case -4:
                    s->phase = 0;
                    s->sub = 0;
                    s->state = 0xE;
                    s->retries = 0;
                    return 0xA;
                default:
                    s->phase = 0;
                    s->sub = 0;
                    s->state = 0xE;
                    s->retries = 0;
                    return 0xA;
                }
            }
        }
        break;
    }
    return 0;
}

/* Watches the memory card in slot 1 for the load job. (original: TakuLoad_card_kansi) */
s32 TakuLoad_card_watch(s32 mode) {
    extern s32 D_0034FB10;
    extern s32 D_0034FB14;
    extern s32 D_0034FB18;
    u8 *state = (u8 *)&D_0034FB00;
    s32 result;

    D_0034FB00.result = func_00194380(D_0034FB08, D_0034FB0C,
                               &D_0034FB10, &D_0034FB14, &D_0034FB18);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1) {
        if (*(s32 *)(state + 0x20) == 1) {
            switch (*(s32 *)(state + 0x24)) {
            case 0:
                goto mode_switch;
            case -1:
                *(s16 *)(state + 0x30) = 3;
                *(s16 *)(state + 0x34) = 0;
                *(s16 *)(state + 0x40) = 0;
                result = 0x700;
                goto done;
            case -2:
                *(s16 *)(state + 0x30) = 3;
                *(s16 *)(state + 0x34) = 0;
                *(s16 *)(state + 0x40) = 0;
                result = 0x700;
                goto done;
            default:
                *(s16 *)(state + 0x30) = 3;
                *(s16 *)(state + 0x34) = 0;
                *(s16 *)(state + 0x40) = 0;
                /* fall through */
            }
mode_switch:
            switch (*(s32 *)(state + 0x10)) {
                case 0:
                    *(s16 *)(state + 0x30) = 3;
                    *(s16 *)(state + 0x34) = 0;
                    *(s16 *)(state + 0x40) = 0;
                    result = 2;
                    goto done;
                case 1:
                    *(s16 *)(state + 0x30) = 3;
                    *(s16 *)(state + 0x34) = 0;
                    *(s16 *)(state + 0x40) = 0;
                    result = 4;
                    goto done;
                case 2:
                    goto state2;
                case 3:
                    *(s16 *)(state + 0x30) = 3;
                    *(s16 *)(state + 0x34) = 0;
                    *(s16 *)(state + 0x40) = 0;
                    result = 4;
                    goto done;
                default:
                    *(s16 *)(state + 0x30) = 3;
                    *(s16 *)(state + 0x34) = 0;
                    *(s16 *)(state + 0x40) = 0;
                    result = 2;
                    goto done;
                }
state2:
                if (*(s32 *)(state + 0x10) == 2) {
                    switch (*(s32 *)(state + 0x18)) {
                    case 0:
                        *(s16 *)(state + 0x40) = *(s16 *)(state + 0x40) + 1;
                        if (*(s16 *)(state + 0x40) >= 3) {
                            *(s16 *)(state + 0x30) = 3;
                            *(s16 *)(state + 0x34) = 0;
                            *(s16 *)(state + 0x40) = 3;
                            result = 3;
                            goto done;
                        }
                        break;
                    case 1:
                        if (*(s16 *)(state + 0x30) == 0) {
                            *(s16 *)(state + 0x30) = 1;
                            *(s16 *)(state + 0x34) = 0;
                            *(s16 *)(state + 0x40) = 0;
                            result = 0x10;
                            goto done;
                        }
                        break;
                    default:
                        *(s16 *)(state + 0x30) = 3;
                        *(s16 *)(state + 0x34) = 0;
                        *(s16 *)(state + 0x40) = 0;
                        result = 2;
                        goto done;
                }
            }
        }
    }
    result = 0;
done:
    return result;
}

typedef struct {
    s32 result;
    s32 status;
    s32 input0;
    s32 input1;
    u8 pad_10[0x10];
    s32 event;
    s32 value;
    u8 pad_28[8];
    s16 action;
    u8 pad_32[2];
    s16 mode;
    u8 pad_36[0xA];
    s16 attempts;
    u8 pad_42[0x1E];
    s32 input2;
    u8 pad_64[0x1C];
    u8 pad_80[0x240];
} State_0023F340;

/* Looks for the game's save file to load. */
s32 TakuLoad_card_filename_check(void) {
    extern struct State_0023E610 D_0034FB00;
    State_0023F340 *state = (State_0023F340 *)&D_0034FB00;

    switch (D_0034FB34) {
    case 0:
    state->result = func_00194758(state->input0, state->input1,
                                 D_0029B100, (u8 *)state + 0x2C0);
    state->status = func_00194248(1, &state->event, &state->value);
    if (state->status == 1 && state->event == 0xC) {
        switch (state->value) {
        case 0:
            state->mode = 1;
            state->attempts = 0;
            return 0;
        case -2:
            state->attempts++;
            if (state->attempts >= 3) {
                state->action = 3;
                state->mode = 0;
                state->attempts = 3;
                return 3;
            }
            return 0;
        case -4:
            state->action = 3;
            state->mode = 0;
            state->attempts = 0;
            return 7;
        default:
            state->action = 3;
            state->mode = 0;
            state->attempts = 0;
            return 2;
        }
    } else {
        return 0;
    }
    break;

    case 1:
    state->result = func_00194578(state->input0, state->input1,
                                 D_0029B1BE, state->input2, 1,
                                 (u8 *)state + 0x80);
    state->status = func_00194248(1, &state->event, &state->value);
    if (state->status == 1 && state->event == 0xD) {
            if (state->value < 0) {
                switch (state->value) {
                case -2:
                    state->attempts++;
                    if (state->attempts >= 3) {
                        state->action = 3;
                        state->mode = 0;
                        state->attempts = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->action = 3;
                    state->mode = 0;
                    state->attempts = 0;
                    return 10;
                default:
                    state->action = 3;
                    state->attempts = 0;
                    state->mode = 0;
                    return 2;
                }
            }
            state->action = 2;
            state->mode = 0;
            return 9;
    } else {
        return 0;
    }
    break;

    default:
        return 0;
    }
}

typedef struct State_0023F5A0 {
    s32 result;
    s32 status;
    s32 index;
    s32 parameter;
    u8 pad10[0x10];
    s32 command;
    s32 response;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 phase;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[6];
    s32 handles[2];
    u8 pad50[0x266];
    s16 mode;
    s16 length;
} State_0023F5A0;

typedef struct Pair_0023F5A0 {
    s32 first;
    s32 second;
} Pair_0023F5A0;

typedef struct Header_0023F5A0 {
    s16 first;
    s16 second;
} Header_0023F5A0;

typedef struct Save_0023F5A0 {
    Header_0023F5A0 header;
    Pair_0023F5A0 pairs[0x1FF4];
    s32 tail[0x53];
} Save_0023F5A0;

typedef struct Tail_0023F5A0 {
    s32 words[0x53];
} Tail_0023F5A0;
extern s32 *memCardTrunkData; /* original: p_kaban_data */
extern Header_0023F5A0 saveFileHeader; /* original: Taku_card_info */

/* Reads the save file from the memory card and checks it. */
s32 TakuLoad_card_file_open(void) {
    extern struct State_0023E610 D_0034FB00;
    State_0023F5A0 *state = (State_0023F5A0 *)&D_0034FB00;
    s32 *destination = (s32 *)&campaignState;

    switch (D_0034FB34) {
    case 0:
        state->result = func_00193BA8(state->index, state->parameter, D_0029B1BE, 1);
        state->status = func_00194248(1, &state->command, &state->response);
        if (state->status == 1 && state->command == 2) {
                if (state->response < 0) {
                    switch (state->response) {
                    case -2:
                        state->retries++;
                        if (state->retries >= 3) {
                            state->state = 3;
                            state->phase = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 5;
                    case -4:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 10;
                    case -5:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 10;
                    case -7:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 10;
                    default:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->handles[state->index] = state->response;
                    state->phase = 1;
                    state->retries = 0;
                    return 0;
                }
        } else {
            return 0;
        }
        break;
    case 1:
        state->result = func_00193DD0(state->handles[state->index], state->mode, state->length, 1);
        state->status = func_00194248(1, &state->command, &state->response);
        if (state->status == 1 && state->command == 4) {
                switch (state->response) {
                case 0:
                    state->phase = 2;
                    state->retries = 0;
                    return 0;
                case -2:
                    state->retries++;
                    if (state->retries >= 3) {
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 3;
                    state->phase = 0;
                    state->retries = 0;
                    return 10;
                default:
                    state->state = 3;
                    state->phase = 0;
                    state->retries = 0;
                    return 2;
                }
        } else {
            return 0;
        }
        break;
    case 2:
        FlushCache(0);
        state->result = func_00193F38(state->handles[state->index], &((Save_0023F5A0 *)0x1E10000)[state->index], 0x100F0);
        state->status = func_00194248(1, &state->command, &state->response);
        if (state->status == 1 && state->command == 5) {
                if (state->response < 0) {
                    switch (state->response) {
                    case -2:
                        state->retries++;
                        if (state->retries >= 3) {
                            state->state = 3;
                            state->phase = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -4:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 10;
                    default:
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->phase = 3;
                    state->retries = 0;
                    return 0;
                }
        } else {
            return 0;
        }
        break;
    case 3:
        state->result = sceMcClose(state->handles[state->index]);
        state->status = func_00194248(1, &state->command, &state->response);
        if (state->status == 1 && state->command == 3) {
                switch (state->response) {
                case 0:
                {
                    s32 second;
                    s32 first;
                    s32 count;
                    s32 *dst;
                    s32 *src;

                    state->state = 0;
                    state->phase = 0;
                    state->retries = 0;
                    dst = memCardTrunkData;
                    count = 0x1FF4;
                    src = (s32 *)((Save_0023F5A0 *)0x1E10000)[state->index].pairs;
                    do {
                        first = *src++;
                        second = *src++;
                        count--;
                        dst[0] = first;
                        dst[1] = second;
                        dst += 2;
                    } while (count > 0);
                    saveFileHeader = ((Save_0023F5A0 *)0x1E10000)[state->index].header;
                    *(Tail_0023F5A0 *)destination = *(Tail_0023F5A0 *)((Save_0023F5A0 *)0x1E10000)[state->index].tail;
                    if (LkCheckData((u16 *)&((Save_0023F5A0 *)0x1E10000)[state->index]) != 0) {
                        TakuLoad_Name_Set(state->parameter);
                        return 0x100;
                    }
                    state->state = 3;
                    state->phase = 0;
                    state->retries = 0;
                    return 10;
                }
                case -2:
                    state->retries++;
                    if (state->retries >= 3) {
                        state->state = 3;
                        state->phase = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 3;
                    state->phase = 0;
                    state->retries = 0;
                    return 10;
                default:
                    state->state = 3;
                    state->phase = 0;
                    state->retries = 0;
                    return 2;
                }
        } else {
            return 0;
        }
        break;
    default:
        return 0;
    }
}

/* Copies the loaded player name into side `side`'s profile. */
void TakuLoad_Name_Set(s32 side) {
    extern volatile s32 D_002D19D8;
    extern s32 D_002D19E0;
    extern u16 D_002D49D4[];
    s16 i;
    u16 *dest;
    s32 offset;
    u8 *src;
    u16 v;
    s32 off2;

    src = (u8 *)&campaignState;
    if (side == 0) {
        i = 0;
        offset = 0;
        while (i < 12) {
            if (i == 0) {
                dest = (u16 *)((u8 *)&D_002D49D4[D_002D19D8] + offset);
                *dest = *(u16 *)(src + 0x24);
            }
            v = *(u16 *)(src + 0x24);
            dest = (u16 *)((u8 *)&D_002D49D4[D_002D19D8] + offset + 4);
            offset += 2;
            *dest = v;
            src += 2;
            i++;
        }
    } else {
        i = 0;
        off2 = 0;
        while (i < 12) {
            v = *(u16 *)(src + 0x24);
            dest = (u16 *)((u8 *)&D_002D49D4[D_002D19E0] + off2);
            off2 += 2;
            *dest = v;
            src += 2;
            i++;
        }
    }
}

typedef struct State_0023FCE0 {
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
    s32 field_20;
    s32 field_24;
    u8 pad_28[8];
    s16 field_30;
    s16 field_32;
    s16 field_34;
    u8 pad_36[10];
    s16 field_40;
} State_0023FCE0;
extern s32 D_0034FB10;
extern s32 D_0034FB14;
extern s32 D_0034FB18;

/* Resets a memory-card job's state words. */
static inline void reset_0023FCE0(State_0023FCE0 *state, s32 value) {
    state->field_30 = value;
    state->field_34 = 0;
    state->field_40 = 0;
}

/* Watches the memory card for the custom-duel load. (original: TakuCustom_card_kansi) */
s32 TakuCustom_card_watch(s32 mode) {
    extern struct State_0023E610 D_0034FB00;
    State_0023FCE0 *state = (State_0023FCE0 *)&D_0034FB00;
    s32 status;
    s32 status2;

    *(s32 *)0x0034FB00 = func_00194380(D_0034FB08, D_0034FB0C, &D_0034FB10, &D_0034FB14, &D_0034FB18);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if (D_0034FB04 == 1) {
        if (state->field_20 == 1) {
            switch (state->field_24) { /* switch 1; irregular */
            case 0:
                break;
            case -1:
                reset_0023FCE0(state, 3);
                return 0x700;
            case -2:                                /* switch 1 */
                reset_0023FCE0(state, 3);
                return 0x700;
            default:                                /* switch 1 */
                reset_0023FCE0(state, 3);
                break;
            }
                switch (state->field_10) {
                case 0:                             /* switch 2 */
                    reset_0023FCE0(state, 3);
                    return 2;
                case 1:                             /* switch 2 */
                    reset_0023FCE0(state, 3);
                    if (state->field_8 == 1) {
                        status = 0x400;
                    } else {
                        status = 4;
                    }
                    return status;
                case 2:
                    break;
                case 3:
                    reset_0023FCE0(state, 3);
                    if (state->field_8 == 1) {
                        status2 = 0x500;
                    } else {
                        status2 = 4;
                    }
                    return status2;
                default:                            /* switch 2 */
                    reset_0023FCE0(state, 3);
                    return 2;
                }
                    if (state->field_10 == 2) {
                        switch (state->field_18) { /* switch 3; irregular */
                        case 0:                     /* switch 3 */
                            state->field_40 = (s16) (state->field_40 + 1);
                            if (state->field_40 >= 3) {
                                state->field_30 = 3;
                                state->field_34 = 0;
                                state->field_40 = 3;
                                return 3;
                            }
                            break;
                        case 1:                     /* switch 3 */
                            if (state->field_30 == 0) {
                                reset_0023FCE0(state, 1);
                                return 0x10;
                            }
                            break;
                        default:                    /* switch 3 */
                            reset_0023FCE0(state, 3);
                            return 2;
                        }
                    }
        }
    }
    return 0;
}

typedef struct State_0023FF30 {
    s32 request;
    s32 status;
    s32 port;
    s32 slot;
    u8 pad10[0x10];
    s32 operation;
    s32 result;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 step;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[2];
    s16 ready[2];
    s32 handles[2];
    u8 pad50[0x266];
    s16 mode;
    s16 offset;
} State_0023FF30;

/* Reads the custom-duel opponent's save from the memory card. */
s32 TakuCustom_card_file_open(void) {
    extern struct State_0023E610 D_0034FB00;
    extern void *D_0034FAEC;
    State_0023FF30 *state;
    s32 *destination;

    state = (State_0023FF30 *)&D_0034FB00;
    destination = (s32 *)&campaignState;
    switch (D_0034FB34) {
    case 0:
        state->request = func_00193BA8(state->port, state->slot, D_0029B1BE, 1);
        state->status = func_00194248(1, &state->operation, &state->result);
        if (state->status == 1) {
            if (state->operation == 2) {
                if (state->result < 0) {
                    switch (state->result) {
                    case -2:
                        state->retries = (s16) (state->retries + 1);
                        if (state->retries >= 3) {
                            state->state = 3;
                            state->step = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 5;
                    case -4:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 0xA;
                    case -5:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 0xA;
                    case -7:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 0xA;
                    default:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->handles[state->port] = (s32) state->result;
                    state->step = 1;
                    state->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    case 1:
        state->request = func_00193DD0(state->handles[state->port], state->mode, state->offset, 1);
        state->status = func_00194248(1, &state->operation, &state->result);
        if (state->status == 1) {
            if (state->operation == 4) {
                switch (state->result) {
                case 0:
                    state->step = 2;
                    state->retries = 0;
                    return 0;
                case -2:
                    state->retries = (s16) (state->retries + 1);
                    if (state->retries >= 3) {
                        state->state = 3;
                        state->step = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 3;
                    state->step = 0;
                    state->retries = 0;
                    return 0xA;
                default:
                    state->state = 3;
                    state->step = 0;
                    state->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 2:
        FlushCache(0);
        state->request = func_00193F38(state->handles[state->port], (u8 *)0x01E10000 + state->port * 0x100F0, 0x100F0);
        state->status = func_00194248(1, &state->operation, &state->result);
        if (state->status == 1) {
            if (state->operation == 5) {
                if (state->result < 0) {
                    switch (state->result) {
                    case -2:
                        state->retries = (s16) (state->retries + 1);
                        if (state->retries >= 3) {
                            state->state = 3;
                            state->step = 0;
                            state->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -4:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 0xA;
                    default:
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 2;
                    }
                } else {
                    state->step = 3;
                    state->retries = 0;
                    return 0;
                }
            }
        }
        return 0;
    case 3:
        state->request = sceMcClose(state->handles[state->port]);
        state->status = func_00194248(1, &state->operation, &state->result);
        if (state->status == 1) {
            if (state->operation == 3) {
                switch (state->result) {
                case 0:
                    state->state = 0;
                    state->step = 0;
                    state->retries = 0;
                    if (state->port == 0) {
                        {
                            s32 second;
                            s32 first;
                            s32 count;
                            s32 *dst;
                            s32 *src;

                            dst = (s32 *)memCardTrunkData;
                            src = (s32 *)((u8 *)0x01E10004 + state->port * 0x100F0);
                            count = 0x1FF4;
                            do {
                                first = *src++;
                                second = *src++;
                                count--;
                                dst[0] = first;
                                dst[1] = second;
                                dst += 2;
                            } while (count > 0);
                        }
                        saveFileHeader = *(Header_0023F5A0 *)((u8 *)0x01E10000 + state->port * 0x100F0);
                        *(Tail_0023F5A0 *)destination = *(Tail_0023F5A0 *)((u8 *)0x01E1FFA4 + state->port * 0x100F0);
                        if (LkCheckData((u16 *)((u8 *)0x01E10000 + state->port * 0x100F0)) != 0) {
                            TakuLoad_Name_Set(state->port);
                            state->ready[state->port] = 1;
                            state->port = 1;
                            return 0x10;
                        }
                        state->state = 3;
                        state->step = 0;
                        state->retries = 0;
                        return 0xA;
                    }
                    {
                        s32 second;
                        s32 first;
                        s32 count;
                        s32 *dst;
                        s32 *src;

                        dst = (s32 *)D_0034FAEC;
                        src = (s32 *)((u8 *)0x01E10004 + state->port * 0x100F0);
                        count = 0x1FF4;
                        do {
                            first = *src++;
                            second = *src++;
                            count--;
                            dst[0] = first;
                            dst[1] = second;
                            dst += 2;
                        } while (count > 0);
                    }
                    saveFileHeader = *(Header_0023F5A0 *)((u8 *)0x01E10000 + state->port * 0x100F0);
                    *(Tail_0023F5A0 *)destination = *(Tail_0023F5A0 *)((u8 *)0x01E1FFA4 + state->port * 0x100F0);
                    if (LkCheckData((u16 *)((u8 *)0x01E10000 + state->port * 0x100F0)) != 0) {
                        TakuLoad_Name_Set(state->port);
                        state->ready[state->port] = 1;
                        state->port = 1;
                        return 0x100;
                    }
                    state->state = 3;
                    state->step = 0;
                    state->retries = 0;
                    return 0xA;
                case -2:
                    state->retries = (s16) (state->retries + 1);
                    if (state->retries >= 3) {
                        state->state = 3;
                        state->step = 0;
                        state->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    state->state = 3;
                    state->step = 0;
                    state->retries = 0;
                    return 0xA;
                default:
                    state->state = 3;
                    state->step = 0;
                    state->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    default:
        return 0;
    }
}

typedef struct State_002406C0 {
    s32 result;
    s32 result4;
    s32 index;
    s32 slot;
    s32 status;
    s32 value;
    s32 ready;
    s32 unused1C;
    s32 status20;
    s32 status24;
    u8 unused28[8];
    s16 mode;
    s16 unused32;
    s16 count;
    u8 unused36[10];
    s16 retries;
    s16 unused42;
    s16 flags[2];
} State_002406C0;

/* Watches the memory card for the after-trade save. (original: TakuTrade_Save_card_kansi) */
s32 TakuTrade_Save_card_watch(s32 mode) {
    State_002406C0 *state = (State_002406C0 *)&D_0034FB00;
    s32 ret;

    D_0034FB00.result = func_00194380(D_0034FB08, D_0034FB0C,
                                    &D_0034FB10, &D_0034FB14, &D_0034FB18);
    D_0034FB04 = func_00194248(1, &D_0034FB20, &D_0034FB24);
    if ((D_0034FB04 == 1) && (state->status20 == 1)) {
        switch (state->status24) {
        case 0:
            break;
        case -1:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 0x700;
            goto done;
        case -2:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 0x700;
            goto done;
        default:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            break;
        }
        switch (state->status) {
        case 0:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 2;
            goto done;
        case 1:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 4;
            goto done;
        case 2:
            break;
        case 3:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 4;
            goto done;
        default:
            state->mode = 14;
            state->count = 0;
            state->retries = 0;
            ret = 2;
            goto done;
        }
        if (state->status == 2) {
            switch (state->ready) {
            case 0:
                state->retries++;
                if (state->retries >= 3) {
                    state->mode = 11;
                    state->count = 0;
                    state->retries = 3;
                    if (state->mode == 11) {
                        ret = 14;
                    } else {
                        ret = 3;
                    }
                    return ret;
                }
                break;
            case 1:
                state->retries = 0;
                if (state->mode == 0) {
                    if (state->index == 0) {
                        state->flags[state->index] = 1;
                        state->index = 1;
                        ret = 0;
                        goto done;
                    }
                    state->flags[0] = 0;
                    state->flags[1] = 0;
                    state->index = 0;
                    state->mode = 5;
                    ret = 9;
                    goto done;
                }
                if (state->mode == 3) {
                    if (state->value < 250) {
                        state->mode = 14;
                        state->count = 0;
                        state->retries = 0;
                        ret = 5;
                        goto done;
                    }
                    state->mode = 4;
                    ret = 9;
                    goto done;
                }
                break;
            default:
                state->mode = 14;
                state->count = 0;
                state->retries = 0;
                ret = 2;
                goto done;
            }
        }
    }
    switch (state->mode) {
    case 0:
        ret = 9;
        break;
    case 3:
        ret = 17;
        break;
    case 11:
        ret = 14;
        break;
    case 13:
        ret = 1;
        break;
    default:
        ret = 0;
        break;
    }
done:
    return ret;
}

typedef struct IOState_002409E0 {
    s32 call_result;
    s32 sync_result;
    s32 slot;
    s32 path;
    u8 pad10[0x10];
    s32 command;
    s32 result;
    u8 pad28[8];
    s16 state;
    u8 pad32[2];
    s16 step;
    u8 pad36[0xA];
    s16 retries;
    u8 pad42[6];
    s32 handles[2];
    u8 pad50[0x266];
    s16 first_block;
    s16 block_count;
} IOState_002409E0;

/* Writes the save file after a trade. (original: TakuTrade_Save_card_file_kakikomi_Ver2) */
s32 TakuTrade_Save_card_file_write_Ver2(void) {
    extern s32 func_00193DD0();
    extern s32 *memCardTrunkData;
    extern struct State_0023E610 D_0034FB00;
    s32 second;
    s32 first;
    s32 count;
    s32 *dest;
    s32 *source;
    IOState_002409E0 *io = (IOState_002409E0 *)&D_0034FB00;

    switch (D_0034FB34) {
    case 0:
        io->call_result = func_00193BA8(io->slot, io->path, D_0029B1BE, 2);
        io->sync_result = func_00194248(1, &io->command, &io->result);
        if (io->sync_result == 1) {
            if (io->command == 2) {
                if (io->result < 0) {
                    switch (io->result) {
                    case -2:
                        io->retries = (s16) (io->retries + 1);
                        if (io->retries >= 3) {
                            io->state = 0xB;
                            io->step = 0;
                            io->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 5;
                    case -4:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 0xA;
                    case -5:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 0xA;
                    case -7:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 0xA;
                    default:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 2;
                    }
                } else {
                    io->handles[io->slot] = (s32) io->result;
                    io->step = 1;
                    io->retries = 0;
                    io->step = 0;
                    io->retries = 0;
                    if (io->slot == 0) {
                        io->slot = 1;
                    } else {
                        io->slot = 0;
                        io->step = 1;
                    }
                    return 0;
                }
            }
        }
        return 0;
    case 1:
        io->call_result = func_00193DD0(io->handles[io->slot], io->first_block, io->block_count);
        io->sync_result = func_00194248(1, &io->command, &io->result);
        if (io->sync_result == 1) {
            if (io->command == 4) {
                switch (io->result) {
                case 0:
                    io->step = 2;
                    io->retries = 0;
                    io->step = 1;
                    io->retries = 0;
                    if (io->slot == 0) {
                        io->slot = 1;
                    } else {
                        io->slot = 0;
                        io->step = 2;
                    }
                    return 0;
                case -2:
                    io->retries = (s16) (io->retries + 1);
                    if (io->retries >= 3) {
                        io->state = 0xB;
                        io->step = 0;
                        io->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    io->state = 0xE;
                    io->step = 0;
                    io->retries = 0;
                    return 0xA;
                default:
                    io->state = 0xE;
                    io->step = 0;
                    io->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 2:
        source = (&memCardTrunkData)[io->slot];
        count = 0x1FF4;
        dest = (s32 *)((u8 *)0x01E10004 + io->slot * 0x100F0);
        do {
            first = *source++;
            second = *source++;
            count--;
            dest[0] = first;
            dest[1] = second;
            dest += 2;
        } while (count > 0);
        LkCheckData((u16 *)((u8 *)0x01E10000 + io->slot * 0x100F0));
        FlushCache(0);
        io->call_result = func_00194058(io->handles[io->slot], (u8 *)0x01E10000 + io->slot * 0x100F0, 0x100F0);
        io->sync_result = func_00194248(1, &io->command, &io->result);
        if (io->sync_result == 1) {
            if (io->command == 6) {
                if (io->result < 0) {
                    switch (io->result) {
                    case -2:
                        io->retries = (s16) (io->retries + 1);
                        if (io->retries >= 3) {
                            io->state = 0xB;
                            io->step = 0;
                            io->retries = 3;
                            return 3;
                        }
                        return 0;
                    case -3:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 5;
                    case -4:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 0xA;
                    case -5:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 0xA;
                    default:
                        io->state = 0xE;
                        io->step = 0;
                        io->retries = 0;
                        return 2;
                    }
                } else {
                    io->step = 4;
                    io->retries = 0;
                    io->step = 2;
                    io->retries = 0;
                    if (io->slot == 0) {
                        io->slot = 1;
                    } else {
                        io->slot = 0;
                        io->step = 4;
                    }
                    return 0;
                }
            }
        }
        return 0;
    case 3:
        io->call_result = sceMcFlush(io->handles[io->slot]);
        io->sync_result = func_00194248(1, &io->command, &io->result);
        if (io->sync_result == 1) {
            if (io->command == 0xA) {
                switch (io->result) {
                case 0:
                    io->step = 4;
                    io->retries = 0;
                    return 0;
                case -2:
                    io->retries = (s16) (io->retries + 1);
                    if (io->retries >= 3) {
                        io->state = 0xB;
                        io->step = 0;
                        io->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    io->state = 0xE;
                    io->step = 0;
                    io->retries = 0;
                    return 0xA;
                default:
                    io->state = 0xE;
                    io->step = 0;
                    io->retries = 0;
                    return 2;
                }
            }
        }
        return 0;
    case 4:
        io->call_result = sceMcClose(io->handles[io->slot]);
        io->sync_result = func_00194248(1, &io->command, &io->result);
        if (io->sync_result == 1) {
            if (io->command == 3) {
                switch (io->result) {
                case 0:
                    io->step = 0;
                    io->retries = 0;
                    io->state = 0;
                    io->step = 4;
                    io->retries = 0;
                    io->state = 5;
                    if (io->slot == 0) {
                        io->slot = 1;
                        return 0;
                    }
                    io->slot = 0;
                    io->step = 0;
                    return 0x100;
                case -2:
                    io->retries = (s16) (io->retries + 1);
                    if (io->retries >= 3) {
                        io->state = 0xB;
                        io->step = 0;
                        io->retries = 3;
                        return 3;
                    }
                    return 0;
                case -4:
                    io->state = 0xE;
                    io->retries = 0;
                    io->step = 0;
                    return 0xA;
                default:
                    io->state = 0xE;
                    io->retries = 0;
                    io->step = 0;
                    return 2;
                }
            }
        }
        return 0;
    }
    return 0;
}

/* Checks a save file's checksum. */
s32 LkCheckData(u16 *data) {
    u16 checksum;
    u16 saved;
    u16 i;
    u16 *p;

    saved = data[1];
    checksum = 0;
    i = 0;
    p = data;
    data[1] = 0;
    while (i < 0x8078) {
        checksum ^= *p++;
        i++;
    }
    checksum ^= 0x4C6B;
    data[1] = checksum;
    if (checksum == saved) {
        return 1;
    }
    return 0;
}
