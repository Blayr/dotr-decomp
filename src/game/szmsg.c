/* Message boxes and their font (SzMsg_*). */

#include "common.h"

/* Clears the message system. */
void SzMsg_Initialize(void) {
    extern u8 textState[];

    RhMem_FillMemory((s8 *)textState, 0, 0x27C);
}

/* Starts the message system with palette `palette` at GS address `address`. */
s32 SzMsg_Init(s32 palette, s32 address) {
    s32 sp3C;

    RhBase_SetVifPacketArea(SzMsg_Init_Pipe(RhBase_GetVifPacketArea(), palette, address, &sp3C));
    return sp3C;
}

typedef struct State_001FD320 {
    s32 width;
    s32 height;
    s32 tw;
    s32 th;
    s32 cbp;
    s32 tbp;
    s32 cbpOffset;
    u8 pad1C[0x258];
    s32 unk274;
    u16 unk278;
} State_001FD320;

/* Starts the message system: the 640x384 text texture, its palettes at GS address `address`; the GS memory it took
   through `outSize`. */
s32 SzMsg_Init_Pipe(s32 packet, s32 palette, s32 address, s32 *outSize) {
    extern State_001FD320 textState;
    extern s32 D_002D19D0;
    extern u16 StringBlob[];
    extern s32 SzText_InitClutManage();
    extern s32 SzMsg_LoadClut_Pipe();
    State_001FD320 *state = &textState;
    s32 start;
    s32 i;
    s32 tw;
    s32 th;

    start = address;
    SzMsg_FreeAll();
    textState.width = 640;
    textState.height = 384;
    for (tw = 0; (1 << tw) < 640; tw++) {
    }
    for (th = 0; (1 << th) < 384; th++) {
    }
    state->tw = tw;
    state->th = th;
    state->cbp = SzText_GetClutGsAddr(3);
    if (state->cbp < 0) {
        address += SzText_InitClutManage(address, 1);
        state->cbp = SzText_GetClutGsAddr(3);
    }
    state->tbp = address;
    for (i = 0; i < 3; i++) {
        packet = SzMsg_LoadClut_Pipe(packet, i, state->cbp + i);
    }
    if (outSize != NULL) {
        *outSize = address + 0x1E0 - start;
    }
    state->cbpOffset = palette;
    state->unk274 = 0xFFFFFB;
    state->unk278 = StringBlob[D_002D19D0] & 0x1FFF;
    return packet;
}

/* Sets the depth messages are drawn at. */
void SzMsg_SetDefPrioZ(s32 z) {
    Msg_DefPrioZ = z;
}

typedef union Packet_001FD4C0 {
    u64 words[14];
    struct {
        u16 count;
        u8 pad02;
        u8 flag;
        u32 pad04;
        u32 dma0;
        u32 dma1;
    } header;
} Packet_001FD4C0;

/* Loads text palette `index` into GS memory at `address`. */
s32 SzMsg_LoadClut_Pipe(u64 *cursor, s32 index, s32 address) {
    extern void *RhMem_CopyMemory4(void *, void *, s32);
    extern u8 textAlphas[][16];
    extern u8 textColors[][16];
    Packet_001FD4C0 *packet = (Packet_001FD4C0 *)cursor;
    u8 colors[16][4];
    s32 i;
    u64 *end;
    s32 count;

    for (i = 0; i < 16; i++) {
        colors[i][0] = colors[i][1] = colors[i][2] = textColors[index][i];
        colors[i][3] = textAlphas[index][i];
    }

    cursor[1] = 0;
    cursor[0] = 0;
    ((Packet_001FD4C0 *)cursor)->header.flag = 0x10;
    cursor[2] = 4 | ((u64)0x10000000 << 32);
    cursor[3] = 0xE;
    cursor[4] = ((s64)address << 32) | ((u64)0x10000 << 32);
    cursor[5] = 0x50;
    cursor[6] = 0;
    cursor[7] = 0x51;
    cursor[8] = 8 | ((u64)2 << 32);
    cursor[9] = 0x52;
    cursor[10] = 0;
    cursor[11] = 0x53;
    cursor[12] = 0x8004 | ((u64)0x08000000 << 32);
    cursor[13] = 0;
    cursor += 14;
    end = RhMem_CopyMemory4(cursor, colors, 16);
    count = ((end - packet->words) >> 1) - 1;
    packet->header.count = count;
    packet->header.dma0 = 0x11000000;
    packet->header.dma1 = (count & 0xFFFF) | 0x51000000;
    return (s32)end;
}

