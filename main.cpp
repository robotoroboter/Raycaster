#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#define M_PI 3.14159265358979323846
#include <cmath>
#include <windows.h>
#include <string>

//these two for random
#include <stdlib.h>
#include <time.h>

using namespace std;

//constant values//
const int blockSize = 8;
const int mapWidth = blockSize * 32; //16 is a block size, 32 is a number of blocks
const int mapHeight = blockSize * 32;
int level[blockSize * 32][blockSize * 32]; //height and width values again

//technical variables// //also giving them default values
const int screenWidth = 320;
const int screenHeight = 180;
const int fov = 80;

int column[screenWidth]; // max valid number of columns - the columns from 0 to screenWidth will contain wall sizes (depends it its far or close)

//gameplay variables//
int playerX;
int playerY;
int playerAngle = 0;
//int renderDistance = 44; //not used right now


int ray(int playerAngle, float cleanAngle, int dist, char axis); 
void loadMap(); //mapFile to level array
void movePlayer(); //check if player moves
void renderScreenImage();
void render2dImage();
void loadTextures();
//void draw(); //draws first person view




sf::Image screenImage;

sf::Texture screenTexture;

sf::Sprite screenSprite;

sf::Texture smgTexture;

sf::Sprite weaponSprite;

sf::RenderWindow gameWindow(sf::VideoMode(screenWidth, screenHeight), "Raycaster ");

int main() {
    srand(time(NULL));

    loadMap();

    loadTextures();

    while (gameWindow.isOpen())
    {
        sf::Event gameEvent;
        while (gameWindow.pollEvent(gameEvent))
        {
            if (gameEvent.type == sf::Event::Closed || (gameEvent.type == sf::Event::KeyPressed && gameEvent.key.code == sf::Keyboard::Escape))
            {
                printf("game window closed");
                gameWindow.close();
            }
        }
        gameWindow.clear();
        renderScreenImage();
        //render2dImage();
        screenTexture.update(screenImage);
        gameWindow.draw(screenSprite);
        gameWindow.draw(weaponSprite);
        gameWindow.display();
        movePlayer();
    }
    

    //while (true) {
    //    update();
    //    //draw();
    //}
}

void loadMap() {
	string levelLine;
	ifstream mapFile;
	mapFile.open("level00.txt");
	for (int y = mapHeight - 1; y >= 0; y--)
	{
		if ((y + 1) % blockSize == 0)
			getline(mapFile, levelLine);

		for (int x = 0; x < mapWidth; x++)
		{
			//cout<<"gamemap Y: "<<y<<"    gamemap X: "<<x<<"    file Y: "<<y/16<<"    file X: "<<x/16<<"    level[x][y]: "<<level[x/16][y/16]<<endl;
			//getchar();
			switch (levelLine[x / blockSize]) {
			case '1':
				level[x][y] = 1;
				break;
			case ' ':
				level[x][y] = 0;
				break;
			case 'p':
				level[x][y] = 0;
				playerX = x;
				playerY = y;
				break;
			default:
				cout << "error: unknown symbol on a map: " << levelLine[x] << endl;
				break;
			}
		}
	}
}

void loadTextures() {
    gameWindow.setFramerateLimit(50);
    screenImage.create(screenWidth, screenHeight);
    screenTexture.create(screenWidth, screenHeight);
    screenSprite.setTexture(screenTexture);
    smgTexture.loadFromFile("resources/textures/smg.png");
    weaponSprite.setTexture(smgTexture);
}

