#include "common.h"


typedef struct Flags2C_001A6C80 {
    u8 low : 2;
    s8 mode : 2;
    u8 value : 2;
    u8 high : 2;
} Flags2C_001A6C80;

typedef struct Flags2D_001A6C80 {
    u8 first : 3;
    u8 second : 3;
    u8 high : 2;
} Flags2D_001A6C80;

typedef struct Flags2E_001A6C80 {
    u8 value : 3;
    u8 bit3 : 1;
    s8 bit4 : 1;
    s8 bit5 : 1;
    s8 bit6 : 1;
    s8 bit7 : 1;
} Flags2E_001A6C80;

void func_001A6C80(void) {
    s8 *data = (s8 *)&D_00317250;
    s32 i;
    s32 *p;

    RhMem_FillMemory((s8 *) &D_00317250, 0, 0x230);
    D_00317250 = 0;
    D_00317254 = 0;
    D_0031747A = 1;
    i = 0;
    p = (s32 *)data;
    do {
        p[0x138 / 4] = 0;
        p[0xA4 / 4] = 0;
        p[0x10 / 4] = 0;
        data[0x1CC + i] = 10;
        i++;
        p++;
    } while (i < 0x25);
    *(s32 *)(data + 0x14) = 2;
    *(s32 *)(data + 0xA8) = 0x38;
    *(s32 *)(data + 0x18) = 1;
    *(s32 *)(data + 0xAC) = 2;
    *(s32 *)(data + 0x1C) = 4;
    *(s32 *)(data + 0xB0) = 0x66;
    *(s32 *)(data + 0x144) = 0x64;
    *(s32 *)(data + 0x20) = 4;
    *(s32 *)(data + 0xB4) = 0x66;
    *(s32 *)(data + 0x148) = 0x64;
    *(s32 *)(data + 0x24) = 2;
    *(s32 *)(data + 0xB8) = 0xA;
    *(s32 *)(data + 0x28) = 1;
    *(s32 *)(data + 0xBC) = 2;
    *(s32 *)(data + 0x2C) = 3;
    *(s32 *)(data + 0xC0) = 0x2AB;
    *(s32 *)(data + 0x34) = 1;
    *(s32 *)(data + 0xC8) = 5;
    *(s32 *)(data + 0x38) = 1;
    *(s32 *)(data + 0xCC) = 3;
    *(s32 *)(data + 0x3C) = 2;
    *(s32 *)(data + 0xD0) = 0x64;
    *(s32 *)(data + 0x40) = 1;
    *(s32 *)(data + 0xD4) = 5;
    *(s32 *)(data + 0x54) = 4;
    *(s32 *)(data + 0xE8) = 0x2710;
    *(s32 *)(data + 0x5C) = 4;
    *(s32 *)(data + 0xF0) = 0x2710;
    *(s32 *)(data + 0x60) = 1;
    *(s32 *)(data + 0xF4) = 7;
    *(s32 *)(data + 0x64) = 1;
    *(s32 *)(data + 0xF8) = 2;
    *(s32 *)(data + 0x18C) = 1;
    *(s32 *)(data + 0x68) = 4;
    *(s32 *)(data + 0xFC) = 0x2710;
    *(s32 *)(data + 0x190) = 0x63;
    *(s32 *)(data + 0x6C) = 5;
    *(s32 *)(data + 0x100) = 0x186A0;
    *(s32 *)(data + 0x70) = 4;
    *(s32 *)(data + 0x104) = 0x10000;
    *(s8 *)(data + 0x1E4) = 0x10;
    *(s32 *)(data + 0x74) = 1;
    *(s32 *)(data + 0x108) = 2;
    *(s32 *)(data + 0x19C) = 1;
    *(s32 *)(data + 0x78) = 2;
    *(s32 *)(data + 0x10C) = 0x81;
    *(s32 *)(data + 0x1A0) = 0x80;
    *(s8 *)(data + 0x1E6) = 0x10;
    *(s32 *)(data + 0x7C) = 2;
    *(s32 *)(data + 0x110) = 0xD;
    *(s32 *)(data + 0x1A4) = 1;
    *(s32 *)(data + 0x80) = 1;
    *(s32 *)(data + 0x114) = 4;
    *(s32 *)(data + 0x1A8) = 3;
    *(s32 *)(data + 0x84) = 1;
    *(s32 *)(data + 0x118) = 4;
    *(s32 *)(data + 0x1AC) = 3;
    *(s32 *)(data + 0x88) = 1;
    *(s32 *)(data + 0x11C) = 2;
    *(s32 *)(data + 0x1B0) = 1;
    *(s32 *)(data + 0x8C) = 1;
    *(s32 *)(data + 0x120) = 2;
    *(s32 *)(data + 0x90) = 1;
    *(s32 *)(data + 0x124) = 2;
    *(s32 *)(data + 0x50) = 1;
    *(s32 *)(data + 0xE4) = 4;
    *(s32 *)(data + 0x94) = 2;
    *(s32 *)(data + 0x128) = 0x12;
    *(s8 *)(data + 0x21E) = -3;
    *(s8 *)(data + 0x21F) = -3;
    *(s8 *)(data + 0x220) = -3;
    *(s8 *)(data + 0x221) = 0;
    *(s8 *)(data + 0x1F1) = -3;
    *(s8 *)(data + 0x1F9) = 0;
    *(s8 *)(data + 0x222) = 0;
    *(s8 *)(data + 0x223) = 0;
    *(s8 *)(data + 0x22B) = *(s8 *)(data + 0x188);
    ((Flags2D_001A6C80 *)(data + 0x22D))->first = 0;
    *(s16 *)(data + 0x21C) = 0;
    ((Flags2D_001A6C80 *)(data + 0x22D))->second = 0;
    ((Flags2E_001A6C80 *)(data + 0x22E))->value = 0;
    ((Flags2E_001A6C80 *)(data + 0x22E))->bit3 = 0;
    ((Flags2E_001A6C80 *)(data + 0x22E))->bit5 = *(s8 *)(data + 0x18C);
    SzData_SetOption(0, 0, *(s32 *)(data + 0x1B8));
    SzData_SetOption(0, 1, *(s32 *)(data + 0x1B4));
    SzData_SetOption(0, 2, *(s32 *)(data + 0x19C));
    ((Flags2E_001A6C80 *)(data + 0x22E))->bit6 = 1;
    ((Flags2E_001A6C80 *)(data + 0x22E))->bit7 = 0;
    ((Flags2C_001A6C80 *)(data + 0x22C))->value = 0;
    ((Flags2E_001A6C80 *)(data + 0x22E))->bit4 = 0;
    *(s32 *)(data + 0xC) = 0;
    *(s8 *)(data + 0x229) = 0;
    *(s8 *)(data + 0x228) = 0;
    ((Flags2C_001A6C80 *)(data + 0x22C))->mode = 1;
    *(s32 *)(data + 0x204) = 0;
    *(s32 *)(data + 0x208) = 0;
    *(s8 *)(data + 0x20E) = 0;
    *(s8 *)(data + 0x20D) = 0;
    *(s8 *)(data + 0x20C) = 0;
    *(u8 *)(data + 0x20F) = 0x80;
    *(s32 *)(data + 0x214) = 0;
    *(s32 *)(data + 0x218) = 0;
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrDigitEntry {
    int unknown_00;
    int words[4];
};
extern struct DotrDigitEntry *func_001FEAB0_b(int index);
extern void func_001FE880_b(int a0, int a1, int *words, int a3);
extern void func_001FE750_b(int a0, int a1, int a2, int a3, void (*draw)(void));
extern void func_001FDFE0_b(void);
struct DotrDigitView {
    unsigned char unknown_000[0x10];
    unsigned int count[37];
    int flag[37];
    unsigned int value[37];
    unsigned char radix[37];
    unsigned char unknown_1f1[0x32];
    unsigned char cursor;
    unsigned char unknown_224[9];
    unsigned char page : 3;
};
extern struct DotrDigitView D_00317250_1a6ff0;
extern struct DotrDigitView D_00317250_1a6ff0;
extern unsigned char D_002BE660_1a6ff0[];
struct DotrDigitWords {
    float x, y, z, w;
};

void SzGame_DrawMenu(void)
{
    struct DotrDigitView *view = &D_00317250_1a6ff0;
    int first;
    unsigned char *label;
    int words[4];
    int source[4];
    int slot;
    int digit;
    struct DotrDigitEntry *low;
    struct DotrDigitEntry *high;
    int i;
    unsigned int j;
    int label_id;
    int row;
    struct DotrDigitEntry *entry;
    int x;
    int scale;
    int y;
    unsigned char *walk;

    SzMsg_GetDefRect(source);
    *(struct DotrDigitWords *)words = *(struct DotrDigitWords *)source;
    low = func_001FEAB0_b(20);
    high = func_001FEAB0_b(21);
    first = D_00317250_1a6ff0.page * 20;
    SzMsg_Init(0, RhBase_GetUserGsAddress());
    label = &D_002BE660_1a6ff0[first];
    for (i = 0, walk = label; i < 20; i++, walk++) {
        if ((unsigned int)(first + i) < 29) {
            SzMsg_LoadFont(i, *walk + 284, i < 10 ? 0 : 320, (i % 10 + 2) * 22);
        }
    }
    SzMsg_LoadFont(i, 21, 0, 0);
    SzMsg_LoadFont(i + 1, 24, 0, 22);
    low->words[2] = 22;
    high->words[2] = 22;
    ExFlushTexture();
    for (row = 0, y = 0; row < 20; row++, label++, y += 22) {
        entry = func_001FEAB0_b(row);
        if ((unsigned int)(first + row) < 29) {
            label_id = *label;
            if (view->cursor == row) {
                words[2] = entry->words[2];
                if (view->flag[label_id] != 0) {
                    words[2] = (view->count[label_id] + 10) * 22;
                }
                func_001FE880_b(0, y, words, 0);
            }
            func_001FE750_b(row, 0, y, 0, func_001FDFE0_b);
            if (view->flag[label_id] != 0) {
                scale = 1;
                x = 220;
                for (j = 1; j < view->count[label_id]; j++) {
                    scale *= view->radix[label_id];
                }
                for (j = 0; j < view->count[label_id]; j++) {
                    digit = view->value[label_id] / scale % view->radix[label_id];
                    slot = 20;
                    if (digit < 10) {
                        low->words[0] = digit * 22;
                    } else {
                        slot++;
                        high->words[0] = (digit - 10) * 22;
                    }
                    func_001FE750_b(slot, x, y, 0, func_001FDFE0_b);
                    x += 22;
                    scale /= view->radix[label_id];
                }
            }
        }
        SzMsg_Free(row);
    }
}

typedef struct Flags_001A7380 {
    s8 reserved0 : 5;
    s8 enabled : 1;
    s8 reserved1 : 2;
} Flags_001A7380;

typedef struct Menu_001A7380 {
    u8 pad000[0xA4];
    u32 limits[37];
    u32 values[37];
    u8 pad1CC[0x38];
    s32 firstAddress;
    s32 secondAddress;
    u8 pad20C[0x14];
    s8 x;
    s8 y;
    u8 pad222;
    u8 selected;
    u8 pad224[7];
    s8 mode;
    u8 pad22C;
    u8 page;
    Flags_001A7380 flags;
} Menu_001A7380;

typedef struct File_001A7380 {
    u8 pad000[8];
    s32 size : 31;
    u32 flag : 1;
} File_001A7380;

extern u8 D_002BE660[];
extern char D_002BE7D0[];
extern char D_002BE7D5[];
extern u8 D_00317473;
extern u8 D_0031747D;

void SzGame_ActMenu(void) {
    extern void func_0019B648();
    extern s32 SzGame_ActMemCardProc();
    Menu_001A7380 *menu;
    u32 selectionIndex;
    s32 high;
    s32 low;
    u32 limit;
    u32 offset;
    u32 *value;
    s32 item;
    u32 previous;
    char filename[128];

    menu = (Menu_001A7380 *) &D_00317250;
    selectionIndex = D_00317473 + (D_0031747D & 7) * 20;
    if (SzGame_ActMemCardProc() >= 0) {
        return;
    }
        if (selectionIndex >= 29) {
            selectionIndex = (menu->page & 7) * 20;
            menu->selected = 0;
        }
        item = D_002BE660[selectionIndex];
        if (SzFade_GetRestCount(0) == 0) {
            SzGame_SetMode(menu->x, menu->y);
            SzFade_SetKillFlag(0);
            SzFade_Destroy(1);
            SzFade_Entry(1, 0, 1, 0, 60, 0);
            SzFade_SetKillFlag(1);
            SzFade_SetPauseFlag(1, 1);
            return;
        }
        if (SzPad_Check(0, 2, 0x5000) != 0) {
            s32 high;
            s32 low;
            low = menu->selected;
            high = 9;
            if ((u32) ((menu->page & 7) + 1) < 2) {
                high = 20;
            }
            if (SzPad_Check(0, 2, 0x1000) != 0) {
                menu->selected = (menu->selected + high - 1) % high;
            } else {
                menu->selected = (menu->selected + high + 1) % high;
            }
            if (menu->selected != low) {
                SzSound_PlaySE(0, 3);
            }
            return;
        }
        if (SzPad_Check(0, 2, 0xA000) != 0) {
            s32 high;
            high = menu->page & 7;
            if (SzPad_Check(0, 2, 0x8000) != 0) {
                menu->page = (menu->page & ~7) | (((menu->page & 7) + 1) & 1);
            } else {
                menu->page = (menu->page & ~7) | (((menu->page & 7) + 3) & 1);
            }
            if ((menu->page & 7) != high) {
                SzSound_PlaySE(0, 3);
            }
            return;
        }
        {
            offset = item * 4;
            limit = menu->limits[item];
            if (limit != 0) {
                previous = menu->values[item];
                value = &menu->values[item];
                switch (item) {
                case 3:
                case 4:
                    high = *value / 1000U;
                    low = *value % 1000U;
                    if (SzPad_Check(0, 2, 4) != 0) {
                        low = (low + limit - 1) % limit;
                    }
                    if (SzPad_Check(0, 2, 8) != 0) {
                        low = (low + limit + 1) % limit;
                    }
                    if (SzPad_Check(0, 2, 1) != 0) {
                        high = (high + 1) % 2;
                    }
                    if (SzPad_Check(0, 2, 2) != 0) {
                        high = (high + 3) % 2;
                    }
                    *value = low + high * 1000;
                    break;
                case 17:
                case 19:
                case 22:
                    high = *value / 100U;
                    low = *value % 100U;
                    if (SzPad_Check(0, 2, 4) != 0) {
                        low = (low + 99) % 100;
                    }
                    if (SzPad_Check(0, 2, 8) != 0) {
                        low = (low + 101) % 100;
                    }
                    if (SzPad_Check(0, 2, 1) != 0) {
                        high = (high + 99) % 100;
                    }
                    if (SzPad_Check(0, 2, 2) != 0) {
                        high = (high + 101) % 100;
                    }
                    *value = low + high * 100;
                    break;
                case 23:
                    high = *value / 1000U;
                    low = *value % 1000U;
                    if (SzPad_Check(0, 2, 4) != 0) {
                        low = (low + 999) % 1000;
                    }
                    if (SzPad_Check(0, 2, 8) != 0) {
                        low = (low + 1001) % 1000;
                    }
                    if (SzPad_Check(0, 2, 1) != 0) {
                        high = (high + 99) % 100;
                    }
                    if (SzPad_Check(0, 2, 2) != 0) {
                        high = (high + 101) % 100;
                    }
                    *value = low + high * 1000;
                    break;
                case 24: {
                    u32 packed;
                    packed = *value;
                    high = packed >> 8;
                    low = packed & 0xFF;
                    if (SzPad_Check(0, 2, 4) != 0) {
                        low = (low + 255) % 256;
                    }
                    if (SzPad_Check(0, 2, 8) != 0) {
                        low = (low + 257) % 256;
                    }
                    if (SzPad_Check(0, 2, 1) != 0) {
                        high = (high + 255) % 256;
                    }
                    if (SzPad_Check(0, 2, 2) != 0) {
                        high = (high + 257) % 256;
                    }
                    *value = low + (high << 8);
                    break;
                }
                case 26:
                    if (SzPad_Check(0, 2, 4) != 0) {
                        *value = (*value + limit - 1) % limit;
                        if (*value == 0) {
                            *value = limit - 1;
                        }
                    }
                    if (SzPad_Check(0, 2, 8) != 0) {
                        *value = (*value + limit + 1) % limit;
                        if (*value == 0) {
                            *value = 1;
                        }
                    }
                    break;
                case 27:
                    if (SzPad_Check(0, 2, 4) != 0) {
                        *value = (*value + limit - 1) % limit;
                        if (*value == 0) {
                            *value = 12;
                        }
                    }
                    if (SzPad_Check(0, 2, 8) != 0) {
                        *value = (*value + limit + 1) % limit;
                        if (*value == 0) {
                            *value = 1;
                        }
                    }
                    break;
                default:
                    if (SzPad_Check(0, 2, 4) != 0) {
                        *value = (*value + limit - 1) % limit;
                    }
                    if (SzPad_Check(0, 2, 8) != 0) {
                        *value = (*value + limit + 1) % limit;
                    }
                    break;
                }
                if (*value != previous) {
                    SzSound_PlaySE(0, 3);
                }
            }
            switch (item) {
            case 2:
            case 3:
            case 4:
            case 29:
            case 30:
                return;
            case 6:
                if (SzPad_Check(0, 0, 0x10) != 0) {
                    if ((s32) menu->values[1] < 22) {
                        high = menu->values[1] + 26;
                        if (menu->values[1] == 0) {
                            high = 17;
                        }
                        SzSound_PlaySE(0, 4);
                        SzData_SetupFromConstDeck(*(u32 *) (offset + (u32) menu + 0x138), high);
                        return;
                    } else {
                        SzSound_PlaySE(0, 6);
                        return;
                    }
                } else if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_PlaySE(0, 4);
                    SzGame_Push(item, 0);
                }
                return;
            case 10:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_PlaySE(0, 4);
                    SzGame_Push(item, 0);
                }
                return;
            case 13:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_PlaySE(0, 4);
                    *(u32 *) (offset + (u32) menu + 0x138) = 1;
                    SzGame_Push(item, 0);
                }
                return;
            case 15:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_PlaySE(0, 4);
                    *(u32 *) (offset + (u32) menu + 0x138) = 1;
                    SzGame_Push(item, 0);
                }
                return;
            case 17:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    u8 *address;
                    u8 *directory;
                    File_001A7380 *loaded;
                    address = (u8 *) 0x04000000;
                    directory = SzFile_GetEnv((s32) D_002BE7D0);
                    low = menu->values[17] % 100U;
                    high = menu->values[17] / 100U;
                    menu->secondAddress = 0;
                    menu->firstAddress = 0;
                    func_0019B648(filename, D_002BE7D5, (s32) directory, low);
                    if ((loaded = (File_001A7380 *) SzFile_Read((s32) filename, (s32) address, -1)) != NULL) {
                        menu->firstAddress = 0x04000000;
                        RhText_BindAddress(menu->firstAddress);
                        address = (u8 *) 0x04000000 + ((loaded->size + 63) & ~63);
                    }
                    if (high != 0) {
                        func_0019B648(filename, D_002BE7D5, directory, high);
                        if (SzFile_Read((s32) filename, (s32) address, -1) != 0) {
                            menu->secondAddress = (s32) address;
                            RhText_BindAddress(menu->secondAddress);
                        }
                    }
                    if (menu->firstAddress != 0 || menu->secondAddress != 0) {
                        SzSound_PlaySE(0, 4);
                        SzGame_Push(item, 0);
                        return;
                    } else {
                        SzSound_PlaySE(0, 6);
                        return;
                    }
                }
                return;
            case 20:
                menu->mode = *(s8 *) &menu->values[20];
                return;
            case 21:
                menu->flags.enabled = *(s8 *) &menu->values[21];
                return;
            case 22:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_PlayBGM(menu->values[22], 1);
                    return;
                } else if (SzPad_Check(0, 0, 0x20) != 0) {
                    SzSound_StopBGM(0x100);
                    return;
                }
                return;
            case 23: {
                s32 channel;
                s32 sound;
                channel = menu->values[23] / 1000U;
                sound = menu->values[23] % 1000U;
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_TransferSEGrp(channel, sound, 1);
                }
                return;
            }
            case 24: {
                s32 channel;
                channel = menu->values[23] / 1000U;
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_PlaySE(channel, menu->values[24]);
                    return;
                } else if (SzPad_Check(0, 0, 0x20) != 0) {
                    SzSound_StopSE(channel, menu->values[24]);
                    return;
                }
                return;
            }
            case 25:
                if (SzPad_Check(0, 0, 0x10) != 0) {
                    if (menu->values[25] != 0) {
                        SD_SuspendSoundSystem(0);
                        SzSound_Init();
                    } else {
                        SD_StopAll();
                        SD_SuspendSoundSystem(1);
                        SzSound_Term();
                    }
                }
                SzData_SetOption(0, 2, menu->values[25]);
                return;
            case 26:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SD_BGMSetSourceLevel(menu->values[26], 0x80);
                    SzSound_PlaySE(0, 4);
                }
                return;
            case 27:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    s32 count;
                    s32 i;
                    count = menu->values[27];
                    i = 0;
                    do {
                        SzData_SetRankDirect(0, i, count);
                        SzData_SetRankDirect(1, i, count);
                        i++;
                    } while (i < 854);
                    SzSound_PlaySE(0, 4);
                }
                return;
            case 31:
                SzData_SetOption(0, 1, menu->values[31]);
                return;
            case 32:
                SzData_SetOption(0, 0, menu->values[32]);
                return;
            case 16:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzGame_PlayMovieNo(*(u32 *) (offset + (u32) menu + 0x138), 1, 1);
                }
                return;
            case 33:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    if (SzFile_InqRequestEx() == 0) {
                        SzText_LoadMerge(menu->values[33], 1);
                        SzSound_PlaySE(0, 4);
                        return;
                    } else {
                        SzSound_PlaySE(0, 6);
                        return;
                    }
                }
                return;
            case 34:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_PlaySE(0, 4);
                    SzGame_InitMemCardProc(0);
                }
                return;
            case 35:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_PlaySE(0, 4);
                    SzGame_InitMemCardProc(1);
                }
                return;
            default:
                if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_PlaySE(0, 4);
                    SzGame_Push(item, 0);
                }
                return;
            }
        }
}

