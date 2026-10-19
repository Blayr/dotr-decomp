#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "enums.h"

/* Declarations collected by `dk accept`. Move them into topic headers as the
 * game's structure becomes clear. */











extern s32 *g_SDValue;




extern u8 D_1FE0000;


/* Card ids: 0..CARD_COUNT-1. CARD_NONE marks an empty deck, graveyard or hand slot. Card 0x29F is
   treated as no card: the deck, graveyard and hand adders refuse it, Xax2New/New2Xax map it to
   CARD_NONE. */
#define CARD_COUNT 0x356
#define CARD_NONE 999
#define CARD_REJECTED 0x29F

/* The `operation` of SzDuel_CalcLP / SzDuel_CalcSummonPower. */
#define DUEL_CALC_ADD 0
#define DUEL_CALC_SUB 1
#define DUEL_CALC_MUL 2
#define DUEL_CALC_DIV 3
#define DUEL_CALC_SET 4

/* A side's deck: cards land in random free slots (SzDuel_AddDeck) and are drawn from cards[0]. */
typedef struct DuelDeck {
    u16 cards[40];
    u8 count;
} DuelDeck;

/* A side's graveyard, packed to the front (SzDuel_PackGrave). */
typedef struct DuelGrave {
    u16 cards[120];
    u8 count;
} DuelGrave;

/* A side's hand: card id in bits 0-11, a pick-order tag in bits 12-15 (SzDuel_SetHandTag). */
typedef struct DuelHand {
    u16 cards[5];
    u8 count;
} DuelHand;

/* Board squares, units, cards and the AI's task records. Names from batzpup's Ghidra project; the unit's, the
   card constants' and the card request's layouts are the developers' own (the Japanese release's debug
   information for the AI files, whose names follow each field). */

typedef struct Vec4i {
    s32 x, y, z, w;
} Vec4i;

/* A colour in the GS's byte order. */
typedef struct Rgba {
    u8 r, g, b, a;
} Rgba;

/* A card's constant record (gSzDuel_CardConstInfo[card id]; 0x14 bytes). */
typedef struct CardConstInfo {
    u8 kind;                        /* 0x00 (bKind) */
    u8 kindOfs;                     /* 0x01 (bKindOfs) */
    u8 lvAttr;                      /* 0x02: attribute and level, 4 bits each (bAttr, bLevel) */
    u8 deckCost;                    /* 0x03 (bDeckCost) */
    u16 effectId;                   /* 0x04 (wEffIdx) */
    u16 xaxId;                      /* 0x06 (wEffNo) */
    u16 apWithFlags;                /* 0x08: attack, and flags fPermanent, fGetPasswd, fGetRecycle (wAP) */
    u16 dpWithFlags;                /* 0x0A: defence, and flag fGetSlot (wDP) */
    u8 password[8];                 /* 0x0C */
} CardConstInfo;

/* A card drawn in 3D (cardRequests[32], 0xA0 bytes): where and how, and the unit it shows. */
typedef struct CardRequest {
    Vec4f pos;                      /* 0x00 (pntPos) */
    Vec4i rot;                      /* 0x10 (ivecRot) */
    Vec4i look;                     /* 0x20 (ivecLook) */
    Vec4f scale;                    /* 0x30 (vecScale) */
    Rgba color;                     /* 0x40 (icolRgba) */
    Rgba filter;                    /* 0x44 (icolFilter) */
    u8 node[0x30];                  /* 0x48 (Node) */
    void *nodePtr;                  /* 0x78 (pNode) */
    void *work;                     /* 0x7C (pWork) */
    u32 flags;                      /* 0x80: nMax, fBig, fLook, fScale, fColor, nNode, bFilterMode, fIgnore, fBusy */
    u8 pad84[0x90 - 0x84];
    struct Unit *unit;              /* 0x90: the unit it shows, or NULL (pVarInfo) */
    u8 pad94[0xA0 - 0x94];
} CardRequest;

