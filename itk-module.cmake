set(DOCUMENTATION "This module have implementations of anomalous diffusion filtering paradigm, being able to handle multidimensional data.

Documentation can be found in the Insight Journal article, 'Anomalous Diffusion Paradigm for Image Denoising Process', by Senra Filho A.C da S. and Murta Junior, L.O.
http://hdl.handle.net/10380/3565")

itk_module(ITKAnomalousDiffusionFilters
  DEPENDS
    ITKCommon
    ITKIOImageBase
    ITKImageFilterBase
  TEST_DEPENDS
    ITKTestKernel
    ITKMetaIO
  EXCLUDE_FROM_DEFAULT
  DESCRIPTION
    "${DOCUMENTATION}"
)
