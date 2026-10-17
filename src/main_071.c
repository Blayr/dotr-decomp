#include "common.h"

/* One of six cards at random (ids 0x23, 0x4F, 0x2C, 0x5C, 0x17B, 0x18A): what card 0x17B's combination gives. */
s32 TaEnc_GetRandomElf(void) {
    s32 roll;

    roll = func_0019A5C8() % 6;
    switch (roll) {
    case 0:
        return 0x23;
    case 1:
        return 0x4F;
    case 2:
        return 0x2C;
    case 3:
        return 0x5C;
    case 4:
        return 0x17B;
    case 5:
    default:
        return 0x18A;
    }
}

/* Whether equip effect `eNo` reflects an attack. */
s32 TaEnc_IsActReflexEnc(s32 eNo) {
    return (D_0029D1F0[eNo & 0xFFFF] == 0) ? 1 : 0;
}

/* The equip effect of card `nCardNo`. */
u8 TaEnc_GetEncID(s32 nCardNo) {
    return D_0029D1F0[nCardNo & 0xFFFF];
}

/* The fusion result of cards `No1` and `No2`, or none. */
u32 Fusion(s32 No1, s32 No2) {
    s32 i;
    u32 *entry;
    u32 packed;
    s32 temp;

    if (No1 < No2) {
        temp = No1;
        No1 = No2;
        No2 = temp;
    }
    entry = fusionTable;
    i = 0;
    do {
        packed = *entry;
        if ((No1 == (packed & 0x3FF)) &&
            (No2 == ((packed & 0xFFC00) >> 10))) {
            return (fusionTable[i] & 0x3FF00000) >> 20;
        }
        i++;
        entry++;
    } while (i < 0x67AC);
    return 0x3E7U;
}

/* The fusion result of unit (nSide, nID) with a wall card, or none. */
s32 WallFusion(s32 nSide, s32 nID) {
    void *unitEffect;

    unitEffect = Ta_GetUnitEffect(nSide, nID, 1);
    if ((unitEffect != NULL) && ((*(u32 *)unitEffect >> 8) == 9)) {
        return *(u16 *)((u8 *)unitEffect + 4);
    }
    return -1;
}
