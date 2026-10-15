#include "common.h"

typedef struct Entry_001F3790 {
    u64 state : 3;
    u64 unused : 29;
    s32 handle;
} Entry_001F3790;

typedef struct Slot_001F3790 {
    u64 state : 3;
    u64 rest : 61;
    u8 pad[0x10];
} Slot_001F3790;

typedef struct State_001F3790 {
    Entry_001F3790 entries[32];
    Slot_001F3790 slots[24];
    s32 group;
    s32 entry;
    s32 count;
    s32 pending;
} State_001F3790;

void SzEffect_Clear(void) {
    extern State_001F3790 D_0031BB50;
    extern Slot_001F3790 D_0031BC50[];
    State_001F3790 *state;
    Entry_001F3790 *entry;
    Slot_001F3790 *slot;
    s32 i;

    state = &D_0031BB50;
    slot = D_0031BC50;
    entry = D_0031BB50.entries;
    for (i = 0; i < 24; i++, slot++) {
        slot->state = 0;
    }
    for (i = 0; (s64)i < 32; i++, entry++) {
        entry->state = 0;
        if (entry->handle != 0) {
            SzMem_Free(entry->handle);
            entry->handle = 0;
        }
    }
    state->count = 0;
    state->pending = 0;
    state->group = -1;
    state->entry = -1;
}

typedef struct Entry_001F3870 {
    u64 state : 3;
    u64 source : 3;
    u64 target : 10;
    u64 reserved : 48;
} Entry_001F3870;

void SzEffect_TrimModule(void) {
    extern Entry_001F3870 D_0031BB50[];
    Entry_001F3870 *entry;
    s32 i;

    entry = D_0031BB50;
    for (i = 0; (s64)i < 32; i++, entry++) {
        if (entry->state == 2 && SzEffect_IsUse2(entry->source, entry->target) == 0) {
            entry->state = 3;
        }
    }
}

typedef struct {
    u8 state : 3;
    u8 kind : 3;
    u16 card : 10;
    u16 pad;
    s32 resource;
} Entry_001F3910;

s32 SzEffect_LoadModule(s32 kind, s32 card, s32 mode, void *unused) {
    extern Entry_001F3910 D_0031BB50[];
    extern u8 D_0031BEA8;
    extern char D_002CFBB0[];
    extern char D_002CFBC6[];
    extern void lSzEffect_LoadOverlayCB();
    extern s32 func_0019B648();
    extern s32 SzFile_ReadRequestParam();
    Entry_001F3910 *entries = D_0031BB50;
    s32 count;
    s32 candidate;
    Entry_001F3910 *scan;
    Entry_001F3910 *entry;
    s32 index;
    s32 i;
    s64 destination;
    s8 letter;
    char path[128];

    scan = D_0031BB50;
    for (i = 0; i < 32L; i++, scan++) {
        if (scan->kind == kind && scan->card == card) {
            if (scan->state == 2) {
                return (s32)scan;
            }
            if (scan->state == 3) {
                scan->state = 2;
                return (s32)scan;
            }
        }
    }

    entry = entries;
    for (index = 0; index < 32L; index++, entry++) {
        if (entry->state == 0) {
            break;
        }
    }
    if (index >= 32L) {
        count = 0;
        candidate = D_0031BEA8 + count;
        for (; count < 32L; candidate++, count++) {
            s32 slot = candidate % 32L;
            entry = &entries[slot];
            if (entry->state == 3) {
                index = slot;
                break;
            }
        }
        D_0031BEA8 = (D_0031BEA8 + 1) % 32L;
    }
    if (index < 32L) {
        destination = (s64)(s32)(0x01EE0000 + (s64)index * 0x8000);
        letter = '?';
        if (entry->resource != 0) {
            SzMem_Free(entry->resource);
            entry->resource = 0;
        }
        switch (kind) {
        case 0: letter = 'C'; break;
        case 1: letter = 'B'; break;
        case 2: letter = 'M'; break;
        }
        if (mode != 0) {
            return 0;
        }
        if (card < 0 || card >= 0x356) {
            return 0;
        }
        func_0019B648(path, D_002CFBB0, SzFile_GetEnv((s32)D_002CFBC6), letter);
        if ((u32)kind < 3) {
            s32 offset = card << 15;
            if ((u32)(kind - 1) < 2) {
                s32 file = SzDuel_Xax2New(card);
                if (file >= 0x2AB) {
                    return 0;
                }
                offset = file << 15;
            }
            if (SzFile_ReadRequestParam(0x800, 0, path, destination, 0x8000,
                             offset, 0x8000, lSzEffect_LoadOverlayCB, index) == 0) {
                return 0;
            }
            entry->kind = kind;
            entry->card = card;
            entry->state = 1;
        } else {
            return 0;
        }
        return (s32)entry;
    }
    return 0;
}

typedef struct Obj_001F3CB0 {
    u8 pad00[8];
    s32 value : 31;
    u32 flag : 1;
    u8 pad0C[3];
    u8 pad0F : 7;
    s8 hi : 1;
    u8 pad10[4];
    s32 f14;
    u8 pad18[4];
    s32 f1C;
} Obj_001F3CB0;

