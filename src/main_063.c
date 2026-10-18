#include "common.h"
#include "campaign.h"

typedef struct {
    __int128 value;
} Scale_002232F0;

extern Scale_002232F0 D_0029A7D0;

typedef struct {
    s32 x, y, w, h;
} Rect_002232F0;

typedef struct {
    s32 pad;
    Rect_002232F0 rect;
} Texture_002232F0;

typedef struct {
    u8 r, g, b, a;
} Color_002232F0;

/* Draws a number in the campaign windows' digits. (original: Taku_Camp_Kazu_Disp) */
s32 Taku_Camp_Number_Disp(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 SzMsg_GetInfo();
    extern s32 SzMsg_DrawRect_Pipe();
    Rect_002232F0 rect;
    Scale_002232F0 scale;
    Color_002232F0 color;
    s16 i;
    s16 column;
    s16 row;
    s16 x;
    s32 digit;
    Texture_002232F0 *texture;

    scale = D_0029A7D0;
    color.r = color.g = color.b = 0xFF;
    color.a = 0x80;
    i = 0;
    x = 0xA0;
    for (; i < 4; i++) {
        digit = 0;
        switch (i) {
        case 0:
            digit = arg1 % 10;
            break;
        case 1:
            digit = 10;
            break;
        case 2:
            digit = (arg2 / 10) % 10;
            break;
        case 3:
            digit = arg2 % 10;
            break;
        }
        if (digit == 0) {
            column = 4;
            row = 1;
        } else if (digit < 6) {
            column = digit - 1;
            row = 0;
        } else if (digit < 10) {
            column = digit - 6;
            row = 1;
        } else {
            column = 2;
            row = 4;
        }
        arg0 = SzMsg_LoadFont_Pipe(arg0, 1, 7, 0, 0x16);
        arg0 = RhText_SetTextureFlush(arg0);
        texture = (Texture_002232F0 *)SzMsg_GetInfo(1);
        rect = texture->rect;
        color.r = color.g = color.b = 0xFF;
        color.a = 0x80;
        texture->rect.x = rect.x + column * 0x16;
        texture->rect.y = rect.y + row * 0x16;
        texture->rect.w = 0x16;
        texture->rect.h = 0x16;
        arg0 = SzMsg_DrawRect_Pipe(arg0, 1, x + arg3, 0x110, &scale, &color);
        SzMsg_Free(1);
        x += 0x10;
    }
    return arg0;
}

typedef struct {
    s16 x, y;
    u8 pad04[12];
    u8 r, g, b, a;
    u8 pad14[3], alpha1;
    u8 pad18[3], alpha2;
    u8 pad1C[3], alpha3;
    u8 pad20[6];
} Sprite_00223600;
typedef struct { s32 value[4]; } UV_00223600;
typedef struct { s16 rgb[10][3]; } Palette_00223600;
typedef struct { Sprite_00223600 item[6]; } SixSprites_00223600;
typedef struct { Sprite_00223600 item[3]; } ThreeSprites_00223600;
typedef struct { s16 u, v, w, h, page; } Image_00223600;
typedef struct { s32 x, y, w, h; } Rect_00223600;
typedef struct { s32 flags; Rect_00223600 rect; } Texture_00223600;


extern UV_00223600 D_0029A7E0;
extern Palette_00223600 D_0029A7F0;
extern Image_00223600 D_0029A830;
extern SixSprites_00223600 D_0029A840;
extern Sprite_00223600 D_0029A930;
extern ThreeSprites_00223600 D_0029A960;
extern Sprite_00223600 D_0029A9E0;
extern s16 D_002999A0[][3];
extern s8 D_0030F0B0[];

#pragma conditional_move off
#pragma opt_dead_assignments off

