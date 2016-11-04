#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include <cmath>
#include <GL/freeglut.h>
#include "Utils.h"
using namespace std;

class Circle {
string ID;                          //Identifies the circle
GLfloat radius;                     //Circle's radius
GLfloat centerX;                    //Coordinate X of the circle's center
GLfloat centerY;                    //Coordinate Y of the circle's center
string fill;                        //Color of the circle

public:
//CONSTRUCTORS
Circle();
Circle(string, GLfloat, GLfloat, GLfloat, string);

//GETTERS
string getID();
GLfloat getRadius();
GLfloat getCenterX();
GLfloat getCenterY();
string getFill();

//SETTERS
void setID(string);
void setRadius(GLfloat);
void setCenterX(GLfloat);
void setCenterY(GLfloat);
void setFill(string);

//Draws a circle at the position specified by its attributes.
void drawCircle();
};

#endif //CIRCLE_H
