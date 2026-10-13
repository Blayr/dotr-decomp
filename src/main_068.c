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

extern s8 D_0034F6F8;

void func_0023BC80(void) {
    D_0034F6F8 = 1;
    *(Copy_0023BC80 *)0x01E301E0 = *(Copy_0023BC80 *)func_002145E0(0);
    func_001A8870(1, 0);
}

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023BCE0);

typedef struct Flags_0023BFF0 {
    s8 unused : 4;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
} Flags_0023BFF0;

typedef struct Draw_0023BFF0 {
    u8 pad00[0x10];
    s32 field10;
    s32 field14;
    s32 field18;
    s32 field1C;
    u8 vector20[0x10];
    s32 field30;
    s32 field34;
    u8 pad38[0x49];
    Flags_0023BFF0 flags;
    u8 pad82[0xE];
} Draw_0023BFF0;

typedef struct Texture_0023BFF0 {
    u8 pad00[0x44];
    u8 field44;
    u8 pad45[0x1B];
} Texture_0023BFF0;

void *func_0023BFF0(void *arg0, f32 fparg0, s32 arg1, f32 fparg1, s32 arg2) {
    extern void func_001CD560();
    Texture_0023BFF0 texture;
    Draw_0023BFF0 draw;

    func_001CD560(&draw);
    draw.flags.enabled = 1;
    draw.flags.colored = 1;
    draw.flags.reserved = 0;
    draw.flags.horizontal = 1;
    draw.field30 = 0x3F000000;
    draw.field34 = 0x3F000000;
    func_001DCD70(&texture, 999);
    texture.field44 = arg1;
    func_00205C40((s32)draw.vector20);
    draw.field10 = 0;
    draw.field14 = arg2;
    draw.field18 = 0;
    draw.field1C = 0;
    arg0 = (void *)func_001D9A20((s32)arg0);
    func_001D9ED0(0xFFFFFF);
    func_00205CB0(&draw, fparg0, fparg1);
    return (void *)func_001D9E70(func_001DBD30(
        func_001DBC40((s32)arg0, (s32)(func_001D9F00(&draw, 1) ? &texture : NULL), &draw),
        (s32)&draw));
}

s8 func_0023C140(void) {
    return D_00299EDA;
}

void func_0023C150(void) {
    D_00299EDA = 0;
}

s32 func_0023C160(void) {
    return (s32) D_00299E4E;
}

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
    u8 pad2BA[0x586];
} State_0023C170;


s32 func_0023C170(s32 arg0) {
    extern void *D_0034FAE8;
    extern void *D_0034FAEC;
    extern s8 D_0034FAF0;
    extern State_0023C170 D_0034FB00;
    extern s32 func_00194248(s32, s32 *, s32 *);
    extern s32 func_00194380(s32, s32, s32 *, s32 *, s32 *);
    s32 found[2];
    State_0023C170 *state = &D_0034FB00;
    s16 i;
    s32 *out;

    D_0034FAE8 = func_002145E0(0);
    D_0034FAEC = func_002145E0(1);
    D_0034FAF0 = 1;
    func_00195108((s32)&D_0034FB00, 0x840);
    D_0034FB00.field30 = 0;
    D_0034FB00.field34 = 0;
    D_0034FB00.field36 = 0;
    D_0034FB00.field38 = 0;
    D_0034FB00.field3A = 0;
    D_0034FB00.field3C = 0;
    D_0034FB00.field3E = 0;
    D_0034FB00.field40 = 0;
    D_0034FB00.field42 = 0;
    D_0034FB00.field54 = 0;
    D_0034FB00.field56 = 0;
    D_0034FB00.field48 = 0;
    D_0034FB00.field4C = 0;
    D_0034FB00.field50 = 0;
    D_0034FB00.field52 = 0;
    D_0034FB00.field08 = 0;
    D_0034FB00.field0C = 0;
    D_0034FB00.field10 = 0;
    D_0034FB00.field14 = 0;
    D_0034FB00.field18 = 0;
    D_0034FB00.field1C = 0;
    D_0034FB00.field20 = 0;
    D_0034FB00.field24 = 0;
    D_0034FB00.field2C = 0;
    D_0034FB00.field2E = 0;
    D_0034FB00.field5C = 0;
    D_0034FB00.field60 = 0;
    D_0034FB00.field68 = 6;
    D_0034FB00.field64 = 0;
    D_0034FB00.field284 = 0;
    D_0034FB00.field288 = 0;
    D_0034FB00.field28C = 0;
    D_0034FB00.field290 = 0;
    D_0034FB00.field294 = 0;
    D_0034FB00.field296 = 0;
    D_0034FB00.field2B4 = 0;
    D_0034FB00.field280 = 0;
    D_0034FB00.field2A8 = 0;
    D_0034FB00.field2AA = 0;
    D_0034FB00.field2AC = 0;
    D_0034FB00.field2AE = 0;
    D_0034FB00.field2B0 = 0;
    D_0034FB00.field2B2 = 0;
    D_0034FB00.field2B6 = 0;
    D_0034FB00.field2B8 = 0;

    out = found;
    for (i = 0; i < 2; i++) {
        func_00194380(i, state->field0C, &state->field10, &state->field14, &state->field18);
        func_00194248(0, &state->field20, out);
        out++;
    }

    if (arg0 == 1 && (found[0] != 0 || found[1] != 0)) {
        return 1;
    }
    return 0;
}

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

