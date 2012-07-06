/*=========================================================================

  Program:   Visualization Toolkit
  Module:    TestTensorProbeWidget.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// Test for vtkTensorProbeWidget class
//
#include "vtkSmartPointer.h"
#include "vtkActor.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkTestUtilities.h"
#include "vtkTensorProbeRepresentation.h"
#include "vtkTensorProbeWidget.h"
#include "vtkCamera.h"
#include "vtkDoubleArray.h"
#include "vtkXMLPolyDataReader.h"
#include "vtkXMLPolyDataWriter.h"
#include "vtkPoints.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkTesting.h"

const char TestTensorProbeWidgetEventLog[] =
  "# StreamVersion 1 i\n"
  "ConfigureEvent 0 0 0 0 0 0 0\n"
  "EnterEvent 367 152 0 0 0 0 0\n"
  "MouseMoveEvent 367 154 0 0 0 0 0\n"
  "MouseMoveEvent 494 202 0 0 0 0 0\n"
  "LeftButtonPressEvent 52 31 0 0 0 0 0\n"
  "MouseMoveEvent 52 33 0 0 0 0 0\n"
  "RenderEvent 52 33 0 0 0 0 0\n"
  "MouseMoveEvent 52 35 0 0 0 0 0\n"
  "RenderEvent 52 35 0 0 0 0 0\n"
  "MouseMoveEvent 52 37 0 0 0 0 0\n"
  "RenderEvent 52 37 0 0 0 0 0\n"
  "MouseMoveEvent 52 39 0 0 0 0 0\n"
  "RenderEvent 52 39 0 0 0 0 0\n"
  "MouseMoveEvent 52 41 0 0 0 0 0\n"
  "RenderEvent 52 41 0 0 0 0 0\n"
  "MouseMoveEvent 52 42 0 0 0 0 0\n"
  "RenderEvent 52 42 0 0 0 0 0\n"
  "MouseMoveEvent 52 44 0 0 0 0 0\n"
  "RenderEvent 52 44 0 0 0 0 0\n"
  "MouseMoveEvent 52 45 0 0 0 0 0\n"
  "RenderEvent 52 45 0 0 0 0 0\n"
  "MouseMoveEvent 52 46 0 0 0 0 0\n"
  "RenderEvent 52 46 0 0 0 0 0\n"
  "MouseMoveEvent 52 47 0 0 0 0 0\n"
  "RenderEvent 52 47 0 0 0 0 0\n"
  "MouseMoveEvent 53 48 0 0 0 0 0\n"
  "RenderEvent 53 48 0 0 0 0 0\n"
  "MouseMoveEvent 53 49 0 0 0 0 0\n"
  "RenderEvent 53 49 0 0 0 0 0\n"
  "MouseMoveEvent 53 50 0 0 0 0 0\n"
  "RenderEvent 53 50 0 0 0 0 0\n"
  "MouseMoveEvent 54 52 0 0 0 0 0\n"
  "RenderEvent 54 52 0 0 0 0 0\n"
  "MouseMoveEvent 55 53 0 0 0 0 0\n"
  "RenderEvent 55 53 0 0 0 0 0\n"
  "MouseMoveEvent 55 54 0 0 0 0 0\n"
  "RenderEvent 55 54 0 0 0 0 0\n"
  "MouseMoveEvent 56 56 0 0 0 0 0\n"
  "RenderEvent 56 56 0 0 0 0 0\n"
  "MouseMoveEvent 57 57 0 0 0 0 0\n"
  "RenderEvent 57 57 0 0 0 0 0\n"
  "MouseMoveEvent 57 59 0 0 0 0 0\n"
  "RenderEvent 57 59 0 0 0 0 0\n"
  "MouseMoveEvent 58 61 0 0 0 0 0\n"
  "RenderEvent 58 61 0 0 0 0 0\n"
  "MouseMoveEvent 59 63 0 0 0 0 0\n"
  "RenderEvent 59 63 0 0 0 0 0\n"
  "MouseMoveEvent 60 65 0 0 0 0 0\n"
  "RenderEvent 60 65 0 0 0 0 0\n"
  "MouseMoveEvent 61 66 0 0 0 0 0\n"
  "RenderEvent 61 66 0 0 0 0 0\n"
  "MouseMoveEvent 61 68 0 0 0 0 0\n"
  "RenderEvent 61 68 0 0 0 0 0\n"
  "MouseMoveEvent 62 69 0 0 0 0 0\n"
  "RenderEvent 62 69 0 0 0 0 0\n"
  "MouseMoveEvent 63 70 0 0 0 0 0\n"
  "RenderEvent 63 70 0 0 0 0 0\n"
  "MouseMoveEvent 64 72 0 0 0 0 0\n"
  "RenderEvent 64 72 0 0 0 0 0\n"
  "MouseMoveEvent 64 73 0 0 0 0 0\n"
  "RenderEvent 64 73 0 0 0 0 0\n"
  "MouseMoveEvent 65 75 0 0 0 0 0\n"
  "RenderEvent 65 75 0 0 0 0 0\n"
  "MouseMoveEvent 66 76 0 0 0 0 0\n"
  "RenderEvent 66 76 0 0 0 0 0\n"
  "MouseMoveEvent 67 78 0 0 0 0 0\n"
  "RenderEvent 67 78 0 0 0 0 0\n"
  "MouseMoveEvent 68 80 0 0 0 0 0\n"
  "RenderEvent 68 80 0 0 0 0 0\n"
  "MouseMoveEvent 69 81 0 0 0 0 0\n"
  "RenderEvent 69 81 0 0 0 0 0\n"
  "MouseMoveEvent 69 83 0 0 0 0 0\n"
  "RenderEvent 69 83 0 0 0 0 0\n"
  "MouseMoveEvent 73 87 0 0 0 0 0\n"
  "RenderEvent 73 87 0 0 0 0 0\n"
  "MouseMoveEvent 74 89 0 0 0 0 0\n"
  "RenderEvent 74 89 0 0 0 0 0\n"
  "MouseMoveEvent 75 91 0 0 0 0 0\n"
  "RenderEvent 75 91 0 0 0 0 0\n"
  "MouseMoveEvent 79 95 0 0 0 0 0\n"
  "RenderEvent 79 95 0 0 0 0 0\n"
  "MouseMoveEvent 80 97 0 0 0 0 0\n"
  "RenderEvent 80 97 0 0 0 0 0\n"
  "MouseMoveEvent 81 99 0 0 0 0 0\n"
  "RenderEvent 81 99 0 0 0 0 0\n"
  "MouseMoveEvent 85 103 0 0 0 0 0\n"
  "RenderEvent 85 103 0 0 0 0 0\n"
  "MouseMoveEvent 86 105 0 0 0 0 0\n"
  "RenderEvent 86 105 0 0 0 0 0\n"
  "MouseMoveEvent 87 107 0 0 0 0 0\n"
  "RenderEvent 87 107 0 0 0 0 0\n"
  "MouseMoveEvent 89 108 0 0 0 0 0\n"
  "RenderEvent 89 108 0 0 0 0 0\n"
  "MouseMoveEvent 90 110 0 0 0 0 0\n"
  "RenderEvent 90 110 0 0 0 0 0\n"
  "MouseMoveEvent 90 111 0 0 0 0 0\n"
  "RenderEvent 90 111 0 0 0 0 0\n"
  "MouseMoveEvent 91 113 0 0 0 0 0\n"
  "RenderEvent 91 113 0 0 0 0 0\n"
  "MouseMoveEvent 95 117 0 0 0 0 0\n"
  "RenderEvent 95 117 0 0 0 0 0\n"
  "MouseMoveEvent 96 118 0 0 0 0 0\n"
  "RenderEvent 96 118 0 0 0 0 0\n"
  "MouseMoveEvent 97 120 0 0 0 0 0\n"
  "RenderEvent 97 120 0 0 0 0 0\n"
  "MouseMoveEvent 98 121 0 0 0 0 0\n"
  "RenderEvent 98 121 0 0 0 0 0\n"
  "MouseMoveEvent 99 122 0 0 0 0 0\n"
  "RenderEvent 99 122 0 0 0 0 0\n"
  "MouseMoveEvent 100 124 0 0 0 0 0\n"
  "RenderEvent 100 124 0 0 0 0 0\n"
  "MouseMoveEvent 101 125 0 0 0 0 0\n"
  "RenderEvent 101 125 0 0 0 0 0\n"
  "MouseMoveEvent 102 127 0 0 0 0 0\n"
  "RenderEvent 102 127 0 0 0 0 0\n"
  "MouseMoveEvent 103 128 0 0 0 0 0\n"
  "RenderEvent 103 128 0 0 0 0 0\n"
  "MouseMoveEvent 104 129 0 0 0 0 0\n"
  "RenderEvent 104 129 0 0 0 0 0\n"
  "MouseMoveEvent 105 130 0 0 0 0 0\n"
  "RenderEvent 105 130 0 0 0 0 0\n"
  "MouseMoveEvent 105 132 0 0 0 0 0\n"
  "RenderEvent 105 132 0 0 0 0 0\n"
  "MouseMoveEvent 106 133 0 0 0 0 0\n"
  "RenderEvent 106 133 0 0 0 0 0\n"
  "MouseMoveEvent 107 133 0 0 0 0 0\n"
  "RenderEvent 107 133 0 0 0 0 0\n"
  "MouseMoveEvent 108 135 0 0 0 0 0\n"
  "RenderEvent 108 135 0 0 0 0 0\n"
  "MouseMoveEvent 108 136 0 0 0 0 0\n"
  "RenderEvent 108 136 0 0 0 0 0\n"
  "MouseMoveEvent 109 137 0 0 0 0 0\n"
  "RenderEvent 109 137 0 0 0 0 0\n"
  "MouseMoveEvent 110 138 0 0 0 0 0\n"
  "RenderEvent 110 138 0 0 0 0 0\n"
  "MouseMoveEvent 111 140 0 0 0 0 0\n"
  "RenderEvent 111 140 0 0 0 0 0\n"
  "MouseMoveEvent 112 141 0 0 0 0 0\n"
  "RenderEvent 112 141 0 0 0 0 0\n"
  "MouseMoveEvent 113 143 0 0 0 0 0\n"
  "RenderEvent 113 143 0 0 0 0 0\n"
  "MouseMoveEvent 113 144 0 0 0 0 0\n"
  "RenderEvent 113 144 0 0 0 0 0\n"
  "MouseMoveEvent 114 145 0 0 0 0 0\n"
  "RenderEvent 114 145 0 0 0 0 0\n"
  "MouseMoveEvent 115 147 0 0 0 0 0\n"
  "RenderEvent 115 147 0 0 0 0 0\n"
  "MouseMoveEvent 116 149 0 0 0 0 0\n"
  "RenderEvent 116 149 0 0 0 0 0\n"
  "MouseMoveEvent 117 150 0 0 0 0 0\n"
  "RenderEvent 117 150 0 0 0 0 0\n"
  "MouseMoveEvent 117 152 0 0 0 0 0\n"
  "RenderEvent 117 152 0 0 0 0 0\n"
  "MouseMoveEvent 118 153 0 0 0 0 0\n"
  "RenderEvent 118 153 0 0 0 0 0\n"
  "MouseMoveEvent 119 154 0 0 0 0 0\n"
  "RenderEvent 119 154 0 0 0 0 0\n"
  "MouseMoveEvent 120 156 0 0 0 0 0\n"
  "RenderEvent 120 156 0 0 0 0 0\n"
  "MouseMoveEvent 120 157 0 0 0 0 0\n"
  "RenderEvent 120 157 0 0 0 0 0\n"
  "MouseMoveEvent 121 158 0 0 0 0 0\n"
  "RenderEvent 121 158 0 0 0 0 0\n"
  "MouseMoveEvent 121 160 0 0 0 0 0\n"
  "RenderEvent 121 160 0 0 0 0 0\n"
  "MouseMoveEvent 122 161 0 0 0 0 0\n"
  "RenderEvent 122 161 0 0 0 0 0\n"
  "MouseMoveEvent 123 161 0 0 0 0 0\n"
  "RenderEvent 123 161 0 0 0 0 0\n"
  "MouseMoveEvent 123 162 0 0 0 0 0\n"
  "RenderEvent 123 162 0 0 0 0 0\n"
  "MouseMoveEvent 124 164 0 0 0 0 0\n"
  "RenderEvent 124 164 0 0 0 0 0\n"
  "MouseMoveEvent 124 165 0 0 0 0 0\n"
  "RenderEvent 124 165 0 0 0 0 0\n"
  "MouseMoveEvent 125 166 0 0 0 0 0\n"
  "RenderEvent 125 166 0 0 0 0 0\n"
  "MouseMoveEvent 125 168 0 0 0 0 0\n"
  "RenderEvent 125 168 0 0 0 0 0\n"
  "MouseMoveEvent 126 169 0 0 0 0 0\n"
  "RenderEvent 126 169 0 0 0 0 0\n"
  "MouseMoveEvent 127 169 0 0 0 0 0\n"
  "RenderEvent 127 169 0 0 0 0 0\n"
  "MouseMoveEvent 128 171 0 0 0 0 0\n"
  "RenderEvent 128 171 0 0 0 0 0\n"
  "MouseMoveEvent 128 173 0 0 0 0 0\n"
  "RenderEvent 128 173 0 0 0 0 0\n"
  "MouseMoveEvent 129 174 0 0 0 0 0\n"
  "RenderEvent 129 174 0 0 0 0 0\n"
  "MouseMoveEvent 130 176 0 0 0 0 0\n"
  "RenderEvent 130 176 0 0 0 0 0\n"
  "MouseMoveEvent 131 177 0 0 0 0 0\n"
  "RenderEvent 131 177 0 0 0 0 0\n"
  "MouseMoveEvent 132 178 0 0 0 0 0\n"
  "RenderEvent 132 178 0 0 0 0 0\n"
  "MouseMoveEvent 132 180 0 0 0 0 0\n"
  "RenderEvent 132 180 0 0 0 0 0\n"
  "MouseMoveEvent 133 181 0 0 0 0 0\n"
  "RenderEvent 133 181 0 0 0 0 0\n"
  "MouseMoveEvent 133 183 0 0 0 0 0\n"
  "RenderEvent 133 183 0 0 0 0 0\n"
  "MouseMoveEvent 137 187 0 0 0 0 0\n"
  "RenderEvent 137 187 0 0 0 0 0\n"
  "MouseMoveEvent 138 189 0 0 0 0 0\n"
  "RenderEvent 138 189 0 0 0 0 0\n"
  "MouseMoveEvent 139 191 0 0 0 0 0\n"
  "RenderEvent 139 191 0 0 0 0 0\n"
  "MouseMoveEvent 140 193 0 0 0 0 0\n"
  "RenderEvent 140 193 0 0 0 0 0\n"
  "MouseMoveEvent 141 195 0 0 0 0 0\n"
  "RenderEvent 141 195 0 0 0 0 0\n"
  "MouseMoveEvent 143 196 0 0 0 0 0\n"
  "RenderEvent 143 196 0 0 0 0 0\n"
  "MouseMoveEvent 143 198 0 0 0 0 0\n"
  "RenderEvent 143 198 0 0 0 0 0\n"
  "MouseMoveEvent 145 199 0 0 0 0 0\n"
  "RenderEvent 145 199 0 0 0 0 0\n"
  "MouseMoveEvent 147 205 0 0 0 0 0\n"
  "RenderEvent 147 205 0 0 0 0 0\n"
  "MouseMoveEvent 148 206 0 0 0 0 0\n"
  "RenderEvent 148 206 0 0 0 0 0\n"
  "MouseMoveEvent 149 208 0 0 0 0 0\n"
  "RenderEvent 149 208 0 0 0 0 0\n"
  "MouseMoveEvent 150 210 0 0 0 0 0\n"
  "RenderEvent 150 210 0 0 0 0 0\n"
  "MouseMoveEvent 151 211 0 0 0 0 0\n"
  "RenderEvent 151 211 0 0 0 0 0\n"
  "MouseMoveEvent 152 213 0 0 0 0 0\n"
  "RenderEvent 152 213 0 0 0 0 0\n"
  "MouseMoveEvent 154 214 0 0 0 0 0\n"
  "RenderEvent 154 214 0 0 0 0 0\n"
  "MouseMoveEvent 155 216 0 0 0 0 0\n"
  "RenderEvent 155 216 0 0 0 0 0\n"
  "MouseMoveEvent 156 217 0 0 0 0 0\n"
  "RenderEvent 156 217 0 0 0 0 0\n"
  "MouseMoveEvent 157 218 0 0 0 0 0\n"
  "RenderEvent 157 218 0 0 0 0 0\n"
  "MouseMoveEvent 158 219 0 0 0 0 0\n"
  "RenderEvent 158 219 0 0 0 0 0\n"
  "MouseMoveEvent 159 220 0 0 0 0 0\n"
  "RenderEvent 159 220 0 0 0 0 0\n"
  "MouseMoveEvent 159 221 0 0 0 0 0\n"
  "RenderEvent 159 221 0 0 0 0 0\n"
  "MouseMoveEvent 160 222 0 0 0 0 0\n"
  "RenderEvent 160 222 0 0 0 0 0\n"
  "MouseMoveEvent 161 223 0 0 0 0 0\n"
  "RenderEvent 161 223 0 0 0 0 0\n"
  "MouseMoveEvent 162 224 0 0 0 0 0\n"
  "RenderEvent 162 224 0 0 0 0 0\n"
  "MouseMoveEvent 163 225 0 0 0 0 0\n"
  "RenderEvent 163 225 0 0 0 0 0\n"
  "MouseMoveEvent 163 226 0 0 0 0 0\n"
  "RenderEvent 163 226 0 0 0 0 0\n"
  "MouseMoveEvent 164 227 0 0 0 0 0\n"
  "RenderEvent 164 227 0 0 0 0 0\n"
  "MouseMoveEvent 168 231 0 0 0 0 0\n"
  "RenderEvent 168 231 0 0 0 0 0\n"
  "MouseMoveEvent 169 232 0 0 0 0 0\n"
  "RenderEvent 169 232 0 0 0 0 0\n"
  "MouseMoveEvent 170 233 0 0 0 0 0\n"
  "RenderEvent 170 233 0 0 0 0 0\n"
  "MouseMoveEvent 174 237 0 0 0 0 0\n"
  "RenderEvent 174 237 0 0 0 0 0\n"
  "MouseMoveEvent 175 238 0 0 0 0 0\n"
  "RenderEvent 175 238 0 0 0 0 0\n"
  "MouseMoveEvent 177 239 0 0 0 0 0\n"
  "RenderEvent 177 239 0 0 0 0 0\n"
  "MouseMoveEvent 181 243 0 0 0 0 0\n"
  "RenderEvent 181 243 0 0 0 0 0\n"
  "MouseMoveEvent 182 244 0 0 0 0 0\n"
  "RenderEvent 182 244 0 0 0 0 0\n"
  "MouseMoveEvent 184 245 0 0 0 0 0\n"
  "RenderEvent 184 245 0 0 0 0 0\n"
  "MouseMoveEvent 188 249 0 0 0 0 0\n"
  "RenderEvent 188 249 0 0 0 0 0\n"
  "MouseMoveEvent 189 250 0 0 0 0 0\n"
  "RenderEvent 189 250 0 0 0 0 0\n"
  "MouseMoveEvent 191 251 0 0 0 0 0\n"
  "RenderEvent 191 251 0 0 0 0 0\n"
  "MouseMoveEvent 192 253 0 0 0 0 0\n"
  "RenderEvent 192 253 0 0 0 0 0\n"
  "MouseMoveEvent 193 254 0 0 0 0 0\n"
  "RenderEvent 193 254 0 0 0 0 0\n"
  "MouseMoveEvent 197 258 0 0 0 0 0\n"
  "RenderEvent 197 258 0 0 0 0 0\n"
  "MouseMoveEvent 198 259 0 0 0 0 0\n"
  "RenderEvent 198 259 0 0 0 0 0\n"
  "MouseMoveEvent 200 260 0 0 0 0 0\n"
  "RenderEvent 200 260 0 0 0 0 0\n"
  "MouseMoveEvent 201 261 0 0 0 0 0\n"
  "RenderEvent 201 261 0 0 0 0 0\n"
  "MouseMoveEvent 202 262 0 0 0 0 0\n"
  "RenderEvent 202 262 0 0 0 0 0\n"
  "MouseMoveEvent 204 263 0 0 0 0 0\n"
  "RenderEvent 204 263 0 0 0 0 0\n"
  "MouseMoveEvent 205 264 0 0 0 0 0\n"
  "RenderEvent 205 264 0 0 0 0 0\n"
  "MouseMoveEvent 206 265 0 0 0 0 0\n"
  "RenderEvent 206 265 0 0 0 0 0\n"
  "MouseMoveEvent 208 266 0 0 0 0 0\n"
  "RenderEvent 208 266 0 0 0 0 0\n"
  "MouseMoveEvent 209 267 0 0 0 0 0\n"
  "RenderEvent 209 267 0 0 0 0 0\n"
  "MouseMoveEvent 210 268 0 0 0 0 0\n"
  "RenderEvent 210 268 0 0 0 0 0\n"
  "MouseMoveEvent 212 268 0 0 0 0 0\n"
  "RenderEvent 212 268 0 0 0 0 0\n"
  "MouseMoveEvent 213 269 0 0 0 0 0\n"
  "RenderEvent 213 269 0 0 0 0 0\n"
  "MouseMoveEvent 214 269 0 0 0 0 0\n"
  "RenderEvent 214 269 0 0 0 0 0\n"
  "MouseMoveEvent 215 270 0 0 0 0 0\n"
  "RenderEvent 215 270 0 0 0 0 0\n"
  "MouseMoveEvent 217 271 0 0 0 0 0\n"
  "RenderEvent 217 271 0 0 0 0 0\n"
  "MouseMoveEvent 218 271 0 0 0 0 0\n"
  "RenderEvent 218 271 0 0 0 0 0\n"
  "MouseMoveEvent 219 272 0 0 0 0 0\n"
  "RenderEvent 219 272 0 0 0 0 0\n"
  "MouseMoveEvent 220 272 0 0 0 0 0\n"
  "RenderEvent 220 272 0 0 0 0 0\n"
  "MouseMoveEvent 221 272 0 0 0 0 0\n"
  "RenderEvent 221 272 0 0 0 0 0\n"
  "MouseMoveEvent 222 272 0 0 0 0 0\n"
  "RenderEvent 222 272 0 0 0 0 0\n"
  "MouseMoveEvent 223 273 0 0 0 0 0\n"
  "RenderEvent 223 273 0 0 0 0 0\n"
  "MouseMoveEvent 224 273 0 0 0 0 0\n"
  "RenderEvent 224 273 0 0 0 0 0\n"
  "MouseMoveEvent 225 273 0 0 0 0 0\n"
  "RenderEvent 225 273 0 0 0 0 0\n"
  "MouseMoveEvent 225 274 0 0 0 0 0\n"
  "RenderEvent 225 274 0 0 0 0 0\n"
  "MouseMoveEvent 226 274 0 0 0 0 0\n"
  "RenderEvent 226 274 0 0 0 0 0\n"
  "MouseMoveEvent 227 275 0 0 0 0 0\n"
  "RenderEvent 227 275 0 0 0 0 0\n"
  "MouseMoveEvent 228 275 0 0 0 0 0\n"
  "RenderEvent 228 275 0 0 0 0 0\n"
  "MouseMoveEvent 229 276 0 0 0 0 0\n"
  "RenderEvent 229 276 0 0 0 0 0\n"
  "MouseMoveEvent 230 276 0 0 0 0 0\n"
  "RenderEvent 230 276 0 0 0 0 0\n"
  "MouseMoveEvent 231 276 0 0 0 0 0\n"
  "RenderEvent 231 276 0 0 0 0 0\n"
  "MouseMoveEvent 232 276 0 0 0 0 0\n"
  "RenderEvent 232 276 0 0 0 0 0\n"
  "MouseMoveEvent 234 277 0 0 0 0 0\n"
  "RenderEvent 234 277 0 0 0 0 0\n"
  "MouseMoveEvent 236 278 0 0 0 0 0\n"
  "RenderEvent 236 278 0 0 0 0 0\n"
  "MouseMoveEvent 237 279 0 0 0 0 0\n"
  "RenderEvent 237 279 0 0 0 0 0\n"
  "MouseMoveEvent 238 279 0 0 0 0 0\n"
  "RenderEvent 238 279 0 0 0 0 0\n"
  "MouseMoveEvent 239 279 0 0 0 0 0\n"
  "RenderEvent 239 279 0 0 0 0 0\n"
  "MouseMoveEvent 240 280 0 0 0 0 0\n"
  "RenderEvent 240 280 0 0 0 0 0\n"
  "MouseMoveEvent 241 280 0 0 0 0 0\n"
  "RenderEvent 241 280 0 0 0 0 0\n"
  "MouseMoveEvent 242 280 0 0 0 0 0\n"
  "RenderEvent 242 280 0 0 0 0 0\n"
  "MouseMoveEvent 244 280 0 0 0 0 0\n"
  "RenderEvent 244 280 0 0 0 0 0\n"
  "MouseMoveEvent 245 281 0 0 0 0 0\n"
  "RenderEvent 245 281 0 0 0 0 0\n"
  "MouseMoveEvent 247 282 0 0 0 0 0\n"
  "RenderEvent 247 282 0 0 0 0 0\n"
  "MouseMoveEvent 253 284 0 0 0 0 0\n"
  "RenderEvent 253 284 0 0 0 0 0\n"
  "MouseMoveEvent 255 285 0 0 0 0 0\n"
  "RenderEvent 255 285 0 0 0 0 0\n"
  "MouseMoveEvent 261 291 0 0 0 0 0\n"
  "RenderEvent 261 291 0 0 0 0 0\n"
  "MouseMoveEvent 267 293 0 0 0 0 0\n"
  "RenderEvent 267 293 0 0 0 0 0\n"
  "MouseMoveEvent 273 297 0 0 0 0 0\n"
  "RenderEvent 273 297 0 0 0 0 0\n"
  "MouseMoveEvent 277 301 0 0 0 0 0\n"
  "RenderEvent 277 301 0 0 0 0 0\n"
  "MouseMoveEvent 279 301 0 0 0 0 0\n"
  "RenderEvent 279 301 0 0 0 0 0\n"
  "MouseMoveEvent 280 302 0 0 0 0 0\n"
  "RenderEvent 280 302 0 0 0 0 0\n"
  "MouseMoveEvent 282 302 0 0 0 0 0\n"
  "RenderEvent 282 302 0 0 0 0 0\n"
  "MouseMoveEvent 282 303 0 0 0 0 0\n"
  "RenderEvent 282 303 0 0 0 0 0\n"
  "MouseMoveEvent 283 304 0 0 0 0 0\n"
  "RenderEvent 283 304 0 0 0 0 0\n"
  "MouseMoveEvent 284 304 0 0 0 0 0\n"
  "RenderEvent 284 304 0 0 0 0 0\n"
  "MouseMoveEvent 284 305 0 0 0 0 0\n"
  "RenderEvent 284 305 0 0 0 0 0\n"
  "MouseMoveEvent 285 305 0 0 0 0 0\n"
  "RenderEvent 285 305 0 0 0 0 0\n"
  "MouseMoveEvent 286 305 0 0 0 0 0\n"
  "RenderEvent 286 305 0 0 0 0 0\n"
  "MouseMoveEvent 287 305 0 0 0 0 0\n"
  "RenderEvent 287 305 0 0 0 0 0\n"
  "MouseMoveEvent 288 305 0 0 0 0 0\n"
  "RenderEvent 288 305 0 0 0 0 0\n"
  "MouseMoveEvent 289 305 0 0 0 0 0\n"
  "RenderEvent 289 305 0 0 0 0 0\n"
  "MouseMoveEvent 291 305 0 0 0 0 0\n"
  "RenderEvent 291 305 0 0 0 0 0\n"
  "MouseMoveEvent 292 305 0 0 0 0 0\n"
  "RenderEvent 292 305 0 0 0 0 0\n"
  "MouseMoveEvent 294 306 0 0 0 0 0\n"
  "RenderEvent 294 306 0 0 0 0 0\n"
  "MouseMoveEvent 295 306 0 0 0 0 0\n"
  "RenderEvent 295 306 0 0 0 0 0\n"
  "MouseMoveEvent 296 306 0 0 0 0 0\n"
  "RenderEvent 296 306 0 0 0 0 0\n"
  "MouseMoveEvent 298 306 0 0 0 0 0\n"
  "RenderEvent 298 306 0 0 0 0 0\n"
  "MouseMoveEvent 299 306 0 0 0 0 0\n"
  "RenderEvent 299 306 0 0 0 0 0\n"
  "MouseMoveEvent 300 306 0 0 0 0 0\n"
  "RenderEvent 300 306 0 0 0 0 0\n"
  "MouseMoveEvent 302 307 0 0 0 0 0\n"
  "RenderEvent 302 307 0 0 0 0 0\n"
  "MouseMoveEvent 304 307 0 0 0 0 0\n"
  "RenderEvent 304 307 0 0 0 0 0\n"
  "MouseMoveEvent 306 307 0 0 0 0 0\n"
  "RenderEvent 306 307 0 0 0 0 0\n"
  "MouseMoveEvent 307 307 0 0 0 0 0\n"
  "RenderEvent 307 307 0 0 0 0 0\n"
  "MouseMoveEvent 308 308 0 0 0 0 0\n"
  "RenderEvent 308 308 0 0 0 0 0\n"
  "MouseMoveEvent 310 308 0 0 0 0 0\n"
  "RenderEvent 310 308 0 0 0 0 0\n"
  "MouseMoveEvent 311 308 0 0 0 0 0\n"
  "RenderEvent 311 308 0 0 0 0 0\n"
  "MouseMoveEvent 312 308 0 0 0 0 0\n"
  "RenderEvent 312 308 0 0 0 0 0\n"
  "MouseMoveEvent 314 308 0 0 0 0 0\n"
  "RenderEvent 314 308 0 0 0 0 0\n"
  "MouseMoveEvent 315 309 0 0 0 0 0\n"
  "RenderEvent 315 309 0 0 0 0 0\n"
  "MouseMoveEvent 317 309 0 0 0 0 0\n"
  "RenderEvent 317 309 0 0 0 0 0\n"
  "MouseMoveEvent 319 309 0 0 0 0 0\n"
  "RenderEvent 319 309 0 0 0 0 0\n"
  "MouseMoveEvent 325 311 0 0 0 0 0\n"
  "RenderEvent 325 311 0 0 0 0 0\n"
  "MouseMoveEvent 331 313 0 0 0 0 0\n"
  "RenderEvent 331 313 0 0 0 0 0\n"
  "MouseMoveEvent 337 315 0 0 0 0 0\n"
  "RenderEvent 337 315 0 0 0 0 0\n"
  "MouseMoveEvent 345 317 0 0 0 0 0\n"
  "RenderEvent 345 317 0 0 0 0 0\n"
  "MouseMoveEvent 348 317 0 0 0 0 0\n"
  "RenderEvent 348 317 0 0 0 0 0\n"
  "MouseMoveEvent 354 319 0 0 0 0 0\n"
  "RenderEvent 354 319 0 0 0 0 0\n"
  "MouseMoveEvent 357 319 0 0 0 0 0\n"
  "RenderEvent 357 319 0 0 0 0 0\n"
  "MouseMoveEvent 363 321 0 0 0 0 0\n"
  "RenderEvent 363 321 0 0 0 0 0\n"
  "MouseMoveEvent 369 323 0 0 0 0 0\n"
  "RenderEvent 369 323 0 0 0 0 0\n"
  "MouseMoveEvent 370 323 0 0 0 0 0\n"
  "RenderEvent 370 323 0 0 0 0 0\n"
  "MouseMoveEvent 372 324 0 0 0 0 0\n"
  "RenderEvent 372 324 0 0 0 0 0\n"
  "MouseMoveEvent 373 324 0 0 0 0 0\n"
  "RenderEvent 373 324 0 0 0 0 0\n"
  "MouseMoveEvent 374 324 0 0 0 0 0\n"
  "RenderEvent 374 324 0 0 0 0 0\n"
  "MouseMoveEvent 376 324 0 0 0 0 0\n"
  "RenderEvent 376 324 0 0 0 0 0\n"
  "MouseMoveEvent 377 324 0 0 0 0 0\n"
  "RenderEvent 377 324 0 0 0 0 0\n"
  "MouseMoveEvent 377 325 0 0 0 0 0\n"
  "RenderEvent 377 325 0 0 0 0 0\n"
  "MouseMoveEvent 378 325 0 0 0 0 0\n"
  "RenderEvent 378 325 0 0 0 0 0\n"
  "MouseMoveEvent 379 325 0 0 0 0 0\n"
  "RenderEvent 379 325 0 0 0 0 0\n"
  "MouseMoveEvent 380 326 0 0 0 0 0\n"
  "RenderEvent 380 326 0 0 0 0 0\n"
  "MouseMoveEvent 381 326 0 0 0 0 0\n"
  "RenderEvent 381 326 0 0 0 0 0\n"
  "MouseMoveEvent 382 327 0 0 0 0 0\n"
  "RenderEvent 382 327 0 0 0 0 0\n"
  "MouseMoveEvent 383 327 0 0 0 0 0\n"
  "RenderEvent 383 327 0 0 0 0 0\n"
  "MouseMoveEvent 384 328 0 0 0 0 0\n"
  "RenderEvent 384 328 0 0 0 0 0\n"
  "MouseMoveEvent 385 328 0 0 0 0 0\n"
  "RenderEvent 385 328 0 0 0 0 0\n"
  "MouseMoveEvent 386 328 0 0 0 0 0\n"
  "RenderEvent 386 328 0 0 0 0 0\n"
  "MouseMoveEvent 387 328 0 0 0 0 0\n"
  "RenderEvent 387 328 0 0 0 0 0\n"
  "MouseMoveEvent 388 328 0 0 0 0 0\n"
  "RenderEvent 388 328 0 0 0 0 0\n"
  "MouseMoveEvent 389 329 0 0 0 0 0\n"
  "RenderEvent 389 329 0 0 0 0 0\n"
  "MouseMoveEvent 390 329 0 0 0 0 0\n"
  "RenderEvent 390 329 0 0 0 0 0\n"
  "MouseMoveEvent 391 330 0 0 0 0 0\n"
  "RenderEvent 391 330 0 0 0 0 0\n"
  "MouseMoveEvent 392 330 0 0 0 0 0\n"
  "RenderEvent 392 330 0 0 0 0 0\n"
  "MouseMoveEvent 393 331 0 0 0 0 0\n"
  "RenderEvent 393 331 0 0 0 0 0\n"
  "MouseMoveEvent 394 331 0 0 0 0 0\n"
  "RenderEvent 394 331 0 0 0 0 0\n"
  "MouseMoveEvent 395 332 0 0 0 0 0\n"
  "RenderEvent 395 332 0 0 0 0 0\n"
  "MouseMoveEvent 396 332 0 0 0 0 0\n"
  "RenderEvent 396 332 0 0 0 0 0\n"
  "MouseMoveEvent 397 332 0 0 0 0 0\n"
  "RenderEvent 397 332 0 0 0 0 0\n"
  "MouseMoveEvent 398 332 0 0 0 0 0\n"
  "RenderEvent 398 332 0 0 0 0 0\n"
  "MouseMoveEvent 399 332 0 0 0 0 0\n"
  "RenderEvent 399 332 0 0 0 0 0\n"
  "MouseMoveEvent 400 332 0 0 0 0 0\n"
  "RenderEvent 400 332 0 0 0 0 0\n"
  "MouseMoveEvent 401 333 0 0 0 0 0\n"
  "RenderEvent 401 333 0 0 0 0 0\n"
  "MouseMoveEvent 402 333 0 0 0 0 0\n"
  "RenderEvent 402 333 0 0 0 0 0\n"
  "MouseMoveEvent 403 333 0 0 0 0 0\n"
  "RenderEvent 403 333 0 0 0 0 0\n"
  "MouseMoveEvent 403 334 0 0 0 0 0\n"
  "RenderEvent 403 334 0 0 0 0 0\n"
  "MouseMoveEvent 404 334 0 0 0 0 0\n"
  "RenderEvent 404 334 0 0 0 0 0\n"
  "MouseMoveEvent 405 334 0 0 0 0 0\n"
  "RenderEvent 405 334 0 0 0 0 0\n"
  "MouseMoveEvent 406 335 0 0 0 0 0\n"
  "RenderEvent 406 335 0 0 0 0 0\n"
  "MouseMoveEvent 407 335 0 0 0 0 0\n"
  "RenderEvent 407 335 0 0 0 0 0\n"
  "MouseMoveEvent 408 336 0 0 0 0 0\n"
  "RenderEvent 408 336 0 0 0 0 0\n"
  "MouseMoveEvent 409 336 0 0 0 0 0\n"
  "RenderEvent 409 336 0 0 0 0 0\n"
  "MouseMoveEvent 410 336 0 0 0 0 0\n"
  "RenderEvent 410 336 0 0 0 0 0\n"
  "MouseMoveEvent 411 336 0 0 0 0 0\n"
  "RenderEvent 411 336 0 0 0 0 0\n"
  "MouseMoveEvent 412 336 0 0 0 0 0\n"
  "RenderEvent 412 336 0 0 0 0 0\n"
  "MouseMoveEvent 413 337 0 0 0 0 0\n"
  "RenderEvent 413 337 0 0 0 0 0\n"
  "MouseMoveEvent 414 337 0 0 0 0 0\n"
  "RenderEvent 414 337 0 0 0 0 0\n"
  "MouseMoveEvent 415 338 0 0 0 0 0\n"
  "RenderEvent 415 338 0 0 0 0 0\n"
  "MouseMoveEvent 416 338 0 0 0 0 0\n"
  "RenderEvent 416 338 0 0 0 0 0\n"
  "MouseMoveEvent 417 338 0 0 0 0 0\n"
  "RenderEvent 417 338 0 0 0 0 0\n"
  "MouseMoveEvent 418 339 0 0 0 0 0\n"
  "RenderEvent 418 339 0 0 0 0 0\n"
  "MouseMoveEvent 419 339 0 0 0 0 0\n"
  "RenderEvent 419 339 0 0 0 0 0\n"
  "MouseMoveEvent 420 339 0 0 0 0 0\n"
  "RenderEvent 420 339 0 0 0 0 0\n"
  "MouseMoveEvent 421 340 0 0 0 0 0\n"
  "RenderEvent 421 340 0 0 0 0 0\n"
  "MouseMoveEvent 422 340 0 0 0 0 0\n"
  "RenderEvent 422 340 0 0 0 0 0\n"
  "LeftButtonReleaseEvent 422 340 0 0 0 0 0\n"
  ;


int TestTensorProbeWidget( int argc, char *argv[] )
{ 
  vtkSmartPointer<vtkXMLPolyDataReader> r =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  const char *cfname=
    vtkTestUtilities::ExpandDataFileName(argc, argv,
                                         "Data/SyntheticPolyline.vtp");
  r->SetFileName(cfname);
  r->Update();
  delete[] cfname;
  
  vtkPolyData *pd = r->GetOutput();

  // Create the RenderWindow, Renderer
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  vtkSmartPointer<vtkTensorProbeWidget> w =
    vtkSmartPointer<vtkTensorProbeWidget>::New(); 
  w->SetInteractor(iren);
  vtkTensorProbeRepresentation * rep = 
    vtkTensorProbeRepresentation::SafeDownCast(
      w->GetRepresentation());
  rep->SetTrajectory(pd);

  renWin->SetSize(512,512);
  renWin->Render();
  iren->Initialize();
  w->EnabledOn();

  ren1->ResetCamera();
  ren1->ResetCameraClippingRange();
  ren1->GetActiveCamera()->SetPosition(4.50141, 2.82662, 0.42005);
  ren1->GetActiveCamera()->SetViewUp(-0.529751, 0.83346, -0.157189);
  ren1->GetActiveCamera()->SetFocalPoint(3.06943, 2.31262, 2.5207);
  renWin->Render();


  return vtkTesting::InteractorEventLoop( 
      argc, argv, iren, TestTensorProbeWidgetEventLog );
}