/* One unit record (duelUnits[3][11], side 2 = the leaders' spare row; 0x5C bytes). */
typedef struct Unit {
    CardConstInfo *constInfo;       /* 0x00: the card's constant record (pConstInfo) */
    CardRequest *cardModel;         /* 0x04: the card drawn for it (pCardReq) */
    union {
        struct { s32 type, data; } effects[5];
        u16 leaderAbilities[20];
    } cardEffects;                  /* 0x08: monster effects, or a leader's abilities (aVarEffIdx) */
    s32 VisualRelated;              /* 0x30: its rotation (nRotY) */
    s16 xOffsetTerrain;             /* 0x34 (sOfsX) */
    s16 yOffsetTerrain;             /* 0x36 (sOfsZ) */
    s16 apBoost;                    /* 0x38 (sVarAP) */
    s16 dpBoost;                    /* 0x3A (sVarDP) */
    u16 cardNo;                     /* 0x3C: card id (wCardNo) */
    u8 kind;                        /* 0x3E (bVarKind) */
    u8 attr;                        /* 0x3F: Attribute (bVarAttr) */
    u8 locCol;                      /* 0x40: board column (bMapX) */
    u8 locRow;                      /* 0x41: board row (bMapZ) */
    u8 toMoveCol;                   /* 0x42 (bPosX) */
    u8 toMoveRow;                   /* 0x43 (bPosZ) */
    u8 team;                        /* 0x44: the side that owns it (bOwner) */
    u8 slot;                        /* 0x45: its unit number, 0 = leader (bID) */
    u8 modelId;                     /* 0x46 (bModelID) */
    u8 summonOrder;                 /* 0x47 (bSummonOrder) */
    u8 lvRev;                       /* 0x48 (bSummonCost) */
    u8 curseRest;                   /* 0x49 (bCurseRest) */
    u8 spellRest;                   /* 0x4A (bSpellRest) */
    u8 delayCount;                  /* 0x4B (bDelayCount) */
    u8 bMovable;                    /* 0x4C (bMovable) */
    u8 CardHighlight;               /* 0x4D: its glow (bDarkRate) */
    u8 ctlModeC;                    /* 0x4E (bCtlModeC) */
    u8 ctlModeM;                    /* 0x4F (bCtlModeM) */
    u8 ctlGoalC;                    /* 0x50 (bCtlGoalC) */
    u8 ctlGoalM;                    /* 0x51 (bCtlGoalM) */
    u8 ctlRateC;                    /* 0x52 (bCtlRateC) */
    u8 ctlRateM;                    /* 0x53 (bCtlRateM) */
    u8 openRate;                    /* 0x54 (bOpenRate) */
    u8 defenseRate;                 /* 0x55 (bDefenseRate) */
    struct {
        s8 nCtlFlipC : 2;
        s8 nCtlFlipM : 2;
        s8 nOpenFlip : 2;
        s8 nDefenseFlip : 2;
    } SomeStatusBitfield;           /* 0x56 */
    struct {
        s8 fFinish : 1;
        s8 fRevolt : 1;             /* controlled by the other side */
        s8 fOpen : 1;               /* face up */
        s8 fDefense : 1;
        s8 fOpenF : 1;
        s8 fDefenseF : 1;
        s8 fPickup : 1;
        s8 fCardBusy : 1;
    } status;                       /* 0x57 */
    struct {
        s8 fModelBusy : 1;
        s8 fCardColBusy : 1;
        s8 fHand : 1;
        s8 fCurse : 1;
        s8 nEffHandle : 4;
    } modelStatusFlags;             /* 0x58 */
    u8 pad59[3];
} Unit;

/* One board square (boardSquares: [7][7], [row][column]; 0x1C bytes). batzpup's names; the four colours are
   grouped as the code uses them (SzDuel_CalcMapColor moves each current colour towards its target). */
typedef struct MapInfo {
    Unit *unit;                     /* 0x00: the unit standing here, or NULL */
    Rgba TargetHighlight;       /* 0x04: the square's colour to fade to */
    Rgba Highlight;             /* 0x08: its colour now (a: its height) */
    Rgba TargetBorderOutline;   /* 0x0C: the unit's glow to fade to */
    Rgba BorderOutline;         /* 0x10: its glow now */
    s16 fieldRate;                  /* 0x14: the move highlight, -0x80..0x80 */
    u8 field;                       /* 0x16: the terrain (Field) */
    u8 MapMovable;                  /* 0x17: how far a unit can still walk from here (0xFF: not reached) */
    u8 TargetSelectionHighlight;    /* 0x18 */
    u8 SelectionHighlightType;      /* 0x19 */
    s8 mapAlpha;                    /* 0x1A */
    u8 field23_0x1b;                /* 0x1B */
} MapInfo;

/* The computer opponent's plan for one of its units (DuelPlayer.taskList; 0x10 bytes). */
typedef struct UnitTask {
    u16 ownerId;                    /* 0x00: (side << 8) | unit */
    u16 summonOrder;                /* 0x02 */
    u8 mission1;                    /* 0x04: UnitMission; the upper bits are the mission type */
    u8 mission2Main;                /* 0x05: UnitMission */
    u8 field4_0x6;                  /* 0x06 */
    u8 field5_0x7;                  /* 0x07 */
    u16 goalLoc1[2];                /* 0x08 */
    u8 field7_0xc;                  /* 0x0C */
    u8 field8_0xd;                  /* 0x0D */
    u8 field9_0xe;                  /* 0x0E */
    u8 field10_0xf;                 /* 0x0F */
} UnitTask;

/* What the computer opponent does next (a TaLogic_*_GetMinimumTask result; 0x14 bytes). */
typedef struct MinimumTask {
    u16 unitOwnerId;                /* 0x00 */
    u8 taskType;                    /* 0x02: TaskType */
    u8 padding1;                    /* 0x03 */
    u16 loc;                        /* 0x04: (z << 8) | x */
    u8 handPlay[5];                 /* 0x06 */
    u8 padding2;                    /* 0x0B */
    s32 shouldFlipUp;               /* 0x0C: 0 face down, 1 face up, 2 no change */
    u8 atkDefPosition;              /* 0x10: 0 attack, 1 defence, 2 no change */
    u8 padding3[3];
} MinimumTask;

/* One side of the duel: the first 0x6A0 bytes of the duel state hold two of these, [0] and [1].
   Card ids run 0..0x355 (SzDuel_AddDeck rejects others); 999 (0x3E7) marks an empty slot. */
