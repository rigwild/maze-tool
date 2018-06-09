# maze-tool
This was made as part of a school project. The goal was to create a maze that would always have a path from the entrance to the exit.
You can choose the start and exit locations, place a wall (It will test if the wall is blocking the path) and show the path from entrance to exit.

It's written in C. The texts are in french as it was a school project, but the code is commented in english.

I added the possibility to generate a random maze with random walls, with the path from entrance to exit still there.

## Feature(s)
- Manually create a maze
- Manually add walls, checking if a path from entrance to exit is still possible
- Generate a random maze with random walls
- Show the path from entrance to exit
- Save the maze to a file
- Load a maze from a file

## Known bug(s)
- When drawing the path from entrance to exit, the path stops if x = 0 or if y = 0. I don't know from where comes this bug from.

## Disclaimer
As it was part of a school project, there may be bugs. Plus, this repository will not be maintened.

## Screenshot(s)
Main menu :

![Home menu](https://github.asauvage.fr/img/other/maze-tool.jpg)

A random maze with its path. Entrance is "E" in the bottom left-hand corner. Exit is "S" in the top right-hand corner.
The path is reprensented by X.

![Random maze](https://github.asauvage.fr/img/other/maze-tool2.jpg)
