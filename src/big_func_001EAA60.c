#include "common.h"

/* Debug viewer controls for one object slot: the pad drives animation, camera, light and fog settings
   depending on the viewer page (func_00205150). */

typedef struct DbgFlags_001EAA60 {
    u8 pad[4];
    s32 flags;
} DbgFlags_001EAA60;

typedef struct Digits4_001EAA60 {
    s32 d0, d1, d2, d3;
} Digits4_001EAA60;

typedef struct Digits3_001EAA60 {
    s32 d0, d1, d2;
} Digits3_001EAA60;

typedef struct DbgObj_001EAA60 {
    f32 pos[3];                       /* 0x000 */
    u8 pad00C[0x14];
    s32 rot[3];                       /* 0x020 */
    u8 pad02C[4];
    Vec4f v;                          /* 0x030 */
    u8 pad040[0xE0];
    f32 light[3];                     /* 0x120 */
    u8 col0[4];                       /* 0x12C */
    u8 col1[4];                       /* 0x130 */
    u8 pad134[4];
    DbgFlags_001EAA60 *model;         /* 0x138 */
    u8 pad13C[8];
    s32 parts[8];                     /* 0x144 */
    u8 pad164[8];
    void *anim;                       /* 0x16C */
    u8 pad170[8];
    ObjSlot_0031ABB0 *slots[8];       /* 0x178 */
    f32 speed;                        /* 0x198 */
    f32 frame;                        /* 0x19C */
    u8 pad1A0[0x20];
    u32 vals[8];                      /* 0x1C0 */
    s8 lv[4];                         /* 0x1E0 */
    u8 pad1E4[8];
    s32 sound;                        /* 0x1EC */
    u8 pad1F0[2];
    s8 page;                          /* 0x1F2 */
    s8 kind;                          /* 0x1F3 */
    u8 pad1F4[2];
    u16 num : 14;                     /* 0x1F6 */
    s16 loop : 2;
    u8 fog0 : 2;                      /* 0x1F8 */
    u8 fog1 : 2;
    u8 pad1F8 : 4;
    u8 pad1F9[5];
    u8 count;                         /* 0x1FE */
    u8 pad1FF[3];
    u16 f202;                         /* 0x202 */
    u8 pad204[2];
    u16 f206;                         /* 0x206 */
    u16 f208;                         /* 0x208 */
} DbgObj_001EAA60;

extern u8 icolF[4];
extern u8 icolT[4];
extern u16 wFrame;
extern s32 nCameraCur;
extern s32 nEffCur;
extern Digits4_001EAA60 D_00292F90;
extern Digits4_001EAA60 D_00292FA0;
extern Digits3_001EAA60 D_00292FB0;
extern Digits3_001EAA60 D_00292FC0;
extern char D_002CFA17[];
extern char D_002CFB7D[];
extern s32 gSzModel_fRefLock;
extern s32 gSzModel_nRefLock;
extern u16 wAlphaMode;
extern s32 nBlurUse;
extern s32 nBlurCur;
extern s32 nEffCur2;

#define PAD_001EAA60(m, b) func_00203A40(0, m, b)

/* Debug: the model viewer for model slot `index`: moves, turns, scales and colours it, steps its motions, effects
   and camera with the pads. */
