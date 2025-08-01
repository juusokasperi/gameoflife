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
