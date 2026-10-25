s32 func_01E03940_b179(void *arg0, s32 arg1, s32 arg2) {
    M2C_UNK sp40;
    u8 sp45;
    M2C_UNK sp58;
    u8 sp68;
    u8 sp69;
    u8 sp6A;
    s8 sp6B;
    s32 sp6C;
    M2C_UNK sp70;
    s64 sp78;                                       /* compiler-managed */
    u8 sp80;
    u8 sp81;
    u8 sp82;
    s8 sp83;
    s32 sp84;
    M2C_UNK sp88;
    s64 sp90;                                       /* compiler-managed */
    u8 sp98;
    u8 sp99;
    u8 sp9A;
    s8 sp9B;
    s32 sp9C;
    M2C_UNK spA0;
    s16 spA8;
    s16 spAA;
    s8 spAF;
    u8 spB0;
    u8 spB1;
    u8 spB2;
    s8 spB3;
    s32 spB4;
    M2C_UNK spB8;
    s64 spC0;                                       /* compiler-managed */
    u8 spEC;
    s32 temp_v1;
    s64 temp_v0_4;
    s64 temp_v0_5;
    s64 temp_v0_6;
    s8 var_a0;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;

    if (((arg2 & 0xFFFF) >= (s32) M2C_FIELD(arg0, u16 *, 0)) && ((s32) M2C_FIELD(arg0, u16 *, 2) >= (arg2 & 0xFFFF))) {
        M2C_FIELD(&sp58, u16 *, 2) = 0x34U;
        M2C_FIELD(&sp58, s16 *, 0) = 0xC;
        M2C_FIELD(&sp58, s64 *, 8) = (s64) (0x21421421 | (0x4214 << 0x20));
        M2C_FIELD(&sp58, s32 *, 4) = 0;
        func_002087A0(&sp58, 1);
        temp_v0 = M2C_FIELD(arg0, u8 *, 0x2E);
        spB0 = temp_v0;
        sp98 = temp_v0;
        sp80 = temp_v0;
        sp68 = temp_v0;
        temp_v0_2 = M2C_FIELD(arg0, u8 *, 0x2D);
        spB1 = temp_v0_2;
        sp99 = temp_v0_2;
        sp81 = temp_v0_2;
        sp69 = temp_v0_2;
        temp_v0_3 = M2C_FIELD(arg0, u8 *, 0x2C);
        spB2 = temp_v0_3;
        sp9A = temp_v0_3;
        sp82 = temp_v0_3;
        sp6A = temp_v0_3;
        spB4 = 0x3F800000;
        sp9C = 0x3F800000;
        sp84 = 0x3F800000;
        sp6C = 0x3F800000;
        temp_v0_4 = (spC0 & ((0xFFFF << 0x10) | 0xFFFF | (0xFF000000 << 0x20))) | (((u64) (0xFFFFFF << 0x28) >> 0x28) << 0x20);
        spC0 = temp_v0_4;
        temp_v0_5 = (sp90 & ((0xFFFF << 0x10) | 0xFFFF | (0xFF000000 << 0x20))) | (((u64) (((u64) (temp_v0_4 << 8) >> 0x28) << 0x28) >> 0x28) << 0x20);
        sp90 = temp_v0_5;
        temp_v0_6 = (sp90 & ((0xFFFF << 0x10) | 0xFFFF | (0xFF000000 << 0x20))) | (((u64) (((u64) (temp_v0_5 << 8) >> 0x28) << 0x28) >> 0x28) << 0x20);
        sp90 = temp_v0_6;
        sp78 = (sp78 & ((0xFFFF << 0x10) | 0xFFFF | (0xFF000000 << 0x20))) | (((u64) (((u64) (temp_v0_6 << 8) >> 0x28) << 0x28) >> 0x28) << 0x20);
        unkspC7 = 0;
        spAF = 0;
        unksp97 = 0;
        unksp7F = 0;
        temp_v1 = (arg2 & 0xFFFF) - M2C_FIELD(arg0, u16 *, 0);
        var_a0 = (M2C_FIELD(arg0, u8 *, 5) * 0x10) & 0xFF;
        if (temp_v1 < (s32) M2C_FIELD(arg0, u8 *, 5)) {
            var_a0 = (temp_v1 * 0x10) & 0xFF;
        }
        if ((M2C_FIELD(arg0, u16 *, 2) - (arg2 & 0xFFFF)) < (M2C_FIELD(arg0, u8 *, 5) * 2)) {
            var_a0 = (((u8) M2C_FIELD(arg0, u16 *, 2) - arg2) * 8) & 0xFF;
        }
        spB3 = var_a0;
        sp9B = var_a0;
        sp83 = var_a0;
        sp6B = var_a0;
        sp45 = M2C_FIELD(arg0, u8 *, 6);
        func_00101C80(&sp40, &spEC);
        func_002086D0(&sp58, ((s64) spEF << 6) | (((s64) spEE * 0x10) | (spEC | ((s64) spED * 4))));
        M2C_FIELD(&sp58, u16 *, 2) = (u16) (M2C_FIELD(&sp58, u16 *, 2) | 0x800);
        M2C_FIELD(&sp70, u16 *, 0) = (u16) ((M2C_FIELD(&sp70, u16 *, 0) & ~0x3FFF) | (0 & 0x3FFF));
        M2C_FIELD(&sp70, u16 *, 2) = (u16) ((M2C_FIELD(&sp70, u16 *, 2) & ~0x3FFF) | (0 & 0x3FFF));
        M2C_FIELD(&sp88, u16 *, 0) = (u16) ((M2C_FIELD(&sp88, u16 *, 0) & ~0x3FFF) | 0x2800);
        M2C_FIELD(&sp88, u16 *, 2) = (u16) ((M2C_FIELD(&sp88, u16 *, 2) & ~0x3FFF) | (0 & 0x3FFF));
        M2C_FIELD(&spA0, u16 *, 0) = (u16) ((M2C_FIELD(&spA0, u16 *, 0) & ~0x3FFF) | (0 & 0x3FFF));
        M2C_FIELD(&spA0, u16 *, 2) = (u16) ((M2C_FIELD(&spA0, u16 *, 2) & ~0x3FFF) | 0x1C00);
        M2C_FIELD(&spB8, u16 *, 0) = (u16) ((M2C_FIELD(&spB8, u16 *, 0) & ~0x3FFF) | 0x2800);
        M2C_FIELD(&spB8, u16 *, 2) = (u16) ((M2C_FIELD(&spB8, u16 *, 2) & ~0x3FFF) | 0x1C00);
        sp78 = func_001A23B0(27648.0f + (f32) (M2C_FIELD(arg0, s32 *, 0xC) * 0x10));
        sp90 = func_001A23B0(37888.0f + (f32) (M2C_FIELD(arg0, s32 *, 0x10) * 0x10));
        spA8 = func_001A23B0(27648.0f + (f32) (M2C_FIELD(arg0, s32 *, 0x14) * 0x10));
        spC0 = func_001A23B0(37888.0f + (f32) (M2C_FIELD(arg0, s32 *, 0x18) * 0x10));
        unksp7A = func_001A23B0(29184.0f + (f32) (M2C_FIELD(arg0, s32 *, 0x1C) * 0x10));
        unksp92 = func_001A23B0(29184.0f + (f32) (M2C_FIELD(arg0, s32 *, 0x20) * 0x10));
        spAA = func_001A23B0(36352.0f + (f32) (M2C_FIELD(arg0, s32 *, 0x24) * 0x10));
        unkspC2 = func_001A23B0(36352.0f + (f32) (M2C_FIELD(arg0, s32 *, 0x28) * 0x10));
        func_002075F0((s32) &sp58, arg1, func_001A23B0(M2C_FIELD(arg0, f32 *, 8)));
    }
    return 1;
}
