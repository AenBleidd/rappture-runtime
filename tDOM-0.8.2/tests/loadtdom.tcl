# loadtdom.tcl --
#
# This file is [source]d by all.tcl and all test files, to ensure, that
# the tcltest package and the lastest tdom build is present.
#
# RCS: @(#) $Id: loadtdom.tcl,v 1.8 2007/08/05 18:48:21 rolf Exp $
#

if {[lsearch [namespace children] ::tcltest] == -1} {
    if {$tcl_version < 8.2} {
        puts stderr "sourcing def.tcl"
        source [file join [file dir [info script]] defs.tcl]
        set auto_path [pwd]
    } else {
        package require tcltest
        namespace import ::tcltest::*
    }
}

if {[catch {package present -exact tdom 0.8.2}]} {
    package require -exact tdom 0.8.2
} else {
    if {[lsearch [namespace children] ::tDOM] == -1} {
        # tcldomsh without the script library. Source the lib.
        source [file join [file dir [info script]] ../lib tdom.tcl]
    }
}

