FluxViz               http://sourceforge.net/projects/fluxviz/
---------------------------------------------------------------
Version: 1.0 		Created by: Nelis Franken	Copyright: 2008


ABOUT:
===============================================================
FluxViz is a cross-platform tool that implements parallel 
coordinates along with primitive "brushing" techniques to ease 
the visualization of high-dimensional data.

FluxViz was originally designed to visualise complex algorithm
parameter spaces, and to aid the algorithm designer in finding
trends (or optimal regions) within the parameter space.

The name FluxViz is derived from the words "flux" (specifically
the meanings "mix together different elements" and "move or 
progress freely as if in a stream" as a reflection of the
structure of parallel coordinates) and "visualization".


CONTENTS:
===============================================================

1. New in this release.

2. Getting started.

3. System requirements.

4. Downloading and compiling the source.

5. Known problems.

6. Version history.

7. Contact information.

8. Bibliography

9. Legal information.



1. NEW IN THIS RELEASE
===============================================================

- 11 March 2008:

  This is the stable release (version 1.0) of FluxViz. It also 
  contains a number of small bug-fixes and usability 
  improvements (detailed below):

  > A mouse menu has been added to ease navigating through all the
    rendering modes and options. The mouse menu is accessible by
    right-clicking inside the FluxViz application window.
    
  > A help screen has been added that doubles as a quick reference
    for the various keyboard shortcuts. The help screen is available
    by pressing the spacebar.
    
  > A couple of accidental rendering bugs have been fixed. It is now
    impossible to see the extents overlay mode while switched to
    either "Traditional" or "Full-colour" rendering modes, which
    results in correct behaviour since the extents do not mean
    anything without the specific underlying brushing enabled.

- 4 March 2008: 

  This is the first release of FluxViz, and as such should be
  considered Beta software. A short list of features include:
  
  > Parsing of structured tab-seperated data in plain-text format.
  > Full-colour and gray-scale rendering of the high-dimensional 
    input data using parallel coordinates.
  > Different "brushing" modes depending on how the data is
    interpreted (display all, best/worst 20%, best/worst 5% etc.)
  > Anti-aliased rendering.
  > Full-screen rendering.
  > Native screen-capturing to sequentially labeled TGA files.
  > A variety of ways to display labels (min/max, 20% extents,
    or detailed subdivision) at custom decimal resolution.
  > Two built-in colour schemes (one favours on-screen usage with
    a dark gray background, the other produces images suitable 
    for publication using a white background)
  > Various visibility tweaks to ensure labels are properly
    visible among the (potentially) thousands of lines:
    (darken/brighten lines, darken/brighten extents polygon,
    fade lines)
  

2. GETTING STARTED
===============================================================

2.1 Starting Fluxviz
--------------------

By reading this file I assume that you have downloaded the 
source archive and extracted it to an easily accessible 
directory of your choice. For information on how to compile the
source code, refer to section 4 below.

Fluxviz takes a formatted (tab-seperated) plain-text input file
and visualises it using OpenGL. The proper command-line usage
for Fluxviz is:

	./fluxviz inputFile nrOfRows nrOfColumns logLastColumn
	
where inputFile is the name of the input file; nrOfRows is a
positive number that represents how many data patterns need to 
be visualised; nrOfColumns is a positive number that represents
the dimensionality of the data patterns; and logLastColumn is a
single ('y' or 'n') character indicating whether or not the
data from the last column (the dependent variable) should be
log-scaled or not.

As an example, the input file "test.txt" contains the following:

0.93	1.92	0.88	1153.13	253.26
0.68	0.68	0.51	1003.13	116.93
1.67	1.67	0.02	403.13	114.24
1.18	0.18	0.76	703.13	40.22
0.18	1.18	0.27	103.13	37.9
0.24	0.24	0.67	590.63	75.52

Fluxviz can be called to visualize the data as follows:

	./fluxviz test.txt 6 5 n
	
Substituting the 'n' with a 'y' will perform a standard log-scale
on the last column's data. This is useful for data that contains
outliers, or otherwise heavily skewed data sets.


2.2 Interacting with Fluxviz
----------------------------

The primary method of interaction is through the keyboard. 
A mouse menu is available by right-clicking anywhere inside the 
main rendering window. Each option in the menu also has a
corresponding keyboard shortcut key. Press spacebar to see a
graphical overview of the various keyboard shortcuts.

Before continuing, make sure that your CAPS-lock is off. The
following key-bindings are supported:

Switching between rendering modes:
..................................

Key: '1' - Visualise the data using a single foreground and
           single background colour. This is the same as the
           traditional parallel coordinates view. This is the
           default rendering mode.
           
