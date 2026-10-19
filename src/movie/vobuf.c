/* Movie player: the video output buffer. */

#include "common.h"

typedef struct State_00245770 {
    s32 value;
    u8 *entries;
    s32 field8;
    s32 fieldC;
    s32 count;
} State_00245770;

/* Sets up the decoded-picture buffer: `count` pictures at `data`, with `tag`. */
void voBufCreate(void *f, s32 tag, void *data, s32 count) {
    State_00245770 *state = f;
    s32 *temp_a2;
    s32 i;

    state->value = tag;
    state->entries = data;
    state->count = count;
    state->fieldC = 0;
    state->field8 = 0;
    for (i = 0; i < count; i++) {
        temp_a2 = (s32 *)(state->entries + i * 0x4CE40);
        *temp_a2 = 0;
    }
}

/* Frees the decoded-picture buffer (nothing to do). */
void voBufDelete(void) {

}

/* Empties the decoded-picture buffer. */
void voBufReset(void *f) {
    *(s32 *)((u8 *)f + 0xC) = 0;
    *(s32 *)((u8 *)f + 0x8) = 0;
}

typedef struct {
    u8 pad[0xC];
    s32 field_C;
    s32 field_10;
} Fields_002457E0;

/* Whether the decoded-picture buffer is full. */
s32 voBufIsFull(void *f) {
    return ((Fields_002457E0 *)f)->field_C == ((Fields_002457E0 *)f)->field_10;
}

typedef struct {
    s32 unk0;
    u8 *data;
    s32 index;
    s32 count;
    s32 capacity;
} Queue_00245800;

/* Adds one decoded picture. */
void voBufIncCount(void *f) {
    Queue_00245800 *queue = (Queue_00245800 *)f;

    func_001843E0();
    *(s32 *)(queue->data + queue->index * 0x4CE40) = 2;
    queue->count++;
    queue->index = (queue->index + 1) % queue->capacity;
    func_00184428();
}

typedef struct State_00245890 {
    s32 base;
    s32 unk4;
    s32 index;
    s32 current;
    s32 end;
} State_00245890;

/* Whether the decoded-picture buffer is empty. */
static inline u8 empty_00245890(void *arg0) {
    State_00245890 *state = arg0;

    return state->current == state->end;
}

/* The next decoded picture, or 0. */
s32 voBufGetData(void *f) {
    State_00245890 *state = f;

    if (empty_00245890(state)) {
        return 0;
    }
    return state->base + (state->index * 0x195000);
}

typedef struct Buffer_002458E0 {
    s32 unk0;
    s32 base;
    s32 index;
    volatile s32 count;
    s32 capacity;
} Buffer_002458E0;

/* Whether the decoded-picture buffer is empty. */
static inline u8 is_empty_002458E0(void *arg0) {
    return ((Buffer_002458E0 *)arg0)->count == 0;
}

/* The next decoded picture's DMA tag, or 0. */
s32 voBufGetTag(void *f) {
    s32 capacity;
    Buffer_002458E0 *buffer = f;

    if (is_empty_002458E0(f)) {
        return 0;
    }
    capacity = buffer->capacity;
    return buffer->base + ((capacity + (buffer->index - buffer->count)) % capacity) * 0x4CE40;
}

typedef struct Counter_00245960 {
    u8 pad[0xC];
    volatile s32 count;
} Counter_00245960;

/* Drops the oldest decoded picture. */
void voBufDecCount(void *f) {
    Counter_00245960 *counter = f;

    if (counter->count > 0) {
        counter->count--;
    }
}
