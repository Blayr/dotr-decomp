#include "common.h"
#include "campaign.h"

typedef struct State_0022F1C0 {
    u16 halves[18];
    s16 field_24;
} State_0022F1C0;

extern State_0022F1C0 D_0029ABC0;

/* Draws the "press a button" (botan mati) prompt. */
s32 Taku_Camp_BOTAN_MATI(s32 packet, s32 arg1, s16 arg2, s16 arg3) {
    extern s32 Taku_Obj_Set(s32, void *, s16, s16);
    s8 *slide = &campaignState;
    State_0022F1C0 local;
    s32 flag;
    s32 step;

    local = D_0029ABC0;
    flag = 1;
    switch (campaignWork.talkSpeaker) {
    case 0:
        arg2 = 0x1CC;
        arg3 = 0x68;
        break;
    case 1:
        arg2 = 0x258;
        arg3 = 0x198;
        break;
    case 2:
        arg2 = 0x258;
        arg3 = 0x198;
        break;
    case 3:
        arg2 = 0x1CC;
        arg3 = 0x68;
        break;
    }
    step = *(u8 *)&campaignWork.unk53B2 % 15;
    if (step < 5) {
        local.field_24 = 0x98;
    } else if (step < 10) {
        local.field_24 = 0x99;
    } else if (step < 15) {
        local.field_24 = 0x9A;
    }
    if (slide[0] == 0 && *(s16 *)(slide + 0xC2) == 0x64) {
        flag = 0;
    }
    if (slide[0] == 1 && *(s16 *)(slide + 0xC2) == 0x69) {
        flag = 0;
    }
    if (slide[0] == 1 && *(s16 *)(slide + 0xC2) == 0x6A) {
        flag = 0;
    }
    if ((campaignWork.talkStep == 4 || campaignWork.eventPictureState == 2) && flag != 0) {
        packet = Taku_Obj_Set(packet, &local, arg2, arg3);
        *(u8 *)&campaignWork.unk53B2 += 1;
    }
    return packet;
}
