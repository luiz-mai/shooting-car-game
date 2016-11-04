#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cmath>
#include <GL/freeglut.h>
using namespace std;

class Utils {

public:
//Determines the color of theelement based on its parameter.
//PARAMETER: (string) color that must be used
void checkColor(string);

//Returns a random integer between two numbers;
//PARAMETER: (int) minimum value
//PARAMETER: (int) maximum value
//RETURN: random number.
int randomInt(int, int);

//Returns the distance between two points.
//PAPRAMETER: (GLfloat) Coordinate X of the first point
//PAPRAMETER: (GLfloat) Coordinate Y of the first point
//PAPRAMETER: (GLfloat) Coordinate X of the second point
//PAPRAMETER: (GLfloat) Coordinate Y of the second point
//RETURN: distance between the two points.
GLfloat distance2P(GLfloat, GLfloat, GLfloat, GLfloat);
};

#endif //UTILS_H
