#include "__cf_AD_Vect_low_izm_dif_modes_subsyst.h"
#include <math.h>
#include "AD_Vect_low_izm_dif_modes_subsyst_acc.h"
#include "AD_Vect_low_izm_dif_modes_subsyst_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayUpdateTailOrGrowBuf
( int_T * bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr ,
real_T tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * *
xBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay , int_T *
maxNewBufSzPtr ) { int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = *
bufSzPtr ; real_T * tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T
numBuffer = 2 ; if ( istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ;
} testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay
<= tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T *
tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T
newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr ) { *
maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer *
newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false )
; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
tBufPtr = tempT ; * uBufPtr = tempU ; if ( istransportdelay ) * xBufPtr =
tempX ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayInterpolate ( real_T
tMinusDelay , real_T tStart , real_T * tBuf , real_T * uBuf , int_T bufSz ,
int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput ,
boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ;
real_T yout , t1 , t2 , u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } real_T look1_pbinlxpw ( real_T
u0 , const real_T bp0 [ ] , const real_T table [ ] , uint32_T prevIndex [ ] ,
uint32_T maxIndex ) { real_T frac ; uint32_T iRght ; uint32_T iLeft ;
uint32_T bpIdx ; uint32_T found ; if ( u0 <= bp0 [ 0U ] ) { bpIdx = 0U ; frac
= ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ] - bp0 [ 0U ] ) ; } else if ( u0 < bp0 [
maxIndex ] ) { bpIdx = prevIndex [ 0U ] ; iLeft = 0U ; iRght = maxIndex ;
found = 0U ; while ( found == 0U ) { if ( u0 < bp0 [ bpIdx ] ) { iRght =
bpIdx - 1U ; bpIdx = ( iRght + iLeft ) >> 1U ; } else if ( u0 < bp0 [ bpIdx +
1U ] ) { found = 1U ; } else { iLeft = bpIdx + 1U ; bpIdx = ( iRght + iLeft )
>> 1U ; } } frac = ( u0 - bp0 [ bpIdx ] ) / ( bp0 [ bpIdx + 1U ] - bp0 [
bpIdx ] ) ; } else { bpIdx = maxIndex - 1U ; frac = ( u0 - bp0 [ maxIndex -
1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex - 1U ] ) ; } prevIndex [ 0U ] =
bpIdx ; return ( table [ bpIdx + 1U ] - table [ bpIdx ] ) * frac + table [
bpIdx ] ; } void rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T
blkIdx , char_T * * path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ;
} void rt_ssSet_slErrMsg ( SimStruct * S , void * diag ) { if ( !
_ssIsErrorStatusAslErrMsg ( S ) ) { _ssSet_slErrMsg ( S , diag ) ; } else {
_ssDiscardDiagnostic ( S , diag ) ; } } void rt_ssReportDiagnosticAsWarning (
SimStruct * S , void * diag ) { _ssReportDiagnosticAsWarning ( S , diag ) ; }
void rt_invd4x4_snf ( const real_T u [ 16 ] , real_T y [ 16 ] ) { int8_T p [
4 ] ; real_T A [ 16 ] ; int8_T ipiv [ 4 ] ; int32_T pipk ; int32_T jj ;
int32_T jp1j ; int32_T jBcol ; int32_T idxmax ; int32_T ix ; real_T smax ;
real_T s ; int32_T iy ; int32_T jA ; int32_T ijA ; for ( iy = 0 ; iy < 16 ;
iy ++ ) { y [ iy ] = 0.0 ; A [ iy ] = u [ iy ] ; } ipiv [ 0 ] = 1 ; ipiv [ 1
] = 2 ; ipiv [ 2 ] = 3 ; for ( pipk = 0 ; pipk < 3 ; pipk ++ ) { jBcol = pipk
* 5 + 1 ; jj = pipk * 5 ; jp1j = jBcol + 1 ; iy = 4 - pipk ; idxmax = 1 ; ix
= jBcol ; smax = muDoubleScalarAbs ( A [ jj ] ) ; for ( jA = 2 ; jA <= iy ;
jA ++ ) { ix ++ ; s = muDoubleScalarAbs ( A [ ix - 1 ] ) ; if ( s > smax ) {
idxmax = jA ; smax = s ; } } if ( A [ ( jBcol + idxmax ) - 2 ] != 0.0 ) { if
( idxmax - 1 != 0 ) { ipiv [ pipk ] = ( int8_T ) ( pipk + idxmax ) ; ix =
pipk + 1 ; iy = pipk + idxmax ; smax = A [ ix - 1 ] ; A [ ix - 1 ] = A [ iy -
1 ] ; A [ iy - 1 ] = smax ; ix += 4 ; iy += 4 ; smax = A [ ix - 1 ] ; A [ ix
- 1 ] = A [ iy - 1 ] ; A [ iy - 1 ] = smax ; ix += 4 ; iy += 4 ; smax = A [
ix - 1 ] ; A [ ix - 1 ] = A [ iy - 1 ] ; A [ iy - 1 ] = smax ; ix += 4 ; iy
+= 4 ; smax = A [ ix - 1 ] ; A [ ix - 1 ] = A [ iy - 1 ] ; A [ iy - 1 ] =
smax ; } iy = jp1j - pipk ; for ( ix = jp1j ; ix <= iy + 2 ; ix ++ ) { A [ ix
- 1 ] /= A [ jj ] ; } } jBcol = 2 - pipk ; jA = jj ; jj += 4 ; for ( idxmax =
0 ; idxmax <= jBcol ; idxmax ++ ) { if ( A [ jj ] != 0.0 ) { smax = - A [ jj
] ; ix = jp1j ; iy = jA - pipk ; for ( ijA = jA + 6 ; ijA <= iy + 8 ; ijA ++
) { A [ ijA - 1 ] += A [ ix - 1 ] * smax ; ix ++ ; } } jj += 4 ; jA += 4 ; }
} p [ 0 ] = 1 ; p [ 1 ] = 2 ; p [ 2 ] = 3 ; p [ 3 ] = 4 ; if ( ipiv [ 0 ] > 1
) { pipk = p [ ipiv [ 0 ] - 1 ] ; p [ ipiv [ 0 ] - 1 ] = 1 ; p [ 0 ] = (
int8_T ) pipk ; } if ( ipiv [ 1 ] > 2 ) { pipk = p [ ipiv [ 1 ] - 1 ] ; p [
ipiv [ 1 ] - 1 ] = p [ 1 ] ; p [ 1 ] = ( int8_T ) pipk ; } if ( ipiv [ 2 ] >
3 ) { pipk = p [ 3 ] ; p [ 3 ] = p [ 2 ] ; p [ 2 ] = ( int8_T ) pipk ; }
jBcol = p [ 0 ] ; y [ ( p [ 0 ] - 1 ) << 2 ] = 1.0 ; for ( pipk = 1 ; pipk <
5 ; pipk ++ ) { if ( y [ ( ( ( jBcol - 1 ) << 2 ) + pipk ) - 1 ] != 0.0 ) {
for ( ix = pipk + 1 ; ix < 5 ; ix ++ ) { y [ ( ix + ( ( jBcol - 1 ) << 2 ) )
- 1 ] -= y [ ( ( ( jBcol - 1 ) << 2 ) + pipk ) - 1 ] * A [ ( ( ( pipk - 1 )
<< 2 ) + ix ) - 1 ] ; } } } jBcol = p [ 1 ] ; y [ 1 + ( ( p [ 1 ] - 1 ) << 2
) ] = 1.0 ; for ( pipk = 2 ; pipk < 5 ; pipk ++ ) { if ( y [ ( ( ( jBcol - 1
) << 2 ) + pipk ) - 1 ] != 0.0 ) { for ( ix = pipk + 1 ; ix < 5 ; ix ++ ) { y
[ ( ix + ( ( jBcol - 1 ) << 2 ) ) - 1 ] -= y [ ( ( ( jBcol - 1 ) << 2 ) +
pipk ) - 1 ] * A [ ( ( ( pipk - 1 ) << 2 ) + ix ) - 1 ] ; } } } jBcol = p [ 2
] ; y [ 2 + ( ( p [ 2 ] - 1 ) << 2 ) ] = 1.0 ; for ( pipk = 3 ; pipk < 5 ;
pipk ++ ) { if ( y [ ( ( ( jBcol - 1 ) << 2 ) + pipk ) - 1 ] != 0.0 ) { for (
ix = pipk + 1 ; ix < 5 ; ix ++ ) { y [ ( ( jBcol - 1 ) << 2 ) + 3 ] -= y [ (
( ( jBcol - 1 ) << 2 ) + pipk ) - 1 ] * A [ ( ( pipk - 1 ) << 2 ) + 3 ] ; } }
} y [ 3 + ( ( p [ 3 ] - 1 ) << 2 ) ] = 1.0 ; for ( pipk = 0 ; pipk < 4 ; pipk
++ ) { jBcol = pipk << 2 ; if ( y [ jBcol + 3 ] != 0.0 ) { y [ jBcol + 3 ] /=
A [ 15 ] ; for ( ix = 0 ; ix < 3 ; ix ++ ) { jp1j = ix + 1 ; y [ ( jp1j +
jBcol ) - 1 ] -= y [ jBcol + 3 ] * A [ jp1j + 11 ] ; } } if ( y [ jBcol + 2 ]
!= 0.0 ) { y [ jBcol + 2 ] /= A [ 10 ] ; for ( ix = 0 ; ix < 2 ; ix ++ ) {
jp1j = ix + 1 ; y [ ( jp1j + jBcol ) - 1 ] -= y [ jBcol + 2 ] * A [ jp1j + 7
] ; } } if ( y [ jBcol + 1 ] != 0.0 ) { y [ jBcol + 1 ] /= A [ 5 ] ; for ( ix
= 0 ; ix < 1 ; ix ++ ) { y [ jBcol ] -= y [ jBcol + 1 ] * A [ 4 ] ; } } if (
y [ jBcol ] != 0.0 ) { y [ jBcol ] /= A [ 0 ] ; } } } static void mdlOutputs
( SimStruct * S , int_T tid ) { real_T B_18_76_0 ; real_T B_18_92_0 ;
boolean_T rtb_B_18_79_0 ; real_T rtb_B_1_4_0 ; real_T rtb_B_1_11_0 ; real_T
rtb_B_1_15_0 [ 16 ] ; int32_T i ; int32_T i_0 ; real_T tmp ; real_T tmp_0 ;
B_AD_Vect_low_izm_dif_modes_subsyst_T * _rtB ;
P_AD_Vect_low_izm_dif_modes_subsyst_T * _rtP ;
X_AD_Vect_low_izm_dif_modes_subsyst_T * _rtX ;
DW_AD_Vect_low_izm_dif_modes_subsyst_T * _rtDW ; _rtDW = ( (
DW_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetRootDWork ( S ) ) ; _rtX = (
( X_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetContStates ( S ) ) ; _rtP =
( ( P_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetModelRtp ( S ) ) ; _rtB =
( ( B_AD_Vect_low_izm_dif_modes_subsyst_T * ) _ssGetModelBlockIO ( S ) ) ;
_rtB -> B_18_0_0 [ 0 ] = _rtX -> Integrator_CSTATE [ 0 ] ; _rtB -> B_18_0_0 [
1 ] = _rtX -> Integrator_CSTATE [ 1 ] ; _rtB -> B_18_0_0 [ 2 ] = _rtX ->
Integrator_CSTATE [ 2 ] ; _rtB -> B_18_0_0 [ 3 ] = _rtX -> Integrator_CSTATE
[ 3 ] ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( i != 0 ) && (
ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB -> B_18_1_0 > 0.0 ) { if ( !
_rtDW -> Saturation_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S
) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } ( (
XDis_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetContStateDisabled ( S ) )
-> Integrator_CSTATE_b = 0 ; _rtDW -> Saturation_MODE = true ; } } else { if
( _rtDW -> Saturation_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S
) ; ( ( XDis_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetContStateDisabled (
S ) ) -> Integrator_CSTATE_b = 1 ; _rtDW -> Saturation_MODE = false ; } } }
if ( _rtDW -> Saturation_MODE ) { _rtB -> B_1_0_0 = _rtX ->
Integrator_CSTATE_b ; _rtB -> B_1_1_0 [ 0 ] = _rtB -> B_1_1_0_g [ 0 ] ; _rtB
-> B_1_1_0 [ 1 ] = _rtB -> B_1_1_0_g [ 1 ] ; _rtB -> B_1_1_0 [ 2 ] = _rtB ->
B_1_0_0 ; _rtB -> B_1_3_0 = ( 1.0 / _rtB -> B_1_1_0 [ 0 ] + 1.0 / _rtB ->
B_1_1_0 [ 1 ] ) + 1.0 / _rtB -> B_1_1_0 [ 2 ] ; rtb_B_1_4_0 = 1.0 / _rtB ->
B_1_3_0 ; _rtB -> B_1_5_0 [ 0 ] = _rtB -> B_1_4_0 [ 0 ] * rtb_B_1_4_0 ; _rtB
-> B_1_5_0 [ 1 ] = _rtB -> B_1_4_0 [ 1 ] * rtb_B_1_4_0 ; _rtB -> B_1_6_0 [ 0
] = _rtB -> B_18_0_0 [ 0 ] * _rtB -> B_1_5_0 [ 0 ] ; _rtB -> B_1_6_0 [ 1 ] =
_rtB -> B_18_0_0 [ 2 ] * _rtB -> B_1_5_0 [ 1 ] ; _rtB -> B_1_7_0 = _rtB ->
B_1_6_0 [ 0 ] + _rtB -> B_1_6_0 [ 1 ] ; _rtB -> B_1_8_0 [ 0 ] = _rtB ->
B_18_0_0 [ 1 ] * _rtB -> B_1_5_0 [ 0 ] ; _rtB -> B_1_8_0 [ 1 ] = _rtB ->
B_18_0_0 [ 3 ] * _rtB -> B_1_5_0 [ 1 ] ; _rtB -> B_1_9_0 = _rtB -> B_1_8_0 [
0 ] + _rtB -> B_1_8_0 [ 1 ] ; rtb_B_1_4_0 = muDoubleScalarHypot ( _rtB ->
B_1_7_0 , _rtB -> B_1_9_0 ) ; rtb_B_1_11_0 = look1_pbinlxpw ( rtb_B_1_4_0 ,
_rtP -> P_5 , _rtP -> P_4 , & _rtDW -> m_bpIndex , 1U ) ; if ( rtb_B_1_11_0
!= 0.0 ) { _rtB -> B_0_0_0 = rtb_B_1_4_0 / rtb_B_1_11_0 ; _rtB -> B_1_13_0 =
_rtB -> B_0_0_0 ; } else { _rtB -> B_1_13_0 = _rtB -> B_1_0_0_d ; } memcpy (
& rtb_B_1_15_0 [ 0 ] , & _rtB -> B_1_2_0 [ 0 ] , sizeof ( real_T ) << 4U ) ;
rtb_B_1_15_0 [ 0 ] = _rtB -> B_1_13_0 ; rtb_B_1_15_0 [ 5 ] = _rtB -> B_1_13_0
; rtb_B_1_15_0 [ 2 ] = _rtB -> B_1_13_0 ; rtb_B_1_15_0 [ 7 ] = _rtB ->
B_1_13_0 ; rtb_B_1_15_0 [ 8 ] = _rtB -> B_1_13_0 ; rtb_B_1_15_0 [ 13 ] = _rtB
-> B_1_13_0 ; rtb_B_1_15_0 [ 10 ] = _rtB -> B_1_13_0 ; rtb_B_1_15_0 [ 15 ] =
_rtB -> B_1_13_0 ; for ( i = 0 ; i < 16 ; i ++ ) { _rtB -> B_1_16_0 [ i ] =
rtb_B_1_15_0 [ i ] + _rtB -> B_1_3_0_l [ i ] ; } rt_invd4x4_snf ( _rtB ->
B_1_16_0 , _rtB -> B_1_17_0 ) ; for ( i = 0 ; i < 4 ; i ++ ) { for ( i_0 = 0
; i_0 < 4 ; i_0 ++ ) { _rtB -> B_1_18_0 [ i_0 + ( i << 2 ) ] = 0.0 ; _rtB ->
B_1_18_0 [ i_0 + ( i << 2 ) ] += _rtB -> B_1_17_0 [ i << 2 ] * _rtB ->
B_1_5_0_d [ i_0 ] ; _rtB -> B_1_18_0 [ i_0 + ( i << 2 ) ] += _rtB -> B_1_17_0
[ ( i << 2 ) + 1 ] * _rtB -> B_1_5_0_d [ i_0 + 4 ] ; _rtB -> B_1_18_0 [ i_0 +
( i << 2 ) ] += _rtB -> B_1_17_0 [ ( i << 2 ) + 2 ] * _rtB -> B_1_5_0_d [ i_0
+ 8 ] ; _rtB -> B_1_18_0 [ i_0 + ( i << 2 ) ] += _rtB -> B_1_17_0 [ ( i << 2
) + 3 ] * _rtB -> B_1_5_0_d [ i_0 + 12 ] ; } } _rtB -> B_1_19_0 = _rtB ->
B_1_13_0 - _rtB -> B_1_0_0 ; _rtB -> B_1_20_0 = _rtP -> P_6 * _rtB ->
B_1_19_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
Saturation_SubsysRanBC ) ; } } for ( i = 0 ; i < 16 ; i ++ ) { if ( _rtB ->
B_18_2_0_c >= _rtP -> P_49 ) { _rtB -> B_18_2_0 [ i ] = _rtB -> B_1_17_0 [ i
] ; } else { _rtB -> B_18_2_0 [ i ] = _rtB -> B_18_3_0_k [ i ] ; } } for ( i
= 0 ; i < 4 ; i ++ ) { _rtB -> B_18_3_0 [ i ] = 0.0 ; _rtB -> B_18_3_0 [ i ]
+= _rtB -> B_18_2_0 [ i ] * _rtB -> B_18_0_0 [ 0 ] ; _rtB -> B_18_3_0 [ i ]
+= _rtB -> B_18_2_0 [ i + 4 ] * _rtB -> B_18_0_0 [ 1 ] ; _rtB -> B_18_3_0 [ i
] += _rtB -> B_18_2_0 [ i + 8 ] * _rtB -> B_18_0_0 [ 2 ] ; _rtB -> B_18_3_0 [
i ] += _rtB -> B_18_2_0 [ i + 12 ] * _rtB -> B_18_0_0 [ 3 ] ; } _rtB ->
B_18_4_0 = _rtX -> Rotoranglethetam_CSTATE ; _rtB -> B_18_5_0 = _rtX ->
Rotorspeedwm_CSTATE ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( i != 0 ) && (
ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB -> B_18_20_0_n ) { if ( ! _rtDW
-> sinthrcosthr_MODE ) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) )
{ ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
sinthrcosthr_MODE = true ; } } else { if ( _rtDW -> sinthrcosthr_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtB -> B_9_2_0 [ 0 ] =
_rtP -> P_31 ; _rtB -> B_9_2_0 [ 1 ] = _rtP -> P_31 ; _rtB -> B_9_2_0 [ 2 ] =
_rtP -> P_31 ; _rtB -> B_9_2_0 [ 3 ] = _rtP -> P_31 ; for ( i = 0 ; i < 16 ;
i ++ ) { _rtB -> B_9_4_0 [ i ] = _rtP -> P_32 ; } _rtDW -> sinthrcosthr_MODE
= false ; } } } if ( _rtDW -> sinthrcosthr_MODE ) { _rtB -> B_9_0_0 = _rtP ->
P_33 * _rtB -> B_18_5_0 ; muDoubleScalarSinCos ( _rtB -> B_18_4_0 , & _rtB ->
B_9_2_0 [ 0 ] , & _rtB -> B_9_2_0 [ 1 ] ) ; _rtB -> B_9_2_0 [ 2 ] = _rtB ->
B_9_0_0_l [ 0 ] ; _rtB -> B_9_2_0 [ 3 ] = _rtB -> B_9_0_0_l [ 1 ] ; memcpy (
& _rtB -> B_9_4_0 [ 0 ] , & _rtB -> B_9_1_0 [ 0 ] , sizeof ( real_T ) << 4U )
; _rtB -> B_9_4_0 [ 4 ] = _rtB -> B_18_5_0 ; _rtB -> B_9_4_0 [ 1 ] = _rtB ->
B_9_0_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
sinthrcosthr_SubsysRanBC ) ; } } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( i
!= 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB -> B_18_21_0_b ) {
if ( ! _rtDW -> sinthrcosthr1_MODE ) { if ( ssGetTaskTime ( S , 1 ) !=
ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
_rtDW -> sinthrcosthr1_MODE = true ; } } else { if ( _rtDW ->
sinthrcosthr1_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
_rtB -> B_10_2_0 [ 0 ] = _rtP -> P_36 ; _rtB -> B_10_2_0 [ 1 ] = _rtP -> P_36
; _rtB -> B_10_2_0 [ 2 ] = _rtP -> P_36 ; _rtB -> B_10_2_0 [ 3 ] = _rtP ->
P_36 ; _rtDW -> sinthrcosthr1_MODE = false ; } } } if ( _rtDW ->
sinthrcosthr1_MODE ) { _rtB -> B_10_0_0 = _rtP -> P_38 * _rtB -> B_18_5_0 ;
muDoubleScalarSinCos ( _rtB -> B_18_4_0 , & _rtB -> B_10_2_0 [ 0 ] , & _rtB
-> B_10_2_0 [ 1 ] ) ; _rtB -> B_10_2_0 [ 2 ] = _rtB -> B_10_0_0_p [ 0 ] ;
_rtB -> B_10_2_0 [ 3 ] = _rtB -> B_10_0_0_p [ 1 ] ; memcpy ( & _rtB ->
B_10_4_0 [ 0 ] , & _rtB -> B_10_1_0 [ 0 ] , sizeof ( real_T ) << 4U ) ; _rtB
-> B_10_4_0 [ 14 ] = _rtB -> B_10_0_0 ; _rtB -> B_10_4_0 [ 11 ] = _rtB ->
B_18_5_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
sinthrcosthr1_SubsysRanBC ) ; } } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( i
!= 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB -> B_18_23_0_l ) {
if ( ! _rtDW -> sinbetacosbetasinthcosth_MODE ) { if ( ssGetTaskTime ( S , 1
) != ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
} _rtDW -> sinbetacosbetasinthcosth_MODE = true ; } } else { if ( _rtDW ->
sinbetacosbetasinthcosth_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep
( S ) ; _rtDW -> sinbetacosbetasinthcosth_MODE = false ; } } } if ( _rtDW ->
sinbetacosbetasinthcosth_MODE ) { _rtB -> B_8_1_0 = _rtB -> B_8_1_0_j - _rtB
-> B_18_5_0 ; _rtB -> B_8_2_0 = _rtP -> P_27 * _rtB -> B_8_1_0 ; _rtB ->
B_8_3_0 = _rtP -> P_28 * ssGetT ( S ) ; _rtB -> B_8_4_0 = _rtB -> B_8_3_0 -
_rtB -> B_18_4_0 ; muDoubleScalarSinCos ( _rtB -> B_8_3_0 , & _rtB -> B_8_5_0
, & _rtB -> B_8_5_1 ) ; muDoubleScalarSinCos ( _rtB -> B_8_4_0 , & _rtB ->
B_8_6_0 , & _rtB -> B_8_6_1 ) ; memcpy ( & _rtB -> B_8_8_0 [ 0 ] , & _rtB ->
B_8_0_0 [ 0 ] , sizeof ( real_T ) << 4U ) ; _rtB -> B_8_8_0 [ 14 ] = _rtB ->
B_8_1_0 ; _rtB -> B_8_8_0 [ 11 ] = _rtB -> B_8_2_0 ; if ( ssIsMajorTimeStep (
S ) != 0 ) { srUpdateBC ( _rtDW -> sinbetacosbetasinthcosth_SubsysRanBC ) ; }
} switch ( ( int32_T ) _rtB -> B_18_22_0_g ) { case 1 : _rtB -> B_18_9_0 [ 0
] = _rtB -> B_9_2_0 [ 0 ] ; _rtB -> B_18_9_0 [ 1 ] = _rtB -> B_9_2_0 [ 1 ] ;
_rtB -> B_18_9_0 [ 2 ] = _rtB -> B_9_2_0 [ 2 ] ; _rtB -> B_18_9_0 [ 3 ] =
_rtB -> B_9_2_0 [ 3 ] ; break ; case 2 : _rtB -> B_18_9_0 [ 0 ] = _rtB ->
B_10_2_0 [ 0 ] ; _rtB -> B_18_9_0 [ 1 ] = _rtB -> B_10_2_0 [ 1 ] ; _rtB ->
B_18_9_0 [ 2 ] = _rtB -> B_10_2_0 [ 2 ] ; _rtB -> B_18_9_0 [ 3 ] = _rtB ->
B_10_2_0 [ 3 ] ; break ; default : _rtB -> B_18_9_0 [ 0 ] = _rtB -> B_8_6_0 ;
_rtB -> B_18_9_0 [ 1 ] = _rtB -> B_8_6_1 ; _rtB -> B_18_9_0 [ 2 ] = _rtB ->
B_8_5_0 ; _rtB -> B_18_9_0 [ 3 ] = _rtB -> B_8_5_1 ; break ; } i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( i != 0 ) && ( ssIsMajorTimeStep ( S ) !=
0 ) ) { if ( _rtB -> B_18_15_0_l ) { if ( ! _rtDW -> Rotorreferenceframe_MODE
) { if ( ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Rotorreferenceframe_MODE = true ; } } else { if ( _rtDW ->
Rotorreferenceframe_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S )
; _rtB -> B_5_0_0 = _rtP -> P_19 ; _rtB -> B_5_1_0 = _rtP -> P_19 ; _rtB ->
B_5_2_0 = _rtP -> P_20 ; _rtB -> B_5_3_0 = _rtP -> P_20 ; _rtDW ->
Rotorreferenceframe_MODE = false ; } } } if ( _rtDW ->
Rotorreferenceframe_MODE ) { _rtB -> B_5_0_0 = _rtB -> B_18_3_0 [ 2 ] ; _rtB
-> B_5_1_0 = - ( 1.7320508075688772 * _rtB -> B_18_3_0 [ 3 ] + _rtB ->
B_18_3_0 [ 2 ] ) / 2.0 ; _rtB -> B_5_2_0 = _rtB -> B_18_9_0 [ 1 ] * _rtB ->
B_18_3_0 [ 0 ] + _rtB -> B_18_9_0 [ 0 ] * _rtB -> B_18_3_0 [ 1 ] ; _rtB ->
B_5_3_0 = ( ( 1.7320508075688772 * _rtB -> B_18_9_0 [ 0 ] + - _rtB ->
B_18_9_0 [ 1 ] ) * _rtB -> B_18_3_0 [ 0 ] + ( - 1.7320508075688772 * _rtB ->
B_18_9_0 [ 1 ] - _rtB -> B_18_9_0 [ 0 ] ) * _rtB -> B_18_3_0 [ 1 ] ) / 2.0 ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
Rotorreferenceframe_SubsysRanBC ) ; } } i = ssIsSampleHit ( S , 1 , 0 ) ; if
( ( i != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB -> B_18_16_0_o
) { if ( ! _rtDW -> Stationaryreferenceframe_MODE ) { if ( ssGetTaskTime ( S
, 1 ) != ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S
) ; } _rtDW -> Stationaryreferenceframe_MODE = true ; } } else { if ( _rtDW
-> Stationaryreferenceframe_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtB -> B_6_0_0 = _rtP ->
P_21 ; _rtB -> B_6_1_0 = _rtP -> P_21 ; _rtB -> B_6_2_0 = _rtP -> P_22 ; _rtB
-> B_6_3_0 = _rtP -> P_22 ; _rtDW -> Stationaryreferenceframe_MODE = false ;
} } } if ( _rtDW -> Stationaryreferenceframe_MODE ) { _rtB -> B_6_0_0 = _rtB
-> B_18_9_0 [ 1 ] * _rtB -> B_18_3_0 [ 2 ] - _rtB -> B_18_9_0 [ 0 ] * _rtB ->
B_18_3_0 [ 3 ] ; _rtB -> B_6_1_0 = ( ( - _rtB -> B_18_9_0 [ 1 ] -
1.7320508075688772 * _rtB -> B_18_9_0 [ 0 ] ) * _rtB -> B_18_3_0 [ 2 ] + (
_rtB -> B_18_9_0 [ 0 ] - 1.7320508075688772 * _rtB -> B_18_9_0 [ 1 ] ) * _rtB
-> B_18_3_0 [ 3 ] ) / 2.0 ; _rtB -> B_6_2_0 = _rtB -> B_18_3_0 [ 0 ] ; _rtB
-> B_6_3_0 = - ( 1.7320508075688772 * _rtB -> B_18_3_0 [ 1 ] + _rtB ->
B_18_3_0 [ 0 ] ) / 2.0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC (
_rtDW -> Stationaryreferenceframe_SubsysRanBC ) ; } } i = ssIsSampleHit ( S ,
1 , 0 ) ; if ( ( i != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB
-> B_18_17_0_b ) { if ( ! _rtDW -> Synchronousreferenceframe_MODE ) { if (
ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Synchronousreferenceframe_MODE = true ; } } else { if ( _rtDW ->
Synchronousreferenceframe_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep
( S ) ; _rtB -> B_7_0_0 = _rtP -> P_23 ; _rtB -> B_7_1_0 = _rtP -> P_23 ;
_rtB -> B_7_2_0 = _rtP -> P_24 ; _rtB -> B_7_3_0 = _rtP -> P_24 ; _rtDW ->
Synchronousreferenceframe_MODE = false ; } } } if ( _rtDW ->
Synchronousreferenceframe_MODE ) { _rtB -> B_7_0_0 = _rtB -> B_18_9_0 [ 1 ] *
_rtB -> B_18_3_0 [ 2 ] + _rtB -> B_18_9_0 [ 0 ] * _rtB -> B_18_3_0 [ 3 ] ;
_rtB -> B_7_1_0 = ( ( 1.7320508075688772 * _rtB -> B_18_9_0 [ 0 ] + - _rtB ->
B_18_9_0 [ 1 ] ) * _rtB -> B_18_3_0 [ 2 ] + ( - 1.7320508075688772 * _rtB ->
B_18_9_0 [ 1 ] - _rtB -> B_18_9_0 [ 0 ] ) * _rtB -> B_18_3_0 [ 3 ] ) / 2.0 ;
_rtB -> B_7_2_0 = _rtB -> B_18_9_0 [ 3 ] * _rtB -> B_18_3_0 [ 0 ] + _rtB ->
B_18_9_0 [ 2 ] * _rtB -> B_18_3_0 [ 1 ] ; _rtB -> B_7_3_0 = ( (
1.7320508075688772 * _rtB -> B_18_9_0 [ 2 ] + - _rtB -> B_18_9_0 [ 3 ] ) *
_rtB -> B_18_3_0 [ 0 ] + ( - 1.7320508075688772 * _rtB -> B_18_9_0 [ 3 ] -
_rtB -> B_18_9_0 [ 2 ] ) * _rtB -> B_18_3_0 [ 1 ] ) / 2.0 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
Synchronousreferenceframe_SubsysRanBC ) ; } } switch ( ( int32_T ) _rtB ->
B_18_18_0_f ) { case 1 : _rtB -> B_18_13_0 [ 0 ] = _rtB -> B_5_0_0 ; _rtB ->
B_18_13_0 [ 1 ] = _rtB -> B_5_1_0 ; break ; case 2 : _rtB -> B_18_13_0 [ 0 ]
= _rtB -> B_6_0_0 ; _rtB -> B_18_13_0 [ 1 ] = _rtB -> B_6_1_0 ; break ;
default : _rtB -> B_18_13_0 [ 0 ] = _rtB -> B_7_0_0 ; _rtB -> B_18_13_0 [ 1 ]
= _rtB -> B_7_1_0 ; break ; } switch ( ( int32_T ) _rtB -> B_18_19_0_g ) {
case 1 : _rtB -> B_18_14_0 [ 0 ] = _rtB -> B_5_2_0 ; _rtB -> B_18_14_0 [ 1 ]
= _rtB -> B_5_3_0 ; break ; case 2 : _rtB -> B_18_14_0 [ 0 ] = _rtB ->
B_6_2_0 ; _rtB -> B_18_14_0 [ 1 ] = _rtB -> B_6_3_0 ; break ; default : _rtB
-> B_18_14_0 [ 0 ] = _rtB -> B_7_2_0 ; _rtB -> B_18_14_0 [ 1 ] = _rtB ->
B_7_3_0 ; break ; } _rtB -> B_18_15_0 [ 0 ] = _rtP -> P_52 * _rtB ->
B_18_13_0 [ 0 ] ; _rtB -> B_18_15_0 [ 2 ] = _rtP -> P_52 * _rtB -> B_18_14_0
[ 0 ] ; _rtB -> B_18_15_0 [ 1 ] = _rtP -> P_52 * _rtB -> B_18_13_0 [ 1 ] ;
_rtB -> B_18_15_0 [ 3 ] = _rtP -> P_52 * _rtB -> B_18_14_0 [ 1 ] ; { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 3 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay ; {
int_T i1 ; real_T * y0 = & _rtB -> B_18_16_0 [ 0 ] ; int_T * iw_Tail = &
_rtDW -> TransportDelay_IWORK . Tail [ 0 ] ; int_T * iw_Head = & _rtDW ->
TransportDelay_IWORK . Head [ 0 ] ; int_T * iw_Last = & _rtDW ->
TransportDelay_IWORK . Last [ 0 ] ; int_T * iw_CircularBufSize = & _rtDW ->
TransportDelay_IWORK . CircularBufSize [ 0 ] ; for ( i1 = 0 ; i1 < 3 ; i1 ++
) { tMinusDelay = ( ( _rtP -> P_53 > 0.0 ) ? _rtP -> P_53 : 0.0 ) ;
tMinusDelay = simTime - tMinusDelay ; y0 [ i1 ] =
AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , iw_CircularBufSize [ i1 ] , & iw_Last [ i1 ] ,
iw_Tail [ i1 ] , iw_Head [ i1 ] , _rtP -> P_54 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; tBuffer ++ ; uBuffer ++ ; } } } ssCallAccelRunBlock ( S , 18 , 17 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_18_18_0 [ 0 ] = _rtP -> P_63 [ 0 ] * _rtB
-> B_18_3_0 [ 0 ] ; _rtB -> B_18_18_0 [ 1 ] = _rtP -> P_63 [ 1 ] * _rtB ->
B_18_3_0 [ 1 ] ; _rtB -> B_18_19_0 [ 0 ] = _rtB -> B_18_0_0 [ 1 ] * _rtB ->
B_18_18_0 [ 0 ] ; _rtB -> B_18_19_0 [ 1 ] = _rtB -> B_18_0_0 [ 0 ] * _rtB ->
B_18_18_0 [ 1 ] ; _rtB -> B_18_20_0 = _rtB -> B_18_19_0 [ 0 ] + _rtB ->
B_18_19_0 [ 1 ] ; _rtB -> B_18_21_0 = _rtP -> P_64 * _rtB -> B_18_4_0 ; _rtB
-> B_18_22_0 [ 0 ] = _rtP -> P_65 [ 0 ] * _rtB -> B_18_5_0 ; _rtB ->
B_18_22_0 [ 1 ] = _rtP -> P_65 [ 1 ] * _rtB -> B_18_20_0 ; _rtB -> B_18_22_0
[ 2 ] = _rtP -> P_65 [ 2 ] * _rtB -> B_18_21_0 ; _rtB -> B_18_23_0 = _rtP ->
P_66 * _rtB -> B_18_22_0 [ 0 ] ; _rtB -> B_18_25_0 = _rtB -> B_18_33_0_n -
_rtP -> P_67 * _rtB -> B_18_23_0 ; ssCallAccelRunBlock ( S , 18 , 26 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_18_28_0 [ 0 ] = _rtP -> P_68 * _rtB ->
B_18_14_0_c [ 0 ] ; _rtB -> B_18_28_0 [ 2 ] = _rtP -> P_68 * _rtB ->
B_18_17_0 [ 0 ] ; _rtB -> B_18_28_0 [ 1 ] = _rtP -> P_68 * _rtB ->
B_18_14_0_c [ 1 ] ; _rtB -> B_18_28_0 [ 3 ] = _rtP -> P_68 * _rtB ->
B_18_17_0 [ 1 ] ; _rtB -> B_18_27_0 = ( 0.0 - _rtB -> B_18_13_0 [ 0 ] ) -
_rtB -> B_18_13_0 [ 1 ] ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( ( i != 0 )
&& ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB -> B_18_9_0_d ) { if ( !
_rtDW -> Rotorreferenceframe_MODE_c ) { if ( ssGetTaskTime ( S , 1 ) !=
ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
_rtDW -> Rotorreferenceframe_MODE_c = true ; } } else { if ( _rtDW ->
Rotorreferenceframe_MODE_c ) { ssSetBlockStateForSolverChangedAtMajorStep ( S
) ; _rtB -> B_2_2_0 = _rtP -> P_13 ; _rtB -> B_2_0_0 = _rtP -> P_13 ; _rtB ->
B_2_3_0 = _rtP -> P_14 ; _rtB -> B_2_1_0 = _rtP -> P_14 ; _rtDW ->
Rotorreferenceframe_MODE_c = false ; } } } if ( _rtDW ->
Rotorreferenceframe_MODE_c ) { _rtB -> B_2_0_0 = - 0.57735026918962573 * _rtB
-> B_18_28_0 [ 1 ] ; _rtB -> B_2_1_0 = ( ( _rtB -> B_18_9_0 [ 0 ] -
1.7320508075688772 * _rtB -> B_18_9_0 [ 1 ] ) * _rtB -> B_18_28_0 [ 3 ] + 2.0
* _rtB -> B_18_9_0 [ 0 ] * _rtB -> B_18_28_0 [ 2 ] ) * 0.33333333333333331 ;
_rtB -> B_2_2_0 = ( 2.0 * _rtB -> B_18_28_0 [ 0 ] + _rtB -> B_18_28_0 [ 1 ] )
* 0.33333333333333331 ; _rtB -> B_2_3_0 = ( ( 1.7320508075688772 * _rtB ->
B_18_9_0 [ 0 ] + _rtB -> B_18_9_0 [ 1 ] ) * _rtB -> B_18_28_0 [ 3 ] + 2.0 *
_rtB -> B_18_9_0 [ 1 ] * _rtB -> B_18_28_0 [ 2 ] ) * 0.33333333333333331 ; if
( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
Rotorreferenceframe_SubsysRanBC_c ) ; } } i = ssIsSampleHit ( S , 1 , 0 ) ;
if ( ( i != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB ->
B_18_10_0 ) { if ( ! _rtDW -> Stationaryreferenceframe_MODE_n ) { if (
ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Stationaryreferenceframe_MODE_n = true ; } } else { if ( _rtDW ->
Stationaryreferenceframe_MODE_n ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtB -> B_3_2_0 = _rtP ->
P_15 ; _rtB -> B_3_0_0 = _rtP -> P_15 ; _rtB -> B_3_3_0 = _rtP -> P_16 ; _rtB
-> B_3_1_0 = _rtP -> P_16 ; _rtDW -> Stationaryreferenceframe_MODE_n = false
; } } } if ( _rtDW -> Stationaryreferenceframe_MODE_n ) { _rtB -> B_3_0_0 = (
( - _rtB -> B_18_9_0 [ 0 ] - 1.7320508075688772 * _rtB -> B_18_9_0 [ 1 ] ) *
_rtB -> B_18_28_0 [ 1 ] + - 2.0 * _rtB -> B_18_9_0 [ 0 ] * _rtB -> B_18_28_0
[ 0 ] ) * 0.33333333333333331 ; _rtB -> B_3_1_0 = - 0.57735026918962573 *
_rtB -> B_18_28_0 [ 3 ] ; _rtB -> B_3_2_0 = ( ( _rtB -> B_18_9_0 [ 1 ] -
1.7320508075688772 * _rtB -> B_18_9_0 [ 0 ] ) * _rtB -> B_18_28_0 [ 1 ] + 2.0
* _rtB -> B_18_9_0 [ 1 ] * _rtB -> B_18_28_0 [ 0 ] ) * 0.33333333333333331 ;
_rtB -> B_3_3_0 = ( 2.0 * _rtB -> B_18_28_0 [ 2 ] + _rtB -> B_18_28_0 [ 3 ] )
* 0.33333333333333331 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC (
_rtDW -> Stationaryreferenceframe_SubsysRanBC_k ) ; } } i = ssIsSampleHit ( S
, 1 , 0 ) ; if ( ( i != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB
-> B_18_11_0 ) { if ( ! _rtDW -> Synchronousreferenceframe_MODE_f ) { if (
ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Synchronousreferenceframe_MODE_f = true ; } } else { if ( _rtDW ->
Synchronousreferenceframe_MODE_f ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtB -> B_4_2_0 = _rtP ->
P_17 ; _rtB -> B_4_0_0 = _rtP -> P_17 ; _rtB -> B_4_3_0 = _rtP -> P_18 ; _rtB
-> B_4_1_0 = _rtP -> P_18 ; _rtDW -> Synchronousreferenceframe_MODE_f = false
; } } } if ( _rtDW -> Synchronousreferenceframe_MODE_f ) { _rtB -> B_4_0_0 =
( ( _rtB -> B_18_9_0 [ 0 ] - 1.7320508075688772 * _rtB -> B_18_9_0 [ 1 ] ) *
_rtB -> B_18_28_0 [ 1 ] + 2.0 * _rtB -> B_18_9_0 [ 0 ] * _rtB -> B_18_28_0 [
0 ] ) / 3.0 ; _rtB -> B_4_1_0 = ( ( _rtB -> B_18_9_0 [ 2 ] -
1.7320508075688772 * _rtB -> B_18_9_0 [ 3 ] ) * _rtB -> B_18_28_0 [ 3 ] + 2.0
* _rtB -> B_18_9_0 [ 2 ] * _rtB -> B_18_28_0 [ 2 ] ) / 3.0 ; _rtB -> B_4_2_0
= ( ( 1.7320508075688772 * _rtB -> B_18_9_0 [ 0 ] + _rtB -> B_18_9_0 [ 1 ] )
* _rtB -> B_18_28_0 [ 1 ] + 2.0 * _rtB -> B_18_9_0 [ 1 ] * _rtB -> B_18_28_0
[ 0 ] ) / 3.0 ; _rtB -> B_4_3_0 = ( ( 1.7320508075688772 * _rtB -> B_18_9_0 [
2 ] + _rtB -> B_18_9_0 [ 3 ] ) * _rtB -> B_18_28_0 [ 3 ] + 2.0 * _rtB ->
B_18_9_0 [ 3 ] * _rtB -> B_18_28_0 [ 2 ] ) / 3.0 ; if ( ssIsMajorTimeStep ( S
) != 0 ) { srUpdateBC ( _rtDW -> Synchronousreferenceframe_SubsysRanBC_i ) ;
} } switch ( ( int32_T ) _rtB -> B_18_12_0 ) { case 1 : _rtB -> B_18_32_0 [ 0
] = _rtB -> B_2_2_0 ; _rtB -> B_18_32_0 [ 1 ] = _rtB -> B_2_0_0 ; break ;
case 2 : _rtB -> B_18_32_0 [ 0 ] = _rtB -> B_3_2_0 ; _rtB -> B_18_32_0 [ 1 ]
= _rtB -> B_3_0_0 ; break ; default : _rtB -> B_18_32_0 [ 0 ] = _rtB ->
B_4_2_0 ; _rtB -> B_18_32_0 [ 1 ] = _rtB -> B_4_0_0 ; break ; } _rtB ->
B_18_33_0 = ( 0.0 - _rtB -> B_18_14_0 [ 0 ] ) - _rtB -> B_18_14_0 [ 1 ] ;
switch ( ( int32_T ) _rtB -> B_18_13_0_p ) { case 1 : _rtB -> B_18_34_0 [ 0 ]
= _rtB -> B_2_3_0 ; _rtB -> B_18_34_0 [ 1 ] = _rtB -> B_2_1_0 ; break ; case
2 : _rtB -> B_18_34_0 [ 0 ] = _rtB -> B_3_3_0 ; _rtB -> B_18_34_0 [ 1 ] =
_rtB -> B_3_1_0 ; break ; default : _rtB -> B_18_34_0 [ 0 ] = _rtB -> B_4_3_0
; _rtB -> B_18_34_0 [ 1 ] = _rtB -> B_4_1_0 ; break ; } if ( _rtB -> B_18_6_0
>= _rtP -> P_69 ) { _rtB -> B_18_35_0 = _rtB -> B_1_13_0 ; } else { _rtB ->
B_18_35_0 = _rtB -> B_18_7_0 ; } _rtB -> B_18_36_0 [ 2 ] = _rtP -> P_70 [ 2 ]
* _rtB -> B_18_27_0 ; _rtB -> B_18_36_0 [ 11 ] = _rtP -> P_70 [ 11 ] * _rtB
-> B_18_33_0 ; _rtB -> B_18_36_0 [ 0 ] = _rtP -> P_70 [ 0 ] * _rtB ->
B_18_13_0 [ 0 ] ; _rtB -> B_18_36_0 [ 3 ] = _rtP -> P_70 [ 3 ] * _rtB ->
B_18_3_0 [ 2 ] ; _rtB -> B_18_36_0 [ 5 ] = _rtP -> P_70 [ 5 ] * _rtB ->
B_18_0_0 [ 2 ] ; _rtB -> B_18_36_0 [ 7 ] = _rtP -> P_70 [ 7 ] * _rtB ->
B_18_32_0 [ 0 ] ; _rtB -> B_18_36_0 [ 9 ] = _rtP -> P_70 [ 9 ] * _rtB ->
B_18_14_0 [ 0 ] ; _rtB -> B_18_36_0 [ 12 ] = _rtP -> P_70 [ 12 ] * _rtB ->
B_18_3_0 [ 0 ] ; _rtB -> B_18_36_0 [ 14 ] = _rtP -> P_70 [ 14 ] * _rtB ->
B_18_0_0 [ 0 ] ; _rtB -> B_18_36_0 [ 16 ] = _rtP -> P_70 [ 16 ] * _rtB ->
B_18_34_0 [ 0 ] ; _rtB -> B_18_36_0 [ 1 ] = _rtP -> P_70 [ 1 ] * _rtB ->
B_18_13_0 [ 1 ] ; _rtB -> B_18_36_0 [ 4 ] = _rtP -> P_70 [ 4 ] * _rtB ->
B_18_3_0 [ 3 ] ; _rtB -> B_18_36_0 [ 6 ] = _rtP -> P_70 [ 6 ] * _rtB ->
B_18_0_0 [ 3 ] ; _rtB -> B_18_36_0 [ 8 ] = _rtP -> P_70 [ 8 ] * _rtB ->
B_18_32_0 [ 1 ] ; _rtB -> B_18_36_0 [ 10 ] = _rtP -> P_70 [ 10 ] * _rtB ->
B_18_14_0 [ 1 ] ; _rtB -> B_18_36_0 [ 13 ] = _rtP -> P_70 [ 13 ] * _rtB ->
B_18_3_0 [ 1 ] ; _rtB -> B_18_36_0 [ 15 ] = _rtP -> P_70 [ 15 ] * _rtB ->
B_18_0_0 [ 1 ] ; _rtB -> B_18_36_0 [ 17 ] = _rtP -> P_70 [ 17 ] * _rtB ->
B_18_34_0 [ 1 ] ; _rtB -> B_18_36_0 [ 18 ] = _rtP -> P_70 [ 18 ] * _rtB ->
B_18_35_0 ; _rtB -> B_18_37_0 = muDoubleScalarAtan2 ( _rtB -> B_18_36_0 [ 5 ]
, _rtB -> B_18_36_0 [ 6 ] ) ; ssCallAccelRunBlock ( S , 15 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; rtb_B_1_4_0 = _rtB -> B_15_0_1 + _rtP -> P_71 ; _rtB
-> B_18_40_0 = muDoubleScalarCos ( rtb_B_1_4_0 - 1.5707963267948966 ) * _rtB
-> B_18_36_0 [ 6 ] + muDoubleScalarSin ( rtb_B_1_4_0 - 1.5707963267948966 ) *
_rtB -> B_18_36_0 [ 5 ] ; _rtB -> B_18_41_0 = - muDoubleScalarSin (
rtb_B_1_4_0 - 1.5707963267948966 ) * _rtB -> B_18_36_0 [ 6 ] +
muDoubleScalarCos ( rtb_B_1_4_0 - 1.5707963267948966 ) * _rtB -> B_18_36_0 [
5 ] ; _rtB -> B_18_42_0 = 0.0 ; _rtB -> B_18_46_0 [ 0 ] = ( ( _rtB ->
B_18_36_0 [ 9 ] - 0.5 * _rtB -> B_18_36_0 [ 10 ] ) - 0.5 * _rtB -> B_18_36_0
[ 11 ] ) * _rtP -> P_72 [ 0 ] ; _rtB -> B_18_46_0 [ 1 ] = ( _rtB -> B_18_36_0
[ 10 ] - _rtB -> B_18_36_0 [ 11 ] ) * 1.7320508075688772 / 2.0 * _rtP -> P_72
[ 1 ] ; _rtB -> B_18_46_0 [ 2 ] = ( ( _rtB -> B_18_36_0 [ 9 ] + _rtB ->
B_18_36_0 [ 10 ] ) + _rtB -> B_18_36_0 [ 11 ] ) * _rtP -> P_72 [ 2 ] ; _rtB
-> B_18_47_0 = _rtP -> P_73 * _rtB -> B_18_22_0 [ 2 ] ; _rtB -> B_18_48_0 =
_rtB -> B_18_37_0 + _rtB -> B_18_47_0 ; _rtB -> B_18_49_0 = muDoubleScalarCos
( _rtB -> B_18_48_0 - 1.5707963267948966 ) * _rtB -> B_18_46_0 [ 0 ] +
muDoubleScalarSin ( _rtB -> B_18_48_0 - 1.5707963267948966 ) * _rtB ->
B_18_46_0 [ 1 ] ; _rtB -> B_18_50_0 = - muDoubleScalarSin ( _rtB -> B_18_48_0
- 1.5707963267948966 ) * _rtB -> B_18_46_0 [ 0 ] + muDoubleScalarCos ( _rtB
-> B_18_48_0 - 1.5707963267948966 ) * _rtB -> B_18_46_0 [ 1 ] ; _rtB ->
B_18_51_0 = _rtB -> B_18_46_0 [ 2 ] ; _rtB -> B_18_52_0 = muDoubleScalarHypot
( _rtB -> B_18_36_0 [ 6 ] , _rtB -> B_18_36_0 [ 5 ] ) ; _rtB -> B_18_53_0 =
_rtB -> B_18_0_0_m - _rtB -> B_18_52_0 ; _rtB -> B_18_54_0 = _rtP -> P_74 *
_rtB -> B_18_53_0 ; _rtB -> B_18_55_0 = _rtX -> Integrator_CSTATE_k ; _rtB ->
B_18_56_0 = _rtB -> B_18_54_0 + _rtB -> B_18_55_0 ; if ( _rtB -> B_18_56_0 >
_rtP -> P_76 ) { _rtB -> B_18_57_0 = _rtP -> P_76 ; } else if ( _rtB ->
B_18_56_0 < _rtP -> P_77 ) { _rtB -> B_18_57_0 = _rtP -> P_77 ; } else { _rtB
-> B_18_57_0 = _rtB -> B_18_56_0 ; } _rtB -> B_18_58_0 = _rtB -> B_18_57_0 -
_rtB -> B_18_49_0 ; _rtB -> B_18_59_0 = _rtP -> P_78 * _rtB -> B_18_58_0 ;
_rtB -> B_18_60_0 = _rtX -> Integrator_CSTATE_e ; _rtB -> B_18_61_0 = _rtB ->
B_18_59_0 + _rtB -> B_18_60_0 ; if ( _rtB -> B_18_61_0 > _rtP -> P_80 ) {
_rtB -> B_18_62_0 = _rtP -> P_80 ; } else if ( _rtB -> B_18_61_0 < _rtP ->
P_81 ) { _rtB -> B_18_62_0 = _rtP -> P_81 ; } else { _rtB -> B_18_62_0 = _rtB
-> B_18_61_0 ; } _rtB -> B_18_63_0 = _rtP -> P_82 * _rtB -> B_18_22_0 [ 0 ] ;
_rtB -> B_18_64_0 = _rtB -> B_18_33_0_n - _rtB -> B_18_63_0 ; _rtB ->
B_18_65_0 = _rtP -> P_83 * _rtB -> B_18_64_0 ; _rtB -> B_18_66_0 = _rtX ->
Integrator_CSTATE_m ; _rtB -> B_18_67_0 = _rtB -> B_18_65_0 + _rtB ->
B_18_66_0 ; if ( _rtB -> B_18_67_0 > _rtP -> P_85 ) { _rtB -> B_18_68_0 =
_rtP -> P_85 ; } else if ( _rtB -> B_18_67_0 < _rtP -> P_86 ) { _rtB ->
B_18_68_0 = _rtP -> P_86 ; } else { _rtB -> B_18_68_0 = _rtB -> B_18_67_0 ; }
_rtB -> B_18_69_0 = _rtB -> B_18_68_0 - _rtB -> B_18_50_0 ; _rtB -> B_18_70_0
= _rtP -> P_87 * _rtB -> B_18_69_0 ; _rtB -> B_18_71_0 = _rtX ->
Integrator_CSTATE_ex ; _rtB -> B_18_72_0 = _rtB -> B_18_70_0 + _rtB ->
B_18_71_0 ; if ( _rtB -> B_18_72_0 > _rtP -> P_89 ) { _rtB -> B_18_73_0 =
_rtP -> P_89 ; } else if ( _rtB -> B_18_72_0 < _rtP -> P_90 ) { _rtB ->
B_18_73_0 = _rtP -> P_90 ; } else { _rtB -> B_18_73_0 = _rtB -> B_18_72_0 ; }
_rtB -> B_16_0_0 [ 0 ] = _rtB -> B_18_62_0 ; _rtB -> B_16_0_0 [ 1 ] = _rtB ->
B_18_73_0 ; ssCallAccelRunBlock ( S , 16 , 1 , SS_CALL_MDL_OUTPUTS ) ; _rtB
-> B_18_75_0 = _rtX -> integrator_CSTATE ; { real_T * * uBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 1
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_92 ; B_18_76_0 = AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayInterpolate
( tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_l
. CircularBufSize , & _rtDW -> TransportDelay_IWORK_l . Last , _rtDW ->
TransportDelay_IWORK_l . Tail , _rtDW -> TransportDelay_IWORK_l . Head , _rtP
-> P_93 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } i = ssIsSampleHit ( S ,
1 , 0 ) ; if ( i != 0 ) { _rtB -> B_18_78_0 = _rtP -> P_94 ; } rtb_B_18_79_0
= ( ssGetT ( S ) >= _rtB -> B_18_78_0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ;
if ( i != 0 ) { _rtB -> B_18_80_0 = _rtDW -> Memory_PreviousInput ; } if (
rtb_B_18_79_0 ) { _rtB -> B_18_82_0 = ( _rtB -> B_18_75_0 - B_18_76_0 ) *
_rtP -> P_42 ; } else { _rtB -> B_18_82_0 = _rtB -> B_18_80_0 ; } _rtB ->
B_18_83_0 = _rtX -> integrator_CSTATE_m ; { real_T * * uBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T * * tBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK_l . TUbufferPtrs [ 1 ] ;
real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_97 ;
_rtB -> B_18_84_0 =
AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_h .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_h . Last , _rtDW ->
TransportDelay_IWORK_h . Tail , _rtDW -> TransportDelay_IWORK_h . Head , _rtP
-> P_98 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } i = ssIsSampleHit ( S ,
1 , 0 ) ; if ( i != 0 ) { _rtB -> B_18_86_0 = _rtP -> P_99 ; } rtb_B_18_79_0
= ( ssGetT ( S ) >= _rtB -> B_18_86_0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ;
if ( i != 0 ) { _rtB -> B_18_88_0 = _rtDW -> Memory_PreviousInput_p ; } if (
rtb_B_18_79_0 ) { _rtB -> B_17_0_0 = _rtB -> B_18_83_0 - _rtB -> B_18_84_0 ;
_rtB -> B_17_1_0 = _rtP -> P_43 * _rtB -> B_17_0_0 ; _rtB -> B_18_90_0 = _rtB
-> B_17_1_0 ; } else { _rtB -> B_18_90_0 = _rtB -> B_18_88_0 ; } _rtB ->
B_18_91_0 = _rtX -> integrator_CSTATE_j ; { real_T * * uBuffer = ( real_T * *
) & _rtDW -> TransportDelay_PWORK_h5 . TUbufferPtrs [ 0 ] ; real_T * *
tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_h5 . TUbufferPtrs [
1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_102 ; B_18_92_0 =
AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay_IWORK_f .
CircularBufSize , & _rtDW -> TransportDelay_IWORK_f . Last , _rtDW ->
TransportDelay_IWORK_f . Tail , _rtDW -> TransportDelay_IWORK_f . Head , _rtP
-> P_103 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } i = ssIsSampleHit ( S ,
1 , 0 ) ; if ( i != 0 ) { _rtB -> B_18_94_0 = _rtP -> P_104 ; } rtb_B_18_79_0
= ( ssGetT ( S ) >= _rtB -> B_18_94_0 ) ; i = ssIsSampleHit ( S , 1 , 0 ) ;
if ( i != 0 ) { _rtB -> B_18_96_0 = _rtDW -> Memory_PreviousInput_a ; } if (
rtb_B_18_79_0 ) { _rtB -> B_18_98_0 = ( _rtB -> B_18_91_0 - B_18_92_0 ) *
_rtP -> P_41 ; } else { _rtB -> B_18_98_0 = _rtB -> B_18_96_0 ; } _rtB ->
B_18_99_0 = _rtB -> B_18_82_0 / _rtB -> B_18_98_0 ; ssCallAccelRunBlock ( S ,
18 , 100 , SS_CALL_MDL_OUTPUTS ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i
!= 0 ) { { if ( ( _rtDW -> TAQSigLogging_InsertedFor_From2_at_outport_0_PWORK
. AQHandles || _rtDW -> TAQSigLogging_InsertedFor_From2_at_outport_0_PWORK .
SlioLTF ) && ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_From2_at_outport_0_PWORK . AQHandles , _rtDW ->
TAQSigLogging_InsertedFor_From2_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_18_52_0 + 0 ) ; } } } switch
( ( int32_T ) _rtB -> B_18_24_0 ) { case 1 : memcpy ( & _rtB -> B_18_111_0 [
0 ] , & _rtB -> B_9_4_0 [ 0 ] , sizeof ( real_T ) << 4U ) ; break ; case 2 :
memcpy ( & _rtB -> B_18_111_0 [ 0 ] , & _rtB -> B_10_4_0 [ 0 ] , sizeof (
real_T ) << 4U ) ; break ; default : memcpy ( & _rtB -> B_18_111_0 [ 0 ] , &
_rtB -> B_8_8_0 [ 0 ] , sizeof ( real_T ) << 4U ) ; break ; } for ( i = 0 ; i
< 16 ; i ++ ) { if ( _rtB -> B_18_4_0_c >= _rtP -> P_106 ) { _rtB ->
B_18_112_0 [ i ] = _rtB -> B_1_18_0 [ i ] ; } else { _rtB -> B_18_112_0 [ i ]
= _rtB -> B_18_5_0_b [ i ] ; } _rtB -> B_18_113_0 [ i ] = ( 0.0 - _rtB ->
B_18_111_0 [ i ] ) - _rtB -> B_18_112_0 [ i ] ; } for ( i = 0 ; i < 4 ; i ++
) { _rtB -> B_18_114_0 [ i ] = 0.0 ; _rtB -> B_18_114_0 [ i ] += _rtB ->
B_18_113_0 [ i ] * _rtB -> B_18_0_0 [ 0 ] ; _rtB -> B_18_114_0 [ i ] += _rtB
-> B_18_113_0 [ i + 4 ] * _rtB -> B_18_0_0 [ 1 ] ; _rtB -> B_18_114_0 [ i ]
+= _rtB -> B_18_113_0 [ i + 8 ] * _rtB -> B_18_0_0 [ 2 ] ; _rtB -> B_18_114_0
[ i ] += _rtB -> B_18_113_0 [ i + 12 ] * _rtB -> B_18_0_0 [ 3 ] ; } _rtB ->
B_18_115_0 [ 0 ] = _rtB -> B_18_34_0 [ 0 ] + _rtB -> B_18_114_0 [ 0 ] ; _rtB
-> B_18_115_0 [ 2 ] = _rtB -> B_18_32_0 [ 0 ] + _rtB -> B_18_114_0 [ 2 ] ;
_rtB -> B_18_115_0 [ 1 ] = _rtB -> B_18_34_0 [ 1 ] + _rtB -> B_18_114_0 [ 1 ]
; _rtB -> B_18_115_0 [ 3 ] = _rtB -> B_18_32_0 [ 1 ] + _rtB -> B_18_114_0 [ 3
] ; _rtB -> B_18_116_0 [ 0 ] = _rtP -> P_107 * _rtB -> B_18_115_0 [ 0 ] ;
_rtB -> B_18_116_0 [ 1 ] = _rtP -> P_107 * _rtB -> B_18_115_0 [ 1 ] ; _rtB ->
B_18_116_0 [ 2 ] = _rtP -> P_107 * _rtB -> B_18_115_0 [ 2 ] ; _rtB ->
B_18_116_0 [ 3 ] = _rtP -> P_107 * _rtB -> B_18_115_0 [ 3 ] ; _rtB ->
B_18_117_0 = _rtP -> P_108 * _rtB -> B_18_22_0 [ 0 ] ; if ( _rtB ->
B_18_117_0 > _rtB -> B_18_28_0_m ) { _rtB -> B_18_120_0 = _rtB -> B_18_28_0_m
; } else { if ( _rtB -> B_18_117_0 < _rtB -> B_18_29_0 ) { _rtB -> B_11_1_0 =
_rtB -> B_18_29_0 ; } else { _rtB -> B_11_1_0 = _rtB -> B_18_117_0 ; } _rtB
-> B_18_120_0 = _rtB -> B_11_1_0 ; } _rtB -> B_18_121_0 = _rtP -> P_109 *
_rtB -> B_18_120_0 ; _rtB -> B_18_122_0 = _rtP -> P_110 * _rtB -> B_18_5_0 ;
_rtB -> B_18_123_0 = ( _rtB -> B_18_20_0 - _rtB -> B_18_121_0 ) - _rtB ->
B_18_122_0 ; _rtB -> B_18_124_0 = _rtP -> P_111 * _rtB -> B_18_123_0 ; _rtB
-> B_18_125_0 = _rtP -> P_112 * _rtB -> B_18_5_0 ; _rtB -> B_18_131_0 [ 0 ] =
_rtP -> P_113 [ 0 ] * _rtB -> B_18_17_0 [ 4 ] ; _rtB -> B_18_131_0 [ 1 ] =
_rtP -> P_113 [ 1 ] * _rtB -> B_18_17_0 [ 2 ] ; _rtB -> B_18_131_0 [ 2 ] =
_rtP -> P_113 [ 2 ] * _rtB -> B_18_17_0 [ 3 ] ; i = ssIsSampleHit ( S , 1 , 0
) ; if ( ( i != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( _rtB ->
B_18_30_0 > 0.0 ) { if ( ! _rtDW -> StoreData_MODE ) { if ( ssGetTaskTime ( S
, 1 ) != ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S
) ; } _rtDW -> StoreData_MODE = true ; } } else { if ( _rtDW ->
StoreData_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtDW
-> StoreData_MODE = false ; } } } if ( _rtDW -> StoreData_MODE ) {
ssCallAccelRunBlock ( S , 14 , 0 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW -> StoreData_SubsysRanBC
) ; } } _rtB -> B_18_134_0 = _rtB -> B_18_22_0 [ 0 ] * _rtB -> B_18_22_0 [ 1
] ; _rtB -> B_18_138_0 [ 0 ] = ( ( muDoubleScalarSin ( _rtB -> B_18_48_0 ) *
_rtB -> B_16_1_1 [ 0 ] + muDoubleScalarCos ( _rtB -> B_18_48_0 ) * _rtB ->
B_16_1_1 [ 1 ] ) + _rtB -> B_16_1_1 [ 2 ] ) * _rtP -> P_114 ; _rtB ->
B_18_138_0 [ 1 ] = ( ( muDoubleScalarSin ( _rtB -> B_18_48_0 -
2.0943951023931953 ) * _rtB -> B_16_1_1 [ 0 ] + muDoubleScalarCos ( _rtB ->
B_18_48_0 - 2.0943951023931953 ) * _rtB -> B_16_1_1 [ 1 ] ) + _rtB ->
B_16_1_1 [ 2 ] ) * _rtP -> P_114 ; _rtB -> B_18_138_0 [ 2 ] = ( (
muDoubleScalarSin ( _rtB -> B_18_48_0 + 2.0943951023931953 ) * _rtB ->
B_16_1_1 [ 0 ] + muDoubleScalarCos ( _rtB -> B_18_48_0 + 2.0943951023931953 )
* _rtB -> B_16_1_1 [ 1 ] ) + _rtB -> B_16_1_1 [ 2 ] ) * _rtP -> P_114 ; if (
_rtB -> B_18_61_0 > _rtP -> P_117 ) { rtb_B_1_4_0 = _rtB -> B_18_61_0 - _rtP
-> P_117 ; } else if ( _rtB -> B_18_61_0 >= _rtP -> P_116 ) { rtb_B_1_4_0 =
0.0 ; } else { rtb_B_1_4_0 = _rtB -> B_18_61_0 - _rtP -> P_116 ; } _rtB ->
B_18_144_0 = _rtP -> P_118 * _rtB -> B_18_58_0 ; tmp = muDoubleScalarSign (
rtb_B_1_4_0 ) ; if ( muDoubleScalarIsNaN ( tmp ) ) { tmp = 0.0 ; } else { tmp
= muDoubleScalarRem ( tmp , 256.0 ) ; } tmp_0 = muDoubleScalarSign ( _rtB ->
B_18_144_0 ) ; if ( muDoubleScalarIsNaN ( tmp_0 ) ) { tmp_0 = 0.0 ; } else {
tmp_0 = muDoubleScalarRem ( tmp_0 , 256.0 ) ; } _rtB -> B_18_148_0 = ( ( _rtP
-> P_115 * _rtB -> B_18_61_0 != rtb_B_1_4_0 ) && ( ( tmp < 0.0 ? ( int32_T )
( int8_T ) - ( int8_T ) ( uint8_T ) - tmp : ( int32_T ) ( int8_T ) ( uint8_T
) tmp ) == ( tmp_0 < 0.0 ? ( int32_T ) ( int8_T ) - ( int8_T ) ( uint8_T ) -
tmp_0 : ( int32_T ) ( int8_T ) ( uint8_T ) tmp_0 ) ) ) ; i = ssIsSampleHit (
S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_18_149_0 = _rtDW ->
Memory_PreviousInput_h ; } if ( _rtB -> B_18_149_0 ) { _rtB -> B_18_150_0 =
AD_Vect_low_izm_dif_modes_subsyst_rtC ( S ) -> B_18_0_0 ; } else { _rtB ->
B_18_150_0 = _rtB -> B_18_144_0 ; } if ( _rtB -> B_18_56_0 > _rtP -> P_121 )
{ rtb_B_1_4_0 = _rtB -> B_18_56_0 - _rtP -> P_121 ; } else if ( _rtB ->
B_18_56_0 >= _rtP -> P_120 ) { rtb_B_1_4_0 = 0.0 ; } else { rtb_B_1_4_0 =
_rtB -> B_18_56_0 - _rtP -> P_120 ; } _rtB -> B_18_156_0 = _rtP -> P_122 *
_rtB -> B_18_53_0 ; tmp = muDoubleScalarSign ( rtb_B_1_4_0 ) ; if (
muDoubleScalarIsNaN ( tmp ) ) { tmp = 0.0 ; } else { tmp = muDoubleScalarRem
( tmp , 256.0 ) ; } tmp_0 = muDoubleScalarSign ( _rtB -> B_18_156_0 ) ; if (
muDoubleScalarIsNaN ( tmp_0 ) ) { tmp_0 = 0.0 ; } else { tmp_0 =
muDoubleScalarRem ( tmp_0 , 256.0 ) ; } _rtB -> B_18_160_0 = ( ( _rtP ->
P_119 * _rtB -> B_18_56_0 != rtb_B_1_4_0 ) && ( ( tmp < 0.0 ? ( int32_T ) (
int8_T ) - ( int8_T ) ( uint8_T ) - tmp : ( int32_T ) ( int8_T ) ( uint8_T )
tmp ) == ( tmp_0 < 0.0 ? ( int32_T ) ( int8_T ) - ( int8_T ) ( uint8_T ) -
tmp_0 : ( int32_T ) ( int8_T ) ( uint8_T ) tmp_0 ) ) ) ; i = ssIsSampleHit (
S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_18_161_0 = _rtDW ->
Memory_PreviousInput_l ; } if ( _rtB -> B_18_161_0 ) { _rtB -> B_18_162_0 =
AD_Vect_low_izm_dif_modes_subsyst_rtC ( S ) -> B_18_1_0 ; } else { _rtB ->
B_18_162_0 = _rtB -> B_18_156_0 ; } if ( _rtB -> B_18_67_0 > _rtP -> P_125 )
{ rtb_B_1_4_0 = _rtB -> B_18_67_0 - _rtP -> P_125 ; } else if ( _rtB ->
B_18_67_0 >= _rtP -> P_124 ) { rtb_B_1_4_0 = 0.0 ; } else { rtb_B_1_4_0 =
_rtB -> B_18_67_0 - _rtP -> P_124 ; } _rtB -> B_18_168_0 = _rtP -> P_126 *
_rtB -> B_18_64_0 ; tmp = muDoubleScalarSign ( rtb_B_1_4_0 ) ; if (
muDoubleScalarIsNaN ( tmp ) ) { tmp = 0.0 ; } else { tmp = muDoubleScalarRem
( tmp , 256.0 ) ; } tmp_0 = muDoubleScalarSign ( _rtB -> B_18_168_0 ) ; if (
muDoubleScalarIsNaN ( tmp_0 ) ) { tmp_0 = 0.0 ; } else { tmp_0 =
muDoubleScalarRem ( tmp_0 , 256.0 ) ; } _rtB -> B_18_172_0 = ( ( _rtP ->
P_123 * _rtB -> B_18_67_0 != rtb_B_1_4_0 ) && ( ( tmp < 0.0 ? ( int32_T ) (
int8_T ) - ( int8_T ) ( uint8_T ) - tmp : ( int32_T ) ( int8_T ) ( uint8_T )
tmp ) == ( tmp_0 < 0.0 ? ( int32_T ) ( int8_T ) - ( int8_T ) ( uint8_T ) -
tmp_0 : ( int32_T ) ( int8_T ) ( uint8_T ) tmp_0 ) ) ) ; i = ssIsSampleHit (
S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_18_173_0 = _rtDW ->
Memory_PreviousInput_k ; } if ( _rtB -> B_18_173_0 ) { _rtB -> B_18_174_0 =
AD_Vect_low_izm_dif_modes_subsyst_rtC ( S ) -> B_18_2_0 ; } else { _rtB ->
B_18_174_0 = _rtB -> B_18_168_0 ; } if ( _rtB -> B_18_72_0 > _rtP -> P_129 )
{ rtb_B_1_4_0 = _rtB -> B_18_72_0 - _rtP -> P_129 ; } else if ( _rtB ->
B_18_72_0 >= _rtP -> P_128 ) { rtb_B_1_4_0 = 0.0 ; } else { rtb_B_1_4_0 =
_rtB -> B_18_72_0 - _rtP -> P_128 ; } _rtB -> B_18_180_0 = _rtP -> P_130 *
_rtB -> B_18_69_0 ; tmp = muDoubleScalarSign ( rtb_B_1_4_0 ) ; if (
muDoubleScalarIsNaN ( tmp ) ) { tmp = 0.0 ; } else { tmp = muDoubleScalarRem
( tmp , 256.0 ) ; } tmp_0 = muDoubleScalarSign ( _rtB -> B_18_180_0 ) ; if (
muDoubleScalarIsNaN ( tmp_0 ) ) { tmp_0 = 0.0 ; } else { tmp_0 =
muDoubleScalarRem ( tmp_0 , 256.0 ) ; } _rtB -> B_18_184_0 = ( ( _rtP ->
P_127 * _rtB -> B_18_72_0 != rtb_B_1_4_0 ) && ( ( tmp < 0.0 ? ( int32_T ) (
int8_T ) - ( int8_T ) ( uint8_T ) - tmp : ( int32_T ) ( int8_T ) ( uint8_T )
tmp ) == ( tmp_0 < 0.0 ? ( int32_T ) ( int8_T ) - ( int8_T ) ( uint8_T ) -
tmp_0 : ( int32_T ) ( int8_T ) ( uint8_T ) tmp_0 ) ) ) ; i = ssIsSampleHit (
S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_18_185_0 = _rtDW ->
Memory_PreviousInput_c ; } if ( _rtB -> B_18_185_0 ) { _rtB -> B_18_186_0 =
AD_Vect_low_izm_dif_modes_subsyst_rtC ( S ) -> B_18_3_0 ; } else { _rtB ->
B_18_186_0 = _rtB -> B_18_180_0 ; } _rtB -> B_18_187_0 = _rtB -> B_18_131_0 [
0 ] - _rtB -> B_18_131_0 [ 1 ] ; _rtB -> B_18_188_0 = _rtB -> B_18_187_0 *
_rtB -> B_18_36_0 [ 9 ] ; _rtB -> B_18_189_0 = _rtB -> B_18_131_0 [ 2 ] -
_rtB -> B_18_131_0 [ 1 ] ; _rtB -> B_18_190_0 = _rtB -> B_18_36_0 [ 11 ] *
_rtB -> B_18_189_0 ; _rtB -> B_18_191_0 = _rtB -> B_18_188_0 + _rtB ->
B_18_190_0 ; UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID2 (
SimStruct * S , int_T tid ) { B_AD_Vect_low_izm_dif_modes_subsyst_T * _rtB ;
P_AD_Vect_low_izm_dif_modes_subsyst_T * _rtP ;
DW_AD_Vect_low_izm_dif_modes_subsyst_T * _rtDW ; _rtDW = ( (
DW_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetRootDWork ( S ) ) ; _rtP = (
( P_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetModelRtp ( S ) ) ; _rtB = (
( B_AD_Vect_low_izm_dif_modes_subsyst_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB
-> B_18_0_0_m = _rtP -> P_131 ; _rtB -> B_18_1_0 = _rtP -> P_132 ; _rtB ->
B_18_2_0_c = _rtP -> P_133 ; _rtB -> B_18_4_0_c = _rtP -> P_135 ; _rtB ->
B_18_6_0 = _rtP -> P_137 ; _rtB -> B_18_7_0 = _rtP -> P_138 ; _rtB ->
B_1_0_0_d = _rtP -> P_7 ; _rtB -> B_1_1_0_g [ 0 ] = _rtP -> P_8 [ 0 ] ; _rtB
-> B_1_1_0_g [ 1 ] = _rtP -> P_8 [ 1 ] ; _rtB -> B_1_4_0 [ 0 ] = _rtP -> P_11
[ 0 ] ; _rtB -> B_1_4_0 [ 1 ] = _rtP -> P_11 [ 1 ] ; memcpy ( & _rtB ->
B_18_3_0_k [ 0 ] , & _rtP -> P_134 [ 0 ] , sizeof ( real_T ) << 4U ) ; memcpy
( & _rtB -> B_18_5_0_b [ 0 ] , & _rtP -> P_136 [ 0 ] , sizeof ( real_T ) <<
4U ) ; memcpy ( & _rtB -> B_1_2_0 [ 0 ] , & _rtP -> P_9 [ 0 ] , sizeof (
real_T ) << 4U ) ; memcpy ( & _rtB -> B_1_3_0_l [ 0 ] , & _rtP -> P_10 [ 0 ]
, sizeof ( real_T ) << 4U ) ; memcpy ( & _rtB -> B_1_5_0_d [ 0 ] , & _rtP ->
P_12 [ 0 ] , sizeof ( real_T ) << 4U ) ; if ( ssIsMajorTimeStep ( S ) != 0 )
{ srUpdateBC ( _rtDW -> Saturation_SubsysRanBC ) ; } _rtB -> B_18_9_0_d =
_rtP -> P_155 ; _rtB -> B_18_10_0 = _rtP -> P_156 ; _rtB -> B_18_11_0 = _rtP
-> P_157 ; _rtB -> B_18_12_0 = _rtP -> P_139 ; _rtB -> B_18_13_0_p = _rtP ->
P_140 ; _rtB -> B_18_14_0_c [ 0 ] = _rtP -> P_141 [ 0 ] ; _rtB -> B_18_14_0_c
[ 1 ] = _rtP -> P_141 [ 1 ] ; _rtB -> B_18_15_0_l = _rtP -> P_158 ; _rtB ->
B_18_16_0_o = _rtP -> P_159 ; _rtB -> B_18_17_0_b = _rtP -> P_160 ; _rtB ->
B_18_18_0_f = _rtP -> P_142 ; _rtB -> B_18_19_0_g = _rtP -> P_143 ; _rtB ->
B_18_20_0_n = _rtP -> P_161 ; _rtB -> B_18_21_0_b = _rtP -> P_162 ; _rtB ->
B_18_22_0_g = _rtP -> P_144 ; _rtB -> B_18_23_0_l = _rtP -> P_163 ; _rtB ->
B_18_24_0 = _rtP -> P_145 ; memcpy ( & _rtB -> B_8_0_0 [ 0 ] , & _rtP -> P_29
[ 0 ] , sizeof ( real_T ) << 4U ) ; _rtB -> B_8_1_0_j = _rtP -> P_30 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
sinbetacosbetasinthcosth_SubsysRanBC ) ; } _rtB -> B_9_0_0_l [ 0 ] = _rtP ->
P_34 [ 0 ] ; _rtB -> B_9_0_0_l [ 1 ] = _rtP -> P_34 [ 1 ] ; memcpy ( & _rtB
-> B_9_1_0 [ 0 ] , & _rtP -> P_35 [ 0 ] , sizeof ( real_T ) << 4U ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
sinthrcosthr_SubsysRanBC ) ; } _rtB -> B_10_0_0_p [ 0 ] = _rtP -> P_39 [ 0 ]
; _rtB -> B_10_0_0_p [ 1 ] = _rtP -> P_39 [ 1 ] ; memcpy ( & _rtB -> B_10_1_0
[ 0 ] , & _rtP -> P_40 [ 0 ] , sizeof ( real_T ) << 4U ) ; if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
sinthrcosthr1_SubsysRanBC ) ; } _rtB -> B_18_28_0_m = _rtP -> P_146 ; _rtB ->
B_18_29_0 = _rtP -> P_147 * _rtB -> B_18_28_0_m ; _rtB -> B_18_30_0 = _rtP ->
P_148 ; _rtB -> B_18_31_0 = _rtP -> P_149 ; _rtB -> B_18_33_0_n = _rtP ->
P_150 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { int32_T isHit ;
B_AD_Vect_low_izm_dif_modes_subsyst_T * _rtB ;
P_AD_Vect_low_izm_dif_modes_subsyst_T * _rtP ;
DW_AD_Vect_low_izm_dif_modes_subsyst_T * _rtDW ; _rtDW = ( (
DW_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetRootDWork ( S ) ) ; _rtP = (
( P_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetModelRtp ( S ) ) ; _rtB = (
( B_AD_Vect_low_izm_dif_modes_subsyst_T * ) _ssGetModelBlockIO ( S ) ) ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 3 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK . Head [ 0 ] = ( ( _rtDW ->
TransportDelay_IWORK . Head [ 0 ] < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize [ 0 ] - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head [ 0 ]
+ 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK . Head [ 0 ] == _rtDW ->
TransportDelay_IWORK . Tail [ 0 ] ) { if ( !
AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK . CircularBufSize [ 0 ] , & _rtDW ->
TransportDelay_IWORK . Tail [ 0 ] , & _rtDW -> TransportDelay_IWORK . Head [
0 ] , & _rtDW -> TransportDelay_IWORK . Last [ 0 ] , simTime - _rtP -> P_53 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ++ ) [ _rtDW ->
TransportDelay_IWORK . Head [ 0 ] ] = simTime ; ( * uBuffer ++ ) [ _rtDW ->
TransportDelay_IWORK . Head [ 0 ] ] = _rtB -> B_18_138_0 [ 0 ] ; _rtDW ->
TransportDelay_IWORK . Head [ 1 ] = ( ( _rtDW -> TransportDelay_IWORK . Head
[ 1 ] < ( _rtDW -> TransportDelay_IWORK . CircularBufSize [ 1 ] - 1 ) ) ? (
_rtDW -> TransportDelay_IWORK . Head [ 1 ] + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK . Head [ 1 ] == _rtDW -> TransportDelay_IWORK . Tail [ 1
] ) { if ( !
AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK . CircularBufSize [ 1 ] , & _rtDW ->
TransportDelay_IWORK . Tail [ 1 ] , & _rtDW -> TransportDelay_IWORK . Head [
1 ] , & _rtDW -> TransportDelay_IWORK . Last [ 1 ] , simTime - _rtP -> P_53 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ++ ) [ _rtDW ->
TransportDelay_IWORK . Head [ 1 ] ] = simTime ; ( * uBuffer ++ ) [ _rtDW ->
TransportDelay_IWORK . Head [ 1 ] ] = _rtB -> B_18_138_0 [ 1 ] ; _rtDW ->
TransportDelay_IWORK . Head [ 2 ] = ( ( _rtDW -> TransportDelay_IWORK . Head
[ 2 ] < ( _rtDW -> TransportDelay_IWORK . CircularBufSize [ 2 ] - 1 ) ) ? (
_rtDW -> TransportDelay_IWORK . Head [ 2 ] + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK . Head [ 2 ] == _rtDW -> TransportDelay_IWORK . Tail [ 2
] ) { if ( !
AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK . CircularBufSize [ 2 ] , & _rtDW ->
TransportDelay_IWORK . Tail [ 2 ] , & _rtDW -> TransportDelay_IWORK . Head [
2 ] , & _rtDW -> TransportDelay_IWORK . Last [ 2 ] , simTime - _rtP -> P_53 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head [ 2 ] ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head [ 2 ] ] = _rtB -> B_18_138_0 [ 2 ] ; }
ssCallAccelRunBlock ( S , 18 , 17 , SS_CALL_MDL_UPDATE ) ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_h . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_h .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK_l . Head = ( ( _rtDW -> TransportDelay_IWORK_l . Head <
( _rtDW -> TransportDelay_IWORK_l . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_l . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_l . Head == _rtDW -> TransportDelay_IWORK_l . Tail ) {
if ( ! AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayUpdateTailOrGrowBuf ( &
_rtDW -> TransportDelay_IWORK_l . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_l . Tail , & _rtDW -> TransportDelay_IWORK_l . Head , &
_rtDW -> TransportDelay_IWORK_l . Last , simTime - _rtP -> P_92 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_l . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_l . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_l . Head ] = _rtB -> B_18_75_0 ; } isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput = _rtB ->
B_18_82_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay_PWORK_l . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_h . Head = ( ( _rtDW ->
TransportDelay_IWORK_h . Head < ( _rtDW -> TransportDelay_IWORK_h .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_h . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_h . Head == _rtDW ->
TransportDelay_IWORK_h . Tail ) { if ( !
AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK_h . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_h . Tail , & _rtDW -> TransportDelay_IWORK_h . Head , &
_rtDW -> TransportDelay_IWORK_h . Last , simTime - _rtP -> P_97 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_h . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_h . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_h . Head ] = _rtB -> B_18_83_0 ; } isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput_p = _rtB ->
B_18_90_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_h5 . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK_h5 . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_f . Head = ( ( _rtDW
-> TransportDelay_IWORK_f . Head < ( _rtDW -> TransportDelay_IWORK_f .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_f . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_f . Head == _rtDW ->
TransportDelay_IWORK_f . Tail ) { if ( !
AD_Vect_low_izm_dif_modes_subsyst_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK_f . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_f . Tail , & _rtDW -> TransportDelay_IWORK_f . Head , &
_rtDW -> TransportDelay_IWORK_f . Last , simTime - _rtP -> P_102 , tBuffer ,
uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_f . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK_f . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_f . Head ] = _rtB -> B_18_91_0 ; } isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory_PreviousInput_a = _rtB ->
B_18_98_0 ; _rtDW -> Memory_PreviousInput_h = _rtB -> B_18_148_0 ; _rtDW ->
Memory_PreviousInput_l = _rtB -> B_18_160_0 ; _rtDW -> Memory_PreviousInput_k
= _rtB -> B_18_172_0 ; _rtDW -> Memory_PreviousInput_c = _rtB -> B_18_184_0 ;
} UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID2 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) {
B_AD_Vect_low_izm_dif_modes_subsyst_T * _rtB ;
P_AD_Vect_low_izm_dif_modes_subsyst_T * _rtP ;
XDot_AD_Vect_low_izm_dif_modes_subsyst_T * _rtXdot ;
DW_AD_Vect_low_izm_dif_modes_subsyst_T * _rtDW ; _rtDW = ( (
DW_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetRootDWork ( S ) ) ; _rtXdot =
( ( XDot_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetdX ( S ) ) ; _rtP = ( (
P_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_AD_Vect_low_izm_dif_modes_subsyst_T * ) _ssGetModelBlockIO ( S ) ) ;
_rtXdot -> Integrator_CSTATE [ 0 ] = _rtB -> B_18_116_0 [ 0 ] ; _rtXdot ->
Integrator_CSTATE [ 1 ] = _rtB -> B_18_116_0 [ 1 ] ; _rtXdot ->
Integrator_CSTATE [ 2 ] = _rtB -> B_18_116_0 [ 2 ] ; _rtXdot ->
Integrator_CSTATE [ 3 ] = _rtB -> B_18_116_0 [ 3 ] ; if ( _rtDW ->
Saturation_MODE ) { _rtXdot -> Integrator_CSTATE_b = _rtB -> B_1_20_0 ; }
else { ( ( XDot_AD_Vect_low_izm_dif_modes_subsyst_T * ) ssGetdX ( S ) ) ->
Integrator_CSTATE_b = 0.0 ; } _rtXdot -> Rotoranglethetam_CSTATE = _rtB ->
B_18_125_0 ; _rtXdot -> Rotorspeedwm_CSTATE = _rtB -> B_18_124_0 ; _rtXdot ->
Integrator_CSTATE_k = _rtB -> B_18_162_0 ; _rtXdot -> Integrator_CSTATE_e =
_rtB -> B_18_150_0 ; _rtXdot -> Integrator_CSTATE_m = _rtB -> B_18_174_0 ;
_rtXdot -> Integrator_CSTATE_ex = _rtB -> B_18_186_0 ; _rtXdot ->
integrator_CSTATE = _rtB -> B_18_134_0 ; _rtXdot -> integrator_CSTATE_m =
_rtB -> B_18_191_0 ; _rtXdot -> integrator_CSTATE_j = _rtB -> B_18_90_0 ; }
static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 ,
439347142U ) ; ssSetChecksumVal ( S , 1 , 559184933U ) ; ssSetChecksumVal ( S
, 2 , 3311701478U ) ; ssSetChecksumVal ( S , 3 , 3315095127U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.0" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_AD_Vect_low_izm_dif_modes_subsyst_T ) ) { ssSetErrorStatus
( S , "Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_AD_Vect_low_izm_dif_modes_subsyst_T ) ) { ssSetErrorStatus (
S , "Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_AD_Vect_low_izm_dif_modes_subsyst_T ) ) { static char msg [ 256 ] ; sprintf
( msg , "Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & AD_Vect_low_izm_dif_modes_subsyst_rtDefaultP ) ; _ssSetConstBlockIO ( S ,
& AD_Vect_low_izm_dif_modes_subsyst_rtInvariant ) ; rt_InitInfAndNaN ( sizeof
( real_T ) ) ; } static void mdlInitializeSampleTimes ( SimStruct * S ) { {
SimStruct * childS ; SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S
, 0 ) ; callSysFcns = ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [
3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 1 ) ;
callSysFcns = ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ]
= ( SysOutputFcn ) ( NULL ) ; } slAccRegPrmChangeFcn ( S , mdlOutputsTID2 ) ;
} static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