typedef struct {
    u8 padding[0x138];
    s32 entries[0x25];
} Table_001A82E0;

s32 SzGame_GetMenuNum(s32 arg0) {
    Table_001A82E0 *table = (Table_001A82E0 *)&D_00317250;
    s32 result;

    if ((arg0 < 0) || (arg0 >= 0x25)) {
        result = -1;
    } else {
        result = table->entries[arg0];
    }
    return result;
}

typedef struct State_001A8320 {
    u8 padding[0x138];
    s32 values[0x25];
} State_001A8320;

s32 SzGame_SetMenuNum(s32 arg0, s32 arg1) {
    State_001A8320 *state = (State_001A8320 *)&D_00317250;

    if ((arg0 < 0) || (arg0 >= 0x25)) {
        return 0;
    }
    state->values[arg0] = arg1;
    return 1;
}

void SzGame_PlayMovieNo(s32 arg0, s32 arg1, s32 arg2) {
    u8 *SzFile_GetEnv(u8 *);
    void func_0019B648(void *, void *, ...);
    u8 buf[128];

    func_0019B648(buf, D_002BE809, SzFile_GetEnv(D_002BE80F), D_0028FF10[arg0]);
    SzGame_PlayMovie(buf, arg1, arg2);
}

s32 SzGame_PlayMovie(u8 *arg0, s32 arg1, s32 arg2) {
    extern s32 movie_play();
    extern s32 SzModel_GetModelNo(s32);
    s32 flag;
    s32 i;
    s32 result;

    flag = SzSound_IsStandby();
    while (SzFile_InqRequestEx() != 0) {
        SzFile_DoRequestS();
    }
    if (flag != 0) {
        SD_StopAll();
        SD_SuspendSoundSystem(1);
        SzSound_Term();
    }
    for (i = 0; i < 10; i++) {
        SzModel_Preset(i + 0x14, -1, SzModel_GetModelNo(i + 0x14));
    }
    RhBase_FlipBuffer();
    RhBase_ResetGsEnv(1);
    result = movie_play(arg0, arg1, arg2);
    sceGsSyncV(0);
    RhBase_ResetGsEnv(0);
    SzGame_ClearGsMem(10, 0, 0, 0, 0x400, 0x400);
    if (flag != 0) {
        SD_SuspendSoundSystem(0);
        SzSound_Init();
    }
    return result;
}

