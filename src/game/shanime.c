/* 2D animation data (ShAnime_*). */

#include "common.h"

typedef struct Quad_00245980 {
    s16 x;
    s16 y;
    s16 z;
    s16 w;
} Quad_00245980;

extern Quad_00245980 **faceSetIndex[]; /* original: gpShFaceIndex */

/* The texture rectangle of part `part` of face set `face` into `out`. */
void ShAnime_GetPartsRect(s32 face, s32 part, void *out) {
    *(Quad_00245980 *)out = (*faceSetIndex[(u8)face])[(u8)part];
}

typedef struct Name_002459D0 {
    u8 text[8];
} Name_002459D0;

/* Pattern `pattern` of face set `face` into `out`. */
void ShAnime_GetPatInfo(u8 face, u8 pattern, void *out) {
    *(Name_002459D0 *)out = ((Name_002459D0 **)faceSetIndex[face])[1][pattern];
}

typedef struct Record_00245A30 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Record_00245A30;

typedef struct Data_00245A30 {
    s32 unk0;
    u8 (*indices)[8];
    Record_00245A30 *records;
} Data_00245A30;

/* The fixed record of animation `anim` of face set `face`, `step` links on, into `out`. */
void ShAnime_GetFixInfo(s32 face, s32 anim, s32 step, void *out) {
    extern struct Quad_00245980 **faceSetIndex[];
    u8 link;
    u8 next;
    Record_00245A30 *records;
    s32 i;

    i = 0;
    link = ((Data_00245A30 *)faceSetIndex[face & 0xFF])->indices[anim & 0xFF][1];
    if (step != 0) {
        records = ((Data_00245A30 *)faceSetIndex[face & 0xFF])->records;
        while (i != (step & 0xFF)) {
            next = *(u8 *)&records[link & 0xFF];
            if (next == 0 || next == 0xFF) {
                break;
            }
            i += 1;
            link = next & 0xFF;
        }
    }
    *(Record_00245A30 *)out = ((Data_00245A30 *)faceSetIndex[face & 0xFF])->records[link & 0xFF];
}

typedef struct Record_00245AE0 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Record_00245AE0;

typedef struct Data_00245AE0 {
    s32 unk0;
    u8 (*indices)[8];
    union {
        Record_00245AE0 *records;
        u8 (*links)[8];
    } u;
} Data_00245AE0;

/* The animation record of animation `anim` of face set `face`, `step` and then `frame` links on, into `out`. */
void ShAnime_GetAnmDat(s32 face, s32 anim, s32 step, s32 frame, void *out) {
    extern struct Quad_00245980 **faceSetIndex[];
    Record_00245AE0 *table;
    u8 link;
    u8 next;
    Record_00245AE0 *records;
    s32 i;
    s32 count;

    i = 0;
    link = ((Data_00245AE0 *)faceSetIndex[face & 0xFF])->indices[anim & 0xFF][1];
    if (step != 0) {
        records = ((Data_00245AE0 *)faceSetIndex[face & 0xFF])->u.records;
        while (i != (step & 0xFF)) {
            next = *(u8 *)&records[link & 0xFF];
            if (next == 0 || next == 0xFF) {
                break;
            }
            i += 1;
            link = next & 0xFF;
        }
    }
    i = ((Data_00245AE0 *)faceSetIndex[face & 0xFF])->u.links[link & 0xFF][6];
    table = ((Data_00245AE0 *)faceSetIndex[face & 0xFF])->u.records;
    count = 0;
    if (frame != 0) {
        while (count != (frame & 0xFF)) {
            next = *(u8 *)&table[i & 0xFF];
            if (next == 0 || next == 0xFF) {
                break;
            }
            count += 1;
            i = next & 0xFF;
        }
    }
    *(Record_00245AE0 *)out = table[i & 0xFF];
}