typedef struct DuelPlayer {
    UnitTask taskList[22];         /* 0x000: the computer opponent's plan, one task per unit */
    u16 inputQue[32];              /* 0x160: the pad inputs it queued (Input) */
    u8 inputQueueSize;             /* 0x1A0: bits 0-4: how many tasks have been turned into inputs */
    u8 AiActiveRelated;            /* 0x1A1 */
    u16 inputCount;                /* 0x1A2 */
    u8 pad1A4[0x1D0 - 0x1A4];
    s32 cameraOrbit[4];            /* 0x1D0: the camera around this side's cursor: distance, heading, pitch
                                      (SzDuel_Init: 200, 0x4000 or 0xC000, 0x2000; SzView_IV2V reads it) */
    DuelDeck deck;                 /* 0x1E0 */
    DuelGrave grave;               /* 0x232: the graveyard */
    DuelHand hand;                 /* 0x324 */
    s32 unk330;                    /* 0x330: a handle SzDuel_Act opens per side (-1 = none) */
    s32 loadedData;                /* 0x334: memory SzDuel_Init frees (SzMem_Free) */
    u16 loadedSize;                /* 0x338 */
    u16 lifePoints;                /* 0x33A: 0..9999 (SzDuel_CalcLP) */
    u8 duelistId;                  /* 0x33C: who plays this side: 0..0x1F a computer duelist, 0x20..0x63 a
                                      tutorial script (both run duelistControllers[id]), 100 + n the human on pad n */
    u8 cursorX;                    /* 0x33D: board column 0..6 */
    u8 cursorZ;                    /* 0x33E: board row 0..6 */
    u8 pad33F[0x341 - 0x33F];
    u8 summonPower;                /* 0x341: 0..12 (SzDuel_CalcSummonPower) */
    u8 summonCharge;               /* 0x342 */
    u8 unitsSummoned;              /* 0x343: the summon order the next unit gets (batzpup: NumberOfUnitsSummoned) */
    u8 destinyDraw;                /* 0x344: bits 0-3 destinyDrawTable entry, 4-6 bonus level, 7 used this duel */
    s8 cursorHeight;               /* 0x345: the cursor's height above the board (40 at the start) */
    struct {
        s8 handPhase : 1;          /* SzDuel_InqHandPhase / SetHandPhase */
        s8 b1 : 7;
    } flags346;                    /* 0x346 */
    u8 pad347[0x350 - 0x347];
} DuelPlayer;
typedef DuelPlayer LogicData; /* batzpup's name for it */

typedef struct DuelState {
    DuelPlayer players[2];         /* 0x000: the two sides */
    u8 pad6A0[0x6D0 - 0x6A0];
    struct {
        u8 pad00[0x20];
        u16 ids[3];                /* 0x20: the three cards picked */
    } *pick;                       /* 0x6D0 */
    u8 pad6D4[0x6D8 - 0x6D4];
    u16 *trunkList;                /* 0x6D8: the deck-building screen's trunk list (card ids) */
    u16 *deckList;                 /* 0x6DC: the deck-building screen's deck list (40 card ids) */
    u8 pad6E0[0xC58 - 0x6E0];
    s32 depth;                     /* 0xC58: GS z of the duel windows (SzDuel_SetWindowDefPrioZ) */
    u8 padC5C[0xC86 - 0xC5C];
    u16 wave1;                     /* 0xC86 */
    u16 wave2;                     /* 0xC88 */
    u16 trunkTop;                  /* 0xC8A: first trunk entry on screen */
    u16 trunkCount;                /* 0xC8C: how many entries the trunk list holds */
    u16 deckTop;                   /* 0xC8E: first deck entry on screen */
    u16 deckCount;                 /* 0xC90: how many cards the deck list holds */
    s16 scroll;                    /* 0xC92 */
    s16 scrollTo;                  /* 0xC94 */
    u16 idleTimer;                 /* 0xC96: frames left of a 90-frame wait (reset on input) */
    s16 unkC98;                    /* 0xC98 */
    s16 popupPos[4][2];            /* 0xC9A: x, y of the duel pop-ups: 0 options, 2 hand card, 3 message */
    u16 popupValue[4];             /* 0xCAA: what each pop-up holds (the hand slot, the message's card) */
    s8 popupState[4];              /* 0xCB2: each pop-up's state; 0x18 = closed */
    u8 sort[3];                    /* 0xCB6 */
    u8 sort2[3];                   /* 0xCB9 */
    u8 sort3;                      /* 0xCBC */
    u8 sort4;                      /* 0xCBD */
    u8 pstate[4];                  /* 0xCBE: per-player state bytes, [player] */
    char code[8];                  /* 0xCC2: password digits */
    u8 padCCA[0xD32 - 0xCCA];
    u8 dirty;                      /* 0xD32 */
    u8 padD33[0xD35 - 0xD33];
    u8 prevMode;                   /* 0xD35 */
    u8 sel;                        /* 0xD36 */
    u8 padD37[0xD52 - 0xD37];
    u8 turnFirst;                  /* 0xD52: the side that took the first turn */
    u8 turnCount;                  /* 0xD53: turns played, capped at 255 */
    u8 turnOwner;                  /* 0xD54: the side whose turn it is (0 or 1) */
    u8 padD55[0xD57 - 0xD55];
    u8 step;                       /* 0xD57 */
    u8 padD58[0xD5C - 0xD58];
    u8 player;                     /* 0xD5C */
    u8 mode;                       /* 0xD5D */
    u8 trunkRow;                   /* 0xD5E: cursor row in the trunk list (0..4) */
    u8 deckRow;                    /* 0xD5F: cursor row in the deck list (0..4) */
    u8 digit[3];                   /* 0xD60 */
    u8 hold;                       /* 0xD63 */
    struct {
        s8 dir1 : 2;               /* bits 0-1 */
        s8 dir2 : 2;               /* bits 2-3 */
        s8 b4 : 1;
        s8 b5 : 1;
        s8 b6 : 1;
        s8 b7 : 1;
    } dirs;                        /* 0xD64 */
    struct {
        s8 b0 : 1;
        s8 b1 : 1;
        s8 b2 : 1;
        s8 b3 : 1;
        s8 b4 : 1;
        s8 b5 : 1;
        s8 b6 : 1;
        s8 b7 : 1;
    } f65;                         /* 0xD65: one-bit flags (bit 0 first) */
    struct {
        s8 b0 : 1;
        u8 b1 : 1;                 /* read unsigned (lbu/dsrl32) */
        s8 b2 : 1;
        s8 b3 : 1;
        s8 b4 : 1;
        s8 b5 : 1;
        s8 b6 : 1;
        s8 windowsShown : 1;       /* the duel windows are shown (SzDuel_Get/SetWindowDisp) */
    } f66;                         /* 0xD66 */
    struct {
        s8 windowsDraw : 1;        /* the duel windows are drawn (SzDuel_SetWindowDraw) */
        s8 windowsBusy : 1;        /* the duel windows are busy (SzDuel_SetWindowBusy) */
        s8 b2 : 1;
        s8 b3 : 1;
        s8 b4 : 1;
        s8 b5 : 1;
        s8 b6 : 1;
        s8 b7 : 1;
    } f67;                         /* 0xD67 */
    u8 padD68[0xD70 - 0xD68];
} DuelState;

