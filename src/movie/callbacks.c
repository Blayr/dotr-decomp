/* Movie player: the video and PCM callbacks. */

#include "common.h"

typedef struct Buffer_00242D10 {
    s32 unk0;
    s32 unk4;
    u8 *data;
    u32 size;
    s64 unk10;
    s64 unk18;
} Buffer_00242D10;

typedef struct Ring_00242D10 {
    u8 pad[0x50008];
    s32 capacity;
} Ring_00242D10;

/* The MPEG library's video-stream callback: queues the stream data for the video decoder. */
s32 videoCallback(s32 mp, void *str, u8 *dataIn) {
    extern s32 videoDecPutTs();
    extern char D_0030F5E0[];
    Ring_00242D10 *ring;
    Buffer_00242D10 *buffer;
    u8 *data;
    u32 avail;
    u32 first;
    u32 rest;
    s32 dst1;
    s32 dst2;
    s32 dstSize1;
    s32 dstSize2;
    s32 result;

    ring = (Ring_00242D10 *)dataIn;
    buffer = (Buffer_00242D10 *)str;
    data = buffer->data;
    avail = (u8 *)ring + ring->capacity - data;
    first = buffer->size;
    first = (first < avail) ? first : avail;
    rest = ((Buffer_00242D10 *)str)->size - first;
    videoDecBeginPut(videoDec, &dst1, &dstSize1, &dst2, &dstSize2);
    result = copy2area((void *)((dst1 & 0x0FFFFFFF) | 0x20000000), dstSize1,
                           (void *)((dst2 & 0x0FFFFFFF) | 0x20000000), dstSize2,
                           data, first, ring, rest);
    if (result > 0 && videoDecPutTs(videoDec, ((Buffer_00242D10 *)str)->unk10,
                                    ((Buffer_00242D10 *)str)->unk18, dst1, result) == 0) {
        ErrMessage(D_0030F5E0);
    }
    videoDecEndPut(videoDec, result);
    return (result > 0) ? 1 : 0;
}

typedef struct Buffer_00242E40 {
    s32 unk0;
    s32 unk4;
    u8 *data;
    s32 size;
} Buffer_00242E40;

typedef struct Ring_00242E40 {
    u8 pad[0x50008];
    s32 capacity;
} Ring_00242E40;

/* The MPEG library's PCM-stream callback: queues the audio data for the audio decoder. */
s32 pcmCallback(s32 mp, void *str, u8 *dataIn) {
    u8 *data;
    s32 size;
    s32 firstSize;
    void *dst1;
    void *dst2;
    s32 dstSize1;
    s32 dstSize2;
    s32 capacity;
    u8 *end;
    s32 result;

    data = ((Buffer_00242E40 *)str)->data + 4;
    capacity = ((Ring_00242E40 *)dataIn)->capacity;
    end = dataIn + capacity;
    if (data >= end) {
        data -= capacity;
    }
    size = ((Buffer_00242E40 *)str)->size - 4;
    firstSize = end - data;
    if (size < firstSize) {
        firstSize = size;
    }
    audioDecBeginPut(audioDec, &dst1, &dstSize1, &dst2, &dstSize2);
    result = copy2area(dst1, dstSize1, dst2, dstSize2,
                          data, firstSize, dataIn, size - firstSize);
    audioDecEndPut(audioDec, result);
    if (result > 0) {
        return 1;
    }
    return 0;
}

/* Copies two source areas (ps0/s0, ps1/s1) into two destination areas (pd0/d0, pd1/d1), as far as they fit. */
s32 copy2area(void *pd0, s32 d0, void *pd1, s32 d1,
                  void *ps0, s32 s0, void *ps1, s32 s1) {
    s32 gap;

    if ((d0 + d1) < (s0 + s1)) {
        return 0;
    }
    if (s0 >= d0) {
        func_00198790(pd0, ps0, d0);
        func_00198790(pd1, (const u8 *)ps0 + d0, s0 - d0);
        func_00198790((u8 *)pd1 + s0 - d0, ps1, s1);
    } else {
        gap = d0 - s0;
        if (s1 >= gap) {
            func_00198790(pd0, ps0, s0);
            func_00198790((u8 *)pd0 + s0, ps1, gap);
            func_00198790(pd1, (const u8 *)ps1 + d0 - s0, s1 - gap);
        } else {
            func_00198790(pd0, ps0, s0);
            func_00198790((u8 *)pd0 + s0, ps1, s1);
        }
    }
    return s0 + s1;
}
