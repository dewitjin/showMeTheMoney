## Synopsis

Note: 	text file = dataOut.txt <br />
	data binary file = clients.dat <br />
	index binary file = lastname.idx <br />
	
This project teaches you how to read from a text file, creates a data binary file with the data in the text file, converts the data binary file into an index binary file and displays the data in various ways (i.e. sorting by last name, natural order etc).

## Code Example

I started the project by building each feature one by one.  If you try to learn the code from scratch or build a project this big by doing everything at once, there is a strong chance you will fail. 

 My recommendation is to try to build this piece by piece in the following order:

1) Build the convert.c file and display.c

convert.c should be able to read a text file and create a data binary file (with the data inside the text file)<br />
display.c should be able to read from the data binary file and display the data onto the console<br />

2) Build index.c and modify convert.c and display.c

convert.c file should be able to read from the data binary file and create a index file (index.c) with useful information (i.e. data key, file position) //TODO have multiple indices in one index file, right now it’s just one index (lastname, file position)<br />
display.c file should be able to read the index file, grab the file position stored inside the index, and then use the file position to locate the account data inside the data binary file<br />

3) Build a startProgram.c file, datadefs.h, convert.h, index.h, display.h and modify the old files to include the appropriate header files to reduce code repetition 

//TODO change assign06.c to startProgram.c<br />

The biggestest challenge in refractoring my code to different header files is getting a redefinition error.  In order to debug it, I would define the struct in different headers to see what worked and what didn't. My error was fixed by including datadefs.h once in startProgram.c, and in all other header files (covert.h, index.h and display.h).  I didn't have to include the other source files in startProgram.c.  In the other source files (covert.c, index.c and display.c) I included the appropriate header files (covert.h, index.h and display.h). I think my redefinition error occured because I tried to include the other source files in startProgram.c, and somewhere the program tried to redefine the code inside.  It was hard to debug because the debugger wouldn't jump to a file twice, it just threw the error.

startProgram.c should include the datadefs.h, display a menu to convert, index, display natural order, display by last name ascending order, and exit <br />

//TODO after adding more sorting feature, remember to add more options in the menu<br />

other header files should include datadefs.h (because it stores main struct and program definitions)<br />
all other source code (convert.c, index.c, display.c) should have no main function and include the appropriate header files<br />

Note: I borrowed code from different places and modified them when I needed too - borrowed code are noted down in source files<br />

## Motivation

This project exist because it was assign to me.  However, I find it useful in a lot of application that I am building and wanted to share the code.  The most difficult part about the whole project was not knowing what to do when the data was displaying incorrectly.  Since the assignment required the data to be stored in binary, it was not easy to just check if the data was written out correctly.  Fortunately, Hynek showed me how I could start fixing the problem.  Hynek told me I had to make sure the data binary files contained all the right data first.  So Hynek wrote me some code to read the data binary file to see the messed up data and then I went on fixing from there.

## Installation

In order to run this code, you need an integrated development environment like Visual Studio. This program is created using Visual Studio 2015 and started with an empty Win32 Console Application.

## API Reference

None. Just included a standard C programing header files.

## Tests

None.

## Contributors

The best way to reach me is via my email at dewi.tjin + @ + gmail.com.

If you would like to contribute please fork the repo and I will review code.

## License

Copyright 2017 DEWI TJIN

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.




