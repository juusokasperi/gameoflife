# <p align="center">Conway's Game of Life</p>
<p align="center">
	<img src="./img/raylib.png" width="400" alt="gameoflife-raylib" />
</p>

---

- Implemented in C
- Running `make` builds the binary `./life`, `make optimize` builds `./life_optimized` that includes compiler optimization flags.
- Usage:
	`./life(_optimized) <initial_state> <iterations>`
- A `<initial_state>` file can contain only characters `.` and `X`, for OFF and ON cells.

## Branches
`main`
- Calculates all the steps as specified by the user, and prints out the final result into the terminal.

`print-iterations`
- Prints out all the intermediary states into the terminal while the program is going through the iterations as specified by the user.

`raylib-print`
- Similar to print-iterations, but uses the `Raylib` graphical library to create a nicer output.
- This branch also supports different transition rules - the binary accepts two more argument, `./life(_optimized) <initial_state> <iterations> <cell_born> <cell_alive>`. If the additional arguments are not provided, the program uses the B3/S23 transition rule.
- Some common transition rules;
	- Seeds: B2/S
	- Replicator: B1357/S1357
	- Highlife: B36/S23
