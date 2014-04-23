//----------------------------------------------------------------------------------
//! The ML module class AxisEdgeMask.
/*!
// \file    
// \author     wieke
// \date    2014-04-23
//
// 
*/
//----------------------------------------------------------------------------------


#ifndef __mlAxisEdgeMask_H
#define __mlAxisEdgeMask_H


// Local includes
#include "_MLAxisEdgeMaskSystem.h"

// ML includes
#include <mlModuleIncludes.h>

ML_START_NAMESPACE


//! 
class _MLAXISEDGEMASK_EXPORT AxisEdgeMask : public Module
{
public:

  //! Constructor.
  AxisEdgeMask();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);

  // ----------------------------------------------------------
  //! \name Image processing methods.
  //@{
  // ----------------------------------------------------------

  //! Sets properties of the output image at output \p outputIndex.
  virtual void calculateOutputImageProperties(int outputIndex, PagedImage* outputImage);

  //! Creates the AxisEdgeMaskHandler for the given output image whenever calculateOutputImageProperties()
  //! is called and the outputImage is valid.
  virtual CalculateOutputImageHandler* createCalculateOutputImageHandler(PagedImage* outputImage);

private:

  // ----------------------------------------------------------
  //! \name Module field declarations
  //@{
  // ----------------------------------------------------------

  //! 
  BoolField* _frontFld;
  //! 
  BoolField* _backFld;
  //! 
  BoolField* _rightFld;
  //! 
  BoolField* _leftFld;
  //! 
  BoolField* _topFld;
  //! 
  BoolField* _bottomFld;
  //@}

  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(AxisEdgeMask)
};


ML_END_NAMESPACE

#endif // __mlAxisEdgeMask_H