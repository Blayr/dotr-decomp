#include "common.h"
#include "game.h"
#include "campaign.h"
#include "m2c_macros.h"

extern s16 D_00298C32;
extern s16 D_00298CD0;
extern f32 D_00298D0C;
extern f32 D_00298D14;
extern s16 D_00298D6A;
extern f32 D_00298DDC;
extern f32 D_00298DE4;
extern s16 D_00299ED2;
extern s8 D_0033F72C;

/* Runs the campaign's events (ivent): the script of each place's story, the duels it starts and what they unlock. */
void Taku_Camp_Ivent(void) {
    u8 *ctx = (u8 *)&campaignState;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_a1_3;
    s16 temp_a1_4;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_a2_3;
    s16 temp_a2_4;
    s16 temp_a2_5;
    s16 temp_a2_6;
    s16 temp_a2_7;
    s16 temp_a2_8;
    s16 temp_a2_9;
    s16 temp_v1;
    s16 temp_v1_10;
    s16 temp_v1_11;
    s16 temp_v1_12;
    s16 temp_v1_13;
    s16 temp_v1_14;
    s16 temp_v1_15;
    s16 temp_v1_16;
    s16 temp_v1_17;
    s16 temp_v1_18;
    s16 temp_v1_19;
    s16 temp_v1_20;
    s16 temp_v1_21;
    s16 temp_v1_22;
    s16 temp_v1_23;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 temp_v1_5;
    s16 temp_v1_6;
    s16 temp_v1_7;
    s16 temp_v1_8;
    s16 temp_v1_9;

    switch (D_00299ED2) {
        case 0x2724:                                /* switch 2 */
            temp_v1 = campaignWork.eventStep;
            switch (temp_v1) {                      /* switch 3 */
            case 0:                                 /* switch 3 */
                func_001F48F0(0, 0x190, 0, 0, 0);
                func_00217980(0x18, 1);
                campaignWork.cameraTarget[0] = 0;
                campaignWork.cameraTarget[2] = 0;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.cameraMode = 1;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0x1000;
                campaignWork.cloudState = 1;
                campaignWork.cloudCover = 0x1000;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.unk53B4 = 0;
                campaignWork.unk53B5 = 0;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.unk546C = 0;
                campaignWork.unk546D = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 3 */
                if (campaignWork.cinemaState == 2) {
                    campaignWork.talkStep = 1;
                    campaignWork.talkPage = 1;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            default:                                /* switch 3 */
dflt_3:
                goto end_0021E330;
            case 2:                                 /* switch 3 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.cloudState = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 3:                                 /* switch 3 */
                campaignWork.zoomMove = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 4:                                 /* switch 3 */
                campaignWork.cloudState = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 5:                                 /* switch 3 */
                if (campaignWork.zoom < 0x7D0) {
                    if (campaignWork.unk546C == 0) {
                        func_00217980(0x19, 0);
                        campaignWork.unk546C = 1;
                    }
                }
                if (campaignWork.zoom < 0x50) {
                    campaignWork.cloudState = 0xA;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 6:                                 /* switch 3 */
                if (campaignWork.cloudState == 0xB) {
                    (*(s16 *)(ctx + 0xC2)) = 0x2738;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x2738:                                /* switch 2 */
            temp_v1_2 = campaignWork.eventStep;
            switch (temp_v1_2) {                    /* switch 4 */
            case 0:                                 /* switch 4 */
                func_001F48F0(0, 0x191, 0, 0, 0);
                campaignWork.cameraTarget[0] = 0;
                campaignWork.cameraTarget[2] = 0;
                *(s32 *)&campaignWork.cameraTarget[3] = 0;
                func_00233F50(2);
                campaignWork.cameraMode = 2;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0x1000;
                campaignWork.cloudState = 0x14;
                campaignWork.cloudCover = 0x1000;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.unk546C = 0;
                campaignWork.eventPictureZoom = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 4 */
                if (campaignWork.cloudState == 0x15) {
                    func_00217710(0, 0x22);
                    func_00217710(0, 0x23);
                    campaignWork.zoomMove = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 4 */
                if (campaignWork.zoomMove == 0) {
                    campaignWork.cloudState = 0x1E;
                    campaignWork.cloudCover = 0;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 3:                                 /* switch 4 */
                if (campaignWork.cloudState == 0x1F) {
                    campaignWork.cloudState = 0x20;
                    campaignWork.cloudCover = 0x1000;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 4:                                 /* switch 4 */
                if (campaignWork.cloudState == 0x21) {
                    func_00217980(0x19, 1);
                    campaignWork.talkStep = 1;
                    campaignWork.talkPage = 1;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 5:                                 /* switch 4 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0xD;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 6:                                 /* switch 4 */
                if (campaignWork.talkStep == 0xE) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 0;
                    campaignWork.cameraMode = 3;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 7:                                 /* switch 4 */
                if (campaignWork.cinemaState == 2) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventWindowState = 1;
                    campaignWork.eventWindowOpen = 0;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 8:                                 /* switch 4 */
                if (campaignWork.eventWindowState == 4) {
                    campaignWork.eventWindowState = 0;
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.cameraMode = 3;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 9:                                 /* switch 4 */
                if (campaignWork.cinemaState == 2) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventWindowState = 0;
                    campaignWork.eventWindowOpen = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2739;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            default:                                    /* switch 4 */
                goto dflt_3;
            }
            break;
        case 0x2739:                                /* switch 2 */
            temp_a0 = campaignWork.eventStep;
            switch (temp_a0) {                      /* switch 5; irregular */
            case 0:                                 /* switch 5 */
                func_00233F50(2);
                campaignWork.cameraMode = 3;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventPictureZoom = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 5 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventWindowState = 0;
                    campaignWork.eventWindowOpen = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2742;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x2742:                                /* switch 2 */
            temp_v1_3 = campaignWork.eventStep;
            switch (temp_v1_3) {                    /* switch 6; irregular */
            case 0:                                 /* switch 6 */
                func_00233F50(2);
                campaignWork.cameraMode = 3;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 6 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventWindowState = 1;
                    campaignWork.eventWindowOpen = 0;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 6 */
                if (campaignWork.eventWindowState == 4) {
                    campaignWork.eventWindowState = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x274C;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x274C:                                /* switch 2 */
            temp_v1_4 = campaignWork.eventStep;
            switch (temp_v1_4) {                    /* switch 7; irregular */
            case 0:                                 /* switch 7 */
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.cameraMode = 3;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 7 */
                if (campaignWork.cinemaState == 2) {
                    campaignWork.talkStep = 1;
                    campaignWork.talkPage = 1;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 7 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2756;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
        case 0x2756:                                /* switch 2 */
            temp_v1_5 = campaignWork.eventStep;
            switch (temp_v1_5) {                    /* switch 8; irregular */
            case 0:                                 /* switch 8 */
                func_00233F50(2);
                campaignWork.cameraMode = 3;
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.deckShowPhase = 0;
                campaignWork.deckShowDone = 0;
                campaignWork.deckCardSlide[0] = 0;
                campaignWork.deckCardSlide[1] = -0x64;
                campaignWork.deckCardSlide[2] = -0xC8;
                campaignWork.deckShowSound[0] = 0;
                campaignWork.deckShowSound[1] = 0;
                campaignWork.deckShowSound[2] = 0;
                campaignWork.eventWindowChoice = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            case 1:                                 /* switch 8 */
                if (campaignWork.talkStep == 0xC) {
                    campaignWork.talkStep = 0;
                    campaignWork.talkPage = 0;
                    campaignWork.eventWindowState = 1;
                    campaignWork.eventWindowOpen = 0;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
                break;
            case 2:                                 /* switch 8 */
                if (campaignWork.eventWindowState == 4) {
                    campaignWork.eventWindowState = 4;
                    (*(s16 *)(ctx + 0xC2)) = 0x2757;
                    campaignWork.eventStep = 0;
                    goto end_0021E330;
                }
                break;
            }
            break;
    case 0x2757:
        temp_a0_2 = campaignWork.eventStep;
        switch (temp_a0_2) {
        case 0:
            func_00233F50(2);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 4;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2760;
                campaignWork.eventStep = 0;
                func_00217980(0x1A, 0);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2760:                                    /* switch 1 */
        temp_v1_6 = campaignWork.eventStep;
        switch (temp_v1_6) {                        /* switch 9; irregular */
        case 0:                                     /* switch 9 */
            func_00233F50(2);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.unk546D = 0;
            campaignWork.unk546C = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 9 */
            if (campaignWork.talkPage == 3) {
                if ((campaignWork.talkStep == 5) && (campaignWork.unk546C == 0)) {
                    func_00217980(0x1A, 1);
                    campaignWork.unk546C = 1;
                }
            }
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowChoice = 1;
                (*(s16 *)(ctx + 0xC2)) = 0x276A;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x276A:                                    /* switch 1 */
        temp_a2 = campaignWork.eventStep;
        switch (temp_a2) {                          /* switch 10; irregular */
        case 0:                                     /* switch 10 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            func_00217980(0x1A, 1);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            func_00217980(0x1A, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 10 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 10 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowState = 1;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 10 */
            if (campaignWork.eventWindowState == 4) {
                campaignWork.eventWindowState = 0;
                if (campaignWork.eventWindowChoice == 0) {
                    (*(s8 *)(ctx + 0)) = 1;
                    (*(s16 *)(ctx + 0xC2)) = 0x2EE0;
                    (*(s8 *)(ctx + 0xC9)) = 2;
                } else {
                    (*(s8 *)(ctx + 0)) = 0;
                    (*(s16 *)(ctx + 0xC2)) = 0x2AF8;
                    (*(s8 *)(ctx + 0xC9)) = 0;
                }
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2AF8:                                    /* switch 1 */
        temp_a1 = campaignWork.eventStep;
        switch (temp_a1) {                          /* switch 11; irregular */
        case 0:                                     /* switch 11 */
            func_00233F50(2);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 11 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 11 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cloudState = 0x16;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 11 */
            if (campaignWork.cloudState == 0x17) {
                func_00233F50(3);
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                func_001E7F70(3, 2, 0);
                func_001F93F0(0, 7, 0, NULL);
                func_001F6E80(7, 1.0f);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 11 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 0;
                campaignWork.cameraTarget[0] = D_00298DDC;
                campaignWork.cameraTarget[2] = D_00298DE4;
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x64;
                func_00217980(4, 1);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B02:
        break;
    case 0x2B0C:                                    /* switch 1 */
        temp_v1_7 = campaignWork.eventStep;
        switch (temp_v1_7) {                        /* switch 12 */
        case 0:                                     /* switch 12 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureState = 1;
            campaignWork.eventPictureZoom = 0;
            func_00217980(0x1B, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 12 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureX = (s16) (campaignWork.eventPictureX - 4);
                if (campaignWork.eventPictureX < -0x280) {
                    campaignWork.eventPictureX = -0x280;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 12 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 12 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 12 */
            if (campaignWork.talkStep == 0xE) {
                func_00217980(4, 0);
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 12 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x65;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 12 */
            goto dflt_3;
        }
        break;
    case 0x2B70:                                    /* switch 1 */
        temp_v1_8 = campaignWork.eventStep;
        switch (temp_v1_8) {                        /* switch 13; irregular */
        case 0:                                     /* switch 13 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk5483 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            func_00217980(0x1C, 0);
            goto end_0021E330;
        case 1:                                     /* switch 13 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.unk5483 = 1;
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 13 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.unk5483 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 13 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B72;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B72:                                    /* switch 1 */
        temp_a2_2 = campaignWork.eventStep;
        switch (temp_a2_2) {                        /* switch 14; irregular */
        case 0:                                     /* switch 14 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = -0x1C0;
            campaignWork.eventPictureState = 1;
            func_00217980(0x1C, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 14 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureY = (s16) (campaignWork.eventPictureY + 4);
                if (campaignWork.eventPictureY > -0x50) {
                    campaignWork.eventPictureY = -0x50;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 14 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 14 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 14 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B74;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B74:                                    /* switch 1 */
        temp_a2_3 = campaignWork.eventStep;
        switch (temp_a2_3) {                        /* switch 15; irregular */
        case 0:                                     /* switch 15 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.cameraTarget[0] = D_00298D0C;
            campaignWork.cameraTarget[2] = D_00298D14;
            campaignWork.placeReached[7] = 0;
            campaignWork.unk5483 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 15 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.unk5483 = 1;
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 15 */
            if (campaignWork.talkStep == 0xC) {
                func_00217980(4, 0);
                campaignWork.unk5483 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 15 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.routes[0][12].state = D_00298C32;
                campaignWork.routes[0][13].state = D_00298CD0;
                campaignWork.routes[0][11].state = D_00298D6A;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 15 */
            if (campaignWork.placeReached[7] == 1) {
                (*(s16 *)(ctx + 0xC2)) = 0;
                campaignWork.eventStep = 0;
                campaignWork.unk5374 = 0;
                campaignWork.unk5375 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 0;
                campaignWork.leaderShow = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B84:                                    /* switch 1 */
        temp_v1_9 = campaignWork.eventStep;
        switch (temp_v1_9) {                        /* switch 16 */
        case 0:                                     /* switch 16 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureZoom = 0;
            campaignWork.unk546C = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 16 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 16 */
            if (campaignWork.talkPage == 4) {
                if (campaignWork.unk546C == 0) {
                    func_00217980(0x1D, 0);
                    campaignWork.unk546C = 1;
                }
            }
            if (campaignWork.talkPage == 6) {
                if (campaignWork.unk546C < 2) {
                    func_00217980(0x1D, 1);
                    campaignWork.unk546C = 2;
                }
            }
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 16 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 16 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 16 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B86;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 16 */
            goto dflt_3;
        }
        break;
    case 0x2B86:                                    /* switch 1 */
        temp_a2_4 = campaignWork.eventStep;
        switch (temp_a2_4) {                        /* switch 17; irregular */
        case 0:                                     /* switch 17 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureState = 1;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 17 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureY = (s16) (campaignWork.eventPictureY - 4);
                if (campaignWork.eventPictureY < -0x1C0) {
                    campaignWork.eventPictureY = -0x1C0;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 17 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 17 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 17 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B87;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                func_00217980(0x1E, 0);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B87:                                    /* switch 1 */
        temp_v1_10 = campaignWork.eventStep;
        switch (temp_v1_10) {                       /* switch 18; irregular */
        case 0:                                     /* switch 18 */
            func_00233F50(3);
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 18 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2B88;
                campaignWork.eventStep = 0;
                func_00217980(0x1E, 1);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B88:                                    /* switch 1 */
        temp_v1_11 = campaignWork.eventStep;
        switch (temp_v1_11) {                       /* switch 19 */
        case 0:                                     /* switch 19 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureState = 1;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 19 */
            if (campaignWork.cinemaState == 2) {
                if (campaignWork.eventPictureState < 3) {
                    campaignWork.eventPictureState = 2;
                    campaignWork.talkSpeaker = 2;
                }
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 19 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 19 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 1;
                campaignWork.eventPictureState = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 19 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureFade = 1;
                campaignWork.eventPictureAlpha = 0x80;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 19 */
            if (campaignWork.eventPictureFade == 0xA) {
                if (campaignWork.eventPictureState < 3) {
                    campaignWork.eventPictureState = 2;
                    campaignWork.talkSpeaker = 2;
                }
            }
            if (campaignWork.eventPictureState == 3) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 19 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B8A;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                campaignWork.eventPictureAlpha = 0x80;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 19 */
            goto dflt_3;
        }
        break;
    case 0x2B8A:                                    /* switch 1 */
        temp_a2_5 = campaignWork.eventStep;
        switch (temp_a2_5) {                        /* switch 20; irregular */
        case 0:                                     /* switch 20 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureState = 1;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 20 */
            if (campaignWork.cinemaState == 2) {
                if (campaignWork.eventPictureState < 3) {
                    campaignWork.eventPictureState = 2;
                    campaignWork.talkSpeaker = 2;
                }
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 20 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 20 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 20 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B8B;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B8B:                                    /* switch 1 */
        temp_a0_2 = campaignWork.eventStep;
        switch (temp_a0_2) {                        /* switch 21; irregular */
        case 0:                                     /* switch 21 */
            func_00233F50(3);
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 21 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2B8C;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B8C:                                    /* switch 1 */
        temp_a2_6 = campaignWork.eventStep;
        switch (temp_a2_6) {                        /* switch 22; irregular */
        case 0:                                     /* switch 22 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk5483 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 22 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 22 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 22 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                (*(s16 *)(ctx + 0xC2)) = (s16) ((*(s16 *)(ctx + 0xC2)) + 1);
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 22 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x6C;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B8D:                                    /* switch 1 */
        temp_v1_12 = campaignWork.eventStep;
        switch (temp_v1_12) {                       /* switch 23; irregular */
        case 0:                                     /* switch 23 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk5483 = 1;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 23 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.unk5483 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                func_00217980(4, 0);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 23 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x6C;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2B98:                                    /* switch 1 */
        temp_v1_13 = campaignWork.eventStep;
        switch (temp_v1_13) {                       /* switch 24 */
        case 0:                                     /* switch 24 */
            func_00217980(0x1F, 0);
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 3;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk546C = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 24 */
            if (campaignWork.cinemaState == 2) {
                func_001E7F70(3, 0, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 24 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 3;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 24 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 24 */
            if (campaignWork.talkPage == 3) {
                if (campaignWork.unk546C == 0) {
                    func_00217980(0x1F, 1);
                    campaignWork.unk546C = 1;
                }
            }
            if (campaignWork.talkPage == 0xD) {
                if (campaignWork.unk546C < 2) {
                    func_00217980(0x20, 1);
                    campaignWork.unk546C = 2;
                    campaignWork.unk547F = 1;
                    campaignWork.unk5480 = 0;
                }
            }
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 24 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 24 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2B9A;
                campaignWork.eventStep = 0;
                campaignWork.eventPictureState = 0;
                campaignWork.eventPictureX = 0;
                campaignWork.eventPictureY = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 24 */
            goto dflt_3;
        }
        break;
    case 0x2B9A:                                    /* switch 1 */
        temp_v1_14 = campaignWork.eventStep;
        switch (temp_v1_14) {                       /* switch 25 */
        case 0:                                     /* switch 25 */
            func_001F48F0(0, 0x191, 0, 0, 0);
            campaignWork.cameraTarget[0] = 0;
            campaignWork.cameraTarget[2] = 0;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 2;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0x1000;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk546E = 0;
            campaignWork.unk5470 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 25 */
            if (campaignWork.cinemaState == 2) {
                func_00217710(0, 0x22);
                func_00217710(0, 0x23);
                campaignWork.zoomMove = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 25 */
            if (campaignWork.zoomMove == 0) {
                campaignWork.cloudState = 0x1E;
                campaignWork.cloudCover = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 25 */
            if (campaignWork.cloudState == 0x1F) {
                campaignWork.cloudState = 0x20;
                campaignWork.cloudCover = 0x1000;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 25 */
            if (campaignWork.cloudState == 0x21) {
                campaignWork.eventPictureZoom = (s8) (campaignWork.eventPictureZoom - 4);
                if (campaignWork.eventPictureZoom < -0x63) {
                    campaignWork.eventPictureZoom = -0x64;
                    campaignWork.unk546E = 1;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 5:                                     /* switch 25 */
            if ((campaignWork.unk546E == 5) && (campaignWork.unk547F == 4)) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                func_00217980(0x21, 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 25 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 7:                                     /* switch 25 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                func_00217980(4, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 8:                                     /* switch 25 */
            if (campaignWork.cinemaState == 2) {
                func_001E7F70(3, 2, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 9:                                     /* switch 25 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                (*(s8 *)(ctx + 0xC9)) = 1;
                campaignWork.cameraTarget[0] = D_00298DDC;
                campaignWork.cameraTarget[2] = D_00298DE4;
                goto end_0021E330;
            }
            break;
        case 10:                                    /* switch 25 */
            if (campaignWork.cinemaState == 2) {
                (*(s8 *)(ctx + 0xC9)) = 1;
                campaignWork.cameraTarget[0] = D_00298DDC;
                campaignWork.cameraTarget[2] = D_00298DE4;
                (*(s16 *)(ctx + 0xC2)) = 0x70;
                campaignWork.eventStep = 0;
                campaignWork.unk5374 = 1;
                campaignWork.unk5375 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 0;
                campaignWork.leaderShow = 0;
                campaignWork.unk546C = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 25 */
            goto dflt_3;
        }
        break;
    case 0x2BAC:                                    /* switch 1 */
        temp_v1_15 = campaignWork.eventStep;
        switch (temp_v1_15) {                       /* switch 26 */
        case 0:                                     /* switch 26 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 3;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk546E = 0;
            campaignWork.unk5470 = 0;
            campaignWork.unk547F = 0;
            campaignWork.unk5480 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 26 */
            if (campaignWork.cinemaState == 2) {
                func_001E7F70(3, 0, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 26 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 3;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 26 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 26 */
            if (campaignWork.talkPage == 3) {
                if ((campaignWork.talkStep == 3) && (campaignWork.unk546E == 0) && (campaignWork.eventPictureZoom < -0x63)) {
                    campaignWork.unk546E = 1;
                    campaignWork.unk5470 = 0;
                    campaignWork.unk547F = 1;
                }
            }
            if ((campaignWork.talkStep == 0xC) && (campaignWork.unk546E == 5) && (campaignWork.unk547F == 4)) {
                campaignWork.talkStep = 0xD;
                campaignWork.unk547F = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 26 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.unk546E = 0;
                campaignWork.unk5470 = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 26 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2BAE;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 26 */
            goto dflt_3;
        }
        break;
    case 0x2BAE:                                    /* switch 1 */
        temp_v1_16 = campaignWork.eventStep;
        switch (temp_v1_16) {                       /* switch 27 */
        case 0:                                     /* switch 27 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = -0x180;
            campaignWork.eventPictureState = 1;
            func_00217980(0x22, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 27 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureX = (s16) (campaignWork.eventPictureX - 2);
                if (campaignWork.eventPictureX < -0xC0) {
                    campaignWork.eventPictureX = -0xC0;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                temp_a1_2 = campaignWork.eventPictureX;
                campaignWork.eventPictureY = (-temp_a1_2 * 0x180) / 384 - 0x180;
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 27 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 27 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 1;
                campaignWork.eventPictureState = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 27 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureX = (s16) (campaignWork.eventPictureX - 2);
                if (campaignWork.eventPictureX < -0x180) {
                    campaignWork.eventPictureX = -0x180;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                temp_a1_3 = campaignWork.eventPictureX;
                campaignWork.eventPictureY = (-temp_a1_3 * 0x180) / 384 - 0x180;
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 3;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 5:                                     /* switch 27 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2BB0;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 27 */
            goto dflt_3;
        }
        break;
    case 0x2BB0:                                    /* switch 1 */
        temp_v1_17 = campaignWork.eventStep;
        switch (temp_v1_17) {                       /* switch 28; irregular */
        case 0:                                     /* switch 28 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 1;
            campaignWork.cameraTarget[0] = 0;
            campaignWork.cameraTarget[2] = 0;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.zoomMove = 1;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = 0;
            campaignWork.eventPictureY = 0;
            campaignWork.unk5447 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto block_534;
        case 1:                                     /* switch 28 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            }
            goto block_534;
        case 2:                                     /* switch 28 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                (*(s16 *)(ctx + 0x3C)) = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            }
            goto block_534;
        case 3:                                     /* switch 28 */
            if (campaignWork.cinemaState == 2) {
                if (campaignWork.helpOpen == 0) {
                    (*(s8 *)(ctx + 1)) = 1;
                    if ((*(s8 *)(ctx + 1)) != 0) {
                        if ((*(s8 *)(ctx + 2)) != 0) {
                            func_00217230(0, 1);
                        }
                    }
                    func_001AAFA0(2);
                    campaignWork.helpOpen = 1;
                }
                if (0 > func_001AB1D0()) {
                    campaignWork.helpOpen = 0;
                    func_001A8360(2, 1, 0);
                    campaignMoveDone = 1;
                    func_001A8320(0xA, 1);
                    func_001A8920();
                    goto block_534;
                }
            } else {
                goto block_534;
            }
            break;
        default:                                    /* switch 28 */
block_534:
            if (campaignWork.zoom > 0xBB8) {
                campaignWork.cloudState = 4;
            }
            if ((campaignWork.zoom > 0x7D0) && (campaignWork.unk5447 == 0)) {
                func_001F48F0(0, 0x192, 0, 0, 0);
                campaignWork.unk5447 = 1;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2EE0:                                    /* switch 1 */
        temp_v1_18 = campaignWork.eventStep;
        switch (temp_v1_18) {                       /* switch 29; irregular */
        case 0:                                     /* switch 29 */
            func_00233F50(2);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.unk546E = 0;
            campaignWork.unk5470 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 29 */
            if (campaignWork.talkPage == 4) {
                if ((campaignWork.talkStep == 3) && (campaignWork.unk546E == 0)) {
                    campaignWork.unk546E = 1;
                    campaignWork.unk5470 = 0;
                }
            }
            if ((campaignWork.talkStep == 0xC) && (campaignWork.unk546E == 5)) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 29 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cloudState = 0x16;
                campaignWork.unk546E = 0;
                campaignWork.unk5470 = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 29 */
            if (campaignWork.cloudState == 0x17) {
                func_00233F50(3);
                campaignWork.zoomMove = 0;
                campaignWork.zoom = 0;
                campaignWork.cloudState = 0;
                campaignWork.cloudCover = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventWindowState = 0;
                campaignWork.eventWindowOpen = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                func_001E7F70(3, 2, 0);
                func_001F93F0(0, 7, 0, NULL);
                func_001F6E80(7, 1.0f);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 29 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 0;
                campaignWork.cameraTarget[0] = D_00298DDC;
                campaignWork.cameraTarget[2] = D_00298DE4;
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x64;
                func_00217980(4, 1);
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F08:                                    /* switch 1 */
        temp_v1_19 = campaignWork.eventStep;
        switch (temp_v1_19) {                       /* switch 30; irregular */
        case 0:                                     /* switch 30 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            func_00217980(0x23, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 30 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 30 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x68;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F09:                                    /* switch 1 */
        temp_a1_4 = campaignWork.eventStep;
        switch (temp_a1_4) {                        /* switch 31; irregular */
        case 0:                                     /* switch 31 */
            func_00233F50(2);
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 31 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 31 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.placeReached[16] = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 31 */
            if ((campaignWork.placeReached[16] == 0) && (func_0022C3C0(1) != 0)) {
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 31 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0;
                campaignWork.eventStep = 0;
                campaignWork.unk5374 = 0;
                campaignWork.unk5375 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 0;
                campaignWork.leaderShow = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F62:                                    /* switch 1 */
        temp_v1_20 = campaignWork.eventStep;
        switch (temp_v1_20) {                       /* switch 32 */
        case 0:                                     /* switch 32 */
            func_00233F50(3);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            func_00217980(0x24, 1);
            func_001E7F70(3, 0, 0);
            campaignWork.unk547F = 0;
            campaignWork.unk5480 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 32 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 3;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 32 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 32 */
            if (campaignWork.talkPage == 2) {
                if (campaignWork.talkStep == 3) {
                    campaignWork.unk547F = 1;
                }
            }
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 32 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 32 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2F64;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 32 */
            goto dflt_3;
        }
        break;
    case 0x2F64:                                    /* switch 1 */
        temp_v1_21 = campaignWork.eventStep;
        switch (temp_v1_21) {                       /* switch 33 */
        case 0:                                     /* switch 33 */
            func_001F48F0(0, 0x191, 0, 0, 0);
            campaignWork.cameraTarget[0] = 0;
            campaignWork.cameraTarget[2] = 0;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 2;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0x1000;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.unk546E = 0;
            campaignWork.unk5470 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 33 */
            if (campaignWork.cinemaState == 2) {
                func_00217710(0, 0x22);
                func_00217710(0, 0x23);
                campaignWork.zoomMove = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 33 */
            if (campaignWork.zoomMove == 0) {
                campaignWork.cloudState = 0x1E;
                campaignWork.cloudCover = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 33 */
            if (campaignWork.cloudState == 0x1F) {
                campaignWork.cloudState = 0x20;
                campaignWork.cloudCover = 0x1000;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 33 */
            if (campaignWork.cloudState == 0x21) {
                campaignWork.eventPictureZoom = (s8) (campaignWork.eventPictureZoom - 4);
                if (campaignWork.eventPictureZoom < -0x63) {
                    campaignWork.eventPictureZoom = -0x64;
                    campaignWork.unk546E = 1;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 5:                                     /* switch 33 */
            if ((campaignWork.unk546E == 5) && (campaignWork.unk547F == 4)) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                func_00217980(0x21, 1);
                goto end_0021E330;
            }
            break;
        case 6:                                     /* switch 33 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 7:                                     /* switch 33 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                func_00217980(4, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 8:                                     /* switch 33 */
            if (campaignWork.cinemaState == 2) {
                func_001E7F70(3, 2, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 9:                                     /* switch 33 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 0;
                campaignWork.cameraTarget[0] = D_00298DDC;
                campaignWork.cameraTarget[2] = D_00298DE4;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 10:                                    /* switch 33 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0;
                campaignWork.unk5374 = 0;
                campaignWork.unk5375 = 0;
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.moveStep = 0;
                campaignWork.unk5372 = 0;
                campaignWork.leaderShow = 0;
                campaignWork.unk546C = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 33 */
            goto dflt_3;
        }
        break;
    case 0x2F76:                                    /* switch 1 */
        temp_a2_7 = campaignWork.eventStep;
        switch (temp_a2_7) {                        /* switch 34; irregular */
        case 0:                                     /* switch 34 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 3;
            campaignWork.cameraMode = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.unk546E = 0;
            campaignWork.unk5470 = 0;
            campaignWork.unk547F = 0;
            campaignWork.unk5480 = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 34 */
            if (campaignWork.cinemaState == 2) {
                func_001E7F70(3, 0, 0);
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 34 */
            if (func_001FF300() == 0) {
                campaignWork.cameraMode = 3;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 2;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 34 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 34 */
            if (campaignWork.talkPage == 2) {
                if ((campaignWork.unk546E == 0) && (campaignWork.eventPictureZoom < -0x63)) {
                    campaignWork.unk546E = 1;
                    campaignWork.unk5470 = 0;
                    campaignWork.unk547F = 1;
                }
            }
            if ((campaignWork.talkStep == 0xC) && (campaignWork.unk546E == 5) && (campaignWork.unk547F == 4)) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventStep = 0;
                (*(s16 *)(ctx + 0xC2)) = 0x2F78;
                campaignWork.unk546E = 0;
                campaignWork.unk5470 = 0;
                campaignWork.unk547F = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F78:                                    /* switch 1 */
        temp_a2_8 = campaignWork.eventStep;
        switch (temp_a2_8) {                        /* switch 35; irregular */
        case 0:                                     /* switch 35 */
            func_00233F50(2);
            campaignWork.cameraMode = 3;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 1;
            campaignWork.talkPage = 1;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            func_00217980(0x25, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 35 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 2:                                     /* switch 35 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 35 */
            if (campaignWork.cinemaState == 2) {
                (*(s16 *)(ctx + 0xC2)) = 0x2F7A;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        }
        break;
    case 0x2F7A:                                    /* switch 1 */
        temp_v1_22 = campaignWork.eventStep;
        switch (temp_v1_22) {                       /* switch 36 */
        case 0:                                     /* switch 36 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 1;
            campaignWork.cameraMode = 1;
            campaignWork.cameraTarget[0] = 0;
            campaignWork.cameraTarget[2] = 0;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.zoomMove = 0;
            campaignWork.zoom = 0;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.eventPictureState = 0;
            campaignWork.eventPictureX = -0x180;
            campaignWork.eventPictureY = 0;
            campaignWork.eventPictureState = 1;
            campaignWork.eventPictureFade = 0;
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto end_0021E330;
        case 1:                                     /* switch 36 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.eventPictureX = (s16) (campaignWork.eventPictureX + 2);
                if (0 < campaignWork.eventPictureX) {
                    campaignWork.eventPictureX = 0;
                    if (campaignWork.eventPictureState < 3) {
                        campaignWork.eventPictureState = 2;
                        campaignWork.talkSpeaker = 2;
                    }
                }
                temp_a2_9 = campaignWork.eventPictureX;
                campaignWork.eventPictureY = (-temp_a2_9 * 0x19C) / 384 - 0x19C;
                if (campaignWork.eventPictureState == 3) {
                    campaignWork.cinemaState = 1;
                    campaignWork.cinemaMode = 2;
                    campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                    goto end_0021E330;
                }
            }
            break;
        case 2:                                     /* switch 36 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 3:                                     /* switch 36 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0xD;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 4:                                     /* switch 36 */
            if (campaignWork.talkStep == 0xE) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.eventPictureFade = 1;
                campaignWork.eventPictureAlpha = 0x80;
                campaignWork.zoomMove = 1;
                campaignWork.zoom = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
                goto end_0021E330;
            }
            break;
        case 5:                                     /* switch 36 */
            if (campaignWork.eventPictureFade == 0xA) {
                (*(s16 *)(ctx + 0xC2)) = 0x2F7C;
                campaignWork.eventStep = 0;
                goto end_0021E330;
            }
            break;
        default:                                    /* switch 36 */
            goto dflt_3;
        }
        break;
    case 0x2F7C:                                    /* switch 1 */
        temp_v1_23 = campaignWork.eventStep;
        switch (temp_v1_23) {                       /* switch 37; irregular */
        case 0:                                     /* switch 37 */
            campaignWork.cinemaState = 1;
            campaignWork.cinemaMode = 2;
            campaignWork.cameraMode = 1;
            campaignWork.cameraTarget[0] = 0;
            campaignWork.cameraTarget[2] = 0;
            *(s32 *)&campaignWork.cameraTarget[3] = 0;
            campaignWork.zoomMove = 1;
            campaignWork.cloudState = 0;
            campaignWork.cloudCover = 0;
            campaignWork.talkStep = 0;
            campaignWork.talkPage = 0;
            campaignWork.unk53B4 = 0;
            campaignWork.unk53B5 = 0;
            campaignWork.eventWindowState = 0;
            campaignWork.eventWindowOpen = 0;
            campaignWork.unk5447 = 0;
            func_00217980(0x26, 1);
            campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            goto block_727;
        case 1:                                     /* switch 37 */
            if (campaignWork.cinemaState == 2) {
                campaignWork.talkStep = 1;
                campaignWork.talkPage = 1;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            }
            goto block_727;
        case 2:                                     /* switch 37 */
            if (campaignWork.talkStep == 0xC) {
                campaignWork.talkStep = 0;
                campaignWork.talkPage = 0;
                campaignWork.cinemaState = 1;
                campaignWork.cinemaMode = 3;
                (*(s16 *)(ctx + 0x3C)) = 0;
                campaignWork.eventStep = (s16) (campaignWork.eventStep + 1);
            }
            goto block_727;
        case 3:                                     /* switch 37 */
            if (campaignWork.cinemaState == 2) {
                if (campaignWork.helpOpen == 0) {
                    (*(s8 *)(ctx + 2)) = 1;
                    if ((*(s8 *)(ctx + 1)) != 0) {
                        if ((*(s8 *)(ctx + 2)) != 0) {
                            func_00217230(0, 1);
                        }
                    }
                    func_001AAFA0(2);
                    campaignWork.helpOpen = 1;
                }
                if (0 > func_001AB1D0()) {
                    campaignWork.helpOpen = 0;
                    func_001A8360(3, 1, 0);
                    campaignMoveDone = 1;
                    func_001A8320(0xA, 1);
                    func_001A8920();
                    (*(s16 *)(ctx + 0xC2)) = 0;
                    goto block_727;
                }
            } else {
                goto block_727;
            }
            break;
        default:                                    /* switch 37 */
block_727:
            if (campaignWork.zoom > 0xBB8) {
                campaignWork.cloudState = 4;
            }
            if ((campaignWork.zoom > 0x7D0) && (campaignWork.unk5447 == 0)) {
                func_001F48F0(0, 0x192, 0, 0, 0);
                campaignWork.unk5447 = 1;
                goto end_0021E330;
            }
            break;
        }
        break;
    default:
        campaignWork.cameraMode = 0;
        break;
    }
end_0021E330:;
}
