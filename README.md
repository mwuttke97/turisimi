turisimi
========

>>> *TURisimi IS a **Simple** turIng Mashine sImulator.*
g

**turisimi** is also a pure console application written in C++11 which *obviously* **can** interact to the user. It reads from `std::cin` and writes into `std::cout` but input and output can also be redirected into files for each task.

First it reads the IDs of the accepting states and some 5-tuples standing for the Turing Mashine. The tuples contains of the conditional state, the read condition, the character to write and the movement of the reader/writer (`l`=left; `r`=right and `s`=stop).
The second input file contains the band data. `turisimi` reads the first data pointer and the data itself as a string.
The third task is the simulation itself. If the flag `-sbs` aka. `--step-by-step` is set, the execution interupts for each step. It prints the band datas for each state. The user (will) can interact to the Turing Mashine or let the simulation continue.

(TODO: More of this later.)

Some things to be done
===

>>> That I'll not forgot it:

 * Some new debug commands as changing the turing mashine while simulating or delete/change/add states.
 * When this is finished: Implent some outputs in`help.cpp`.
 * Maybe (ASCII-) graphical Turing Mashine output. (But I think this verry is not trival at all.)--