/* Renders message `msg` into text slot `slot` at (x, y) of the text texture. */
void SzMsg_LoadFont(s32 slot, s32 msg, s32 x, s32 y) {
    RhBase_SetVifPacketArea(SzMsg_LoadFont_Pipe(RhBase_GetVifPacketArea(), slot, msg, x, y));
}

typedef struct {
    u32 count : 8;
    u32 width : 12;
    u32 height : 11;
    s32 used : 1;
    s32 x;
    s32 y;
    s32 pixelWidth;
    s32 pixelHeight;
} Texture_001FD680;

typedef struct {
    s32 width;
    u8 pad[0x10];
    s32 tbp;
} Context_001FD680;

/* Renders message `msg` (the game's text) into text slot `slot` at (x, y) of the text texture, glyph by glyph. */
s32 SzMsg_LoadFont_Pipe(s32 cursorIn, s32 slot, s32 msg, s32 x, s32 y) {
    extern s32 D_002D19D0[];
    extern u16 StringBlob[];
    extern u8 gSzMsgImage[];
    extern Context_001FD680 textState;
    Context_001FD680 *context = &textState;
    u8 *glyphs[17][53];
    u8 runs[17][53];
    u16 indices[17][53];
    u16 counts[17];
    u16 advances[17];
    u16 lineCount;
    s64 *packet = (s64 *)cursorIn;
    Texture_001FD680 *texture;
    u16 *stream;
    u16 width;
    u16 height;
    u16 *count;
    u16 *advance;
    s32 n;
    s32 clearIndex;
    u16 *clearCount;
    u16 *clearAdvance;
    u8 *data;
    u8 *out;
    u16 maxCount;
    s32 pixelHeight;
    s32 maxWidth;
    s32 glyphIndex;
    u16 *nextId;
    u8 **next;
    s32 num;
    s32 offset;
    u16 *id;
    s32 outputRow;
    u8 **nextGlyph;
    s32 rowSize;
    u16 *nextCount;
    s32 bytes;
    u8 **lineGlyphs;
    s32 lineIndex;
    u8 *run;
    u8 **glyph;
    s32 outputGlyph;
    u16 currentAdvance;
    s32 pixelWidth;
    s32 rows;
    u8 *lineRuns;
    s64 dimensions;
    s64 coordinates;
    s32 length;

    texture = (Texture_001FD680 *)SzMsg_GetInfo(slot);
    stream = &StringBlob[D_002D19D0[msg]];
    width = 16;
    height = 16;
    lineCount = 0;
    if (texture == 0) {
        return cursorIn;
    }
    if (texture->used) {
        return cursorIn;
    }
    count = counts;
    advance = advances;
    clearIndex = 0;
    clearCount = count;
    clearAdvance = advance;
    do {
        clearIndex++;
        *clearCount++ = 0;
        *clearAdvance++ = 0;
    } while (clearIndex < 17);

    do {
        n = lSzMsg_FontTrace(stream, (char (*)[53])runs, (short (*)[53])indices, counts, advances, &lineCount);
        if (stream[n - 1] & 0x8000) {
            break;
        }
        stream += n;
    } while (1);

    lineCount++;
    lineGlyphs = glyphs[0];
    id = indices[0];
    maxWidth = 0;
    maxCount = maxWidth;
    lineIndex = 0;
    nextGlyph = lineGlyphs;
    nextCount = count;
    while (lineIndex < lineCount) {
        num = *nextCount;
        glyphIndex = 0;
        nextId = id;
        next = nextGlyph;
        goto glyph_test;
    glyph_loop:
        *next = gSzMsgImage + *nextId * 242;
        glyphIndex++;
        nextId++;
        next++;
    glyph_test:
        if (glyphIndex < num) {
            goto glyph_loop;
        }
        if ((u16)maxWidth < (currentAdvance = *advance)) {
            maxCount = *nextCount;
            maxWidth = (u16)currentAdvance;
        }
        id += 53;
        nextGlyph += 53;
        nextCount++;
        advance++;
        lineIndex++;
    }

    pixelHeight = (u16)(lineCount * 22);
    pixelWidth = (u16)maxWidth;
    while (pixelWidth > (u16)width) {
        width = (u16)(width * 2);
    }
    rows = (u16)pixelHeight;
    while (rows > (u16)height) {
        height = (u16)(height * 2);
    }

    dimensions = (s64)(u16)maxWidth | ((s64)(u16)pixelHeight << 32);
    texture->used = 1;
    texture->count = maxCount;
    texture->width = width;
    texture->height = height;
    texture->x = x;
    texture->y = y;
    texture->pixelWidth = pixelWidth;
    texture->pixelHeight = rows;

    packet[1] = 0;
    packet[0] = 0;
    ((u8 *)packet)[3] = 16;
    packet[2] = 4 | ((s64)0x10000000 << 32);
    packet[3] = 14;
    coordinates = ((s64)x << 32) | ((s64)y << 48);
    packet[4] = ((s64)context->tbp << 32) |
                      ((s64)(context->width >> 6) << 48) |
                      ((s64)0x14000000 << 32);
    packet[5] = 0x50;
    packet[6] = coordinates;
    packet[7] = 0x51;
    packet[8] = dimensions;
    packet[9] = 0x52;
    packet[10] = 0;
    packet[11] = 0x53;
    n = pixelWidth >> 1;
    packet[12] = (s64)((n * rows + 15) >> 4) |
                       (0x8000 | ((s64)0x08000000 << 32));
    out = (u8 *)(packet + 14);
    packet[13] = 0;
    lineRuns = runs[0];
    lineIndex = 0;
    while (lineIndex < lineCount) {
        outputRow = 0;
        do {
            rowSize = 0;
            outputGlyph = 0;
            run = lineRuns;
            glyph = lineGlyphs;
            while (outputGlyph < *count) {
                bytes = *run;
                offset = 0;
                if (0 < bytes) {
                    do {
                        *out++ = (*glyph)[offset++];
                    } while (offset < (s32)bytes);
                }
                rowSize += bytes;
                run++;
                outputGlyph++;
                *glyph += 11;
                glyph++;
            }
            goto padding_test;
        padding_loop:
            *out++ = 0;
            rowSize++;
        padding_test:
            if (rowSize < n) {
                goto padding_loop;
            }
            outputRow++;
        } while (outputRow < 22);
        lineRuns += 53;
        lineGlyphs += 53;
        count++;
        lineIndex++;
    }
    while ((s32)out % 16 != 0) {
        out++;
    }
    length = (((s64 *)out - packet) >> 1) - 1;
    *(u16 *)packet = length;
    ((s32 *)packet)[2] = 0x11000000;
    ((s32 *)packet)[3] = (u16)length | 0x51000000;
    return (s32)out;
}

