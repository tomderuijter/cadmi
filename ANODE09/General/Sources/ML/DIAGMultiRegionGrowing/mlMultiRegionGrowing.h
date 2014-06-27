//----------------------------------------------------------------------------------
//! The ML module class MultiRegionGrowing.
/*!
// \file    
// \author  Wieke
// \date    2014-06-27
//
// 
*/
//----------------------------------------------------------------------------------


#ifndef __mlMultiRegionGrowing_H
#define __mlMultiRegionGrowing_H


// Local includes
#include "DIAGMultiRegionGrowingSystem.h"

// ML includes
#include <mlModuleIncludes.h>

ML_START_NAMESPACE


//! 
class DIAGMULTIREGIONGROWING_EXPORT MultiRegionGrowing : public Module
{
public:

  //! Constructor.
  MultiRegionGrowing();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);

  // ----------------------------------------------------------
  //! \name Image processing methods.
  //@{
  // ----------------------------------------------------------

  //! Sets properties of the output image at output \p outputIndex.
  virtual void calculateOutputImageProperties(int outputIndex, PagedImage* outputImage);

  //! Creates the MultiRegionGrowingHandler for the given output image whenever calculateOutputImageProperties()
  //! is called and the outputImage is valid.
  virtual CalculateOutputImageHandler* createCalculateOutputImageHandler(PagedImage* outputImage);

private:

  // ----------------------------------------------------------
  //! \name Module field declarations
  //@{
  // ----------------------------------------------------------

  //! Tolerance
  FloatField* _toleranceFld;
  //@}

  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(MultiRegionGrowing)
};


ML_END_NAMESPACE

#endif // __mlMultiRegionGrowing_H