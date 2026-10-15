#include "common.h"

typedef struct Slot_002009E0 {
    void *ptr;
    s32 x4;
    s16 lo : 3;
    s16 cat : 13;
    s16 type;
} Slot_002009E0;

extern Slot_002009E0 D_003229A0[0x400];
extern char D_002D074B[];
extern char D_002D0750[];
extern char *D_00293CD0;
extern char *D_00293CD4;
extern char *D_00293CD8;
extern char *D_00293CDC;
extern char *D_00293CE0;
extern char *D_00293CE4;
extern char *D_00293CE8;
extern char *D_00293CEC;
extern char *D_00293CF0;
extern char *D_00293CF4;
extern s32 D_00293CC0;
extern s32 D_00293CC4;
extern s32 D_00293CC8;
extern s32 D_00293CCC;

static inline Slot_002009E0 *find_002009E0(s32 cat, s32 type) {
    Slot_002009E0 *p;
    s32 i;

    p = D_003229A0;
    if (type < 0) {
        return NULL;
    }
    for (i = 0; i < 0x400; i++, p++) {
        if (p->ptr != NULL && p->cat == cat && p->type == type) {
            return p;
        }
    }
    return NULL;
}

s32 func_002009E0(s32 arg0, s32 arg1) {
    char name[0x80];
    u16 ids[41];
    u16 list[17];
    u8 *dir;
    s32 result;
    s32 i;
    s32 j;
    s32 idx;
    s32 base;
    s32 n;
    s32 count;
    s32 id;
    s32 got;
    s32 sector;
    s32 pos;
    s32 size;
    s32 k;
    s32 len;
    s32 off;
    u16 t;

    dir = func_001FFF90((s32)D_002D074B);
    result = 0;
    if (arg0 < 0 || arg0 >= 18) {
        return 0;
    }
    switch (arg0) {
    case 0:
        func_0019B648(name, D_002D0750, dir, D_00293CD0);
        if (find_002009E0(0, 0) == NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 1) != NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 5) != NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 6) != NULL) {
            arg1 = 1;
        }
        if (arg1 == 0) {
            return 1;
        }
        for (i = 0; i < 5; i++) {
            func_001E7E70(i, -1, 999);
        }
        for (i = 0; i < 2; i++) {
            func_001E7E70(i + 5, -1, 999);
        }
        for (i = 0; i < 1; i++) {
            func_001E7E70(i + 7, -1, 999);
        }
        for (i = 0; i < 12; i++) {
            func_001E7E70(i + 8, -1, 999);
        }
        for (i = 1; i < 11; i++) {
            func_001DFBB0(0, i);
            func_001DFBB0(1, i);
        }
        for (i = 0; i < 10; i++) {
            func_001E7E70(i + 0x14, -1, 999);
        }
        for (i = 0; i < 2; i++) {
            func_001E7E70(i + 0x20, -1, 999);
        }
        for (i = 0; i < 40; i++) {
            func_001E7E70(i + 0x22, -1, 999);
        }
        for (i = 0; i < 10; i++) {
            func_001E7E70(i + 0x4A, -1, 999);
        }
        func_002029B0(0, 1);
        func_002029B0(0, 5);
        func_002029B0(0, 6);
        func_002029B0(1, -1);
        func_002029B0(7, -1);
        func_002029B0(8, -1);
        {
            s32 SZ0;
            s32 CNT0;
            s32 SEC0;
            s32 POS0;
            s32 ID0;
            s32 K0;

            for (K0 = 0, SEC0 = 0, POS0 = 0, ID0 = 0; K0 <= 8; K0++, SEC0 += 0x1A9640, POS0 += 0x1C2000, ID0 += 0x10) {
                if (K0 < 8) {
                    CNT0 = 100;
                } else {
                    CNT0 = 71;
                }
                SZ0 = CNT0 * 0x4800;
                func_002029B0(0, ID0);
                result |= func_00202220(0, ID0, name, (s32)((s64)SEC0 + 0xB1B000), SZ0, POS0, SZ0);
            }
        }
        break;
    case 1:
        func_0019B648(name, D_002D0750, dir, D_00293CD4);
        if (find_002009E0(0, 1) == NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 0) != NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 5) != NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 6) != NULL) {
            arg1 = 1;
        }
        if (arg1 == 0) {
            return 1;
        }
        func_002029B0(0, 0);
        func_002029B0(0, 1);
        func_002029B0(0, 5);
        func_002029B0(0, 6);
        func_002029B0(1, -1);
        func_002029B0(7, -1);
        func_002029B0(8, -1);
        result = func_00202220(0, 1, name, 0xB1B000, -1, 0, -1);
        break;
    case 2:
    case 3:
        idx = arg0 - 2;
        got = func_002159D0(idx, func_002158B0(idx));
        base = idx * 41 + 0xDF;
        func_0019B648(name, D_002D0750, dir, D_00293CD0);
        ids[40] = got;
        for (i = 0; i < 40; i++) {
            ids[i] = func_001DE9E0(idx, i);
        }
        for (i = 0; i < 41; i++) {
            for (j = i + 1; j < 41; j++) {
                if (ids[i] > ids[j]) {
                    t = ids[i];
                    ids[i] = ids[j];
                    ids[j] = t;
                }
            }
        }
        for (i = 0; i < 41; base++, i++) {
            id = ids[i];
            if (id != 999) {
                id = func_002166D0(idx, id);
            }
            if (find_002009E0(1, id) == NULL) {
                result |= func_00202220(1, id, name, (s32)((s64)(base * 0x4410) + 0xB1B000), 0x4800, id * 0x4800, 0x4800);
            }
        }
        break;
    case 10:
        n = 0;
        func_0019B648(name, D_002D0750, dir, D_00293CD0);
        for (i = 0; i < 17; i++) {
            list[i] = func_00214910(i, 0);
        }
        for (i = 0; i < 17; i++) {
            for (j = i + 1; j < 17; j++) {
                if (list[i] > list[j]) {
                    t = list[i];
                    list[i] = list[j];
                    list[j] = t;
                }
            }
        }
        func_002029B0(0, 0);
        func_002029B0(0, 1);
        func_002029B0(1, -1);
        for (i = 0; i < 17; n++, i++) {
            id = list[i];
            if (find_002009E0(1, id) == NULL) {
                result |= func_00202220(1, id, name, (s32)((s64)(n * 0x4410) + 0xB1B000), 0x4800, id * 0x4800, 0x4800);
            }
        }
        break;
    case 4:
        result = func_002009E0(5, arg1);
        result |= func_002009E0(6, arg1);
        break;
    case 5:
    case 6:
        idx = arg0 - 5;
        got = func_002159D0(idx, func_002158B0(idx));
        func_0019B648(name, D_002D0750, dir, D_00293CD8);
        if (find_002009E0(2, idx) == NULL) {
            arg1 = 1;
        }
        if (arg1 == 0) {
            return 1;
        }
        func_002029B0(2, idx);
        if (got == 999) {
            break;
        }
        id = func_002166D0(idx, got);
        pos = idx << 12;
        sector = got << 12;
        if (id != got) {
            sector = (id - 0xAB) << 12;
        }
        result = func_00202220(2, idx, name, (s32)((s64)pos + 0xB19000), 0x1000, sector, 0x1000);
        break;
    case 7:
        result = func_002009E0(8, arg1);
        result |= func_002009E0(9, arg1);
        break;
    case 8:
    case 9:
        {
            s32 ID8;
            s32 I8;
            s32 IDX8;
            s32 GOT8;
            s32 POS8;
            s32 SEC8;
            s32 K8;

            IDX8 = arg0 - 8;
            func_0019B648(name, D_002D0750, dir, D_00293CD8);
            func_002029B0(0, 7);
            func_002029B0(0, 8);
            func_002029B0(0, 9);
            func_002029B0(9, -1);
            for (I8 = 0; I8 < 3; I8++) {
                GOT8 = func_002159D0(IDX8, I8);
                ID8 = func_002166D0(IDX8, GOT8);
                K8 = I8 + (IDX8 ? 20 : 10);
                POS8 = (IDX8 * 3 + I8) << 12;
                SEC8 = GOT8 << 12;
                if (ID8 != GOT8) {
                    SEC8 = (ID8 - 0xAB) << 12;
                }
                func_002029B0(2, K8);
                result = func_00202220(2, K8, name, (s32)((s64)POS8 + 0xA75000), 0x1000, SEC8, 0x1000);
            }
        }
        break;
    case 11:
        func_0019B648(name, D_002D0750, dir, D_00293CDC);
        if (find_002009E0(0, 3) == NULL) {
            arg1 = 1;
        }
        if (arg1 == 0) {
            return 1;
        }
        func_002029B0(0, 3);
        func_002029B0(3, -1);
        result = func_00202220(0, 3, name, 0x912000, 0x11E800, 0, -1);
        break;
    case 12:
        func_0019B648(name, D_002D0750, dir, D_00293CE0);
        if (find_002009E0(0, 4) == NULL) {
            arg1 = 1;
        }
        if (arg1 == 0) {
            return 1;
        }
        func_002029B0(0, 4);
        func_002029B0(4, -1);
        result = func_00202220(0, 4, name, 0xA30800, 0x44800, 0, -1);
        break;
    case 13:
        func_0019B648(name, D_002D0750, dir, D_00293CE4);
        if (find_002009E0(0, 5) == NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 0) != NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 1) != NULL) {
            arg1 = 1;
        }
        if (arg1 == 0) {
            return 1;
        }
        func_002029B0(0, 0);
        func_002029B0(0, 1);
        func_002029B0(0, 5);
        func_002029B0(1, -1);
        func_002029B0(7, -1);
        result = func_00202220(0, 5, name, 0xB63540, 0x16A800, 0, -1);
        break;
    case 14:
        func_0019B648(name, D_002D0750, dir, D_00293CE8);
        if (find_002009E0(0, 6) == NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 0) != NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 1) != NULL) {
            arg1 = 1;
        }
        if (arg1 == 0) {
            return 1;
        }
        for (i = 0; i < 5; i++) {
            func_001E7E70(i, -1, 999);
        }
        for (i = 0; i < 2; i++) {
            func_001E7E70(i + 5, -1, 999);
        }
        for (i = 0; i < 1; i++) {
            func_001E7E70(i + 7, -1, 999);
        }
        for (i = 0; i < 12; i++) {
            func_001E7E70(i + 8, -1, 999);
        }
        for (i = 0; i < 2; i++) {
            func_001E7E70(i + 0x20, -1, 999);
        }
        for (i = 0; i < 10; i++) {
            func_001E7E70(i + 0x4A, -1, 999);
        }
        func_002029B0(0, 0);
        func_002029B0(0, 1);
        func_002029B0(0, 6);
        func_002029B0(1, -1);
        func_002029B0(8, -1);
        result = func_00202220(0, 6, name, 0xCCDD40, 0x47F000, 0, -1);
        break;
    case 15:
        off = D_00293CC0;
        len = D_00293CC4 - off;
        func_0019B648(name, D_002D0750, dir, D_00293CEC);
        if (find_002009E0(0, 7) == NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 8) != NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 9) != NULL) {
            arg1 = 1;
        }
        if (arg1 == 0) {
            return 1;
        }
        func_002029B0(0, 7);
        func_002029B0(0, 8);
        func_002029B0(0, 9);
        func_002029B0(9, -1);
        result = func_00202220(0, 7, name, 0xA75000, len, off, len);
        break;
    case 16:
        off = D_00293CC4;
        len = D_00293CC8 - off;
        func_0019B648(name, D_002D0750, dir, D_00293CF0);
        if (find_002009E0(0, 8) == NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 7) != NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 9) != NULL) {
            arg1 = 1;
        }
        if (arg1 == 0) {
            return 1;
        }
        func_002029B0(0, 8);
        func_002029B0(0, 7);
        func_002029B0(0, 9);
        func_002029B0(9, -1);
        result = func_00202220(0, 8, name, 0xA75000, len, off, len);
        break;
    case 17:
        off = D_00293CC8;
        len = D_00293CCC - off;
        func_0019B648(name, D_002D0750, dir, D_00293CF4);
        if (find_002009E0(0, 9) == NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 7) != NULL) {
            arg1 = 1;
        }
        if (find_002009E0(0, 8) != NULL) {
            arg1 = 1;
        }
        if (arg1 == 0) {
            return 1;
        }
        func_002029B0(0, 9);
        func_002029B0(0, 7);
        func_002029B0(0, 8);
        func_002029B0(9, -1);
        result = func_00202220(0, 9, name, 0xA75000, len, off, len);
        break;
    }
    return result;
}