typedef union {
    u32 words[4];
    u64 halves[2];
    __int128 quad;
} Packet_001A8520;


void SzGame_ClearGsMem(s64 arg0, s32 arg1, s32 arg2, s64 arg3, s64 arg4, s64 arg5) {
    s32 sceGsSetDefDrawEnv(void *, s64, s64, s64, s64, s64);
    s32 sceGsSetDefClear(void *, s64, s64, s64, s64, s64, s32, s32, s64, s64, s64);
    void sceDmaSend(s32, void *);
    Packet_001A8520 packet[20];
    s32 channel;
    u8 *cursor;

    channel = sceDmaGetChan(2);
    cursor = (u8 *)packet;
    *(u32 *)(cursor + 0) = 0x10000010;
    *(u32 *)(cursor + 4) = 0;
    *(u32 *)(cursor + 8) = 0;
    *(u32 *)(cursor + 12) = 0;
    *(u64 *)(cursor + 16) = 0x1000000000000008ULL;
    *(u64 *)(cursor + 24) = 0xE;
    cursor += 32;
    cursor += sceGsSetDefDrawEnv(cursor, (s16)arg0, (s16)arg4, (s16)arg5, 0, 0) * 16;
    *(u64 *)(cursor + 0) = 0x1000000000008006ULL;
    *(u64 *)(cursor + 8) = 0xE;
    cursor += 16;
    cursor += sceGsSetDefClear(cursor, 2, 0, 0, 0xFFF, 0xFFF, arg1, arg2, arg3, 0, 0) * 16;
    *(u32 *)(cursor + 0) = 0x70000000;
    *(u32 *)(cursor + 4) = 0;
    *(u32 *)(cursor + 8) = 0;
    *(u32 *)(cursor + 12) = 0;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceDmaSend(channel, packet);
    sceGsSyncPath(0, 0);
}

s8 SzGame_InqAutoBlur(void) {
    return D_0031747B;
}

typedef struct {
    u8 pad00[0xF4];
    u32 count;
    u8 padF8[0x133];
    s8 selected;
} State_001A86A0;

void SzGame_SetAutoBlur(s32 arg0) {
    State_001A86A0 *state = (State_001A86A0 *)&D_00317250;

    if ((arg0 >= 0) && ((u32)arg0 < state->count)) {
        state->selected = arg0;
    }
}

typedef struct Flags_001A86D0 {
    s8 reserved0 : 5;
    s8 enabled : 1;
    s8 flag6 : 1;
    s8 reserved1 : 1;
} Flags_001A86D0;

extern Flags_001A86D0 D_0031747E;

s32 SzGame_InqSoftFocus(void) {
    return D_0031747E.enabled != 0 ? 1 : 0;
}

s32 SzGame_VSync(void) {
    D_00317250 += 1;
    return 1;
}

s32 SzGame_GetHSyncCount(void) {
    return *(s32 *)0x10000800;
}

s32 SzGame_GetFrameCount(void) {
    return D_00317254;
}

s32 SzGame_AddFrameCount(void) {
    return ++D_00317254;
}

void SzGame_SetFrameSpeed(s32 arg0) {
    D_0031747A = (s8) arg0;
}

u8 SzGame_GetFrameSpeed(void) {
    return D_0031747A;
}

void SzGame_SetStabilizer(s64 arg0) {
    D_0031747E.flag6 = arg0;
}

s32 SzGame_GetStabilizer(void) {
    return D_0031747E.flag6 != 0 ? 1 : 0;
}

typedef struct {
    s8 padding[0x1F9];
    s8 values[0x28];
    s8 index;
    u8 base;
} State_001A87C0;

typedef struct {
    s8 a;
    s8 b;
    s8 c;
} Tail_001A87C0;

extern Tail_001A87C0 D_0031746F;

void SzGame_Goto(s32 arg0, s32 arg1) {
    State_001A87C0 *state = (State_001A87C0 *)&D_00317250;

    SzFade_Entry(0, 1, 1, 0, 60, 0);
    D_0031746F.a = -2;
    D_0031746F.b = arg0;
    D_0031746F.c = 0;
    if (arg1 >= 0) {
        *((s8 *)(state->index + (state->base + (s32)state)) + 0x1F9) = arg1;
    }
    if (arg1 < 2) {
        SzGame_ReqBGM(-2, 1);
    }
}

extern u8 D_00317472;

typedef struct State_001A8870 {
    u8 pad_000[0x1F9];
    s8 entries[0x26];
    s8 field_21F;
    s8 field_220;
    s8 field_221;
    u8 field_222;
} State_001A8870;

void SzGame_Push(s32 arg0, s32 arg1) {
    State_001A8870 *state = (State_001A8870 *)&D_00317250;
    s8 *entry;

    if ((D_00317472 + 1) < 8) {
        SzFade_Entry(0, 1, 1, 0, 60, 0);
        state->field_21F = -2;
        state->field_220 = arg0;
        state->field_221 = 1;
        entry = (s8 *)(state->field_222 + (u32)state);
        entry[state->field_221 + 0x1F9] = arg1;
        if (arg1 < 2) {
            SzGame_ReqBGM(-2, 1);
        }
    }
}

typedef struct {
    u8 padding[0x1F0];
    s8 entries[0x2F];
    s8 state;
    s8 selected;
    s8 previous;
    u8 index;
} State_001A8920;

extern u8 D_00317472;

void SzGame_Pop(void) {
    State_001A8920 *state = (State_001A8920 *)&D_00317250;

    if ((D_00317472 - 1) >= 0) {
        SzFade_Entry(0, 1, 1, 0, 60, 0);
        state->state = -2;
        state->selected = state->entries[state->index];
        state->previous = -1;
        if (state->entries[state->index + 1] < 2) {
            SzGame_ReqBGM(-2, 1);
        }
    }
}

struct DotrMovieOperationsStatePrefix {
    unsigned char unknown_000[8];
    unsigned int field_008; 
    int field_00c;
    unsigned char unknown_010[0x14c];
    int field_15c; 
    int field_160; 
    int field_164; 
    unsigned char unknown_168[0x28];
    int field_190; 
    unsigned char unknown_194[0x5d];
    signed char bytes_1f1[8];
    unsigned char bytes_1f9[8];
    unsigned char unknown_201[0xb];
    unsigned char bytes_20c[4]; 
    unsigned char unknown_210[4];
    int field_214; 
    int field_218;
    unsigned short field_21c;
    signed char field_21e;
    signed char field_21f;
    signed char field_220;
    signed char field_221;
    unsigned char field_222;
    unsigned char unknown_223;
    unsigned char field_224; 
    unsigned char field_225; 
    unsigned char field_226; 
    unsigned char field_227;
    signed char field_228;
    signed char field_229;
    unsigned char unknown_22a[2];
    struct {
        signed char unknown_0 : 2;
        signed char field_2 : 2;
        unsigned char field_4 : 2;
        signed char unknown_6 : 2;
    } field_22c;
    unsigned char unknown_22d;
    struct {
        signed char unknown_0 : 4;
        signed char field_4 : 1;
        signed char field_5 : 1;
        signed char unknown_6 : 2;
    } field_22e;
    struct {
        signed char field_0 : 1;
        signed char field_1 : 1;
    } field_22f;
};
extern struct DotrMovieOperationsStatePrefix D_00317250_b;

void SzGame_SetMode(int arg0, int arg1)
{
    struct DotrMovieOperationsStatePrefix *state = &D_00317250_b;
    int flag = 1;
    unsigned int prior = state->bytes_1f9[state->field_222];
    state->field_21e = state->bytes_1f1[state->field_222];
    state->field_222 += arg1;
    state->bytes_1f1[state->field_222] = arg0;
    state->field_21f = arg0;
    if (state->bytes_1f9[state->field_222] == 0 || arg1 <= 0)
        SzGame_ModeTerm(state->field_21e);
    else
        flag = 0;
    SzGame_ComInit();
    if (prior == 0 || arg1 >= 0)
        SzGame_ModeInit(state->field_21f);
    else
        flag = 0;
    switch (arg0) {
    case -3:
    case -2:
    case -1:
    case 10:
    case 36:
        flag = 0;
        break;
    case 15:
        if (state->field_21e == 1)
            flag = 0;
        break;
    }
    state->field_221 = 0;
    state->field_22c.field_4 = 3;
    state->field_22e.field_4 = (signed char)flag;
    state->field_00c = 0;
    state->field_229 = 0;
    state->field_228 = 0;
    state->field_22c.field_2 = 1;
}

