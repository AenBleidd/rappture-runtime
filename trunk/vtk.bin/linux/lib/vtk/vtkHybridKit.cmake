# Directory containing class headers.
SET(VTK_HYBRID_HEADER_DIR "/opt/rappture-runtime/VTK4.4/build/include/vtk")

# Classes in vtkHybrid.
SET(VTK_HYBRID_CLASSES
  "vtk3DSImporter"
  "vtk3DWidget"
  "vtkArcPlotter"
  "vtkBoxWidget"
  "vtkCaptionActor2D"
  "vtkCubeAxesActor2D"
  "vtkDepthSortPolyData"
  "vtkEarthSource"
  "vtkGreedyTerrainDecimation"
  "vtkGridTransform"
  "vtkImagePlaneWidget"
  "vtkImageToPolyDataFilter"
  "vtkImageTracerWidget"
  "vtkImplicitModeller"
  "vtkImplicitPlaneWidget"
  "vtkIterativeClosestPointTransform"
  "vtkLandmarkTransform"
  "vtkLegendBoxActor"
  "vtkLineWidget"
  "vtkPCAAnalysisFilter"
  "vtkPlaneWidget"
  "vtkPointWidget"
  "vtkPolyDataSourceWidget"
  "vtkPolyDataToImageStencil"
  "vtkProcrustesAlignmentFilter"
  "vtkPushImageFilterSample"
  "vtkPushImageReader"
  "vtkPushPipeline"
  "vtkRIBExporter"
  "vtkRIBLight"
  "vtkRIBProperty"
  "vtkRenderLargeImage"
  "vtkScalarBarWidget"
  "vtkSphereWidget"
  "vtkSplineWidget"
  "vtkThinPlateSplineTransform"
  "vtkTransformToGrid"
  "vtkVRMLImporter"
  "vtkVectorText"
  "vtkVideoSource"
  "vtkWeightedTransformFilter"
  "vtkXYPlotActor"
  "vtkXYPlotWidget")

# Abstract classes in vtkHybrid.
SET(VTK_HYBRID_CLASSES_ABSTRACT
  "vtk3DWidget"
  "vtkPolyDataSourceWidget")

# Wrap-exclude classes in vtkHybrid.
SET(VTK_HYBRID_CLASSES_WRAP_EXCLUDE)

# Set convenient variables to test each class.
FOREACH(class ${VTK_HYBRID_CLASSES})
  SET(VTK_CLASS_EXISTS_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_HYBRID_CLASSES_ABSTRACT})
  SET(VTK_CLASS_ABSTRACT_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_HYBRID_CLASSES_WRAP_EXCLUDE})
  SET(VTK_CLASS_WRAP_EXCLUDE_${class} 1)
ENDFOREACH(class)
