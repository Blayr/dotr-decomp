#include "common.h"
#include "game.h"

extern char ***D_0028F7A0;

s32 func_00197570(s32 reent_ptr, s32 arg1, s32 arg2) {
    const char *name = (const char *)arg1;
    s32 *offset = (s32 *)arg2;
    s32 len;
    char **p;
    const char *c;

    ((void (*)(s32))func_001966E8)(reent_ptr);

    if (!*D_0028F7A0)
        return 0;

    c = name;
    len = 0;
    while (*c && *c != '=') {
        c++;
        len++;
    }

    for (p = *D_0028F7A0; *p; ++p)
        if (!func_0019C100(*p, name, len))
            if (*(c = *p + len) == '=') {
                *offset = p - *D_0028F7A0;
                ((void (*)(s32))func_001966F0)(reent_ptr);
                return (s32)(++c);
            }
    ((void (*)(s32))func_001966F0)(reent_ptr);
    return 0;
}
