# Raycaster
A "video game" prototype written during the summer of 2020, just after I finished high school. It was a test if I could recreate the rendering technique from the 90s pseudo-3d games, which fascinated me at that time. Also a good revision for my math skills (especially trygonometry), and programming 2d graphics.<br>
The whole program is based on a game programming pattern called Game Loop, which is an infinite loop that handles all the events occuring during the program execution: getting player's input, updating the game world and rendering it to the screen.<br>
It supports walking, rotating camera, loading custom 2d maps (as .txt files)<br>
#### Technologies used:
C++ and SFML
## Raycasting - description
![raycasting](https://upload.wikimedia.org/wikipedia/commons/e/e7/Simple_raycasting_with_fisheye_correction.gif)<br>
Raycasting is a technique of simulating 3d first person view based on a 2d tilemap. The program reads the level file and the player position, and for each screen pixel column creates a ray which computes the distance between the player and the closest wall. Then the pixel column is filled with color using perspective simulation, so that the closer the wall, the higher it appears on the screen. It creates a primitive 3d effect despite no 3d computations in the program.
## Running
Simply run "raycaster.exe"<br>
#### Controls:
Walking: W, A, S, D <br>
Rotating: Left arrow, Right arrow

## Screenshots & gifs
### Current version:
<img src="https://github.com/robotoroboter/Raycaster/blob/main/img/sfml.png?raw=true" width="800"/>
<img src="https://github.com/robotoroboter/Raycaster/blob/main/img/sfml.gif?raw=true" width="800"/>

### First version (command line, ASCII symbols instead of pixels)
<img src="https://github.com/robotoroboter/Raycaster/blob/main/img/cmd.png?raw=true" width="800"/>
<img src="https://github.com/robotoroboter/Raycaster/blob/main/img/cmd.gif?raw=true" width="800"/>
