>>> Volumetric Image Processing Tool <<<

--- Definitions ---
Imagebase -> A selection of images in .raw format and a single .data file


--- Instructions for use ---
The imagebase must be stored inside a folder. This folder must have the same name
as the imagebase. In addition the folder must be place in the directory of the source code.

For example: Given the argument "MRI", the program will attempt to open the
file: "./MRI/MRI.data" and to read the data from "./MRI/MRIx.raw" files

-- Program Arguments --

<imageBase> [-d i j output_file_name] [-x i output_file_name]

<imageBased> sould be replace with the name of the image base

-d  will trigger a difference map between images i and j and store the result to file output_file_name
-x  will trigger an extract and save of image i. Two files are generated output_file_name.data and 
    output_file_name.raw


--- MAKEFILE ---
The makefile will allow the program to be compiled, run and binaries to be cleaned.

Command -> Action
_________________________________________________________________________________________________
>> Standard Commands <<
make                            -> Compile all source code
make clean                      -> Remove all binaries
make run args="<Custom args>"   -> Runs the volimage binary with the argument(s) given between ""

>> Debugging commands <<
make runblank                   -> Used for debugging only (requires MRI scan to be present)
make runx                       -> Used for debugging only (requires MRI scan to be present)
make rund                       -> Used for debugging only (requires MRI scan to be present)
_________________________________________________________________________________________________

Note: The debugging commands essentially use a predefined argument string which allowed
for less typing during the debugging process. The predefined string may be modified
to use a different imagebase.


--- Source Code Description ---
>> volimage.cpp <<
This is the 'driver' and contains the main() method. This source is only concerned with processing
the arguments passed in by the user. Once the arguments have been processed the appropriate
function in the processor source is called.

>> processor.h <<
This header file contains the VolImage class declaration. All the methods that where prescribed in
the assignment brief are declared here. Some additional functions where implemented as it seemed fit.

>> processor.cpp <<
This is the source for all operations pertaining to the manipulation file i/o operations.
The implemtation of all the functions is done in this source file.


--- Student Details ---
Work of Justin Wylie
Student number: WYLJUS002