#include "common.h"
#include "sce/libc.h"

void func_001976B8(s32 arg0, s32 arg1) {
    s32 sp0[4];
    func_00197570(arg0, arg1, (s32) sp0);
}

char *func_001976D8(char *arg0, s32 arg1) {
    return func_0019BB00(arg0, arg1);
}

s32 func_001976F0(s32 p, s32 category, s32 locale) {
    if (locale) {
        if (func_0019BC90((const char *)locale, D_002BD270) && func_0019BC90((const char *)locale, D_002BD260))
            return 0;
        *(s32 *)(p + 0x30) = category;
        *(s32 *)(p + 0x34) = locale;
    }
    return (s32)D_002BD270;
}

s32 *func_00197780(void) {
    return &D_002BD230;
}

void func_00197790(s32 arg0, s32 arg1) {
    func_001976F0(D_0028FA98, arg0, arg1);
}

s32 *func_001977B8(void) {
    return ((s32 *(*)(s32))func_00197780)(D_0028FA98);
}

s32 func_001977D8(s32 *ptr, s32 fd, s32 pos, s32 whence) {
    s32 ret;
    D_003512F8 = 0;
    if ((ret = ((s32 (*)(s32, s32, s32))func_0017BFD8)(fd, pos, whence)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

typedef struct mb_reent { u8 pad0[0x3C]; s32 (*__cleanup)(s32); } mb_reent;
typedef struct mb_sbuf { u8 *_base; s32 _size; } mb_sbuf;
typedef struct mb_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    mb_sbuf _bf;
    s32 _lbfsize;
    void *_cookie;
    void *_read;
    void *_write;
    void *_seek;
    void *_close;
    mb_sbuf _ub;
    u8 *_up;
    s32 _ur;
    u8 _ubuf[3];
    u8 _nbuf[1];
    mb_sbuf _lb;
    s32 _blksize;
    s32 _offset;
    mb_reent *_data;
} mb_FILE;
typedef struct mb_stat { s16 st_dev; u16 st_ino; u32 st_mode; u8 pad8[0x68]; } mb_stat;

void func_00197838(void *arg0) {
    mb_FILE *fp = arg0;
    u32 size, couldbetty;
    void *p;
    mb_stat st;

    if (fp->_flags & 2) {
        fp->_bf._base = fp->_p = fp->_nbuf;
        fp->_bf._size = 1;
        return;
    }
    if (fp->_file < 0 || func_00197048((s32 *)fp->_data, fp->_file, &st) < 0) {
        couldbetty = 0;
        size = 1024;
        fp->_flags |= 0x800;
    } else {
        couldbetty = (st.st_mode & 0xF000) == 0x2000;
        size = 1024;
        if ((st.st_mode & 0xF000) == 0x8000 && fp->_seek == (void *)func_0019B870) {
            fp->_flags |= 0x400;
            fp->_blksize = 1024;
        } else
            fp->_flags |= 0x800;
    }
    if ((p = (void *)func_00197EB8((s32)fp->_data, size)) == NULL) {
        fp->_flags |= 2;
        fp->_bf._base = fp->_p = fp->_nbuf;
        fp->_bf._size = 1;
    } else {
        fp->_data->__cleanup = func_001969F0;
        fp->_flags |= 0x80;
        fp->_bf._base = fp->_p = (u8 *)p;
        fp->_bf._size = size;
        if (couldbetty && ((s32 (*)(s32))func_0017C090)(fp->_file))
            fp->_flags |= 1;
    }
}

void *func_00197990(s32 arg0, s32 arg1) {
    void *temp_s1;

    func_00198A08(D_0028FA98);
    temp_s1 = func_001979F8(D_0028FA98, arg0, arg1);
    func_00198A88(D_0028FA98);
    return temp_s1;
}

typedef struct ma_chunk {
    u32 prev_size;
    u32 size;
    struct ma_chunk *fd;
    struct ma_chunk *bk;
} ma_chunk;

#define ma_mem2chunk(mem) ((ma_chunk *)((char *)(mem) - 8))
#define ma_chunk2mem(p) ((void *)((char *)(p) + 8))
#define ma_chunksize(p) ((p)->size & ~(0x1 | 0x2))
#define ma_set_head(p, s) ((p)->size = (s))
#define ma_set_head_size(p, s) ((p)->size = (((p)->size & 0x1) | (s)))
#define ma_set_inuse_bit_at_offset(p, s) (((ma_chunk *)(((char *)(p)) + (s)))->size |= 0x1)
#define ma_chunk_at_offset(p, s) ((ma_chunk *)(((char *)(p)) + (s)))
#define ma_request2size(req) \
    (((unsigned long)((req) + (4 + 15)) < (unsigned long)(16 + 15)) ? 16 : (((req) + (4 + 15)) & ~(15)))
#define ma_long_sub_size_t(x, y) \
    (sizeof(long) > sizeof(u32) && x < y ? -(long)(y - x) : (long)(x - y))

void *func_001979F8(s32 reent_ptr, s32 arg1, s32 arg2) {
    u32 alignment = arg1;
    u32 bytes = arg2;
    u32 nb;
    char *m;
    ma_chunk *p;
    char *brk;
    ma_chunk *newp;
    u32 newsize;
    u32 leadsize;
    ma_chunk *remainder;
    long remainder_size;

    if (alignment <= 16)
        return (void *)func_00197EB8(reent_ptr, bytes);

    if (alignment < 16)
        alignment = 16;

    nb = ma_request2size(bytes);
    m = (char *)func_00197EB8(reent_ptr, nb + alignment + 16);

    if (m == NULL)
        return NULL;

    func_00198A08(reent_ptr);

    p = ma_mem2chunk(m);

    if ((((unsigned long)(m)) % alignment) == 0) {
    } else {
        brk = (char *)ma_mem2chunk(((unsigned long)(m + alignment - 1)) & -alignment);
        if ((long)(brk - (char *)(p)) < (long)16)
            brk = brk + alignment;

        newp = (ma_chunk *)brk;
        leadsize = brk - (char *)(p);
        newsize = ma_chunksize(p) - leadsize;

        ma_set_head(newp, newsize | 0x1);
        ma_set_inuse_bit_at_offset(newp, newsize);
        ma_set_head_size(p, leadsize);
        func_00196BE0(reent_ptr, (s32)ma_chunk2mem(p));
        p = newp;
    }

    remainder_size = ma_long_sub_size_t(ma_chunksize(p), nb);

    if (remainder_size >= (long)16) {
        remainder = ma_chunk_at_offset(p, nb);
        ma_set_head(remainder, remainder_size | 0x1);
        ma_set_head_size(p, nb);
        func_00196BE0(reent_ptr, (s32)ma_chunk2mem(remainder));
    }

    func_00198A88(reent_ptr);
    return ma_chunk2mem(p);
}

s32 func_00197BC0(s32 arg0) {
    s32 temp_s1;

    func_00198A08(D_0028FA98);
    temp_s1 = func_00197EB8(D_0028FA98, arg0);
    func_00198A88(D_0028FA98);
    return temp_s1;
}

s32 func_00197C18(s32 arg0) {
    func_00198A08(D_0028FA98);
    func_00196BE0(D_0028FA98, arg0);
    return func_00198A88(D_0028FA98);
}

#define malloc_unlock(r) ((void (*)(s32))func_00198A88)(r)
#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))
#define PREV_INUSE 0x1
#define SIZE_BITS 0x3
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_size = (s))
#define chunk_at_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define bin_at(i) ((mchunkptr)((char *)&(D_0028FAA8[2 * (i) + 2]) - 2 * SIZE_SZ))
#define top (bin_at(0)->fd)
#define last_remainder (bin_at(1))
#define binblocks (bin_at(0)->size)
#define MAX_SMALLBIN_SIZE 512
#define BINBLOCKWIDTH 4
#define smallbin_index(sz) (((unsigned long)(sz)) >> 3)
#define bin_index(sz)                                                                              \
    ((((sz) >> 9) == 0)      ? ((sz) >> 3)                                                         \
     : (((sz) >> 9) <= 4)    ? 56 + ((sz) >> 6)                                                    \
     : (((sz) >> 9) <= 20)   ? 91 + ((sz) >> 9)                                                    \
     : (((sz) >> 9) <= 84)   ? 110 + ((sz) >> 12)                                                  \
     : (((sz) >> 9) <= 340)  ? 119 + ((sz) >> 15)                                                  \
     : (((sz) >> 9) <= 1364) ? 124 + ((sz) >> 18)                                                  \
                             : 126)
#define idx2binblock(ix) ((unsigned long)1 << ((ix) / BINBLOCKWIDTH))
#define mark_binblock(ii) (binblocks |= idx2binblock(ii))
#define unlink(P, BK, FD)                                                                          \
    {                                                                                              \
        BK = P->bk;                                                                                \
        FD = P->fd;                                                                                \
        FD->bk = BK;                                                                               \
        BK->fd = FD;                                                                               \
    }
#define link_last_remainder(P)                                                                     \
    {                                                                                              \
        last_remainder->fd = last_remainder->bk = P;                                               \
        P->fd = P->bk = last_remainder;                                                            \
    }
#define frontlink(P, S, IDX, BK, FD)                                                               \
    {                                                                                              \
        if (S < MAX_SMALLBIN_SIZE) {                                                               \
            IDX = smallbin_index(S);                                                               \
            mark_binblock(IDX);                                                                    \
            BK = bin_at(IDX);                                                                      \
            FD = BK->fd;                                                                           \
            P->bk = BK;                                                                            \
            P->fd = FD;                                                                            \
            FD->bk = BK->fd = P;                                                                   \
        } else {                                                                                   \
            IDX = bin_index(S);                                                                    \
            BK = bin_at(IDX);                                                                      \
            FD = BK->fd;                                                                           \
            if (FD == BK) {                                                                        \
                mark_binblock(IDX);                                                                \
            } else {                                                                               \
                while (FD != BK && S < chunksize(FD))                                              \
                    FD = FD->fd;                                                                   \
                BK = FD->bk;                                                                       \
            }                                                                                      \
            P->bk = BK;                                                                            \
            P->fd = FD;                                                                            \
            FD->bk = BK->fd = P;                                                                   \
        }                                                                                          \
    }
#define MALLOC_ALIGNMENT 16
#define MALLOC_ALIGN_MASK (MALLOC_ALIGNMENT - 1)
#define MINSIZE (sizeof(struct malloc_chunk))
#define chunk2mem(p) ((void *)((char *)(p) + 2 * SIZE_SZ))
#define set_head_size(p, s) ((p)->size = (((p)->size & PREV_INUSE) | (s)))
#define initial_top ((mchunkptr)(bin_at(0)))

/* malloc_extend_top (newlib 1.9.0 mallocr.c): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void func_00197C60(s32 reent_ptr, u32 nb) {
    char *brk;
    INTERNAL_SIZE_T front_misalign;
    INTERNAL_SIZE_T correction;
    char *new_brk;
    INTERNAL_SIZE_T top_size;

    mchunkptr old_top = top;
    INTERNAL_SIZE_T old_top_size = chunksize(old_top);
    char *old_end = (char *)(chunk_at_offset(old_top, old_top_size));

    INTERNAL_SIZE_T sbrk_size = nb + D_0028FEB8 + MINSIZE;
    unsigned long pagesz = 4096;

    if (D_0028FEC0 != (char *)(-1))
        sbrk_size = (sbrk_size + (pagesz - 1)) & ~(pagesz - 1);

    brk = (char *)(func_0019B0A0((s32 *)reent_ptr, sbrk_size));

    if (brk == (char *)(-1) || (brk < old_end && old_top != initial_top))
        return;

    D_0028FED8.arena += sbrk_size;

    if (brk == old_end) {
        top_size = sbrk_size + old_top_size;
        set_head(top, top_size | PREV_INUSE);
    } else {
        if (D_0028FEC0 == (char *)(-1))
            D_0028FEC0 = brk;
        else
            D_0028FED8.arena += brk - (char *)old_end;

        front_misalign = (u32)chunk2mem(brk) & MALLOC_ALIGN_MASK;
        if (front_misalign > 0) {
            correction = (MALLOC_ALIGNMENT)-front_misalign;
            brk += correction;
        } else
            correction = 0;

        correction += pagesz - ((u32)(brk + sbrk_size) & (pagesz - 1));

        new_brk = (char *)(func_0019B0A0((s32 *)reent_ptr, correction));
        if (new_brk == (char *)(-1))
            return;

        D_0028FED8.arena += correction;

        top = (mchunkptr)brk;
        top_size = new_brk - brk + correction;
        set_head(top, top_size | PREV_INUSE);

        if (old_top != initial_top) {
            if (old_top_size < MINSIZE) {
                set_head(top, PREV_INUSE);
                return;
            }

            old_top_size = (old_top_size - 3 * SIZE_SZ) & ~MALLOC_ALIGN_MASK;
            set_head_size(old_top, old_top_size);
            chunk_at_offset(old_top, old_top_size)->size = SIZE_SZ | PREV_INUSE;
            chunk_at_offset(old_top, old_top_size + SIZE_SZ)->size = SIZE_SZ | PREV_INUSE;
            if (old_top_size >= MINSIZE)
                func_00196BE0(reent_ptr, chunk2mem(old_top));
        }
    }

    if ((unsigned long)D_0028FED8.arena > (unsigned long)D_0028FEC8)
        D_0028FEC8 = D_0028FED8.arena;
    if ((unsigned long)(D_0028FED8.arena) > (unsigned long)D_0028FED0)
        D_0028FED0 = D_0028FED8.arena;
}

#undef malloc_unlock
#undef SIZE_SZ
#undef PREV_INUSE
#undef SIZE_BITS
#undef chunksize
#undef set_head
#undef set_foot
#undef chunk_at_offset
#undef bin_at
#undef top
#undef last_remainder
#undef binblocks
#undef MAX_SMALLBIN_SIZE
#undef BINBLOCKWIDTH
#undef smallbin_index
#undef bin_index
#undef idx2binblock
#undef mark_binblock
#undef unlink
#undef link_last_remainder
#undef frontlink
#undef MALLOC_ALIGNMENT
#undef MALLOC_ALIGN_MASK
#undef MINSIZE
#undef chunk2mem
#undef set_head_size
#undef initial_top

#define malloc_unlock(r) ((void (*)(s32))func_00198A88)(r)
#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))
#define PREV_INUSE 0x1
#define SIZE_BITS 0x3
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_size = (s))
#define chunk_at_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define bin_at(i) ((mchunkptr)((char *)&(D_0028FAA8[2 * (i) + 2]) - 2 * SIZE_SZ))
#define top (bin_at(0)->fd)
#define last_remainder (bin_at(1))
#define binblocks (bin_at(0)->size)
#define MAX_SMALLBIN_SIZE 512
#define BINBLOCKWIDTH 4
#define smallbin_index(sz) (((unsigned long)(sz)) >> 3)
#define bin_index(sz)                                                                              \
    ((((sz) >> 9) == 0)      ? ((sz) >> 3)                                                         \
     : (((sz) >> 9) <= 4)    ? 56 + ((sz) >> 6)                                                    \
     : (((sz) >> 9) <= 20)   ? 91 + ((sz) >> 9)                                                    \
     : (((sz) >> 9) <= 84)   ? 110 + ((sz) >> 12)                                                  \
     : (((sz) >> 9) <= 340)  ? 119 + ((sz) >> 15)                                                  \
     : (((sz) >> 9) <= 1364) ? 124 + ((sz) >> 18)                                                  \
                             : 126)
#define idx2binblock(ix) ((unsigned long)1 << ((ix) / BINBLOCKWIDTH))
#define mark_binblock(ii) (binblocks |= idx2binblock(ii))
#define unlink(P, BK, FD)                                                                          \
    {                                                                                              \
        BK = P->bk;                                                                                \
        FD = P->fd;                                                                                \
        FD->bk = BK;                                                                               \
        BK->fd = FD;                                                                               \
    }
#define link_last_remainder(P)                                                                     \
    {                                                                                              \
        last_remainder->fd = last_remainder->bk = P;                                               \
        P->fd = P->bk = last_remainder;                                                            \
    }
#define frontlink(P, S, IDX, BK, FD)                                                               \
    {                                                                                              \
        if (S < MAX_SMALLBIN_SIZE) {                                                               \
            IDX = smallbin_index(S);                                                               \
            mark_binblock(IDX);                                                                    \
            BK = bin_at(IDX);                                                                      \
            FD = BK->fd;                                                                           \
            P->bk = BK;                                                                            \
            P->fd = FD;                                                                            \
            FD->bk = BK->fd = P;                                                                   \
        } else {                                                                                   \
            IDX = bin_index(S);                                                                    \
            BK = bin_at(IDX);                                                                      \
            FD = BK->fd;                                                                           \
            if (FD == BK) {                                                                        \
                mark_binblock(IDX);                                                                \
            } else {                                                                               \
                while (FD != BK && S < chunksize(FD))                                              \
                    FD = FD->fd;                                                                   \
                BK = FD->bk;                                                                       \
            }                                                                                      \
            P->bk = BK;                                                                            \
            P->fd = FD;                                                                            \
            FD->bk = BK->fd = P;                                                                   \
        }                                                                                          \
    }
#define MALLOC_ALIGNMENT 16
#define MALLOC_ALIGN_MASK (MALLOC_ALIGNMENT - 1)
#define MINSIZE (sizeof(struct malloc_chunk))
#define chunk2mem(p) ((void *)((char *)(p) + 2 * SIZE_SZ))
#define request2size(req)                                                                          \
    (((long)((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) < (long)(MINSIZE + MALLOC_ALIGN_MASK))         \
         ? ((MINSIZE + MALLOC_ALIGN_MASK) & ~(MALLOC_ALIGN_MASK))                                  \
         : (((req) + (SIZE_SZ + MALLOC_ALIGN_MASK)) & ~(MALLOC_ALIGN_MASK)))
#define set_inuse_bit_at_offset(p, s) (((mchunkptr)(((char *)(p)) + (s)))->size |= PREV_INUSE)
#define next_bin(b) ((mchunkptr)((char *)(b) + 2 * sizeof(mchunkptr)))
#define prev_bin(b) ((mchunkptr)((char *)(b) - 2 * sizeof(mchunkptr)))
#define first(b) ((b)->fd)
#define last(b) ((b)->bk)
#define MAX_SMALLBIN ((MAX_SMALLBIN_SIZE / 8) - 1)
#define is_small_request(nb) (nb < MAX_SMALLBIN_SIZE - 8)
#define clear_last_remainder (last_remainder->fd = last_remainder->bk = last_remainder)
#define long_sub_size_t(x, y) ((x < y) ? -((long)(y - x)) : (x - y));

/* _malloc_r (newlib 1.9.0 mallocr.c): adapted from the ICO decompilation via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void *func_00197EB8(s32 reent_ptr, s32 bytes) {
    extern void func_00197C60(s32, u32);
    mchunkptr victim;
    INTERNAL_SIZE_T victim_size;
    s32 idx;
    mchunkptr bin;
    mchunkptr remainder;
    long remainder_size;
    s32 remainder_index;
    unsigned long block;
    s32 startidx;
    mchunkptr fwd;
    mchunkptr bck;
    mchunkptr q;

    INTERNAL_SIZE_T nb = request2size(bytes);

    func_00198A08(reent_ptr);

    if (is_small_request(nb)) {
        idx = smallbin_index(nb);

        q = bin_at(idx);
        victim = last(q);

        if (victim != q) {
            victim_size = chunksize(victim);
            unlink(victim, bck, fwd);
            set_inuse_bit_at_offset(victim, victim_size);
            malloc_unlock(reent_ptr);
            return chunk2mem(victim);
        }

        idx += 2;

    } else {
        idx = bin_index(nb);
        bin = bin_at(idx);

        for (victim = last(bin); victim != bin; victim = victim->bk) {
            victim_size = chunksize(victim);
            remainder_size = long_sub_size_t(victim_size, nb);

            if (remainder_size >= (long)MINSIZE) {
                --idx;
                break;
            }

            else if (remainder_size >= 0) {
                unlink(victim, bck, fwd);
                set_inuse_bit_at_offset(victim, victim_size);
                malloc_unlock(reent_ptr);
                return chunk2mem(victim);
            }
        }

        ++idx;
    }

    if ((victim = last_remainder->fd) != last_remainder) {
        victim_size = chunksize(victim);
        remainder_size = long_sub_size_t(victim_size, nb);

        if (remainder_size >= (long)MINSIZE) {
            remainder = chunk_at_offset(victim, nb);
            set_head(victim, nb | PREV_INUSE);
            link_last_remainder(remainder);
            set_head(remainder, remainder_size | PREV_INUSE);
            set_foot(remainder, remainder_size);
            malloc_unlock(reent_ptr);
            return chunk2mem(victim);
        }

        clear_last_remainder;

        if (remainder_size >= 0) {
            set_inuse_bit_at_offset(victim, victim_size);
            malloc_unlock(reent_ptr);
            return chunk2mem(victim);
        }

        frontlink(victim, victim_size, remainder_index, bck, fwd);
    }

    if ((block = idx2binblock(idx)) <= binblocks) {
        if ((block & binblocks) == 0) {
            idx = (idx & ~(BINBLOCKWIDTH - 1)) + BINBLOCKWIDTH;
            block <<= 1;
            while ((block & binblocks) == 0) {
                idx += BINBLOCKWIDTH;
                block <<= 1;
            }
        }

        for (;;) {
            startidx = idx;
            q = bin = bin_at(idx);

            do {
                for (victim = last(bin); victim != bin; victim = victim->bk) {
                    victim_size = chunksize(victim);
                    remainder_size = long_sub_size_t(victim_size, nb);

                    if (remainder_size >= (long)MINSIZE) {
                        remainder = chunk_at_offset(victim, nb);
                        set_head(victim, nb | PREV_INUSE);
                        unlink(victim, bck, fwd);
                        link_last_remainder(remainder);
                        set_head(remainder, remainder_size | PREV_INUSE);
                        set_foot(remainder, remainder_size);
                        malloc_unlock(reent_ptr);
                        return chunk2mem(victim);
                    }

                    else if (remainder_size >= 0) {
                        set_inuse_bit_at_offset(victim, victim_size);
                        unlink(victim, bck, fwd);
                        malloc_unlock(reent_ptr);
                        return chunk2mem(victim);
                    }
                }

                bin = next_bin(bin);

                if (idx < MAX_SMALLBIN) {
                    bin = next_bin(bin);
                    ++idx;
                }
            } while ((++idx & (BINBLOCKWIDTH - 1)) != 0);

            do {
                if ((startidx & (BINBLOCKWIDTH - 1)) == 0) {
                    binblocks &= ~block;
                    break;
                }
                --startidx;
                q = prev_bin(q);
            } while (first(q) == q);

            if ((block <<= 1) <= binblocks && (block != 0)) {
                while ((block & binblocks) == 0) {
                    idx += BINBLOCKWIDTH;
                    block <<= 1;
                }
            } else
                break;
        }
    }

    remainder_size = long_sub_size_t(chunksize(top), nb);
    if (chunksize(top) < nb || remainder_size < (long)MINSIZE) {
        func_00197C60(reent_ptr, nb);
        remainder_size = long_sub_size_t(chunksize(top), nb);
        if (chunksize(top) < nb || remainder_size < (long)MINSIZE) {
            malloc_unlock(reent_ptr);
            return 0;
        }
    }

    victim = top;
    set_head(victim, nb | PREV_INUSE);
    top = chunk_at_offset(victim, nb);
    set_head(top, remainder_size | PREV_INUSE);
    malloc_unlock(reent_ptr);
    return chunk2mem(victim);
}

#undef malloc_unlock
#undef SIZE_SZ
#undef PREV_INUSE
#undef SIZE_BITS
#undef chunksize
#undef set_head
#undef set_foot
#undef chunk_at_offset
#undef bin_at
#undef top
#undef last_remainder
#undef binblocks
#undef MAX_SMALLBIN_SIZE
#undef BINBLOCKWIDTH
#undef smallbin_index
#undef bin_index
#undef idx2binblock
#undef mark_binblock
#undef unlink
#undef link_last_remainder
#undef frontlink
#undef MALLOC_ALIGNMENT
#undef MALLOC_ALIGN_MASK
#undef MINSIZE
#undef chunk2mem
#undef request2size
#undef set_inuse_bit_at_offset
#undef next_bin
#undef prev_bin
#undef first
#undef last
#undef MAX_SMALLBIN
#undef is_small_request
#undef clear_last_remainder
#undef long_sub_size_t

s32 func_001985E0(void *r, s32 *pwc, const char *s, u32 n, s32 *state) {
    s32 dummy;
    u8 *t = (u8 *)s;

    if (pwc == NULL)
        pwc = &dummy;
    if (s != NULL && n == 0)
        return -1;
    if (s == NULL)
        return 0;
    *pwc = (s32)*t;
    return (*t != '\0');
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198618);

INCLUDE_ASM("asm/nonmatchings/main_034", func_001986F8);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198790);

INCLUDE_ASM("asm/nonmatchings/main_034", func_00198840);

/* memset: newlib's hand-written r5900 assembly (libc/machine/r5900/memset.S), kept as asm; identified via kfiv-decomp (MIT), see THIRD_PARTY_NOTICES.md */

void *func_00198948(void *dst, s32 c, u32 n) {
    register s32 r4 __asm__("$4");

    __asm__ __volatile__(
        "	.set	noreorder\n"
        "	sltiu	$2,$6,0x8\n"
        "	bnez	$2,_func_00198948_001989C8\n"
        "	daddu	$3,$4,$0\n"
        "	andi	$2,$4,0xF\n"
        "	bnez	$2,_func_00198948_001989C8\n"
        "	daddu	$7,$4,$0\n"
        "	andi	$9,$5,0xFF\n"
        "	sltiu	$10,$6,0x20\n"
        "	daddu	$8,$9,$0\n"
        "	dsll	$3,$8,8\n"
        "	or	$8,$3,$9\n"
        "	pcpyh	$3,$8\n"
        "	bnez	$10,_func_00198948_001989B4\n"
        "	sltiu	$2,$6,0x8\n"
        "	pcpyld	$8,$3,$3\n"
        "_func_00198948_00198984:\n"
        "	sq	$8,0x0($7)\n"
        "	addiu	$6,$6,-0x20\n"
        "	addiu	$7,$7,0x10\n"
        "	sltiu	$2,$6,0x20\n"
        "	sq	$8,0x0($7)\n"
        "	beqz	$2,_func_00198948_00198984\n"
        "	addiu	$7,$7,0x10\n"
        "	b	_func_00198948_001989B4\n"
        "	sltiu	$2,$6,0x8\n"
        "_func_00198948_001989A8:\n"
        "	addiu	$6,$6,-0x8\n"
        "	addiu	$7,$7,0x8\n"
        "	sltiu	$2,$6,0x8\n"
        "_func_00198948_001989B4:\n"
        "	nop\n"
        "	nop\n"
        "	beql	$2,$0,_func_00198948_001989A8\n"
        "	sd	$3,0x0($7)\n"
        "	daddu	$3,$7,$0\n"
        "_func_00198948_001989C8:\n"
        "	lui	$2,(0xFFFFFFFF >> 16)\n"
        "	addiu	$6,$6,-0x1\n"
        "	ori	$2,$2,(0xFFFFFFFF & 0xFFFF)\n"
        "	beq	$6,$2,_func_00198948_00198A00\n"
        "	nop\n"
        "	lui	$2,(0xFFFFFFFF >> 16)\n"
        "	ori	$2,$2,(0xFFFFFFFF & 0xFFFF)\n"
        "_func_00198948_001989E4:\n"
        "	sb	$5,0x0($3)\n"
        "	addiu	$6,$6,-0x1\n"
        "	addiu	$3,$3,0x1\n"
        "	nop\n"
        "	nop\n"
        "	bne	$6,$2,_func_00198948_001989E4\n"
        "	nop\n"
        "_func_00198948_00198A00:\n"
        "	.set	reorder\n"
        : "=r"(r4));
    return (void *)r4;
}

void func_00198A08(s32 r) {
    s32 id = func_0017B7D0();

    if (D_0028FF00 == id) {
        D_0028FF04++;
    } else {
        func_0017B920(D_0028D114);
        D_0028FF00 = id;
        D_0028FF04++;
    }
}

s32 func_00198A88(s32 r) {
    if (--D_0028FF04 == 0) {
        D_0028FF00 = -1;
        return ((s32 (*)(s32))func_0017B900)(D_0028D114);
    }
}

i2b_Bigint *func_00198AD8(void *ptr, s32 k) {
    s32 x;
    i2b_Bigint *rv;

    if (*(i2b_Bigint ***)((u8 *)ptr + 0x4C) == NULL) {
        *(i2b_Bigint ***)((u8 *)ptr + 0x4C) = (i2b_Bigint **)func_00195140(ptr, sizeof(i2b_Bigint *), 15 + 1);
        if (*(i2b_Bigint ***)((u8 *)ptr + 0x4C) == NULL)
            return NULL;
    }
    if ((rv = (*(i2b_Bigint ***)((u8 *)ptr + 0x4C))[k]) != 0) {
        (*(i2b_Bigint ***)((u8 *)ptr + 0x4C))[k] = rv->next;
    } else {
        x = 1 << k;
        rv = (i2b_Bigint *)func_00195140(ptr, 1, sizeof(i2b_Bigint) + (x - 1) * sizeof(rv->x));
        if (rv == NULL) return NULL;
        rv->k = k;
        rv->maxwds = x;
    }
    rv->sign = rv->wds = 0;
    return rv;
}

void func_00198B80(void *arg0, void *arg1) {
    void **temp_v0;

    if (arg1 != NULL) {
        temp_v0 = ((*(s32 *)((u8 *)arg1 + 4)) * 4) + (*(s32 *)((u8 *)arg0 + 0x4C));
        (*(void **)arg1) = (void *) *temp_v0;
        *temp_v0 = arg1;
    }
}

i2b_Bigint *func_00198BB0(void *ptr, i2b_Bigint *b, s32 m, s32 a) {
    s32 i, wds;
    u32 *x, y;
    u32 xi, z;
    i2b_Bigint *b1;

    wds = b->wds;
    x = b->x;
    i = 0;
    do {
        xi = *x;
        y = (xi & 0xffff) * m + a;
        z = (xi >> 16) * m + (y >> 16);
        a = (s32)(z >> 16);
        *x++ = (z << 16) + (y & 0xffff);
    } while (++i < wds);
    if (a) {
        if (wds >= b->maxwds) {
            b1 = func_00198AD8(ptr, b->k + 1);
            func_00198790((char *)&b1->sign, (char *)&b->sign, b->wds * sizeof(s32) + 2 * sizeof(s32));
            func_00198B80(ptr, b);
            b = b1;
        }
        b->x[wds++] = a;
        b->wds = wds;
    }
    return b;
}

i2b_Bigint *func_00198CB8(void *ptr, const char *s, s32 nd0, s32 nd, u32 y9) {
    i2b_Bigint *b;
    s32 i, k;
    s32 x, y;

    x = (nd + 8) / 9;
    for (k = 0, y = 1; x > y; y <<= 1, k++);
    b = func_00198AD8(ptr, k);
    b->x[0] = y9;
    b->wds = 1;

    i = 9;
    if (9 < nd0) {
        s += 9;
        do
            b = func_00198BB0(ptr, b, 10, *s++ - '0');
        while (++i < nd0);
        s++;
    } else
        s += 10;
    for (; i < nd; i++)
        b = func_00198BB0(ptr, b, 10, *s++ - '0');
    return b;
}

s32 func_00198DE8(u32 x) {
    s32 k = 0;

    if (!(x & 0xffff0000)) {
        k = 16;
        x <<= 16;
    }
    if (!(x & 0xff000000)) {
        k += 8;
        x <<= 8;
    }
    if (!(x & 0xf0000000)) {
        k += 4;
        x <<= 4;
    }
    if (!(x & 0xc0000000)) {
        k += 2;
        x <<= 2;
    }
    if (!(x & 0x80000000)) {
        k++;
        if (!(x & 0x40000000))
            return 32;
    }
    return k;
}

s32 func_00198E68(u32 *y) {
    s32 k;
    u32 x = *y;

    if (x & 7) {
        if (x & 1)
            return 0;
        if (x & 2) {
            *y = x >> 1;
            return 1;
        }
        *y = x >> 2;
        return 2;
    }
    k = 0;
    if (!(x & 0xffff)) {
        k = 16;
        x >>= 16;
    }
    if (!(x & 0xff)) {
        k += 8;
        x >>= 8;
    }
    if (!(x & 0xf)) {
        k += 4;
        x >>= 4;
    }
    if (!(x & 0x3)) {
        k += 2;
        x >>= 2;
    }
    if (!(x & 1)) {
        k++;
        x >>= 1;
        if (!x & 1)
            return 32;
    }
    *y = x;
    return k;
}

i2b_Bigint *func_00198F28(void *ptr, s32 i) {
    i2b_Bigint *b;

    b = func_00198AD8(ptr, 1);
    b->x[0] = i;
    b->wds = 1;
    return b;
}

#define MU_Storeinc(a, b, c) (((u16 *)a)[1] = (u16)b, ((u16 *)a)[0] = (u16)c, a++)

i2b_Bigint *func_00198F60(void *ptr, i2b_Bigint *a, i2b_Bigint *b) {
    i2b_Bigint *c;
    s32 k, wa, wb, wc;
    u32 carry, y, z;
    u32 *x, *xa, *xae, *xb, *xbe, *xc, *xc0;
    u32 z2;

    if (a->wds < b->wds) {
        c = a;
        a = b;
        b = c;
    }
    k = a->k;
    wa = a->wds;
    wb = b->wds;
    wc = wa + wb;
    if (wc > a->maxwds)
        k++;
    c = func_00198AD8(ptr, k);
    for (x = c->x, xa = x + wc; x < xa; x++)
        *x = 0;
    xa = a->x;
    xae = xa + wa;
    xb = b->x;
    xbe = xb + wb;
    xc0 = c->x;
    for (; xb < xbe; xb++, xc0++) {
        if ((y = *xb & 0xffff) != 0) {
            x = xa;
            xc = xc0;
            carry = 0;
            do {
                z = (*x & 0xffff) * y + (*xc & 0xffff) + carry;
                carry = z >> 16;
                z2 = (*x++ >> 16) * y + (*xc >> 16) + carry;
                carry = z2 >> 16;
                MU_Storeinc(xc, z2, z);
            } while (x < xae);
            *xc = carry;
        }
        if ((y = *xb >> 16) != 0) {
            x = xa;
            xc = xc0;
            carry = 0;
            z2 = *xc;
            do {
                z = (*x & 0xffff) * y + (*xc >> 16) + carry;
                carry = z >> 16;
                MU_Storeinc(xc, z, z2);
                z2 = (*x++ >> 16) * y + (*xc & 0xffff) + carry;
                carry = z2 >> 16;
            } while (x < xae);
            *xc = z2;
        }
    }
    for (xc0 = c->x, xc = xc0 + wc; wc > 0 && !*--xc; --wc)
        ;
    c->wds = wc;
    return c;
}

i2b_Bigint *func_00199170(void *arg0, i2b_Bigint *b, s32 k) {
    p5_reent *ptr = arg0;
    i2b_Bigint *b1, *p5, *p51;
    s32 i;

    if ((i = k & 3))
        b = func_00198BB0(ptr, b, D_002BD274[i], 0);

    if (!(k >>= 2))
        return b;
    if (!(p5 = ptr->_p5s)) {
        p5 = ptr->_p5s = func_00198F28(ptr, 625);
        p5->next = 0;
    }
    for (;;) {
        if (k & 1) {
            b1 = func_00198F60(ptr, b, p5);
            func_00198B80(ptr, b);
            b = b1;
        }
        if (!(k >>= 1))
            break;
        if (!(p51 = p5->next)) {
            p51 = p5->next = func_00198F60(ptr, p5, p5);
            p51->next = 0;
        }
        p5 = p51;
    }
    return b;
}

i2b_Bigint *func_00199270(void *ptr, i2b_Bigint *b, s32 k) {
    s32 i, k1, n, n1;
    i2b_Bigint *b1;
    u32 *x, *x1, *xe, z;

    n = k >> 5;
    k1 = b->k;
    n1 = n + b->wds + 1;
    for (i = b->maxwds; n1 > i; i <<= 1)
        k1++;
    b1 = func_00198AD8(ptr, k1);
    x1 = b1->x;
    for (i = 0; i < n; i++)
        *x1++ = 0;
    x = b->x;
    xe = x + b->wds;
    if (k &= 0x1f) {
        k1 = 32 - k;
        z = 0;
        do {
            *x1++ = *x << k | z;
            z = *x++ >> k1;
        } while (x < xe);
        if ((*x1 = z) != 0)
            ++n1;
    } else
        do
            *x1++ = *x++;
        while (x < xe);
    b1->wds = n1 - 1;
    func_00198B80(ptr, b);
    return b1;
}

s32 func_001993C8(mcmp_Bigint *a, mcmp_Bigint *b) {
    u32 *xa, *xa0, *xb, *xb0;
    s32 i, j;

    i = a->wds;
    j = b->wds;
    if (i -= j)
        return i;
    xa0 = a->x;
    xa = xa0 + j;
    xb0 = b->x;
    xb = xb0 + j;
    for (;;) {
        if (*--xa != *--xb)
            return *xa < *xb ? -1 : 1;
        if (xa <= xa0)
            break;
    }
    return 0;
}

#define md_Storeinc(a, b, c) (((u16 *)a)[1] = (u16)b, ((u16 *)a)[0] = (u16)c, a++)

i2b_Bigint *func_00199430(void *ptr, i2b_Bigint *a, i2b_Bigint *b) {
    s32 i, wa, wb;
    i2b_Bigint *c;
    s32 borrow, y;
    u32 *xa, *xae, *xb, *xbe, *xc;
    s32 z;

    i = func_001993C8((mcmp_Bigint *)a, (mcmp_Bigint *)b);
    if (!i) {
        c = func_00198AD8(ptr, 0);
        c->wds = 1;
        c->x[0] = 0;
        return c;
    }
    if (i < 0) {
        c = a;
        a = b;
        b = c;
        i = 1;
    } else
        i = 0;
    c = func_00198AD8(ptr, a->k);
    c->sign = i;
    wa = a->wds;
    xa = a->x;
    xae = xa + wa;
    wb = b->wds;
    xb = b->x;
    xbe = xb + wb;
    xc = c->x;
    borrow = 0;
    do {
        y = (*xa & 0xffff) - (*xb & 0xffff) + borrow;
        borrow = y >> 16;
        z = (*xa++ >> 16) - (*xb++ >> 16) + borrow;
        borrow = z >> 16;
        md_Storeinc(xc, z, y);
    } while (xb < xbe);
    while (xa < xae) {
        y = (*xa & 0xffff) + borrow;
        borrow = y >> 16;
        z = (*xa++ >> 16) + borrow;
        borrow = z >> 16;
        md_Storeinc(xc, z, y);
    }
    while (!*--xc)
        wa--;
    c->wds = wa;
    return c;
}

double func_001995C0(double _x) {
    ulp_du x, a;
    s32 L;

    x.d = _x;
    L = (x.i[1] & 0x7ff00000) - (53 - 1) * 0x100000;
    if (L > 0) {
        a.i[1] = L;
        a.i[0] = 0;
    } else {
        L = -L >> 20;
        if (L < 20) {
            a.i[1] = 0x80000 >> L;
            a.i[0] = 0;
        } else {
            a.i[1] = 0;
            L -= 20;
            a.i[0] = L >= 31 ? 1 : 1 << (31 - L);
        }
    }
    return a.d;
}

double func_00199690(i2b_Bigint *a, s32 *e) {
    u32 *xa, *xa0, w, y, z;
    s32 k;
    b2d_du d;

    xa0 = a->x;
    xa = xa0 + a->wds;
    y = *--xa;
    k = func_00198DE8(y);
    *e = 32 - k;
    if (k < 11) {
        d.i[1] = 0x3ff00000 | y >> (11 - k);
        w = xa > xa0 ? *--xa : 0;
        d.i[0] = y << ((32 - 11) + k) | w >> (11 - k);
        goto ret_d;
    }
    z = xa > xa0 ? *--xa : 0;
    if (k -= 11) {
        d.i[1] = 0x3ff00000 | y << k | z >> (32 - k);
        y = xa > xa0 ? *--xa : 0;
        d.i[0] = z << k | y >> (32 - k);
    } else {
        d.i[1] = 0x3ff00000 | y;
        d.i[0] = z;
    }
ret_d:
    return d.d;
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_00199828);

double func_001999B0(i2b_Bigint *a, i2b_Bigint *b) {
    ratio_du da, db;
    s32 k, ka, kb;

    da.d = func_00199690(a, &ka);
    db.d = func_00199690(b, &kb);
    k = ka - kb + 32 * (a->wds - b->wds);
    if (k > 0)
        da.i[1] += k * 0x100000;
    else {
        k = -k;
        db.i[1] += k * 0x100000;
    }
    return da.d / db.d;
}

double func_00199A80(s32 dig) {
    double v = 1.0;

    if (dig < 24)
        return D_002BD288[dig];
    while (dig > 0) {
        v *= 10;
        dig--;
    }
    return v;
}

s32 func_00199AF0(vf_reent *ptr, const char *fmt, ...) {
    s32 ret;
    __builtin_va_list ap;

    __builtin_stdarg_start(ap, fmt);
    ret = func_0019DDE8(ptr, *(vf_FILE **)((u8 *)ptr + 8), fmt, ap);
    __builtin_va_end(ap);
    return ret;
}

typedef __builtin_va_list va_list;
#define va_start(v, l) __builtin_stdarg_start((v), l)
#define va_end(v) __builtin_va_end(v)

void func_00199B50(const char *fmt, ...) {
    s32 ret;
    va_list ap;

    va_start(ap, fmt);
    (*(vf_FILE **)(D_0028FA98 + 8))->_data = (vf_reent *)D_0028FA98;
    ret = func_0019DD70(*(vf_FILE **)(D_0028FA98 + 8), fmt, ap);
    va_end(ap);
}

/* qsort (newlib 1.x qsort.c, 4.4BSD) */

typedef s32 (*cmp_t_00199BC0)(const void *, const void *);

#define min(a, b) (a) < (b) ? a : b

#define swapcode(TYPE, parmi, parmj, n) {         \
        long i = (n) / sizeof(TYPE);              \
        register TYPE *pi = (TYPE *)(parmi);      \
        register TYPE *pj = (TYPE *)(parmj);      \
        do {                                      \
            register TYPE t = *pi;                \
            *pi++ = *pj;                          \
            *pj++ = t;                            \
        } while (--i > 0);                        \
    }

