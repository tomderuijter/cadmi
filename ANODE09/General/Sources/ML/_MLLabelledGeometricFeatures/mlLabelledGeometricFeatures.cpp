//----------------------------------------------------------------------------------
//! The ML module class LabelledGeometricFeatures.
/*!
// \file   
// \author     wieke
// \date    2014-05-21
//
// 
*/
//----------------------------------------------------------------------------------

// Local includes
#include "mlLabelledGeometricFeatures.h"
#include <sstream>
#include <string>
#include <limits>
#include <math.h> 

ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(LabelledGeometricFeatures, Module);

//----------------------------------------------------------------------------------

LabelledGeometricFeatures::LabelledGeometricFeatures() : Module(1, 1)
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

void LabelledGeometricFeatures::handleNotification(Field* field)
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

void LabelledGeometricFeatures::calculateOutputImageProperties(int /*outputIndex*/, PagedImage* outputImage)
{
  // Change properties of output image outputImage here whose
  // defaults are inherited from the input image 0 (if there is one).
}

//----------------------------------------------------------------------------------

SubImageBox LabelledGeometricFeatures::calculateInputSubImageBox(int inputIndex, const SubImageBox& outputSubImageBox, int outputIndex)
{
  // Return region of input image inputIndex needed to compute region
  // outSubImgBox of output image outputIndex.
  return outputSubImageBox;
}


//----------------------------------------------------------------------------------

ML_CALCULATEOUTPUTSUBIMAGE_NUM_INPUTS_1_CPP(LabelledGeometricFeatures);

template <typename T>
void LabelledGeometricFeatures::calculateOutputSubImage(TSubImage<T>* outputSubImage, int outputIndex
                                     , TSubImage<T>* inputSubImage0
                                     )
{
  // Compute sub-image of output image outputIndex from input sub-images.
  // Clamp box of output image against image extent to avoid that unused areas are processed.
  const SubImageBox validOutBox = outputSubImage->getValidRegion();

  T min;
  T max;
  
  inputSubImage0 -> calculateMinMax(min, max, NULL);
  
  std::vector<float> volume((int)max,1.0);
  std::vector<float> surface((int)max,1.0);
  
  std::vector<int> minX((int)max,std::numeric_limits<int>::max());
  std::vector<int> maxX((int)max,std::numeric_limits<int>::max()*-1);
  
  std::vector<int> minY((int)max,std::numeric_limits<int>::max());
  std::vector<int> maxY((int)max,std::numeric_limits<int>::max()*-1);
  
  std::vector<int> minZ((int)max,std::numeric_limits<int>::max());
  std::vector<int> maxZ((int)max,std::numeric_limits<int>::max()*-1);
  
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
              
            	if (isSurfaceVoxel(inputSubImage0, p, *inVoxel0)){
	              *outVoxel = *inVoxel0;
	              
	              if ((int)(*inVoxel0) > 0)
		              surface[(int)(*inVoxel0)-1] += 1.0;
		              
            	} else
	            	*outVoxel = 0;
	            
	            if ((int)(*inVoxel0) > 0){
		            volume[(int)(*inVoxel0)-1] += 1.0;
		            
		            if (p.x < minX[(int)(*inVoxel0) -1])
		            	minX[(int)(*inVoxel0) -1] = p.x;
		            	
		            if (p.x > maxX[(int)(*inVoxel0) -1])
		            	maxX[(int)(*inVoxel0) -1] = p.x;
		            	
		            if (p.y < minY[(int)(*inVoxel0) -1])
		            	minY[(int)(*inVoxel0) -1] = p.y;
		            	
		            if (p.y > maxY[(int)(*inVoxel0) -1])
		            	maxY[(int)(*inVoxel0) -1] = p.y;
		            	
		            if (p.z < minZ[(int)(*inVoxel0) -1])
		            	minZ[(int)(*inVoxel0) -1] = p.z;
		            	
		            if (p.z > maxZ[(int)(*inVoxel0) -1])
		            	maxZ[(int)(*inVoxel0) -1] = p.z;		            			           
		          }
            }
          }
        }
      }
    }
  }
 
	std::stringstream output;

  for (int i = 0; i < (int)max; i++){
    float vol = volume[i];
    float sur = surface[i];
    
		float x = maxX[i] - minX[i] + 1;
 		float y = maxY[i] - minY[i] + 1;
  	float z = maxZ[i] - minZ[i] + 1;
  	
		float minDim = std::min(x,std::min(y,z));
		float maxDim = std::max(x,std::max(y,z));
		float medDim = x + y + z - minDim - maxDim;
		
		
		float ratio1 = maxDim/minDim;
		float ratio2 = maxDim/medDim;
  
  	float compactness1 = vol / (x*y*z);
  	float compactness2 = vol / std::pow(maxDim,3);
  	
  	// Stiekem is dit sphericity.
  	float compactness3 = std::pow(M_PI,1.0/6.0)* std::pow(6*vol, 2.0/3.0) / sur;

    output << vol << ",";
    output << sur << ",";
    output << minDim << ",";
    output << maxDim << ",";
    output << ratio1 << ",";
    output << ratio2 << ",";
    output << compactness1 << ",";
    output << compactness2 << ",";
    output << compactness3 << ",";
    output << std::endl;
  }
  _OutputFld -> setStringValue(output.str());
}

template <typename T>
bool LabelledGeometricFeatures::isSurfaceVoxel(TSubImage<T>* inputSubImage0, ImageVector p, int label){
	
	p.x = p.x + 1;
	T* inVoxel0 = inputSubImage0->getImagePointer(p);
	if ((int)(*inVoxel0) != label)
		return true;
		
	p.x = p.x - 2;
	inVoxel0 = inputSubImage0->getImagePointer(p);
	if ((int)(*inVoxel0) != label)
		return true;
	p.x = p.x + 1;
	
	p.y = p.y + 1;
	inVoxel0 = inputSubImage0->getImagePointer(p);
	if ((int)(*inVoxel0) != label)
		return true;
		
	p.y = p.y - 2;
	inVoxel0 = inputSubImage0->getImagePointer(p);
	if ((int)(*inVoxel0) != label)
		return true;
	p.y = p.y + 1;

	p.z = p.z + 1;
	inVoxel0 = inputSubImage0->getImagePointer(p);
	if ((int)(*inVoxel0) != label)
		return true;
		
	p.z = p.z - 2;
	inVoxel0 = inputSubImage0->getImagePointer(p);
	if ((int)(*inVoxel0) != label)
		return true;
	p.z = p.z + 1;
	
	return false;
}

ML_END_NAMESPACE
