# AsciiEngine
3D Ascii Game Engine from scratch. 
Using AsciiGL (https://github.com/JFonS/AsciiGL) as graphical engine (also made from scratch by us just using ncurses to print the characters).

To use it, you must get first the "asciiGL.a" static lib file. In order to do this just do:

   # Lets compile the asciiGL.a static lib file and get the AsciiGL/*.h headers
     git clone https://github.com/JFonS/AsciiEngine   #First do this step
     git clone https://github.com/JFonS/AsciiGL       
     cd AsciiGL           
   # AsciiGL/compile.sh will copy all the necessary files (lib .a file and *.h headers) into "../AsciiEngine"
     ./compile.sh

   # Now its time to compile AsciiEngine
     cd ../AsciiEngine
     qmake
     make clean
     make
     
     #enjoy

Follow the steps in the exact order as above.

