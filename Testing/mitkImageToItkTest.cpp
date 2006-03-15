/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile$
Language:  C++
Date:      $Date$
Version:   $Revision$

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#include "mitkImage.h"
#include "mitkImageAccessByItk.h"

#include <fstream>
int mitkImageToItkTest(int argc, char* argv[])
{
	//Create Image out of nowhere
	mitk::Image::Pointer imgMem;
	mitk::PixelType pt(typeid(int));
	unsigned int dim[]={100,100,20};

  std::cout << "Testing creation of Image: ";
	imgMem=mitk::Image::New();
  if(imgMem.IsNull())
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  // geometry information for image
  mitk::Point3D origin;
  mitk::Vector3D right, bottom;
  mitk::Vector3D spacing;
  mitk::FillVector3D(origin, 17.0, 19.92, 7.83);
  mitk::FillVector3D(right, 1.0, 2.0, 3.0);
  mitk::FillVector3D(bottom, 0.0, -3.0, 2.0);
  mitk::FillVector3D(spacing, 0.78, 0.91, 2.23);

  std::cout << "Testing InitializeStandardPlane(rightVector, downVector, spacing): " << std::flush;
  mitk::PlaneGeometry::Pointer planegeometry = mitk::PlaneGeometry::New();
  planegeometry->InitializeStandardPlane(100, 100, right, bottom, &spacing);
  planegeometry->SetOrigin(origin);
  std::cout << "done" << std::endl;

  std::cout << "Testing Initialize(const mitk::PixelType& type, int sDim, const mitk::PlaneGeometry& geometry) and GetData(): ";
  imgMem->Initialize(mitk::PixelType(typeid(int)), 40, *planegeometry); //XXXXXXXXXXXXXXXXXXXXXCHANGE!
  int *p = (int*)imgMem->GetData();
  if(p==NULL)
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  std::cout << "Testing mitk::CastToItkImage: " << std::flush;
  typedef itk::Image<float,3> ImageType;
  ImageType::Pointer itkImage;
  mitk::CastToItkImage( imgMem, itkImage );
  std::cout<<"[PASSED]"<<std::endl;

  std::cout << "Testing mitk::CastToMitkImage: " << std::flush;
  mitk::Image::Pointer mitkImage = mitk::Image::New();
  mitk::CastToMitkImage( itkImage, mitkImage );
  std::cout<<"[PASSED]"<<std::endl;

  std::cout << "Testing transfer of GetGeometry()->GetOrigin(): " << std::flush;
  if(mitk::Equal(imgMem->GetGeometry()->GetOrigin(), mitkImage->GetGeometry()->GetOrigin()) == false)
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  std::cout << "Testing transfer of GetGeometry()->GetSpacing(): " << std::flush;
  if(mitk::Equal(imgMem->GetGeometry()->GetSpacing(), mitkImage->GetGeometry()->GetSpacing()) == false)
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  int i;
  for(i=0; i<3; ++i)
  {
    std::cout << "Testing transfer of GetGeometry()->GetAxisVector(" << i << "): " << std::flush;
    if(mitk::Equal(imgMem->GetGeometry()->GetAxisVector(i), mitkImage->GetGeometry()->GetAxisVector(i)) == false)
    {
      std::cout<<"[FAILED]"<<std::endl;
      return EXIT_FAILURE;
    }
    std::cout<<"[PASSED]"<<std::endl;
  }

  std::cout<<"[TEST DONE]"<<std::endl;
  return EXIT_SUCCESS;
}
