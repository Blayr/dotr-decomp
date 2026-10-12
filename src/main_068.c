#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023B1F0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023B920);

void func_0023BB00(s32 arg0) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    switch (D_0034F700) {
    case 0:
        var_s0 = 0x20;
        var_s1 = 0x11;
        var_s2 = 0x12;
        break;
    case 1:
        var_s0 = 0x21;
        var_s1 = 0x13;
        var_s2 = 0x14;
        break;
    case 2:
        var_s0 = 0x22;
        var_s1 = 0x15;
        var_s2 = 0x16;
        break;
    case 3:
        var_s0 = 0x23;
        var_s1 = 0x17;
        var_s2 = 0x18;
        break;
    case 4:
        var_s0 = 0x24;
        var_s1 = 0x19;
        var_s2 = 0x1A;
        break;
    }
    func_001A8320(1, 0);
    func_001A8320(2, 0);
    func_001A8320(3, var_s0);
    func_001A8320(4, var_s0);
    func_00214990(0, var_s1);
    func_00214990(1, var_s2);
    if (D_0034F700 < 3) {
        D_0034F700 += 1;
        if (D_0034F700 > 2) {
            D_0034F700 = 0;
            D_0034F708 = 1;
        }
    }
    if (arg0 != 0) {
        func_001A87C0(1, 0);
    } else {
        func_001A8870(1, 0);
    }
}

typedef struct Copy_0023BC80 {
    s32 words[0x3FE8];
} Copy_0023BC80;

void *func_002145E0(s32);
extern s8 D_0034F6F8;

