# Operative Systems 2

## Laboratory

A course-long project will be built, expanding upon previous work with new concepts every so oftnen.

The general objetive of the course is to learn how to take advantage of multi-core capabilities of
modern systems to parallelize tasks. In this case, the task will be to index a list of flights between
US cities, and generate statistical data on delayed flights.

The files can be found at [StatComputing (flight data 2009)](http://stat-computing.org/dataexpo/2009/the-data.html)
The format is CSV, it is up to the student how to read and process the file.

### Students
__Herman Dempere__  
__Arnau Sistach__

## Objectives

- [X] Read the CSV file and extract relevant information
- [X] Read the CSV file in blocks of X lines, and build a HashTable.
- [X] Insert the HashTable into a RB Binary Search Tree
- [X] The BST contains the data in linked list form for each city as index, there is a linked list of cities where
flights go to.
- [X] Use the POSIX Threads library to parallelize the processing and insertion of data from the CSV files into the BST
- [X] Performance testing
