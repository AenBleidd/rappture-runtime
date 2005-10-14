# Directory containing class headers.
SET(VTK_RENDERING_HEADER_DIR "/opt/rappture-runtime/VTK4.4/build/include/vtk")

# Classes in vtkRendering.
SET(VTK_RENDERING_CLASSES
  "vtkAbstractMapper3D"
  "vtkAbstractVolumeMapper"
  "vtkAbstractPicker"
  "vtkAbstractPropPicker"
  "vtkActor"
  "vtkActorCollection"
  "vtkAssembly"
  "vtkAxisActor2D"
  "vtkCamera"
  "vtkCellPicker"
  "vtkCuller"
  "vtkCullerCollection"
  "vtkDataSetMapper"
  "vtkDirectionEncoder"
  "vtkEncodedGradientEstimator"
  "vtkEncodedGradientShader"
  "vtkExporter"
  "vtkFiniteDifferenceGradientEstimator"
  "vtkFollower"
  "vtkFrustumCoverageCuller"
  "vtkGenericRenderWindowInteractor"
  "vtkGraphicsFactory"
  "vtkIVExporter"
  "vtkImageActor"
  "vtkImageMapper"
  "vtkImageViewer"
  "vtkImageViewer2"
  "vtkImagingFactory"
  "vtkImporter"
  "vtkInteractorEventRecorder"
  "vtkInteractorObserver"
  "vtkInteractorStyle"
  "vtkInteractorStyleFlight"
  "vtkInteractorStyleImage"
  "vtkInteractorStyleJoystickActor"
  "vtkInteractorStyleJoystickCamera"
  "vtkInteractorStyleRubberBandZoom"
  "vtkInteractorStyleSwitch"
  "vtkInteractorStyleTerrain"
  "vtkInteractorStyleTrackball"
  "vtkInteractorStyleTrackballActor"
  "vtkInteractorStyleTrackballCamera"
  "vtkInteractorStyleUnicam"
  "vtkInteractorStyleUser"
  "vtkLODActor"
  "vtkLODProp3D"
  "vtkLabeledDataMapper"
  "vtkLight"
  "vtkLightCollection"
  "vtkLightKit"
  "vtkMapper"
  "vtkMapperCollection"
  "vtkOBJExporter"
  "vtkOOGLExporter"
  "vtkParallelCoordinatesActor"
  "vtkPicker"
  "vtkPointPicker"
  "vtkPolyDataMapper"
  "vtkPolyDataMapper2D"
  "vtkProp3D"
  "vtkProp3DCollection"
  "vtkPropPicker"
  "vtkProperty"
  "vtkRayCastImageDisplayHelper"
  "vtkRecursiveSphereDirectionEncoder"
  "vtkRenderWindow"
  "vtkRenderWindowCollection"
  "vtkRenderWindowInteractor"
  "vtkRenderer"
  "vtkRendererCollection"
  "vtkRendererSource"
  "vtkScalarBarActor"
  "vtkScaledTextActor"
  "vtkSelectVisiblePoints"
  "vtkTesting"
  "vtkTextActor"
  "vtkTextMapper"
  "vtkTextProperty"
  "vtkTexture"
  "vtkUnstructuredGridBunykRayCastFunction"
  "vtkUnstructuredGridVolumeMapper"
  "vtkUnstructuredGridVolumeRayCastFunction"
  "vtkUnstructuredGridVolumeRayCastMapper"
  "vtkVRMLExporter"
  "vtkVolume"
  "vtkVolumeCollection"
  "vtkVolumeMapper"
  "vtkVolumeProMapper"
  "vtkVolumeProperty"
  "vtkVolumeRayCastCompositeFunction"
  "vtkVolumeRayCastFunction"
  "vtkVolumeRayCastIsosurfaceFunction"
  "vtkVolumeRayCastMIPFunction"
  "vtkVolumeRayCastMapper"
  "vtkVolumeTextureMapper"
  "vtkVolumeTextureMapper2D"
  "vtkWindowToImageFilter"
  "vtkWorldPointPicker"
  "vtkFreeTypeFontCache"
  "vtkXRenderWindowInteractor"
  "vtkOpenGLActor"
  "vtkOpenGLCamera"
  "vtkOpenGLImageActor"
  "vtkOpenGLImageMapper"
  "vtkOpenGLLight"
  "vtkOpenGLPolyDataMapper"
  "vtkOpenGLPolyDataMapper2D"
  "vtkOpenGLProperty"
  "vtkOpenGLRayCastImageDisplayHelper"
  "vtkOpenGLRenderWindow"
  "vtkOpenGLRenderer"
  "vtkOpenGLTexture"
  "vtkOpenGLVolumeRayCastMapper"
  "vtkOpenGLVolumeTextureMapper2D"
  "vtkOpenGLFreeTypeTextMapper"
  "vtkXOpenGLRenderWindow")

# Abstract classes in vtkRendering.
SET(VTK_RENDERING_CLASSES_ABSTRACT
  "vtkAbstractMapper3D"
  "vtkAbstractVolumeMapper"
  "vtkAbstractPicker"
  "vtkAbstractPropPicker"
  "vtkCuller"
  "vtkDirectionEncoder"
  "vtkEncodedGradientEstimator"
  "vtkExporter"
  "vtkImporter"
  "vtkInteractorObserver"
  "vtkMapper"
  "vtkProp3D"
  "vtkRayCastImageDisplayHelper"
  "vtkUnstructuredGridVolumeMapper"
  "vtkUnstructuredGridVolumeRayCastFunction"
  "vtkVolumeMapper"
  "vtkVolumeRayCastFunction"
  "vtkVolumeTextureMapper"
  "vtkOpenGLRenderWindow")

# Wrap-exclude classes in vtkRendering.
SET(VTK_RENDERING_CLASSES_WRAP_EXCLUDE
  "vtkFreeTypeFontCache")

# Set convenient variables to test each class.
FOREACH(class ${VTK_RENDERING_CLASSES})
  SET(VTK_CLASS_EXISTS_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_RENDERING_CLASSES_ABSTRACT})
  SET(VTK_CLASS_ABSTRACT_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_RENDERING_CLASSES_WRAP_EXCLUDE})
  SET(VTK_CLASS_WRAP_EXCLUDE_${class} 1)
ENDFOREACH(class)