struct DotrSlotTableEntry {
    unsigned int unknown_000 : 31;
    signed int flag : 1;
    int unknown_004[4];
};
typedef char DotrSlotTableEntrySizeMustBe20[(sizeof(struct DotrSlotTableEntry) == 20) ? 1 : -1];
struct DotrSlotTable {
    int words[7];
    struct DotrSlotTableEntry entries[30];
    int unknown_274;
    unsigned short unknown_278;
};
extern struct DotrSlotTable D_0031C070_1fdb90;
extern int D_002D19D0_1fdb90;
extern unsigned short D_002D49D4_1fdb90[];
/* Whether a character code is half width. */
static inline int narrow_p(unsigned short x) { return (x & 0x2000) ? 1 : 0; }

/* Lays out a message line by line: each character's width and code, and the line widths. */
int lSzMsg_FontTrace(unsigned short *p, char (*half)[53], short (*code)[53], unsigned short *cols, unsigned short *widths, unsigned short *line)
{
    struct DotrSlotTable *ml = &D_0031C070_1fdb90;
    unsigned short word = *p;
    unsigned short c = word & 0x1fff;
    unsigned char w = narrow_p(word) ? 12 : 22;
    int ret = 1;
    int n;
    int count;
    unsigned short *q;

    if (word & 0x4000) {
        word = *++p;
        count = c & 0x3f;
        q = &D_002D49D4_1fdb90[(&D_002D19D0_1fdb90)[word & 0x3fff]];
        q += (c >> 6) & 0x7f;
        while (count != 0) {
            n = lSzMsg_FontTrace(q, half, code, cols, widths, line);
            if (q[n - 1] & 0x8000) {
                break;
            }
            count -= n;
            q += n;
        }
        ret = 2;
    } else if (c == ml->unknown_278) {
        (*line)++;
    } else {
        widths[*line] += w;
        half[*line][cols[*line]] = w >> 1;
        code[*line][cols[*line]] = c;
        cols[*line]++;
    }
    return ret;
}