/* Draws the campaign event window's title: the place's name, the opponent's name and portrait. (original: Taku_Camp_Ivent_Name) */
s32 Taku_Camp_Event_Name(s32 packet) {
    extern s32 SzDuel_DrawWindow_Font_Pipe();
    extern s32 Taku_Obj_Set(s32, void *, s16, s16);
    extern s32 Taku_G4_Set(s32, void *, s16, s16);
    extern s32 SzMsg_DrawRect_Pipe();
    extern s32 SzMsg_GetInfo();
    extern s32 Taku_Text_Set(s32, s32, s32, s16, s16, f32, f32, s32, void *);
    s16 fromX;
    s32 font;
    s16 row;
    s16 textRow;
    s16 section;
    s16 page;
    s16 left;
    s16 right;
    s16 textOffset;
    s16 paletteRow;
    s16 nextPaletteRow;
    s16 cellBase;
    s16 sectionX;
    s16 (*entry)[3];
    s16 colourIndex;
    s32 slide;
    s16 fromY;
    CampaignWork *state;
    s16 shift;
    s16 scroll;
    s16 rowY;
    s32 selX;
    s32 selY;
    Texture_00223600 *texture;
    s16 charX;
    s32 texX;
    s32 texY;
    s16 col;
    s16 i;
    s16 k;
    s16 texCol;
    s16 texRow;
    Texture_00223600 *selTex;
    Sprite_00223600 *sprite;
    s32 labelX;
    s16 labelLeft;
    s16 labelRight;
    s16 count;
    s16 x;
    s16 y;
    s16 dx;
    s16 band;
    s16 offset;
    s16 cellX;
    s16 toX;
    s16 group;
    s8 cell;
    s16 n;
    s16 lcol;
    s16 lrow;
    s16 lx;
    s16 ly;
    s32 ltx;
    s32 lty;
    s32 px;
    s32 sy;
    s16 py;
    s16 tx;
    s32 ty;
    Rect_00223600 baseRect;
    UV_00223600 uv;
    Palette_00223600 palette;
    SixSprites_00223600 decorations;
    Sprite_00223600 tile;
    ThreeSprites_00223600 labels;
    Sprite_00223600 cursor;
    Rect_00223600 listRect;
    Rect_00223600 selectedRect;
    Image_00223600 image;
    u8 rgba[4];

    state = &campaignWork;
    font = 0;
    uv = D_0029A7E0;
    palette = D_0029A7F0;
    image = D_0029A830;
    decorations = D_0029A840;
    tile = D_0029A930;
    labels = D_0029A960;
    cursor = D_0029A9E0;
    rgba[2] = 255; rgba[1] = 255; rgba[0] = 255; rgba[3] = 128;
    image.page = 2;
    image.w = 0x300;
    image.h = (state->eventWindowOpen * 404) / 100 + 16;
    if (state->eventWindowState == 1) {
        state->eventWindowOpen += 6;
        if (state->eventWindowOpen >= 100) {
            state->eventWindowOpen = 100;
            state->eventWindowState = 2;
        }
    }
    if (state->eventWindowState == 3) {
        state->eventWindowOpen -= 6;
        if (state->eventWindowOpen < 0) {
            state->eventWindowOpen = 0;
            state->eventWindowState = 4;
        }
    }
    packet = Taku_Window_Set(packet, &image, 2, 0, 0xFFC0, 16, 0, 128, 64);
    if (0 < state->eventWindowState) {
        slide = (state->eventWindowOpen * 640) / 100;
        left = 640 - slide;
        image.page = 2;
        image.w = 236;
        image.h = 32;
        right = slide - 640;
        x = left + 28;
        packet = Taku_Window_Set(packet, &image, 5, 0, x, 28, 0, 128, 128);
        x += 43;
        packet = SzDuel_DrawWindow_Font_Pipe(packet, x, 35, 2, 1, 10, D_0030F0B0, 0);
        image.page = 0;
        x = right + 176;
        image.w = 288;
        image.h = 40;
        packet = Taku_Window_Set(packet, &image, 2, 0, x, 88, 0, 128, 64);
        labelX = (s16)x + 96;
        sprite = labels.item;
        i = 0;
        labelLeft = x - 12;
        labelRight = 288 + x;
        for (; i < 3; i++) {
            x = labelX;
            y = 74;
            switch (i) {
            case 0:
                break;
            case 1:
                x = labelLeft;
                y = 92;
                break;
            case 2:
                x = labelRight;
                y = 92;
                break;
            }
            packet = (s32)Taku_FT4_Set((void *)packet, sprite, x, y, 0);
            sprite++;
        }
        x = right + (state->nameLength * 22 + 185);
        if (0 <= state->nameBlink) {
            y = (s8)state->nameBlink;
        } else {
            y = -(s8)state->nameBlink;
        }
        cursor.alpha3 = y;
        cursor.alpha2 = y;
        cursor.alpha1 = y;
        cursor.a = y;
        state->nameBlink += 16;
        if (state->nameLength < 12) {
            packet = Taku_G4_Set(packet, &cursor, x, 94);
        }
        x = 48 + left;
        image.page = 9;
        image.w = 540;
        image.h = 34;
        packet = Taku_Window_Set(packet, &image, 3, 0, x, 383, 0, 128, 64);
        sprite = decorations.item;
        for (i = 0; i < 6; i++) {
            x = left + 0;
            if (i != 3 && i != 4) {
                packet = Taku_Obj_Set(packet, sprite, x, 0);
            }
            sprite++;
        }
        dx = left;
        entry = D_002999A0;
        for (i = 0; i < 3; i++) {
            font = (*entry)[2];
            packet = Taku_Text_Set(packet, 1, font, (s16)dx + (*entry)[0], (*entry)[1], 1.0f, 1.0f, 0, rgba);
            entry++;
        }
        if (state->nameTableTurn != 0) {
            count = 3;
            scroll = (state->nameTableSlide * 640) / 100;
        } else {
            count = 1;
            scroll = 0;
        }
        for (page = 0; page < count; page++) {
            shift = 0;
            switch (page) {
            case 1:
                shift = -640;
                break;
            case 2:
                shift = 640;
                break;
            }
            for (section = 0, sectionX = 0; section < 3; section++) {
                band = 0;
                switch (state->nameTable) {
                case 0:
                    switch (page) {
                    case 0:
                        break;
                    case 1:
                        band = 6;
                        break;
                    case 2:
                        band = 3;
                        break;
                    }
                    break;
                case 1:
                    switch (page) {
                    case 0:
                        band = 3;
                        break;
                    case 1:
                        break;
                    case 2:
                        band = 6;
                        break;
                    }
                    break;
                case 2:
                    switch (page) {
                    case 0:
                        band = 6;
                        break;
                    case 1:
                        band = 3;
                        break;
                    case 2:
                        band = 0;
                        break;
                    }
                    break;
                }
                paletteRow = section + band;
                nextPaletteRow = section + 1 + band;
                cellBase = sectionX + 0;
                for (row = 0, rowY = 0; row < 6; row++) {
                    if (row % 2 == 0) {
                        colourIndex = paletteRow;
                    } else {
                        colourIndex = nextPaletteRow;
                    }
                    if (row % 2 == 0) {
                        offset = right;
                    } else {
                        offset = left;
                    }
                    cellX = cellBase;
                    for (col = 0; col < 5; col++) {
                        tx = offset + (shift + cellX);
                        ty = rowY;
                        tile.r = (palette.rgb[(s16)colourIndex][0] >> 1) * 3;
                        tile.g = (palette.rgb[(s16)colourIndex][1] >> 1) * 3;
                        tile.b = (palette.rgb[(s16)colourIndex][2] >> 1) * 3;
                        packet = Taku_Obj_Set(packet, &tile, (s16)(tx + scroll), ty);
                        cellX = cellX + 32;
                    }
                    rowY += 36;
                }
                sectionX += 160;
            }
            for (textRow = 0; textRow < 3; textRow++) {
                switch (state->nameTable) {
                case 0:
                    switch (page) {
                    case 0:
                        font = textRow + 11;
                        break;
                    case 1:
                        font = textRow + 5;
                        break;
                    case 2:
                        font = textRow + 14;
                        break;
                    }
                    break;
                case 1:
                    switch (page) {
                    case 0:
                        font = textRow + 14;
                        break;
                    case 1:
                        font = textRow + 11;
                        break;
                    case 2:
                        font = textRow + 5;
                        break;
                    }
                    break;
                case 2:
                    switch (page) {
                    case 0:
                        font = textRow + 5;
                        break;
                    case 1:
                        font = textRow + 14;
                        break;
                    case 2:
                        font = textRow + 11;
                        break;
                    }
                    break;
                }
                packet = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, font, 0, 22));
                texture = (Texture_00223600 *)SzMsg_GetInfo(1);
                baseRect = texture->rect;
                texY = baseRect.y;
                for (row = 0; row < 6; row++) {
                    if (row % 2 == 0) {
                        textOffset = right;
                    } else {
                        textOffset = left;
                    }
                    texX = baseRect.x;
                    for (col = 0, charX = 0; col < 5; col++) {
                        tx = textOffset + (tile.x + 5 + charX + textRow * 160);
                        py = tile.y + 5 + row * 36;
                        rgba[2] = 0; rgba[1] = 0; rgba[0] = 0; rgba[3] = 128;
                        texture->rect.x = texX;
                        texture->rect.y = texY;
                        texture->rect.w = 22;
                        texture->rect.h = 22;
                        packet = SzMsg_DrawRect_Pipe(packet, 1, scroll + (tx + shift), py, &uv, rgba);
                        tx = textOffset + (tile.x + 3 + charX + textRow * 160);
                        py = tile.y + 3 + row * 36;
                        rgba[2] = 255; rgba[1] = 255; rgba[0] = 255; rgba[3] = 128;
                        texture->rect.x = texX;
                        texture->rect.y = texY;
                        texture->rect.w = 22;
                        texture->rect.h = 22;
                        packet = SzMsg_DrawRect_Pipe(packet, 1, scroll + (tx + shift), py, &uv, rgba);
                        charX = charX + 32;
                        texX += 22;
                    }
                    texY += 22;
                }
                SzMsg_Free(1);
            }
        }
        if (state->nameTyping == 1) {
            for (k = 0; k < 3; k++) {
                texCol = state->namePickedColumn % 5;
                texRow = state->namePickedRow;
                if (state->namePickedColumn / 5 == k) {
                    switch (state->nameTable) {
                    case 0:
                        font = k + 11;
                        break;
                    case 1:
                        font = k + 14;
                        break;
                    case 2:
                        font = k + 5;
                        break;
                    }
                    packet = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, font, 0, 22));
                    selTex = (Texture_00223600 *)SzMsg_GetInfo(1);
                    selectedRect = selTex->rect;
                    rgba[2] = 0; rgba[1] = 0; rgba[0] = 0; rgba[3] = 128;
                    toX = state->nameLength * 22 + 190;
                    fromX = tile.x + 5 + state->namePickedColumn * 32;
                    fromY = tile.y + 5 + state->namePickedRow * 36;
                    px = fromX + (s16)((state->nameTypingT * (toX - fromX)) / 100);
                    sy = fromY + (s16)((state->nameTypingT * (96 - fromY)) / 100);
                    selX = selectedRect.x + (s16)texCol * 22;
                    selTex->rect.x = selX;
                    selY = selectedRect.y + (s16)texRow * 22;
                    selTex->rect.y = selY;
                    selTex->rect.w = 22;
                    selTex->rect.h = 22;
                    packet = SzMsg_DrawRect_Pipe(packet, 1, px, sy, &uv, rgba);
                    rgba[2] = 255; rgba[1] = 255; rgba[0] = 255; rgba[3] = 128;
                    fromX = tile.x + 3 + state->namePickedColumn * 32;
                    fromY = tile.y + 3 + state->namePickedRow * 36;
                    px = fromX + (s16)((state->nameTypingT * ((s16)(state->nameLength * 22 + 188) - fromX)) / 100);
                    sy = fromY + (s16)((state->nameTypingT * (94 - fromY)) / 100);
                    selTex->rect.x = selX;
                    selTex->rect.y = selY;
                    selTex->rect.w = 22;
                    selTex->rect.h = 22;
                    packet = SzMsg_DrawRect_Pipe(packet, 1, px, sy, &uv, rgba);
                    SzMsg_Free(1);
                }
            }
        }
        image.page = 10;
        image.w = 36;
        image.h = 36;
        x = (s16)(left + (tile.x - 4 + state->nameColumn * 32));
        y = (s16)(tile.y - 4 + state->nameRow * 36);
        packet = Taku_Window_Set(packet, &image, 3, 0, x, y, 0, 128, 0);
        n = 0;
        lx = 190;
        ly = 188;
        for (; n < 12; n++) {
            /* 41 copies of header prototypes: the compiler-state lever (PLAYBOOK, Taku_Camp_Event_Name section)
               that keeps Taku_Camp_Event_Window, later in this file, matching; code-neutral here. */
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            void SzMsg_Free(s32 arg0);
            s32 SzMsg_LoadFont_Pipe(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
            void *Taku_FT4_Set(void *packet, void *src, s16 x, s16 y, u16 flip);
            s32 Taku_Window_Set(s32 p, void *rect_arg, u16 style, u16 mode, u16 dx, u16 dy, u16 depth, s32 unused, s16 alpha);
            s32 RhText_SetTextureFlush(s32 arg0);
            cell = state->nameLetterColumn[n];
            lcol = cell % 5;
            lrow = state->nameLetterRow[n];
            group = cell / 5;
            switch (state->nameLetterTable[n]) {
            case 0:
                font = (s16)group + 11;
                break;
            case 1:
                font = (s16)group + 14;
                break;
            case 2:
                font = (s16)group + 5;
                break;
            }
            packet = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(packet, 1, font, 0, 22));
            texture = (Texture_00223600 *)SzMsg_GetInfo(1);
            listRect = texture->rect;
            tx = right + lx;
            rgba[2] = 0; rgba[1] = 0; rgba[0] = 0; rgba[3] = 128;
            ltx = listRect.x + (s16)lcol * 22;
            texture->rect.x = ltx;
            lty = listRect.y + (s16)lrow * 22;
            texture->rect.y = lty;
            texture->rect.w = 22;
            texture->rect.h = 22;
            packet = SzMsg_DrawRect_Pipe(packet, 1, tx, 99, &uv, rgba);
            rgba[2] = 255; rgba[1] = 255; rgba[0] = 255; rgba[3] = 128;
            tx = right + ly;
            texture->rect.x = ltx;
            texture->rect.y = lty;
            texture->rect.w = 22;
            texture->rect.h = 22;
            packet = SzMsg_DrawRect_Pipe(packet, 1, tx, 97, &uv, rgba);
            SzMsg_Free(1);
            lx = lx + 22;
            ly = ly + 22;
        }
    }
    return packet;
}
#pragma conditional_move reset
#pragma opt_dead_assignments reset

