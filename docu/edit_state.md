How to use `edit_state()`? 
===========================

With `edit_state()`, obvously, you can edit a state.

It's like stepping -- that's how it works:

* Repead:
 * Print state (The "pointer" is marked with `^`.)
 * Process input.

Valid commands are:

* EMPTY STRING [ENTER]: Process `r`.
* `m POINTER`: Moves pointer to POINTER.
* `m COUNT [l|r]`: Moves pointer `COUNT` times left or right.
* `[l|r]`: Moves cursor left or right.
* **`w CHAR`**: Writes `CHAR` to the pointer position.
* `s`: Quits `edit_state()`.
