#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCastImageFilter.h"

#include "itkAnisotropicAnomalousDiffusionImageFilter.h"
#include "itkIsotropicAnomalousDiffusionImageFilter.h"

int AnomalousDiffusionTest(int argc, char* argv[])
{
 if( argc < 3 )
    {
    std::cerr << "You must supply an input image file name and an output image file name " << std::endl;
    return 1;
    }

    const unsigned int Dimension = 2;

    typedef unsigned char                       PixelType;
    typedef itk::Image<PixelType, Dimension>    ImageType;
    typedef itk::Image<float, Dimension>        CastImageType;

    typedef itk::ImageFileReader<ImageType> ReaderType;
    typedef itk::ImageFileWriter<ImageType> WriterType;

    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(argv[1]);
    try
        {
        reader->Update();
        }
      catch ( itk::ExceptionObject &err)
        {
        std::cerr << "ExceptionObject caught !" << std::endl;
        std::cerr << err << std::endl;
        return 1;
        }    
    typedef itk::CastImageFilter<ImageType, CastImageType> CastType;
    typename CastType::Pointer cast = CastType::New();
    cast->SetInput(reader->GetOutput());
    cast->Update();


    typedef itk::IsotropicAnomalousDiffusionImageFilter<CastImageType, CastImageType> IsotropicFilterType;
    typedef itk::AnisotropicAnomalousDiffusionImageFilter<CastImageType, CastImageType> FilterType;
    FilterType::Pointer filter = FilterType::New();

    filter->SetInput(cast->GetOutput());
    filter->SetCondutance(15.0);
    filter->SetQ(1.2);
    filter->SetIterations(5);
    filter->SetTimeStep(0.125);
    filter->Update();  
  
    typedef itk::CastImageFilter<CastImageType, ImageType> CastBackType;
    typename CastBackType::Pointer castBack = CastBackType::New();
    castBack->SetInput(filter->GetOutput());
    castBack->Update();

    WriterType::Pointer writer = WriterType::New();
    std::ostringstream baseName;

    baseName << argv[2];    
    //baseName << argv[1] << ".base.png";
    writer->SetFileName( baseName.str().c_str() );
    writer->SetInput( castBack->GetOutput() );


      try
        {
        writer->Update();
        }
      catch ( itk::ExceptionObject &err)
        {
        std::cerr << "Error during write of " << baseName.str() << std::endl;
        return 1;
        }

  return EXIT_SUCCESS;
}

