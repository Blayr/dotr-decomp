#ifndef CAMPAIGN_H
#define CAMPAIGN_H

/*
 * The campaign work area: a fixed block of memory at 0x01ED0000 that the campaign map (Taku_*, TkCamp_*) keeps
 * its running state in: the camera, the routes drawn between places, the event script's step, the talk window,
 * the cut-scene player and the menus. The original code reads it through raw addresses; here it is one struct,
 * `campaignWork`, so `*(s16 *)0x01ED536C` reads `campaignWork.eventStep`.
 *
 * Other screens reuse the same memory as scratch while the campaign is not running (deck building and trade keep
 * card lists there, the AI's search tree and the slot machine use it, duel effects load into it): those users
 * take CAMPAIGN_WORK_ADDR (common.h) as a plain buffer address and are not part of this layout.
 *
 * Unknown space is padXXXX; a field whose use is known but not its meaning is unkXXXX (offset in the name).
 * Where the original reads a field with another type than the one declared here, the code keeps that read
 * as `*(type *)&campaignWork.field`: it is the same address, and the read type decides the instruction.
 */

/* One route on the campaign map between two places: the points of the drawn line. */
typedef struct CampaignRoute {
    f32 x[64];       /* 0x000 */
    f32 z[64];       /* 0x100 */
    s16 count;       /* 0x200: points used */
    s16 state;       /* 0x202: 0 hidden, 1 drawing in, 2 drawing out, 3 drawn */
} CampaignRoute;     /* 0x204 bytes */

/* A face picture request for ShFace_Request / ShFace_Close (the portraits beside the campaign's windows). */
typedef struct CampaignFace {
    u8 id;           /* 0x0: 255 = new request */
    u8 no;           /* 0x1: whose face */
    u8 kind;         /* 0x2: which expression */
    u8 mode;         /* 0x3: 1 open, 3 change */
    u16 x;           /* 0x4 */
    u16 y;           /* 0x6 */
} CampaignFace;      /* 8 bytes */