/* The duel state (also the work area of the duel-side menus: deck building, trade, custom duel, map edit).
   Code written against raw offsets reads it as bytes (.b), the rest by field (.s). */
typedef union DuelStateBytes {
    u8 b[0xD70];
    DuelState s;
} DuelStateBytes;

extern DuelStateBytes duelState; /* original: gSzDuel_dl */

/* The duel state and side `i`'s record as pointers computed from the byte view. The original code forms the
   address this way (base, then the field offset in the load or store); writing duelState.s.players[i].x
   instead folds the offset into the address and changes the bytes. */
#define DUEL_STATE ((DuelState *)duelState.b)
#define DUEL_PLAYER(i) ((DuelPlayer *)(duelState.b + (i) * 0x350))

/* duelState.s.turnOwner as a symbol of its own: SzDuel_Act only matches reading it this way. */
extern u8 D_003181E4;


typedef __int128 Q128_0020F290;
extern u8 D_0032A5E0[];
extern Q128_0020F290 D_0032A600;

extern u8 D_003506C8[];





extern u8 GSI[];
extern u8 screenState[]; /* original: gRhBase_dl */
extern s32 frameBufferIndex;


extern char D_002B90DA[];
extern char D_002B9102[];
extern char D_002B9112[];
extern char D_002B9127[];
extern char D_002B9135[];

extern s32 gameState; /* original: gSzGame_gl */

extern s32 D_00317254;

extern s32 D_00317B68;

extern s32 D_00317B6C;


extern s32 effectTarget;

extern u8 padStates[]; /* original: gSzPad_pl */

extern s32 D_0032618C;
extern s32 currentTimingModeValue;

extern s32 screenCenterX;
extern s32 ScreenCenterY;


extern s32 isCountVblank;
extern s32 frd;




extern s32 effectSource;


extern u8 D_002D0655[];

extern volatile s32 gSh_FaceMode;

extern u8 D_0029D1F0[];

extern s16 clutState; /* original: gSzText_tl */
extern u16 D_00322992;
extern s16 D_00322994;

extern u8 viewClipPlanes[]; /* original: gEx3d_aPlane */

extern u8 mainDrawList[]; /* original: gMyOT */

extern s32 viewStackIndex; /* original: gRhView_nStackIndex */

extern s32 zSortList; /* original: gRhZSort_zsl */
extern s32 D_0032F784;
extern s32 D_0032F788;
extern s32 D_0032F78C;

extern char D_0030F8E9;



extern u8 D_0029D586[];


extern u8 cardControls[]; /* original: gSzDuel_aCardControl */
extern u16 gSzDuel_CardDefaultCamDist[];





extern s64 alphaBlendModes[]; /* original: gExPrim_aqwAlpha */


extern s8 campaignMoveDone; /* original: Move_END_flg */
extern s32 isWithAudio;
extern u8 audioDec[];



extern u8 cardRequests[]; /* original: gSzDuel_aCardRequest */


extern s32 g_SDBuffer;


extern s32 views[]; /* original: gSzView_hView */








typedef void (*Callback_00286910)(void);











extern u8 voBuf[];
extern volatile s32 D_0035060C;


extern u16 AlternateCardIds[];
extern MapInfo boardSquares[7][7]; /* [row][column]; original: gSzDuel_aaMapInfo */







extern u8 equipMatchTable[]; /* original: EnchMatch */








extern char D_0030F354[];
extern s32 D_003503B8;
extern s32 controller_val;
extern u8 videoDec[];
extern u8 infile[];
extern s32 readBuf;

extern u16 AnmPat_Bakura_used_for_EnchantScore[];


extern u16 gSzData_ConstDeck[51][41];

extern u8 D_00299F90[];


extern u8 D_002B90B0[];



extern char D_002BF002[];


extern char D_002BF040;


extern u32 fusionTable[]; /* original: FusionDat */







extern u64 ditherMatrices[]; /* original: g_aqwExDitherMatrix */




extern s32 eventLoadedScene; /* original: gSzEvent_nSave */