s32 func_0023F130(s32);
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

s32 func_00194248(s32, s32 *, s32 *);
s32 func_00194380(s32, s32, s32 *, s32 *, s32 *);

s32 func_0023CE40(s32 arg0) {
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
            if (arg0 != 1) {
                state->state = 14;
                state->timer = 0;
                state->retries = 0;
            }
            break;
        }
        switch (state->mode) {
        case 0:
            if (arg0 == 1 && state->state == 14) {
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
                        if (arg0 == 1) {
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

struct State_0023E610;

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

s32 func_00193BA8(s32, s32, void *, s32);
s32 func_00193CE0(s32, s32, void *);
s32 func_00193D18(s32);
s32 func_00194248(s32, s32 *, s32 *);
s32 func_00194758(s32, s32, void *, void *);
s32 func_0023E7A0(void);
extern s16 D_0034FB34;
extern u8 D_0029B100[];
extern u8 D_0029B1BE[];

s32 func_0023D920(void) {
    extern struct State_0023E610 D_0034FB00;
    State_0023D920 *state = (State_0023D920 *)&D_0034FB00;
    s32 result;

    switch (D_0034FB34) {
    case 0:
        state->result = func_00193CE0(state->port, state->slot, D_0029B100);
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
        result = func_0023E7A0();
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
        state->result = func_00193D18(state->handles[state->port]);
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

INCLUDE_ASM("asm/nonmatchings/main_068", func_0023DE90);

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

s32 func_0023E6D0(void) {
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

s32 func_00193BA8(s32, s32, void *, s32);
s32 func_00193D18(s32);
s32 func_00193DD0(s32, s16, s16, s32);
s32 func_00193F38(s32, void *, s32);
s32 func_00194248(s32, s32 *, s32 *);
void func_0023FBE0(s32);
extern u8 D_0029B1BE[];
extern s32 *D_0034FAE8;
extern Header_0023F5A0 D_0034FAF0;
extern s16 D_0034FB34;

s32 func_0023F5A0(void) {
    extern struct State_0023E610 D_0034FB00;
    State_0023F5A0 *state = (State_0023F5A0 *)&D_0034FB00;
    s32 *destination = (s32 *)&D_00299E10;

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
        func_0017BB60(0);
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
        state->result = func_00193D18(state->handles[state->index]);
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
                    dst = D_0034FAE8;
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
                    D_0034FAF0 = ((Save_0023F5A0 *)0x1E10000)[state->index].header;
                    *(Tail_0023F5A0 *)destination = *(Tail_0023F5A0 *)((Save_0023F5A0 *)0x1E10000)[state->index].tail;
                    if (func_00241190((u16 *)&((Save_0023F5A0 *)0x1E10000)[state->index]) != 0) {
                        func_0023FBE0(state->parameter);
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

s32 func_002406C0(void) {
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

typedef struct {
    u16 nloop : 15;
    u16 eop : 1;
    u8 reserved[5];
    u8 pad7 : 4;
    u8 nreg : 4;
    u8 reg : 4;
    u8 pad8 : 4;
    u8 tail[7];
} GifTag_00241C20;

typedef struct {
    void *base;
    s32 size;
    void *current;
    void *giftag;
} Packet_00241C20;

typedef struct {
    __int128 value;
} Quad_00241C20;


void func_00184E10(void *, s32, s64, s64, s32, s32);
void func_00185100(void *);
s32 func_00186120(s32);
void func_00186470(s32, s32);
void func_00187308(void *);
void func_00187318(void *);
void func_00187480(void *, s32, s32, s32);
void func_00187510(void *, __int128);
void func_00187528(void *);
void func_001875D0(void *, s32, u64);

void func_00241C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    extern void func_001872F8();
    extern Quad_00241C20 D_0029B2C0;
    extern GifTag_00241C20 D_00350410;
    extern u8 D_00350420[];
    extern u8 D_00350440[];
    Quad_00241C20 tag;
    Packet_00241C20 packet;
    u32 data[24];
    s32 channel;

    tag = D_0029B2C0;
    channel = func_00186120(2);
    *(__int128 *)&D_00350410 = 0;
    D_00350410.nloop = 8;
    D_00350410.eop = 1;
    D_00350410.nreg = 1;
    D_00350410.reg = 14;
    func_00184E10(D_00350420, 0, (s64)(s16)arg3,
                 (s64)(s16)(((((arg4 >> 1) + 31) >> 5) + ((arg4 + 31) >> 5)) << 6),
                 0, 0);
    *(s64 *)D_00350440 = 0;
    func_0017BB60(0);
    func_00185578(0, 0);
    func_00185100(&D_00350410);
    func_001872F8(&packet, (__int128 *)data);
    func_00187308(&packet);
    func_00187480(&packet, 0, 0, 0);
    func_00187510(&packet, *(__int128 *)&tag);
    func_001875D0(&packet, 0, 6);
    func_001875D0(&packet, 1, ((s64)arg2 << 16) | ((s64)arg0 | ((s64)arg1 << 8)));
    func_001875D0(&packet, 5, 0);
    func_001875D0(&packet, 5, ((s64)0xB400 << 16) | 0x2D00);
    func_00187528(&packet);
    func_00187318(&packet);
    func_0017BB60(0);
    func_00185578(0, 0);
    func_00186470(channel, packet.size);
    func_00185578(0, 0);
}

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
