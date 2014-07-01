//----------------------------------------------------------------------------------
//! The ML module class MultiRegionGrowing.
/*!
// \file   
// \author     wieke
// \date    2014-07-01
//
// 
*/
//----------------------------------------------------------------------------------

// Local includes
#include "mlMultiRegionGrowing.h"

#include "mlMultiRegionGrowingOutputImageHandler.h"

ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(MultiRegionGrowing, Module);

//----------------------------------------------------------------------------------

MultiRegionGrowing::MultiRegionGrowing() : Module(2, 1)
{
  // Suppress calls of handleNotification on field changes to
  // avoid side effects during initialization phase.
  handleNotificationOff();

  // Add fields to the module and set their values.
  _toleranceFld = addFloat("tolerance", 0.1);
  _sizeFld = addInt("size", 30);

  // Reactivate calls of handleNotification on field changes.
  handleNotificationOn();


  // Activate inplace data buffers for output outputIndex and input inputIndex.
  // setOutputImageInplace(outputIndex, inputIndex);

  // Activate page data bypass from input inputIndex to output outputIndex.
  // Note that the module must still be able to calculate the output image.
  // setBypass(outputIndex, inputIndex);

}

//----------------------------------------------------------------------------------

void MultiRegionGrowing::handleNotification(Field* field)
{
  // Handle changes of module parameters and input image fields here.
  bool touchOutputs = false;
  if (isInputImageField(field))
  {
    touchOutputs = true;
  }
  else if (field == _toleranceFld)
  {
    touchOutputs = true;
  }
  else if (field == _sizeFld)
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

void MultiRegionGrowing::calculateOutputImageProperties(int /*outputIndex*/, PagedImage* outputImage)
{
  // Setup data types and read-only flags of output image and input sub-images.
  MultiRegionGrowingOutputImageHandler::setupKnownProperties(outputImage);

  // Change properties of output image outputImage here whose
  // defaults are inherited from the input image 0 (if there is one).

  // Verify if the input/output data types are supported by our handler.
  // This will invalidate the output image if the type combination is not supported by the handler.
  MultiRegionGrowingOutputImageHandler::verifyProperties(outputImage);
}

//----------------------------------------------------------------------------------

CalculateOutputImageHandler* MultiRegionGrowing::createCalculateOutputImageHandler(PagedImage* outputImage)
{
  MultiRegionGrowingOutputImageHandler::Parameters processingParameters;
  processingParameters.tolerance = this->_toleranceFld->getFloatValue();
  processingParameters.size = this->_sizeFld->getIntValue();
  return new MultiRegionGrowingOutputImageHandler(outputImage->getOutputIndex(), processingParameters);  
}

ML_END_NAMESPACE