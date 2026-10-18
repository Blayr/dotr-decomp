#include "common.h"


typedef struct {
    s8 axis_0 : 2;
    s8 axis_1 : 2;
    s8 unused : 4;
} MoveFlags_001C2540;

typedef struct {
    u8 padding[0x6E0];
    u8 *first;
    u8 *second;
} State_001C32B0;

typedef struct {
    u32 id : 31;
    u32 flag : 1;
    u32 position : 30;
    u32 state : 2;
} Entry_001C33A0;

typedef struct {
    u8 padding[0x6E0];
    u8 *counts0;
    u8 *counts1;
} State_001C33A0;

typedef struct {
    u8 pad_000[0x6D8];
    s32 values[2];
    u8 pad_6E0[0x67C];
    s8 selection;
} State_001C3520;

typedef struct State_001C35A0 {
    u8 pad0[0x6D8];
    u16 *values0;
    u16 *values1;
    u8 pad1[0x5AA];
    u16 index0;
    u16 condition0;
    u16 index1;
    u16 condition1;
    s16 amount0;
    s16 amount1;
    u8 pad2[0x28];
    u8 mode0;
    u8 mode1;
    u8 pad3[0x9C];
    u8 side;
    u8 pad4;
    u8 selection0;
    u8 selection1;
} State_001C35A0;

extern u16 D_0031811C;

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C38E0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C38E0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C38E0;

typedef struct {
    Color_001C38E0 color;
    Vertex_001C38E0 xyz;
} Point_001C38E0;

typedef struct {
    u64 tag[2];
    Point_001C38E0 points[4];
    u64 end;
} Packet_001C38E0;

typedef struct {
    u8 b, g, r, a;
} Source_001C38E0;

typedef struct Header_001C3E20 {
    u16 type;
    u16 count;
    u32 pad;
    u64 registers;
} Header_001C3E20;

typedef struct Vertex_001C3E20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C3E20;

typedef struct Packet_001C3E20 {
    Header_001C3E20 header;
    u8 r, g, b, a;
    f32 q;
    Vertex_001C3E20 first;
    Vertex_001C3E20 second;
} Packet_001C3E20;

typedef struct Labels_001C3E20 {
    s8 *text[3];
} Labels_001C3E20;

typedef struct Work_001C3E20 {
    Labels_001C3E20 labels;
    Packet_001C3E20 packet;
} Work_001C3E20;

#define SIDE_001C3E20(left, right) side_001C3E20(arg1, left, right)


#pragma opt_propagation off

#pragma opt_propagation reset

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C4B00;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C4B00;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C4B00;

typedef struct {
    u64 tag[2];
    Color_001C4B00 color;
    Vertex_001C4B00 vertex0;
    Vertex_001C4B00 vertex1;
    u64 end;
} Box_001C4B00;

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles_001C4B00;

extern u8 duelAttrIcons[]; /* original: gSzDuel_Attr */
extern u8 duelIcons[]; /* original: gSzDuel_Icon */
extern u8 D_0029086E[];
extern u8 D_00290878[];
extern u8 D_002908BE[];
extern u8 D_002908C8[];
extern s32 D_002908E6;
extern u8 D_002908F0[];
extern u8 D_00290A12[];
extern s8 D_002BF02D;
extern char D_002BF030[];
extern char D_002BE940[];
extern char D_002BE948[];

#pragma opt_dead_assignments off

#pragma opt_dead_assignments reset


#pragma opt_propagation off

#pragma opt_propagation reset


/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrMiscLargeEntry {
    int unknown_words[16360];
};
struct DotrMiscLargeEntry *SzData_GetData_b(int value);
struct DotrMiscControlPair {
    unsigned short top;
    unsigned short count;
};
struct DotrMiscControlLists {
    unsigned char unknown_000[0x6d4];
    void *table;
    short *lists[2];
    unsigned char *counts[2];
    unsigned char unknown_6e8[0x5a2];
    struct DotrMiscControlPair pairs[2];
    short unknown_c92;
    short unknown_c94;
    short unknown_c96;
    short unknown_c98;
    unsigned char unknown_c9a[0x1c];
    unsigned char unknown_cb6[6];
    unsigned char unknown_cbc[2];
    unsigned char unknown_cbe[2];
    unsigned char modes[2];
    unsigned char unknown_cc2[0x9a];
    unsigned char side;         
    unsigned char unknown_d5d;
    unsigned char rows[2];
};
extern struct DotrMiscControlLists D_00317490_1c5d70;
struct DotrCustomDuelSide {
    unsigned char unknown_000[0x33a];
    unsigned short lp;
    unsigned char deck;
    unsigned char unknown_33d[5];
    unsigned char n;
    unsigned char unknown_343[0xd];
};
struct DotrCustomDuelControl {
    struct DotrCustomDuelSide side[2];
    unsigned char unknown_6a0[0x692];
    unsigned char a;
    unsigned char b;
};
struct DotrCustomDuel {
    unsigned char f0[2];
    unsigned char f2[2];
    unsigned char deck[2];
    unsigned char f6[2];
    unsigned char f8[2];
    unsigned char fa[2];
    unsigned char fc[2];
    unsigned char fe[2];
    unsigned short lp[2];
    unsigned short lp2[2];
    unsigned short list[56];
    unsigned char mode;
    unsigned char last;
    unsigned char count;
    unsigned char f8b;
    unsigned char f8c;
    unsigned char f8d;
};
/* 0xa9c000 is CUSTOM_DUEL_ADDR (common.h). The literals stay spelled out in this file: SzDuel_Act, further down,
   matches only with them written as they are (the compiler carries state from the functions before it). */
#define DOTR_CUSTOM_DUEL ((struct DotrCustomDuel *)0xa9c000)
struct DotrCustomDuelFlags {
    unsigned char unknown_0000[0xff9c];
    unsigned int b0 : 5;
    unsigned int b5 : 1;
};
extern unsigned char *RhMem_CopyMemory_b(unsigned char *destination, unsigned char *source, int count);
#undef DOTR_CUSTOM_DUEL


/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrCustomProcControlSide {
    unsigned char unknown_000[0x33c];
    unsigned char deck;                 
    unsigned char unknown_33d[0x13];
};
struct DotrCustomProcControl {
    struct DotrCustomProcControlSide side[2];
    unsigned char unknown_6a0[0x692];
    unsigned char reload[2];            
};
extern signed char D_00317490_b[];
struct DotrCustomProc {
    unsigned char cur[2];               
    unsigned char menu[2];              
    unsigned char deck[2];              
    unsigned char charge[2];            
    unsigned char f8[2];                
    unsigned char fa[2];                
    unsigned char fc[2];                
    unsigned char fe[2];                
    short lp[2];                        
    short lp2[2];                       
    unsigned short list[56];            
    unsigned char mode;                 
    unsigned char last;                 
    unsigned char count;                
    unsigned char f8b;                  
    unsigned char map;                  
    unsigned char maps;                 
    unsigned char yes;                  
};
struct DotrCustomProcAt {
    unsigned char pad[0xa9c000];
    unsigned char cur;
    unsigned char pad01;
    unsigned char menu;
    unsigned char pad03;
    unsigned char deck;
    unsigned char pad05;
    unsigned char charge;
    unsigned char pad07;
    unsigned char f8;
    unsigned char pad09;
    unsigned char fa;
    unsigned char pad0b;
    unsigned char fc;
    unsigned char pad0d;
    unsigned char fe;
    unsigned char pad0f;
    short lp;
    short pad12;
    short lp2;
};
#define DOTR_CUSTOM_PROC ((struct DotrCustomProc *)0xa9c000)
#define DOTR_CUSTOM_PROC_BYTES_AT(i) ((struct DotrCustomProcAt *)(i))
#define DOTR_CUSTOM_PROC_WORDS_AT(i) ((struct DotrCustomProcAt *)((i) * 2))
struct DotrCustomProcSave {
    unsigned char pad[0xfea3];
    unsigned char map[1][7][7];
};
extern unsigned char D_002BEAC0_1c6170[2][2][5];
extern void func_00215920_b(int side, int deck);
extern void func_002029B0_b(int a, int b);
extern int func_001DE690_b(int index);
extern void func_001DE6B0_b(int index, int value);
extern int func_001E2220_b(int x, int y, int value);
#define MENU(i) (DOTR_CUSTOM_PROC_BYTES_AT(i)->menu)
#define LP(i) (DOTR_CUSTOM_PROC_WORDS_AT(i)->lp)
#define LP2(i) (DOTR_CUSTOM_PROC_WORDS_AT(i)->lp2)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(v, lo, hi) MIN(MAX(v, lo), hi)

#undef DOTR_CUSTOM_PROC
#undef DOTR_CUSTOM_PROC_BYTES_AT
#undef DOTR_CUSTOM_PROC_WORDS_AT
#undef MENU
#undef LP
#undef LP2
#undef MAX
#undef MIN
#undef CLAMP


#pragma opt_propagation off
#pragma opt_lifetimes off

#pragma opt_lifetimes reset
#pragma opt_propagation reset

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C7790;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C7790;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C7790;

typedef struct {
    Color_001C7790 color;
    Vertex_001C7790 xyz;
} Point_001C7790;

typedef struct {
    u64 tag[2];
    Point_001C7790 points[4];
    u64 end;
} Packet_001C7790;

typedef struct {
    u8 b, g, r, a;
} Source_001C7790;

extern s32 D_002908E6;
extern s32 D_00290A1C;
extern char D_002BF051[];
extern char D_002BF056[];

extern u8 duelIcons[]; /* original: gSzDuel_Icon */
extern u8 D_002908F0[];
extern u8 D_0029099A[];

typedef struct TextInfo_001C7D20 {
    u8 pad[12];
    s32 width;
} TextInfo_001C7D20;

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001C92C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001C92C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001C92C0;

typedef struct {
    Color_001C92C0 color;
    Vertex_001C92C0 xyz;
} Point_001C92C0;

typedef struct {
    u64 tag[2];
    Point_001C92C0 points[4];
    u64 end;
} Packet_001C92C0;

typedef struct {
    u8 b, g, r, a;
} Source_001C92C0;

typedef struct {
    Source_001C92C0 c[2];
} Pair_001C92C0;

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001CA7C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001CA7C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001CA7C0;

typedef struct {
    Color_001CA7C0 color;
    Vertex_001CA7C0 xyz;
} Point_001CA7C0;

typedef struct {
    u64 tag[2];
    Point_001CA7C0 points[4];
    u64 end;
} Packet_001CA7C0;

typedef struct {
    u64 tag[2];
    Color_001CA7C0 color;
    Vertex_001CA7C0 xyz[2];
    u64 end;
} Rect_001CA7C0;

typedef struct {
    u8 b, g, r, a;
} Source_001CA7C0;

typedef struct {
    u8 pad[0xFEA3];
    u8 maps[5][7][7];
} Maps_001CA7C0;

#pragma optimization_level 3

#pragma optimization_level reset

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001CB6B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001CB6B0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001CB6B0;

typedef struct {
    Color_001CB6B0 color;
    Vertex_001CB6B0 xyz;
} Point_001CB6B0;

typedef struct {
    u64 tag[2];
    Point_001CB6B0 points[4];
    u64 end;
} Packet_001CB6B0;

typedef struct {
    u64 tag[2];
    Color_001CB6B0 color;
    Vertex_001CB6B0 xyz[2];
    u64 end;
} Rect_001CB6B0;

typedef struct {
    u8 b, g, r, a;
} Source_001CB6B0;

typedef struct {
    u8 pad[0xFEA3];
    u8 maps[5][7][7];
} Maps_001CB6B0;

/* Sets two vertex colours from `src`. */
static inline void set_color_001CB6B0(Color_001CB6B0 *a, Color_001CB6B0 *b,
                                      Source_001CB6B0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

/* Sets a screen vertex at (x, y) at the windows' depth. */
static inline void set_xyz_001CB6B0(Vertex_001CB6B0 *v, s32 x, s32 y, u8 *state) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = *(s32 *)(state + 0xC58);
    v->fog = 0;
}

/* Sets one corner of a drawing rectangle. */
static inline void set_corner_001CB6B0(Vertex_001CB6B0 *v, s32 x, s32 y) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = duelState.s.depth;
    v->fog = 0;
}

/* Draws the edited-map choice menu for `player`, with a small picture of each map. */
s32 lSzDuel_DrawCustomDuel_Menu_SelectMapEdit_Pipe(s32 id, s32 player, s32 x, s32 y) {
    extern s32 *func_001FEAB0(s32);
    extern s32 func_001FE7D0(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001B6EA0(s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B65F0(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern u8 duelIcons[];
    extern u8 fieldColors[];
    extern char D_002BF074[];
    extern char D_002BEF93[];
    extern s32 D_002902C4;
    extern s32 D_00290256;
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s32 ret;
    u8 *state = duelState.b;
    u8 *save = (u8 *)0xA9C000;
    Maps_001CB6B0 *maps;
    s8 *text1;
    s8 *text2;
    s32 sel;
    s32 hint = 0;
    s32 tx;
    s32 ty;
    s32 i;
    s32 j;
    s32 row;
    s32 count;
    s32 n;
    s32 hl;
    u8 *board;
    s32 px;
    s32 py;
    s32 w;
    s32 h;
    Rect_001CB6B0 rect __attribute__((aligned(8)));
    Packet_001CB6B0 packet __attribute__((aligned(8)));

    maps = func_002145E0(0);
    text1 = D_002BF074;
    text2 = D_002BEF93;
    sel = (*(u8 *)0xA9C08C + 2) % *(u8 *)0xA9C08D;
    id = func_001FD680(id, 1, 0x88, 0, 0x16);
    id = func_0020F290(func_001FD680(id, 2, 0x8B, 0, 0x2C));
    id = func_001B4780(id, 0xC, 3, 4, x + 0xBA, y, -0xD0, -0x20, 1);
    id = func_001FE7D0(id, 1, x + 0x122 - (func_001FEAB0(1)[3] >> 1), y + 5, 0, SzMsg_DrawRect_Pipe);
    func_001FEAF0(1);
    py = y + 0x20;
    id = func_001B4780(id, player, -1, 0xB, x, py, -0x244, -0xAA, 1);
    py = y + 0x35;
    id = func_001B4780(id, 0xC, -1, 6, x + 0x5D, py, -0xEC, -0x7C, 1);
    px = x + 0x71D;
    py = y + 0x789;
    ((Tag_001CB6B0 *)rect.tag)->flags = 6;
    ((Tag_001CB6B0 *)rect.tag)->count = 3;
    ((Tag_001CB6B0 *)rect.tag)->registers = 0x441;
    ((Tag_001CB6B0 *)rect.tag)->padding = 0;
    rect.color.r = 0x80;
    rect.color.g = 0;
    rect.color.b = 0;
    rect.color.a = 0x80;
    rect.color.q = 1.0f;
    set_corner_001CB6B0(&rect.xyz[0], px, py);
    set_corner_001CB6B0(&rect.xyz[1], px + 0xF0, py + 0x18);
    id = func_00207650(id, (s32)rect.tag, 0, 0);
    py = y + 0x35;
    id = func_001B4780(id, -1, -1, 6, x + 0x5D, py, -0xEC, -0x7C, hint != 0 ? 0 : 1);
    for (i = 0; i < 5; i++) {
        hl = (i == 2) ? 0 : (s32)D_002BE944;
        n = (save[0x8C] + i) % save[0x8D];
        id = func_001FE7D0(id, 2, x + 0x69, y + 0x3A + i * 0x18, hl, SzMsg_DrawRect_Pipe);
        id = func_001B6CA0(id, x + 0x119, y + 0x3A + i * 0x18, 2, n, 0, 1, hl);
    }
    func_001FEAF0(2);
    py = y + 0x78D;
    id = func_001B3CC0(id, &D_002902C4, x + 0x71F, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x78D;
    id = func_001B3CC0(id, &D_002902C4, x + 0x803, py, 0, 1, 0, 0, 1, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    board = &maps->maps[sel][0][0];
    px = x + 0x81C;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            id = func_001B3CC0(id, duelIcons + (board[i * 7 + j] + 0x10E) * 10, px + j * 16,
                               y + 0x75C + i * 16, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0x80);
        }
    }
    py = y + 0x35;
    id = func_001B4780(id, -1, 1, 1, x + 0x155, py, -0x76, -0x76, 1);
    py = y + 0x7C7;
    id = func_001B3CC0(id, &D_00290256, x + 0x834, py, 0, 1, 0, 0, 0, 1, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    for (row = 0; row < 10; row++) {
        count = 0;
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                if (row == board[i * 7 + j]) {
                    count++;
                }
            }
        }
        id = func_001B3CC0(id, duelIcons + (row + 0x10E) * 10, x + 0x89B, y + 0x745 + row * 16, 0, 1, 0,
                           0, 0, 0, 1, 0, -1, 0x80);
        id = func_001B4780(id, 0xD, -1, 5, x + 0x1EB, y + 0x25 + row * 16, -0x54, -0x10, 1);
        px = x + 0x8AB;
        py = y + 0x745 + row * 16;
        w = (s32)((f32)count * 84.0f / 49.0f);
        h = 8;
        ((Tag_001CB6B0 *)packet.tag)->flags = 0x14;
        ((Tag_001CB6B0 *)packet.tag)->count = 8;
        ((Tag_001CB6B0 *)packet.tag)->registers = 0x41414141;
        ((Tag_001CB6B0 *)packet.tag)->padding = 0;
        set_color_001CB6B0(&packet.points[0].color, &packet.points[1].color, &((Source_001CB6B0 *)fieldColors)[row * 3]);
        set_color_001CB6B0(&packet.points[2].color, &packet.points[3].color, &((Source_001CB6B0 *)fieldColors)[row * 3 + 1]);
        set_xyz_001CB6B0(&packet.points[0].xyz, px, py, state);
        set_xyz_001CB6B0(&packet.points[1].xyz, px + w, py, state);
        set_xyz_001CB6B0(&packet.points[2].xyz, px, py + h, state);
        set_xyz_001CB6B0(&packet.points[3].xyz, px + w, py + h, state);
        id = func_00207650(id, (s32)packet.tag, 0, 0);
        set_color_001CB6B0(&packet.points[0].color, &packet.points[1].color, &((Source_001CB6B0 *)fieldColors)[row * 3 + 1]);
        set_color_001CB6B0(&packet.points[2].color, &packet.points[3].color, &((Source_001CB6B0 *)fieldColors)[row * 3 + 2]);
        set_xyz_001CB6B0(&packet.points[0].xyz, px, py + h, state);
        set_xyz_001CB6B0(&packet.points[1].xyz, px + w, py + h, state);
        set_xyz_001CB6B0(&packet.points[2].xyz, px, py + h * 2, state);
        set_xyz_001CB6B0(&packet.points[3].xyz, px + w, py + h * 2, state);
        id = func_00207650(id, (s32)packet.tag, 0, 0);
        id = func_001B4780(id, -1, -1, 5, x + 0x1EB, y + 0x25 + row * 16, -0x54, -0x10, 1);
        id = func_001B6EA0(id, x + 0x215, y + 0x27 + row * 16, 0, 2, 2, count);
    }
    id = func_001B65F0(id, player, x + 6, y + 0x26, -0x4E, -0x9E, -1, 0);
    py = y + 0x76E;
    id = func_001B3CC0(id, &D_00290A62, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    py = y + 0x77E;
    ret = func_001B3CC0(id, &D_00290A58, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    tx = x + 0x20;
    ty = y + 0x58;
    ret = func_001B6F70(ret, tx, ty, 1, 0, func_0019BEF0((char *)text1), text1,
                       hint != 0 ? (s32)D_002BE944 : 0);
    py = y + 0x7B7;
    ret = func_001B3CC0(ret, &D_00290A6C, x + 0x6CE, py, 0, 1, 0, 0, 0, 0, 1, 0, -1, hint != 0 ? 0x40 : 0x80);
    tx = x + 0x20;
    ty = y + 0x99;
    return func_001B6F70(ret, tx, ty, 1, 0, func_0019BEF0((char *)text2), text2,
                         hint != 0 ? (s32)D_002BE944 : 0);
}

/* Draws the leave-custom-duel dialog (yes / no). */
void lSzDuel_DrawCustomDuel_Exit_Pipe(s32 packet, s32 left, s32 top) {
    extern s32 lSzDuel_DrawDialog_Window_Pipe(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    s32 text = (s32)D_002BEF98;
    s8 *text2 = D_002BEF6F;
    s8 *text3 = D_002BEF73;
    s32 id;

    packet = lSzDuel_DrawDialog_Window_Pipe(packet, 2, -1, 0x91, left + 0x140, top + 0x94, 0x140, 0x98,
                         func_0019BEF0((char *)text), text, 0);
    id = SzDuel_DrawWindow_Font_Pipe(packet, left + 0xF0, top + 0x108, 2, 3, func_0019BEF0((char *)text2), text2,
                       *(u8 *)0xA9C08E != 0 ? 0 : (s32)D_002BE944);
    SzDuel_DrawWindow_Font_Pipe(id, left + 0x190, top + 0x108, 2, 3, func_0019BEF0((char *)text3), text3,
                  *(u8 *)0xA9C08E != 0 ? (s32)D_002BE944 : 0);
}

typedef struct {
    u8 enabled : 1;
} Flags_001CC4B0;

typedef struct {
    f32 data[4];
} Vec4_001CC4B0;

extern Vec4_001CC4B0 D_002914B0;
extern Vec4_001CC4B0 D_002914C0;

/* Opens the map editor (`fromCustomDuel` keeps the map being edited): board colours, models, camera. */
void SzDuel_InitMapEdit(s32 fromCustomDuel) {
    u8 *state = duelState.b;
    s32 i;
    Vec4_001CC4B0 vector0;
    Vec4_001CC4B0 vector1;

    vector0 = D_002914B0;
    vector1 = D_002914C0;
    i = 0;
    do {
        SzModel_SetDrawFlag(i, 0);
        i++;
    } while (i < 0x54);
    i = 0;
    do {
        SzModel_SetDrawFlag(i, 1);
        i++;
    } while (i < 5);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x4A, 1);
        i++;
    } while (i < 0xA);
    SzView_SetCP(0, vector0.data);
    SzView_SetLookSP(0, vector1.data);
    *(s8 *)0xA9C08F = 3;
    *(s8 *)0xA9C090 = 3;
    *(s8 *)0xA9C091 = 0;
    ((Flags_001CC4B0 *)0xA9C092)->enabled = 0;
    SzDuel_InitMapColor2(0, 0, 1, 0);
    state[0xD57] = 0x63;
    if (fromCustomDuel != 0) {
        *(u8 *)0xA9C08D = 5;
        *(u8 *)0xA9C08C = *(u8 *)0xA9C08D - 2;
    }
    state[0xD63] = 0;
}

/* Ends the map editor (nothing to do). */
void SzDuel_TermMapEdit(void) {

}

typedef struct {
    s8 first : 2;
    s8 second : 2;
    s8 unused : 4;
} PulseFlags_001CC620;

typedef struct {
    u8 padding[0xC86];
    u16 first;
    u16 second;
    u8 padding2[0xD63 - 0xC8A];
    u8 active;
    PulseFlags_001CC620 flags;
} State_001CC620;

typedef struct {
    u8 diagonal : 1;
    u8 unused : 7;
} InputFlags_001CC620;

extern u16 D_00318118;
extern u8 D_003181F3;
extern PulseFlags_001CC620 D_003181F4;

#pragma conditional_move off

/* Runs the map editor: moves the cursor over the board, changes the field type under it, leaves on cancel. */
void SzDuel_ActMapEdit(void) {
    extern void *SzData_GetData(s32);
    extern s32 SzDuel_SetField();
    State_001CC620 *state = (State_001CC620 *)duelState.b;
    s32 row;
    s32 column;
    u8 *cell;
    u8 *rowStart;
    s32 value;
    s32 positive;
    s32 step;
    u8 tile;
    u16 buttons;
    State_001CC620 *p;
    State_001CC620 *p2;

    {
        p = (State_001CC620 *)duelState.b;
        if (D_003181F3 != 0) {
            p->flags.first = 1;
        }
        value = p->first + (p->flags.first << 9);
        p->first = (value > 0 ? value : 0) < 0x8000 ?
            (value > 0 ? value : 0) : 0x8000;
        if (p->first == 0 || p->first >= 0x8000) {
            p->flags.first = (s8)-p->flags.first;
        }
    }
    {
        p2 = (State_001CC620 *)duelState.b;
        step = D_003181F4.second << 11;
        p2->second = (D_00318118 + step > 0 ? p2->second + step : 0) < 0x8000 ?
            (p2->second + step > 0 ? p2->second + step : 0) : 0x8000;
        if (p2->second == 0 || p2->second >= 0x8000) {
            p2->flags.second = (s8)-p2->flags.second;
        }
    }
    if (*(u8 *)0xA9C091 != 0) {
        --*(u8 *)0xA9C091;
    }
    if (SzPad_Check(0, 0, 0x8C0) != 0) {
        rowStart = (u8 *)SzData_GetData(0) +
            ((*(u8 *)0xA9C08C + 2) % *(u8 *)0xA9C08D) * 49;
        row = 0;
        do {
            column = 0;
            cell = rowStart;
            do {
                cell[0xFEA3] = SzDuel_GetField(column, row);
                ++column;
                ++cell;
            } while (column < 7);
            ++row;
            rowStart += 7;
        } while (row < 7);
        SzSound_PlaySE(0, 4);
        SzGame_Pop();
        return;
    }
    if (SzPad_Check(0, 0, 0x20) != 0) {
        SzSound_PlaySE(0, 5);
        SzGame_Pop();
        return;
    }
    if (SzPad_Check(0, 2, 0xC) != 0) {
        tile = SzDuel_GetField(*(u8 *)0xA9C08F, *(u8 *)0xA9C090);
        if (SzPad_Check(0, 2, 4) != 0) {
            tile = (tile + 9) % 10;
        }
        if (SzPad_Check(0, 2, 8) != 0) {
            tile = (tile + 11) % 10;
        }
        SzSound_PlaySE(0, 3);
        SzDuel_SetField(*(u8 *)0xA9C08F, *(u8 *)0xA9C090, tile);
    }
    if (*(u8 *)0xA9C091 == 0) {
        buttons = SzPad_Check(0, 1, 0xFFFF);
        if (buttons & 0xF000) {
            if (((buttons & 0x8000) && *(u8 *)0xA9C08F <= 0) ||
                ((buttons & 0x2000) && *(u8 *)0xA9C08F >= 6)) {
                buttons &= 0x5FFF;
            }
            if (((buttons & 0x1000) && *(u8 *)0xA9C090 <= 0) ||
                ((buttons & 0x4000) && *(u8 *)0xA9C090 >= 6)) {
                buttons &= 0xAFFF;
            }
            state->active = 60;
            if (((InputFlags_001CC620 *)0xA9C092)->diagonal) {
                if (buttons & 0x5000) {
                    buttons &= 0x5000;
                } else {
                    ((InputFlags_001CC620 *)0xA9C092)->diagonal = 0;
                }
            }
            if (buttons & 0xA000) {
                if (buttons & 0x8000) {
                    --*(u8 *)0xA9C08F;
                } else {
                    ++*(u8 *)0xA9C08F;
                }
                if (buttons & 0x5000) {
                    ((InputFlags_001CC620 *)0xA9C092)->diagonal = 1;
                }
            } else if (buttons & 0x5000) {
                if (buttons & 0x1000) {
                    --*(u8 *)0xA9C090;
                } else {
                    ++*(u8 *)0xA9C090;
                }
                ((InputFlags_001CC620 *)0xA9C092)->diagonal = 0;
            } else {
                ((InputFlags_001CC620 *)0xA9C092)->diagonal = 0;
                return;
            }
            SzSound_PlaySE(0, 3);
            *(u8 *)0xA9C091 = 8;
        }
    }
}
#pragma conditional_move reset

/* Draws the map editor. */
void SzDuel_DrawMapEdit(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawMapEdit_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color_001CCBB0;

typedef struct {
    u8 pad0[0x8F];
    u8 x;
    u8 y;
} Cursor_001CCBB0;

/* Draws a window title from message `text`. */
static inline s32 title_001CCBB0(s32 id, s32 text, s32 x, s32 y) {
    extern s32 lSzDuel_DrawWindow_Frame_Pipe();
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, s32, void (*)(void));
    s32 width;
    s32 result;
    f32 scale;

    scale = 1.0f;
    id = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(id, 1, text + 0x47, 0, 0x16));
    id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, 2, 3, x, y, 9, 0x12, 1);
    id = lSzDuel_DrawWindow_Frame_Pipe(id, 5, -1, 3, x, y + 0x40, 9, 2, 1);
    width = ((s32 *)SzMsg_GetInfo(1))[3];
    if (width > 0x54) {
        scale = 84.0f / (f32)width;
    }
    result = SzMsg_DrawRatioX_Pipe(id, 1, (x + 0x30) - (s32)((f32)(width >> 1) * scale), y + 0x43,
                           scale, 1.0f, 0, SzMsg_DrawRect_Pipe);
    SzMsg_Free(1);
    return result;
}

/* Draws the map editor: the board colours, the field piece under the cursor, the field counts, the button guide. */
s32 SzDuel_DrawMapEdit_Pipe(s32 packet) {
    extern Color_001CCBB0 D_002914D0;
    extern u16 D_00318116;
    extern s32 lSzDuel_DrawWindow_FieldPiece_Pipe(s32, s32, s32, s32, s32, f32);
    extern s32 lSzDuel_DrawMapEdit_Graph_Pipe(s32, s32, s32);
    extern s32 SzDuel_SetMapColor2();
    Cursor_001CCBB0 *cursor = (Cursor_001CCBB0 *)0xA9C000;
    Color_001CCBB0 color;
    s32 x;
    s32 y;
    s32 id;
    s32 timer;
    s32 hint = 0;

    timer = D_00318116;
    color = D_002914D0;
    color.a = hint != 0 ? 0x80 : (u8)(((timer >> 8) & 0xFF) + 0x40);
    SzDuel_InitMapColor2(0, 0, 0, 0);
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 7; x++) {
            if (cursor->x == x || cursor->y == y) {
                SzDuel_SetMapColor2(x, y, 1, &color, 0, 0);
            }
        }
    }
    SzDuel_SetMapColor2(cursor->x, cursor->y, 1, &color, 0, 0);
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 7; x++) {
            SzDuel_CalcMapColor(x, y);
        }
    }
    SzDuel_SetWindowDefPrioZ(0xFFFFF8);
    packet = lSzDuel_DrawWindow_FieldPiece_Pipe(packet, 0, SzDuel_GetField(cursor->x, cursor->y), 6, 0x150, 100.0f);
    id = SzDuel_StartWindowSessionWithPalette_Pipe(packet, 0);
    id = title_001CCBB0(id, SzDuel_GetField(cursor->x, cursor->y), 6, 0x150);
    id = lSzDuel_DrawMapEdit_Graph_Pipe(lSzDuel_DrawWindow_CommandGuide_Pipe(id, 0, 0x21A, 0x150), 6, 0x90);
    SzMsg_Free(0);
    return id;
}

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001CCEA0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001CCEA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001CCEA0;

