#include "common.h"

s32 func_0022D140(void) {
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

    player = D_00299E10;
    context = &D_00299E10;
    if (D_00299ED2 < 0xC8) {
        *(s8 *)0x01ED537E = 0;
        if ((s16)player == 0) {
            switch (context[0xC6]) {
            case 2:
                *(s16 *)0x01ED5378 = 0x887;
                *(s8 *)0x01ED537C = 1;
                break;
            case 3:
                *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x89E;
                *(s8 *)0x01ED537C = 6;
                break;
            case 4:
                *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x88D;
                *(s8 *)0x01ED537C = 2;
                break;
            case 5:
                *(s16 *)0x01ED5378 = 0x895;
                *(s8 *)0x01ED537C = 1;
                break;
            case 6:
                *(s16 *)0x01ED5378 = 0x898;
                *(s8 *)0x01ED537C = 1;
                break;
            case 7:
                *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8AD;
                *(s8 *)0x01ED537C = 7;
                break;
            case 8:
                *(s16 *)0x01ED5378 = 0x88A;
                *(s8 *)0x01ED537C = 1;
                break;
            case 9:
                *(s16 *)0x01ED5378 = 0x892;
                *(s8 *)0x01ED537C = 1;
                break;
            case 10:
                *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x89A;
                *(s8 *)0x01ED537C = 2;
                break;
            case 11:
                if (context[0xE] == 1 || context[0xE] == 2) {
                    *(s8 *)0x01ED537C = 9;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8DF;
                } else if (context[0xE] >= 3) {
                    if (*(s8 *)0x01ED53C2 == 1) {
                        *(s8 *)0x01ED537C = 1;
                        *(s16 *)0x01ED5378 = 0x902;
                    } else {
                        *(s8 *)0x01ED537C = 9;
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8DF;
                    }
                }
                break;
            }
            if (*(s16 *)(context + 0xC2) != 0x64) {
                return ret;
            }
            *(s8 *)0x01ED537C = 1;
            *(s16 *)0x01ED5378 = 0x86C;
            *(s8 *)0x01ED537E = 1;
            return ret;
        }
        switch (context[0xC6]) {
        case 12:
            *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x935;
            *(s8 *)0x01ED537C = 2;
            break;
        case 13:
            *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x939;
            *(s8 *)0x01ED537C = 2;
            break;
        case 14:
            *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x93D;
            *(s8 *)0x01ED537C = 2;
            break;
        case 16:
            *(s16 *)0x01ED5378 = 0x94A;
            *(s8 *)0x01ED537C = 1;
            break;
        case 18:
            *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x94E;
            *(s8 *)0x01ED537C = 3;
            break;
        case 19:
            *(s8 *)0x01ED537C = 4;
            *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x953;
            break;
        case 20:
            *(s16 *)0x01ED5378 = 0x95C;
            *(s8 *)0x01ED537C = 1;
            break;
        case 21:
            *(s8 *)0x01ED537C = 5;
            *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x95E;
            break;
        case 0:
            *(s8 *)0x01ED537C = 2;
            *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x968;
            break;
        case 11:
            *(s8 *)0x01ED537C = 1;
            *(s16 *)0x01ED5378 = 0x983;
            break;
        }
        switch (*(s16 *)(context + 0xC2)) {
        case 0x69:
            *(s8 *)0x01ED537C = 1;
            *(s16 *)0x01ED5378 = 0x94E;
            *(s8 *)0x01ED537E = 1;
            return ret;
        case 0x6F:
            *(s8 *)0x01ED537C = 1;
            *(s16 *)0x01ED5378 = 0x970;
            *(s8 *)0x01ED537E = 2;
            *(s16 *)0x01ED53BC = 0xC5;
            *(s8 *)0x01ED53BF = 1;
            *(s8 *)0x01ED53B5 = 1;
            return ret;
        }
    } else if (*(s16 *)(context + 0xC2) >= 0xC8 && *(s16 *)(context + 0xC2) < 0x12C) {
            {
                *(s8 *)0x01ED537E = 0;
                if ((s16)player == 0) {
                    switch (context[0xC6]) {
                    case 2:
                        *(s16 *)0x01ED5378 = 0x888;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 3:
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8A4;
                        *(s8 *)0x01ED537C = 2;
                        return ret;
                    case 4:
                        *(s16 *)0x01ED5378 = 0x890;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 5:
                        *(s16 *)0x01ED5378 = 0x896;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 6:
                        *(s16 *)0x01ED5378 = 0x899;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 7:
                        *(s8 *)0x01ED537C = 1;
                        *(s16 *)0x01ED5378 = 0x8B5;
                        return ret;
                    case 8:
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x88A;
                        *(s8 *)0x01ED537C = 2;
                        return ret;
                    case 9:
                        *(s16 *)0x01ED5378 = 0x893;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 10:
                        *(s16 *)0x01ED5378 = 0x89D;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 11:
                        if (*(s16 *)(context + 0xC2) == 0xD4) {
                            *(s8 *)0x01ED537C = 1;
                            *(s16 *)0x01ED5378 = 0x8E9;
                            return ret;
                        }
                        if (*(s16 *)(context + 0xC2) == 0xD5) {
                            *(s8 *)0x01ED537C = 2;
                            *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x902;
                            return ret;
                        }
                        break;
                    }
                } else {
                    switch (context[0xC6]) {
                    case 12:
                        *(s16 *)0x01ED5378 = 0x938;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 13:
                        *(s16 *)0x01ED5378 = 0x93C;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 14:
                        *(s16 *)0x01ED5378 = 0x940;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 16:
                        *(s16 *)0x01ED5378 = 0x94B;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 18:
                        *(s16 *)0x01ED5378 = 0x952;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 19:
                        *(s8 *)0x01ED537C = 1;
                        *(s16 *)0x01ED5378 = 0x958;
                        return ret;
                    case 20:
                        *(s16 *)0x01ED5378 = 0x95D;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 21:
                        *(s8 *)0x01ED537C = 3;
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x963;
                        return ret;
                    case 0:
                        *(s8 *)0x01ED537C = 2;
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x96A;
                        return ret;
                    case 11:
                        *(s8 *)0x01ED537C = 2;
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x983;
                        return ret;
                    }
                }
            }
    } else if (*(s16 *)(context + 0xC2) >= 0x12C && *(s16 *)(context + 0xC2) < 0x190) {
            {
                *(s8 *)0x01ED537E = 0;
                if ((s16)player == 0) {
                    switch (context[0xC6]) {
                    case 2:
                        *(s8 *)0x01ED537C = 1;
                        *(s16 *)0x01ED5378 = 0x889;
                        return ret;
                    case 3:
                        *(s8 *)0x01ED537C = 4;
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8A6;
                        return ret;
                    case 4:
                        *(s16 *)0x01ED5378 = 0x891;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 5:
                        *(s16 *)0x01ED5378 = 0x897;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 6:
                        *(s16 *)0x01ED5378 = 0x89A;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 7:
                        *(s8 *)0x01ED537C = 1;
                        *(s16 *)0x01ED5378 = 0x8B6;
                        return ret;
                    case 8:
                        *(s16 *)0x01ED5378 = 0x88D;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 9:
                        *(s16 *)0x01ED5378 = 0x894;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 10:
                        *(s16 *)0x01ED5378 = 0x89E;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 11:
                        if (*(s16 *)(context + 0xC2) == 0x138) {
                            *(s8 *)0x01ED537C = 1;
                            *(s16 *)0x01ED5378 = 0x8EA;
                            return ret;
                        }
                        if (*(s16 *)(context + 0xC2) == 0x139) {
                            *(s8 *)0x01ED537C = 1;
                            *(s16 *)0x01ED5378 = 0x905;
                            return ret;
                        }
                        break;
                    }
                } else {
                    switch (context[0xC6]) {
                    case 12:
                        *(s16 *)0x01ED5378 = 0x939;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 13:
                        *(s16 *)0x01ED5378 = 0x93D;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 14:
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x940;
                        *(s8 *)0x01ED537C = 2;
                        return ret;
                    case 16:
                        *(s8 *)0x01ED537C = 2;
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x94B;
                        return ret;
                    case 18:
                        *(s16 *)0x01ED5378 = 0x953;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 19:
                        *(s8 *)0x01ED537C = 3;
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x958;
                        return ret;
                    case 20:
                        *(s16 *)0x01ED5378 = 0x95E;
                        *(s8 *)0x01ED537C = 1;
                        return ret;
                    case 21:
                        *(s8 *)0x01ED537C = 2;
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x966;
                        return ret;
                    case 0:
                        *(s8 *)0x01ED537C = 3;
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x96C;
                        return ret;
                    case 11:
                        *(s8 *)0x01ED537C = 3;
                        *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x985;
                        return ret;
                    }
                }
            }
    } else {
            {
                switch (*(s16 *)(context + 0xC2)) {
                case 0x2724:
                    temp_a0 = *(s8 *)0x01ED537D;
                    if (temp_a0 == 0xA) {
                        *(s8 *)0x01ED537D = temp_a0 + 1;
                    }
                    *(s8 *)0x01ED537C = 0xF;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x7EC;
                    *(s8 *)0x01ED537E = 1;
                    *(s8 *)0x01ED53B4 = 0;
                    *(s8 *)0x01ED53B5 = 0;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2738:
                    *(s8 *)0x01ED537C = 8;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x7FB;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xC4;
                    *(s8 *)0x01ED53BF = 0;
                    *(s8 *)0x01ED53B4 = 0;
                    *(s8 *)0x01ED53B5 = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2739:
                    *(s8 *)0x01ED537C = 0xF;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x803;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xC4;
                    *(s8 *)0x01ED53BF = 0;
                    *(s8 *)0x01ED53B4 = 0;
                    *(s8 *)0x01ED53B5 = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2742:
                    *(s8 *)0x01ED537C = 8;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x812;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xC4;
                    *(s8 *)0x01ED53BF = 0;
                    *(s8 *)0x01ED53B4 = 0;
                    *(s8 *)0x01ED53B5 = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x274C:
                    *(s8 *)0x01ED537C = 7;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x81A;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xC4;
                    *(s8 *)0x01ED53BF = 0;
                    *(s8 *)0x01ED53B4 = 0;
                    *(s8 *)0x01ED53B5 = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2756:
                    *(s8 *)0x01ED537C = 2;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x821;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xC4;
                    *(s8 *)0x01ED53BF = 0;
                    *(s8 *)0x01ED53B4 = 0;
                    *(s8 *)0x01ED53B5 = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2757:
                    *(s8 *)0x01ED537C = 1;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x823;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xC4;
                    *(s8 *)0x01ED53BF = 0;
                    *(s8 *)0x01ED53B4 = 0;
                    *(s8 *)0x01ED53B5 = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2760:
                    *(s8 *)0x01ED537C = 0x3E;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x824;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    switch (*(s16 *)0x01ED5378) {
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
                        *(s8 *)0x01ED537E = 3;
                        *(s16 *)0x01ED53BA = 0xC5;
                        *(s8 *)0x01ED53BE = 1;
                        if (*(s8 *)0x01ED537D >= 4) {
                            *(s8 *)0x01ED53B4 = 1;
                            return ret;
                        }
                        break;
                    default:
                        *(s8 *)0x01ED537E = 2;
                        *(s16 *)0x01ED53BC = 0xC4;
                        *(s8 *)0x01ED53BF = 0;
                        *(s8 *)0x01ED53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x276A:
                    *(s8 *)0x01ED537C = 4;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x862;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    temp_a1 = *(s8 *)0x01ED537D;
                    switch (temp_a1) {
                    case 1:
                    case 2:
                    case 4:
                        *(s8 *)0x01ED537E = 3;
                        *(s16 *)0x01ED53BA = 0xC5;
                        *(s8 *)0x01ED53BE = 1;
                        *(s8 *)0x01ED53B4 = 1;
                        return ret;
                    default:
                        *(s8 *)0x01ED537E = 2;
                        *(s16 *)0x01ED53BC = 0xC4;
                        *(s8 *)0x01ED53BF = 0;
                        *(s8 *)0x01ED53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x2AF8:
                    *(s8 *)0x01ED537C = 5;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x866;
                    *(s8 *)0x01ED537E = 3;
                    *(s16 *)0x01ED53BA = 0xC5;
                    *(s8 *)0x01ED53BE = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B02:
                    *(s8 *)0x01ED537C = 1;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x86B;
                    *(s8 *)0x01ED537E = 2;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B0C:
                    *(s8 *)0x01ED537C = 0x18;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x86C;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    temp_v1_2 = *(s16 *)0x01ED5378;
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
                        *(s8 *)0x01ED537E = 3;
                        *(s16 *)0x01ED53BA = 0xD7;
                        *(s8 *)0x01ED53BE = 0;
                        *(s8 *)0x01ED53B4 = 1;
                        return ret;
                    default:
                        *(s8 *)0x01ED537E = 2;
                        *(s16 *)0x01ED53BC = 0xC4;
                        *(s8 *)0x01ED53BF = 0;
                        *(s8 *)0x01ED53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x2B70:
                    *(s8 *)0x01ED537C = 1;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8AA;
                    *(s8 *)0x01ED537E = 2;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B72:
                    *(s8 *)0x01ED537C = 1;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8AB;
                    *(s8 *)0x01ED537E = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B74:
                    *(s8 *)0x01ED537C = 1;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8AC;
                    *(s8 *)0x01ED537E = 2;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B84:
                    *(s8 *)0x01ED537C = 0x16;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8B6;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    temp_v1_3 = *(s16 *)0x01ED5378;
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
                        *(s8 *)0x01ED537E = 3;
                        *(s16 *)0x01ED53BA = 0xCD;
                        *(s8 *)0x01ED53BE = 1;
                        if (*(s8 *)0x01ED537D >= 6) {
                            *(s8 *)0x01ED53B4 = 1;
                            return ret;
                        }
                        break;
                    default:
                        *(s8 *)0x01ED537E = 2;
                        *(s16 *)0x01ED53BC = 0xCE;
                        *(s8 *)0x01ED53BF = 1;
                        *(s8 *)0x01ED53B5 = 1;
                        return ret;
                    }
                    break;
                case 0x2B86:
                    *(s8 *)0x01ED537C = 1;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8CC;
                    *(s8 *)0x01ED537E = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B87:
                    *(s8 *)0x01ED537C = 1;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8CD;
                    *(s8 *)0x01ED537E = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B88:
                    *(s8 *)0x01ED537C = 3;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8CE;
                    *(s8 *)0x01ED537E = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B8A:
                    *(s8 *)0x01ED537C = 3;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8D1;
                    *(s8 *)0x01ED537E = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B8B:
                    *(s8 *)0x01ED537C = 1;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8D4;
                    *(s8 *)0x01ED537E = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B8C:
                    *(s8 *)0x01ED537C = 9;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8D5;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    temp_a0_2 = *(s16 *)0x01ED5378;
                    switch (temp_a0_2) {
                    case 0x8D9:
                    case 0x8DB:
                        *(s8 *)0x01ED537E = 3;
                        *(s16 *)0x01ED53BA = 0xCD;
                        *(s8 *)0x01ED53BE = 1;
                        *(s8 *)0x01ED53B4 = 1;
                        break;
                    default:
                        *(s8 *)0x01ED537E = 2;
                        *(s16 *)0x01ED53BC = 0xD7;
                        *(s8 *)0x01ED53BF = 0;
                        *(s8 *)0x01ED53B5 = 1;
                        break;
                    }
                    if (*(s8 *)0x01ED537D >= 0xA) {
                        *(s8 *)0x01ED53B4 = 0;
                        *(s8 *)0x01ED53B5 = 0;
                        return ret;
                    }
                    break;
                case 0x2B8D:
                    *(s8 *)0x01ED537C = 1;
                    *(s16 *)0x01ED5378 = 0x8DF;
                    *(s8 *)0x01ED537E = 2;
                    *(s8 *)0x01ED53B4 = 0;
                    *(s8 *)0x01ED53B5 = 0;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2B98:
                    *(s8 *)0x01ED537C = 0x11;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8EA;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xC5;
                    *(s8 *)0x01ED53BF = 1;
                    *(s8 *)0x01ED53B5 = 1;
                    temp_a0_3 = *(s8 *)0x01ED537D;
                    switch (temp_a0_3) {
                    case 1:
                        *(s8 *)0x01ED546A = 0;
                        *(s8 *)0x01ED5469 = 2;
                        return ret;
                    case 2:
                        *(s8 *)0x01ED5469 = 2;
                        return ret;
                    case 3:
                        *(s8 *)0x01ED5469 = 1;
                        return ret;
                    }
                    break;
                case 0x2B9A:
                    *(s8 *)0x01ED537C = 6;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x8FB;
                    temp_a0_4 = *(s16 *)0x01ED5378;
                    switch (temp_a0_4) {
                    case 0x8FC:
                    case 0x900:
                    case 0x901:
                        *(s8 *)0x01ED537E = 3;
                        *(s16 *)0x01ED53BA = 0xD8;
                        *(s8 *)0x01ED53BE = 1;
                        *(s8 *)0x01ED53B4 = 1;
                        break;
                    default:
                        *(s8 *)0x01ED537E = 2;
                        *(s16 *)0x01ED53BC = 0xC5;
                        *(s8 *)0x01ED53BF = 1;
                        *(s8 *)0x01ED53B5 = 1;
                        break;
                    }
                    temp_a0_5 = *(s8 *)0x01ED537D;
                    switch (temp_a0_5) {
                    case 0x8FC:
                        *(s8 *)0x01ED546A = 0;
                        *(s8 *)0x01ED5469 = 0;
                        return ret;
                    case 0x8FD:
                    case 0x8FE:
                    case 0x8FF:
                        *(s8 *)0x01ED5469 = 1;
                        return ret;
                    }
                    break;
                case 0x2BAC:
                    *(s8 *)0x01ED537C = 3;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x905;
                    switch (*(s8 *)0x01ED537D) {
                    case 1:
                    case 3:
                        *(s8 *)0x01ED537E = 3;
                        *(s16 *)0x01ED53BA = 0xD8;
                        *(s8 *)0x01ED53BE = 1;
                        *(s8 *)0x01ED53B4 = 1;
                        break;
                    default:
                        *(s8 *)0x01ED537E = 2;
                        *(s16 *)0x01ED53BC = 0xC5;
                        *(s8 *)0x01ED53BF = 1;
                        *(s8 *)0x01ED53B5 = 1;
                        break;
                    }
                    if (*(s8 *)0x01ED537D != 1) {
                        return ret;
                    }
                    *(s8 *)0x01ED546A = 2;
                    *(s8 *)0x01ED5469 = 2;
                    return ret;
                case 0x2BAE:
                    *(s8 *)0x01ED537C = 4;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x908;
                    *(s8 *)0x01ED537E = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2BB0:
                    *(s8 *)0x01ED537C = 0x11;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x90C;
                    *(s8 *)0x01ED537E = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2EE0:
                    *(s8 *)0x01ED537C = 0x17;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x91D;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    switch (*(s8 *)0x01ED537D) {
                    case 4:
                        *(s8 *)0x01ED537E = 2;
                        *(s16 *)0x01ED53BC = 0xC4;
                        *(s8 *)0x01ED53BF = 0;
                        *(s8 *)0x01ED53B4 = 1;
                        *(s8 *)0x01ED5469 = 2;
                        break;
                    default:
                        *(s8 *)0x01ED537E = 3;
                        *(s16 *)0x01ED53BA = 0xC5;
                        *(s8 *)0x01ED53BE = 1;
                        *(s8 *)0x01ED53B5 = 1;
                        if (*(s8 *)0x01ED537D >= 4) {
                            *(s8 *)0x01ED5469 = 2;
                        }
                        break;
                    }
                    if (*(s8 *)0x01ED537D >= 5) {
                        *(s8 *)0x01ED53B5 = 0;
                        return ret;
                    }
                    break;
                case 0x2F08:
                    *(s8 *)0x01ED537C = 1;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x942;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xD2;
                    *(s8 *)0x01ED53BF = 0;
                    *(s8 *)0x01ED53B5 = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2F09:
                    *(s8 *)0x01ED537C = 6;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x943;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xD2;
                    *(s8 *)0x01ED53BF = 0;
                    *(s8 *)0x01ED53B5 = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2F62:
                    *(s8 *)0x01ED537C = 3;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x970;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xC5;
                    *(s8 *)0x01ED53BF = 1;
                    *(s8 *)0x01ED53B5 = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2F64:
                    *(s8 *)0x01ED537C = 0xF;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x973;
                    temp_v1_5 = *(s16 *)0x01ED5378;
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
                        *(s8 *)0x01ED537E = 3;
                        *(s16 *)0x01ED53BA = 0xD8;
                        *(s8 *)0x01ED53BE = 0;
                        *(s8 *)0x01ED53B4 = 1;
                        break;
                    default:
                        *(s8 *)0x01ED537E = 2;
                        *(s16 *)0x01ED53BC = 0xC5;
                        *(s8 *)0x01ED53BF = 1;
                        *(s8 *)0x01ED53B5 = 1;
                        break;
                    }
                    temp_a0_6 = *(s16 *)0x01ED5378;
                    switch (temp_a0_6) {
                    case 0x974:
                        *(s8 *)0x01ED546A = 0;
                        *(s8 *)0x01ED5469 = 0;
                        return ret;
                    case 0x97A:
                        *(s8 *)0x01ED546A = 0;
                        *(s8 *)0x01ED5469 = 2;
                        return ret;
                    }
                    break;
                case 0x2F76:
                    *(s8 *)0x01ED537C = 2;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x988;
                    *(s8 *)0x01ED537E = 3;
                    *(s16 *)0x01ED53BA = 0xD8;
                    *(s8 *)0x01ED53BE = 0;
                    *(s8 *)0x01ED53B4 = 1;
                    if (*(s8 *)0x01ED537D != 1) {
                        return ret;
                    }
                    *(s8 *)0x01ED546A = 2;
                    *(s8 *)0x01ED5469 = 2;
                    return ret;
                case 0x2F78:
                    *(s8 *)0x01ED537C = 0x11;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x98A;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xC5;
                    *(s8 *)0x01ED53BF = 1;
                    *(s8 *)0x01ED53B4 = 0;
                    *(s8 *)0x01ED53B5 = 1;
                    if (*(s8 *)0x01ED537D != 1) {
                        return ret;
                    }
                    *(s8 *)0x01ED546A = 2;
                    *(s8 *)0x01ED5469 = 2;
                    return ret;
                case 0x2F7A:
                    *(s8 *)0x01ED537C = 6;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x99B;
                    *(s8 *)0x01ED537E = 2;
                    *(s16 *)0x01ED53BC = 0xC5;
                    *(s8 *)0x01ED53BF = 1;
                    *(s8 *)0x01ED53B5 = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                case 0x2F7C:
                    *(s8 *)0x01ED537C = 0xE;
                    *(s16 *)0x01ED5378 = *(s8 *)0x01ED537D + 0x9A1;
                    *(s8 *)0x01ED537E = 1;
                    *(s8 *)0x01ED546A = 0;
                    *(s8 *)0x01ED5469 = 0;
                    return ret;
                }
            }
    }
    return ret;
}
