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

extern u8 D_00290020[];
extern u8 D_00290080[];
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

extern u8 D_00290080[];
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

static inline void set_color_001CB6B0(Color_001CB6B0 *a, Color_001CB6B0 *b,
                                      Source_001CB6B0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

static inline void set_xyz_001CB6B0(Vertex_001CB6B0 *v, s32 x, s32 y, u8 *state) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = *(s32 *)(state + 0xC58);
    v->fog = 0;
}

static inline void set_corner_001CB6B0(Vertex_001CB6B0 *v, s32 x, s32 y) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = D_003180E8;
    v->fog = 0;
}

s32 lSzDuel_DrawCustomDuel_Menu_SelectMapEdit_Pipe(s32 id, s32 player, s32 x, s32 y) {
    extern s32 *func_001FEAB0(s32);
    extern s32 func_001FE7D0(s32, s32, s32, s32, s32, void (*)(void));
    extern s32 func_001B6F70(s32, s32, s32, s32, s32, s32, s8 *, s32);
    extern s32 func_001B6EA0(s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B65F0(s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 func_001B3CC0(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern u8 D_00290080[];
    extern u8 D_002BE8C0[];
    extern char D_002BF074[];
    extern char D_002BEF93[];
    extern s32 D_002902C4;
    extern s32 D_00290256;
    extern s32 D_00290A58;
    extern s32 D_00290A62;
    extern s32 D_00290A6C;
    s32 ret;
    u8 *state = D_00317490.b;
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
            id = func_001B3CC0(id, D_00290080 + (board[i * 7 + j] + 0x10E) * 10, px + j * 16,
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
        id = func_001B3CC0(id, D_00290080 + (row + 0x10E) * 10, x + 0x89B, y + 0x745 + row * 16, 0, 1, 0,
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
        set_color_001CB6B0(&packet.points[0].color, &packet.points[1].color, &((Source_001CB6B0 *)D_002BE8C0)[row * 3]);
        set_color_001CB6B0(&packet.points[2].color, &packet.points[3].color, &((Source_001CB6B0 *)D_002BE8C0)[row * 3 + 1]);
        set_xyz_001CB6B0(&packet.points[0].xyz, px, py, state);
        set_xyz_001CB6B0(&packet.points[1].xyz, px + w, py, state);
        set_xyz_001CB6B0(&packet.points[2].xyz, px, py + h, state);
        set_xyz_001CB6B0(&packet.points[3].xyz, px + w, py + h, state);
        id = func_00207650(id, (s32)packet.tag, 0, 0);
        set_color_001CB6B0(&packet.points[0].color, &packet.points[1].color, &((Source_001CB6B0 *)D_002BE8C0)[row * 3 + 1]);
        set_color_001CB6B0(&packet.points[2].color, &packet.points[3].color, &((Source_001CB6B0 *)D_002BE8C0)[row * 3 + 2]);
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

void lSzDuel_DrawCustomDuel_Exit_Pipe(s32 arg0, s32 arg1, s32 arg2) {
    extern s32 lSzDuel_DrawDialog_Window_Pipe(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 SzDuel_DrawWindow_Font_Pipe(s32, s32, s32, s32, s32, s32, s8 *, s32);
    s32 text = (s32)D_002BEF98;
    s8 *text2 = D_002BEF6F;
    s8 *text3 = D_002BEF73;
    s32 id;

    arg0 = lSzDuel_DrawDialog_Window_Pipe(arg0, 2, -1, 0x91, arg1 + 0x140, arg2 + 0x94, 0x140, 0x98,
                         func_0019BEF0((char *)text), text, 0);
    id = SzDuel_DrawWindow_Font_Pipe(arg0, arg1 + 0xF0, arg2 + 0x108, 2, 3, func_0019BEF0((char *)text2), text2,
                       *(u8 *)0xA9C08E != 0 ? 0 : (s32)D_002BE944);
    SzDuel_DrawWindow_Font_Pipe(id, arg1 + 0x190, arg2 + 0x108, 2, 3, func_0019BEF0((char *)text3), text3,
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

void SzDuel_InitMapEdit(s32 arg0) {
    u8 *state = D_00317490.b;
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
    if (arg0 != 0) {
        *(u8 *)0xA9C08D = 5;
        *(u8 *)0xA9C08C = *(u8 *)0xA9C08D - 2;
    }
    state[0xD63] = 0;
}

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

void SzDuel_ActMapEdit(void) {
    extern void *SzData_GetData(s32);
    extern s32 SzDuel_SetField();
    State_001CC620 *state = (State_001CC620 *)D_00317490.b;
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
        p = (State_001CC620 *)D_00317490.b;
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
        p2 = (State_001CC620 *)D_00317490.b;
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

s32 SzDuel_DrawMapEdit_Pipe(s32 arg0) {
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
    arg0 = lSzDuel_DrawWindow_FieldPiece_Pipe(arg0, 0, SzDuel_GetField(cursor->x, cursor->y), 6, 0x150, 100.0f);
    id = SzDuel_StartWindowSessionWithPalette_Pipe(arg0, 0);
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

static inline void set_color_001CCEA0(Color_001CCEA0 *a, Color_001CCEA0 *b,
                                      Source_001CCEA0 *src) {
    a->r = b->r = src->r;
    a->g = b->g = src->g;
    a->b = b->b = src->b;
    a->a = b->a = src->a;
    a->q = b->q = 1.0f;
}

static inline void set_xyz_001CCEA0(Vertex_001CCEA0 *v, s32 x, s32 y, u8 *state) {
    v->x = x << 4;
    v->y = y << 4;
    v->z = *(s32 *)(state + 0xC58);
    v->fog = 0;
}

s32 lSzDuel_DrawMapEdit_Graph_Pipe(s32 arg0, s32 x, s32 y) {
    extern s32 lSzDuel_DrawWindow_ExIcon_Pipe(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
    extern s32 SzDuel_DrawWindow_FontDigit_Pipe(s32, s32, s32, s32, s32, s32, s32);
    extern u8 D_00290080[];
    extern u8 D_002BE8C0[];
    u8 *state = D_00317490.b;
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
    id = lSzDuel_DrawWindow_Frame_Pipe(arg0, 0, -1, 0xB, x, y, -0x6E, -0xAA, 1);
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
        id = lSzDuel_DrawWindow_ExIcon_Pipe(id, D_00290080 + (row + 0x10E) * 10, px, y + 0x725 + row * 16, 0, 1, 0,
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
        set_color_001CCEA0(&packet.points[0].color, &packet.points[1].color, &((Source_001CCEA0 *)D_002BE8C0)[row * 3]);
        set_color_001CCEA0(&packet.points[2].color, &packet.points[3].color, &((Source_001CCEA0 *)D_002BE8C0)[row * 3 + 1]);
        set_xyz_001CCEA0(&packet.points[0].xyz, px, py, state);
        set_xyz_001CCEA0(&packet.points[1].xyz, px + w, py, state);
        set_xyz_001CCEA0(&packet.points[2].xyz, px, py + h, state);
        set_xyz_001CCEA0(&packet.points[3].xyz, px + w, py + h, state);
        id = ExSortPrim_Pipe(id, (s32)packet.tag, 0, 0);
        set_color_001CCEA0(&packet.points[0].color, &packet.points[1].color, &((Source_001CCEA0 *)D_002BE8C0)[row * 3 + 1]);
        set_color_001CCEA0(&packet.points[2].color, &packet.points[3].color, &((Source_001CCEA0 *)D_002BE8C0)[row * 3 + 2]);
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

s32 SzDuel_ClearDrawCard(void *arg0) {
    Draw_001CD560 *p;

    if (arg0 == NULL) {
        return 0;
    }
    p = arg0;
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


s32 SzDuel_DrawAllCard_Pipe(s32 arg0) {
    extern s32 SzDuel_DrawHandCard_Pipe(s32);
    Vec4_001CD710 position;
    Command_001CD710 command;
    u8 *base = D_00317490.b;
    u8 *selected = D_00317490.b + D_003181E4 * 0x350;
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
    original = arg0;
    switch (mode) {
    case 1:
    case 0:
        if (SzModel_GetDrawFlag(0) == 0) {
            return original;
        }
        arg0 = ExSetAnchor_Pipe(arg0);
        arg0 = SzDuel_StartCardSession_Pipe(arg0);
        arg0 = SzDuel_DrawCardRequest_Pipe(arg0);
        arg0 = RhBase_SetZBufferMode(arg0, 1);
        SzDuel_GetUnitPos(0, 0, &position.x);
        position.y = 0.0f;
        arg0 = SzDuel_DrawLeaderBase_Pipe(arg0, 0, &position.x, 0x80, 1);
        SzDuel_GetUnitPos(1, 0, &position.x);
        position.y = 0.0f;
        value = RhBase_SetZBufferMode(SzDuel_DrawLeaderBase_Pipe(arg0, 1, &position.x, 0x80, 1), 0);
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

void SzDuel_InitCardRequest(void) {
    u8 *entry;
    s32 i;

    entry = D_003193C0;
    i = 0;
    do {
        SzDuel_FreeCardRequest(entry);
        i += 1;
        entry += 0xA0;
    } while (i < 0x20);
}

s32 SzDuel_FreeCardRequest(void *arg0) {
    extern void SzDuel_ClearDrawCard();

    if (arg0 == NULL) {
        return 0;
    }
    SzDuel_ClearDrawCard();
    *(s32 *)((u8 *)arg0 + 0x90) = 0;
    return 1;
}


typedef struct {
    u8 pad_00[0x90];
    s32 in_use;
    u8 pad_94[0xC];
} Slot_001CDAA0;

u8 *SzDuel_GetCardRequest(void) {
    s32 i;
    Slot_001CDAA0 *slot;

    slot = (Slot_001CDAA0 *)D_003193C0;
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

s32 SzDuel_DrawCardRequest_Pipe(s32 arg0) {
    Draw_001CDB00 draw;
    PackedColor_001CDB00 color;
    Entry_001CDB00 *entry;
    s32 i;
    void *position;
    s32 height;

    entry = (Entry_001CDB00 *)D_003193C0;
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
                arg0 = SzDuel_SetupCard2_Pipe(arg0, (s32)(SzDuel_GetCardNode(&draw, 1) ? unit : NULL), &draw);
                arg0 = RhBase_SetZBufferMode(arg0, 1);
                arg0 = SzDuel_DrawCard_Pipe(arg0, (s32)&draw);
                arg0 = RhBase_SetZBufferMode(arg0, 0);
            }
        }
        i++;
        entry++;
    } while (i < 32);
    return arg0;
}

#include "common.h"

void SzDuel_InitCardControl(void) {
    u8 *p;
    s32 i;

    p = D_0031A7C0;
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

s32 SzDuel_ClearCardControl(u8 *arg0) {
    State_001CDD90 *state = (State_001CDD90 *)arg0;
    Flags_001CDD90 *flags;

    if (arg0 == NULL) {
        return 0;
    }
    state->value = 0;
    state->field98 = 0;
    state->field9A = 0;
    state->field9C = 0xFF;
    flags = (Flags_001CDD90 *)(arg0 + 0x9F);
    flags->bit2 = 0;
    flags->bit3 = 0;
    flags->bit4 = 0;
    flags->bit5 = 0;
    flags->bit6 = 0;
    flags->bit7 = 0;
    return 1;
}

void *SzDuel_GetCardControl(s32 arg0) {
    if (arg0 < 0 || arg0 >= 6) {
        return NULL;
    }

    return &D_0031A7C0[arg0 * 0xA0];
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

s32 SzDuel_DoCardControl0(void *arg0) {
    extern s32 func_001A22C0(f32);
    Output_001CDEB0 *output;
    f32 blend;
    f32 inverse;
    Blend_001CDEB0 *src = arg0;

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

s32 SzDuel_DrawUnit_Pipe(s32 arg0) {
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

    game = D_00317490.b;
    player = D_00317490.b + D_003181E4 * 0x350;
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
                    arg0 = SzModel_ExSort_Pipe(arg0, model, (s32)pos, (s32)&render, 0, 0, 0x80FFFFF6);
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
            arg0 = SzModel_ExSort_Pipe(arg0, extraModel, NULL, NULL, 0, 0, 0x80FFFFF6);
        }
        extra++;
    } while (extra < 2);
    return arg0;
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

extern s32 (*D_002BAEB0[])(u16, void *);
extern s8 D_0034F700;
extern s8 D_0034F708;

s32 lSzDuel_GetControl(s32 arg0, s32 arg1) {
    u8 *base = D_00317490.b;
    s32 ret = 0;
    Record_001CECF0 *record = (Record_001CECF0 *)(D_00317490.b + arg0 * 0x350);
    void *selected;
    s32 result;

    switch (record->kind) {
    case 0x64:
        ret = SzPad_Check(0, arg1, 0xFFFF) & 0xFFFF;
        break;
    case 0x65:
        ret = SzPad_Check(1, arg1, 0xFFFF) & 0xFFFF;
        break;
    default:
        if (record->kind < 0x64) {
            selected = record;
            if (TaTuto_IsTuto(arg0) != 0) {
                selected = base;
            }
            if (SzView_InqRequest(-1, -1) == NULL) {
                result = D_002BAEB0[record->kind]((u16)((record->high << 8) | record->low), selected);
                if (result < 0) {
                    if (D_0034F700 != 0) {
                        if (result == -1) {
                            Taku_Camp_Go_Rensyu_Duel(1);
                        } else {
                            D_0034F700 = 0;
                            D_0034F708 = 1;
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

INCLUDE_ASM("asm/nonmatchings/main_042", SzDuel_Act);