extern u8 DeckBuildingSide;

extern s8 campaignState; /* original: save_data */
extern s16 SelectedBattleArena;














extern char D_002B90C0[];
extern s32 s_iUsingNow;
typedef struct { s32 src; s32 offset; s32 size; s32 position; s32 left; } cdstream_t;
extern cdstream_t D_0030FFA0;




extern s32 vu1DrawMethod; /* original: gRhVu1Mac_State */
extern s32 D_00325E2C;



extern s32 voBufData;
extern s32 voBufTag;
extern s32 viBufTag;
extern s32 mpegWork;
extern s32 defStack;
extern s32 audioBuff;
extern s32 viBufData;
extern s32 videoDecStack;
extern s32 timeStamp;
extern s32 isWithInter;
extern u8 D_003503C0[];



extern f32 gRhMath_adwSinTable[];


extern Unit duelUnits[3][11]; /* [side][unit], side 2 the spare row; original: gSzDuel_aaVarInfo */









extern s8 practiceDuelFlag; /* original: Rensyu_flg */
extern s8 practiceDuelEnd; /* original: Rensyu_END */




extern u8 FrameSpeed;
extern s32 D_003180E4;
extern s32 GSUserAddress;
extern s8 AutoBlur;



extern s8 HandCursorState; /* duelState.s.popupState[2] as a symbol of its own (the close functions read it so) */
extern s8 MsgPopUpID; /* duelState.s.popupState[3] */
extern s32 D_0031AB90;
extern s8 MenuVisualToDisplay; /* duelState.s.popupState[0] */

extern s32 modelDrawCache; /* original: gSzModel_pfhCache */




extern s8 blackOutForBattle;

extern u8 MonsterBlackOutEffect;
extern s32 Msg_DefPrioZ;
extern s32 VifPacketArea;


extern s8 blackOutForDuel;
extern s32 RhGeom_Related;

extern s8 D_00299EDA;

extern s16 winCount;
extern char D_0030F3AE[];


extern s32 gSzView_pCamera;


extern u8 ScreenFadeAmount;


extern char D_002BF00B;

extern s32 movieFileNames[]; /* original: apchMovie */
extern u8 D_002BE809[];
extern u8 D_002BE80F[];





extern char D_002BEF67[];















extern char D_002BEF98[];
extern char D_002BEF6F[];
extern char D_002BEF73[];
extern char D_002BE944[];
extern u8 D_003181C6;






extern u8 D_00325F00[];
extern Q128_0020F290 D_00325EF0;
extern u64 D_00326180;











extern f32 duelStageParams; /* original: gSzDuel_StageParam */
extern f32 D_0029100C;
extern f32 D_00291020;
extern f32 D_002910B0;
extern f32 D_002910B8;




extern s32 (*sortCompareFuncs[])(s32, s32); /* original: gSzDuel_pfnSort */

extern u8 gSzDuel_NameIndex0[];
extern u8 gSzDuel_NameIndex1[];

extern u8 D_002909B8[];
extern u8 WhoGoesFirst;





extern f32 D_00298BA4;


extern u8 InvertView[];


extern u8 D_0032A784[];


extern f32 vu1LightDirs; /* original: gRhVu1Mac_matDir */
extern f32 D_00325D54;
extern f32 D_00325D58;
extern f32 D_00325D60;
extern f32 D_00325D64;
extern f32 D_00325D68;
extern f32 D_00325D70;
extern f32 D_00325D74;
extern f32 D_00325D78;
extern f32 vu1LightColors; /* original: gRhVu1Mac_matCol */
extern f32 D_00325D94;
extern f32 D_00325D98;
extern f32 D_00325DA0;
extern f32 D_00325DA4;
extern f32 D_00325DA8;
extern f32 D_00325DB0;
extern f32 D_00325DB4;
extern f32 D_00325DB8;

extern s16 campaignSystemIcons[]; /* original: camp_sys_icon */
extern s16 D_002982F8[];
extern s16 campaignButtonIcons[]; /* original: camp_sys_icon_botan */
extern s16 camp_sys_icon_button[];
extern s8 D_0030F102[];
extern s8 D_0030F107[];
extern s8 D_0030F10C[];
extern s8 D_0030F113[];
extern s8 D_0030F118[];




extern char s_szReadPCMListAtFirst[];



extern s32 globals;

extern s32 sceDmaDebugMode;

extern s8 D_002BCA98;

extern s32 D_0028DC90;

extern s32 D_00310E98;

extern s32 D_0028D8F0;

extern s32 lconv;




extern s32 D_0028CAA4;

extern u8 D_002BCB08[];

extern u8 D_002BCB38[];


extern u8 D_002BCB50[];


extern u8 D_002BCB88[];





















extern s32 mcRunCmdNo;
extern s32 D_0028F794;
extern s32 D_00315C40;
extern s32 D_00317200;

extern s32 _cmd_init_check;
extern s32 D_00310E94;

extern s32 _fs_init;
extern s32 D_00313BA8;


extern s32 _bind_check;
extern s32 D_00314028;


extern s32 D_0028D108;








extern s32 *D_00315C68;
extern s32 *D_00315C6C;
extern s32 *D_00315C70;



extern s32 D_0028CDF0;
extern s32 func_00184080;


extern s32 D_00315500;

extern s32 D_002BC900;
extern s32 D_002BC920;

extern s32 _sceSifInitCheck;

extern s8 D_002BD0A0;
extern s32 D_00315CC0;



