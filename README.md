# <p align="center">Conway's Game of Life</p>
<p align="center">
	<img src="./img/raylib.png" width="400" alt="gameoflife-raylib" />
</p>

---

- Implemented in C as part of a 2-day Rush project at Hive Helsinki school.
- Running `make` builds the binary `./life`, `make optimize` builds `./life_optimized` that includes compiler optimization flags.
- Usage:
	- `./life(_optimized) <initial_state> <iterations>` OR:
	- `./life(_optimized) <initial_state> <iterations> <cell_born> <cell_alive>`
	- If the optional `<cell_born>` and `<cell_alive>` arguments are not provided, the program uses the B3/S23 transition rule.
- Some common transition rules;
	- Seeds: B2/S
	- Replicator: B1357/S1357
	- Highlife: B36/S23
- A `<initial_state>` file can contain only characters `.` and `X`, for OFF and ON cells.

## Branches
`main`
- Calculates all the steps as specified by the user, and prints out the final result into the terminal.

`print-iterations`
- Prints out all the intermediary states into the terminal while the program is going through the iterations as specified by the user.

`raylib-print`
- Similar to print-iterations, but uses the `Raylib` graphical library to create a nicer output.
- Keys:

| Key          | Function                                                     |
|--------------|--------------------------------------------------------------|
| `P`          | Pause iterations                                             |
| `C`          | Continue iterations                                          |
| `N`          | Next iteration (can be held down)                            |
| `T`          | Show keyboard commands (these)                               |
| `Left Click` | Toggle cells on/off when paused or at the end of iterations. |
