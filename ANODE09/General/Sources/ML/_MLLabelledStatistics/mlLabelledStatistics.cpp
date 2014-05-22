//----------------------------------------------------------------------------------
//! The ML module class LabelledStatistics.
/*!
// \file   
// \author  Wieke
// \date    2014-05-16
//
// 
*/
//----------------------------------------------------------------------------------

// Local includes
#include "mlLabelledStatistics.h"
#include <sstream>
#include <string>
#include <limits>
#include <math.h>       /* pow */

ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(LabelledStatistics, Module);

//----------------------------------------------------------------------------------

LabelledStatistics::LabelledStatistics() : Module(2, 1)
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

void LabelledStatistics::handleNotification(Field* field)
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

void LabelledStatistics::calculateOutputImageProperties(int /*outputIndex*/, PagedImage* outputImage)
{
  // Change properties of output image outputImage here whose
  // defaults are inherited from the input image 0 (if there is one).
}

//----------------------------------------------------------------------------------

SubImageBox LabelledStatistics::calculateInputSubImageBox(int inputIndex, const SubImageBox& outputSubImageBox, int outputIndex)
{
  // Return region of input image inputIndex needed to compute region
  // outSubImgBox of output image outputIndex.
  return outputSubImageBox;
}


//----------------------------------------------------------------------------------

ML_CALCULATEOUTPUTSUBIMAGE_NUM_INPUTS_2_CPP(LabelledStatistics);

template <typename T>
void LabelledStatistics::calculateOutputSubImage(TSubImage<T>* outputSubImage, int outputIndex
                                     , TSubImage<T>* inputSubImage0
                                     , TSubImage<T>* inputSubImage1
                                     )
{
  // Compute sub-image of output image outputIndex from input sub-images.

  // Clamp box of output image against image extent to avoid that unused areas are processed.
  const SubImageBox validOutBox = outputSubImage->getValidRegion();

  T min;
  T max;
  
  inputSubImage0 -> calculateMinMax(min, max, NULL);
  const int nrCandidates = (int) max;
  std::vector<std::vector<float> > values(nrCandidates);
  
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
            const T* inVoxel1 = inputSubImage1->getImagePointer(p);

            T*  outVoxel = outputSubImage->getImagePointer(p);

            const MLint rowEnd   = validOutBox.v2.x;

            // Process all row voxels.
            for (; p.x <= rowEnd;  ++p.x, ++outVoxel, ++inVoxel0, ++inVoxel1)
            {
              *outVoxel = *inVoxel0;
              if (*inVoxel0 > 0){
                values[(int)*inVoxel0 -1].push_back((float)(*inVoxel1));
              }
            }
          }
        }
      }
    }
  }
  
  std::stringstream output;
  
  for (int i = 0; i < (int)max; i++){
    std::sort (values[i].begin(), values[i].end());
    
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::max() * -1;
    float average = 0;
    float median = (float) values[i][(int)(values[i].size()/2)];
    
    for (int k = 0; k < values[i].size(); k++){

      if (values[i][k] < min){
        min = values[i][k];
      }
      if (values[i][k] > max){
        max = values[i][k];
      }
      average += values[i][k];
    }
    
    average = average / values[i].size();
    
    float stdev = 0;
    
    for (int k = 0; k < values[i].size(); k++){
      stdev += std::pow(values[i][k] - average, 2);
    }   
    stdev = std::pow(stdev/values[i].size(),0.5f);
    
    output << average << ",";
    output << median << ",";
    output << stdev << ","; 
    output << min << ","; 
    output << max << ","; 
    output << std::endl;
  }
  _OutputFld -> setStringValue(output.str());
}

ML_END_NAMESPACE