typedef struct Entry_001F3CB0 {
    u8 state : 3;
    u8 sub : 3;
    u16 big : 10;
    s16 h2;
    u8 pad4[4];
} Entry_001F3CB0;

void lSzEffect_LoadOverlayCB(void *arg0, s32 arg1) {
    extern s32 func_0019C100();
    extern s32 SzFile_ReadRequestParam();
    extern u8 D_002CFBC6[];
    extern u8 D_002CFBCB[];
    extern u8 D_002CFBCF[];
    extern Entry_001F3CB0 D_0031BB50[];
    Obj_001F3CB0 *obj;
    Entry_001F3CB0 *entry;
    u8 sp50[0x80];
    s32 size;

    obj = arg0;
    entry = &D_0031BB50[obj->f1C];
    if (arg1 != 0) {
        if (func_0019C100(obj->f14, D_002CFBCB, 3) != 0) {
            if (obj->hi != 0) {
                SzMem_Free(obj->f14);
            }
            arg1 = 0;
        }
        if (entry->state != 1) {
            arg1 = 0;
        }
    }
    if (arg1 == 0) {
        entry->state = 0;
        return;
    }
    entry->h2 = (s16)obj->value;
    if (entry->sub == 0) {
        size = entry->big << 11;
        func_0019B648(sp50, D_002CFBCF, (s32)SzFile_GetEnv((s32)D_002CFBC6));
        arg0 = (void *)SzFile_ReadRequestParam(0xC00, 0, sp50, 0, 0x800, size, 0x800, lSzEffect_LoadSECtlCB,
                                     (s64)obj->f1C);
        if (arg0 == NULL) {
            entry->state = 3;
        }
    } else {
        entry->state = 3;
    }
}

typedef struct Entry_001F3E40 {
    u64 state : 3;
    u64 unused : 29;
    s32 value;
} Entry_001F3E40;

typedef struct Input_001F3E40 {
    u8 pad00[0x14];
    s32 value;
    u8 pad18[4];
    s32 index;
} Input_001F3E40;

void lSzEffect_LoadSECtlCB(void *arg0, s32 arg1) {
    extern Entry_001F3E40 D_0031BB50[];
    Input_001F3E40 *input = arg0;
    Entry_001F3E40 *entry = &D_0031BB50[input->index];

    if (entry->state == 1) {
        entry->state = 3;
    }
    if (arg1 != 0) {
        entry->value = input->value;
    }
}

typedef struct {
    u8 unused : 3;
    u8 kind : 3;
} Flags_001F3EA0;

typedef struct {
    u16 unused : 6;
    u16 id : 10;
} Id_001F3EA0;

u8 *SzEffect_GetModuleInfo(s32 arg0, s32 arg1) {
    extern u8 D_0031BB50[];
    u8 *entry;
    s32 i;

    entry = D_0031BB50;
    i = 0;
    while ((s64)i < 32) {
        if ((arg0 < 0 || ((Flags_001F3EA0 *)entry)->kind == arg0) &&
            (arg1 < 0 || ((Id_001F3EA0 *)entry)->id == arg1)) {
            return entry;
        }
        i++;
        entry += 8;
    }
    return NULL;
}

typedef struct Entry_001F3F20 {
    u64 kind : 3;
    u64 time : 13;
    u64 source : 3;
    u64 target : 10;
    u64 rest : 35;
    u8 pad[0x10];
} Entry_001F3F20;

typedef struct Link_001F3F20 {
    u64 status : 3;
    u64 from : 3;
    u64 to : 10;
    u64 extra : 48;
} Link_001F3F20;

typedef struct Cue_001F3F20 {
    u16 end : 4;
    u16 time : 12;
    u16 id;
} Cue_001F3F20;

static inline Link_001F3F20 *find_001F3F20(s32 source, s32 target) {
    extern Link_001F3F20 D_0031BB50[];
    Link_001F3F20 *slot;
    s32 i;

    slot = D_0031BB50;
    for (i = 0; (s64)i < 32; i++, slot++) {
        if ((source < 0 || slot->from == source) && (target < 0 || slot->to == target)) {
            return slot;
        }
    }
    return NULL;
}

void SzEffect_ReqSE(void) {
    extern Entry_001F3F20 D_0031BC50[];
    extern s32 SzGame_GetFrameSpeed();
    Entry_001F3F20 *entry;
    s32 i;
    s32 j;
    s32 start;
    s32 now;
    Link_001F3F20 *slot;
    s32 delta;
    Cue_001F3F20 *cue;

    entry = D_0031BC50;
    for (i = 0; i < 24; i++, entry++) {
        if (entry->source != 0) {
            continue;
        }
        if (entry->kind != 1) {
            continue;
        }
        slot = find_001F3F20(entry->source, entry->target);
        if (slot == NULL || slot->status != 2) {
            continue;
        }
        cue = *(Cue_001F3F20 **)((u8 *)slot + 4);
        if (cue == NULL) {
            continue;
        }
        delta = SzGame_GetFrameSpeed();
        now = (u16)entry->time;
        start = (u16)(now - delta);
        for (j = 0; j < 64; j++) {
            if (cue[j].end == 0xF) {
                break;
            }
            if (cue[j].time >= start && cue[j].time < now) {
                SzSound_PlaySE(1, cue[j].id);
            }
        }
    }
}

