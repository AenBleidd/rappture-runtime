# Visualization Toolkit (VTK) Tcl package configuration.

package ifneeded vtkinit {4.4} {
  namespace eval ::vtk::init {
    proc load_library_package {libName libPath {libPrefix {lib}}} {
      set libExt [info sharedlibextension]
      set currentDirectory [pwd]
      set libFile [file join $libPath "$libPrefix$libName$libExt"]
      if {[catch "cd {$libPath}; load {$libFile}" errorMessage]} {
        puts $errorMessage
      }
      cd $currentDirectory
    }
    proc require_package {name {version {4.4}}} {
      if {[catch "package require -exact $name $version" errorMessage]} {
        puts $errorMessage
        return 0
      } else {
        return 1
      }
    }
    set version {4.4}
    set kits {}
    foreach kit { base Common Filtering IO Imaging Graphics
                  Rendering Hybrid 
                   Parallel } {
      lappend kits [string tolower "${kit}"]
    }
  }
  package provide vtkinit {4.4}
}

foreach kit { Common Filtering IO Imaging Graphics
              Rendering Hybrid 
               Parallel } {
  package ifneeded "vtk${kit}TCL" {4.4} "
    package require -exact vtkinit {4.4}
    ::vtk::init::load_library_package {vtk${kit}TCL} {[file dirname [file dirname [info script]]]}
  "
  package ifneeded "vtk[string tolower ${kit}]" {4.4} "
    package require -exact vtkinit {4.4}
    if {\[catch {source \[file join {[file dirname [info script]]} {vtk[string tolower ${kit}]} {vtk[string tolower ${kit}].tcl}\]} errorMessage\]} {
      puts \$errorMessage
    }
  "
}

foreach src {vtk vtkbase vtkinteraction vtktesting} {
  package ifneeded ${src} {4.4} "
    package require -exact vtkinit {4.4}
    if {\[catch {source \[file join {[file dirname [info script]]} {$src} {$src.tcl}\]} errorMessage\]} {
      puts \$errorMessage
    }
  "
}
