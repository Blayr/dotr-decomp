#ifndef SCE_LIBMPEG_H
#define SCE_LIBMPEG_H

/* Sony libmpeg records. Adapted from the ICO decompilation via kfiv-decomp (MIT), see
 * THIRD_PARTY_NOTICES.md. */

/* the decoder handle: picture size and count, time stamps, and the decoder's own record */
typedef struct sceMpeg {
    s32 width, height, frameCount, pad0C;
    s64 pts, dts;
    s64 flags;
    s64 pts2nd, dts2nd;
    s64 flags2nd;
    struct MpegSys *sys; /* 0x40 */
} sceMpeg;

typedef s32 (*sceMpegCallback)(sceMpeg *mp, void *cbdata, void *anyData);

/* one entry of the callback table, by callback type */
typedef struct {
    sceMpegCallback func;
    void *data;
} MpegCb;

/* one demux callback: the stream id, the id bits that take part in the match, the handler */
typedef struct StrCb {
    s64 id;
    u64 mask;
    sceMpegCallback func;
    void *arg;
} StrCb;

/* the head of the decoder's record (the fields used so far) */
typedef struct MpegSys {
    s32 isEnd;     /* 0x000 */
    s32 refCount;  /* 0x004 */
    s32 outState;  /* 0x008 */
    MpegCb cb[7];  /* 0x00C */
    StrCb *strCb;  /* 0x044 */
    s32 nStrCb;    /* 0x048 */
} MpegSys;

/* the PSS stream descriptors: an id template and the mask of its stream-number bits */
typedef struct {
    u64 id;
    u64 mask;
} StrDesc;

extern StrDesc _strmap[10];

#endif