Key: '2' - Assign colours (non-gray) to lines that represent
           patterns in the top 5% of the data set. Patterns are 
           sorted based on the dependent variable (last column 
           values). Pressing '2' again, toggles between the 5% 
           colour mode, and a top 20% gray-scale mode.
           
Key: '3' - The same functionality as for button '2' above,
           except that it applies to the bottom 5%, and bottom
           20% of data patterns (depending on the toggle).
           
Key: '4' - Assign a unique colour to each pattern based on its
           dependent variable. All lines are coloured, and all
           patterns that share the same dependent variable
           value will share the same colour. Small values are 
           coloured blue, mid-range values green, and large
           values are coloured red. If the dependent variable
           designates a class identifier, each class will have
           its own colour, and the different classes should be
           easily visible.

Switching between labeling modes:
.................................

Key: '9' - Default mode: render only minimum and maximum values
           for all axes. Press '9' again to shuffle to next mode.
           
           Extents mode: render only the minimum and maximum
           values for the top/bottom 20% of values (depending on
           current rendering mode). A semi-transparent polygon
           will highlight the area as well. Press '9' again to 
           shuffle to next mode.
           
           Detail mode: render the overall minimum and maximum
           values for all axes, and render a subset of values at
           equally spaced intervals inbetween the min/max points.
           Press '9' again to shuffle to first (default) mode.
           
Key: ';' - For all labeling modes, increase the number of digits
           after the decimal, up to a maximum of 10 per number.
           