typedef struct Entry_001F40D0 {
    u64 kind : 3;
    u64 time : 13;
    u64 source : 3;
    u64 target : 10;
    s64 noLoad : 1;
    s64 reload : 1;
    s64 started : 1;
    u16 model;
    u16 motion;
    u8 pad08[8];
    s32 result;
    u8 pad14[4];
} Entry_001F40D0;

typedef struct Link_001F40D0 {
    u64 status : 3;
    u64 from : 3;
    u64 to : 10;
    u64 extra : 48;
} Link_001F40D0;

typedef struct State_001F40D0 {
    Link_001F40D0 links[32];
    Entry_001F40D0 entries[24];
    s32 group;
    s32 entry;
} State_001F40D0;

typedef s32 (*Play_001F40D0)(void *, s32);

typedef struct Table_001F40D0 {
    Play_001F40D0 *plays;
    s32 unused;
    s32 count;
} Table_001F40D0;

static inline Link_001F40D0 *find_001F40D0(s32 source, s32 target) {
    extern State_001F40D0 D_0031BB50;
    Link_001F40D0 *link;
    s32 i;

    link = D_0031BB50.links;
    for (i = 0; i < 32L; i++, link++) {
        if ((source < 0 || link->from == source) && (target < 0 || link->to == target)) {
            return link;
        }
    }
    return NULL;
}

static inline void restart_001F40D0(s32 model, s32 loop) {
    SzModel_SetAnimSpeed(model, 0.0f);
    if (loop >= 0) {
        SzModel_SetAnimIntrReverse(model);
    } else {
        SzModel_SetAnimIntrParam(model, 0, 0x10);
    }
    SzModel_SetAnimSpeed(model, 1.0f);
}

