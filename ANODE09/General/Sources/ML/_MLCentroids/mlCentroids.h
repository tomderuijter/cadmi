//----------------------------------------------------------------------------------
//! The ML module class Centroids.
/*!
// \file    
// \author  Wieke
// \date    2014-05-15
//
// 
*/
//----------------------------------------------------------------------------------


#ifndef __mlCentroids_H
#define __mlCentroids_H


// Local includes
#include "_MLCentroidsSystem.h"

// ML includes
#include <mlModuleIncludes.h>

ML_START_NAMESPACE


//! 
class _MLCENTROIDS_EXPORT Centroids : public Module
{
public:

  //! Constructor.
  Centroids();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);

  // ----------------------------------------------------------
  //! \name Image processing methods.
  //@{
  // ----------------------------------------------------------

  //! Sets properties of the output image at output \p outputIndex.
  virtual void calculateOutputImageProperties(int outputIndex, PagedImage* outputImage);

  //! Creates the CentroidsHandler for the given output image whenever calculateOutputImageProperties()
  //! is called and the outputImage is valid.
  virtual CalculateOutputImageHandler* createCalculateOutputImageHandler(PagedImage* outputImage);

private:


  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(Centroids)
};


ML_END_NAMESPACE

#endif // __mlCentroids_H