#define SWAPINIT(a, es) swaptype = ((char *)a - (char *)0) % sizeof(long) || \
    es % sizeof(long) ? 2 : es == sizeof(long) ? 0 : 1;

static inline void swapfunc_00199BC0(char *a, char *b, int n, int swaptype) {
    if (swaptype <= 1)
        swapcode(long, a, b, n)
    else
        swapcode(char, a, b, n)
}

#define swap(a, b)                          \
    if (swaptype == 0) {                    \
        long t = *(long *)(a);              \
        *(long *)(a) = *(long *)(b);        \
        *(long *)(b) = t;                   \
    } else                                  \
        swapfunc_00199BC0(a, b, es, swaptype)

#define vecswap(a, b, n) if ((n) > 0) swapfunc_00199BC0(a, b, n, swaptype)

static inline char *med3_00199BC0(char *a, char *b, char *c, cmp_t_00199BC0 cmp) {
    return cmp(a, b) < 0 ?
           (cmp(b, c) < 0 ? b : (cmp(a, c) < 0 ? c : a))
           : (cmp(b, c) > 0 ? b : (cmp(a, c) < 0 ? a : c));
}

void func_00199BC0(s32 arg0, u32 n, u32 es, void (*arg3)(void)) {
    cmp_t_00199BC0 cmp = (cmp_t_00199BC0)arg3;
    void *a = (void *)arg0;
    char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
    int d, r, swaptype, swap_cnt;

loop:
    SWAPINIT(a, es);
    swap_cnt = 0;
    if (n < 7) {
        for (pm = (char *)a + es; pm < (char *)a + n * es; pm += es)
            for (pl = pm; pl > (char *)a && cmp(pl - es, pl) > 0; pl -= es)
                swap(pl, pl - es);
        return;
    }
    pm = (char *)a + (n / 2) * es;
    if (n > 7) {
        pl = a;
        pn = (char *)a + (n - 1) * es;
        if (n > 40) {
            d = (n / 8) * es;
            pl = med3_00199BC0(pl, pl + d, pl + 2 * d, cmp);
            pm = med3_00199BC0(pm - d, pm, pm + d, cmp);
            pn = med3_00199BC0(pn - 2 * d, pn - d, pn, cmp);
        }
        pm = med3_00199BC0(pl, pm, pn, cmp);
    }
    swap(a, pm);
    pa = pb = (char *)a + es;

    pc = pd = (char *)a + (n - 1) * es;
    for (;;) {
        while (pb <= pc && (r = cmp(pb, a)) <= 0) {
            if (r == 0) {
                swap_cnt = 1;
                swap(pa, pb);
                pa += es;
            }
            pb += es;
        }
        while (pb <= pc && (r = cmp(pc, a)) >= 0) {
            if (r == 0) {
                swap_cnt = 1;
                swap(pc, pd);
                pd -= es;
            }
            pc -= es;
        }
        if (pb > pc)
            break;
        swap(pb, pc);
        swap_cnt = 1;
        pb += es;
        pc -= es;
    }
    if (swap_cnt == 0) {
        for (pm = (char *)a + es; pm < (char *)a + n * es; pm += es)
            for (pl = pm; pl > (char *)a && cmp(pl - es, pl) > 0; pl -= es)
                swap(pl, pl - es);
        return;
    }

    pn = (char *)a + n * es;
    r = min(pa - (char *)a, pb - pa);
    vecswap(a, pb - r, r);
    r = min(pd - pc, pn - pd - es);
    vecswap(pb, pn - r, r);
    if ((r = pb - pa) > es)
        func_00199BC0((s32)a, r / es, es, (void (*)(void))cmp);
    if ((r = pd - pc) > es) {
        a = pn - r;
        n = r / es;
        goto loop;
    }
}

