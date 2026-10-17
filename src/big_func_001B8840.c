#include "common.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


/* Clamps at 0. */
static inline s32 nonnegative_001B8840(s32 value) {
    if (value > 0) {
        return value;
    }
    return 0;
}

/* Runs one frame of deck building: the trunk and deck lists, moving cards, sorting, passwords, reincarnation, the
   3D viewer and leaving. */
void SzDuel_ActBuildDeck(void) {
    DuelState *d = &duelState.s;
    s32 player;
    s32 dx;
    s32 dy;
    s32 slot;
    s32 alt;
    u16 card;
    s32 held;
    s32 info;
    s32 oldRow;
    s32 index;
    s32 info2;
    s32 oldRow2;
    s32 stick;
    s32 stick2;
    s32 code;
    u16 oldOffset2;
    s32 limit2;
    s32 offset2;
    s32 n;
    u16 oldOffset;
    s32 limit;
    s32 offset;
    s32 digit;
    s32 owned;
    s32 usable;
    s32 owned2;
    s32 owned3;
    s32 number;
    s32 k;
    s32 next;
    s32 pickCard;
    s32 card2;
    s32 old0;
    s32 oldSort;
    s32 oldSort3;
    s32 oldKey;
    s32 oldKey2;
    s32 oldSort4;
    s32 oldSel;
    s32 old1;
    s32 old2;
    s32 delta;
    u8 ch;
    u16 *ids;

    player = d->player;
    slot = SzData_GetCurrentDeck((s32) player);
    alt = ((d->mode == 2) || (d->mode == 5)) ? 1 : 0;
    dx = 0;
    dy = 0;
    if ((SzFile_InqRequestEx() == 0) && (d->dirty != 0)) {
        SzText_LoadMerge(player + 5, 1);
        d->dirty = 0U;
    }
    {
        DuelState *p = &duelState.s;
        if (p->hold != 0) {
            p->dirs.dir1 = 1;
        }
        p->wave1 = MIN(MAX(p->wave1 + (p->dirs.dir1 << 9), 0), 0x8000);
        if ((p->wave1 == 0) || ((s32) p->wave1 >= 0x8000)) {
            p->dirs.dir1 = (s8) -p->dirs.dir1;
        }
    }
    {
        DuelState *p = &duelState.s;
        s32 step = p->dirs.dir2 << 0xB;
        p->wave2 = MIN(MAX(p->wave2 + step, 0), 0x8000);
        if ((p->wave2 == 0) || ((s32) p->wave2 >= 0x8000)) {
            p->dirs.dir2 = (s8) -p->dirs.dir2;
        }
    }
    if (d->scroll != d->scrollTo) {
        d->scroll += MIN(MAX(d->scrollTo - d->scroll, -0x2D), 0x2D);
        return;
    }
    if (SzPad_Check(0, 1, 0xFFFF) != 0) {
        d->idle = 0x5A;
    } else if (d->idle != 0) {
        d->idle--;
    }
    switch (d->mode) {
    case 0:
        if (SzPad_Check(0, 0, 0x20) != 0) {
            d->mode = 1U;
            d->scrollTo = 0x140;
            SzSound_PlaySE(0, 0x11);
        } else if (SzPad_Check(0, 2, 0xF00C) != 0) {
            old0 = d->digit[0];
            old1 = d->digit[1];
            old2 = d->digit[2];
            delta = 0;
            if (SzPad_Check(0, 2, 0xC) != 0) {
                if (SzPad_Check(0, 2, 4) != 0) {
                    delta = -0xA;
                } else {
                    delta = 0xA;
                }
            } else if (SzPad_Check(0, 2, 0x5000) != 0) {
                if (SzPad_Check(0, 2, 0x1000) != 0) {
                    if (d->digit[2] > 0) {
                        d->digit[2]--;
                    } else {
                        delta = -1;
                    }
                } else if (d->digit[2] < 9) {
                    d->digit[2]++;
                } else {
                    delta = 1;
                }
            }
            if (delta != 0) {
                d->digit[0] = MIN(MAX(d->digit[0] + delta, 0), 0x4C);
            }
            if (SzPad_Check(0, 2, 0xA000) != 0) {
                if (SzPad_Check(0, 2, 0x8000) != 0) {
                    d->digit[1] = (d->digit[1] + 9) % 10;
                } else {
                    d->digit[1] = (d->digit[1] + 0xB) % 10;
                }
            }
            if (d->digit[1] != old1 || d->digit[2] != old2 || d->digit[0] != old0) {
                SzSound_PlaySE(0, 3);
            }
        } else if (SzPad_Check(0, 2, 3) != 0) {
            oldSort = d->sort3;
            if (SzPad_Check(0, 2, 1) != 0) {
                d->sort3 = (d->sort3 + 3) % 4;
            } else {
                d->sort3 = (d->sort3 + 5) % 4;
            }
            if (d->sort3 != oldSort) {
                SzSound_PlaySE(0, 0x13);
            }
        } else if (SzPad_Check(0, 0, 0xD0) != 0) {
            number = d->digit[1] + ((d->digit[0] + d->digit[2]) * 0xA);
            owned = 0;
            if (number == 0x29F) {
                number = 0x3E7;
            }
            if (number < 0x2AB) {
                if (SzData_GetBagCount((s32) player, number, -1) > 0) {
                    owned = 1;
                }
                if (SzData_GetLookFlag((s32) player, number) != 0) {
                    owned = 1;
                }
            }
            if (owned != 0) {
                SzDuel_Init3DView(number);
                SzGame_Push(7, 2);
                SzSound_PlaySE(0, 4);
            } else {
                SzSound_PlaySE(0, 6);
            }
        }
        break;
    case 1:
        if (SzPad_Check(0, 0, 0x800) != 0) {
            d->mode = 0U;
            d->scrollTo = 0x280;
            SzSound_PlaySE(0, 0x10);
        } else if (SzPad_Check(0, 2, 0x5000) != 0) {
            oldSort3 = d->sort3;
            if (SzPad_Check(0, 2, 0x1000) != 0) {
                d->sort3 = (d->sort3 + 3) % 4;
            } else {
                d->sort3 = (d->sort3 + 5) % 4;
            }
            if (d->sort3 != oldSort3) {
                SzSound_PlaySE(0, 0x13);
            }
            SzPad_ResetCounter(0, 0xA000);
        } else if (SzPad_Check(0, 2, 0x2000) != 0) {
            d->mode = 2U;
            SzSound_PlaySE(0, 0x12);
        } else if (SzPad_Check(0, 2, 0x20) != 0) {
            d->mode = 2U;
            SzSound_PlaySE(0, 0x11);
        }
        break;
    case 2:
    case 3:
        card = d->list[d->offset + d->row];
        info = SzData_CheckDeck((s32) player, slot, (s32) card);
        held = (SzPad_Check(0, 1, 0x100) != 0) ? 1 : 0;
        oldRow = d->row;
        if (SzPad_Check(0, 0, 0x200) != 0) {
            usable = SzData_GetBagCount((s32) player, (s32) card, 3);
            if (SzFile_InqRequestEx() != 0) {
                usable = 0;
            }
            if (Taku_Get_Duel5_flg() < 5) {
                usable = 0;
            }
            if ((lSzDuel_IsDeckReady((s32) player, 0) == 0) && (lSzDuel_IsDeckReady((s32) player, 1) == 0) && (lSzDuel_IsDeckReady((s32) player, 2) == 0)) {
                usable = 0;
            }
            if (usable > 0) {
                d->sel = 0U;
                d->prevMode = (u8) d->mode;
                d->mode = 7U;
                SzSound_PlaySE(0, 0x10);
            } else {
                SzSound_PlaySE(0, 6);
            }
        } else if (SzPad_Check(0, 0, 0x400) != 0) {
            n = 0;
            do {
                d->code[n] = 0x30;
                n += 1;
            } while (n < 8);
            d->sel = 0U;
            d->prevMode = (u8) d->mode;
            d->mode = 9U;
            SzSound_PlaySE(0, 0x10);
        } else {
            if (SzPad_Check(0, 2, 0xC) != 0) {
                if (SzPad_Check(0, 2, 4) != 0) {
                    dx = -5;
                } else {
                    dx = 5;
                }
            } else if (SzPad_Check(0, 2, 0x5000) != 0) {
                if (SzPad_Check(0, 2, 0x1000) != 0) {
                    if (d->row > 0) {
                        d->row--;
                    } else {
                        dx = -1;
                    }
                } else if (d->row < 4) {
                    d->row++;
                } else {
                    dx = 1;
                }
                SzPad_ResetCounter(0, 0xA000);
            }
            if (d->row != oldRow) {
                SzSound_PlaySE(0, 3);
            } else if (dx == 0) {
                if (SzPad_Check(0, 0, 0x800) != 0) {
                    if (SzData_GetRank((s32) player, (s32) card) > 0) {
                        if (SzData_GetBagCount((s32) player, (s32) card, 3) > 0) {
                            if (*d->list2 != 0x3E7) {
                                SzData_PullDeckLeader((s32) player, slot);
                                *d->list2 = 0x3E7;
                            }
                            if (SzData_PushDeckLeader((s32) player, slot, (s32) card) != 0) {
                                *d->list2 = card;
                                lSzDuel_ReqGhostCard(card, (s32) d->row, 1, 0, 0);
                                SzText_Free(2, (s32) player);
                                d->dirty = 1U;
                            }
                            SzSound_PlaySE(0, 4);
                        } else {
                            SzSound_PlaySE(0, 6);
                        }
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                } else if (SzPad_Check(0, 2, 0xC0) != 0) {
                    if (SzPad_Check(0, 2, 0x80) != 0) {
                        if (SzData_PullDeck((s32) player, slot, info) != 0) {
                            for (k = 0; k < 0x28; k++) {
                                if (card == d->list2[k + 1]) {
                                    d->list2[k + 1] = 0x3E7;
                                    break;
                                }
                            }
                            lSzDuel_SortDeck();
                            lSzDuel_ReqGhostCard(card, (s32) d->row, 0, 0, 1);
                            SzSound_PlaySE(0, 4);
                        } else {
                            SzSound_PlaySE(0, 6);
                        }
                    } else if (SzData_PushDeck((s32) player, slot, (s32) card) != 0) {
                        d->list2[d->count2 - 1] = card;
                        lSzDuel_SortDeck();
                        lSzDuel_ReqGhostCard(card, (s32) d->row, 1, 0, 0);
                        SzSound_PlaySE(0, 4);
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                } else if (SzPad_Check(0, 2, 3) != 0) {
                    oldKey = d->sort[held];
                    if (SzPad_Check(0, 2, 1) != 0) {
                        d->sort[held] = (d->sort[held] + 9) % 10;
                    } else {
                        d->sort[held] = (d->sort[held] + 0xB) % 10;
                    }
                    if (d->sort[held] != oldKey) {
                        lSzDuel_SortBag();
                        SzSound_PlaySE(0, 0x13);
                    }
                } else if (SzPad_Check(0, 0, 0x20) != 0) {
                    if (alt != 0) {
                        d->mode = 3U;
                        d->scrollTo = 0;
                        SzSound_PlaySE(0, 0x11);
                    } else if (lSzDuel_IsDeckReady((s32) player, slot) != 0) {
                        SzSound_PlaySE(0, 5);
                        SzGame_Pop();
                    } else {
                        SzSound_PlaySE(0, 6);
                        d->prevMode = (u8) d->mode;
                        d->mode = 0xDU;
                    }
                } else if (SzPad_Check(0, 0, 0x10) != 0) {
                    if (alt != 0) {
                        owned2 = 0;
                        if ((s32) card < 0x2AB) {
                            if (SzData_GetBagCount((s32) player, (s32) card, -1) > 0) {
                                owned2 = 1;
                            }
                            if (SzData_GetLookFlag((s32) player, (s32) card) != 0) {
                                owned2 = 1;
                            }
                        }
                        if (owned2 != 0) {
                            SzDuel_Init3DView((s32) card);
                            SzGame_Push(7, 2);
                            SzSound_PlaySE(0, 4);
                        } else {
                            SzSound_PlaySE(0, 6);
                        }
                    } else {
                        d->mode = 2U;
                        d->scrollTo = 0x140;
                        SzSound_PlaySE(0, 0x10);
                    }
                } else if (SzPad_Check(0, 2, 0xA000) != 0) {
                    if (SzPad_Check(0, 2, 0x8000) != 0) {
                        if (alt != 0) {
                            d->mode = 1U;
                        } else {
                            d->mode = 2U;
                            d->scrollTo = 0x140;
                        }
                        SzSound_PlaySE(0, 0x12);
                    } else {
                        if (alt != 0) {
                            d->mode = 3U;
                            d->scrollTo = 0;
                        } else {
                            d->mode = 4U;
                            d->row2 = (u8) d->row;
                        }
                        SzSound_PlaySE(0, 0x12);
                    }
                }
            }
        }
        break;
    case 4:
    case 5:
        index = d->offset2 + d->row2;
        card2 = d->list2[index];
        info2 = SzData_CheckDeck((s32) player, slot, (s32) card2);
        held = (SzPad_Check(0, 1, 0x100) != 0) ? 1 : 0;
        oldRow2 = (s32) d->row2;
        if (SzPad_Check(0, 2, 0xC) != 0) {
            if (SzPad_Check(0, 2, 4) != 0) {
                dy = -5;
            } else {
                dy = 5;
            }
        } else if (SzPad_Check(0, 2, 0x5000) != 0) {
            if (SzPad_Check(0, 2, 0x1000) != 0) {
                if (d->row2 > 0) {
                    d->row2--;
                } else {
                    dy = -1;
                }
            } else if (d->row2 < 4) {
                d->row2++;
            } else {
                dy = 1;
            }
            SzPad_ResetCounter(0, 0xA000);
        }
        if (d->row2 != oldRow2) {
            SzSound_PlaySE(0, 3);
        } else if (dy == 0) {
            if (SzPad_Check(0, 0, 0x800) != 0) {
                SzData_SetCurrentDeck((s32) player, (s32) (slot + 1) % 3);
                {
                    s32 i;
                    u16 *entry;
                    s32 r2;
                    s32 player2;
                    DuelState *state;

                    player2 = duelState.s.player;
                    state = &duelState.s;
                    r2 = SzData_GetCurrentDeck(player2);
                    entry = duelState.s.list2;
                    duelState.s.count2 = 0;
                    *entry = SzData_GetLeader(player2, r2);
                    entry++;
                    duelState.s.count2++;
                    i = 0;
                    do {
                        *entry = SzData_GetCardNo(player2, r2, i);
                        i++;
                        entry++;
                        state->count2++;
                    } while (i < 0x28);
                }
                lSzDuel_SortDeck();
                SzText_Free(2, (s32) player);
                d->dirty = 1U;
                SzSound_PlaySE(0, 9);
            } else if (SzPad_Check(0, 2, 0xC0) != 0) {
                if (index > 0) {
                    if (card2 == 0x3E7) {
                        SzSound_PlaySE(0, 6);
                    } else if (SzPad_Check(0, 2, 0x80) != 0) {
                        if (SzData_PullDeck((s32) player, slot, info2) != 0) {
                            d->list2[index] = 0x3E7;
                            lSzDuel_SortDeck();
                            lSzDuel_ReqGhostCard(card2, (s32) d->row2, 0, 0, 1);
                            SzSound_PlaySE(0, 4);
                        } else {
                            SzSound_PlaySE(0, 6);
                        }
                    } else if (SzData_PushDeck((s32) player, slot, (s32) card2) != 0) {
                        d->list2[d->count2 - 1] = card2;
                        lSzDuel_SortDeck();
                        lSzDuel_ReqGhostCard(card2, (s32) d->row2, 1, 0, 0);
                        SzSound_PlaySE(0, 4);
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                } else if (SzPad_Check(0, 2, 0x80) != 0) {
                    if (*d->list2 != 0x3E7) {
                        SzData_PullDeckLeader((s32) player, slot);
                        *d->list2 = 0x3E7;
                        lSzDuel_ReqGhostCard(card2, (s32) d->row2, 0, 1, 0);
                        SzText_Free(2, (s32) player);
                        d->dirty = 1U;
                        SzSound_PlaySE(0, 4);
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                }
            } else if (SzPad_Check(0, 2, 3) != 0) {
                oldKey2 = d->sort2[held];
                if (SzPad_Check(0, 2, 1) != 0) {
                    d->sort2[held] = (d->sort2[held] + 9) % 10;
                } else {
                    d->sort2[held] = (d->sort2[held] + 0xB) % 10;
                }
                if (d->sort2[held] != oldKey2) {
                    lSzDuel_SortDeck();
                    SzSound_PlaySE(0, 0x13);
                }
            } else if (SzPad_Check(0, 0, 0x20) != 0) {
                if (alt != 0) {
                    d->mode = 4U;
                    d->scrollTo = 0;
                    SzSound_PlaySE(0, 0x11);
                } else if (lSzDuel_IsDeckReady((s32) player, slot) != 0) {
                    SzSound_PlaySE(0, 5);
                    SzGame_Pop();
                } else {
                    SzSound_PlaySE(0, 6);
                    d->prevMode = (u8) d->mode;
                    d->mode = 0xDU;
                }
            } else if (SzPad_Check(0, 0, 0x10) != 0) {
                if (alt != 0) {
                    owned3 = 0;
                    if ((s32) card2 < 0x2AB) {
                        if (SzData_GetBagCount((s32) player, (s32) card2, -1) > 0) {
                            owned3 = 1;
                        }
                        if (SzData_GetLookFlag((s32) player, (s32) card2) != 0) {
                            owned3 = 1;
                        }
                    }
                    if (owned3 != 0) {
                        SzDuel_Init3DView((s32) card2);
                        SzGame_Push(7, 2);
                        SzSound_PlaySE(0, 4);
                    } else {
                        SzSound_PlaySE(0, 6);
                    }
                } else {
                    d->mode = 5U;
                    d->scrollTo = -0x140;
                    SzSound_PlaySE(0, 0x10);
                }
            } else if (SzPad_Check(0, 2, 0xA000) != 0) {
                if (SzPad_Check(0, 2, 0x8000) != 0) {
                    if (alt != 0) {
                        d->mode = 4U;
                        d->scrollTo = 0;
                    } else {
                        d->mode = 3U;
                        d->row = (u8) d->row2;
                    }
                    SzSound_PlaySE(0, 0x12);
                } else {
                    if (alt != 0) {
                        d->mode = 6U;
                    } else {
                        d->mode = 5U;
                        d->scrollTo = -0x140;
                    }
                    SzSound_PlaySE(0, 0x12);
                }
            }
        }
        break;
    case 6:
        if (SzPad_Check(0, 2, 0x5000) != 0) {
            oldSort4 = d->sort4;
            if (SzPad_Check(0, 2, 0x1000) != 0) {
                d->sort4 = (d->sort4 + 3) % 4;
            } else {
                d->sort4 = (d->sort4 + 5) % 4;
            }
            if (d->sort4 != oldSort4) {
                SzSound_PlaySE(0, 0x13);
            }
            SzPad_ResetCounter(0, 0xA000);
        } else if (SzPad_Check(0, 2, 0x8000) != 0) {
            d->mode = 5U;
            SzSound_PlaySE(0, 0x12);
        } else if (SzPad_Check(0, 2, 0x20) != 0) {
            d->mode = 5U;
            SzSound_PlaySE(0, 0x11);
        }
        break;
    case 7:
        if (SzPad_Check(0, 0, 0xA000) != 0) {
            oldSel = d->sel;
            if (SzPad_Check(0, 0, 0x8000) != 0) {
                d->sel = 1U;
            } else {
                d->sel = 0U;
            }
            if (d->sel != oldSel) {
                SzSound_PlaySE(0, 3);
            }
        } else if (SzPad_Check(0, 0, 0xC0) != 0) {
            if (d->sel != 0) {
                pickCard = d->list[d->offset + d->row];
                ids = d->pick->ids;
                ids[0] = Ta_GetRecycle((s32) player, (s32) pickCard);
                ids[1] = Ta_GetRecycle((s32) player, (s32) pickCard);
                ids[2] = Ta_GetRecycle((s32) player, (s32) pickCard);
                SzData_DelBag((s32) player, (s32) pickCard);
                d->step = 0;
                d->sel = 0;
                d->mode = 8;
            } else {
                d->mode = d->prevMode;
            }
            SzSound_PlaySE(0, 4);
        } else if (SzPad_Check(0, 0, 0x20) != 0) {
            d->mode = (u8) d->prevMode;
            SzSound_PlaySE(0, 0x11);
        }
        break;
    case 8:
        if ((s32) d->step < 3) {
            if ((s32) d->sel < 0x80) {
                if (d->sel == 0x7F) {
                    SzData_AddBag((s32) player, 0, ((u16 *)d->pick->ids)[d->step]);
                    lSzDuel_ReBuildBag();
                    SzSound_PlaySE(0, 7);
                }
                d->sel = (u8) (d->sel + 1);
            } else if (SzPad_Check(0, 0, 0xF0) != 0) {
                SzSound_PlaySE(0, 4);
                d->step = (u8) (d->step + 1);
                if ((s32) d->step < 3) {
                    d->sel = 0U;
                }
            }
        } else if (SzPad_Check(0, 0, 0xF0) != 0) {
            Taku_Set_Duel5_flg();
            d->mode = (u8) d->prevMode;
            SzSound_PlaySE(0, 4);
        }
        break;
    case 9:
        if (SzPad_Check(0, 2, 0xA000) != 0) {
            if (SzPad_Check(0, 2, 0x8000) != 0) {
                d->sel = (d->sel + 7) % 8;
            } else {
                d->sel = (d->sel + 9) % 8;
            }
            SzSound_PlaySE(0, 3);
        } else if (SzPad_Check(0, 2, 0x5000) != 0) {
            ch = d->code[d->sel];
            digit = ch - 0x30;
            if ((s32) ch >= 0x61) {
                digit = ch - 0x57;
            }
            if (SzPad_Check(0, 2, 0x1000) != 0) {
                next = (s32) (digit + 0x25) % 36;
            } else {
                next = (s32) (digit + 0x23) % 36;
            }
            if (next >= 0xA) {
                d->code[d->sel] = next + 0x57;
            } else {
                d->code[d->sel] = next + 0x30;
            }
            SzSound_PlaySE(0, 3);
        } else if (SzPad_Check(0, 0, 0xC0) != 0) {
            code = lSzDuel_HitPassword(d->code);
            if (code >= 0) {
                if (SzData_GetPassFlag((s32) player, code) != 0) {
                    d->mode = 0xCU;
                } else {
                    d->pick->ids[0] = code;
                    d->mode = 0xAU;
                    SzData_SetPassFlag((s32) player, code, 1);
                    SzData_AddBag((s32) player, 0, code);
                    lSzDuel_ReBuildBag();
                }
                SzSound_PlaySE(0, 4);
            } else {
                d->mode = 0xBU;
                SzSound_PlaySE(0, 6);
            }
        } else if (SzPad_Check(0, 0, 0x20) != 0) {
            d->mode = (u8) d->prevMode;
            SzSound_PlaySE(0, 0x11);
        }
        break;
    case 10:
    case 11:
    case 12:
    case 13:
        if (SzPad_Check(0, 0, 0xF0) != 0) {
            d->mode = (u8) d->prevMode;
            SzSound_PlaySE(0, 4);
        }
        break;
    }
    if (SzPad_IsAnalog(0) != 0) {
        if (((d->mode == 1U) || (d->mode == 2U) || (d->mode == 3U) || (d->mode == 4U)) && (dx == 0)) {
            stick = (SzPad_GetAnalogInfo(0, 3) & 0xFF) - 0x80;
            if (((stick >= 0) ? stick : -stick) > 0x30) {
                if (stick > 0) {
                    stick -= 0x30;
                } else {
                    stick += 0x30;
                }
                dx = (stick * 0xF) >> 7;
            }
        }
        if (((d->mode == 3U) || (d->mode == 4U) || (d->mode == 5U) || (d->mode == 6U)) && (dy == 0)) {
            stick2 = (SzPad_GetAnalogInfo(0, 1) & 0xFF) - 0x80;
            if (((stick2 >= 0) ? stick2 : -stick2) > 0x30) {
                if (stick2 > 0) {
                    stick2 -= 0x30;
                } else {
                    stick2 += 0x30;
                }
                dy = (stick2 * 5) >> 7;
            }
        }
    }
    if (dx != 0) {
        limit = nonnegative_001B8840(d->count - 5);
        oldOffset = d->offset;
        offset = oldOffset + dx;
        if (nonnegative_001B8840(offset) < limit) {
            offset = nonnegative_001B8840(offset);
        } else {
            offset = limit;
        }
        d->offset = offset;
        if (d->offset != oldOffset) {
            SzSound_PlaySE(0, 3);
        }
        d->idle = 0x5A;
    }
    if (dy != 0) {
        limit2 = nonnegative_001B8840(d->count2 - 5);
        oldOffset2 = d->offset2;
        offset2 = oldOffset2 + dy;
        if (nonnegative_001B8840(offset2) < limit2) {
            offset2 = nonnegative_001B8840(offset2);
        } else {
            offset2 = limit2;
        }
        d->offset2 = offset2;
        if (d->offset2 != oldOffset2) {
            SzSound_PlaySE(0, 3);
        }
        d->idle = 0x5A;
    }
}
