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

// Local includes
#include "mlSphericity.h"

#include "mlSphericityOutputImageHandler.h"

ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(Sphericity, Module);

//----------------------------------------------------------------------------------

Sphericity::Sphericity() : Module(2, 1)
{
  // Suppress calls of handleNotification on field changes to
  // avoid side effects during initialization phase.
  handleNotificationOff();

  // Add fields to the module and set their values.
  _thresholdFld = addFloat("threshold", 0);

  // Reactivate calls of handleNotification on field changes.
  handleNotificationOn();


  // Activate inplace data buffers for output outputIndex and input inputIndex.
  // setOutputImageInplace(outputIndex, inputIndex);

  // Activate page data bypass from input inputIndex to output outputIndex.
  // Note that the module must still be able to calculate the output image.
  // setBypass(outputIndex, inputIndex);

}

//----------------------------------------------------------------------------------

void Sphericity::handleNotification(Field* field)
{
  // Handle changes of module parameters and input image fields here.
  bool touchOutputs = false;
  if (isInputImageField(field))
  {
    touchOutputs = true;
  }
  else if (field == _thresholdFld)
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

void Sphericity::calculateOutputImageProperties(int /*outputIndex*/, PagedImage* outputImage)
{
  // Setup data types and read-only flags of output image and input sub-images.
  SphericityOutputImageHandler::setupKnownProperties(outputImage);

  // Change properties of output image outputImage here whose
  // defaults are inherited from the input image 0 (if there is one).

  // Verify if the input/output data types are supported by our handler.
  // This will invalidate the output image if the type combination is not supported by the handler.
  SphericityOutputImageHandler::verifyProperties(outputImage);
}

//----------------------------------------------------------------------------------

CalculateOutputImageHandler* Sphericity::createCalculateOutputImageHandler(PagedImage* outputImage)
{
  SphericityOutputImageHandler::Parameters processingParameters;
  processingParameters.threshold = this->_thresholdFld->getFloatValue();
  return new SphericityOutputImageHandler(outputImage->getOutputIndex(), processingParameters);  
}

ML_END_NAMESPACE