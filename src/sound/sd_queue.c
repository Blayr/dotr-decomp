/* Sound driver: sound-effect group transfers and the CD / SIF request queues. */

#include "common.h"

/* Moves loaded sound-effect groups from main memory to the IOP, one step per call. */
void SD_vTransferSEGrpToIopProc(void) {
    u8 request[0x1C];
    s32 command;

    if (g_SDValue != NULL && (g_SDValue[1] & 4)) {
        switch (g_SDValue[0x82C]) {
        case 1:
            if (SDFS_IsUsingNow() == 0) {
                SD_AddEeToIopReq((s32)((u8 *)g_SDBuffer + 0x101800),
                             g_SDValue[5] + 0x40000, 0x80800);
                g_SDValue[0x82C]++;
            }
            break;
        case 2:
            if (SD_DoesExistAnySIFReq() == 0) {
                SDRPC_SendCommand(0x5100, g_SDValue[0x82D],
                             g_SDValue[5] + 0x40000);
                g_SDValue[0x82C]++;
            }
            break;
        case 3:
            if (((u8 *)g_SDValue)[0x5A] == 0) {
                g_SDValue[0x82C] = 0;
                g_SDValue[0] &= ~0x4000;
            }
            break;
        case 20:
            if (SD_IsAnyJobOnCD() == 0) {
                g_SDValue[0x82C] = 1;
            }
            break;
        case 30:
            if (SD_IsAnyJobOnCD() == 0) {
                g_SDValue[0x82C]++;
            }
            break;
        case 31:
            if (SDFS_IsUsingNow() == 0) {
                g_SDValue[0x82E] = *(s32 *)((u8 *)g_SDBuffer + 0x101804) + 0x800;
                g_SDValue[0x82F] = 0;
                if (g_SDValue[0x82E] <= 0x80800) {
                    g_SDValue[0x830] = g_SDValue[0x82E];
                } else {
                    g_SDValue[0x830] = 0x80800;
                }
                SD_AddEeToIopReq((s32)((u8 *)g_SDBuffer + 0x101800),
                             g_SDValue[5] + 0x40000, g_SDValue[0x830]);
                g_SDValue[0x82E] -= g_SDValue[0x830];
                *(u32 *)&g_SDValue[0x82F] += g_SDValue[0x830];
                g_SDValue[0x82C]++;
            }
            break;
        case 32:
            if (SD_DoesExistAnySIFReq() == 0) {
                SDRPC_SendCommand(0x5102, g_SDValue[0x82D],
                             g_SDValue[5] + 0x40000, g_SDValue[0x830], 0);
                if (g_SDValue[0x82E] > 0) {
                    g_SDValue[0x82C]++;
                } else {
                    g_SDValue[0x82C] = 3;
                }
            }
            break;
        case 33:
            if (((u8 *)g_SDValue)[0x5A] == 0) {
                if (g_SDValue[0x82E] <= 0x80800) {
                    g_SDValue[0x830] = g_SDValue[0x82E];
                } else {
                    g_SDValue[0x830] = 0x80800;
                }
                SD_AddReadToEeReq(g_SDValue + 0x81C,
                             (u8 *)g_SDBuffer + 0x101800,
                             g_SDValue[0x82F], g_SDValue[0x830]);
                g_SDValue[0x82C]++;
            }
            break;
        case 34:
            if (SD_IsAnyJobOnCD() == 0) {
                g_SDValue[0x82C]++;
            }
            break;
        case 35:
            if (SDFS_IsUsingNow() == 0) {
                SD_AddEeToIopReq((s32)((u8 *)g_SDBuffer + 0x101800),
                             g_SDValue[5] + 0x40000, g_SDValue[0x830]);
                g_SDValue[0x82E] -= g_SDValue[0x830];
                *(u32 *)&g_SDValue[0x82F] += g_SDValue[0x830];
                g_SDValue[0x82C]++;
            }
            break;
        case 36:
            if (SD_DoesExistAnySIFReq() == 0) {
                SDRPC_SendCommand(0x5102, g_SDValue[0x82D],
                             g_SDValue[5] + 0x40000, g_SDValue[0x830],
                             g_SDValue[0x82F] - g_SDValue[0x830] - 0x800);
                if (g_SDValue[0x82E] > 0) {
                    g_SDValue[0x82C] = 33;
                } else {
                    g_SDValue[0x82C] = 3;
                }
            }
            break;
        default:
            g_SDValue[0x82C] = 0;
            if (SD_FetchFromXferQueue(&command, request) != 0) {
                SD_KickSEGroupReadSequence(command, (s32)request);
            }
            break;
        }
    }
}

