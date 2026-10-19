/* Movie player (Sony's MPEG sample code): the read ring buffer. */

#include "common.h"
#include "campaign.h"

typedef struct Buffer_00241A90 {
    u8 data[0x50000];
    s32 field_50000;
    s32 field_50004;
    s32 field_50008;
} Buffer_00241A90;

/* Sets up the movie player's read buffer. */
void readBufCreate(void *buf) {
    Buffer_00241A90 *buffer = buf;

    buffer->field_50004 = 0;
    buffer->field_50000 = 0;
    buffer->field_50008 = 0x50000;
}

/* Frees the movie read buffer (nothing to do). */
void readBufDelete(void) {

}

typedef struct Header_00241AD0 {
    u8 padding[0x50000];
    s32 offset;
    s32 start;
    s32 end;
} Header_00241AD0;

/* Where the next read can go in the movie buffer, through `out`; returns how much room there is. */
s32 readBufBeginPut(void *buffer, void **out) {
    s32 size = ((Header_00241AD0 *)buffer)->end - ((Header_00241AD0 *)buffer)->start;

    if (size != 0) {
        *out = (u8 *)buffer + ((Header_00241AD0 *)buffer)->offset;
    }
    return size;
}

typedef struct {
    u8 padding[0x50000];
    s32 position;
    s32 count;
    s32 capacity;
} Buffer_00241B10;

/* Marks `size` bytes as read into the movie buffer. */
s32 readBufEndPut(void *buf, s32 size) {
    Buffer_00241B10 *buffer = buf;
    s32 capacity;
    s32 available;

    capacity = buffer->capacity;
    available = capacity - buffer->count;
    size = (size < available) ? size : available;
    buffer->position = (buffer->position + size) % capacity;
    buffer->count = buffer->count + size;
    return size;
}

typedef struct {
    u8 data[0x50000];
    s32 write_index;
    s32 count;
    s32 capacity;
} Buffer_00241B80;

/* Where the next unread data of the movie buffer is, through `out`; returns how much there is. */
s32 readBufBeginGet(void *buf, void **out) {
    Buffer_00241B80 *buffer = buf;
    s32 count;
    s32 capacity;

    count = buffer->count;
    if (count != 0) {
        capacity = buffer->capacity;
        *out = (u8 *)buf + ((capacity + (buffer->write_index - count)) % capacity);
    }
    return buffer->count;
}

/* Marks `size` bytes of the movie buffer as used. */
s32 readBufEndGet(s32 *buffer, s32 size) {
    s32 remaining;

    remaining = buffer[0x14001];
    size = (size < remaining) ? size : remaining;
    buffer[0x14001] -= size;
    return size;
}