void SzGame_ComInit(void) {
    extern s32 SzModel_SetAnimSpeed(s32, f32);
    s32 i;

    SzDuel_InitMapColor(0, 0, 1);
    SzDuel_InitFieldRate();
    SzView_SetRoll(0, 0);
    SzView_SetScreenDistance(0, 800.0f);
    SzView_SetCamera(0, 0, 0);
    SzView_RollCamera(0, 0, 1, 3.0434179f, 0.19634955f, 0.0f);

    for (i = 0; i < 10; i++) {
        SzView_SetFogParamZ(0, i, 0);
        SzView_SetFogParamY(0, i, 0);
        SzView_SetStraightLight(0, i, 0);
        SzView_SetPointLight(0, i, 0);
    }
    for (i = 0; i < 10; i++) {
        SzModel_SetDeform(i + 20, 0);
        SzModel_SetDeformRatio(i + 20, 0);
    }
    for (i = 0; i < 2; i++) {
        SzModel_SetDeform(i + 30, 0);
        SzModel_SetDeformRatio(i + 30, 0);
    }
    for (i = 0; i < 84; i++) {
        SzModel_SetDrawFlag(i, 0);
        SzModel_SetScale(i, NULL);
        SzModel_SetRotC(i, NULL);
        SzModel_SetDeform(i, 0);
        SzModel_SetDeformRatio(i, 0);
        SzModel_SetAnimDirect(i, 0);
        SzModel_SetAnimDir(i, 1);
        SzModel_SetAnimSpeed(i, 1.0f);
        SzModel_SetRgba(i, 0, NULL);
        SzModel_SetFilter(i, 1, NULL);
        SzModel_SetIntensity(i, NULL);
    }
    SzEffect_SetBlackOutForMonster(0x80);
    SzEffect_SetBlackOutForDuel(0x80);
    SzEffect_SetBlackOutForBattle(0x80);
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct MovieUpdateBits {
    signed char unknown_0_6 : 7;
    signed char bit_7 : 1;
};
struct MovieUpdatePrefix {
    unsigned char unknown_000[0x138];
    unsigned int menu_nums[37];
    unsigned char unknown_1cc[0x52];
    signed char byte_21e;
    unsigned char unknown_21f[0x0f];
    struct MovieUpdateBits bits_22e;
    unsigned char unknown_22f;
    unsigned char byte_230;
};
extern struct MovieUpdatePrefix D_00317250_1a8db0;
extern char D_002BE80F_b[];
extern char D_002BE809_b[];
extern const char *D_0028FF10_b[];
extern char *func_00197548_1a8db0(const char *);
extern char *func_001FFF90_b(const char *);
extern void SzModel_LoadMerge(int, int, int);
extern void func_002051C0_b(int);
extern void func_001E3850_b(int, int, int);
extern void func_001FC9B0_b(int);
extern void func_002009E0_b(int, int);
extern void func_001E1E70_b(int, int, int, int);
extern void func_001E1D70_b(int, int, int, int);
extern void func_001E1C10_b(int, int, int, int);
extern void func_00217590_b(int, int, int);
extern void func_001C5D70_1a8db0(int);
extern void func_001F30B0_b(int, int);
extern void func_001DDD80_b(int, int);

void SzGame_ModeInit(int index)
{
    struct MovieUpdatePrefix *state = &D_00317250_1a8db0;
    int value_0, value_1, result_0, result_1;
    int i, is_one;
    char path[128];
    switch (index) {
    case -1:
        for (i = 0; i < 84; ++i)
            func_001F30B0_b(i, 0);
        state->bits_22e.bit_7 = -1;
        func_00217590_b(0, 0, 0);
        break;
    case 0:
        func_002009E0_b(1, 0);
        
    case 1:
        if (index == 1)
            is_one = 1;
        else
            is_one = 0;
        SzData_SetRoseFlag(state->menu_nums[2]);
        func_002009E0_b(11, 0);
        func_002009E0_b(12, 0);
        func_001DDD80_b(1, state->menu_nums[1]);
        SzDuel_SetPlayer(0, state->menu_nums[3] % 1000);
        SzDuel_SetPlayer(1, state->menu_nums[4] % 1000);
        SzDuel_Init(state->menu_nums[1], state->menu_nums[2], is_one);
        break;

    case 5: {
        func_002009E0_b(12, 0);
        SzModel_LoadMerge(1, 0, 0);
        SzModel_LoadMerge(2, state->menu_nums[index], 0);
        value_0 = SzData_GetCurrentDeck(0);
        value_1 = SzData_GetCurrentDeck(1);
        result_0 = SzData_GetLeader(0, value_0);
        result_1 = SzData_GetLeader(1, value_1);
        if (result_0 == 999)
            result_0 = 0;
        if (result_1 == 999)
            result_1 = 0;
        SzDuel_Initialize();
        SzDuel_AddUnit(0, 3, 6, result_0, 1);
        SzDuel_AddUnit(1, 3, 0, result_1, 1);
        SzBattle_Init(state->menu_nums[index]);
        SzBattle_Entry(0, 0);
        func_001E3850_b(0, 0, 0);
        SzBattle_Entry(1, 256);
        func_001E3850_b(1, 0, 0);
        break;
    }
    case 6: {
        SzData_SetRoseFlag(0);
        func_002009E0_b(11, 0);
        func_002009E0_b(4, 1);
        SzDuel_InitBuildDeck(state->menu_nums[index]);
        break;
    }
    case 7: {
        SzModel_LoadMerge(4, 1, 0);
        if (state->byte_21e == -1)
            SzDuel_Init3DView(state->menu_nums[index]);
        SzDuel_Init3DView(-1);
        break;
    }
    case 8: {
        SzData_SetRoseFlag(0);
        func_002009E0_b(11, 0);
        SzDuel_InitTrade();
        break;
    }
    case 9: {
        SzData_SetRoseFlag(0);
        func_002009E0_b(11, 0);
        func_001C5D70_1a8db0(state->menu_nums[index]);
        break;
    }
    case 36: {
        func_002009E0_b(11, 0);
        lSzGame_InitMemCheck();
        break;
    }
    case 10: {
        func_002009E0_b(11, 0);
        func_002009E0_b(15, 0);
        if (func_00197548_1a8db0(D_002BE80F_b) != 0 && state->menu_nums[index] == 0) {
            int selected = D_00317250_1a8db0.byte_230;
            char *directory = func_001FFF90_b(D_002BE80F_b);
            func_0019B648(path, D_002BE809_b, directory, D_0028FF10_b[selected]);
            SzGame_PlayMovie(path, 1, 1);
            D_00317250_1a8db0.byte_230 =
                (D_00317250_1a8db0.byte_230 + 1) % 2;
        }
        lSzGame_InitTitle(state->menu_nums[index]);
        SzModel_LoadMerge(5, 3, 1);
        func_00217590_b(0, 0, 0);
        break;
    }
    case 11: {
        SzData_SetRoseFlag(0);
        D_00317250_1a8db0.menu_nums[28] = 3;
        D_00317250_1a8db0.menu_nums[29] = 3;
        func_002009E0_b(11, 0);
        func_002009E0_b(16, 0);
        func_002009E0_b(13, 0);
        func_002009E0_b(14, 0);
        func_002009E0_b(5, 1);
        SzDuel_Initialize();
        SzDuel_AddUnit(0, 3, 6, 0, 1);
        func_001E1E70_b(0, 0, 4, 1);
        func_001E1D70_b(0, 0, 0, 255);
        func_001E1C10_b(0, 0, 1, 0);
        SzEvent_Init(2);
        TkCamp_Init(state->menu_nums[index]);
        ShFace_Init(0);
        break;
    }
    case 12: {
        SzModel_LoadMerge(3, state->menu_nums[index], 0);
        SzEvent_Init(state->menu_nums[index]);
        break;
    }
    case 13: {
        SzModel_LoadMerge(6, 0, 0);
        SzModel_LoadMerge(0, 0, 0);
        SzDuel_InitMapEdit(state->menu_nums[index]);
        break;
    }
    case 14: {
        func_002009E0_b(13, 0);
        ShFace_Init(1);
        break;
    }
    case 15: {
        func_002009E0_b(11, 0);
        func_002009E0_b(12, 0);
        func_002009E0_b(17, 0);
        if (state->menu_nums[index] != 0)
            func_002009E0_b(0, 0);
        ShSlot_Init(state->menu_nums[index]);
        state->menu_nums[index] = 0;
        break;
    }
    case 18: {
        func_002009E0_b(11, 0);
        func_002009E0_b(0, 0);
        break;
    }
    case 19: {
        SzModel_LoadMerge(1, 0, 0);
        SzModel_LoadMerge(2, state->menu_nums[5], 0);
        func_002051C0_b(0);
        value_0 = SzData_GetCurrentDeck(0);
        value_1 = SzData_GetCurrentDeck(1);
        result_0 = SzData_GetLeader(0, value_0);
        result_1 = SzData_GetLeader(1, value_1);
        if (result_0 == 999)
            result_0 = 0;
        if (result_1 == 999)
            result_1 = 0;
        SzDuel_Initialize();
        SzDuel_AddUnit(0, 3, 6, result_0, 1);
        SzDuel_AddUnit(1, 3, 0, result_1, 1);
        SzBattle_Init(state->menu_nums[5]);
        SzBattle_Entry(0, 0);
        func_001E3850_b(0, 0, 0);
        SzBattle_Entry(1, 256);
        func_001E3850_b(1, 0, 0);
        func_001FC9B0_b(state->menu_nums[index]);
        break;
    }
    default:
        break;
    }
}

typedef struct Flags_001A9800 {
    u8 unused:4;
    u8 state:2;
    u8 unused2:2;
} Flags_001A9800;

extern Flags_001A9800 D_0031747C;

typedef struct Xyzf_001A9590 {
    u64 x:16;
    u64 y:16;
    u64 z:24;
    u64 f:8;
} Xyzf_001A9590;

typedef struct Sprite_001A9590 {
    s16 kind;
    s16 count;
    s32 unk4;
    s64 prim;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    f32 q;
    Xyzf_001A9590 v[2];
} Sprite_001A9590;


#pragma conditional_move off
#pragma opt_propagation off

void SzGame_ModeDraw(void) {
    u8 *data = (u8 *)&D_00317250;
    s64 temp_v0;
    Sprite_001A9590 sprite;
    Sprite_001A9590 *s;

    temp_v0 = SzGame_GetMode(1);
    if (D_0031747C.state < 3) {
        switch (data[0x228]) {
        case 0:
        switch (temp_v0) {
        case -1:
            SzGame_DrawMenu();
            break;
        case 1:
            SzDuel_DrawWindow();
            break;
        case 6:
            SzDuel_DrawBuildDeck();
            break;
        case 7:
            SzDuel_Draw3DView();
            break;
        case 8:
            SzDuel_DrawTrade();
            break;
        case 9:
            SzDuel_DrawCustomDuel();
            break;
        case 10:
            lSzGame_DrawTitle();
            break;
        case 11:
            ExDitherMatrixEz(1);
            TkCamp_Draw();
            break;
        case 12:
            ExDitherMatrixEz(1);
            SzEvent_Draw();
            break;
        case 13:
            SzDuel_DrawMapEdit();
            break;
        case 18:
            SzDuel_DrawCardTest();
            break;
        case 14:
            ShFace_Draw();
            break;
        case 15:
            ShSlot_Draw();
            break;
        case 17:
            (s = &sprite)->count = 6;
            s->kind = 3;
            s->prim = 0x441;
            s->unk4 = 0;
            sprite.r = data[0x20E];
            sprite.g = data[0x20D];
            sprite.b = data[0x20C];
            sprite.a = data[0x20F];
            sprite.q = 1.0f;
            sprite.v[0].x = 0x6BF8;
            sprite.v[0].y = 0x71F8;
            sprite.v[0].z = 0xFFFFF8;
            sprite.v[0].f = 0;
            sprite.v[1].x = 0x93F8;
            sprite.v[1].y = 0x8DF8;
            sprite.v[1].z = 0xFFFFF8;
            sprite.v[1].f = 0;
            ExSortPrim((s32)s, 0, 0);
            if (*(void **)(data + 0x208) != NULL) {
                lSzGame_TEXTURE_TEST(*(void **)(data + 0x208), 0, 0, 0);
            }
            if (*(void **)(data + 0x204) != NULL) {
                lSzGame_TEXTURE_TEST(*(void **)(data + 0x204), *(s32 *)(data + 0x214), *(s32 *)(data + 0x218),
                              ((struct { s8 b0:1; s8 rest:7; } *)(data + 0x22F))->b0);
            }
            break;
        }
            break;
        }
    }
}
#pragma opt_propagation reset
#pragma conditional_move reset


void SzGame_ModeDrawAfter(void) {
    u8 *data = (u8 *) &D_00317250;
    s64 temp_v0;

    temp_v0 = SzGame_GetMode(1);
    if (D_0031747C.state < 3) {
        switch (data[0x228]) {
        default:
            return;
        case 0:
            switch (temp_v0) {
            case 1:
                SzDuel_DrawJoinFade();
                SzDuel_DrawJoinCard();
                break;
            case 11:
                ExDitherMatrixEz(2);
                TkCamp_Draw_After();
                ShFace_Draw();
                break;
            }
            SzDuel_DrawDialog();
            break;
        }
    }
}

typedef int DotrDrawWord;
struct DotrCursorPacketHeader {
    unsigned short unknown_00;
    unsigned short unknown_02;
    int unknown_04;
    long unknown_08;
};
long func_00208D00_b(int index);
int func_002086D0_b(struct DotrCursorPacketHeader *packet, long value);
DotrDrawWord func_00207650_b(DotrDrawWord cursor, void *packet, int a1, int a2);
struct DotrCursorTex {
    long word;
};
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
struct DotrCursorSlotRectVertex {
    long uv;
    struct DotrCursorSlotXyz xyz;
};
struct DotrModeLastView {
    unsigned char unknown_000[12];
    unsigned int counter;
    unsigned char unknown_010[0x218];
    unsigned char busy;
    unsigned char alpha;
    unsigned char unknown_22a[2];
    signed char unknown_bits_0_1 : 2;
    signed char step : 2;
    unsigned char mode : 2;
    unsigned char unknown_22d;
    signed char unknown_22e_bits : 4;
    signed char enabled : 1;
};
struct DotrModeLastPacket {
    long header[2];
    unsigned char colour[4];
    float unknown_14;
    struct DotrCursorSlotRectVertex vertex[2];
    long unknown_38;
    struct DotrCursorTex tex0;
    struct DotrCursorTex tex1;
    long unknown_50;
};
struct DotrModeLastColour {
    unsigned char b[4];
};
extern struct DotrModeLastView D_00317250_1a98b0;
extern struct DotrModeLastView D_00317250_1a98b0;
extern struct DotrModeLastColour D_0028FF20;
extern char D_002BE815[];
extern int func_001AAF60_b(int a);
extern int *func_001AF140_b(int index);
static inline DotrDrawWord Cells(DotrDrawWord cursor, struct DotrModeLastPacket *packet, int *first, int end)
{
    int i;
    for (i = *first; i < end; i++) {
        int cy;
        int row;
        int cx;
        cx = i % 35 * 18 + 5;
        row = i / 35;
        cy = row * 24 + 4;
        if (row >= 8) {
            cy += 48;
        }
        packet->vertex[0].xyz.x = (cx + 1728) << 4;
        packet->vertex[0].xyz.y = (cy + 1824) << 4;
        packet->vertex[1].xyz.x = (cx + 1746) << 4;
        packet->vertex[1].xyz.y = (cy + 1848) << 4;
        cursor = func_00207650_b(cursor, packet, 0, 0);
    }
    *first = i;
    return cursor;
}

void SzGame_ModeDrawLast(void)
{
    struct DotrModeLastView *view = &D_00317250_1a98b0;
    struct DotrModeLastColour colour;
    int page;
    unsigned int count;
    struct DotrModeLastPacket packet;
    int n;
    int *texture;
    int x;
    int a;
    int y;
    int i;
    DotrDrawWord cursor;
    const char *text;
    unsigned char alpha;

    func_001AAF60_b(1);
    if (D_00317250_1a98b0.mode < 3 && view->busy == 0) {
        return;
    }
    if (view->enabled) {
        cursor = SzDuel_StartWindowSessionWithPalette_Pipe(RhBase_GetVifPacketArea(), 0);
        SzDuel_SetWindowDefPrioZ(0xffffff);
        texture = func_001AF140_b(6);
        if (texture) {
            count = view->counter;
            page = count / 560 % 5;
            n = count % 560;
            x = (page < 3 ? 200 : 80) + page % 3 * 18;
            y = page < 3 ? 136 : 128;
            text = D_002BE815;
            alpha = view->busy ? view->busy : (count < 128 ? count : 128);
            colour = D_0028FF20;
            a = view->alpha + 64;
            a = a < 128 ? a : 128;
            colour.b[3] = (alpha * a) >> 7;
            ((struct DotrCursorPacketHeader *)packet.header)->unknown_02 = 38;
            ((struct DotrCursorPacketHeader *)packet.header)->unknown_00 = 5;
            ((struct DotrCursorPacketHeader *)packet.header)->unknown_08 = 0x42421;
            ((struct DotrCursorPacketHeader *)packet.header)->unknown_04 = 0;
            ((struct DotrCursorPacketHeader *)packet.header)->unknown_02 |= 0x800;
            ExAssignTexture((struct DotrCursorPacketHeader *)packet.header, texture, 0);
            func_002086D0_b((struct DotrCursorPacketHeader *)packet.header, func_00208D00_b(0));
            ((struct DotrCursorSlotUv *)&packet.vertex[0].uv)->u = (x << 4) + 8;
            ((struct DotrCursorSlotUv *)&packet.vertex[0].uv)->v = (y << 4) + 8;
            ((struct DotrCursorSlotUv *)&packet.vertex[1].uv)->u = ((x + 18) << 4) + 8;
            ((struct DotrCursorSlotUv *)&packet.vertex[1].uv)->v = ((y + 24) << 4) + 8;
            packet.colour[0] = 128;
            packet.colour[1] = 128;
            packet.colour[2] = 128;
            packet.colour[3] = alpha;
            packet.unknown_14 = 1.0f;
            packet.vertex[0].xyz.z = 0xffffff;
            packet.vertex[0].xyz.f = 0;
            packet.vertex[1].xyz.z = 0xffffff;
            packet.vertex[1].xyz.f = 0;
            i = 0;
            cursor = Cells(cursor, &packet, &i, n);
            if ((unsigned int)n < view->counter) {
                page = (page + 4) % 5;
                x = (page < 3 ? 200 : 80) + page % 3 * 18;
                y = page < 3 ? 136 : 128;
                ((struct DotrCursorSlotUv *)&packet.vertex[0].uv)->u = (x << 4) + 8;
                ((struct DotrCursorSlotUv *)&packet.vertex[0].uv)->v = (y << 4) + 8;
                ((struct DotrCursorSlotUv *)&packet.vertex[1].uv)->u = ((x + 18) << 4) + 8;
                ((struct DotrCursorSlotUv *)&packet.vertex[1].uv)->v = ((y + 24) << 4) + 8;
                cursor = Cells(cursor, &packet, &i, 560);
            }
            cursor = SzDuel_DrawWindow_Font_Pipe(cursor, 320, 212, 2, 3, func_0019BEF0(text), text, colour.b);
            view->alpha += view->step * 4;
            if (view->alpha <= 0 || view->alpha >= 128) {
                view->step = -view->step;
            }
            if (view->busy) {
                view->busy -= 4;
            }
            view->counter++;
        }
        RhBase_SetVifPacketArea(ExSortSoftFocus_Pipe(SzDuel_FinishWindowSession_Pipe(cursor), 0, 0, 0, 0, 12, 0));
        

        return;
    }
}

typedef struct {
    u16 loops;
    u16 primitive;
    u32 flags;
    u64 registers;
} Tag_001A9F50;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001A9F50;

typedef struct {
    Tag_001A9F50 tag;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    Vertex_001A9F50 xyz0;
    f32 s1, t1;
    Vertex_001A9F50 xyz1;
    u64 extra[4];
} Sprite_001A9F50;

void lSzGame_TEXTURE_TEST(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Sprite_001A9F50 sprite __attribute__((aligned(8)));
    s32 centerX;
    s32 centerY;
    s32 halfWidth;
    s32 halfHeight;
    u16 width;
    u16 height;
    s32 texture;
    u16 textureWidth;
    u16 textureHeight;
    extern s32 SzText_InitClutManage();

    width = *(u16 *)((u8 *)arg0 + 0x54);
    height = *(u16 *)((u8 *)arg0 + 0x56);
    centerX = arg1 + 0x800;
    centerY = arg2 + 0x800;
    halfWidth = width >> 1;
    halfHeight = height >> 1;
    if (arg3 != 0) {
        halfWidth *= 2;
        halfHeight *= 2;
    }
    ExFlushTexture();
    texture = RhBase_GetUserGsAddress();
    texture += SzText_InitClutManage(texture, 1);
    SzText_Load((s32)arg0, texture, 0);
    ExFlushTexture();
    ((Tag_001A9F50 *)&sprite.tag)->primitive = 0x26;
    ((Tag_001A9F50 *)&sprite.tag)->loops = 5;
    ((Tag_001A9F50 *)&sprite.tag)->registers = 0x42421;
    ((Tag_001A9F50 *)&sprite.tag)->flags = 0;
    ExAssignAlpha(&sprite, ExGetAlphaVal(0));
    ExAssignTexture(&sprite, arg0, 0);
    sprite.r = 0x80;
    sprite.g = 0x80;
    sprite.b = 0x80;
    sprite.a = 0x80;
    sprite.q = 1.0f;
    textureWidth = 0x10;
    textureHeight = 0x10;
    while (width > textureWidth) {
        textureWidth <<= 1;
    }
    while (height > textureHeight) {
        textureHeight <<= 1;
    }
    sprite.s0 = 0.0f;
    sprite.t0 = 0.0f;
    sprite.s1 = (f32)width / (f32)textureWidth;
    sprite.t1 = (f32)height / (f32)textureHeight;
    sprite.xyz0.x = ((centerX - halfWidth) << 4) - 8;
    sprite.xyz0.y = ((centerY - halfHeight) << 4) - 8;
    sprite.xyz0.z = 0xFFFFF8;
    sprite.xyz0.fog = 0;
    sprite.xyz1.x = ((centerX + halfWidth) << 4) - 8;
    sprite.xyz1.y = ((centerY + halfHeight) << 4) - 8;
    sprite.xyz1.z = 0xFFFFF8;
    sprite.xyz1.fog = 0;
    ExSortPrim((s32)&sprite, 0, 0);
}

typedef struct {
    u8 unused0 : 4;
    u8 mode : 2;
    u8 unused6 : 2;
} Mode_001AA260;

typedef struct {
    s8 unused0 : 4;
    s8 pending : 1;
    s8 busy : 1;
    s8 unused6 : 2;
} Flags_001AA260;

typedef struct {
    s8 enabled : 1;
    s8 unused1 : 7;
} Toggle_001AA260;

typedef struct {
    u8 pad000[0xC];
    s32 field00C;
    u8 pad010[0x180];
    s32 field190;
    u8 pad194[0x5C];
    s8 entries[0x1C];
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 pad210[4];
    s32 x;
    s32 y;
    u8 pad21C[3];
    s8 selection;
    s8 entry;
    s8 field221;
    u8 index;
    u8 pad223[5];
    u8 wait;
    u8 pad229[3];
    Mode_001AA260 mode;
    u8 pad22D;
    Flags_001AA260 flags;
    Toggle_001AA260 toggle;
} State_001AA260;

extern u8 D_00317472;

s32 SzDuel_Act(void);
void func_00237730(void);

void SzGame_ModeAct(void) {
    extern void SzGame_ReqBGM();
    State_001AA260 *state;
    s64 event;
    s32 i;
    s32 position;
    s32 j0;
    s32 j5;
    s32 j12;
    s32 step;

    state = (State_001AA260 *)&D_00317250;
    event = SzGame_GetMode(0);
    switch (D_0031747C.state) {
    case 3:
        if (SzFile_InqRequestEx() != 0) {
            return;
        }
        if (state->field190 != 0) {
            SzGame_ReqBGM(event, 1);
        }
        if (state->flags.pending != 0) {
            state->wait = 0x80;
        }
        state->mode.mode--;
        return;
    case 2:
        if (((D_0031747E.enabled != 0 ? 1 : 0) != 0) && (SzSound_IsLoadingBGM() != 0)) {
            return;
        }
        switch (event) {
        case 1:
            SzText_LoadMerge(4, 1);
            SzText_LoadMerge(1, 0);
            SzText_LoadMerge(2, 0);
            SzText_LoadMerge(3, 0);
            break;
        case 6:
        case 8:
            SzText_LoadMerge(0, 0);
            break;
        }
        state->mode.mode--;
        return;
    case 1:
        if (state->wait != 0) {
            return;
        }
        SzFade_SetPauseFlag(1, 0);
        state->field00C = 0;
        break;
    }

    if (SzSound_IsStandby() != 0) {
        for (i = 0; i < 2; i++) {
            position = SzBattle_InqEntry(i);
            if (position < 0) {
                continue;
            }
            SzModel_ReqSE(i + 2, SzDuel_GetUnitModelID(position >> 8, position & 0xFF));
        }
        SzEffect_ReqSE();
    }
    i = 0;
    do {
        SzModel_Motion(i);
        i++;
    } while (i < 0x54);
    SzEffect_TrimModule();
    if (SzFade_IsDoing(1) != 0) {
        return;
    }
    switch (event) {
    case -3:
        break;
    case -2:
    case -1:
        SzGame_ActMenu();
        break;
    case 0:
        SzDebug_Act();
        if (SzDebug_IsEffect() == 0) {
            j0 = 0;
            do {
                SzModel_Act(j0);
                j0++;
            } while (j0 < 0x54);
        }
        SzView_Act(0);
        break;
    case 1:
        do {
        } while (SzDuel_Act() != 0);
        break;
    case 5:
        SzDebug_Act();
        if (SzDebug_IsEffect() == 0) {
            j5 = 0;
            do {
                SzModel_Act(j5);
                j5++;
            } while (j5 < 0x54);
        }
        SzView_Act(0);
        break;
    case 6:
        SzDuel_ActBuildDeck();
        break;
    case 7:
        SzDuel_Act3DView();
        break;
    case 8:
        SzDuel_ActTrade();
        break;
    case 9:
        SzDuel_ActCustomDuel();
        break;
    case 36:
        lSzGame_ActMemCheck();
        break;
    case 10:
        lSzGame_ActTitle();
        break;
    case 11:
        func_00237730();
        ShFace_Act();
        break;
    case 12:
        SzDebug_Act();
        if (SzDebug_IsEffect() == 0) {
            j12 = 0;
            do {
                SzModel_Act(j12);
                j12++;
            } while (j12 < 0x54);
        }
        SzView_Act(0);
        break;
    case 13:
        SzDuel_ActMapEdit();
        break;
    case 18:
        SzDuel_ActCardTest();
        break;
    case 19:
        SzView_ActCamera();
        SzView_Act(0);
        break;
    case 14:
        ShFace_Act();
        break;
    case 15:
        ShSlot_Act();
        break;
    case 17:
        step = 1;
        if (SzPad_Check(0, 0, 0x10) != 0) {
            state->toggle.enabled = (s8)(state->toggle.enabled != 0 ? 0 : 1);
        }
        if (SzPad_Check(0, 1, 0x20) != 0) {
            step = 2;
        }
        if (SzPad_Check(0, 1, 0x80) != 0) {
            step = 2;
        }
        if (SzPad_Check(0, 1, 0xF000) != 0) {
            if (SzPad_Check(0, 1, 0x8000) != 0) {
                state->x -= step;
            }
            if (SzPad_Check(0, 1, 0x2000) != 0) {
                state->x += step;
            }
            if (SzPad_Check(0, 1, 0x1000) != 0) {
                state->y -= step;
            }
            if (SzPad_Check(0, 1, 0x4000) != 0) {
                state->y += step;
            }
        }
        if (SzPad_Check(1, 1, 0x1000) != 0) {
            if (SzPad_Check(1, 2, 0x80) != 0) {
                if (state->alpha > 0) {
                    state->alpha--;
                }
            }
            if (SzPad_Check(1, 2, 0x20) != 0) {
                if (state->alpha < 0xFF) {
                    state->alpha++;
                }
            }
        } else {
            if (SzPad_Check(1, 2, 0x81) != 0) {
                if (state->blue > 0) {
                    state->blue--;
                }
            }
            if (SzPad_Check(1, 2, 0x22) != 0) {
                if (state->blue < 0xFF) {
                    state->blue++;
                }
            }
            if (SzPad_Check(1, 2, 0x41) != 0) {
                if (state->green > 0) {
                    state->green--;
                }
            }
            if (SzPad_Check(1, 2, 0x12) != 0) {
                if (state->green < 0xFF) {
                    state->green++;
                }
            }
            if (SzPad_Check(1, 2, 5) != 0) {
                if (state->red > 0) {
                    state->red--;
                }
            }
            if (SzPad_Check(1, 2, 10) != 0) {
                if (state->red < 0xFF) {
                    state->red++;
                }
            }
        }
        if (SzPad_Check(0, 0, 0x20) != 0) {
            state = (State_001AA260 *)&D_00317250;
            if ((D_00317472 - 1) >= 0) {
                SzFade_Entry(0, 1, 1, 0, 0x3C, 0);
                state->selection = -2;
                state->entry = state->entries[state->index];
                state->field221 = -1;
                if (state->entries[state->index + 1] < 2) {
                    SzGame_ReqBGM(-2, 1);
                }
            }
        }
        break;
    }
}

/* From the dotr-decomp CC0 bundle (commit 88c32bb2), chatC/imp/conv.py. */

struct DotrBgmGame {
    unsigned char unknown_000[316];
    int stage;
    int flag;
    unsigned char unknown_144[8];
    int place;
};
extern struct DotrBgmGame D_00317250_1aaaf0;
extern int func_00217A10_b(int n);

void SzGame_ReqBGM(int n, int b)
{
    int stage;
    int flag;
    int bgm;
    struct DotrBgmGame *g;

    g = &D_00317250_1aaaf0;
    switch (n % 1000) {
    case -2:
    case -1:
        func_00217A10_b(256);
        return;
    case 0:
        SzSound_PlayBGM(7, b);
        break;
    case 1:
        stage = g->stage;
        flag = g->flag;
        switch (stage) {
        case 0:
            stage = 7;
            break;
        case 1:
            stage = 10;
            break;
        case 19:
            stage = 11;
            break;
        case 20:
            stage = 12;
            break;
        case 21:
            stage = 44;
            break;
        default:
            if (stage < 22) {
                if (flag) {
                    stage = 9;
                } else {
                    stage = 8;
                }
            } else {
                stage = 40;
            }
            break;
        }
        if (stage >= 0) {
            stage = n / 1000 * 1000 + stage;
            SzSound_PlayBGM(stage, b);
        }
        break;
    case 2:
    case 3:
    case 4:
        break;
    case 5:
        bgm = -1;
        switch (g->place) {
        case 7:
            bgm = 13;
            break;
        case 3:
            bgm = 14;
            break;
        case 2:
            bgm = 15;
            break;
        case 4:
            bgm = 16;
            break;
        case 0:
            bgm = 17;
            break;
        case 1:
            bgm = 18;
            break;
        case 9:
            bgm = 19;
            break;
        case 5:
            bgm = 20;
            break;
        case 6:
            bgm = 21;
            break;
        case 8:
            bgm = 22;
            break;
        }
        if (bgm >= 0) {
            SzSound_PlayBGM(bgm, b);
        }
        break;
    case 6:
        SzSound_PlayBGM(5, b);
        break;
    case 7:
        SzSound_PlayBGM(5, b);
        break;
    case 8:
        SzSound_PlayBGM(41, b);
        break;
    case 9:
        SzSound_PlayBGM(3, b);
        break;
    case 10:
        SzSound_PlayBGM(2, b);
        break;
    case 11:
    case 12:
    case 13:
    case 14:
        break;
    case 15:
        SzSound_PlayBGM(21, b);
        break;
    }
}

void SzGame_ModeTerm(s32 arg0) {
    extern void func_001C5D70(s32);
    s8 *data = (s8 *)&D_00317250;

    switch (arg0) {
    case 1:
        SzDuel_Term();
        if (data[0x21F] == 9) {
            func_001C5D70(-1);
        }
        break;
    case 5:
        SzBattle_Term();
        break;
    case 6:
        SzDuel_TermBuildDeck();
        if (data[0x21F] == 9) {
            func_001C5D70(-1);
        }
        break;
    case 7:
        SzDuel_Term3DView();
        break;
    case 8:
        SzDuel_TermTrade();
        break;
    case 9:
        SzDuel_TermCustomDuel();
        break;
    case 0x24:
        lSzGame_TermMemCheck();
        break;
    case 0xA:
        lSzGame_TermTitle();
        break;
    case 0xB:
        TkCamp_Term();
        ShFace_Term();
        break;
    case 0xC:
        SzEvent_Term();
        break;
    case 0xD:
        SzDuel_TermMapEdit();
        break;
    case 0xE:
        ShFace_Term();
        break;
    case 0xF:
        ShSlot_Term();
        if (data[0x21F] == 9) {
            func_001C5D70(-1);
        }
        break;
    case 0x13:
        SzBattle_Term();
        SzView_TermCamera();
        break;
    }
}

typedef struct {
    u8 pad[0x1F1];
    s8 values[0x2D];
    s8 negative;
    s8 zero;
    u8 pad220[2];
    u8 selected;
} State_001AAF60;

s64 SzGame_GetMode(s32 arg0) {
    s8 value;
    State_001AAF60 *state = (State_001AAF60 *)&D_00317250;

    if (arg0 > 0) {
        value = state->values[state->selected];
    } else if (arg0 < 0) {
        value = state->negative;
    } else {
        value = state->zero;
    }
    return value;
}

typedef struct Flags2D_001AAFA0 {
    u8 first : 3;
    u8 second : 3;
    u8 high : 2;
} Flags2D_001AAFA0;

typedef struct Flags2E_001AAFA0 {
    u8 value : 3;
    u8 bit3 : 1;
    u8 high : 4;
} Flags2E_001AAFA0;

void SzGame_InitMemCardProc(s32 arg0) {
    extern char D_002BE7D0[];
    extern char D_002BE821[];
    s8 *data = (s8 *)&D_00317250;

    switch (arg0) {
    case 0:
        TkMc_Load_Main(1);
        ((Flags2E_001AAFA0 *)(data + 0x22E))->value = 2;
        break;
    case 1: {
        u8 path[128];

        func_0019B648(path, D_002BE821, (s32)SzFile_GetEnv((s32)D_002BE7D0));
        SzFile_ReadRequestParam(0, 0, (s32)path, 0x01E301E0, -1, 0, -1, 0, 0);
        ((Flags2E_001AAFA0 *)(data + 0x22E))->value = 1;
        break;
    }
    case 2: {
        u8 path[128];

        func_0019B648(path, D_002BE821, (s32)SzFile_GetEnv((s32)D_002BE7D0));
        SzFile_ReadRequestParam(0, 0, (s32)path, 0x01E301E0, -1, 0, -1, 0, 0);
        ((Flags2E_001AAFA0 *)(data + 0x22E))->value = 1;
        break;
    }
    case 3:
        TkMc_Custom_Main(1);
        ((Flags2E_001AAFA0 *)(data + 0x22E))->value = 1;
        break;
    case 4:
        TkMc_Trade_Load_Main(1);
        ((Flags2E_001AAFA0 *)(data + 0x22E))->value = 1;
        break;
    case 5:
        TkMc_Trade_Save_Main(1);
        ((Flags2E_001AAFA0 *)(data + 0x22E))->value = 1;
        break;
    case 6:
        TkMc_Check_Main(1);
        ((Flags2E_001AAFA0 *)(data + 0x22E))->value = 1;
        break;
    }
    *(s16 *)(data + 0x21C) = 0;
    ((Flags2D_001AAFA0 *)(data + 0x22D))->second = arg0;
    ((Flags2E_001AAFA0 *)(data + 0x22E))->bit3 = (arg0 == 2) ? 1 : 0;
}

typedef struct Flags2D_001AB1D0 {
    u8 first : 3;
    u8 second : 3;
    u8 high : 2;
} Flags2D_001AB1D0;

typedef struct Flags2E_001AB1D0 {
    u8 value : 3;
    u8 bit3 : 1;
    u8 high : 4;
} Flags2E_001AB1D0;

extern u8 D_0031747D;

#define F2D ((Flags2D_001AB1D0 *)(data + 0x22D))
#define F2E ((Flags2E_001AB1D0 *)(data + 0x22E))
#define RESULT (*(s32 *)(data + 0x210))
#define CODE (*(u16 *)(data + 0x21C))

s32 SzGame_ActMemCardProc(void) {
    s8 *data = (s8 *)&D_00317250;
    s32 prev;
    s32 cancel;
    s32 cmd;
    s32 res;
    s32 old;
    s32 mode;

    if (((&D_0031747D)[1] & 7)) {
        cmd = 5;
        cancel = 0;
        res = 0;
        prev = F2E->value;
        if (SzFile_InqRequestEx() != 0) {
            return 0;
        }
        mode = F2D->second;
        switch (mode) {
        case 0:
            switch (F2E->value) {
            case 1:
                F2E->value = 2;
            case 2:
            case 3:
            case 4:
                CODE = TkMc_Load_Main(F2E->value - 2);
                res = lSzGame_GetMCardMsg(F2D->second, CODE, &RESULT);
                F2E->value = 2;
                switch (CODE & 0xFF00) {
                case 0:
                    if (res != 0 && SzPad_Check(0, 0, 0xF0) != 0) {
                        SzSound_PlaySE(0, 4);
                        F2E->value = 0;
                        RESULT = -1;
                        cancel = 1;
                    }
                    break;
                case 0x100:
                    F2E->value = 5;
                    break;
                case 0x700:
                    F2E->bit3 = 0;
                    F2E->value = 3;
                    break;
                }
                break;
            case 5:
                res = 1;
                if (SzPad_Check(0, 0, 0xF0) != 0) {
                    SzSound_PlaySE(0, 4);
                    F2E->value = 0;
                    RESULT = -1;
                }
                break;
            }
            break;
        case 1:
        case 2:
            switch (F2E->value) {
            case 1:
                if (mode == 1) {
                    TkMc_Save_Main(1);
                    F2E->value = 2;
                    break;
                }
                res = 2;
                RESULT = 0x9C9;
                if (SzPad_Check(0, 0, 0xA000) != 0) {
                    old = F2E->bit3;
                    if (SzPad_Check(0, 0, 0x8000) != 0) {
                        F2E->bit3 = 1;
                    } else {
                        F2E->bit3 = 0;
                    }
                    if (F2E->bit3 != old) {
                        SzSound_PlaySE(0, 3);
                    }
                } else if (SzPad_Check(0, 0, 0xC0) != 0) {
                    SzSound_PlaySE(0, 4);
                    if (F2E->bit3) {
                        TkMc_Save_Main(1);
                        F2E->value = 2;
                    } else {
                        F2E->value = 0;
                        RESULT = -1;
                        cancel = 1;
                    }
                } else if (SzPad_Check(0, 0, 0x20) != 0) {
                    SzSound_PlaySE(0, 5);
                    F2E->value = 0;
                    RESULT = -1;
                    cancel = 1;
                }
                break;
            case 2:
            case 3:
            case 4:
                CODE = TkMc_Save_Main(F2E->value - 2);
                res = lSzGame_GetMCardMsg(F2D->second, CODE, &RESULT);
                F2E->value = 2;
                switch (CODE & 0xFF00) {
                case 0:
                    if (res == 0) {
                    } else if (res == 2) {
                        if (SzPad_Check(0, 0, 0xA000) != 0) {
                            old = F2E->bit3;
                            if (SzPad_Check(0, 0, 0x8000) != 0) {
                                F2E->bit3 = 1;
                            } else {
                                F2E->bit3 = 0;
                            }
                            if (F2E->bit3 != old) {
                                SzSound_PlaySE(0, 3);
                            }
                        } else if (SzPad_Check(0, 0, 0xC0) != 0) {
                            SzSound_PlaySE(0, 4);
                            if (F2E->bit3) {
                                F2E->value = 4;
                            } else if (F2D->second == 1) {
                                cancel = 1;
                                F2E->value = 0;
                                RESULT = -1;
                            } else {
                                prev = F2E->value = 1;
                                F2E->bit3 = 1;
                            }
                        } else if (SzPad_Check(0, 0, 0x20) != 0) {
                            SzSound_PlaySE(0, 5);
                            if (F2D->second == 1) {
                                cancel = 1;
                                F2E->value = 0;
                                RESULT = -1;
                            } else {
                                prev = F2E->value = 1;
                                F2E->bit3 = 1;
                            }
                        }
                    } else if (res == 3) {
                        if (SzPad_Check(0, 0, 0xF0) != 0) {
                            SzSound_PlaySE(0, 4);
                            F2E->value = 4;
                        }
                    } else {
                        if (SzPad_Check(0, 0, 0xF0) != 0) {
                            SzSound_PlaySE(0, 4);
                            if (F2D->second == 1) {
                                cancel = 1;
                                F2E->value = 0;
                                RESULT = -1;
                            } else {
                                prev = F2E->value = 1;
                                F2E->bit3 = 1;
                            }
                        }
                    }
                    break;
                case 0x100:
                    F2E->value = 5;
                    break;
                case 0x700:
                    F2E->bit3 = 0;
                    F2E->value = 3;
                    break;
                }
                break;
            case 5:
                res = 1;
                if (SzPad_Check(0, 0, 0xF0) != 0) {
                    SzSound_PlaySE(0, 4);
                    F2E->value = 0;
                    RESULT = -1;
                }
                break;
            }
            break;
        case 3:
            switch (F2E->value) {
            case 1:
                F2E->value = 2;
            case 2:
            case 3:
            case 4:
                CODE = TkMc_Custom_Main(F2E->value - 2);
                res = lSzGame_GetMCardMsg(F2D->second, CODE, &RESULT);
                F2E->value = 2;
                switch (CODE & 0xFF00) {
                case 0:
                    if (res != 0 && SzPad_Check(0, 0, 0xF0) != 0) {
                        SzSound_PlaySE(0, 4);
                        F2E->value = 0;
                        RESULT = -1;
                        cancel = 1;
                    }
                    break;
                case 0x100:
                case 0x200:
                case 0x300:
                case 0x400:
                case 0x500:
                    F2E->value = 5;
                    break;
                case 0x700:
                    F2E->bit3 = 0;
                    F2E->value = 3;
                    break;
                }
                break;
            case 5:
                res = 1;
                if (SzPad_Check(0, 0, 0xF0) != 0) {
                    SzSound_PlaySE(0, 4);
                    F2E->value = 0;
                    RESULT = -1;
                }
                break;
            }
            break;
        case 4:
            switch (F2E->value) {
            case 1:
                F2E->value = 2;
            case 2:
            case 3:
            case 4:
                CODE = TkMc_Trade_Load_Main(F2E->value - 2);
                res = lSzGame_GetMCardMsg(F2D->second, CODE, &RESULT);
                F2E->value = 2;
                switch (CODE & 0xFF00) {
                case 0:
                    if (res != 0) {
                        if (SzPad_Check(0, 0, 0xF0) != 0 || SzPad_Check(1, 0, 0xF0) != 0) {
                            SzSound_PlaySE(0, 4);
                            F2E->value = 0;
                            RESULT = -1;
                            cancel = 1;
                        }
                    }
                    break;
                case 0x100:
                    F2E->value = 5;
                    break;
                case 0x700:
                    F2E->bit3 = 0;
                    F2E->value = 3;
                    break;
                }
                break;
            case 5:
                res = 1;
                if (SzPad_Check(0, 0, 0xF0) != 0 || SzPad_Check(1, 0, 0xF0) != 0) {
                    SzSound_PlaySE(0, 4);
                    F2E->value = 0;
                    RESULT = -1;
                }
                break;
            }
            break;
        case 5:
            switch (F2E->value) {
            case 1:
                F2E->value = 2;
            case 2:
            case 3:
            case 4:
                CODE = TkMc_Trade_Save_Main(F2E->value - 2);
                res = lSzGame_GetMCardMsg(F2D->second, CODE, &RESULT);
                F2E->value = 2;
                switch (CODE & 0xFF00) {
                case 0:
                    if (res != 0) {
                        res = 1;
                        if (SzPad_Check(0, 0, 0xF0) != 0 || SzPad_Check(1, 0, 0xF0) != 0) {
                            SzSound_PlaySE(0, 4);
                            F2E->value = 0;
                            RESULT = -1;
                            cancel = 1;
                        }
                    }
                    break;
                case 0x100:
                case 0x600:
                    F2E->value = 5;
                    break;
                case 0x700:
                    F2E->bit3 = 0;
                    F2E->value = 3;
                    break;
                }
                break;
            case 5:
                res = 1;
                if (SzPad_Check(0, 0, 0xF0) != 0 || SzPad_Check(1, 0, 0xF0) != 0) {
                    SzSound_PlaySE(0, 4);
                    F2E->value = 0;
                    RESULT = -1;
                }
                break;
            }
            break;
        case 6:
            switch (F2E->value) {
            case 1:
                F2E->value = 2;
            case 2:
            case 3:
            case 4:
                CODE = TkMc_Check_Main(F2E->value - 2);
                res = lSzGame_GetMCardMsg(F2D->second, CODE, &RESULT);
                if (RESULT == 0x9B2) {
                    RESULT = -1;
                }
                F2E->value = 2;
                switch (CODE & 0xFF00) {
                case 0:
                    if (res != 0 && SzPad_Check(0, 0, 0xF0) != 0) {
                        SzSound_PlaySE(0, 4);
                        F2E->value = 0;
                        RESULT = -1;
                        cancel = 1;
                    }
                    break;
                case 0x100:
                    F2E->value = 0;
                    RESULT = -1;
                    break;
                case 0x700:
                    F2E->bit3 = 0;
                    F2E->value = 3;
                    break;
                }
                break;
            }
            break;
        }
        if (RESULT < 0) {
            SzDuel_CloseMsgPopup();
            return (cancel != 0) ? 2 : 1;
        }
        switch (res) {
        case 1:
        case 3:
            cmd = 6;
            break;
        case 2:
            if (F2E->bit3) {
                RESULT |= 0x8000;
            } else {
                RESULT &= 0xFFFF7FFF;
            }
            if (F2E->value != prev) {
                F2E->bit3 = 0;
            }
            cmd = 7;
            break;
        }
        SzDuel_OpenMsgPopup(cmd, 0, 0, RESULT);
        return 0;
    }
    return -1;
}

#undef F2D
#undef F2E
#undef RESULT
#undef CODE

s32 lSzGame_GetMCardMsg(s32 arg0, s32 arg1, s32 *arg2) {
    s32 alt;
    s32 result;

    alt = (arg1 & 0x80) ? 1 : 0;
    result = 0;
    *arg2 = (alt ? 1 : 0) + 0x9B2;
    switch (arg1 & 0x7F) {
    case 1:
        *arg2 = 0x9D9;
        result = 2;
        break;
    case 2:
    case 4:
        *arg2 = (alt ? 1 : 0) + 0x9B5;
        result = 1;
        break;
    case 3:
    case 14:
        *arg2 = (alt ? 1 : 0) + 0x9CA;
        result = 2;
        break;
    case 5:
        if (arg0 == 6) {
            *arg2 = 0x9BB;
        } else {
            *arg2 = (alt ? 3 : 0) + 0x9BA;
        }
        result = 1;
        break;
    case 6:
        *arg2 = (alt ? 1 : 0) + 0x9B8;
        result = 1;
        break;
    case 7:
        *arg2 = (alt ? 2 : 0) + 0x9BF;
        result = 1;
        break;
    case 9:
        if (arg0 == 4 || arg0 == 5) {
            if (arg0 == 4) {
                *arg2 = 0x9C5;
            } else {
                *arg2 = 0x9D6;
            }
        } else if (arg0 == 0 || arg0 == 3) {
            *arg2 = (alt ? 1 : 0) + 0x9C3;
        } else {
            *arg2 = (alt ? 1 : 0) + 0x9D4;
        }
        break;
    case 8:
    case 10:
        if (arg0 == 0 || arg0 == 3 || arg0 == 4) {
            *arg2 = 0x9C7;
        } else {
            *arg2 = 0x9D8;
        }
        result = 1;
        break;
    case 11:
        *arg2 = (alt ? 1 : 0) + 0x9CE;
        break;
    case 12:
        *arg2 = (alt ? 1 : 0) + 0x9D0;
        result = 3;
        break;
    case 13:
        *arg2 = (alt ? 1 : 0) + 0x9D2;
        result = 1;
        break;
    }
    switch (arg1 & 0xFF00) {
    case 0x100:
    case 0x200:
    case 0x300:
    case 0x400:
    case 0x500:
        if (arg0 == 4) {
            *arg2 = 0x9DA;
        } else if (arg0 == 0 || arg0 == 3) {
            *arg2 = 0x9C6;
        } else {
            *arg2 = 0x9D7;
        }
        break;
    case 0x600:
        *arg2 = 0x9DB;
        break;
    }
    return result;
}

void lSzGame_InitMemCheck(void) {
    s32 i;

    i = 0;
    do {
        SzModel_SetDrawFlag(i, 0);
        i += 1;
    } while (i < 0x54);
    SzGame_InitMemCardProc(6);
}

typedef struct Block_001AC560 {
    u8 entries[0x26];
    s8 mode;
    s8 selected;
    s8 previous;
    u8 index;
} Block_001AC560;

extern s32 D_003173B0;
extern Block_001AC560 D_00317449;

void lSzGame_ActMemCheck(void) {
    if (SzGame_ActMemCardProc() < 0) {
        D_003173B0 = 0;
        SzFade_Entry(0, 1, 1, 0, 60, 0);
        D_00317449.mode = -2;
        D_00317449.selected = 10;
        D_00317449.previous = 0;
        D_00317449.entries[D_00317449.index + D_00317449.previous] = 0;
        SzGame_ReqBGM(-2, 1);
    }
}

void lSzGame_TermMemCheck(void) {

}

typedef struct State_001AC610 {
    s32 pad0[2];
    s32 counter;
    u8 padC[0x218];
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 pad228[4];
    s8 mode : 2;
    s8 pad22C : 6;
    u8 pad22D[2];
    s8 pad22F : 1;
    s8 enabled : 1;
    s8 pad22FHigh : 6;
} State_001AC610;

extern s32 D_003173B0;

void lSzGame_InitTitle(s32 arg0) {
    State_001AC610 *state = (State_001AC610 *)&D_00317250;
    s32 i;

    i = 0;
    do {
        SzModel_SetDrawFlag(i, 0);
        i += 1;
    } while (i < 0x54);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x22, 1);
        i += 1;
    } while (i < 0x28);
    if (arg0 < 2) {
        D_003173B0 = 2;
        state->red = 0;
        state->green = 0;
        state->blue = 0;
        state->alpha = 0x80;
        state->mode = 1;
        state->enabled = 1;
        state->counter = 0;
    }
}

