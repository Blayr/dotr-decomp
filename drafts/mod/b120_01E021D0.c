M2C_UNK func_01E00260_b120(void *, M2C_UNK, M2C_UNK, f32 *); /* extern */

/* Warning: Gap in callee-saved word stack region.
 * Saved: [0x0, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c], gap at: 0x8. */
s32 func_01E021D0_b120(void *arg0, void *arg1) {
    f32 sp50;
    f32 sp54;
    f32 sp58;
    f32 var_f0;
    f32 var_f0_2;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v1;
    s16 var_v1;
    s32 temp_v0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_v1_2;
    u8 temp_v0_3;
    u8 temp_v0_4;
    void *temp_v0_2;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;
    void *var_a0;
    void *var_a0_2;
    void *var_at;

    if (M2C_FIELD(arg1, s16 *, 0x36) == 1) {
        M2C_FIELD(arg1, s16 *, 0xA) = 0x14;
        temp_v0 = func_0019A5C8();
        var_v1 = temp_v0 & 1;
        if (temp_v0 < 0) {
            if (var_v1 != 0) {
                var_v1 -= 2;
            }
        }
        M2C_FIELD(arg1, s16 *, 8) = var_v1;
        if (M2C_FIELD(arg0, s16 *, 0xACB8) != 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
        } else {
            M2C_FIELD(arg1, s32 *, 0x14) = 0x4000;
        }
        M2C_FIELD(arg1, s32 *, 0x1C) = (s32) ((func_0019A5C8() % 60) - 0x1E);
        M2C_FIELD(arg1, s32 *, 0x1C) = func_001A22C0((f32) M2C_FIELD(arg1, s32 *, 0x1C) / 10.0f);
        func_001076F0(arg1 + 0x2C, 0x80, 0x80, 0x80);
        func_001F5F90(func_001F53A0(M2C_ERROR(/* Read from unset register $a0 */)), arg0 + (M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + 0x2938 + 0x7FF8);
        temp_v0_2 = (M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0;
        M2C_FIELD(temp_v0_2, f32 *, 0xA930) = (f32) (M2C_FIELD(temp_v0_2, f32 *, 0xA930) + (4.0f * (f32) M2C_FIELD(arg1, s32 *, 0x1C)));
        sp54 = 0.0f;
        var_a1 = 0;
        M2C_FIELD(arg1, s16 *, 0x3A) = (s16) (func_0019A5C8() % 360);
        sp58 = M2C_FIELD(((M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0), f32 *, 0xA938);
        sp50 = M2C_FIELD(((M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0), f32 *, 0xA930);
        var_a0 = arg0 + (M2C_FIELD(arg1, s16 *, 0x30) * 0x280) + 0x2C30;
        do {
            var_a1 += 1;
            M2C_FIELD(var_a0, f32 *, 0) = sp50;
            M2C_FIELD(var_a0, f32 *, 4) = (f32) sp54;
            M2C_FIELD(var_a0, f32 *, 8) = (f32) sp58;
            var_a0 += 0x10;
        } while (var_a1 < 0x13);
        sp54 = (f32) ((s64) (0x14 << 0x30) >> 0x30) / 10.0f;
        var_a1_2 = 0;
        var_a0_2 = arg0 + (M2C_FIELD(arg1, s16 *, 0x30) * 0x280) + 0x2D70;
        do {
            var_a1_2 += 1;
            M2C_FIELD(var_a0_2, f32 *, 0) = sp50;
            M2C_FIELD(var_a0_2, f32 *, 4) = (f32) sp54;
            M2C_FIELD(var_a0_2, f32 *, 8) = (f32) sp58;
            var_a0_2 += 0x10;
        } while (var_a1_2 < 0x13);
        M2C_FIELD(arg1, s16 *, 6) = 2;
        M2C_FIELD(arg1, u8 *, 0x2B) = 0U;
        M2C_FIELD(arg1, s16 *, 8) = 0;
        M2C_FIELD(arg1, s16 *, 0x34) = 0;
        M2C_FIELD(arg1, s16 *, 0x38) = 5;
        M2C_FIELD(arg1, s16 *, 0x36) = 2;
    }
    if (M2C_FIELD(arg1, s16 *, 0x32) < 0x12) {
        temp_v0_3 = M2C_FIELD(arg1, u8 *, 0x2B);
        if ((s32) temp_v0_3 < 0x80) {
            M2C_FIELD(arg1, u8 *, 0x2B) = (u8) (temp_v0_3 + 0xA);
        }
    } else {
        temp_v0_4 = M2C_FIELD(arg1, u8 *, 0x2B);
        if ((s32) temp_v0_4 >= 0xB) {
            M2C_FIELD(arg1, u8 *, 0x2B) = (u8) (temp_v0_4 - 9);
        } else {
            M2C_FIELD(arg1, s16 *, 0x36) = 0;
        }
    }
    temp_v1 = M2C_FIELD(arg1, s16 *, 0x3A);
    if (temp_v1 >= 0x168) {
        M2C_FIELD(arg1, s16 *, 0x3A) = (s16) (temp_v1 % 360);
    }
    sp54 = (f32) M2C_FIELD(arg1, s16 *, 8);
    sp58 = M2C_FIELD(((M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0), f32 *, 0xA938);
    sp50 = M2C_FIELD(((M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0), f32 *, 0xA930);
    func_01E00260_b120(arg0 + (M2C_FIELD(arg1, s16 *, 0x30) * 0x280) + 0x2D60, 0x14, 0, &sp50);
    *M2C_ERROR(/* Read from unset register $a5 */) = (second half of f64) + (f32) M2C_FIELD(arg1, s16 *, 8);
    if (M2C_FIELD(arg0, s16 *, 0xACB8) != 0) {
        var_f0 = 10.0f + M2C_FIELD(((M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0), f32 *, 0xA938);
    } else {
        var_f0 = M2C_FIELD(((M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0), f32 *, 0xA938) - 10.0f;
    }
    *M2C_ERROR(/* Read from unset register $a6 */) = var_f0;
    sp50 = M2C_FIELD(((M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0), f32 *, 0xA930);
    func_01E00260_b120(arg0 + (M2C_FIELD(arg1, s16 *, 0x30) * 0x280) + 0x2EA0, 0x14, 0, &sp50);
    temp_v0_5 = M2C_FIELD(arg1, s16 *, 0x32);
    var_v1_2 = temp_v0_5 & 1;
    if (temp_v0_5 < 0) {
        if (var_v1_2 != 0) {
            var_v1_2 -= 2;
        }
    }
    if (var_v1_2 == 1) {
        func_001076F0(arg1 + 0x28, 0x80, 0x20, 0x40);
    } else {
        func_001076F0(arg1 + 0x28, 0x70, 0x10, 0x30);
    }
    if (M2C_FIELD(arg1, s16 *, 0x32) != 0) {
        temp_v0_6 = M2C_FIELD(arg1, s16 *, 6);
        if (temp_v0_6 < 0x12) {
            M2C_FIELD(arg1, s16 *, 6) = (s16) (temp_v0_6 + 1);
        }
    }
    if (M2C_FIELD(arg0, s16 *, 0xACB8) != 0) {
        temp_v0_7 = (M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0;
        var_f0_2 = M2C_FIELD(temp_v0_7, f32 *, 0xA938) - 6.5f;
        var_at = temp_v0_7 + 0x10000;
    } else {
        temp_v0_8 = (M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0;
        var_f0_2 = M2C_FIELD(temp_v0_8, f32 *, 0xA938) + 6.5f;
        var_at = temp_v0_8 + 0x10000;
    }
    M2C_FIELD(var_at, f32 *, -0x56C8) = var_f0_2;
    if (M2C_FIELD(arg1, s16 *, 0x32) != 0) {
        temp_v0_9 = (M2C_FIELD(arg1, s16 *, 0x30) * 0x10) + arg0;
        M2C_FIELD(temp_v0_9, f32 *, 0xA930) = (f32) (M2C_FIELD(temp_v0_9, f32 *, 0xA930) + (f32) M2C_FIELD(arg1, s32 *, 0x1C));
    }
    M2C_FIELD(arg1, s16 *, 0x32) = (s16) (M2C_FIELD(arg1, s16 *, 0x32) + 1);
    return 0;
}
