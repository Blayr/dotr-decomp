/* Movie player: play a movie, threads, start and stop. */

#include "common.h"
#include "campaign.h"

/* Plays the movie file `path` (with audio `withAudio`, interlaced `interlaced`) in the movie memory area. */
void movie_play(s32 path, s32 withAudio, s32 interlaced) {
    isWithAudio = withAudio;
    isWithInter = interlaced;
    clearGsMem(0, 0, 0, 0x280, 0x1C0);
    sceGsSetDefDBuff(D_003503C0, 0, 0x280, 0xE0, 0, 0, 1);
    FlushCache(0);
    voBufData = 0x01200000;
    voBufTag = 0x0152A000;
    viBufTag = 0x015C3C80;
    mpegWork = 0x015C4CC0;
    defStack = 0x0178DE40;
    readBuf = 0x0178E640;
    audioBuff = 0x017DE680;
    viBufData = 0x017EA680;
    videoDecStack = 0x0186A680;
    timeStamp = 0x0186E680;
    movie(path);
}

/* Plays movie file `name` (Sony's ezmpeg sample player): sets everything up, plays until the end or a button
   press, then tears down. */
s32 movie(s32 name) {
    s32 temp_a1;

    temp_a1 = D_003503B8;
    D_003503B8 = temp_a1 + 1;
    func_00199B50(D_0030F354, temp_a1);
    initAll(name);
    readMpeg((void *)videoDec, (void *)readBuf, (void *)infile);
    termAll();
    return controller_val;
}

struct DotrMpegDecoder {
    int unknown_00[2];
    int unknown_08;
};
struct DotrMpegReadBuf {
    char data[0x50000];
    int unknown_50000[2];
    int size;
};
struct DotrMpegFile {
    int unknown_00;
    int size;
    int start;
};
struct DotrMpegAudio;
struct DotrMpegVideoOut;
extern struct DotrMpegVideoOut D_00350600_b;
extern struct DotrMpegAudio D_00350620_b;
extern struct DotrMpegDecoder D_00350680_b;
extern int func_00203320_b(void);
extern int func_00203840_b(void);
extern int func_00242D00_b(void);
extern int func_00243DE0_b(struct DotrMpegFile *file, char *buffer, int byte_count, int position);
extern int func_0018DEE8_b(struct DotrMpegDecoder *vd, char *data, int size, struct DotrMpegReadBuf *ring, int ring_size);

/* The movie's read thread: reads the file into the read buffer and passes video and audio packets on. */
int readMpeg(void *vd_v, void *rb_v, void *file_v)
{
    struct DotrMpegDecoder * vd = vd_v;
    struct DotrMpegReadBuf * rb = rb_v;
    struct DotrMpegFile * file = file_v;
    char *put_ptr;
    char *get_ptr;
    int putsize;
    int getsize;
    int readrest = file->size;
    int sector = 0;
    int writerest = file->size;
    int count;
    int proceed;
    int isStarted = 0;
    unsigned int button_old = 0;
    unsigned int pushed;
    int isPaused = 0;
    int keep;

    while (isPaused || (writerest > 4 && videoDecGetState(vd) != 3)) {
        

        keep = isPaused;
        func_00203320_b();
        SzPad_VSync();
        func_00203840_b();
        controller_val = SzPad_Check(0, 1, 0xffff) & 0xffff;
        pushed = controller_val & (button_old ^ controller_val) & 0x8e0;
        button_old = controller_val;
        if (isWithInter && pushed && vd->unknown_08 > 10 && !isPaused) {
            endDisplay();
            if (isWithAudio) {
                audioDecPause(&D_00350620_b);
            }
            videoDecAbort(&D_00350680_b);
            return -1;
        }
        putsize = readBufBeginPut(rb, &put_ptr);
        if (readrest > 0 && putsize >= 0x10000) {
            count = func_00243DE0_b(file, put_ptr, 0x10000, file->start + sector);
            readBufEndPut(rb, count);
            sector += count >> 11;
            readrest -= count;
        }
        switchThread();
        getsize = readBufBeginGet(rb, &get_ptr);
        if (getsize > 0) {
            proceed = func_0018DEE8_b(vd, get_ptr, getsize, rb, rb->size);
            readBufEndGet(rb, proceed);
            writerest -= proceed;
        }
        isPaused = keep;
        func_00242D00_b();
        if (!isStarted && voBufIsFull(&D_00350600_b) && isAudioOK()) {
            startDisplay(1);
            if (isWithAudio) {
                audioDecStart(&D_00350620_b);
            }
            isStarted = 1;
        }
    }
    while (!videoDecFlush(vd)) {
        switchThread();
    }
    while (!videoDecIsFlushed(vd) && videoDecGetState(vd) != 3) {
        switchThread();
    }
    endDisplay();
    if (isWithAudio) {
        audioDecReset(&D_00350620_b);
    }
    return 1;
}