extern s32 ncmd_semid;
extern s32 D_0028DD40;
extern s32 D_0028EE90;
extern s32 scmd_semid;
extern s32 D_0028EEC0;
extern s32 D_0028F708;


extern s32 D_002BC8A8;
extern s32 D_002BC8D0;

extern PadSlot_00192A88 D_003159D0[2][4];
extern s32 D_00315BC0;

extern s32 D_00310FC0;
extern s32 D_0028DA50;



typedef union { f32 value; u32 word; } fshape;

/* libgcc fp-bit.c (sdk/lgcc): Cygnus built it for the r5900 with US_SOFTWARE_GOFAST and
   FLOAT_BIT_ORDER_MISMATCH, once for float (NO_NANS) and once for double. */
typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;
typedef struct { fp_class_type class; u32 sign; s32 normal_exp; u32 fraction; } fp_number_f;
typedef struct { fp_class_type class; u32 sign; s32 normal_exp; u64 fraction; } fp_number_d;
typedef union {
    f32 value;
    u32 value_raw;
#if defined(__GNUC__) && !defined(__MWERKS__) && !defined(M2CTX) && !defined(PERMUTER)
    struct {
        u32 fraction : 23 __attribute__((packed));
        u32 exp : 8 __attribute__((packed));
        u32 sign : 1 __attribute__((packed));
    } bits;
#endif
} fp_union_f;
typedef union {
    double value;
    u64 value_raw;
#if defined(__GNUC__) && !defined(__MWERKS__) && !defined(M2CTX) && !defined(PERMUTER)
    struct {
        u64 fraction : 52 __attribute__((packed));
        u32 exp : 11 __attribute__((packed));
        u32 sign : 1 __attribute__((packed));
    } bits;
#endif
} fp_union_d;
extern fp_number_d D_002BDF30; /* __thenan_df */
#if defined(__GNUC__) && !defined(__MWERKS__) && !defined(M2CTX) && !defined(PERMUTER)
/* fp-bit's INLINE predicates: a test of their int result compiles to xori/beqz */
static __inline__ s32 fp_isnan_f(fp_number_f *x) { return x->class == CLASS_SNAN || x->class == CLASS_QNAN; }
static __inline__ s32 fp_isinf_f(fp_number_f *x) { return x->class == CLASS_INFINITY; }
static __inline__ s32 fp_iszero_f(fp_number_f *x) { return x->class == CLASS_ZERO; }
static __inline__ s32 fp_isnan_d(fp_number_d *x) { return x->class == CLASS_SNAN || x->class == CLASS_QNAN; }
static __inline__ s32 fp_isinf_d(fp_number_d *x) { return x->class == CLASS_INFINITY; }
static __inline__ s32 fp_iszero_d(fp_number_d *x) { return x->class == CLASS_ZERO; }
#endif


extern s32 D_00310980;


extern s32 D_0028CAA8;
extern s32 D_0028CAAC;

extern s32 D_00310920;
extern s32 D_002BC1E8;
extern s32 stm_status;
extern s32 dum_mode;
extern s32 SCE_CD_debug;
extern s32 D_002BCE58;
extern s32 D_002BCE88;

extern s32 D_002BCE70;

extern s32 D_00313E00;
extern s32 D_00314000;
extern s32 D_002BC9F8;
extern s32 isInit;


extern char D_002BCA18[];

extern s32 D_001842C0;
extern s32 D_0028CDF8;

extern s32 dch;

extern s32 PadStateStr;
extern u8 D_002BD000;
extern s32 ReqStateStr;

extern s32 D_0028F300;

extern s32 D_0028C24C;
extern s32 *D_0028CAC4;



typedef struct { void (*fn)(s32); s32 arg; } hcall_t;
extern s32 *D_0028D11C;

extern void (*_putchar)(s32);

extern s32 D_00316200;


typedef struct { u8 a; u8 b; } ringent_t;
typedef struct { s32 x0; u32 count; ringent_t e[0x200]; } ring_t;
extern s32 topId;
extern s32 D_00310510;
extern s32 D_00310518;


extern s32 *D_0028CAB0;
extern s32 D_0028DCFC;
extern s32 D_003156C4;
extern s32 D_003156C8;
extern s32 D_0028DCE4;

extern s32 D_0028C254;

extern s32 D_003512F8;

typedef struct { u8 pad0[0xC]; s16 _flags; u8 pad1[0x58 - 0xE]; } nl_FILE;
typedef struct nl_glue { struct nl_glue *_next; s32 _niobs; nl_FILE *_iobs; } nl_glue;
typedef struct { u8 pad0[0x58]; } nl_mFILE;
typedef struct nl_mglue { struct nl_mglue *_next; s32 _niobs; nl_mFILE *_iobs; } nl_mglue;

extern s8 D_002BD0C1[];


typedef union { double value; struct { u32 lsw; u32 msw; } parts; } nl_dshape;

extern s32 D_002BC828;

extern s32 D_002BC9D0;

extern f32 D_002BE5D0[]; /* fdlibm kf_tan.c T[13] */

extern s32 D_002BC7C0;
extern s32 D_002BC7E8;

extern s32 D_002BE4C4[];  /* fdlibm ef_rem_pio2.c npio2_hw[] - 1 */
extern s32 D_002BE1B0[];  /* two_over_pi[] */

extern s32 D_00315CA0;
extern s32 D_00315CF0;


