#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#endif

#include "Utils.h"
using namespace std;

class Rectangle {
string ID;                      //Identifies the circle
GLfloat beginX;                 //Coordinate X of the rectangle's first point
GLfloat beginY;                 //Coordinate Y of the rectangle's first point
GLfloat width;                  //Rectangle's width
GLfloat height;                 //Rectangle's height
string fill;                    //Color of the rectangle

public:
//CONSTRUCTORS
Rectangle();
Rectangle(string, GLfloat, GLfloat, GLfloat, GLfloat, string);

//GETTERS
string getID();
GLfloat getBeginX();
GLfloat getBeginY();
GLfloat getWidth();
GLfloat getHeight();
string getFill();

//SETTERS
void setID(string);
void setBeginX(GLfloat);
void setBeginY(GLfloat);
void setWidth(GLfloat);
void setHeight(GLfloat);
void setFill(string);

//Draws a rectangle at the position specified by its attributes.
void drawRectangle();
};

#endif //RECTANGLE_H
