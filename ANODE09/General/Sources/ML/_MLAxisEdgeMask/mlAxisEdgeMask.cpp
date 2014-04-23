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

// Local includes
#include "mlAxisEdgeMask.h"

#include "mlAxisEdgeMaskOutputImageHandler.h"

ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(AxisEdgeMask, Module);

//----------------------------------------------------------------------------------

AxisEdgeMask::AxisEdgeMask() : Module(1, 1)
{
  // Suppress calls of handleNotification on field changes to
  // avoid side effects during initialization phase.
  handleNotificationOff();

  // Add fields to the module and set their values.
  _frontFld = addBool("front", false);
  _backFld = addBool("back", false);
  _rightFld = addBool("right", false);
  _leftFld = addBool("left", false);
  _topFld = addBool("top", false);
  _bottomFld = addBool("bottom", false);

  // Reactivate calls of handleNotification on field changes.
  handleNotificationOn();


  // Activate inplace data buffers for output outputIndex and input inputIndex.
  // setOutputImageInplace(outputIndex, inputIndex);

  // Activate page data bypass from input inputIndex to output outputIndex.
  // Note that the module must still be able to calculate the output image.
  // setBypass(outputIndex, inputIndex);

}

//----------------------------------------------------------------------------------

void AxisEdgeMask::handleNotification(Field* field)
{
  // Handle changes of module parameters and input image fields here.
  bool touchOutputs = false;
  if (isInputImageField(field))
  {
    touchOutputs = true;
  }
  else if (field == _frontFld)
  {
    touchOutputs = true;
  }
  else if (field == _backFld)
  {
    touchOutputs = true;
  }
  else if (field == _rightFld)
  {
    touchOutputs = true;
  }
  else if (field == _leftFld)
  {
    touchOutputs = true;
  }
  else if (field == _topFld)
  {
    touchOutputs = true;
  }
  else if (field == _bottomFld)
  {
    touchOutputs = true;
  }

  if (touchOutputs) 
  {
    // Touch all output image fields to notify connected modules.
    touchOutputImageFields();
  }
}

//----------------------------------------------------------------------------------

void AxisEdgeMask::calculateOutputImageProperties(int /*outputIndex*/, PagedImage* outputImage)
{
  // Setup data types and read-only flags of output image and input sub-images.
  AxisEdgeMaskOutputImageHandler::setupKnownProperties(outputImage);

  // Change properties of output image outputImage here whose
  // defaults are inherited from the input image 0 (if there is one).

  // Verify if the input/output data types are supported by our handler.
  // This will invalidate the output image if the type combination is not supported by the handler.
  AxisEdgeMaskOutputImageHandler::verifyProperties(outputImage);
}

//----------------------------------------------------------------------------------

CalculateOutputImageHandler* AxisEdgeMask::createCalculateOutputImageHandler(PagedImage* outputImage)
{
  AxisEdgeMaskOutputImageHandler::Parameters processingParameters;
  processingParameters.front = this->_frontFld->getBoolValue();
  processingParameters.back = this->_backFld->getBoolValue();
  processingParameters.right = this->_rightFld->getBoolValue();
  processingParameters.left = this->_leftFld->getBoolValue();
  processingParameters.top = this->_topFld->getBoolValue();
  processingParameters.bottom = this->_bottomFld->getBoolValue();
  return new AxisEdgeMaskOutputImageHandler(outputImage->getOutputIndex(), processingParameters);  
}

ML_END_NAMESPACE