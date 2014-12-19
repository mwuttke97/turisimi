Step by Step Mode
=================

In step-by-step mode (SBS) you can watch how the states change. Each step, all states and their band data are printed. There is a command promt. The user decides how to handle the states. He / She can edit and add, also clone extisting states. Bellow, the commands are explained.

Debug Commands (*dbg_cmd*)
####

* `s` or `step` or just ENTER: Execution continues for one step.
* `td` or `toggle debug`: Turns debug mode off.
* `r` or `run`: Turns SBS off. However, allways when reaching a break point, SBS will be reactivated.
* `R` or `Run` or `RUN` or `RUN!`: Deactivate all debugging options (SBS included), delete all break points and run till no states more left! TERMINATION **NOT** GRANTED!!! :-)
* `toggle break_point` or `toggle bp`; followed by a collon-separated list
* `toggle break_point` or `toggle bp`; followed by a collon-separated list: Toggle all break points in the list.

Modification Commands
####

Bellow are verry useful commands:

State modification
###

* `state add`: Add a new state with an emty band.
* `state clone`; optional followed by ID [= 0]: Clone state ID.
* `state edit `; optional followed by ID [= 0]: [Edit](edit_state.md) state ID.
* `state erase`; optional followed by ID [= 0]: Delete state ID.
* `spule`; optional followed by COUNT [= BACK]: Spule back the states tree COUNT times or to the verry initial state.

Turing Mashine editting:
###

* `tuples`: [Edit](edit_tuples.md) the tuples. So, edit the Turing Mashine.
* `export`; optional followed by FILENAME: Can safe changings made with the command obove. If no FILENAME is given, the application tries to save it to the FILENAME given by the "arg" `-tm`.
