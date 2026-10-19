/* The controller (SzPad_*). */

#include "common.h"

typedef struct {
    s8 low : 4;
    s8 high : 4;
} Flags_002031F0;

typedef struct {
    s8 type;
    Flags_002031F0 mode;
    u8 pad[0x5A];
} Port_002031F0;

extern u8 controllerTwoBuffer;
extern Port_002031F0 D_00325C75[];

/* Starts the two pads. */
void SzPad_Init(void) {
    RhMem_FillMemory((s8 *) padStates, 0, 0x2C0);
    D_00325C75[-1].type = 0xA;
    D_00325C75[0].type = 0xA;
    D_00325C75[-1].mode.low = 4;
    D_00325C75[0].mode.low = 4;
    scePadInit(0);
    scePadPortOpen(0, 0, padStates);
    scePadPortOpen(1, 0, &controllerTwoBuffer);
}

/* Ends the pads. */
void SzPad_Term(void) {
    RhMem_FillMemory4(padStates, 0, 0xB0);
}

extern s8 D_00325C19[];

typedef struct {
    u8 pad[0x25A];
    s8 low : 4;
    s8 high : 4;
} Flags_002032C0;

/* Sets pad `pad`'s key-repeat interval and its analog mode. */
void SzPad_SetParam(s32 pad, s8 interval, s64 analog) {
    s32 offset;
    Flags_002032C0 *entry;

    offset = pad * 0x5C;
    D_00325C19[offset] = interval;
    entry = (Flags_002032C0 *)(padStates + offset);
    entry->low = analog;
}

typedef struct Pad_00203320 {
    u16 buttons[3];
    u8 act[4];
    u8 data[12];
    u8 pad16[2];
    s32 press[16];
    s8 mode;
    s8 base;
    s8 low : 4;
    s8 count : 4;
    s8 state : 6;
    s8 pressed : 1;
    s8 ready : 1;
} Pad_00203320;

/* Clears a pad's state. */
static inline void reset_00203320(Pad_00203320 *pad) {
    s32 i;

    for (i = 0; i < 3; i++) {
        pad->buttons[i] = 0;
    }
    for (i = 0; i < 16; i++) {
        pad->press[i] = -pad->base;
    }
    pad->pressed = 0;
    for (i = 0; i < 4; i++) {
        pad->act[i] = 0x80;
    }
    pad->ready = 0;
    for (i = 0; i < 12; i++) {
        pad->data[i] = 0;
    }
}

/* Reads both pads' state from libpad: connected, analog or not, buttons, sticks, pressures. */
void SzPad_Status(void) {
    extern s32 scePadGetReqState();
    s32 port;
    Pad_00203320 *pad;
    u8 *base;
    s32 state;
    s32 id;
    s32 offs;

    base = padStates;
    for (port = 0; port < 2; port++, base += 0x5C) {
        pad = (Pad_00203320 *)(base + 0x200);
        state = scePadGetState(port, 0);
        if (state == 0) {
            reset_00203320(pad);
            pad->state = 0;
        }
        if (state == 2 || state == 6) {
            switch (pad->state) {
            case 0:
                for (state = 0; state < 3; state++) {
                    pad->buttons[state] = 0;
                }
                for (state = 0; state < 16; state++) {
                    pad->press[state] = -pad->base;
                }
                pad->pressed = 0;
                for (state = 0; state < 4; state++) {
                    pad->act[state] = 0x80;
                }
                pad->ready = 0;
                for (state = 0; state < 12; state++) {
                    pad->data[state] = 0;
                }
                pad->count = scePadInfoMode(port, 0, 4, -1);
                id = scePadInfoMode(port, 0, 1, 0);
                if (id == 0) {
                    break;
                }
                pad->mode = id;
                id = scePadInfoMode(port, 0, 2, 0);
                if (id > 0) {
                    pad->mode = id;
                }
                if (pad->count != 0) {
                    pad->state = 1;
                } else {
                    pad->state = 5;
                }
                break;
            case 1:
                pad->state = 5;
                for (offs = 0; offs < pad->count; offs++) {
                    id = scePadInfoMode(port, 0, 4, offs);
                    if (id == 7 && scePadSetMainMode(port, 0, offs, 3) == 1) {
                        pad->mode = id;
                        pad->state = 2;
                        break;
                    }
                }
                break;
            case 2:
                id = scePadGetReqState(port, 0);
                if (id != 0) {
                    if (id == 1) {
                        pad->state = 1;
                    }
                } else {
                    pad->pressed = 1;
                    pad->state = 3;
                }
                break;
            case 3:
                pad->state = 5;
                if (scePadInfoPressMode(port, 0) == 1 && scePadEnterPressMode(port, 0) == 1) {
                    pad->state = 4;
                }
                break;
            case 4:
                id = scePadGetReqState(port, 0);
                if (id != 0) {
                    if (id == 1) {
                        pad->state = 3;
                    }
                } else {
                    pad->ready = 1;
                    pad->state = 5;
                }
                break;
            case 5:
                break;
            }
        }
    }
}

