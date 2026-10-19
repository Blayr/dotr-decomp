/* Battle events (SzEvent_*). */

#include "common.h"

/* Starts event scene `scene`: which models draw, the light. */
void SzEvent_Init(s32 scene) {
    s32 i;

    SzView_SetStraightLight(0, 9, 1);
    i = 0;
    do {
        SzModel_SetDrawFlag(i, 0);
        i += 1;
    } while (i < 0x54);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x22, 1);
        i += 1;
    } while (i < 0x28);
    i = 0;
    do {
        SzModel_SetDrawFlag(i + 0x1E, 1);
        i += 1;
    } while (i < 2);
    if (scene != eventLoadedScene) {
        eventLoadedScene = scene;
    }
}

/* Draws the event scene. */
void SzEvent_Draw(void) {
    RhBase_SetVifPacketArea(SzEvent_Draw_Pipe(RhBase_GetVifPacketArea()));
}

typedef struct Entry_001E78C0 {
    s16 first;
    s16 second;
    f32 x;
    f32 z;
} Entry_001E78C0;

typedef union Quad_001E78C0 {
    __int128 q;
    f32 f[4];
} Quad_001E78C0;

/* Draws the event scene's models. */
s32 SzEvent_Draw_Pipe(s32 packet) {
    extern Quad_001E78C0 D_00292470;
    extern Entry_001E78C0 aCastleData[];
    Quad_001E78C0 position;
    s32 i;
    s32 firstId;
    s32 secondId;
    s32 id;

    if (SzModel_GetDrawFlag(0x22) != 0) {
        if (eventLoadedScene == 2) {
            for (i = 0; aCastleData[i].second >= 0; i++) {
                secondId = aCastleData[i].second + 0x22;
                firstId = aCastleData[i].first + 0x22;
                position = D_00292470;
                position.f[0] = aCastleData[i].x;
                position.f[2] = aCastleData[i].z;
                if (aCastleData[i].first >= 0 && SzModel_IsModelDisp(firstId) != 0) {
                    packet = SzModel_DrawWithOutCalc_Pipe(packet, firstId, (s32) &position, 0, 0, 0, 0);
                }
                if (aCastleData[i].second >= 0 && SzModel_IsModelDisp(secondId) != 0) {
                    packet = SzModel_DrawWithOutCalc_Pipe(packet, secondId, (s32) &position, 0, 0, 0, 0);
                }
            }
        } else {
            for (i = 0; i < 0x28; i++) {
                id = i + 0x22;
                if (SzModel_IsModelDisp(id) != 0) {
                    packet = SzModel_DrawWithOutCalc_Pipe(packet, id, 0, 0, 0, 0, 0);
                }
            }
        }
    }
    return packet;
}

/* Ends the event scene (nothing to do). */
void SzEvent_Term(void) {

}
