# Directory containing class headers.
SET(VTK_COMMON_HEADER_DIR "/home/cxsong/rappture-runtime/VTK4.4/build/include/vtk")

# Classes in vtkCommon.
SET(VTK_COMMON_CLASSES
  "vtkAbstractMapper"
  "vtkAbstractTransform"
  "vtkActor2D"
  "vtkActor2DCollection"
  "vtkAmoebaMinimizer"
  "vtkAssemblyNode"
  "vtkAssemblyPath"
  "vtkAssemblyPaths"
  "vtkBitArray"
  "vtkBox"
  "vtkByteSwap"
  "vtkCallbackCommand"
  "vtkCell"
  "vtkCell3D"
  "vtkCellArray"
  "vtkCellData"
  "vtkCellLinks"
  "vtkCellTypes"
  "vtkCharArray"
  "vtkCollection"
  "vtkCollectionIterator"
  "vtkCommand"
  "vtkCompositeDataIterator"
  "vtkCompositeDataSet"
  "vtkCompositeDataVisitor"
  "vtkCompositeDataCommand"
  "vtkContourValues"
  "vtkConvexPointSet"
  "vtkCoordinate"
  "vtkCriticalSection"
  "vtkCylindricalTransform"
  "vtkDataArray"
  "vtkDataArrayCollection"
  "vtkDataArrayCollectionIterator"
  "vtkDataArraySelection"
  "vtkDataObject"
  "vtkDataObjectCollection"
  "vtkDataSet"
  "vtkDataSetAttributes"
  "vtkDataSetCollection"
  "vtkDebugLeaks"
  "vtkDebugLeaksManager"
  "vtkDirectory"
  "vtkDoubleArray"
  "vtkDynamicLoader"
  "vtkEdgeTable"
  "vtkEmptyCell"
  "vtkErrorCode"
  "vtkExplicitCell"
  "vtkExtentSplitter"
  "vtkExtentTranslator"
  "vtkFieldData"
  "vtkFileOutputWindow"
  "vtkFloatArray"
  "vtkFunctionParser"
  "vtkFunctionSet"
  "vtkGeneralTransform"
  "vtkGenericCell"
  "vtkHeap"
  "vtkHexahedron"
  "vtkHierarchicalBoxDataSet"
  "vtkHierarchicalBoxVisitor"
  "vtkHierarchicalDataSet"
  "vtkHierarchicalDataIterator"
  "vtkHomogeneousTransform"
  "vtkIdList"
  "vtkIdListCollection"
  "vtkIdType"
  "vtkIdTypeArray"
  "vtkIdentityTransform"
  "vtkImageData"
  "vtkImageIterator"
  "vtkImageProgressIterator"
  "vtkImplicitFunction"
  "vtkImplicitFunctionCollection"
  "vtkIndent"
  "vtkInitialValueProblemSolver"
  "vtkInstantiator"
  "vtkIntArray"
  "vtkInterpolatedVelocityField"
  "vtkLargeInteger"
  "vtkLine"
  "vtkLinearTransform"
  "vtkLocator"
  "vtkLogLookupTable"
  "vtkLongArray"
  "vtkLookupTable"
  "vtkMapper2D"
  "vtkMath"
  "vtkMatrix4x4"
  "vtkMatrixToHomogeneousTransform"
  "vtkMatrixToLinearTransform"
  "vtkMultiBlockDataIterator"
  "vtkMultiBlockDataSet"
  "vtkMultiBlockDataVisitor"
  "vtkMultiPartExtentTranslator"
  "vtkMultiThreader"
  "vtkMutexLock"
  "vtkNonLinearCell"
  "vtkOStrStreamWrapper"
  "vtkOStreamWrapper"
  "vtkObject"
  "vtkObjectBase"
  "vtkObjectFactory"
  "vtkObjectFactoryCollection"
  "vtkOldStyleCallbackCommand"
  "vtkOrderedTriangulator"
  "vtkOutputWindow"
  "vtkOverrideInformation"
  "vtkOverrideInformationCollection"
  "vtkPerspectiveTransform"
  "vtkPixel"
  "vtkPlane"
  "vtkPlaneCollection"
  "vtkPlanes"
  "vtkPointData"
  "vtkPointLocator"
  "vtkPointSet"
  "vtkPoints"
  "vtkPolyData"
  "vtkPolyLine"
  "vtkPolyVertex"
  "vtkPolygon"
  "vtkPriorityQueue"
  "vtkProcessObject"
  "vtkProp"
  "vtkPropAssembly"
  "vtkPropCollection"
  "vtkProperty2D"
  "vtkPyramid"
  "vtkQuad"
  "vtkQuadraticEdge"
  "vtkQuadraticHexahedron"
  "vtkQuadraticQuad"
  "vtkQuadraticTetra"
  "vtkQuadraticTriangle"
  "vtkQuadric"
  "vtkRectilinearGrid"
  "vtkReferenceCount"
  "vtkRungeKutta2"
  "vtkRungeKutta4"
  "vtkRungeKutta45"
  "vtkScalarsToColors"
  "vtkShortArray"
  "vtkSmartPointerBase"
  "vtkSource"
  "vtkSphericalTransform"
  "vtkStdString"
  "vtkStructuredData"
  "vtkStructuredGrid"
  "vtkStructuredPoints"
  "vtkStructuredVisibilityConstraint"
  "vtkTableExtentTranslator"
  "vtkTensor"
  "vtkTetra"
  "vtkTimeStamp"
  "vtkTimerLog"
  "vtkTransform"
  "vtkTransformCollection"
  "vtkTriangle"
  "vtkTriangleStrip"
  "vtkUniformGrid"
  "vtkUnsignedCharArray"
  "vtkUnsignedIntArray"
  "vtkUnsignedLongArray"
  "vtkUnsignedShortArray"
  "vtkUnstructuredGrid"
  "vtkVersion"
  "vtkVertex"
  "vtkViewport"
  "vtkVoidArray"
  "vtkVoxel"
  "vtkWarpTransform"
  "vtkWedge"
  "vtkWindow"
  "vtkWindowLevelLookupTable"
  "vtkXMLFileOutputWindow")

