/* Movie player: the video decoder. */

#include "common.h"

/* Sets up the movie's video decoder with its MPEG work area, the input FIFO areas and timestamps. */
s32 videoDecCreate(void *vd, s32 mpegWork, s32 mpegWorkSize, s32 data, u32 tag, s32 tagSize, s32 pts, s32 n_pts) {
    sceMpegCreate(vd, mpegWork, mpegWorkSize);
    sceMpegAddCallback(vd, 0, mpegError, 0);
    sceMpegAddCallback(vd, 1, mpegNodata, 0);
    sceMpegAddCallback(vd, 2, mpegStopDMA, 0);
    sceMpegAddCallback(vd, 3, mpegRestartDMA, 0);
    sceMpegAddCallback(vd, 5, (s32 (*)()) mpegTS, 0);
    videoDecReset(vd);
    viBufCreate((u8 *)vd + 0x48, data, tag, tagSize, pts, n_pts);
    return 1;
}

/* Hooks the video and audio streams to the decoders. */
s32 videoDecSetStream(void) {
    extern s32 sceMpegAddStrCallback();

    sceMpegAddStrCallback();
    return 1;
}

/* Where the next video data can go (ptr0/len0, ptr1/len1). */
void videoDecBeginPut(void *vd, s32 *ptr0, s32 *len0, s32 *ptr1, s32 *len1) {
    viBufBeginPut((u8 *)vd + 0x48, ptr0, len0, ptr1, len1);
}

/* Marks `size` bytes of video data as put. */
void videoDecEndPut(void *vd, s32 size) {
    viBufEndPut((u8 *)vd + 0x48, size);
}

/* Resets the movie's video decoder. */
void videoDecReset(void *vd) {
    *(s32 *)((u8 *)vd + 0xA8) = 0;
}

/* Frees the movie's video decoder. */
s32 videoDecDelete(u8 *vd) {
    s32 sceMpegDelete(void *);

    viBufDelete(vd + 0x48);
    sceMpegDelete(vd);
    return 1;
}

/* Stops the movie's video decoder. */
void videoDecAbort(void *vd) {
    *(s32 *)((u8 *)vd + 0xA8) = 1;
}

/* The movie video decoder's state. */
s32 videoDecGetState(void *vd) {
    return *(s32 *)((u8 *)vd + 0xA8);
}

typedef struct Values_00245160 {
    s64 first;
    s64 second;
    s32 offset;
    s32 fourth;
} Values_00245160;

extern u8 D_003506C8[];

/* Records a video timestamp (pts, dts) for stream position `pos` of `len` bytes. */
s32 videoDecPutTs(void *vd, s64 pts, s64 dts, s32 pos, s32 len) {
    Values_00245160 values;

    values.first = pts;
    values.second = dts;
    values.offset = pos - *(s32 *)((u8 *)vd + 0x48);
    values.fourth = len;
    return viBufPutTs(D_003506C8, &values);
}

typedef struct {
    u8 pad00[0x48];
    u8 unk48[0x60];
    s32 unkA8;
} Obj_002451A0;

typedef struct {
    f32 v;
} Flt_002451A0;

extern Flt_002451A0 D_0029B300;

/* Flushes the movie video decoder's data. */
s32 videoDecFlush(void *vd) {
    Obj_002451A0 *p = (Obj_002451A0 *)vd;
    s32 sp2C;
    s32 sp30;
    Flt_002451A0 sp34;
    s32 sp38;
    s32 sp3C;

    sp34 = D_0029B300;
    viBufBeginPut(p->unk48, &sp2C, &sp38, &sp30, &sp3C);
    if ((sp38 + sp3C) < 4) {
        return 0;
    }
    viBufEndPut(D_003506C8, cpy2area((sp2C & 0xFFFFFFF) | 0x20000000, sp38, (sp30 & 0xFFFFFFF) | 0x20000000, sp3C, &sp34, 4, 0, 0));
    viBufFlush(p->unk48);
    if (p->unkA8 == 0) {
        p->unkA8 = 2;
    }
    return 1;
}

/* Whether the movie video decoder has flushed. */
s32 videoDecIsFlushed(void *vd) {
    s32 result;

    result = 0;
    if (viBufCount((u8 *)vd + 0x48) == 0) {
        if (sceMpegIsRefBuffEmpty(vd) != 0) {
            result = 1;
        }
    }
    return result;
}

/* The movie video decoder's thread: decodes pictures until the end. */
void videoDecMain(void *vd) {
    viBufReset((u8 *)vd + 0x48);
    voBufReset(voBuf);
    decBs0(vd);
    do {

    } while (D_0035060C != 0);
    *(s32 *)((u8 *)vd + 0xA8) = 3;
}