typedef struct Tables_00224A40 {
    s32 pad[8];
    s32 normal[3];
    s32 type0[3];
    s32 type1[3];
} Tables_00224A40;


/* Picks the texts of the campaign event window for the current place and opponent. (original: Taku_Camp_Ivent_Name_Set) */
void Taku_Camp_Event_Name_Set(void) {
    extern u16 campaignDeckChoiceSets[];
    extern u16 campaignDeckChoices[][6];
    extern Tables_00224A40 D_002D19D0;
    extern s32 D_002D19D8;
    extern u16 D_002D49D4[];
    CampaignWork *state;
    s16 i;
    s16 group;
    s16 slot;
    u16 *dest;
    s32 offset;
    u8 *out;
    u8 *sum_ptr;
    s32 sum;
    s16 sum_index;
    u16 code_index;
    s32 shift;
    u8 *code_ptr;

    state = &campaignWork;
    sum_ptr = (u8 *)&campaignState;
    i = 0;
    offset = 0;
    out = sum_ptr;
    while (i < 12) {
        group = state->nameLetterColumn[i] / 5;
        slot = (s16)(state->nameLetterColumn[i] % 5) + state->nameLetterRow[i] * 6;
        if (i == 0) {
            dest = (u16 *)((u8 *)&D_002D49D4[D_002D19D8] + offset);
            switch (state->nameLetterTable[i]) {
            case 0:
                *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.type0[group] * 2 + slot * 2) & 0x1FFF;
                break;
            case 1:
                *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.type1[group] * 2 + slot * 2) & 0x1FFF;
                break;
            default:
                *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.normal[group] * 2 + slot * 2) & 0x3FFF;
                break;
            }
        }
        dest = (u16 *)((u8 *)&D_002D49D4[D_002D19D8] + offset + 4);
        switch (state->nameLetterTable[i]) {
        case 0:
            *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.type0[group] * 2 + slot * 2) & 0x1FFF;
            break;
        case 1:
            *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.type1[group] * 2 + slot * 2) & 0x1FFF;
            break;
        default:
            *dest = *(u16 *)((u8 *)D_002D49D4 + D_002D19D0.normal[group] * 2 + slot * 2) & 0x3FFF;
            break;
        }
        if (i == 12 || i == state->nameCursor) {
            *dest |= 0x8000;
        }
        i++;
        offset += 2;
        *(s16 *)(out + 0x24) = *(s16 *)dest;
        out += 2;
    }
    sum_index = 0;
    sum = 0;
    while (sum_index < 12) {
        sum += (s32)*(u16 *)(sum_ptr + 0x24) % 16;
        sum_index++;
        sum_ptr += 2;
    }
    state->startingDeckSet = sum & 0xF;
    code_index = 0;
    shift = 0;
    code_ptr = (u8 *)state;
    while (code_index < 3) {
        *(u16 *)(code_ptr + 0x53F8) = ((s32)campaignDeckChoiceSets[state->startingDeckSet] >> shift) & 0x1F;
        shift += 5;
        *(u16 *)(code_ptr + 0x53FE) = campaignDeckChoices[*(u16 *)(code_ptr + 0x53F8)][0] & 0x3FF;
        code_index++;
        code_ptr += 2;
    }
}

