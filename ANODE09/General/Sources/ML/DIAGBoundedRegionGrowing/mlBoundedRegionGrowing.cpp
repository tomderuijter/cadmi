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

// Local includes
#include "mlBoundedRegionGrowing.h"

#include "mlBoundedRegionGrowingOutputImageHandler.h"

ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(BoundedRegionGrowing, Module);

//----------------------------------------------------------------------------------

BoundedRegionGrowing::BoundedRegionGrowing() : Module(2, 1)
{
  // Suppress calls of handleNotification on field changes to
  // avoid side effects during initialization phase.
  handleNotificationOff();

  // Add fields to the module and set their values.
  _lowerBoundFld = addInt("lowerBound", -1000);
  _upperBoundFld = addInt("upperBound", 500);
  _relUpperThresholdFld = addInt("relUpperThreshold", 10);
  _relLowerThresholdFld = addInt("relLowerThreshold", 10);

  // Reactivate calls of handleNotification on field changes.
  handleNotificationOn();


  // Activate inplace data buffers for output outputIndex and input inputIndex.
  // setOutputImageInplace(outputIndex, inputIndex);

  // Activate page data bypass from input inputIndex to output outputIndex.
  // Note that the module must still be able to calculate the output image.
  // setBypass(outputIndex, inputIndex);

}

//----------------------------------------------------------------------------------

void BoundedRegionGrowing::handleNotification(Field* field)
{
  // Handle changes of module parameters and input image fields here.
  bool touchOutputs = false;
  if (isInputImageField(field))
  {
    touchOutputs = true;
  }
  else if (field == _lowerBoundFld)
  {
    touchOutputs = true;
  }
  else if (field == _upperBoundFld)
  {
    touchOutputs = true;
  }
  else if (field == _relUpperThresholdFld)
  {
    touchOutputs = true;
  }
  else if (field == _relLowerThresholdFld)
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

void BoundedRegionGrowing::calculateOutputImageProperties(int /*outputIndex*/, PagedImage* outputImage)
{
  // Setup data types and read-only flags of output image and input sub-images.
  BoundedRegionGrowingOutputImageHandler::setupKnownProperties(outputImage);

  // Change properties of output image outputImage here whose
  // defaults are inherited from the input image 0 (if there is one).

  // Verify if the input/output data types are supported by our handler.
  // This will invalidate the output image if the type combination is not supported by the handler.
  BoundedRegionGrowingOutputImageHandler::verifyProperties(outputImage);
}

//----------------------------------------------------------------------------------

CalculateOutputImageHandler* BoundedRegionGrowing::createCalculateOutputImageHandler(PagedImage* outputImage)
{
  BoundedRegionGrowingOutputImageHandler::Parameters processingParameters;
  processingParameters.lowerBound = this->_lowerBoundFld->getIntValue();
  processingParameters.upperBound = this->_upperBoundFld->getIntValue();
  processingParameters.relUpperThreshold = this->_relUpperThresholdFld->getIntValue();
  processingParameters.relLowerThreshold = this->_relLowerThresholdFld->getIntValue();
  return new BoundedRegionGrowingOutputImageHandler(outputImage->getOutputIndex(), processingParameters);  
}

ML_END_NAMESPACE