void SzEffect_Draw(s32 group) {
    extern State_001F40D0 D_0031BB50;
    extern Entry_001F40D0 D_0031BC50[];
    extern Table_001F40D0 D_00292FF0[];
    extern void iFlushCache(s32);
    extern s32 SzModel_GetAnim(s32);
    extern s32 SzModel_GetAnimParam(s32, s32);
    extern s32 SzModel_GetAnimDir(s32);
    extern void SzView_ReqCamera(s32, s32, s32, u16, s32, void *);
    Entry_001F40D0 *entry;
    Link_001F40D0 *link;
    Link_001F40D0 *links;
    State_001F40D0 *state;
    s32 i;
    s32 flags;
    void *data;
    s32 source;
    s32 target;
    s32 result;
    s32 phase;
    s32 model;
    s32 current;
    s32 loop;
    s32 kind;
    s32 length;
    s32 go;
    s32 hi;
    s32 lo;
    void *addr;
    long base;
    f32 frame;
    f32 start;

    links = D_0031BB50.links;
    entry = D_0031BC50;
    SzGame_GetMode(1);
    RhGeom_PushMatrix(0);
    for (i = 0, base = 0x1E10000; i < 24; i++, entry++, base += 0x8000) {
        if (group >= 0 && entry->source != group) {
            continue;
        }
        flags = -1;
        addr = (void *)0x1ED0000;
        data = NULL;
        if (entry->kind != 1) {
            continue;
        }
        if (entry->noLoad) {
            flags = -2;
        }
        if (entry->reload) {
            flags = -3;
        }
        switch (group) {
        case 1:
            data = (void *)SzModel_GetOverlayB(SzDuel_GetUnitModelID(entry->motion >> 8, entry->motion & 0xFF));
            break;
        case 2:
            data = (void *)SzModel_GetOverlayM(SzDuel_GetUnitModelID(entry->motion >> 8, entry->motion & 0xFF));
            break;
        }
        if (data == NULL) {
            link = find_001F40D0(entry->source, entry->target);
            if (link == NULL || link->status != 2) {
                continue;
            }
            data = (void *)(0x1EE0000 + (long)(link - links) * 0x8000);
        }
        state = &D_0031BB50;
        target = entry->target;
        source = entry->source;
        if (state->group != source || state->entry != target) {
            RhMem_CopyMemory16((void *)0x1E00000, data, 0x800);
            iFlushCache(0);
            mwOverlayInit(0x1E00000, *(s32 *)0x1E0001C - 0x1E00000);
            state->group = source;
            state->entry = target;
        }
        SzEffect_SetTarget(entry->model);
        SzEffect_SetFrom(entry->motion);
        if (entry->source != 1) {
            addr = (void *)base;
        }
        entry->result = result = D_00292FF0[entry->source].plays[entry->target](addr, flags);
        entry->time++;
        if (entry->source == 1) {
            lo = entry->model;
            hi = lo >> 8;
            lo &= 0xFF;
            phase = SzEffect_GetPlayMotion(0);
            model = SzDuel_GetUnitModelID(hi, lo);
            current = SzModel_GetAnim(model);
            loop = SzModel_GetAnimParam(model, 1);
            kind = SzModel_GetAnimDir(model);
            frame = SzModel_GetAnimFrame(model);
            if (result == 1) {
                if (phase == 6) {
                    result = 6;
                } else {
                    result = 0;
                }
            }
            if (result == 3 || result == 4 || result == 8) {
                if (!entry->started) {
                    if (phase == current) {
                        start = SzModel_GetAnimFrame(model);
                    } else {
                        start = 0.0f;
                    }
                    length = SzModel_GetAnimFrameMax(model, phase) - (s32)start;
                    SzView_FreeRequest(0, 1);
                    if (length < 30) {
                        length = 30;
                    }
                    SzView_ReqCamera(0, 2, 0, length, 800, NULL);
                    SzView_ReqCamera(0, 2, 1, length, 0, NULL);
                    SzView_ReqCamera(0, 2, 6, length, model, NULL);
                    entry->started = 1;
                }
                if (result == 4) {
                    result = 0;
                }
            }
            if (phase == 4 && result == 5) {
                SzModel_SetStoneFlag(model, 1);
            }
            if (result == 2 || result == 3 || result == 5 || result == 6) {
                if (current == 3 || current == 4 || current == 6) {
                    if (phase == 6) {
                        SzModel_SetMotionDelay(model, 0);
                    }
                    if (result == 6 && kind == 1 && !(frame < 11.0f)) {
                        go = 0;
                        if (frame >= 16.0f) {
                            go = 1;
                        } else if ((s32)(3.0f * (func_0019A5C8() / 2147483648.0f)) != 0) {
                            go = 1;
                        }
                        if (go) {
                            SzModel_SetAnimFrame(model, frame - 2.0f);
                        }
                    }
                } else {
                    SzModel_SetAnimSpeed(model, 1.0f);
                    if (loop >= 0) {
                        SzModel_SetAnimIntrReverse(model);
                    } else {
                        if (phase == 3) {
                            phase = 4;
                        }
                        SzModel_SetAnimIntr(model, phase);
                    }
                    SzModel_SetAnimSpeed(model, 1.0f);
                }
            } else if (result == 7) {
                if (current == 3 || current == 4) {
                    restart_001F40D0(model, loop);
                }
            } else if (result == 0) {
                if (phase == 3 && current == 4 && !(frame < 16.0f)) {
                    restart_001F40D0(model, loop);
                }
            } else if (result == 8) {
                if (phase == 3 && current == 4) {
                    restart_001F40D0(model, loop);
                }
                SzEffect_Destroy(i);
            }
        } else if (flags == -2) {
            if (result == 8) {
                entry->kind = 2;
            }
        } else if (result == 8) {
            SzEffect_Destroy(i);
        }
    }
    RhGeom_PopMatrix();
}

void SzEffect_Entry(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    SzEffect_EntryCallback(arg0, arg1, arg2, arg3, arg4, 0, 0);
}

typedef struct Slot_001F4900 {
    u16 state : 3;
    u16 counter : 13;
    u16 group : 3;
    u16 entry : 10;
    s16 flagA : 1;
    s16 flagB : 1;
    s16 flagC : 1;
    s16 arg3;
    s16 arg4;
    s32 arg5;
    s32 arg6;
    s32 timer;
    s32 arg2;
} Slot_001F4900;

typedef struct Cache_001F4900 {
    u8 data[0x340];
    s32 group;
    s32 entry;
} Cache_001F4900;

typedef struct Dispatch_001F4900 {
    s32 (**handlers)(void *, s32);
    s32 unused;
    s32 count;
} Dispatch_001F4900;

extern s32 D_0031BE90;
extern Dispatch_001F4900 D_00292FF0[];
extern s32 D_00292FF8[];