Key: ''' (apostrophe) - For all labeling modes, decrease the number
           of digits after the decimal, down to a minimum of 0 per
           number.

Key: '.' - For the detailed labeling mode, increase the number of
           subdivisions between labels (render finer grained
           label values), up to a maximum of 70 labels per axis.

Key: ',' - For the detailed labeling mode, decrease the number of
           subdivisions between labels, down to 6 labels per axis.

Tweaking display output:
........................

Key: 'a' - Enable/disable anti-aliased rendering. Fonts appear
           smoother when rendered in this way. It does however have
           a negative performance impact.

Key: 'f' - Enable/disable full-screen/windowed rendering.

Key: 'i' - Invert the colour display (switch between screen-
           friendly and publication-friendly colour schemes). The
           default colour scheme is screen-friendly (dark gray
           background), while the publication-friendly background
           is white.
           
Key: '-' - Decrease the opacity of the semi-transparent polygon in
           extents labeling mode.
           
Key: '=' - Increase the opacity of the semi-transparent polygon in
           extents labeling mode.

Key: '[' - Darken the display of the output lines (makes reading of
           the labels easier) in extents and detailed labeling modes.
           
Key: ']' - Brighten the display of the output lines in extents and
           detailed labeling modes.
           
Key: '0' - Enable/disable line fading. This will also improve the
           legibility of the labels, especially when visualising
           large numbers of data patterns. Lines will fade to gray
           as they approach an axis from the left.

Other additional functionality:
...............................

Key: 'c' - Capture the current window/screen's contents and
           save as a uniquely numbered TGA file (in the format
           capture_000.tga) to the current working directory.

Key: spacebar - Display the help screen.


3. SYSTEM REQUIREMENTS
===============================================================

Fluxviz can be compiled on any platform that supports ANSI C++
and OpenGL 1.2. As always, make sure that you have the latest
display drivers installed for your specific display adapter.

Fluxviz has been tested to work on x86 systems, in the following
environments:
 - Mac OS X (Leopard 10.5.2)
 - Windows XP SP2
 - Gentoo Linux (linux-2.6.24-gentoo-r3)

The source has been successfully compiled under:
 - XCode 3.0 GCC (i686-apple-darwin9-gcc-4.0.1)
 - Cygwin GCC 3.4.4 (cygming special) (gdc 0.12, using dmd 0.125)
 - Gentoo Linux GCC (x86_64-pc-linux-gnu-4.2.3)
 - Visual Studio 2005 (Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 14.00.50727.42 for 80x86)

The following versions of GLUT have also been tested to work
correctly:
 - GLUT 3.7.6 for Windows (official download)
 - GLUT 3.7 (Cygwin package opengl-1.1.0-7.tar.bz2)
 - FreeGLUT 2.4 (Gentoo package freeglut-2.4.0-r1)
 - GLUT Framework for XCode 3.0 (Mac OS X Leopard 10.5.2)
 

4. DOWNLOADING AND COMPILING THE SOURCE
===============================================================

You can download the latest release of Fluxviz from the project's
Sourceforge website: https://sourceforge.net/projects/fluxviz/

In order to compile the source, you need a modern C++ compiler
and the GLUT libraries. After compiling the code, you need to
open a command-prompt and run Fluxviz from the command line,
specifying the necessary parameters (see section 2.1).


Compiling with Visual Studio 2003/2005:
.......................................
- Download the GLUT libraries for Windows (available at
  http://www.xmission.com/~nate/glut.html) and extract them to
  a temporary directory.
- Copy the files to the correct directories:
- Copy "glut32.dll" to "C:\Windows\System".
- Copy "glut32.lib" to "C:\Program Files\Microsoft Visual Studio NET 2003\Vc7\PlatformSDK\Lib"
  (or equivalent for your version of Visual Studio)
- Copy "glut.h" to "C:\Program Files\Microsoft Visual Studio NET 2003\Vc7\PlatformSDK\Include\gl"
  (or equivalent for your version of Visual Studio)

- Create an empty C++ Win32 Console Project.
- Add the Fluxviz source file(s) to your project.
- Open the project's "Property Pages" dialog and select 
  "All Configurations" from the "Configuration:" list box.
- In the "Linker -> Input" subtree, add the following to the 
  "Additional Dependencies" text box: opengl32.lib glu32.lib glut32.lib
- Close the dialog boxes, and open the source file.
- Select the "Release" configuration from the "Configuraton:"
  list box, and compile the code.
  
Compiling with Cygwin in Windows XP SP2:
........................................
- Make sure to install the necessary packages when setting up
  Cygwin. Specifically, make sure to install the "gcc" packages,
  and the "glut" packages.
- Navigate to the directory where you extracted the Fluxviz code.
- Type the following at the command prompt to compile the code:
  
  g++ main.cpp -lglut32 -lglu32 -lopengl32 -o fluxviz.exe

Compiling under Linux:
......................
- Depending on your distribution, you may need to install the
  gcc compiler (this is sometimes grouped as a "developer"
  package). Type gcc --version at the console to determine if 
  you have gcc installed. You may also need to install the glut
  or freeglut packages. Consult your distribution's package 
  repository and documentation for more information on how to
  get ensure that you have the necessary packages installed.
- Using the console, navigate to the directory where you extracted 
  the Fluxviz source code. Type the following to compile the code:
  
  g++ main.cpp -L/usr/X11R6/lib -lglut -lGL -lGLU -lXmu -lX11 -lXi -lm -o fluxviz
  
- Depending on your distribution, you may get some errors with
  regards to the -lX related linker flags. Simply remove the
  flags that cause the errors, and try to compile again.
  
Compiling under Mac OS X using XCode 3.0:
.........................................
- Using XCode, create a new "Command Line Utility / C++ Tool" project.
- Add the OpenGL and GLUT Frameworks to your project.
- Select "Release" in the "Active Build Configuration" list box.
- Click on "Build"


5. KNOWN PROBLEMS
===============================================================

- When compiling with Cygwin (GCC 3.4.4) for Windows XP in 
  emulation under Parallels 2.5 for Mac OS X, labels will not
  render correctly in the extents and detailed modes. This seems
  to be an issue with the generic display driver. Upgrading to
  Parallels 3.0 should solve the problem (although this still
  needs to be confirmed).

- The 'fullscreen' functionality in Linux currently simply
  maximises the window without removing the window borders and
  other decorations. This seems to be problem with GLUT not
  sending the correct state information to the underlying window
  manager. It is recommended to rather manually maximise the
  window using the 'maximise' button for the current window.
  The screen capture functionality will correctly capture a
  manually-maximised window.
  

6. VERSION HISTORY
===============================================================

- 11 March 2008: Bug fixes and usability improvements. 
                 First stable release (version 1.0)
                 
- 4 March 2008: First release (version 1.0 Beta)


7. CONTACT INFORMATION
===============================================================

Feel free to contact the original author via e-mail directly at 
nelisfranken@gmail.com, or make use of the relevant contact
options at the Fluxviz project page: https://sourceforge.net/projects/fluxviz/


8. BIBLIOGRAPHY
===============================================================

Parallel Coordinates was invented by Alfred Inselberg in 1980. 
Visit http://www.math.tau.ac.il/~aiisreal/ for more information
on the technique.

Many enhancements to the core visualization approach has been
proposed over the years. Fluxviz still has a lot of scope for
growth, and the bibliography will be updated as this happens.


9. LEGAL INFORMATION
===============================================================

FluxViz v1.0 - A flexible parallel coordinates visualization 
tool. Copyright (C) 2008 Nelis Franken

This program is free software: you can redistribute it and/or 
modify it under the terms of the GNU General Public License as 
published by the Free Software Foundation, either version 3 of 
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public 
License along with this program. If not, see 
<http://www.gnu.org/licenses/>
