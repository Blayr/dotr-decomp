#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* Prototypes of every decompiled function. dk rewrites this file. */
void func_001000C0(void);
s32 func_001001D0(void); /* JP: Main_Init */
s32 func_00100350(void); /* JP: lMain_InitModel2 */
void func_001004C0(void); /* JP: Main_Term */
void func_00100520(void); /* JP: Main_Loop */
void func_00100560(void); /* JP: Main_LoopProc */
void func_00100610(s32 arg0);
void func_00100780(void); /* JP: lMain_LoadModel */
s32 func_00100820(void); /* JP: Main_VSync */
void func_00100850(void); /* JP: Main_Draw (matched by position) */
void func_00100B00(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: GRotTransPers_3 */
void func_00100BA0(void *arg0, void *arg1, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: GRotTransPers_4 */
void func_00100C60(void *arg0, void *arg1, s32 arg2, s32 arg3); /* JP: GSet_WindowUv */
s32 func_00100D00(s32 arg0); /* JP: GGet_ModelPosZSign */
f32 func_00100D50(s32 arg0, s32 arg1, s32 arg2); /* JP: GCalc_Trans */
void func_00100E00(s32 arg0, s32 arg1, s32 arg2); /* JP: GRot_Matrix */
void func_00100E40(void *matrix, f32 *vector); /* JP: GVec2RotMat_Z */
f32 func_00100FF0(f32 fparg0, f32 fparg1, f32 fparg2); /* JP: GCalc_Decrease */
f32 func_00101020(f32 fparg0, f32 fparg1); /* JP: GCalc_Increase */
s32 func_00101050(s32 arg0, s32 arg1, s32 arg2); /* JP: GWithin_LimitsI */
void func_00101080(f32 *vector, f32 scale); /* JP: GSet_RandVector */
s32 func_00101430(void *arg0, void *arg1, void *arg2); /* JP: GJudge_FrontBack2 */
s32 func_00101600(void *arg0); /* JP: ShFx_isClip */
s32 func_00101770(void *arg0); /* JP: ShFx_isClipSC */
f32 func_001018E0(f32 fparg0, f32 fparg1); /* JP: ShFx_GetDrawSize */
void func_00101940(f32 *arg0, s32 *arg1); /* JP: ShFx_Vec2Rot */
void func_00101A00(f32 *src, void *dst); /* JP: ShFx_Vec2Mat */
void func_00101AD0(s8 *arg0, s8 arg1, s8 arg2, s8 arg3); /* JP: ShFx_initTimer */
s32 func_00101AF0(void *arg0); /* JP: ShFx_isTimer */
void func_00101B40(void *arg0, s8 arg1, s8 arg2); /* JP: ShFx_initPartsTimer */
s32 func_00101B50(void *arg0); /* JP: ShFx_isPartsTimer */
void func_00101BA0(void *arg0, s32 arg1); /* JP: ShFx_AdjustPoint */
s32 func_00101C30(u8 *arg0, s32 arg1, s32 arg2); /* JP: ShFx_GetTempIndex */
void func_00101C80(void *arg0, void *arg1); /* JP: ShFx_GetAlpha */
void func_00101D20(void *arg0, void *arg1, void *arg2); /* JP: ShFx_SetTexFT4 */
void func_00101EE0(void *arg0, void *arg1, void *arg2); /* JP: ShFx_SetTexGT4 */
void func_001020B0(s32 *rect, s32 index, u32 mode, s32 width); /* JP: ShFx_SetUV */
void func_00102210(u32 arg0, s32 *arg1, s32 *arg2); /* JP: ShFx_GetTexWidth */
s32 func_001022D0(u32 arg0, s32 arg1); /* JP: ShFx_GetAnmID */
void func_00102330(s8 *arg0, s32 arg1); /* JP: ShFx_MakeRnd */
void func_00102390(s32 n, f32 *x, f32 *y, f32 *y2); /* JP: ShFx_Spline_MakeTable */
s32 func_00102550(void *arg0); /* JP: ShFx_Spline */
void func_00102A50(void *arg0); /* JP: ShFx_Vib2P */
void func_00102CB0(void *arg0); /* JP: ShFx_Spin2P */
void func_00102F20(void *arg0); /* JP: ShFx_Hsin2P */
void func_001031C0(u16 *arg0, s32 arg1); /* JP: ShFx_BlackBG */
s32 func_00103260(s32 *arg0); /* JP: LkInitTex2 */
s32 func_00103290(s32 *arg0); /* JP: LkInitTexBtl */
s32 func_001032C0(u8 *arg0, u8 arg1, u8 arg2); /* JP: LkIncrBYTE */
s32 func_00103300(s16 *arg0, s32 arg1, s32 arg2); /* JP: LkIncrSHORT */
s32 func_00103350(s32 *arg0, s32 arg1, s32 arg2); /* JP: LkIncrINT */
s32 func_00103390(f32 *arg0, f32 fparg0, f32 fparg1); /* JP: LkIncrFLOAT */
s32 func_001033D0(f32 *values, f32 target, f32 step); /* JP: LkIncrVec */
s32 func_00103470(u8 *arg0, u8 arg1, s32 arg2); /* JP: LkDecrBYTE */
s32 func_001034B0(s16 *arg0, s16 arg1, s16 arg2); /* JP: LkDecrSHORT */
s32 func_00103500(s32 *arg0, s32 arg1, s32 arg2); /* JP: LkDecrINT */
s32 func_00103540(f32 *arg0, f32 fparg0, f32 fparg1); /* JP: LkDecrFLOAT */
s32 func_00103580(void *arg0, f32 fparg0, f32 fparg1); /* JP: LkDecrVec */
void func_00103620(void *arg0, void *arg1); /* JP: LkAddVector */
void func_00103660(void *arg0, void *arg1); /* JP: LkSubVector */
void func_001036A0(void *arg0, void *arg1); /* JP: LkMulVector */
void func_001036E0(f32 *arg0, f32 *arg1, f32 *arg2); /* JP: LkGetCenter */
void func_00103760(void *arg0); /* JP: LkSetAngleXY_m90 */
s32 func_001037C0(u8 *arg0, s32 arg1, s32 arg2); /* JP: LkSetAngleW2S */
void func_00103890(void *arg0); /* JP: LkInitCoordinate */
void func_001038D0(void *arg0); /* JP: LkSetCoordinate */
s32 func_00103920(void *arg0, f32 fparg0, f32 fparg1); /* JP: LkChange2D */
s32 func_001039A0(void *arg0); /* JP: LkRotSF */
s32 func_00103A30(f32 *arg0, s32 *arg1); /* JP: LkVec2Rot */
s32 func_00103B50(f32 *arg0, s32 *arg1); /* JP: LkVec2RotXY */
s32 func_00103C40(Vec4f *arg0, void *arg1); /* JP: LkVec2Mat */
s32 func_00103D00(s32 arg0, s32 arg1); /* JP: LkRegulateRotBorder */
s32 func_00103DB0(f32 *arg0, f32 *arg1, s32 *arg2); /* JP: LkChangeAxisY */
s32 func_00103EC0(f32 *position, f32 *target, f32 *velocity, s32 limit); /* JP: LkMoveHoming */
s32 func_001043F0(void *arg0, f32 fparg0); /* JP: LkGetRandVec */
void func_00104490(f32 *arg0, f32 *arg1, s32 arg2); /* JP: LkOBJ_TransitVector */
s32 func_00104520(s32 arg0, s32 arg1); /* JP: LkCheckFlag */
s32 func_00104540(void *arg0, void *arg1, s32 arg2); /* JP: LkAssignUV */
void func_00104DC0(void *arg0, void *arg1); /* JP: LkAssignUVST */
void func_00105260(void *arg0, void *arg1, s32 arg2); /* JP: LkAssignUVST3 */
void func_00105830(void *arg0, void *arg1, s32 arg2); /* JP: LkAssignUV2 */
s32 func_00105C40(void *arg0); /* JP: LkAssignFrameST */
void func_00105D00(void *dst, s16 kind, s16 index); /* JP: RH2_DATA_IN */
void func_00106080(void *arg0, s16 arg1, s16 arg2); /* JP: RH2_DATA_IN2 */
s32 func_00106A00(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SHOKI_OBJ */
void func_00106AB0(s16 *arg0, f32 *arg1, s32 arg2); /* JP: PV_IN_ */
void func_00106B50(void *arg0, void *arg1); /* JP: POS_POS */
s32 func_00106B90(void *arg0, s32 arg1, s32 arg2); /* JP: OBJECT_RGB_A_OFF */
s32 func_00106BC0(void *arg0, s32 arg1, s32 arg2); /* JP: OBJECT_RGB_A_ON */
s32 func_00106BF0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: OBJECT_RGB_INOFF */
s32 func_00106C50(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: OBJECT_RGBA_INOFF */
s32 func_00106CC0(s32 arg0, s32 arg1); /* JP: OBJ_ADDRESS_IN */
s32 func_00106CF0(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: XC_ZS_IN */
s32 func_00106D80(s32 arg0, s16 *arg1); /* JP: RAD_IN_360_ */
void func_00106DD0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2); /* JP: OBJ_SCL2 */
void func_00106DE0(f32 x, f32 y, f32 z, s32 *out); /* JP: OBJ_ROT */
void func_00106E40(s32 *dst, f32 *src); /* JP: OBJ_I_V_IN */
void func_00106E90(void *arg0, void *arg1); /* JP: OBJ_VE_SCL_KAKE */
void func_00106ED0(void *arg0, void *arg1); /* JP: OBJ_VE_SCL_KAKE_4 */
void func_00106FA0(f32 *dst, f32 *src); /* JP: POS_POS_4 */
s32 func_00107070(void *arg0, s64 arg1, f32 fparg0); /* JP: XYZ_POS_4 */
s32 func_00107130(void *arg0, void *arg1, s32 arg2); /* JP: POINT_IN_VECTOR_ */
s32 func_00107180(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: MODEL_OFF */
s32 func_00107280(s32 arg0); /* JP: CARD_OFF */
s32 func_00107310(s32 arg0, s32 arg1, s32 arg2); /* JP: MODEL_ON */
s32 func_00107370(s32 arg0, f32 fparg0); /* JP: MODEL_SCL_ON_1 */
s32 func_00107450(s32 arg0, f32 fparg0); /* JP: MODEL_SCL_OFF_1 */
s32 func_00107510(s32 arg0, f32 fparg0); /* JP: CARD_SCL_ON_1 */
s32 func_00107650(s32 arg0, s32 arg1); /* JP: CARD_ON */
s32 func_001076F0(void *arg0, s8 arg1, s8 arg2, s8 arg3); /* JP: OBJ_RGB_IN */
s32 func_00107710(u8 *arg0, u8 *arg1); /* JP: OBJ_GsRGB_RGB_IN */
void func_00107740(void *arg0, void *arg1); /* JP: OBJ_GsRGB_RGB_IN2 */
s32 func_00107790(void *arg0, u8 *arg1, s32 arg2); /* JP: GT4_IN_RGBA */
s32 func_00107990(void *arg0, u8 *arg1, s32 arg2); /* JP: G4_IN_RGBA */
void func_00107B90(f32 *arg0, f32 *arg1, void *arg2, void *arg3); /* JP: CARD_X_Z_IN_ */
void func_00107C10(f32 *arg0); /* JP: SIN_IN_PSYS */
void func_00107CB0(void *arg0, s32 arg1, s32 arg2); /* JP: SIN_IN_PSYS2 */
s32 func_00107DD0(void *arg0, void *arg1, void *arg2); /* JP: V0IN_V1_V2_XZ */
s32 func_00107E40(f32 fparg0, f32 fparg1, f32 fparg2, void *arg0); /* JP: OBJ_RR2H_IN */
s32 func_00107EA0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2); /* JP: PSYS_RR2H_IN */
s32 func_00107EC0(u8 *arg0, s32 arg1, s16 arg2); /* JP: OBJ_GsRGB_RGB_IN_DATA */
f32 func_00108030(s32 arg0, s32 arg1, s32 arg2); /* JP: SIN_COS_INRAD */
s32 func_001082B0(s64 x, s64 y); /* JP: tanD_360_ */
void func_00108500(void *arg0, void *arg1, s32 arg2); /* JP: POLPAN_UVIN_ */
void func_00108BE0(void *arg0, void *arg1, s64 arg2, f32 arg3, f32 arg4); /* JP: RAD_XYZ_IN */
s32 func_00108CE0(void *arg0, f32 fparg0, f32 fparg1); /* JP: PAINT_VECTOR_4TG_SET_IN */
s32 func_00108D20(void *dst, f32 x, f32 z); /* JP: PAINT_VECTOR_4TG_SET_IN2 */
s32 func_00108D60(void *arg0, s32 arg1, s32 arg2, s16 arg3); /* JP: PAINT_VECTOR_4TG_SET_INMAP4 */
void func_00108EF0(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: S_I_P_IN */
s32 func_00108F90(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: PAINT_PIRM_G4 */
s32 func_00108FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: PAINT_PIRM_GT4 */
s32 func_00109050(s32 arg0, void *arg1, s32 arg2, s32 arg3); /* JP: PAINT_PIRM_LG2 */
s32 func_00109100(u8 *arg0, void *arg1, s32 arg2, s32 arg3); /* JP: MATRIX_XYZ_ININ_4 */
s32 func_001091B0(void *arg0, void *arg1, void *arg2); /* JP: PAINT__2G_SET_IN */
s32 func_00109270(void *arg0); /* JP: PAINT__GT4_SET_IN */
s32 func_001092E0(void *arg0, s32 arg1); /* JP: PAINT__G4_SET_IN */
s32 func_00109380(void *arg0, s32 arg1); /* JP: GT4_Xyz_ZIN */
s32 func_001094F0(void *arg0); /* JP: G4_BOX_IN__ */
s32 func_001095D0(void *arg0, void *arg1, void *arg2); /* JP: GT4_BOX_IN__2DMAP */
void func_001098E0(void *out, f32 *offset, f32 *point, f32 *a, f32 *b); /* JP: ATARI3 */
void func_001099E0(void *arg0, void *arg1, void *arg2, f32 fparg0); /* JP: Card_V_IN */
s32 func_00109A70(void *arg0, void *arg1); /* JP: VEC_POI_IN */
void func_00109A90(void); /* JP: SD_InitializeDevice */
s32 func_00109CA0(s32 arg0); /* JP: SD_Init */
void func_00109D50(void); /* JP: SD_Term */
void func_00109D70(s32 arg0); /* JP: SD_SuspendSoundSystem */
void func_00109DC0(void); /* JP: SD_CallEveryVSync */
s32 func_00109E80(s32 arg0, s32 arg1); /* JP: SD_BGMPreLoad */
s32 func_00109F10(void); /* JP: SD_IsLoadingNow */
void func_00109F60(s32 arg0); /* JP: SD_SetOutputType */
void func_00109FC0(void); /* JP: SD_StopAll */
void func_0010A010(void); /* JP: SD_BGMStop */
void func_0010A090(s16 arg0); /* JP: SD_BGMFadeOut */
s32 func_0010A0F0(void); /* JP: SD_BGMGetVolume */
void func_0010A160(s32 arg0, s32 arg1); /* JP: SD_BGMSetSourceLevel */
void func_0010A1D0(s32 arg0, s32 arg1, s32 arg2); /* JP: SD_SEPlay2 */
void func_0010A280(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: SD_SEPlayWithParam6 */
void func_0010A390(s32 arg0, s32 arg1, s32 arg2); /* JP: SD_SEPlayOnlyOnce */
void func_0010A3B0(s32 arg0, s32 arg1); /* JP: SD_SEStop */
void func_0010A450(void); /* JP: SD_SEStopAll */
void func_0010A4D0(void); /* JP: SD_vRunAmbienceOnIopProc (matched by position) */
s32 func_0010A780(s32 arg0); /* JP: _iDecodeLPCM */
s32 func_0010A8A0(void); /* JP: SD_iGetSDStatus */
void func_0010A8B0(void); /* JP: SD_vInitializeFileHandler */
void func_0010A8D0(s32 arg0, s32 arg1, s32 arg2); /* JP: _vLoadBGMFileToEE */
void func_0010AC20(s32 arg0); /* JP: _vDecodeLPCMThenSendToIOP */
void func_0010ADB0(void); /* JP: SD_vAutoDMASequentialWatchDog */
s32 func_0010B1F0(void); /* JP: SD_iStartAutoDMA */
s32 func_0010B270(void); /* JP: SD_iStopAutoDMA */
void func_0010B330(void); /* JP: SD_vInitSDThread */
void func_0010B360(void); /* JP: SD_vInitializeAutoDMA */
s32 func_0010B3C0(s32 value); /* JP: SD_iPreparePreBlockOnIOP */
s32 func_0010B490(s32 id); /* JP: SD_iPlayBGMByAutoDMA */
void func_0010B6C0(void); /* JP: SD_vTransferSEGrpToIopProc (matched by position) */
s32 func_0010BBC0(void); /* JP: SD_iTransferSEGrpToIop */
void func_0010BC30(s32 arg0, s32 arg1); /* JP: SD_KickSEGroupReadSequence */
s32 func_0010BCC0(s32 value, void *src); /* JP: SD_AddToXferQueue */
s32 func_0010BD40(s32 *arg0, void *arg1); /* JP: SD_FetchFromXferQueue */
void func_0010BDC0(void); /* JP: SD_ClearXferQueue */
s32 func_0010BDE0(void); /* JP: SD_DoesExistAnyCDReq */
s32 func_0010BE20(void); /* JP: SD_DoesExistAnySIFReq */
void func_0010BE60(void); /* JP: SD_vDoFsCommandQueue */
void func_0010C110(void *arg0, void *arg1, s32 arg2, s32 arg3); /* JP: SD_AddReadToEeReq */
void func_0010C220(s32 arg0, s32 arg1, s32 arg2); /* JP: SD_AddEeToIopReq */
s32 func_0010C290(void); /* JP: SD_IsAnyJobOnCD */
s32 func_0010C2C0(void); /* JP: SDFS_IsUsingNow */
s32 func_0010C2D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SDFS_ReadToEE */
s32 func_0010C3D0(s32 file, s32 destination, s32 position, s32 size); /* JP: SDFS_ReadToEEBlock */
void func_0010C580(void); /* JP: lSDFS_FinishCallback */
s32 func_0010C720(s32 cmd, ...); /* JP: SDRPC_SendCommand */
s32 func_0010C800(s32 arg0, s32 arg1, s32 arg2); /* JP: SDRPC_StartTransferToIop */
s32 func_0010C8A0(void); /* JP: SDRPC_TranserToIopStatus */
s32 func_0010C8B0(void); /* JP: SDRPC_Init (matched by position) */
s32 func_0010C940(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_0010CE20(u16 *arg0, u16 *arg1); /* JP: TaLogic_CommandUnit */
s32 func_0010D080(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_0010D490(void *arg0, s32 arg1, u8 arg2); /* JP: TaLogic_CommandBtlUnit */
void func_0010D820(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic002_GetNearUnit */
void func_0010D880(void *arg0, s32 arg1, u8 arg2); /* JP: TaLogic_CommandEfcMonster */
void func_0010DB00(void *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_CommandDefenseUnit */
void func_0010DC40(void *arg0); /* JP: TaLogic002_CommandMagicUnit */
s32 func_0010DD50(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_0010DFC0(s32 arg0, void *arg1); /* JP: TaLogic_IsHandPlay */
s32 func_0010E320(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic_SetComboQue */
s32 func_0010E540(s32 arg0, void *arg1, s32 arg2, s32 arg3); /* JP: TaLogic_SetSpecialComboQue */
void func_0010E6B0(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_0010ED90(s32 arg0, u32 arg1); /* JP: TaLogic_GetSommonPiecePreference */
s32 func_0010EDA0(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_0010EE00(s32 arg0, s32 arg1, u32 *arg2); /* JP: TaLogic_IsOpenUnit */
s32 func_0010F030(void); /* JP: TaLogic002_IsActiveMode */
s32 func_0010F220(s32 arg0); /* JP: TaLogic002_IsRefuseEmptyCombo */
s32 func_0010F450(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic002_GetSpellPlay */
s32 func_0010F6F0(s32 arg0); /* JP: TaLogic002_IsMakeDefense */
s32 func_0010F850(s32 arg0, s32 arg1); /* JP: TaLogic002_GetLinePiece */
s32 func_0010F940(s32 arg0, s32 arg1); /* JP: TaLogic002_IsDoCerem */
s32 func_0010FA60(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_0010FFF0(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_001106F0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_00110F00(s32 arg0, void *arg1); /* JP: L002 */
s32 func_001110D0(s32 arg0); /* JP: TaLogicCom_GetRevoltObj */
s32 func_00111320(s32 arg0, s32 arg1); /* JP: TaLogicCom_IsOpenUnit */
s32 func_001123C0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogicCom_IsUseObjEffect */
s32 func_00112600(s32 arg0, s32 *arg1); /* JP: TaLogicCom_GetUseXYRangeSpell */
s32 func_00112850(s32 arg0, s32 arg1); /* JP: TaLogicCom_IsDoCerem */
s32 func_00112960(s32 arg0); /* JP: TaLogicCom_IsExzParts */
s32 func_00112980(s32 arg0); /* JP: TaLogic_IsTactixExz */
s32 func_00112A40(s32 arg0); /* JP: TaLogic_IsExzodia */
s32 func_00112B90(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_00113140(void *arg0, s32 arg1); /* JP: TaLogic_CommandUnit */
s32 func_00113370(u16 *arg0, s32 arg1, s32 arg2, void *arg3); /* JP: TaLogic_GetNextActiveUnit */
void func_00113760(void *arg0, s32 arg1, s32 arg2); /* JP: TaLogic001_CommandBtlUnit */
void func_00113A00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic001_GetNearUnit */
void func_00113A60(void *arg0); /* JP: TaLogic001_CommandInvadeUnit */
s32 func_00113B60(s32 arg0, s32 arg1); /* JP: TaLogic001_GetNextGrassPoint */
void func_00113BB0(void *arg0, s32 arg1); /* JP: TaLogic001_CommandEfcMonster */
void func_00113ED0(void *arg0); /* JP: TaLogic001_CommandSpellUnit */
s32 func_00114080(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_00114310(s32 arg0, void *arg1); /* JP: TaLogic001_IsHandPlay */
s32 func_001146C0(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic001_GetSpecCardPlay */
s32 func_001147B0(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic001_GetProtectCardPlay */
s32 func_00114B40(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic001_GetSpellPlay */
s32 func_00114D40(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic001_SetComboQue */
void func_00114F20(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_00115100(s32 arg0); /* JP: TaLogic001_IsRefuseEmptyCombo */
s32 func_00115160(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic001_SetSpecialComboQue */
s32 func_00115340(s32 arg0, u8 arg1, void *arg2, s32 arg3); /* JP: TaLogic001_GetSummonPiece */
s32 func_00115850(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00115E20(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_001162F0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_00116B60(void *arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic_GetMinimumTask_TrapMission */
s32 func_001170A0(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_ReviveMission */
s32 func_00117340(void); /* JP: TaLogic001_IsActiveMode */
s32 func_001173E0(s32 arg0); /* JP: TaLogic001_IsUseLifeHourGlass */
s32 func_00117550(s32 arg0); /* JP: TaLogic001_IsUseBraveHourGlass */
s32 func_00117600(s32 arg0); /* JP: TaLogic001_IsUseLordOfDragon */
s32 func_00117680(s32 arg0); /* JP: TaLogic001_IsUseRevive */
s32 func_00117B10(s32 arg0); /* JP: TaLogic001_IsLandNearCntr */
s32 func_00117BD0(s32 arg0, s32 arg1); /* JP: TaLogic001_IsDoCerem */
s32 func_00117C30(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_00117C90(s32 arg0, void *arg1); /* JP: L001 */
s32 func_00117E60(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_00118330(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_00118510(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_001188F0(void *arg0, s32 arg1); /* JP: TaLogic_CommandBtlUnit */
void func_00118B60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic003_GetNearUnit */
void func_00118BC0(void *arg0); /* JP: TaLogic003_CommandAtkLineUnit */
s32 func_00118CE0(s32 arg0, s32 arg1); /* JP: TaLogic003_IsEmptyAtkLine */
s32 func_00118DD0(s32 arg0); /* JP: TaLogic003_GetEmptyAtkLineStart */
s32 func_00118E90(s32 arg0); /* JP: TaLogic003_GetEmptyAtkLineEnd */
void func_00118F50(void *arg0); /* JP: TaLogic_CommandTrapUnit */
s32 func_00119300(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_00119520(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogic003_GetSummonPiece */
s32 func_00119A40(s32 arg0, void *arg1); /* JP: TaLogic_IsHandPlay */
s32 func_00119D30(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic003_GetSpellPlay */
s32 func_00119F30(s32 arg0, void *arg1, s32 arg2); /* JP: TaLogic003_IsSpellPlay */
s32 func_0011A0D0(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic_SetComboQue */
void func_0011A2F0(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_0011A4C0(s32 arg0, u32 arg1); /* JP: TaLogic_GetSommonPiecePreference */
s32 func_0011A4D0(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_0011AA10(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_0011AA70(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_0011B0E0(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_TrapMission */
s32 func_0011B680(u32 *arg0, s32 arg1, u16 *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_0011C140(s32 arg0, s32 arg1, u32 *arg2); /* JP: TaLogic_IsOpenUnit */
s32 func_0011C2E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic003_IsOpenMoveUnit */
void func_0011C3E0(void *arg0, u8 arg1); /* JP: TaLogic003_InitRogicControl */
s32 func_0011C430(s32 arg0, void *arg1); /* JP: L003 */
s32 func_0011C600(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_0011CB20(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_0011CD30(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_0011D110(void *arg0, s32 arg1); /* JP: TaLogic_CommandBtlUnit */
void func_0011D380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic004_GetNearUnit */
void func_0011D3E0(void *arg0); /* JP: TaLogic004_CommandAtkLineUnit */
void func_0011D4E0(s32 arg0, s32 arg1, s32 arg2, void *arg3); /* JP: TaLogic004_GetNearAtkLineEdge */
s32 func_0011D6D0(s32 arg0, s32 arg1); /* JP: TaLogic004_IsUnitOnLine */
s32 func_0011D7B0(s32 arg0, u8 arg1); /* JP: TaLogic004_IsEmptyAtkLine */
s32 func_0011D8D0(s32 arg0, s32 arg1); /* JP: TaLogic004_GetAtkLineStart */
s32 func_0011D940(s32 arg0, s32 arg1); /* JP: TaLogic004_GetAtkLineEnd */
void func_0011D9B0(void *arg0, s32 arg1); /* JP: TaLogic_CommandEfcMonster */
void func_0011DC00(void *arg0); /* JP: TaLogic_CommandTrapUnit */
s32 func_0011DFB0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_0011E270(s32 arg0, u8 arg1, void *arg2); /* JP: TaLogic004_GetSummonPiece */
s32 func_0011E6E0(s32 arg0, void *arg1); /* JP: TaLogic_IsHandPlay */
s32 func_0011EB10(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaLogic004_GetSpecialComboPlay */
s32 func_0011ED50(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic004_GetSpellPlay */
s32 func_0011EF60(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic_SetComboQue */
void func_0011F150(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_0011F330(s32 arg0); /* JP: TaLogic004_IsRefuseEmptyCombo */
s32 func_0011F3C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaLogic_SetSpecialComboQue */
s32 func_0011F530(s32 arg0, u32 arg1); /* JP: TaLogic_GetSommonPiecePreference */
s32 func_0011F540(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_0011FA80(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_0011FAE0(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_00120150(void *arg0, s32 card, void *arg2, u8 kind); /* JP: TaLogic_GetMinimumTask_TrapMission */
s32 func_001206F0(u32 *arg0, s32 arg1, u16 *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_001211B0(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogic_IsOpenUnit */
s32 func_001214E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: TaLogic004_IsOpenMoveUnit */
void func_001215E0(void *arg0, u8 arg1); /* JP: TaLogic004_InitRogicControl */
s32 func_00121630(s32 arg0, void *arg1); /* JP: L004 */
s32 func_00121800(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_00121CE0(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_00121E90(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_00122270(void *arg0, s32 arg1); /* JP: TaLogic_CommandBtlUnit */
void func_001224D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic005_GetNearUnit */
void func_00122530(void *arg0); /* JP: TaLogic005_CommandRoutineUnit */
s32 func_00122680(s32 arg0, s32 arg1); /* JP: TaLogic005_GetUnitOnCycleRoot */
s32 func_00122810(s32 arg0, s32 arg1); /* JP: TaLogic005_GetNearCyclePoint */
s32 func_00122970(s32 arg0); /* JP: TaLogic_GetCyclePoint */
void func_001229F0(void *arg0, s32 arg1); /* JP: TaLogic_CommandEfcMonster */
void func_00122B50(void *arg0); /* JP: TaLogic005_CommandTrapBUnit */
s32 func_00122D30(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_00123010(s32 arg0, u8 arg1, void *arg2, s32 arg3); /* JP: TaLogic005_GetSummonPiece */
void func_00123500(s32 arg0, s32 arg1, s32 arg2, void *arg3); /* JP: TaLogic005_GetNearDefensePoint */
s32 func_00123670(s32 arg0); /* JP: TaLogic005_GetDefensePoint */
s32 func_001236C0(s32 arg0); /* JP: TaLogic005_IsEmptyDefensePoint */
s32 func_00123740(s32 player, void *output); /* JP: TaLogic_IsHandPlay */
s32 func_00123D70(s32 arg0, s32 *arg1); /* JP: TaLogic005_Is2Head_ThunderDragon */
s32 func_00123F90(s32 arg0, s32 *arg1, s32 arg2); /* JP: TaLogic005_IsKeepHandCombo */
s32 func_00124040(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic005_GetSpecialSpellPlay */
s32 func_00124520(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic005_GetSpecialCardPlay */
s32 func_00124610(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic005_GetSpellPlay */
s32 func_00124810(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic005_SetComboQue */
void func_00124A30(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_00124C10(s32 arg0); /* JP: TaLogic005_IsRefuseEmptyCombo */
s32 func_00124C90(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic_SetSpecialComboQue */
s32 func_00124F50(s32 arg0, u32 arg1); /* JP: TaLogic_GetSommonPiecePreference */
s32 func_00124F60(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_001254A0(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_00125500(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_00125B70(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_00126380(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogic_IsOpenUnit */
s32 func_00126840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic005_IsOpenMoveUnit */
void func_00126940(void *arg0, u8 arg1); /* JP: TaLogic005_InitRogicControl */
s32 func_001269C0(s32 arg0, s32 arg1); /* JP: TaLogic005_IsDoCerem */
s32 func_00126AB0(s32 arg0, void *arg1); /* JP: L005 */
s32 func_00126C80(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_001271F0(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_001273E0(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_001277C0(void *arg0, s32 arg1); /* JP: TaLogic006_CommandBtlUnit */
void func_00127A30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic006_GetNearUnit */
void func_00127A90(void *arg0); /* JP: TaLogic006_CommandInvadeUnit */
void func_00127B00(void *arg0); /* JP: TaLogic006_CommandEfcMonster */
void func_00127D20(void *arg0); /* JP: TaLogic006_CommandSpellUnit */
s32 func_00127E30(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_001280C0(s32 arg0, void *arg1); /* JP: TaLogic006_IsHandPlay */
s32 func_00128430(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic006_GetSpecCardPlay */
s32 func_00128520(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic006_GetSpellPlay */
s32 func_00128720(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic006_SetComboQue */
void func_00128900(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_00128AE0(s32 arg0); /* JP: TaLogic006_IsRefuseEmptyCombo */
s32 func_00128B50(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic006_SetSpecialComboQue */
s32 func_001291C0(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00129700(void *arg0, s32 arg1, s32 arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_ReviveMission */
s32 func_00129D00(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_0012A2E0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_0012AAC0(void *arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic_GetMinimumTask_TrapMission */
void func_0012B000(void);
s32 func_0012B1B0(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_0012B210(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogic_IsOpenUnit */
s32 func_0012B730(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic006_IsOpenMoveUnit */
void func_0012B830(void *arg0, u8 arg1); /* JP: TaLogic006_InitRogicControl */
s32 func_0012B8B0(s32 arg0, s32 arg1); /* JP: TaLogic006_IsDoCerem */
s32 func_0012B9A0(s32 arg0, void *arg1); /* JP: L006 */
s32 func_0012BB70(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_0012C1A0(void *arg0, s32 arg1); /* JP: TaLogic_CommandUnit */
s32 func_0012C3F0(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_0012C7F0(void *arg0, s32 arg1, s32 arg2); /* JP: TaLogic007_CommandBtlUnit */
void func_0012CB80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic007_GetNearUnit */
void func_0012CBE0(void *arg0, s32 arg1); /* JP: TaLogic007_CommandEfcMonster */
void func_0012CE50(void *arg0); /* JP: TaLogic_CommandTrapUnit */
s32 func_0012D270(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_0012D520(s32 arg0, void *arg1, s32 arg2); /* JP: TaLogic007_IsHandPlay */
s32 func_0012D960(s32 arg0, s32 *arg1, void *arg2, void *arg3); /* JP: TaLogic007_GetCurseCardPlay */
s32 func_0012DAE0(s32 arg0, s32 *arg1, void *arg2, void *arg3, s32 arg4); /* JP: TaLogic007_GetSpecCardPlay */
s32 func_0012DBE0(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic007_GetSpellPlay */
s32 func_0012DDE0(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic007_SetComboQue */
void func_0012DFC0(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_0012E1A0(s32 arg0); /* JP: TaLogic007_IsRefuseEmptyCombo */
s32 func_0012E1F0(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic007_SetSpecialComboQue */
s32 func_0012E3F0(s32 arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic007_GetSummonPiece */
s32 func_0012E820(u16 *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_0012ED70(void *arg0, s32 arg1, s32 arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_ReviveMission */
s32 func_0012F350(void *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_0012F930(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4, u8 arg5); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_00130120(void *arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic_GetMinimumTask_TrapMission */
s32 func_00130660(s32 arg0); /* JP: TaLogic007_IsRevivePlay */
s32 func_00130780(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_001307E0(s32 arg0, s32 arg1); /* JP: TaLogic007_IsDoCerem */
s32 func_00130940(s32 arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic_IsOpenUnit */
s32 func_00130BB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic007_IsOpenMoveUnit */
s32 func_00130CB0(void); /* JP: TaLogic007_IsActiveMode */
s32 func_00130E90(s32 arg0, void *arg1); /* JP: L007 */
s32 func_00131060(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_00131540(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_00131750(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_00131B30(void *arg0, s32 arg1); /* JP: TaLogic008_CommandBtlUnit */
void func_00131DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic008_GetNearUnit */
void func_00131E40(void *arg0); /* JP: TaLogic008_CommandInvadeUnit */
s32 func_00131F80(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic008_GetNextInvadePoint */
void func_00132280(u16 *arg0); /* JP: TaLogic008_CommandSpellUnit */
s32 func_00132460(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_001326F0(s32 arg0, void *arg1); /* JP: TaLogic008_IsHandPlay */
s32 func_00132A10(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic008_GetSpecCardPlay */
s32 func_00132B00(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic008_GetSpellPlay */
s32 func_00132D00(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic008_SetComboQue */
void func_00132EE0(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_001330C0(s32 arg0); /* JP: TaLogic008_IsRefuseEmptyCombo */
s32 func_00133130(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic008_SetSpecialComboQue */
s32 func_00133320(s32 arg0, u8 arg1, void *arg2, s32 arg3); /* JP: TaLogic008_GetSummonPiece */
s32 func_001336A0(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00133BE0(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_001341C0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_001349A0(s32 arg0); /* JP: TaLogic008_GetWallEmpty */
s32 func_00134AE0(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_00134B40(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogic_IsOpenUnit */
s32 func_00134F00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic008_IsOpenMoveUnit */
s32 func_00135000(s32 arg0, s32 arg1); /* JP: TaLogic008_IsDoCerem */
s32 func_00135060(s32 arg0, void *arg1); /* JP: L008 */
s32 func_00135230(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_00135790(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_00135970(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_00135D50(void *arg0, s32 arg1); /* JP: TaLogic009_CommandBtlUnit */
void func_00135FB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic009_GetNearUnit */
void func_00136010(void *arg0); /* JP: TaLogic009_CommandDefenseUnit */
s32 func_00136060(void *arg0); /* JP: TaLogic009_GetEmptyDefensePoint */
void func_001360E0(void *arg0); /* JP: TaLogic009_CommandSpellUnit */
s32 func_00136210(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_00136490(s32 arg0, void *arg1); /* JP: TaLogic009_IsHandPlay */
s32 func_00136890(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic009_GetSpecCardPlay */
s32 func_00136980(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic009_GetSpellPlay */
void func_00136D60(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_00136F30(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic009_SetSpecialComboQue */
s32 func_00137120(s32 arg0, u8 arg1, void *arg2, s32 arg3); /* JP: TaLogic009_GetSummonPiece */
s32 func_001374D0(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_001379F0(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_00137FB0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_00138780(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_ReviveMission */
s32 func_00138950(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RevoltMission */
s32 func_00138B60(s32 arg0); /* JP: TaLogic009_GetRevoltObj */
s32 func_00138DB0(s32 arg0); /* JP: TaLogic009_IsUseCurseDragonPot */
s32 func_00138EA0(s32 arg0); /* JP: TaLogic009_IsUseCopyCat */
s32 func_00138F90(s32 arg0, s32 arg1); /* JP: TaLogic009_IsDoCerem */
s32 func_00139080(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic009_IsOpenMoveUnit */
s32 func_00139180(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogic_IsOpenUnit */
s32 func_001396C0(s32 arg0, void *arg1); /* JP: L009 */
s32 func_00139890(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_00139D90(void *arg0, s32 arg1); /* JP: TaLogic_CommandUnit */
s32 func_0013A010(u16 *arg0, s32 arg1, s32 arg2, void *arg3); /* JP: TaLogic_GetNextActiveUnit */
void func_0013A400(void *arg0, s32 arg1, s32 arg2); /* JP: TaLogic010_CommandBtlUnit */
void func_0013A6B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic010_GetNearUnit */
void func_0013A710(void *arg0, s32 arg1); /* JP: TaLogic010_CommandInvadeUnit */
s32 func_0013A870(s32 arg0); /* JP: TaLogic010_GetEmptyLine */
s32 func_0013A9A0(s32 arg0); /* JP: TaLogic010_GetLineHeight */
void func_0013AA40(void *arg0); /* JP: TaLogic010_CommandSpellUnit */
s32 func_0013AB70(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_0013AE00(s32 arg0, void *arg1); /* JP: TaLogic010_IsHandPlay */
s32 func_0013B130(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic010_GetSpecCardPlay */
s32 func_0013B220(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic010_GetSpellPlay */
s32 func_0013B420(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic010_SetComboQue */
void func_0013B600(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_0013B7E0(s32 arg0); /* JP: TaLogic010_IsRefuseEmptyCombo */
s32 func_0013B840(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic010_SetSpecialComboQue */
s32 func_0013BA30(s32 arg0, u8 arg1, void *arg2, s32 arg3); /* JP: TaLogic010_GetSummonPiece */
s32 func_0013BE60(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_0013C430(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_0013CA10(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_0013D280(void); /* JP: TaLogic010_IsActiveMode */
s32 func_0013D2C0(s32 arg0); /* JP: TaLogic010_GetUseThunderBolt */
s32 func_0013D3D0(s32 arg0, s32 arg1); /* JP: TaLogic_IsOpenUnit */
s32 func_0013D880(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic010_IsOpenMoveUnit */
s32 func_0013D980(s32 arg0, s32 arg1); /* JP: TaLogic010_IsDoCerem */
s32 func_0013DA70(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_0013DAD0(s32 arg0, void *arg1); /* JP: L010 */
s32 func_0013DCA0(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_0013E1D0(u8 *arg0); /* JP: TaLogic_CommandUnit */
s32 func_0013E3D0(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_0013E7B0(void *arg0, s32 arg1); /* JP: TaLogic011_CommandBtlUnit */
void func_0013EA20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic011_GetNearUnit */
void func_0013EA80(void *arg0); /* JP: TaLogic011_CommandDefenseUnit */
s32 func_0013EB20(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic011_GetNearMountain */
void func_0013ECF0(void *arg0); /* JP: TaLogic011_CommandEfcMonster */
s32 func_0013EEE0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_0013F170(s32 arg0, void *arg1); /* JP: TaLogic011_IsHandPlay */
s32 func_0013F3B0(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic011_GetSpecComboPlay */
s32 func_0013F540(s32 arg0, s32 *arg1, void *arg2, void *arg3, s32 arg4); /* JP: TaLogic011_GetSpecCardPlay */
s32 func_0013F640(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic011_GetSpellPlay */
s32 func_0013F850(s32 arg0, u8 *arg1, u8 *arg2); /* JP: TaLogic011_SetComboQue */
void func_0013FA90(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_0013FC70(s32 arg0); /* JP: TaLogic011_IsRefuseEmptyCombo */
s32 func_0013FCC0(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic011_SetSpecialComboQue */
s32 func_0013FEB0(s32 arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic011_GetSummonPiece */
s32 func_001402F0(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00140830(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_00140E10(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_001415F0(void *arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic_GetMinimumTask_TrapMission */
s32 func_00141B30(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_00141B90(s32 arg0, s32 arg1); /* JP: TaLogic_IsOpenUnit */
s32 func_00141E30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic011_IsOpenMoveUnit */
s32 func_00141F30(s32 arg0); /* JP: TaLogic011_IsUseBindChain */
s32 func_00142220(s32 arg0); /* JP: TaLogic011_IsUseBraveHourGlass */
s32 func_00142280(s32 arg0); /* JP: TaLogic011_IsUseReversalGoddess */
s32 func_001422E0(s32 arg0, void *arg1); /* JP: L011 */
s32 func_001424B0(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_001429B0(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_00142B70(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_00143540(void *arg0); /* JP: TaLogic012_CommandBtlUnit */
void func_00143790(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic012_GetNearUnit */
s32 func_001437F0(s16 *output, s32 arg1, s32 arg2, s32 flags); /* JP: TaLogic012_GetLineUnitLst */
s32 func_00143900(void *arg0); /* JP: TaLogic012_GetAgreeLineZ */
s32 func_00143A80(s32 arg0, s32 arg1); /* JP: TaLogic012_IsLineEmpty */
s32 func_00143BA0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_00143DE0(s32 arg0, void *arg1); /* JP: TaLogic012_IsHandPlay */
s32 func_00144150(s32 arg0, s32 *arg1, void *arg2, void *arg3, s32 arg4); /* JP: TaLogic012_GetSpecCardPlay */
s32 func_00144250(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic012_GetSpellPlay */
s32 func_00144450(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic012_SetComboQue */
void func_00144630(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_00144810(s32 arg0); /* JP: TaLogic012_IsRefuseEmptyCombo */
s32 func_00144860(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic012_SetSpecialComboQue */
s32 func_00144A60(s32 arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic012_GetSummonPiece */
s32 func_00144EC0(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00145400(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_001459E0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_001461C0(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_00146220(s32 arg0, s32 arg1); /* JP: TaLogic_IsOpenUnit */
s32 func_001464A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic012_IsOpenMoveUnit */
s32 func_001465A0(s32 arg0); /* JP: TaLogic012_IsPinch */
s32 func_001466A0(s32 arg0, s32 arg1); /* JP: TaLogic012_IsDoCerem */
s32 func_00146790(s32 arg0, void *arg1); /* JP: L012 */
s32 func_00146960(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_00146EC0(void *arg0, s32 arg1); /* JP: TaLogic_CommandUnit */
s32 func_00147100(u16 *arg0, s32 arg1, s32 arg2, void *arg3); /* JP: TaLogic_GetNextActiveUnit */
void func_001474F0(void *arg0); /* JP: TaLogic013_CommandBtlUnit */
void func_001477D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u16 arg9, s32 arg10, s32 arg11, u8 arg12, s32 arg13); /* JP: TaLogic013_GetNearUnit */
void func_00147AC0(void *arg0); /* JP: TaLogic013_CommandEfcMonster */
s32 func_00147E00(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic013_GetInvadePoint */
s32 func_00147E50(s32 arg0, s32 arg1); /* JP: TaLogic013_IsDefensePoint */
s32 func_00147EB0(s32 arg0); /* JP: TaLogic013_GetDefensePoint */
s32 func_00147F40(void); /* JP: TaLogic013_GetEmptyLine */
s32 func_00148020(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_001482F0(s32 arg0, void *arg1); /* JP: TaLogic013_IsHandPlay */
s32 func_00148630(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic013_GetSpecialComboPlay */
s32 func_00148870(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic013_GetSpecCardPlay */
s32 func_00148960(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic013_GetSpellPlay */
s32 func_00148B60(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic013_SetComboQue */
void func_00148D40(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_00148F20(s32 arg0); /* JP: TaLogic013_IsRefuseEmptyCombo */
s32 func_00148F80(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic013_SetSpecialComboQue */
s32 func_001491B0(s32 arg0, u8 arg1, void *arg2, s32 arg3); /* JP: TaLogic013_GetSummonPiece */
s32 func_00149690(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00149C60(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_0014A240(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_0014AAB0(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_ReviveMission */
s32 func_0014ACA0(void); /* JP: TaLogic013_IsActiveMode */
s32 func_0014AE60(s32 arg0, s32 arg1); /* JP: TaLogic_IsOpenUnit */
s32 func_0014B140(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic013_IsOpenMoveUnit */
s32 func_0014B240(s32 arg0, s32 arg1); /* JP: TaLogic013_IsDoCerem */
s32 func_0014B330(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_0014B390(void); /* JP: TaLogic013_IsUnitInvader */
s32 func_0014B490(s32 arg0); /* JP: TaLogic013_IsUseRevive */
s32 func_0014B730(s32 arg0, void *arg1); /* JP: L013 */
s32 func_0014B900(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_0014BDE0(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_0014BFD0(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_0014C3B0(void *arg0); /* JP: TaLogic014_CommandBtlUnit */
void func_0014C6C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic014_GetNearUnit */
void func_0014C720(void *arg0); /* JP: TaLogic014_CommandEfcMonster */
void func_0014C870(void *arg0); /* JP: TaLogic014_CommandSpellUnit */
s32 func_0014C970(s32 arg0, s32 arg1); /* JP: TaLogic014_IsLinePoint */
s32 func_0014C9D0(s32 arg0); /* JP: TaLogic014_GetLine */
s32 func_0014CA60(void); /* JP: TaLogic014_GetEmptyLine */
s32 func_0014CBA0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_0014CE30(s32 arg0, void *arg1); /* JP: TaLogic014_IsHandPlay */
s32 func_0014D0F0(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic014_GetSpecCardPlay */
s32 func_0014D1E0(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic014_GetSpellPlay */
s32 func_0014D3E0(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic014_SetComboQue */
void func_0014D5C0(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_0014D7A0(s32 arg0); /* JP: TaLogic014_IsRefuseEmptyCombo */
s32 func_0014D800(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic014_SetSpecialComboQue */
void func_0014DA30(s32 unused0, s32 unused1); /* JP: TaLogic_GetSommonPiecePreference */
s32 func_0014DA40(s32 arg0, u8 arg1, void *arg2, s32 arg3); /* JP: TaLogic014_GetSummonPiece */
s32 func_0014DF80(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_0014E550(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_0014EB30(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_0014F3A0(void); /* JP: TaLogic014_IsActiveMode */
s32 func_0014F7C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic014_IsOpenMoveUnit */
s32 func_0014F8C0(s32 arg0, s32 arg1); /* JP: TaLogic014_IsDoCerem */
s32 func_0014F9B0(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_0014FA10(s32 arg0, s32 arg1); /* JP: TaLogic014_IsUnitNaturalEffectUse */
s32 func_0014FB70(s32 arg0, void *arg1); /* JP: L014 */
s32 func_00150270(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_00150470(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_00150BE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, u16 a9, s32 a10, s32 a11, u8 a12, s32 a13); /* JP: TaLogic015_GetNearUnit */
s32 func_00150C40(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_00150F10(s32 arg0, void *arg1); /* JP: TaLogic015_IsHandPlay */
s32 func_00151170(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic015_GetSpecialComboPlay */
s32 func_001513B0(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic015_GetSpecCardPlay */
s32 func_001514A0(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic015_GetSpellPlay */
s32 func_001516A0(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic015_SetComboQue */
void func_00151880(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_00151A60(s32 arg0); /* JP: TaLogic015_IsRefuseEmptyCombo */
s32 func_00151AC0(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic015_SetSpecialComboQue */
s32 func_00151CF0(s32 arg0, u8 arg1, void *arg2, s32 arg3); /* JP: TaLogic015_GetSummonPiece */
s32 func_00152100(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_001526D0(void *src, s32 arg1, u16 *out, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_00152CD0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_00153550(void *arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic_GetMinimumTask_TrapMission */
s32 func_00153AB0(void); /* JP: TaLogic015_IsActiveMode */
s32 func_00153AE0(s32 arg0, s32 arg1); /* JP: TaLogic_IsOpenUnit */
s32 func_00153DD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic015_IsOpenMoveUnit */
s32 func_00153ED0(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_00153F30(s32 arg0); /* JP: TaLogic015_IsUseRevive */
s32 func_00154040(s32 arg0, void *arg1); /* JP: L015 */
void func_00154210(void); /* JP: L016 */
s32 func_00154220(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_001547A0(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_00154AD0(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_00154EB0(void *arg0); /* JP: TaLogic017_CommandBtlUnit */
void func_00155070(void *arg0); /* JP: TaLogic017_CommandEfcMonster */
void func_00155230(void *arg0); /* JP: TaLogic017_CommandSpellUnit */
s32 func_001554B0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic017_IsLinePoint */
s32 func_00155520(s32 arg0, s32 arg1); /* JP: TaLogic017_GetLine */
s32 func_001555F0(s32 arg0); /* JP: TaLogic017_GetEmptyLine */
s32 func_00155670(s32 arg0, s32 arg1); /* JP: TaLogic017_IsLineTop */
s32 func_00155770(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_00155A00(s32 arg0, void *arg1); /* JP: TaLogic017_IsHandPlay */
s32 func_00155C90(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic017_PlayExzCombo */
void func_00155FB0(u16 *indices, s32 first, s32 last, s32 key, s32 *values); /* JP: TaLogic017_SortTempArray */
void func_001562B0(s32 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic017_SortSwap */
s32 func_001562E0(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic017_GetSpellPlay */
s32 func_001564E0(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic017_SetComboQue */
void func_001566D0(s32 arg0, u16 *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_00156870(s32 arg0); /* JP: TaLogic017_IsRefuseEmptyCombo */
s32 func_00156910(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic017_SetSpecialComboQue */
s32 func_00156EA0(void); /* JP: TaLogic017_GetEmptyExzPiece */
s32 func_00156F70(void); /* JP: TaLogic017_GetEmptyTrapPiece */
s32 func_00156FC0(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_00157480(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00157A50(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4, u8 arg5); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_00158360(s32 arg0, s32 arg1); /* JP: TaLogic_IsOpenUnit */
s32 func_00158780(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_001587E0(s32 arg0); /* JP: TaLogic017_IsExzParts */
s32 func_00158800(s32 arg0); /* JP: TaLogic017_IsExzSafe */
s32 func_00158810(s32 arg0); /* JP: TaLogic017_IsSetTrap */
s32 func_00158960(s32 arg0); /* JP: TaLogic017_IsExzodia */
s32 func_00158AB0(s32 arg0, void *arg1); /* JP: L017 */
s32 func_00158C80(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_001591B0(u16 *arg0); /* JP: TaLogic_CommandUnit */
s32 func_00159380(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_00159760(void *arg0); /* JP: TaLogic018_CommandLDUnit */
s32 func_00159BE0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic018_GetSummonPoint */
void func_00159D00(void *arg0); /* JP: TaLogic018_CommandBtlUnit */
void func_00159F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic018_GetNearUnit */
void func_00159FE0(void *arg0); /* JP: TaLogic018_CommandEfcMonster */
void func_0015A120(s32 a0, s32 a1, u16 *buf); /* JP: TaLogic018_GetOutVirusZone */
void func_0015A180(s32 arg0, s32 arg1, u16 *arg2); /* JP: TaLogic018_GetZoneSide */
s32 func_0015A2E0(s32 arg0, u16 *arg1); /* JP: TaLogic018_IsZonePast */
s32 func_0015A320(u16 *arg0); /* JP: TaLogic018_GetZoneSize */
s32 func_0015A360(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_0015A5F0(s32 arg0, void *arg1); /* JP: TaLogic018_IsHandPlay */
s32 func_0015A820(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic018_GetSpecCardPlay */
s32 func_0015A910(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic018_GetSpellPlay */
s32 func_0015AD00(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic018_SetSpecialComboQue */
s32 func_0015AF30(s32 arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic018_GetSummonPiece */
s32 func_0015B250(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_0015B820(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_0015BE00(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_0015C670(void *arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic_GetMinimumTask_TrapMission */
s32 func_0015CBB0(s32 arg0, s32 arg1); /* JP: TaLogic_IsOpenUnit */
s32 func_0015CF30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic018_IsOpenMoveUnit */
s32 func_0015D030(s32 arg0, s32 arg1); /* JP: TaLogic018_IsDoCerem */
s32 func_0015D120(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_0015D180(s32 arg0, void *arg1); /* JP: L018 */
s32 func_0015D350(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_0015D8E0(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_0015DAF0(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_0015DED0(void *arg0); /* JP: TaLogic019_CommandBtlUnit */
void func_0015E030(void *arg0); /* JP: TaLogic019_CommandAtkUnit */
s32 func_0015E2E0(s32 arg0, s32 arg1); /* JP: TaLogic019_IsEmptyTrapGuard */
s32 func_0015E440(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic019_IsEmptyCntrGuard */
void func_0015E520(void *arg0, s32 arg1); /* JP: TaLogic019_CommandLineUnit */
void func_0015E8F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic019_GetNearUnit */
void func_0015E950(void *arg0); /* JP: TaLogic019_CommandEfcMonster */
void func_0015EC60(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogic019_CommandLDGuardUnit */
s32 func_0015ED30(s32 arg0, s32 arg1); /* JP: TaLogic019_IsLinePoint */
s32 func_0015ED90(s32 arg0); /* JP: TaLogic019_GetLine */
s32 func_0015EE40(void); /* JP: TaLogic019_GetEmptyLine */
void func_0015EF40(void *arg0); /* JP: TaLogic019_CommandSpellUnit */
s32 func_0015F300(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_0015F5E0(s32 arg0, void *arg1); /* JP: TaLogic019_IsHandPlay */
s32 func_0015FA00(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic019_GetSpecialComboPlay */
s32 func_0015FB60(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic019_GetSpecCardPlay */
s32 func_0015FC50(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic019_GetSpellPlay */
s32 func_0015FE50(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic019_SetComboQue */
void func_00160030(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_00160210(s32 arg0); /* JP: TaLogic019_IsRefuseEmptyCombo */
s32 func_00160270(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic019_SetSpecialComboQue */
void func_001604A0(s32 unused0, s32 unused1); /* JP: TaLogic_GetSommonPiecePreference */
s32 func_001604B0(s32 arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic019_GetSummonPiece */
s32 func_001607D0(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00160DA0(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_00161380(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_00161BF0(u16 *arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic_GetMinimumTask_ReviveMission */
s32 func_00161EA0(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RevoltMission */
s32 func_001620B0(s32 arg0, s32 arg1); /* JP: TaLogic_IsOpenUnit */
s32 func_00162390(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic019_IsOpenMoveUnit */
s32 func_00162490(s32 arg0, s32 arg1); /* JP: TaLogic019_IsDoCerem */
s32 func_00162580(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_001625E0(s32 arg0); /* JP: TaLogic019_GetUseThunderBolt */
s32 func_001626F0(s32 arg0); /* JP: TaLogic019_IsUseGFK */
s32 func_001627D0(s32 arg0); /* JP: TaLogic019_IsUseRevive */
s32 func_00162A70(s32 arg0); /* JP: TaLogic019_IsUseSaint */
s32 func_00162D10(s32 arg0); /* JP: TaLogic019_IsUseRevolt */
s32 func_00162F60(s32 arg0, void *arg1); /* JP: L019 */
s32 func_00163130(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_00163660(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_00163870(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_00163C50(void *arg0, s32 arg1); /* JP: TaLogic020_CommandBtlUnit */
void func_00163EC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic020_GetNearUnit */
void func_00163F20(void *arg0); /* JP: TaLogic020_CommandInvadeUnit */
s32 func_00163F90(s32 arg0, s32 arg1); /* JP: TaLogic020_GetNextGrassPoint */
void func_00164020(s32 arg0); /* JP: TaLogic020_CommandEfcMonster */
void func_00164260(void *arg0); /* JP: TaLogic020_CommandSpellUnit */
s32 func_00164360(s32 arg0); /* JP: TaLogic020_GetLinePiece */
s32 func_001643F0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_00164680(s32 arg0, void *arg1); /* JP: TaLogic020_IsHandPlay */
s32 func_00164910(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic020_GetSpecCardPlay */
s32 func_00164A00(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic020_GetTrapCardPlay */
s32 func_00164AE0(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic020_GetSpellPlay */
s32 func_00164CE0(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic020_SetComboQue */
void func_00164EC0(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_001650A0(s32 arg0); /* JP: TaLogic020_IsRefuseEmptyCombo */
s32 func_00165100(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic020_SetSpecialComboQue */
s32 func_001652F0(s32 arg0, u8 arg1, void *arg2, s32 arg3); /* JP: TaLogic020_GetSummonPiece */
s32 func_001658F0(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00165EC0(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_001664A0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_00166D10(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_ReviveMission */
s32 func_001670A0(s32 arg0, s32 arg1); /* JP: TaLogic_IsOpenUnit */
s32 func_00167570(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic020_IsOpenMoveUnit */
s32 func_00167670(s32 arg0, s32 arg1); /* JP: TaLogic020_IsDoCerem */
s32 func_001676D0(void); /* JP: TaLogic_GetWarnHideLvl */
s32 func_001676E0(s32 arg0, void *arg1); /* JP: L020 */
s32 func_001678B0(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_00167D30(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_00167E80(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_00168260(void *arg0, s32 arg1); /* JP: TaLogic021_CommandBtlUnit */
void func_001684D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic021_GetNearUnit */
void func_00168530(u16 *arg0); /* JP: TaLogic021_CommandInvadeUnit */
s32 func_001687A0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_00168A30(s32 arg0, void *arg1); /* JP: TaLogic021_IsHandPlay */
s32 func_00168D10(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic021_GetSpecCardPlay */
s32 func_00168E00(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic021_GetSpellPlay */
s32 func_00169000(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic021_SetComboQue */
void func_001691E0(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_001693C0(s32 arg0); /* JP: TaLogic021_IsRefuseEmptyCombo */
s32 func_00169420(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic021_SetSpecialComboQue */
s32 func_00169610(s32 arg0, u8 arg1, void *arg2, s32 arg3); /* JP: TaLogic021_GetSummonPiece */
s32 func_00169A10(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00169FE0(void *src, s32 arg1, u16 *out, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_0016A5C0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_0016AE30(s32 arg0, s32 arg1); /* JP: TaLogic_IsOpenUnit */
s32 func_0016AFE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic021_IsOpenMoveUnit */
s32 func_0016B0E0(void); /* JP: TaLogic_GetWarnHideLvl */
s32 func_0016B1F0(s32 arg0, void *arg1); /* JP: L021 */
s32 func_0016B3C0(s32 arg0); /* JP: TaLogicCom_GetRevoltObj */
s32 func_0016B610(s32 arg0, s32 arg1, void *arg2); /* JP: TaLogicCom_IsOpenUnit */
s32 func_0016C6B0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogicCom_IsUseObjEffect */
s32 func_0016CBB0(s32 arg0, s32 *arg1); /* JP: TaLogicCom_GetUseXYRangeSpell */
s32 func_0016CE00(s32 arg0, s32 arg1); /* JP: TaLogicCom_IsDoCerem */
s32 func_0016CF10(s32 arg0); /* JP: TaLogicCom_IsExzParts */
s32 func_0016CF30(s32 arg0); /* JP: TaLogic_IsTactixExz */
s32 func_0016CFF0(s32 arg0); /* JP: TaLogic_IsExzodia */
s32 func_0016D140(void *work, void *arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask */
s32 func_0016D6A0(void *arg0); /* JP: TaLogic_CommandUnit */
s32 func_0016D8C0(u16 *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetNextActiveUnit */
void func_0016DCA0(u16 *arg0); /* JP: TaLogic022_CommandBtlUnit */
void func_0016DDA0(void *arg0); /* JP: TaLogic022_CommandAtkUnit */
s32 func_0016E000(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic022_IsEmptyCntrGuard */
void func_0016E0E0(u16 *arg0, s32 arg1); /* JP: TaLogic022_CommandLineUnit */
void func_0016E4B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0, u16 arg_sp8, s32 arg_sp10, s32 arg_sp18, u8 arg_sp20, s32 arg_sp28); /* JP: TaLogic022_GetNearUnit */
void func_0016E510(u16 *arg0); /* JP: TaLogic022_CommandEfcMonster */
void func_0016F240(u16 *arg0); /* JP: TaLogic022_CommandSpellUnit */
s32 func_0016F4D0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetMinimumTask_Summon */
s32 func_0016F760(s32 arg0, void *arg1); /* JP: TaLogic022_IsHandPlay */
s32 func_0016FC00(s32 arg0, void *arg1, void *arg2, s32 arg3); /* JP: TaLogic022_GetSpecCardPlay */
s32 func_0016FCF0(s32 arg0, u8 *arg1, void *arg2, s32 arg3); /* JP: TaLogic022_GetSpellPlay */
s32 func_0016FEF0(s32 arg0, u8 *arg1, void *arg2); /* JP: TaLogic022_SetComboQue */
void func_001700D0(s32 arg0, void *arg1, s32 *arg2); /* JP: TaLogic_ConvEmptyCombo */
s32 func_001702B0(s32 arg0); /* JP: TaLogic022_IsRefuseEmptyCombo */
s32 func_001703E0(s32 arg0, void *arg1, void *arg2); /* JP: TaLogic022_SetSpecialComboQue */
s32 func_00170610(s32 arg0, u32 arg1); /* JP: TaLogic_GetSommonPiecePreference */
s32 func_00170620(s32 arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic022_GetSummonPiece */
s32 func_00170940(u16 *unit, s32 arg1, void *out, u8 arg3); /* JP: TaLogic_GetMinimumTask_RunMission */
s32 func_00170F10(void *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_AtkMission */
s32 func_001714F0(void *arg0, s32 arg1, void *arg2, u8 arg3, u8 arg4); /* JP: TaLogic_GetMinimumTask_MoveMission */
s32 func_00171D60(u16 *arg0, s32 arg1, void *arg2, s32 arg3); /* JP: TaLogic_GetMinimumTask_ReviveMission */
s32 func_00172000(u16 *arg0, s32 arg1, void *arg2, u8 arg3); /* JP: TaLogic_GetMinimumTask_RevoltMission */
s32 func_00172210(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic022_IsOpenMoveUnit */
s32 func_00172310(s32 arg0); /* JP: TaLogic_GetWarnHideLvl */
s32 func_00172370(s32 arg0, void *arg1); /* JP: L022 */
s32 func_001728A0(s32 arg0, u8 *arg1); /* JP: L032 */
s32 func_001747D0(s32 arg0, void *tutorial); /* JP: L033 */
s32 func_00175FE0(s32 arg0, void *tutorial); /* JP: L034 */
s32 func_00178590(s32 arg0, void *tutorial); /* JP: L035 */
f32 func_0017B340(u64 arg0); /* JP: _f_ulltof */
void func_0017B380(u32 arg0); /* JP: _d_utod */
s32 func_0017B3D0(void); /* JP: _dpflt */
s32 func_0017B3F0(void); /* JP: _dpfgt */
void func_0017B410(s32 arg0, s32 arg1); /* JP: mwOverlayInit */
int func_0017B4C0(void); /* JP: RFU000_FullReset */
int func_0017B4D0(void); /* JP: ResetEE */
int func_0017B4E0(int arg0, int arg1, int arg2); /* JP: SetGsCrt */
int func_0017B4F0(void); /* JP: RFU003 */
int func_0017B500(int arg0); /* JP: Exit */
int func_0017B510(void); /* JP: RFU005 */
int func_0017B520(int arg0, int arg1, int arg2); /* JP: LoadExecPS2 */
s32 func_0017B530(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: ExecPS2 */
int func_0017B540(void); /* JP: RFU008 */
int func_0017B550(void); /* JP: RFU009 */
int func_0017B560(void); /* JP: AddSbusIntcHandler */
int func_0017B570(void); /* JP: RemoveSbusIntcHandler */
int func_0017B580(void); /* JP: Interrupt2Iop */
int func_0017B590(int arg0, int *arg1); /* JP: SetVTLBRefillHandler */
int func_0017B5A0(int arg0, int *arg1); /* JP: SetVCommonHandler */
int func_0017B5B0(void); /* JP: SetVInterruptHandler */
s32 func_0017B5C0(s32 arg0, void (*arg1)(), s32 arg2); /* JP: AddIntcHandler */
int func_0017B5D0(void); /* JP: AddIntcHandler2 */
int func_0017B5E0(int arg0, int arg1); /* JP: RemoveIntcHandler */
s32 func_0017B5F0(s32 arg0, void (*arg1)(), s32 arg2); /* JP: AddDmacHandler */
s32 func_0017B600(s32 arg0, s32 (*arg1)(s32, void *), s32 arg2, u32 *arg3); /* JP: AddDmacHandler2 */
int func_0017B610(int arg0, int arg1); /* JP: RemoveDmacHandler */
int func_0017B620(int arg0); /* JP: _EnableIntc */
int func_0017B630(int arg0); /* JP: _DisableIntc */
int func_0017B640(int arg0); /* JP: _EnableDmac */
int func_0017B650(int arg0); /* JP: _DisableDmac */
int func_0017B660(int arg0, int *arg1, int arg2); /* JP: _SetAlarm */
int func_0017B670(void); /* JP: _ReleaseAlarm */
void func_0017B680(void); /* JP: _iEnableIntc */
void func_0017B690(void); /* JP: _iDisableIntc */
void func_0017B6A0(void); /* JP: _iEnableDmac */
void func_0017B6B0(void); /* JP: _iDisableDmac */
int func_0017B6C0(void); /* JP: _iSetAlarm */
int func_0017B6D0(void); /* JP: _iReleaseAlarm */
s32 func_0017B6E0(void *arg0); /* JP: CreateThread */
int func_0017B6F0(void); /* JP: DeleteThread */
s32 func_0017B700(s32 arg0, void *arg1); /* JP: StartThread */
int func_0017B710(void); /* JP: ExitThread */
void func_0017B720(void); /* JP: ExitDeleteThread */
int func_0017B730(void); /* JP: TerminateThread */
int func_0017B740(void); /* JP: iTerminateThread */
int func_0017B750(void); /* JP: DisableDispatchThread */
int func_0017B760(void); /* JP: EnableDispatchThread */
s32 func_0017B770(s32 arg0, s32 arg1); /* JP: ChangeThreadPriority */
int func_0017B780(void); /* JP: iChangeThreadPriority */
int func_0017B790(int arg0); /* JP: RotateThreadReadyQueue */
int func_0017B7A0(void); /* JP: _iRotateThreadReadyQueue */
int func_0017B7B0(void); /* JP: ReleaseWaitThread */
int func_0017B7C0(void); /* JP: iReleaseWaitThread */
int func_0017B7D0(void); /* JP: GetThreadId */
s32 func_0017B7E0(s32 arg0, s32 *arg1); /* JP: ReferThreadStatus */
int func_0017B7F0(void); /* JP: iReferThreadStatus */
int func_0017B800(void); /* JP: SleepThread */
int func_0017B810(void); /* JP: WakeupThread */
int func_0017B820(int arg0); /* JP: _iWakeupThread */
int func_0017B830(void); /* JP: CancelWakeupThread */
int func_0017B840(void); /* JP: iCancelWakeupThread */
int func_0017B850(void); /* JP: SuspendThread */
int func_0017B860(int arg0); /* JP: _iSuspendThread */
int func_0017B870(void); /* JP: ResumeThread */
int func_0017B880(void); /* JP: iResumeThread */
int func_0017B890(void); /* JP: JoinThread */
int func_0017B8A0(void); /* JP: RFU060 */
int func_0017B8B0(void); /* JP: RFU061 */
unsigned int func_0017B8C0(void); /* JP: EndOfHeap */
int func_0017B8D0(void); /* JP: RFU063 */
int func_0017B8E0(void *arg0); /* JP: CreateSema */
int func_0017B8F0(int arg0); /* JP: DeleteSema */
void func_0017B900(int arg0); /* JP: SignalSema */
void func_0017B910(int arg0); /* JP: iSignalSema */
void func_0017B920(int arg0); /* JP: WaitSema */
int func_0017B930(int arg0); /* JP: PollSema */
int func_0017B940(void); /* JP: iPollSema */
int func_0017B950(void); /* JP: ReferSemaStatus */
int func_0017B960(void); /* JP: iReferSemaStatus */
int func_0017B970(void); /* JP: RFU073 */
int func_0017B980(unsigned int *arg0); /* JP: SetOsdConfigParam */
int func_0017B990(unsigned int *arg0); /* JP: GetOsdConfigParam */
int func_0017B9A0(void); /* JP: GetGsHParam */
int func_0017B9B0(void); /* JP: GetGsVParam */
int func_0017B9C0(void); /* JP: SetGsHParam */
int func_0017B9D0(void); /* JP: SetGsVParam */
int func_0017B9E0(void); /* JP: RFU080_CreateEventFlag */
int func_0017B9F0(void); /* JP: RFU081_DeleteEventFlag */
int func_0017BA00(void); /* JP: RFU082_SetEventFlag */
int func_0017BA10(void); /* JP: RFU083_iSetEventFlag */
int func_0017BA20(void); /* JP: RFU084_ClearEventFlag */
int func_0017BA30(void); /* JP: RFU085_iClearEventFlag */
int func_0017BA40(void); /* JP: RFU086_WaitEvnetFlag */
int func_0017BA50(void); /* JP: RFU087_PollEvnetFlag */
int func_0017BA60(void); /* JP: RFU088_iPollEvnetFlag */
int func_0017BA70(void); /* JP: RFU089_ReferEventFlagStatus */
int func_0017BA80(void); /* JP: RFU090_iReferEventFlagStatus */
int func_0017BA90(void); /* JP: RFU091 */
int func_0017BAA0(void); /* JP: EnableIntcHandler */
int func_0017BAB0(void); /* JP: iEnableIntcHandler */
int func_0017BAC0(void); /* JP: DisableIntcHandler */
int func_0017BAD0(void); /* JP: iDisableIntcHandler */
int func_0017BAE0(void); /* JP: EnableDmacHandler */
int func_0017BAF0(void); /* JP: iEnableDmacHandler */
int func_0017BB00(void); /* JP: DisableDmacHandler */
int func_0017BB10(void); /* JP: iDisableDmacHandler */
int func_0017BB20(void); /* JP: KSeg0 */
int func_0017BB30(void); /* JP: EnableCache */
int func_0017BB40(void); /* JP: DisableCache */
int func_0017BB50(void); /* JP: GetCop0 */
void func_0017BB60(int arg0); /* JP: FlushCache */
int func_0017BB70(void); /* JP: CpuConfig */
int func_0017BB80(void); /* JP: iGetCop0 */
void func_0017BB90(s32 arg0); /* JP: iFlushCache */
int func_0017BBA0(void); /* JP: iCpuConfig */
int func_0017BBB0(void); /* JP: sceSifStopDma */
int func_0017BBC0(void); /* JP: SetCPUTimerHandler */
int func_0017BBD0(void); /* JP: SetCPUTimer */
int func_0017BBE0(void); /* JP: SetOsdConfigParam2 */
int func_0017BBF0(void); /* JP: GetOsdConfigParam2 */
u64 func_0017BC00(void); /* JP: GsGetIMR */
int func_0017BC10(void); /* JP: iGsGetIMR */
unsigned long long func_0017BC20(unsigned long long arg0); /* JP: GsPutIMR */
int func_0017BC30(void); /* JP: iGsPutIMR */
int func_0017BC40(void); /* JP: SetPgifHandler */
int func_0017BC50(void *arg0, long long *arg1); /* JP: SetVSyncFlag */
int func_0017BC60(void); /* JP: RFU116 */
int func_0017BC70(void); /* JP: print */
int func_0017BC80(int arg0); /* JP: sceSifDmaStat */
int func_0017BC90(void); /* JP: isceSifDmaStat */
int func_0017BCA0(int *arg0, int arg1); /* JP: sceSifSetDma */
int func_0017BCB0(void); /* JP: isceSifSetDma */
int func_0017BCC0(void); /* JP: sceSifSetDChain */
int func_0017BCD0(void); /* JP: isceSifSetDChain */
int func_0017BCE0(void); /* JP: sceSifSetReg */
int func_0017BCF0(int arg0); /* JP: sceSifGetReg */
int func_0017BD00(int arg0, int arg1); /* JP: ExecOSD */
int func_0017BD10(int arg0, void *arg1); /* JP: Deci2Call */
int func_0017BD20(void); /* JP: PSMode */
int func_0017BD30(void); /* JP: MachineType */
int func_0017BD40(void); /* JP: GetMemorySize */
int func_0017BD50(void);
void func_0017BD70(void);
s64 func_0017BE00(void);
s32 func_0017BEA8(s32 mode, s32 a, s32 b); /* JP: write */
s32 func_0017BF28(s32 fd, char *buf, s32 n); /* JP: read */
s32 func_0017BFA0(void); /* JP: open */
s32 func_0017BFC8(void); /* JP: close */
s32 func_0017BFD0(void); /* JP: ioctl */
s32 func_0017BFD8(void); /* JP: lseek */
u32 func_0017BFE0(s32 incr); /* JP: sbrk */
s32 func_0017C090(void); /* JP: isatty */
s32 func_0017C098(s32 arg0, void *arg1); /* JP: fstat */
s32 func_0017C0B0(void); /* JP: getpid */
s32 func_0017C0B8(s32 arg0, s32 arg1); /* JP: kill */
s32 func_0017C0E0(void); /* JP: stat */
s32 func_0017C108(void); /* JP: unlink */
void func_0017C130(u32 start, u32 end); /* JP: _sceSDC */
void func_0017C1D8(u32 arg0, u32 arg1); /* JP: SyncDCache (matched by position) */
void func_0017C258(u32 arg0, u32 arg1); /* JP: iSyncDCache */
void func_0017C270(u32 start, u32 end); /* JP: _sceIDC */
void func_0017C318(u32 arg0, u32 arg1); /* JP: InvalidDCache (matched by position) */
void func_0017C398(u32 arg0, u32 arg1); /* JP: iInvalidDCache */
s32 func_0017C3B0(void);
s32 func_0017C3C0(s32 arg0);
s32 func_0017C428(s32 arg0);
s32 func_0017C490(s32 arg0);
s32 func_0017C4F8(s32 arg0);
void func_0017C560(void); /* JP: iEnableIntc */
void func_0017C580(void); /* JP: iDisableIntc */
void func_0017C5A0(void); /* JP: iEnableDmac */
void func_0017C5C0(void); /* JP: iDisableDmac */
void func_0017C5E0(int arg0, int arg1);
int func_0017C5F0(int arg0, int *arg1, int arg2);
s32 func_0017C600(s32 *arg0, s32 *arg1, u32 arg2);
int func_0017C638(int arg0);
void func_0017C648(void);
void func_0017C720(void *arg); /* JP: topThread */
s32 func_0017C7F8(void); /* JP: InitThread */
s32 func_0017C8D0(s32 arg0); /* JP: iWakeupThread */
s32 func_0017C968(u32 arg0); /* JP: iRotateThreadReadyQueue */
s32 func_0017C9E8(s32 arg0); /* JP: iSuspendThread */
s32 func_0017CA80(s32 arg0, s32 arg1, s32 arg2); /* JP: sceDeci2Open */
void func_0017CAC8(s32 arg0); /* JP: sceDeci2Close */
void func_0017CAF0(s32 arg0, s8 arg1); /* JP: sceDeci2ReqSend */
void func_0017CB20(s32 arg0); /* JP: sceDeci2Poll */
void func_0017CB48(s32 arg0, s32 arg1, s32 arg2); /* JP: sceDeci2ExRecv */
void func_0017CB80(s32 arg0, s32 arg1, s32 arg2); /* JP: sceDeci2ExSend */
void func_0017CBB8(s32 arg0, s8 arg1); /* JP: sceDeci2ExReqSend */
void func_0017CBE8(s32 arg0); /* JP: sceDeci2ExLock */
void func_0017CC10(s32 arg0); /* JP: sceDeci2ExUnLock */
void func_0017CC38(s32 arg0); /* JP: kputs */
s32 *func_0017CC60(s32 arg0); /* JP: QueueInit */
void func_0017CC88(void *arg0); /* JP: QueuePeekWriteDone */
void func_0017CCC8(void *arg0); /* JP: QueuePeekReadDone */
void func_0017CD08(s32 event, s32 param, void *opt); /* JP: sceTtyHandler */
s32 func_0017CEA0(const char *buf, int len); /* JP: sceTtyWrite (matched by position) */
s32 func_0017CFF0(char *arg0, s32 arg1); /* JP: sceTtyRead */
s32 func_0017D0C0(void); /* JP: sceTtyInit */
s32 func_0017D180(s32 arg0); /* JP: kputchar */
void func_0017D1B8(s32 arg0); /* JP: deci2Putchar */
void func_0017D268(s32 arg0); /* JP: serialPutchar */
s32 func_0017D2A0(u64 a); /* JP: ftoi */
void func_0017D498(char *fmt, u8 *ap); /* JP: _printf */
s32 func_0017DA60(const char *arg0, ...); /* JP: kprintf */
s32 func_0017DA98(const char *arg0, ...); /* JP: scePrintf */
void func_0017DAF8(s32 *arg0, s32 *arg1); /* JP: _set_sreg */
void func_0017DB18(void *arg0, void *arg1); /* JP: _change_addr */
s32 func_0017DB28(s32 arg0); /* JP: sceSifGetSreg */
s32 func_0017DB40(s32 arg0, s32 arg1); /* JP: sceSifSetSreg */
s32 *func_0017DB60(void); /* JP: sceSifGetDataTable */
void func_0017DDF0(void); /* JP: sceSifExitCmd */
s32 func_0017DE28(s32 arg0, s32 arg1); /* JP: sceSifSetCmdBuffer */
s32 func_0017DE40(s32 arg0, s32 arg1); /* JP: sceSifSetSysCmdBuffer */
s32 func_0017DE58(s32 cid, s32 *f, s32 data); /* JP: sceSifAddCmdHandler */
s32 func_0017DE88(s32 cid); /* JP: sceSifRemoveCmdHandler */
s32 func_0017DEB0(s32 cid, s32 mode, s32 pkt, s32 pktsize, s32 src, s32 dest, s32 size); /* JP: _sceSifSendCmd */
s32 func_0017DFE8(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: sceSifSendCmd */
s32 func_0017E028(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: isceSifSendCmd */
s32 func_0017E068(s32 ch);
void func_0017E190(s32 *ptr, s32 size);
void func_0017E3E0(void); /* JP: sceSifExitRpc */
void *func_0017E408(s32 *data); /* JP: _sceRpcGetPacket (matched by position) */
void func_0017E4B0(void *arg0); /* JP: _sceRpcFreePacket */
void *func_0017E4D0(s32 arg0); /* JP: _sceRpcGetFPacket */
void *func_0017E500(void *arg0, s32 arg1); /* JP: _sceRpcGetFPacket2 */
void func_0017E540(void *pkt, void *data); /* JP: _request_end */
void func_0017E5F8(void *arg0, s32 arg1); /* JP: _request_rdata */
s32 func_0017E658(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: sceSifGetOtherData */
void *func_0017E7B0(s32 arg0, s32 arg1); /* JP: _search_svdata */
void func_0017E800(void *arg0, s32 arg1); /* JP: _request_bind */
s32 func_0017E8B0(void *arg0, s32 arg1, s32 arg4); /* JP: sceSifBindRpc */
void func_0017E9F0(void *pkt, void *data); /* JP: _request_call */
s32 func_0017EA80(s32 *client, s32 rpc_number, s32 mode, s32 *sendbuf, s32 ssize, s32 *recvbuf, s32 rsize, s32 end_func, s32 end_param); /* JP: sceSifCallRpc */
s32 func_0017EC70(void *arg0); /* JP: sceSifCheckStatRpc */
void func_0017ECB0(void *arg0, s32 arg1); /* JP: sceSifSetRpcQueue (matched by position) */
void func_0017ED48(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, void *arg6);
void *func_0017EE18(void *arg0, void *arg1); /* JP: sceSifRemoveRpc (matched by position) */
void *func_0017EEB0(void *arg0); /* JP: sceSifRemoveRpcQueue (matched by position) */
void *func_0017EF40(void *arg0); /* JP: sceSifGetNextRequest (matched by position) */
void func_0017EF98(void *data); /* JP: sceSifExecRequest (matched by position) */
void func_0017F160(void *arg0); /* JP: sceSifRpcLoop */
void func_0017F1A0(void);
void *func_0017F200(void);
void *func_0017F288(u32 i);
void func_0017F2F8(void);
void func_0017F6B8(void);
s32 func_0017F708(void);
void func_0017F738(void); /* JP: _cleanup */
s32 func_0017F748(s32 arg0, s32 arg1);
void func_0017F7D8(s32 arg0, hcall_t *arg1);
s32 func_0017F9D0(void);
s32 func_0017FA60(void); /* JP: sceFsReset */
s32 func_0017FA98(void *name, s32 flags, ...);
s32 func_0017FD20(u32 fd);
s32 func_0017FEA0(u32 fd, s32 offset, s32 whence);
s32 func_001800D8(s32 fd, s32 buf, s32 nbyte);
s32 func_00180348(s32 fd, void *buf, s32 nbyte);
s32 func_00180608(u32 fd, s32 request, void *argp);
s32 func_00180958(u32 fd, s32 request, void *argp, u32 arglen, void *bufp, u32 buflen);
s32 func_00180B38(s32 name, s32 code);
s32 func_00180CE0(s32 arg0);
s32 func_00180D00(char *name, s32 mode);
s32 func_00180EB0(s32 arg0);
s32 func_00180ED0(u8 *dev, u8 *blockdev, u8 *arg, s32 arglen);
s32 func_00181140(s32 arg0);
s32 func_00181260(s32 arg0);
s32 func_00181348(u32 fd);
s32 func_001814B0(s32 arg0, s32 arg1);
s32 func_00181608(u8 *name, void *stat);
s32 func_001817A8(u8 *name, void *stat, s32 mask);
s32 func_001819E8(u8 *oldname, u8 *newname);
s32 func_00181BD8(s32 arg0);
s32 func_00181BF8(u8 *name, s32 flag);
s32 func_00181D90(u8 *fsname, u8 *devname, s32 flag, u8 *arg, s32 arglen);
s32 func_00182000(s32 arg0);
s64 func_00182020(s32 fd, s64 offset, s32 whence);
s32 func_00182258(u8 *name, s32 cmd, u8 *arg, u32 arglen, void *bufp, u32 buflen);
s32 func_00182490(u8 *existing, u8 *newpath);
s32 func_00182670(u8 *name, void *buf, u32 len);
s32 func_00182838(void); /* JP: sceSifInitIopHeap */
s32 func_001828C0(s32 arg0); /* JP: sceSifAllocIopHeap */
s32 func_00182930(s32 arg0, s32 arg1, s32 arg2);
s32 func_001829B0(s32 arg0); /* JP: sceSifFreeIopHeap */
s32 func_00182A28(s32 arg0);
s32 func_00182A48(const char *name, void *addr); /* JP: sceSifLoadIopHeap */
s32 func_00182B38(void); /* JP: _lf_bind */
s32 func_00182C38(void);
s32 func_00182CC8(void); /* JP: sceSifLoadFileReset */
s32 func_00182D00(s32 addr, s32 arglen, s32 args, s32 *ret);
s32 func_00182F08(s32 addr, s32 arglen, s32 args, s32 *ret);
s32 func_00183110(s32 arg0);
s32 func_001831A0(void *arg0);
s32 func_00183240(s32 arg0);
s32 func_001832D0(s32 arg0, s32 arg1, s32 arg2);
s32 func_001832F0(s32 arg0);
s32 func_00183310(s32 name, s32 arglen, s32 args, s32 ret, s32 rpcno);
void func_00183538(s32 arg0, s32 arg1, s32 arg2);
s32 func_00183558(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00183578(s32 name, s32 sec, s32 out, s32 rpcno); /* JP: _sceSifLoadElfPart */
s32 func_00183680(s32 arg0, s32 arg1, s32 arg2); /* JP: sceSifLoadElfPart */
s32 func_001836A0(s32 arg0, s32 arg1); /* JP: sceSifLoadElf */
s32 func_001836C8(s32 arg0, void *arg1, u32 arg2); /* JP: sceSifGetIopAddr */
s32 func_001837B8(s32 arg0, void *arg1, s32 arg2); /* JP: sceSifSetIopAddr */
s32 func_001839D8(void); /* JP: sceSifIsAliveIop */
s32 func_00183A00(void);
s32 func_00183A38(char *arg);
s32 func_00183B48(s32 arg0);
u32 func_00183BA8(s32 arg0, s32 arg1);
int func_00183C30(int arg0, int *arg1, int arg2);
s32 func_00183C40(s32 *arg0, s32 *arg1, u32 arg2);
int func_00183C78(int arg0);
void func_00183C88(int arg0, int arg1);
void func_00183C98(void);
int func_00183D50(void);
int func_00183D60(void);
int func_00183D70(int arg0, int arg1, int arg2, int arg3, int arg4);
s32 func_00183D80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
int func_00183DB0(void);
int func_00183DC0(void);
int func_00183DD0(void);
int func_00183DE0(void);
int func_00183DF0(void);
int func_00183E00(void);
s32 func_00183E10(void);
s32 func_00183E50(void);
s32 func_001843E0(void);
s32 func_00184428(void);
void func_00184440(void);
s32 *func_00184488(s32 arg0);
s32 func_001844C0(s32 *arg0);
s32 func_001844D0(void);
void func_00184510(int arg0, int arg1);
s32 *func_00184520(s32 arg0);
void func_00184540(void);
void func_00184580(int arg0, int arg1);
int func_00184590(int arg0, int *arg1, int arg2);
s32 func_001845A0(s32 *arg0, s32 *arg1, u32 arg2);
int func_001845D8(int arg0);
s32 func_001845E8(void);
void func_00184650(void);
void func_00184700(void);
s32 func_00184708(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00184768(s32 arg0, s32 arg1, s32 arg2);
void func_001847B0(s32 arg0);
void func_001847D8(s32 arg0, s32 arg1);
void func_00184810(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
s32 *func_001849A0(void); /* JP: sceGsGetGParam */
void func_001849B0(void); /* JP: sceGsResetPath */
void func_00184A18(void *arg0, s16 psm, s16 w, s16 h, s16 dx, s16 dy); /* JP: sceGsSetDefDispEnv */
s32 func_00184C88(void *arg0); /* JP: sceGsPutDispEnv */
s32 func_00184D48(s16 arg0, s16 arg1, s16 arg2); /* JP: sceGszbufaddr */
s32 func_00184E10(void *arg0, s16 psm, s16 w, s16 h, s16 ztest, s16 zpsm); /* JP: sceGsSetDefDrawEnv */
s32 func_00184FF8(void *arg0, s16 ztest, s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b, u8 a, u32 z); /* JP: sceGsSetDefClear */
s32 func_00185100(void *arg0); /* JP: sceGsPutDrawEnv */
void func_001851E8(void *arg0, s16 psm, s16 w, s16 h, s16 ztst, s16 zpsm, s16 flag); /* JP: sceGsSetDefDBuff */
s32 func_00185480(u8 *arg0, s32 arg1); /* JP: sceGsSwapDBuff */
s32 func_001854E0(s32 arg0); /* JP: sceGsSyncV */
s32 func_00185578(s32 mode, s32 timeout); /* JP: sceGsSyncPath */
s32 func_00185890(void *arg0, s16 sbp, s16 sbw, s16 spsm, s16 ssax, s16 ssay, s16 rrw, s16 rrh); /* JP: sceGsSetDefStoreImage */
s32 func_001859D0(void *arg0, void *arg1); /* JP: sceGsExecStoreImage */
void func_00186060(u8 *arg0, s16 arg1, s16 arg2, s16 arg3); /* JP: sceGsSetHalfOffset */
void func_001860E8(s8 *arg0, s32 arg1); /* JP: memclr */
s32 func_00186120(s32 arg0); /* JP: sceDmaGetChan */
s32 func_00186148(s32 arg0); /* JP: sceDmaReset */
s32 func_00186228(s32 arg0); /* JP: sceDmaDebug */
s32 func_00186238(void *arg0); /* JP: sceDmaPutEnv */
void *func_00186410(void *arg0); /* JP: sceDmaGetEnv */
s32 func_00186448(u32 arg0); /* JP: sceDmaPutStallAddr */
void func_00186470(void *arg0, void *tag); /* JP: sceDmaSend */
void func_00186548(void *arg0, void *addr, s32 size); /* JP: sceDmaSendN */
void func_00186630(void *arg0, void *addr, s32 size); /* JP: sceDmaSendI */
void func_00186718(void *arg0); /* JP: sceDmaRecv */
void func_001867E0(void *arg0, void *addr, s32 size); /* JP: sceDmaRecvN */
void func_001868D0(void *arg0, void *addr, s32 size); /* JP: sceDmaRecvI */
s32 func_001869C0(void *arg0, s32 mode, s32 timeout); /* JP: sceDmaSync */
s32 func_00186A88(void *arg0, void *addr, s32 mode, s32 timeout); /* JP: sceDmaWatch */
s32 func_00186BA0(u32 *arg0, u32 arg1);
s32 func_00186BB8(void); /* JP: sceDevVu0CheckBusy */
void func_00186BD0(void); /* JP: sceDevVu0Reset */
s32 func_00186BE8(void); /* JP: sceDevVu0Pause */
s32 func_00186C48(void); /* JP: sceDevVu0Continue */
void func_00186C98(s32 on); /* JP: sceDevVu0PutDBit */
void func_00186CC8(s32 on); /* JP: sceDevVu0PutTBit */
s32 func_00186CF8(void); /* JP: sceDevVu0GetDBit */
s32 func_00186D08(void); /* JP: sceDevVu0GetTBit */
s32 func_00186D18(void); /* JP: sceDevVu0Sync */
void func_00186D58(s32 addr); /* JP: sceDevVu0Exec */
u32 func_00186D68(void); /* JP: sceDevVu0GetTpc */
s32 func_00186D78(void *arg0); /* JP: sceDevVu0GetCnd */
s32 func_00186E58(void *arg0); /* JP: sceDevVu0PutCnd (matched by position) */
void func_00186FC8(void); /* JP: sceDevVif0Reset */
s32 func_00186FF0(s32 arg0); /* JP: sceDevVif0Pause */
s32 func_00187058(void); /* JP: sceDevVif0Continue */
u32 func_00187098(u32 arg0, u32 arg1, u32 arg2); /* JP: sceDevVif0PutErr */
s32 func_001870B8(void); /* JP: sceDevVif0GetErr */
u32 func_001870C8(void); /* JP: sceDevVif0Sync */
s32 func_00187118(void *arg0); /* JP: sceDevVif0GetCnd */
s32 func_00187298(__int128 *data, s32 n); /* JP: sceDevVif0PutFifo */
void func_001872F8(void *p0, u64 p1); /* JP: sceGifPkInit */
void func_00187308(void *arg0); /* JP: sceGifPkReset */
s32 func_00187318(void *arg0); /* JP: sceGifPkTerminate */
void func_00187370(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: sceGifPkCnt */
void func_001873E8(void *arg0, s32 addr, s32 size, s32 a3, s32 a4, s32 a5); /* JP: sceGifPkRef */
void func_00187480(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: sceGifPkEnd */
void *func_001874F8(void *p0, s32 p1); /* JP: sceGifPkReserve */
void func_00187510(s32 *arg0, __int128 arg1); /* JP: sceGifPkOpenGifTag */
void func_00187528(void *arg0); /* JP: sceGifPkCloseGifTag (matched by position) */
void func_001875D0(u64 **arg0, u32 arg1, u64 arg2); /* JP: sceGifPkAddGsAD */
void func_001875F8(s32 *arg0, s32 arg1); /* JP: sceVif1PkInit */
s32 func_00187608(void *arg0); /* JP: sceVif1PkTerminate */
void func_00187660(void *arg0, s32 arg1); /* JP: sceVif1PkCnt */
void func_001876B8(void *arg0, __int128 arg1); /* JP: sceVif1PkOpenGifTag */
void func_001876D0(void *arg0); /* JP: sceVif1PkCloseGifTag (matched by position) */
void func_001877F8(s32 **arg0, s32 arg1); /* JP: sceVif1PkAddCode */
void func_00187810(s32 **arg0, s32 arg1); /* JP: sceVif1PkAddData */
void func_00187828(void *arg0, s32 arg1, s64 arg2); /* JP: sceVif1PkAddGsAD */
void func_00187858(void *arg0, s32 arg1); /* JP: sceVif1PkOpenDirectHLCode */
void func_001878B0(void *arg0); /* JP: sceVif1PkCloseDirectHLCode */
void func_001878E0(void *p0, void *p1, void *p2); /* JP: sceVu0ApplyMatrix */
void func_00187910(void *p0, void *p1, void *p2); /* JP: sceVu0MulMatrix */
void func_00187958(void *p0, void *p1, void *p2); /* JP: sceVu0OuterProduct */
float func_00187978(void *p0, void *p1); /* JP: sceVu0InnerProduct */
void func_001879A0(void *p0, void *p1); /* JP: sceVu0Normalize (matched by position) */
void func_001879E0(void *m0, void *m1); /* JP: sceVu0TransposeMatrix */
void func_00187A28(void *p0, void *p1); /* JP: sceVu0InversMatrix */
void func_00187A98(void *p0, void *p1, float f0); /* JP: sceVu0DivVector */
void func_00187AB8(void *p0, void *p1, float f0); /* JP: sceVu0DivVectorXYZ */
void func_00187AD8(void *p0, void *p1, void *p2, float f0); /* JP: sceVu0InterVector */
void func_00187B00(void *v0, void *v1, void *v2); /* JP: sceVu0AddVector */
void func_00187B18(void *v0, void *v1, void *v2); /* JP: sceVu0SubVector */
void func_00187B30(void *p0, void *p1, void *p2); /* JP: sceVu0MulVector */
void func_00187B48(void *p0, void *p1, float f0); /* JP: sceVu0ScaleVector */
void func_00187B60(void *p0, void *p1, void *p2); /* JP: sceVu0TransMatrix */
void func_00187B90(void *p0, void *p1); /* JP: sceVu0CopyVector */
void func_00187BA0(void *m0, void *m1); /* JP: sceVu0CopyMatrix */
void func_00187BC8(void *p0, void *p1); /* JP: sceVu0FTOI4Vector */
void func_00187BD8(void *p0, void *p1); /* JP: sceVu0FTOI0Vector */
void func_00187BE8(void *p0, void *p1); /* JP: sceVu0ITOF4Vector */
void func_00187BF8(void *p0, void *p1); /* JP: sceVu0ITOF0Vector */
void func_00187C08(void *p0); /* JP: sceVu0UnitMatrix */
void func_00187C30(void *p0, void *p1, void *p2, void *p3); /* JP: _sceVu0ecossin */
void func_00187CA8(void *p0, void *p1, float f0); /* JP: sceVu0RotMatrixZ */
void func_00187D50(void *p0, void *p1, float f0); /* JP: sceVu0RotMatrixX */
void func_00187DF8(void *p0, void *p1, float f0); /* JP: sceVu0RotMatrixY */
void func_00187EA0(s32 arg0, s32 arg1, void *arg2); /* JP: sceVu0RotMatrix */
void func_00187EF0(void *p0, void *p1, float f0, float f1); /* JP: sceVu0ClampVector */
void func_00187F18(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3); /* JP: sceVu0CameraMatrix */
void func_00187FC8(f32 (*m)[4], f32 *x, f32 *y, f32 *z); /* JP: sceVu0NormalLightMatrix */
void func_00188088(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: sceVu0LightColorMatrix */
void func_001880F0(f32 (*m)[4], f32 scrz, f32 ax, f32 ay, f32 cx, f32 cy, f32 zmin, f32 zmax, f32 nearz, f32 farz); /* JP: sceVu0ViewScreenMatrix */
void func_001881F8(f32 (*m)[4], f32 *lp, f32 a, f32 b, f32 c, s32 mode); /* JP: sceVu0DropShadowMatrix */
void func_00188388(void *p0, void *p1, void *p2, void *p3); /* JP: sceVu0RotTransPersN */
void func_001883E0(void *p0, void *p1, void *p2, void *p3); /* JP: sceVu0RotTransPers */
void func_00188428(f32 *arg0, f32 *arg1); /* JP: sceVu0CopyVectorXYZ */
void func_00188448(void *p0, void *p1, void *p2, float f0); /* JP: sceVu0InterVectorXYZ */
void func_00188478(void *p0, void *p1, float f0); /* JP: sceVu0ScaleVectorXYZ */
int func_00188490(void *p0); /* JP: sceVu0ClipScreen */
int func_001884D8(void *p0, void *p1, void *p2); /* JP: sceVu0ClipScreen3 */
int func_00188538(void *p0, void *p1, void *p2, void *p3); /* JP: sceVu0ClipAll */
void func_001885C8(void); /* JP: sceVpu0Reset */
void func_001893A8(void *arg0, s32 idx);
void func_001895C8(void *p0); /* JP: _rix_000 */
void func_00189640(void *p0); /* JP: _ri0_000 */
void func_001896D8(void *p0); /* JP: _rix_001 */
void func_00189790(void *p0); /* JP: _ri0_001 */
void func_00189860(void *p0); /* JP: _rix_010 */
void func_00189910(void *p0); /* JP: _ri0_010 */
void func_001899C8(void *p0); /* JP: _rix_011 */
void func_00189AC0(void *p0); /* JP: _ri0_011 */
void func_00189BC0(void *p0); /* JP: _rix_100 (matched by position) */
void func_00189C60(void *p0); /* JP: _ri0_100 */
void func_00189D10(void *p0); /* JP: _rix_101 (matched by position) */
void func_00189DF0(void *p0); /* JP: _ri0_101 */
void func_00189ED8(void *p0); /* JP: _rix_110 (matched by position) */
void func_00189FB0(void *p0); /* JP: _ri0_110 */
void func_0018A080(void *p0); /* JP: _rix_111 (matched by position) */
void func_0018A1A0(void *p0); /* JP: _ri0_111 */
void func_0018A2B8(void *p0, void *p1, void *p2); /* JP: _copyAddRefImage */
void func_0018A378(s32 arg0); /* JP: _ipuSetMPEG1 */
s32 func_0018A590(s32 arg0); /* JP: _dmVector (matched by position) */
void func_0018A5B0(void *arg0, s32 DMV[][2], s32 *dmvector, s32 mvx, s32 mvy); /* JP: _dualPrimeVector (matched by position) */
s32 func_0018A848(void *arg0); /* JP: _pictureData0 (matched by position) */
s32 func_0018A950(void *arg0, s32 arg1, s32 *arg2, s32 *arg3, void *arg4); /* JP: _sliceA0 (matched by position) */
s32 func_0018AA80(void *arg0, s32 arg1); /* JP: _slice0 (matched by position) */
s32 func_0018AC70(void *arg0, void *arg1, s32 *arg2, void *arg3, s32 *arg4); /* JP: _skipMB0 (matched by position) */
s32 func_0018B1D8(s32 *pred, s32 r_size, s32 motion_code, s32 motion_residual, s32 full_pel_vector); /* JP: decode_motion_vector */
void func_0018B260(s32 arg0, s32 PMV[2][2][2], s32 *dmvector, s32 sel[2][2], s32 s, s32 count, s32 fmt, s32 h_r, s32 v_r, s32 dmv, s32 mvscale);
void func_0018B400(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
s32 func_0018B550(void *arg0, s32 arg1);
void func_0018B580(void *arg0);
s64 func_0018B628(void *arg0);
s32 func_0018B850(void *arg0, s32 arg1);
s32 func_0018BA48(void *arg0, s32 arg1);
void func_0018BB98(void *arg0);
s32 func_0018BC18(void *arg0, s32 arg1);
s32 func_0018BC80(void *arg0);
void func_0018BD90(void *arg0, s32 arg1);
void func_0018BE58(void *d);
void func_0018BF80(void *arg0);
s32 func_0018C170(void *arg0);
s32 func_0018C1B8(void *arg0, s32 arg1);
void func_0018C230(void *arg0, s32 arg1);
void func_0018C2D0(void *arg0, s32 arg1);
void func_0018C398(void *arg0);
void func_0018C490(s32 arg0, s32 arg1);
s32 func_0018C520(void *arg0);
void func_0018C5F0(void *arg0, s32 arg1, s32 arg2);
s32 func_0018C938(void *arg0, s32 *arg1);
void func_0018C9D8(void *arg0, s32 *s);
void func_0018CC48(void *arg0);
void func_0018CC70(void *arg0, s32 *img, void *arg2, void *arg3, void *arg4);
void func_0018CE00(void *d, s32 arg1, s32 unused);
void func_0018CF10(void *d, s32 arg1, s32 arg2, s32 unused);
void func_0018D0C8(void *arg0);
void func_0018D220(s32 arg0, s32 arg1);
void func_0018D290(void *arg0, s32 arg1, s32 arg2);
s32 func_0018D3A8(s32 ch, void *arg);
s32 func_0018D6D0(s32 arg0, void *arg1);
void func_0018D7D8(void *arg0, s32 *arg1);
void func_0018DA50(u64 *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: _sysbitInit */
s32 func_0018DA88(u64 *arg0, s32 arg1); /* JP: _sysbitNext */
void func_0018DAA8(void *arg0, s32 n); /* JP: _sysbitFlush */
s32 func_0018DB40(u64 *arg0, s32 arg1); /* JP: _sysbitGet */
s32 func_0018DB90(u64 *arg0); /* JP: _sysbitMarker */
void func_0018DBD8(s32 *bs, s32 bytes); /* JP: _sysbitJump */
u32 func_0018DC30(void *arg0, s32 arg1); /* JP: _sysbitPtr */
s64 func_0018DC60(s32 type, s32 ch); /* JP: _type2id */
s32 func_0018DCE8(s32 *type, s32 *num, u64 id); /* JP: _id2type */
s32 func_0018E1E0(s32 arg0, s32 arg1, s32 arg2); /* JP: sceMpegDemuxPss */
s32 func_0018E200(void *arg0, s32 type, s32 ch, void *func, void *data); /* JP: sceMpegAddStrCallback */
s32 func_0018E2F8(u64 *arg0, void *arg1); /* JP: _pack_header */
s32 func_0018E448(u64 *arg0, void *arg1); /* JP: _system_header */
s32 func_0018E4B8(s32 mp, int *bs, void *arg2); /* JP: _PES_packet (matched by position) */
void func_0018EA68(void); /* JP: sceMpegInit (matched by position) */
s32 func_0018EB08(void *arg0, s32 arg1, s32 arg2); /* JP: sceMpegCreate (matched by position) */
s32 func_0018ED10(s32 unused0); /* JP: sceMpegDelete */
void func_0018ED18(void *arg0, s32 arg1, s32 arg2);
s32 func_0018ED40(void *arg0, s32 arg1, s32 arg2); /* JP: sceMpegGetPicture */
s32 func_0018ED88(void *arg0, s32 arg1, s32 arg2); /* JP: sceMpegGetPictureRAW8 */
s32 func_0018EDD0(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: sceMpegGetPictureRAW8xy */
void func_0018EE20(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: sceMpegSetDecodeMode */
void func_0018EE38(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3); /* JP: sceMpegGetDecodeMode */
s32 func_0018EE58(void *arg0); /* JP: sceMpegIsEnd */
s32 func_0018EE68(void *arg0); /* JP: sceMpegIsRefBuffEmpty */
void func_0018EE78(void *arg0); /* JP: sceMpegReset (matched by position) */
s32 func_0018EEC8(void *arg0); /* JP: sceMpegClearRefBuff (matched by position) */
s32 func_0018EF20(void *arg0, s32 arg1, s32 (*arg2)(), s32 arg3); /* JP: sceMpegAddCallback */
s32 func_0018EF48(s32 arg0, void *arg1); /* JP: _dispatchMpegCallback */
void func_0018EF98(s32 arg0); /* JP: _dispatchMpegCbNodata */
void func_0018EFC0(void *arg0, s64 arg1); /* JP: sceMpegSetDefaultPtsGap */
void func_0018EFD8(void *arg0); /* JP: sceMpegResetDefaultPtsGap */
void func_0018EFE8(void *arg0, s32 arg1);
s32 func_0018EFF8(void *arg0); /* JP: sceMpegDispWidth */
s32 func_0018F008(void *arg0); /* JP: sceMpegDispHeight */
s32 func_0018F018(void *arg0); /* JP: sceMpegDispCenterOffX */
s32 func_0018F028(void *arg0); /* JP: sceMpegDispCenterOffY */
s32 func_0018F038(void *arg0, s32 arg1); /* JP: sceSetBrokenLink */
void func_0018F048(void *arg0, s64 arg1); /* JP: sceSetPtm */
void func_0018F060(void *arg0, s32 arg1, s32 arg2); /* JP: _alalcInit */
void func_0018F078(void *arg0); /* JP: _alalcSetDynamic */
void func_0018F088(void *arg0); /* JP: _alalcFree */
s32 func_0018F098(s32 arg0, void *arg1, s32 arg2, u32 arg3); /* JP: _alalcAlloc (matched by position) */
s32 func_0018F108(s32 *arg0); /* JP: _alalcRest */
s32 func_0018F120(void *arg0); /* JP: _getpic (matched by position) */
s32 func_0018F3A8(void *arg0, s32 arg1, s32 arg2); /* JP: _decodeOrSkip (matched by position) */
s32 func_0018F3F0(void *arg0, s32 arg1, s32 arg2); /* JP: _decodeOrSkipField (matched by position) */
s32 func_0018F550(void *arg0); /* JP: _sceMpegFlush (matched by position) */
void func_0018F5B8(void *arg0); /* JP: _initSeqAgain (matched by position) */
void func_0018F5C8(void *arg0); /* JP: _lastFrame (matched by position) */
void func_0018F648(void *arg0); /* JP: _clearOnce (matched by position) */
void func_0018F6A8(void *arg0); /* JP: _clearEach (matched by position) */
void func_0018F768(s32 arg0); /* JP: _ErrMessage */
void func_0018F778(s32 arg0, void *arg1, s32 arg2); /* JP: _Error1 (matched by position) */
void func_0018F7B0(s32 arg0, void *arg1); /* JP: _Error (matched by position) */
s32 func_0018F8F8(void *arg0, s32 arg1, s32 arg2); /* JP: _RefImageInit */
void func_0018F918(void *arg0); /* JP: _sequenceHeader (matched by position) */
void func_0018FCE8(int *frame0, int *frame1, int *frame2, int *top0, int *top1, int *top2, int *bot0, int *bot1, int *bot2, int y, int cb, int cr, int width, int height); /* JP: _initRefImages (matched by position) */
void func_0018FDC8(void *arg0, s32 arg1, s32 arg2); /* JP: _setDefaultQM (matched by position) */
void func_0018FEA0(void *arg0); /* JP: _sequenceExtension (matched by position) */
void func_0018FFD0(void *arg0, s32 arg1); /* JP: _sequenceDisplayExtension (matched by position) */
void func_00190060(s32 arg0); /* JP: _sequenceScalableExtension (matched by position) */
void func_00190070(s32 arg0); /* JP: _unknown_extension (matched by position) */
void func_00190080(s32 arg0); /* JP: _pictureSpatialScalableExtension (matched by position) */
void func_00190090(s32 arg0); /* JP: _pictureTemporalScalableExtension (matched by position) */
void func_001900A0(void *arg0); /* JP: _defStopDMA */
void func_001900B0(void *arg0); /* JP: _defRestartDMA */
void func_001900C0(s32 arg0);
void func_00190128(s32 arg0);
void func_00190190(s32 arg0);
void func_00190278(s32 arg0);
s32 func_001903C8(s32 arg0, s32 arg1); /* JP: sceIpuSync */
void func_00190430(s32 arg0);
void func_00190498(void);
s32 func_001906D0(void);
s32 func_00190778(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00190800(s32 arg0);
void func_00190A00(s32 arg0, s32 arg1, s32 arg2);
void func_00190A28(u16 arg0); /* JP: sceCdDelayThread */
s32 func_00190A90(void (*arg0)(void));
void func_00190AE8(void *data); /* JP: cd_callback (matched by position) */
void func_00190B88(void); /* JP: _Cdvd_cbLoop (matched by position) */
s32 func_00190C48(s32 arg0, void *arg1, s32 arg2); /* JP: sceCdInitEeCB */
void func_00190D20(void *arg0); /* JP: cd_read_intr */
void func_00190DC0(void); /* JP: cmd_sem_init */
void func_00190E58(void); /* JP: cdvd_exit (matched by position) */
s32 func_00190ED8(s32 arg0, s32 arg1);
void func_00190F48(void);
s32 func_00190F88(void);
s32 func_00190FF0(void *arg0, const char *name); /* JP: sceCdSearchFile (matched by position) */
s32 func_001912F0(int cmd); /* JP: ncmd_prechk */
s32 func_00191460(void);
s32 func_001914F8(s32 arg0); /* JP: sceCdSync */
s32 func_00191598(s32 arg0); /* JP: sceCdSyncS */
s32 func_00191608(int cmd); /* JP: scmd_prechk */
s32 func_00191778(s32 mode);
s32 func_00191A58(int mode);
s32 func_00191C50(s32 arg0);
s32 func_00191D18(s32 lsn, s32 sectors, s32 buf, void *arg3);
s32 func_00191EF8(void);
s32 func_00191F90(s32 arg0, s32 arg1, s32 arg2); /* JP: sceCdStInit */
s32 func_00191FC0(s32 arg0, s32 *arg1); /* JP: sceCdStStart */
s32 func_00191FF8(s32 arg0); /* JP: sceCdStSeekF */
s32 func_00192028(s32 arg0); /* JP: sceCdStSeek */
s32 func_00192058(void); /* JP: sceCdStStop */
s32 func_00192090(s32 sectors, s32 buf, s32 mode, s32 *err); /* JP: sceCdStRead (matched by position) */
s32 func_00192218(void); /* JP: sceCdStPause */
s32 func_00192268(void); /* JP: sceCdStResume */
s32 func_001922C0(void); /* JP: sceCdStStat */
s32 func_00192308(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4); /* JP: sceCdStream (matched by position) */
s32 func_00192470(s32 port, s32 slot); /* JP: _send_to_iop (matched by position) */
s32 func_00192588(s32 a0); /* JP: scePadInit */
s32 func_001926C8(s32 a0); /* JP: scePadInit2 */
s32 func_00192768(void); /* JP: scePadEnd */
s32 func_001927E8(s32 port, s32 slot, void *addr); /* JP: scePadPortOpen (matched by position) */
s32 func_001929D0(s32 port, s32 slot); /* JP: scePadPortClose */
u8 *func_00192A88(s32 arg0, s32 arg1); /* JP: scePadGetDmaStr */
s32 func_00192AE8(s32 port, s32 slot); /* JP: scePadGetFrameCount */
s32 func_00192B38(s32 port, s32 slot, u8 *data); /* JP: scePadRead */
s32 func_00192BB8(s32 port, s32 slot); /* JP: scePadGetState */
void func_00192C30(u32 arg0, s8 *arg1); /* JP: scePadStateIntToStr */
s32 func_00192C68(s32 port, s32 slot, s32 state); /* JP: scePadSetReqState */
u8 func_00192CD0(s32 port, s32 slot); /* JP: scePadGetReqState */
void func_00192D20(u32 arg0, s8 *arg1); /* JP: scePadReqIntToStr */
s32 func_00192D58(s32 port, s32 slot, s32 term, s32 offs); /* JP: scePadInfoAct */
s32 func_00192E78(s32 port, s32 slot, s32 actno, s32 term); /* JP: scePadInfoComb */
s32 func_00192F98(s32 port, s32 slot, s32 term, s32 offs); /* JP: scePadInfoMode */
s32 func_001930D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: scePadSetMainMode */
s32 func_00193188(s32 port, s32 slot, u8 *data); /* JP: scePadSetActDirect (matched by position) */
s32 func_00193248(s32 arg0, s32 arg1, u8 *arg2); /* JP: scePadSetActAlign */
s32 func_00193320(s32 port, s32 slot); /* JP: scePadGetButtonMask */
s32 func_001933D8(s32 arg0, s32 arg1, s32 arg2); /* JP: scePadSetButtonInfo */
s32 func_00193488(s32 port, s32 slot); /* JP: scePadInfoPressMode */
s32 func_001934E8(s32 port, s32 slot); /* JP: scePadEnterPressMode */
s32 func_00193540(s32 port, s32 slot); /* JP: scePadExitPressMode */
s32 func_00193598(s32 port, s32 slot, u8 *data); /* JP: scePadSetVrefParam */
s32 func_00193668(void); /* JP: scePadGetPortMax */
s32 func_001936D0(s32 arg0); /* JP: scePadGetSlotMax */
s32 func_00193738(void); /* JP: scePadGetModVersion */
s32 func_001937A0(s32 arg0); /* JP: scePadSetWarningLevel */
s32 func_00193808(void);
s32 func_001939C0(void);
s32 *func_00193A00(s32 **arg0, s32 **arg1);
s32 func_00193A30(s32 arg0);
s32 func_00193AE8(s32 arg0);
s32 func_00193BA8(s32 arg0, s32 arg1, s8 *arg2, s32 arg3);
s32 func_00193CE0(s32 arg0, s32 arg1, void *arg2); /* JP: sceMcMkdir */
s32 func_00193D18(s32 arg0); /* JP: sceMcClose (matched by position) */
s32 func_00193DD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00193EA8(void *arg0); /* JP: mceIntrReadFixAlign */
s32 func_00193F38(s32 arg0, s32 *arg1, s32 arg2);
s32 func_00194058(s32 arg0, void *arg1, s32 arg2);
void func_001941D8(s32 arg0, s32 arg1, s32 arg2);
void func_00194200(s32 arg0);
s32 func_00194248(s32 arg0, s32 *arg1, s32 *arg2);
void func_00194328(s32 arg0); /* JP: mceGetInfoApdx */
s32 func_00194380(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 *arg4);
s32 func_00194508(void);
s32 func_00194578(s32 arg0, s32 arg1, void *arg2, u32 arg3, s32 arg4, void *arg5);
void func_001946D0(void *arg0); /* JP: mceStorePwd */
s32 func_00194758(s32 arg0, s32 arg1, void *arg2, void *arg3);
s32 func_001948A8(s32 arg0, s32 arg1);
s32 func_00194970(s32 arg0, s32 arg1, s8 *arg2);
s32 func_00194A98(s32 arg0); /* JP: sceMcFlush (matched by position) */
s32 func_00194B50(s32 arg0, s32 arg1, s8 *arg2, void *arg3, s32 arg4);
s32 func_00194D28(s32 arg0, s32 arg1, s8 *arg2, void *arg3);
s32 func_00194E90(s32 arg0, s32 arg1);
s32 func_00194F58(s32 arg0, s32 arg1, s8 *arg2);
s32 func_00195070(s32 arg0); /* JP: abs */
void func_00195088(s32 arg0); /* JP: atof (matched by position) */
s32 func_001950A0(const char *s); /* JP: atoi */
void func_001950C8(s8 *arg0);
void func_001950E8(s32 arg0, s32 arg1);
void func_00195108(s32 arg0, s32 arg1);
void *func_00195140(void *ptr, u32 n, u32 size);
s32 func_001951F8(s32 *ptr, s32 fd);
s32 func_00195250(i2b_Bigint *b, i2b_Bigint *S);
void func_001966E8(void); /* JP: __env_lock */
void func_001966F0(void); /* JP: __env_unlock */
s32 func_001966F8(void); /* JP: __errno */
s32 func_00196708(nl_FILE *arg0); /* JP: fflush (matched by position) */
void func_00196820(void *arg0, s16 arg1, s16 arg2, s32 arg3); /* JP: std (matched by position) */
nl_mglue *func_00196880(s32 d, s32 n); /* JP: __sfmoreglue (matched by position) */
void *func_001968F8(void *arg0); /* JP: __sfp (matched by position) */
s32 func_001969F0(s32 ptr);
void func_00196A10(void);
void func_00196A30(void *arg0); /* JP: __sinit (matched by position) */
u32 func_00196AC0(void *buf, u32 size, u32 count, void *arg3); /* JP: fread (matched by position) */
s32 func_00196ED8(s32 reent_ptr, u32 pad); /* JP: _malloc_trim_r (matched by position) */
s32 func_00197048(s32 *ptr, s32 fd, void *st); /* JP: _fstat_r (matched by position) */
s32 func_001970A8(void *arg0, void *arg1); /* JP: __sfvwrite (matched by position) */
s32 func_00197488(u8 *ptr, s32 (*function)(nl_FILE *)); /* JP: _fwalk (matched by position) */
void func_00197520(s32 arg0, s32 arg1); /* JP: _findenv (matched by position) */
u8 *func_00197548(s32 arg0); /* JP: getenv (matched by position) */
s32 func_00197570(s32 reent_ptr, s32 arg1, s32 arg2); /* JP: _findenv_r (matched by position) */
void func_001976B8(s32 arg0, s32 arg1); /* JP: _getenv_r */
char *func_001976D8(char *arg0, s32 arg1);
s32 func_001976F0(s32 p, s32 category, s32 locale); /* JP: _setlocale_r (matched by position) */
s32 *func_00197780(void); /* JP: _localeconv_r */
void func_00197790(s32 arg0, s32 arg1); /* JP: setlocale (matched by position) */
s32 *func_001977B8(void); /* JP: localeconv (matched by position) */
s32 func_001977D8(s32 *ptr, s32 fd, s32 pos, s32 whence); /* JP: _lseek_r (matched by position) */
void func_00197838(void *arg0); /* JP: __smakebuf (matched by position) */
void *func_00197990(s32 arg0, s32 arg1);
void *func_001979F8(s32 reent_ptr, s32 arg1, s32 arg2); /* JP: _memalign_r (matched by position) */
s32 func_00197BC0(s32 arg0);
s32 func_00197C18(s32 arg0);
void func_00197C60(s32 reent_ptr, u32 nb); /* JP: malloc_extend_top (matched by position) */
void *func_00197EB8(s32 reent_ptr, s32 bytes); /* JP: _malloc_r (matched by position) */
s32 func_001985E0(void *r, s32 *pwc, const char *s, u32 n, s32 *state); /* JP: _mbtowc_r (matched by position) */
void *func_00198618(const void *s, s32 c, u32 n); /* JP: memchr */
s32 func_001986F8(s32 *a, s32 *b, s32 n); /* JP: memcmp */
void *func_00198790(void *dst, const void *src, s32 n); /* JP: memcpy (matched by position) */
s32 func_00198840(s32 dst, s32 src); /* JP: memmove (matched by position) */
void *func_00198948(void *dst, s32 c, u32 n); /* JP: memset (matched by position) */
void func_00198A08(s32 r);
s32 func_00198A88(s32 r);
i2b_Bigint *func_00198AD8(void *ptr, s32 k); /* JP: _Balloc (matched by position) */
void func_00198B80(void *arg0, void *arg1); /* JP: _Bfree */
i2b_Bigint *func_00198BB0(void *ptr, i2b_Bigint *b, s32 m, s32 a);
i2b_Bigint *func_00198CB8(void *ptr, const char *s, s32 nd0, s32 nd, u32 y9);
s32 func_00198DE8(u32 x);
s32 func_00198E68(u32 *y);
i2b_Bigint *func_00198F28(void *ptr, s32 i);
i2b_Bigint *func_00198F60(void *ptr, i2b_Bigint *a, i2b_Bigint *b);
i2b_Bigint *func_00199170(void *arg0, i2b_Bigint *b, s32 k);
i2b_Bigint *func_00199270(void *ptr, i2b_Bigint *b, s32 k);
s32 func_001993C8(mcmp_Bigint *a, mcmp_Bigint *b);
i2b_Bigint *func_00199430(void *ptr, i2b_Bigint *a, i2b_Bigint *b);
double func_001995C0(double _x);
double func_00199690(i2b_Bigint *a, s32 *e);
double func_001999B0(i2b_Bigint *a, i2b_Bigint *b);
double func_00199A80(s32 dig);
s32 func_00199AF0(vf_reent *ptr, const char *fmt, ...);
void func_00199B50(const char *fmt, ...);
void func_00199BC0(s32 arg0, u32 n, u32 es, void (*arg3)(void));
void func_0019A5B0(s64 arg0);
s32 func_0019A5C8(void);
s64 func_0019A630(s32 *ptr, s32 fd, s32 buf, s32 cnt);
s32 func_0019AC30(void *arg0);
s32 func_0019AC68(void *arg0);
double func_0019ADE8(double x, double y);
s32 func_0019AE30(double x);
s32 func_0019AE78(double x);
double func_0019AEB8(double x, s32 n);
void *func_0019B0A0(s32 *ptr, s32 incr);
void func_0019B0F8(s32 arg0, s32 arg1, s32 arg2);
void func_0019B128(s32 arg0);
s32 func_0019B148(s32 reent_ptr, s32 name, s32 arg2, s32 rewrite);
s32 func_0019B418(s32 reent_ptr, s32 name);
f32 func_0019B4B8(f32 fparg0, f32 fparg1);
f32 func_0019B4F8(f32 x, s32 n);
s32 func_0019B5C0(void *ptr, char *str, const char *fmt, ...);
s32 func_0019B648(char *str, const char *fmt, ...);
s32 func_0019B6D8(void); /* JP: eofread */
s32 func_0019B6E0(const char *str, const char *fmt, ...); /* JP: sscanf (matched by position) */
s32 func_0019B788(void *cookie, char *buf, s32 n); /* JP: __sread (matched by position) */
s32 func_0019B7F0(void *arg0, s32 arg1, s32 arg2); /* JP: __swrite (matched by position) */
s64 func_0019B870(void *cookie, s64 offset, s32 whence); /* JP: __sseek (matched by position) */
void func_0019B8D8(void *arg0); /* JP: __sclose (matched by position) */
s32 func_0019B8F8(const char *s1, const char *s2); /* JP: strcasecmp (matched by position) */
char *func_0019B9D0(char *dst, const char *src); /* JP: strcat */
char *func_0019BB00(char *s, s32 c); /* JP: strchr */
s32 func_0019BC90(const char *a, const char *b); /* JP: strcmp */
char *func_0019BDD8(char *dst, const char *src); /* JP: strcpy (matched by position) */
s32 func_0019BEF0(const char *s); /* JP: strlen */
s32 func_0019C028(const char *s1, const char *s2, u32 n); /* JP: strncasecmp (matched by position) */
s32 func_0019C100(const char *a, const char *b, u32 n); /* JP: strncmp */
void *func_0019C2B8(void *dst, const void *src, u32 n); /* JP: strncpy (matched by position) */
char *func_0019C478(const char *s, s32 i); /* JP: strrchr */
double func_0019C4C8(void *ptr0, const char *s00, char **se);
void func_0019D3E0(s32 arg0, s32 arg1);
f32 func_0019D408(s32 s, s32 ptr);
char *func_0019D430(char *s, const char *delim);
char *func_0019D450(char *s, const char *delim, char **lasts);
long func_0019D518(s32 rptr, const char *nptr, char **endptr, s32 base);
long func_0019D750(const char *arg0, char **arg1, s32 arg2);
u64 func_0019D780(s32 rptr, const char *nptr, char **endptr, s32 base);
void func_0019D9B0(s32 arg0, s32 arg1, s32 arg2);
s32 func_0019D9E0(s32 c);
s32 func_0019DA00(void *arg0);
s32 func_0019DAE8(s32 c, void *arg1);
s32 func_0019DC70(s32 arg0, void *arg1);
s32 func_0019DCB8(void *arg0, const char *fmt, void *ap);
s32 func_0019DD70(vf_FILE *fp, const char *fmt0, void *ap);
s32 func_0019DDE8(vf_reent *data, vf_FILE *fp_0019DDE8, const char *fmt0, void *ap_0019DDE8);
char *func_0019F448(void *data, double value, s32 ndigits, s32 flags, char *sign, s32 *decpt, s32 ch, s32 *length);
s32 func_0019F608(char *p0, s32 exp, s32 fmtch);
s32 func_0019F6E8(void *fp_0019F6E8, const char *fmt0, void *ap0);
char *func_001A0378(char *tab, char *fmt);
s64 func_001A0478(s32 *ptr, s32 fd, s32 buf, s32 cnt);
s32 func_001A04D8(void *arg0);
s64 func_001A05E8(s64 u, s64 v);
s64 func_001A0660(s64 u, s64 v);
s64 func_001A0CF8(s64 u, s64 v);
u64 func_001A1388(u64 n, u64 d);
u64 func_001A1908(u64 u, u64 v);
double func_001A1E70(s64 u);
u64 func_001A2000(double a);
s64 func_001A2118(double a);
f32 func_001A2190(fp_number_f *src);
void func_001A2260(fp_union_f *src, fp_number_f *dst);
s64 func_001A22C0(f32 arg_a);
f32 func_001A2340(fp_class_type class, u32 sign, s32 exp, u32 frac);
double func_001A2370(f32 arg_a);
s32 func_001A23B0(f32 arg_a);
double func_001A2430(fp_number_d *src);
void func_001A2548(fp_union_d *src, fp_number_d *dst);
fp_number_d *func_001A25F8(fp_number_d *a, fp_number_d *b, fp_number_d *tmp);
double func_001A2858(double arg_a, double arg_b);
double func_001A28B0(double arg_a, double arg_b);
double func_001A2918(double arg_a, double arg_b);
double func_001A2BC8(double arg_a, double arg_b);
s32 func_001A2D40(fp_number_d *a, fp_number_d *b);
s32 func_001A2E60(double arg_a, double arg_b);
double func_001A2EB0(s32 arg_a);
s32 func_001A2F68(double arg_a);
double func_001A3008(fp_class_type class, u32 sign, s32 exp, u64 frac);
f32 func_001A3038(double arg_a);
u32 func_001A3090(double arg_a);
double func_001A4088(double x);
f32 func_001A43A8(f32 x);
f32 func_001A4760(f32 y, f32 x);
f32 func_001A4948(f32 x, f32 y);
f32 func_001A4B18(f32 x, f32 y);
s32 func_001A5338(f32 x, f32 *y);
f32 func_001A5700(f32 x);
f32 func_001A57D8(f32 x, f32 y);
s32 func_001A5948(f32 *x, f32 *y, s32 e0, s32 nx, s32 prec, const s32 *ipio2);
f32 func_001A61F0(f32 x, f32 y, s32 iy);
f32 func_001A6318(f32 x, f32 y, s32 iy);
double func_001A65C0(double x);
f32 func_001A65F8(f32 x);
f32 func_001A6898(f32 x);
f32 func_001A6970(f32 x);
f32 func_001A6998(f32 x);
f32 func_001A6A88(f32 x);
f32 func_001A6B70(f32 x);
s32 func_001A6BE8(s64 arg0, s32 arg1);
f32 func_001A6C00(f32 x);
f32 func_001A6C18(f32 y, f32 x);
f32 func_001A6C30(f32 x, f32 y);
f32 func_001A6C48(f32 y, f32 x);
f32 func_001A6C60(f32 x);
void func_001A6C80(void);
void func_001A7380(void); /* JP: SzGame_ActMenu */
s32 func_001A82E0(s32 arg0); /* JP: SzGame_GetMenuNum */
s32 func_001A8320(s32 arg0, s32 arg1); /* JP: SzGame_SetMenuNum */
void func_001A8360(s32 arg0, s32 arg1, s32 arg2); /* JP: SzGame_PlayMovieNo */
s32 func_001A83E0(u8 *arg0, s32 arg1, s32 arg2); /* JP: SzGame_PlayMovie */
void func_001A8520(s64 arg0, s32 arg1, s32 arg2, s64 arg3, s64 arg4, s64 arg5); /* JP: SzGame_ClearGsMem */
s8 func_001A8690(void); /* JP: SzGame_InqAutoBlur */
void func_001A86A0(s32 arg0); /* JP: SzGame_SetAutoBlur */
s32 func_001A86D0(void); /* JP: SzGame_InqSoftFocus */
s32 func_001A86F0(void); /* JP: SzGame_VSync */
s32 func_001A8710(void); /* JP: SzGame_GetHSyncCount */
s32 func_001A8720(void); /* JP: SzGame_GetFrameCount */
s32 func_001A8730(void); /* JP: SzGame_AddFrameCount */
void func_001A8750(s32 arg0); /* JP: SzGame_SetFrameSpeed */
u8 func_001A8760(void); /* JP: SzGame_GetFrameSpeed */
void func_001A8770(s64 arg0); /* JP: SzGame_SetStabilizer */
s32 func_001A87A0(void); /* JP: SzGame_GetStabilizer */
void func_001A87C0(s32 arg0, s32 arg1); /* JP: SzGame_Goto */
void func_001A8870(s32 arg0, s32 arg1); /* JP: SzGame_Push */
void func_001A8920(void); /* JP: SzGame_Pop */
void func_001A8BB0(void); /* JP: SzGame_ComInit */
void func_001A9590(void); /* JP: SzGame_ModeDraw (matched by position) */
void func_001A9800(void); /* JP: SzGame_ModeDrawAfter */
void func_001A9F50(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: lSzGame_TEXTURE_TEST */
void func_001AA260(void); /* JP: SzGame_ModeAct (matched by position) */
void func_001AAD50(s32 arg0); /* JP: SzGame_ModeTerm */
s64 func_001AAF60(s32 arg0); /* JP: SzGame_GetMode */
void func_001AAFA0(s32 arg0); /* JP: SzGame_InitMemCardProc */
s32 func_001AB1D0(void); /* JP: SzGame_ActMemCardProc */
s32 func_001AC290(s32 arg0, s32 arg1, s32 *arg2); /* JP: lSzGame_GetMCardMsg (matched by position) */
void func_001AC510(void); /* JP: lSzGame_InitMemCheck */
void func_001AC560(void); /* JP: lSzGame_ActMemCheck */
void func_001AC600(void); /* JP: lSzGame_TermMemCheck */
void func_001AC610(s32 arg0); /* JP: lSzGame_InitTitle */
void func_001AC6F0(void); /* JP: lSzGame_TermTitle */
void func_001ACC50(void); /* JP: lSzGame_DrawTitle */
s32 func_001AD670(s32 packet, s32 id, s32 x, s32 y, s32 width, s32 height, f32 depth); /* JP: lSzGame_DrawTitle_Rose_Pipe */
void func_001AD960(void); /* JP: SzDuel_Initialize */
void func_001ADA80(s32 arg0); /* JP: lSzDuel_InitCom */
void func_001ADD00(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_Init */
void func_001AE520(void); /* JP: SzDuel_Term */
s32 func_001AE5A0(s32 arg0); /* JP: SzDuel_DrawStage_Pipe */
s32 func_001AE5F0(s32 arg0); /* JP: lSzDuel_DrawStage_Pipe */
void func_001AEE80(void); /* JP: SzDuel_DrawStageAfter */
s32 func_001AEEB0(s32 arg0); /* JP: SzDuel_DrawStageAfter_Pipe */
s32 func_001AEFC0(s32 arg0); /* JP: SzDuel_StartWindowSession_Pipe */
s32 func_001AEFD0(s32 arg0, s32 arg1); /* JP: SzDuel_StartWindowSessionWithPalette_Pipe */
s32 func_001AF110(s32 arg0); /* JP: SzDuel_FinishWindowSession_Pipe */
s32 func_001AF140(s32 arg0); /* JP: SzDuel_GetWindowTexture */
s32 func_001AF5C0(s32 arg0); /* JP: SzDuel_DrawHandCursor_Pipe */
void func_001AF7B0(void); /* JP: SzDuel_DrawDialog */
void func_001B1190(void); /* JP: SzDuel_DrawWindow */
s32 func_001B1EF0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawWindow_Level_Pipe */
s32 func_001B20E0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawWindow_SummonCost_Pipe */
s32 func_001B3100(s32 arg0, s32 arg1, s64 arg2, s64 arg3); /* JP: lSzDuel_DrawWindow_CommandGuide_Pipe (matched by position) */
s32 func_001B3640(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: lSzDuel_DrawWindow_Field_Pipe (matched by position) */
s32 func_001B3790(s32 arg0, s32 colorIndex, s32 card, s32 x, s32 y, f32 scale); /* JP: lSzDuel_DrawWindow_FieldPiece_Pipe */
void func_001B3C80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10); /* JP: lSzDuel_DrawWindow_Icon_Pipe */
s32 func_001B3CC0(s32 packet, u16 *src, s32 x, s32 y, s32 background, s32 image, s32 border, s32 shrink, s32 flipX, s32 flipY, s32 bright, u8 *rgb, s32 blend, u8 alpha); /* JP: lSzDuel_DrawWindow_ExIcon_Pipe */
s32 func_001B62F0(s32 packet, s32 x, s32 y, s32 columns, s32 rows); /* JP: lSzDuel_DrawWindow_Base_Pipe */
void func_001B65E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: lSzDuel_DrawWindow_Board_Pipe */
s32 func_001B65F0(s32 packet, s32 colorIndex, s32 x, s32 y, s32 w, s32 h, s32 shadow, s32 style); /* JP: lSzDuel_DrawWindow_ExBoard_Pipe */
void func_001B6C90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: SzDuel_DrawWindow_Digit_Pipe */
s32 func_001B6CA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7); /* JP: SzDuel_DrawWindow_ExDigit_Pipe */
void func_001B6EA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 flags, s32 width, s32 number); /* JP: SzDuel_DrawWindow_FontDigit_Pipe */
s32 func_001B6F70(s32 packet, s32 x, s32 y, s32 font, s32 flags, s32 count, s8 *text, u8 *color); /* JP: SzDuel_DrawWindow_Font_Pipe */
void func_001B76E0(s32 arg0, s32 arg1, s32 arg2, s8 *arg3, s32 *arg4, s32 *arg5); /* JP: lSzDuel_GetFontSize */
s32 func_001B7820(s32 packet, s32 x, s32 y, s32 alpha); /* JP: lSzDuel_DrawWindow_DualShock2_Pipe */
s32 func_001B7D60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s64 arg6); /* JP: lSzDuel_DrawWindow_PicItem_Pipe */
s32 func_001B7F90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s64 arg6, s32 arg7); /* JP: lSzDuel_DrawWindow_PicMini_Pipe */
void func_001B81E0(void); /* JP: SzDuel_DrawJoinFade */
s32 func_001B8210(s32 arg0); /* JP: SzDuel_DrawJoinFade_Pipe */
void func_001B8260(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: lSzDuel_Draw_Fade_Pipe */
void func_001B83C0(void); /* JP: SzDuel_DrawJoinCard */
s32 func_001B83F0(s32 arg0); /* JP: SzDuel_DrawJoinCard_Pipe */
void func_001B8520(s32 arg0); /* JP: SzDuel_InitBuildDeck */
void func_001B8720(void); /* JP: lSzDuel_ReBuildBag */
void func_001B8830(void); /* JP: SzDuel_TermBuildDeck */
void func_001B8840(void); /* JP: SzDuel_ActBuildDeck (matched by position) */
s32 func_001BA3B0(s32 arg0, s32 arg1); /* JP: lSzDuel_IsDeckReady */
s32 func_001BA420(u8 *arg0); /* JP: lSzDuel_HitPassword */
s32 func_001BA520(s32 arg0, s32 arg1, s64 arg2, s64 arg3, s64 arg4); /* JP: lSzDuel_ReqGhostCard */
void func_001BA5F0(void); /* JP: lSzDuel_SortBag */
void func_001BA610(void); /* JP: lSzDuel_SortDeck */
s32 func_001BA630(s32 arg0, s32 arg1); /* JP: lSzDuel_SortFunc1 */
s32 func_001BA710(s32 arg0, s32 arg1); /* JP: lSzDuel_SortFunc2 */
s32 func_001BA7F0(u16 *arg0, u16 *arg1); /* JP: lSzDuel_NewComerCmp */
s32 func_001BA8A0(u16 *arg0, u16 *arg1); /* JP: lSzDuel_ClassCmp */
s32 func_001BA930(u16 *arg0, u16 *arg1); /* JP: lSzDuel_NameCmp */
s32 func_001BA9C0(u16 *arg0, u16 *arg1); /* JP: lSzDuel_APCmp */
s32 func_001BAA30(u16 *arg0, u16 *arg1); /* JP: lSzDuel_DPCmp */
s32 func_001BAAA0(u16 *arg0, u16 *arg1); /* JP: lSzDuel_AttrCmp */
s32 func_001BAB60(u16 *arg0, u16 *arg1); /* JP: lSzDuel_LevelCmp */
s32 func_001BAC00(u16 *arg0, u16 *arg1); /* JP: lSzDuel_DeckCostCmp */
s32 func_001BAC90(u16 *arg0, u16 *arg1); /* JP: lSzDuel_RankCmp */
s32 func_001BAD40(u16 *arg0, u16 *arg1); /* JP: lSzDuel_CardColorCmp */
s32 func_001BAE40(u16 *arg0, u16 *arg1); /* JP: lSzDuel_NumberCmp */
void func_001BAE70(void); /* JP: SzDuel_DrawBuildDeck */
s32 func_001BAEA0(s32 arg0); /* JP: SzDuel_DrawBuildDeck_Pipe */
s32 func_001BB260(s32 arg0); /* JP: lSzDuel_DrawBuildDeck_Base_Pipe */
void func_001BC350(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawBuildDeck_Deck_Pipe */
s32 func_001BCCE0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawBuildDeck_Ghost_Pipe */
void *func_001BCE20(void *arg0, s32 card, s32 x, s32 y, s32 flag, s32 flag2); /* JP: lSzDuel_DrawBuildDeck_Card_Pipe */
s32 func_001BD8A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5); /* JP: lSzDuel_DrawBuildDeck_GhostCard_Pipe */
s32 func_001BF180(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: lSzDuel_DrawBuildDeck_Detail_Special_Pipe (matched by position) */
s32 func_001BFF00(s32 id, s32 arg1, s32 arg2, s32 arg3); /* JP: lSzDuel_DrawBuildDeck_BagCursor_Pipe */
s32 func_001C02E0(s32 id, s32 arg1, s32 arg2, s32 arg3); /* JP: lSzDuel_DrawBuildDeck_DeckCursor_Pipe */
void func_001C05F0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawBuildDeck_Reincarnation_Pipe */
s32 func_001C07E0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawBuildDeck_ReincarnationDone_Pipe */
s32 func_001C0CE0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawBuildDeck_PasswordSuccess_Pipe */
void func_001C0EE0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawBuildDeck_PasswordFail_Pipe */
void func_001C0F70(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawBuildDeck_PasswordDone_Pipe */
void func_001C1000(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawBuildDeck_Caution_Pipe */
void func_001C1090(s32 arg0); /* JP: SzDuel_Init3DView */
void func_001C1270(void); /* JP: SzDuel_Term3DView */
void func_001C12B0(void); /* JP: SzDuel_Act3DView */
void func_001C1AD0(void); /* JP: SzDuel_Draw3DView */
void func_001C1FE0(s32 arg0, f32 *position, u8 alpha, f32 width, f32 height); /* JP: lSzDuel_DrawFadeBoard_Pipe */
void func_001C21A0(void); /* JP: SzDuel_InitTrade */
void func_001C2300(s32 arg0); /* JP: lSzDuel_SetupTrade */
void func_001C2530(void); /* JP: SzDuel_TermTrade */
void func_001C2540(void); /* JP: SzDuel_ActTrade */
s32 func_001C2720(s32 player); /* JP: lSzDuel_ActTradeProc */
s32 func_001C32B0(void); /* JP: lSzDuel_TradeDo */
void func_001C33A0(s32 player); /* JP: lSzDuel_TradeDoSide */
void func_001C3520(s32 arg0); /* JP: lSzDuel_SortTrade */
void func_001C3570(void); /* JP: SzDuel_DrawTrade */
s32 func_001C35A0(s32 arg0); /* JP: SzDuel_DrawTrade_Pipe */
s32 func_001C38E0(s32 arg0); /* JP: lSzDuel_DrawTrade_Base_Pipe */
void func_001C3D50(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawTrade_Title_Pipe */
s32 func_001C5550(s32 id, s32 player, s32 arg2, s32 arg3, s32 arg4); /* JP: lSzDuel_DrawTrade_Cursor_Pipe */
void func_001C5980(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawTrade_Exit_Pipe */
void func_001C5B30(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawTrade_Do_Pipe */
void func_001C5CE0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawTrade_Notice_Pipe */
void func_001C6120(void); /* JP: SzDuel_TermCustomDuel */
s32 func_001C6130(void); /* JP: SzDuel_ActCustomDuel */
void func_001C7430(void); /* JP: SzDuel_DrawCustomDuel */
s32 func_001C7790(s32 arg0); /* JP: lSzDuel_DrawCustomDuel_Base_Pipe */
void func_001C7C00(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawCustomDuel_Title_Pipe */
s32 func_001C8590(s32 arg0, u8 *arg1, s32 arg2, s32 arg3); /* JP: lSzDuel_DrawCustomDuel_Menu_Pipe */
s32 func_001C8690(s32 arg0, u8 *arg1, s32 x, s32 y); /* JP: lSzDuel_DrawCustomDuel_Menu_Top_Pipe (matched by position) */
s32 func_001C8DC0(s32 arg0, u8 *arg1, s32 x, s32 y); /* JP: lSzDuel_DrawCustomDuel_Menu_SelectDeck_Pipe (matched by position) */
s32 func_001C92C0(s32 arg0, s32 player, s32 x, s32 y); /* JP: lSzDuel_DrawCustomDuel_Menu_LifeSet_Pipe */
s32 func_001C9C60(s32 arg0, u8 *arg1, s32 x, s32 y); /* JP: lSzDuel_DrawCustomDuel_Menu_SummonCharge_Pipe (matched by position) */
s32 func_001CA0E0(s32 arg0, u8 *arg1, s32 x, s32 y); /* JP: lSzDuel_DrawCustomDuel_Menu_LeaderAbility_Pipe */
s32 func_001CA450(s32 arg0, u8 *arg1, s32 x, s32 y); /* JP: lSzDuel_DrawCustomDuel_Menu_CardDisp_Pipe */
void func_001CC380(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_DrawCustomDuel_Exit_Pipe */
void func_001CC4B0(s32 arg0); /* JP: SzDuel_InitMapEdit */
void func_001CC610(void); /* JP: SzDuel_TermMapEdit */
void func_001CC620(void); /* JP: SzDuel_ActMapEdit */
void func_001CCB80(void); /* JP: SzDuel_DrawMapEdit */
s32 func_001CCBB0(s32 arg0); /* JP: SzDuel_DrawMapEdit_Pipe (matched by position) */
s32 func_001CCEA0(s32 arg0, s32 x, s32 y); /* JP: lSzDuel_DrawMapEdit_Graph_Pipe */
s32 func_001CD560(void *arg0); /* JP: SzDuel_ClearDrawCard */
void func_001CD6E0(void); /* JP: SzDuel_DrawAllCard */
s32 func_001CD710(s32 arg0); /* JP: SzDuel_DrawAllCard_Pipe */
void func_001CDA10(void); /* JP: SzDuel_InitCardRequest */
s32 func_001CDA60(void *arg0); /* JP: SzDuel_FreeCardRequest */
u8 *func_001CDAA0(void); /* JP: SzDuel_GetCardRequest */
s32 func_001CDB00(s32 arg0); /* JP: SzDuel_DrawCardRequest_Pipe */
void func_001CDD40(void); /* JP: SzDuel_InitCardControl */
s32 func_001CDD90(u8 *arg0); /* JP: SzDuel_ClearCardControl */
void *func_001CDE70(s32 arg0); /* JP: SzDuel_GetCardControl */
s32 func_001CDEB0(void *arg0); /* JP: SzDuel_DoCardControl0 */
void func_001CE400(void); /* JP: SzDuel_DrawUnit */
s32 func_001CE430(s32 arg0); /* JP: SzDuel_DrawUnit_Pipe */
void func_001CEA50(void); /* JP: SzDuel_DrawCardTest */
s32 func_001CECF0(s32 arg0, s32 arg1); /* JP: lSzDuel_GetControl */
void func_001D7D10(s32 arg0, s32 arg1); /* JP: lSzDuel_InitHandUp */
s32 func_001D8080(s32 arg0); /* JP: lSzDuel_InitHandCancel */
s32 func_001D82C0(s32 arg0); /* JP: lSzDuel_InitHandCombo */
s32 func_001D8880(s32 arg0, s32 arg1); /* JP: lSzDuel_InitHandDark */
s32 func_001D89F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: lSzDuel_InitHandInfo */
s32 func_001D8CD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: lSzDuel_InitHandInfo2 */
s32 func_001D8FB0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: lSzDuel_SetCardCtl */
s32 func_001D9030(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: lSzDuel_SetCardCtl2 */
void func_001D90E0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzDuel_LockCamera */
void func_001D91B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: lSzDuel_LockCamera2 */
s32 func_001D9420(void *arg0); /* JP: lSzDuel_IsUnitHide */
void func_001D95F0(void); /* JP: SzDuel_ActCardTest */
void func_001D9820(s32 arg0, s32 arg1); /* JP: SzDuel_InitTurn */
void func_001D99F0(void); /* JP: SzDuel_StartCardSession */
s32 func_001D9A20(s32 arg0); /* JP: SzDuel_StartCardSession_Pipe */
s32 func_001D9A30(s32 arg0, s32 arg1); /* JP: SzDuel_StartCardSessionWithPalette_Pipe (matched by position) */
s32 func_001D9C40(s32 arg0, s32 arg1); /* JP: lSzDuel_SetupCardTexture */
void func_001D9DD0(void); /* JP: SzDuel_FinishCardSession */
s32 func_001D9E00(s32 arg0); /* JP: SzDuel_FinishCardSession_Pipe */
s32 func_001D9E70(s32 arg0); /* JP: SzDuel_FinishCardSessionX_Pipe */
void func_001D9ED0(s32 arg0); /* JP: SzDuel_SetCardDefPrioZ */
void func_001D9EE0(s32 arg0); /* JP: SzDuel_SetWindowDefPrioZ */
s32 func_001D9EF0(void); /* JP: SzDuel_GetUserGsAddress */
s32 func_001D9F00(void *arg0, s32 arg1); /* JP: SzDuel_GetCardNode */
s32 func_001DA2B0(void *arg0, s32 arg1, f32 fparg0, f32 fparg1); /* JP: SzDuel_GetCardNodeOnScreen */
s32 func_001DA4C0(s32 mode, void *dst); /* JP: SzDuel_GetCardNodeUnit */
s32 func_001DA5E0(s32 arg0, f32 x, f32 y, void *arg1, void *arg2); /* JP: SzDuel_GetCardNodeUnitOnScreen */
void func_001DA7A0(s32 arg0, s32 arg1); /* JP: SzDuel_SetupCard */
s32 func_001DBC40(s32 arg0, s32 arg1, void *arg2); /* JP: SzDuel_SetupCard2_Pipe */
void func_001DBCF0(s32 arg0); /* JP: SzDuel_DrawCard */
s32 func_001DBD30(s32 arg0, s32 arg1); /* JP: SzDuel_DrawCard_Pipe */
s32 func_001DBD50(s32 arg0, f32 *position, f32 width, f32 height, s32 arg2, u8 *color, s32 arg4); /* JP: SzDuel_DrawCursor_Pipe */
void func_001DBFE0(s32 arg0, f32 *arg1, u8 *arg2, s32 arg3); /* JP: SzDuel_DrawBoxCursor_Pipe */
s32 func_001DC790(s32 arg0, s32 arg1, f32 *arg2, s32 arg3, s32 arg4); /* JP: SzDuel_DrawLeaderBase_Pipe */
void func_001DCC90(void *arg0); /* JP: SzDuel_InitMapInfo */
void *func_001DCD00(s32 arg0, s32 arg1); /* JP: SzDuel_GetMapInfo */
void func_001DCD70(void *arg0, s32 arg1); /* JP: SzDuel_InitCardInfo */
u8 *func_001DD0E0(s32 arg0); /* JP: SzDuel_GetCardConstInfo */
void *func_001DD130(s32 group, s32 index); /* JP: SzDuel_GetCardInfo */
void func_001DD220(void); /* JP: SzDuel_DoUnitRequest */
s32 func_001DD890(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_TrimUnitDir */
s32 func_001DD990(s32 arg0, s32 arg1); /* JP: SzDuel_TrimUnitDir1 */
s32 func_001DDAC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_TrimUnitDir2 */
void func_001DDD80(s32 arg0, s32 arg1, s32 arg2, void *arg3); /* JP: SzDuel_SetupDuel */
void func_001DDE80(s32 arg0); /* JP: SzDuel_SetupMap */
s32 func_001DE020(s32 arg0); /* JP: SzDuel_Kind2Type */
s32 func_001DE090(s64 arg0, s32 arg1); /* JP: SzDuel_Type2Attr */
s32 func_001DE0B0(s32 arg0, s32 arg1); /* JP: SzDuel_Kind2Attr */
s32 func_001DE130(s32 arg0); /* JP: SzDuel_Xax2New */
s32 func_001DE1A0(s32 arg0); /* JP: SzDuel_New2Xax */
s32 func_001DE210(s32 arg0); /* JP: SzDuel_GetMsgName (matched by position) */
s32 func_001DE260(s32 arg0); /* JP: SzDuel_GetCamDist */
void func_001DE2A0(void); /* JP: SzDuel_GetOption3DBattle */
s32 func_001DE2B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: SzDuel_GetPlayMotion */
u8 func_001DE4E0(s32 arg0); /* JP: SzDuel_GetPlayer */
void func_001DE500(s32 arg0, s32 arg1); /* JP: SzDuel_SetPlayer */
s32 func_001DE540(void); /* JP: SzDuel_GetTurnOwner */
u8 func_001DE550(void); /* JP: SzDuel_GetTurnFirst */
u8 func_001DE560(void); /* JP: SzDuel_GetTurnCount */
void func_001DE570(s32 arg0); /* JP: SzDuel_SetTurnCount */
s32 func_001DE5C0(s32 arg0); /* JP: SzDuel_GetSummonPower */
s32 func_001DE5E0(s32 index, s32 operation, s32 value); /* JP: SzDuel_CalcSummonPower */
u8 func_001DE690(s32 arg0); /* JP: SzDuel_GetSummonCharge */
void func_001DE6B0(s32 arg0, s8 arg1); /* JP: SzDuel_SetSummonCharge */
s32 func_001DE6D0(s32 arg0); /* JP: SzDuel_InqHandPhase */
void func_001DE700(s32 arg0, s32 arg1); /* JP: SzDuel_SetHandPhase */
u8 func_001DE740(s32 arg0); /* JP: SzDuel_InqDestinyFlag */
void func_001DE760(s32 arg0, s8 arg1); /* JP: SzDuel_SetDestinyFlag */
s32 func_001DE780(void); /* JP: SzDuel_GetWindowDisp */
void func_001DE7A0(s32 arg0); /* JP: SzDuel_SetWindowDisp */
void func_001DE7E0(s32 arg0); /* JP: SzDuel_SetWindowDraw */
void func_001DE820(s32 arg0); /* JP: SzDuel_SetWindowBusy */
s32 func_001DE860(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetPlayerCur */
void func_001DE970(s32 arg0); /* JP: SzDuel_InitDeck */
s32 func_001DE9C0(s32 arg0); /* JP: SzDuel_GetDeckCount */
s32 func_001DE9E0(s32 arg0, s32 arg1); /* JP: SzDuel_InqDeck */
s32 func_001DEA30(s32 player, s32 card); /* JP: SzDuel_AddDeck */
void func_001DEB20(s32 arg0); /* JP: SzDuel_PackDeck */
s32 func_001DEC00(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetDeck */
s32 func_001DECC0(s32 arg0, s32 arg1); /* JP: SzDuel_DelDeck */
s32 func_001DED30(s32 arg0); /* JP: SzDuel_DrawDeck */
void func_001DEDB0(s32 arg0); /* JP: SzDuel_InitGrave */
s32 func_001DEE00(s32 arg0, s32 arg1); /* JP: SzDuel_InqGrave */
u8 func_001DEE50(s32 arg0); /* JP: SzDuel_GetGraveCount */
s32 func_001DEE70(s32 arg0, s32 arg1); /* JP: SzDuel_AddGrave */
void func_001DEF20(s32 arg0); /* JP: SzDuel_PackGrave */
s32 func_001DF000(s32 arg0, s32 arg1); /* JP: SzDuel_DelGrave */
void func_001DF070(s32 arg0); /* JP: SzDuel_InitHand */
s32 func_001DF0C0(s32 arg0, s32 arg1); /* JP: SzDuel_InqHand */
s32 func_001DF110(s32 arg0); /* JP: SzDuel_GetHandCount */
s32 func_001DF130(s32 arg0, s32 arg1); /* JP: SzDuel_AddHand */
void func_001DF1E0(s32 index); /* JP: SzDuel_PackHand */
s32 func_001DF2C0(s32 arg0, s32 arg1); /* JP: SzDuel_DelHand */
s32 func_001DF330(s32 arg0); /* JP: SzDuel_ClearHandTag */
s32 func_001DF370(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetHandTag */
s32 func_001DF470(s32 arg0); /* JP: SzDuel_GetLP */
s32 func_001DF490(s32 index, s32 operation, s32 value); /* JP: SzDuel_CalcLP */
s32 func_001DF540(s32 arg0, s32 arg1); /* JP: SzDuel_GetUnit */
void func_001DF580(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: SzDuel_AddUnit */
s32 func_001DFAF0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_PutUnit */
s32 func_001DFBB0(s32 arg0, s32 arg1); /* JP: SzDuel_DelUnit */
void *func_001DFD50(s32 arg0, s32 arg1, s32 x, s32 y); /* JP: SzDuel_MoveUnit */
s32 func_001E0110(s32 arg0); /* JP: SzDuel_GetUnitCount */
s32 func_001E0150(s32 arg0); /* JP: SzDuel_GetUnitMonsterCount */
s32 func_001E01F0(s32 arg0); /* JP: SzDuel_GetUnitSpellCount */
s32 func_001E0290(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_GetUnitAP */
s32 func_001E02F0(void *arg0, s32 arg1); /* JP: SzDuel_GetUnitAP2 */
s32 func_001E0370(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_GetUnitDP */
s32 func_001E03D0(void *arg0, s32 arg1); /* JP: SzDuel_GetUnitDP2 */
void func_001E0450(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_CalcUnitAP */
s32 func_001E04C0(void *arg0, s32 arg1, s32 arg2); /* JP: SzDuel_CalcUnitAP2 */
s32 func_001E0570(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_CalcUnitDP */
s32 func_001E05E0(void *arg0, s32 arg1, s32 arg2); /* JP: SzDuel_CalcUnitDP2 */
s32 func_001E0690(s32 unused0, s32 unused1); /* JP: SzDuel_GetUnitConstKind */
s32 func_001E0700(s32 arg0, s32 arg1); /* JP: SzDuel_GetUnitKind */
s32 func_001E0760(s32 a0, s32 a1, s8 arg2); /* JP: SzDuel_SetUnitKind */
s32 func_001E07C0(void); /* JP: SzDuel_GetUnitKindOfs */
s32 func_001E0830(s32 arg0, s32 arg1); /* JP: SzDuel_GetUnitAttr */
s32 func_001E0890(s32 arg0, s32 arg1, s8 arg2); /* JP: SzDuel_SetUnitAttr */
void func_001E08F0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_GetUnitLevel */
s32 func_001E0950(void *arg0, s32 arg1); /* JP: SzDuel_GetUnitLevel2 */
void *func_001E09E0(void *arg0, s32 arg1); /* JP: SzDuel_GetUnitConstEffect2 */
void *func_001E0B70(s32 arg0, s32 arg1, s32 index); /* JP: SzDuel_GetUnitEffect */
s32 func_001E0C00(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_GetUnitLeaderAbility */
s32 func_001E0C70(void *arg0, s32 arg1, s32 arg2); /* JP: SzDuel_GetUnitLeaderAbility2 */
s32 func_001E0C80(void *arg0, u32 arg1, s32 *arg2, s32 arg3); /* JP: SzDuel_GetUnitLeaderAbility3 */
s32 func_001E1030(void); /* JP: SzDuel_GetUnitCardNo */
s32 func_001E1090(s32 arg0, s32 arg1); /* JP: SzDuel_GetUnitLoc */
void func_001E10F0(s32 arg0, s32 arg1, s32 arg2, void *arg3); /* JP: SzDuel_CalcUnitPos */
s32 func_001E11B0(s32 arg0, s32 arg1, f32 *arg2); /* JP: SzDuel_GetUnitPos */
s32 func_001E1360(s32 unused0, s32 unused1); /* JP: SzDuel_GetUnitModelID */
s32 func_001E13C0(s32 unused0, s32 unused1); /* JP: SzDuel_GetUnitSummonOrder */
s32 func_001E1420(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetUnitCurseFlag */
s32 func_001E14B0(void); /* JP: SzDuel_GetUnitCurseFlag */
s32 func_001E1520(s32 arg0, s32 arg1, s8 arg2); /* JP: SzDuel_SetUnitCurseRest */
s32 func_001E1580(void); /* JP: SzDuel_GetUnitCurseRest */
s32 func_001E15E0(s32 arg0, s32 arg1, s8 arg2); /* JP: SzDuel_SetUnitSpellRest */
s32 func_001E1640(void); /* JP: SzDuel_GetUnitSpellRest */
s32 func_001E16A0(s32 a0, s32 a1, s8 arg2); /* JP: SzDuel_SetUnitDelayCount */
s32 func_001E1700(void); /* JP: SzDuel_GetUnitDelayCount */
s32 func_001E1760(void); /* JP: SzDuel_CalcUnitMovable */
s32 func_001E17D0(void); /* JP: SzDuel_IsUnitMovableOnLabyrinth */
s32 func_001E1840(s32 arg0, s32 arg1, s8 arg2); /* JP: SzDuel_SetUnitCtlModeC */
s32 func_001E18A0(s32 arg0, s32 arg1, s8 arg2); /* JP: SzDuel_SetUnitCtlModeM */
s32 func_001E1900(s32 arg0, s32 arg1, s8 arg2); /* JP: SzDuel_SetUnitCtlGoal */
s32 func_001E1970(s32 arg0, s32 arg1, s8 arg2); /* JP: SzDuel_SetUnitCtlGoalC */
s32 func_001E19D0(s32 arg0, s32 arg1, s8 arg2); /* JP: SzDuel_SetUnitCtlGoalM */
s32 func_001E1A30(void); /* JP: SzDuel_GetUnitCtlGoalC */
s32 func_001E1A90(void); /* JP: SzDuel_GetUnitCtlGoalM */
s32 func_001E1AF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_SetUnitCtlRate */
s32 func_001E1B70(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_SetUnitCtlRateC */
s32 func_001E1C10(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_SetUnitCtlRateM */
s32 func_001E1CB0(void); /* JP: SzDuel_GetUnitCtlRateC */
s32 func_001E1D10(void); /* JP: SzDuel_GetUnitCtlRateM */
s32 func_001E1D70(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_SetUnitOpenRate */
s32 func_001E1E10(void); /* JP: SzDuel_GetUnitOpenRate */
s32 func_001E1E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_SetUnitStatus */
s32 func_001E2100(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_GetUnitStatus */
s32 func_001E2220(s32 arg0, s32 arg1, s8 arg2); /* JP: SzDuel_SetField */
s32 func_001E22B0(s32 arg0, s32 arg1); /* JP: SzDuel_GetField */
void func_001E2340(void); /* JP: SzDuel_InitFieldRate */
s32 func_001E23A0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetFieldRate */
s16 func_001E2450(s32 arg0, s32 arg1); /* JP: SzDuel_GetFieldRate */
u8 func_001E24E0(s32 x, s32 y); /* JP: SzDuel_GetMapMovable */
void func_001E27D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 *arg7, u8 *arg8, s32 count); /* JP: lSzDuel_CalcMapMovable */
void func_001E2A60(s32 arg0, s32 arg1, s32 arg2, s32 x, s32 y, s32 limit, u8 *oldX, u8 *oldY, s32 oldCount, u8 *pathX, u8 *pathY, s32 depth, s32 allowance); /* JP: lSzDuel_CalcMapMovableRecursive */
void func_001E2FB0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_InitMapColor */
void func_001E2FC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_InitMapColor2 */
void func_001E3060(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: SzDuel_SetMapColor */
s32 func_001E3070(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: SzDuel_SetMapColor2 */
s32 func_001E3230(s32 x, s32 y); /* JP: SzDuel_CalcMapColor */
s32 func_001E3650(s32 arg0, s32 arg1, s8 arg2); /* JP: SzDuel_SetMapAlpha */
s32 func_001E36E0(s32 arg0, s32 arg1); /* JP: SzDuel_GetMapUnit */
s32 func_001E3790(s32 arg0, s32 arg1); /* JP: SzDuel_GetMapUnitID */
s32 func_001E3850(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetBusyFlag */
s32 func_001E3900(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetCardBusyFlag */
s32 func_001E3990(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetCardColBusyFlag */
s32 func_001E3A20(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetModelBusyFlag */
s32 func_001E3AB0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetCardPos */
s32 func_001E3B50(s32 arg0, s32 arg1, void *arg2); /* JP: SzDuel_GetCardPos */
s32 func_001E3BF0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetCardRot */
s32 func_001E3C90(s32 arg0, s32 arg1, void *arg2); /* JP: SzDuel_GetCardRot */
s32 func_001E3D30(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetCardScale */
s32 func_001E3DD0(s32 arg0, s32 arg1, void *arg2); /* JP: SzDuel_GetCardScale */
s32 func_001E3E70(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_SetCardRgba */
s32 func_001E3F10(s32 arg0, s32 arg1, void *arg2); /* JP: SzDuel_GetCardRgba */
void func_001E3FB0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_OpenHandPopup */
void func_001E3FE0(void); /* JP: SzDuel_CloseHandPopup */
void func_001E3FF0(s32 arg0, s16 arg1, s16 arg2); /* JP: SzDuel_OpenOptionPopup */
s32 func_001E40A0(s32 arg0); /* JP: SzDuel_ActOptionPopup (matched by position) */
void func_001E42B0(void); /* JP: SzDuel_CloseOptionPopup */
void func_001E42C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzDuel_OpenMsgPopup */
s32 func_001E4430(s32 arg0); /* JP: SzDuel_ActMsgPopup */
void func_001E4530(void); /* JP: SzDuel_CloseMsgPopup */
void func_001E4540(s32 arg0, s32 arg1, s32 arg2); /* JP: SzDuel_OpenHandCursor */
void func_001E4570(s32 packet, s32 angle, s32 x, s32 y); /* JP: lSzDuel_OpenHandCursor_Pipe */
void func_001E4E50(void); /* JP: SzDuel_CloseHandCursor */
void func_001E4E60(s64 arg0); /* JP: SzDuel_SetIgnoreJudge */
void func_001E4E90(void); /* JP: SzBattle_Initialize */
void func_001E4F00(s32 arg0); /* JP: SzBattle_Init */
void func_001E5210(void *arg0, s32 arg1); /* JP: lSzBattle_CameraCB */
s32 func_001E5230(void); /* JP: SzBattle_InqCamera */
s32 func_001E5240(s32 index); /* JP: SzBattle_InqEntry */
void func_001E5260(s32 arg0, s32 arg1); /* JP: SzBattle_Entry */
void func_001E53C0(s32 arg0, s32 arg1); /* JP: SzBattle_Return */
s32 func_001E5590(s32 arg0); /* JP: SzBattle_DrawStage_Pipe */
s32 func_001E55E0(s32 arg0); /* JP: lSzBattle_DrawStage_Pipe */
s32 func_001E5D30(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzBattle_DrawWasteland_Pipe */
s32 func_001E5DD0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzBattle_DrawGrass_Pipe */
s32 func_001E5EB0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzBattle_DrawSea_Pipe */
s32 func_001E60E0(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzBattle_DrawNormal_Pipe */
void func_001E77A0(void); /* JP: SzBattle_Term */
void func_001E77E0(s32 arg0); /* JP: SzEvent_Init */
void func_001E7890(void); /* JP: SzEvent_Draw */
s32 func_001E78C0(s32 arg0); /* JP: SzEvent_Draw_Pipe */
void func_001E7A50(void); /* JP: SzEvent_Term */
s32 func_001E7A60(void); /* JP: SzModel_Init */
s32 func_001E7B20(s32 arg0); /* JP: SzModel_Create */
s32 func_001E7D00(s32 index); /* JP: lSzModel_Clean */
s32 func_001E7DE0(s32 arg0); /* JP: SzModel_Destroy */
s32 func_001E7E70(s32 arg0, s32 arg1, s32 arg2); /* JP: SzModel_Preset */
s32 func_001E8780(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzModel_Load */
void func_001E8E90(void *arg0, s32 arg1); /* JP: lSzModel_LoadCameraCB */
s32 func_001E8FA0(s32 arg0); /* JP: SzModel_BindTextureFile */
void func_001E9280(void *arg0, s32 arg1); /* JP: lSzModel_LoadTextureFileCB */
void func_001E92C0(void *arg0, s32 arg1); /* JP: lSzModel_LoadTexAnimFileCB */
s32 func_001EA0F0(s32 arg0); /* JP: SzModel_LoadEffectTextureFile */
void func_001EA270(void *arg0, s32 arg1); /* JP: lSzModel_LoadEffectTextureFileCB */
s32 func_001EA2A0(s32 current, s32 object, void *data, s32 *size); /* JP: SzModel_LoadTexture_Pipe */
void func_001ED460(s32 arg0); /* JP: lSzModel_EffectCB */
s32 func_001ED4A0(s32 index); /* JP: SzModel_Motion */
s32 func_001EDCB0(s32 index, s16 duration, s32 mode, void *color0, void *color1, s32 enabled); /* JP: SzModel_ReqMotionBlur */
void func_001EDF20(s32 arg0); /* JP: SzModel_CancelMotionBlur */
void func_001EDF90(s32 arg0); /* JP: SzModel_DrawMotionBlur */
s32 func_001EDFD0(s32 arg0, s32 arg1); /* JP: SzModel_DrawMotionBlur_Pipe */
void func_001EE4A0(s32 arg0); /* JP: SzModel_SetDrawCache */
s32 func_001EE4B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: SzModel_Draw_Pipe */
void func_001EE570(s32 arg0); /* JP: lSzModel_Draw_DefFunc */
s32 func_001EFA80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: SzModel_DrawWithOutCalc_Pipe */
s32 func_001EFB40(s32 arg0, s32 arg1, s32 *arg2); /* JP: lSzModel_GetGNode */
s32 func_001EFBD0(s32 target, s32 base, s32 node, s32 *index, s32 depthAddress, s32 *maxDepth, s32 callbackAddress); /* JP: lSzModel_TraceGNode */
void func_001EFD30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: SzModel_ShotTextureWithFunc */
s32 func_001EFDC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: SzModel_ShotTextureWithFunc_Pipe */
s32 func_001EFF70(s32 arg0, void *arg1); /* JP: lSzModel_LoadModel */
s32 func_001F0060(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: lSzModel_LoadModelPack */
void func_001F01A0(void *arg0, s32 arg1); /* JP: lSzModel_LoadModelCB */
void func_001F0390(s32 arg0, s32 arg1); /* JP: lSzModel_LoadModelPackCB */
s32 func_001F0500(s32 arg0, void *arg1); /* JP: lSzModel_BindModelByAddr */
s32 func_001F0760(s32 arg0, s32 arg1, s32 arg2); /* JP: lSzModel_LoadMotion */
void func_001F0830(void *arg0, s32 arg1); /* JP: lSzModel_LoadMotionCB */
s32 func_001F08D0(s32 arg0); /* JP: lSzModel_FreeModel */
s32 func_001F0C10(s32 arg0, s32 arg1); /* JP: lSzModel_FreeMotion */
s32 func_001F0CD0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzModel_BattleSeq */
s32 func_001F0E50(s32 arg0, s32 arg1, s32 arg2); /* JP: SzModel_BattleSeq2 */
f32 func_001F0F40(s32 arg0); /* JP: SzModel_GetRadius */
u8 *func_001F0FA0(s32 arg0); /* JP: SzModel_GetEffTextureB */
s32 func_001F0FF0(s32 arg0); /* JP: SzModel_GetOverlayM */
s32 func_001F1070(s32 arg0); /* JP: SzModel_LoadOverlayB */
s32 func_001F1130(s32 arg0); /* JP: SzModel_GetOverlayB */
s32 func_001F11B0(s32 arg0, s32 arg1); /* JP: SzModel_GetCamera */
s32 func_001F1240(s32 arg0); /* JP: SzModel_IsModelReady */
s32 func_001F12A0(s32 arg0); /* JP: SzModel_IsModelLoading */
s32 func_001F1300(s32 arg0); /* JP: SzModel_IsModelStandby */
s32 func_001F1370(s32 arg0); /* JP: SzModel_IsModelDisp */
s8 func_001F13F0(s32 arg0); /* JP: SzModel_GetAnim */
s8 func_001F1400(s32 arg0, s32 arg1); /* JP: SzModel_GetAnimParam */
s32 func_001F1480(s32 arg0, s32 arg1); /* JP: SzModel_SetAnim */
s32 func_001F1490(s32 arg0, s32 arg1, s32 arg2); /* JP: SzModel_SetAnimParam */
s32 func_001F1550(s32 arg0, s32 arg1); /* JP: SzModel_SetAnimIntr */
s32 func_001F1560(s32 arg0, s32 arg1, s32 arg2); /* JP: SzModel_SetAnimIntrParam */
s32 func_001F16B0(s32 arg0); /* JP: SzModel_SetAnimIntrReverse */
s32 func_001F1830(s32 arg0, s32 arg1); /* JP: SzModel_SetAnimDirect */
s32 func_001F1940(s32 arg0, s8 arg1); /* JP: SzModel_SetMotionDelay */
s64 func_001F19A0(s32 arg0); /* JP: SzModel_GetAnimDir */
s32 func_001F1A00(s32 arg0, s64 arg1); /* JP: SzModel_SetAnimDir */
s32 func_001F1A80(s32 arg0, f32 value); /* JP: SzModel_SetAnimSpeed */
s32 func_001F1A90(s32 arg0, s32 arg1, f32 value); /* JP: SzModel_SetAnimSpeedParam */
f32 func_001F1B50(s32 arg0); /* JP: SzModel_GetAnimFrame */
f32 func_001F1B60(s32 arg0, s32 arg1); /* JP: SzModel_GetAnimFrameParam */
void func_001F1C40(s32 arg0, f32 value); /* JP: SzModel_SetAnimFrame */
s32 func_001F1C50(s32 arg0, s32 arg1, f32 value); /* JP: SzModel_SetAnimFrameParam */
s32 func_001F1D50(s32 arg0, s32 arg1); /* JP: SzModel_GetAnimFrameMax */
s32 func_001F1E10(s32 arg0, f32 *arg1); /* JP: SzModel_GetIntensity */
s32 func_001F1E80(s32 arg0, f32 *arg1); /* JP: SzModel_GetIntensityOnly */
s32 func_001F1EE0(s32 arg0, f32 *arg1); /* JP: SzModel_SetIntensity */
s32 func_001F1F70(s32 arg0, f32 fparg0); /* JP: SzModel_SetIntensityOnly */
s32 func_001F1FD0(s32 arg0, void *arg1); /* JP: SzModel_GetPos */
s32 func_001F2050(s32 index, void *out); /* JP: SzModel_GetCenter */
s32 func_001F2150(s32 arg0, f32 *arg1); /* JP: SzModel_GetCenterOfs */
s32 func_001F22B0(s32 index, void *src); /* JP: SzModel_SetPos */
s32 func_001F2330(s32 arg0, void *arg1); /* JP: SzModel_GetRot */
s32 func_001F23B0(s32 arg0, void *arg1); /* JP: SzModel_GetRotC */
s32 func_001F2430(s32 arg0, void *arg1); /* JP: SzModel_SetRot */
s32 func_001F24C0(s32 index, void *src); /* JP: SzModel_SetRotC */
s32 func_001F2550(s32 arg0, void *arg1); /* JP: SzModel_GetScale */
s32 func_001F25D0(s32 idx, void *src); /* JP: SzModel_SetScale */
s32 func_001F2660(s32 arg0, void *arg1); /* JP: SzModel_GetRgba */
s32 func_001F26E0(s32 arg0, s32 arg1, void *arg2); /* JP: SzModel_SetRgba */
s32 func_001F27A0(s32 arg0); /* JP: SzModel_GetAlpha */
s32 func_001F2800(s32 arg0, u8 arg1); /* JP: SzModel_SetAlpha */
s32 func_001F2860(s32 arg0, s32 arg1, void *arg2); /* JP: SzModel_SetFilter */
s16 func_001F2920(s32 arg0); /* JP: SzModel_GetModelNo */
s8 func_001F2980(s32 arg0); /* JP: SzModel_GetModelType */
s32 func_001F29E0(s32 arg0, s32 arg1); /* JP: SzModel_SetDeform */
s32 func_001F2A70(s32 arg0); /* JP: SzModel_GetDeform */
s32 func_001F2AD0(s32 arg0, s8 arg1); /* JP: SzModel_SetDeformRatio */
s32 func_001F2B30(s32 index); /* JP: SzModel_GetRefNum */
s32 func_001F2BE0(s32 arg0, s32 arg1); /* JP: SzModel_InqRefID */
s32 func_001F2C60(s32 arg0, s32 arg1, s32 arg2); /* JP: SzModel_SetRefID */
s32 func_001F2DD0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzModel_SetRefID_RefNo */
s32 func_001F2EC0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzModel_GetRef */
s32 func_001F2FF0(s32 arg0, s16 arg1); /* JP: SzModel_SetMaxOT */
s32 func_001F3050(s32 arg0); /* JP: SzModel_GetMaxOT */
s32 func_001F30B0(s32 arg0, s32 arg1); /* JP: SzModel_SetDrawFlag */
s32 func_001F3130(s32 arg0); /* JP: SzModel_GetDrawFlag */
s32 func_001F3190(s32 arg0, s32 arg1); /* JP: SzModel_SetCalcFlag */
s32 func_001F3210(s32 arg0); /* JP: SzModel_GetCalcFlag */
s32 func_001F3270(s32 arg0, s64 arg1); /* JP: SzModel_SetFogFlag */
s32 func_001F32F0(s32 arg0, s64 arg1); /* JP: SzModel_SetPauseFlag */
s32 func_001F3360(s32 arg0); /* JP: SzModel_GetPauseFlag */
s32 func_001F33C0(s32 arg0, s64 arg1); /* JP: SzModel_SetStoneFlag */
s32 func_001F3440(s32 arg0); /* JP: SzModel_GetStoneFlag */
s32 func_001F3690(s32 arg0); /* JP: SzModel_GetStoneRatio */
void func_001F3700(void); /* JP: SzEffect_Init */
void func_001F3790(void); /* JP: SzEffect_Clear */
void func_001F3870(void); /* JP: SzEffect_TrimModule */
s32 func_001F3910(s32 kind, s32 card, s32 mode, void *unused); /* JP: SzEffect_LoadModule */
void func_001F3CB0(void *arg0, s32 arg1); /* JP: lSzEffect_LoadOverlayCB */
void func_001F3E40(void *arg0, s32 arg1); /* JP: lSzEffect_LoadSECtlCB */
u8 *func_001F3EA0(s32 arg0, s32 arg1); /* JP: SzEffect_GetModuleInfo */
void func_001F3F20(void); /* JP: SzEffect_ReqSE */
void func_001F40D0(s32 group); /* JP: SzEffect_Draw */
void func_001F48F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: SzEffect_Entry */
s32 func_001F4900(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: SzEffect_EntryCallback */
s32 func_001F4CB0(s32 arg0); /* JP: SzEffect_Destroy */
s32 func_001F4E50(s32 arg0, s32 arg1); /* JP: SzEffect_Destroy2 */
s32 func_001F4F10(s32 arg0, s32 arg1); /* JP: SzEffect_Sleep */
s32 func_001F4FD0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzEffect_Sleep2 */
s32 func_001F5090(s32 arg0, s32 arg1); /* JP: SzEffect_Erase2 */
s32 func_001F51D0(s32 arg0); /* JP: SzEffect_IsUse */
s32 func_001F5240(s32 arg0, s32 arg1); /* JP: SzEffect_IsUse2 */
s32 func_001F52D0(s32 arg0); /* JP: SzEffect_GetStatus */
s32 func_001F5320(s32 arg0); /* JP: SzEffect_GetCount */
void func_001F5370(s32 arg0); /* JP: SzEffect_SetTarget */
s32 func_001F5380(u8 arg0); /* JP: SzEffect_GetTarget */
void func_001F5390(s32 arg0); /* JP: SzEffect_SetFrom */
s32 func_001F53A0(u8 arg0); /* JP: SzEffect_GetFrom */
void func_001F53B0(s32 arg0, s32 arg1); /* JP: SzEffect_GetPos */
s32 func_001F53C0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzEffect_GetPos2 */
s32 func_001F54E0(s32 arg0); /* JP: SzEffect_GetRefNum2 */
s32 func_001F5560(s32 arg0, s32 arg1, s32 arg2); /* JP: SzEffect_SetRefID2 */
s32 func_001F5620(s32 arg0, s32 arg1, s32 arg2); /* JP: SzEffect_GetRef2 */
s32 func_001F56D0(s32 arg0, s32 arg1); /* JP: SzEffect_ClearRefID2 */
void func_001F57B0(s32 arg0); /* JP: SzEffect_SetMaxOT */
s32 func_001F57C0(s32 arg0, s32 arg1); /* JP: SzEffect_SetMaxOT2 */
void func_001F5850(void); /* JP: SzEffect_GetRadius */
f32 func_001F5860(s32 arg0); /* JP: SzEffect_GetRadius2 */
s32 func_001F58E0(s32 arg0); /* JP: SzEffect_GetCamDist2 */
s32 func_001F5970(s32 arg0, s32 arg1); /* JP: SzEffect_SetBusyFlag2 */
s32 func_001F59D0(s32 arg0, s32 arg1); /* JP: SzEffect_SetCardBusyFlag2 */
s32 func_001F5A30(s32 arg0, s32 arg1); /* JP: SzEffect_SetCardColBusyFlag2 */
s32 func_001F5A90(s32 arg0, s32 arg1); /* JP: SzEffect_SetModelBusyFlag2 */
s32 func_001F5AF0(s32 arg0); /* JP: SzEffect_IsCardStandby2 */
s32 func_001F5B30(s32 arg0); /* JP: SzEffect_GetCardRequest2 */
s32 func_001F5B70(s32 arg0, s32 arg1); /* JP: SzEffect_SetCardPos2 */
s32 func_001F5BD0(s32 arg0, void *arg1); /* JP: SzEffect_GetCardPos2 */
s32 func_001F5C40(s32 arg0, s32 arg1); /* JP: SzEffect_SetCardRot2 */
s32 func_001F5CA0(s32 arg0, void *arg1); /* JP: SzEffect_GetCardRot2 */
s32 func_001F5D10(s32 arg0, s32 arg1); /* JP: SzEffect_SetCardScale2 */
s32 func_001F5D70(s32 arg0, void *arg1); /* JP: SzEffect_GetCardScale2 */
s32 func_001F5DE0(s32 arg0, s32 arg1); /* JP: SzEffect_SetCardRgba2 */
s32 func_001F5E40(s32 arg0, u8 *arg1); /* JP: SzEffect_GetCardRgba2 */
s32 func_001F5EB0(void); /* JP: SzEffect_IsModelStandby */
s32 func_001F5EC0(s32 arg0); /* JP: SzEffect_IsModelStandby2 */
s32 func_001F5F00(s32 arg0, void *arg1); /* JP: SzEffect_SetModelPos2 */
s32 func_001F5F90(s32 arg0, f32 *arg1); /* JP: SzEffect_GetModelPos2 */
s32 func_001F6030(s32 arg0, void *arg1); /* JP: SzEffect_SetModelRot2 */
void func_001F60C0(s32 arg0); /* JP: SzEffect_SetModelRotC */
s32 func_001F60D0(s32 arg0, s32 arg1); /* JP: SzEffect_SetModelRotC2 */
s32 func_001F6160(s32 arg0, void *arg1); /* JP: SzEffect_GetModelRot2 */
void func_001F6200(s32 arg0); /* JP: SzEffect_GetModelRotC */
s32 func_001F6210(s32 arg0, s32 arg1); /* JP: SzEffect_GetModelRotC2 */
s32 func_001F62B0(s32 arg0, void *arg1); /* JP: SzEffect_SetModelScale2 */
s32 func_001F6340(s32 arg0, f32 *arg1); /* JP: SzEffect_GetModelScale2 */
void func_001F63E0(s32 arg0, s32 arg1); /* JP: SzEffect_SetModelRgba2 */
s32 func_001F63F0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzEffect_SetModelRgbaX */
void func_001F6480(s32 arg0); /* JP: SzEffect_GetModelRgba */
s32 func_001F6490(s32 arg0, u8 *arg1); /* JP: SzEffect_GetModelRgba2 */
s32 func_001F64C0(s32 arg0, u8 *arg1); /* JP: SzEffect_GetModelRgbaX */
void func_001F6560(s32 arg0); /* JP: SzEffect_SetModelFilter */
void func_001F6580(s32 arg0, s32 arg1); /* JP: SzEffect_SetModelFilter2 */
s32 func_001F6590(s32 arg0, s32 arg1, s32 arg2); /* JP: SzEffect_SetModelFilterX */
s32 func_001F6620(s32 arg0); /* JP: SzEffect_GetAnim2 */
s32 func_001F66A0(s32 arg0, s32 arg1); /* JP: SzEffect_SetAnimIntr2 */
s32 func_001F6730(s32 arg0, s64 arg1); /* JP: SzEffect_SetAnimDir2 */
f32 func_001F67C0(s32 arg0, s32 arg1); /* JP: SzEffect_GetAnimFrame2 */
s32 func_001F6840(s32 arg0, f32 arg1); /* JP: SzEffect_SetAnimFrame2 */
void func_001F68D0(s32 arg0); /* JP: SzEffect_SetFogColorForMonster */
void func_001F6910(s32 arg0); /* JP: SzEffect_SetFogColorForDuel */
void func_001F6960(s32 arg0); /* JP: SzEffect_SetFogColorForBattle */
void func_001F69A0(s32 arg0); /* JP: SzEffect_SetFogParamZForMonster */
void func_001F69E0(s32 arg0); /* JP: SzEffect_SetFogParamZForDuel */
void func_001F6A30(s32 arg0); /* JP: SzEffect_SetFogParamZForBattle */
void func_001F6A70(s32 arg0); /* JP: SzEffect_SetFogParamYForMonster */
void func_001F6AB0(s32 arg0); /* JP: SzEffect_SetFogParamYForDuel */
void func_001F6B00(s32 arg0); /* JP: SzEffect_SetFogParamYForBattle */
void func_001F6B40(s32 arg0); /* JP: SzEffect_SetStraightLightForMonster */
void func_001F6B80(s32 arg0); /* JP: SzEffect_SetStraightLightForDuel */
void func_001F6BD0(s32 arg0); /* JP: SzEffect_SetStraightLightForBattle */
void func_001F6C10(s32 arg0); /* JP: SzEffect_SetPointLightForMonster */
void func_001F6C50(s32 arg0); /* JP: SzEffect_SetPointLightForDuel */
void func_001F6CA0(s32 arg0); /* JP: SzEffect_SetPointLightForBattle */
void func_001F6CE0(s32 arg0); /* JP: SzEffect_SetBlackOutForMonster */
void func_001F6CF0(s32 arg0); /* JP: SzEffect_SetBlackOutForDuel */
void func_001F6D00(s32 arg0); /* JP: SzEffect_SetBlackOutForBattle */
u8 func_001F6D10(void); /* JP: SzEffect_GetBlackOutForMonster */
u8 func_001F6D20(void); /* JP: SzEffect_GetBlackOutForDuel */
u8 func_001F6D30(void); /* JP: SzEffect_GetBlackOutForBattle */
void func_001F6D40(s32 arg0); /* JP: SzEffect_SetIntensityForMonster */
void func_001F6D80(s32 arg0); /* JP: SzEffect_SetIntensityForDuel */
void func_001F6DD0(s32 arg0); /* JP: SzEffect_SetIntensityForBattle */
s32 func_001F6E10(s32 arg0, s32 arg1); /* JP: SzEffect_SetIntensity */
void func_001F6E80(s32 arg0, f32 fparg0); /* JP: SzEffect_SetIntensityOnly */
s32 func_001F6EF0(void); /* JP: SzEffect_InqDuelResult */
s32 func_001F6F50(s32 arg0); /* JP: SzEffect_GetPlayMotion */
s32 func_001F7060(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzEffect_ModelShotTexture2 */
void func_001F7070(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: SzEffect_ModelShotTextureWithFunc */
s32 func_001F70A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: SzEffect_ModelShotTextureWithFunc2 */
void func_001F7170(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: SzEffect_ReqMotionBlur */
s32 func_001F71A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: SzEffect_ReqMotionBlur2 */
void func_001F7260(s32 arg0); /* JP: SzEffect_SetPauseFor3DBattle */
s32 func_001F72C0(s32 arg0, s64 arg1); /* JP: SzEffect_SetModelPause2 */
s32 func_001F7350(s32 arg0, s32 arg1); /* JP: SzEffect_SetModelPauseForType */
void func_001F73C0(void); /* JP: SzEffect_StoneProc */
s32 func_001F74B0(void); /* JP: SzView_Init */
s32 func_001F74C0(s32 arg0); /* JP: SzView_Create */
s32 func_001F7720(s32 arg0); /* JP: SzView_Destroy */
s32 func_001F7790(s32 arg0); /* JP: SzView_Act */
s32 func_001F8A30(s32 arg0, s32 arg1); /* JP: SzView_Set_Pipe */
s32 func_001F8D30(s32 arg0, s32 arg1, s32 arg2); /* JP: SzView_SetLight_Pipe */
s32 func_001F8F80(s32 arg0); /* JP: lSzView_CalcLook */
s32 func_001F90E0(s32 arg0); /* JP: lSzView_CalcRel */
s32 func_001F9170(s32 arg0, s32 arg1, s32 arg2); /* JP: SzView_SetFogColor */
s32 func_001F9230(s32 arg0, s32 arg1, s32 arg2); /* JP: SzView_SetFogParamZ */
s32 func_001F9310(s32 arg0, s32 arg1, s32 arg2); /* JP: SzView_SetFogParamY */
s32 func_001F93F0(s32 arg0, s32 arg1, s32 arg2, void *arg3); /* JP: SzView_SetStraightLightColor */
s32 func_001F9500(s32 arg0, s32 arg1, s32 arg2, void *arg3); /* JP: SzView_GetStraightLightVector */
s32 func_001F95E0(s32 arg0, s32 arg1, s32 arg2, void *arg3); /* JP: SzView_SetStraightLightDirection */
s32 func_001F96F0(s32 arg0, s32 arg1); /* JP: SzView_InqStraightLight */
s32 func_001F9770(s32 arg0, s32 arg1, s32 arg2); /* JP: SzView_SetStraightLight */
s32 func_001F98C0(s32 arg0, s32 arg1); /* JP: SzView_InqPointLight */
s32 func_001F9940(s32 arg0, s32 arg1, s32 arg2); /* JP: SzView_SetPointLight */
f32 func_001F9A20(s32 arg0); /* JP: SzView_GetScreenDistance */
s32 func_001F9A80(s32 arg0, f32 fparg0); /* JP: SzView_SetScreenDistance */
s32 func_001F9AD0(s32 arg0); /* JP: SzView_GetSP */
s32 func_001F9B20(s32 arg0, void *arg1); /* JP: SzView_SetSP */
s32 func_001F9D30(s32 arg0); /* JP: SzView_GetCP */
s32 func_001F9D80(s32 arg0, void *arg1); /* JP: SzView_SetCP */
s32 func_001F9F90(s32 arg0, s32 arg1); /* JP: SzView_SetRoll */
s32 func_001F9FE0(s32 arg0, void *arg1, void *arg2); /* JP: SzView_SetCamera */
void *func_001FA6F0(s32 arg0, s32 arg1); /* JP: SzView_InqRequest */
s32 func_001FA770(s32 arg0, s32 arg1, s32 arg2); /* JP: SzView_PauseRequest */
s32 func_001FA810(s32 arg0, s32 arg1); /* JP: SzView_FreeRequest */
s32 func_001FA8A0(s32 owner, s32 target, s32 type, s32 count, s32 value, void *data); /* JP: SzView_ReqCamera */
s32 func_001FAD10(s32 arg0); /* JP: SzView_GetRel */
s32 func_001FAD60(s32 arg0, void *arg1); /* JP: SzView_SetRelSP */
f32 *func_001FAF60(s32 arg0); /* JP: SzView_GetLook */
s32 func_001FAFB0(s32 arg0, s32 arg1); /* JP: SzView_GetLookVector */
s32 func_001FB0B0(s32 arg0, s32 arg1); /* JP: SzView_GetLookMatrix */
s32 func_001FB1D0(s32 arg0, s32 arg1); /* JP: SzView_GetLookMatrixWithRoll */
s32 func_001FB360(s32 index, f32 *src); /* JP: SzView_SetLookSP */
s32 func_001FB500(s32 index, f32 *src); /* JP: SzView_SetLookCP */
s32 func_001FB6A0(s32 arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1, f32 fparg2); /* JP: SzView_RollCamera */
s32 func_001FB940(s32 index, void *motion, s32 duration, s32 frame, s32 parent, s32 mirror); /* JP: SzView_SetInterpCameraMotion */
void func_001FBE50(void *arg0, void *arg1, s32 arg2, f32 fparg0); /* JP: lSzView_CalcInterpCameraMotion */
f32 func_001FC050(u8 *arg0, s32 arg1, f32 fparg0); /* JP: lSzView_CalcInterpCameraMotion1 */
s32 func_001FC210(s32 index, s32 otherIndex, f32 *target, s32 mode, f32 weight); /* JP: SzView_SetViewCamera */
s32 func_001FC6D0(s32 arg0, s32 arg1); /* JP: SzView_IsFogZ */
s32 func_001FC760(s32 arg0, s32 arg1); /* JP: SzView_IsFogY */
s32 func_001FC7F0(s32 arg0); /* JP: SzView_GetMode */
s32 func_001FC840(s32 arg0, s32 arg1); /* JP: SzView_SetMode */
void func_001FC890(f32 *src, s32 *dst); /* JP: SzView_V2IV */
void func_001FC950(void *arg0, void *arg1); /* JP: SzView_IV2V */
s32 func_001FC9B0(s32 arg0); /* JP: SzView_InitCamera */
void func_001FCA70(void); /* JP: SzView_TermCamera */
void func_001FCAB0(void); /* JP: SzView_ActCamera */
void func_001FCC20(void); /* JP: SzFade_Init */
s32 func_001FCC70(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, void *arg5); /* JP: SzFade_Entry */
s32 func_001FCD60(s32 arg0); /* JP: SzFade_Destroy */
void func_001FCDA0(void); /* JP: SzFade_DispAll */
s32 func_001FCDE0(s32 arg0); /* JP: SzFade_Disp */
void func_001FCF30(s32 arg0, s32 arg1, s32 arg2); /* JP: SzFade_Draw */
s32 func_001FCF90(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzFade_Draw_Pipe */
s32 func_001FD0B0(s32 arg0); /* JP: SzFade_SetKillFlag */
s32 func_001FD130(s32 arg0, s64 arg1); /* JP: SzFade_SetPauseFlag */
s32 func_001FD1B0(s32 arg0); /* JP: SzFade_GetRestCount */
s32 func_001FD220(s32 arg0); /* JP: SzFade_IsDoing */
void func_001FD2B0(void); /* JP: SzMsg_Initialize */
s32 func_001FD2D0(s32 arg0, s32 arg1); /* JP: SzMsg_Init */
s32 func_001FD320(s32 arg0, s32 arg1, s32 arg2, s32 *arg3); /* JP: SzMsg_Init_Pipe (matched by position) */
void func_001FD4B0(s32 arg0); /* JP: SzMsg_SetDefPrioZ */
void func_001FD4C0(u64 *arg0, s32 arg1, s32 arg2); /* JP: SzMsg_LoadClut_Pipe */
void func_001FD610(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzMsg_LoadFont */
void func_001FDD70(void *arg0, void *arg1); /* JP: lSzMsg_GetTexInfo */
s32 func_001FDFE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, u8 *arg5); /* JP: SzMsg_DrawRect_Pipe */
s32 func_001FE660(s32 arg0, s32 arg1, s64 arg2, s64 arg3, f32 scaleX, f32 scaleY, s32 arg4, void (*arg5)(void)); /* JP: SzMsg_DrawRatioX_Pipe */
void func_001FE750(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: SzMsg_DrawX */
s32 func_001FE7D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: SzMsg_DrawX_Pipe */
void func_001FE880(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzMsg_DrawGlass */
s32 func_001FE8F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: SzMsg_DrawGlass_Pipe */
void func_001FEA80(void *arg0); /* JP: SzMsg_GetDefRect */
void *func_001FEAB0(s32 arg0); /* JP: SzMsg_GetInfo */
void func_001FEAF0(s32 arg0); /* JP: SzMsg_Free */
void func_001FEB40(void); /* JP: SzMsg_FreeAll */
void func_001FEB80(void); /* JP: SzFile_Init */
void func_001FEC70(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s64 arg5); /* JP: SzFile_ReadRequest */
s32 func_001FECB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s64 arg8); /* JP: SzFile_ReadRequestParam */
s32 func_001FEDA0(void *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9); /* JP: lSzFile_SetReadRequestParam */
void func_001FF250(s8 *p); /* JP: lSzFile_StrNormalize */
s32 func_001FF300(void); /* JP: SzFile_InqRequestEx */
s32 func_001FF350(s32 arg0); /* JP: SzFile_InqRequest */
s32 func_001FF360(s32 arg0, s32 arg1); /* JP: SzFile_InqRequestX */
void func_001FF3D0(void); /* JP: SzFile_DoRequest */
s32 func_001FF420(void); /* JP: SzFile_DoRequestS */
s32 func_001FF480(s32 arg0); /* JP: lSzFile_DoRequestMain */
void func_001FFAC0(s32 arg0, s32 arg1); /* JP: lSzFile_TermRequest */
s32 func_001FFC50(s32 arg0, s32 arg1); /* JP: SzFile_EntryGroup */
void func_001FFCB0(void *arg0); /* JP: SzFile_InqGroup */
void *func_001FFCC0(void *arg0, s32 arg1); /* JP: SzFile_InqGroupX */
s32 func_001FFD30(s32 arg0, s32 arg1, s32 arg2); /* JP: SzFile_Read */
void *func_001FFE00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: SzFile_ReadParam */
void func_001FFF60(s32 arg0, s64 arg1); /* JP: lSzFile_ReadCB */
u8 *func_001FFF90(s32 unused0); /* JP: SzFile_GetEnv */
s32 func_001FFFC0(void); /* JP: RhFile_Init */
void func_00200170(s32 arg0); /* JP: lRhFile_CdCallback */
s32 func_00200210(void); /* JP: RhFile_Term */
void func_00200220(s32 arg0, s32 arg1); /* JP: RhFile_LoadIopModuleWrapper */
s32 func_00200230(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: RhFile_LoadIopModuleWrapperEx */
void func_00200300(s8 *arg0); /* JP: lRhFile_StrUpper */
void func_00200350(void); /* JP: RhFile_VSyncProcess */
s32 func_00200360(s32 arg0); /* JP: RhFile_OpenFile */
s32 func_002003E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: RhFile_ReadAndBlock */
s32 func_002004C0(s32 arg0); /* JP: RhFile_CloseFile */
s32 func_00200510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void (*arg4)(void), s32 arg5, s32 arg6); /* JP: RhFile_ReadAndCallbackByFileName */
void func_00200680(void *arg0); /* JP: lRhFile_ReadCB */
s32 func_002006C0(s32 arg0); /* JP: RhFile_ExistFile */
void func_002007D0(void); /* JP: SzText_Init */
void *func_002008A0(s32 arg0, s32 arg1); /* JP: SzText_GetItem */
void *func_00200930(s32 arg0, s32 arg1); /* JP: SzText_GetReadyItem */
s32 func_002009E0(s32 arg0, s32 arg1); /* JP: SzText_LoadMerge */
s32 func_00202220(s32 arg0, s32 arg1, char *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: SzText_LoadFileEx */
void func_002024D0(void *arg0, s32 arg1); /* JP: lSzText_LoadFileCB */
s32 func_00202810(s32 arg0, s32 arg1, char *arg2, s32 arg3); /* JP: SzText_AddFile */
s32 func_002029B0(s32 arg0, s32 arg1); /* JP: SzText_Free */
s32 func_00202AB0(s32 arg0, s32 arg1); /* JP: SzText_DoRequest */
s32 func_00202B00(s32 arg0, s32 arg1, s32 arg2, s32 *arg3); /* JP: SzText_DoRequest_Pipe */
s32 func_00202BF0(s32 arg0, s32 arg1); /* JP: SzText_LoadRequest */
s32 func_00202CB0(s32 category, s32 id, s32 enabled); /* JP: SzText_SleepRequest */
s32 func_00202D60(s32 arg0, s32 arg1); /* JP: SzText_FreeRequest */
u16 func_00202E00(s16 arg0, s32 arg1); /* JP: SzText_InitClutManage */
s32 func_00202E30(void *arg0); /* JP: SzText_GetClutSize */
s32 func_00202F00(s32 arg0); /* JP: SzText_GetClutGsAddr */
void func_00202F50(s32 arg0, s32 arg1, s32 arg2); /* JP: SzText_Load */
s32 func_00202FB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzText_Load_Pipe */
void func_002031F0(void); /* JP: SzPad_Init */
void func_002032A0(void); /* JP: SzPad_Term */
void func_002032C0(s32 arg0, s8 arg1, s64 arg2); /* JP: SzPad_SetParam */
void func_00203320(void); /* JP: SzPad_Status */
void func_00203840(void); /* JP: SzPad_Act */
s32 func_002038F0(void); /* JP: SzPad_VSync */
s32 func_00203A40(s32 arg0, s32 arg1, s32 arg2); /* JP: SzPad_Check */
s32 func_00203B50(s32 arg0, s32 arg1); /* JP: SzPad_ResetCounter */
s32 func_00203BC0(s32 arg0); /* JP: SzPad_IsAnalog */
s32 func_00203C00(s32 arg0); /* JP: SzPad_IsPress */
u8 func_00203C40(s32 arg0, s32 arg1); /* JP: SzPad_GetAnalogInfo */
void func_00203C70(s32 arg0, s32 arg1, s8 arg2); /* JP: SzPad_SetAnalogInfo */
u8 func_00203CA0(s32 arg0, s32 arg1); /* JP: SzPad_GetPressInfo */
void func_00203CD0(void); /* JP: SzDebug_Init */
s32 func_00205150(void); /* JP: SzDebug_GetActiveMenu */
s32 func_00205160(void); /* JP: SzDebug_GetActiveModel */
s32 func_00205170(void); /* JP: SzDebug_IsHide */
void func_002051C0(s64 arg0); /* JP: SzDebug_SetHideFlag */
s32 func_002051F0(void); /* JP: SzDebug_IsEffect */
void func_00205210(void); /* JP: SzDebug_OutputFrameBuffer */
s32 func_00205440(s32 arg0, void *arg1, u16 *arg2, s32 *arg3); /* JP: Ex3d_RotTransPers */
s32 func_00205630(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 *arg4); /* JP: Ex3d_RotTransPersAuto */
f32 func_00205C40(s32 arg0); /* JP: Ex3d_GetLookVector */
void func_00205C90(s32 arg0); /* JP: Ex3d_GetLookMatrix */
void func_00205CA0(s32 arg0); /* JP: Ex3d_GetLookMatrixWithRoll */
void func_00205CB0(void *arg0, f32 fparg0, f32 fparg1); /* JP: Ex3d_GetPointOnScreen */
s32 func_00205D10(void *arg0, f32 fparg0); /* JP: Ex3d_GetSampleZ */
f32 func_00205DF0(void *arg0, f32 fparg0); /* JP: Ex3d_GetSampleW */
s32 func_00205E70(s32 count, void *arg1, f32 *normal); /* JP: Ex3d_GetSurfaceNormal */
s32 func_00206030(s32 count, void *arg1, void *arg2); /* JP: Ex3d_GetPointsAverage */
s32 func_002060F0(f32 *origin, s32 count, f32 *points, f32 *out); /* JP: Ex3d_GetViewVector */
s32 func_002061F0(f32 *origin, s32 count, void *src, f32 *out); /* JP: Ex3d_GetViewVectorForNode */
void func_002062F0(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3); /* JP: Ex3d_GetSurfaceC */
void func_00206430(void *arg0, void *arg1, void *arg2, void *arg3); /* JP: Ex3d_IntersectP */
void func_00206530(void *arg0, void *arg1, s32 flags, void *arg3, f32 factor); /* JP: Ex3d_DivideN */
void func_00206D00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: Ex3d_ViewClip */
s32 func_00206D30(s32 planeCount, void *planeArg, s32 count, s32 verticesArg, s32 unused, s32 outputArg, s32 flags); /* JP: Ex3d_Clipping */
s32 func_002070F0(void *matrix, s32 count, void *vertices, s32 arg3, void *arg4, s32 flags, f32 *depth); /* JP: Ex3d_NodeL2V */
void func_00207230(void *matrix, s32 count, void *vertices); /* JP: Ex3d_NodeV2S */
void func_00207360(void); /* JP: ExInitPrim */
void func_002073A0(void); /* JP: ExTermPrim */
void func_002073D0(u8 *arg0, s32 arg1, s32 arg2); /* JP: ExClearOt */
u8 *func_00207500(void); /* JP: ExGetMyOT */
void func_00207510(void *arg0); /* JP: ExBindPrim */
void func_002075F0(s32 arg0, s32 arg1, s32 arg2); /* JP: ExSortPrim */
s32 func_00207F60(void); /* JP: ExSetAnchor */
s32 func_00207FA0(s32 arg0); /* JP: ExSetAnchor_Pipe */
void func_00207FD0(s32 arg0, s32 arg1, s32 arg2); /* JP: ExSortAnchor */
s32 func_00208030(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: ExSortAnchor_Pipe */
void func_00208090(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: ExSortDispBlur */
s32 func_00208110(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: ExSortDispBlur_Pipe */
s32 func_00208280(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6); /* JP: ExSortSoftFocus_Pipe */
void func_00208460(void); /* JP: ExFlushTexture */
void func_00208490(s32 arg0); /* JP: ExZBufferMode */
s32 func_002084D0(s32 arg0, s64 arg1); /* JP: ExClampMode_Pipe */
void *func_00208530(void *arg0, s32 arg1); /* JP: ExDitherMode_Pipe */
void func_002085A0(s32 arg0); /* JP: ExDitherMatrixEz */
s32 func_002085E0(s32 arg0, s32 arg1); /* JP: ExDitherMatrixEz_Pipe */
s64 func_00208680(s32 arg0, s32 arg1); /* JP: ExGetRegVal */
s32 func_002086D0(void *arg0, s64 arg1); /* JP: ExAssignAlpha */
s32 func_00208700(void *arg0, void *arg1, s32 arg2); /* JP: ExAssignTexture */
s32 func_002087A0(void *arg0, s32 arg1); /* JP: ExAssignFrameBuffer */
void func_00208800(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: ExFrameBuffer2Texture */
s32 func_00208870(s32 arg0, s32 arg1, s32 arg2, void *arg3, void *arg4); /* JP: ExFrameBuffer2Texture_Pipe */
s32 func_00208CB0(void *arg0, s64 arg1); /* JP: ExAssignClamp */
s64 func_00208D00(s32 arg0); /* JP: ExGetAlphaVal */
void *func_00208D40(void *arg0, s32 arg1); /* JP: RhVu1Mac_ChangeDrawMethod */
void *func_00208E40(void *arg0); /* JP: RhVu1Mac_ReserveChangeDrawMethod */
void *func_00208E60(void *arg0, void *arg1); /* JP: RhVu1Mac_SetViewScreenMatrix */
void *func_00208EB0(void *arg0, void *arg1); /* JP: RhVu1Mac_SetScreenWorldMatrix */
s32 func_00208F00(s32 packet, void *arg1, void *arg2, s32 arg3); /* JP: RhVu1Mac_SetStraightLightToVu1_Ex */
s32 func_00209110(s32 arg0, void *arg1, void *arg2, f32 fparg0, f32 fparg1, f32 fparg2); /* JP: RhVu1Mac_SetPointLightToVu1 */
s32 func_00209270(void *arg0, void *arg1, f32 *arg2, f32 *arg3, f32 *arg4); /* JP: RhVu1Mac_GetPointLight */
void *func_00209320(void *arg0, s32 arg1, f32 fparg0, f32 fparg1, f32 fparg2); /* JP: RhVu1Mac_SetClipParameter */
void *func_002093E0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3); /* JP: RhVu1Mac_SetFogParameterEx */
void *func_00209490(void *arg0, s32 arg1, s32 arg2); /* JP: RhVu1Mac_SetFogOnOff */
s32 func_00209510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: RhBase_Init */
s32 func_00209870(void); /* JP: RhBase_Term */
void func_002098B0(s32 arg0); /* JP: RhBase_ResetGsEnv */
s32 func_002099D0(void); /* JP: RhBase_FlipBuffer (matched by position) */
s32 func_00209D20(void); /* JP: RhBase_GetVifPacketArea */
void func_00209D30(s32 arg0); /* JP: RhBase_SetVifPacketArea */
f32 func_00209D40(s32 *arg0); /* JP: RhBase_GetAspectY */
s32 func_00209D60(s32 *arg0, s32 *arg1); /* JP: RhBase_GetScreenSize */
s32 func_00209D80(s32 *arg0, s32 *arg1); /* JP: RhBase_GetZMinMax */
s32 func_00209E30(s32 *arg0, s32 *arg1); /* JP: RhBase_GetScreenCenter */
s32 func_00209E50(void); /* JP: RhBase_GetUserGsAddress */
s32 func_00209E90(u8 arg0, u8 arg1, u8 arg2, u8 arg3); /* JP: RhBase_SetClearColorEx */
s32 func_00209EF0(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3); /* JP: RhBase_GetBufferFormatEx */
s32 func_00209F60(void (*arg0)(void)); /* JP: RhBase_SetVSyncCallback */
void *func_00209F70(void *arg0, u32 arg1); /* JP: RhBase_MaskFBuffer */
s32 func_0020A0B0(s32 arg0, s32 arg1); /* JP: RhBase_SetZBufferMode */
void func_0020A280(void *arg0); /* JP: RhBase_GetZBufInfo */
void *func_0020A340(void *arg0, void *arg1); /* JP: RhBase_SetFogColor */
void func_0020A3B0(u32 arg0); /* JP: RhBase_CopyFrameBuffer */
s32 func_0020A470(s32 arg0, s32 arg1, s32 arg2); /* JP: RhBase_AssignRenderFrame */
void *func_0020A610(void *arg0); /* JP: RhBase_EnableRenderFrame */
void *func_0020A760(void *arg0); /* JP: RhBase_DisableRenderFrame */
void *func_0020A870(u8 *packet, u8 *color); /* JP: RhBase_ClearRenderFrame */
void func_0020A9E0(void); /* JP: RhBase_FreeRenderFrame */
s32 func_0020AA30(void *arg0, void *arg1); /* JP: RhBase_GetTextureInfoForRender */
void func_0020AD10(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: lRhBase_InitScreenVariables */
s32 func_0020B000(s32 arg0); /* JP: lRhBase_InitGsAndVif */
void func_0020B1E0(s32 arg0); /* JP: lRhBase_SetRandomDither */
u8 *func_0020B300(u8 *arg0, u8 *arg1, s32 arg2); /* JP: RhMem_CopyMemory */
void *func_0020B340(void *dest, void *source, s32 count); /* JP: RhMem_CopyMemory4 */
void *func_0020B380(void *dest, void *source, s32 count); /* JP: RhMem_CopyMemory16 */
s8 *func_0020B3C0(s8 *arg0, s8 arg1, s32 arg2); /* JP: RhMem_FillMemory */
void *func_0020B400(void *dst, s32 val, s32 count); /* JP: RhMem_FillMemory4 */
s64 *func_0020B440(s64 *arg0, s64 arg1, s32 arg2); /* JP: RhMem_FillMemory8 */
f32 func_0020B480(s32 arg0); /* JP: RhMath_CosI */
f32 func_0020B550(s32 arg0); /* JP: RhMath_SinI */
f32 func_0020B620(f32 angle); /* JP: RhMath_Cos (matched by position) */
f32 func_0020B730(f32 angle); /* JP: RhMath_Sin */
void func_0020B840(u8 *arg0, s32 arg1, s32 arg2, s32 (*arg3)(u8 *, u8 *)); /* JP: RhMath_HeapSortStruct */
s32 func_0020BA70(void); /* JP: RhGeom_Init */
s32 func_0020BA80(void); /* JP: RhGeom_Term */
void func_0020BA90(void *p); /* JP: RhGeom_SetMatrix */
void func_0020BAD0(void *p); /* JP: RhGeom_GetMatrix */
void func_0020BAF0(s32 arg0); /* JP: RhGeom_PushMatrix */
void func_0020BB50(void); /* JP: RhGeom_PopMatrix */
s32 func_0020BBA0(void); /* JP: RhGeom_ResetMatrixStack */
void func_0020BBB0(void *arg0); /* JP: RhGeom_UnitMatrix */
void func_0020BC00(s32 arg0, void *arg1); /* JP: RhGeom_MulMatrix */
void func_0020BCF0(s32 arg0, s32 arg1); /* JP: RhGeom_MulMatrixRev */
void func_0020BDE0(void *dst, void *src); /* JP: RhGeom_InvertMatrix */
void func_0020C630(void *dst, void *src); /* JP: RhGeom_GetRotXYZMatrix */
void func_0020C750(void *arg0, void *arg1, s32 arg2); /* JP: RhGeom_GetRotVectorMatrix */
void func_0020C8F0(void *arg0, f32 *arg1); /* JP: RhGeom_GetTransMatrix */
void func_0020C940(void *arg0, void *p1, void *p2, void *p3); /* JP: RhGeom_GetScaleRotXYZTransMatrix */
void func_0020CB20(void *arg0, void *arg1); /* JP: RhGeom_ScaleMatrix */
void func_0020CB90(s32 arg0, u32 *arg1); /* JP: RhGeom_RotXYZMatrix */
void func_0020CBD0(s32 arg0); /* JP: RhGeom_RotVectorMatrix */
void func_0020CC10(void *dst, register f32 *scale, s32 *rot, register f32 *trans); /* JP: RhGeom_ScaleRotXYZTransMatrix */
void func_0020CDD0(void *arg0, void *arg1, void *arg2); /* JP: RhGeom_MulMatrixVector */
void func_0020D070(f32 *arg0); /* JP: RhGeom_NormalizeVector */
f32 func_0020D0E0(f32 *arg0); /* JP: RhGeom_GetVectorScalor */
f32 func_0020D100(f32 *arg0, f32 *arg1); /* JP: RhGeom_GetPointsDistance */
void func_0020D140(f32 *arg0, f32 *arg1, f32 *arg2); /* JP: RhGeom_OuterProduct */
f32 func_0020D1A0(f32 *arg0, f32 *arg1); /* JP: RhGeom_InnerProduct */
s64 func_0020D1D0(s32 arg0, s32 arg1, f32 weight0, f32 weight1); /* JP: RhGeom_RotationInterpolate */
void func_0020D240(s32 *out, s32 *from, s32 *to, f32 weight0, f32 weight1); /* JP: RhGeom_RoationComplexInterpolate */
void func_0020D5E0(f32 *arg0, f32 *arg1, f32 *arg2, s32 arg3); /* JP: RhGeom_CreateCameraMatrix2 */
void func_0020D8E0(f32 *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5, f32 fparg6, f32 fparg7, f32 arg_sp0); /* JP: RhGeom_GetScreenMatrix */
void func_0020D9F0(void *arg0); /* JP: RhGeomEx_SetMatrixForStraightLight */
void func_0020DA70(void); /* JP: RhGeomEx_SetMatrixForPointLight */
void func_0020DB00(void *arg0); /* JP: RhGeomEx_GetMatrix */
void func_0020DB20(void); /* JP: RhGeomEx_PushMatrix */
void func_0020DB80(void); /* JP: RhGeomEx_PopMatrix */
void func_0020DBE0(register void *scale, void *rot, register void *trans); /* JP: RhGeomEx_ScaleRotXYZTransMatrix */
s32 func_0020DDB0(void); /* JP: RhView_Init */
s32 func_0020DEE0(void); /* JP: RhView_Term */
s32 func_0020DEF0(void *arg0); /* JP: RhView_GetCurView */
s32 func_0020DF40(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4); /* JP: RhView_SetScreen */
s32 func_0020DF90(f32 fparg0, f32 fparg1); /* JP: RhView_SetAspect */
s32 func_0020DFD0(f32 fparg0, f32 fparg1); /* JP: RhView_SetClipZ */
s32 func_0020E010(f32 *arg0, f32 *arg1); /* JP: RhView_GetScreenCenter */
s32 func_0020E050(f32 *arg0); /* JP: RhView_GetScreenDist */
s32 func_0020E090(f32 *arg0, f32 *arg1); /* JP: RhView_GetClipZ */
s32 func_0020E0D0(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3); /* JP: RhView_SetFogParameter */
s32 func_0020E130(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, u8 *arg4); /* JP: RhView_GetFogParameter */
s32 func_0020E1A0(void *state); /* JP: RhView_Reset */
s32 func_0020E260(void *arg0); /* JP: RhView_Set */
s32 func_0020E360(void *arg0); /* JP: RhView_Modify */
s32 func_0020E460(void); /* JP: RhView_PushStack */
s32 func_0020E4F0(void); /* JP: RhView_PopStack */
s32 func_0020E520(f32 *point, f32 *normal, void *output); /* JP: RhView_PushFakeMirror */
s32 func_0020E970(void *arg0); /* JP: RhView_PopFakeMirror */
s32 func_0020E9F0(void); /* JP: lRhView_ConstructMatrix */
void func_0020EB40(void *arg0); /* JP: RhView_GetWorldScreenMatrix */
void func_0020EBA0(void *arg0); /* JP: RhView_GetWorldViewMatrix */
void func_0020EC00(void *dst); /* JP: RhView_GetViewScreenMatrix */
s32 func_0020EC60(s32 arg0); /* JP: RhView_SendViewParameters */
void func_0020ED30(void *arg0, f32 fparg0); /* JP: RhView_GetSampleZ */
void func_0020F250(s32 arg0); /* JP: RhText_BindAddress */
s32 func_0020F290(s32 arg0); /* JP: RhText_SetTextureFlush */
s32 func_0020F370(void *arg0); /* JP: RhModel_BindAddress */
void *func_0020F4E0(void *arg0, void *arg1); /* JP: RhModel_Draw */
void func_0020FAF0(void *arg0); /* JP: lRhModel_DrawCommonPart */
void func_0020FED0(void *arg0, void *arg1, void *arg2, s32 arg3); /* JP: lRhModel_DynamicAddressBind */
void func_00210010(void *arg0, void *arg1, void *arg2); /* JP: lRhModel_SetupNoMotionRecursive */
s32 func_00210310(void *arg0, s32 depth, void *arg2); /* JP: lRhModel_SetupMultiMotionRecursive */
s32 func_002106E0(void *src0, void *src1, s32 flags, f32 time0, f32 weight0, f32 time1, f32 weight1, void *pos, void *rot, void *scl, f32 multiplier); /* JP: lRhModel_GetMultiMotionItem */
s32 func_00210940(void *arg0, s32 depth, void *arg2); /* JP: lRhModel_SetupFloatMotionRecursive */
s32 func_00210CF0(void *src, f32 time, s32 flags, f32 *position, void *rotation, void *scale, f32 multiplier); /* JP: lRhModel_GetInterpolateMotionItem */
s32 func_00211530(void *arg0, s32 depth, void *arg2); /* JP: lRhModel_SetupPulseMotionRecursive */
s32 func_002118F0(void *src, u32 time, s32 flags, f32 *position, s32 *rotation, f32 *scale, f32 factor); /* JP: lRhModel_GetPulseMotionItem */
void func_00211F70(void *arg0, void *arg1, void *arg2, s32 arg3); /* JP: lRhModel_SetupTexture */
s32 func_00212170(void *arg0, void *arg1, void *arg2, s32 arg3, s32 mask); /* JP: lRhModel_SetupOptionObject */
void func_00212250(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4); /* JP: lRhModel_SetMaterialIntensity */
void func_00212D70(s32 arg0, s32 arg1, s32 arg2); /* JP: lRhModel_ChangeL2VtoL2S */
void func_00212DE0(void); /* JP: GetAnyCoordinateInit */
s32 func_00212DF0(s32 id); /* JP: BookingGetAnyCoordinate */
s32 func_00212E60(s32 arg0, void *arg1); /* JP: GetAnyCoordinate */
u8 *func_00212FD0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: RhModelCpu_DrawAlpha */
s32 func_002130A0(s32 arg0); /* JP: lRhModelCpu_SetupGlobal */
s32 func_00213410(s32 arg0, u32 cursor, s32 size); /* JP: lRhModelCpu_TraceStaticBlock */
s32 func_002134D0(s32 arg0, s32 *arg1); /* JP: lRhModelCpu_CalcIndepStrip */
void func_00213F10(u8 *start, u8 *end); /* JP: lRhModelCpu_CleanupPacket */
void func_00213F60(s32 arg0, s32 arg1); /* JP: RhZSort_Start */
void func_00213F90(void); /* JP: RhZSort_Finish */
s32 func_00213FC0(s32 arg0); /* JP: RhZSort_Finish_Pipe */
s32 func_00214080(s32 *arg0, s32 *arg1); /* JP: lRhZSort_ZCompare */
s32 func_00214090(void *arg0); /* JP: NjaReloc_Adjust_M3DMOT */
s32 func_00214100(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: lNjaReloc_AdjustMotion */
s32 func_00214190(u8 *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: lNjaReloc_AdjustMData2 */
s32 func_00214210(u8 *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: lNjaReloc_AdjustMData3 */
void func_00214290(void); /* JP: SzData_Initialize */
void func_002145D0(s32 arg0); /* JP: SzData_SetRoseFlag */
void *func_002145E0(s32 arg0); /* JP: SzData_GetData */
void func_00214620(s32 arg0); /* JP: SzData_ClearData */
s32 func_00214910(s32 arg0, s32 arg1); /* JP: SzData_GetConstDeck */
void func_00214990(s32 arg0, s32 arg1); /* JP: SzData_SetupFromConstDeck (matched by position) */
s32 func_00214BB0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzData_SetOption */
s32 func_00214D00(s32 arg0, s32 arg1); /* JP: SzData_GetOption */
void *func_00214DD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzData_CheckBag */
void *func_00214F00(s32 arg0, s32 arg1, s32 arg2); /* JP: SzData_GetCardInfo */
s32 func_00214FD0(void *arg0); /* JP: SzData_ClearCardInfo */
s32 func_00215060(s32 arg0, s32 arg1, u32 arg2, s32 arg3); /* JP: SzData_CheckDup */
s32 func_002151D0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzData_CheckDeck */
s32 func_00215280(s32 arg0, s32 arg1, s32 arg2); /* JP: SzData_PushDeckLeader */
s32 func_002153D0(s32 arg0, s32 arg1); /* JP: SzData_PullDeckLeader */
s32 func_002154E0(s32 player, s32 deck_index, s32 card_id); /* JP: SzData_PushDeck */
s32 func_00215770(s32 arg0, s32 arg1, s32 arg2); /* JP: SzData_PullDeck */
s32 func_002158B0(s32 arg0); /* JP: SzData_GetCurrentDeck */
s32 func_00215920(s32 arg0, s32 arg1); /* JP: SzData_SetCurrentDeck */
s32 func_002159D0(s32 arg0, s32 arg1); /* JP: SzData_GetLeader */
s32 func_00215A60(s32 arg0, s32 arg1, s32 arg2); /* JP: SzData_GetCardNo */
s32 func_00215B10(s32 arg0, s32 arg1, s32 operation, s32 value); /* JP: SzData_CalcExp */
s32 func_00215C40(s32 arg0, s32 arg1); /* JP: SzData_CalcDeckCost */
s64 func_00215D30(s32 arg0, s32 arg1); /* JP: SzData_GetRank */
s32 func_00215DE0(s32 player, s32 index); /* JP: SzData_SetRank */
s32 func_00215F00(s32 arg0, s32 arg1); /* JP: SzData_GetDeckCost */
s32 func_00215F90(s32 arg0, s32 arg1); /* JP: SzData_GetDeckCount */
s32 func_00216040(s32 arg0, s32 arg1, s32 arg2); /* JP: SzData_AddBag */
s32 func_00216280(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzData_AddBag2 */
s32 func_00216490(s32 arg0, s32 arg1); /* JP: SzData_DelBag */
s32 func_00216580(s32 arg0, s32 arg1); /* JP: SzData_RollSpecial */
s32 func_002166D0(s32 arg0, s32 arg1); /* JP: SzData_ExchSpecial */
s32 func_00216800(s32 arg0, s32 arg1); /* JP: SzData_PushBagNew */
s32 func_00216920(s32 arg0, s32 arg1); /* JP: SzData_IsBagNew */
s32 func_002169F0(s32 arg0); /* JP: SzData_GetBagCountAll */
s32 func_00216AC0(s32 player, s32 card, s32 category); /* JP: SzData_GetBagCount */
s32 func_00216BC0(s32 arg0, s32 arg1); /* JP: SzData_GetLookFlag (matched by position) */
s32 func_00216C70(s32 arg0, s32 arg1, s32 arg2); /* JP: SzData_SetLookFlag (matched by position) */
s32 func_00216D30(s32 arg0, s32 arg1); /* JP: SzData_GetPassFlag */
s32 func_00216DF0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzData_SetPassFlag */
s32 func_00216EC0(s32 arg0, s32 arg1); /* JP: SzData_GetTreasureFlag */
s32 func_00216F80(s32 player, s32 flag, s32 enabled); /* JP: SzData_SetTreasureFlag */
u16 func_002170A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: SzData_SearchTreasure */
s32 func_002171B0(s32 arg0); /* JP: SzData_GetMapEditFlag */
s32 func_00217230(s32 arg0, s32 arg1); /* JP: SzData_SetMapEditFlag */
s32 func_002172D0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzData_SetRankDirect */
s32 func_002173D0(void); /* JP: RhMemCard_Init */
s32 func_002173F0(void); /* JP: RhMemCard_Term */
s32 func_00217400(void); /* JP: RhMemCard_Act */
void func_00217410(void); /* JP: SzSound_Init */
void func_002174D0(void); /* JP: SzSound_Term */
s32 func_00217530(void); /* JP: SzSound_IsStandby */
void func_00217550(void); /* JP: SzSound_VSync */
s32 func_00217590(s32 arg0, s32 arg1, s32 arg2); /* JP: SzSound_TransferSEGrp */
s32 func_002176B0(void); /* JP: SzSound_IsPlaySE */
s32 func_00217710(s32 arg0, s32 arg1); /* JP: SzSound_PlaySE */
s32 func_002177E0(s32 arg0, s32 arg1, s32 arg2); /* JP: SzSound_StereoPlaySE */
s32 func_002178C0(s32 arg0, s32 arg1); /* JP: SzSound_StopSE */
s32 func_00217980(s32 arg0, s32 arg1); /* JP: SzSound_PlayBGM */
s32 func_002179C0(void); /* JP: SzSound_IsLoadingBGM */
s32 func_00217A10(s64 arg0); /* JP: SzSound_StopBGM */
s32 func_00217A70(s32 arg0); /* JP: SzSound_SetOutput */
void func_00217B00(void); /* JP: SzMem_Init */
s32 func_00217B40(s32 arg0); /* JP: SzMem_Alloc */
void func_00217B50(s32 unused0); /* JP: SzMem_Free */
char *func_00217B60(char *arg0); /* JP: SzMem_StrDup */
void func_00217BD0(s32 arg0, void *src, s16 dx, s16 dy); /* JP: Taku_Obj_Set */
void func_00217CB0(s32 arg0, void *arg1, s16 x, s16 y); /* JP: Taku_Te_Set */
void func_00217D70(s32 arg0, s16 x0, s16 y0, s16 x1, s16 y1, s16 u, s16 v, s16 width, s16 height, u8 r, u8 g, u8 b, u8 a, u8 mode, u16 texture, u8 flag, s16 depth); /* JP: Taku_Prim_Set_SP1 */
void func_00217F90(void *arg0, s32 x, s32 y, s32 width, s32 height, s32 z, s32 f); /* JP: TAKU_SP_XYWH */
void *func_00218020(void *packet, void *src, s16 x, s16 y, u16 flip); /* JP: Taku_FT4_Set */
void *func_00218340(void *arg0, s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, s16 x3, s16 y3, s16 u0, s16 v0, s16 u1, s16 v1, s16 u2, s16 v2, s16 u3, s16 v3, u8 r, u8 g, u8 b, u8 a, u8 mode, u16 texture, u8 flag, s16 depth); /* JP: Taku_Prim_Set_FT4 */
void *func_002185E0(void *arg0, s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, s16 x3, s16 y3, s16 u0, s16 v0, s16 u1, s16 v1, s16 u2, s16 v2, s16 u3, s16 v3, u8 r, u8 g, u8 b, u8 a, u8 unused0, u16 texture, u8 unused1, s16 z); /* JP: Taku_Prim_Set_FT4_ST */
void func_00218840(void *arg0, u16 x0, u16 y0, s32 z0, u8 f0, u16 x1, u16 y1, s32 z1, u8 f1, u16 x2, u16 y2, s32 z2, u8 f2, u16 x3, u16 y3, s32 z3, u8 f3); /* JP: TAKU_FT4_XYWH */
void func_00218970(void *arg0, void *src, s16 x, s16 y); /* JP: Taku_G4_Set */
void func_00218AB0(void *arg0, void *src, s16 x, s16 y, s16 dx, s16 dy); /* JP: Taku_G4_Set2 */
void func_00218C10(void *arg0, s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, s16 x3, s16 y3, u8 r0, u8 g0, u8 b0, u8 a0, u8 r1, u8 g1, u8 b1, u8 a1, u8 r2, u8 g2, u8 b2, u8 a2, u8 r3, u8 g3, u8 b3, u8 a3, u16 mode, s16 z); /* JP: Taku_Prim_Set_G4 */
void func_00218E80(void *arg0, u16 x0, u16 y0, s32 z0, u8 fog0, u16 x1, u16 y1, s32 z1, u8 fog1, u16 x2, u16 y2, s32 z2, u8 fog2, u16 x3, u16 y3, s32 z3, u8 fog3); /* JP: TAKU_G4_XYWH */
void func_00218FB0(void *arg0, void *src, s16 x, s16 y, s16 dx, s16 dy); /* JP: Taku_GT4_Set */
void func_00219180(void *arg0, s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, s16 x3, s16 y3, s16 u0, s16 v0, s16 u1, s16 v1, s16 u2, s16 v2, s16 u3, s16 v3, u8 r0, u8 g0, u8 b0, u8 a0, u8 r1, u8 g1, u8 b1, u8 a1, u8 r2, u8 g2, u8 b2, u8 a2, u8 r3, u8 g3, u8 b3, u8 a3, u8 unused0, u16 texture, u8 unused1, s16 z); /* JP: Taku_Prim_Set_GT4 */
void func_002194B0(void *arg0, s16 x0, s16 y0, s32 z0, u8 fog0, s16 x1, s16 y1, s32 z1, u8 fog1, s16 x2, s16 y2, s32 z2, u8 fog2, s16 x3, s16 y3, s32 z3, u8 fog3); /* JP: TAKU_GT4_XYWH */
void func_0021BAE0(void *arg0); /* JP: Taku_Coord_Init */
void func_0021BB20(u8 *arg0); /* JP: Taku_Coord_Set */
void func_0021BB70(void *arg0, void *arg1); /* JP: Taku_Vector_Set */
void func_0021BB90(s32 *arg0, s32 *arg1, s32 arg2); /* JP: Taku_3D_2D_Set */
void func_0021BC10(f32 *outX, f32 *outY, s16 *outCount, f32 *points, f32 *intervals, s32 count, s16 mode, f32 spacing); /* JP: Taku_spline2 */
f32 func_0021C320(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4); /* JP: func */
void func_0021C350(f32 *a, f32 *b, f32 *c, f32 *r, f32 *u, s32 n); /* JP: tri_diag */
s32 func_0021C450(s32 arg0, s32 arg1, s32 arg2, s64 arg3, s64 arg4, s32 arg5, s32 arg6); /* JP: Taku_Bunsyou_Set */
void func_0021D480(void); /* JP: Taku_Camp_Data_Init */
void func_0021D850(void); /* JP: Taku_Screen_Init */
void func_0021DA60(void); /* JP: TkCamp_Draw */
void func_0021DAA0(void); /* JP: TkCamp_Draw_After */
s32 func_0021DDA0(s32 arg0); /* JP: TkCamp_Draw_Pipe */
void *func_0021DFF0(void *packet, s32 id, s32 x, s32 y, f32 depth, s32 width, s32 height, s32 alpha); /* JP: Taku_Camp_Teki_Model_Disp */
s32 func_002232F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: Taku_Camp_Kazu_Disp (matched by position) */
void func_00224A40(void); /* JP: Taku_Camp_Ivent_Name_Set (matched by position) */
void *func_00226120(void *arg0); /* JP: Taku_Camp_Kumo */
void func_00228660(s16 player, s16 side, s8 state, s16 *items, s16 count); /* JP: Taku_Dodai_Root_init */
void func_00228940(s16 arg0, s16 arg1); /* JP: Taku_Fune_init */
s32 func_00228970(void); /* JP: Taku_Tyumoku_ido */
s32 func_00228AD0(s16 arg0, s16 arg1, s16 *arg2, s16 arg3); /* JP: Taku_Tyumoku_ido0 */
s32 func_00228F50(s16 arg0, s16 arg1); /* JP: Taku_Tyumoku_ido1 */
s32 func_00229140(s32 arg0, s32 arg1, s16 arg2); /* JP: Taku_Tyumoku_ido_kettei */
s32 func_002294B0(s32 arg0, s16 arg1); /* JP: Taku_Tyumoku_ido_katimake */
s32 func_0022A020(s32 arg0); /* JP: Taku_Camp_STON */
s32 func_0022A140(s32 arg0); /* JP: Taku_DECK_CARD_DISP */
void func_0022A710(s32 packet); /* JP: Taku_Camp_3D */
s32 func_0022C3C0(s32 arg0); /* JP: My_LedarModel_a_set */
void func_0022C450(void); /* JP: Taku_spline_init */
s32 func_0022CC40(s32 arg0, s16 arg1, s16 arg2, s16 arg3); /* JP: Taku_Camp_3D_FUNE */
s32 func_0022D140(void); /* JP: Taku_Camp_BUN_HANTEI (matched by position) */
s32 func_0022F1C0(s32 arg0, s32 arg1, s16 arg2, s16 arg3); /* JP: Taku_Camp_BOTAN_MATI */
void func_002336F0(void); /* JP: Taku_Camp_Set_Go_Duel */
void func_00233F50(s8 arg0); /* JP: Taku_Camp_SINEMA_Init */
void *func_002351A0(void *arg0); /* JP: Taku_Camp_SYS_ICON */
s32 func_00236C50(s32 arg0); /* JP: Taku_Camp_TIKEI_WINDOW */
void func_002374D0(void); /* JP: Taku_Camp_3D_Poly_Init */
void func_0023B1F0(s32 arg0); /* JP: TkCamp_Act2 */
void func_0023B920(void); /* JP: TkCamp_Term */
void func_0023BB00(s32 arg0); /* JP: Taku_Camp_Go_Rensyu_Duel */
void func_0023BC80(void); /* JP: Taku_Camp_Go_Help */
void *func_0023BFF0(void *arg0, f32 fparg0, s32 arg1, f32 fparg1, s32 arg2); /* JP: Taku_Camp_Card_Get */
s32 func_0023C140(void); /* JP: Taku_Get_Duel5_flg */
void func_0023C150(void); /* JP: Taku_Set_Duel5_flg */
s32 func_0023C160(void); /* JP: Taku_Get_WinCount */
s32 func_0023C170(s32 arg0); /* JP: TakuCard_inti */
s32 func_0023C3F0(s32 arg0); /* JP: TkMc_Check_Main */
s16 func_0023C560(s32 arg0); /* JP: TkMc_Save_Main (matched by position) */
s32 func_0023C770(s32 arg0); /* JP: TkMc_Load_Main (matched by position) */
s32 func_0023C8B0(s32 arg0); /* JP: TkMc_Trade_Load_Main (matched by position) */
s16 func_0023CA10(s32 arg0); /* JP: TkMc_Trade_Save_Main (matched by position) */
s16 func_0023CC50(s32 arg0); /* JP: TkMc_Custom_Main (matched by position) */
s32 func_0023CE40(s32 arg0); /* JP: TakuSave_card_kansi (matched by position) */
s32 func_0023D170(s32 arg0); /* JP: TakuSave_card_filename_check */
s32 func_0023D400(void); /* JP: TakuSave_card_file_open (matched by position) */
s32 func_0023D920(void); /* JP: TakuSave_make_file */
s32 func_0023DE90(void); /* JP: TakuSave_card_file_kakikomi (matched by position) */
s32 func_0023E610(void); /* JP: TakuSave_card_format (matched by position) */
s32 func_0023E6D0(void); /* JP: TakuSave_card_unformat */
s32 func_0023F130(s32 arg0); /* JP: TakuLoad_card_kansi (matched by position) */
s32 func_0023F340(void); /* JP: TakuLoad_card_filename_check */
s32 func_0023F5A0(void); /* JP: TakuLoad_card_file_open (matched by position) */
s32 func_0023FCE0(s32 arg0); /* JP: TakuCustom_card_kansi (matched by position) */
s32 func_0023FF30(void); /* JP: TakuCustom_card_file_open (matched by position) */
s32 func_002406C0(s32 arg0); /* JP: TakuTrade_Save_card_kansi */
s32 func_002409E0(void); /* JP: TakuTrade_Save_card_file_kakikomi_Ver2 (matched by position) */
s32 func_00241190(u16 *arg0); /* JP: LkCheckData */
void func_002413F0(u8 *out, u8 value, f32 hue, f32 light, f32 sat); /* JP: SzColor_HLS2RGB (matched by position) */
void func_00241840(u8 *color, s32 r, s32 g, s32 b, s32 arg4, u8 max, f32 scale); /* JP: SzColor_RGB2SEP */
s32 func_00241A00(s32 arg0, s32 arg1, f32 scale); /* JP: SzColor_CLUT2SEP */
void func_00241A90(void *arg0); /* JP: readBufCreate */
void func_00241AC0(void); /* JP: readBufDelete */
s32 func_00241AD0(void *arg0, void **arg1); /* JP: readBufBeginPut */
s32 func_00241B10(void *arg0, s32 arg1); /* JP: readBufEndPut */
s32 func_00241B80(void *arg0, void **arg1); /* JP: readBufBeginGet */
s32 func_00241BE0(s32 *arg0, s32 arg1); /* JP: readBufEndGet */
void func_00241C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: clearGsMem */
void func_00241E80(u64 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: setImageTag */
s32 func_002423A0(void); /* JP: handler_endimage */
void func_002423F0(s32 arg0); /* JP: startDisplay */
void func_00242450(void); /* JP: endDisplay */
void func_00242470(s32 arg0, s32 arg1, s32 arg2); /* JP: movie_play */
s32 func_00242580(s32 arg0); /* JP: movie */
void func_00242900(void); /* JP: switchThread */
s32 func_00242910(void); /* JP: isAudioOK */
void func_00242950(s32 arg0); /* JP: initAll */
void func_00242C20(void); /* JP: termAll */
void func_00242CD0(void); /* JP: defMain */
void func_00242CF0(s8 *arg0); /* JP: ErrMessage */
void func_00242D00(void); /* JP: proceedAudio */
s32 func_00242D10(s32 arg0, void *arg1, u8 *arg2); /* JP: videoCallback */
s32 func_00242E40(s32 arg0, void *arg1, u8 *arg2); /* JP: pcmCallback */
s32 func_00242F20(void *arg0, s32 arg1, void *arg2, s32 arg3, void *arg4, s32 arg5, void *arg6, s32 arg7); /* JP: copy2area */
s32 func_00243060(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: audioDecCreate */
s32 func_00243170(void *arg0); /* JP: audioDecDelete */
void func_002431B0(void *arg0); /* JP: audioDecPause */
void func_00243230(void *arg0); /* JP: audioDecResume */
void func_00243290(void *arg0); /* JP: audioDecStart */
void func_002432F0(void *arg0); /* JP: audioDecReset */
void func_00243390(void *arg0, void **arg1, s32 *arg2, void **arg3, s32 *arg4); /* JP: audioDecBeginPut */
void func_00243450(void *arg0, u32 arg1); /* JP: audioDecEndPut */
s32 func_00243580(void *arg0); /* JP: audioDecIsPreset */
s32 func_002435A0(void *arg0); /* JP: audioDecSendToIOP */
void func_00243750(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, void *arg4, s32 offset); /* JP: iopGetArea */
s32 func_002437F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7); /* JP: sendToIOP2area */
s32 func_00243950(s32 arg0, s32 arg1, s32 arg2); /* JP: sendToIOP */
void func_002439D0(s32 arg0); /* JP: changeMasterVolume */
void func_00243A40(s32 arg0); /* JP: changeInputVolume */
s32 func_00243A90(void *arg0, s32 arg1); /* JP: strFileOpen */
s32 func_00243D90(void *arg0); /* JP: strFileClose */
s32 func_00243DE0(s32 *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: strFileRead */
s32 func_00243EE0(void *arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: viBufCreate */
s32 func_00243F60(void *arg0); /* JP: viBufReset (matched by position) */
void func_002440F0(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4); /* JP: viBufBeginPut */
void func_002441F0(void *arg0, s32 arg1); /* JP: viBufEndPut */
s32 func_00244250(void *arg0); /* JP: viBufAddDMA (matched by position) */
s32 func_00244530(u8 *arg0); /* JP: viBufStopDMA (matched by position) */
s32 func_00244A40(void *arg0); /* JP: viBufDelete (matched by position) */
s32 func_00244AD0(void *arg0); /* JP: viBufCount */
void func_00244B20(void *arg0); /* JP: viBufFlush */
s32 func_00244B70(void *arg0, void *arg1); /* JP: viBufModifyPts */
s32 func_00244CB0(void *arg0, void *arg1); /* JP: viBufPutTs */
s32 func_00244FB0(void *arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4, s32 arg5, s32 arg6, s32 arg7); /* JP: videoDecCreate */
s32 func_002450B0(void); /* JP: videoDecSetStream */
void func_002450D0(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4); /* JP: videoDecBeginPut */
void func_002450E0(void *arg0, s32 arg1); /* JP: videoDecEndPut */
void func_002450F0(void *arg0); /* JP: videoDecReset */
s32 func_00245100(u8 *arg0); /* JP: videoDecDelete */
void func_00245140(void *arg0); /* JP: videoDecAbort */
s32 func_00245150(void *arg0); /* JP: videoDecGetState */
void func_00245160(void *arg0, s64 arg1, s64 arg2, s32 arg3, s32 arg4); /* JP: videoDecPutTs */
s32 func_002451A0(void *arg0); /* JP: videoDecFlush */
s32 func_00245280(void *arg0); /* JP: videoDecIsFlushed */
void func_002452E0(void *arg0); /* JP: videoDecMain */
s32 func_00245520(void *arg0, void *arg1); /* JP: mpegError */
s32 func_00245550(void); /* JP: mpegNodata */
s32 func_00245580(void); /* JP: mpegStopDMA */
s32 func_002455B0(void); /* JP: mpegRestartDMA */
s32 func_002455E0(s32 arg0, void *arg1); /* JP: mpegTS */
s32 func_00245630(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4, s32 arg5, s32 arg6, s32 arg7); /* JP: cpy2area */
void func_00245770(void *arg0, s32 arg1, void *arg2, s32 arg3); /* JP: voBufCreate */
void func_002457C0(void); /* JP: voBufDelete */
void func_002457D0(void *arg0); /* JP: voBufReset */
s32 func_002457E0(void *arg0); /* JP: voBufIsFull */
void func_00245800(void *arg0); /* JP: voBufIncCount (matched by position) */
s32 func_00245890(void *arg0); /* JP: voBufGetData */
s32 func_002458E0(void *arg0); /* JP: voBufGetTag */
void func_00245960(void *arg0); /* JP: voBufDecCount */
void func_00245980(s32 arg0, s32 arg1, void *arg2); /* JP: ShAnime_GetPartsRect */
void func_002459D0(u8 arg0, u8 arg1, void *arg2); /* JP: ShAnime_GetPatInfo */
void func_00245A30(s32 arg0, s32 arg1, s32 arg2, void *arg3); /* JP: ShAnime_GetFixInfo */
void func_00245AE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4); /* JP: ShAnime_GetAnmDat */
s32 func_00245BE0(void *arg0); /* JP: ShFace_Request */
void func_00245D80(u8 *arg0); /* JP: ShFace_Close */
void func_00245DB0(void *arg0, void *arg1, s32 arg2, s32 arg3); /* JP: ShFace_Prim */
void func_002460F0(void *arg0); /* JP: ShFace_DrawOne */
s32 func_00246340(s32 arg0); /* JP: ShFace_Draw_Pipe */
void func_00246450(s32 arg0); /* JP: ShFace_Init */
void func_00246490(void); /* JP: ShFace_Draw */
void func_002464C0(void); /* JP: ShFace_Act */
void func_002464E0(void); /* JP: ShFace_Term */
s32 func_002464F0(s32 arg0, s32 arg1, s32 arg2); /* JP: GetMoveRev */
s32 func_00246810(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, void *arg6); /* JP: Battle */
s32 func_00248370(u32 arg0, s32 arg1, s32 arg2); /* JP: Do_ChkEncMatch */
s32 func_002487A0(s32 arg0, s32 arg1); /* JP: Do_Chk_Enc */
s32 func_00248AF0(s32 arg0, s32 arg1, s32 arg2); /* JP: Chk_Enc */
s32 func_00248E30(s32 arg0, s32 arg1); /* JP: Ta_GetForceEffection */
s32 func_00248EA0(void); /* JP: Ta_GetEnchantOfs */
s32 func_00248F60(s32 arg0, s32 arg1); /* JP: Ta_GetHandEnchant */
s32 func_00248FD0(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_GetHandEnchant2 */
s32 func_00249040(s32 arg0, s32 arg1); /* JP: Ta_GetHandEnchant3 */
s32 func_00249200(s32 arg0); /* JP: Ta_GetEncEffect */
s32 func_002492F0(s32 arg0); /* JP: Ta_GetToonAgreement */
s32 func_00249320(s32 arg0); /* JP: TaEnc_IsEncDo */
s64 func_002493A0(s32 arg0); /* JP: TaEnc_GetEncScore */
s32 func_00249410(u16 arg0, u16 *arg1); /* JP: TaEnc_GetEnchantLst */
s32 func_002494D0(void); /* JP: TaEnc_GetRandomElf (matched by position) */
s32 func_00249560(s32 arg0); /* JP: TaEnc_IsActReflexEnc */
u8 func_00249580(s32 arg0); /* JP: TaEnc_GetEncID */
u32 func_002495A0(s32 arg0, s32 arg1); /* JP: Fusion */
s32 func_00249630(s32 arg0, s32 arg1); /* JP: WallFusion */
s32 func_0024B310(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 arg5); /* JP: Chk_TrapA */
void func_0024C330(s32 *list, s32 left, s32 right); /* JP: SortByOrder */
void func_0024C450(s32 *arg0, s32 arg1, s32 arg2); /* JP: Swap */
s32 func_0024C480(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaTrapA_IsTrapAct */
s32 func_0024C780(u32 arg0, s32 arg1, s32 arg2); /* JP: ConvUnitIDtoFlagList */
s32 func_0024C7D0(u32 arg0, s32 arg1, s32 arg2); /* JP: ConvUnitIDtoFlagList_OFF */
s32 func_0024C870(s32 arg0); /* JP: Ta_ConvBitLengthToNumericLength */
void func_0024C910(s32 arg0, s32 arg1, s16 *arg2); /* JP: TaUtil_GetUnitLst */
s32 func_0024DD80(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_SideMatch */
s32 func_0024DE20(s32 arg0, s32 arg1); /* JP: Ta_GetEOwnerSide */
s32 func_0024DE70(s32 arg0, s32 arg1); /* JP: Ta_GetCurrentSide */
s32 func_0024DEB0(s32 arg0, void *arg1); /* JP: CheckLandAgreement */
s32 func_0024DF00(s32 arg0, s32 arg1, s32 arg2); /* JP: CheckLandAgreement2 */
s32 func_0024E220(s32 arg0, s32 arg1); /* JP: Ta_GetSummonablePiece */
s32 func_0024E300(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_GetSummonablePieceWithOrder */
s32 func_0024E410(s32 arg0, u32 arg1); /* JP: Ta_GetSommonPiecePreference */
s32 func_0024E780(s32 arg0, u8 arg1); /* JP: Ta_GetUnitNum */
void func_0024E880(void *arg0, s32 *arg1); /* JP: Ta_SetEffectObjByField */
s32 func_0024E910(s32 arg0); /* JP: Ta_GetUnitNumFrom22bitFlagList */
s32 func_0024E950(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_GetLocDistanceFromCenterOnRangeXY */
s32 func_0024EA10(s32 arg0, u32 arg1); /* JP: Ta_GetAgreeOwnerIDon22bitFlagLst */
s32 func_0024EA60(void); /* JP: TaUtil_GetObjSideNum */
s32 func_0024EA70(s32 arg0, s32 arg1); /* JP: ChkAttrAdv */
s32 func_0024EBD0(s32 arg0); /* JP: Ta_GetRandomUnit */
s32 func_0024EC50(s32 mask, s32 ordinal); /* JP: Ta_GetUnitOwnerIDFromLstCount */
s32 func_0024ECD0(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: Ta_GetUnitAgreeWithVarInfo */
s32 func_0024EFB0(s32 mask); /* JP: Ta_GetMinimumOrderUnitFromFlagList */
s32 func_0024F060(s32 arg0, s32 arg1); /* JP: Ta_GetMinimumOrderUnitFromFlagList2 */
s32 func_0024F150(s32 mask); /* JP: Ta_GetMaximumOrderUnitFromFlagList */
u32 func_0024F200(s32 arg0); /* JP: Ta_GetMinimumParamUnitFromFlagList */
s32 func_0024F2F0(s32 arg0, s32 arg1); /* JP: Ta_GetAPPlusDP */
s32 func_0024F520(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4); /* JP: TaUnit_AddUnitEfc */
s32 func_0024F780(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: Ta_Do_CompMove */
s32 func_0024FD10(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_IsVirus */
void func_0024FDA0(s32 arg0, s32 arg1); /* JP: Ta_IsVirus_Chk */
s32 func_0024FDD0(s32 arg0); /* JP: Ta_IsVirus_Chk2 */
s32 func_0024FE40(void *arg0, s32 arg1, s32 arg2); /* JP: Ta_IsVirus_Chk3 */
s32 func_0024FEB0(void *arg0); /* JP: Ta_IsVirusAll */
s32 func_00250000(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_IsGraveEntryHit */
void func_002500C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: Ta_UnitFade */
s32 func_00250300(u16 arg0, s32 arg1, s32 arg2); /* JP: Ta_CalcCtrlRate */
s32 func_00250360(s32 arg0, s32 arg1); /* JP: Ta_IsUnitControl */
s32 func_00250370(void *arg0); /* JP: Ta_IsUnitControl2 */
void func_002503B0(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_SetUnitCurseRest */
s32 func_00250430(s32 arg0, s32 arg1); /* JP: Ta_GetRecycle */
s32 func_00250620(s32 arg0, s32 arg1); /* JP: Ta_GetRecycleRequestLvl */
void *func_00250740(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_GetUnitEffect */
s32 func_002507D0(s32 arg0, s32 arg1); /* JP: TaUtil_IsExMonster */
s32 func_00250860(s32 arg0, s32 arg1); /* JP: GetCap */
s32 func_002508D0(s32 arg0); /* JP: GetParCap */
s32 func_00250900(void *arg0); /* JP: TaUtil_IsVarInfoLeader */
s32 func_00250940(s32 arg0, s32 arg1); /* JP: TaUtil_GetGraveCardNum */
s32 func_002509E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaUtil_GetUnitAP */
s32 func_00250A60(s32 arg0, s32 arg1, s32 arg2); /* JP: TaUtil_GetUnitAP2 */
s32 func_00250AC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaUtil_GetUnitAP3 */
s32 func_00250B40(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaUtil_GetUnitDP */
void func_00250BC0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaUtil_GetUnitDP2 */
s32 func_00250C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaUtil_GetUnitDP3 */
s32 func_00250CA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaUtil_CalcUnitAP */
s32 func_00250E80(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaUtil_CalcUnitDP */
s32 func_00251370(s32 count, u16 *src, void *dst); /* JP: TaSlot_SetReelData */
void func_002516D0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaUtil_DoOpen */
s32 func_002517D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 *out, s32 arg7); /* JP: Ta_Manage_DestEfc */
s32 func_00252440(s32 x, s32 y, void *arg2, s32 phase); /* JP: Ta_Open */
s32 func_00252EC0(s32 x, s32 y, void *arg2, u8 *tail, s32 phase, u32 *info); /* JP: Ta_Do_Magic */
s32 func_00254890(s32 *arg0, s32 arg1); /* JP: Ta_GetSacrificeUnit */
s32 func_00254B20(void *arg0, s32 arg1); /* JP: Ta_GetScrificeOrder */
void func_00254C90(s32 *arg0, s32 arg1); /* JP: Ta_GetCeremSacrifice */
s32 func_002550C0(u32 *arg0, u16 *arg1, s32 arg2); /* JP: Ta_Manage_Effect */
void func_00255960(void *arg0); /* JP: InitEffectTemp */
s32 func_00255A30(void *arg0, void *arg1); /* JP: Ta_Do_Effect */
s32 func_00255AC0(void *arg0, s16 arg1); /* JP: TaEffect_LoadModule */
s32 func_00255B50(void *arg0); /* JP: TaEffect_IsLoadModule */
s32 func_00255C30(void *arg0, s32 arg1); /* JP: TaEffect_IsLoadModule2 */
void func_00255CD0(void *arg0); /* JP: TaEffect_ClearEffectTemp */
void func_00255D40(s32 *arg0); /* JP: Ta_GetStdCompleteView */
void func_00255DB0(void *arg0); /* JP: Ta_GetStdTopDownView */
void func_00255E20(void *arg0); /* JP: Ta_GetFlatCompleteView */
void func_00255E90(void *arg0); /* JP: Ta_GetDestinyView */
void func_00255F00(void *arg0, s32 arg1); /* JP: Ta_GetStdFocusView */
void func_00255F70(void *arg0, s32 arg1); /* JP: Ta_GetStdFocusView2 */
void func_00255FE0(void *arg0); /* JP: Ta_GetTopView */
void func_00256050(void *arg0); /* JP: Ta_GetSkyView */
s32 func_002560C0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_000 */
s32 func_00256AB0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_003B */
s32 func_00256D80(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_001 */
s32 func_00257340(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_004 */
s32 func_00257AA0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_005 */
s32 func_00258490(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_006 */
s32 func_00258760(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_007 */
s32 func_00258E20(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_008 */
s32 func_00259D90(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_012 */
s32 func_0025A060(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_013 */
s32 func_0025A4C0(void *arg0, u16 *arg1, s32 arg2); /* JP: Ta_Eff_014 */
s32 func_0025A940(s32 arg0, u16 *arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: TaEff_PopHand */
s32 func_0025AA80(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_015 */
s32 func_0025AD60(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_016 */
s32 func_0025B050(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_017_A */
s32 func_0025B330(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_018 */
s32 func_0025B610(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_019 */
s32 func_0025B900(s32 arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_020 */
s32 func_0025BE50(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_021 */
s32 func_0025C0B0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_023 */
s32 func_0025C330(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_025 */
s32 func_0025C9E0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_026 */
s32 func_0025D230(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_029_CNG */
s32 func_0025D640(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_029 */
s32 func_0025D9D0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_028 */
s32 func_0025DE70(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_030 */
s32 func_0025E200(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_031 */
void func_0025EBE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: Ta_SwapUnit */
s32 func_0025ECB0(void); /* JP: Ta_SearchMoveTemp */
s32 func_0025ED20(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_034 */
s32 func_0025EE40(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_033 */
s32 func_0025EF40(s32 arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_035 */
s32 func_0025F2A0(void); /* JP: Ta_GetStackMapPiece */
void func_0025F310(void); /* JP: Ta_InitMazePiece */
s32 func_0025F390(void *arg0); /* JP: Ta_IsFinishEffect */
s32 func_0025F400(void *arg0, void *arg1, void *arg2); /* JP: Ta_ManageDestroyEffect */
s32 func_0025F670(void *arg0, void *arg1); /* JP: Ta_IsFinishDestEfc */
void func_0025F720(void *arg0, void *arg1, void *arg2, s32 arg3); /* JP: Ta_SetEffectDependOnFlagLst */
void func_0025F820(void *arg0, void *arg1, void *arg2, s32 arg3); /* JP: Ta_SetEffectDependOnFlagLst2 */
void func_0025F990(void *arg0, void *arg1, void *arg2, s32 arg3); /* JP: Ta_SetEffectDependOnFlagLst3 */
void func_0025FB00(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_CalcLPinEffectSeq */
void func_0025FC30(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: Ta_AllUnitFade2 */
s32 func_0025FD90(void); /* JP: Ta_IsFinishFade (matched by position) */
void func_0025FF30(s32 arg0, s32 arg1); /* JP: TaEff_RestoreStdRate */
void func_00260020(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: Ta_AllUnitFade */
s32 func_00260200(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_ETC */
s32 func_00260320(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_WAIT */
void func_00260490(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: Ta_SetRangeVisual */
void func_00260740(s32 arg0); /* JP: TaView_ReqStdCompleteView */
void func_002607D0(s32 arg0); /* JP: TaView_ReqStdTopDownView */
void func_00260860(s32 arg0); /* JP: TaView_ReqFlatCompleteView */
void func_002608F0(s32 arg0); /* JP: TaView_SetDestinyCamera */
void func_00260990(s32 arg0, s32 arg1); /* JP: TaView_ReqRotCamera */
void func_00260A70(void *arg0, s32 arg1); /* JP: TaView_RestoreOriginalView */
void func_00260AF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaView_ReqFocusCamera */
void func_00260D10(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaView_ReqFocusCamera3 */
void func_00260EB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaView_ReqExzFocusCamera */
void func_002610D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaView_ReqBackFocusCamera */
void func_002612E0(void *arg0, s32 arg1, s32 arg2); /* JP: TaView_SetModelFrontView */
void func_00261380(void *arg0, s32 arg1, s32 arg2); /* JP: TaView_SetExzModelFrontView */
void func_00261420(void *arg0, s32 arg1, s32 arg2); /* JP: TaView_SetModelBackView */
void func_002614C0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaView_ReqFocusCamera2 */
void func_00261570(s32 arg0, s32 arg1, u8 arg2, u8 arg3); /* JP: TaView_ReqFireView */
void func_00261580(void); /* JP: TaView_ReqTopView */
void func_00261600(void); /* JP: TaView_ReqSkyView */
void func_00261680(s32 arg0); /* JP: TaEffect_SetOuchMotion */
s32 func_00261760(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_017_MEGUMI */
s32 func_00261B70(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_006_WIND */
s32 func_00261F20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4); /* JP: Manage_AtkEfc */
s32 func_00262190(u32 arg0, u32 arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7); /* JP: Do_AtkEfc */
s32 func_00262680(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: Match_AtkEfcObj */
s32 func_002626F0(s32 arg0, s32 arg1, s32 arg2); /* JP: Do_Match_AtkEfcObj */
s32 func_00262BE0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_100 */
s32 func_00263500(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_063 */
s32 func_00263790(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_065 */
s32 func_00265050(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_045 */
s32 func_00265440(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_044 */
s32 func_00265890(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_046 */
s32 func_002660E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: Ta_GetParamOfs */
s32 func_00266500(s32 arg0, s32 arg1, void *output); /* JP: Ta_ManageNaturalEffectInStandbyPhase */
s32 func_00266910(s32 arg0, s32 arg1, void *arg2); /* JP: Ta_ManageNaturalEffectInStandbyPhase2 */
s32 func_00266A80(s32 arg0, s32 arg1); /* JP: TaPerm_IsPermCurseActive */
s32 func_00266C70(s32 arg0, s32 arg1); /* JP: Ta_SearchUncTypeNaturalEffectUser */
s32 func_00266DF0(s32 arg0); /* JP: Ta_SearchUncTypeNaturalEffectUserNum */
s32 func_00266F70(s32 arg0, s32 arg1); /* JP: Ta_SearchUncTypeNaturalEffectUserNumWithSide */
s32 func_002670F0(s32 arg0, s32 arg1); /* JP: Ta_GetLPRevByNaturalEffect */
s32 func_00267380(s32 arg0, s32 arg1); /* JP: Ta_IsUnitHide */
s32 func_00267560(s32 arg0); /* JP: Ta_IsUnitHide2 */
s32 func_00267700(s32 arg0, s32 arg1); /* JP: Ta_IsResistAll */
s32 func_00267860(s32 arg0, s32 arg1); /* JP: Ta_IsResistAllMaster */
s32 func_002679C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: Ta_IsVisualAttrAdv */
s32 func_00267B30(s32 arg0); /* JP: Ta_GetSummonCalcRevision */
s32 func_00268600(s32 arg0, s32 arg1); /* JP: Ta_GetExzodiaPartsUnit */
s32 func_002686F0(s32 arg0); /* JP: Ta_GetExzodiaPartsCardNo */
s32 func_00268760(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_057 */
s32 func_00268FA0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_059 */
s32 func_002692D0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_060 */
s32 func_002695D0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_036 */
void func_00269D60(void *arg0, void *arg1); /* JP: Ta_Eff_036_LoadEffect */
void func_00269E10(void *arg0); /* JP: Ta_Eff_036_GetSound */
void func_00269EC0(void *arg0, void *arg1); /* JP: Ta_Eff_036_ManageSound */
s32 func_0026A0A0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_037 */
s32 func_0026AB80(s32 arg0, s32 arg1); /* JP: Ta_IsActiveTrapB */
s32 func_0026AC90(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_GetActiveTrapBUnit */
s32 func_0026AE70(s32 arg0, s32 arg1, s32 arg2, s32 *arg3); /* JP: Ta_IsTrapBInDecideOperation */
s32 func_0026B1F0(s32 arg0, s32 arg1, s32 arg2, u8 arg3); /* JP: Ta_IsTrapBInDecideOperation2 */
s32 func_0026B430(void *arg0); /* JP: Ta_DoUncTrapB */
s32 func_0026B480(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_054 */
s32 func_0026BB80(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_056 */
s32 func_0026BE20(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_101 */
s32 func_0026BF50(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_102 */
s32 func_0026C170(u32 *src, void *arg1, s32 arg2); /* JP: Ta_Eff_109 */
void func_0026CD80(s32 arg0); /* JP: Ta109_BlackOutForExz */
s32 func_0026CFC0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_072 */
s32 func_0026D600(s32 arg0, s32 arg1, s32 arg2, s32 *arg3); /* JP: Ta_RequestGravityReserve */
s32 func_0026D6E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: Ta_GetUnitGravityLoc */
s32 func_0026D840(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: Ta_GetUnitGravityLocSearchOnZ */
s32 func_0026D8F0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_066 */
s32 func_0026DCC0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_067 */
s32 func_0026E1F0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_051 */
s32 func_0026E950(void); /* JP: Ta_GetSummonCost */
s32 func_0026EA00(s32 *arg0); /* JP: Ta_ManageHandEffect */
s32 func_0026EA80(s32 arg0, s32 arg1); /* JP: Ta_GetSummonRev */
s32 func_0026EEA0(void *arg0, s32 arg1, s32 arg2); /* JP: Ta_Do_HandDestroyEfc */
s32 func_0026EED0(s32 arg0); /* JP: Ta_IsDestinyDraw */
s32 func_0026F600(s32 arg0, s32 *arg1); /* JP: Ta_SetDestinyEffect */
s32 func_0026F690(s32 arg0, u16 *arg1, s16 *arg2, s32 arg3); /* JP: Ta_GetDestinyDraw */
s32 func_0026FA70(s32 arg0, s32 arg1); /* JP: TaHand_GetCardSummonCost */
s32 func_0026FA80(s32 arg0, s32 arg1); /* JP: TaHand_GetCardSummonCost2 */
s32 func_0026FB10(s32 arg0, s32 arg1); /* JP: TaHand_IsCardSummon2 */
s32 func_0026FB60(s32 arg0, s32 arg1); /* JP: TaHand_IsCardSummon */
u32 func_0026FBB0(s32 arg0); /* JP: TaHand_GetCardAPDP */
s32 func_0026FC10(s32 arg0); /* JP: TaHand_IsCardEffect */
void *func_0026FC90(s32 arg0, s32 arg1); /* JP: TaHand_GetCardEffect */
s32 func_0026FCE0(s32 arg0); /* JP: TaHand_GetCardKind */
void func_0026FD30(s32 arg0, s32 *arg1); /* JP: TaHand_GetNextHand */
s32 func_0026FE20(s32 arg0); /* JP: TaHand_GetNextHandNum */
s32 func_0026FE70(void *src, void *obj, s32 mode); /* JP: Ta_Eff_Hand_Fail */
s32 func_00270030(void *src, void *obj, s32 mode); /* JP: Ta_Eff_Hand_Fusion */
s32 func_00270260(void *src, void *state, s32 mode); /* JP: Ta_Eff_Hand_Enc */
s32 func_00271630(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_Hand_Dest */
s32 func_00271740(s32 arg0, s32 arg1); /* JP: Ta_IsLDAbl */
s32 func_002717A0(s32 arg0); /* JP: Ta_GetLDChgLand */
s32 func_00271830(s32 arg0); /* JP: Ta_GetLDLvRev */
s32 func_00271950(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: Ta_IsSquareRange */
s32 func_00271A40(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_IsLDRange */
s32 func_00271AF0(void *arg0, s32 arg1, s32 arg2); /* JP: Ta_GetLDParamOfs2 */
s32 func_00271C90(s32 arg0, s32 arg1); /* JP: Ta_IsLD_PDownObj */
s32 func_00271E40(s32 arg0, s32 arg1, s32 arg2); /* JP: Ta_IsLDRangeAvility */
s32 func_00271F00(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: Ta_IsLDRangeAvilityFromLoc */
s32 func_00271F90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: Ta_IsLDRangeAvilityWithLocation */
s32 func_00272050(s32 arg0, s32 arg1); /* JP: Ta_IsLD_CurseObj */
s32 func_002720F0(s32 arg0, s32 arg1); /* JP: Ta_IsLD_DestObj */
u32 func_00272210(s32 arg0, s32 arg1); /* JP: Ta_RemoveObjFromFlagLst */
u32 func_00272330(s32 arg0, s32 arg1); /* JP: Ta_RemoveObjFromFlagLst2 */
s32 func_002724C0(s32 arg0); /* JP: Ta_GetLDRange */
s32 func_002724F0(s32 phase, s32 *res); /* JP: Ta_Do_EndPhase */
s32 func_00273460(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_112 */
s32 func_002738B0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_113 */
s32 func_002755D0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_BTL_002 */
s32 func_00275740(u32 *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_070 */
s32 func_002759D0(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_071 */
s32 func_00275D00(s32 arg0, void *arg1); /* JP: TaLogic_InitLogicData */
s32 func_00275E30(void *arg0); /* JP: TaLogic_AdjustLogicData */
s32 func_00275E80(void *arg0); /* JP: TaLogic_DoAdjustLogicData */
s32 func_002760E0(u16 value, u16 *entries); /* JP: TaLogic_IsUnitAssign */
s32 func_00276120(u16 arg0, void *arg1); /* JP: TaLogic_DoUnitAssign */
void func_002761D0(void *arg0); /* JP: TaLogic_DoSortTaskList */
s32 func_00276B60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic_GetQueueXY_Move1 */
s32 func_00276C80(u16 *arg0, s32 arg1); /* JP: TaLogic_GetActionUnitFromOwnerID */
void func_00276EC0(u16 *arg0, s32 arg1, void *arg2); /* JP: TaLogic_GetMinimumTask_DoNone */
s32 func_00276F10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9); /* JP: TaLogic_GetNearCard2 */
void func_002770E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12); /* JP: TaLogic_GetNearUnitL2 */
s32 func_002774F0(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u16 arg7); /* JP: TaLogic_GetFollowNearUnit */
u8 *func_002777F0(u8 *node, s32 parent, s32 card, s32 x, s32 y, s32 owner, u8 limit, s32 flags, u16 value, u8 depth, u16 *pool, u16 *poolCount, void *visited, u16 *visitCount, s32 context); /* JP: TaLogic_GetNearUnitPickUpTree */
s32 func_00277C60(void *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_IsAdjustUnitLst */
s32 func_00277CD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4, u8 range, s32 arg6, u8 arg7, u8 arg8, s32 arg9, s32 fallback, u16 count, u8 arg12); /* JP: TaLogic_GetTrapNearCard */
s32 func_00278150(s32 arg0, s32 arg1); /* JP: TaLogic_IsStatusMatch */
s32 func_002781B0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_IsJudgeUnitDanger */
s32 func_002781F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaLogic_IsUnitWin */
s32 func_00278250(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaLogic_IsUnitWin2 */
s32 func_00278420(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaLogic_IsUnitWin3 */
void func_00278510(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic_IsUnitWin4 */
s32 func_002785D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic_IsUnitWin5 */
u16 func_002787F0(void *arg0, void *arg1); /* JP: TaLogic_GetActOfs */
void func_00278890(s32 arg0, s32 arg1); /* JP: TaLogic_GetUnitNum */
void *func_002788D0(u16 *arg0, u16 *arg1); /* JP: TaLogic_TreeAloc */
void func_00278930(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaLogic_InitTree */
s32 func_002789F0(s32 arg0, s32 arg1); /* JP: TaLogic_GetHandFusion */
void *func_00278C80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 *arg5, u16 *arg6); /* JP: TaLogic_GetFusionTree2 */
void func_00278D20(u8 *arg0, u8 arg1); /* JP: TaLogic_AddEmptyCombo */
s32 func_00278D90(u8 *arg0); /* JP: TaLogic_GetArrayLength */
void func_00278DD0(u8 *src, u8 *dst); /* JP: TaLogic_CopyArray */
s32 func_00278E00(u8 value, u8 *values); /* JP: TaLogic_IsUseHandInCombo */
u16 *func_00278E40(u16 *arg0); /* JP: TaLogic_GetFusionRes */
s32 func_00278F10(s32 arg0, u16 *arg1, void **arg2, s32 arg3); /* JP: TaLogic_GetEnchantQue */
s32 func_00279130(s32 arg0, u16 *arg1); /* JP: TaLogic_GetEnchantQue2 */
s32 func_00279170(void *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_IsKeepEnchant */
void func_00279230(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8); /* JP: TaLogic_GetRoot */
s32 func_002792C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 arg6, u8 arg7); /* JP: TaLogic_GetRoot2 */
u8 *func_002794E0(u8 *node, s32 parent, s32 card, s32 x, s32 y, s32 targetX, s32 targetY, u8 limit, s8 *found, s32 mode, u8 depth, u16 *pool, u16 *poolEnd, s32 arg13); /* JP: TaLogic_GetRootTree2 */
void func_00279850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: TaLogic_IsPassRoot */
s32 func_002798C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5); /* JP: TaLogic_IsPassRoot2 */
void func_00279C40(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7); /* JP: TaLogic_IsRunPassRoot */
s32 func_00279CC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6); /* JP: TaLogic_IsRunPassRoot2 */
void func_0027A090(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9, u16 arg10); /* JP: TaLogic_GetInvadeRoot */
s32 func_0027A130(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8, u16 arg9); /* JP: TaLogic_GetInvadeRoot2 */
u8 *func_0027A360(u8 *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, u8 *arg_sp0, s32 *arg_sp8, s32 arg_sp10, u16 arg_sp18, u8 arg_sp20, u16 *arg_sp28, u16 *arg_sp30, s32 arg_sp38); /* JP: TaLogic_GetInvadeRootTree2 */
s32 func_0027A710(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 *arg5, s32 arg6, u8 arg7, u16 arg8); /* JP: TaLogic_IsPassInvadeRoot2 */
s32 func_0027ABD0(void *arg0, u8 arg1, u8 arg2); /* JP: TaLogic_IsConnectRoot */
void func_0027AC70(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaLogic_GetShortRoot */
void func_0027ACB0(s32 first, s32 *count, u8 *bestDepth, s32 node, s32 x, s32 y, s32 closest, u8 depth); /* JP: TaLogic_DoGetShortRoot */
u8 func_0027AF20(void *arg0, u8 depth); /* JP: TaLogic_GetNextPiece */
void func_0027AF80(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaLogic_SetRootTreeDat */
s32 func_0027AFC0(u8 *arg0); /* JP: TaLogic_GetMinGoalCount */
s32 func_0027B010(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5); /* JP: TaLogic_IsRootPast2 */
u8 *func_0027B150(u16 *arg0, u16 *arg1); /* JP: TaLogic_RootTreeAloc */
void func_0027B1B0(void *arg0, u8 arg1); /* JP: TaLogic_InitRogicControl */
void func_0027B200(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8); /* JP: TaLogic_IsRootOpen */
s32 func_0027B290(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7); /* JP: TaLogic_IsRootOpen2 */
s32 func_0027B360(s32 arg0, u16 *arg1, u16 *arg2); /* JP: TaLogic_GetAtkUnitNow */
s32 func_0027B520(void *arg0, u8 arg1); /* JP: TaLogic_IsAtkNowToGoal */
s32 func_0027B740(void *arg0, s32 arg1); /* JP: TaLogic_GetMaxApUnit2 */
s32 func_0027B860(u16 *arg0, s32 arg1); /* JP: TaLogic_GetMaxApUnit3 */
s32 func_0027B9B0(s32 arg0); /* JP: TaLogic_IsUnitReadyMove */
s32 func_0027BBC0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_IsAttackedNow */
s32 func_0027BE10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: TaLogic_IsAttackedNow2 */
void func_0027C070(s32 arg0, u16 *arg1, s32 arg2, u8 arg3); /* JP: TaLogic_GetUnitCtlLst */
void func_0027C2C0(s32 arg0, u16 *arg1, s32 arg2, s32 arg3, u8 arg4); /* JP: TaLogic_GetUnitCtlLst2 */
s32 func_0027C5A0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_IsUnitCategory */
s32 func_0027C670(u16 *values); /* JP: TaLogic_GetUnitCtlLstLen */
s32 func_0027C6D0(s32 arg0); /* JP: TaLogic_IsPickUp */
s32 func_0027D020(void *arg0, s32 arg1, void *arg2, u8 arg3, s32 arg4, s32 cost, s32 arg6, u8 arg7); /* JP: TaLogic_GetMinimumTask_EncMission */
s32 func_0027D720(u16 *arg0, s32 arg1); /* JP: TaLogic_CommandGunnerUnit */
s32 func_0027DA40(s32 arg0, s32 arg1); /* JP: TaLogic_GetMaxAPGraveCard */
s32 func_0027DBC0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetGraveEntryAfterScreen */
s32 func_0027DD20(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_GetGraveCardCount */
s32 func_0027DE20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u16 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15); /* JP: TaLogic_GetNearUnit */
s32 func_0027E150(s32 arg0); /* JP: TaLogic_RemoveHideUnit */
void func_0027E210(void *arg0, s32 arg1, s32 arg2, s32 arg3); /* JP: TaLogic_CommandStdLDUnit */
s32 func_0027E360(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4); /* JP: TaLogic_IsDefStyleUnit */
s32 func_0027E5B0(s32 arg0, s32 arg1, s32 arg2); /* JP: TaLogic_IsSafeTrap */
void func_0027E770(void); /* JP: TaLogic_InitIgnoreLst */
void func_0027E780(void *arg0, s32 arg1, s32 arg2); /* JP: TaLogic_SetTaskAtkOrMove */
s32 func_0027E840(void *arg0, void *arg1, s32 arg2); /* JP: Ta_Eff_114 */
s32 func_0027EB00(void *arg0, void *arg1, s32 arg2); /* JP: TaLib_c615 */
void func_0027F0D0(void *arg0); /* JP: Ta_LkInitCoordinate */
void func_0027F110(u8 *arg0); /* JP: Ta_LkSetCoordinate */
s32 func_0027F160(s32 arg0, s32 arg1); /* JP: Ta_LkCheckFlag */
s32 func_0027F180(void *arg0, s32 arg1, f32 *arg2); /* JP: Ta_LkPrim_DrawCard */
void func_0027F290(void *arg0, void *arg1, s32 arg2); /* JP: Ta_LkOBJ_TransitVector */
void func_0027F360(void *arg0, void *arg1); /* JP: Ta_LkAddVector */
void func_0027F3A0(void *arg0, void *arg1); /* JP: Ta_LkSubVector */
void func_0027F3E0(u8 arg0, s32 arg1); /* JP: TaTuto_InitTutorial */
void func_0027F480(s32 arg0); /* JP: TaTuto_InitTutoData */
void func_0027F5A0(void); /* JP: TaTuto_Init032 */
s32 func_0027F830(s32 arg0); /* JP: TaTuto_IsTuto */
void func_0027FFC0(s32 arg0); /* JP: TaView_ReqHalfFarView */
s32 func_00280060(void *arg0, s32 arg1); /* JP: ShSlot_Flear */
void func_00280670(void); /* JP: ShSlot_Start */
void func_00280920(void); /* JP: ShSlot_HitCardRequest */
void func_00280CB0(s32 arg0); /* JP: ShSlot_CheckLine */
s32 func_002817C0(void); /* JP: ShSlot_IsFlashStop */
void func_002825F0(void); /* JP: ShSlot_DrawEye */
void func_002831A0(void); /* JP: ShSlot_FlashBox */
void func_00283880(s32 arg0); /* JP: ShSlot_DrawReel */
s32 func_00284D30(s32 arg0); /* JP: ShSlot_Draw_Pipe */
void func_00285880(s32 arg0); /* JP: ShSlot_Init */
void func_00285EE0(void); /* JP: ShSlot_Draw */
void func_00285F20(void); /* JP: ShSlot_Act */
void func_00286900(void); /* JP: ShSlot_Term */
void func_00286910(void *arg0, void *arg1); /* JP: __initialize_cpp_rts */

#endif