s32 SzEffect_EntryCallback(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    extern Cache_001F4900 D_0031BB50;
    extern Slot_001F4900 D_0031BC50[];
    Slot_001F4900 *slot;
    void *source;
    u8 *buffer;
    s32 index;
    void *destination;
    s32 result;
    extern s32 SzEffect_LoadModule();

    buffer = (u8 *)&D_0031BB50;
    slot = D_0031BC50;
    source = 0;
    if (arg0 < 0 || arg0 >= 3) {
        return -1;
    }
    if (arg1 < 0 || arg1 >= D_00292FF8[arg0 * 3]) {
        return -1;
    }
    if (arg0 == 1 && SzEffect_IsUse2(1, -1) != 0) {
        return -1;
    }
    switch (arg0) {
    case 1:
        source = (void *)SzModel_GetOverlayB(SzDuel_GetUnitModelID(arg4 >> 8, arg4 & 0xFF));
        break;
    case 2:
        source = (void *)SzModel_GetOverlayM(SzDuel_GetUnitModelID(arg4 >> 8, arg4 & 0xFF));
        break;
    }
    if (source == 0) {
        s32 allocation = SzEffect_LoadModule(arg0, arg1, 1);
        if (allocation == 0) {
            return -1;
        }
        source = (void *)(((s64)(((u8 *)allocation - buffer) >> 3) << 15) + 0x01EE0000);
    }
    index = 0;
    do {
        destination = (void *)0x01ED0000;
        if (slot->state == 0) {
            Cache_001F4900 *cache = &D_0031BB50;
            if (D_0031BE90 != arg0 || cache->entry != arg1) {
                RhMem_CopyMemory16((void *)0x01E00000, (void *)source, 0x800);
                iFlushCache(0);
                mwOverlayInit(0x01E00000, *(s32 *)0x01E0001C + 0xFE200000);
                cache->group = arg0;
                cache->entry = arg1;
            }
            SzEffect_SetTarget(arg3);
            SzEffect_SetFrom(arg4);
            RhGeom_PushMatrix(0);
            if (arg0 != 1) {
                destination = (void *)(((s64)index << 15) + 0x01E10000);
            }
            result = D_00292FF0[arg0].handlers[arg1](destination, arg2);
            RhGeom_PopMatrix();
            slot->state = 1;
            slot->group = arg0;
            slot->entry = arg1;
            slot->arg2 = arg2;
            slot->arg3 = arg3;
            slot->arg4 = arg4;
            slot->flagA = 0;
            slot->flagB = 0;
            slot->flagC = 0;
            slot->counter = 0;
            slot->timer = 0;
            slot->arg5 = arg5;
            slot->arg6 = arg6;
            if (result == 8) {
                SzEffect_Destroy(index);
                index = -1;
            }
            return index;
        }
        index++;
        slot++;
    } while (index < 24);
    return -1;
}

typedef struct {
    u64 state : 3;
    u64 source : 3;
    u64 target : 10;
    u64 reserved : 48;
} Entry_001F4CB0;

typedef struct {
    u8 state : 3;
    u8 : 5;
    u8 unk1;
    u16 kind : 3;
    u16 value : 10;
    u16 : 3;
    u16 unk4;
    u16 unk6;
    void (*callback)(s32);
    s32 arg;
    s32 unk10;
    s32 unk14;
} Slot_001F4CB0;

typedef struct {
    Entry_001F4CB0 entries[32];
    Slot_001F4CB0 slots[24];
} Data_001F4CB0;


static inline void *find_001F4CB0(s32 source, s32 target) {
    extern Data_001F4CB0 D_0031BB50;
    Entry_001F4CB0 *entry;
    s32 i;

    entry = D_0031BB50.entries;
    for (i = 0; (s64)i < 32; i++, entry++) {
        if ((source < 0 || entry->source == source) && (target < 0 || entry->target == target)) {
            return entry;
        }
    }
    return NULL;
}

s32 SzEffect_Destroy(s32 arg0) {
    extern Data_001F4CB0 D_0031BB50;
    Slot_001F4CB0 *slot = &D_0031BB50.slots[arg0];
    Entry_001F4CB0 *entry;

    if (arg0 < 0 || arg0 >= 24) {
        return 0;
    }
    if (slot->kind == 1 || slot->kind == 2) {
        SzEffect_ClearRefID2(slot->unk6, slot->kind);
        SzEffect_ClearRefID2(slot->unk4, slot->kind);
    }
    slot->state = 0;
    if (slot->callback != NULL) {
        slot->callback(slot->arg);
    }
    entry = find_001F4CB0(slot->kind, slot->value);
    if (entry == NULL) {
        return 1;
    }
    if (entry->state == 2 && SzEffect_IsUse2(entry->source, entry->target) == 0) {
        entry->state = 3;
    }
    return 1;
}

typedef struct Entry_001F4E50 {
    u8 pad0[2];
    u16 category : 3;
    u16 kind : 10;
    u16 reserved : 3;
    u8 pad4[0x14];
} Entry_001F4E50;

extern struct Entry_001F5240 D_0031BC50[];

s32 SzEffect_Destroy2(s32 arg0, s32 arg1) {
    Entry_001F4E50 *var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s0 = (Entry_001F4E50 *)D_0031BC50;
    var_s1 = 0;
    var_s2 = 0;
    do {
        if ((arg0 < 0 || var_s0->category == arg0) &&
            (arg1 < 0 || var_s0->kind == arg1)) {
            var_s1 |= SzEffect_Destroy(var_s2);
        }
        var_s2 += 1;
        var_s0++;
    } while (var_s2 < 0x18);
    return var_s1;
}

typedef struct Entry_001F4F10 {
    u8 state : 3;
    u8 unused0 : 5;
    u8 pad1[2];
    s8 unused3 : 5;
    s8 flag : 1;
    s8 unused4 : 2;
    u8 pad4[0x14];
} Entry_001F4F10;