/* Queues a sound-effect group transfer to the IOP. */
s32 SD_iTransferSEGrpToIop(void) {
    extern s32 SD_AddToXferQueue();

    if (g_SDValue == NULL) {
        return 0;
    }
    if (!(g_SDValue[1] & 4)) {
        return 0;
    }
    if (g_SDValue[0] & 1) {
        return SD_AddToXferQueue();
    }
    return 0;
}

/* Starts reading sound-effect group `group` from the disc into slot `slot`. */
void SD_KickSEGroupReadSequence(s32 group, s32 slot) {
    *(s32 *)((u8 *)g_SDValue + 0x20B4) = group;
    func_0019B648((u8 *)g_SDValue + 0x2070, D_002B90B0, slot);
    SD_AddReadToEeReq((u8 *)g_SDValue + 0x2070, (u8 *)g_SDBuffer + 0x101800, 0, 0x80800);
    *g_SDValue |= 0x4000;
    *(s32 *)((u8 *)g_SDValue + 0x20B0) = 0x1E;
}

/* Adds transfer `value` (data `src`) to the transfer queue. */
s32 SD_AddToXferQueue(s32 value, void *src) {
    s32 next;
    s32 offset;
    s8 index;

    index = *(s8 *)((u8 *)g_SDValue + 0x20C4);
    next = (index + 1) & 7;
    if (next == *(s8 *)((u8 *)g_SDValue + 0x20C5)) {
        return 0;
    }
    offset = index << 5;
    *(s32 *)(offset + (u32)g_SDValue + 0x20C8) = value;
    func_0019C2B8((u8 *)g_SDValue + offset + 0x20CC, src, 0x1C);
    *(s8 *)((u8 *)g_SDValue + 0x20C4) = next;
    return 1;
}

/* Takes the next transfer off the queue into `outValue` and `outData`. */
s32 SD_FetchFromXferQueue(s32 *outValue, void *outData) {
    s32 temp_v1_2;
    s8 temp_v1;

    temp_v1 = *(s8 *)((u8 *)g_SDValue + 0x20C5);
    if (temp_v1 == *(s8 *)((u8 *)g_SDValue + 0x20C4)) {
        return 0;
    }
    *(s8 *)((u8 *)g_SDValue + 0x20C5) = (s8)((temp_v1 + 1) & 7);
    temp_v1_2 = temp_v1 << 5;
    *outValue = *(s32 *)(temp_v1_2 + (u32)g_SDValue + 0x20C8);
    func_0019C2B8(outData, (u8 *)g_SDValue + temp_v1_2 + 0x20CC, 0x1C);
    return 1;
}

/* Empties the transfer queue. */
void SD_ClearXferQueue(void) {
    *((s8 *)g_SDValue + 0x20C5) = 0;
    *((s8 *)g_SDValue + 0x20C4) = 0;
}

