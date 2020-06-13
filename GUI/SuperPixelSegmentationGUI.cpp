
/*=========================================================================
 *
 *  Copyright David Doria 2011 daviddoria@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "SuperPixelSegmentationGUI.h"

// Custom
#include "Helpers.h"
#include "HelpersQt.h"

// ITK
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRGBPixel.h"
#include "itkScalarToRGBColormapImageFilter.h"

// Qt
#include <QIcon>
#include <QFileDialog>
#include <QGraphicsPixmapItem>

// Called by all constructors
void SuperPixelSegmentationGUI::DefaultConstructor()
{
  this->setupUi(this);

  // GraphCut sliders
  this->MinSizeMin = 0;
  this->MinSizeMax = 200;
  this->sldGraphCutMinSize->setMinimum(this->MinSizeMin);
  this->sldGraphCutMinSize->setMaximum(this->MinSizeMax);
  
  this->KMin = 0.0f;
  this->KMax = 1000.0f;
  this->sldGraphCutK->setMinimum(this->KMin);
  this->sldGraphCutK->setMaximum(this->KMax);

  this->SigmaMin = 0.0f;
  this->SigmaMax = 2.0f;
  this->sldGraphCutSigma->setMinimum(this->SigmaMin);
  this->sldGraphCutSigma->setMaximum(this->SigmaMax);
  
  // QuickShift sliders
  this->MaxDistMin = 0.0f;
  this->MaxDistMax = 100.0f;
  this->sldMaxDist->setMinimum(this->MaxDistMin);
  this->sldMaxDist->setMaximum(this->MaxDistMax);
  
  this->KernelSizeMin = 1;
  this->KernelSizeMax = 10;
  this->sldKernelSize->setMinimum(this->KernelSizeMin);
  this->sldKernelSize->setMaximum(this->KernelSizeMax);
  
  this->RatioMin = 0;
  this->RatioMax = 10;
  this->sldRatio->setMinimum(this->RatioMin);
  this->sldRatio->setMaximum(this->RatioMax);
  
  // SLIC sliders
  this->NumberOfSuperPixelsMin = 100;
  this->NumberOfSuperPixelsMax = 1000;
  this->sldSLICNumberOfSuperPixels->setMinimum(this->NumberOfSuperPixelsMin);
  this->sldSLICNumberOfSuperPixels->setMaximum(this->NumberOfSuperPixelsMax);
  
  this->SpatialDistanceWeightMin = 0;
  this->SpatialDistanceWeightMax = 10;
  this->sldSLICSpatialDistanceWeight->setMinimum(this->SpatialDistanceWeightMin);
  this->sldSLICSpatialDistanceWeight->setMaximum(this->SpatialDistanceWeightMax);
  
  // Marquee mode
  this->progressBar->setMinimum(0);
  this->progressBar->setMaximum(0);
  this->progressBar->hide();

  
  
  this->QuickShiftFilter = QuickShiftFilterType::New();
  this->QuickShiftThread = new ITKComputationThread<QuickShiftFilterType>;
  connect(this->QuickShiftThread, SIGNAL(StartProgressBarSignal()), this, SLOT(slot_StartProgressBar()));