s32 SzEffect_Sleep(s32 arg0, s32 arg1) {
    extern u8 D_0031BB50[];
    Entry_001F4F10 *entry;
    s32 state;

    entry = (Entry_001F4F10 *)(D_0031BB50 + arg0 * 0x18 + 0x100);
    if ((arg0 < 0) || (arg0 >= 0x18)) {
        return 0;
    }
    state = entry->state;
    if (state == 0) {
        return 0;
    }
    if (arg1 != 0) {
        if (state != 1) {
            return 0;
        }
    } else {
        if (state != 2) {
            return 0;
        }
        entry->state = 1;
    }
    entry->flag = arg1;
    return 1;
}

typedef struct Entry_001F4FD0 {
    u16 unk0;
    u16 category : 3;
    u16 group : 10;
    u16 unused : 3;
    u8 unk4[0x14];
} Entry_001F4FD0;

extern struct Entry_001F5240 D_0031BC50[];

s32 SzEffect_Sleep2(s32 arg0, s32 arg1, s32 arg2) {
    Entry_001F4FD0 *var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s0 = (Entry_001F4FD0 *)D_0031BC50;
    var_s1 = 0;
    var_s2 = 0;
    do {
        if (arg0 < 0 || var_s0->category == arg0) {
            if (arg1 < 0 || var_s0->group == arg1) {
                var_s1 |= SzEffect_Sleep(var_s2, arg2);
            }
        }
        var_s2 += 1;
        var_s0++;
    } while (var_s2 < 0x18);
    return var_s1;
}

typedef struct {
    u8 state : 3;
    u8 : 5;
    u8 unknown1;
    u16 category : 3;
    u16 variant : 10;
    u16 : 3;
    u8 unknown4[20];
} Entry_001F5090;

typedef struct {
    s8 : 6;
    s8 selected : 1;
    s8 : 1;
} Flags_001F5090;

extern struct Entry_001F5240 D_0031BC50[];

static inline s32 act_001F5090(s32 index) {
    extern u8 D_0031BB50[];
    Entry_001F5090 *entry = (Entry_001F5090 *)(D_0031BB50 + 0x100 + index * 0x18);

    if (index < 0 || index >= 24) {
        return 0;
    }
    if (entry->state == 2) {
        return SzEffect_Destroy(index);
    } else if (entry->state != 1) {
        return 0;
    } else {
        ((Flags_001F5090 *)((u8 *)entry + 3))->selected = 1;
        return 1;
    }
}

s32 SzEffect_Erase2(s32 arg0, s32 arg1) {
    Entry_001F5090 *entry;
    s32 result;
    s32 index;

    entry = (Entry_001F5090 *)D_0031BC50;
    result = 0;
    index = 0;
    do {
        if (arg0 < 0 || entry->category == arg0) {
            if (arg1 < 0 || entry->variant == arg1) {
                result |= act_001F5090(index);
            }
        }
        index++;
        entry++;
    } while (index < 24);
    return result;
}

typedef struct Entry_001F51D0 {
    u8 flags;
    u8 pad[0x17];
} Entry_001F51D0;

typedef struct State_001F51D0 {
    u8 pad[0x100];
    Entry_001F51D0 entries[0x18];
} State_001F51D0;

s32 SzEffect_IsUse(s32 arg0) {
    extern State_001F51D0 D_0031BB50;
    Entry_001F51D0 *entry;
    s32 temp_a0;
    s32 var_v0;

    entry = &D_0031BB50.entries[arg0];
    var_v0 = 0;
    if ((arg0 < 0) || (arg0 >= 0x18)) {
        return 0;
    }
    temp_a0 = entry->flags & 7;
    if (temp_a0 == 1) {
        var_v0 |= 1;
    }
    if (temp_a0 == 2) {
        var_v0 |= 2;
    }
    return var_v0;
}

typedef struct Entry_001F5240 {
    u8 state : 3;
    u8 : 5;
    u8 unk1;
    u16 kind : 3;
    u16 value : 10;
    u16 : 3;
    u8 padding[0x14];
} Entry_001F5240;

extern Entry_001F5240 D_0031BC50[];

s32 SzEffect_IsUse2(s32 arg0, s32 arg1) {
    Entry_001F5240 *entry;
    s32 result;
    s32 i;
    s32 state;

    entry = D_0031BC50;
    result = 0;
    i = 0;
    do {
        if (arg0 < 0 || entry->kind == arg0) {
            if (arg1 < 0 || entry->value == arg1) {
                state = entry->state;
                if (state == 1) {
                    result |= 1;
                }
                if (state == 2) {
                    result |= 2;
                }
            }
        }
        i++;
        entry++;
    } while (i < 0x18);
    return result;
}

typedef struct {
    u8 unk00[0x10];
    s32 unk10;
    s32 unk14;
} Entry_001F52D0;

typedef struct {
    u8 unk00[0x100];
    Entry_001F52D0 entries[0x18];
} Data_001F52D0;

extern Data_001F52D0 D_0031BB50;

s32 SzEffect_GetStatus(s32 arg0) {
    Entry_001F52D0 *entry = &D_0031BB50.entries[arg0];
    s32 ret;

    if ((arg0 < 0) || (arg0 >= 0x18)) {
        ret = -1;
    } else {
        ret = entry->unk10;
    }
    return ret;
}

