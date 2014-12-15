turisimi
========

> **TURisimi** IS a **Simple** turIng Mashine sImulator.

**turisimi** is also a pure console application written in C++11 which *obviously* **can** interact to the user. It reads from `std::cin` and writes into `std::cout` but input and output can also be redirected into files for each task.

First it reads the IDs of the accepting states and some 5-tuples standing for the Turing Mashine. The tuples contain of the conditional state, the read condition, the character to write and the movement of the reader/writer (`l`=left; `r`=right and `s`=stop).
The second input file contains the band data. **turisimi** reads the first data pointer and the data itself as a string.
The third task is the simulation itself. If the flag `-sbs` aka. `--step-by-step` is set, the execution interupts for each step. It prints the bands data for each state. The user (will) can interact to the Turing Mashine or let the simulation continue.

(TODO: More of this later.)

Some things to be done
===

> That I'll **not** forget it:

 * Restrict the length of the state-stack to the width of the terminal. Add a parameter that aims to change this behavior.
 * Some new **debug commands** like change turing mashine while simulating and delete/change/add states.
 * Implement some more [Examples](Examples).
 * Implent some outputs in`help.cpp`.
 * Maybe (ASCII-) graphical Turing Mashine output. (But I think this verry is not trival at all.)