void lSzGame_TermTitle(void) {

}

typedef unsigned int DotrMovieAddress;
struct DotrMovieOperationsStatePrefix_1ac700 {
    unsigned char unknown_000[8];
    unsigned int field_008; 
    int field_00c;
    unsigned char unknown_010[0x14c];
    int field_15c; 
    int field_160; 
    int field_164; 
    unsigned char unknown_168[0x28];
    int field_190; 
    unsigned char unknown_194[0x5d];
    signed char bytes_1f1[8];
    unsigned char bytes_1f9[8];
    unsigned char unknown_201[0xb];
    unsigned char bytes_20c[4]; 
    unsigned char unknown_210[4];
    int field_214; 
    int field_218;
    unsigned short field_21c;
    signed char field_21e;
    signed char field_21f;
    signed char field_220;
    signed char field_221;
    unsigned char field_222;
    unsigned char unknown_223;
    unsigned char field_224; 
    unsigned char field_225; 
    unsigned char field_226; 
    unsigned char field_227;
    signed char field_228;
    signed char field_229;
    unsigned char unknown_22a[2];
    struct {
        signed char unknown_0 : 2;
        signed char field_2 : 2;
        unsigned char field_4 : 2;
        signed char unknown_6 : 2;
    } field_22c;
    unsigned char unknown_22d;
    struct {
        signed char unknown_0 : 4;
        signed char field_4 : 1;
        signed char field_5 : 1;
        signed char unknown_6 : 2;
    } field_22e;
    struct {
        signed char field_0 : 1;
        signed char field_1 : 1;
    } field_22f;
};
extern void func_001FCC70_b(int, int, int, int, int, int);
extern void func_001AAAF0_1ac700(int, int);
extern struct DotrMovieOperationsStatePrefix_1ac700 D_00317250_1ac700;
extern char *func_00197548_b(const char *label);
extern char D_002BE80F_b[];
static inline void SzGame_Push_inline(int arg0, int arg1)
{
    struct DotrMovieOperationsStatePrefix_1ac700 *state = &D_00317250_1ac700;
    if (state->field_222 + 1 < 8) {
        func_001FCC70_b(0, 1, 1, 0, 60, 0);
        state->field_21f = -2;
        state->field_220 = arg0;
        state->field_221 = 1;
        ((signed char *)(state->field_221 + (state->field_222 + (DotrMovieAddress)state)))[0x1f9] = arg1;
        if (arg1 < 2)
            func_001AAAF0_1ac700(-2, 1);
    }
}