typedef struct Bits_001F5320 {
    u16 state : 3;
    u16 value : 13;
} Bits_001F5320;

s32 SzEffect_GetCount(s32 arg0) {
    Entry_001F52D0 *entry = &D_0031BB50.entries[arg0];

    if ((arg0 < 0) || (arg0 >= 0x18)) {
        return -1;
    }
    return ((Bits_001F5320 *)entry)->value;
}

void SzEffect_SetTarget(s32 arg0) {
    D_0031BE98 = arg0;
}

s32 SzEffect_GetTarget(u8 arg0) {
    return D_0031BE98;
}

void SzEffect_SetFrom(s32 arg0) {
    D_0031BE9C = arg0;
}

s32 SzEffect_GetFrom(u8 arg0) {
    return D_0031BE9C;
}

void SzEffect_GetPos(s32 arg0, s32 arg1) {
    SzEffect_GetPos2(arg0, D_0031BE98, arg1);
}

s32 SzEffect_GetPos2(s32 arg0, s32 arg1, s32 arg2) {
    s32 hi;
    s32 lo;
    f32 *vec;

    vec = (f32 *)arg2;
    hi = arg1 >> 8;
    lo = arg1 & 0xFF;
    vec[2] = 0.0f;
    vec[1] = 0.0f;
    vec[0] = 0.0f;
    vec[3] = 1.0f;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg1 = SzDuel_GetUnitModelID(hi, lo);
    if (arg1 < 0) {
        return 0;
    }
    switch (arg0) {
    case 0:
        return SzDuel_GetCardPos(hi, lo, vec);
    case 1:
        return SzModel_GetCenter(arg1, vec);
    case 2:
        return SzModel_GetPos(8, vec);
    }
    return 0;
}

s32 SzEffect_GetRefNum2(s32 arg0) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return -1;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return -1;
    }
    return SzModel_GetRefNum(arg0);
}

typedef struct {
    u8 unk000[0x340];
    s32 unk340;
} State_001F5560;

s32 SzEffect_SetRefID2(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 SzModel_SetRefID(s32, s32, s32);
    State_001F5560 *state = (State_001F5560 *)&D_0031BB50;
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return -1;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return -1;
    }
    if (arg1 >= 0) {
        arg1 = ((state->unk340 << 8) & 0x7F00) | (arg1 & 0xFF);
    }
    return SzModel_SetRefID(arg0, arg1, arg2);
}

s32 SzEffect_GetRef2(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi = arg0 >> 8;
    s32 lo = arg0 & 0xFF;
    f32 *vec = (f32 *)arg2;

    vec[2] = 0.0f;
    vec[1] = 0.0f;
    vec[0] = 0.0f;
    vec[3] = 1.0f;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_GetRef(arg0, arg1, arg2);
}

s32 SzEffect_ClearRefID2(s32 arg0, s32 arg1) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;
    s32 i;
    s32 value;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        value = SzModel_InqRefID(arg0, i);
        if (value >= 0 && value < 8 && ((value & 0x7F00) >> 8) == arg1) {
            SzModel_SetRefID_RefNo(arg0, -1, i);
        }
    }
    return 1;
}

void SzEffect_SetMaxOT(s32 arg0) {
    SzEffect_SetMaxOT2(D_0031BE9C, arg0);
}

s32 SzEffect_SetMaxOT2(s32 arg0, s32 arg1) {
    s32 SzDuel_GetUnitModelID(s32, s32);
    s32 SzModel_SetMaxOT(s32, s32);
    s32 row;
    s32 column;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 0xB) {
        return 0;
    }
    arg0 = SzDuel_GetUnitModelID(row, column);
    if (arg0 < 0) {
        return 0;
    }
    return SzModel_SetMaxOT(arg0, arg1);
}

void SzEffect_GetRadius(void) {
    SzEffect_GetRadius2(D_0031BE98);
}

f32 SzEffect_GetRadius2(s32 arg0) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return 0.0f;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return 0.0f;
    }
    return SzModel_GetRadius(arg0);
}

s32 SzEffect_GetCamDist2(s32 arg0) {
    extern s32 SzDuel_GetUnitModelID(s32, s32);
    extern s32 SzModel_GetModelNo(s32);
    s32 hi;
    s32 lo;

    hi = arg0 >> 8;
    lo = arg0 & 0xFF;
    if (hi < 0 || hi >= 3 || lo < 0 || lo >= 0xB) {
        return -1;
    }
    arg0 = SzDuel_GetUnitModelID(hi, lo);
    if (arg0 < 0) {
        return -1;
    }
    return SzDuel_GetCamDist(SzDuel_Xax2New(SzModel_GetModelNo(arg0)));
}

s32 SzEffect_SetBusyFlag2(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = arg0 >> 8;
    temp_a1 = arg0 & 0xFF;
    if ((temp_v1 < 0) || (temp_v1 >= 3) ||
        (temp_a1 < 0) || (temp_a1 >= 0xB)) {
        return 0;
    }
    return SzDuel_SetBusyFlag(temp_v1, temp_a1, arg1);
}