extern f32 D_002BE120[]; /* fdlibm ef_fmod.c Zero[] = { 0.0, -0.0 } */

extern s32 D_00316140;

extern f32 D_002BE608[]; /* fdlibm sf_atan.c atanhi[4] */
extern f32 D_002BE618[]; /* atanlo[4] */
extern f32 D_002BE628[]; /* aT[11] */

extern s32 cb_thid;
extern s32 cb_semid;
extern volatile s32 c_cb_sem;
extern s32 sceCdCbfunc_num;
extern volatile s32 D_0028DD18;
extern char D_002BCBE8[];
extern void (*D_003156C0)(s32);
extern s32 D_003156CC;




extern f32 D_002BE128[]; /* fdlibm ef_pow.c bp[2] = { 1.0, 1.5 } */
extern f32 D_002BE130[]; /* dp_h[2] */
extern f32 D_002BE138[]; /* dp_l[2] */
extern f32 D_002BE1AC;   /* huge * huge, folded (the compiler kept it in rodata) */

extern s32 D_002BE570[]; /* fdlibm kf_rem_pio2.c init_jk[] = { 4, 7, 9 } */
extern f32 D_002BE580[]; /* PIo2[11] */


typedef struct i2b_Bigint { struct i2b_Bigint *next; s32 k, maxwds, sign, wds; u32 x[1]; } i2b_Bigint;


extern hcall_t D_00313C00;

extern s32 D_0028FF04;
extern s32 D_0028FF00;
extern s32 D_0028D114;

extern s32 D_002BCA78;

typedef struct mcmp_Bigint { struct mcmp_Bigint *next; s32 k, maxwds, sign, wds; u32 x[1]; } mcmp_Bigint;

extern double D_002BD288[]; /* mprec tens[] */

typedef struct vf_reent { u8 pad[0x38]; s32 __sdidinit; } vf_reent;
typedef struct vf_FILE { u8 pad[0x54]; vf_reent *_data; } vf_FILE;

typedef struct sread_FILE { u8 pad0[0xC]; s16 _flags; s16 _file; u8 pad1[0x40]; s32 _offset; s32 *_data; } sread_FILE;

typedef struct sseek_FILE { u8 pad0[0xC]; s16 _flags; s16 _file; u8 pad1[0x40]; s32 _offset; s32 *_data; } sseek_FILE;

typedef struct sprr_FILE { u8 *_p; s32 _r; s32 _w; s16 _flags; s16 _file; u8 *_bf_base; s32 _bf_size; s32 _lbfsize; void *_cookie; void *_read; void *_write; void *_seek; void *_close; u8 *_ub_base; s32 _ub_size; u8 *_up; s32 _ur; u8 _ubuf[3]; u8 _nbuf[1]; u8 *_lb_base; s32 _lb_size; s32 _blksize; s32 _offset; void *_data; } sprr_FILE;

typedef struct spr_FILE { u8 *_p; s32 _r; s32 _w; s16 _flags; s16 _file; u8 *_bf_base; s32 _bf_size; s32 _lbfsize; void *_cookie; void *_read; void *_write; void *_seek; void *_close; u8 *_ub_base; s32 _ub_size; u8 *_up; s32 _ur; u8 _ubuf[3]; u8 _nbuf[1]; u8 *_lb_base; s32 _lb_size; s32 _blksize; s32 _offset; void *_data; } spr_FILE;

typedef struct ssc_FILE { u8 *_p; s32 _r; s32 _w; s16 _flags; s16 _file; u8 *_bf_base; s32 _bf_size; s32 _lbfsize; void *_cookie; void *_read; void *_write; void *_seek; void *_close; u8 *_ub_base; s32 _ub_size; u8 *_up; s32 _ur; u8 _ubuf[3]; u8 _nbuf[1]; u8 *_lb_base; s32 _lb_size; s32 _blksize; s32 _offset; void *_data; } ssc_FILE;

extern char D_002BD270[]; /* "C" */
extern char D_002BD260[]; /* "" */


extern char ***D_0028FF08; /* p_environ */

typedef struct cal_chunk { u32 prev_size; u32 size; } cal_chunk;

extern s32 D_00312840;
extern s32 D_00313E08;
extern s32 D_00315D04;

typedef union { double d; u32 i[2]; } ratio_du;

typedef union { double d; u32 i[2]; } ulp_du;

extern s32 isclr;

typedef struct fr_FILE { u8 *_p; s32 _r; } fr_FILE;



extern s32 D_0028DB80;
extern s32 D_0028DBC0;
extern s32 D_002BCAA8;


typedef struct p5_reent { u8 pad0[0x48]; i2b_Bigint *_p5s; } p5_reent;
extern s32 D_002BD274[];


typedef union b2d_du { double d; u32 i[2]; } b2d_du;

extern s32 D_002BC7A0;

typedef union cvt_du { double d; u32 i[2]; } cvt_du;





extern s32 D_002BCCD0;

extern s32 D_002BCCC0;


extern s32 D_002BC940;


extern s32 D_002BCAC0;
extern s32 D_002BCAE8;

extern s32 D_002BC808;

extern s8 D_002BC2D8;



extern s32 D_0028D118;


extern s32 _bind;
extern s32 D_00313C40;
extern s32 _rdata;
extern s32 __fih_data;

extern s32 D_00313500;
extern s32 D_00313B80;




extern s32 D_0028CA08;
extern char D_00310D40[];

extern __int128 D_0028D9F0[];


