#!/usr/bin/env perl
# Time-stamp: <2002-01-18 16:17:26 barre>
#
# Summary ?
#
# barre : Sebastien Barre <sebastien.barre@kitware.com>
#
# 0.2 (barre)
#   - add --headerext s : expected header file extension
#   - add --headernewext s : new header file extension
#   - add --headernewsuffix s : new header file suffix
#
# 0.1 (barre)
#   - first release

use Carp;
use Cwd 'abs_path';
use Getopt::Long;
use Fcntl;
use File::Basename;
use File::Find;
use File::Path;
use strict;

my ($VERSION, $PROGNAME, $AUTHOR) = (0.2, $0, "Sebastien Barre");
$PROGNAME =~ s/^.*[\\\/]//;
print "$PROGNAME $VERSION, by $AUTHOR\n";

# -------------------------------------------------------------------------
# Defaults (add options as you want : "verbose" => 1 for default verbose mode)

my %default = 
  (
   codematch => "\w(?:->|\.)InvokeEvent\s*\(\s*(vtkCommand::\w+)[\s,]",
   dirs => ["../../Charts",
            "../../Common",
            "../../Filtering",
            "../../GenericFiltering",
            "../../GenericFiltering/Testing/Cxx",
            "../../Geovis",
            "../../Graphics",
            "../../GUISupport/MFC",
            "../../GUISupport/Qt",
            "../../Hybrid",
            "../../Imaging",
            "../../Infovis",
            "../../IO",
            "../../Parallel",
            "../../Rendering",
            "../../TextAnalysis",
            "../../Views",
            "../../VolumeRendering",
            "../../Widgets"],
   headerext => "h",
   headernewext => "h",
   headernewsuffix => "",
   label => "Events",
   project => "VTK",
   relativeto => "",
   sectionmatch => "^vtkCommand::(\w)",
   sectionmatch2 => "^vtk(\w)",
   store => "doc_VTK_events.dox",
   store2 => "doc_VTK_events2.dox",
   title => "Event To Classes",
   title2 => "Class to Events",
   to => "../../../VTK-doxygen",
   unique => "v",
   weight => 90000
  );

# -------------------------------------------------------------------------
# Parse options

my %args;
Getopt::Long::Configure("bundling");
GetOptions (\%args, "help", "verbose|v", "debug", "label=s", "codematch=s", "headerext=s", "headernewext=s", "headernewsuffix=s", "project=s", "relativeto=s", "sectionmatch=s", "sectionmatch2=s", "store=s", "store2=s", "title=s", "title2=s", "to=s", "unique=s", "weight=i");

if (exists $args{"help"}) {
    print <<"EOT";
Usage : $PROGNAME [--help] [--verbose|-v] [--limit n] [--stop file] [--sectionmatch str] [--sectionmatch2 file] [--store file] [--store2 file] [--title string] [--title2 string] [--to path] [--relativeto path] [--weight n] [files|directories...]
  --help            : this message
  --verbose|-v      : verbose (display filenames while processing)
  --codematch str   : codematch used to generate matches against code (default: $default{codematch})
  --headerext s     : expected header file extension (default: $default{headerext})
  --headernewext s  : new header file extension (default: $default{headernewext})
  --headernewsuffix s : new header file suffix (default: $default{headernewsuffix})
  --project name    : project name, used to uniquify (default: $default{project})
  --label str       : use string as label in class page (default: $default{label})
  --sectionmatch s  : use string against match to get unique alpha section (default: $default{sectionmatch})
  --sectionmatch2 s : use string against class to get unique alpha section (default: $default{sectionmatch2})
  --store file      : use 'file' to store 'match to classes' (default: $default{store})
  --store2 file     : use 'file' to store 'classes to matches' (default: $default{store2})
  --title str       : use string as title in 'match to classes' (default: $default{title})
  --title2 str      : use string as title in 'class to matches' (default: $default{title2})
  --to path         : use 'path' as destination directory (default : $default{to})
  --unique str      : use string as a unique page identifier among "Class To..." pages generated by this script (otherwise MD5) (default : $default{unique})
  --relativeto path : each file/directory to document is considered relative to 'path', where --to and --relativeto should be absolute (default: $default{relativeto})
  --weight n     : use 'n' as an approximation of the maximum page weight (default : $default{weight})

Example:
  $PROGNAME
EOT
    exit;
}