typedef struct {
    s16 x0, y0, x1, y1;
    s16 kind;
} Frame_00224E40;

typedef struct {
    s16 x0, y0, x1, y1, x2, y2, x3, y3;
    u8 data[0x14];
    u16 index;
} Sprite_00224E40;

typedef struct {
    Sprite_00224E40 s[2];
} Pair_00224E40;

typedef struct {
    u8 r, g, b, a;
} Color_00224E40;

typedef struct {
    s16 u, v, width, height;
    u8 pad08[8];
    u16 texture;
    u8 pad12[2];
} Tex_00224E40;

typedef struct {
    u16 value;
    u16 number;
    u16 digits;
    u16 pad06;
    u32 types;
} Code_00224E40;


extern s16 D_00299ED2;
extern Frame_00224E40 D_0029AA08;
extern Sprite_00224E40 D_0029AA20;
extern Pair_00224E40 D_0029AA50;
extern Sprite_00224E40 D_0029AAA0;
extern Pair_00224E40 D_0029AAD0;
extern Sprite_00224E40 D_0029AB20;
extern Sprite_00224E40 D_0029AB50;
extern Sprite_00224E40 roseSprites[]; /* original: tex_bara_data */
extern Tex_00224E40 campaignSprites[]; /* original: tex_uv_data */
extern Code_00224E40 campaignDeckChoices[]; /* original: DeckDat */
extern char D_0030F0BB[];
extern char D_0030F0C7[];
extern char D_0030F0D4[];
extern char D_0030F0E8[];

