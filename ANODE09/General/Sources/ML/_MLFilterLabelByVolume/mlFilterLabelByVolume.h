//----------------------------------------------------------------------------------
//! The ML module class FilterLabelByVolume.
/*!
// \file    
// \author     wieke
// \date    2014-05-08
//
// 
*/
//----------------------------------------------------------------------------------


#ifndef __mlFilterLabelByVolume_H
#define __mlFilterLabelByVolume_H


// Local includes
#include "_MLFilterLabelByVolumeSystem.h"

// ML includes
#include <mlModuleIncludes.h>

ML_START_NAMESPACE


//! 
class _MLFILTERLABELBYVOLUME_EXPORT FilterLabelByVolume : public Module
{
public:

  //! Constructor.
  FilterLabelByVolume();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);

  // ----------------------------------------------------------
  //! \name Image processing methods.
  //@{
  // ----------------------------------------------------------

  //! Sets properties of the output image at output \p outputIndex.
  virtual void calculateOutputImageProperties(int outputIndex, PagedImage* outputImage);

  //! Creates the FilterLabelByVolumeHandler for the given output image whenever calculateOutputImageProperties()
  //! is called and the outputImage is valid.
  virtual CalculateOutputImageHandler* createCalculateOutputImageHandler(PagedImage* outputImage);

private:

  // ----------------------------------------------------------
  //! \name Module field declarations
  //@{
  // ----------------------------------------------------------

  //! Threshold (in voxels)
  IntField* _thresholdFld;
  //@}

  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(FilterLabelByVolume)
};


ML_END_NAMESPACE

#endif // __mlFilterLabelByVolume_H