$args{"debug"} = $default{"debug"} if exists $default{"debug"};
$args{"verbose"} = 1 if exists $default{"verbose"};
$args{"codematch"} = $default{"codematch"} if ! exists $args{"codematch"};
$args{"headerext"} = $default{"headerext"} if ! exists $args{"headerext"};
$args{"headernewext"} = $default{"headernewext"} if ! exists $args{"headernewext"};
$args{"headernewsuffix"} = $default{"headernewsuffix"} 
if ! exists $args{"headernewsuffix"};
$args{"project"} = $default{"project"} if ! exists $args{"project"};
$args{"label"} = $default{"label"} if ! exists $args{"label"};
$args{"sectionmatch"} = $default{"sectionmatch"} if ! exists $args{"sectionmatch"};
$args{"store"} = $default{"store"} if ! exists $args{"store"};
$args{"title"} = $default{"title"} if ! exists $args{"title"};
$args{"sectionmatch2"} = $default{"sectionmatch2"} if ! exists $args{"sectionmatch2"};
$args{"store2"} = $default{"store2"} if ! exists $args{"store2"};
$args{"title2"} = $default{"title2"} if ! exists $args{"title2"};
$args{"to"} = $default{"to"} if ! exists $args{"to"};
$args{"to"} =~ s/[\\\/]*$// if exists $args{"to"};
$args{"relativeto"} = $default{"relativeto"} if ! exists $args{"relativeto"};
$args{"relativeto"} =~ s/[\\\/]*$// if exists $args{"relativeto"};
$args{"unique"} = $default{"unique"} if ! exists $args{"unique"};
$args{"weight"} = $default{"weight"} if ! exists $args{"weight"};

my $os_is_win = ($^O =~ m/(MSWin32|Cygwin)/i);
my $open_file_as_text = $os_is_win ? O_TEXT : 0;
my $start_time = time();

# -------------------------------------------------------------------------
# Collect all files and directories

print "Collecting files...\n";

push @ARGV, @{$default{dirs}} if !@ARGV;

my @files;
foreach my $file (@ARGV) {
    if (-f $file) {
        push @files, $file;
    } elsif (-d $file) {
        find sub { push @files, $File::Find::name; }, $file;
    }
}

# -------------------------------------------------------------------------
# Parse implementation files corresponding to headers

print "Parsing implementation files and updating headers...\n";
my $intermediate_time = time();

# %allclasses reports all class that have been parsed.
# %allmatches reports all matches that have been found.
# %match2classes associates a match to a class name and reports how many 
# times that association was found.
# Example: $match2classes{"vtkCommand::Event"}{"vtkMarchingCubes"} = 2
# %class2matches associates a class name to a match

my %allclasses;
my %allmatches;
my %class2matches;
my %match2classes;

my ($nb_files, $nb_replaced_files, $nb_classes_matching) = (0, 0);
undef $/;  # slurp mode

