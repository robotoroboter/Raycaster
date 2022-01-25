# Raycaster
A raycasting implementation prototype written in C++ using the SFML library<br>
Supports walking, rotating camera, custom 2d maps<br>
## Raycasting - description<br>
![raycasting](https://upload.wikimedia.org/wikipedia/commons/e/e7/Simple_raycasting_with_fisheye_correction.gif)<br>
Raycasting is a technique of simulating 3d first person view based on a 2d tilemap. The program reads the level file and the player position, and for each screen pixel column creates a ray which computes the distance between the player and the closest wall. Then the pixel column is filled with color using perspective simulation, so that the closer the wall, the higher it appears on the screen. It creates a primitive 3d effect despite no 3d computations in the program.
## Screenshots & gifs
### Current version:
<img src="https://github.com/robotoroboter/Raycaster/blob/main/img/sfml.png?raw=true" width="800"/>
<img src="https://github.com/robotoroboter/Raycaster/blob/main/img/sfml.gif?raw=true" width="800"/>

### First version (command line)
<img src="https://github.com/robotoroboter/Raycaster/blob/main/img/cmd.png?raw=true" width="800"/>
<img src="https://github.com/robotoroboter/Raycaster/blob/main/img/cmd.gif?raw=true" width="800"/>