/* Lets the other movie threads run. */
void switchThread(void) {
    RotateThreadReadyQueue(0x20);
}

/* Whether the movie's audio has been set up. */
s32 isAudioOK(void) {
    if (isWithAudio != 0) {
        return audioDecIsPreset(audioDec);
    }
    return 1;
}

typedef struct ThreadParams_00242950 {
    s32 attr;
    void (*entry)();
    s32 stack;
    s32 stack_size;
    void *gp;
    s32 priority;
    s32 current_priority;
    s32 status;
    s32 option;
} ThreadParams_00242950;

extern char D_0030F39A[];
extern u8 D_00317EF0[];
extern s32 D_00350730;
extern s32 D_00350734;
extern s32 defaultTh;
extern s32 videoDecTh;

/* Sets up the movie player for file `name`: buffers, decoders, threads, the display. */
void initAll(s32 name) {
    ThreadParams_00242950 thread;
    extern s32 func_00190810();
    extern s32 videoDecCreate();
    extern s32 videoDecSetStream(void *, s32, s32, void (*)(), s32);
    extern void voBufCreate();

    *(s32 *)D_CTRL_ADDR |= 3;
    *(s32 *)D_STAT_ADDR = 4;
    readBufCreate((void *)readBuf);
    sceMpegInit();
    videoDecCreate(videoDec, mpegWork, 0x1C9168, viBufData,
                 viBufTag, 0x100, timeStamp, 0x200);
    func_001906D0();
    func_00190810(1, 0x8000, 0);
    audioDecCreate(audioDec, audioBuff, 0xC000, 0x6000);
    videoDecSetStream(videoDec, 0, 0, (void (*)())videoCallback, readBuf);
    if (isWithAudio != 0) {
        videoDecSetStream(videoDec, 2, 0, (void (*)())pcmCallback, readBuf);
    }
    voBufCreate(voBuf,
                 ((u64)((s64)voBufData << 36) >> 36) | 0x20000000,
                 (void *)voBufTag, 2);
    thread.entry = defMain;
    thread.stack = defStack;
    thread.stack_size = 0x800;
    thread.priority = 0x20;
    thread.gp = D_00317EF0;
    thread.option = 0;
    defaultTh = CreateThread(&thread);
    StartThread(defaultTh, NULL);
    thread.entry = (void (*)())videoDecMain;
    thread.stack = videoDecStack;
    thread.stack_size = 0x4000;
    thread.priority = 0x20;
    thread.gp = D_00317EF0;
    thread.option = 0;
    videoDecTh = CreateThread(&thread);
    StartThread(videoDecTh, videoDec);
    if (strFileOpen(infile, name) == 0) {
        do {
            func_00199B50(D_0030F39A, name);
        } while (strFileOpen(infile, name) == 0);
    }
    D_00350734 = AddIntcHandler(2, vblankHandler, 0);
    func_0017C428(2);
    D_00350730 = AddDmacHandler(2, handler_endimage, 0);
    func_0017C4F8(2);
}

/* Tears the movie player down. */
void termAll(void) {
    extern void readBufDelete();
    extern void voBufDelete();
    extern s32 TerminateThread(s32);
    extern s32 DeleteThread(s32);
    extern s32 func_0017C490(s32);
    extern s32 RemoveDmacHandler(s32, s32);
    extern s32 func_0017C3C0(s32);
    extern s32 RemoveIntcHandler(s32, s32);
    extern s32 D_00350730;
    extern s32 D_00350734;
    extern s32 defaultTh;
    extern s32 videoDecTh;

    readBufDelete(readBuf);
    voBufDelete(voBuf);
    TerminateThread(videoDecTh);
    DeleteThread(videoDecTh);
    TerminateThread(defaultTh);
    DeleteThread(defaultTh);
    func_0017C490(2);
    RemoveDmacHandler(2, D_00350730);
    func_0017C3C0(2);
    RemoveIntcHandler(2, D_00350734);
    videoDecDelete(videoDec);
    audioDecDelete(audioDec);
    strFileClose(infile);
}

/* The movie player's default thread (waits). */
void defMain(void) {
loop_1:
    RotateThreadReadyQueue(0x20);
    goto loop_1;
}

/* Prints a movie player error. */
void ErrMessage(s8 *message) {
    func_00199B50(D_0030F3AE, message);
}

/* Sends decoded movie audio on to the IOP. */
void proceedAudio(void) {
    audioDecSendToIOP(audioDec);
}
