#include "__cf_AD_Vect_low_izm_dif_modes_subsyst.h"
#ifndef RTW_HEADER_AD_Vect_low_izm_dif_modes_subsyst_acc_h_
#define RTW_HEADER_AD_Vect_low_izm_dif_modes_subsyst_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef AD_Vect_low_izm_dif_modes_subsyst_acc_COMMON_INCLUDES_
#define AD_Vect_low_izm_dif_modes_subsyst_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "AD_Vect_low_izm_dif_modes_subsyst_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_18_0_0 [ 4 ] ; real_T B_18_2_0 [ 16 ] ; real_T
B_18_3_0 [ 4 ] ; real_T B_18_4_0 ; real_T B_18_5_0 ; real_T B_18_9_0 [ 4 ] ;
real_T B_18_13_0 [ 2 ] ; real_T B_18_14_0 [ 2 ] ; real_T B_18_15_0 [ 4 ] ;
real_T B_18_16_0 [ 3 ] ; real_T B_18_17_0 [ 5 ] ; real_T B_18_18_0 [ 2 ] ;
real_T B_18_19_0 [ 2 ] ; real_T B_18_20_0 ; real_T B_18_21_0 ; real_T
B_18_22_0 [ 3 ] ; real_T B_18_23_0 ; real_T B_18_25_0 ; real_T B_18_27_0 ;
real_T B_18_28_0 [ 4 ] ; real_T B_18_32_0 [ 2 ] ; real_T B_18_33_0 ; real_T
B_18_34_0 [ 2 ] ; real_T B_18_35_0 ; real_T B_18_36_0 [ 19 ] ; real_T
B_18_37_0 ; real_T B_18_40_0 ; real_T B_18_41_0 ; real_T B_18_42_0 ; real_T
B_18_46_0 [ 3 ] ; real_T B_18_47_0 ; real_T B_18_48_0 ; real_T B_18_49_0 ;
real_T B_18_50_0 ; real_T B_18_51_0 ; real_T B_18_52_0 ; real_T B_18_53_0 ;
real_T B_18_54_0 ; real_T B_18_55_0 ; real_T B_18_56_0 ; real_T B_18_57_0 ;
real_T B_18_58_0 ; real_T B_18_59_0 ; real_T B_18_60_0 ; real_T B_18_61_0 ;
real_T B_18_62_0 ; real_T B_18_63_0 ; real_T B_18_64_0 ; real_T B_18_65_0 ;
real_T B_18_66_0 ; real_T B_18_67_0 ; real_T B_18_68_0 ; real_T B_18_69_0 ;
real_T B_18_70_0 ; real_T B_18_71_0 ; real_T B_18_72_0 ; real_T B_18_73_0 ;
real_T B_18_75_0 ; real_T B_18_78_0 ; real_T B_18_80_0 ; real_T B_18_82_0 ;
real_T B_18_83_0 ; real_T B_18_84_0 ; real_T B_18_86_0 ; real_T B_18_88_0 ;
real_T B_18_90_0 ; real_T B_18_91_0 ; real_T B_18_94_0 ; real_T B_18_96_0 ;
real_T B_18_98_0 ; real_T B_18_99_0 ; real_T B_18_111_0 [ 16 ] ; real_T
B_18_112_0 [ 16 ] ; real_T B_18_113_0 [ 16 ] ; real_T B_18_114_0 [ 4 ] ;
real_T B_18_115_0 [ 4 ] ; real_T B_18_116_0 [ 4 ] ; real_T B_18_117_0 ;
real_T B_18_120_0 ; real_T B_18_121_0 ; real_T B_18_122_0 ; real_T B_18_123_0
; real_T B_18_124_0 ; real_T B_18_125_0 ; real_T B_18_131_0 [ 3 ] ; real_T
B_18_134_0 ; real_T B_18_138_0 [ 3 ] ; real_T B_18_144_0 ; real_T B_18_150_0
; real_T B_18_156_0 ; real_T B_18_162_0 ; real_T B_18_168_0 ; real_T
B_18_174_0 ; real_T B_18_180_0 ; real_T B_18_186_0 ; real_T B_18_187_0 ;
real_T B_18_188_0 ; real_T B_18_189_0 ; real_T B_18_190_0 ; real_T B_18_191_0
; real_T B_18_0_0_m ; real_T B_18_1_0 ; real_T B_18_2_0_c ; real_T B_18_3_0_k
[ 16 ] ; real_T B_18_4_0_c ; real_T B_18_5_0_b [ 16 ] ; real_T B_18_6_0 ;
real_T B_18_7_0 ; real_T B_18_12_0 ; real_T B_18_13_0_p ; real_T B_18_14_0_c
[ 2 ] ; real_T B_18_18_0_f ; real_T B_18_19_0_g ; real_T B_18_22_0_g ; real_T
B_18_24_0 ; real_T B_18_28_0_m ; real_T B_18_29_0 ; real_T B_18_30_0 ; real_T
B_18_31_0 ; real_T B_18_33_0_n ; real_T B_17_0_0 ; real_T B_17_1_0 ; real_T
B_16_0_0 [ 2 ] ; real_T B_16_1_1 [ 3 ] ; real_T B_16_1_2 [ 3 ] ; real_T
B_15_0_1 ; real_T B_11_1_0 ; real_T B_10_0_0 ; real_T B_10_2_0 [ 4 ] ; real_T
B_10_4_0 [ 16 ] ; real_T B_10_0_0_p [ 2 ] ; real_T B_10_1_0 [ 16 ] ; real_T
B_9_0_0 ; real_T B_9_2_0 [ 4 ] ; real_T B_9_4_0 [ 16 ] ; real_T B_9_0_0_l [ 2
] ; real_T B_9_1_0 [ 16 ] ; real_T B_8_1_0 ; real_T B_8_2_0 ; real_T B_8_3_0
; real_T B_8_4_0 ; real_T B_8_5_0 ; real_T B_8_5_1 ; real_T B_8_6_0 ; real_T
B_8_6_1 ; real_T B_8_8_0 [ 16 ] ; real_T B_8_0_0 [ 16 ] ; real_T B_8_1_0_j ;
real_T B_7_0_0 ; real_T B_7_1_0 ; real_T B_7_2_0 ; real_T B_7_3_0 ; real_T
B_6_0_0 ; real_T B_6_1_0 ; real_T B_6_2_0 ; real_T B_6_3_0 ; real_T B_5_0_0 ;
real_T B_5_1_0 ; real_T B_5_2_0 ; real_T B_5_3_0 ; real_T B_4_0_0 ; real_T
B_4_1_0 ; real_T B_4_2_0 ; real_T B_4_3_0 ; real_T B_3_0_0 ; real_T B_3_1_0 ;
real_T B_3_2_0 ; real_T B_3_3_0 ; real_T B_2_0_0 ; real_T B_2_1_0 ; real_T
B_2_2_0 ; real_T B_2_3_0 ; real_T B_1_0_0 ; real_T B_1_1_0 [ 3 ] ; real_T
B_1_3_0 ; real_T B_1_5_0 [ 2 ] ; real_T B_1_6_0 [ 2 ] ; real_T B_1_7_0 ;
real_T B_1_8_0 [ 2 ] ; real_T B_1_9_0 ; real_T B_1_13_0 ; real_T B_1_16_0 [
16 ] ; real_T B_1_17_0 [ 16 ] ; real_T B_1_18_0 [ 16 ] ; real_T B_1_19_0 ;
real_T B_1_20_0 ; real_T B_1_0_0_d ; real_T B_1_1_0_g [ 2 ] ; real_T B_1_2_0
[ 16 ] ; real_T B_1_3_0_l [ 16 ] ; real_T B_1_4_0 [ 2 ] ; real_T B_1_5_0_d [
16 ] ; real_T B_0_0_0 ; boolean_T B_18_148_0 ; boolean_T B_18_149_0 ;
boolean_T B_18_160_0 ; boolean_T B_18_161_0 ; boolean_T B_18_172_0 ;
boolean_T B_18_173_0 ; boolean_T B_18_184_0 ; boolean_T B_18_185_0 ;
boolean_T B_18_9_0_d ; boolean_T B_18_10_0 ; boolean_T B_18_11_0 ; boolean_T
B_18_15_0_l ; boolean_T B_18_16_0_o ; boolean_T B_18_17_0_b ; boolean_T
B_18_20_0_n ; boolean_T B_18_21_0_b ; boolean_T B_18_23_0_l ; char_T
pad_B_18_23_0_l [ 7 ] ; } B_AD_Vect_low_izm_dif_modes_subsyst_T ; typedef
struct { real_T Memory_PreviousInput ; real_T Memory_PreviousInput_p ; real_T
Memory_PreviousInput_a ; real_T inversion_DWORK1 [ 16 ] ; real_T
inversion_DWORK3 [ 16 ] ; real_T inversion_DWORK4 [ 16 ] ; struct { real_T
modelTStart ; } TransportDelay_RWORK ; real_T StateSpace_RWORK [ 2 ] ; struct
{ real_T modelTStart ; } TransportDelay_RWORK_g ; struct { real_T modelTStart
; } TransportDelay_RWORK_e ; struct { real_T modelTStart ; }
TransportDelay_RWORK_gs ; struct { void * TUbufferPtrs [ 6 ] ; }
TransportDelay_PWORK ; void * StateSpace_PWORK [ 22 ] ; void * Scope_PWORK ;
struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_h ; struct { void
* TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_l ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_h5 ; void * Scope1_PWORK [ 8 ] ;
struct { void * AQHandles ; void * SlioLTF ; }
TAQSigLogging_InsertedFor_From2_at_outport_0_PWORK ; void * ToWorkspace_PWORK
; int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
MATLABFunction1_sysIdxToRun ; int32_T MATLABFunction2_sysIdxToRun ; int32_T
StoreData_sysIdxToRun ; int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_h
; int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_o ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun ; int32_T
sinthrcosthr1_sysIdxToRun ; int32_T sinthrcosthr_sysIdxToRun ; int32_T
sinbetacosbetasinthcosth_sysIdxToRun ; int32_T
Synchronousreferenceframe_sysIdxToRun ; int32_T
Stationaryreferenceframe_sysIdxToRun ; int32_T
Rotorreferenceframe_sysIdxToRun ; int32_T
Synchronousreferenceframe_sysIdxToRun_k ; int32_T
Stationaryreferenceframe_sysIdxToRun_b ; int32_T
Rotorreferenceframe_sysIdxToRun_i ; int32_T Saturation_sysIdxToRun ; int32_T
inversion_DWORK2 [ 4 ] ; int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_j
; uint32_T m_bpIndex ; struct { int_T Tail [ 3 ] ; int_T Head [ 3 ] ; int_T
Last [ 3 ] ; int_T CircularBufSize [ 3 ] ; int_T MaxNewBufSize ; }
TransportDelay_IWORK ; int_T StateSpace_IWORK [ 23 ] ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_l ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_h ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_f ; int8_T StoreData_SubsysRanBC ;
int8_T sinthrcosthr1_SubsysRanBC ; int8_T sinthrcosthr_SubsysRanBC ; int8_T
sinbetacosbetasinthcosth_SubsysRanBC ; int8_T
Synchronousreferenceframe_SubsysRanBC ; int8_T
Stationaryreferenceframe_SubsysRanBC ; int8_T Rotorreferenceframe_SubsysRanBC
; int8_T Synchronousreferenceframe_SubsysRanBC_i ; int8_T
Stationaryreferenceframe_SubsysRanBC_k ; int8_T
Rotorreferenceframe_SubsysRanBC_c ; int8_T Saturation_SubsysRanBC ; boolean_T
Memory_PreviousInput_h ; boolean_T Memory_PreviousInput_l ; boolean_T
Memory_PreviousInput_k ; boolean_T Memory_PreviousInput_c ; boolean_T
StoreData_MODE ; boolean_T sinthrcosthr1_MODE ; boolean_T sinthrcosthr_MODE ;
boolean_T sinbetacosbetasinthcosth_MODE ; boolean_T
Synchronousreferenceframe_MODE ; boolean_T Stationaryreferenceframe_MODE ;
boolean_T Rotorreferenceframe_MODE ; boolean_T
Synchronousreferenceframe_MODE_f ; boolean_T Stationaryreferenceframe_MODE_n
; boolean_T Rotorreferenceframe_MODE_c ; boolean_T Saturation_MODE ; char_T
pad_Saturation_MODE [ 6 ] ; } DW_AD_Vect_low_izm_dif_modes_subsyst_T ;
typedef struct { real_T Integrator_CSTATE [ 4 ] ; real_T
Rotoranglethetam_CSTATE ; real_T Rotorspeedwm_CSTATE ; real_T
Integrator_CSTATE_k ; real_T Integrator_CSTATE_e ; real_T Integrator_CSTATE_m
; real_T Integrator_CSTATE_ex ; real_T integrator_CSTATE ; real_T
integrator_CSTATE_m ; real_T integrator_CSTATE_j ; real_T Integrator_CSTATE_b
; } X_AD_Vect_low_izm_dif_modes_subsyst_T ; typedef struct { real_T
Integrator_CSTATE [ 4 ] ; real_T Rotoranglethetam_CSTATE ; real_T
Rotorspeedwm_CSTATE ; real_T Integrator_CSTATE_k ; real_T Integrator_CSTATE_e
; real_T Integrator_CSTATE_m ; real_T Integrator_CSTATE_ex ; real_T
integrator_CSTATE ; real_T integrator_CSTATE_m ; real_T integrator_CSTATE_j ;
real_T Integrator_CSTATE_b ; } XDot_AD_Vect_low_izm_dif_modes_subsyst_T ;
typedef struct { boolean_T Integrator_CSTATE [ 4 ] ; boolean_T
Rotoranglethetam_CSTATE ; boolean_T Rotorspeedwm_CSTATE ; boolean_T
Integrator_CSTATE_k ; boolean_T Integrator_CSTATE_e ; boolean_T
Integrator_CSTATE_m ; boolean_T Integrator_CSTATE_ex ; boolean_T
integrator_CSTATE ; boolean_T integrator_CSTATE_m ; boolean_T
integrator_CSTATE_j ; boolean_T Integrator_CSTATE_b ; }
XDis_AD_Vect_low_izm_dif_modes_subsyst_T ; typedef struct { real_T
Integrator_CSTATE [ 4 ] ; real_T Rotoranglethetam_CSTATE ; real_T
Rotorspeedwm_CSTATE ; real_T Integrator_CSTATE_k ; real_T Integrator_CSTATE_e
; real_T Integrator_CSTATE_m ; real_T Integrator_CSTATE_ex ; real_T
integrator_CSTATE ; real_T integrator_CSTATE_m ; real_T integrator_CSTATE_j ;
real_T Integrator_CSTATE_b ; }
CStateAbsTol_AD_Vect_low_izm_dif_modes_subsyst_T ; typedef struct { const
real_T B_18_0_0 ; const real_T B_18_1_0 ; const real_T B_18_2_0 ; const
real_T B_18_3_0 ; } ConstB_AD_Vect_low_izm_dif_modes_subsyst_T ;
#define AD_Vect_low_izm_dif_modes_subsyst_rtC(S) ((ConstB_AD_Vect_low_izm_dif_modes_subsyst_T *) _ssGetConstBlockIO(S))
struct P_AD_Vect_low_izm_dif_modes_subsyst_T_ { real_T P_0 ; real_T P_1 ;
real_T P_2 ; real_T P_3 ; real_T P_4 [ 2 ] ; real_T P_5 [ 2 ] ; real_T P_6 ;
real_T P_7 ; real_T P_8 [ 2 ] ; real_T P_9 [ 16 ] ; real_T P_10 [ 16 ] ;
real_T P_11 [ 2 ] ; real_T P_12 [ 16 ] ; real_T P_13 ; real_T P_14 ; real_T
P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T P_20 ;
real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ; real_T P_25 ; real_T
P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 [ 16 ] ; real_T P_30 ; real_T
P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 [ 2 ] ; real_T P_35 [ 16 ] ;
real_T P_36 ; real_T P_37 ; real_T P_38 ; real_T P_39 [ 2 ] ; real_T P_40 [
16 ] ; real_T P_41 ; real_T P_42 ; real_T P_43 ; real_T P_44 ; real_T P_45 ;
real_T P_46 ; real_T P_47 ; real_T P_48 [ 4 ] ; real_T P_49 ; real_T P_50 ;
real_T P_51 ; real_T P_52 ; real_T P_53 ; real_T P_54 ; real_T P_55 [ 2 ] ;
real_T P_56 [ 50 ] ; real_T P_57 [ 2 ] ; real_T P_58 [ 4 ] ; real_T P_59 [ 2
] ; real_T P_61 [ 2 ] ; real_T P_62 [ 550 ] ; real_T P_63 [ 2 ] ; real_T P_64
; real_T P_65 [ 3 ] ; real_T P_66 ; real_T P_67 ; real_T P_68 ; real_T P_69 ;
real_T P_70 [ 19 ] ; real_T P_71 ; real_T P_72 [ 3 ] ; real_T P_73 ; real_T
P_74 ; real_T P_75 ; real_T P_76 ; real_T P_77 ; real_T P_78 ; real_T P_79 ;
real_T P_80 ; real_T P_81 ; real_T P_82 ; real_T P_83 ; real_T P_84 ; real_T
P_85 ; real_T P_86 ; real_T P_87 ; real_T P_88 ; real_T P_89 ; real_T P_90 ;
real_T P_91 ; real_T P_92 ; real_T P_93 ; real_T P_94 ; real_T P_95 ; real_T
P_96 ; real_T P_97 ; real_T P_98 ; real_T P_99 ; real_T P_100 ; real_T P_101
; real_T P_102 ; real_T P_103 ; real_T P_104 ; real_T P_105 ; real_T P_106 ;
real_T P_107 ; real_T P_108 ; real_T P_109 ; real_T P_110 ; real_T P_111 ;
real_T P_112 ; real_T P_113 [ 3 ] ; real_T P_114 ; real_T P_115 ; real_T
P_116 ; real_T P_117 ; real_T P_118 ; real_T P_119 ; real_T P_120 ; real_T
P_121 ; real_T P_122 ; real_T P_123 ; real_T P_124 ; real_T P_125 ; real_T
P_126 ; real_T P_127 ; real_T P_128 ; real_T P_129 ; real_T P_130 ; real_T
P_131 ; real_T P_132 ; real_T P_133 ; real_T P_134 [ 16 ] ; real_T P_135 ;
real_T P_136 [ 16 ] ; real_T P_137 ; real_T P_138 ; real_T P_139 ; real_T
P_140 ; real_T P_141 [ 2 ] ; real_T P_142 ; real_T P_143 ; real_T P_144 ;
real_T P_145 ; real_T P_146 ; real_T P_147 ; real_T P_148 ; real_T P_149 ;
real_T P_150 ; boolean_T P_151 ; boolean_T P_152 ; boolean_T P_153 ;
boolean_T P_154 ; boolean_T P_155 ; boolean_T P_156 ; boolean_T P_157 ;
boolean_T P_158 ; boolean_T P_159 ; boolean_T P_160 ; boolean_T P_161 ;
boolean_T P_162 ; boolean_T P_163 ; char_T pad_P_163 [ 3 ] ; } ; extern
P_AD_Vect_low_izm_dif_modes_subsyst_T
AD_Vect_low_izm_dif_modes_subsyst_rtDefaultP ; extern const
ConstB_AD_Vect_low_izm_dif_modes_subsyst_T
AD_Vect_low_izm_dif_modes_subsyst_rtInvariant ;
#endif
