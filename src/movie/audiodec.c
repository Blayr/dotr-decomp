/* Movie player: the audio decoder. */

#include "common.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x28];
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
} State_00243060;

extern char D_0030F600[];
extern char D_0030F61C[];
extern u8 _0_buf[];

/* Sets up the movie's audio decoder with buffer `buff` of `buffSize` and an IOP buffer of `iopBuffSize`. */
s32 audioDecCreate(void *ad, s32 buff, s32 buffSize, s32 iopBuffSize) {
    State_00243060 *state = ad;
    s32 unk44;
    s32 unk58;

    state->unk0 = 0;
    state->unk2C = 0;
    state->unk30 = buff;
    state->unk34 = 0;
    state->unk38 = 0;
    state->unk3C = buffSize;
    state->unk40 = 0;
    state->unk54 = 0;
    state->unk48 = iopBuffSize;
    state->unk4C = 0;
    state->unk50 = 0;
    state->unk44 = sceSifAllocIopHeap(iopBuffSize);
    unk44 = state->unk44;
    if (unk44 < 0) {
        func_00199B50(D_0030F600, unk44);
        return 0;
    }
    func_00199B50(D_0030F61C, unk44, iopBuffSize);
    state->unk58 = sceSifAllocIopHeap(0x800);
    unk58 = state->unk58;
    if (unk58 < 0) {
        func_00199B50(D_0030F600, unk58);
        return 0;
    }
    func_00199B50(D_0030F61C, unk58, 0x800);
    func_00198948(_0_buf, 0, 0x800U);
    sendToIOP(state->unk58, (s32) _0_buf, 0x800);
    changeMasterVolume(0x3FFF);
    return 1;
}

/* Frees the movie's audio decoder. */
s32 audioDecDelete(void *ad) {
    func_00182A28(*(s32 *)((u8 *)ad + 0x44));
    func_00182A28(*(s32 *)((u8 *)ad + 0x58));
    changeMasterVolume(0);
    return 1;
}

/* Pauses the movie's audio. */
void audioDecPause(void *ad) {
    s32 *p = (s32 *)ad;
    s32 func_00190810(s32, ...);

    p[0] = 3;
    changeInputVolume(0);
    p[0x14] = (func_00190810(1, 0x80E0, 0, 2, 0, 0) & 0xFFFFFF) - p[0x11];
    func_00190810(1, 0x80D0, 0, 0, p[0x16], 0x4000, 0x800);
}

/* Resumes the movie's audio. */
void audioDecResume(void *ad) {
    s32 *p = (s32 *)ad;
    s32 func_00190810(s32, s32, s32, s32, s32, s32, s32);
    changeInputVolume(0x7FFF);
    func_00190810(1, 0x80E0, 0, 0x13, p[0x11], (p[0x12] >> 10) << 10, p[0x11] + p[0x14]);
    *(s32 *)ad = 2;
}

/* Starts the movie's audio. */
void audioDecStart(void *ad) {
    s32 *p = (s32 *)ad;
    s32 func_00190810(s32, s32, s32, s32, s32, s32, s32);
    changeInputVolume(0x7FFF);
    func_00190810(1, 0x80E0, 0, 0x13, p[0x11], (p[0x12] >> 10) << 10, p[0x11] + p[0x14]);
    *(s32 *)ad = 2;
}

/* Resets the movie's audio decoder. */
void audioDecReset(void *ad) {
    s32 *p = (s32 *)ad;
    s32 func_00190810(s32, ...);

    p[0] = 3;
    changeInputVolume(0);
    p[0x14] = (func_00190810(1, 0x80E0, 0, 2, 0, 0) & 0xFFFFFF) - p[0x11];
    func_00190810(1, 0x80D0, 0, 0, p[0x16], 0x4000, 0x800);
    p[0] = 0;
    p[0xB] = 0;
    p[0xD] = 0;
    p[0xE] = 0;
    p[0x10] = 0;
    p[0x15] = 0;
    p[0x13] = 0;
    p[0x14] = 0;
}

