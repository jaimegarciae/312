Jaime Eugenio Garcia JEG3954 

Testing main.c

The Makefile included in the folder sets up a suite that allows to test the program contained in main.c, which takes as input a list of numbers (ending with the sentinel 999) and stores them in a dynamically allocated array.

Tests:
	Test1: CheckInputRead (provided in assignment) checks whether the input is read correctly from the keyboard
	Test2: emptyArray checks if the program works properly when the array it receives is empty
	Test3: boundaryTest checks that the program properly allocates memory and stores values correctly when it receives 10 numbers as input (original memory allocation size)
	Test4: overBoundary checks that the program correctly does memory reallocation and liberation after needing to increase array size
	Test5: regularList checks with regular input (under 10 numbers) if program correctly stores and prints numbers, and frees the memory properly
	Test6: negativeNumbers checks that the program also takes negative numbers as input and manipulates them correctly
	Test7: largeNumbers checks that the program can rightly take large numbers, store them, and manipulate them

How to use suite:
To run each of the tests simply type "make test#" (replace # with the test number you wish to run) and it will take the input to the program from the input file, output to a new output file, and compare this generated output with the expected output from the expected output file.

How to tell if a test passed:
Given that the "diff" command is used to compare the program's output with the expected output (both stored in files), whenever a test has passed, there will not be further output under the "diff" command. If there is any extra output generated, the test has failed, and the output will indicate the differences between the program's output and the expected output; the program needs corrections if any of the tests fails.