void func_0023BC80(void) {
    D_0034F6F8 = 1;
    *(Copy_0023BC80 *)0x01E301E0 = *(Copy_0023BC80 *)func_002145E0(0);
    func_001A8870(1, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023BCE0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023BFF0);

s8 func_0023C140(void) {
    return D_00299EDA;
}

void func_0023C150(void) {
    D_00299EDA = 0;
}

s32 func_0023C160(void) {
    return (s32) D_00299E4E;
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023C170);

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

void func_0023C170(s32);
s32 func_0023CE40(s32);
extern struct State_0023E610 D_0034FB00;

s32 func_0023C3F0(s32 arg0) {
    State_0023C3F0 *state = (State_0023C3F0 *)&D_0034FB00;
    s32 var_s1;

    var_s1 = 0;
    if (arg0 == 1) {
        func_0023C170(0);
        state->result = 0;
    }
    switch (state->mode) {
    case 0:
    case 14:
    case 11:
        var_s1 = func_0023CE40(1);
        break;
    case 1:
        var_s1 = func_0023D170(1);
        break;
    case 3:
        var_s1 = func_0023CE40(1);
        break;
    }
    if (arg0 == 1) {
        state->field34 = 0;
        state->field40 = 0;
        state->mode = 0;
    }
    switch (var_s1) {
    case 2:
    case 3:
    case 14:
    case 6:
    case 8:
    case 10:
        var_s1 = 0x100;
        break;
    case 0:
        break;
    }
    if (var_s1 != 0) {
        state->result = var_s1;
    }
    if (var_s1 == 0x100) {
        return 0x100;
    }
    return state->result;
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023C560);

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

void func_0023C170(s32);
s32 func_0023F130(s32);
s32 func_0023F5A0(void);
extern struct State_0023E610 D_0034FB00;

s32 func_0023C770(s32 arg0) {
    State_0023C770 *data = (State_0023C770 *)&D_0034FB00;
    s32 var_s1;

    var_s1 = 0;
    if (arg0 == 1) {
        func_0023C170(0);
        data->result = 0;
    }
    switch (data->state) {
    case 0:
        var_s1 = func_0023F130(arg0);
        if (var_s1 == 2) {
            data->state = 0;
        }
        break;
    case 1:
        var_s1 = func_0023F340();
        break;
    case 2:
        var_s1 = func_0023F5A0();
        break;
    case 3:
        var_s1 = func_0023F130(arg0);
        if (var_s1 == 2) {
            var_s1 = 0xA;
        }
        break;
    }
    if (arg0 == 1) {
        data->field_34 = 0;
        data->field_40 = 0;
        var_s1 = 0x10;
        data->state = 0;
    }
    if (var_s1 == 3) {
        var_s1 = 7;
    }
    if (var_s1 != 0) {
        data->result = var_s1;
    }
    if (var_s1 == 0x100) {
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

void func_0023C170(s32);
s32 func_0023F130(s32);
s32 func_0023FF30(void);
extern struct State_0023E610 D_0034FB00;

s32 func_0023C8B0(s32 arg0) {
    State_0023C8B0 *state = (State_0023C8B0 *)&D_0034FB00;
    s32 var_s1;

    var_s1 = 0;
    if (arg0 == 1) {
        func_0023C170(0);
        state->field2BE = 0;
    }
    switch (state->field30) {
    case 0:
        var_s1 = func_0023F130(arg0);
        if (var_s1 == 2) {
            state->field30 = 0;
        }
        break;
    case 1:
        var_s1 = func_0023F340();
        break;
    case 2:
        var_s1 = func_0023FF30();
        break;
    case 3:
        var_s1 = func_0023F130(arg0);
        if (var_s1 == 2) {
            var_s1 = 0xA;
        }
        break;
    }
    if (arg0 == 1) {
        state->field34 = 0;
        state->field40 = 0;
        state->field30 = 0;
        var_s1 = 0x10;
        state->fieldC = 0;
    }
    if (var_s1 == 3) {
        var_s1 = 7;
    }
    if (var_s1 != 0) {
        state->field2BE = var_s1;
    }
    if (var_s1 == 0x100) {
        return 0x100;
    }
    if (state->field8 == 1) {
        state->field2BE = state->field2BE | 0x80;
    }
    return state->field2BE;
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023CA10);

s16 func_0023CC50(s32 arg0) {
    extern struct State_0023E610 D_0034FB00;
    u8 *state = (u8 *)&D_0034FB00;
    s32 result;

    result = 0;
    if (arg0 == 1) {
        func_0023C170(0);
        *(s16 *)(state + 0x2BE) = 0;
    }

    switch (*(s16 *)(state + 0x30)) {
    case 0:
        result = func_0023FCE0(arg0);
        if (result == 2) {
            *(s16 *)(state + 0x30) = 0;
        }
        break;
    case 1:
        result = func_0023F340();
        break;
    case 2:
        result = func_0023FF30();
        break;
    case 3:
        result = func_0023FCE0(arg0);
        if (result == 2) {
            result = 0xA;
        }
        break;
    }

    if (arg0 == 1) {
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

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023CE40);

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


s32 func_00194248(s32, s32 *, s32 *);
s32 func_00194578(s32, s32, void *, u32, s32, void *);
s32 func_00194758(s32, s32, void *, void *);
extern u8 D_0029B100[];
extern u8 D_0029B1BE[];
extern s16 D_0034FB34;

s32 func_0023D170(s32 arg0) {
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
                    if (arg0 == 1) {
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

s32 func_00193BA8(s32, s32, void *, s32);
s32 func_00193D18(s32);
s32 func_00193DD0(s32, s16, s16, s32);
s32 func_00193F38(s32, void *, s32);
s32 func_00194248(s32, s32 *, s32 *);
extern u8 D_0029B1BE[];
extern s16 D_0034FB34;
extern struct State_0023E610 D_0034FB00;

s32 func_0023D400(void) {
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
        func_0017BB60(0);
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
        p->request = func_00193D18(p->handles[p->slot]);
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

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023D920);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023DE90);

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

s32 func_00194248(s32, s32 *, s32 *);
s32 func_001948A8(s32, s32);
extern State_0023E610 D_0034FB00;
extern s32 D_0034FB04;
extern s32 D_0034FB08;
extern s32 D_0034FB0C;
extern s32 D_0034FB20;
extern s32 D_0034FB24;

s32 func_0023E610(void) {
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

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023E6D0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023E7A0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023F130);

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

extern s16 D_0034FB34;
extern u8 D_0029B100[];
extern u8 D_0029B1BE[];

s32 func_00194248(s32, s32 *, s32 *);
s32 func_00194578(s32, s32, void *, u32, s32, void *);
s32 func_00194758(s32, s32, void *, void *);

s32 func_0023F340(void) {
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

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023F5A0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023FBE0);

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

s32 func_00194248(s32, s32 *, s32 *);
s32 func_00194380(s32, s32, s32 *, s32 *, s32 *);
extern s32 D_0034FB04;
extern s32 D_0034FB08;
extern s32 D_0034FB0C;
extern s32 D_0034FB10;
extern s32 D_0034FB14;
extern s32 D_0034FB18;
extern s32 D_0034FB20;
extern s32 D_0034FB24;

static inline void reset_0023FCE0(State_0023FCE0 *state, s32 value) {
    state->field_30 = value;
    state->field_34 = 0;
    state->field_40 = 0;
}

s32 func_0023FCE0(s32 arg0) {
    extern struct State_0023E610 D_0034FB00;
    State_0023FCE0 *state = (State_0023FCE0 *)&D_0034FB00;
    s32 var_v0;
    s32 var_v0_2;

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
                        var_v0 = 0x400;
                    } else {
                        var_v0 = 4;
                    }
                    return var_v0;
                case 2:
                    break;
                case 3:
                    reset_0023FCE0(state, 3);
                    if (state->field_8 == 1) {
                        var_v0_2 = 0x500;
                    } else {
                        var_v0_2 = 4;
                    }
                    return var_v0_2;
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

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023FF30);

INCLUDE_ASM("asm/nonmatchings/main_068", func_002406C0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_002409E0);

s32 func_00241190(u16 *arg0) {
    u16 checksum;
    u16 saved;
    u16 i;
    u16 *p;

    saved = arg0[1];
    checksum = 0;
    i = 0;
    p = arg0;
    arg0[1] = 0;
    while (i < 0x8078) {
        checksum ^= *p++;
        i++;
    }
    checksum ^= 0x4C6B;
    arg0[1] = checksum;
    if (checksum == saved) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241200);

INCLUDE_ASM("asm/nonmatchings/main_068", func_002413F0);

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241840);

s32 func_00241A00(s32 arg0, s32 arg1) {
    u8 color[4];
    s32 temp_v1;

    temp_v1 = arg0 & 0xFFFF;
    if (!(temp_v1 & 0xFFFF7FFF)) {
        return arg0;
    }
    func_00241840(color, temp_v1 & 0x1F, (temp_v1 >> 5) & 0x1F, (temp_v1 >> 0xA) & 0x1F, arg1, 0x1F);
    return (arg0 & 0x8000) | (((color[2] & 0x1F) << 0xA) | ((color[0] & 0x1F) | ((color[1] & 0x1F) << 5)));
}

typedef struct Buffer_00241A90 {
    u8 data[0x50000];
    s32 field_50000;
    s32 field_50004;
    s32 field_50008;
} Buffer_00241A90;

void func_00241A90(void *arg0) {
    Buffer_00241A90 *buffer = arg0;

    buffer->field_50004 = 0;
    buffer->field_50000 = 0;
    buffer->field_50008 = 0x50000;
}

void func_00241AC0(void) {

}

typedef struct Header_00241AD0 {
    u8 padding[0x50000];
    s32 offset;
    s32 start;
    s32 end;
} Header_00241AD0;

s32 func_00241AD0(void *arg0, void **arg1) {
    s32 size = ((Header_00241AD0 *)arg0)->end - ((Header_00241AD0 *)arg0)->start;

    if (size != 0) {
        *arg1 = (u8 *)arg0 + ((Header_00241AD0 *)arg0)->offset;
    }
    return size;
}

typedef struct {
    u8 padding[0x50000];
    s32 position;
    s32 count;
    s32 capacity;
} Buffer_00241B10;

s32 func_00241B10(void *arg0, s32 arg1) {
    Buffer_00241B10 *buffer = arg0;
    s32 capacity;
    s32 available;

    capacity = buffer->capacity;
    available = capacity - buffer->count;
    arg1 = (arg1 < available) ? arg1 : available;
    buffer->position = (buffer->position + arg1) % capacity;
    buffer->count = buffer->count + arg1;
    return arg1;
}

typedef struct {
    u8 data[0x50000];
    s32 write_index;
    s32 count;
    s32 capacity;
} Buffer_00241B80;

s32 func_00241B80(void *arg0, void **arg1) {
    Buffer_00241B80 *buffer = arg0;
    s32 count;
    s32 capacity;

    count = buffer->count;
    if (count != 0) {
        capacity = buffer->capacity;
        *arg1 = (u8 *)arg0 + ((capacity + (buffer->write_index - count)) % capacity);
    }
    return buffer->count;
}

s32 func_00241BE0(s32 *arg0, s32 arg1) {
    s32 remaining;

    remaining = arg0[0x14001];
    arg1 = (arg1 < remaining) ? arg1 : remaining;
    arg0[0x14001] -= arg1;
    return arg1;
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_00241C20);

typedef struct {
    u32 words[4];
} Tag_00241E80;

void func_001872F8(void *, u64);
void func_00187308(void *);
void func_00187318(void *);
void func_00187370(void *, s32, s32, s32);
void func_001873E8(void *, u64, s32, s32, s32, s32);
void func_00187480(void *, s32, s32, s32);
void *func_001874F8(void *, s32);
void func_00187510(void *, __int128);
void func_00187528(void *);
void func_001875D0(void *, s32, u64);
extern Tag_00241E80 D_0029B2D0;
extern Tag_00241E80 D_0029B2E0;

void func_00241E80(u64 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 spB0[16];
    Tag_00241E80 spC0;
    Tag_00241E80 spD0;
    s32 temp_s0;
    s32 temp_s7;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    u64 rowBits;
    s32 var_s5;
    u64 *temp_v0;

    spC0 = D_0029B2D0;
    temp_s7 = arg3 >> 4;
    temp_s0 = arg4 >> 4;
    spD0 = D_0029B2E0;
    func_001872F8(&spB0, (arg0 & 0x0FFFFFFF) | 0x20000000);
    func_00187308(&spB0);
    if (arg2 == 0) {
        func_00187370(&spB0, 0, 0, 0);
        func_00187510(&spB0, *(__int128 *) &spC0);
        func_001875D0(&spB0, 0x50, 0xC1B00ULL << 0x20);
        func_001875D0(&spB0, 0x52, 0x10 | (0x10ULL << 0x20));
        func_00187528(&spB0);
        var_s1 = 0;
        if (var_s1 < temp_s7) {
            var_s5 = 0;
            do {
                var_s2 = 0;
                if (var_s2 < temp_s0) {
                    var_s3 = 0;
                    rowBits = (u64) (u32) var_s5 << 0x20;
                    do {
                        func_00187370(&spB0, 0, 0, 0);
                        func_00187510(&spB0, *(__int128 *) &spC0);
                        func_001875D0(&spB0, 0x51, rowBits | ((u64) (u32) var_s3 << 0x30));
                        func_001875D0(&spB0, 0x53, 0);
                        func_00187528(&spB0);
                        temp_v0 = func_001874F8(&spB0, 4);
                        temp_v0[0] = 0x40 | (0x08000000ULL << 0x20);
                        temp_v0[1] = 0;
                        func_001873E8(&spB0, (u64) (u32) arg1 & 0x0FFFFFFF, 0x40, 0, 0, 0);
                        var_s2 += 1;
                        arg1 += 0x400;
                        var_s3 += 0x10;
                    } while (var_s2 < temp_s0);
                }
                var_s1 += 1;
                var_s5 += 0x10;
            } while (var_s1 < temp_s7);
        }
    }
    func_00187480(&spB0, 0, 0, 0);
    func_00187510(&spB0, *(__int128 *) &spD0);
    func_001875D0(&spB0, 0x3F, 0);
    func_001875D0(&spB0, 0x14, 0x60);
    func_001875D0(&spB0, 6, (0xA803ULL << 0x10) | 0x1B00 | (0xAULL << 0x20));
    func_001875D0(&spB0, 0, 0x116);
    func_001875D0(&spB0, 3, 0x80008);
    func_001875D0(&spB0, 5, 0x79006C00);
    func_001875D0(&spB0, 3, (s64) ((arg3 * 0x10) + 8) | ((s64) ((arg4 * 0x10) + 8) << 0x10));
    func_001875D0(&spB0, 5, (0x8700ULL << 0x10) | 0x9400);
    func_00187528(&spB0);
    func_00187318(&spB0);
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_00242190);

INCLUDE_ASM("asm/nonmatchings/main_068", func_002423A0);

void func_002423F0(s32 arg0) {
    do {
    } while (arg0 == func_001854E0(0));
    D_003505F8 = 0;
    D_00350340 = 1;
    (&D_00350340)[2] = 0;
}

void func_00242450(void) {
    D_00350340 = 0;
    D_003505F8 = 0;
}

void func_00242470(s32 arg0, s32 arg1, s32 arg2) {
    D_0029B2F0 = arg1;
    D_003503B0 = arg2;
    func_00241C20(0, 0, 0, 0x280, 0x1C0);
    func_001851E8(D_003503C0, 0, 0x280, 0xE0, 0, 0, 1);
    func_0017BB60(0);
    D_00350368 = 0x01200000;
    D_00350370 = 0x0152A000;
    D_00350378 = 0x015C3C80;
    D_00350380 = 0x015C4CC0;
    D_00350388 = 0x0178DE40;
    D_00350788 = 0x0178E640;
    D_00350390 = 0x017DE680;
    D_00350398 = 0x017EA680;
    D_003503A0 = 0x0186A680;
    D_003503A8 = 0x0186E680;
    func_00242580(arg0);
}
