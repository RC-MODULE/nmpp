#include "nmpp.h"
#include "nmpli.h"

#ifdef __cplusplus
		extern "C" {
#endif


 //! \defgroup funcs Функции деинтерлейсинга
 //! \ingroup nmppcGroup
 //! \{
	//! Функция разделяет кадр на два полукадра.
	//! \param pSrcImg указатель на исходный кадр.
	//! \param nSrcWidth ширина исходного кадра в пикселях.
	//! \param nSrcHeight высота исходого кадра в пикселях.
	//! \param pDstEven указатель на буфер четного полукадра
	//! \param pDstOdd указатель на буфер нечетного полукадра
	//! \return \e void
void nmppiDeinterlaceSplit(nm8u* pSrcImg, int nSrcWidth, int nSrcHeight, nm8u* pDstEven, nm8u* pDstOdd);

	//! Функция объединяет два полукдра в один полный кадр.
	//! \param pSrcEven указатель на четный полукадр.
	//! \param nSrcOdd указатель на нечетный полукадр.
	//! \param nSrcWidth ширина исходых полукадров в пикселях.
	//! \param pSrcHeight высота исходых полукадров в пикселях.
	//! \param pDst указатель на буфер результирующего кадр
	//! \return \e void
void nmppiDeinterlaceBlend(nm8u* pSrcEven, nm8u* pSrcOdd, int nSrcWidth, int nSrcHeight, nm8u* pDst);

//! \}

#ifdef __cplusplus
	};
#endif
