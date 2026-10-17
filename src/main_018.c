#include "common.h"

/* Gives side 0 a fixed starting hand for event duel `arg0`. */
void func_00178320(s32 arg0) {
    switch ((u16)arg0) {
    case 0x25:
    case 0x3B:
    case 0xD0:
        SzDuel_InitHand(0);
        SzDuel_AddHand(0, 0x141);
        SzDuel_AddHand(0, 0x7);
        SzDuel_AddHand(0, 0x9C);
        SzDuel_AddHand(0, 0xF9);
        SzDuel_AddHand(0, 0x126);
        break;
    case 0x48:
        SzDuel_InitHand(0);
        SzDuel_AddHand(0, 0xF);
        SzDuel_AddHand(0, 0x5);
        SzDuel_AddHand(0, 0x9C);
        SzDuel_AddHand(0, 0xF9);
        SzDuel_AddHand(0, 0x126);
        break;
    case 0x5D:
    case 0xAC:
        SzDuel_InitHand(0);
        SzDuel_AddHand(0, 0x141);
        SzDuel_AddHand(0, 0x7);
        SzDuel_AddHand(0, 0x9C);
        SzDuel_AddHand(0, 0xF9);
        SzDuel_AddHand(0, 0x2FE);
        break;
    case 0x71:
        SzDuel_InitHand(0);
        SzDuel_AddHand(0, 0x141);
        SzDuel_AddHand(0, 0x7);
        SzDuel_AddHand(0, 0x9C);
        SzDuel_AddHand(0, 0xF9);
        SzDuel_AddHand(0, 0x2F0);
        break;
    case 0x87:
        SzDuel_InitHand(0);
        SzDuel_AddHand(0, 0x141);
        SzDuel_AddHand(0, 0x7);
        SzDuel_AddHand(0, 0x9C);
        SzDuel_AddHand(0, 0x2FE);
        SzDuel_AddHand(0, 0x2FE);
        break;
    case 0x98:
        SzDuel_InitHand(0);
        SzDuel_AddHand(0, 0xF);
        SzDuel_AddHand(0, 0x5);
        SzDuel_AddHand(0, 0x126);
        SzDuel_AddHand(0, 0x2FE);
        SzDuel_AddHand(0, 0x2FE);
        break;
    }
    SzDuel_PackHand(0);
}