typedef struct {
    s32 mode;
    u8 data[0x28];
    s32 offset;
    u8 *buffer;
    s32 start;
    s32 end;
    s32 capacity;
} Buffer_00243390;

/* Where the next audio data can go (two areas: ptr0/len0, ptr1/len1). */
void audioDecBeginPut(void *ad, void **ptr0, s32 *len0, void **ptr1, s32 *len1) {
    s32 available;
    s32 capacity;
    s32 start;
    Buffer_00243390 *buffer = ad;

    if (buffer->mode == 0) {
        *ptr0 = (void *)((u32)buffer->data + buffer->offset);
        *len0 = 0x28 - buffer->offset;
        *ptr1 = buffer->buffer;
        *len1 = buffer->capacity;
    } else {
        available = (capacity = buffer->capacity) - buffer->end;
        start = buffer->start;
        if ((capacity - start) >= available) {
            *ptr0 = buffer->buffer + start;
            *len0 = available;
            *ptr1 = 0;
            *len1 = 0;
        } else {
            *ptr0 = buffer->buffer + start;
            *len0 = buffer->capacity - buffer->start;
            *ptr1 = buffer->buffer;
            *len1 = available - (buffer->capacity - buffer->start);
        }
    }
}

typedef struct State_00243450 {
    s32 printed;
    s8 byteParams[4];
    s32 wordParams[7];
    s8 moreByteParams[4];
    s32 moreWordParam;
    u32 delay;
    s32 unused;
    s32 position;
    s32 elapsed;
    s32 period;
    s32 total;
} State_00243450;

extern char D_0030F645[];
extern char D_0030F676[];
extern char D_0030F7B1[];

/* Marks `size` bytes of audio data as put. */
void audioDecEndPut(void *ad, u32 size) {
    u32 amount;
    State_00243450 *state;

    state = ad;
    if (state->printed == 0) {
        amount = 0x28 - state->delay;
        amount = amount < size ? amount : size;
        state->delay += amount;
        if (state->delay >= 0x28U) {
            state->printed = 1;
            func_00199B50(D_0030F645);
            func_00199B50(D_0030F676,
                state->byteParams[0], state->byteParams[1],
                state->byteParams[2], state->byteParams[3],
                state->wordParams[0], state->wordParams[1],
                state->wordParams[2], (s64)state->wordParams[3],
                (s64)state->wordParams[4], (s64)state->wordParams[5],
                (s64)state->wordParams[6]);
            func_00199B50(D_0030F7B1,
                state->moreByteParams[0], state->moreByteParams[1],
                state->moreByteParams[2], state->moreByteParams[3],
                state->moreWordParam);
        }
        size -= amount;
    }
    state->position = (s32)(state->position + size) % state->period;
    state->elapsed += size;
    state->total += size;
}

/* Whether the audio buffer has filled enough to start. */
s32 audioDecIsPreset(void *ad) {
    return *(s32 *)((u8 *)ad + 0x54) >= *(s32 *)((u8 *)ad + 0x48);
}

typedef struct Stream_002435A0 {
    s32 kind;
    u8 pad04[0x2C];
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    u8 pad40[4];
    s32 f44;
    s32 f48;
    s32 f4C;
    u8 pad50[4];
    s32 f54;
} Stream_002435A0;