void lSzGame_ActTitle(void)
{
    struct DotrMovieOperationsStatePrefix_1ac700 *p = &D_00317250_1ac700;
    int v;

    switch (SzGame_ActMemCardProc()) {
    case 0:
    case 2:
        return;
    case 1:
        switch (p->field_225) {
        case 1:
            p->field_164 = 1;
            SzGame_Push_inline(11, 0);
            break;
        case 2:
            D_00317250_1ac700.field_15c = (p->field_21c >> 8) - 1;
            SzGame_Push_inline(9, 0);
            break;
        case 3:
            SzGame_Push_inline(8, 0);
            break;
        }
        SzSound_SetOutput(SzData_GetOption(0, 2));
        return;
    }
    if (p->field_22f.field_1) {
        if (p->field_224 >= 128) {
            p->field_227 += p->field_22c.unknown_0 * 4;
            if (p->field_227 <= 128 || p->field_227 >= 240)
                p->field_22c.unknown_0 = -p->field_22c.unknown_0;
            if (func_00197548_b(D_002BE80F_b) != 0) {
                if (++p->field_008 >= 900) {
                    D_00317250_1ac700.field_160 = 0;
                    func_001FCC70_b(0, 1, 1, 0, 60, 0);
                    D_00317250_1ac700.field_21f = -2;
                    D_00317250_1ac700.field_220 = 10;
                    D_00317250_1ac700.field_221 = 0;
                    (D_00317250_1ac700.bytes_1f9 + D_00317250_1ac700.field_222)[D_00317250_1ac700.field_221] = 0;
                    func_001AAAF0_1ac700(-2, 1);
                    return;
                }
            }
            if (SzPad_Check(0, 0, 2048)) {
                SzSound_PlaySE(0, 4);
                p->field_22f.field_1 = 0;
            }
        } else {
            if (SzSound_IsStandby() && !SzSound_IsPlaySE())
                return;
            v = p->field_224 + 4;
            v = v < 128 ? v : 128; p->field_224 = v;
        }
    } else if (p->field_226 >= 128) {
        if (SzPad_Check(0, 2, 20480)) {
            if (SzPad_Check(0, 2, 4096))
                p->field_225 = (p->field_225 + 3) % 4;
            else
                p->field_225 = (p->field_225 + 5) % 4;
            SzSound_PlaySE(0, 3);
            return;
        }
        if (SzPad_Check(0, 0, 192)) {
            SzSound_PlaySE(0, 4);
            switch (p->field_225) {
            case 0:
                p->field_164 = 0;
                SzGame_Push_inline(11, 0);
                SzData_SetOption(0, 0, 1);
                SzData_SetOption(0, 1, 1);
                SzData_SetOption(0, 2, 1);
                break;
            case 1:
                SzGame_InitMemCardProc(0);
                break;
            case 2:
                SzGame_InitMemCardProc(3);
                break;
            case 3:
                SzGame_InitMemCardProc(4);
                break;
            }
            

            return;
        }
    } else {
        v = p->field_226 + 4;
        v = v < 128 ? v : 128; p->field_226 = v;
    }
}