typedef struct {
    Color_001CCEA0 color;
    Vertex_001CCEA0 xyz;
} Point_001CCEA0;

typedef struct {
    u64 tag[2];
    Point_001CCEA0 points[4];
    u64 end;
} Packet_001CCEA0;

typedef struct {
    u8 b, g, r, a;
} Source_001CCEA0;

/* Sets two vertex colours from `src`. */
static inline void set_color_001CCEA0(Color_001CCEA0 *a, Color_001CCEA0 *b,
                                      Source_001CCEA0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

/* Sets a screen vertex at (x, y) at the windows' depth. */
static inline void set_xyz_001CCEA0(Vertex_001CCEA0 *v, s32 x, s32 y, u8 *state) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = *(s32 *)(state + 0xC58);
    v->fog = 0;
}

/* Draws the map editor's bar graph: how many squares of each field type the map has. */
s32 lSzDuel_DrawMapEdit_Graph_Pipe(s32 out, s32 x, s32 y) {
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe(s32, s32, s32, s32, s32, s32, s32);
    extern u8 duelIcons[];
    extern u8 fieldColors[];
    u8 *state = duelState.b;
    u8 cur;
    s32 j;
    s32 i;
    s32 row;
    s32 count;
    s32 px;
    s32 py;
    s32 w;
    s32 h;
    s32 id;
    Packet_001CCEA0 packet __attribute__((aligned(8)));

    cur = SzDuel_GetField(*(u8 *)0xA9C08F, *(u8 *)0xA9C090);
    id = lSzDuel_DrawWindow_Frame_Pipe(out, 0, -1, 0xB, x, y, -0x6E, -0xAA, 1);
    for (row = 0; row < 10; row++) {
        count = 0;
        for (j = 0; j < 7; j++) {
            for (i = 0; i < 7; i++) {
                if (row == SzDuel_GetField(i, j)) {
                    count++;
                }
            }
        }
        px = x + 0x6C5;
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, duelIcons + (row + 0x10E) * 10, px, y + 0x725 + row * 16, 0, 1, 0,
                           0, 0, 0, 1, 0, (cur == row) ? 1 : -1, 0x80);
        id = lSzDuel_DrawWindow_Frame_Pipe(id, 0xD, -1, 5, x + 0x15, y + 5 + row * 16, -0x54, -0x10, 1);
        px = x + 0x6D5;
        py = y + 0x725 + row * 16;
        w = (s32)((f32)count * 84.0f / 49.0f);
        h = 8;
        ((Tag_001CCEA0 *)packet.tag)->flags = 0x14;
        ((Tag_001CCEA0 *)packet.tag)->count = 8;
        ((Tag_001CCEA0 *)packet.tag)->registers = 0x41414141;
        ((Tag_001CCEA0 *)packet.tag)->padding = 0;
        set_color_001CCEA0(&packet.points[0].color, &packet.points[1].color, &((Source_001CCEA0 *)fieldColors)[row * 3]);
        set_color_001CCEA0(&packet.points[2].color, &packet.points[3].color, &((Source_001CCEA0 *)fieldColors)[row * 3 + 1]);
        set_xyz_001CCEA0(&packet.points[0].xyz, px, py, state);
        set_xyz_001CCEA0(&packet.points[1].xyz, px + w, py, state);
        set_xyz_001CCEA0(&packet.points[2].xyz, px, py + h, state);
        set_xyz_001CCEA0(&packet.points[3].xyz, px + w, py + h, state);
        id = ExSortPrim_Pipe(id, (s32)packet.tag, 0, 0);
        set_color_001CCEA0(&packet.points[0].color, &packet.points[1].color, &((Source_001CCEA0 *)fieldColors)[row * 3 + 1]);
        set_color_001CCEA0(&packet.points[2].color, &packet.points[3].color, &((Source_001CCEA0 *)fieldColors)[row * 3 + 2]);
        set_xyz_001CCEA0(&packet.points[0].xyz, px, py + h, state);
        set_xyz_001CCEA0(&packet.points[1].xyz, px + w, py + h, state);
        set_xyz_001CCEA0(&packet.points[2].xyz, px, py + h * 2, state);
        set_xyz_001CCEA0(&packet.points[3].xyz, px + w, py + h * 2, state);
        id = ExSortPrim_Pipe(id, (s32)packet.tag, 0, 0);
        id = lSzDuel_DrawWindow_Frame_Pipe(id, -1, -1, 5, x + 0x15, y + 5 + row * 16, -0x54, -0x10, 1);
        id = SzDuel_DrawWindow_FontDigit_Pipe(id, x + 0x3F, y + 7 + row * 16, 0, 2, 2, count);
    }
    return id;
}

typedef struct Draw_001CD560 {
    s32 f00;
    s32 f04;
    s32 f08;
    f32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    s32 f3C;
    u8 g40;
    u8 g41;
    u8 g42;
    u8 alpha;
    u8 g44;
    u8 g45;
    u8 g46;
    u8 g47;
    u16 h48;
    u16 h4A;
    s32 f4C;
    s64 d50;
    u8 pad58[0x20];
    s32 p78;
    s32 p7C;
    s16 a80 : 12;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
    s16 a82 : 12;
    u8 b83a : 2;
    s8 b83c : 1;
    s8 b83d : 1;
} Draw_001CD560;

/* Resets a card draw record to its defaults. Returns 0 for none. */
s32 SzDuel_ClearDrawCard(void *draw) {
    Draw_001CD560 *p;

    if (draw == NULL) {
        return 0;
    }
    p = draw;
    p->f00 = 0;
    p->f04 = 0;
    p->f08 = 0;
    p->f0C = 1.0f;
    p->f10 = 0x4000;
    p->f14 = 0;
    p->f18 = 0;
    p->f1C = 0;
    p->f20 = 0;
    p->f24 = 0;
    p->f28 = 0;
    p->f2C = 0;
    p->f30 = 0.1f;
    p->f34 = 0.1f;
    p->f38 = 1.0f;
    p->f3C = 0;
    p->g42 = 0x80;
    p->g41 = 0x80;
    p->g40 = 0x80;
    p->alpha = 0x80;
    p->g46 = 0;
    p->g45 = 0;
    p->g44 = 0;
    p->g47 = 0;
    p->h4A = 7;
    p->h48 = 0;
    p->d50 = 0;
    p->f4C = 0;
    p->p78 = 0x70002000;
    p->p7C = 0x70000000;
    p->a80 = 0xAA;
    p->a82 = 0;
    p->b83a = 1;
    p->horizontal = 1;
    p->enabled = 0;
    p->colored = 1;
    p->reserved = 1;
    p->b83c = 0;
    p->b83d = 0;
    return 1;
}

