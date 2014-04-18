//----------------------------------------------------------------------------------
//! The ML module class FrontBackMask.
/*!
// \file    
// \author     wieke
// \date    2014-04-18
//
// 
*/
//----------------------------------------------------------------------------------


#ifndef __mlFrontBackMask_H
#define __mlFrontBackMask_H


// Local includes
#include "_MLFrontBackMaskSystem.h"

// ML includes
#include <mlModuleIncludes.h>

ML_START_NAMESPACE


//! 
class _MLFRONTBACKMASK_EXPORT FrontBackMask : public Module
{
public:

  //! Constructor.
  FrontBackMask();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);

  // ----------------------------------------------------------
  //! \name Image processing methods.
  //@{
  // ----------------------------------------------------------

  //! Sets properties of the output image at output \p outputIndex.
  virtual void calculateOutputImageProperties(int outputIndex, PagedImage* outputImage);

  //! Creates the FrontBackMaskHandler for the given output image whenever calculateOutputImageProperties()
  //! is called and the outputImage is valid.
  virtual CalculateOutputImageHandler* createCalculateOutputImageHandler(PagedImage* outputImage);

private:


  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(FrontBackMask)
};


ML_END_NAMESPACE

#endif // __mlFrontBackMask_H