void movePlayer() {
    //cout<<"player X: "<<playerX<<endl<<"player Y: "<<playerY<<endl<<"Angle:"<<playerAngle<<endl;
    int walkSpeed = 1;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerAngle = playerAngle - 5;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playerAngle = playerAngle + 5;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {

        //for (int steps = 0; steps < walkSpeed; steps++) {
            if (level[playerX][playerY + ray(playerAngle, 0, walkSpeed, 'y')] == 0)
                playerY = playerY + ray(playerAngle, 0, walkSpeed, 'y');
        //}
        //for (int steps = 0; steps < walkSpeed; steps++) {
            if (level[playerX + ray(playerAngle, 0, walkSpeed, 'x')][playerY] == 0)
                playerX = playerX + ray(playerAngle, 0, walkSpeed, 'x');
        //}
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {

        //for (int steps = 0; steps < walkSpeed; steps++) {
        if (level[playerX][playerY + ray(playerAngle, 180, walkSpeed, 'y')] == 0)
            playerY = playerY + ray(playerAngle, 180, walkSpeed, 'y');
        //}
        //for (int steps = 0; steps < walkSpeed; steps++) {
        if (level[playerX + ray(playerAngle, 180, walkSpeed, 'x')][playerY] == 0)
            playerX = playerX + ray(playerAngle, 180, walkSpeed, 'x');
        //}
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {

        //for (int steps = 0; steps < walkSpeed; steps++) {
        if (level[playerX][playerY + ray(playerAngle, 90, walkSpeed, 'y')] == 0)
            playerY = playerY + ray(playerAngle, 90, walkSpeed, 'y');
        //}
        //for (int steps = 0; steps < walkSpeed; steps++) {
        if (level[playerX + ray(playerAngle, 90, walkSpeed, 'x')][playerY] == 0)
            playerX = playerX + ray(playerAngle, 90, walkSpeed, 'x');
        //}
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {

        //for (int steps = 0; steps < walkSpeed; steps++) {
        if (level[playerX][playerY + ray(playerAngle, 270, walkSpeed, 'y')] == 0)
            playerY = playerY + ray(playerAngle, 270, walkSpeed, 'y');
        //}
        //for (int steps = 0; steps < walkSpeed; steps++) {
        if (level[playerX + ray(playerAngle, 270, walkSpeed, 'x')][playerY] == 0)
            playerX = playerX + ray(playerAngle, 270, walkSpeed, 'x');
        //}
    }
    
    if (playerAngle < 0)
        playerAngle = playerAngle + 360;
    else if (playerAngle >= 360)
        playerAngle = playerAngle - 360;
}

void renderScreenImage() { 
    bool wall[screenWidth]; //to check if a ray met a wall or it has to go further
    int wallDistance[screenWidth];

    for (int i = 0; i < screenWidth; i++) {
        wall[i] = false;
    }

    for (int c = 0; c < screenWidth; c++) { //c means each column in screenWidth
        float a = ((float)fov / (float)(screenWidth - 1)) * c; //a means angle value for each column    //floats because output of int divisions would be int

        int d = 1; //d means distance to check if there is a wall (will increment)
        while (wall[c] != true) {
            if (level[playerX + ray(playerAngle, (a - fov / 2), d, 'x')][playerY + ray(playerAngle, (a - fov / 2), d, 'y')] == 1)
                wall[c] = true;
            else
                d++;
        }
        ///if it works on SFML, there will be column pixel drawing part
        wallDistance[c] = d;
        column[c] = (blockSize * 2 * screenHeight) / d;
        //cout << d << endl;
        //system("pause");
        if (column[c] < 0)
            column[c] = 0;

    }


    for (int h = 0; h < screenHeight / 2 - 1; h++) {
        for (int w = 0; w < screenWidth; w++) {
            if (h >= (screenHeight - column[w]) / 2) {
                if (((float)column[w] / ((float)screenHeight * 2)) < 1)
                    screenImage.setPixel(w, h, sf::Color::Color(0, 0, 255 * ((float)column[w] / ((float)screenHeight * 2))));
                else
                    screenImage.setPixel(w, h, sf::Color::Color(0, 0, 255));
            }
            else
                screenImage.setPixel(w, h, sf::Color::Color(100 + rand() % 30, 100 + rand() % 30, 100 + rand() % 30));
        }
    }

    for (int h = (screenHeight) / 2 - 1; h <= screenHeight - 1; h++) {
        for (int w = 0; w < screenWidth; w++) {
            if (h <= column[w] + (screenHeight - column[w]) / 2) {
                if (((float)column[w] / ((float)screenHeight * 2)) < 1)
                    screenImage.setPixel(w, h, sf::Color::Color(0, 0, 255 * ((float)column[w] / ((float)screenHeight * 2))));
                else
                    screenImage.setPixel(w, h, sf::Color::Color(0, 0, 255));
            }
            else
                screenImage.setPixel(w, h, sf::Color::Color(80, 40, 10));
        }
    }
}

void render2dImage()
{
    for (int h = 1; h <= mapHeight; h++) {
        for (int w = 1; w <= mapWidth; w++) {
            if (level[w][h]==1)
                screenImage.setPixel( round( (screenWidth-1) * (w / mapWidth) ), round ( (screenHeight-1) * (h / mapHeight ) ), sf::Color::Color(0, 0, 255));
            else
                screenImage.setPixel( round( (screenWidth-1) * (w / mapWidth) ), round ( (screenHeight-1) * (h / mapHeight ) ), sf::Color::Color(100, 100, 100));
        }
    }
}

int ray(int playerAngle, float cleanAngle, int dist, char axis) {
    float rayAngle = playerAngle + cleanAngle;
    if (rayAngle >= 360)
        rayAngle = rayAngle - 360;
    else if (rayAngle < 0)
        rayAngle = rayAngle + 360;

    int rayQuarter; //I or II or III or IV      clockwise order

    if (rayAngle < 90)
        rayQuarter = 1;
    else if (rayAngle < 180)
        rayQuarter = 2;
    else if (rayAngle < 270)
        rayQuarter = 3;
    else
        rayQuarter = 4;

    while (rayAngle >= 90) {
        rayAngle = rayAngle - 90;
    }

    int quarterX, quarterY;
    int finalX, finalY;

    float radianRayAngle = (rayAngle * M_PI) / 180;

    float cleanY = sqrt((dist * dist) / (tan(radianRayAngle) * tan(radianRayAngle) + 1));
    float cleanX = tan(radianRayAngle) * cleanY;

    quarterX = round(cleanX);
    quarterY = round(cleanY);


    //now correcting these values with quarters - converting from 0-89 to 0-359
    switch (rayQuarter) {
    case 1:
        finalX = quarterX;
        finalY = quarterY;
        break;
    case 2:
        finalX = quarterY;
        finalY = -quarterX;
        break;
    case 3:
        finalX = -quarterX;
        finalY = -quarterY;
        break;
    case 4:
        finalX = -quarterY;
        finalY = quarterX;
        break;
    }
    ///////////////
    /*
    cout<<"x quarter value: "<<quarterX<<endl<<"y quarter value: "<<quarterY<<endl;
    cout<<"x real value: "<<finalX<<endl<<"y real value: "<<finalY<<endl;
    cout<<"angle: "<<rayAngle<<endl;
    getchar();
    */
    ///////////////
    switch (axis) {
        case 'x':
            return finalX;
            break;
        case 'y':
            return finalY;
            break;
        default:
            cout << "error: unknown axis name in ray function: " << axis << endl;
            break;
    }
}
