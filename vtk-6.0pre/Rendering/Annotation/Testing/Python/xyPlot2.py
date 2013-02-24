#!/usr/bin/env python
import vtk
from vtk.test import Testing
from vtk.util.misc import vtkGetDataRoot
VTK_DATA_ROOT = vtkGetDataRoot()

# create pipeline
#
pl3d = vtk.vtkMultiBlockPLOT3DReader()
pl3d.SetXYZFileName("" + str(VTK_DATA_ROOT) + "/Data/combxyz.bin")
pl3d.SetQFileName("" + str(VTK_DATA_ROOT) + "/Data/combq.bin")
pl3d.SetScalarFunctionNumber(100)
pl3d.SetVectorFunctionNumber(202)
pl3d.Update()
output = pl3d.GetOutput().GetBlock(0)
# create three line probes
line = vtk.vtkLineSource()
line.SetResolution(30)
transL1 = vtk.vtkTransform()
transL1.Translate(3.7,0.0,28.37)
transL1.Scale(5,5,5)
transL1.RotateY(90)
tf = vtk.vtkTransformPolyDataFilter()
tf.SetInputConnection(line.GetOutputPort())
tf.SetTransform(transL1)
probe = vtk.vtkProbeFilter()
probe.SetInputConnection(tf.GetOutputPort())
probe.SetSourceData(output)
probe.Update()
transL2 = vtk.vtkTransform()
transL2.Translate(9.2,0.0,31.20)
transL2.Scale(5,5,5)
transL2.RotateY(90)
tf2 = vtk.vtkTransformPolyDataFilter()
tf2.SetInputConnection(line.GetOutputPort())
tf2.SetTransform(transL2)
probe2 = vtk.vtkProbeFilter()
probe2.SetInputConnection(tf2.GetOutputPort())
probe2.SetSourceData(output)
probe2.Update()
transL3 = vtk.vtkTransform()
transL3.Translate(13.27,0.0,33.40)
transL3.Scale(4.5,4.5,4.5)
transL3.RotateY(90)
tf3 = vtk.vtkTransformPolyDataFilter()
tf3.SetInputConnection(line.GetOutputPort())
tf3.SetTransform(transL3)
probe3 = vtk.vtkProbeFilter()
probe3.SetInputConnection(tf3.GetOutputPort())
probe3.SetSourceData(output)
probe3.Update()
appendF = vtk.vtkAppendPolyData()
appendF.AddInputConnection(probe.GetOutputPort())
appendF.AddInputConnection(probe2.GetOutputPort())
appendF.AddInputConnection(probe3.GetOutputPort())
tuber = vtk.vtkTubeFilter()
tuber.SetInputConnection(appendF.GetOutputPort())
tuber.SetRadius(0.1)
lineMapper = vtk.vtkPolyDataMapper()
lineMapper.SetInputConnection(tuber.GetOutputPort())
lineActor = vtk.vtkActor()
lineActor.SetMapper(lineMapper)
# probe the line and plot it
triangle = vtk.vtkGlyphSource2D()
triangle.SetGlyphTypeToTriangle()
triangle.Update()
cross = vtk.vtkGlyphSource2D()
cross.SetGlyphTypeToCross()
cross.Update()
xyplot = vtk.vtkXYPlotActor()
xyplot.AddDataSetInputConnection(probe.GetOutputPort())
xyplot.AddDataSetInputConnection(probe2.GetOutputPort())
xyplot.AddDataSetInputConnection(probe3.GetOutputPort())
xyplot.GetPositionCoordinate().SetValue(0.0,0.67,0)
xyplot.GetPosition2Coordinate().SetValue(1.0,0.33,0)
#relative to Position
xyplot.SetXValuesToArcLength()
xyplot.SetNumberOfXLabels(6)
xyplot.SetTitle("Pressure vs. Arc Length (Zoomed View)")
xyplot.SetXTitle("")
xyplot.SetYTitle("P")
xyplot.SetXRange(.1,.35)
xyplot.SetYRange(.2,.4)
xyplot.GetProperty().SetColor(0,0,0)
xyplot.PlotLinesOn()
xyplot.GetProperty().SetLineWidth(1)
xyplot.PlotPointsOn()
xyplot.GetProperty().SetPointSize(3)
xyplot.LegendOn()
xyplot.SetPlotSymbol(2,triangle.GetOutput())
xyplot.SetPlotColor(2,0,0,1)
xyplot.SetPlotColor(1,0,0,0)
xyplot.SetPlotColor(0,0,0,0)
xyplot.SetGlyphSize(0.025)
# Set text prop color (same color for backward compat with test)
# Assign same object to all text props
tprop = xyplot.GetTitleTextProperty()
tprop.SetColor(xyplot.GetProperty().GetColor())
xyplot.SetAxisTitleTextProperty(tprop)
xyplot.SetAxisLabelTextProperty(tprop)
xyplot.SetLabelFormat("%-#6.2f")
vertexGlyph = vtk.vtkSphereSource()
vertexGlyph.Update()
xyplot2 = vtk.vtkXYPlotActor()
xyplot2.AddDataSetInputConnection(probe.GetOutputPort())
xyplot2.AddDataSetInputConnection(probe2.GetOutputPort())
xyplot2.AddDataSetInputConnection(probe3.GetOutputPort())
xyplot2.GetPositionCoordinate().SetValue(0.00,0.33,0)
xyplot2.GetPosition2Coordinate().SetValue(1.0,0.33,0)
#relative to Position
xyplot2.SetXValuesToNormalizedArcLength()
xyplot2.SetNumberOfXLabels(6)
xyplot2.SetXRange(0.2,1.0)
xyplot2.SetTitle("VTK Quality vs. Alcohol Consumption")
xyplot2.SetXTitle("")
xyplot2.SetYTitle("A")
xyplot2.PlotPointsOn()
xyplot2.PlotLinesOff()
xyplot2.LegendOn()
xyplot2.SetLegendPosition(0.4,0.6)
xyplot2.SetLegendPosition2(0.40,0.25)
xyplot2.GetProperty().SetColor(1,0,0)
xyplot2.GetProperty().SetPointSize(2)
xyplot2.SetPlotSymbol(0,vertexGlyph.GetOutput())
xyplot2.SetPlotLabel(0,"Ken's Mudslide Consumption")
xyplot2.SetPlotColor(0,1,0,0)
xyplot2.SetPlotSymbol(1,cross.GetOutput())
xyplot2.SetPlotColor(1,1,0,1)
xyplot2.SetPlotLabel(1,"Bill's Beer Consumption")
xyplot2.SetPlotSymbol(2,triangle.GetOutput())
xyplot2.SetPlotColor(2,0,0,1)
xyplot2.SetPlotLabel(2,"VTK Quality")
# Set text prop color (same color for backward compat with test)
# Assign same object to all text props
tprop = xyplot2.GetTitleTextProperty()
tprop.SetColor(xyplot2.GetProperty().GetColor())
xyplot2.SetAxisTitleTextProperty(tprop)
xyplot2.SetAxisLabelTextProperty(tprop)
xyplot2.SetLabelFormat(xyplot.GetLabelFormat())
#Okay exercise data object stuff
ds2do = vtk.vtkDataSetToDataObjectFilter()
ds2do.SetInputConnection(probe.GetOutputPort())
ds2do2 = vtk.vtkDataSetToDataObjectFilter()
ds2do2.SetInputConnection(probe.GetOutputPort())
ds2do2.Update()
ds2do3 = vtk.vtkDataSetToDataObjectFilter()
ds2do3.SetInputConnection(probe.GetOutputPort())
ds2do3.Update()
xyplot3 = vtk.vtkXYPlotActor()
xyplot3.AddDataObjectInputConnection(ds2do.GetOutputPort())
xyplot3.SetDataObjectXComponent(0,2)
xyplot3.SetDataObjectYComponent(0,5)
xyplot3.SetPlotColor(0,1,0,0)
xyplot3.SetPlotLabel(0,"Mx")
xyplot3.AddDataObjectInput(ds2do2.GetOutput())
xyplot3.SetDataObjectXComponent(1,2)
xyplot3.SetDataObjectYComponent(1,6)
xyplot3.SetPlotColor(1,0,1,0)
xyplot3.SetPlotLabel(1,"My")
xyplot3.AddDataObjectInput(ds2do3.GetOutput())
xyplot3.SetDataObjectXComponent(2,2)
xyplot3.SetDataObjectYComponent(2,7)
xyplot3.SetPlotColor(2,0,0,1)
xyplot3.SetPlotLabel(2,"Mz")
xyplot3.GetPositionCoordinate().SetValue(0.0,0.0,0)
xyplot3.GetPosition2Coordinate().SetValue(1.0,0.33,0)
#relative to Position
xyplot3.SetXValuesToIndex()
xyplot3.SetNumberOfXLabels(6)
xyplot3.SetTitle("Momentum Component vs. Point Id")
xyplot3.SetXTitle("Point Id")
xyplot3.SetYTitle("M")
xyplot3.PlotPointsOn()
xyplot3.GetProperty().SetColor(0,0,1)
xyplot3.GetProperty().SetPointSize(3)
xyplot3.LegendOn()
xyplot3.SetLegendPosition(0.8,0.28)
xyplot3.SetLegendPosition2(0.20,0.20)
# Set text prop color (same color for backward compat with test)
# Assign same object to all text props
tprop = xyplot3.GetTitleTextProperty()
tprop.SetColor(xyplot3.GetProperty().GetColor())
xyplot3.SetAxisTitleTextProperty(tprop)
xyplot3.SetAxisLabelTextProperty(tprop)
xyplot3.SetLabelFormat("%4.f")
# draw an outline
outline = vtk.vtkStructuredGridOutlineFilter()
outline.SetInputData(output)
outlineMapper = vtk.vtkPolyDataMapper()
outlineMapper.SetInputConnection(outline.GetOutputPort())
outlineActor = vtk.vtkActor()
outlineActor.SetMapper(outlineMapper)
outlineActor.GetProperty().SetColor(0,0,0)
# Create graphics stuff
#
ren1 = vtk.vtkRenderer()
ren2 = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.SetMultiSamples(0)
renWin.AddRenderer(ren1)
renWin.AddRenderer(ren2)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
ren1.SetBackground(0.6784,0.8471,0.9020)
ren1.SetViewport(0,0,.5,1)
ren1.AddActor(outlineActor)
ren1.AddActor(lineActor)
ren2.SetBackground(1,1,1)
ren2.SetViewport(0.5,0.0,1.0,1.0)
ren2.AddActor2D(xyplot)
ren2.AddActor2D(xyplot2)
ren2.AddActor2D(xyplot3)
renWin.SetSize(790,400)
cam1 = ren1.GetActiveCamera()
cam1.SetClippingRange(3.95297,100)
cam1.SetFocalPoint(8.88908,0.595038,29.3342)
cam1.SetPosition(-12.3332,31.7479,41.2387)
cam1.SetViewUp(0.060772,-0.319905,0.945498)
iren.Initialize()
renWin.Render()
# render the image
#
# prevent the tk window from showing up then start the event loop
# --- end of script --