s32 SzEffect_SetCardBusyFlag2(s32 arg0, s32 arg1) {
    s32 column;
    s32 row;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return SzDuel_SetCardBusyFlag(row, column, arg1);
}

s32 SzEffect_SetCardColBusyFlag2(s32 arg0, s32 arg1) {
    s32 row;
    s32 column;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return SzDuel_SetCardColBusyFlag(row, column, arg1);
}

s32 SzEffect_SetModelBusyFlag2(s32 arg0, s32 arg1) {
    s32 column;
    s32 row;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return SzDuel_SetModelBusyFlag(row, column, arg1);
}

s32 SzEffect_IsCardStandby2(s32 arg0) {
    s32 temp_v0;

    temp_v0 = SzDuel_GetUnit(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 == 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)temp_v0 + 4) != 0) ? 1 : 0;
}

s32 SzEffect_GetCardRequest2(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = (s32 *)SzDuel_GetUnit(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 == 0) {
        return 0;
    }
    return temp_v0[1];
}

s32 SzEffect_SetCardPos2(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = arg0 >> 8;
    temp_a1 = arg0 & 0xFF;
    if (temp_v1 < 0 || temp_v1 >= 3 || temp_a1 < 0 || temp_a1 >= 0xB) {
        return 0;
    }
    return SzDuel_SetCardPos(temp_v1, temp_a1, arg1);
}

typedef struct Vec4_001F5BD0 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001F5BD0;


s32 SzEffect_GetCardPos2(s32 arg0, void *arg1) {
    s32 index;
    s32 group;
    Vec4_001F5BD0 *out = arg1;

    group = arg0 >> 8;
    index = arg0 & 0xFF;
    out->z = 0.0f;
    out->y = 0.0f;
    out->x = 0.0f;
    out->w = 1.0f;
    if (group < 0 || group >= 3 || index < 0 || index >= 11) {
        return 0;
    }
    return SzDuel_GetCardPos(group, index, out);
}

s32 SzEffect_SetCardRot2(s32 arg0, s32 arg1) {
    s32 column;
    s32 row;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if ((row < 0) || (row >= 3) || (column < 0) || (column >= 11)) {
        return 0;
    }
    return SzDuel_SetCardRot(row, column, arg1);
}

s32 SzEffect_GetCardRot2(s32 arg0, void *arg1) {
    s32 row = arg0 >> 8;
    s32 column = arg0 & 0xFF;
    s32 *out = arg1;

    out[3] = 0;
    out[2] = 0;
    out[1] = 0;
    out[0] = 0;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return SzDuel_GetCardRot(row, column, arg1);
}

s32 SzEffect_SetCardScale2(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = arg0 >> 8;
    temp_a1 = arg0 & 0xFF;
    if (temp_v1 < 0 || temp_v1 >= 3 || temp_a1 < 0 || temp_a1 >= 0xB) {
        return 0;
    }
    return SzDuel_SetCardScale(temp_v1, temp_a1, arg1);
}

typedef struct {
    f32 x, y, z, w;
} Vec4_001F5D70;


s32 SzEffect_GetCardScale2(s32 arg0, void *arg1) {
    Vec4_001F5D70 *out = (Vec4_001F5D70 *)arg1;
    s32 a = arg0 >> 8;
    s32 b = arg0 & 0xFF;

    out->z = 0.0f;
    out->y = 0.0f;
    out->x = 0.0f;
    out->w = 1.0f;
    if (a < 0 || a >= 3 || b < 0 || b >= 0xB) {
        return 0;
    }
    return SzDuel_GetCardScale(a, b, out);
}

s32 SzEffect_SetCardRgba2(s32 arg0, s32 arg1) {
    s32 row;
    s32 column;

    row = arg0 >> 8;
    column = arg0 & 0xFF;
    if (row < 0 || row >= 3 || column < 0 || column >= 11) {
        return 0;
    }
    return SzDuel_SetCardRgba(row, column, arg1);
}

s32 SzEffect_GetCardRgba2(s32 arg0, u8 *arg1) {
    s32 index;
    s32 bank;

    bank = arg0 >> 8;
    index = arg0 & 0xFF;
    arg1[3] = 0x80;
    arg1[0] = 0x80;
    arg1[1] = 0x80;
    arg1[2] = 0x80;
    if (bank < 0 || bank >= 3 || index < 0 || index >= 11) {
        return 0;
    }
    return SzDuel_GetCardRgba(bank, index, arg1);
}

s32 SzEffect_IsModelStandby(void) {
    return SzEffect_IsModelStandby2(D_0031BE98);
}

s32 SzEffect_IsModelStandby2(s32 arg0) {
    s32 temp_v0;

    temp_v0 = SzDuel_GetUnit(arg0 >> 8, arg0 & 0xFF);
    if (temp_v0 != 0) {
        return SzModel_IsModelDisp(*((u8 *)temp_v0 + 0x46));
    }
    return 0;
}