typedef struct Flags_00203840 {
    s8 status : 6;
    s8 unused : 2;
} Flags_00203840;

/* Works out this frame's newly pressed, held and repeating buttons of both pads. */
void SzPad_Act(void) {
    s32 i;
    s32 j;
    u8 *temp_t0;
    s32 temp_t1;
    u8 *var_t2;
    u8 *var_t3;
    s32 temp_t4;

    var_t3 = padStates;
    i = 0;
    do {
        temp_t0 = var_t3 + 0x200;
        if (((Flags_00203840 *)(var_t3 + 0x25B))->status == 5) {
            j = 0;
            var_t2 = temp_t0;
            do {
                temp_t1 = 1 << j;
                temp_t4 = *(u16 *)temp_t0 & temp_t1;
                if ((temp_t4 != 0) && (temp_t4 == (*(u16 *)(temp_t0 + 2) & temp_t1))) {
                    *(s32 *)(var_t2 + 0x18) += 1;
                } else {
                    *(s32 *)(var_t2 + 0x18) = -*(s8 *)(temp_t0 + 0x59);
                }
                j += 1;
                var_t2 += 4;
            } while (j < 0x10);
            *(u16 *)(temp_t0 + 2) = *(u16 *)temp_t0;
            *(u16 *)temp_t0 = *(u16 *)(temp_t0 + 4);
            *(u16 *)(temp_t0 + 4) = 0;
        }
        i += 1;
        var_t3 += 0x5C;
    } while (i < 2);
}

typedef struct Flags_002038F0 {
    s8 mode : 6;
    s8 axes : 1;
    s8 pressure : 1;
} Flags_002038F0;

extern u8 padStates[]; /* original: gSzPad_pl */

/* The pads' per-vertical-blank work. */
s32 SzPad_VSync(void) {
    u8 data[20];
    u8 *pressure;
    s32 axisIndex;
    s32 state;
    u8 *axes;
    s32 pressureIndex;
    s32 port;
    u8 *pad;
    u8 *entry;

    entry = padStates;
    port = 0;
    do {
        pad = entry + 0x200;
        if (((Flags_002038F0 *)(entry + 0x25B))->mode == 5) {
            state = scePadGetState(port, 0);
            if (state == 2 || state == 6) {
                if (scePadRead(port, 0, data) != 0) {
                    if (((Flags_002038F0 *)(pad + 0x5B))->axes) {
                        axes = data;
                        axisIndex = 0;
                        do {
                            pad[6 + axisIndex] = axes[4];
                            axisIndex++;
                            axes++;
                        } while (axisIndex < 4);
                    }
                    if (((Flags_002038F0 *)(pad + 0x5B))->pressure) {
                        pressure = data;
                        pressureIndex = 0;
                        do {
                            pad[0xA + pressureIndex] = pressure[8];
                            pressureIndex++;
                            pressure++;
                        } while (pressureIndex < 12);
                    }
                    *(u16 *)(pad + 4) |= ((data[2] << 8) | data[3]) ^ 0xFFFF;
                }
            }
        }
        port++;
        entry += 0x5C;
    } while (port < 2);
    return 1;
}

