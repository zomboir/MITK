/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date: 2008-02-25 17:27:17 +0100 (Mo, 25 Feb 2008) $
Version:   $Revision: 7837 $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "mitkDataTreeNode.h"

#include <vtkWindow.h>
#include "mitkVtkPropRenderer.h"

#include "mitkTestingMacros.h"
#include "mitkGlobalInteraction.h"

#include <iostream>

//Basedata Test
#include <mitkContour.h>
#include <mitkContourSet.h>
#include <mitkItkBaseDataAdapter.h>
#include <mitkPointData.h>
#include <mitkMesh.h>
#include <mitkSeedsImage.h>
#include <mitkBoundingObject.h>
#include <mitkUnstructuredGrid.h>

//Mapper Test
#include <mitkMapper.h>
#include <mitkMapper2D.h>
#include <mitkBaseVtkMapper2D.h>
#include <mitkContourMapper2D.h>
#include <mitkContourSetMapper2D.h>
#include <mitkMeshMapper2D.h>
#include <mitkUnstructuredGridMapper2D.h>
#include <mitkLineMapper2D.h>
#include <mitkSplineMapper2D.h>

#include <mitkContourSetVtkMapper3D.h>
#include <mitkContourVtkMapper3D.h>
#include <mitkMeshVtkMapper3D.h>
#include <mitkPointDataVtkMapper3D.h>
#include <mitkUnstructuredGridVtkMapper3D.h>
#include <mitkLineVtkMapper3D.h>
#include <mitkSplineVtkMapper3D.h>

//Interactors
#include <mitkConnectPointsInteractor.h>
#include <mitkContourInteractor.h>
#include <mitkExtrudedContourInteractor.h>
#include <mitkPointInteractor.h>
#include <mitkPointSelectorInteractor.h>
#include <mitkSeedsInteractor.h>
#include <mitkDisplayPointSetInteractor.h>

//Propertylist Test
#include <mitkAnnotationProperty.h>
#include <mitkClippingProperty.h>
#include <mitkColorProperty.h>
#include <mitkEnumerationProperty.h>
#include <mitkGridRepresentationProperty.h>
#include <mitkGridVolumeMapperProperty.h>
#include <mitkOrganTypeProperty.h>
#include <mitkVtkInterpolationProperty.h>
#include <mitkVtkRepresentationProperty.h>
#include <mitkVtkResliceInterpolationProperty.h>
#include <mitkVtkScalarModeProperty.h>


/**
 *  Extended test for mitk::DataTreeNode. A number of tests from the core test
 *  mitkDataTreeNodeTest are assumed to pass!
 */
class mitkDataTreeNodeExtTestClass { public:

static void TestDataSetting(mitk::DataTreeNode::Pointer dataTreeNode)
{

  mitk::BaseData::Pointer baseData; 

  //NULL pointer Test
  dataTreeNode->SetData(baseData);
  MITK_TEST_CONDITION( baseData == dataTreeNode->GetData(), "Testing if a NULL pointer was set correctly" )

  baseData = mitk::Contour::New();
  dataTreeNode->SetData(baseData);
  MITK_TEST_CONDITION( baseData == dataTreeNode->GetData(), "Testing if a Contour object was set correctly" )

  baseData = mitk::ContourSet::New();
  dataTreeNode->SetData(baseData);
  MITK_TEST_CONDITION( baseData == dataTreeNode->GetData(), "Testing if a ContourSet object was set correctly" )
  
  baseData = mitk::ItkBaseDataAdapter::New();
  dataTreeNode->SetData(baseData);
  MITK_TEST_CONDITION( baseData == dataTreeNode->GetData(), "Testing if a ItkBaseDataAdapter object was set correctly" )

  baseData = mitk::PointData::New();
  dataTreeNode->SetData(baseData);
  MITK_TEST_CONDITION( baseData == dataTreeNode->GetData(), "Testing if a PointSet object was set correctly" )
  
  baseData = mitk::Mesh::New();
  dataTreeNode->SetData(baseData);
  MITK_TEST_CONDITION( baseData == dataTreeNode->GetData(), "Testing if a Mesh object was set correctly" )

  baseData = mitk::SeedsImage::New();
  dataTreeNode->SetData(baseData);
  MITK_TEST_CONDITION( baseData == dataTreeNode->GetData(), "Testing if a SeedsImage object was set correctly" )

  baseData = mitk::BoundingObject::New();
  dataTreeNode->SetData(baseData);
  MITK_TEST_CONDITION( baseData == dataTreeNode->GetData(), "Testing if a BoundingObject object was set correctly" )

  baseData = mitk::UnstructuredGrid::New();
  dataTreeNode->SetData(baseData);
  MITK_TEST_CONDITION( baseData == dataTreeNode->GetData(), "Testing if a UnstructuredGrid object was set correctly" )
}

static void TestMapperSetting(mitk::DataTreeNode::Pointer dataTreeNode)
{
  //tests the SetMapper() method
  //in dataTreeNode is a mapper vector which can be accessed by index
  //in this test method we use only slot 0 (filled with null) and slot 1
  //so we also test the destructor of the mapper classes
  mitk::Mapper::Pointer mapper;

  dataTreeNode->SetMapper(0,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(0), "Testing if a NULL pointer was set correctly" )

  mapper = mitk::ContourMapper2D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a ContourMapper2D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  mapper = mitk::ContourSetMapper2D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a ContourSetMapper2D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )
  