extern s32 ttyinit;
typedef struct { void *func; void *data; } SifCmdHandlerData;
extern SifCmdHandlerData *D_00310EA4;
extern SifCmdHandlerData *D_00310EAC;

extern const char D_002BD0C0[];
typedef struct su_reent { s32 _errno; } su_reent;

typedef struct sl_reent { s32 _errno; } sl_reent;

extern u32 D_0028DA78[];

extern s32 isWarning;
extern char D_002BCEE0[];

extern char D_002BC670[];

extern s32 D_00317240;
extern char **D_0028F79C;

extern char D_002B9141[];
extern char D_002B9168[];
extern char gSdfs_sa[];

extern u8 abTmpBuf;

extern u8 cardTestState[]; /* original: gSzDuel_dt */

extern s32 isFrameEnd;

extern s32 matrixStack; /* original: gRhGeom_rgl */


extern s32 vecNormal;

extern f32 D_01E01A80_b505;
extern f32 D_01E01A88_b505;

extern f32 D_01E01E00_b350;
extern f32 D_01E01E08_b350;

extern f32 D_01E03D00_b267;
extern f32 D_01E03D08_b267;
extern f32 D_01E02400_b850;
extern f32 D_01E02408_b850;

extern f32 D_01E03C00_b378;
extern f32 D_01E03C08_b378;
extern f32 D_01E03780_b195;
extern f32 D_01E03788_b195;
extern f32 D_01E03580_b266;
extern f32 D_01E03588_b266;
extern f32 D_01E02780_b294;
extern f32 D_01E02788_b294;

extern f32 D_01E02C80_b484;
extern f32 D_01E02C88_b484;

extern f32 D_01E02D00_b477;
extern f32 D_01E02D08_b477;
extern f32 D_01E03180_b397;
extern f32 D_01E03188_b397;

extern f32 D_01E02E00_b284;
extern f32 D_01E02E08_b284;

extern f32 D_01E03C00_b192;
extern f32 D_01E03C08_b192;
extern f32 D_01E03000_b566;
extern f32 D_01E03008_b566;
extern f32 D_01E03380_b513;
extern f32 D_01E03388_b513;
extern f32 D_01E02E00_b552;
extern f32 D_01E02E08_b552;
extern f32 D_01E03180_b297;
extern f32 D_01E03188_b297;

extern f32 D_01E03B80_b052;
extern f32 D_01E03B88_b052;

extern f32 D_01E03D00_b567;
extern f32 D_01E03D08_b567;
extern f32 D_01E04000_b555;
extern f32 D_01E04008_b555;

extern f32 D_01E03E80_b018;
extern f32 D_01E03E88_b018;
extern f32 D_01E03E80_b019;
extern f32 D_01E03E88_b019;
extern f32 D_01E04000_b080;
extern f32 D_01E04008_b080;
extern f32 D_01E04480_b734;
extern f32 D_01E04488_b734;
extern f32 D_01E04F00_b430;
extern f32 D_01E04F08_b430;

extern f32 D_01E03F80_b393;
extern f32 D_01E03F88_b393;

extern f32 D_01E04300_b046;
extern f32 D_01E04308_b046;

extern f32 D_01E05100_b225;
extern f32 D_01E05108_b225;

extern f32 D_01E04680_b527;
extern f32 D_01E04688_b527;
extern f32 D_01E04580_b257;
extern f32 D_01E04588_b257;
extern f32 D_01E05780_b582;
extern f32 D_01E05788_b582;
extern f32 D_01E04800_b476;
extern f32 D_01E04808_b476;

extern f32 D_01E05B80_b258;
extern f32 D_01E05B88_b258;
extern f32 D_01E05480_b573;
extern f32 D_01E05488_b573;
extern f32 D_01E05C80_b218;
extern f32 D_01E05C88_b218;

extern f32 D_01E04B00_b207;
extern f32 D_01E04B08_b207;

extern f32 D_01E05600_b718;
extern f32 D_01E05608_b718;

extern f32 D_01E05600_b383;
extern f32 D_01E05608_b383;
extern f32 D_01E05600_b148;
extern f32 D_01E05608_b148;
extern f32 D_01E06100_b709;
extern f32 D_01E06108_b709;
extern f32 D_01E05A00_b417;
extern f32 D_01E05A08_b417;
extern f32 D_01E06A00_b357;
extern f32 D_01E06A08_b357;

extern u8 D_912000[];
extern char D_002B8F00[], D_002B8F05[], D_002B8F07[], D_002B8F0D[], D_002B8F13[], D_002B8F18[];
extern char D_002B8F1F[], D_002B8F27[], D_002B8F2C[], D_002B8F32[];

extern s32 D_002BC768;

s32 func_00224E40(s32);
s32 func_0022F3C0(s32);
s32 func_002311D0(s32);
s32 func_002347D0(s32);
s32 func_002354A0(s32);
s32 func_00236C50(s32);
s32 Taku_Camp_BUN_DARE_b(s32, s8);
s32 Taku_Camp_BOTAN_MATI_b(s32);

extern s32 D_002BC858;

typedef struct { f32 x, y, z, w; } Vec4_00109830;

extern s32 D_00315640[];
extern s32 D_00315680;
extern s32 D_0028DCA4;
extern s32 D_0028DCA8;
extern s32 D_0028DCAC;
extern s32 D_0028DCB0;
extern s32 D_0028DCB4;
extern s32 D_0028DCB8;

extern char gSzDuel_aicolMsg[];


#endif
