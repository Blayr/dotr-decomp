#include "common.h"
#include "campaign.h"

/* Works out which campaign text (bun) to show next and when it ends (hantei: judgement). */
s32 Taku_Camp_BUN_HANTEI(void) {
    extern s16 D_00299ED2;
    s32 player;
    s32 ret;
    s8 *context;
    s8 temp_a0;
    s8 temp_a1;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 temp_a0_2;
    s8 temp_a0_3;
    s16 temp_a0_4;
    s8 temp_a0_5;
    s8 temp_v1_4;
    s16 temp_v1_5;
    s16 temp_a0_6;

    player = campaignState;
    context = &campaignState;
    if (D_00299ED2 < 0xC8) {
        campaignWork.talkSpeaker = 0;
        if ((s16)player == 0) {
            switch (context[0xC6]) {
            case 2:
                campaignWork.talkMessage = 0x887;
                campaignWork.talkMessageCount = 1;
                break;
            case 3:
                campaignWork.talkMessage = campaignWork.talkPage + 0x89E;
                campaignWork.talkMessageCount = 6;
                break;
            case 4:
                campaignWork.talkMessage = campaignWork.talkPage + 0x88D;
                campaignWork.talkMessageCount = 2;
                break;
            case 5:
                campaignWork.talkMessage = 0x895;
                campaignWork.talkMessageCount = 1;
                break;
            case 6:
                campaignWork.talkMessage = 0x898;
                campaignWork.talkMessageCount = 1;
                break;
            case 7:
                campaignWork.talkMessage = campaignWork.talkPage + 0x8AD;
                campaignWork.talkMessageCount = 7;
                break;
            case 8:
                campaignWork.talkMessage = 0x88A;
                campaignWork.talkMessageCount = 1;
                break;
            case 9:
                campaignWork.talkMessage = 0x892;
                campaignWork.talkMessageCount = 1;
                break;
            case 10:
                campaignWork.talkMessage = campaignWork.talkPage + 0x89A;
                campaignWork.talkMessageCount = 2;
                break;
            case 11:
                if (context[0xE] == 1 || context[0xE] == 2) {
                    campaignWork.talkMessageCount = 9;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8DF;
                } else if (context[0xE] >= 3) {
                    if (campaignWork.duelMenuChoice == 1) {
                        campaignWork.talkMessageCount = 1;
                        campaignWork.talkMessage = 0x902;
                    } else {
                        campaignWork.talkMessageCount = 9;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x8DF;
                    }
                }
                break;
            }
            if (*(s16 *)(context + 0xC2) != 0x64) {
                return ret;
            }
            campaignWork.talkMessageCount = 1;
            campaignWork.talkMessage = 0x86C;
            campaignWork.talkSpeaker = 1;
            return ret;
        }
        switch (context[0xC6]) {
        case 12:
            campaignWork.talkMessage = campaignWork.talkPage + 0x935;
            campaignWork.talkMessageCount = 2;
            break;
        case 13:
            campaignWork.talkMessage = campaignWork.talkPage + 0x939;
            campaignWork.talkMessageCount = 2;
            break;
        case 14:
            campaignWork.talkMessage = campaignWork.talkPage + 0x93D;
            campaignWork.talkMessageCount = 2;
            break;
        case 16:
            campaignWork.talkMessage = 0x94A;
            campaignWork.talkMessageCount = 1;
            break;
        case 18:
            campaignWork.talkMessage = campaignWork.talkPage + 0x94E;
            campaignWork.talkMessageCount = 3;
            break;
        case 19:
            campaignWork.talkMessageCount = 4;
            campaignWork.talkMessage = campaignWork.talkPage + 0x953;
            break;
        case 20:
            campaignWork.talkMessage = 0x95C;
            campaignWork.talkMessageCount = 1;
            break;
        case 21:
            campaignWork.talkMessageCount = 5;
            campaignWork.talkMessage = campaignWork.talkPage + 0x95E;
            break;
        case 0:
            campaignWork.talkMessageCount = 2;
            campaignWork.talkMessage = campaignWork.talkPage + 0x968;
            break;
        case 11:
            campaignWork.talkMessageCount = 1;
            campaignWork.talkMessage = 0x983;
            break;
        }
        switch (*(s16 *)(context + 0xC2)) {
        case 0x69:
            campaignWork.talkMessageCount = 1;
            campaignWork.talkMessage = 0x94E;
            campaignWork.talkSpeaker = 1;
            return ret;
        case 0x6F:
            campaignWork.talkMessageCount = 1;
            campaignWork.talkMessage = 0x970;
            campaignWork.talkSpeaker = 2;
            campaignWork.duelistName[1] = 0xC5;
            campaignWork.duelistSide[1] = 1;
            campaignWork.unk53B5 = 1;
            return ret;
        }
    } else if (*(s16 *)(context + 0xC2) >= 0xC8 && *(s16 *)(context + 0xC2) < 0x12C) {
            {
                campaignWork.talkSpeaker = 0;
                if ((s16)player == 0) {
                    switch (context[0xC6]) {
                    case 2:
                        campaignWork.talkMessage = 0x888;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 3:
                        campaignWork.talkMessage = campaignWork.talkPage + 0x8A4;
                        campaignWork.talkMessageCount = 2;
                        return ret;
                    case 4:
                        campaignWork.talkMessage = 0x890;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 5:
                        campaignWork.talkMessage = 0x896;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 6:
                        campaignWork.talkMessage = 0x899;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 7:
                        campaignWork.talkMessageCount = 1;
                        campaignWork.talkMessage = 0x8B5;
                        return ret;
                    case 8:
                        campaignWork.talkMessage = campaignWork.talkPage + 0x88A;
                        campaignWork.talkMessageCount = 2;
                        return ret;
                    case 9:
                        campaignWork.talkMessage = 0x893;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 10:
                        campaignWork.talkMessage = 0x89D;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 11:
                        if (*(s16 *)(context + 0xC2) == 0xD4) {
                            campaignWork.talkMessageCount = 1;
                            campaignWork.talkMessage = 0x8E9;
                            return ret;
                        }
                        if (*(s16 *)(context + 0xC2) == 0xD5) {
                            campaignWork.talkMessageCount = 2;
                            campaignWork.talkMessage = campaignWork.talkPage + 0x902;
                            return ret;
                        }
                        break;
                    }
                } else {
                    switch (context[0xC6]) {
                    case 12:
                        campaignWork.talkMessage = 0x938;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 13:
                        campaignWork.talkMessage = 0x93C;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 14:
                        campaignWork.talkMessage = 0x940;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 16:
                        campaignWork.talkMessage = 0x94B;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 18:
                        campaignWork.talkMessage = 0x952;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 19:
                        campaignWork.talkMessageCount = 1;
                        campaignWork.talkMessage = 0x958;
                        return ret;
                    case 20:
                        campaignWork.talkMessage = 0x95D;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 21:
                        campaignWork.talkMessageCount = 3;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x963;
                        return ret;
                    case 0:
                        campaignWork.talkMessageCount = 2;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x96A;
                        return ret;
                    case 11:
                        campaignWork.talkMessageCount = 2;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x983;
                        return ret;
                    }
                }
            }
    } else if (*(s16 *)(context + 0xC2) >= 0x12C && *(s16 *)(context + 0xC2) < 0x190) {
            {
                campaignWork.talkSpeaker = 0;
                if ((s16)player == 0) {
                    switch (context[0xC6]) {
                    case 2:
                        campaignWork.talkMessageCount = 1;
                        campaignWork.talkMessage = 0x889;
                        return ret;
                    case 3:
                        campaignWork.talkMessageCount = 4;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x8A6;
                        return ret;
                    case 4:
                        campaignWork.talkMessage = 0x891;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 5:
                        campaignWork.talkMessage = 0x897;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 6:
                        campaignWork.talkMessage = 0x89A;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 7:
                        campaignWork.talkMessageCount = 1;
                        campaignWork.talkMessage = 0x8B6;
                        return ret;
                    case 8:
                        campaignWork.talkMessage = 0x88D;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 9:
                        campaignWork.talkMessage = 0x894;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 10:
                        campaignWork.talkMessage = 0x89E;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 11:
                        if (*(s16 *)(context + 0xC2) == 0x138) {
                            campaignWork.talkMessageCount = 1;
                            campaignWork.talkMessage = 0x8EA;
                            return ret;
                        }
                        if (*(s16 *)(context + 0xC2) == 0x139) {
                            campaignWork.talkMessageCount = 1;
                            campaignWork.talkMessage = 0x905;
                            return ret;
                        }
                        break;
                    }
                } else {
                    switch (context[0xC6]) {
                    case 12:
                        campaignWork.talkMessage = 0x939;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 13:
                        campaignWork.talkMessage = 0x93D;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 14:
                        campaignWork.talkMessage = campaignWork.talkPage + 0x940;
                        campaignWork.talkMessageCount = 2;
                        return ret;
                    case 16:
                        campaignWork.talkMessageCount = 2;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x94B;
                        return ret;
                    case 18:
                        campaignWork.talkMessage = 0x953;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 19:
                        campaignWork.talkMessageCount = 3;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x958;
                        return ret;
                    case 20:
                        campaignWork.talkMessage = 0x95E;
                        campaignWork.talkMessageCount = 1;
                        return ret;
                    case 21:
                        campaignWork.talkMessageCount = 2;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x966;
                        return ret;
                    case 0:
                        campaignWork.talkMessageCount = 3;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x96C;
                        return ret;
                    case 11:
                        campaignWork.talkMessageCount = 3;
                        campaignWork.talkMessage = campaignWork.talkPage + 0x985;
                        return ret;
                    }
                }
            }
    } else {
            {
                switch (*(s16 *)(context + 0xC2)) {
                case 0x2724:
                    temp_a0 = campaignWork.talkPage;
                    if (temp_a0 == 0xA) {
                        campaignWork.talkPage = temp_a0 + 1;
                    }
                    campaignWork.talkMessageCount = 0xF;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x7EC;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 0;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2738:
                    campaignWork.talkMessageCount = 8;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x7FB;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2739:
                    campaignWork.talkMessageCount = 0xF;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x803;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2742:
                    campaignWork.talkMessageCount = 8;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x812;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x274C:
                    campaignWork.talkMessageCount = 7;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x81A;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2756:
                    campaignWork.talkMessageCount = 2;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x821;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2757:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x823;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC4;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2760:
                    campaignWork.talkMessageCount = 0x3E;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x824;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    switch (campaignWork.talkMessage) {
                    case 0x825:
                    case 0x826:
                    case 0x828:
                    case 0x82A:
                    case 0x82B:
                    case 0x82C:
                    case 0x82D:
                    case 0x82E:
                    case 0x82F:
                    case 0x830:
                    case 0x832:
                    case 0x833:
                    case 0x834:
                    case 0x835:
                    case 0x83D:
                    case 0x83E:
                    case 0x83F:
                    case 0x840:
                    case 0x841:
                    case 0x842:
                    case 0x844:
                    case 0x845:
                    case 0x846:
                    case 0x847:
                    case 0x84C:
                    case 0x84E:
                    case 0x84F:
                    case 0x850:
                    case 0x851:
                    case 0x853:
                    case 0x854:
                    case 0x857:
                    case 0x858:
                    case 0x859:
                    case 0x85A:
                    case 0x85B:
                    case 0x85C:
                    case 0x85D:
                    case 0x85F:
                    case 0x860:
                    case 0x861:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xC5;
                        campaignWork.duelistSide[0] = 1;
                        if (campaignWork.talkPage >= 4) {
                            campaignWork.unk53B4 = 1;
                            return ret;
                        }
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC4;
                        campaignWork.duelistSide[1] = 0;
                        campaignWork.unk53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x276A:
                    campaignWork.talkMessageCount = 4;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x862;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    temp_a1 = campaignWork.talkPage;
                    switch (temp_a1) {
                    case 1:
                    case 2:
                    case 4:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xC5;
                        campaignWork.duelistSide[0] = 1;
                        campaignWork.unk53B4 = 1;
                        return ret;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC4;
                        campaignWork.duelistSide[1] = 0;
                        campaignWork.unk53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x2AF8:
                    campaignWork.talkMessageCount = 5;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x866;
                    campaignWork.talkSpeaker = 3;
                    campaignWork.duelistName[0] = 0xC5;
                    campaignWork.duelistSide[0] = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B02:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x86B;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B0C:
                    campaignWork.talkMessageCount = 0x18;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x86C;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    temp_v1_2 = campaignWork.talkMessage;
                    switch (temp_v1_2) {
                    case 0x870:
                    case 0x872:
                    case 0x873:
                    case 0x874:
                    case 0x875:
                    case 0x876:
                    case 0x877:
                    case 0x878:
                    case 0x879:
                    case 0x87C:
                    case 0x87D:
                    case 0x87E:
                    case 0x87F:
                    case 0x880:
                    case 0x881:
                    case 0x882:
                    case 0x883:
                    case 0x884:
                    case 0x885:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xD7;
                        campaignWork.duelistSide[0] = 0;
                        campaignWork.unk53B4 = 1;
                        return ret;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC4;
                        campaignWork.duelistSide[1] = 0;
                        campaignWork.unk53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x2B70:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8AA;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B72:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8AB;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B74:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8AC;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B84:
                    campaignWork.talkMessageCount = 0x16;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8B6;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    temp_v1_3 = campaignWork.talkMessage;
                    switch (temp_v1_3) {
                    case 0x8BB:
                    case 0x8BD:
                    case 0x8BF:
                    case 0x8C0:
                    case 0x8C1:
                    case 0x8C3:
                    case 0x8C5:
                    case 0x8C6:
                    case 0x8C7:
                    case 0x8C8:
                    case 0x8C9:
                    case 0x8CB:
                    case 0x8CC:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xCD;
                        campaignWork.duelistSide[0] = 1;
                        if (campaignWork.talkPage >= 6) {
                            campaignWork.unk53B4 = 1;
                            return ret;
                        }
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xCE;
                        campaignWork.duelistSide[1] = 1;
                        campaignWork.unk53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x2B86:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8CC;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B87:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8CD;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B88:
                    campaignWork.talkMessageCount = 3;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8CE;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B8A:
                    campaignWork.talkMessageCount = 3;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8D1;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B8B:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8D4;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B8C:
                    campaignWork.talkMessageCount = 9;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8D5;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    temp_a0_2 = campaignWork.talkMessage;
                    switch (temp_a0_2) {
                    case 0x8D9:
                    case 0x8DB:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xCD;
                        campaignWork.duelistSide[0] = 1;
                        campaignWork.unk53B4 = 1;
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xD7;
                        campaignWork.duelistSide[1] = 0;
                        campaignWork.unk53B5 = 1;
                        break;
                    }
                    if (campaignWork.talkPage >= 0xA) {
                        campaignWork.unk53B4 = 0;
                        campaignWork.unk53B5 = 0;
                        return ret;
                    }
                    break;
                case 0x2B8D:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = 0x8DF;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 0;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2B98:
                    campaignWork.talkMessageCount = 0x11;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8EA;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC5;
                    campaignWork.duelistSide[1] = 1;
                    campaignWork.unk53B5 = 1;
                    temp_a0_3 = campaignWork.talkPage;
                    switch (temp_a0_3) {
                    case 1:
                        campaignWork.duelist0Look = 0;
                        campaignWork.duelist1Look = 2;
                        return ret;
                    case 2:
                        campaignWork.duelist1Look = 2;
                        return ret;
                    case 3:
                        campaignWork.duelist1Look = 1;
                        return ret;
                    }
                    break;
                case 0x2B9A:
                    campaignWork.talkMessageCount = 6;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x8FB;
                    temp_a0_4 = campaignWork.talkMessage;
                    switch (temp_a0_4) {
                    case 0x8FC:
                    case 0x900:
                    case 0x901:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xD8;
                        campaignWork.duelistSide[0] = 1;
                        campaignWork.unk53B4 = 1;
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC5;
                        campaignWork.duelistSide[1] = 1;
                        campaignWork.unk53B5 = 1;
                        break;
                    }
                    temp_a0_5 = campaignWork.talkPage;
                    switch (temp_a0_5) {
                    case 0x8FC:
                        campaignWork.duelist0Look = 0;
                        campaignWork.duelist1Look = 0;
                        return ret;
                    case 0x8FD:
                    case 0x8FE:
                    case 0x8FF:
                        campaignWork.duelist1Look = 1;
                        return ret;
                    }
                    break;
                case 0x2BAC:
                    campaignWork.talkMessageCount = 3;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x905;
                    switch (campaignWork.talkPage) {
                    case 1:
                    case 3:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xD8;
                        campaignWork.duelistSide[0] = 1;
                        campaignWork.unk53B4 = 1;
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC5;
                        campaignWork.duelistSide[1] = 1;
                        campaignWork.unk53B5 = 1;
                        break;
                    }
                    if (campaignWork.talkPage != 1) {
                        return ret;
                    }
                    campaignWork.duelist0Look = 2;
                    campaignWork.duelist1Look = 2;
                    return ret;
                case 0x2BAE:
                    campaignWork.talkMessageCount = 4;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x908;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2BB0:
                    campaignWork.talkMessageCount = 0x11;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x90C;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2EE0:
                    campaignWork.talkMessageCount = 0x17;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x91D;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    switch (campaignWork.talkPage) {
                    case 4:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC4;
                        campaignWork.duelistSide[1] = 0;
                        campaignWork.unk53B4 = 1;
                        campaignWork.duelist1Look = 2;
                        break;
                    default:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xC5;
                        campaignWork.duelistSide[0] = 1;
                        campaignWork.unk53B5 = 1;
                        if (campaignWork.talkPage >= 4) {
                            campaignWork.duelist1Look = 2;
                        }
                        break;
                    }
                    if (campaignWork.talkPage >= 5) {
                        campaignWork.unk53B5 = 0;
                        return ret;
                    }
                    break;
                case 0x2F08:
                    campaignWork.talkMessageCount = 1;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x942;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xD2;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2F09:
                    campaignWork.talkMessageCount = 6;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x943;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xD2;
                    campaignWork.duelistSide[1] = 0;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2F62:
                    campaignWork.talkMessageCount = 3;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x970;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC5;
                    campaignWork.duelistSide[1] = 1;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2F64:
                    campaignWork.talkMessageCount = 0xF;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x973;
                    temp_v1_5 = campaignWork.talkMessage;
                    switch (temp_v1_5) {
                    case 0x974:
                    case 0x975:
                    case 0x976:
                    case 0x977:
                    case 0x978:
                    case 0x979:
                    case 0x97B:
                    case 0x97C:
                    case 0x97D:
                    case 0x982:
                        campaignWork.talkSpeaker = 3;
                        campaignWork.duelistName[0] = 0xD8;
                        campaignWork.duelistSide[0] = 0;
                        campaignWork.unk53B4 = 1;
                        break;
                    default:
                        campaignWork.talkSpeaker = 2;
                        campaignWork.duelistName[1] = 0xC5;
                        campaignWork.duelistSide[1] = 1;
                        campaignWork.unk53B5 = 1;
                        break;
                    }
                    temp_a0_6 = campaignWork.talkMessage;
                    switch (temp_a0_6) {
                    case 0x974:
                        campaignWork.duelist0Look = 0;
                        campaignWork.duelist1Look = 0;
                        return ret;
                    case 0x97A:
                        campaignWork.duelist0Look = 0;
                        campaignWork.duelist1Look = 2;
                        return ret;
                    }
                    break;
                case 0x2F76:
                    campaignWork.talkMessageCount = 2;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x988;
                    campaignWork.talkSpeaker = 3;
                    campaignWork.duelistName[0] = 0xD8;
                    campaignWork.duelistSide[0] = 0;
                    campaignWork.unk53B4 = 1;
                    if (campaignWork.talkPage != 1) {
                        return ret;
                    }
                    campaignWork.duelist0Look = 2;
                    campaignWork.duelist1Look = 2;
                    return ret;
                case 0x2F78:
                    campaignWork.talkMessageCount = 0x11;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x98A;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC5;
                    campaignWork.duelistSide[1] = 1;
                    campaignWork.unk53B4 = 0;
                    campaignWork.unk53B5 = 1;
                    if (campaignWork.talkPage != 1) {
                        return ret;
                    }
                    campaignWork.duelist0Look = 2;
                    campaignWork.duelist1Look = 2;
                    return ret;
                case 0x2F7A:
                    campaignWork.talkMessageCount = 6;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x99B;
                    campaignWork.talkSpeaker = 2;
                    campaignWork.duelistName[1] = 0xC5;
                    campaignWork.duelistSide[1] = 1;
                    campaignWork.unk53B5 = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                case 0x2F7C:
                    campaignWork.talkMessageCount = 0xE;
                    campaignWork.talkMessage = campaignWork.talkPage + 0x9A1;
                    campaignWork.talkSpeaker = 1;
                    campaignWork.duelist0Look = 0;
                    campaignWork.duelist1Look = 0;
                    return ret;
                }
            }
    }
    return ret;
}