foreach my $source (@files) {

    # Skip if not a VTK header file or has no implementation file

    next if $source !~ /(\w?vtk[^\\\/]*)\.$args{"headerext"}\Z/;
    my ($class, $implem) = ($1, $source);
    $implem =~ s/\.$args{"headerext"}\Z/\.cxx/;
    next if ! -e $implem;

    ++$nb_files;

    # Open the implementation file, read it entirely

    sysopen(IMPLEMFILE, $implem, O_RDONLY|$open_file_as_text)
      or croak "$PROGNAME: unable to open $implem\n";
    my $implemfile = <IMPLEMFILE>;
    close(IMPLEMFILE);
    
    # Remove all comments
   
    $implemfile =~ s/\/\*.*?\*\/|\/\/.*?$//gms;

    # Grab matches, skip to next file if none found

    my @matches = $implemfile =~ m/$args{"codematch"}/gms;

    next if ! @matches;
    $allclasses{$class} = 1;

    # Setup match <-> class relationships

    foreach my $match (@matches) {
        $allmatches{$match}++;
        $class2matches{$class}{$match}++;
        $match2classes{$match}{$class}++;
    }

    # Figure out the name of the already-converted-to-doxygen header
    # file using --to and --relativeto destination file now

    my $header;

    # If source has absolute path, just use the basename (unless a
    # relativeto path has been set) otherwise remove the ../ component
    # before the source filename, so that it might be appended to the
    # "to" directory.

    if ($source =~ m/^(\/|[a-zA-W]\:[\/\\])/) {
        if ($args{"relativeto"}) {
            my ($dir, $absrel) = (abs_path(dirname($source)), 
                                  abs_path($args{"relativeto"}));
            $dir =~ s/$absrel//;
            $header = $args{"to"} . $dir . '/' . basename($source);
        } else {
            $header = $args{"to"} . '/' . basename($source);
        }
    } else {
        $source =~ s/^(\.\.[\/\\])*//;
        $header = $args{"to"} . '/' . $source;
    }
    $header =~ s/\.$args{"headerext"}\Z/$args{"headernewsuffix"}\.$args{"headernewext"}/;

    next if ! -e $header;

    # Read that header

    sysopen(HEADERFILE, $header, O_RDONLY|$open_file_as_text)
      or croak "$PROGNAME: unable to open $header\n";
    my $headerfile = <HEADERFILE>;
    close(HEADERFILE);
    
    # Search for the documentation block (@class ...)

    if ($headerfile !~ /(.*\/\*\!\s+)(\@class\s.+?)(\*\/.*)/gms) {
        carp  "$PROGNAME: no documentation block in $header ! (skipping)\n";
        next;
    }
    my ($pre, $block, $post) = ($1, $2, $3);

    # Create new doc section, insert it into block
    
    my $preamble = "    \@par      " . $args{"label"} . ":\n";
    my $doc = $preamble . 
      "              " . join(" ", keys %{$class2matches{$class}}) . "\n";

    if ($block !~ s/($preamble.+?)(\s*\@par|\z)/$doc$2/gms) {
        $block .= "\n$doc";
    }

    # Write new header

    sysopen(HEADERFILE, $header, 
            O_WRONLY|O_TRUNC|O_CREAT|$open_file_as_text)
      or croak "$PROGNAME: unable to open $header\n";
    print HEADERFILE $pre . $block . $post;
    close(HEADERFILE);

    ++$nb_replaced_files;
}

print " => parsed in ", time() - $intermediate_time, " s.\n";

# -------------------------------------------------------------------------
# Build the page summary documentation

# $indent is the indentation string

my $indent = "    ";

# $header is the Doxygen string summarizing what has been documented as well
# as the credits.

my $header;
my (@summary, @credits);

push @summary, 
  "  - $nb_files implementation file(s) returning " . scalar (keys %allmatches) . " word(s) for " . scalar (keys %allclasses) . " classe(es) on " . localtime(),
  "  - $nb_replaced_files file(s) updated";

push @credits, 
  "\@version $VERSION",
  "\@author \@c $PROGNAME, by $AUTHOR";

$header = $indent . join("\n$indent", @summary) . 
  "\n\n$indent" . join("\n$indent", @credits) . "\n\n";

# -------------------------------------------------------------------------
# (first part - match 2 classes)

