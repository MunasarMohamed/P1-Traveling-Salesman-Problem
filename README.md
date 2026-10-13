# Traveling Salesman Problem

A terminal program written in C that finds a short round trip through a set of coordinates. It was made as a first-semester (P1) project.

The program takes a list of points, runs one of two heuristic algorithms, and prints the route together with the estimated cost of driving it in DKK.

## Features

- Three ways to enter coordinates: typed in the terminal, read from a file, or randomly generated
- Two algorithms: Nearest Neighbor and 2-Opt
- Cost model based on driving time and diesel consumption
- Menu navigation with the arrow keys or number keys

## Requirements

- Windows (the menu uses `conio.h`)
- A C compiler such as GCC (MinGW)
- CMake 3.29 or newer (optional)

## Build and run

With CMake:

```
cmake -S . -B build
cmake --build build
build\main.exe
```

Or directly with GCC:

```
gcc -o main main.c generate-random-coordinates.c get-coordinates-from-terminal.c help.c nearest-neighbor.c read-from-file.c travel-cost.c two-opt.c -lm
main.exe
```

Run the compiled `main.exe` in a normal terminal. The built-in consoles in IDEs such as CLion do not handle the menu and screen clearing correctly.

## Usage

When the program starts, it shows the input menu:

```
    === Solving The Traveling Salesman Problem ===

    Navigate the menu using up and down arrow keys or use the number associated.

 >  1. Get Input from Terminal
    2. Read Input from File
    3. Generate N Random Data Points
    4. Help
```

After the coordinates are loaded, you choose an algorithm:

```
 >  1. Nearest Neighbor
    2. Two Opt
    3. Redo Input / Back
    4. Help
```

### Input formats

**Terminal:** enter one point per line as `x y`, and type `finished` when you are done.

```
Enter coordinates (x y): 3 4
Enter coordinates (x y): 7 2
Enter coordinates (x y): 2 8
Enter coordinates (x y): finished
```

**File:** enter the file name. The file must contain one point per line:

```
2 3
4 2
6 1
2 5
```

**Random:** enter the number of points and the range they should be generated within.

```
Enter the number of coordinates to generate: 100
Enter the minimum range: 0
Enter the maximum range: 20
```

## Example

Input file with 8 points:

```
2 3
4 2
6 1
2 5
7 1
3 6
3 7
1 3
```

| Nearest Neighbor | 2-Opt |
| --- | --- |
| <pre>Total Cost: 73.73 DKK<br><br>Tour:<br>(2, 3)<br>(1, 3)<br>(2, 5)<br>(3, 6)<br>(3, 7)<br>(4, 2)<br>(6, 1)<br>(7, 1)<br>(2, 3)</pre> | <pre>Total Cost: 69.78 DKK<br><br>Tour:<br>(2, 3)<br>(4, 2)<br>(6, 1)<br>(7, 1)<br>(3, 7)<br>(3, 6)<br>(2, 5)<br>(1, 3)<br>(2, 3)</pre> |

On this input, 2-Opt finds a route that is about 5% cheaper than Nearest Neighbor.

## Algorithms

**Nearest Neighbor** starts at the first point and always moves to the cheapest unvisited point. It is fast but often leaves crossing edges in the route. Recommended for large inputs (2000+ points).

**2-Opt** starts from the input order and repeatedly reverses parts of the route whenever doing so lowers the cost, until no improvement is left. It is slower but usually gives a better result. Recommended for smaller inputs.

## Cost model

The cost of each leg is calculated in `travel-cost.c` as the sum of:

- **Time cost:** distance / 50 km/h, multiplied by an hourly rate of 150 DKK
- **Fuel cost:** distance x diesel price (12.55 DKK/L) x fuel consumption at 50 km/h, estimated with a polynomial fitted to consumption data

Distance is the straight-line (Euclidean) distance between two points, with one unit treated as one kilometre.

## Project structure

| File | Description |
| --- | --- |
| `main.c` | Menus and program flow |
| `header.h` | `Coordinate` struct and function declarations |
| `get-coordinates-from-terminal.c` | Reads coordinates typed in the terminal |
| `read-from-file.c` | Reads coordinates from a text file |
| `generate-random-coordinates.c` | Generates random coordinates |
| `nearest-neighbor.c` | Nearest Neighbor algorithm |
| `two-opt.c` | 2-Opt algorithm |
| `travel-cost.c` | Cost calculation between two points |
| `help.c` | Help screens |