void lSzGame_DrawTitle(void) {
    RhBase_SetVifPacketArea(lSzGame_DrawTitle_Pipe(RhBase_GetVifPacketArea()));
}

INCLUDE_ASM("asm/nonmatchings/main_037", lSzGame_DrawTitle_Pipe);

typedef struct {
    u16 count;
    u16 flags;
    u32 padding;
    u64 registers;
} Tag_001AD670;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Color_001AD670;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_001AD670;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Vertex_001AD670;

typedef struct {
    u64 tag[2];
    Color_001AD670 color;
    u64 uv0;
    Vertex_001AD670 vertex0;
    u64 uv1;
    Vertex_001AD670 vertex1;
    u64 test;
    s64 texture0;
    s64 texture1;
    u64 clamp;
} Packet_001AD670;

typedef struct {
    u8 pad00[0x40];
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;
    u8 pad4C[4];
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    u8 pad5C[0x24];
    s32 roll;
    u8 pad84[0xC];
} View_001AD670;

static inline void set_uv_001AD670(UV_001AD670 *p, s32 u, s32 v) {
    p->u = u;
    p->v = v;
}

s32 lSzGame_DrawTitle_Rose_Pipe(s32 packet, s32 id, s32 x, s32 y, s32 width, s32 height, f32 depth) {
    extern u8 D_00317476;
    extern s32 RhBase_AssignRenderFrame(s32, s32, s32);
    View_001AD670 view;
    Packet_001AD670 sprite __attribute__((aligned(8)));

    ((Tag_001AD670 *)sprite.tag)->flags = 0x26;
    ((Tag_001AD670 *)sprite.tag)->count = 5;
    ((Tag_001AD670 *)sprite.tag)->registers = 0x42421;
    ((Tag_001AD670 *)sprite.tag)->padding = 0;
    ((Tag_001AD670 *)sprite.tag)->flags |= 0x800;
    ExAssignAlpha(sprite.tag, 0x44 | ((s64)0x80 << 32));
    sprite.color.r = 0x80;
    sprite.color.g = 0x80;
    sprite.color.b = 0x80;
    sprite.color.a = D_00317476;
    sprite.color.q = 1.0f;
    sprite.vertex0.z = 0xFFFFF8;
    sprite.vertex0.fog = 0;
    sprite.vertex1.z = 0xFFFFF8;
    sprite.vertex1.fog = 0;
    RhView_GetCurView(&view);
    if (RhView_PushStack() != 0) {
        RhBase_AssignRenderFrame(0, 2, 0x32);
        packet = (s32)RhBase_EnableRenderFrame((void *)packet);
        packet = (s32)RhBase_ClearRenderFrame((u8 *)packet, 0);
        view.eyeX = 0.0f;
        view.eyeY = 0.0f;
        view.eyeZ = -depth;
        view.targetX = 0.0f;
        view.targetY = 0.0f;
        view.targetZ = 1.0f;
        view.roll = 0;
        RhView_SetClipZ(1.0f, 512.0f);
        RhView_Modify(&view);
        packet = SzModel_DrawWithOutCalc_Pipe(RhView_SendViewParameters(packet), id, 0, 0, 0, 0, 0);
        RhBase_GetTextureInfoForRender(&sprite.texture0, &sprite.texture1);
        packet = RhText_SetTextureFlush((s32)RhBase_DisableRenderFrame((void *)packet));
        set_uv_001AD670((UV_001AD670 *)&sprite.uv0, 0, 0);
        set_uv_001AD670((UV_001AD670 *)&sprite.uv1, 0x280 << 4, 0x1C0 << 4);
        sprite.vertex0.x = (((x + 0x800) - (width >> 1)) << 4) - 8;
        sprite.vertex0.y = (((y + 0x800) - (height >> 1)) << 4) - 8;
        sprite.vertex1.x = (((x + 0x800) + (width >> 1)) << 4) - 8;
        sprite.vertex1.y = (((y + 0x800) + (height >> 1)) << 4) - 8;
        RhView_PopStack();
        RhView_GetCurView(&view);
        RhView_Modify(&view);
        packet = ExSortPrim_Pipe(RhView_SendViewParameters(packet), (s32)&sprite, 0, 0);
        RhBase_FreeRenderFrame();
    }
    return packet;
}

