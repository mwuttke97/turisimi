User manual
===========


General
####

**turisimi** is a Turing Machine simulator. You should know about Turing Machines, if you want to use this application. On the Internet there are useful informations.

Usage
####

**turisimi** is a console application. It has therefore no graphical interface (GUI) but instead a command line interface (CLI).
User input is organized into two types:

1. The command line arguments ("args") that you give the application when you start it. (Explained first)
2. Prompts while executing. (Explained later)

Command line arguments
###

* To execute **turisimi**, open a terminal emulator (e.g. `cmd.exe` on Windows) and go (using `cd` on most systems) to the path where the executeable file is located.
* Type `./turisimi.exe` on Windows or `./turisimi` on UNIX to start the programm. You can add some arguments (SPACE-seperated).

List of command arguments ("args"):

* `-q` or `--qiet`: The application does not print prompt strings or extra informations for the *user*. Only relevant informations are to be displayed.
* `-tm` or `--tm_in`; followed by FILE: The application will read FILE instead of asking the user to input the Turing Machine.
* `-bin` or `--band_in`; followed by FILE: The application will read FILE instead of asking the user for the band data.
* `-b` or `--band`; followed by DATA: The application will load DATA into the band data.
* `-i` or `--in`; followed by FILE: The application will read the Turing Machine *and* the band data from FILE.
* `-p` or `--band-init`; followed by POINTER: Sets the "first" band data pointer. Default is 0.
* `-din` or `--debug-in`; followed by FILEIN and `-dout` or `--debug_out`; followed by FILEOUT: specify the input and output files while simulation. If FILEIN is set all inputs are read from FILEIN. If FILEOUT is set all outputs will be directed into the file FILEOUT.
* `-sbs` or `--step-by-step`: activates the usefull **Step-by-Step** mode. Read more [here](sbs.md).
* `-c` or `--continue`: Let the programm continue simulating until a break point is reached.
* `-bp` or `--break-points`; followed by BREAKPOINTS: Collon (`,`) separated list of the break points state IDs. When a state thats ID is in BREAKPOINTS is activated, the simulation goes into *SBS* mode.

Command Promts
###

If SBS is activated the **debug_prompt** will be activated. Read more [here](sbs.md).