#undef min
#undef swapcode
#undef SWAPINIT
#undef swap
#undef vecswap

void func_0019A5B0(s64 arg0) {
    (*(u64 *)((u8 *)D_0028FA98 + 0xA8)) = (u64) ((u64) (arg0 << 0x20) >> 0x20);
}

s32 func_0019A5C8(void) {
    u8 *r = (u8 *)D_0028FA98;

    *(u64 *)(r + 0xA8) = *(u64 *)(r + 0xA8) * 6364136223846793005ULL + 1;
    return (s32)((*(u64 *)(r + 0xA8) >> 32) & 0x7fffffff);
}

s64 func_0019A630(s32 *ptr, s32 fd, s32 buf, s32 cnt) {
    s64 ret;
    D_003512F8 = 0;
    if ((ret = (s64)func_0017BF28(fd, buf, cnt)) == -1 && D_003512F8 != 0)
        *ptr = D_003512F8;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main_034", func_0019A690);

s32 func_0019AC30(void *arg0) {
    if (((*(u16 *)((u8 *)arg0 + 0xC)) & 9) == 9) {
        return func_00196708(arg0);
    }
    return 0;
}

typedef struct sr_reent { u8 pad0[0x38]; s32 __sdidinit; } sr_reent;
typedef struct sr_sbuf { u8 *_base; s32 _size; } sr_sbuf;
typedef struct sr_FILE {
    u8 *_p;
    s32 _r;
    s32 _w;
    s16 _flags;
    s16 _file;
    sr_sbuf _bf;
    s32 _lbfsize;
    void *_cookie;
    s32 (*_read)(void *, char *, s32);
    s32 (*_write)(void *, const char *, s32);
    void *_seek;
    void *_close;
    sr_sbuf _ub;
    u8 *_up;
    s32 _ur;
    u8 _ubuf[3];
    u8 _nbuf[1];
    sr_sbuf _lb;
    s32 _blksize;
    s32 _offset;
    sr_reent *_data;
} sr_FILE;

s32 func_0019AC68(void *arg0) {
    sr_FILE *fp = arg0;

    do {
        if (fp->_data == 0)
            fp->_data = (sr_reent *)D_0028FA98;
        if (!fp->_data->__sdidinit)
            func_00196A30(fp->_data);
    } while (0);

    fp->_r = 0;

    if (fp->_flags & 0x20)
        return -1;

    if ((fp->_flags & 4) == 0) {
        if ((fp->_flags & 0x10) == 0)
            return -1;
        if (fp->_flags & 8) {
            if (func_00196708((nl_FILE *)fp))
                return -1;
            fp->_flags &= ~8;
            fp->_w = 0;
            fp->_lbfsize = 0;
        }
        fp->_flags |= 4;
    } else {
        if (fp->_ub._base != NULL) {
            if (fp->_ub._base != fp->_ubuf)
                func_00196BE0((s32)fp->_data, (s32)fp->_ub._base);
            fp->_ub._base = NULL;
            if ((fp->_r = fp->_ur) != 0) {
                fp->_p = fp->_up;
                return 0;
            }
        }
    }

    if (fp->_bf._base == NULL)
        func_00197838(fp);

    if (fp->_flags & (1 | 2))
        func_00197488((u8 *)fp->_data, (s32 (*)(nl_FILE *))func_0019AC30);
    fp->_p = fp->_bf._base;
    fp->_r = (*fp->_read)(fp->_cookie, (char *)fp->_p, fp->_bf._size);
    fp->_flags &= ~0x2000;
    if (fp->_r <= 0) {
        if (fp->_r == 0)
            fp->_flags |= 0x20;
        else {
            fp->_r = 0;
            fp->_flags |= 0x40;
        }
        return -1;
    }
    return 0;
}

double func_0019ADE8(double x, double y) {
    u32 hx, hy;

    do { nl_dshape gh_u; gh_u.value = (x); (hx) = gh_u.parts.msw; } while (0);
    do { nl_dshape gh_u; gh_u.value = (y); (hy) = gh_u.parts.msw; } while (0);
    do { nl_dshape sh_u; sh_u.value = (x); sh_u.parts.msw = ((hx & 0x7fffffff) | (hy & 0x80000000)); (x) = sh_u.value; } while (0);
    return x;
}

s32 func_0019AE30(double x) {
    s32 hx, lx;

    do { nl_dshape ew_u; ew_u.value = (x); (hx) = ew_u.parts.msw; (lx) = ew_u.parts.lsw; } while (0);
    hx &= 0x7fffffff;
    hx |= (u32)(lx | (-lx)) >> 31;
    hx = 0x7ff00000 - hx;
    return 1 - (s32)((u32)(hx | (-hx)) >> 31);
}
