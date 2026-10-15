#include "common.h"
#include "sce/libc.h"

s32 func_0019DC70(s32 arg0, void *arg1) {
    s32 temp_v0;

    if ((*(s32 *)((u8 *)arg1 + 8)) == 0) {
        (*(s32 *)((u8 *)arg1 + 4)) = 0;
        return 0;
    }
    temp_v0 = __sfvwrite(arg0, arg1);
    (*(s32 *)((u8 *)arg1 + 8)) = 0;
    (*(s32 *)((u8 *)arg1 + 4)) = 0;
    return temp_v0;
}

#define fp_0019DCB8 ((Fil *)arg0)

/* __sbprintf (newlib 1.9.0 vfprintf.c): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

s32 func_0019DCB8(void *arg0, const char *fmt, void *ap) {
    s32 ret;
    Fil fake;
    u8 buf[1024];

    fake.data = fp_0019DCB8->data;
    fake.flags = fp_0019DCB8->flags & ~0x0002;
    fake.file = fp_0019DCB8->file;
    fake.cookie = fp_0019DCB8->cookie;
    fake.write = fp_0019DCB8->write;

    fake.bf.base = fake.p = buf;
    fake.bf.size = fake.w = sizeof(buf);
    fake.lbfsize = 0;

    ret = func_0019DD70((vf_FILE *)&fake, fmt, ap);
    if (ret >= 0 && fflush((nl_FILE *)&fake))
        ret = -1;
    if (fake.flags & 0x0040)
        fp_0019DCB8->flags |= 0x0040;
    return ret;
}

#undef fp_0019DCB8

s32 func_0019DD70(vf_FILE *fp, const char *fmt0, void *ap) {
    do {
        if ((fp)->_data == 0)
            (fp)->_data = (vf_reent *)D_0028FA98;
        if (!(fp)->_data->__sdidinit)
            __sinit((fp)->_data);
    } while (0);
    return func_0019DDE8(fp->_data, fp, fmt0, ap);
}