typedef struct State_00203A40 {
    u16 held;       /* the buttons held this frame */
    u16 heldBefore; /* the buttons held the frame before (SzPad_Act copies `held` here first) */
    u8 padding04[0x14];
    s32 counters[16];
    u8 padding58[2];
    s8 interval : 4;
    s8 other : 4;
    u8 padding5B;
} State_00203A40;

/* Pad `pad`'s buttons in `wanted` that are newly pressed (`mode` 0), held (1), or newly pressed or repeating (2). */
s32 SzPad_Check(s32 pad, s32 mode, s32 wanted) {
    s32 bit;
    State_00203A40 *buttons;
    s32 bitMask;
    u8 *counters;
    s32 mask;
    s32 counter;
    s32 result;
    u8 *padState;

    padState = padStates + (pad * 0x5C);
    buttons = (State_00203A40 *)(padState + 0x200);
    switch (mode) {
    case 0:
        return wanted & (buttons->held & ~buttons->heldBefore);
    case 2:
        result = 0;
        bit = 0;
        counters = (u8 *)buttons;
        mask = wanted & 0xFFFF;
        do {
            bitMask = 1 << bit;
            if (mask & bitMask) {
                counter = *(s32 *)(counters + 0x18);
                if ((counter >= 0) && ((counter % buttons->interval) == 0)) {
                    result = (result | bitMask) & 0xFFFF;
                }
            }
            bit += 1;
            counters += 4;
        } while (bit < 0x10);
        return result | SzPad_Check(pad, 0, wanted);
    case 1:
        return buttons->held & wanted;
    }
    return 0;
}

/* Restarts the key-repeat counters of pad `pad`'s buttons in `mask`. */
s32 SzPad_ResetCounter(s32 pad, s32 mask) {
    u8 *buttons;
    s32 bit;
    u8 *counters;

    buttons = padStates + (pad * 0x5C) + 0x200;
    bit = 0;
    counters = buttons;
    do {
        if (mask & 0xFFFF & (1 << bit)) {
            *(s32 *)(counters + 0x18) = -*(s8 *)(buttons + 0x59);
        }
        bit += 1;
        counters += 4;
    } while (bit < 0x10);
    return 0;
}

typedef struct {
    u8 padding[0x25B];
    s8 unused : 6;
    s8 flag : 1;
    s8 unused_high : 1;
} Flags_00203BC0;

/* Whether pad `pad` is in analog mode. */
s32 SzPad_IsAnalog(s32 pad) {
    return ((Flags_00203BC0 *)(padStates + pad * 0x5C))->flag ? 1 : 0;
}

typedef struct {
    u8 padding[0x25B];
    s8 : 7;
    s8 flag : 1;
} Flags_00203C00;

/* Whether pad `pad` reports button pressures. */
s32 SzPad_IsPress(s32 pad) {
    Flags_00203C00 *flags = (Flags_00203C00 *)(padStates + pad * 0x5C);

    return flags->flag ? 1 : 0;
}

typedef struct Entry_00203C40 {
    u8 pad[0x206];
    u8 value;
} Entry_00203C40;

/* Analog byte `index` of pad `pad` (the sticks). */
u8 SzPad_GetAnalogInfo(s32 pad, s32 index) {
    return ((Entry_00203C40 *)(padStates + pad * 0x5C + index))->value;
}

/* Sets analog byte `index` of pad `pad` (the tutorial fakes stick input with it). */
void SzPad_SetAnalogInfo(s32 pad, s32 index, s8 value) {
    *(s8 *)(padStates + pad * 0x5C + index + 0x206) = value;
}

typedef struct {
    u8 pad[0x20A];
    u8 value;
} Entry_00203CA0;

/* The pressure of button `index` of pad `pad`. */
u8 SzPad_GetPressInfo(s32 pad, s32 index) {
    return ((Entry_00203CA0 *)(index + (padStates + pad * 0x5C)))->value;
}
