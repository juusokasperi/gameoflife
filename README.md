# Conway's Game of Life
- Implemented in C
- Running `make` builds the binary `./life`, `make optimize` builds `./life_optimized` that includes compiler optimization flags.
- Usage:
	`./life(_optimized) <initial_state> <iterations>`
- The program validates the file `<initial_state>` and the `<iterations>`, runs the simulation for `n` times as specified by the `iterations` value and then prints out the state of the simulation after the iterations.
- A `<initial_state>` file can contain only characters `.` and `X`, for OFF and ON cells.

- Branch `print-iterations` has a version that prints out all the intermediary states while the program is going through all the iterations specified by the user.