void SzDuel_Initialize(void) {
    u8 *state = D_00317490.b;
    s32 x;
    s32 y;
    u8 *cell;
    s32 group;
    s32 index;
    u8 *entry;
    u8 *row;

    RhMem_FillMemory((s8 *)D_00317490.b, 0, 0xD70);
    SzDuel_InitCardRequest();
    SzDuel_InitCardControl();
    y = 0;
    do {
        x = 0;
        do {
            cell = SzDuel_GetMapInfo(x, y);
            SzDuel_InitMapInfo(cell);
            cell[0x16] = (y + x) % 10;
            x++;
        } while (x < 7);
        y++;
    } while (y < 7);

    row = D_00318280;
    group = 0;
    do {
        index = 0;
        entry = row;
        do {
            SzDuel_InitCardInfo(entry, -1);
            index++;
            entry += 0x5C;
        } while (index < 11);
        group++;
        row += 0x3F4;
    } while (group < 3);

    state[0x33C] = 100;
    state[0x68C] = 100;
    SzDuel_Init(0, 0, 0);
}

void lSzDuel_InitCom(s32 arg0) {
    extern s32 SzGame_GetMode();
    s32 mode;
    s32 i;

    mode = SzGame_GetMode(1);
    SzView_SetStraightLight(0, 9, 1);
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
        SzModel_SetDrawFlag(i + 5, 1);
        i++;
    } while (i < 2);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x14, 1);
        i++;
    } while (i < 0xA);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x1E, 1);
        i++;
    } while (i < 2);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x20, 1);
        i++;
    } while (i < 2);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x4A, 1);
        i++;
    } while (i < 0xA);
    if (mode == 1) {
        s32 j = 0;
        do {
            SzModel_SetDeform(j + 0x14, 1);
            SzModel_SetDeformRatio(j + 0x14, 0x20);
            j++;
        } while (j < 0xA);
        j = 0;
        do {
            SzModel_SetDeform(j + 0x1E, 1);
            SzModel_SetDeformRatio(j + 0x1E, 0x20);
            j++;
        } while (j < 2);
    }
    if (arg0 != 0) {
        s32 color = (s32) &D_00291000;
        s32 ambient = (s32) &D_0029100C;
        s32 matrix = (s32) &D_00291020;
        s32 range = (s32) &D_002910B0;
        s32 position = (s32) &D_002910B8;

        SzEffect_SetFogColorForMonster((s32) position);
        SzEffect_SetFogColorForDuel((s32) position);
        SzEffect_SetFogParamZForMonster(0);
        SzEffect_SetFogParamZForDuel(0);
        if (((f32 *) range)[0] == ((f32 *) range)[1]) {
            SzEffect_SetFogParamYForMonster(0);
            SzEffect_SetFogParamYForDuel(0);
        } else {
            SzEffect_SetFogParamYForMonster((s32) range);
            SzEffect_SetFogParamYForDuel((s32) range);
        }
        SzEffect_SetStraightLightForMonster((s32) matrix);
        SzEffect_SetStraightLightForDuel((s32) matrix);
        SzEffect_SetPointLightForMonster(0);
        SzEffect_SetPointLightForDuel(0);
        SzEffect_SetIntensityForMonster((s32) ambient);
        SzEffect_SetIntensityForDuel((s32) color);
        SzEffect_SetBlackOutForMonster(0x80);
        SzEffect_SetBlackOutForDuel(0x80);
    }
}