#pragma opt_dead_assignments off

/* Draws the campaign event window: the event's text, the opponent, the rewards and the duel choice. (original: Taku_Camp_Ivent_Window) */
s32 Taku_Camp_Event_Window(s32 arg0) {
    s16 ny;
    extern s32 Taku_Camp_Event_Name();
    extern s32 Taku_Window_Set(s32, void *, s32, s32, u16, u16, s32, s32, s32);
    extern s32 Taku_Obj_Set(s32, void *, s16, s16);
    extern s32 Taku_Text_Set(s32, s32, s32, s16, s16, f32, f32, s32, void *);
    extern s32 SzMsg_LoadFont_Pipe(s32, s32, s32, s32, s32);
    extern s32 Taku_FT4_Set(s32, void *, s16, s16, u16);
    extern s32 SzMsg_DrawRatioX_Pipe(s32, s32, s32, s32, f32, f32, void *, void (*)(void));
    s16 flag2;
    s8 *ctx;
    s16 i;
    CampaignWork *state;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 nx;
    s32 right;
    s32 left;
    s32 t;
    s32 xx;
    s16 j;
    s16 n;
    s16 m;
    s16 k2;
    Sprite_00224E40 *tmpl;
    s16 k3;
    s16 i2;
    s32 xx3;
    s32 pos;
    s8 v;
    s16 cur;
    s16 flag;
    s16 flip;
    s16 k1;
    s16 k;
    s32 id;
    s32 q;
    s32 width;
    s8 sel;
    s8 mode;
    Code_00224E40 *code;
    f32 sx;
    f32 sy;

    u16 digits[3][4];
    u16 types[3][4];
    Sprite_00224E40 s100;
    Pair_00224E40 pair130;
    Sprite_00224E40 s180;
    Pair_00224E40 pair1B0;
    Sprite_00224E40 s200;
    Sprite_00224E40 s230;
    u16 hundreds[3];
    u16 ones[3];
    Frame_00224E40 frame;
    Color_00224E40 color;

    ctx = (s8 *)&campaignState;
    state = &campaignWork;
    frame = D_0029AA08;
    s100 = D_0029AA20;
    pair130 = D_0029AA50;
    s180 = D_0029AAA0;
    pair1B0 = D_0029AAD0;
    s200 = D_0029AB20;
    color.r = color.g = color.b = 0x80;
    color.a = 0x80;
    if (D_00299ED2 == 0x2738 && campaignWork.eventWindowState != 0) {
        arg0 = Taku_Camp_Event_Name(arg0);
    } else if (campaignWork.eventWindowState != 0) {
        switch (*(s16 *)(0xC2 + ctx)) {
        case 0x2738:
            x = 0x1B;
            y = 0x28;
            w = 0x24A;
            h = 0x180;
            break;
        case 0x276A:
        case 0x2742:
            x = 0x5B;
            y = 0x93;
            w = 0x1CA;
            h = 0x9A;
            break;
        case 0x2756:
            x = 0x1B;
            y = 0xAB;
            w = 0x24A;
            h = 0x8A;
            break;
        }
        frame.kind = 2;
        frame.x1 = ((w - 0x10) * campaignWork.eventWindowOpen) / 100 + 0x10;
        frame.y1 = ((h - 0x10) * campaignWork.eventWindowOpen) / 100 + 0x10;
        arg0 = Taku_Window_Set(arg0, &frame, 2, 0, x, y, 0, 0x80, 0x40);
        if (campaignWork.eventWindowState != 0) {
            t = (campaignWork.eventWindowOpen * 0x280) / 100;
            nx = x + w - 0x8B;
            right = 0x280 - t;
            ny = y + h - 0x2A;
            frame.kind = 9;
            frame.x1 = 0x82;
            frame.y1 = 0x22;
            left = t - 0x280;
            arg0 = Taku_Window_Set(arg0, &frame, 3, 0, nx + right, ny, 0, 0x80, 0x40);
            arg0 = Taku_Obj_Set(arg0, &pair1B0, nx + 0x1B + right, ny + 9);
            arg0 = Taku_Text_Set(arg0, 1, 0xA7, nx + 0x3C + right, 6 + ny, 1.0f, 1.0f, 0, &color);
            switch (*(s16 *)(0xC2 + ctx)) {
            case 0x2738:
            case 0x276A:
                if (campaignWork.eventWindowState == 2) {
                    tmpl = roseSprites;
                    for (i = 0; i < 2; i++) {
                        s100 = *tmpl;
                        if (i == 0) {
                            s100.x0 = 0x90;
                            s100.y0 = 0xE0;
                        } else {
                            s100.x0 = 0x90;
                            s100.y0 = 0xB0;
                        }
                        s100.x1 = s100.x0 + 0x20;
                        s100.y1 = s100.y0 + 0x20;
                        arg0 = Taku_Obj_Set(arg0, &s100, 0, 0);
                        tmpl++;
                    }
                }
                frame.x1 = 0x140;
                frame.y1 = 0x21;
            case 0x2742:
                if (*(s16 *)(ctx + 0xC2) == 0x2742) {
                    x = 0x97;
                } else {
                    x = 0xB0;
                }
                sel = campaignWork.eventWindowChoice;
                t = (s16)((sel == 0) ? 0xB0 : 0xE0);
                frame.kind = 8;
                y = t;
                if (*(s16 *)(0xC2 + ctx) == 0x2742) {
                    frame.x1 = 0x148;
                    frame.y1 = 0x21;
                }
                if (campaignWork.eventWindowState == 2) {
                    arg0 = Taku_Window_Set(arg0, &frame, 3, 0, x + left, y, 0, 0x80, 0x40);
                }
                if (campaignWork.eventWindowState == 2) {
                    for (i2 = 0; i2 < 2; i2++) {
                        if (i2 == state->eventWindowChoice) {
                            color.r = color.g = color.b = 0x80;
                            color.a = 0x80;
                        } else {
                            color.r = color.g = color.b = 0x40;
                            color.a = 0x80;
                        }
                        if (*(s16 *)(0xC2 + ctx) == 0x2742) {
                            x = 0x97;
                        } else {
                            x = 0xB0;
                        }
                        if (i2 == 0) {
                            sy = sx = 1.0f;
                            if (*(s16 *)(0xC2 + ctx) == 0x276A) {
                                id = 0x100;
                            } else {
                                id = 0xFD;
                            }
                            arg0 = Taku_Text_Set(arg0, 1, id, x + 8 + left, 0xB4, sx, sy, 0, &color);
                        } else {
                            if (*(s16 *)(ctx + 0xC2) == 0x276A) {
                                id = 0x101;
                            } else {
                                id = 0xFE;
                            }
                            sy = sx = 1.0f;
                            arg0 = Taku_Text_Set(arg0, 1, id, x + 8 + right, 0xE4, sx, sy, 0, &color);
                        }
                    }
                }
                color.r = color.g = color.b = 0x80;
                color.a = 0x80;
                break;
            case 0x2756:
            case 0x2757:
            case 0x2760:
                for (n = 0; n < 3; n++) {
                    hundreds[n] = campaignDeckChoices[state->deckChoices[n]].number / 100;
                    ones[n] = campaignDeckChoices[state->deckChoices[n]].number % 100;
                    for (m = 0; m < 4; m++) {
                        digits[n][m] = ((s32)campaignDeckChoices[state->deckChoices[n]].digits >> (m * 3)) & 7;
                        types[n][m] = (campaignDeckChoices[state->deckChoices[n]].types >> (5 * m)) & 0x1F;
                    }
                }
                if (campaignWork.deckShowPhase == 0) {
                    switch (v = campaignWork.deckShowDone) {
                    case 0:
                        cur = 2;
                        break;
                    default:
                        cur = v;
                        break;
                    }
                } else {
                    cur = campaignWork.eventWindowChoice;
                }
                frame.kind = 1;
                frame.x1 = 0xF0;
                frame.y1 = 0x20;
                arg0 = Taku_Window_Set(arg0, &frame, 2, 0, left + 0xA, 0x8B, 0, 0x80, 0x40);
                sx = 1.0f;
                arg0 = Taku_Text_Set(arg0, 1, 0xFF, left + 0x10, 0x91, sx, sx, 0, &color);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, left + 0x2E, 0xE6, 1, 0, 0xB, D_0030F0BB, NULL);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, left + 0x52, 0xF5, 1, 0, 0xC, D_0030F0C7, NULL);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, right + 0x1A2, 0xB5, 1, 0, 0x13, D_0030F0D4, NULL);
                arg0 = SzDuel_DrawWindow_Font_Pipe(arg0, right + 0x1A2, 0xDD, 1, 0, 0xE, D_0030F0E8, NULL);

                for (n = 0, xx3 = left; n <= hundreds[cur]; n++, xx3 += 0x10) {
                    if (n < hundreds[cur]) {
                        arg0 = Taku_Obj_Set(arg0, &pair130.s[0], xx3, 0);
                    } else {
                        campaignSprites[pair130.s[1].index].width = (ones[cur] * 16) / 100;
                        pair130.s[1].x1 = pair130.s[1].x0 + campaignSprites[pair130.s[1].index].width;
                        arg0 = Taku_Obj_Set(arg0, &pair130.s[1], xx3, 0);
                    }
                }
                arg0 = Taku_Camp_Number_Disp(arg0, hundreds[cur], ones[cur], left);
                for (n = 0; n < 4; n++) {
                    flag = 1;
                    switch (digits[cur][n]) {
                    case 1:
                        s180.index = 0x8A;
                        break;
                    case 2:
                        s180.index = 0x8F;
                        break;
                    case 3:
                        s180.index = 0x8C;
                        break;
                    case 4:
                        s180.index = 0x8D;
                        break;
                    case 5:
                        s180.index = 0x8B;
                        break;
                    case 6:
                        s180.index = 0x8E;
                        break;
                    default:
                        flag = 0;
                        break;
                    }
                    if (flag) {
                        arg0 = Taku_Obj_Set(arg0, &s180, right + (0x208 - n * 0x20), 0xC4);
                    }
                }
                for (k3 = 0; k3 < 4; k3++) {
                    flag2 = 1;
                    switch (types[cur][k3]) {
                    case 1:
                        s180.index = 0x4E;
                        break;
                    case 2:
                        s180.index = 0x58;
                        break;
                    case 3:
                        s180.index = 0x5D;
                        break;
                    case 4:
                        s180.index = 0x4F;
                        break;
                    case 5:
                        s180.index = 0x53;
                        break;
                    case 6:
                        s180.index = 0x55;
                        break;
                    case 7:
                        s180.index = 0x56;
                        break;
                    case 8:
                        s180.index = 0x57;
                        break;
                    case 9:
                        s180.index = 0x51;
                        break;
                    case 10:
                        s180.index = 0x52;
                        break;
                    case 11:
                        s180.index = 0x59;
                        break;
                    case 12:
                        s180.index = 0x54;
                        break;
                    case 13:
                        s180.index = 0x5A;
                        break;
                    case 14:
                        s180.index = 0x5B;
                        break;
                    case 15:
                        s180.index = 0x5C;
                        break;
                    case 16:
                        s180.index = 0x50;
                        break;
                    case 17:
                        s180.index = 0x5E;
                        break;
                    case 18:
                        s180.index = 0x5F;
                        break;
                    case 19:
                        s180.index = 0x60;
                        break;
                    case 20:
                        s180.index = 0x61;
                        break;
                    case 21:
                        s180.index = 0x65;
                        break;
                    default:
                        flag2 = 0;
                        break;
                    }
                    if (k3 == 3) {
                        s200.index = s180.index;
                    }
                    if (flag2) {
                        arg0 = Taku_Obj_Set(arg0, &s180, right + (0x208 - k3 * 0x20), 0xEB);
                    }
                }
                for (k = 0, xx = 0xE0; k < 2; k++, xx += 0x94) {
                    s230 = D_0029AB50;
                    flip = 0;
                    if (1 == k) {
                        s230.x0 = 0x18;
                        s230.y0 = 0;
                        s230.x1 = 0;
                        s230.y1 = 0;
                        s230.x2 = 0x18;
                        s230.y2 = 0x18;
                        s230.x3 = 0;
                        s230.y3 = 0x18;
                        flip = 1;
                    }
                    mode = state->deckChoiceTurn;
                    if (mode == 0) {
                        if (k == 0) {
                            arg0 = Taku_FT4_Set(arg0, &s230, left + xx, 0xF1, flip);
                        } else {
                            arg0 = Taku_FT4_Set(arg0, &s230, right + xx, 0xF1, flip);
                        }
                    } else if (mode == 1 && k == 0) {
                        arg0 = Taku_FT4_Set(arg0, &s230, xx, 0xF1, flip);
                    } else if (mode == 2 && k == 1) {
                        arg0 = Taku_FT4_Set(arg0, &s230, xx, 0xF1, flip);
                    }
                }
                frame.kind = 9;
                frame.x1 = 0xD5;
                frame.y1 = 0x22;
                arg0 = Taku_Window_Set(arg0, &frame, 1, 0, 0x22 + left, 0xB2, 0, 0x80, 0x40);
                arg0 = Taku_Obj_Set(arg0, &s200, 0x27 + left, 0xB7);
                q = RhText_SetTextureFlush(SzMsg_LoadFont_Pipe(arg0, 1, SzDuel_GetMsgName(state->deckChoiceCards[cur]), 0, 0x16));
                width = *(s32 *)((u8 *)SzMsg_GetInfo(1) + 0xC);
                if (width <= 0xA9) {
                    sy = sx = 1.0f;
                    arg0 = SzMsg_DrawRatioX_Pipe(q, 1, left + 0x45, 0xB7, sx, sy, &color, SzMsg_DrawRect_Pipe);
                } else {
                    arg0 = SzMsg_DrawRatioX_Pipe(q, 1, left + 0x45, 0xB7, 170.0f / width, 1.0f, &color, SzMsg_DrawRect_Pipe);
                }
                SzMsg_Free(1);
                break;
            }
        }
        if (campaignWork.eventWindowState == 1) {
            campaignWork.eventWindowOpen += 6;
            if (campaignWork.eventWindowOpen >= 100) {
                campaignWork.eventWindowOpen = 100;
                campaignWork.eventWindowState = 2;
            }
        }
        switch (*(s16 *)(ctx + 0xC2)) {
        case 0x2738:
        case 0x276A:
        case 0x2742:
            if (campaignWork.eventWindowState == 3) {
                campaignWork.eventWindowOpen -= 6;
                if (campaignWork.eventWindowOpen < 0) {
                    campaignWork.eventWindowOpen = 0;
                    campaignWork.eventWindowState = 4;
                }
            }
            break;
        case 0x2756:
        case 0x2757:
        case 0x2760:
            if (campaignWork.eventWindowState == 3 && campaignWork.deckShowPhase >= 3) {
                campaignWork.eventWindowOpen -= 6;
                if (campaignWork.eventWindowOpen < 0) {
                    campaignWork.eventWindowOpen = 0;
                    campaignWork.eventWindowState = 4;
                }
            }
            break;
        }
    }
    return arg0;
}
#pragma opt_dead_assignments reset

