/* Movie player: stream file reads. */

#include "common.h"

typedef struct File_00243A90 {
    s32 disc;
    s32 size;
    s32 handle;
    s32 disc_size;
    u8 pad10[0x1C];
    u32 allocation;
    s32 fd;
} File_00243A90;

extern char D_0030F7F0[];
extern char D_0030F7F7[];
extern char D_0030F7F8[];
extern char D_0030F800[];
extern char D_0030F806[];
extern char D_0030F80C[];
extern char D_0030F816[];
extern char D_0030F839[];
extern char D_0030F854[];
extern char D_0030F86F[];

/* Opens movie stream file `filename` (from the CD). */
s32 strFileOpen(void *fileIn, s32 filename) {
    extern void func_0019B648();
    char path[256];
    char prefix[76];
    u8 mode[3];
    char *separator;
    File_00243A90 *file = fileIn;

    separator = func_001976D8((char *)filename, ':');
    if (separator != NULL) {
        s32 prefix_length;

        prefix_length = separator - (char *)filename;
        func_0019C2B8(prefix, (char *)filename, prefix_length);
        prefix[prefix_length] = 0;
        if (func_0019BC90(prefix, D_0030F7F0) == 0) {
            s32 i;
            s32 length;
            char *current;
            char *suffix;

            length = func_0019BEF0(separator + 1);
            file->disc = 1;
            for (i = 0; i < length; i++) {
                current = separator + i + 1;
                if (*current == '/') {
                    *current = '\\';
                }
                *current = func_0019D9E0(*current);
            }
            suffix = func_001976D8((char *)filename, ';') ? D_0030F7F7 : D_0030F7F8;
            func_0019B648(path, D_0030F7F8 + 3, separator + 1, suffix);
        } else {
            file->disc = 0;
            func_0019B648(path, D_0030F800, prefix, separator + 1);
        }
    } else {
        func_0019BDD8(prefix, D_0030F806);
        file->disc = 0;
        func_0019B648(path, D_0030F800, prefix, filename);
    }
    func_00199B50(D_0030F80C, path);
    if (file->disc != 0) {
        do {
        } while (func_00191A58(0) != 2);
        file->allocation = sceSifAllocIopHeap(0x28010);
        sceCdStInit(0x50, 5, ((file->allocation + 0xF) >> 4) << 4);
        if (sceCdSearchFile(&file->handle, path) == 0) {
            func_00199B50(D_0030F816, path);
            return 0;
        }
        file->size = file->disc_size;
        mode[0] = 0;
        mode[1] = 0;
        mode[2] = 0;
        sceCdStStart(file->handle, mode);
    } else {
        file->fd = func_0017FA98(path, 1);
        if (file->fd < 0) {
            func_00199B50(D_0030F839, path);
            return 0;
        }
        file->size = func_0017FEA0(file->fd, 0, 2);
        if (file->size < 0) {
            func_00199B50(D_0030F854, path, file->size);
            func_0017FD20(file->fd);
            return 0;
        }
        if (func_0017FEA0(file->fd, 0, 0) < 0) {
            func_00199B50(D_0030F86F, path);
            func_0017FD20(file->fd);
            return 0;
        }
    }
    return 1;
}

typedef struct {
    s32 unk00;
    u8 pad04[0x28];
    s32 unk2C;
    s32 unk30;
} Obj_00243D90;

/* Closes the movie stream file. */
s32 strFileClose(void *file) {
    Obj_00243D90 *p = (Obj_00243D90 *)file;

    if (p->unk00 != 0) {
        sceCdStStop();
        func_00182A28(p->unk2C);
    } else {
        func_0017FD20(p->unk30);
    }
    return 1;
}

typedef struct {
    f32 value;
} Float_00243DE0;

extern Float_00243DE0 D_0029B2F8;

/* Reads `size` bytes of the movie stream into `buff`. */
s32 strFileRead(s32 *file, s32 buff, s32 size, s32 arg3) {
    Float_00243DE0 sp48;
    s32 sp4C;
    s32 result;

    if (*file != 0) {
        sp48 = D_0029B2F8;
        while (1) {
            FlushCache(0);
            result = sceCdStRead(size >> 11, buff, 1, &sp4C);
            if (sp4C == 0) {
                break;
            }
            if (isWithAudio != 0) {
                audioDecPause(audioDec);
            }
            sceCdStStop();
            while (func_00191A58(0) != 2 || sceCdStStart(arg3, (u8 *)&sp48) == 0) {
            }
            if (isWithAudio != 0) {
                audioDecResume(audioDec);
            }
        }
        result <<= 11;
    } else {
        result = func_001800D8(file[12], buff, size);
    }
    return result;
}
