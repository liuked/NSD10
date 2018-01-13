--------------------
NSD: Practical 10-11
--------------------

Authors:
- ANDREA FERLINI
- LUCA DE MORI

Programming Language:
- C++ (objects oriented)

Content:

This repository contains the code to solve the exercises of Practical10-11 (NSD-TME, M2 UPMC).

Fall Semester 2017/18


1. FOLDER STRUCTURE

The main directory contains the following folders:
	
a. /src:          Contains all the libraries
c. /plot_scriptd: Contains the scripts to plot the graphs
	

2. FILE FORMAT SPECIFICATION

	2.1 LINK LIST
	Lines of tuples describing contacts among participants, written in the format:

	n1 n2 ts te

	n1, n2: identifiers of the two nodes involved in the contact
	ts:     time at which the contact started;
	te:     time at which the last contact between n1 and n2 has been recorded. 

	NB: contacts are undirected and, by convention, n1 < n2.

	2.2 EVENT LIST 
	List of the event of creation and deletion of links that occur at each time interval. Each line is written in the format:

	t n1 n2 e

	t:      time instant (the file is ordered by this key)
	n1, n2: identifiers of the two nodes involved in the contact
	e:      event that occurs in on the link between n1 and n2;
	        it could be
	        C: the link has been created in t
	        S: the link has been deleted (the link existed until t-1)


3. CODE STRUCTURE

	3.1 FILE ARTICULATION

	- main.cpp
	Contains an example of how to use the functions using as source the Infocom06 dataset
	contained in Infocom06/ directory.

	- GraphFileHandler.cpp, GraphFileHandler.h
	this file contains all the required functions to solve the Exercises. 
	The functions are static, so they can be directly called as GraphFileHandler::<function-name>(<args>).
	***See the .h file for the function description.

	- DynAdjList.cpp, DynAdjList.h
	contains a structure to dynamically load a graph (adding and removing nodes)
	It is not optimized for big graphs (it doesn't use the contiguous storage).

	- Node.cpp, Node.h
	structure used in the AdjList

	- DynamicVector.h
	Structure that can dinamically grow. Used in some functions

	- Event.cpp, Event.h
	Structure used in the event-list grnerator function

	AdjacencyList.cpp, AdjacencyList.h
	Class to load the adjacency list of a graph from a file in the format: 
	"x y" (with x, y integers >1)




3. USAGE
	

	3.1 LAUNCH THE PROGRAM

	We recommend to put the graph file inside a folder and use it ar root for all the other generated files.
	The file main.cpp contains already the code to run some calculations.

	Follow the steps:
		a. Uncomment the required section.
		b. Edit the variables containing the filenames as explained in the comments.
		   (for simplicity, don't change the output filenames, so tit will not be
		   mandatory to change them also in the plot scripts)
		c. Compile everything in the folder "/src"
		d. Run ./program_name
		e. Copy the scripts in the directory containing the output files
		f. Modify if needed the name of input and output files in the script
		   (not needed if you left the default output names in main.cpp)
		f. run the scripts with ./<nameofthescript> (requires gnuplot to be installed in /usr/bin/gnuplot)
