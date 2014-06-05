//----------------------------------------------------------------------------------
//! The ML module class PixelCoordinates.
/*!
// \file   
// \author  Wieke
// \date    2014-06-05
//
// 
*/
//----------------------------------------------------------------------------------

// Local includes
#include "mlPixelCoordinates.h"
#include <sstream>
#include <string>
#include <math.h>

ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(PixelCoordinates, Module);

//----------------------------------------------------------------------------------

PixelCoordinates::PixelCoordinates() : Module(1, 1)
{
  // Suppress calls of handleNotification on field changes to
  // avoid side effects during initialization phase.
  handleNotificationOff();

  // Add fields to the module and set their values.
  _OutputFld = addString("Output", "");

  // Reactivate calls of handleNotification on field changes.
  handleNotificationOn();


  // Activate inplace data buffers for output outputIndex and input inputIndex.
  // setOutputImageInplace(outputIndex, inputIndex);

  // Activate page data bypass from input inputIndex to output outputIndex.
  // Note that the module must still be able to calculate the output image.
  // setBypass(outputIndex, inputIndex);

}

//----------------------------------------------------------------------------------

void PixelCoordinates::handleNotification(Field* field)
{
  // Handle changes of module parameters and input image fields here.
  bool touchOutputs = false;
  if (isInputImageField(field))
  {
    touchOutputs = true;
  }
  else if (field == _OutputFld)
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

void PixelCoordinates::calculateOutputImageProperties(int /*outputIndex*/, PagedImage* outputImage)
{
  // Change properties of output image outputImage here whose
  // defaults are inherited from the input image 0 (if there is one).
}

//----------------------------------------------------------------------------------

SubImageBox PixelCoordinates::calculateInputSubImageBox(int inputIndex, const SubImageBox& outputSubImageBox, int outputIndex)
{
  // Return region of input image inputIndex needed to compute region
  // outSubImgBox of output image outputIndex.
  return outputSubImageBox;
}


//----------------------------------------------------------------------------------

ML_CALCULATEOUTPUTSUBIMAGE_NUM_INPUTS_1_CPP(PixelCoordinates);

template <typename T>
void PixelCoordinates::calculateOutputSubImage(TSubImage<T>* outputSubImage, int outputIndex
                                     , TSubImage<T>* inputSubImage0
                                     )
{
  const SubImageBox validOutBox = outputSubImage->getValidRegion();
  std::stringstream output;
  // Process all voxels of the valid region of the output page.
  ImageVector p;
  for (p.u=validOutBox.v1.u;  p.u<=validOutBox.v2.u;  ++p.u) {
    for (p.t=validOutBox.v1.t;  p.t<=validOutBox.v2.t;  ++p.t) {
      for (p.c=validOutBox.v1.c;  p.c<=validOutBox.v2.c;  ++p.c) {
        for (p.z=validOutBox.v1.z;  p.z<=validOutBox.v2.z;  ++p.z) {
          for (p.y=validOutBox.v1.y;  p.y<=validOutBox.v2.y;  ++p.y) {

            p.x = validOutBox.v1.x;
            // Get pointers to row starts of input and output sub-images.
            const T* inVoxel0 = inputSubImage0->getImagePointer(p);
            
            T*  outVoxel = outputSubImage->getImagePointer(p);

            const MLint rowEnd   = validOutBox.v2.x;

            // Process all row voxels.
            for (; p.x <= rowEnd;  ++p.x, ++outVoxel, ++inVoxel0)
            {
              *outVoxel = *inVoxel0;
              if (*inVoxel0> 0){
                output << round(p.x) << " " << round(p.y) << " " << round(p.z) << std::endl;
              }
            }
          }
        }
      }
    }
  }
  
  _OutputFld -> setStringValue(output.str());

}

ML_END_NAMESPACE