typedef struct CampaignWork {
    s16 cursorX;                             /* 0x0000: the map cursor (hand) on screen; also the system-menu cursor */
    s16 cursorY;                             /* 0x0002 */
    u16 unk0004;                             /* 0x0004: 1 while the button for the place info is held; 2 in the free-duel menu (TkCamp_Act) */
    s16 terrainCounts[10];                   /* 0x0006: the terrain window (Taku_Camp_TERRAIN_Map_Show): how many squares of each terrain the duel field has */
    s16 cinemaMode;                          /* 0x001A: the cut-scene player (Taku_Camp_CINEMA_*): which kind of shot */
    s16 cinemaState;                         /* 0x001C: 0 off, 1 starting, then the player's own steps */
    s16 cinemaCut[3];                        /* 0x001E: the three shot numbers of the current cut */
    u8 pad0024[0xC];
    f32 cameraEye[4];                        /* 0x0030: x, y, z, w: where the map camera stands (SzView_SetCamera) */
    f32 cameraTarget[4];                     /* 0x0040: x, y, z, w: what it looks at */
    f32 moveFromX;                           /* 0x0050: the camera target's x when a camera move began (Taku_Focus_move*) */
    u8 pad0054[0x4];
    f32 moveFromZ;                           /* 0x0058: its z */
    u8 pad005C[0x4];
    s16 moveStep;                            /* 0x0060: the camera move's step (0 = idle) */
    s8 zoomMove;                             /* 0x0062: 0 still, 1 zooming in (zoom rises to 0x1000), 2 zooming out (to 0) */
    u8 pad0063[0x1];
    s16 zoom;                                /* 0x0064: 0..0x1000: how far the map camera is pulled back */
    s8 terrainWindowOn;                      /* 0x0066: the terrain window is shown; toggled with a button */
    u8 pad0067[0x1];
    s16 terrainWindowOpen;                   /* 0x0068: its open animation, 0..16 */
    s8 unk006A;                              /* 0x006A */
    u8 pad006B[0x1];
    s16 windowOpen;                          /* 0x006C: 0..0x100: the open animation of the campaign windows (Taku_Window_Set) */
    s8 unk006E;                              /* 0x006E */
    u8 pad006F[0x1];
    s16 iconSlide;                           /* 0x0070: 0..0x100: the system icons sliding in */
    s8 unk0072;                              /* 0x0072 */
    u8 pad0073[0x1];
    s16 cursorMoveT;                         /* 0x0074: 0..0x100: the cursor gliding from cursorFromX/Y to a system icon */
    s16 cursorFromX;                         /* 0x0076 */
    s16 cursorFromY;                         /* 0x0078 */
    s16 unk007A;                             /* 0x007A */
    s16 unk007C;                             /* 0x007C */
    s8 unk007E;                              /* 0x007E */
    u8 pad007F[0x1];
    s16 iconUnderCursor;                     /* 0x0080: the system icon (0..3) under the cursor */
    s16 iconGrow[4];                         /* 0x0082: per system icon: 0..16, it grows while the cursor is on it */
    u8 pad008A[0x2];
    s32 placeScreenX[32];                    /* 0x008C: per place: where it is on screen (Taku_3D_2D_Set, every frame) */
    s32 placeScreenY[32];                    /* 0x010C */
    s8 unk018C;                              /* 0x018C: nonzero: the menu choice at campaignState+0xC9 runs over 3 entries instead of 2 */
    u8 pad018D[0x3];
    f32 groundPlane[4];                      /* 0x0190: the map's ground plane (Ex3d_GetSurfaceC), for picking where the cursor points */
    u8 pad01A0[0x4];
    s16 shipState;                           /* 0x01A4: the ship (Taku_Camp_3D_SHIP): 0 none, 1 start (Taku_Ship_init), 2 sailing, 3 arrived */
    s16 shipT;                               /* 0x01A6: 0..1024 between two route points */
    s32 shipAngle;                           /* 0x01A8 */
    s8 unk01AC;                              /* 0x01AC */
    u8 pad01AD[0x1];
    s16 unk01AE;                             /* 0x01AE */
    s16 shipPoint;                           /* 0x01B0: the route point the ship sails from */
    s16 shipTo;                              /* 0x01B2: the place the ship sails to */
    s8 shipOn;                               /* 0x01B4 */
    u8 pad01B5[0x3];
    f32 shipPos[3];                          /* 0x01B8: x, y, z: the ship's position (SzModel_Draw_Pipe reads it here) */
    u8 pad01C4[0x4];
    f32 leaderAimX;                          /* 0x01C8: the point the leader model walks towards (mean of the route points) */
    u8 pad01CC[0x4];
    f32 leaderAimZ;                          /* 0x01D0 */
    u8 pad01D4[0x4];
    s16 leaderMoveState;                     /* 0x01D8: the leader model's walk between places (Taku_Focus_move_decide): 0 idle, 1 walking, 2 walking back, 3 arrived */
    s16 leaderT;                             /* 0x01DA: 0..1024 between two route points */
    u8 pad01DC[0x2];
    s16 leaderPoint;                         /* 0x01DE: the route point the leader walks from */
    u8 pad01E0[0x10];
    f32 leaderPos[3];                        /* 0x01F0: the leader model's position on the map */
    u8 pad01FC[0x4];
    s32 leaderAngle;                         /* 0x0200 */
    u8 pad0204[0x20];
    s16 windowAlpha[3];                      /* 0x0224: the three campaign windows dim from 0x80 to 0x60 while a menu is up */
    u8 pad022A[0x2];
    CampaignRoute routes[2][16];             /* 0x022C: the routes drawn between the places, per side and route number */
    s16 routeDrawn[2][16];                   /* 0x42AC: per route: how many points are drawn so far */
    s16 routePointRise[2][16][64];           /* 0x42EC: per route point: 0..256, the marker rising out of the ground */
    s16 placeReached[32];                    /* 0x52EC: per place: set to 1 when a route reaching it has been drawn */
    s16 placeBlink[32];                      /* 0x532C: per place: a counter that makes a newly reached place blink (Taku_Camp_3D) */
    s16 eventStep;                           /* 0x536C: the step inside the current event's script (Taku_Camp_Event); reset when the cut-scene number changes */
    s16 eventCutScene;                       /* 0x536E: the cut-scene number the step belongs to (campaignState's cut-scene number last frame) */
    s16 savedCutScene;                       /* 0x5370: the cut-scene number put aside while a route event plays (Taku_Base_Route_init) */
    s8 unk5372;                              /* 0x5372 */
    s8 leaderShow;                           /* 0x5373: the leader model is on the map (>0); while set, the cursor stays on the selected place (main_068) */
    s8 unk5374;                              /* 0x5374 */
    s8 unk5375;                              /* 0x5375 */
    s8 routesIdle;                           /* 0x5376: 1 when no route is being drawn (Taku_Camp_3D_POLE); the map takes input only then */
    u8 pad5377[0x1];
    s16 talkMessage;                         /* 0x5378: the first message of the talk (Taku_Camp_TEXT_PICK picks it) */
    s8 unk537A;                              /* 0x537A */
    s8 talkStep;                             /* 0x537B: the talk window's step (Taku_Camp_TEXT_*); events wait for given steps */
    s8 talkMessageCount;                     /* 0x537C: how many messages the talk has */
    s8 talkPage;                             /* 0x537D: which message of the talk is showing */
    s8 talkSpeaker;                          /* 0x537E: who speaks (Taku_Camp_TEXT_WHO) */
    u8 pad537F[0x1];
    s16 unk5380[4][4];                       /* 0x5380 */
    s8 unk53A0;                              /* 0x53A0 */
    u8 pad53A1[0x1];
    s16 cloudState;                          /* 0x53A2: the clouds over the map (Taku_Camp_Clouds): even = moving, odd = arrived */
    s16 cloudCover;                          /* 0x53A4: 0..0x1000 */
    s8 eventWindowState;                     /* 0x53A6: the event window (Taku_Camp_Event_Window): 0 closed, 1 opening, 2 open and waiting, 3 closing, 4 closed again */
    s8 eventWindowOpen;                      /* 0x53A7: 0..100: its open animation */
    s8 eventWindowChoice;                    /* 0x53A8: the choice made in it (the starting deck: index into deckChoices) */
    s8 deckChoiceSlide;                      /* 0x53A9: the starting-deck choice (Taku_DECK_CARD_DISP): 0..100, the cards sliding to the next deck */
    s8 deckChoiceTurn;                       /* 0x53AA: which way they slide */
    s8 unk53AB;                              /* 0x53AB */
    s8 eventPictureState;                    /* 0x53AC: the event picture sliding in (Taku_Camp_Event_Picture): 0 off, 1 sliding, 2 in place, 3 done */
    u8 pad53AD[0x1];
    s16 eventPictureX;                       /* 0x53AE */
    s16 eventPictureY;                       /* 0x53B0 */
    s8 unk53B2;                              /* 0x53B2 */
    s8 cameraMode;                           /* 0x53B3: how the map camera moves: 1, 2, 3 (TkCamp_Act); sets the zoom speed */
    s8 unk53B4;                              /* 0x53B4 */
    s8 unk53B5;                              /* 0x53B5 */
    s16 duelistSlide[2];                     /* 0x53B6: the two duelists sliding in before a duel */
    s16 duelistName[2];                      /* 0x53BA: the two duelists shown before a duel (Taku_Camp_Set_Go_Duel): their name messages */
    s8 duelistSide[2];                       /* 0x53BE */
    s8 unk53C0;                              /* 0x53C0 */
    s8 unk53C1;                              /* 0x53C1 */
    s8 duelMenuChoice;                       /* 0x53C2: copied from campaignState's menu choice */
    s8 nameColumn;                           /* 0x53C3: the name entry (cut-scene 0x2738): the cursor's column in the letter table, 0..14 */
    s8 nameRow;                              /* 0x53C4: its row, 0..5 */
    s8 namePickedColumn;                     /* 0x53C5: the letter being typed */
    s8 namePickedRow;                        /* 0x53C6 */
    s8 nameTable;                            /* 0x53C7: which letter table, 0..2 */
    s8 nameTableTurn;                        /* 0x53C8: 1 or 2 while the table turns to the next one */
    s8 nameTableSlide;                       /* 0x53C9: -100..100: that turn's animation */
    s8 nameTyping;                           /* 0x53CA: 1 while a letter flies into the name */
    s8 nameTypingT;                          /* 0x53CB: 0..100: that letter's flight */
    s8 nameBlink;                            /* 0x53CC: the name entry's blinking cursor */
    s8 nameLength;                           /* 0x53CD: letters typed, 0..12 */
    s8 nameCursor;                           /* 0x53CE */
    s8 nameLetterTable[12];                  /* 0x53CF: per letter of the name: its table */
    s8 nameLetterColumn[12];                 /* 0x53DB: its column */
    s8 nameLetterRow[12];                    /* 0x53E7: its row */
    u8 pad53F3[0x1];
    s16 stoneSpin;                           /* 0x53F4: the turning stone model's rotation (Taku_Camp_STONE) */
    u16 startingDeckSet;                     /* 0x53F6: the name's 12 letters summed mod 16 (after the name entry): picks the set of starting decks offered */
    u16 deckChoices[3];                      /* 0x53F8: the starting decks offered (SzData_SetupFromConstDeck) */
    u16 deckChoiceCards[3];                  /* 0x53FE: the three starting decks' cards on show (campaignDeckChoices[].value & 0x3FF) */
    s16 leaderCard;                          /* 0x5404: the leader shown on the map (SzData_GetLeader) */
    s8 unk5406;                              /* 0x5406 */
    s8 duelistState[2];                      /* 0x5407 */
    u8 pad5409[0x1];
    s8 opponentFaceState;                    /* 0x540A: the enemy window's face picture: 0 none, 1 open it, 2 shown, 10 change it, 100 close it */
    u8 pad540B[0x1];
    CampaignFace duelistFace[2];             /* 0x540C: the two duelists' face pictures before a duel */
    u8 pad541C[0x8];
    CampaignFace opponentFace;               /* 0x5424: the opponent's face picture (the enemy window, Taku_Camp_ENEMY_WINDOW) */
    s16 unk542C[5];                          /* 0x542C */
    s8 unk5436;                              /* 0x5436 */
    s8 eventPictureZoom;                     /* 0x5437: 0..100: the event picture growing out of the map (camera and picture follow it) */
    u8 pad5438[0x2];
    s16 unk543A;                             /* 0x543A */
    s8 helpOpen;                             /* 0x543C: the help window (Taku_Camp_Go_Help) */
    s8 helpStep;                             /* 0x543D */
    s8 unk543E;                              /* 0x543E */
    s8 unk543F;                              /* 0x543F */
    s8 unk5440;                              /* 0x5440 */
    u8 pad5441[0x1];
    s16 playerDeckCost;                      /* 0x5442: the player's deck cost (SzData_GetDeckCost(0), shown in the status window) */
    s16 opponentDeckCost;                    /* 0x5444: the opponent's deck cost (SzData_GetDeckCost(1), the enemy window); TkCamp_Act's deck-cost gate compares the two */
    s8 unk5446;                              /* 0x5446 */
    s8 unk5447;                              /* 0x5447 */
    s8 placeSound[32];                       /* 0x5448: per place: its arrival sound has played */
    s8 opponentLook;                         /* 0x5468: the opponent's pose in the enemy window */
    s8 duelist1Look;                         /* 0x5469: the pose of the second duelist shown before a duel (main_066's DOTR_DARE_LOOK1; Taku_Camp_TEXT_PICK sets both) */
    s8 duelist0Look;                         /* 0x546A: the pose of duelist 0 */
    s8 helpPick;                             /* 0x546B: the help page chosen */
    s8 unk546C;                              /* 0x546C */
    s8 unk546D;                              /* 0x546D */
    s8 unk546E;                              /* 0x546E */
    u8 pad546F[0x1];
    s16 unk5470;                             /* 0x5470 */
    s8 unk5472;                              /* 0x5472 */
    u8 pad5473[0x1];
    s32 unk5474;                             /* 0x5474 */
    s16 unk5478;                             /* 0x5478 */
    s8 cursorOnIcon;                         /* 0x547A: set when the cursor is on a system icon */
    u8 pad547B[0x1];
    s16 leaderAlpha;                         /* 0x547C: the leader model's fade (0x80 = solid) */
    u8 unk547E;                              /* 0x547E */
    s8 unk547F;                              /* 0x547F */
    s8 unk5480;                              /* 0x5480 */
    s8 unk5481;                              /* 0x5481 */
    s8 placesReached;                        /* 0x5482: how many places have placeReached set (TkCamp_Act counts them) */
    s8 unk5483;                              /* 0x5483 */
    s8 unk5484;                              /* 0x5484 */
    u8 pad5485[0x1];
    u16 unk5486;                             /* 0x5486 */
    s8 unk5488;                              /* 0x5488 */
    u8 pad5489[0x3];
    f32 eventPictureMapX;                    /* 0x548C: the place the event picture grows from, on the map */
    f32 eventPictureMapZ;                    /* 0x5490 */
    s8 deckShowPhase;                        /* 0x5494: the starting decks' cards coming in: 0 sliding in, 1 shown, 2 chosen (Start), 3 going, 4 gone, 5 deck set up */
    s8 deckShowDone;                         /* 0x5495 */
    s8 deckShowSound[3];                     /* 0x5496: per card: its sound has played */
    u8 pad5499[0x1];
    s16 deckCardSlide[3];                    /* 0x549A: per card: 0..100 (400 going out), its slide */
    s8 eventPictureFade;                     /* 0x54A0: the event picture fading out: 0 off, 1 fading, 10 gone */
    u8 pad54A1[0x1];
    s16 eventPictureAlpha;                   /* 0x54A2 */
    u8 pad54A4[0xC];
} CampaignWork; /* 0x54B0 bytes */

#define campaignWork (*(CampaignWork *)CAMPAIGN_WORK_ADDR)

#endif