# Abstract classes in vtkCommon.
SET(VTK_COMMON_CLASSES_ABSTRACT
  "vtkAbstractMapper"
  "vtkAbstractTransform"
  "vtkCallbackCommand"
  "vtkCell"
  "vtkCell3D"
  "vtkCommand"
  "vtkCompositeDataIterator"
  "vtkCompositeDataSet"
  "vtkCompositeDataVisitor"
  "vtkCompositeDataCommand"
  "vtkDataArray"
  "vtkDataSet"
  "vtkExplicitCell"
  "vtkFunctionSet"
  "vtkHierarchicalDataSet"
  "vtkHomogeneousTransform"
  "vtkImplicitFunction"
  "vtkInitialValueProblemSolver"
  "vtkLinearTransform"
  "vtkLocator"
  "vtkMapper2D"
  "vtkNonLinearCell"
  "vtkObjectBase"
  "vtkObjectFactory"
  "vtkOldStyleCallbackCommand"
  "vtkOverrideInformation"
  "vtkOverrideInformationCollection"
  "vtkPointSet"
  "vtkProcessObject"
  "vtkProp"
  "vtkScalarsToColors"
  "vtkSource"
  "vtkStructuredData"
  "vtkViewport"
  "vtkWarpTransform"
  "vtkWindow")

# Wrap-exclude classes in vtkCommon.
SET(VTK_COMMON_CLASSES_WRAP_EXCLUDE
  "vtkCallbackCommand"
  "vtkCommand"
  "vtkDebugLeaksManager"
  "vtkErrorCode"
  "vtkIdType"
  "vtkImageIterator"
  "vtkImageProgressIterator"
  "vtkIndent"
  "vtkLargeInteger"
  "vtkOStrStreamWrapper"
  "vtkOStreamWrapper"
  "vtkOldStyleCallbackCommand"
  "vtkSmartPointerBase"
  "vtkStdString"
  "vtkTimeStamp")

# Set convenient variables to test each class.
FOREACH(class ${VTK_COMMON_CLASSES})
  SET(VTK_CLASS_EXISTS_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_COMMON_CLASSES_ABSTRACT})
  SET(VTK_CLASS_ABSTRACT_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_COMMON_CLASSES_WRAP_EXCLUDE})
  SET(VTK_CLASS_WRAP_EXCLUDE_${class} 1)
ENDFOREACH(class)