/* Whether any disc read is waiting. */
s32 SD_DoesExistAnyCDReq(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = g_SDValue[0x1710 / sizeof(s32)];
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = g_SDValue[0x171C / sizeof(s32)];
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

/* Whether any IOP transfer is waiting. */
s32 SD_DoesExistAnySIFReq(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = *(s32 *)((u8 *)g_SDValue + 0x1820);
    if (temp_v0_2 != 0) {
        return temp_v0_2;
    }
    temp_v0 = *(s32 *)((u8 *)g_SDValue + 0x182C);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return 0;
}

typedef struct {
    u8 data[0x40];
    s32 arg1;
    s32 arg2;
    s32 arg3;
} Request_0010BE60;

typedef struct {
    s32 arg0;
    s32 arg1;
    s32 arg2;
    s32 reserved;
} Request2_0010BE60;

typedef struct {
    s32 flags;
    u8 padding[0x124C];
    Request_0010BE60 requests[16];
    s32 pending;
    s32 write;
    s32 read;
    s32 state;
    Request2_0010BE60 requests2[16];
    s32 pending2;
    s32 write2;
    s32 read2;
    s32 state2;
} Queues_0010BE60;

/* Runs the next waiting disc read or IOP transfer. */
void SD_vDoFsCommandQueue(void) {
    extern s32 s_iHowManyTimesCDAreUsed;
    Queues_0010BE60 *queues;
    Queues_0010BE60 *queues2;
    s32 state2;
    s32 state;
    Request_0010BE60 *request;
    Request2_0010BE60 *request2;
    s32 *stateField;
    s32 *state2Field;

    queues = (Queues_0010BE60 *)g_SDValue;
    stateField = &queues->state;
    state = *stateField;
    if (state != 0) {
        request = &queues->requests[queues->read];
        switch (state) {
        case 1:
            if (SDFS_IsUsingNow() == 0) {
                SDFS_ReadToEE((s32)request, request->arg1, request->arg2, request->arg3);
                ((Queues_0010BE60 *)g_SDValue)->state++;
                ((Queues_0010BE60 *)g_SDValue)->flags |= 0x800000;
            }
            break;
        case 2:
            if (SDFS_IsUsingNow() == 0) {
                s_iHowManyTimesCDAreUsed++;
                ((Queues_0010BE60 *)g_SDValue)->flags &= 0xFF7FFFFF;
                ((Queues_0010BE60 *)g_SDValue)->read = (((Queues_0010BE60 *)g_SDValue)->read + 1) % 16;
                ((Queues_0010BE60 *)g_SDValue)->state++;
            }
            break;
        default:
            *stateField = 0;
            break;
        }
    } else if (queues->pending != 0) {
        *stateField = 1;
        ((Queues_0010BE60 *)g_SDValue)->pending--;
    }
    queues2 = (Queues_0010BE60 *)g_SDValue;
    state2Field = &queues2->state2;
    state2 = *state2Field;
    if (state2 != 0) {
        request2 = &queues2->requests2[queues2->read2];
        switch (state2) {
        case 1:
            if (SDRPC_TranserToIopStatus() < 0) {
                SDRPC_StartTransferToIop(request2->arg0, request2->arg1, request2->arg2);
                ((Queues_0010BE60 *)g_SDValue)->state2++;
                ((Queues_0010BE60 *)g_SDValue)->flags |= 0x08000000;
                return;
            }
            break;
        case 2:
            if (SDRPC_TranserToIopStatus() < 0) {
                ((Queues_0010BE60 *)g_SDValue)->flags &= 0xF7FFFFFF;
                ((Queues_0010BE60 *)g_SDValue)->read2 = (((Queues_0010BE60 *)g_SDValue)->read2 + 1) % 16;
                ((Queues_0010BE60 *)g_SDValue)->state2++;
                return;
            }
            break;
        default:
            *state2Field = 0;
            return;
        }
    } else if (queues2->pending2 != 0) {
        *state2Field = 1;
        ((Queues_0010BE60 *)g_SDValue)->pending2--;
    }
}

typedef struct {
    char name[0x40];
    u8 *data;
    s32 offset;
    s32 size;
} Request_0010C110;

typedef struct {
    u8 padding[0x1250];
    Request_0010C110 requests[16];
    s32 count;
    s32 index;
} Queue_0010C110;

/* Queues a disc read of file `name` into `dst` (`offset`, `size`). */
void SD_AddReadToEeReq(void *name, void *dst, s32 offset, s32 size) {
    Request_0010C110 *request;

    request = &((Queue_0010C110 *)g_SDValue)->requests[((Queue_0010C110 *)g_SDValue)->index];
    func_0019BDD8(request->name, (const char *)name);
    request->data = dst;
    request->offset = offset;
    request->size = size;
    request->offset &= ~0x7FF;
    request->data -= offset - request->offset;
    request->size += offset - request->offset;
    request->size += 0x7FF;
    request->size &= ~0x7FF;
    ((Queue_0010C110 *)g_SDValue)->index = (((Queue_0010C110 *)g_SDValue)->index + 1) % 16;
    ((Queue_0010C110 *)g_SDValue)->count++;
}

typedef struct QueueEntry_0010C220 {
    s32 value0;
    s32 value1;
    s32 value2;
    s32 unused;
} QueueEntry_0010C220;

typedef struct Queue_0010C220 {
    u8 padding[0x1720];
    QueueEntry_0010C220 entries[16];
    s32 count;
    s32 write_index;
} Queue_0010C220;

/* Queues a transfer of `size` bytes from `src` to IOP address `dst`. */
void SD_AddEeToIopReq(s32 src, s32 dst, s32 size) {
    QueueEntry_0010C220 *entry;

    entry = &((Queue_0010C220 *)g_SDValue)->entries[((Queue_0010C220 *)g_SDValue)->write_index];
    entry->value0 = src;
    entry->value1 = dst;
    entry->value2 = size;
    ((Queue_0010C220 *)g_SDValue)->write_index = (((Queue_0010C220 *)g_SDValue)->write_index + 1) % 16;
    ((Queue_0010C220 *)g_SDValue)->count++;
}

/* Whether the sound driver has a disc job running. */
s32 SD_IsAnyJobOnCD(void) {
    s32 var_v0;

    var_v0 = 1;
    if ((g_SDValue[0x5C4] == 0) && (g_SDValue[0x5C7] == 0)) {
        var_v0 = 0;
    }
    return var_v0;
}
