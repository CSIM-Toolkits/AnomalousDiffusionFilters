/*=========================================================================                                                                                      
 *                                                                                                                                                               
 *  Copyright Insight Software Consortium                                                                                                                        
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
#ifndef __itkIsotropicAnomalousDiffusionImageFilter_h
#define __itkIsotropicAnomalousDiffusionImageFilter_h
#include "itkImageToImageFilter.h"
#include "itkImage.h"
#include "itkNumericTraits.h"

namespace itk
{

template< typename TInputImage, typename TOutputImage >
class ITK_EXPORT IsotropicAnomalousDiffusionImageFilter:
  public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Extract dimension from input and output image. */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      TOutputImage::ImageDimension);

  /** Convenient typedefs for simplifying declarations. */
  typedef TInputImage  InputImageType;
  typedef TOutputImage OutputImageType;

  /** Standard class typedefs. */
  typedef IsotropicAnomalousDiffusionImageFilter                             Self;
  typedef ImageToImageFilter< InputImageType, OutputImageType >                 Superclass;
  typedef SmartPointer< Self >                                                  Pointer;
  typedef SmartPointer< const Self >                                            ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self)

  /** Run-time type information (and related methods). */
  itkTypeMacro(IsotropicAnomalousDiffusionImageFilter, ImageToImageFilter)

  typedef typename InputImageType::PixelType                 InputPixelType;
  typedef typename OutputImageType::PixelType                OutputPixelType;

  typedef typename Superclass::OutputImageRegionType OutputImageRegionType;

  itkSetMacro(GeneralizedDiffusion, double)
  itkSetMacro(Iterations, int)
  itkSetMacro(TimeStep, double)
  itkSetMacro(Q, double)
  itkGetMacro(GeneralizedDiffusion, double)
  itkGetMacro(Iterations, int)
  itkGetMacro(TimeStep, double)
  itkGetMacro(Q, double)

#ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( InputHasNumericTraitsCheck,
                   ( Concept::HasNumericTraits< InputPixelType > ) );
  itkConceptMacro( SameDimensionCheck,
                   ( Concept::SameDimension< InputImageDimension, OutputImageDimension > ) );
#endif

protected:
  IsotropicAnomalousDiffusionImageFilter();
  virtual ~IsotropicAnomalousDiffusionImageFilter() {}
    double m_GeneralizedDiffusion;
    int m_Iterations;
    double m_TimeStep;
    double m_Q;
    virtual void ThreadedGenerateData(const OutputImageRegionType &, ThreadIdType);

private:
  IsotropicAnomalousDiffusionImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented
  void TimeStepTestStability();
  double GeneralizedDiffCurve();
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkIsotropicAnomalousDiffusionImageFilter.hxx"
#endif

#endif