extern int func_00199B50_b(const char *format, ...);
typedef int DotrSoundAddress;
struct DotrSoundBig {
    int state;
    unsigned char unknown_04[60];
    unsigned int tags[2][0x99c0]; 
};
struct DotrSoundBigQueue {
    unsigned char (*images)[0x195000]; 
    struct DotrSoundBig *items;
    int index;
    int count;
    int capacity;
};
struct DotrSoundVideoDec {
    int width;
    int height;
    int frame_count;
    int unknown_0c[39];
    int state;
};
extern struct DotrSoundBigQueue D_00350600_b;
extern char D_0030F8B0[];
extern char D_0030F8C8[];
extern int func_0018EE78_b(struct DotrSoundVideoDec *dec);
extern void func_00242CF0_b(DotrSoundAddress text);
extern void func_00241E80_b(unsigned int *tags, void *image, int index, int w, int h);

/* Decodes the movie's video stream (one call of the MPEG library). */
int decBs0(void *dec_v)
{
    struct DotrSoundVideoDec * dec = dec_v;
    int ret;
    DotrSoundAddress data;
    int i;
    int w;
    int h;

    ret = 1;
    while (sceMpegIsEnd(dec) == 0) {
        if (dec->state == 1) {
            ret = -1;
            func_00199B50_b(D_0030F8B0);
            break;
        }
        while ((data = voBufGetData(&D_00350600_b)) == 0) {
            switchThread();
        }
        if (sceMpegGetPicture(dec, data, 0x654) < 0) {
            func_00242CF0_b((DotrSoundAddress)D_0030F8C8);
        }
        if (dec->frame_count == 0) {
            w = dec->width;
            h = dec->height;
            for (i = 0; i < D_00350600_b.capacity; i++) {
                func_00241E80_b(D_00350600_b.items[i].tags[0], D_00350600_b.images[i], 0, w, h);
                func_00241E80_b(D_00350600_b.items[i].tags[1], D_00350600_b.images[i], 1, w, h);
            }
        }
        voBufIncCount(&D_00350600_b);
        switchThread();
    }
    func_0018EE78_b(dec);
    return ret;
}

/* The MPEG library's error callback. */
s32 mpegError(void *mp, void *data) {
    func_00199B50(&D_0030F8E9, *(s32 *)((u8 *)data + 4));
    return 1;
}

/* The MPEG library's no-data callback: waits for input. */
s32 mpegNodata(void) {
    switchThread();
    viBufAddDMA(D_003506C8);
    return 1;
}

/* The MPEG library's stop-DMA callback. */
s32 mpegStopDMA(void) {
    viBufStopDMA(D_003506C8);
    return 1;
}

/* The MPEG library's restart-DMA callback. */
s32 mpegRestartDMA(void) {
    viBufRestartDMA(D_003506C8);
    return 1;
}

typedef struct Entry_002455E0 {
    s64 values[2];
    s32 offset;
    s32 size;
} Entry_002455E0;

/* The MPEG library's timestamp callback: hands it the next video timestamp. */
s32 mpegTS(s32 mp, void *cbData) {
    Entry_002455E0 entry;

    viBufGetTs(D_003506C8, &entry);
    *(s64 *)((u8 *)cbData + 8) = entry.values[0];
    *(s64 *)((u8 *)cbData + 0x10) = entry.values[1];
    return 1;
}

/* Copies two source areas into two destination areas (the decoded pictures' ring); returns the size copied, 0 if
   it does not fit. */
s32 cpy2area(s32 pd0, s32 d0, s32 pd1, s32 d1,
                  void *ps0, s32 s0, s32 ps1, s32 s1) {
    s32 rest;
    s32 total;

    total = s0 + s1;
    if ((d0 + d1) < total) {
        return 0;
    }
    if (s0 >= d0) {
        func_00198790((u8 *)pd0, ps0, d0);
        func_00198790((u8 *)pd1, (u8 *)ps0 + d0, s0 - d0);
        func_00198790(((u8 *)pd1 + s0) - d0, (u8 *)ps1, s1);
    } else {
        rest = d0 - s0;
        if (s1 >= rest) {
            func_00198790((u8 *)pd0, ps0, s0);
            func_00198790((u8 *)pd0 + s0, (u8 *)ps1, rest);
            func_00198790((u8 *)pd1, ((u8 *)ps1 + d0) - s0, s1 - rest);
        } else {
            func_00198790((u8 *)pd0, ps0, s0);
            func_00198790((u8 *)pd0 + s0, (u8 *)ps1, s1);
        }
    }
    return total;
}
