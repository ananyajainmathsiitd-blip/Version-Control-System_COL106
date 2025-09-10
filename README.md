# Time Travelling File System

## Introduction

This project is the required in-memory version control system inpired by git. It supports file versioning, rollbacks, snapshots, analytics, etc. through a sequence of commands availaible.

## Compilation Instructions
This project includes a shell.sh script.
1. In the terminal in the project folder, run the command
./shell.sh
2. To compile and run immediately
./shell.sh run

This will run the required ./system.cpp file and execute the code.


## Supported Commands

### Creating a file 
- input format should be "CREATE <filename>" without "" or <>
- filename should be unique (error when filename already exists)
- error message "File already exists!"
- success message "File <filename> created successfully"

### Reading from a file
- input format should be "READ <filename>" without "" or <>
- error when no such file filename has been created 
- error message "Error File doesn't exist"


### Inserting in a file
- input format should be "INSERT <filename> <content>" without "" or <>
- error when no such file filename has been created 
- error message "Error File doesn't exist"
- if already snapshot then display "Curent version already snapshoted making a new one"

### Updating a file 
- input format should be "UPDATE <filename> <content>" without "" or <>
- error when no such file filename has been created 
- message "Error File doesn't exist"
- if already snapshot then display "Curent version already snapshoted making a new one"


### Snapshot a file
- input format should be "SNAPSHOT <filename> <message>" without "" or <>
- error when no such file filename has been created 
- error message "Error File doesn't exist"
- success message "Snapshot created!"

### Rollback a file
- input format should be "Rollback <filename> <version>" without "" or <>
- error when no such file filename has been created 
- message "Error File doesn't exist"
- error when version is too large "no such version"
- error when current version is root version "Rollback from root not allowed" 
- success message if version id given "Rolling back to version- <version>"

### History of a file 
- input format should be "History <filename>" without "" or <>
- error when no such file filename has been created 
- message "Error File doesn't exist"

To access more than one file(System_Wide)

### Recentfile
- input format should be "RECENT FILES "<num>" without "" or <>
- shows recentfiles in decreasing order of last modified time and file name

### Biggestfiles
- input format should be "BIGGEST TREES <num> " without "" or <>
- shows recentfiles in decreasing order of no of versions and file name



Other input commands/commands with invailid format considered invalid
- message "ERROR: INVALID CMD <COMMAND>"