/* Draws every card on screen. */
void SzDuel_DrawAllCard(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawAllCard_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct Vec4_001CD710 {
    f32 x, y, z, w;
} Vec4_001CD710;

typedef struct Command_001CD710 {
    __int128 position;
    u8 pad10[0x33];
    u8 flags;
    u8 pad44[0x4C];
} Command_001CD710;

typedef struct Flags_001CD710 {
    s8 low : 6;
    s8 active : 1;
    s8 high : 1;
} Flags_001CD710;

typedef struct Object_001CD710 {
    u8 pad00[4];
    Command_001CD710 *command;
    u8 pad08[0x3C];
    u8 field44;
    u8 field45;
    u8 pad46[0x11];
    Flags_001CD710 flags;
} Object_001CD710;


/* Draws every card on screen: requested cards, the leaders' bases, the cards in hand and those on the board. */
s32 SzDuel_DrawAllCard_Pipe(s32 packet) {
    extern s32 SzDuel_DrawHandCard_Pipe(s32);
    Vec4_001CD710 position;
    Command_001CD710 command;
    u8 *base = duelState.b;
    u8 *selected = duelState.b + D_003181E4 * 0x350;
    s32 original;
    s64 mode;
    s32 special;
    s32 value;
    s32 final_value;
    Object_001CD710 *object;
    extern s32 SzView_GetCP();
    extern s32 SzDuel_DrawCard_Pipe();
    extern s32 ExSortAnchor_Pipe();

    mode = SzGame_GetMode(1);
    original = packet;
    switch (mode) {
    case 1:
    case 0:
        if (SzModel_GetDrawFlag(0) == 0) {
            return original;
        }
        packet = ExSetAnchor_Pipe(packet);
        packet = SzDuel_StartCardSession_Pipe(packet);
        packet = SzDuel_DrawCardRequest_Pipe(packet);
        packet = RhBase_SetZBufferMode(packet, 1);
        SzDuel_GetUnitPos(0, 0, &position.x);
        position.y = 0.0f;
        packet = SzDuel_DrawLeaderBase_Pipe(packet, 0, &position.x, 0x80, 1);
        SzDuel_GetUnitPos(1, 0, &position.x);
        position.y = 0.0f;
        value = RhBase_SetZBufferMode(SzDuel_DrawLeaderBase_Pipe(packet, 1, &position.x, 0x80, 1), 0);
        if (*(Object_001CD710 **)(base + 0x6C8) != NULL) {
            if ((*(Object_001CD710 **)(base + 0x6C8))->flags.active != 0) {
                special = 0;
                if (base[0xD57] == 0x1D && SzView_InqRequest(-1, -1) != NULL) {
                    special = 1;
                }
                if (special != 0) {
                    position = *(Vec4_001CD710 *)SzView_GetCP(0);
                } else {
                    SzDuel_CalcUnitPos(selected[0x33D], selected[0x33E], 0, &position);
                }
                position.y = 1.0f;
                object = *(Object_001CD710 **)(base + 0x6C8);
                if (object->field45 == 0) {
                    value = RhBase_SetZBufferMode(value, 1);
                    value = SzDuel_DrawLeaderBase_Pipe(value, (*(Object_001CD710 **)(base + 0x6C8))->field44, &position.x, 0x40, 0);
                    value = RhBase_SetZBufferMode(value, 0);
                } else if (object->command != NULL) {
                    command = *object->command;
                    command.flags = ((s32)command.flags << 6) >> 7;
                    *(__int128 *)&command = *(__int128 *)&position;
                    object = SzDuel_GetCardNode(&command, 1) ? object : NULL;
                    value = SzDuel_SetupCard2_Pipe(value, (s32)object, &command);
                    value = RhBase_SetZBufferMode(value, 1);
                    value = SzDuel_DrawCard_Pipe(value, &command);
                    value = RhBase_SetZBufferMode(value, 0);
                }
            }
        }
        final_value = SzDuel_FinishCardSession_Pipe(SzDuel_DrawHandCard_Pipe(value));
        return ExSortAnchor_Pipe(final_value, original, ExGetMyOT(), 0xFFFFFF);
    default:
        return original;
    }
}

/* Empties the card request list. */
void SzDuel_InitCardRequest(void) {
    u8 *entry;
    s32 i;

    entry = cardRequests;
    i = 0;
    do {
        SzDuel_FreeCardRequest(entry);
        i += 1;
        entry += 0xA0;
    } while (i < 0x20);
}

/* Frees one card request. */
s32 SzDuel_FreeCardRequest(void *request) {
    extern void SzDuel_ClearDrawCard();

    if (request == NULL) {
        return 0;
    }
    SzDuel_ClearDrawCard();
    *(s32 *)((u8 *)request + 0x90) = 0;
    return 1;
}


typedef struct {
    u8 pad_00[0x90];
    s32 in_use;
    u8 pad_94[0xC];
} Slot_001CDAA0;

/* A free card request record, cleared, or NULL. */
u8 *SzDuel_GetCardRequest(void) {
    s32 i;
    Slot_001CDAA0 *slot;

    slot = (Slot_001CDAA0 *)cardRequests;
    i = 0;
    do {
        if (slot->in_use == 0) {
            SzDuel_ClearDrawCard(slot);
            return (u8 *)slot;
        }
        i += 1;
        slot++;
    } while (i < 0x20);
    return NULL;
}

typedef struct {
    s8 unused : 4;
    u8 mode : 2;
    s8 unused6 : 1;
    s8 set : 1;
} Flags_001CDB00;

typedef struct {
    u8 r, g, b, a;
} Color_001CDB00;

typedef struct {
    f32 value;
} PackedColor_001CDB00;

typedef union {
    struct {
        f32 x, y, z, w;
    } value;
    __int128 quad;
} Vector_001CDB00;

typedef struct {
    Vector_001CDB00 position;
    u8 pad10[0x33];
    u8 visible;
    Color_001CDB00 color;
    u8 pad48[0x39];
    Flags_001CDB00 flags81;
    u8 pad82;
    Flags_001CDB00 flags83;
    u8 pad84[0xC];
} Draw_001CDB00;

typedef struct {
    u8 pad00[0x34];
    s16 x, z;
    u8 pad38[8];
    u8 index40, index41;
    u8 pad42[7];
    u8 color49, color4A;
    u8 pad4B[0xC];
    Flags_001CDB00 flags57;
} Unit_001CDB00;

typedef struct {
    Draw_001CDB00 draw;
    Unit_001CDB00 *unit;
    u8 pad94[0xC];
} Entry_001CDB00;

extern f32 D_002914D8;

/* Draws the cards that were requested (cards shown flying or held up). */
s32 SzDuel_DrawCardRequest_Pipe(s32 packet) {
    Draw_001CDB00 draw;
    PackedColor_001CDB00 color;
    Entry_001CDB00 *entry;
    s32 i;
    void *position;
    s32 height;

    entry = (Entry_001CDB00 *)cardRequests;
    i = 0;
    color = *(PackedColor_001CDB00 *)&D_002914D8;
    do {
        if (entry->unit != NULL) {
            Unit_001CDB00 *unit = entry->unit;

            position = SzDuel_GetMapInfo(unit->index40, unit->index41);
            draw = entry->draw;
            if (!draw.flags83.set && (!draw.flags81.set || draw.visible != 0)) {
                if (!unit->flags57.set) {
                    if (position != NULL) {
                        height = *(s16 *)((u8 *)position + 0x14);
                        height = height > 0 ? height : 0;
                        draw.position.value.y = (f32)(height * 35) / 128.0f;
                        if (unit->color49 != 0 || unit->color4A != 0) {
                            draw.flags83.mode = 3;
                            draw.color = *(Color_001CDB00 *)&color;
                        }
                    }
                    draw.position.value.x += (f32)unit->x;
                    draw.position.value.z += (f32)unit->z;
                }
                packet = SzDuel_SetupCard2_Pipe(packet, (s32)(SzDuel_GetCardNode(&draw, 1) ? unit : NULL), &draw);
                packet = RhBase_SetZBufferMode(packet, 1);
                packet = SzDuel_DrawCard_Pipe(packet, (s32)&draw);
                packet = RhBase_SetZBufferMode(packet, 0);
            }
        }
        i++;
        entry++;
    } while (i < 32);
    return packet;
}

#include "common.h"

/* Clears the six card control records. */
void SzDuel_InitCardControl(void) {
    u8 *p;
    s32 i;

    p = cardControls;
    i = 0;
    do {
        SzDuel_ClearCardControl(p);
        i += 1;
        p += 0xA0;
    } while (i < 6);
}

typedef struct State_001CDD90 {
    s32 value;
    u8 padding[0x94];
    s16 field98;
    s16 field9A;
    u32 field9C : 26;
    u32 reserved : 6;
} State_001CDD90;

typedef struct Flags_001CDD90 {
    s8 reserved : 2;
    s8 bit2 : 1;
    s8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags_001CDD90;

/* Clears one card control record. Returns 0 for none. */
s32 SzDuel_ClearCardControl(u8 *control) {
    State_001CDD90 *state = (State_001CDD90 *)control;
    Flags_001CDD90 *flags;

    if (control == NULL) {
        return 0;
    }
    state->value = 0;
    state->field98 = 0;
    state->field9A = 0;
    state->field9C = 0xFF;
    flags = (Flags_001CDD90 *)(control + 0x9F);
    flags->bit2 = 0;
    flags->bit3 = 0;
    flags->bit4 = 0;
    flags->bit5 = 0;
    flags->bit6 = 0;
    flags->bit7 = 0;
    return 1;
}

/* Card control record `index` (0..5), or NULL. */
void *SzDuel_GetCardControl(s32 index) {
    if (index < 0 || index >= 6) {
        return NULL;
    }

    return &cardControls[index * 0xA0];
}

typedef struct Flags_001CDEB0 {
    s8 unused : 3;
    s8 position : 1;
    s8 rotation : 1;
    s8 rotation2 : 1;
    s8 scale : 1;
    s8 color : 1;
} Flags_001CDEB0;

typedef struct Output_001CDEB0 {
    f32 position[4];
    s32 rotation[4];
    s32 rotation2[4];
    f32 scale[4];
    u8 color[4];
} Output_001CDEB0;

typedef struct Blend_001CDEB0 {
    Output_001CDEB0 *output;
    u8 padding04[12];
    f32 position0[4];
    f32 position1[4];
    s32 rotation0[4];
    s32 rotation1[4];
    s32 rotation20[4];
    s32 rotation21[4];
    f32 scale0[4];
    f32 scale1[4];
    u8 color0[4];
    u8 color1[4];
    u16 duration;
    u16 progress;
    u8 padding9C[3];
    Flags_001CDEB0 flags;
} Blend_001CDEB0;

/* Moves a card along its control record's path (blends its position and turn). */
s32 SzDuel_DoCardControl0(void *control) {
    extern s32 func_001A22C0(f32);
    Output_001CDEB0 *output;
    f32 blend;
    f32 inverse;
    Blend_001CDEB0 *src = control;

    output = src->output;
    if (output != NULL) {
        blend = (f32)src->progress / (f32)src->duration;
        inverse = 1.0f - blend;
        if (src->flags.position) {
            output->position[0] = src->position0[0] * inverse + src->position1[0] * blend;
            output->position[1] = src->position0[1] * inverse + src->position1[1] * blend;
            output->position[2] = src->position0[2] * inverse + src->position1[2] * blend;
            output->position[3] = src->position0[3] * inverse + src->position1[3] * blend;
        }
        if (src->flags.rotation) {
            output->rotation[0] = func_001A22C0((f32)src->rotation0[0] * inverse + (f32)src->rotation1[0] * blend) % 0x10000;
            output->rotation[1] = func_001A22C0((f32)src->rotation0[1] * inverse + (f32)src->rotation1[1] * blend) % 0x10000;
            output->rotation[2] = func_001A22C0((f32)src->rotation0[2] * inverse + (f32)src->rotation1[2] * blend) % 0x10000;
            output->rotation[3] = func_001A22C0((f32)src->rotation0[3] * inverse + (f32)src->rotation1[3] * blend) % 0x10000;
        }
        if (src->flags.rotation2) {
            output->rotation2[0] = func_001A22C0((f32)src->rotation20[0] * inverse + (f32)src->rotation21[0] * blend) % 0x10000;
            output->rotation2[1] = func_001A22C0((f32)src->rotation20[1] * inverse + (f32)src->rotation21[1] * blend) % 0x10000;
            output->rotation2[2] = func_001A22C0((f32)src->rotation20[2] * inverse + (f32)src->rotation21[2] * blend) % 0x10000;
            output->rotation2[3] = func_001A22C0((f32)src->rotation20[3] * inverse + (f32)src->rotation21[3] * blend) % 0x10000;
        }
        if (src->flags.scale) {
            output->scale[0] = src->scale0[0] * inverse + src->scale1[0] * blend;
            output->scale[1] = src->scale0[1] * inverse + src->scale1[1] * blend;
            output->scale[2] = src->scale0[2] * inverse + src->scale1[2] * blend;
            output->scale[3] = src->scale0[3] * inverse + src->scale1[3] * blend;
        }
        if (src->flags.color) {
            output->color[2] = func_001A22C0((f32)src->color0[2] * inverse + (f32)src->color1[2] * blend);
            output->color[1] = func_001A22C0((f32)src->color0[1] * inverse + (f32)src->color1[1] * blend);
            output->color[0] = func_001A22C0((f32)src->color0[0] * inverse + (f32)src->color1[0] * blend);
            output->color[3] = func_001A22C0((f32)src->color0[3] * inverse + (f32)src->color1[3] * blend);
        }
        return 1;
    }
    return 0;
}

/* Draws the monsters and cards on the board. */
void SzDuel_DrawUnit(void) {
    RhBase_SetVifPacketArea(SzDuel_DrawUnit_Pipe(RhBase_GetVifPacketArea()));
}

typedef union Color_001CE430 {
    f32 value;
    struct { u8 r, g, b, a; } channels;
} Color_001CE430;

typedef struct Flags57_001CE430 {
    s8 unused : 6;
    s8 selected : 1;
    s8 unused7 : 1;
} Flags57_001CE430;

typedef struct Flags58_001CE430 {
    s8 hidden : 1;
    s8 unused : 7;
} Flags58_001CE430;

typedef struct Object_001CE430 {
    u8 pad0[0x30];
    s32 render;
    s16 x, z;
    u8 pad38[8];
    u8 cardX, cardZ;
    u8 pad42[2];
    u8 owner, state, model;
    u8 pad47[2];
    u8 moving, turning;
    u8 pad4B[4];
    u8 flags4F;
    u8 pad50;
    u8 status51;
    u8 pad52;
    u8 progress;
    u8 pad54[3];
    Flags57_001CE430 flags57;
    Flags58_001CE430 flags58;
} Object_001CE430;

typedef struct Info_001CE430 {
    u8 pad[0x14];
    s16 height;
} Info_001CE430;

typedef union Render_001CE430 {
    __int128 value;
    s32 words[4];
} Render_001CE430;

extern Color_001CE430 D_002914E0;
extern Color_001CE430 D_002914E8;
extern Color_001CE430 D_002914F0;
extern Render_001CE430 D_00291500;
extern u16 D_00318116;

/* Draws the monsters and cards on the board, lit by the field and turned to face their way. */
s32 SzDuel_DrawUnit_Pipe(s32 packet) {
    extern f32 SzModel_GetAnimFrame();
    extern s32 SzGame_GetMode();
    u32 mode;
    Color_001CE430 *tint;
    f32 position[4];
    Render_001CE430 render;
    Color_001CE430 ownColor, otherColor, warningColor;
    u8 *game;
    f32 *pos;
    u8 *player;
    s32 row, column;
    Object_001CE430 *object;
    s32 selected;
    s32 model;
    Info_001CE430 *info;
    s32 extraModel, extra;
    u8 alpha;
    f32 fade;

    game = duelState.b;
    player = duelState.b + D_003181E4 * 0x350;
    mode = SzGame_GetMode(1);
    alpha = (u8)((((s32)D_00318116 >> 8) & 0xFF) + 0x40);
    ownColor = D_002914E0;
    ownColor.channels.r = D_003181E4 == 0 ? 0 : 0x60;
    ownColor.channels.g = game[0xD54] == 0 ? 0 : 0x60;
    ownColor.channels.b = game[0xD54] == 0 ? 0x80 : 0x60;
    ownColor.channels.a = alpha;
    otherColor = D_002914E8;
    otherColor.channels.r = game[0xD54] == 0 ? 0x60 : 0;
    otherColor.channels.g = game[0xD54] == 0 ? 0x60 : 0;
    otherColor.channels.b = game[0xD54] == 0 ? 0x60 : 0x80;
    otherColor.channels.a = alpha;
    warningColor = D_002914F0;
    warningColor.channels.r = game[0xD54] == 0 ? 0x60 : 0x60;
    warningColor.channels.g = game[0xD54] == 0 ? 0 : 0x80;
    warningColor.channels.b = game[0xD54] == 0 ? 0x80 : 0;
    warningColor.channels.a = alpha;
    tint = NULL;
    pos = NULL;
    fade = (f32)(u32)(u8)SzEffect_GetBlackOutForMonster() / 128.0f;
    SzEffect_SetIntensityOnly(4, fade);
    SzEffect_SetIntensityOnly(5, fade);
    if (mode == 1) {
        Object_001CE430 *target;
        target = (Object_001CE430 *)SzDuel_GetMapUnit(player[0x33D], player[0x33E]);
        if (target != NULL && target->owner != game[0xD54]) {
            tint = &otherColor;
        } else {
            tint = &ownColor;
        }
        if (game[0xD57] >= 0x1D) {
            tint = &warningColor;
        }
    }
    if (mode < 2U) {
        pos = position;
    }
    row = 0;
    do {
        column = 0;
        do {
            object = (Object_001CE430 *)SzDuel_GetUnit(row, column);
            selected = 0;
            render = D_00291500;
            if (object != NULL) {
                model = object->model;
                if (SzModel_IsModelDisp(model) != 0 &&
                    (object->state == 0 || object->status51 != 0 || object->progress != 0)) {
                    info = (Info_001CE430 *)SzDuel_GetMapInfo(object->cardX, object->cardZ);
                    if (mode == 1 && game[0xD38] == 0) {
                        Object_001CE430 *target;
                        if (object->moving != 0 || object->turning != 0) {
                            if ((u32)func_001A23B0(SzModel_GetAnimFrame(model)) < 2U) {
                                SzModel_SetAnimDir(model, 0);
                            }
                        } else {
                            SzModel_SetAnimDir(model, 1);
                        }
                        target = *(Object_001CE430 **)(game + 0x6C8);
                        if (target != NULL) {
                            if (target == object) {
                                selected = 1;
                            } else if (target->flags57.selected &&
                                       *(Object_001CE430 **)(game + 0x6CC) != NULL &&
                                       *(Object_001CE430 **)(game + 0x6CC) == object) {
                                selected = 1;
                            }
                        }
                        if (selected == 0) {
                            SzDuel_TrimUnitDir1(object->owner, object->state);
                        }
                        render.words[1] = object->render;
                    }
                    if (pos != NULL) {
                        if (object->flags58.hidden) {
                            pos[2] = 0.0f;
                            pos[1] = 0.0f;
                            pos[0] = 0.0f;
                        } else {
                            s32 height;
                            u32 remaining;
                            height = info->height;
                            height = height > 0 ? height : 0;
                            pos[0] = (f32)object->x;
                            pos[1] = (f32)(height * 35) / 128.0f;
                            pos[2] = (f32)object->z;
                            if (object->flags4F & 4) {
                                remaining = 128 - object->progress;
                                remaining = (s32)remaining > 0 ? remaining : 0;
                                pos[1] -= (50.0f * (f32)remaining) / 128.0f;
                            }
                        }
                    }
                    if (selected) {
                        SzModel_SetFilter(model, 1, tint);
                    }
                    packet = SzModel_ExSort_Pipe(packet, model, (s32)pos, (s32)&render, 0, 0, 0x80FFFFF6);
                    if (selected) {
                        SzModel_SetFilter(model, 1, NULL);
                    }
                }
            }
            column++;
        } while (column < 6);
        row++;
    } while (row < 2);
    extra = 0;
    do {
        extraModel = extra + 0x20;
        if (SzModel_IsModelDisp(extraModel)) {
            packet = SzModel_ExSort_Pipe(packet, extraModel, NULL, NULL, 0, 0, 0x80FFFFF6);
        }
        extra++;
    } while (extra < 2);
    return packet;
}

typedef struct Vec4_001CEA50 {
    f32 x, y, z, w;
} Vec4_001CEA50;

typedef struct Flags_001CEA50 {
    s8 unused : 4;
    s8 horizontal : 1;
    s8 enabled : 1;
    s8 colored : 1;
    s8 reserved : 1;
} Flags_001CEA50;

typedef struct Draw_001CEA50 {
    u8 pad00[0x10];
    Vec4_001CEA50 position;
    u8 bounds[0x10];
    Vec4_001CEA50 color;
    u8 pad40[0x41];
    Flags_001CEA50 flags;
    u8 pad82[0xE];
} Draw_001CEA50;

extern Vec4_001CEA50 D_0031825C;
extern s32 D_00318270;

/* Debug: draws one card picked with the pad. */
void SzDuel_DrawCardTest(void) {
    extern void SzDuel_ClearDrawCard();
    u8 matrix[0x60];
    Draw_001CEA50 draw;

    SzDuel_ClearDrawCard(&draw);
    draw.flags.enabled = 1;
    draw.flags.colored = 0;
    draw.flags.reserved = 0;
    SzDuel_InitCardInfo(matrix, SzDuel_Xax2New(D_00318270));
    Ex3d_GetLookVector((s32) draw.bounds);
    draw.position = D_0031825C;
    SzDuel_StartCardSession();
    draw.flags.horizontal = 1;
    SzDuel_GetCardNodeOnScreen(&draw, 0, -192.0f, 0.0f);
    SzDuel_SetupCard((s32) matrix, (s32) &draw);
    SzDuel_DrawCard((s32) &draw);
    draw.flags.horizontal = 0;
    SzDuel_GetCardNodeOnScreen(&draw, 0, 0.0f, -96.0f);
    SzDuel_SetupCard((s32) matrix, (s32) &draw);
    SzDuel_DrawCard((s32) &draw);
    draw.flags.horizontal = 1;
    Ex3d_GetPointOnScreen(&draw, 192.0f, 0.0f);
    SzDuel_SetupCard((s32) (SzDuel_GetCardNode(&draw, 1) ? matrix : NULL), (s32) &draw);
    SzDuel_DrawCard((s32) &draw);
    draw.flags.horizontal = 0;
    Ex3d_GetPointOnScreen(&draw, 0.0f, 96.0f);
    SzDuel_SetupCard((s32) (SzDuel_GetCardNode(&draw, 1) ? matrix : NULL), (s32) &draw);
    SzDuel_DrawCard((s32) &draw);
    if (SzPad_Check(0, 1, 0x80) != 0) {
        draw.flags.colored = 1;
        draw.color.x = 0.46875f;
        draw.color.y = 0.489130437f;
        draw.color.z = 1.0f;
        draw.color.w = 0.0f;
        draw.flags.horizontal = 1;
        Ex3d_GetPointOnScreen(&draw, 0.0f, 96.0f);
        SzDuel_SetupCard((s32) (SzDuel_GetCardNode(&draw, 1) ? matrix : NULL), (s32) &draw);
        SzDuel_DrawCard((s32) &draw);
    }
    SzDuel_FinishCardSession();
}

typedef struct Record_001CECF0 {
    u8 padding[0x33C];
    u8 kind;
    u8 low;
    u8 high;
    u8 tail[0x11];
} Record_001CECF0;

extern s32 (*duelistControllers[])(u16, void *); /* original: g_aLogFunc */
extern s8 practiceDuelFlag; /* original: Rensyu_flg */
extern s8 practiceDuelEnd; /* original: Rensyu_END */

/* The buttons side `side` presses this frame (`mode` = pad check mode): the first/second pad for a human
   (ids 100/101), else what its logic function duelistControllers[id] returns (computer duelists and the tutorial). */
s32 lSzDuel_GetControl(s32 side, s32 mode) {
    u8 *base = duelState.b;
    s32 ret = 0;
    Record_001CECF0 *record = (Record_001CECF0 *)(duelState.b + side * 0x350);
    void *selected;
    s32 result;

    switch (record->kind) {
    case 0x64:
        ret = SzPad_Check(0, mode, 0xFFFF) & 0xFFFF;
        break;
    case 0x65:
        ret = SzPad_Check(1, mode, 0xFFFF) & 0xFFFF;
        break;
    default:
        if (record->kind < 0x64) {
            selected = record;
            if (TaTuto_IsTuto(side) != 0) {
                selected = base;
            }
            if (SzView_InqRequest(-1, -1) == NULL) {
                result = duelistControllers[record->kind]((u16)((record->high << 8) | record->low), selected);
                if (result < 0) {
                    if (practiceDuelFlag != 0) {
                        if (result == -1) {
                            Taku_Camp_Go_Practice_Duel(1);
                        } else {
                            practiceDuelFlag = 0;
                            practiceDuelEnd = 1;
                            SzGame_Pop();
                        }
                    } else {
                        SzGame_Pop();
                    }
                } else {
                    ret = result & 0xFFFF;
                }
            }
        }
        break;
    }
    return ret;
}

#include "common.h"

typedef struct Vec4_001CEE60 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4_001CEE60;

typedef struct Flags8_001CEE60 {
    s8 b0 : 1;
    s8 b1 : 1;
    s8 b2 : 1;
    s8 b3 : 1;
    s8 b4 : 1;
    s8 b5 : 1;
    s8 b6 : 1;
    s8 b7 : 1;
} Flags8_001CEE60;

typedef struct Flags56_001CEE60 {
    s8 b01 : 2;
    s8 b23 : 2;
    s8 b45 : 2;
    s8 b67 : 2;
} Flags56_001CEE60;

typedef struct Object_001CEE60 {
    u8 pad0[4];
    u8 *view;
    u8 pad8[0x2C];
    s16 px;
    s16 pz;
    u8 pad38[4];
    u16 id;
    u8 pad3E[2];
    u8 fromX;
    u8 fromZ;
    u8 pad42[2];
    u8 x;
    u8 z;
    u8 model;
    u8 pad47[8];
    u8 flags4F;
    u8 pad50;
    u8 status51;
    u8 pad52;
    u8 progress;
    u8 pad54[2];
    Flags56_001CEE60 flags56;
    Flags8_001CEE60 flags57;
    Flags8_001CEE60 flags58;
} Object_001CEE60;

typedef struct UFlags8_001CEE60 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
} UFlags8_001CEE60;



extern Vec4_001CEE60 D_00291510;
extern Vec4_001CEE60 D_00291520;
extern Vec4_001CEE60 D_00291530;
extern u16 D_002CDF4C[];

s32 func_001E7F70(s32, s32, s32);

extern u8 D_003181E7;
extern u8 D_003181F3;

#define DUEL duel
#define DUEL_S16(off) (*(s16 *)(duel + (off)))
#define MIN_001CEE60(a, b) ((a) < (b) ? (a) : (b))
#define MAX_001CEE60(a, b) ((a) > (b) ? (a) : (b))
#define ABS_001CEE60(x) ((x) >= 0 ? (x) : -(x))
#define REC_S32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define DUEL_U32(off) (*(u32 *)(duel + (off)))
typedef struct { u8 pad[0xC64]; u32 c64; } C64_001CEE60;
#define DUEL_DUO(off) (*(Object_001CEE60 **)(duel + (off)))
#define F64 ((Flags8_001CEE60 *)(duel + 0xD64))
#define F65 ((Flags8_001CEE60 *)(duel + 0xD65))
#define F66 ((Flags8_001CEE60 *)(duel + 0xD66))
#define F67 ((Flags8_001CEE60 *)(duel + 0xD67))
#define U66 ((UFlags8_001CEE60 *)(duel + 0xD66))

/* Whether a board object's model is still moving. */
static inline s32 busy_001CEE60(Object_001CEE60 *p) {
    return p != NULL && p->flags57.b4 && func_001F1300(p->model) && p->progress != p->status51;
}

/* Card control record n, or NULL. */
static inline u8 *slot_001CEE60(s32 n) {
    if (n < 0 || n >= 6) {
        return NULL;
    }
    return cardControls + n * 0xA0;
}

/* Frees a card object. */
static inline void freeobj_001CEE60(u8 *obj) {
    if (obj != NULL) {
        func_001CD560(obj);
        *(s32 *)(obj + 0x90) = 0;
    }
}

/* Frees a card control record and its card. */
static inline void freeslot_001CEE60(u8 *p) {
    if (p != NULL) {
        if (*(u8 **)p != NULL) {
            freeobj_001CEE60(*(u8 **)p);
        }
        func_001CDD90(p);
    }
}

/* Drops card control slot n (and its hand card). */
static inline void drop_001CEE60(u8 *duel, s32 n) {
    u8 *p;

    if (n != 0) {
        func_001DF2C0(duel[0xD54], n - 1);
    }
    if ((p = slot_001CEE60(n)) != NULL && *(u8 **)p != NULL) {
        freeslot_001CEE60(p);
    }
}

/* Runs one frame of the duel: the state machine for turns, moves, summons, battles, fusions, effects and the end. */
s32 SzDuel_Act(void) {
    extern s32 func_001F48F0(s32, s32, s32, s32, s32);
    extern s32 func_001E1D10();
    extern s32 func_001F3910();
    extern s32 func_001F13F0();
    extern s32 func_001E19D0();
    extern void func_001DDD80();
    extern s32 func_001DE2A0();
    extern s32 func_0024F780();
    extern s32 func_0026EA00();
    extern s32 func_001E17D0();
    extern s32 func_001E1760();
    extern s32 func_001E08F0();
    extern s32 func_001A22C0(f32);
    extern s32 func_001E24E0();
    extern s32 func_002170A0();
    extern u16 func_00203A40();
    extern u16 func_001CECF0();
    extern s32 func_001F19A0();
    extern s32 func_00215D30();
    extern void func_00228150(s8);
    extern s32 func_0026EB10();
    s32 j_F;
    s32 i_F;
    s32 nx_2969;
    s32 card_2717;
    s32 i_419;
    s32 nx_F;
    u8 *duel;
    u8 *me;
    u8 *cur;
    s32 hand0;
    s32 hand1;
    u8 prev;
    s32 picked;
    s32 prevX;
    s32 prevZ;
    s32 fullA;
    s32 bx_847;
    s32 fullB;
    s32 soloA;
    s32 soloB;
    s32 mDpad;
    s32 mUD;
    s32 mLR;
    s32 mLR2;
    s32 mR2;
    s32 lifeA100;
    s32 lifeB100;
    s32 lifeA;
    s32 lifeB;
    s32 held;
    s32 held16;
    s32 mUp;
    s32 mLeft;
    u8 hpA;
    u8 hpB;
    s32 cam;
    u8 *list;
    s32 j;
    s32 busy;
    s32 v;
    s32 h;
    u8 *p;
    Vec4_001CEE60 camv;
    Vec4_001CEE60 pos;
    Vec4_001CEE60 pos7;
    Vec4_001CEE60 tgt;
    Vec4_001CEE60 pos2;
    Vec4_001CEE60 tgt2;
    Vec4_001CEE60 spot;
    Object_001CEE60 *obj;
    s32 posA;
    s32 posB;
    s32 field;
    s32 *anim;
    s32 last;
    u16 pad;
    Vec4_001CEE60 look;
    Vec4_001CEE60 eye;
    Vec4_001CEE60 look2;
    Vec4_001CEE60 eye2;
    Vec4_001CEE60 look3;
    Vec4_001CEE60 eye3;
    s32 flip;
    f32 *cpos;
    f32 *cpos_847;
    f32 hgt;
    f32 dz;
    f32 dx;
    f32 lim;
    s32 k;
    s32 side;
    u8 cx;
    u8 cz;
    u8 model;
    s32 bz_847;
    s32 i;
    s32 t;
    s32 bm;
    s32 r;
    s32 *rec;
    s32 win;
    s32 lose;
    s32 slot;
    s32 wonA;
    s32 res;
    s32 wonB;
    s32 low;
    u32 high;
    u32 reply;
    s32 from;
    s32 to;
    u8 *sl;
    u8 *sub;
    u16 rep;
    s32 pressed;
    u16 trig;
    u16 swap;
    u16 keys;
    s32 inHand;
    s32 busy_847;
    s32 onField;
    s32 x0;
    s32 stickRX;
    s32 stickRY;
    s32 stickLY;
    s32 angB_847;
    s32 speed;
    s32 moved;
    s32 gx;
    s32 tx;
    s32 tz;
    s32 angA_847;
    s32 old;
    s32 diff;
    s32 n;
    s32 card;
    s32 scrollA;
    s32 scrollB;
    s32 lock;
    s32 lim2;
    s32 loops;
    s32 nx;
    s32 nz;
    s32 port;
    s32 z0;
    s32 x1;
    s32 z1;
    s32 px;
    s32 pz;
    s32 step;
    s32 lvl;
    s32 ok;
    s32 have;
    s32 need;
    s32 done_847;
    s32 t2;
    s8 bit;
    Object_001CEE60 tmpo;

    duel = duelState.b;
    me = &duelState.b[D_003181E4 * 0x350];
    list = me + 0x1D0;
    cam = func_001F9AD0(0);
    hand0 = func_001DF470(0);
    hand1 = func_001DF470(1);
    prev = D_003181E7;
    hpA = func_001DE4E0(0);
    hpB = func_001DE4E0(1);
    lifeA = hpA;
    if (lifeA >= 100) {
        fullA = 1;
    } else {
        fullA = 0;
    }
    lifeB = hpB;
    if (lifeB >= 100) {
        fullB = 1;
    } else {
        fullB = 0;
    }
    soloB = 1;
    if (DUEL[0xD54] == 0) {
        soloA = 1;
    } else {
        soloA = 0;
    }
    if (DUEL[0xD54] == 1) {
        soloB = 1;
    } else {
        soloB = 0;
    }
    picked = 0;
    switch (DUEL[0xD57]) {
    case 0:
        if (me[0x33C] < 100) {
            DUEL[0xD3A] = 0x80;
        }
        DUEL[0xD57] = 1;
    case 1:
        p = func_001F3EA0(0, 0x26C);
        if (p == NULL || (*p & 7) < 2) {
            return 0;
        }
        DUEL[0xD57] = 2;
    case 2:
        if (me[0x33C] < 100) {
            if (func_001FF300() != 0) {
                return 0;
            }
            DUEL[0xD34] = 0x80;
            func_001E2340();
            func_001D9820(1, DUEL[0xD52]);
            DUEL[0xD57] = 0x15;
            return 0;
        }
        DUEL[0xD57] = 3;
    case 3:
        pos = *(Vec4_001CEE60 *)func_001FAF60(0);
        if (pos.x < 600.0f) {
            pos.x += 20.0f;
            func_001FB360(0, &pos.x);
            return 0;
        }
        DUEL[0xD35] = 0;
        DUEL[0xD57] = 4;
    case 4:
        if (DUEL[0xD35] != 0) {
            DUEL[0xD35]--;
            return 0;
        }
        DUEL[0xD57] = 5;
    case 5:
        v = func_001E2450(0, 0);
        if (v < 0) {
            v = MIN_001CEE60(v + 8, 0);
            for (i = 0; i < 7; i++) {
                for (j = 0; j < 7; j++) {
                    func_001E23A0(j, i, (s16)v);
                }
            }
            return 0;
        }
        DUEL[0xD35] = 0;
        DUEL[0xD57] = 6;
    case 6:
        if (DUEL[0xD35] != 0) {
            DUEL[0xD35]--;
            return 0;
        }
        DUEL[0xD57] = 7;
    case 7:
        pos7 = *(Vec4_001CEE60 *)func_001FAF60(0);
        func_001E10F0(me[0x33D], me[0x33E], 0, &tgt);
        pos7.x = 150.0f;
        func_001FA8A0(0, 0, 3, 0x1E, 0, &tgt);
        func_001FA8A0(0, 0, 4, 0x1E, 0, &pos7);
        DUEL[0xD35] = 0;
        DUEL[0xD57] = 8;
    case 8:
        if (func_001FA6F0(0, 0) != NULL) {
            return 0;
        }
        if (DUEL[0xD35] != 0) {
            DUEL[0xD35]--;
            return 0;
        }
        DUEL[0xD57] = 9;
    case 9:
        if (DUEL[0xD34] < 0x80) {
            DUEL[0xD34] = MIN_001CEE60(DUEL[0xD34] + 8, 0x80);
            return 0;
        }
        DUEL[0xD35] = 0;
        DUEL[0xD57] = 10;
    case 10:
        if (DUEL[0xD35] != 0) {
            DUEL[0xD35]--;
            return 0;
        }
        DUEL[0xD57] = 11;
    case 11:
        pos2 = *(Vec4_001CEE60 *)func_001FAF60(0);
        func_001E10F0(me[0x33D], me[0x33E], 0, &tgt2);
        tgt2.y = *(s8 *)(me + 0x345);
        pos2.x = 100.0f;
        pos2.y = func_001A6C30(6.2831855f + (3.1415927f + pos2.y), 6.2831855f);
        pos2.z = 0.58904862f;
        func_001FA8A0(0, 0, 3, 0x1E, 0, &tgt2);
        func_001FA8A0(0, 0, 4, 0x1E, 0, &pos2);
        for (i_419 = 0, cur = duel; i_419 < 2; i_419++, cur += 0x350) {
            if ((p = (u8 *)func_001DF540(i_419, 0)) != NULL) {
                REC_S32(cur, 0x330) = func_001F48F0(0, 0x26C, 0, (p[0x41] << 8) | p[0x40], 0);
            }
            if (REC_S32(cur, 0x330) < 0) {
                func_001E1C10(i_419, 0, 1, 0);
            }
        }
        DUEL[0xD57] = 12;
    case 12:
        busy = 0;
        for (i = 0; i < 2; i++) {
            rec = &REC_S32(duel + i * 0x350, 0x330);
            if ((h = *rec) >= 0) {
                if ((v = func_001F52D0(h)) >= 0) {
                    if (v == 2) {
                        func_001E1C10(i, 0, 1, 0);
                        *rec = -1;
                    }
                    busy = 1;
                }
            }
        }
        if (busy != 0) {
            return 0;
        }
        DUEL[0xD57] = 13;
    case 13:
        if (func_001FA6F0(0, 0) != NULL) {
            return 0;
        }
        for (i = 0; i < 2; i++) {
            if (func_001E1D10(i, 0) < 0x80) {
                return 0;
            }
        }
        DUEL[0xD35] = 30;
        DUEL[0xD57] = 14;
    case 14:
        if (DUEL[0xD35] != 0) {
            DUEL[0xD35]--;
            return 0;
        }
        if (func_001FF300() != 0) {
            return 0;
        }
        DUEL[0xD57] = 15;
    case 15:
        DUEL[0xD57] = 16;
    case 16:
        DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 8, 0x40);
        if (DUEL_S16(0xC9C) < 0x40) {
            return 0;
        }
        DUEL[0xD57] = 17;
    case 17:
        DUEL[0xD57] = 18;
        return 0;
    case 18:
        DUEL_S16(0xC9C) = MAX_001CEE60(DUEL_S16(0xC9C) - 8, 0);
        if (DUEL_S16(0xC9C) > 0) {
            return 0;
        }
        DUEL[0xCB2] = 0x18;
        func_001D9820(1, DUEL[0xD52]);
        DUEL[0xD57] = 0x15;
    }
    {
        DuelState *q = &duelState.s;
        if (q->hold != 0) {
            q->dirs.dir1 = 1;
        }
        q->wave1 = MIN_001CEE60(MAX_001CEE60(q->wave1 + (q->dirs.dir1 << 9), 0), 0x8000);
        if ((q->wave1 == 0) || ((s32) q->wave1 >= 0x8000)) {
            q->dirs.dir1 = (s8) -q->dirs.dir1;
        }
    }
    {
        DuelState *q = &duelState.s;
        s32 st = q->dirs.dir2 << 0xB;
        q->wave2 = MIN_001CEE60(MAX_001CEE60(q->wave2 + st, 0), 0x8000);
        if ((q->wave2 == 0) || ((s32) q->wave2 >= 0x8000)) {
            q->dirs.dir2 = (s8) -q->dirs.dir2;
        }
    }
    if (DUEL[0xD63] != 0) {
        DUEL[0xD63]--;
    }
    if (F67->b2) {
        u8 vol = 0x80 - ((DUEL[0xD45] << 6) >> 7);
        func_001F6CE0(vol);
        func_001F6CF0(vol);
    }
    if (DUEL[0xD57] == 0x18 && REC_S32(me, 0x1D4) != (DUEL[0xD3C] ? 0xC000 : 0x4000)) {
        DUEL[0xD44] = MIN_001CEE60(DUEL[0xD44] + 0x10, 0x80);
    } else {
        DUEL[0xD44] = MAX_001CEE60(DUEL[0xD44] - 0x10, 0);
    }
    spot.y = *(s8 *)(me + 0x345);
    for (i_F = 0; i_F < 7; i_F++) {
        for (j_F = 0; j_F < 7; j_F++) {
            obj = *(Object_001CEE60 **)func_001DCD00(j_F, i_F);
            h = 0;
            if (obj != NULL && obj->flags58.b0 == 0 && obj->z < 6 &&
                (obj->z == 0 || obj->flags57.b2 != 0 || obj->flags56.b45 != 0)) {
                if (func_001F1370(obj->model) != 0) {
                    spot.x = (j_F - 3) * 50;
                    spot.z = (i_F - 3) * 50;
                    if (func_0020D100(&spot.x, (f32 *)cam) < 80.0f) {
                        h = 1;
                    }
                    if (h) {
                        if (obj->flags4F == 0 || obj->flags4F == 1) {
                            obj->flags4F = 1;
                            obj->flags56.b23 = 3;
                        }
                    } else if (obj->flags4F & 1) {
                        if (obj->progress < obj->status51) {
                            obj->flags56.b23 = 1;
                        }
                        if (obj->progress > obj->status51) {
                            obj->flags56.b23 = 3;
                        }
                    }
                }
            }
        }
    }
    if (DUEL[0xD57] >= 0x54 || hand0 == 0 || hand1 == 0) {
        F66->b7 = 0;
        F67->b0 = F66->b7;
    }
    if (F64->b7) {
        if (func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), -1) == 0) {
            F64->b7 = 0;
        }
        return 0;
    }
    if (DUEL_U32(0xC5C) != 0) {
        switch (DUEL_U32(0xC5C) & 0xFFFF) {
        case 5:
            DUEL[0xD50] = DUEL[0xD54] ^ 1;
            F66->b7 = 0;
            F67->b0 = F66->b7;
            DUEL[0xD51] = 3;
            DUEL[0xD57] = 0x54;
            DUEL_U32(0xC5C) = 0;
            break;
        case 8:
            if (hand0 == hand1) {
                DUEL[0xD50] = 2;
            } else if (hand0 > hand1) {
                DUEL[0xD50] = 0;
            } else {
                DUEL[0xD50] = 1;
            }
            F66->b7 = 0;
            F67->b0 = F66->b7;
            DUEL[0xD51] = 1;
            DUEL[0xD57] = 0x54;
            DUEL_U32(0xC5C) = 0;
            break;
        case 1:
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F64->b7 = 1;
            DUEL_U32(0xC5C) = (DUEL_U32(0xC5C) & 0xFFFF0000) | 0x80;
            break;
        case 0x80:
        case 0:
            if ((DUEL_U32(0xC5C) >> 16) == 0xFF) {
                DUEL_U32(0xC5C) = 0;
            } else {
                DUEL_U32(0xC5C) = func_002724F0(DUEL_U32(0xC5C) >> 16, (s32 *)(duel + 0x6E8));
            }
            break;
        }
        return 0;
    }
    if (F65->b0) {
        if (func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), -1) == 0) {
            switch (DUEL_U32(0xC60) & 0xFFFF) {
            case 5:
                func_00216C70(DUEL[0xD54], 0x29F, 1);
                DUEL[0xD50] = DUEL[0xD54];
                F66->b7 = 0;
                F67->b0 = F66->b7;
                DUEL[0xD51] = 2;
                DUEL[0xD57] = 0x54;
                DUEL_U32(0xC60) = 0;
                F65->b0 = 0;
                break;
            case 1:
                DUEL_U32(0xC60) = (DUEL_U32(0xC60) & 0xFFFF0000) | 0x80;
                F65->b0 = 0;
                break;
            }
        }
        return 0;
    }
    if (DUEL_U32(0xC60) != 0) {
        switch (DUEL_U32(0xC60) & 0xFFFF) {
        case 1:
        case 5:
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F65->b0 = 1;
            break;
        case 0x80:
        case 0:
            if ((DUEL_U32(0xC60) >> 16) == 0xFF) {
                DUEL_U32(0xC60) = 0;
            } else {
                DUEL_U32(0xC60) = func_00267C50(DUEL_U32(0xC60) >> 16, duel + 0x6E8);
            }
            break;
        }
        return 0;
    }
    if (DUEL[0xD38] != 0) {
        switch (DUEL[0xD38] & 0xFF) {
        case 1:
            F67->b0 = 0;
            DUEL[0xD3B] = 0x80;
            DUEL[0xD3A] = MIN_001CEE60(DUEL[0xD3A] + 4, 0x80);
            if (DUEL[0xD3A] < 0x80) {
                break;
            }
            F67->b1 = 1;
            DUEL[0xD3E] = 0x80;
            func_001E3850(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, 0);
            func_001E1C10(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, 0, 0x80);
            func_001E19D0(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, 0x80);
            func_001E3850(DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z, 0);
            func_001E1C10(DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z, 0, 0x80);
            func_001E19D0(DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z, 0x80);
            DUEL[0xD38]++;
            break;
        case 2:
            posA = (DUEL_DUO(0x6C8)->x << 8) | DUEL_DUO(0x6C8)->z;
            posB = (DUEL_DUO(0x6CC)->x << 8) | DUEL_DUO(0x6CC)->z;
            field = func_001E22B0(me[0x33D], me[0x33E]);
            if (func_001A82E0(0x16) != 0) {
                func_001A8320(5, field);
                func_001AAAF0(5, 1);
            }
            func_001A8BB0();
            func_001E7F70(1, 0, 0);
            func_001E7F70(2, field, 0);
            func_001E4F00(field);
            func_001E5260(0, posA);
            func_001E5260(1, posB);
            func_001F1070(DUEL_DUO(0x6C8)->model);
            func_001F1070(DUEL_DUO(0x6CC)->model);
            func_001F3910(0, 0x26D, 0);
            func_001F7260(1);
            DUEL[0xD38]++;
        case 3:
            if (func_001FF300() != 0) {
                break;
            }
            func_001F7260(0);
            if ((anim = (s32 *)func_001E5230()) != NULL) {
                last = anim[3] - 1;
                func_001FA8A0(0, 0, 8, 0, -1, anim);
                func_001FB940(0, anim, last, 0, -1, 0);
                func_001FA770(0, 0, 1);
            } else {
                func_001F9FE0(0, 0, 0);
            }
            DUEL[0xD38]++;
        case 4:
            DUEL[0xD3A] = MAX_001CEE60(DUEL[0xD3A] - 4, 0);
            DUEL[0xD3B] = MAX_001CEE60(DUEL[0xD3B] - 4, 0);
            if (DUEL[0xD3A] > 0) {
                break;
            }
            if (DUEL[0xD3B] > 0) {
                break;
            }
            func_00202CB0(4, -1, 1);
            func_001FA770(0, 0, 0);
            DUEL[0xD39] = 0;
            DUEL[0xD38]++;
        case 5:
            pad = 0;
            if (fullA != 0 && (soloA != 0 || fullB == 0)) {
                pad |= func_00203A40(lifeA - 100, 0, 0xFFFF);
            }
            if (fullB != 0 && (soloB != 0 || fullA == 0)) {
                pad |= func_00203A40(lifeB - 100, 0, 0xFFFF);
            }
            if (pad & 0x20) {
                if (func_001A82E0(0x16) != 0) {
                    func_001AAAF0(*(u16 *)(duel + 0xC84), 0);
                }
                DUEL[0xD38]++;
            }
            switch (DUEL[0xD39]) {
            case 0:
                if (func_001FA6F0(0, 0) != NULL) {
                    break;
                }
                DUEL[0xD36] = 0;
                DUEL[0xD39]++;
            case 1:
                hgt = func_001DE260(DUEL_DUO(0x6C8)->id);
                look = D_00291510;
                look.x = MAX_001CEE60(hgt, 50.0f);
                func_001F2050(DUEL_DUO(0x6C8)->model, &eye);
                func_001F9D80(0, &eye);
                func_001FB360(0, &look.x);
                DUEL[0xD35] = 0x3C;
                DUEL[0xD39]++;
            case 2:
                func_001FC210(0, DUEL_DUO(0x6C8)->model, 0, 1, 1.0f);
                if (DUEL[0xD35] != 0) {
                    DUEL[0xD35]--;
                    break;
                }
                DUEL[0xD39]++;
            case 3:
                high = func_001A23B0(func_001F1B50(DUEL_DUO(0x6C8)->model));
                flip = 0;
                if (high >= 2) {
                    break;
                }
                if (D_002CDF4C[DUEL_DUO(0x6C8)->id] & 0x8000) {
                    flip = (s32)(2.0f * ((f32)func_0019A5C8() / 2147483648.0f)) ? 1 : 0;
                }
                func_001F6C10(0);
                func_001F6CA0(0);
                func_001F1830(DUEL_DUO(0x6CC)->model, 0);
                func_001F1A00(DUEL_DUO(0x6CC)->model, 1);
                func_00202CB0(4, -1, 1);
                func_001F0CD0(0, 1, flip);
                DUEL[0xD39]++;
            case 4:
                if (func_001FA6F0(0, 1) != NULL) {
                    break;
                }
                if (func_001F5240(1, -1) != 0) {
                    extern s32 func_001DE2B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
                    break;
                }
                DUEL[0xD39] = (func_001DE2B0(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z,
                                             DUEL_DUO(0x6CC)->fromX, DUEL_DUO(0x6CC)->fromZ, 0) == 3) ? 5 : 0xD;
                break;
            case 5:
                cpos = func_001FAF60(0);
                hgt = 20.0f + (f32)func_001DE260(DUEL_DUO(0x6CC)->id);
                hgt = MAX_001CEE60(hgt, 50.0f);
                dz = hgt - cpos[0];
                func_001FC210(0, DUEL_DUO(0x6CC)->model, 0, 1, 1.0f);
                lim = 2.0f;
                dz = MIN_001CEE60(MAX_001CEE60(dz, -lim), lim);
                func_001FB6A0(0, 0, 1, 0.0f, 0.0f, dz);
                if (!(dz <= 1e-6f)) {
                    break;
                }
                if (func_001F13F0(DUEL_DUO(0x6CC)->model) != 0) {
                    break;
                }
                DUEL[0xD39]++;
            case 6:
                DUEL[0xD35] = 0x1E;
                DUEL[0xD39]++;
            case 7:
                func_001FC210(0, DUEL_DUO(0x6CC)->model, 0, 1, 1.0f);
                if (DUEL[0xD35] != 0) {
                    DUEL[0xD35]--;
                    break;
                }
                DUEL[0xD39]++;
            case 8:
                high = func_001A23B0(func_001F1B50(DUEL_DUO(0x6CC)->model));
                flip = 0;
                if (high >= 2) {
                    break;
                }
                if (D_002CDF4C[DUEL_DUO(0x6CC)->id] & 0x8000) {
                    flip = (s32)(2.0f * ((f32)func_0019A5C8() / 2147483648.0f)) ? 1 : 0;
                }
                func_001F6C10(0);
                func_001F6CA0(0);
                func_001F1830(DUEL_DUO(0x6C8)->model, 0);
                func_001F1A00(DUEL_DUO(0x6C8)->model, 1);
                func_00202CB0(4, -1, 1);
                func_001F0CD0(1, 1, flip);
                DUEL[0xD39]++;
            case 9:
                if (func_001FA6F0(0, 1) != NULL) {
                    break;
                }
                if (func_001F5240(1, -1) != 0) {
                    break;
                }
                DUEL[0xD39] = (func_001DE2B0(DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z, DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z,
                                             DUEL_DUO(0x6CC)->fromX, DUEL_DUO(0x6CC)->fromZ, 1) == 3) ? 0x12 : 0xC;
                break;
            case 10:
                hgt = func_001DE260(DUEL_DUO(0x6CC)->id);
                look2 = D_00291520;
                look2.x = MAX_001CEE60(hgt, 50.0f);
                func_001F2050(DUEL_DUO(0x6CC)->model, &eye2);
                func_001FA8A0(0, 0, 3, 0x5A, 0, &eye2);
                func_001FA8A0(0, 0, 4, 0x5A, 0, &look2);
                DUEL[0xD39]++;
            case 11:
                if (func_001FA6F0(0, 0) != NULL) {
                    break;
                }
                DUEL[0xD36] = 0x80;
                DUEL[0xD39] = 0xD;
            case 12:
            case 13:
                k = DUEL[0xD39] - 12;
                /* record k's offset is the pointer operand: MWCC adds the pointer operand first (addu v1,v1,s1) */
                *(s32 *)((u8 *)(k * 0x350) + (u32)duel + 0x330) = -1;
                DUEL[0xD35] = 0;
                DUEL[0xD39] = k + 14;
            case 14:
            case 15:
            {
                f32 ldz;
                f32 ldx;

                cpos_847 = func_001FAF60(0);
                    side = DUEL[0xD39] - 14;
                    bx_847 = side ? DUEL_DUO(0x6CC)->x : DUEL_DUO(0x6C8)->x;
                    bz_847 = side ? DUEL_DUO(0x6CC)->z : DUEL_DUO(0x6C8)->z;
                    bm = side ? DUEL_DUO(0x6CC)->model : DUEL_DUO(0x6C8)->model;
                    hgt = 20.0f + (f32)func_001DE260(side ? DUEL_DUO(0x6CC)->id : DUEL_DUO(0x6C8)->id);
                    hgt = MAX_001CEE60(hgt, 50.0f);
                    ldx = hgt - cpos_847[0];
                    ldz = 0.39269909f - cpos_847[2];
                    res = func_001F13F0(bm);
                    t = DUEL[0xD36];
                    t = MIN_001CEE60(t, 0x80);
                    angA_847 = (t << 7) >> 7;
                    angB_847 = (t << 8) >> 7;
                    lim = (2.0f * (f32)t) / 128.0f;
                    done_847 = 0;
                    func_001FC210(0, bm, 0, 1, 1.0f);
                    ldx = MIN_001CEE60(MAX_001CEE60(ldx, -lim), lim);
                    func_001FB6A0(0, 0, 1, -((3.1415927f * (f32)angB_847) / 32768.0f),
                                  MIN_001CEE60(MAX_001CEE60(ldz, -((3.1415927f * (f32)angA_847) / 32768.0f)), (3.1415927f * (f32)angA_847) / 32768.0f), ldx);
                    if (DUEL[0xD36] < 0xFF) {
                        DUEL[0xD36]++;
                    }
                    if (side == 0) {
                        if (func_001DE2B0(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z,
                                          DUEL_DUO(0x6CC)->fromX, DUEL_DUO(0x6CC)->fromZ, 1) == 4) {
                            r = func_001F13F0(DUEL_DUO(0x6CC)->model);
                            if (r != 4) {
                                if (r == 0) {
                                    func_001F1550(DUEL_DUO(0x6CC)->model, 4);
                                }
                                done_847 = 1;
                            }
                        }
                    }
                    if (res == 4) {
                        rec = &REC_S32(duel + side * 0x350, 0x330);
                        busy_847 = func_001F19A0(bm);
                        t = func_001F27A0(bm);
                        if (busy_847 != 0) {
                            break;
                        }
                        if (*rec < 0) {
                            *rec = func_001F48F0(0, 0x26D, 0, (bx_847 << 8) | bz_847, 0);
                            break;
                        }
                        if (DUEL[0xD35] == 0) {
                            if (func_001F52D0(*rec) == 2) {
                                DUEL[0xD35]++;
                            }
                            break;
                        }
                        if (t > 0) {
                            func_001F2800(bm, MAX_001CEE60(t - 1, 0));
                            break;
                        }
                        if (func_001F51D0(*rec) != 0) {
                            break;
                        }
                        if (DUEL[0xD35] < 0x1E) {
                            DUEL[0xD35]++;
                            break;
                        }
                        if (done_847 != 0) {
                            break;
                        }
                    } else if (DUEL[0xD35] < 0x5A) {
                        DUEL[0xD35]++;
                        break;
                    }
                    if (side != 0) {
                        r = func_001DE2B0(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z,
                                          DUEL_DUO(0x6CC)->fromX, DUEL_DUO(0x6CC)->fromZ, 1);
                        if (r != func_001DE2B0(DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z, DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z,
                                               DUEL_DUO(0x6CC)->fromX, DUEL_DUO(0x6CC)->fromZ, 1)) {
                            if (r == 4) {
                                DUEL[0xD39] = 0x10;
                                break;
                            }
                        }
                    } else if (func_001DE2B0(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z,
                                             DUEL_DUO(0x6CC)->fromX, DUEL_DUO(0x6CC)->fromZ, 1) == 4) {
                        if (func_001F19A0(DUEL_DUO(0x6CC)->model) != 0) {
                            break;
                        }
                        DUEL[0xD39] = 0xA;
                        break;
                    }
                    if (func_001A82E0(0x16) != 0) {
                        func_001AAAF0(*(u16 *)(duel + 0xC84), 0);
                    }
                    DUEL[0xD38]++;
                    break;
            }
            case 16:
                flip = 0;
                if (D_002CDF4C[DUEL_DUO(0x6C8)->id] & 0x4000) {
                    flip = (s32)(2.0f * ((f32)func_0019A5C8() / 2147483648.0f)) ? 1 : 0;
                }
                func_001F1830(DUEL_DUO(0x6C8)->model, 0);
                func_001F1A00(DUEL_DUO(0x6C8)->model, 1);
                func_001F0E50(0, 1, flip);
                if (func_001FA6F0(0, 1) != NULL) {
                    func_001FC840(0, 0);
                } else {
                    hgt = func_001DE260(DUEL_DUO(0x6C8)->id);
                    look3 = D_00291530;
                    look3.x = MAX_001CEE60(hgt, 80.0f);
                    func_001F2050(DUEL_DUO(0x6C8)->model, &eye3);
                    func_001F9D80(0, &eye3);
                    func_001FB360(0, &look3.x);
                    func_001FC840(0, 1);
                }
                DUEL[0xD39]++;
            case 17:
                if (func_001FC7F0(0) == 1) {
                    func_001FC210(0, DUEL_DUO(0x6C8)->model, 0, 1, 1.0f);
                } else if (func_001FA6F0(0, 1) != NULL) {
                    break;
                }
                if (func_001F13F0(DUEL_DUO(0x6C8)->model) != 0) {
                    break;
                }
                func_001FC840(0, 0);
                if (func_001A82E0(0x16) != 0) {
                    extern void func_001AAAF0(int n, int b);
                    extern s32 func_001FB6A0(s32 arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1, f32 fparg2);
                    extern s32 func_001A82E0(s32 arg0);
                    func_001AAAF0(*(u16 *)(duel + 0xC84), 0);
                }
                DUEL[0xD38]++;
                break;
            case 18:
                break;
            }
            break;
        case 6:
            func_001FB6A0(0, 0, 1, -0.024543693f, 0.0f, 0.0f);
            DUEL[0xD3A] = MIN_001CEE60(DUEL[0xD3A] + 4, 0x80);
            DUEL[0xD3B] = MIN_001CEE60(DUEL[0xD3B] + 4, 0x80);
            if (DUEL[0xD3A] < 0x80) {
                break;
            }
            if (DUEL[0xD3B] < 0x80) {
                break;
            }
            if (func_001A82E0(0x16) != 0) {
                func_001AAAF0(*(u16 *)(duel + 0xC84), 1);
            }
            DUEL[0xD38]++;
        case 7:
            win = func_001DE2B0(DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z, DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z,
                                DUEL_DUO(0x6CC)->fromX, DUEL_DUO(0x6CC)->fromZ, 1);
            lose = func_001DE2B0(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z,
                                 DUEL_DUO(0x6CC)->fromX, DUEL_DUO(0x6CC)->fromZ, 1);
            slot = DUEL[0xD5B];
            wonA = 0;
            wonB = 0;
            func_00202CB0(4, -1, 0);
            func_00202D60(5, -1);
            func_001F4E50(1, -1);
            func_001F4E50(0, 0x26D);
            func_001F7260(0);
            func_001FA810(0, -1);
            func_001F6C10(0);
            func_001F6CA0(0);
            func_001A86A0(0);
            if (lose != 6) {
                if (win == 4) {
                    wonA = 1;
                }
            }
            if (lose == 4) {
                wonB = 1;
            }
            func_001E53C0(0, wonA);
            func_001E53C0(1, wonB);
            DUEL_DUO(0x6C8)->view[0x43] = 0;
            DUEL_DUO(0x6CC)->view[0x43] = 0;
            func_001E3900(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, 1);
            func_001E3900(DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z, 1);
            func_001A8BB0();
            func_001DDD80(1, DUEL[0xD37]);
            func_001ADA80(1);
            func_001F6CE0(0);
            func_001F6CF0(0);
            func_001D91B0(0, duel[slot + 0xCCA], duel[slot + 0xCFB], duel[slot + 0xCCB], duel[slot + 0xCFC]);
            DUEL[0xD38]++;
        case 8:
            if (func_001FF300() != 0) {
                break;
            }
            DUEL[0xD3A] = MAX_001CEE60(DUEL[0xD3A] - 4, 0);
            if (DUEL[0xD3A] > 0) {
                break;
            }
            if (DUEL[0x706] != 0xFF) {
                func_001F4F10(DUEL[0x706], 0);
            }
            F67->b1 = 0;
            DUEL[0xD3B] = 0;
            DUEL[0xD38] = 0;
            break;
        }
        return 0;
    }
    if (F65->b1) {
        switch (func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), -1)) {
        case 4:
            if (func_001DE2A0(DUEL[0xD54]) != 0) {
                DUEL[0xD38] = 1;
                DUEL_S16(0xC84) = ((s32)(3.0f * ((f32)func_0019A5C8() / 2147483648.0f)) + 1) * 1000 + 1;
                if (func_001A82E0(0x16) != 0) {
                    func_001AAAF0(5, 0);
                }
                return 1;
            }
            break;
        case 3:
            F66->b5 = 1;
            break;
        case 0:
            F65->b1 = 0;
            break;
        }
        return 0;
    }
    if (DUEL_U32(0xC64) != 0 && !F66->b4 && !F66->b3) {
        if (DUEL_DUO(0x6C8) != NULL && DUEL_DUO(0x6C8)->flags57.b4 && func_001F1300(DUEL_DUO(0x6C8)->model) &&
            DUEL_DUO(0x6C8)->progress != DUEL_DUO(0x6C8)->status51) {
            return 0;
        }
        if (DUEL_DUO(0x6CC) != NULL && DUEL_DUO(0x6CC)->flags57.b4 && func_001F1300(DUEL_DUO(0x6CC)->model) &&
            DUEL_DUO(0x6CC)->progress != DUEL_DUO(0x6CC)->status51) {
            return 0;
        }
        switch (DUEL_U32(0xC64) >> 16) {
        case 6:
            if (!F66->b5) {
                DUEL[0xD57] = 0x37;
                F66->b4 = 1;
            }
            DUEL_U32(0xC64) = (u16)DUEL_U32(0xC64) | 0x800000;
            break;
        case 4:
            func_0026B430(duel + 0x6E8);
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F65->b1 = 1;
            DUEL_U32(0xC64) = (u16)DUEL_U32(0xC64) | 0x20000;
            break;
        case 2:
            DUEL[0xD35] = DUEL[0xC51] & 0xF;
            DUEL[0xD36] = DUEL[0xC51] >> 4;
            if (DUEL[0xD36] < 2) {
                DUEL[0xD36] |= 0x80;
            } else {
                DUEL[0xD36] = DUEL[0xD54];
            }
            if (DUEL[0xC50] == 0) {
                DUEL[0xD57] = 0x2B;
            } else {
                DUEL[0xD57] = 0x2F;
            }
            F66->b3 = 1;
            DUEL_U32(0xC64) = (u16)DUEL_U32(0xC64) | 0x10000;
            break;
        case 3:
            func_0026B430(duel + 0x6E8);
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F65->b1 = 1;
            DUEL_U32(0xC64) = (u16)DUEL_U32(0xC64) | 0x10000;
            break;
        case 7:
            DUEL_U32(0xC64) = (DUEL_U32(0xC64) & 0xFFFF) | 0x10000;
        case 1:
            *(Vec4_001CEE60 *)(duel + 0x6E8) = *(Vec4_001CEE60 *)(duel + 0xC40);
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F65->b1 = 1;
            DUEL_U32(0xC64) = (u16)DUEL_U32(0xC64) | 0x800000;
            break;
        case 0x80:
        case 0:
            reply = ((C64_001CEE60 *)duel)->c64;
            low = (u16)reply;
            if ((reply & 0xFF) == 0xE) {
                if (low & 0x100) {
                    DUEL_DUO(0x6C8) = NULL;
                } else {
                    (DUEL_DUO(0x6C8))->flags57.b7 = 0;
                    (DUEL_DUO(0x6C8))->flags58.b0 = 0;
                    (DUEL_DUO(0x6C8))->flags56.b23 = 1;
                }
                if (!(low & 0x200)) {
                    (DUEL_DUO(0x6CC))->flags57.b7 = 0;
                    (DUEL_DUO(0x6CC))->flags58.b0 = 0;
                    (DUEL_DUO(0x6CC))->flags56.b23 = 1;
                }
                DUEL_U32(0xC64) = 0;
            } else {
                DUEL_U32(0xC64) = func_00249680(DUEL[0xD55], DUEL[0xD56], duel[DUEL[0xD5B] + 0xCCB], duel[DUEL[0xD5B] + 0xCFC],
                                                duel + 0xC40, low);
            }
            break;
        }
        return 0;
    }
    if (F65->b6) {
        if (func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), -1) == 0) {
            F65->b6 = 0;
        }
        return 0;
    }
    if (DUEL_U32(0xC6C) != 0 && !F66->b3) {
        high = DUEL_U32(0xC6C) >> 16;
        switch (DUEL_U32(0xC6C) & 0xFF) {
        case 4:
            func_0026B430(duel + 0x6E8);
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F65->b6 = 1;
            DUEL_U32(0xC6C) = (DUEL_U32(0xC6C) & ~0xFF) | 2;
            break;
        case 2:
            DUEL[0xD35] = DUEL[0xC51] & 0xF;
            DUEL[0xD36] = DUEL[0xC51] >> 4;
            if (DUEL[0xD36] < 2) {
                DUEL[0xD36] |= 0x80;
            } else {
                DUEL[0xD36] = DUEL[0xD54];
            }
            if (DUEL[0xC50] == 0) {
                DUEL[0xD57] = 0x2B;
            } else {
                DUEL[0xD57] = 0x2F;
            }
            F66->b3 = 1;
            DUEL_U32(0xC6C) = (DUEL_U32(0xC6C) & ~0xFF) | 1;
            break;
        case 1:
            *(Vec4_001CEE60 *)(duel + 0x6E8) = *(Vec4_001CEE60 *)(duel + 0xC40);
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F65->b6 = 1;
            DUEL_U32(0xC6C) = (DUEL_U32(0xC6C) & ~0xFF) | 0x80;
            break;
        case 0x80:
        case 0:
            if (high != 0) {
                DUEL_U32(0xC6C) = func_00252440(DUEL[0xD55], DUEL[0xD56], duel + 0xC40, high);
            } else {
                if (!(DUEL_U32(0xC6C) & 0x100)) {
                    DUEL_DUO(0x6C8) = NULL;
                }
                DUEL_U32(0xC6C) = 0;
            }
            break;
        }
        return 0;
    }
    if (F65->b7) {
        if (func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), -1) == 0) {
            F65->b7 = 0;
        }
        return 0;
    }
    if (DUEL_U32(0xC70) != 0) {
        switch (DUEL_U32(0xC70) & 0xFF) {
        case 1:
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F65->b7 = 1;
            DUEL_U32(0xC70) = (DUEL_U32(0xC70) & ~0xFF) | 0x80;
            break;
        case 0x80:
        case 0:
            high = DUEL_U32(0xC70) >> 16;
            if (DUEL[0xD57] == 0x3D) {
                k = 1;
            } else {
                k = 0;
            }
            k = DUEL[0xD5B] + k;
            if (high != 0) {
                DUEL_U32(0xC70) = func_0024B310(DUEL[0xD55], DUEL[0xD56], duel[k + 0xCCA], duel[k + 0xCFB], duel + 0x6E8, high);
            } else {
                if (DUEL_U32(0xC70) & 0x200) {
                    F66->b2 = 1;
                }
                if (DUEL_U32(0xC70) & 0x100) {
                    DUEL[0xD57] = 0x39;
                    DUEL_U32(0xC70) = 0;
                } else {
                    DUEL_U32(0xC70) = 0;
                    DUEL_U32(0xC68) = func_0024F780(DUEL[0xD55], DUEL[0xD56], duel[k + 0xCCA], duel[k + 0xCFB], duel + 0x6E8);
                    if (DUEL_U32(0xC68) != 0) {
                        return 1;
                    }
                }
            }
            break;
        }
        return 0;
    }
    if (F66->b0) {
        if (func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), -1) == 0) {
            F66->b0 = 0;
        }
        return 0;
    }
    if (DUEL_U32(0xC74) != 0) {
        switch (DUEL_U32(0xC74) & 0xFFFF) {
        case 1:
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F66->b0 = 1;
            DUEL_U32(0xC74) = (DUEL_U32(0xC74) & 0xFFFF0000) | 0x80;
            break;
        case 0x80:
        case 0:
            DUEL_U32(0xC74) = 0;
            break;
        }
        return 0;
    }
    if (F65->b2) {
        if (func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), -1) == 0) {
            F65->b2 = 0;
        }
        return 0;
    }
    if (DUEL_U32(0xC68) != 0) {
        switch (DUEL_U32(0xC68) & 0xFFFF) {
        case 1:
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F65->b2 = 1;
            DUEL_U32(0xC68) = (DUEL_U32(0xC68) & 0xFFFF0000) | 0x80;
            break;
        case 0x80:
        case 0:
            if ((DUEL_U32(0xC68) >> 16) != 0) {
                DUEL[0xD57] = 0x16;
            }
            DUEL_U32(0xC68) = 0;
            break;
        }
        return 0;
    }
    if (F65->b3) {
        reply = func_0026EA00(duel + 0x6E8, duel + 0x700, -1);
        switch (reply & 0xFFFF) {
        case 2:
            func_001D8CD0(DUEL[0xD54], duel[DUEL[0xD4B] + 0xD2C], reply >> 16, -0x7D, -8);
            break;
        case 0:
            from = duel[DUEL[0xD4B] + 0xD2C];
            to = duel[DUEL[0xD4C] + 0xD2C];
            switch (DUEL_U32(0xC78) & 0xFFFF) {
            case 1:
                if ((DUEL_U32(0xC78) >> 16) != 0) {
                    drop_001CEE60(duel, from);
                    duel[DUEL[0xD4B] + 0xD2C] = 6;
                    DUEL[0xD4B] = DUEL[0xD4C];
                } else {
                    drop_001CEE60(duel, to);
                    duel[DUEL[0xD4C] + 0xD2C] = 6;
                }
                break;
            case 0:
                drop_001CEE60(duel, to);
                duel[DUEL[0xD4C] + 0xD2C] = 6;
                break;
            case 2:
                drop_001CEE60(duel, from);
                duel[DUEL[0xD4B] + 0xD2C] = 6;
                DUEL[0xD4B] = DUEL[0xD4C];
                break;
            }
            if ((sl = slot_001CEE60(duel[DUEL[0xD4B] + 0xD2C])) != NULL && (sub = *(u8 **)sl) != NULL) {
                ((Flags8_001CEE60 *)(sub + 0x83))->b6 = 0;
                sub[0x43] = 0x80;
                func_001D9030(sl, -0x7D, -8, -0x7D, -8, 0x80, 0x80);
            }
            DUEL[0xD4C]++;
            DUEL_U32(0xC78) = (DUEL_U32(0xC78) & 0xFFFF0000) | 3;
            F65->b3 = 0;
            break;
        }
        return 0;
    }
    if ((s32)DUEL_U32(0xC78) >= 0) {
        switch (DUEL_U32(0xC78) & 0xFFFF) {
        case 0:
        case 1:
        case 2:
            func_0026EA00(duel + 0x6E8, duel + 0x700, 0);
            F65->b3 = 1;
            break;
        case 3:
            for (i = DUEL[0xD4C] + 1, j = 1, k = 0x8D; i < DUEL[0xD4D]; k += 0x10, j++, i++) {
                if ((sl = slot_001CEE60(duel[i + 0xD2C])) != NULL && *(u8 **)sl != NULL) {
                    ((Flags8_001CEE60 *)(sl + 0x9F))->b4 = 0;
                    func_001D9030(sl, k, -8, -0x7D, -8, 0, 0x80);
                }
            }
            if (DUEL[0xD4C] >= DUEL[0xD4D]) {
                DUEL[0xD57] = 0x4A;
            }
            DUEL_U32(0xC78) = -1;
            break;
        }
        return 0;
    }
    if (F65->b4) {
        if (func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), -1) == 0) {
            F65->b4 = 0;
        }
        return 0;
    }
    if (F65->b5) {
        if (func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), -1) == 0) {
            F65->b5 = 0;
        }
        return 0;
    }
    if (U66->b1) {
        if (func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), -1) == 0) {
            U66->b1 = 0;
        }
        return 0;
    }
    if (func_001F5240(0, -1) != 0) {
        return 0;
    }
    if (!F67->b5 && DUEL[0xD57] == 0x18 && (hand0 == 0 || hand1 == 0)) {
        if (hand0 == hand1) {
            DUEL[0xD50] = 2;
        } else if (hand0 > hand1) {
            DUEL[0xD50] = 0;
        } else {
            DUEL[0xD50] = 1;
        }
        F66->b7 = 0;
        F67->b0 = F66->b7;
        DUEL[0xD51] = 0;
        DUEL[0xD57] = 0x54;
        return 0;
    }
    if (DUEL[0xD57] == 0x18 || DUEL[0xD57] == 0x1B || DUEL[0xD57] == 0x1D || DUEL[0xD57] == 0x21 ||
        DUEL[0xD57] == 0x25 || DUEL[0xD57] == 0x29 || DUEL[0xD57] == 0x2D || DUEL[0xD57] == 0x30 ||
        DUEL[0xD57] == 0x33 || DUEL[0xD57] == 0x35 || DUEL[0xD57] == 0x3E || DUEL[0xD57] == 0x43 ||
        DUEL[0xD57] == 0x53 || DUEL[0xD57] == 0x46 || DUEL[0xD57] == 0x5C || DUEL[0xD57] == 0x61) {
        sl = &duelState.b[DUEL[0xD54] * 0x350];
        if (sl[0x33C] < 100 && *(s32 *)(sl + 0x334) != 0) {
            func_0020B380((void *)0x3F0000, (void *) *(s32 *)(sl + 0x334), *(u16 *)(sl + 0x338) >> 4);
            func_0017BB60(0);
            func_0017B410(0x3F0000, *(u16 *)(sl + 0x338));
        }
        pressed = func_001CECF0(DUEL[0xD54], 1);
        if (me[0x33C] >= 100) {
            rep = func_001CECF0(DUEL[0xD54], 0);
            trig = func_001CECF0(DUEL[0xD54], 2);
            picked = func_00203BC0(me[0x33C] - 100);
        } else {
            DUEL_S16(0xC96) = 0;
            trig = pressed;
            rep = trig;
        }
        held = (u16)pressed;
        if (DUEL[0xD54] == 1) {
            swap = pressed & 0xFFFF0FFF;
            if (held & 0x8000) {
                swap |= 0x2000;
            }
            if (held & 0x2000) {
                swap |= 0x8000;
            }
            if (held & 0x1000) {
                swap |= 0x4000;
            }
            if (held & 0x4000) {
                swap |= 0x1000;
            }
            held = swap;
        }
    } else {
        pressed = 0;
        rep = pressed;
        DUEL_S16(0xC96) = 0;
        trig = 0;
        held = rep;
    }
    lifeA100 = lifeA - 100;
    lifeB100 = lifeB - 100;
    held16 = held & 0xFFFF;
    mDpad = held16 & 0xF000;
    mUD = trig & 0x5000;
    mUp = trig & 0x1000;
    mLR = trig & 0xA000;
    mLeft = trig & 0x8000;
    mLR2 = trig & 0xC;
    mR2 = trig & 4;
    for (;;) {
        switch (DUEL[0xD57]) {
        case 0x13:
            func_00217710(0, 0x1D);
            DUEL[0xD57] = 0x14;
            DUEL_U32(0xC5C) = func_002724F0(0, (s32 *)(duel + 0x6E8));
            if (DUEL_U32(0xC5C) != 0) {
                return 1;
            }
        case 0x14:
            func_001D9820(0, DUEL[0xD54] ^ 1);
            me = duel + DUEL[0xD54] * 0x350;
            DUEL_DUO(0x6C8) = (Object_001CEE60 *)func_001E36E0(me[0x33D], me[0x33E]);
            DUEL[0xD57] = 0x15;
        case 0x15:
            F67->b0 = 0;
            DUEL[0xD3A] = MAX_001CEE60(DUEL[0xD3A] - 4, 0);
            if (DUEL[0xD3A] > 0) {
                return 0;
            }
            if (func_001FA6F0(-1, -1) != NULL) {
                return 0;
            }
            DUEL[0xD57] = 0x16;
            DUEL_U32(0xC60) = func_00267C50(0, duel + 0x6E8);
        case 0x16:
            F67->b1 = 0;
            DUEL_DUO(0x6C8) = (Object_001CEE60 *)func_001E36E0(me[0x33D], me[0x33E]);
            DUEL_DUO(0x6CC) = NULL;
            DUEL[0xD59] = 0;
            F64->b6 = 0;
            F66->b4 = 0;
            F66->b5 = 0;
            DUEL[0xD57] = 0x17;
        case 0x17:
            if (DUEL_U32(0xC60) != 0) {
                return 1;
            }
            DUEL[0xD57] = 0x18;
            return 0;
        case 0x18:
            DUEL_DUO(0x6C8) = (Object_001CEE60 *)func_001E36E0(me[0x33D], me[0x33E]);
            if (DUEL_DUO(0x6C8) != NULL) {
                DUEL[0xD55] = DUEL_DUO(0x6C8)->x;
                DUEL[0xD56] = DUEL_DUO(0x6C8)->z;
                func_001DD990(DUEL[0xD55], DUEL[0xD56]);
            } else {
                DUEL_S16(0xC96) = 0;
            }
            keys = rep;
            if (keys & 0x10) {
                if (DUEL_DUO(0x6C8) != NULL) {
                    v = 0;
                    if (DUEL_DUO(0x6C8)->z > 0) {
                        v = func_00267380((s32)DUEL_DUO(0x6C8), DUEL[0xD54]);
                    }
                    if (v == 0) {
                        DUEL[0xCB3] = 0x11;
                        DUEL[0xCBD] = 0;
                        DUEL[0xD35] = 0x18;
                        DUEL[0xD57] = 0x20;
                        func_00217710(0, 0x10);
                        return 0;
                    }
                }
                func_00217710(0, 6);
                return 0;
            }
            if (keys & 0x100) {
                DUEL[0xD57] = 0x23;
                func_00217710(0, 4);
                return 0;
            }
            if (keys & 4) {
                DUEL[0xD57] = 0x27;
                func_00217710(0, 4);
                return 0;
            }
            if (keys & 8) {
                DUEL[0xD35] = 0;
                DUEL[0xD36] = DUEL[0xD54];
                DUEL[0xD57] = 0x2B;
                func_00217710(0, 4);
                return 0;
            }
            if (keys & 0xC0) {
                if (DUEL_DUO(0x6C8) != NULL) {
                    v = func_00250360(DUEL[0xD55], DUEL[0xD56]);
                    if (DUEL[0xD54] != v) {
                        func_00217710(0, 6);
                        return 0;
                    }
                    if (DUEL[0xD56] == 0 && (keys & 0x80)) {
                        inHand = func_001DE9C0(DUEL[0xD54]);
                        onField = func_001DF110(DUEL[0xD54]);
                        DUEL[0xD4E] = 0;
                        DUEL[0xD4F] = 0;
                        func_001DF330(DUEL[0xD54]);
                        if (((Flags8_001CEE60 *)(me + 0x346))->b0) {
                            if (inHand + onField <= 0) {
                                func_00217710(0, 6);
                                return 0;
                            }
                            func_001E2570(DUEL[0xD54], me[0x33D], me[0x33E]);
                            DUEL[0xD59] = 0;
                            DUEL[0xD63] = 0;
                            duel[DUEL[0xD59] + 0xCCA] = me[0x33D];
                            duel[DUEL[0xD59] + 0xCFB] = me[0x33E];
                            DUEL[0xD59]++;
                            DUEL[0xD57] = 0x3E;
                            func_00217710(0, 4);
                            return 0;
                        }
                        if (onField <= 0) {
                            func_00217710(0, 6);
                            return 0;
                        }
                        DUEL[0xD57] = 0x51;
                        func_00217710(0, 4);
                        return 0;
                    }
                    if (DUEL_DUO(0x6C8)->flags57.b0 == 0) {
                        F66->b6 = (s8)func_001E17D0(DUEL[0xD55], DUEL[0xD56]);
                        DUEL[0xD5A] = func_001E1760(DUEL[0xD55], DUEL[0xD56]);
                        func_001E27D0(1, F66->b6, DUEL[0xD56] == 0, DUEL[0xD54], me[0x33D], me[0x33E], DUEL[0xD5A], NULL, NULL, 0);
                        DUEL[0xD59] = 0;
                        DUEL[0xD63] = 0;
                        DUEL_DUO(0x6C8)->flags57.b6 = 1;
                        DUEL[0xD57] = 0x19;
                        DUEL[0xD58] = 0x1D;
                        func_00217710(0, 4);
                        return 0;
                    }
                }
                func_00217710(0, 6);
                return 0;
            }
            if (keys & 1) {
                F66->b7 = F66->b7 ? 0 : 1;
                F67->b0 = F66->b7;
                func_00217710(0, 4);
                return 0;
            }
            if (keys & 0x800) {
                DUEL[0xD57] = 0x19;
                DUEL[0xD58] = 0x13;
                return 0;
            }
            if (func_001FA6F0(-1, -1) != NULL) {
                return 0;
            }
            if (picked != 0 || (me[0x33C] >= 0x20 && me[0x33C] < 100)) {
                port = (picked != 0) ? me[0x33C] - 100 : 0;
                stickRX = (func_00203C40(port, 3) & 0xFF) - 0x80;
                stickRY = (func_00203C40(port, 2) & 0xFF) - 0x80;
                stickLY = (func_00203C40(port, 1) & 0xFF) - 0x80;
                func_00203C40(port, 0);
                speed = 8;
                moved = 0;
                if (keys & 0x200) {
                    *(s32 *)(list + 4) = 0x4000;
                    *(s32 *)(list + 8) = 0x2000;
                    speed = 0x1E;
                    if (DUEL[0xD54] == 1) {
                        *(s32 *)(list + 4) = *(s32 *)(list + 4) + 0x7FFF + 1;
                    }
                    moved = 1;
                } else {
                    if (ABS_001CEE60(stickRY) >= 0x30) {
                        *(s32 *)(list + 4) = (*(s32 *)(list + 4) + 0x10000) % 0x10000;
                        if (stickRY >= 0x30) {
                            *(s32 *)(list + 4) = *(s32 *)(list + 4) - 0x1000;
                        } else {
                            *(s32 *)(list + 4) = *(s32 *)(list + 4) + 0x1000;
                        }
                        moved = 1;
                    }
                    if (ABS_001CEE60(stickRX) >= 0x30) {
                        if (stickRX >= 0x30) {
                            *(s32 *)(list + 8) = *(s32 *)(list + 8) - 0x800;
                        } else {
                            *(s32 *)(list + 8) = *(s32 *)(list + 8) + 0x800;
                        }
                        *(s32 *)(list + 8) = MIN_001CEE60(MAX_001CEE60(*(s32 *)(list + 8), 0x800), 0x4000);
                        moved = 1;
                    }
                }
                if (keys & 0x400) {
                    *(s32 *)(list + 0) = 0xC8;
                    speed = 0x1E;
                    moved = 1;
                } else if (ABS_001CEE60(stickLY) >= 0x30) {
                    if (stickLY >= 0x30) {
                        *(s32 *)(list + 0) = *(s32 *)(list + 0) + 0x32;
                    } else {
                        *(s32 *)(list + 0) = *(s32 *)(list + 0) - 0x32;
                    }
                    *(s32 *)(list + 0) = MIN_001CEE60(MAX_001CEE60(*(s32 *)(list + 0), 0x32), 0x1F4);
                    moved = 1;
                }
                if (moved != 0) {
                    func_001FC950(list, &camv);
                    func_001FA8A0(0, 0, 4, (u16)speed, 0, &camv);
                    DUEL_S16(0xC96) = 0;
                }
            }
            if (mDpad == 0) {
                break;
            }
            if (((held16 & 0x8000) && me[0x33D] <= 0) || ((held16 & 0x2000) && me[0x33D] >= 6)) {
                held = (u16)(held & 0x5FFF);
            }
            if ((((u16)held & 0x1000) && me[0x33E] <= 0) || (((u16)held & 0x4000) && me[0x33E] >= 6)) {
                held = (u16)(held & 0xAFFF);
            }
            DUEL[0xD63] = 0x3C;
            if (F64->b6) {
                if ((keys = held) & 0x5000) {
                    held = (u16)(held & 0x5000);
                } else {
                    F64->b6 = 0;
                }
            }
            if ((u16)held & 0xA000) {
                if ((u16)held & 0x8000) {
                    me[0x33D]--;
                } else {
                    me[0x33D]++;
                }
                if ((u16)held & 0x5000) {
                    F64->b6 = 1;
                }
            } else if ((u16)held & 0x5000) {
                if ((u16)held & 0x1000) {
                    me[0x33E]--;
                } else {
                    me[0x33E]++;
                }
                F64->b6 = 0;
            } else {
                F64->b6 = 0;
                return 0;
            }
            gx = (s32)(f32)((me[0x33D] - 3) * 50);
            func_001D90E0(8, gx, (s32)(f32)((me[0x33E] - 3) * 50));
            func_00217710(0, 3);
            return 0;
        case 0x19:
            if (func_001FA6F0(-1, -1) != NULL) {
                return 0;
            }
            DUEL[0xD57] = DUEL[0xD58];
            break;
        case 0x1A:
            DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 8, 0x40);
            if (DUEL_S16(0xC9C) < 0x40) {
                break;
            }
            DUEL[0xD57] = 0x1B;
        case 0x1B:
            if (!(rep & 0xFFFF & 0xF0)) {
                break;
            }
            DUEL[0xD57] = 0x1C;
            func_00217710(0, 4);
            return 0;
        case 0x1C:
            DUEL_S16(0xC9C) = MAX_001CEE60(DUEL_S16(0xC9C) - 8, 0);
            if (DUEL_S16(0xC9C) > 0) {
                break;
            }
            DUEL[0xCB2] = 0x18;
            DUEL_S16(0xC96) = 0;
            DUEL[0xD57] = 0x18;
            return 0;
        case 0x1D:
            DUEL_DUO(0x6CC) = (Object_001CEE60 *)func_001E36E0(me[0x33D], me[0x33E]);
            if (DUEL_DUO(0x6CC) != NULL) {
                func_001DD890(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z);
            } else {
                func_001DDAC0(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, me[0x33D], me[0x33E]);
            }
            keys = rep;
            DUEL_DUO(0x6C8)->pad42[0] = me[0x33D];
            DUEL_DUO(0x6C8)->pad42[1] = me[0x33E];
            if (keys & 0xC0) {
                if (func_001E22B0(me[0x33D], me[0x33E]) == 8) {
                    if (!F66->b6) {
                        F66->b5 = 1;
                    }
                }
                DUEL[0xD57] = 0x1E;
                DUEL_U32(0xC74) = func_0026AE70(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, DUEL_DUO(0x6C8)->flags57.b3, duel + 0x6E8);
                if (DUEL_U32(0xC74) != 0) {
                    if ((DUEL_U32(0xC74) >> 16) != 0) {
                        DUEL[0xD57] = 0x1F;
                        DUEL_DUO(0x6C8)->flags57.b0 = 1;
                    }
                    return 1;
                }
                func_00217710(0, 4);
                return 0;
            }
            if (func_001FA6F0(-1, -1) != NULL) {
                return 0;
            }
            if (keys & 0x20) {
                DUEL[0xD57] = 0x1F;
                func_00217710(0, 5);
                return 0;
            }
            if (mDpad != 0) {
                tx = me[0x33D];
                tz = me[0x33E];
                if (((held16 & 0x8000) && tx <= 0) || ((held16 & 0x2000) && tx >= 6)) {
                    held = (u16)(held & 0x5FFF);
                }
                if ((((u16)held & 0x1000) && tz <= 0) || (((u16)held & 0x4000) && tz >= 6)) {
                    held = (u16)(held & 0xAFFF);
                }
                if (F64->b6) {
                    if ((keys = held) & 0x5000) {
                        held = (u16)(held & 0x5000);
                    } else {
                        F64->b6 = 0;
                    }
                }
                if ((u16)held & 0xA000) {
                    if ((u16)held & 0x8000) {
                        tx--;
                    } else {
                        tx++;
                    }
                    if ((u16)held & 0x5000) {
                        F64->b6 = 1;
                    }
                } else if ((u16)held & 0x5000) {
                    if ((u16)held & 0x1000) {
                        tz--;
                    } else {
                        tz++;
                    }
                    F64->b6 = 0;
                } else {
                    F64->b6 = 0;
                    return 0;
                }
                for (i = 0; i < DUEL[0xD59] - 1; i++) {
                    p = duel + i;
                    if (p[0xCCA] == tx && p[0xCFB] == tz) {
                        return 0;
                    }
                }
                r = func_001E24E0(tx, tz);
                lim2 = DUEL[0xD5A];
                if (r > lim2) {
                    return 0;
                }
                if (DUEL[0xD59] > 0 && tx == duel[DUEL[0xD59] + 0xCC9] && tz == duel[DUEL[0xD59] + 0xCFA]) {
                    DUEL[0xD59]--;
                } else if (DUEL[0xD59] < lim2) {
                    duel[(DUEL[0xD59] & 0xFF) + 0xCCA] = me[0x33D];
                    duel[DUEL[0xD59] + 0xCFB] = me[0x33E];
                    DUEL[0xD59]++;
                } else {
                    return 0;
                }
                me[0x33D] = tx;
                me[0x33E] = tz;
                func_001E27D0(0, F66->b6, DUEL[0xD56] == 0, DUEL[0xD54], me[0x33D], me[0x33E], DUEL[0xD5A] - DUEL[0xD59],
                              duel + 0xCCA, duel + 0xCFB, DUEL[0xD59]);
                gx = (s32)(f32)((me[0x33D] - 3) * 50);
                func_001D90E0(8, gx, (s32)(f32)((me[0x33E] - 3) * 50));
                if (DUEL_DUO(0x6C8)->flags57.b3) {
                    DUEL_DUO(0x6C8)->flags57.b3 = 0;
                    DUEL_DUO(0x6C8)->flags56.b67 = 3;
                }
                func_00217710(0, 3);
                return 0;
            }
            if (DUEL[0xD56] == 0 || DUEL[0xD59] != 0 || !(keys & 0xF)) {
                break;
            }
            if (keys & 0xC) {
                old = DUEL_DUO(0x6C8)->flags57.b3;
                if (keys & 4) {
                    DUEL_DUO(0x6C8)->flags57.b3 = 0;
                    DUEL_DUO(0x6C8)->flags56.b67 = 3;
                } else {
                    DUEL_DUO(0x6C8)->flags57.b3 = 1;
                    DUEL_DUO(0x6C8)->flags56.b67 = 1;
                }
                if (DUEL_DUO(0x6C8)->flags57.b3 != old) {
                    func_00217710(0, 9);
                }
            }
            if (keys & 3) {
                if (!DUEL_DUO(0x6C8)->flags57.b4) {
                    old = DUEL_DUO(0x6C8)->flags57.b2;
                    if (keys & 1) {
                        DUEL_DUO(0x6C8)->flags57.b2 = 0;
                        DUEL_DUO(0x6C8)->flags56.b45 = 3;
                    } else {
                        DUEL_DUO(0x6C8)->flags57.b2 = 1;
                        DUEL_DUO(0x6C8)->flags56.b45 = 1;
                    }
                    if (DUEL_DUO(0x6C8)->flags57.b2 != old) {
                        F66->b6 = (s8)func_001E17D0(DUEL[0xD55], DUEL[0xD56]);
                        DUEL[0xD5A] = func_001E1760(DUEL[0xD55], DUEL[0xD56]);
                        func_001E27D0(1, F66->b6, DUEL[0xD56] == 0, DUEL[0xD54], me[0x33D], me[0x33E], DUEL[0xD5A], NULL, NULL, 0);
                        func_00217710(0, 9);
                    }
                }
            }
            return 0;
        case 0x1E:
            if (DUEL_DUO(0x6C8)->flags56.b67 != 0) {
                break;
            }
            if (DUEL_DUO(0x6C8)->flags56.b45 != 0) {
                break;
            }
            diff = DUEL_DUO(0x6C8)->flags57.b2 != DUEL_DUO(0x6C8)->flags57.b4;
            if (diff) {
                DUEL_DUO(0x6C8)->flags4F = 7;
                DUEL_DUO(0x6C8)->status51 = 0x80;
                DUEL_DUO(0x6C8)->flags56.b23 = 1;
            }
            F66->b2 = 0;
            if (DUEL[0xD59] != 0) {
                duel[(DUEL[0xD59] & 0xFF) + 0xCCA] = me[0x33D];
                duel[DUEL[0xD59] + 0xCFB] = me[0x33E];
                DUEL[0xD5B] = 0;
                if (DUEL_DUO(0x6CC) != NULL) {
                    DUEL[0xD57] = 0x36;
                } else {
                    DUEL[0xD57] = 0x37;
                }
            } else {
                DUEL[0xD57] = 0x38;
            }
            return 0;
        case 0x1F:
            if (DUEL[0xD59] > 0) {
                tz = ABS_001CEE60(me[0x33E] - DUEL[0xCFB]);
                tx = ABS_001CEE60(me[0x33D] - DUEL[0xCCA]);
                me[0x33D] = DUEL[0xCCA];
                me[0x33E] = DUEL[0xCFB];
                gx = (s32)(f32)((me[0x33D] - 3) * 50);
                func_001D90E0((tx + tz) * 8, gx, (s32)(f32)((me[0x33E] - 3) * 50));
                DUEL[0xD59] = 0;
            }
            if (DUEL_DUO(0x6C8)->flags57.b2 != (bit = DUEL_DUO(0x6C8)->flags57.b4)) {
                DUEL_DUO(0x6C8)->flags57.b2 = bit;
                if (DUEL_DUO(0x6C8)->flags57.b4) {
                    DUEL_DUO(0x6C8)->flags56.b45 = 1;
                } else {
                    DUEL_DUO(0x6C8)->flags56.b45 = 3;
                }
            }
            diff = DUEL_DUO(0x6C8)->flags57.b3 != (bit = DUEL_DUO(0x6C8)->flags57.b5);
            if (diff) {
                DUEL_DUO(0x6C8)->flags57.b3 = bit;
                if (DUEL_DUO(0x6C8)->flags57.b5) {
                    DUEL_DUO(0x6C8)->flags56.b67 = 1;
                } else {
                    DUEL_DUO(0x6C8)->flags56.b67 = 3;
                }
            }
            DUEL_DUO(0x6C8)->flags57.b6 = 0;
            DUEL[0xD57] = 0x16;
            return 0;
        case 0x20:
            DUEL[0xD3A] = MIN_001CEE60(DUEL[0xD3A] + 8, 0x40);
            if (DUEL[0xD3A] < 0x40) {
                break;
            }
            DUEL[0xD57] = 0x21;
        case 0x21:
            if (mUD != 0) {
                if (mUp != 0) {
                    DUEL[0xCBD] = (DUEL[0xCBD] + 3) % 4;
                } else {
                    DUEL[0xCBD] = (DUEL[0xCBD] + 5) % 4;
                }
                func_00217710(0, 0x13);
            } else if ((DUEL[0xD35] == 0x43 || DUEL[0xD35] == 0x53) && mLR != 0) {
                n = func_001DF110(DUEL[0xD54]);
                old = DUEL[0xD4F];
                if (mLeft != 0) {
                    DUEL[0xD4F] = (old + n - 1) % n;
                } else {
                    DUEL[0xD4F] = (old + n + 1) % n;
                }
                if (DUEL[0xD4F] != old) {
                    func_00217710(0, 0x13);
                }
            } else if (rep & 0xFFFF & 0x20) {
                DUEL[0xD57] = 0x22;
                func_00217710(0, 0x11);
            }
            break;
        case 0x22:
            DUEL[0xD3A] = MAX_001CEE60(DUEL[0xD3A] - 8, 0);
            if (DUEL[0xD3A] > 0) {
                break;
            }
            DUEL[0xCB3] = 0x18;
            DUEL[0xD57] = DUEL[0xD35];
            return 0;
        case 0x23:
            DUEL[0xCB2] = 8;
            DUEL_S16(0xC9C) = 0;
            DUEL_S16(0xC9A) = 0;
            DUEL[0xD57] = 0x24;
            DUEL[0xD35] = 0;
        case 0x24:
            DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 8, 0x40);
            if (DUEL_S16(0xC9C) < 0x40) {
                break;
            }
            DUEL[0xD57] = 0x25;
        case 0x25:
            keys = rep;
            if (keys & 0xA000) {
                old = DUEL[0xD35];
                if (keys & 0x8000) {
                    DUEL[0xD35] = 1;
                } else {
                    DUEL[0xD35] = 0;
                }
                if (DUEL[0xD35] != old) {
                    func_00217710(0, 3);
                }
                return 0;
            }
            if (keys & 0xC0) {
                DUEL[0xD57] = 0x26;
                func_00217710(0, 4);
                return 0;
            }
            if (!(keys & 0x20)) {
                break;
            }
            DUEL[0xD57] = 0x26;
            func_00217710(0, 5);
            DUEL[0xD35] = 0;
            return 0;
        case 0x26:
            DUEL_S16(0xC9C) = MAX_001CEE60(DUEL_S16(0xC9C) - 8, 0);
            if (DUEL_S16(0xC9C) > 0) {
                break;
            }
            DUEL[0xCB2] = 0x18;
            if (DUEL[0xD35] != 0) {
                DUEL[0xD50] = DUEL[0xD54] ^ 1;
                F66->b7 = 0;
                F67->b0 = F66->b7;
                DUEL[0xD51] = 0;
                DUEL[0xD57] = 0x54;
            } else {
                DUEL[0xD57] = 0x18;
            }
            return 0;
        case 0x27:
            DUEL[0xCB2] = 7;
            DUEL_S16(0xC9A) = 0;
            DUEL_S16(0xC9C) = 0x200;
            DUEL[0xD35] = 0;
            DUEL[0xD36] = 0;
            for (i = 0; i < 3; i++) {
                if (func_00214D00(0, i) != 0) {
                    v = 1;
                } else {
                    v = 0;
                }
                DUEL[0xD36] |= v << i;
            }
            DUEL[0xD57] = 0x28;
        case 0x28:
            DUEL_S16(0xC9C) = MAX_001CEE60(DUEL_S16(0xC9C) - 0x40, 0);
            if (DUEL_S16(0xC9C) > 0) {
                break;
            }
            DUEL[0xD57] = 0x29;
        case 0x29:
            keys = rep;
            if (mUD != 0) {
                old = DUEL[0xD35];
                if (mUp != 0) {
                    DUEL[0xD35] = (old + 1) % 2;
                } else {
                    DUEL[0xD35] = (old + 3) % 2;
                }
                if (DUEL[0xD35] != old) {
                    func_00217710(0, 3);
                }
                return 0;
            }
            if (keys & 0xA000) {
                old = DUEL[0xD36];
                if (keys & 0x8000) {
                    DUEL[0xD36] = old | (1 << (DUEL[0xD35] + 1));
                } else {
                    DUEL[0xD36] = old & ~(1 << (DUEL[0xD35] + 1));
                }
                if (DUEL[0xD36] != old) {
                    func_00217710(0, 3);
                }
                return 0;
            }
            if (keys & 0xC0) {
                for (j = 0; j < 3; j++) {
                    func_00214BB0(0, j, DUEL[0xD36] & (1 << j));
                    func_00214BB0(1, j, DUEL[0xD36] & (1 << j));
                }
                DUEL[0xD57] = 0x2A;
                func_00217710(0, 4);
                return 0;
            }
            if (!(keys & 0x20)) {
                break;
            }
            DUEL[0xD57] = 0x2A;
            func_00217710(0, 5);
            return 0;
        case 0x2A:
            DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 0x40, 0x200);
            if (DUEL_S16(0xC9C) < 0x200) {
                break;
            }
            DUEL[0xCB2] = 0x18;
            DUEL[0xD57] = 0x18;
            return 0;
        case 0x2B: {
            u16 *buf;
            u16 *buf2;
            buf = (u16 *)CAMPAIGN_WORK_ADDR;
            *(u16 **)(duel + 0x6D8) = buf;
            buf2 = (u16 *)(CAMPAIGN_WORK_ADDR + 0xF0);
            *(u16 **)(duel + 0x6DC) = buf2;
            DUEL[0xD5E] = 0;
            DUEL[0xD5F] = 0;
            *(u16 *)(duel + 0xC8A) = 0;
            *(u16 *)(duel + 0xC8E) = 0;
            *(u16 *)(duel + 0xC8C) = 0;
            *(u16 *)(duel + 0xC90) = 0;
            for (i = 0; i < 0x78; i++) {
                v = func_001DEE00(0, i);
                if (v != 999 && func_00250000(0, i, DUEL[0xD35]) != 0) {
                    buf[(*(u16 *)(duel + 0xC8C))++] = v;
                }
            }
            for (n = *(u16 *)(duel + 0xC8C); n < 0x78; n++) {
                buf[n] = 999;
            }
            for (i = 0; i < 0x78; i++) {
                v = func_001DEE00(1, i);
                if (v != 999 && func_00250000(1, i, DUEL[0xD35]) != 0) {
                    buf2[(*(u16 *)(duel + 0xC90))++] = v;
                }
            }
            for (n = *(u16 *)(duel + 0xC90); n < 0x78; n++) {
                buf2[n] = 999;
            }
            DUEL[0xCB2] = 0xE;
            DUEL_S16(0xC9C) = 0;
            DUEL_S16(0xC9A) = 0;
            DUEL[0xD57] = 0x2C;
        }
        case 0x2C:
            DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 8, 0x40);
            if (DUEL_S16(0xC9C) < 0x40) {
                break;
            }
            DUEL[0xD57] = 0x2D;
        case 0x2D:
            scrollA = 0;
            lock = (DUEL[0xD36] & 0x80) ? 1 : 0;
            side = DUEL[0xD36] & 0x7F;
            scrollB = 0;
            if (side == 0) {
                old = DUEL[0xD5E];
                if (mLR2 != 0) {
                    if (mR2 != 0) {
                        scrollA = -5;
                    } else {
                        scrollA = 5;
                    }
                } else {
                    keys = rep;
                    if (mUD != 0) {
                        if (mUp != 0) {
                            if (old > 0) {
                                DUEL[0xD5E] = old - 1;
                            } else {
                                scrollA = -1;
                            }
                        } else {
                            lim2 = MIN_001CEE60(*(u16 *)(duel + 0xC8C) - 1, 4);
                            if (old < lim2) {
                                DUEL[0xD5E]++;
                            } else {
                                scrollA = 1;
                            }
                        }
                    } else if (keys & 0x2000) {
                        if (!lock) {
                            lim2 = MAX_001CEE60(*(u16 *)(duel + 0xC90) - 1, 0);
                            DUEL[0xD36] = 1;
                            DUEL[0xD5F] = MIN_001CEE60(DUEL[0xD5E], lim2);
                            func_00217710(0, 3);
                            return 0;
                        }
                    } else if (keys & 0xC0) {
                        if (F66->b3) {
                            if (*(u16 *)(duel + 0xC8C) != 0) {
                                DUEL[0xD57] = 0x2E;
                                DUEL_U32(0xC4C) = ((DuelState *)duel)->trunkList[*(u16 *)(duel + 0xC8A) + DUEL[0xD5E]];
                                func_00217710(0, 4);
                            } else {
                                func_00217710(0, 6);
                            }
                            return 0;
                        }
                    }
                }
                if (DUEL[0xD5E] != old) {
                    func_00217710(0, 3);
                    return 0;
                }
            } else if (side == 1) {
                old = DUEL[0xD5F];
                if (mLR2 != 0) {
                    if (mR2 != 0) {
                        scrollB = -5;
                    } else {
                        scrollB = 5;
                    }
                } else {
                    keys = rep;
                    if (mUD != 0) {
                        if (mUp != 0) {
                            if (old > 0) {
                                DUEL[0xD5F] = old - 1;
                            } else {
                                scrollB = -1;
                            }
                        } else {
                            lim2 = MIN_001CEE60(*(u16 *)(duel + 0xC90) - 1, 4);
                            if (old < lim2) {
                                DUEL[0xD5F]++;
                            } else {
                                scrollB = 1;
                            }
                        }
                    } else if (keys & 0x8000) {
                        if (!lock) {
                            lim2 = MAX_001CEE60(*(u16 *)(duel + 0xC8C) - 1, 0);
                            DUEL[0xD36] = 0;
                            DUEL[0xD5E] = MIN_001CEE60(DUEL[0xD5F], lim2);
                            func_00217710(0, 3);
                            return 0;
                        }
                    } else if (keys & 0xC0) {
                        if (F66->b3) {
                            if (*(u16 *)(duel + 0xC90) != 0) {
                                DUEL[0xD57] = 0x2E;
                                DUEL_U32(0xC4C) = ((DuelState *)duel)->deckList[*(u16 *)(duel + 0xC8E) + DUEL[0xD5F]] | 0x10000;
                                func_00217710(0, 4);
                            } else {
                                func_00217710(0, 6);
                            }
                            return 0;
                        }
                    }
                }
                if (DUEL[0xD5F] != old) {
                    func_00217710(0, 3);
                    return 0;
                }
            }
            if (scrollA != 0) {
                lim2 = MAX_001CEE60(*(u16 *)(duel + 0xC8C) - 5, 0);
                old = *(u16 *)(duel + 0xC8A);
                n = old + scrollA;
                *(u16 *)(duel + 0xC8A) = MIN_001CEE60(MAX_001CEE60(n, 0), lim2);
                if (*(u16 *)(duel + 0xC8A) != old) {
                    func_00217710(0, 3);
                }
                return 0;
            }
            if (scrollB != 0) {
                lim2 = MAX_001CEE60(*(u16 *)(duel + 0xC90) - 5, 0);
                old = *(u16 *)(duel + 0xC8E);
                *(u16 *)(duel + 0xC8E) = MIN_001CEE60(MAX_001CEE60(old + scrollB, 0), lim2);
                if (*(u16 *)(duel + 0xC8E) != old) {
                    func_00217710(0, 3);
                }
                return 0;
            }
            keys = rep;
            if (keys & 0x10) {
                if (side == 0) {
                    if (*(u16 *)(duel + 0xC8C) != 0) {
                        *(u16 *)(duel + 0xCAC) = ((DuelState *)duel)->trunkList[*(u16 *)(duel + 0xC8A) + DUEL[0xD5E]];
                    } else {
                        func_00217710(0, 6);
                        return 0;
                    }
                } else {
                    if (*(u16 *)(duel + 0xC90) != 0) {
                        *(u16 *)(duel + 0xCAC) = ((DuelState *)duel)->deckList[*(u16 *)(duel + 0xC8E) + DUEL[0xD5F]];
                    } else {
                        func_00217710(0, 6);
                        return 0;
                    }
                }
                DUEL[0xCB3] = 0x11;
                DUEL[0xCBD] = 0;
                DUEL[0xD35] = 0x2D;
                DUEL[0xD57] = 0x20;
                func_00217710(0, 0x10);
                return 0;
            }
            if (!(keys & 0x20)) {
                break;
            }
            if (F66->b3) {
                DUEL_U32(0xC4C) = 999;
            }
            DUEL[0xD57] = 0x2E;
            func_00217710(0, 5);
            return 0;
        case 0x2E:
            DUEL_S16(0xC9C) = MAX_001CEE60(DUEL_S16(0xC9C) - 8, 0);
            if (DUEL_S16(0xC9C) > 0) {
                break;
            }
            DUEL[0xCB2] = 0x18;
            if (F66->b3) {
                DUEL[0xD57] = 0x39;
                F66->b3 = 0;
            } else {
                DUEL[0xD57] = 0x18;
            }
            return 0;
        case 0x2F: {
            u16 *buf;
            s32 bpl;
            loops = (DUEL[0xD36] & 0x80) ? 1 : 2;
            prevX = me[0x33D];
            prevZ = me[0x33E];
            bpl = DUEL[0xD36] & 0x7F;
            k = 0;
            buf = (u16 *)CAMPAIGN_WORK_ADDR;
            *(u16 **)(duel + 0x6D8) = buf;
            DUEL[0xD5E] = 0;
            *(u16 *)(duel + 0xC8C) = 0;
            for (; k < loops; k++) {
                if (DUEL[0xD35] == 0 || DUEL[0xD35] == 1) {
                    for (i = 1; i < 6; i++) {
                        if ((p = (u8 *)func_001DF540(bpl, i)) != NULL) {
                            buf[(*(u16 *)(duel + 0xC8C))++] = (p[0x41] << 8) | p[0x40];
                        }
                    }
                }
                if (DUEL[0xD35] == 0 || DUEL[0xD35] == 2) {
                    for (i = 6; i < 11; i++) {
                        if ((p = (u8 *)func_001DF540(bpl, i)) != NULL) {
                            buf[(*(u16 *)(duel + 0xC8C))++] = (p[0x41] << 8) | p[0x40];
                        }
                    }
                }
                bpl = (bpl + 1) & 2;
            }
            if (*(u16 *)(duel + 0xC8C) == 0) {
                DUEL[0xD57] = 0x39;
                F66->b3 = 0;
                return 0;
            }
            me[0x33D] = *(u8 *)*(u16 **)(duel + 0x6D8);
            me[0x33E] = **(u16 **)(duel + 0x6D8) >> 8;
            tz = ABS_001CEE60(me[0x33E] - prevZ);
            tx = ABS_001CEE60(me[0x33D] - prevX);
            gx = (s32)(f32)((me[0x33D] - 3) * 50);
            func_001D90E0((tx + tz) * 4, gx, (s32)(f32)((me[0x33E] - 3) * 50));
            DUEL[0xD57] = 0x30;
        }
        case 0x30:
            obj = (Object_001CEE60 *)func_001E36E0(me[0x33D], me[0x33E]);
            if (func_001FA6F0(-1, -1) != NULL) {
                return 0;
            }
            keys = rep;
            if (keys & 0xF00C) {
                tx = me[0x33D];
                tz = me[0x33E];
                if (keys & 0x3004) {
                    DUEL[0xD5E] = (DUEL[0xD5E] + *(u16 *)(duel + 0xC8C) - 1) % *(u16 *)(duel + 0xC8C);
                } else {
                    DUEL[0xD5E] = (DUEL[0xD5E] + *(u16 *)(duel + 0xC8C) + 1) % *(u16 *)(duel + 0xC8C);
                }
                me[0x33D] = *(u8 *)&((DuelState *)duel)->trunkList[DUEL[0xD5E]];
                me[0x33E] = ((DuelState *)duel)->trunkList[DUEL[0xD5E]] >> 8;
                tz = ABS_001CEE60(me[0x33E] - tz);
                tx = ABS_001CEE60(me[0x33D] - tx);
                gx = (s32)(f32)((me[0x33D] - 3) * 50);
                func_001D90E0((tx + tz) * 4, gx, (s32)(f32)((me[0x33E] - 3) * 50));
                func_00217710(0, 3);
                return 0;
            }
            if (obj == NULL) {
                break;
            }
            if (keys & 0x10) {
                v = 0;
                if (obj->z > 0) {
                    v = func_00267380((s32)obj, DUEL[0xD54]);
                }
                if (v != 0) {
                    func_00217710(0, 6);
                } else {
                    DUEL[0xCB3] = 0x11;
                    *(u16 *)(duel + 0xCAC) = obj->id;
                    DUEL[0xCBD] = 0;
                    DUEL[0xD35] = 0x30;
                    DUEL[0xD57] = 0x20;
                    func_00217710(0, 0x10);
                }
                return 0;
            }
            if (keys & 0xC0) {
                DUEL[0xD57] = 0x31;
                DUEL_U32(0xC4C) = (obj->x << 8) | obj->z;
                func_00217710(0, 4);
                return 0;
            }
            if (!(keys & 0x20)) {
                break;
            }
            DUEL[0xD57] = 0x31;
            DUEL_U32(0xC4C) = -1;
            func_00217710(0, 5);
            return 0;
        case 0x31:
            DUEL[0xD57] = 0x39;
            F66->b3 = 0;
            return 0;
        case 0x32:
            DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 8, 0x40);
            if (DUEL_S16(0xC9C) < 0x40) {
                break;
            }
            DUEL[0xD57] = 0x33;
        case 0x33:
            if (!(rep & 0xFFFF & 0xF0)) {
                break;
            }
            DUEL[0xD57] = 0x34;
            func_00217710(0, 4);
            return 0;
        case 0x34:
            DUEL_S16(0xC9C) = MAX_001CEE60(DUEL_S16(0xC9C) - 8, 0);
            if (DUEL_S16(0xC9C) > 0) {
                break;
            }
            DUEL[0xCB2] = 0x18;
            DUEL[0xD57] = DUEL[0xD35];
            return 0;
        case 0x36:
            if (DUEL[0xD5B] + 1 >= DUEL[0xD59]) {
                func_001D91B0(0x10, duel[DUEL[0xD5B] + 0xCCA], duel[DUEL[0xD5B] + 0xCFB], duel[DUEL[0xD5B] + 0xCCB],
                              duel[DUEL[0xD5B] + 0xCFC]);
                DUEL[0xD57] = 0x3C;
                return 0;
            }
        case 0x37:
            j = DUEL[0xD5B];
            cx = duel[j + 0xCCB];
            cz = duel[j + 0xCFC];
            x0 = (s32)(f32)((duel[j + 0xCCA] - 3) * 50);
            z0 = func_001A22C0((duel[j + 0xCFB] - 3) * 50);
            x1 = (s32)(f32)((cx - 3) * 50);
            z1 = (s32)(f32)((cz - 3) * 50);
            px = x0 + DUEL_DUO(0x6C8)->px;
            pz = z0 + DUEL_DUO(0x6C8)->pz;
            if (x1 != px) {
                if (px < x1) {
                    step = x1 - px;
                    step = (step > 5) ? 5 : step;
                    px += step;
                } else {
                    step = px - x1;
                    step = (step > 5) ? 5 : step;
                    px -= step;
                }
            }
            if (z1 != pz) {
                if (pz < z1) {
                    step = z1 - pz;
                    step = (step > 5) ? 5 : step;
                    pz += step;
                } else {
                    step = pz - z1;
                    step = (step > 5) ? 5 : step;
                    pz -= step;
                }
            }
            DUEL_DUO(0x6C8)->px = px - x0;
            DUEL_DUO(0x6C8)->pz = pz - z0;
            if (x1 != px || z1 != pz) {
                func_001DDAC0(DUEL[0xD55], DUEL[0xD56], cx, cz);
                return 0;
            }
            func_001DFD50(DUEL[0xD55], DUEL[0xD56], cx, cz);
            DUEL[0xD5B]++;
            if (!F66->b4) {
                DUEL_U32(0xC70) = func_0024B310(DUEL[0xD55], DUEL[0xD56], cx, cz, duel + 0x6E8, 0);
                if (DUEL_U32(0xC70) == 0) {
                    DUEL_U32(0xC68) = func_0024F780(DUEL[0xD55], DUEL[0xD56], cx, cz, duel + 0x6E8);
                }
            }
            if (DUEL[0xD5B] < DUEL[0xD59]) {
                return 0;
            }
            DUEL[0xD57] = 0x38;
            if (DUEL_U32(0xC70) != 0 || DUEL_U32(0xC68) != 0) {
                return 1;
            }
        case 0x38:
            DUEL[0xD57] = 0x39;
            if (!F66->b4 && !F66->b2 && DUEL_DUO(0x6C8)->flags57.b2) {
                DUEL_U32(0xC6C) = func_00252440(DUEL[0xD55], DUEL[0xD56], duel + 0xC40, 0);
                return 1;
            }
        case 0x39:
            DUEL[0xD57] = 0x3A;
            F66->b4 = 0;
            if (DUEL_DUO(0x6C8) != NULL) {
                DUEL_DUO(0x6C8)->flags57.b4 = DUEL_DUO(0x6C8)->flags57.b2;
                DUEL_DUO(0x6C8)->flags57.b5 = DUEL_DUO(0x6C8)->flags57.b3;
                DUEL_DUO(0x6C8)->flags57.b6 = 0;
                DUEL_DUO(0x6C8)->flags57.b0 = 1;
                if (DUEL_DUO(0x6C8)->flags57.b4) {
                    DUEL_DUO(0x6C8)->status51 = 0x80;
                }
                if (me[0x33C] >= 100 && DUEL_DUO(0x6C8)->z == 0 && func_001E0C70(DUEL_DUO(0x6C8), 1, 0) != 0 &&
                    func_00216EC0(DUEL[0xD54], DUEL[0xD37]) == 0) {
                    n = func_00215D30(DUEL[0xD54], DUEL_DUO(0x6C8)->id);
                    lvl = 0;
                    if (n >= 7) {
                        lvl = 2;
                    } else if (n >= 4) {
                        lvl = 1;
                    }
                    card = func_002170A0(DUEL[0xD37], DUEL_DUO(0x6C8)->fromX, DUEL_DUO(0x6C8)->fromZ, lvl);
                    if (card != 999) {
                        func_00216F80(DUEL[0xD54], DUEL[0xD37], 1);
                        func_00216040(DUEL[0xD54], 0, card);
                        DUEL[0xCB2] = 0xB;
                        *(u16 *)(duel + 0xCAA) = card;
                        DUEL_S16(0xC9C) = 0;
                        DUEL_S16(0xC9A) = 0;
                        DUEL[0xD57] = 0x32;
                        DUEL[0xD35] = 0x3A;
                        return 0;
                    }
                }
            }
            if (DUEL_U32(0xC64) != 0) {
                return 0;
            }
        case 0x3A:
            if (DUEL_DUO(0x6CC) != NULL) {
                gx = (s32)(f32)((me[0x33D] - 3) * 50);
                func_001D90E0(0x10, gx, (s32)(f32)((me[0x33E] - 3) * 50));
            }
            DUEL[0xD57] = 0x3B;
        case 0x3B:
            if (func_001FA6F0(-1, -1) != NULL) {
                return 0;
            }
            DUEL[0xD57] = 0x16;
            return 0;
        case 0x3C:
            if (func_001DD890(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z) != 0 ||
                func_001FA6F0(-1, -1) != NULL) {
                return 0;
            }
            if (func_001FF300() != 0) {
                return 0;
            }
            DUEL[0xD57] = 0x3D;
            DUEL_U32(0xC70) = func_0024B310(DUEL[0xD55], DUEL[0xD56], duel[DUEL[0xD5B] + 0xCCB], duel[DUEL[0xD5B] + 0xCFC],
                                            duel + 0x6E8, 0);
            if (DUEL_U32(0xC70) != 0) {
                return 1;
            }
        case 0x3D:
            DUEL[0xD57] = 0x39;
            DUEL_U32(0xC64) = func_00249680(DUEL[0xD55], DUEL[0xD56], duel[DUEL[0xD5B] + 0xCCB], duel[DUEL[0xD5B] + 0xCFC],
                                            duel + 0xC40, 0);
            return 1;
        case 0x3E:
            DUEL_DUO(0x6CC) = (Object_001CEE60 *)func_001E36E0(me[0x33D], me[0x33E]);
            if (DUEL_DUO(0x6CC) != NULL) {
                func_001DD890(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z);
            } else {
                func_001DDAC0(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, me[0x33D], me[0x33E]);
            }
            keys = rep;
            if (keys & 0xC0) {
                t2 = func_001DE9C0(DUEL[0xD54]) > 0;
                ok = 0;
                if (t2) {
                    t2 = me[0x344] > 0;
                }
                if (t2) {
                    if (!(me[0x344] & 0x80)) {
                        ok = 1;
                    }
                }
                if (func_001E24E0(me[0x33D], me[0x33E]) > 0) {
                    func_00217710(0, 6);
                    return 0;
                }
                DUEL[0xD57] = 0x3F;
                func_00217710(0, 4);
                if (ok != 0) {
                    if (func_001DF110(DUEL[0xD54]) < 5) {
                        func_0026F600(DUEL[0xD54], duel + 0x6E8);
                        func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
                        U66->b1 = 1;
                    }
                }
                return 0;
            }
            if (func_001FA6F0(-1, -1) != NULL) {
                return 0;
            }
            if (keys & 0x20) {
                if (DUEL[0xD59] > 0) {
                    tx = ABS_001CEE60(me[0x33E] - DUEL[0xCFB]);
                    tz = ABS_001CEE60(me[0x33D] - DUEL[0xCCA]);
                    me[0x33D] = DUEL[0xCCA];
                    me[0x33E] = DUEL[0xCFB];
                    gx = (s32)(f32)((me[0x33D] - 3) * 50);
                    func_001D90E0((tz + tx) * 8, gx, (s32)(f32)((me[0x33E] - 3) * 50));
                    DUEL[0xD59] = 0;
                }
                DUEL[0xD57] = 0x16;
                func_00217710(0, 5);
                return 0;
            }
            if (mDpad == 0) {
                break;
            }
            tx = me[0x33D];
            tz = me[0x33E];
            if (((held16 & 0x8000) && tx <= 0) || ((held16 & 0x2000) && tx >= 6)) {
                held = (u16)(held & 0x5FFF);
            }
            if ((((u16)held & 0x1000) && tz <= 0) || (((u16)held & 0x4000) && tz >= 6)) {
                held = (u16)(held & 0xAFFF);
            }
            if (F64->b6) {
                if ((keys = held) & 0x5000) {
                    held = (u16)(held & 0x5000);
                } else {
                    F64->b6 = 0;
                }
            }
            if ((u16)held & 0xA000) {
                if ((u16)held & 0x8000) {
                    tx--;
                } else {
                    tx++;
                }
                if ((u16)held & 0x5000) {
                    F64->b6 = 1;
                }
            } else if ((u16)held & 0x5000) {
                if ((u16)held & 0x1000) {
                    tz--;
                } else {
                    tz++;
                }
                F64->b6 = 0;
            } else {
                F64->b6 = 0;
                return 0;
            }
            me[0x33D] = tx;
            me[0x33E] = tz;
            if (DUEL[0xCCA] == tx && DUEL[0xCFB] == tz) {
                DUEL[0xD59] = 0;
            } else {
                DUEL[0xD59] = 1;
            }
            duel[DUEL[0xD59] + 0xCCA] = me[0x33D];
            duel[DUEL[0xD59] + 0xCFB] = me[0x33E];
            DUEL[0xD59]++;
            gx = (s32)(f32)((me[0x33D] - 3) * 50);
            func_001D90E0(8, gx, (s32)(f32)((me[0x33E] - 3) * 50));
            func_00217710(0, 3);
            return 0;
        case 0x3F:
            F67->b2 = 1;
            F67->b3 = 0;
            DUEL[0xD45] = 0;
            DUEL[0xD46] = 0;
            F67->b4 = 0;
            DUEL[0xD47] = 0;
            DUEL[0xD48] = 0;
            DUEL[0xD4B] = 0;
            DUEL[0xD4C] = 0;
            DUEL[0xD4D] = 0;
            DUEL[0xD49] = func_001DF110(DUEL[0xD54]);
            DUEL[0xD4A] = 0;
            func_001D7D10(DUEL[0xD54], 1);
            DUEL[0xD57] = 0x40;
        case 0x40:
            func_001D8880(DUEL[0xD54], 1);
            if (DUEL_DUO(0x6CC) != NULL) {
                func_001DD890(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z);
            } else {
                func_001DDAC0(DUEL_DUO(0x6C8)->x, DUEL_DUO(0x6C8)->z, me[0x33D], me[0x33E]);
            }
            if (F67->b3) {
                DUEL[0xD45] = MAX_001CEE60(DUEL[0xD45] - 0x10, 0);
                DUEL[0xD48] = MAX_001CEE60(DUEL[0xD48] - 0x10, 0);
            } else {
                DUEL[0xD45] = MIN_001CEE60(DUEL[0xD45] + 0x10, 0x80);
                DUEL[0xD48] = MIN_001CEE60(DUEL[0xD48] + 0x10, 0x80);
            }
            for (i = 0; i < 5; i++) {
                if ((sl = slot_001CEE60(i + 1)) != NULL && *(u8 **)sl != NULL) {
                    *(s16 *)(sl + 0x9A) = (DUEL[0xD45] << 7) >> 7;
                    func_001CDEB0(sl);
                }
            }
            if (F67->b3) {
                if (DUEL[0xD45] <= 0) {
                    for (i = 1; i < 6; i++) {
                        freeslot_001CEE60(slot_001CEE60(i));
                    }
                    F67->b2 = 0;
                    DUEL[0xD57] = 0x3E;
                }
            } else if (DUEL[0xD45] >= 0x80) {
                card = func_001DF0C0(DUEL[0xD54], DUEL[0xD49]);
                if (card < 0) {
                    card = 999;
                } else {
                    card &= 0xFFF;
                }
                if (DUEL[0xD49] < 5 && card != 999) {
                    DUEL[0xD57] = 0x41;
                } else {
                    DUEL[0xD57] = 0x43;
                }
            }
            return 0;
        case 0x41:
            sl = slot_001CEE60(DUEL[0xD49] + 1);
            func_001D8880(DUEL[0xD54], 1);
            if (sl != NULL && *(u8 **)sl != NULL) {
                func_001D8FB0(sl, 0x2EE, -8, DUEL[0xD49] * 125 - 250, -8, 0, 0x80);
            }
            DUEL[0xD46] = 0;
            DUEL[0xD57] = 0x42;
            func_00217710(0, 7);
        case 0x42:
            sl = slot_001CEE60(DUEL[0xD49] + 1);
            func_001D8880(DUEL[0xD54], 1);
            DUEL[0xD46] = MIN_001CEE60(DUEL[0xD46] + 6, 0x1E);
            if (sl != NULL && *(u8 **)sl != NULL) {
                *(s16 *)(sl + 0x9A) = (DUEL[0xD46] << 7) / 30;
                func_001CDEB0(sl);
            }
            if (DUEL[0xD46] < 0x1E) {
                break;
            }
            card_2717 = func_001DF0C0(DUEL[0xD54], DUEL[0xD49] + 1);
            if (card_2717 < 0) {
                card_2717 = 999;
            } else {
                card_2717 &= 0xFFF;
            }
            if (sl != NULL && *(u8 **)sl != NULL) {
                func_001D8FB0(sl, DUEL[0xD49] * 125 - 250, 0x1C0, DUEL[0xD49] * 125 - 250, -8, 0x80, 0x80);
            }
            if (++DUEL[0xD49] < 5 && card_2717 != 999) {
                DUEL[0xD57] = 0x41;
            } else {
                DUEL[0xD57] = 0x43;
            }
            return 0;
        case 0x43:
            have = func_001DE5C0(DUEL[0xD54]);
            need = func_001E08F0(2, DUEL[0xD4F] + 1, 0);
            func_001D8880(DUEL[0xD54], 1);
            if (mLR != 0) {
                n = func_001DF110(DUEL[0xD54]);
                old = DUEL[0xD4F];
                if (mLeft != 0) {
                    DUEL[0xD4F] = (old + n - 1) % n;
                } else {
                    DUEL[0xD4F] = (old + n + 1) % n;
                }
                if (DUEL[0xD4F] != old) {
                    func_00217710(0, 3);
                }
                return 0;
            }
            keys = rep;
            if (mUD != 0) {
                if (need <= have) {
                    step = mUp ? 1 : -1;
                    if (func_001DF370(DUEL[0xD54], DUEL[0xD4F], (step > 0) ? DUEL[0xD4E] + step : 0) != 0) {
                        DUEL[0xD4E] += step;
                        func_00217710(0, 9);
                    }
                }
                return 0;
            }
            if (keys & 0x10) {
                DUEL[0xCB3] = 0x11;
                DUEL[0xCBD] = 0;
                DUEL[0xD35] = 0x43;
                DUEL[0xD57] = 0x20;
                func_00217710(0, 0x10);
                return 0;
            }
            if (keys & 0xC0) {
                v = DUEL[0xD4E] != 0 ? func_0026E950() : need;
                if (have < v) {
                    func_00217710(0, 6);
                    return 0;
                }
                DUEL[0xD57] = 0x44;
                func_00217710(0, 4);
                return 0;
            }
            if (!(keys & 0x20)) {
                break;
            }
            F67->b3 = 1;
            DUEL[0xD57] = 0x40;
            func_00217710(0, 5);
            return 0;
        case 0x44:
            F67->b4 = 0;
            DUEL[0xD47] = 0;
            DUEL[0xD4A] = (DUEL_DUO(0x6CC) ? 1 : 0) + MAX_001CEE60(DUEL[0xD4E], 1);
            func_001D82C0(DUEL[0xD54]);
            DUEL[0xD57] = 0x45;
        case 0x45:
            if (F67->b4) {
                DUEL[0xD47] = MAX_001CEE60(DUEL[0xD47] - 2, 0);
                DUEL[0xD45] = MIN_001CEE60(DUEL[0xD45] + 0x10, 0x80);
            } else {
                DUEL[0xD47] = MIN_001CEE60(DUEL[0xD47] + 2, 0x1E);
                DUEL[0xD45] = MAX_001CEE60(DUEL[0xD45] - 0x10, 0);
            }
            if (DUEL_DUO(0x6CC) != NULL && DUEL_DUO(0x6CC)->flags57.b4 && DUEL_DUO(0x6CC)->id < 0x2AB) {
                func_001F2800(DUEL_DUO(0x6CC)->model, DUEL[0xD45]);
                DUEL_DUO(0x6CC)->progress = DUEL[0xD45];
            }
            for (i = 0; i < 6; i++) {
                if ((sl = slot_001CEE60(i)) != NULL && *(u8 **)sl != NULL) {
                    *(s16 *)(sl + 0x9A) = (DUEL[0xD47] << 7) / 30;
                    func_001CDEB0(sl);
                }
            }
            if (F67->b4) {
                if (DUEL[0xD47] <= 0) {
                    func_001D8080(DUEL[0xD54]);
                    DUEL[0xD57] = 0x43;
                }
            } else {
                have = func_001E0150(DUEL[0xD54]);
                need = func_001E01F0(DUEL[0xD54]);
                card = func_001DF0C0(DUEL[0xD54], DUEL[0xD4F]) & 0xFFF;
                if (DUEL_DUO(0x6CC) != NULL || DUEL[0xD4E] != 0) {
                    tx = 999;
                    tz = 999;
                    if (DUEL_DUO(0x6CC) != NULL) {
                        tx = DUEL_DUO(0x6CC)->id;
                        if (tx < 0x2AB) {
                            have--;
                        } else {
                            need--;
                        }
                        if (DUEL[0xD4E] == 0) {
                            tz = card;
                        }
                    }
                    card = func_0026EB10(DUEL[0xD54], tx, tz);
                }
                if (card < 0x2AB) {
                    if (have >= 5) {
                        func_001E42C0(8, 0, -200, 0x116);
                    }
                } else if (need >= 5) {
                    func_001E42C0(8, 0, -200, 0x117);
                }
                if (DUEL[0xD47] >= 0x1E) {
                    F67->b2 = 0;
                    DUEL[0xD57] = 0x46;
                }
            }
            return 0;
        case 0x46:
            keys = rep;
            if (keys & 0xC0) {
                v = func_001E08F0(2, DUEL[0xD4F] + 1, 0);
                if (DUEL[0xD4E] != 0) {
                    v = func_0026E950();
                }
                func_001DE5E0(DUEL[0xD54], 1, v);
                if (DUEL[0xD4A] >= 2) {
                    DUEL[0xD4B] = DUEL_DUO(0x6CC) ? 0 : 1;
                    DUEL[0xD4C] = DUEL[0xD4B] + 1;
                    DUEL[0xD4D] = DUEL[0xD4B] + DUEL[0xD4A];
                    if (DUEL_DUO(0x6CC) != NULL) {
                        if ((sl = cardControls) != NULL && *(u8 **)sl != NULL) {
                            ((Flags8_001CEE60 *)(sl + 0x9F))->b4 = 0;
                            ((Flags8_001CEE60 *)(sl + 0x9F))->b6 = 0;
                            ((Flags8_001CEE60 *)(sl + 0x9F))->b5 = 0;
                            func_00205CB0(sl + 0x10, -125.0f, -8.0f);
                            func_00205CB0(sl + 0x20, -125.0f, -8.0f);
                            *(s32 *)(sl + 0x30) = 0;
                            *(s32 *)(sl + 0x34) = 0;
                            *(s32 *)(sl + 0x38) = 0;
                            *(s32 *)(sl + 0x3C) = 0;
                            *(s32 *)(sl + 0x40) = 0;
                            *(s32 *)(sl + 0x44) = 0x10000;
                            *(s32 *)(sl + 0x48) = 0;
                            *(s32 *)(sl + 0x4C) = 0;
                            *(s16 *)(sl + 0x98) = 0x80;
                            *(s16 *)(sl + 0x9A) = 0;
                            func_001CDEB0(sl);
                        }
                        func_001DFBB0(DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z);
                        DUEL_DUO(0x6CC) = NULL;
                    }
                    DUEL[0xD57] = 0x47;
                } else {
                    DUEL[0xD4B] = 1;
                    DUEL[0xD57] = 0x4C;
                }
                func_00217710(0, 4);
                func_001E4530();
                return 0;
            }
            if (!(keys & 0x20)) {
                break;
            }
            F67->b2 = 1;
            F67->b4 = 1;
            DUEL[0xD4B] = 0;
            DUEL[0xD4C] = 0;
            DUEL[0xD4D] = 0;
            DUEL[0xD57] = 0x45;
            func_00217710(0, 5);
            func_001E4530();
            return 0;
        case 0x47:
            nx = duel[DUEL[0xD4B] + 0xD2C];
            nz = duel[DUEL[0xD4C] + 0xD2C];
            DUEL_U32(0xC78) = func_0026E610(2, nx, 2, nz, duel + 0x6E8);
            if ((s32)DUEL_U32(0xC78) < 0) {
                DUEL_U32(0xC78) = 2;
            }
            if ((s32)DUEL_U32(0xC78) >= 0) {
                if ((sl = slot_001CEE60(nx)) != NULL && *(u8 **)sl != NULL) {
                    ((Flags8_001CEE60 *)(*(u8 **)sl + 0x83))->b6 = 1;
                }
                if ((sl = slot_001CEE60(nz)) != NULL && *(u8 **)sl != NULL) {
                    ((Flags8_001CEE60 *)(*(u8 **)sl + 0x83))->b6 = 1;
                }
                return 1;
            }
            if ((sl = slot_001CEE60(nz)) != NULL && *(u8 **)sl != NULL) {
                ((Flags8_001CEE60 *)(sl + 0x9F))->b4 = 0;
                func_001D9030(sl, 0x7D, -8, -0x7D, -8, 0, 0x80);
            }
            DUEL[0xD46] = 0;
            DUEL[0xD57] = 0x48;
        case 0x48:
            sl = slot_001CEE60(duel[DUEL[0xD4C] + 0xD2C]);
            DUEL[0xD46] = MIN_001CEE60(DUEL[0xD46] + 3, 0x1E);
            if (sl != NULL && *(u8 **)sl != NULL) {
                *(s16 *)(sl + 0x9A) = (DUEL[0xD46] << 7) / 30;
                func_001CDEB0(sl);
            }
            if (DUEL[0xD46] < 0x1E) {
                break;
            }
            nx_F = duel[DUEL[0xD4B] + 0xD2C];
            for (i = DUEL[0xD4C] + 1, j = 0, k = 0x7D; i < DUEL[0xD4D]; k += 0x10, j++, i++) {
                if ((sl = slot_001CEE60(duel[i + 0xD2C])) != NULL && *(u8 **)sl != NULL) {
                    ((Flags8_001CEE60 *)(sl + 0x9F))->b4 = 0;
                    func_001D9030(sl, k, -8, -0x7D, -8, 0, 0x80);
                }
            }
            if ((sl = slot_001CEE60(nx_F)) != NULL && *(u8 **)sl != NULL) {
                ((Flags8_001CEE60 *)(sl + 0x9F))->b5 = 0;
                ((Flags8_001CEE60 *)(sl + 0x9F))->b6 = 0;
                ((Flags8_001CEE60 *)(sl + 0x9F))->b4 = 1;
                *(s32 *)(sl + 0x30) = 0;
                *(s32 *)(sl + 0x34) = 0;
                *(s32 *)(sl + 0x38) = 0;
                *(s32 *)(sl + 0x3C) = 0;
                *(s32 *)(sl + 0x40) = 0;
                *(s32 *)(sl + 0x44) = 0;
                *(s32 *)(sl + 0x48) = 0x30000;
                *(s32 *)(sl + 0x4C) = 0;
                func_001D9030(sl, -0x7D, -8, -0x177, -8, 0, 0x80);
            }
            DUEL[0xD46] = 0;
            DUEL[0xD57] = 0x49;
            return 0;
        case 0x49:
            nx_2969 = duel[DUEL[0xD4B] + 0xD2C];
            sl = slot_001CEE60(nx_2969);
            DUEL[0xD46] = MIN_001CEE60(DUEL[0xD46] + 3, 0x1E);
            if (sl != NULL && *(u8 **)sl != NULL) {
                *(s16 *)(sl + 0x9A) = (DUEL[0xD46] << 7) / 30;
                func_001CDEB0(sl);
            }
            if (DUEL[0xD46] < 0x1E) {
                break;
            }
            if (nx_2969 != 0) {
                func_001DF2C0(DUEL[0xD54], nx_2969 - 1);
            }
            if (sl != NULL && *(u8 **)sl != NULL) {
                freeslot_001CEE60(sl);
            }
            duel[DUEL[0xD4B] + 0xD2C] = 6;
            DUEL[0xD4B] = DUEL[0xD4C];
            if (++DUEL[0xD4C] >= DUEL[0xD4D]) {
                DUEL[0xD57] = 0x4A;
            } else {
                DUEL[0xD57] = 0x47;
            }
            return 0;
        case 0x4A:
            if ((sl = slot_001CEE60(duel[DUEL[0xD4B] + 0xD2C])) != NULL && *(u8 **)sl != NULL) {
                ((Flags8_001CEE60 *)(sl + 0x9F))->b4 = 1;
                func_001D9030(sl, -0x7D, -8, 0, -8, 0, 0x80);
            }
            DUEL[0xD46] = 0;
            DUEL[0xD57] = 0x4B;
        case 0x4B:
            sl = slot_001CEE60(duel[DUEL[0xD4B] + 0xD2C]);
            DUEL[0xD46] = MIN_001CEE60(DUEL[0xD46] + 3, 0x1E);
            if (sl != NULL && *(u8 **)sl != NULL) {
                *(s16 *)(sl + 0x9A) = (DUEL[0xD46] << 7) / 30;
                func_001CDEB0(sl);
            }
            if (DUEL[0xD46] < 0x1E) {
                break;
            }
            DUEL[0xD57] = 0x4C;
            return 0;
        case 0x4C:
            if ((sl = slot_001CEE60(duel[DUEL[0xD4B] + 0xD2C])) != NULL && (sub = *(u8 **)sl) != NULL) {
                obj = *(Object_001CEE60 **)(sub + 0x90);
                *(Vec4_001CEE60 *)(sl + 0x10) = *(Vec4_001CEE60 *)sub;
                func_001E10F0(me[0x33D], me[0x33E], 0, sl + 0x20);
                ((Flags8_001CEE60 *)(sl + 0x9F))->b4 = 1;
                *(s32 *)(sl + 0x30) = 0;
                *(s32 *)(sl + 0x34) = 0x10000;
                *(s32 *)(sl + 0x38) = 0x10000;
                *(s32 *)(sl + 0x3C) = 0;
                *(s32 *)(sl + 0x40) = 0x4000;
                *(s32 *)(sl + 0x44) = 0;
                *(s32 *)(sl + 0x48) = 0;
                *(s32 *)(sl + 0x4C) = 0;
                if (obj->flags57.b4) {
                    *(s32 *)(sl + 0x48) = 0x8000;
                }
                if (obj->flags57.b5) {
                    *(s32 *)(sl + 0x44) -= 0x4000;
                }
                if (DUEL[0xD54] == 0) {
                    *(s32 *)(sl + 0x44) += 0x8000;
                }
                ((Flags8_001CEE60 *)(sl + 0x9F))->b5 = 1;
                func_00205C40((s32)(sl + 0x50));
                *(s32 *)(sl + 0x60) = 0;
                *(s32 *)(sl + 0x64) = 0;
                *(s32 *)(sl + 0x68) = 0;
                *(s32 *)(sl + 0x6C) = 0;
                ((Flags8_001CEE60 *)(sl + 0x9F))->b6 = 1;
                *(s32 *)(sl + 0x70) = 0x3EF00000;
                *(s32 *)(sl + 0x74) = 0x3EFA6F4E;
                *(s32 *)(sl + 0x78) = 0x3F800000;
                *(s32 *)(sl + 0x7C) = 0;
                *(s32 *)(sl + 0x80) = 0x3DCCCCCD;
                *(s32 *)(sl + 0x84) = 0x3DCCCCCD;
                *(s32 *)(sl + 0x88) = 0x3F800000;
                *(s32 *)(sl + 0x8C) = 0;
                *(s16 *)(sl + 0x98) = 0x80;
                *(s16 *)(sl + 0x9A) = 0;
                func_001CDEB0(sl);
            }
            DUEL[0xD46] = 0;
            DUEL[0xD57] = 0x4D;
        case 0x4D:
            sl = slot_001CEE60(duel[DUEL[0xD4B] + 0xD2C]);
            DUEL[0xD48] = MAX_001CEE60(DUEL[0xD48] - 0x10, 0);
            DUEL[0xD46] = MIN_001CEE60(DUEL[0xD46] + 1, 0x1E);
            if (sl != NULL && *(u8 **)sl != NULL) {
                *(s16 *)(sl + 0x9A) = (DUEL[0xD46] << 7) / 30;
                func_001CDEB0(sl);
            }
            if (DUEL[0xD46] < 0x1E) {
                break;
            }
            DUEL[0xD57] = 0x4F;
            if (sl != NULL && *(u8 **)sl != NULL) {
                card = (*(Object_001CEE60 **)(*(u8 **)sl + 0x90))->id;
                have = func_001E0150(DUEL[0xD54]);
                need = func_001E01F0(DUEL[0xD54]);
                t = 0;
                if (card < 0x2AB) {
                    if (have >= 5) {
                        t = 1;
                    }
                } else if (need >= 5) {
                    t = 1;
                }
                if (t) {
                    DUEL[0xD57] = 0x4E;
                }
            }
            return 0;
        case 0x4E:
            func_0026EEA0(duel + 0x6E8, 2, duel[DUEL[0xD4B] + 0xD2C]);
            func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
            F65->b5 = 1;
            DUEL[0xD57] = 0x50;
            return 0;
        case 0x4F:
            if ((sl = slot_001CEE60(duel[DUEL[0xD4B] + 0xD2C])) != NULL && (sub = *(u8 **)sl) != NULL) {
                tmpo = **(Object_001CEE60 **)(sub + 0x90);
                tmpo.view = NULL;
                tmpo.flags57.b7 = 0;
                tmpo.flags58.b0 = 0;
                tmpo.flags58.b2 = 0;
                freeslot_001CEE60(sl);
                DUEL_DUO(0x6CC) = (Object_001CEE60 *)func_001DF5F0(DUEL[0xD54], me[0x33D], me[0x33E], &tmpo, 0);
                if (DUEL_DUO(0x6CC) != NULL) {
                    if (func_0024F520(DUEL_DUO(0x6CC)->x, DUEL_DUO(0x6CC)->z, DUEL_DUO(0x6CC)->fromX,
                                      DUEL_DUO(0x6CC)->fromZ, duel + 0x6E8) == 1) {
                        func_002550C0((u32 *)(duel + 0x6E8), (u16 *)(duel + 0x700), 0);
                        F65->b4 = 1;
                    }
                    func_00217710(0, 8);
                }
            }
            for (i = 0; i < 6; i++) {
                freeslot_001CEE60(slot_001CEE60(i));
            }
            DUEL[0xD57] = 0x50;
            return 0;
        case 0x50:
            if ((n = duel[DUEL[0xD4B] + 0xD2C]) != 0) {
                func_001DF2C0(DUEL[0xD54], n - 1);
            }
            for (i = 0; i < 6; i++) {
                freeslot_001CEE60(slot_001CEE60(i));
            }
            DUEL[0xD45] = 0;
            DUEL[0xD46] = 0;
            DUEL[0xD47] = 0;
            DUEL[0xD48] = 0;
            DUEL[0xD49] = 0;
            DUEL[0xD4A] = 0;
            ((Flags8_001CEE60 *)(me + 0x346))->b0 = 0;
            DUEL[0xD57] = 0x16;
            return 0;
        case 0x51:
            F67->b2 = 1;
            F67->b3 = 0;
            DUEL[0xD45] = 0;
            DUEL[0xD46] = 0;
            F67->b4 = 0;
            DUEL[0xD47] = 0;
            DUEL[0xD48] = 0;
            DUEL[0xD4B] = 0;
            DUEL[0xD4C] = 0;
            DUEL[0xD4D] = 0;
            DUEL[0xD49] = func_001DF110(DUEL[0xD54]);
            DUEL[0xD4A] = 0;
            func_001D7D10(DUEL[0xD54], 0);
            DUEL[0xD57] = 0x52;
        case 0x52:
            if (F67->b3) {
                DUEL[0xD45] = MAX_001CEE60(DUEL[0xD45] - 0x10, 0);
            } else {
                DUEL[0xD45] = MIN_001CEE60(DUEL[0xD45] + 0x10, 0x80);
            }
            for (i = 0; i < 5; i++) {
                if ((sl = slot_001CEE60(i + 1)) != NULL && *(u8 **)sl != NULL) {
                    *(s16 *)(sl + 0x9A) = (DUEL[0xD45] << 7) >> 7;
                    func_001CDEB0(sl);
                }
            }
            if (F67->b3) {
                if (DUEL[0xD45] <= 0) {
                    for (i = 1; i < 6; i++) {
                        freeslot_001CEE60(slot_001CEE60(i));
                    }
                    F67->b2 = 0;
                    DUEL[0xD57] = 0x16;
                }
            } else if (DUEL[0xD45] >= 0x80) {
                DUEL[0xD57] = 0x53;
            }
            return 0;
        case 0x53:
            keys = rep;
            if (mLR != 0) {
                n = func_001DF110(DUEL[0xD54]);
                old = DUEL[0xD4F];
                if (mLeft != 0) {
                    DUEL[0xD4F] = (old + n - 1) % n;
                } else {
                    DUEL[0xD4F] = (old + n + 1) % n;
                }
                if (DUEL[0xD4F] != old) {
                    func_00217710(0, 3);
                }
                return 0;
            }
            if (keys & 0x10) {
                DUEL[0xCB3] = 0x11;
                DUEL[0xCBD] = 0;
                DUEL[0xD35] = 0x53;
                DUEL[0xD57] = 0x20;
                func_00217710(0, 0x10);
                return 0;
            }
            if (!(keys & 0x20)) {
                break;
            }
            F67->b3 = 1;
            DUEL[0xD57] = 0x52;
            func_00217710(0, 5);
            return 0;
        case 0x54:
            if ((fullA && fullB) || (!fullA && !fullB)) {
                if (DUEL[0xD50] < 2) {
                    DUEL[0xD35] = DUEL[0xD50] + 4;
                    DUEL[0xD36] = DUEL[0xD50];
                } else {
                    DUEL[0xD35] = 6;
                }
            } else if (fullA) {
                if (DUEL[0xD50] < 2) {
                    if (DUEL[0xD50] == 0) {
                        DUEL[0xD35] = 2;
                    } else {
                        DUEL[0xD35] = 3;
                    }
                } else {
                    DUEL[0xD35] = 3;
                }
                DUEL[0xD36] = 0;
            } else {
                if (DUEL[0xD50] < 2) {
                    if (DUEL[0xD50] == 1) {
                        DUEL[0xD35] = 2;
                    } else {
                        DUEL[0xD35] = 3;
                    }
                } else {
                    DUEL[0xD35] = 3;
                }
                DUEL[0xD36] = 1;
            }
            if (DUEL[0xD35] == 2U || DUEL[0xD35] == 4U || DUEL[0xD35] == 5U) {
                if (func_001A82E0(0x16) != 0) {
                    func_00217980(0x17, 0);
                }
            } else if (DUEL[0xD35] == 3) {
                if (func_001A82E0(0x16) != 0) {
                    func_00217980(0x2A, 0);
                }
            }
            DUEL[0xD57] = 0x55;
        case 0x55:
            if (func_002179C0() != 0) {
                break;
            }
            if (DUEL[0xD35] == 2U || DUEL[0xD35] == 4U || DUEL[0xD35] == 5U) {
                if (func_001A82E0(0x16) != 0) {
                    func_00217980(0x17, 1);
                }
            } else if (DUEL[0xD35] == 3) {
                if (func_001A82E0(0x16) != 0) {
                    func_00217980(0x2A, 1);
                }
            }
            DUEL_DUO(0x6CC) = NULL;
            DUEL_DUO(0x6C8) = NULL;
            DUEL[0xD54] = DUEL[0xD36];
            DUEL[0xCB2] = DUEL[0xD35];
            DUEL_S16(0xC9C) = 0;
            DUEL_S16(0xC9A) = 0;
            DUEL[0xD57] = 0x56;
        case 0x56:
            if (DUEL[0xD3E] < 0x80) {
                break;
            }
            DUEL[0xD35] = 0;
            DUEL[0xD57] = 0x57;
        case 0x57:
            if (DUEL[0xD35] != 0) {
                DUEL[0xD35]--;
                return 0;
            }
            DUEL[0xD57] = 0x58;
        case 0x58:
            if (DUEL[0xCB2] == 2U || DUEL[0xCB2] == 4U || DUEL[0xCB2] == 5U) {
                p = (u8 *)func_001DF540(DUEL[0xD54], 0);
                gx = (s32)(f32)((p[0x40] - 3) * 50);
                func_001D90E0(0x40, gx, (s32)(f32)((p[0x41] - 3) * 50));
                DUEL[0xD57] = 0x59;
            } else if (DUEL[0xCB2] == 3) {
                DUEL[0xD57] = 0x5A;
            } else {
                DUEL[0xD57] = 0x5B;
            }
            DUEL[0xD3A] = 0;
            return 1;
        case 0x59:
            DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 1, 0x40);
            if (DUEL_S16(0xC9C) < 0x40) {
                break;
            }
            if (func_001FA6F0(-1, -1) != NULL) {
                break;
            }
            DUEL[0xD57] = 0x5C;
            return 1;
        case 0x5A:
            DUEL[0xD3A] = MIN_001CEE60(DUEL[0xD3A] + 2, 0x80);
            DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 1, 0x40);
            if (DUEL_S16(0xC9C) < 0x40) {
                break;
            }
            if (DUEL[0xD3A] < 0x80) {
                break;
            }
            DUEL[0xD57] = 0x5C;
            return 1;
        case 0x5B:
            DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 1, 0x40);
            if (DUEL_S16(0xC9C) < 0x40) {
                break;
            }
            DUEL[0xD57] = 0x5C;
            return 1;
        case 0x5C:
            if (DUEL[0xCB2] == 2U || DUEL[0xCB2] == 4U || DUEL[0xCB2] == 5U) {
                cpos = func_001FAF60(0);
                dz = 0.39269908f - cpos[2];
                dx = 100.0f - cpos[0];
                dx = MIN_001CEE60(MAX_001CEE60(dx, -2.0f), 2.0f);
                dz = MIN_001CEE60(MAX_001CEE60(dz, -0.012271847f), 0.012271847f);
                func_001FB6A0(0, 0, 1, -0.024543693f, (f32)dz, dx);
            }
            if (fullA && (soloA || !fullB)) {
                rep |= func_00203A40(lifeA100, 0, 0xFFFF);
            }
            if (fullB && (soloB || !fullA)) {
                rep |= func_00203A40(lifeB100, 0, 0xFFFF);
            }
            keys = rep;
            if (!(keys & 0xF0)) {
                break;
            }
            DUEL[0xD57] = 0x5D;
            func_00217710(0, 4);
            return 0;
        case 0x5D:
            if (DUEL[0xCB2] == 2U || DUEL[0xCB2] == 4U || DUEL[0xCB2] == 5U) {
                cpos = func_001FAF60(0);
                dz = 0.39269908f - cpos[2];
                dx = 100.0f - cpos[0];
                dx = MIN_001CEE60(MAX_001CEE60(dx, -2.0f), 2.0f);
                dz = MIN_001CEE60(MAX_001CEE60(dz, -0.012271847f), 0.012271847f);
                func_001FB6A0(0, 0, 1, -0.024543693f, (f32)dz, dx);
            }
            DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 1, 0x80);
            DUEL[0xD3A] = MIN_001CEE60(DUEL[0xD3A] + 2, 0x80);
            if (DUEL_S16(0xC9C) < 0x80) {
                break;
            }
            if (DUEL[0xD3A] < 0x80) {
                break;
            }
            DUEL[0xCB2] = 0x18;
            func_00272CC0(DUEL[0xD50], DUEL[0xD51]);
            if ((fullA && fullB) || (!fullA && !fullB)) {
                func_001A8920();
                break;
            }
            if (DUEL[0xD37] < 0x16) {
                func_00228150(DUEL[0xD52] == DUEL[0xD50] ? 1 : 0);
            }
            DUEL[0xD57] = 0x5E;
        case 0x5E: {
            u16 *buf;
            *(u16 *)(duel + 0xC8A) = 0;
            *(u16 *)(duel + 0xC8C) = 0;
            buf = (u16 *)CAMPAIGN_WORK_ADDR;
            if (fullA && !fullB) {
                for (n = 0; n < 0x356; n++) {
                    tx = func_00215D30(0, n);
                    tz = func_00215DE0(0, n);
                    if (tz != tx && func_00200930(1, n) != NULL) {
                        if (tx < tz) {
                            v = n;
                        } else {
                            v = n | 0x4000;
                        }
                        buf[(*(u16 *)(duel + 0xC8C))++] = v;
                    }
                }
            }
            if (!fullA && fullB) {
                for (n = 0; n < 0x356; n++) {
                    tx = func_00215D30(1, n);
                    tz = func_00215DE0(1, n);
                    if (tz != tx && func_00200930(1, n) != NULL) {
                        if (tx < tz) {
                            v = n | 0x8000;
                        } else {
                            v = n | 0xC000;
                        }
                        buf[(*(u16 *)(duel + 0xC8C))++] = v;
                    }
                }
            }
            if (*(u16 *)(duel + 0xC8C) == 0) {
                DUEL[0xD57] = 0x62;
                break;
            }
            DUEL[0xCB2] = 9;
            DUEL_S16(0xC9A) = 0;
            DUEL_S16(0xC9C) = 0;
            DUEL[0xD57] = 0x5F;
            break;
        }
        case 0x5F:
            *(u16 *)(duel + 0xCAA) = ((u16 *)CAMPAIGN_WORK_ADDR)[*(u16 *)(duel + 0xC8A)];
            func_00217710(0, 4);
            DUEL[0xD57] = 0x60;
        case 0x60:
            DUEL_S16(0xC9C) = MIN_001CEE60(DUEL_S16(0xC9C) + 8, 0x40);
            if (DUEL_S16(0xC9C) < 0x40) {
                break;
            }
            DUEL[0xD57] = 0x61;
        case 0x61:
            keys = rep;
            if (keys & 0xF0) {
                if (++*(u16 *)(duel + 0xC8A) >= *(u16 *)(duel + 0xC8C)) {
                    DUEL[0xCB2] = 0x18;
                    func_00217710(0, 4);
                    DUEL[0xD57] = 0x62;
                } else {
                    DUEL[0xD57] = 0x5F;
                }
            }
            return 0;
        case 0x62:
            if (((fullA && DUEL[0xD50] == 0) || (fullB && DUEL[0xD50] == 1)) &&
                func_00251060(DUEL[0xD50] ^ 1, (void *)CAMPAIGN_WORK_ADDR) != 0) {
                func_001A87C0(0xF, -1);
            } else {
                func_001A8920();
            }
            break;
        }
        if (prev == DUEL[0xD57]) {
            break;
        }
        prev = DUEL[0xD57];
    }
    return 0;

}
