/* Model / motion file relocation (NjaReloc_*). */

#include "common.h"

typedef struct Flags_00214090 {
    u8 unused : 7;
    u8 enabled : 1;
} Flags_00214090;

typedef struct Header_00214090 {
    s32 magic;
    u8 padding[0xC];
    u16 count;
    u8 unknown;
    Flags_00214090 flags;
    u32 data;
    u32 extra;
} Header_00214090;

/* Relocates a motion file (its offsets become pointers). */
s32 NjaReloc_Adjust_M3DMOT(void *motion) {
    Header_00214090 *header = motion;

    if (header->magic != 0x1A544F4D) {
        return 0;
    }
    header->data = (u32)header + header->data;
    header->extra = (u32)header + header->extra;
    lNjaReloc_AdjustMotion((void *)header->data, (s32)header, header->count, header->flags.enabled);
    return 1;
}

/* Relocates one motion's data against `base`. */
s32 lNjaReloc_AdjustMotion(void *motion, s32 base, s32 count, s32 first) {
    s32 temp_v1;
    s32 temp_v0;
    s32 temp_v0_2;

    if (first != 0) {
        *(s32 *)((u8 *)motion - 4) = base + *(s32 *)((u8 *)motion - 4);
    }
    temp_v1 = *(u16 *)((u8 *)motion + 8) & 0x3F;
    if (temp_v1 == 3) {
        temp_v0 = *(s32 *)motion;
        if (temp_v0 != 0) {
            *(s32 *)motion = base + temp_v0;
            lNjaReloc_AdjustMData2((u8 *)*(s32 *)motion, base, count, first);
        }
    } else if (temp_v1 == 7) {
        temp_v0_2 = *(s32 *)motion;
        if (temp_v0_2 != 0) {
            *(s32 *)motion = base + temp_v0_2;
            lNjaReloc_AdjustMData3((u8 *)*(s32 *)motion, base, count, first);
        }
    }
    return 1;
}

/* Relocates a motion's two-channel key data. */
s32 lNjaReloc_AdjustMData2(u8 *data, s32 base, s32 count, s32 first) {
    s32 i;
    s32 j;
    s32 *p;

    if (first != 0) {
        *(s32 *)(data - 4) = base + *(s32 *)(data - 4);
    }
    for (i = 0; i < count; i++) {
        j = 0;
        p = (s32 *)data;
        do {
            if (*p != 0) {
                *p = base + *p;
                if (first != 0) {
                    *(s32 *)(*p - 4) = base + *(s32 *)(*p - 4);
                }
            }
            j++;
            p++;
        } while (j < 2);
        data += 0x10;
    }
    return 1;
}

/* Relocates a motion's three-channel key data. */
s32 lNjaReloc_AdjustMData3(u8 *data, s32 base, s32 count, s32 first) {
    s32 i;
    s32 j;
    s32 *p;

    if (first != 0) {
        *(s32 *)(data - 4) = base + *(s32 *)(data - 4);
    }
    for (i = 0; i < count; i++, data += 0x18) {
        j = 0;
        p = (s32 *)data;
        do {
            if (*p != 0) {
                *p = base + *p;
                if (first != 0) {
                    *(s32 *)(*p - 4) = base + *(s32 *)(*p - 4);
                }
            }
            j++;
            p++;
        } while (j < 3);
    }
    return 1;
}