typedef struct {
    u64 TBP0 : 14;
    u64 TBW : 6;
    u64 PSM : 6;
    u64 TW : 4;
    u64 TH : 4;
    u64 TCC : 1;
    u64 TFX : 2;
    u64 CBP : 14;
    u64 CPSM : 4;
    u64 CSM : 1;
    u64 CSA : 5;
    u64 CLD : 3;
} Tex0_001FDD70;

typedef struct {
    u64 LCM : 1;
    u64 : 1;
    u64 MXL : 3;
    u64 MMAG : 1;
    u64 MMIN : 3;
    u64 MTBA : 1;
    u64 : 9;
    u64 L : 2;
    u64 : 11;
    u64 K : 12;
    u64 : 20;
} Tex1_001FDD70;

typedef struct {
    s32 width;
    s32 height;
    s32 tw;
    s32 th;
    s32 cbp;
    s32 tbp;
    s32 cbpOffset;
} TexInfo_001FDD70;

/* The texture rectangle a text slot uses. */
void lSzMsg_GetTexInfo(void *info, void *out) {
    extern TexInfo_001FDD70 textState;
    TexInfo_001FDD70 *texture = &textState;

    if (info != NULL) {
        ((Tex0_001FDD70 *)info)->TBP0 = texture->tbp;
        ((Tex0_001FDD70 *)info)->TBW = texture->width >> 6;
        ((Tex0_001FDD70 *)info)->PSM = 20;
        ((Tex0_001FDD70 *)info)->TW = texture->tw;
        ((Tex0_001FDD70 *)info)->TH = texture->th;
        ((Tex0_001FDD70 *)info)->TCC = 1;
        ((Tex0_001FDD70 *)info)->TFX = 0;
        ((Tex0_001FDD70 *)info)->CBP = texture->cbp + texture->cbpOffset;
        ((Tex0_001FDD70 *)info)->CPSM = 0;
        ((Tex0_001FDD70 *)info)->CSM = 0;
        ((Tex0_001FDD70 *)info)->CSA = 0;
        ((Tex0_001FDD70 *)info)->CLD = 1;
    }
    if (out != NULL) {
        ((Tex1_001FDD70 *)out)->LCM = 0;
        ((Tex1_001FDD70 *)out)->MXL = 0;
        ((Tex1_001FDD70 *)out)->MMAG = 0;
        ((Tex1_001FDD70 *)out)->MMIN = 0;
        ((Tex1_001FDD70 *)out)->MTBA = 0;
        ((Tex1_001FDD70 *)out)->L = 0;
        ((Tex1_001FDD70 *)out)->K = 0;
    }
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001FDFE0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001FDFE0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001FDFE0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001FDFE0;

typedef struct {
    u64 tag[2];
    Color_001FDFE0 color;
    u64 uv0;
    Vertex_001FDFE0 vertex0;
    u64 uv1;
    Vertex_001FDFE0 vertex1;
    u64 test;
    s64 texture0;
    s64 texture1;
    u64 clamp;
} Packet_001FDFE0;

typedef struct {
    s8 pad0[3];
    s8 unused : 7;
    s8 active : 1;
    s32 u;
    s32 v;
    s32 width;
    s32 height;
} Info_001FDFE0;

typedef struct {
    u8 pad[0x274];
    s32 depth;
} State_001FDFE0;

/* Sets a sprite corner's texture coordinates. */
static inline void set_uv_001FDFE0(UV_001FDFE0 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}

/* Draws text slot `slot` at (x, y) inside `rect`, in `color`. */
s32 SzMsg_DrawRect_Pipe(s32 out, s32 slot, s32 x, s32 y, s32 *rectIn, u8 *colorIn) {
    extern u8 D_00293078[];
    extern s32 textDefaultRect[];
    extern State_001FDFE0 textState;
    Packet_001FDFE0 packet __attribute__((aligned(8)));
    State_001FDFE0 *state = &textState;
    Info_001FDFE0 *info;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 u0;
    s32 v0;
    s32 u1;
    s32 v1;
    s32 *rect = rectIn;
    u8 *color = colorIn;

    info = SzMsg_GetInfo(slot);
    if (info == NULL) {
        return out;
    }
    if (info->active == 0) {
        return out;
    }
    if (rect == NULL) {
        rect = textDefaultRect;
    }
    if (color == NULL) {
        color = D_00293078;
    }
    x0 = rect[0] + x;
    y0 = rect[1] + y;
    x1 = rect[2] + x0;
    y1 = rect[3] + y0;
    u0 = info->u;
    v0 = info->v;
    u1 = info->width + u0;
    v1 = info->height + v0;
    ((Tag_001FDFE0 *)packet.tag)->flags = 0x26;
    ((Tag_001FDFE0 *)packet.tag)->count = 5;
    ((Tag_001FDFE0 *)packet.tag)->registers = 0x42421;
    ((Tag_001FDFE0 *)packet.tag)->padding = 0;
    ((Tag_001FDFE0 *)packet.tag)->flags |= 0x800;
    ExAssignAlpha(packet.tag, 0x44 | ((s64)0x80 << 32));
    packet.color.r = color[2];
    packet.color.g = color[1];
    packet.color.b = color[0];
    packet.color.a = color[3];
    packet.color.q = 1.0f;
    packet.vertex0.x = x0 << 4;
    packet.vertex0.y = y0 << 4;
    packet.vertex0.z = state->depth;
    packet.vertex0.fog = 0;
    packet.vertex1.x = x1 << 4;
    packet.vertex1.y = y1 << 4;
    packet.vertex1.z = state->depth;
    packet.vertex1.fog = 0;
    set_uv_001FDFE0((UV_001FDFE0 *)&packet.uv0, (u0 << 4) + 8, (v0 << 4) + 8);
    set_uv_001FDFE0((UV_001FDFE0 *)&packet.uv1, (u1 << 4) + 8, (v1 << 4) + 8);
    lSzMsg_GetTexInfo(&packet.texture0, &packet.texture1);
    return ExSortPrim_Pipe(out, (s32)&packet, 0, 0);
}

typedef int DotrDrawWord;
struct DotrCursorPacketHeader {
    unsigned short unknown_00;
    unsigned short unknown_02;
    int unknown_04;
    long unknown_08;
};
int func_002086D0_b(struct DotrCursorPacketHeader *packet, long value);
DotrDrawWord func_00207650_b(DotrDrawWord cursor, void *packet, int a1, int a2);
extern unsigned char D_0031C070_1fe290[];
struct DotrSlotTableWords {
    int words[4];
};
extern struct DotrSlotTableWords D_002CFCD0_1fe290[];
struct DotrCursorSlotEntry {
    unsigned int unknown_000 : 31;
    signed int flag : 1;
    int unknown_004[4];
};
struct DotrCursorTex {
    long word;
};
extern struct DotrCursorSlotEntry *func_001FEAB0_b(int index);
struct DotrCursorSlotUv {
    unsigned short u : 14;
    unsigned short v : 14;
};
struct DotrCursorSlotXyz {
    unsigned long x : 16;
    unsigned long y : 16;
    unsigned long z : 24;
    unsigned long f : 8;
};
struct DotrCursorRectGVertex {
    unsigned char colour[4];
    float unknown_04;
    long uv;
    struct DotrCursorSlotXyz xyz;
};
struct DotrCursorRectGPacket {
    long header[2];
    struct DotrCursorRectGVertex vertex[4];
    long unknown_70;
    struct DotrCursorTex tex0;
    struct DotrCursorTex tex1;
    long unknown_88;
};
extern unsigned char D_00293080[];

/* Draws text slot `index` at (x, y) inside `rect` with a colour gradient. */
int SzMsg_DrawRectG_Pipe(int cursor, int index, int x, int y, void *rect_v, unsigned char *colour)
{
    struct DotrSlotTableWords * rect = rect_v;
    struct DotrCursorRectGPacket packet;
    int *state = (int *)D_0031C070_1fe290;
    struct DotrCursorSlotEntry *entry;
    int left, top, right, bottom;
    int u, v, u2, v2;

    entry = func_001FEAB0_b(index);
    if (entry == 0) {
        return cursor;
    }
    if (!entry->flag) {
        return cursor;
    }
    if (rect == 0) {
        rect = D_002CFCD0_1fe290;
    }
    if (colour == 0) {
        colour = D_00293080;
    }
    left = rect->words[0] + x;
    top = rect->words[1] + y;
    right = rect->words[2] + left;
    bottom = rect->words[3] + top;
    v = entry->unknown_004[1];
    u = entry->unknown_004[0];
    u2 = entry->unknown_004[2] + u;
    v2 = entry->unknown_004[3] + v;
    ((struct DotrCursorPacketHeader *)packet.header)->unknown_02 = 52;
    ((struct DotrCursorPacketHeader *)packet.header)->unknown_00 = 12;
    ((struct DotrCursorPacketHeader *)packet.header)->unknown_08 = 0x421421421421L;
    ((struct DotrCursorPacketHeader *)packet.header)->unknown_04 = 0;
    ((struct DotrCursorPacketHeader *)packet.header)->unknown_02 |= 0x800;
    func_002086D0_b((struct DotrCursorPacketHeader *)packet.header, 0x8000000044L);
    packet.vertex[0].colour[0] = colour[2];
    packet.vertex[0].colour[1] = colour[1];
    packet.vertex[0].colour[2] = colour[0];
    packet.vertex[0].colour[3] = colour[3];
    packet.vertex[0].unknown_04 = 1.0f;
    packet.vertex[1].colour[0] = colour[6];
    packet.vertex[1].colour[1] = colour[5];
    packet.vertex[1].colour[2] = colour[4];
    packet.vertex[1].colour[3] = colour[7];
    packet.vertex[1].unknown_04 = 1.0f;
    packet.vertex[2].colour[0] = colour[10];
    packet.vertex[2].colour[1] = colour[9];
    packet.vertex[2].colour[2] = colour[8];
    packet.vertex[2].colour[3] = colour[11];
    packet.vertex[2].unknown_04 = 1.0f;
    packet.vertex[3].colour[0] = colour[14];
    packet.vertex[3].colour[1] = colour[13];
    packet.vertex[3].colour[2] = colour[12];
    packet.vertex[3].colour[3] = colour[15];
    packet.vertex[3].unknown_04 = 1.0f;
    packet.vertex[0].xyz.x = left << 4;
    packet.vertex[0].xyz.y = top << 4;
    packet.vertex[0].xyz.z = state[157];
    packet.vertex[0].xyz.f = 0;
    packet.vertex[1].xyz.x = right << 4;
    packet.vertex[1].xyz.y = top << 4;
    packet.vertex[1].xyz.z = state[157];
    packet.vertex[1].xyz.f = 0;
    packet.vertex[2].xyz.x = left << 4;
    packet.vertex[2].xyz.y = bottom << 4;
    packet.vertex[2].xyz.z = state[157];
    packet.vertex[2].xyz.f = 0;
    packet.vertex[3].xyz.x = right << 4;
    packet.vertex[3].xyz.y = bottom << 4;
    packet.vertex[3].xyz.z = state[157];
    packet.vertex[3].xyz.f = 0;
    ((struct DotrCursorSlotUv *)&packet.vertex[0].uv)->u = (u << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[0].uv)->v = (v << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[1].uv)->u = (u2 << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[1].uv)->v = (v << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[2].uv)->u = (u << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[2].uv)->v = (v2 << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[3].uv)->u = (u2 << 4) + 8;
    ((struct DotrCursorSlotUv *)&packet.vertex[3].uv)->v = (v2 << 4) + 8;
    lSzMsg_GetTexInfo(&packet.tex0, &packet.tex1);
    return func_00207650_b(cursor, &packet, 0, 0);
}

typedef struct Rect_001FE660 {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect_001FE660;

typedef s32 (*Draw_001FE660)(s32, s32, s64, s64, Rect_001FE660 *, s32);

/* Draws text slot `slot` at (x, y), scaled, through draw function `draw`. */
s32 SzMsg_DrawRatioX_Pipe(s32 packet, s32 slot, s64 x, s64 y, f32 scaleX, f32 scaleY, s32 color, void (*draw)(void)) {
    extern Rect_001FE660 textDefaultRect;
    Rect_001FE660 rect;
    s32 *info;

    info = SzMsg_GetInfo(slot);
    rect = textDefaultRect;
    if (info == NULL) {
        return packet;
    }
    rect.w = (s32)((f32)info[3] * scaleX);
    rect.h = (s32)((f32)info[4] * scaleY);
    return ((Draw_001FE660)draw)(packet, slot, x, y, &rect, color);
}

/* Draws text slot `slot` at (x, y). */
void SzMsg_DrawX(s32 slot, s32 x, s32 y, s32 arg3, s32 arg4) {
    RhBase_SetVifPacketArea(SzMsg_DrawX_Pipe(RhBase_GetVifPacketArea(), slot, x, y, arg3, arg4));
}

typedef struct Rect_001FE7D0 {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect_001FE7D0;

typedef s32 (*Draw_001FE7D0)(s32, s32, s32, s32, Rect_001FE7D0 *, s32);

/* Draws text slot `slot` at (x, y), through draw function `draw`. */
s32 SzMsg_DrawX_Pipe(s32 packet, s32 slot, s32 x, s32 y, s32 color, s32 draw) {
    extern Rect_001FE7D0 textDefaultRect;
    Rect_001FE7D0 rect;
    s32 *info;

    info = SzMsg_GetInfo(slot);
    rect = textDefaultRect;
    if (info == NULL) {
        return packet;
    }
    rect.w = info[3];
    rect.h = info[4];
    return ((Draw_001FE7D0)draw)(packet, slot, x, y, &rect, color);
}

/* Draws a see-through glass panel. */
void SzMsg_DrawGlass(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    RhBase_SetVifPacketArea(SzMsg_DrawGlass_Pipe(RhBase_GetVifPacketArea(), arg0, arg1, arg2, arg3));
}

typedef struct Xyzf_001FE8F0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyzf_001FE8F0;

typedef struct Packet_001FE8F0 {
    u16 count;
    u16 size;
    u32 flags;
    u64 registers;
    u8 r, g, b, a;
    f32 q;
    Xyzf_001FE8F0 first;
    Xyzf_001FE8F0 second;
} Packet_001FE8F0;

typedef struct State_001FE8F0 {
    u8 pad[0x274];
    s32 depth;
} State_001FE8F0;

/* Fills a GIF tag. */
static inline void tag_001FE8F0(void *packet) {
    *(u16 *)((u8 *)packet + 2) = 6;
    *(u16 *)packet = 3;
    *(u64 *)((u8 *)packet + 8) = 0x441;
    *(u32 *)((u8 *)packet + 4) = 0;
}

/* Draws a see-through glass panel inside `rect` (or the default one), in `color`. */
s32 SzMsg_DrawGlass_Pipe(s32 out, s32 arg1, s32 arg2, s32 rectIn, s32 colorIn) {
    extern u8 D_00293088[];
    extern s32 textDefaultRect[];
    extern State_001FE8F0 textState;
    Packet_001FE8F0 packet;
    u8 *color = (u8 *)colorIn;
    State_001FE8F0 *state = &textState;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 *rect = (s32 *)rectIn;

    if (rect == NULL) {
        rect = textDefaultRect;
    }
    if (color == NULL) {
        color = D_00293088;
    }
    x0 = rect[0] + arg1;
    y0 = rect[1] + arg2;
    x1 = rect[2] + x0;
    y1 = rect[3] + y0;
    tag_001FE8F0(&packet);
    ExAssignAlpha(&packet, 0x8000000044LL);
    packet.r = color[2];
    packet.g = color[1];
    packet.b = color[0];
    packet.a = color[3];
    packet.q = 1.0f;
    packet.first.x = x0 << 4;
    packet.first.y = y0 << 4;
    packet.first.z = state->depth;
    packet.first.fog = 0;
    packet.second.x = x1 << 4;
    packet.second.y = y1 << 4;
    packet.second.z = state->depth;
    packet.second.fog = 0;
    return ExSortPrim_Pipe(out, (s32)&packet, 0, 0);
}

typedef struct Vec4_001FEA80 {
    f32 x, y, z, w;
} Vec4_001FEA80;

extern Vec4_001FEA80 textDefaultRect; /* original: gSzMsg_defRect */

/* The default text rectangle into `out`. */
void SzMsg_GetDefRect(void *out) {
    *(Vec4_001FEA80 *)out = textDefaultRect;
}

/* Text slot `slot`'s record (its rectangle in words 3 and 4), or NULL. */
void *SzMsg_GetInfo(s32 slot) {
    extern u8 textState[];
    u8 *data = textState;
    void *result;

    if (slot >= 0) {
        result = NULL;
        if (slot < 0x1E) {
            result = data + (slot * 0x14) + 0x1C;
        }
    } else {
        result = NULL;
    }
    return result;
}

typedef struct {
    u8 pad00[0x13];
    s8 low_001FEAF0 : 7;
    s8 flag_001FEAF0 : 1;
} Entry_001FEAF0;

typedef struct {
    u8 pad00[0xC];
    Entry_001FEAF0 entries[30];
} Table_001FEAF0;

extern Table_001FEAF0 textState; /* original: gSzMsg_ml */

/* Frees text slot `slot`. */
void SzMsg_Free(s32 slot) {
    Table_001FEAF0 *t = &textState;

    if (slot >= 0 && slot < 0x1E) {
        t->entries[slot].flag_001FEAF0 = 0;
    }
}

typedef struct {
    s8 pad0[3];
    s8 unused : 7;
    s8 active : 1;
    s8 pad4[16];
} Entry_001FEB40;

extern Entry_001FEB40 MessageArray[30];

/* Frees every text slot. */
void SzMsg_FreeAll(void) {
    Entry_001FEB40 *entry;
    s32 i;

    entry = MessageArray;
    i = 0;
    do {
        i += 1;
        entry->active = 0;
        entry++;
    } while (i < 30);
}
