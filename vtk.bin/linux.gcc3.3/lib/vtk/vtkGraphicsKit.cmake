# Directory containing class headers.
SET(VTK_GRAPHICS_HEADER_DIR "/home/cxsong/rappture-runtime/VTK4.4/build/include/vtk")

# Classes in vtkGraphics.
SET(VTK_GRAPHICS_CLASSES
  "vtkAppendFilter"
  "vtkAppendPolyData"
  "vtkApproximatingSubdivisionFilter"
  "vtkArrayCalculator"
  "vtkArrowSource"
  "vtkAssignAttribute"
  "vtkAttributeDataToFieldDataFilter"
  "vtkAxes"
  "vtkBandedPolyDataContourFilter"
  "vtkBlankStructuredGrid"
  "vtkBlankStructuredGridWithImage"
  "vtkBrownianPoints"
  "vtkButterflySubdivisionFilter"
  "vtkButtonSource"
  "vtkCellCenters"
  "vtkCellDataToPointData"
  "vtkCellDerivatives"
  "vtkCleanPolyData"
  "vtkClipDataSet"
  "vtkClipPolyData"
  "vtkClipVolume"
  "vtkConeSource"
  "vtkConnectivityFilter"
  "vtkContourFilter"
  "vtkContourGrid"
  "vtkCubeSource"
  "vtkCursor3D"
  "vtkCutter"
  "vtkCurvatures"
  "vtkCylinderSource"
  "vtkDashedStreamLine"
  "vtkDataObjectToDataSetFilter"
  "vtkDataSetSurfaceFilter"
  "vtkDataSetToDataObjectFilter"
  "vtkDataSetTriangleFilter"
  "vtkDecimatePro"
  "vtkDelaunay2D"
  "vtkDelaunay3D"
  "vtkDicer"
  "vtkDiskSource"
  "vtkEdgePoints"
  "vtkElevationFilter"
  "vtkExtractEdges"
  "vtkExtractGeometry"
  "vtkExtractGrid"
  "vtkExtractPolyDataGeometry"
  "vtkExtractRectilinearGrid"
  "vtkExtractTensorComponents"
  "vtkExtractUnstructuredGrid"
  "vtkExtractVectorComponents"
  "vtkFeatureEdges"
  "vtkFieldDataToAttributeDataFilter"
  "vtkGeometryFilter"
  "vtkGlyph2D"
  "vtkGlyph3D"
  "vtkGlyphSource2D"
  "vtkGraphLayoutFilter"
  "vtkHierarchicalBoxCellDataToPointData"
  "vtkHierarchicalBoxContour"
  "vtkHierarchicalBoxCutter"
  "vtkHierarchicalBoxOutlineFilter"
  "vtkHedgeHog"
  "vtkHull"
  "vtkHyperStreamline"
  "vtkIdFilter"
  "vtkImageDataGeometryFilter"
  "vtkImplicitTextureCoords"
  "vtkInterpolateDataSetAttributes"
  "vtkInterpolatingSubdivisionFilter"
  "vtkLineSource"
  "vtkLinearExtrusionFilter"
  "vtkLinearSubdivisionFilter"
  "vtkLinkEdgels"
  "vtkLoopSubdivisionFilter"
  "vtkMaskFields"
  "vtkMaskPoints"
  "vtkMaskPolyData"
  "vtkMassProperties"
  "vtkMergeDataObjectFilter"
  "vtkMergeFields"
  "vtkMergeFilter"
  "vtkMeshQuality"
  "vtkOBBDicer"
  "vtkOBBTree"
  "vtkOutlineCornerFilter"
  "vtkOutlineCornerSource"
  "vtkOutlineFilter"
  "vtkOutlineSource"
  "vtkPlaneSource"
  "vtkPlatonicSolidSource"
  "vtkPointDataToCellData"
  "vtkPointSource"
  "vtkPolyDataConnectivityFilter"
  "vtkPolyDataNormals"
  "vtkPolyDataStreamer"
  "vtkProbeFilter"
  "vtkProgrammableAttributeDataFilter"
  "vtkProgrammableDataObjectSource"
  "vtkProgrammableFilter"
  "vtkProgrammableGlyphFilter"
  "vtkProgrammableSource"
  "vtkProjectedTexture"
  "vtkQuadricClustering"
  "vtkQuadricDecimation"
  "vtkQuantizePolyDataPoints"
  "vtkRearrangeFields"
  "vtkRectilinearGridGeometryFilter"
  "vtkRectilinearGridToTetrahedra"
  "vtkRecursiveDividingCubes"
  "vtkReflectionFilter"
  "vtkReverseSense"
  "vtkRibbonFilter"
  "vtkRotationalExtrusionFilter"
  "vtkRuledSurfaceFilter"
  "vtkSelectPolyData"
  "vtkShrinkFilter"
  "vtkShrinkPolyData"
  "vtkSimpleElevationFilter"
  "vtkSmoothPolyDataFilter"
  "vtkSpatialRepresentationFilter"
  "vtkSpherePuzzle"
  "vtkSpherePuzzleArrows"
  "vtkSphereSource"
  "vtkSplineFilter"
  "vtkSplitField"
  "vtkStreamLine"
  "vtkStreamPoints"
  "vtkStreamTracer"
  "vtkStreamer"
  "vtkStripper"
  "vtkStructuredGridGeometryFilter"
  "vtkStructuredGridOutlineFilter"
  "vtkStructuredPointsGeometryFilter"
  "vtkSubPixelPositionEdgels"
  "vtkSubdivideTetra"
  "vtkSuperquadricSource"
  "vtkTensorGlyph"
  "vtkTextSource"
  "vtkTextureMapToCylinder"
  "vtkTextureMapToPlane"
  "vtkTextureMapToSphere"
  "vtkTexturedSphereSource"
  "vtkThreshold"
  "vtkThresholdPoints"
  "vtkThresholdTextureCoords"
  "vtkTransformFilter"
  "vtkTransformPolyDataFilter"
  "vtkTransformTextureCoords"
  "vtkTriangleFilter"
  "vtkTriangularTCoords"
  "vtkTubeFilter"
  "vtkVectorDot"
  "vtkVectorNorm"
  "vtkVoxelContoursToSurfaceFilter"
  "vtkWarpLens"
  "vtkWarpScalar"
  "vtkWarpTo"
  "vtkWarpVector"
  "vtkWindowedSincPolyDataFilter")

# Abstract classes in vtkGraphics.
SET(VTK_GRAPHICS_CLASSES_ABSTRACT
  "vtkApproximatingSubdivisionFilter"
  "vtkDicer"
  "vtkInterpolatingSubdivisionFilter"
  "vtkStreamer")

# Wrap-exclude classes in vtkGraphics.
SET(VTK_GRAPHICS_CLASSES_WRAP_EXCLUDE)

# Set convenient variables to test each class.
FOREACH(class ${VTK_GRAPHICS_CLASSES})
  SET(VTK_CLASS_EXISTS_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_GRAPHICS_CLASSES_ABSTRACT})
  SET(VTK_CLASS_ABSTRACT_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_GRAPHICS_CLASSES_WRAP_EXCLUDE})
  SET(VTK_CLASS_WRAP_EXCLUDE_${class} 1)
ENDFOREACH(class)
