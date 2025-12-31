## Conway's game of life

Conway's game of life written in C using SDL2

### Rules:

Each cell has eight neighbours, all those adjacent in the grid. At each step in time:

- Any live cell with fewer than two live neighbours dies
- Any live cell with fewer than two live neighbours lives on to the next generation
- Any live cell with more than three live neighbours dies
- Any dead cell with exactly three live neighbours becomes a live cell
