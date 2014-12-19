turisimi
========

> **TURisimi** IS a **Simple** turIng Mashine sImulator.

**turisimi** is also a pure console application written in C++11 which *obviously* **can** interact to the user. It reads from `std::cin` and writes into `std::cout` but input and output can also be redirected into files for each task.

First it reads the IDs of the accepting states and some 5-tuples standing for the Turing Mashine. The tuples contain of the conditional state, the read condition, the character to write and the movement of the reader/writer (`l`=left; `r`=right and `s`=stop).
The second input file contains the band data. The first data pointer can be changed with the parameter `-p` / `--band-init`. By default it is `0`.
The third task is the simulation itself. If the flag `-sbs` aka. `--step-by-step` is set, the execution interupts for each step. It prints the bands data for each state. The user can interact to the Turing Mashine or let the simulation continue. For example it is possible to spule back the states or to edit current states.

For more informationsbread the [docu/manual.md](manual).

Some things to be done
===

> That I'll **not** forget it:

 * Implement some more [Examples](Examples).
 * Implent some outputs in`help.cpp`.
 * Maybe (ASCII-) graphical Turing Mashine output. (But I think this verry is not trival at all.)
