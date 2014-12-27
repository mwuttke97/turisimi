turisimi
========

> **TURisimi** IS a **Simple** turIng Machine sImulator.

**turisimi** is also a pure console application written in C++11 which *obviously* **can** interact to the user. It reads from `std::cin` and writes into `std::cout` but input and output can also be redirected into files for each task.

First it reads the IDs of the accepting states and some 5-tuples standing for the Turing Machine. The tuples contain of the conditional state, the read condition, the character to write and the movement of the reader/writer (`l`=left; `r`=right and `s`=stop).
The second input file contains the band data. The first data pointer can be changed with the parameter `-p` / `--band-init`. By default it is `0`.
The third task is the simulation itself. If the flag `-sbs` aka. `--step-by-step` is set, the execution interupts for each step. It prints the bands data for each state. The user can interact to the Turing Machine or let the simulation continue. For example it is possible to spule back the states or to edit current states.

For more informations, please read the [manual](docu/manual.md).

A few things left to be done
###

 * Implement some more [Examples](Examples).
 * Implent some outputs in`help.cpp`.

LICENSE
#######

The code is licenced under a [MIT license](LICENSE).
Feel free to freely distribute the programm, but you HAVE to mention the origin authore who is me, mwuttke97@gmail.com.