s32 SzModel_Act(s32 index) {
    extern s32 func_001EDCB0();
    extern s32 func_001FECB0();
    s64 mode;
    DbgObj_001EAA60 *obj;
    s32 page;
    f32 last;
    s32 i;
    s32 sel;
    s32 snd;
    s32 num;
    s32 newnum;
    s32 sub;
    s32 dir;
    s32 flag;
    s32 flag2;
    s32 n;
    f32 *anim;
    s32 pos;
    s8 *cur;
    s8 *lvp;
    void *ap;

    mode = func_001AAF60(1);
    if (index < 0 || index >= 0x54) {
        return 0;
    }
    obj = (DbgObj_001EAA60 *)modelSlots[index];
    if (obj == NULL) {
        return 0;
    }
    if (obj->page == func_00205160()) {
        anim = &obj->speed;
        lvp = &obj->lv[0];
        if (index == 0) lvp = &obj->lv[0]; /* second definition: keeps lvp in its own register (s5) */
        cur = &obj->lv[2];
        page = func_00205150();
        last = (f32)obj->vals[*lvp] - 1.0f;
        if (page == 1) {
            if (obj->slots[*lvp] != NULL) {
                if (!(PAD_001EAA60(1, 3) & 0xFFFF)) {
                    if (PAD_001EAA60(2, 8) != 0) {
                        do {
                            *cur = (*cur + 9) % 8;
                        } while (obj->slots[*cur] == NULL);
                    }
                    if (PAD_001EAA60(2, 4) != 0) {
                        do {
                            *cur = (*cur + 7) % 8;
                        } while (obj->slots[*cur] == NULL);
                    }
                }
                if (PAD_001EAA60(1, 0x10) != 0) {
                    if (PAD_001EAA60(0, 0x10) != 0) {
                        func_001F1480(index, *cur);
                    } else {
                        if (PAD_001EAA60(2, 2) != 0) {
                            func_001F1A80(index, anim[0] + 0.1f);
                        }
                        if (PAD_001EAA60(2, 1) != 0) {
                            func_001F1A80(index, anim[0] - 0.1f);
                        }
                    }
                }
                if (PAD_001EAA60(0, 0xF000) != 0) {
                    sel = 0;
                    if (PAD_001EAA60(0, 0x1000) != 0) {
                        sel = 0;
                    } else if (PAD_001EAA60(0, 0x2000) != 0) {
                        sel = 1;
                    } else if (PAD_001EAA60(0, 0x4000) != 0) {
                        sel = 2;
                    } else if (PAD_001EAA60(0, 0x8000) != 0) {
                        sel = 3;
                    }
                    if (PAD_001EAA60(1, 0x10) != 0) {
                        sel += 4;
                    }
                    func_001F1550(index, sel);
                }
                if (PAD_001EAA60(1, 0x40) != 0 || obj->loop == 0) {
                    if (PAD_001EAA60(2, 0x20) != 0) {
                        obj->loop = 1;
                        if (!(anim[1] < last)) {
                            anim[1] = 1.0f;
                        } else {
                            anim[1] += anim[0];
                            if (!(anim[1] <= last)) {
                                anim[1] = last;
                            }
                        }
                    }
                    if (PAD_001EAA60(2, 0x80) != 0) {
                        obj->loop = -1;
                        if (anim[1] <= 1.0f) {
                            anim[1] = last;
                        } else {
                            anim[1] -= anim[0];
                            if (anim[1] < 1.0f) {
                                anim[1] = 1.0f;
                            }
                        }
                    }
                    if (PAD_001EAA60(1, 0x40) != 0) {
                        obj->loop = 0;
                    }
                } else {
                    if (PAD_001EAA60(0, 0x20) != 0) {
                        obj->loop = 1;
                    }
                    if (PAD_001EAA60(0, 0x80) != 0) {
                        obj->loop = -1;
                    }
                }
            }
        }
        if (page == 2) {
            switch (nBlurCur) {
            case 0:
                flag = 0;
                flag2 = 0;
                if (PAD_001EAA60(0, 0x4000) != 0) {
                    wAlphaMode = 0;
                    wFrame = 6;
                }
                if (!(PAD_001EAA60(1, 3) & 0xFFFF)) {
                    if (PAD_001EAA60(1, 0x1000) != 0) {
                        if (PAD_001EAA60(2, 0xC) != 0) {
                            if (PAD_001EAA60(2, 4) != 0) {
                                wAlphaMode = (wAlphaMode + 3) % 4;
                            } else {
                                wAlphaMode = (wAlphaMode + 5) % 4;
                            }
                        }
                    } else if (PAD_001EAA60(2, 0xC) != 0) {
                        if (PAD_001EAA60(2, 4) != 0) {
                            n = wFrame - 1;
                            wFrame = (n > 1) ? n : 1;
                        } else {
                            n = wFrame + 1;
                            wFrame = (n < 0x63) ? n : 0x63;
                        }
                    }
                }
                if (PAD_001EAA60(1, 0x10) != 0) {
                    if (func_001A8720() & 1) {
                        flag = 1;
                        flag2 = 1;
                    }
                }
                if (PAD_001EAA60(1, 0x80) != 0) {
                    if (func_001A8720() & 1) {
                        flag2 = 1;
                    }
                }
                if (PAD_001EAA60(0, 0x20) != 0) {
                    flag2 = 1;
                }
                if (flag2 != 0) {
                    func_001EDCB0(index, wFrame, wAlphaMode, icolF, icolT, flag);
                }
                break;
            case 1:
                if (PAD_001EAA60(0, 0x4000) != 0) {
                    icolF[0] = 0x80;
                    icolF[1] = 0x80;
                    icolF[2] = 0x80;
                    icolF[3] = 0x40;
                }
                if (PAD_001EAA60(1, 0x1000) != 0) {
                    if (PAD_001EAA60(2, 0x80) != 0) {
                        if (icolF[3] > 0) {
                            icolF[3]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x20) != 0 && icolF[3] < 0xFF) {
                        icolF[3]++;
                    }
                } else {
                    if (PAD_001EAA60(2, 0x81) != 0) {
                        if (icolF[2] > 0) {
                            icolF[2]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x22) != 0) {
                        if (icolF[2] < 0xFF) {
                            icolF[2]++;
                        }
                    }
                    if (PAD_001EAA60(2, 0x41) != 0) {
                        if (icolF[1] > 0) {
                            icolF[1]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x12) != 0) {
                        if (icolF[1] < 0xFF) {
                            icolF[1]++;
                        }
                    }
                    if (PAD_001EAA60(2, 5) != 0) {
                        if (icolF[0] > 0) {
                            icolF[0]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0xA) != 0 && icolF[0] < 0xFF) {
                        icolF[0]++;
                    }
                }
                break;
            case 2:
                if (PAD_001EAA60(0, 0x4000) != 0) {
                    icolT[0] = 0x80;
                    icolT[1] = 0x80;
                    icolT[2] = 0x80;
                    icolT[3] = 0;
                }
                if (PAD_001EAA60(1, 0x1000) != 0) {
                    if (PAD_001EAA60(2, 0x80) != 0) {
                        if (icolT[3] > 0) {
                            icolT[3]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x20) != 0 && icolT[3] < 0xFF) {
                        icolT[3]++;
                    }
                } else {
                    if (PAD_001EAA60(2, 0x81) != 0) {
                        if (icolT[2] > 0) {
                            icolT[2]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x22) != 0) {
                        if (icolT[2] < 0xFF) {
                            icolT[2]++;
                        }
                    }
                    if (PAD_001EAA60(2, 0x41) != 0) {
                        if (icolT[1] > 0) {
                            icolT[1]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0x12) != 0) {
                        if (icolT[1] < 0xFF) {
                            icolT[1]++;
                        }
                    }
                    if (PAD_001EAA60(2, 5) != 0) {
                        if (icolT[0] > 0) {
                            icolT[0]--;
                        }
                    }
                    if (PAD_001EAA60(2, 0xA) != 0 && icolT[0] < 0xFF) {
                        icolT[0]++;
                    }
                }
                break;
            case 3:
                if (PAD_001EAA60(0, 0x4000) != 0) {
                    nBlurUse = 2;
                }
                if (PAD_001EAA60(0, 0x10) != 0) {
                    nBlurUse = 2;
                }
                if (PAD_001EAA60(0, 0xC0) != 0) {
                    nBlurUse = 1;
                }
                if (PAD_001EAA60(0, 0x40) != 0) {
                    nBlurUse = 0;
                }
                break;
            }
            if (PAD_001EAA60(2, 0xA000) != 0) {
                if (PAD_001EAA60(2, 0x8000) != 0) {
                    nBlurCur = (nBlurCur + 3) % 4;
                } else {
                    nBlurCur = (nBlurCur + 5) % 4;
                }
            }
        }
        if (page == 3) {
            Digits4_001EAA60 dig;
            char path[0x80];

            sub = index - 0x1E;
            num = obj->num;
            dig = D_00292F90;
            newnum = num;
            dig.d0 = num / 1000 % 10;
            dig.d1 = num / 100 % 10;
            dig.d2 = num / 10 % 10;
            dig.d3 = num % 10;
            if (PAD_001EAA60(0, 0xC0) != 0) {
                if (obj->anim != NULL) {
                    flag = PAD_001EAA60(1, 3) != 0 ? 1 : 0;
                    dir = PAD_001EAA60(0, 0x80) != 0 ? 1 : 0;
                    func_001FA810(0, 1);
                    snd = obj->sound;
                    if (snd >= 0) {
                        func_001F4CB0(snd);
                    }
                    func_001F1830(0x1E, 0);
                    func_001F1830(0x1F, 0);
                    func_001F1A00(0x1E, 1);
                    func_001F1A00(0x1F, 1);
                    func_001E1E70(sub ^ 1, 0, 5, dir);
                    func_001F0CD0(sub, 1, flag > 0);
                }
            }
            if (PAD_001EAA60(0, 0x600) != 0) {
                if (obj->anim != NULL) {
                    flag = PAD_001EAA60(0, 0x200) != 0 ? 1 : 0;
                    func_001FA810(0, 1);
                    func_001F1830(0x1E, 0);
                    func_001F1A00(0x1E, 1);
                    func_001F1550(index, 5);
                    ap = *(void *volatile *)&obj->anim; /* loaded before f202, as shipped */
                    func_001FA8A0(0, 1, flag + 8, obj->f202, index, ap);
                }
            }
            if (PAD_001EAA60(0, 0x20) != 0) {
                func_001FA810(0, 1);
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
                func_001F1830(0x1E, 0);
                func_001F1830(0x1F, 0);
                func_001F1A00(0x1E, 1);
                func_001F1A00(0x1F, 1);
            }
            if (PAD_001EAA60(0, 0x10) != 0) {
                func_001FA810(0, 1);
                if (obj->model->flags & 0x80000) {
                    obj->anim = NULL;
                } else if (obj->anim != NULL) {
                    func_00217B50((s32)obj->anim);
                    obj->anim = NULL;
                }
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
                func_0019B648(path, D_002CFB7D, func_001FFF90((s32)D_002CFA17), num, num);
                func_001FECB0(0x400, 1, path, 0, -1, 0, -1, lSzModel_LoadCameraCB, index);
            }
            if (PAD_001EAA60(2, 0x5000) != 0) {
                if (PAD_001EAA60(2, 0x1000) != 0) {
                    (&dig.d0)[nCameraCur] = ((&dig.d0)[nCameraCur] + 11) % 10;
                } else {
                    (&dig.d0)[nCameraCur] = ((&dig.d0)[nCameraCur] + 9) % 10;
                }
                newnum = (&dig.d0)[0] * 1000 + (&dig.d0)[1] * 100 + (&dig.d0)[2] * 10 + (&dig.d0)[3];
            }
            if (!(PAD_001EAA60(1, 3) & 0xFFFF)) {
                if (PAD_001EAA60(2, 8) != 0) {
                    if (obj->f202 < 0x3E7) {
                        obj->f202++;
                    }
                }
                if (PAD_001EAA60(2, 4) != 0) {
                    if (obj->f202 > 0) {
                        obj->f202--;
                    }
                }
            }
            if (PAD_001EAA60(2, 0x8000) != 0) {
                nCameraCur = (nCameraCur + 3) % 4;
            }
            if (PAD_001EAA60(2, 0x2000) != 0) {
                nCameraCur = (nCameraCur + 5) % 4;
            }
            if (newnum != num) {
                obj->num = newnum;
                func_001FA810(0, 1);
                if (obj->model->flags & 0x80000) {
                    obj->anim = NULL;
                } else if (obj->anim != NULL) {
                    func_00217B50((s32)obj->anim);
                    obj->anim = NULL;
                }
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
            }
        }
        if (page == 4) {
            Digits4_001EAA60 dig2;
            char path2[0x80];
            s32 num;
            s32 i;
            s32 flag;
            s32 newnum;

            num = obj->num;
            dig2 = D_00292FA0;
            newnum = num;
            dig2.d0 = num / 1000 % 10;
            dig2.d1 = num / 100 % 10;
            dig2.d2 = num / 10 % 10;
            dig2.d3 = num % 10;
            if (PAD_001EAA60(0, 0xC0) != 0) {
                flag = PAD_001EAA60(1, 3) != 0 ? 1 : 0;
                PAD_001EAA60(0, 0x80);
                func_001FA810(0, 1);
                func_001F4E50(0, 0x3D);
                func_001F4E50(0, 0x3E);
                func_001F4E50(0, 0x3F);
                func_001F1830(0x20, 0);
                func_001F1A00(0x20, 1);
                func_00202D60(5, -1);
                for (i = 0; i < 8; i++) {
                    func_00202810(5, i, NULL, obj->parts[i]);
                }
                func_001F4900(0, 0x3D, 0, 0, 0, 0, 0);
                func_001F4900(0, 0x3E, 0, 0, 0, 0, 0);
                func_001F4900(0, 0x3F, 0, 0, 0, 0, 0);
                if (obj->anim != NULL) {
                    func_001FA8A0(0, 1, flag + 8, obj->f202, index, obj->anim);
                }
            }
            if (PAD_001EAA60(0, 0x20) != 0) {
                func_001FA810(0, 1);
                func_001F4E50(0, 0x3D);
                func_001F4E50(0, 0x3E);
                func_001F4E50(0, 0x3F);
                func_001F1830(0x20, 0);
                func_001F1A00(0x20, 1);
            }
            if (PAD_001EAA60(0, 0x10) != 0) {
                func_001FA810(0, 1);
                if (obj->model->flags & 0x80000) {
                    obj->anim = NULL;
                } else if (obj->anim != NULL) {
                    func_00217B50((s32)obj->anim);
                    obj->anim = NULL;
                }
                func_001F4E50(0, 0x3D);
                func_001F4E50(0, 0x3E);
                func_001F4E50(0, 0x3F);
                func_0019B648(path2, D_002CFB7D, func_001FFF90((s32)D_002CFA17), num, num);
                func_001FECB0(0x400, 1, path2, 0, -1, 0, -1, lSzModel_LoadCameraCB, index);
            }
            if (PAD_001EAA60(2, 0x5000) != 0) {
                if (PAD_001EAA60(2, 0x1000) != 0) {
                    (&dig2.d0)[nCameraCur] = ((&dig2.d0)[nCameraCur] + 11) % 10;
                } else {
                    (&dig2.d0)[nCameraCur] = ((&dig2.d0)[nCameraCur] + 9) % 10;
                }
                newnum = (&dig2.d0)[0] * 1000 + (&dig2.d0)[1] * 100 + (&dig2.d0)[2] * 10 + (&dig2.d0)[3];
            }
            if (!(PAD_001EAA60(1, 3) & 0xFFFF)) {
                if (PAD_001EAA60(2, 8) != 0) {
                    if (obj->f202 < 0x3E7) {
                        obj->f202++;
                    }
                }
                if (PAD_001EAA60(2, 4) != 0) {
                    if (obj->f202 > 0) {
                        obj->f202--;
                    }
                }
            }
            if (PAD_001EAA60(2, 0x8000) != 0) {
                nCameraCur = (nCameraCur + 3) % 4;
            }
            if (PAD_001EAA60(2, 0x2000) != 0) {
                nCameraCur = (nCameraCur + 5) % 4;
            }
            if (newnum != num) {
                obj->num = newnum;
                func_001FA810(0, 1);
                if (obj->model->flags & 0x80000) {
                    obj->anim = NULL;
                } else if (obj->anim != NULL) {
                    func_00217B50((s32)obj->anim);
                    obj->anim = NULL;
                }
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
            }
        }
        if (page == 5) {
            Digits3_001EAA60 d3;
            Digits3_001EAA60 d3b;

            sub = index - 0x1E;
            d3 = D_00292FB0;
            d3.d0 = obj->f206 / 100 % 10;
            d3.d1 = obj->f206 / 10 % 10;
            d3.d2 = obj->f206 % 10;
            d3b = D_00292FC0;
            d3b.d0 = obj->f208 / 100 % 10;
            d3b.d1 = obj->f208 / 10 % 10;
            d3b.d2 = obj->f208 % 10;
            if (PAD_001EAA60(0, 0xC0) != 0) {
                dir = PAD_001EAA60(0, 0x80) != 0 ? 1 : 0;
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
                func_001F1830(0x1E, 0);
                func_001F1830(0x1F, 0);
                func_001F1A00(0x1E, 1);
                func_001F1A00(0x1F, 1);
                func_001E1E70(sub ^ 1, 0, 5, dir);
                func_001F0CD0(sub, 0, 0);
            }
            if (PAD_001EAA60(0, 0x40) != 0) {
                snd = obj->sound;
                if (snd >= 0) {
                    func_001F4CB0(snd);
                }
                func_001F1830(0x1E, 0);
                func_001F1830(0x1F, 0);
                func_001F1A00(0x1E, 1);
                func_001F1A00(0x1F, 1);
            }
            if (PAD_001EAA60(0, 0x10) != 0) {
                while (func_001FF350(0x800) != 0) {
                    func_001FF420();
                }
                func_001F4E50(-1, -1);
                func_001F3790();
            }
            switch (nEffCur2) {
            case 0:
                if (PAD_001EAA60(2, 0x2000) != 0) {
                    if (++nEffCur > 2) {
                        nEffCur = 0;
                        nEffCur2 = 1;
                    }
                } else if (PAD_001EAA60(2, 0x8000) != 0) {
                    if (--nEffCur < 0) {
                        nEffCur2 = 1;
                        nEffCur = 2;
                    }
                } else if (PAD_001EAA60(2, 0x5000) != 0) {
                    if (PAD_001EAA60(2, 0x1000) != 0) {
                        (&d3.d0)[nEffCur] = ((&d3.d0)[nEffCur] + 11) % 10;
                    } else {
                        (&d3.d0)[nEffCur] = ((&d3.d0)[nEffCur] + 9) % 10;
                    }
                    obj->f206 = (&d3.d0)[0] * 100 + (&d3.d0)[1] * 10 + (&d3.d0)[2];
                }
                break;
            case 1:
                if (PAD_001EAA60(2, 0x2000) != 0) {
                    if (++nEffCur > 2) {
                        nEffCur2 = 0;
                        nEffCur = 0;
                    }
                } else if (PAD_001EAA60(2, 0x8000) != 0) {
                    if (--nEffCur < 0) {
                        nEffCur2 = 0;
                        nEffCur = 2;
                    }
                } else if (PAD_001EAA60(2, 0x5000) != 0) {
                    if (PAD_001EAA60(2, 0x1000) != 0) {
                        (&d3b.d0)[nEffCur] = ((&d3b.d0)[nEffCur] + 11) % 10;
                    } else {
                        (&d3b.d0)[nEffCur] = ((&d3b.d0)[nEffCur] + 9) % 10;
                    }
                    obj->f208 = (&d3b.d0)[0] * 100 + (&d3b.d0)[1] * 10 + (&d3b.d0)[2];
                }
                break;
            }
        }
        if (page == 6) {
            if (PAD_001EAA60(0, 0xC0) != 0) {
                gSzModel_fRefLock = 1;
            }
            if (PAD_001EAA60(0, 0x40) != 0) {
                gSzModel_fRefLock = 0;
            }
            if (PAD_001EAA60(2, 4) != 0) {
                gSzModel_nRefLock = (gSzModel_nRefLock + obj->count - 1) % obj->count;
            }
            if (PAD_001EAA60(2, 8) != 0) {
                gSzModel_nRefLock = (gSzModel_nRefLock + obj->count + 1) % obj->count;
            }
        }
        if (page == 7) {
            if (PAD_001EAA60(2, 0x8000) != 0) {
                obj->pos[0] -= 0.5f;
            }
            if (PAD_001EAA60(2, 0x2000) != 0) {
                obj->pos[0] += 0.5f;
            }
            if (PAD_001EAA60(2, 0x4000) != 0) {
                obj->pos[1] -= 0.5f;
            }
            if (PAD_001EAA60(2, 0x1000) != 0) {
                obj->pos[1] += 0.5f;
            }
            if (PAD_001EAA60(2, 4) != 0) {
                obj->pos[2] -= 0.5f;
            }
            if (PAD_001EAA60(2, 8) != 0) {
                obj->pos[2] += 0.5f;
            }
            if (PAD_001EAA60(2, 0x80) != 0) {
                obj->rot[1] = (obj->rot[1] + 0xFF00) % 0x10000;
            }
            if (PAD_001EAA60(2, 0x20) != 0) {
                obj->rot[1] = (obj->rot[1] + 0x10100) % 0x10000;
            }
            if (PAD_001EAA60(2, 0x40) != 0) {
                obj->rot[0] = (obj->rot[0] + 0xFF00) % 0x10000;
            }
            if (PAD_001EAA60(2, 0x10) != 0) {
                obj->rot[0] = (obj->rot[0] + 0x10100) % 0x10000;
            }
            if (PAD_001EAA60(2, 1) != 0) {
                obj->rot[2] = (obj->rot[2] + 0xFF00) % 0x10000;
            }
            if (PAD_001EAA60(2, 2) != 0) {
                obj->rot[2] = (obj->rot[2] + 0x10100) % 0x10000;
            }
        }
        if (page == 8) {
            if (PAD_001EAA60(0, 0x4000) != 0) {
                func_001F25D0(index, NULL);
            }
            if (PAD_001EAA60(2, 0x81) != 0) {
                obj->v.x -= 0.01f;
            }
            if (PAD_001EAA60(2, 0x22) != 0) {
                obj->v.x += 0.01f;
            }
            if (PAD_001EAA60(2, 0x41) != 0) {
                obj->v.y -= 0.01f;
            }
            if (PAD_001EAA60(2, 0x12) != 0) {
                obj->v.y += 0.01f;
            }
            if (PAD_001EAA60(2, 5) != 0) {
                obj->v.z -= 0.01f;
            }
            if (PAD_001EAA60(2, 0xA) != 0) {
                obj->v.z += 0.01f;
            }
        }
        if (page == 9) {
            if (PAD_001EAA60(0, 0x4000) != 0) {
                func_001F1EE0(index, NULL);
            }
            if (PAD_001EAA60(2, 0x81) != 0) {
                obj->light[0] -= 0.01f;
            }
            if (PAD_001EAA60(2, 0x22) != 0) {
                obj->light[0] += 0.01f;
            }
            if (PAD_001EAA60(2, 0x41) != 0) {
                obj->light[1] -= 0.01f;
            }
            if (PAD_001EAA60(2, 0x12) != 0) {
                obj->light[1] += 0.01f;
            }
            if (PAD_001EAA60(2, 4) != 0) {
                obj->light[2] -= 0.01f;
            }
            if (PAD_001EAA60(2, 8) != 0) {
                obj->light[2] += 0.01f;
            }
        }
        if (page == 10) {
            if (PAD_001EAA60(0, 0x4000) != 0) {
                func_001F26E0(index, 0, NULL);
            }
            if (PAD_001EAA60(2, 0x8000) != 0) {
                obj->fog0 = (obj->fog0 + 3) % 4;
            }
            if (PAD_001EAA60(2, 0x2000) != 0) {
                obj->fog0 = (obj->fog0 + 5) % 4;
            }
            if (PAD_001EAA60(1, 0x1000) != 0) {
                if (PAD_001EAA60(2, 0x80) != 0) {
                    if (obj->col0[3] > 0) {
                        obj->col0[3]--;
                    }
                }
                if (PAD_001EAA60(2, 0x20) != 0) {
                    if (obj->col0[3] < 0xFF) {
                        obj->col0[3]++;
                    }
                }
            } else {
                if (PAD_001EAA60(2, 0x81) != 0) {
                    if (obj->col0[2] > 0) {
                        obj->col0[2]--;
                    }
                }
                if (PAD_001EAA60(2, 0x22) != 0) {
                    if (obj->col0[2] < 0xFF) {
                        obj->col0[2]++;
                    }
                }
                if (PAD_001EAA60(2, 0x41) != 0) {
                    if (obj->col0[1] > 0) {
                        obj->col0[1]--;
                    }
                }
                if (PAD_001EAA60(2, 0x12) != 0) {
                    if (obj->col0[1] < 0xFF) {
                        obj->col0[1]++;
                    }
                }
                if (PAD_001EAA60(2, 5) != 0) {
                    if (obj->col0[0] > 0) {
                        obj->col0[0]--;
                    }
                }
                if (PAD_001EAA60(2, 0xA) != 0) {
                    if (obj->col0[0] < 0xFF) {
                        obj->col0[0]++;
                    }
                }
            }
        }
        if (page == 11) {
            if (PAD_001EAA60(0, 0x4000) != 0) {
                func_001F2860(index, 1, NULL);
            }
            if (PAD_001EAA60(2, 0x8000) != 0) {
                obj->fog1 = (obj->fog1 + 3) % 4;
            }
            if (PAD_001EAA60(2, 0x2000) != 0) {
                obj->fog1 = (obj->fog1 + 5) % 4;
            }
            if (PAD_001EAA60(1, 0x1000) != 0) {
                if (PAD_001EAA60(2, 0x80) != 0) {
                    if (obj->col1[3] > 0) {
                        obj->col1[3]--;
                    }
                }
                if (PAD_001EAA60(2, 0x20) != 0) {
                    if (obj->col1[3] < 0xFF) {
                        obj->col1[3]++;
                    }
                }
            } else {
                if (PAD_001EAA60(2, 0x81) != 0) {
                    if (obj->col1[2] > 0) {
                        obj->col1[2]--;
                    }
                }
                if (PAD_001EAA60(2, 0x22) != 0) {
                    if (obj->col1[2] < 0xFF) {
                        obj->col1[2]++;
                    }
                }
                if (PAD_001EAA60(2, 0x41) != 0) {
                    if (obj->col1[1] > 0) {
                        obj->col1[1]--;
                    }
                }
                if (PAD_001EAA60(2, 0x12) != 0) {
                    if (obj->col1[1] < 0xFF) {
                        obj->col1[1]++;
                    }
                }
                if (PAD_001EAA60(2, 5) != 0) {
                    if (obj->col1[0] > 0) {
                        obj->col1[0]--;
                    }
                }
                if (PAD_001EAA60(2, 0xA) != 0) {
                    if (obj->col1[0] < 0xFF) {
                        obj->col1[0]++;
                    }
                }
            }
        }
        if (mode == 5 && nBlurUse != 0 && (func_001A8720() & 1)) {
            func_001EDCB0(index, wFrame, wAlphaMode, icolF, icolT, nBlurUse == 1 ? 0 : 1);
        }
        if (func_00205170() == 0) {
            s8 kind = obj->kind;

            if (kind == 5 && mode == 5) {
                if (page == 3) {
                    pos = 1000;
                    i = nCameraCur;
                    while (i-- != 0) {
                        pos /= 10;
                    }
                }
                if (page == 5) {
                    pos = 100;
                    i = nEffCur;
                    while (i-- != 0) {
                        pos /= 10;
                    }
                }
            }
            if (kind == 6 && mode == 0 && page == 4) {
                pos = 1000;
                i = nCameraCur;
                while (i-- != 0) {
                    pos /= 10;
                }
            }
        }
    }
    return 1;
}

#undef PAD_001EAA60