if ($args{"store"}) {

    print "Building page doc (match 2 classes)...\n";

    # @words is the array of words to document

    my @words = sort keys %allmatches;

    # $prefix is a unique prefix that is appended to each link

    my $prefix = "mc_" . $args{"project"} . "_";
    if (exists $args{"unique"}) {
        $prefix .= $args{"unique"};
    } else {
        $prefix .= md5_hex($args{"label"} . $args{"title"});
    }
    $prefix = lc($prefix);

    # word_section_name returns the short string describing a word section

    sub word_section_name {
        my ($word) = @_;
        return $word;
    }
    
    # word_section_doc returns the doxygen doc for a word

    sub word_section_doc {
        my ($word) = @_;
        return "  - " . join(", ", sort keys %{$match2classes{$word}}) . "\n";
    }

    # word_section_alpha returns the single alpha char corresponding to that
    # word's section.

    sub word_section_alpha {
        my ($word) = @_;
        $word =~ /$args{"sectionmatch"}/;
        return $1;
    }

    my $page_doc = build_page_doc($indent,
                                  $args{"title"},
                                  \@words, 
                                  $prefix, 
                                  \&word_section_name, 
                                  \&word_section_doc,
                                  \&word_section_alpha,
                                  $header,
                                  "",
                                  $args{"to"} . "/" . $args{"store"});
}


# -------------------------------------------------------------------------
# (second part - class to matches)

if ($args{"store2"}) {

    print "Building page doc (classes to matches)...\n";

    # @words is the array of words to document

    my @words = sort keys %allclasses;

    # $prefix is a unique prefix that is appended to each link

    my $prefix = "mc2_" . $args{"project"} . "_";
    if (exists $args{"unique"}) {
        $prefix .= $args{"unique"};
    } else {
        $prefix .= md5_hex($args{"label"} . $args{"title"});
    }
    $prefix = lc($prefix);

    # word_section_name returns the short string describing a word section

    sub word_section_name2 {
        my ($word) = @_;
        return $word;
    }
    
    # word_section_doc returns the doxygen doc for a word

    sub word_section_doc2 {
        my ($word) = @_;
        return "  - " . join(", ", sort keys %{$class2matches{$word}}) . "\n";
    }

    # word_section_alpha returns the single alpha char corresponding to that
    # word's section.

    sub word_section_alpha2 {
        my ($word) = @_;
        $word =~ /$args{"sectionmatch2"}/;
        return $1;
    }

    my $page_doc = build_page_doc($indent,
                                  $args{"title2"},
                                  \@words, 
                                  $prefix, 
                                  \&word_section_name2, 
                                  \&word_section_doc2,
                                  \&word_section_alpha2,
                                  $header,
                                  "",
                                  $args{"to"} . "/" . $args{"store2"});
}

print join("\n", @summary), "\n";
print "Finished in ", time() - $start_time, " s.\n";

# -------------------------------------------------------------------------

