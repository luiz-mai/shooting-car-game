#ifndef TRAB3_H
#define TRAB3_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef IMGLOADER_H
#include "imageloader.h"
#endif

#include "Car.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Shot.h"
#include "tinyxml2.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace tinyxml2;

class Trab3 {

public:
  // CONSTRUCTORS
  Trab3();

  // Gets the path to the arena.svg file.
  // Also sets some configurations as the car speed.
  string getArenaPath(int, char **);

  // Reads the arena.svg file.
  // Returns vector containing the tracks of the arena.
  vector<Circle> arenaReading(Trab3, string, vector<Circle>);

  // Reads the first rectangle of the arena (start track)
  Rectangle *rectangleReading(XMLElement *);

  // Reads all the circles of the arena (players and tracks)
  vector<Circle> circleReading(XMLElement *, vector<Circle>);

  // Prints the cronometer at the defined position.
  void printCronometer(GLfloat x, GLfloat y);

  // Prints the Win/Lose message at the end of the game.
  void printEndMessage(GLfloat x, GLfloat y);

  void drawScene();
  void drawMap();

  void PrintText(GLfloat x, GLfloat y, const char *text, double r, double g,
                 double b);

private:
  void RasterChars(GLfloat x, GLfloat y, GLfloat z, const char *text, double r,
                   double g, double b);
};

// OPENGL CALLBACKS
void display(void);
void idle(void);
void reshape(int, int);
void mouseMotion(int, int);
void moveCamera(int, int);
void mouseClick(int, int, int, int);
void keyPressed(unsigned char, int, int);
void keyUp(unsigned char, int, int);

// Check if a shot has left the screen
// PARAMETER: (Shot) shot that must be checked
// RETURN: true - left / false - didn't left
bool outOfScreen(Shot);

// Check if a player's shot colided with a car.
// PARAMETER: (Car) car that must be checked
// RETURN: true - colided / false - didn't colided
bool detectEnemyShotColision(Car);

#endif // TRAB3_H