# Directory containing class headers.
SET(VTK_PARALLEL_HEADER_DIR "/opt/rappture-runtime/VTK4.4/build/include/vtk")

# Classes in vtkParallel.
SET(VTK_PARALLEL_CLASSES
  "vtkDuplicatePolyData"
  "vtkBranchExtentTranslator"
  "vtkCollectPolyData"
  "vtkCommunicator"
  "vtkCompositeManager"
  "vtkCompositer"
  "vtkCompositeRenderManager"
  "vtkCompressCompositer"
  "vtkCutMaterial"
  "vtkDistributedStreamTracer"
  "vtkDummyController"
  "vtkExtractPolyDataPiece"
  "vtkExtractUnstructuredGridPiece"
  "vtkInputPort"
  "vtkMemoryLimitImageDataStreamer"
  "vtkMultiProcessController"
  "vtkOutputPort"
  "vtkParallelRenderManager"
  "vtkPassThroughFilter"
  "vtkPCellDataToPointData"
  "vtkPDataSetReader"
  "vtkPDataSetWriter"
  "vtkPImageWriter"
  "vtkPLinearExtrusionFilter"
  "vtkPOPReader"
  "vtkPOutlineFilter"
  "vtkPOutlineCornerFilter"
  "vtkPPolyDataNormals"
  "vtkPProbeFilter"
  "vtkPSphereSource"
  "vtkPStreamTracer"
  "vtkParallelFactory"
  "vtkPieceScalars"
  "vtkPipelineSize"
  "vtkRTAnalyticSource"
  "vtkRectilinearGridOutlineFilter"
  "vtkSocketCommunicator"
  "vtkSocketController"
  "vtkTransmitPolyDataPiece"
  "vtkTransmitUnstructuredGridPiece"
  "vtkTreeComposite"
  "vtkTreeCompositer"
  "vtkSharedMemoryCommunicator"
  "vtkThreadedController")

# Abstract classes in vtkParallel.
SET(VTK_PARALLEL_CLASSES_ABSTRACT
  "vtkCommunicator"
  "vtkParallelRenderManager"
  "vtkPStreamTracer")

# Wrap-exclude classes in vtkParallel.
SET(VTK_PARALLEL_CLASSES_WRAP_EXCLUDE)

# Set convenient variables to test each class.
FOREACH(class ${VTK_PARALLEL_CLASSES})
  SET(VTK_CLASS_EXISTS_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_PARALLEL_CLASSES_ABSTRACT})
  SET(VTK_CLASS_ABSTRACT_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_PARALLEL_CLASSES_WRAP_EXCLUDE})
  SET(VTK_CLASS_WRAP_EXCLUDE_${class} 1)
ENDFOREACH(class)