sub build_page_doc {

    # $indent is the indentation string
    # $rwords is a reference to the array of words to document
    # $prefix is a unique prefix that is appended to each link
    # word_section_name returns the short string describing a word section
    # word_section_doc returns the doxygen doc for a word
    # word_section_alpha returns the single alpha char corresponding to that
    # word's section.
    # $header is the Doxygen string summarizing what has been documented as 
    # well as the credits.
    # $footer is a Doxygen string appended to each the resulting page
    # $destination_file is the name of the file where this page should be
    # written to.

    my ($ident, $title, $rwords, $prefix, $rword_section_name, $rword_section_doc, $rword_section_alpha, $header, $footer, $destination_file) = @_;

    # %words_doc is a hash associating a word to its Doxygen doc (string)

    my %words_doc;

    # %sections_words is a hash associating a section (alphabetical letter) to
    # an array of words belonging to that section.
    #   Ex: $sections_words{"C"} => ("contour", "cut")
    # %sections_weight is a hash associating a section to its weight (the sum 
    # of the weights of each word belonging to that section).
    # @sections is the array holding the name of all sections

    my (%sections_words, %sections_weight, @sections);

    # $navbar is the Doxygen string describing the sections' navigation bar
    
    my $navbar;
    
    my $intermediate_time = time();
    
    # Browse each word

    foreach my $word (@$rwords) {

        my @temp;
        push @temp, &$rword_section_name($word), &$rword_section_doc($word);
        $words_doc{$word} = $indent . join("\n$indent", @temp) . "\n";

        # Update section(s) and section(s) weight(s)

        my $section = &$rword_section_alpha($word);
        push @{$sections_words{$section}}, $word;
        $sections_weight{$section} += length($words_doc{$word});
        
        print " => ", $word, "\n" if exists $args{"verbose"};
    }

    print " => ", scalar @$rwords, " words(s) documented in ", time() - $intermediate_time, " s.\n";
    
    @sections = sort keys %sections_words;

    # Build the navbar
    
    my @temp;
    foreach my $section (@sections) {
        push @temp, "\@ref ${prefix}_section_$section \"$section\"";
    }
    $navbar = "$indent\@par Navigation: \n$indent\[" . 
      join(" | ", @temp) . "]\n";

    # Add the (approximate) weight of the (header + navbar) to each section

    my $total_weight = 0;
    my $header_weight = length($indent) + 24 + length($navbar);

    foreach my $section (@sections) {
        $sections_weight{$section} += $header_weight;
        $total_weight += $sections_weight{$section};
    }

    if (exists $args{"verbose"}) {
        foreach my $section (@sections) {
            printf("\t- %s : %6d\n", $section, $sections_weight{$section});
        }
    }

    print " => total weight is $total_weight in ", scalar @sections, " section(s) (mean is ", int($total_weight / scalar @sections), ")\n";

    # Compute the alphabetical groups by joining sections depending on weights

    print "Computing alphabetical group(s)/page(s)...\n";

    # %groups is a hash associating a group id (int) to an array of sections 
    # namesbelonging to that group.
    #   Ex: $groups{"0"} => ("A", "B", "C")
    # %groups_weight is a hash associating a group id to its weight (the sum
    # of the weights of each section belonging to that group).

    my (%groups, %groups_weight);

    my $groupid = 0;

    # Remove a section one by one, and put it in a group until the group if 
    # full,then create a next group, etc., until the sections are exhausted.

    my @sections_temp = @sections;
    while (@sections_temp) {
        $groups_weight{$groupid} = $sections_weight{$sections_temp[0]};
        push @{$groups{$groupid}}, shift @sections_temp;
        while (@sections_temp && 
               ($groups_weight{$groupid} +$sections_weight{$sections_temp[0]}) 
               <= $args{"weight"}) {
            $groups_weight{$groupid} += $sections_weight{$sections_temp[0]};
            push @{$groups{$groupid}}, shift @sections_temp;
        }
        $groupid++;
    }

    if (exists $args{"verbose"}) {
        foreach my $groupid (sort {$a <=> $b} keys %groups) {
            printf("\t- %02d (weight: %7d) : %s\n", $groupid, 
                   $groups_weight{$groupid}, join(", ", @{$groups{$groupid}}));
        }
    }

    print " => max weight is ", $args{"weight"}, " per group/page, but a section can not be divided\n";
    print " => ", scalar  keys %groups, " group(s) for ", scalar @sections, " section(s)\n";

    # Build documentation page
    # Browse each group, each section in this group, each word in this section

    my $page_doc;

    foreach my $groupid (sort {$a <=> $b} keys %groups) {

        my $fromto = $groups{$groupid}[0];
        $fromto .= ".." . $groups{$groupid}[scalar @{$groups{$groupid}} - 1]
          if scalar @{$groups{$groupid}} > 1;

        $page_doc .= 
          "/*! \@page ${prefix}_$groupid $title ($fromto)\n\n$header"; 

        foreach my $section (@{$groups{$groupid}}) {
            $page_doc .=
              "\n$indent\@section ${prefix}_section_$section $section\n\n$navbar\n";
            foreach my $word (@{$sections_words{$section}}) {
                $page_doc .= $words_doc{$word}, "\n";
            }
            print "\t- $section\n" if exists $args{"verbose"};
        }
        $page_doc .= "$footer\n*/\n\n";
    }

    print "Writing documentation to ", $destination_file, "...\n";

    $intermediate_time = time();

    sysopen(DEST_FILE, 
            $destination_file, 
            O_WRONLY|O_TRUNC|O_CREAT|$open_file_as_text)
     or croak "$PROGNAME: unable to open destination file $destination_file\n";
    print DEST_FILE $page_doc;
    close(DEST_FILE);

    print " => written in ", time() - $intermediate_time, " s.\n";
}

