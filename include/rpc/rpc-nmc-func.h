#include "rpc/rpc-nmc.h"


//--------------------------
#ifdef RPC_nmppsAbs_64s
NMC_RPC_PPI(nmppsAbs_64s);
#endif 

#ifdef RPC_nmppsAbs_32s
NMC_RPC_PPI(nmppsAbs_32s);
#endif 

#ifdef RPC_nmppsAbs_16s
NMC_RPC_PPI(nmppsAbs_16s);
#endif 

#ifdef RPC_nmppsAbs_8s
NMC_RPC_PPI(nmppsAbs_8s);
#endif 
//-------------------------
#ifdef RPC_nmppsAbs1_8s
NMC_RPC_PPI(nmppsAbs1_8s);
#endif 

#ifdef RPC_nmppsAbs1_16s
NMC_RPC_PPI(nmppsAbs1_16s);
#endif 

#ifdef RPC_nmppsAbs1_32s
NMC_RPC_PPI(nmppsAbs1_32s);
#endif 

#ifdef RPC_nmppsAbs1_64s
NMC_RPC_PPI(nmppsAbs1_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsAdd_8s
NMC_RPC_PPPI(nmppsAdd_8s);
#endif 

#ifdef RPC_nmppsAdd_16s
NMC_RPC_PPPI(nmppsAdd_16s);
#endif 

#ifdef RPC_nmppsAdd_32s
NMC_RPC_PPPI(nmppsAdd_32s);
#endif 

#ifdef RPC_nmppsAdd_64s
NMC_RPC_PPPI(nmppsAdd_64s);
#endif 
//--------------------------
#ifdef RPC_nmppsSub_8s
NMC_RPC_PPPI(nmppsSub_8s);
#endif 

#ifdef RPC_nmppsSub_16s
NMC_RPC_PPPI(nmppsSub_16s);
#endif 

#ifdef RPC_nmppsSub_32s
NMC_RPC_PPPI(nmppsSub_32s);
#endif 

#ifdef RPC_nmppsSub_64s
NMC_RPC_PPPI(nmppsSub_64s);
#endif 
//--------------------------
#ifdef RPC_nmppsAddC_8s
NMC_RPC_PIPI(nmppsAddC_8s);
#endif 

#ifdef RPC_nmppsAddC_16s
NMC_RPC_PIPI(nmppsAddC_16s);
#endif 

#ifdef RPC_nmppsAddC_32s
NMC_RPC_PIPI(nmppsAddC_32s);
#endif 

#ifdef RPC_nmppsAddC_64s
NMC_RPC_PLPI(nmppsAddC_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsSubC_8s
NMC_RPC_PIPI(nmppsSubC_8s);
#endif 

#ifdef RPC_nmppsSubC_16s
NMC_RPC_PIPI(nmppsSubC_16s);
#endif 

#ifdef RPC_nmppsSubC_32s
NMC_RPC_PIPI(nmppsSubC_32s);
#endif 

#ifdef RPC_nmppsSubC_64s
NMC_RPC_PLPI(nmppsSubC_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsSubCRev_8s
NMC_RPC_PIPI(nmppsSubCRev_8s);
#endif 

#ifdef RPC_nmppsSubCRev_16s
NMC_RPC_PIPI(nmppsSubCRev_16s);
#endif 

#ifdef RPC_nmppsSubCRev_32s
NMC_RPC_PIPI(nmppsSubCRev_32s);
#endif 

#ifdef RPC_nmppsSubCRev_64s
NMC_RPC_PLPI(nmppsSubCRev_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsRShiftC_8s
NMC_RPC_PIPI(nmppsRShiftC_8s);
#endif 

#ifdef RPC_nmppsRShiftC_16s
NMC_RPC_PIPI(nmppsRShiftC_16s);
#endif 

#ifdef RPC_nmppsRShiftC_32s
NMC_RPC_PIPI(nmppsRShiftC_32s);
#endif 

#ifdef RPC_nmppsRShiftC_64s
NMC_RPC_PIPI(nmppsRShiftC_64s);
#endif 

//--------------------------
#ifdef RPC_nmppsMin_8s7b
NMC_RPC_PIR(nmppsMin_8s7b);
#endif 

#ifdef RPC_nmppsMin_16s15b
NMC_RPC_PIR(nmppsMin_16s15b);
#endif 

#ifdef RPC_nmppsMin_32s31b
NMC_RPC_PIR(nmppsMin_32s31b);
#endif 

#ifdef RPC_nmppsMin_64s63b
NMC_RPC_PIR64(nmppsMin_64s63b);
#endif 

//--------------------------
#ifdef RPC_nmppsMax_8s7b
NMC_RPC_PIR(nmppsMax_8s7b);
#endif 

#ifdef RPC_nmppsMax_16s15b
NMC_RPC_PIR(nmppsMax_16s15b);
#endif 

#ifdef RPC_nmppsMax_32s31b
NMC_RPC_PIR(nmppsMax_32s31b);
#endif 

#ifdef RPC_nmppsMax_64s63b
NMC_RPC_PIR64(nmppsMax_64s63b);
#endif 

//--------------------------
#ifdef RPC_nmppsAndC_8u
NMC_RPC_PIPI(nmppsAndC_8u);
#endif 

#ifdef RPC_nmppsAndC_16u
NMC_RPC_PIPI(nmppsAndC_16u);
#endif 

#ifdef RPC_nmppsAndC_32u
NMC_RPC_PIPI(nmppsAndC_32u);
#endif 

#ifdef RPC_nmppsAndC_64u
NMC_RPC_PLPI(nmppsAndC_64u);
#endif
//--------------------------
#ifdef RPC_nmppsOrC_8u
NMC_RPC_PIPI(nmppsOrC_8u);
#endif 

#ifdef RPC_nmppsOrC_16u
NMC_RPC_PIPI(nmppsOrC_16u);
#endif 

#ifdef RPC_nmppsOrC_32u
NMC_RPC_PIPI(nmppsOrC_32u);
#endif 

#ifdef RPC_nmppsOrC_64u
NMC_RPC_PLPI(nmppsOrC_64u);
#endif 
//--------------------------
#ifdef RPC_nmppsXorC_8u
NMC_RPC_PIPI(nmppsXorC_8u);
#endif 

#ifdef RPC_nmppsXorC_16u
NMC_RPC_PIPI(nmppsXorC_16u);
#endif 

#ifdef RPC_nmppsXorC_32u
NMC_RPC_PIPI(nmppsXorC_32u);
#endif 

#ifdef RPC_nmppsXorC_64u
NMC_RPC_PLPI(nmppsXorC_64u);
#endif 
//--------------------------
#ifdef RPC_nmppsNot_64u
NMC_RPC_PPI(nmppsNot_64u);
#endif 

#ifdef RPC_nmppsNot_32u
NMC_RPC_PPI(nmppsNot_32u);
#endif 

#ifdef RPC_nmppsNot_16u
NMC_RPC_PPI(nmppsNot_16u);
#endif 

#ifdef RPC_nmppsNot_8u
NMC_RPC_PPI(nmppsNot_8u);
#endif 
//--------------------------
#ifdef RPC_nmppsAnd_64u
NMC_RPC_PPPI(nmppsAnd_64u);
#endif 

#ifdef RPC_nmppsAnd_32u
NMC_RPC_PPPI(nmppsAnd_32u);
#endif 

#ifdef RPC_nmppsAnd_16u
NMC_RPC_PPPI(nmppsAnd_16u);
#endif 

#ifdef RPC_nmppsAnd_8u
NMC_RPC_PPPI(nmppsAnd_8u);
#endif 
//--------------------------
#ifdef RPC_nmppsOr_64u
NMC_RPC_PPPI(nmppsOr_64u);
#endif 

#ifdef RPC_nmppsOr_32u
NMC_RPC_PPPI(nmppsOr_32u);
#endif 

#ifdef RPC_nmppsOr_16u
NMC_RPC_PPPI(nmppsOr_16u);
#endif 

#ifdef RPC_nmppsOr_8u
NMC_RPC_PPPI(nmppsOr_8u);
#endif 
//--------------------------
#ifdef RPC_nmppsXor_64u
NMC_RPC_PPPI(nmppsXor_64u);
#endif 

#ifdef RPC_nmppsXor_32u
NMC_RPC_PPPI(nmppsXor_32u);
#endif 

#ifdef RPC_nmppsXor_16u
NMC_RPC_PPPI(nmppsXor_16u);
#endif 

#ifdef RPC_nmppsXor_8u
NMC_RPC_PPPI(nmppsXor_8u);
#endif 
//--------------------------
#ifdef RPC_nmppsRShiftC_8u
NMC_RPC_PIPI(nmppsRShiftC_8u);
#endif 

#ifdef RPC_nmppsRShiftC_16u
NMC_RPC_PIPI(nmppsRShiftC_16u);
#endif 

#ifdef RPC_nmppsRShiftC_32u
NMC_RPC_PIPI(nmppsRShiftC_32u);
#endif 

#ifdef RPC_nmppsRShiftC_64u
NMC_RPC_PIPI(nmppsRShiftC_64u);
#endif 

//--------------------------
#ifdef RPC_nmppsSum_8s
NMC_RPC_PIR(nmppsSum_8s);
#endif 

#ifdef RPC_nmppsSum_16s
NMC_RPC_PIR64(nmppsSum_16s);
#endif 

#ifdef RPC_nmppsSum_32s
NMC_RPC_PIR64(nmppsSum_32s);
#endif 

#ifdef RPC_nmppsSum_64s
NMC_RPC_PIR64(nmppsSum_64s);
#endif 
//--------------------------
#ifdef RPC_nmppsCmpNe0_64s
NMC_RPC_PPI(nmppsCmpNe0_64s);
#endif 

#ifdef RPC_nmppsCmpNe0_32s
NMC_RPC_PPI(nmppsCmpNe0_32s);
#endif 

#ifdef RPC_nmppsCmpNe0_16s
NMC_RPC_PPI(nmppsCmpNe0_16s);
#endif 

#ifdef RPC_nmppsCmpNe0_8s
NMC_RPC_PPI(nmppsCmpNe0_8s);
#endif 
//--------------------------
#ifdef RPC_nmppsCmpLt0_64s
NMC_RPC_PPI(nmppsCmpLt0_64s);
#endif 

#ifdef RPC_nmppsCmpLt0_32s
NMC_RPC_PPI(nmppsCmpLt0_32s);
#endif 

#ifdef RPC_nmppsCmpLt0_16s
NMC_RPC_PPI(nmppsCmpLt0_16s);
#endif 

#ifdef RPC_nmppsCmpLt0_8s
NMC_RPC_PPI(nmppsCmpLt0_8s);
#endif 

//--------------------------
#ifdef RPC_nmppsCmpNeC_64s
NMC_RPC_PLPI(nmppsCmpNeC_64s);
#endif 

#ifdef RPC_nmppsCmpNeC_32s
NMC_RPC_PIPI(nmppsCmpNeC_32s);
#endif 

#ifdef RPC_nmppsCmpNeC_16s
NMC_RPC_PIPI(nmppsCmpNeC_16s);
#endif 

#ifdef RPC_nmppsCmpNeC_8s
NMC_RPC_PIPI(nmppsCmpNeC_8s);
#endif 
//--------------------------
//#ifdef RPC_nmppsCmpNeC_64s8u
//NMC_RPC_PLPI(nmppsCmpNeC_64s8u);
//#endif 
//
//#ifdef RPC_nmppsCmpNeC_32s8u
//NMC_RPC_PIPI(nmppsCmpNeC_32s8u);
//#endif 
//
//#ifdef RPC_nmppsCmpNeC_16s8u
//NMC_RPC_PIPI(nmppsCmpNeC_16s8u);
//#endif 
//
//#ifdef RPC_nmppsCmpNeC_8s8u
//NMC_RPC_PIPI(nmppsCmpNeC_8s8u);
//#endif 

//--------------------------
//#ifdef RPC_nmppsCmpNe_64s8um
//NMC_RPC_PPPI(nmppsCmpNe_64s8um);
//#endif 
//
//#ifdef RPC_nmppsCmpNe_32s8um
//NMC_RPC_PPPI(nmppsCmpNe_32s8um);
//#endif 
//
//#ifdef RPC_nmppsCmpNe_16s8um
//NMC_RPC_PPPI(nmppsCmpNe_16s8um);
//#endif 
//
//#ifdef RPC_nmppsCmpNe_8s8um
//NMC_RPC_PPPI(nmppsCmpNe_8s8um);
//#endif 



//--------------------------
#ifdef RPC_nmppsCmpLtC_64s
NMC_RPC_PLPI(nmppsCmpLtC_64s);
#endif 

#ifdef RPC_nmppsCmpLtC_32s
NMC_RPC_PIPI(nmppsCmpLtC_32s);
#endif 

#ifdef RPC_nmppsCmpLtC_16s
NMC_RPC_PIPI(nmppsCmpLtC_16s);
#endif 

#ifdef RPC_nmppsCmpLtC_8s
NMC_RPC_PIPI(nmppsCmpLtC_8s);
#endif 

//--------------------------
//#ifdef RPC_nmppsCmpLtC_64s8u
//NMC_RPC_PLPI(nmppsCmpLtC_64s8u); // Not supported by simulink
//#endif 
//
//#ifdef RPC_nmppsCmpLtC_32s8um
//NMC_RPC_PIPI(nmppsCmpLtC_32s8um);
//#endif 
//
//#ifdef RPC_nmppsCmpLtC_16s8um
//NMC_RPC_PIPI(nmppsCmpLtC_16s8um);
//#endif 
//
//#ifdef RPC_nmppsCmpLtC_8s8um
//NMC_RPC_PIPI(nmppsCmpLtC_8s8um);
//#endif 

//--------------------------
//#ifdef RPC_nmppsCmpLt_64s8um
//NMC_RPC_PPPI(nmppsCmpLt_64s8um);
//#endif 
//
//#ifdef RPC_nmppsCmpLt_32s8um
//NMC_RPC_PPPI(nmppsCmpLt_32s8um);
//#endif 
//
//#ifdef RPC_nmppsCmpLt_16s8um
//NMC_RPC_PPPI(nmppsCmpLt_16s8um);
//#endif 
//
//#ifdef RPC_nmppsCmpLt_8s8um
//NMC_RPC_PPPI(nmppsCmpLt_8s8um);
//#endif 



//-----------------------------

#if defined(RPC_nmppmMul_mm_8s8s) || defined(RPC_nmppmMul_mm_colmajor_8s8s)
NMC_RPC_PIIPPI(nmppmMul_mm_8s8s);
#endif 

#if defined(RPC_nmppmMul_mm_8s16s) || defined(RPC_nmppmMul_mm_colmajor_8s16s)
NMC_RPC_PIIPPI(nmppmMul_mm_8s16s);
#endif 

#if defined(RPC_nmppmMul_mm_8s32s) || defined(RPC_nmppmMul_mm_colmajor_8s32s)
NMC_RPC_PIIPPI(nmppmMul_mm_8s32s);
#endif 

#if defined(RPC_nmppmMul_mm_8s64s) || defined(RPC_nmppmMul_mm_colmajor_8s64s)
NMC_RPC_PIIPPI(nmppmMul_mm_8s64s);
#endif 

#if defined(RPC_nmppmMul_mm_16s16s) || defined(RPC_nmppmMul_mm_colmajor_16s16s)
NMC_RPC_PIIPPI(nmppmMul_mm_16s16s);
#endif 

#if defined(RPC_nmppmMul_mm_16s32s) || defined(RPC_nmppmMul_mm_colmajor_16s32s)
NMC_RPC_PIIPPI(nmppmMul_mm_16s32s);
#endif 

#if defined(RPC_nmppmMul_mm_16s64s) || defined(RPC_nmppmMul_mm_colmajor_16s64s)
NMC_RPC_PIIPPI(nmppmMul_mm_16s64s);
#endif 

#if defined(RPC_nmppmMul_mm_32s32s) || defined(RPC_nmppmMul_mm_colmajor_32s32s)
NMC_RPC_PIIPPI(nmppmMul_mm_32s32s);
#endif 

#if defined(RPC_nmppmMul_mm_32s64s) || defined(RPC_nmppmMul_mm_colmajor_32s64s)
NMC_RPC_PIIPPI(nmppmMul_mm_32s64s);
#endif 

//-----------------------------
//#ifdef     RPC_nmppsDotProd_8s8sm
//NMC_RPC_PPIR64(nmppsDotProd_8s8sm);
//#endif 
//
//#ifdef     RPC_nmppsDotProd_8s16sm
//NMC_RPC_PPIR64(nmppsDotProd_8s16sm);
//#endif 
//
//#ifdef     RPC_nmppsDotProd_8s32sm
//NMC_RPC_PPIR64(nmppsDotProd_8s32sm);
//#endif 
//
//#ifdef     RPC_nmppsDotProd_8s64s
//NMC_RPC_PPIR64(nmppsDotProd_8s64s);
//#endif 
//
//#ifdef     RPC_nmppsDotProd_16s16sm
//NMC_RPC_PPIR64(nmppsDotProd_16s16sm);
//#endif 
//
//#ifdef     RPC_nmppsDotProd_16s32sm
//NMC_RPC_PPIR64(nmppsDotProd_16s32sm);
//#endif 
//
//#ifdef     RPC_nmppsDotProd_16s64s
//NMC_RPC_PPIR64(nmppsDotProd_16s64s);
//#endif 
//
//#ifdef     RPC_nmppsDotProd_32s32sm
//NMC_RPC_PPIR64(nmppsDotProd_32s32sm);
//#endif 
//
//#ifdef     RPC_nmppsDotProd_32s64s
//NMC_RPC_PPIR64(nmppsDotProd_32s64s);
//#endif 
//
//#ifdef     RPC_nmppsDotProd_64s64s
//NMC_RPC_PPIR64(nmppsDotProd_64s64s);
//#endif 

//--------------------------
#if defined(RPC_nmppmMul_mv_8s64s) || defined(RPC_nmppmMul_mv_colmajor_8s64s) 
NMC_RPC_PPPII(nmppmMul_mv_8s64s);
#endif 

#if defined(RPC_nmppmMul_mv_16s64s) || defined(RPC_nmppmMul_mv_colmajor_16s64s) 
NMC_RPC_PPPII(nmppmMul_mv_16s64s);
#endif 

#if defined(RPC_nmppmMul_mv_32s64s) || defined(RPC_nmppmMul_mv_colmajor_32s64s) 
NMC_RPC_PPPII(nmppmMul_mv_32s64s);
#endif 
//----------------------------
#ifdef RPC_nmppsMulC_8s			
NMC_RPC_PIPI(nmppsMulC_8s		); 
#endif
#ifdef RPC_nmppsMulC_8s16s		
NMC_RPC_PIPI(nmppsMulC_8s16s	); 
#endif
#ifdef RPC_nmppsMulC_8s32s		
NMC_RPC_PIPI(nmppsMulC_8s32s	); 
#endif
#ifdef RPC_nmppsMulC_8s64s		
NMC_RPC_PLPI(nmppsMulC_8s64s	); 
#endif
#ifdef RPC_nmppsMulC_16s		
NMC_RPC_PIPI(nmppsMulC_16s		); 
#endif
#ifdef RPC_nmppsMulC_16s32s		
NMC_RPC_PIPI(nmppsMulC_16s32s	); 
#endif
#ifdef RPC_nmppsMulC_16s64s		
NMC_RPC_PLPI(nmppsMulC_16s64s	); 
#endif
#ifdef RPC_nmppsMulC_32s		
NMC_RPC_PIPI(nmppsMulC_32s		); 
#endif
#ifdef RPC_nmppsMulC_32s64s		
NMC_RPC_PLPI(nmppsMulC_32s64s	); 
#endif
#ifdef RPC_nmppsMulC_64s		
NMC_RPC_PLPI(nmppsMulC_64s		); 
#endif

