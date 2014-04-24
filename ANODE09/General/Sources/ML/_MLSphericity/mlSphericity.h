//----------------------------------------------------------------------------------
//! The ML module class Sphericity.
/*!
// \file    
// \author  Wieke
// \date    2014-04-24
//
// 
*/
//----------------------------------------------------------------------------------


#ifndef __mlSphericity_H
#define __mlSphericity_H


// Local includes
#include "_MLSphericitySystem.h"

// ML includes
#include <mlModuleIncludes.h>

ML_START_NAMESPACE


//! 
class _MLSPHERICITY_EXPORT Sphericity : public Module
{
public:

  //! Constructor.
  Sphericity();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);

  // ----------------------------------------------------------
  //! \name Image processing methods.
  //@{
  // ----------------------------------------------------------

  //! Sets properties of the output image at output \p outputIndex.
  virtual void calculateOutputImageProperties(int outputIndex, PagedImage* outputImage);

  //! Creates the SphericityHandler for the given output image whenever calculateOutputImageProperties()
  //! is called and the outputImage is valid.
  virtual CalculateOutputImageHandler* createCalculateOutputImageHandler(PagedImage* outputImage);

private:

  // ----------------------------------------------------------
  //! \name Module field declarations
  //@{
  // ----------------------------------------------------------

  //! 
  FloatField* _thresholdFld;
  //@}

  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(Sphericity)
};


ML_END_NAMESPACE

#endif // __mlSphericity_H