/* Sends decoded audio to the IOP's buffer. */
s32 audioDecSendToIOP(void *ad) {
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 result = 0;
    s32 pos;
    s32 avail;
    s32 first;
    s32 rest;
    Stream_002435A0 *st;

    extern s32 func_00190810(s32, ...);

    st = ad;
    switch (st->kind) {
    case 0:
        return 0;
    case 1:
        sp30 = st->f44 + (st->f54 % st->f48);
        sp38 = st->f48 - st->f54;
        sp34 = 0;
        sp3C = 0;
        break;
    case 2:
        iopGetArea(&sp30, &sp38, &sp34, &sp3C, st, (func_00190810(1, 0x8100, 0) & 0xFFFFFF) - st->f44);
        break;
    case 3:
        return 0;
    }

    pos = st->f30 + (st->f3C + (st->f34 - st->f38)) % st->f3C;
    avail = (st->f38 >> 10) << 10;
    first = st->f30 + st->f3C - pos;
    if (avail < first) {
        first = avail;
    }
    rest = avail - first;
    if (sp38 + sp3C >= 0x400 && first + rest >= 0x400) {
        result = sendToIOP2area(sp30, sp38, sp34, sp3C, pos, first, st->f30, rest);
    }
    st->f38 = st->f38 - result;
    st->f54 = st->f54 + result;
    st->f4C = (st->f4C + result) % st->f48;
    return result;
}

typedef struct Range_00243750 {
    u8 padding[0x44];
    s32 start;
    s32 length;
    s32 cursor;
} Range_00243750;

/* The free areas of the IOP audio buffer from position `offset` (pd0/d0, pd1/d1). */
void iopGetArea(s32 *pd0, s32 *d0, s32 *pd1, s32 *d1, void *ad, s32 offset) {
    Range_00243750 *range = ad;
    s32 length = range->length;
    s32 cursor = range->cursor;

    offset = (((offset + length - cursor - 0x400) % length) >> 10) << 10;
    if (length - cursor >= offset) {
        *pd0 = range->start + cursor;
        *d0 = offset;
        *pd1 = 0;
        *d1 = 0;
    } else {
        *pd0 = range->start + cursor;
        *d0 = range->length - range->cursor;
        *pd1 = range->start;
        *d1 = offset - (range->length - range->cursor);
    }
}

/* Sends two source areas into two IOP areas. */
s32 sendToIOP2area(s32 pd0, s32 d0, s32 pd1, s32 d1,
                  s32 ps0, s32 s0, s32 ps1, s32 s1) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;

    temp_v0 = d0 + d1;
    temp_v1 = s0 + s1;
    if (temp_v0 < temp_v1) {
        temp_v1_2 = temp_v1 - temp_v0;
        if (temp_v1_2 >= s1) {
            s0 -= temp_v1_2 - s1;
            s1 = 0;
        } else {
            s1 -= temp_v1_2;
        }
    }
    if (s0 >= d0) {
        sendToIOP(pd0, ps0, d0);
        sendToIOP(pd1, ps0 + d0, s0 - d0);
        sendToIOP((pd1 + s0) - d0, ps1, s1);
    } else {
        temp_s0 = d0 - s0;
        if (s1 >= temp_s0) {
            sendToIOP(pd0, ps0, s0);
            sendToIOP(pd0 + s0, ps1, temp_s0);
            sendToIOP(pd1, (ps1 + d0) - s0, s1 - temp_s0);
        } else {
            sendToIOP(pd0, ps0, s0);
            sendToIOP(pd0 + s0, ps1, s1);
        }
    }
    return s0 + s1;
}

/* Sends `size` bytes from `src` to IOP address `dst`. */
s32 sendToIOP(s32 dst, s32 src, s32 size) {
    s32 request[4];
    s32 id;

    if (size <= 0) {
        return 0;
    }
    request[0] = src;
    request[1] = dst;
    request[2] = size;
    request[3] = 0;
    FlushCache(0);
    id = sceSifSetDma(request, 1);
    do {

    } while (sceSifDmaStat(id) >= 0);
    return size;
}

/* Sets the movie's master volume. */
void changeMasterVolume(s32 val) {
    s32 i;

    i = 0;
    do {
        func_00190810(1, 0x8010, i | 0x980, val);
        func_00190810(1, 0x8010, i | 0xA80, val);
        i += 1;
    } while (i < 2);
}

/* Sets the movie's audio input volume. */
void changeInputVolume(s32 val) {
    func_00190810(1, 0x8010, 0xF80, val);
    func_00190810(1, 0x8010, 0x1080, val);
}
