//----------------------------------------------------------------------------------
//! The ML module class BoundedRegionGrowing.
/*!
// \file    
// \author  Wieke
// \date    2014-05-23
//
// 
*/
//----------------------------------------------------------------------------------


#ifndef __mlBoundedRegionGrowing_H
#define __mlBoundedRegionGrowing_H


// Local includes
#include "DIAGBoundedRegionGrowingSystem.h"

// ML includes
#include <mlModuleIncludes.h>

ML_START_NAMESPACE


//! 
class DIAGBOUNDEDREGIONGROWING_EXPORT BoundedRegionGrowing : public Module
{
public:

  //! Constructor.
  BoundedRegionGrowing();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);

  // ----------------------------------------------------------
  //! \name Image processing methods.
  //@{
  // ----------------------------------------------------------

  //! Sets properties of the output image at output \p outputIndex.
  virtual void calculateOutputImageProperties(int outputIndex, PagedImage* outputImage);

  //! Creates the BoundedRegionGrowingHandler for the given output image whenever calculateOutputImageProperties()
  //! is called and the outputImage is valid.
  virtual CalculateOutputImageHandler* createCalculateOutputImageHandler(PagedImage* outputImage);

private:

  // ----------------------------------------------------------
  //! \name Module field declarations
  //@{
  // ----------------------------------------------------------

  //! Lower Bound
  IntField* _lowerBoundFld;
  //! Upper Bound
  IntField* _upperBoundFld;
  //! Relative Upper Threshold
  IntField* _relUpperThresholdFld;
  //! Relative Lower Threshold
  IntField* _relLowerThresholdFld;
  //@}

  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(BoundedRegionGrowing)
};


ML_END_NAMESPACE

#endif // __mlBoundedRegionGrowing_H