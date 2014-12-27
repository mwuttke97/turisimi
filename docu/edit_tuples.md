How to use `edit_tuples()`? 
===========================

With `edit_tuples()`, obvously, you can edit tuples.
You edit the Turing Machine and aim to debug / edit a Turing Machine while executing. You don't have to use an text editor, through this is kinda *special* (simple) text editor.

It's like stepping -- that's how it works:

* Repead:
 * Print tuples
 * Mark one with `<--` ("cursor")
 * Process input.

Valid commands are:

* EMPTY STRING [ENTER]: Process `r`.
* `m TUPLE_ID`: Moves cursor to line `TUPLE_ID`.
* `m COUNT [u|d]`: Moves cursor `COUNT` times up or down. 
* `[u|d]`: Moves cursor up or down.
* **`w TUPLE`**: Writes 5-Tuple TUPLE to cursor position.
* `s`: Quits `edit_tuples()`. **TIPP**: After `s` you can type `export` in `dbg_cmd` prompt to save changes.