  mapper = mitk::MeshMapper2D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a MeshMapper2D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  mapper = mitk::UnstructuredGridMapper2D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a UnstructuredGridMapper2D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  mapper = mitk::LineMapper2D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a LineMapper2D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  mapper = mitk::SplineMapper2D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a SplineMapper2D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  //3D Mappers
  mapper = mitk::ContourSetVtkMapper3D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a ContourSetVtkMapper3D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  mapper = mitk::ContourVtkMapper3D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a ContourVtkMapper3D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  mapper = mitk::MeshVtkMapper3D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a MeshVtkMapper3D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  mapper = mitk::PointDataVtkMapper3D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a PointDataVtkMapper3D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  mapper = mitk::UnstructuredGridVtkMapper3D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a UnstructuredGridVtkMapper3D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  //linker error
  //mapper = mitk::LineVtkMapper3D::New();
  //dataTreeNode->SetMapper(1,mapper);
  //MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a LineVtkMapper3D was set correctly" )
  //MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )

  mapper = mitk::SplineVtkMapper3D::New();
  dataTreeNode->SetMapper(1,mapper);
  MITK_TEST_CONDITION( mapper == dataTreeNode->GetMapper(1), "Testing if a SplineVtkMapper3D was set correctly" )
  MITK_TEST_CONDITION( dataTreeNode == mapper->GetDataTreeNode(), "Testing if the mapper returns the right DataTreeNode" )
}
static void TestInteractorSetting(mitk::DataTreeNode::Pointer dataTreeNode)
{

  //this method tests the SetInteractor() and GetInteractor methods
  //the Interactor base class calls the DataTreeNode->SetInteractor method

  mitk::Interactor::Pointer interactor;

  MITK_TEST_CONDITION( interactor == dataTreeNode->GetInteractor(), "Testing if a NULL pointer was set correctly (Interactor)" )

  interactor = mitk::ConnectPointsInteractor::New("AffineInteractions click to select", dataTreeNode);
  MITK_TEST_CONDITION( interactor == dataTreeNode->GetInteractor(), "Testing if a ConnectPointsInteractor was set correctly" )

  interactor = mitk::ContourInteractor::New("AffineInteractions click to select", dataTreeNode);
  MITK_TEST_CONDITION( interactor == dataTreeNode->GetInteractor(), "Testing if a ContourInteractor was set correctly" )

  interactor = mitk::ExtrudedContourInteractor::New("AffineInteractions click to select", dataTreeNode);
  MITK_TEST_CONDITION( interactor == dataTreeNode->GetInteractor(), "Testing if a ExtrudedContourInteractor was set correctly" )

  interactor = mitk::PointInteractor::New("AffineInteractions click to select", dataTreeNode);
  MITK_TEST_CONDITION( interactor == dataTreeNode->GetInteractor(), "Testing if a PointInteractor was set correctly" )

  interactor = mitk::PointSelectorInteractor::New("AffineInteractions click to select", dataTreeNode);
  MITK_TEST_CONDITION( interactor == dataTreeNode->GetInteractor(), "Testing if a PointSelectorInteractor was set correctly" )

  interactor = mitk::SeedsInteractor::New("AffineInteractions click to select", dataTreeNode);
  MITK_TEST_CONDITION( interactor == dataTreeNode->GetInteractor(), "Testing if a SeedsInteractor was set correctly" )

  interactor = mitk::DisplayPointSetInteractor::New("AffineInteractions click to select", dataTreeNode);
  MITK_TEST_CONDITION( interactor == dataTreeNode->GetInteractor(), "Testing if a DisplayPointSetInteractor was set correctly" )
}

};

int mitkDataTreeNodeExtTest(int /* argc */, char* /*argv*/[])
{
  // always start with this!
  MITK_TEST_BEGIN("DataTreeNode")

  // Global interaction must(!) be initialized
  mitk::GlobalInteraction::GetInstance()->Initialize("global");

  // let's create an object of our class  
  mitk::DataTreeNode::Pointer myDataTreeNode = mitk::DataTreeNode::New();

  // first test: did this work?
  // using MITK_TEST_CONDITION_REQUIRED makes the test stop after failure, since
  // it makes no sense to continue without an object.
  MITK_TEST_CONDITION_REQUIRED(myDataTreeNode.IsNotNull(),"Testing instantiation") 

  //test setData() Method
  mitkDataTreeNodeExtTestClass::TestDataSetting(myDataTreeNode);
  mitkDataTreeNodeExtTestClass::TestMapperSetting(myDataTreeNode);
  
  //note, that no data is set to the dataTreeNode
  mitkDataTreeNodeExtTestClass::TestInteractorSetting(myDataTreeNode);

  // write your own tests here and use the macros from mitkTestingMacros.h !!!
  // do not write to std::cout and do not return from this function yourself!
  
  // always end with this!
  MITK_TEST_END()
}