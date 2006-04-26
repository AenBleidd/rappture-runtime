SET(vtkzlib_LIB_DEPENDS "")
SET(vtkjpeg_LIB_DEPENDS "")
SET(vtkpng_LIB_DEPENDS "vtkzlib;")
SET(vtktiff_LIB_DEPENDS "vtkzlib;vtkjpeg;")
SET(vtkexpat_LIB_DEPENDS "")
SET(vtkDICOMParser_LIB_DEPENDS "")
SET(vtkfreetype_LIB_DEPENDS "")
SET(vtkftgl_LIB_DEPENDS "/usr/lib/libGLU.so;/usr/lib/libGL.so;-lSM;-lICE;-lSM;-lICE;/usr/X11R6/lib/libX11.so;/usr/X11R6/lib/libXext.so;/usr/X11R6/lib/libX11.so;/usr/X11R6/lib/libXext.so;vtkfreetype;")
SET(vtkCommon_LIB_DEPENDS "-lpthread;-ldl;-lm;")
SET(vtkCommonTCL_LIB_DEPENDS "vtkCommon;/opt/rappture/lib/libtcl8.4.so;")
SET(vtkFiltering_LIB_DEPENDS "vtkCommon;")
SET(vtkFilteringTCL_LIB_DEPENDS "vtkFiltering;vtkCommonTCL;")
SET(vtkImaging_LIB_DEPENDS "vtkFiltering;")
SET(vtkImagingTCL_LIB_DEPENDS "vtkImaging;vtkFilteringTCL;")
SET(vtkGraphics_LIB_DEPENDS "vtkFiltering;")
SET(vtkGraphicsTCL_LIB_DEPENDS "vtkGraphics;vtkFilteringTCL;")
SET(vtkIO_LIB_DEPENDS "vtkFiltering;vtkDICOMParser;vtkpng;vtkzlib;vtkjpeg;vtktiff;vtkexpat;")
SET(vtkIOTCL_LIB_DEPENDS "vtkIO;vtkFilteringTCL;")
SET(vtkRendering_LIB_DEPENDS "vtkGraphics;vtkImaging;vtkIO;vtkftgl;vtkfreetype;/usr/lib/libGLU.so;/usr/lib/libGL.so;-lSM;-lICE;-lSM;-lICE;/usr/X11R6/lib/libX11.so;/usr/X11R6/lib/libXext.so;/usr/X11R6/lib/libX11.so;/usr/X11R6/lib/libXext.so;-lXt;-lSM;-lICE;/usr/X11R6/lib/libX11.so;/usr/X11R6/lib/libXext.so;")
SET(vtkRenderingTCL_LIB_DEPENDS "vtkRendering;vtkGraphicsTCL;vtkImagingTCL;/opt/rappture/lib/libtcl8.4.so;/opt/rappture/lib/libtk8.4.so;")
SET(vtkHybrid_LIB_DEPENDS "vtkRendering;vtkIO;")
SET(vtkHybridTCL_LIB_DEPENDS "vtkHybrid;vtkRenderingTCL;vtkIOTCL;")
SET(vtkParallel_LIB_DEPENDS "vtkRendering;vtkIO;")
SET(vtkParallelTCL_LIB_DEPENDS "vtkParallel;vtkRenderingTCL;vtkIOTCL;")