typedef struct Packet_00226120 {
    s16 x0, y0, x1, y1, x2, y2, x3, y3;
    u8 r0, g0, b0, a0;
    u8 r1, g1, b1, a1;
    u8 r2, g2, b2, a2;
    u8 r3, g3, b3, a3;
    s16 field20;
    s16 depth;
    s16 field24;
} Packet_00226120;

extern s16 D_00299ED2;
extern u8 campaignCoord; /* original: prim_data */
extern Packet_00226120 D_0029AB80;

/* Draws the clouds drifting over the campaign map. (original: Taku_Camp_Kumo) */
void *Taku_Camp_Clouds(void *packetIn) {
    extern void *Taku_G4_Set();
    s8 *context = &campaignState;
    u8 *slot = &campaignCoord;
    Packet_00226120 packet = D_0029AB80;
    s16 state;
    s16 i;

    if (D_00299ED2 == 0x2724 && campaignWork.eventStep < 6) {
        packet.depth = -10;
    } else if (*(s16 *)(context + 0xC2) == 0x2BB0) {
        packet.depth = -10;
    } else if (*(s16 *)(context + 0xC2) == 0x2F7C) {
        packet.depth = -10;
    }

    state = campaignWork.cloudState;
    if (state != 0) {
        switch ((s16)state) {
        case 2:
            break;
        case 3:
            if (0 <= campaignWork.cloudCover) {
                campaignWork.cloudCover -= 0x10;
                if (campaignWork.cloudCover <= 0) {
                    campaignWork.cloudCover = 0;
                    campaignWork.cloudState = 0;
                }
            }
            break;
        case 4:
            if (campaignWork.cloudCover <= 0x1000) {
                campaignWork.cloudCover += 0x20;
                if (campaignWork.cloudCover >= 0x1000) {
                    campaignWork.cloudCover = 0x1000;
                    campaignWork.cloudState = 4;
                }
            }
            break;
        case 10:
            campaignWork.cloudCover += 0x400;
            if (campaignWork.cloudCover >= 0x1000) {
                campaignWork.cloudCover = 0x1000;
                campaignWork.cloudState = 11;
            }
            break;
        case 20:
            campaignWork.cloudCover -= 0x100;
            if (campaignWork.cloudCover <= 0) {
                campaignWork.cloudCover = 0;
                campaignWork.cloudState = 21;
            }
            break;
        case 22:
            campaignWork.cloudCover += 0x100;
            if (campaignWork.cloudCover >= 0x1000) {
                campaignWork.cloudCover = 0x1000;
                campaignWork.cloudState = 23;
            }
            break;
        case 30:
            campaignWork.cloudCover += 0x400;
            if (campaignWork.cloudCover >= 0x1000) {
                campaignWork.cloudCover = 0x1000;
                campaignWork.cloudState = 31;
            }
            break;
        case 32:
            campaignWork.cloudCover -= 0x20;
            if (campaignWork.cloudCover <= 0) {
                campaignWork.cloudCover = 0;
                campaignWork.cloudState = 33;
            }
            break;
        }

        state = campaignWork.cloudState;
        if (state >= 30) {
            packet.r0 = packet.r1 = packet.r2 = packet.r3 = 255;
            packet.g0 = packet.g1 = packet.g2 = packet.g3 = 255;
            packet.b0 = packet.b1 = packet.b2 = packet.b3 = 255;
        } else if (state >= 20) {
            packet.r0 = packet.r1 = packet.r2 = packet.r3 = 0;
            packet.g0 = packet.g1 = packet.g2 = packet.g3 = 0;
            packet.b0 = packet.b1 = packet.b2 = packet.b3 = 0;
        } else if (state >= 10) {
            packet.r0 = packet.r1 = packet.r2 = packet.r3 = 0;
            packet.g0 = packet.g1 = packet.g2 = packet.g3 = 0;
            packet.b0 = packet.b1 = packet.b2 = packet.b3 = 32;
        }

        packet.x0 = packet.x2 = 0;
        packet.x1 = packet.x3 = 640;
        packet.y0 = packet.y1 = 0;
        packet.y2 = packet.y3 = 448;

        if (*(s16 *)(context + 0xC2) == 0x2738 && campaignWork.eventStep > 1) {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 = 0;
        } else if (*(s16 *)(context + 0xC2) == 0x2B9A ||
                   *(s16 *)(context + 0xC2) == 0x2F64) {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 = 0;
        } else {
            packet.a0 = packet.a1 = packet.a2 = packet.a3 =
                (campaignWork.cloudCover << 7) >> 12;
            packetIn = Taku_G4_Set(packetIn, &packet, 0, 0);
        }
    }

    Taku_Coord_Set(slot);
    for (i = 0; i < 16; i++) {
    }
    return packetIn;
}
