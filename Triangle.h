#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#endif

#include "Utils.h"
using namespace std;

class Triangle {
string ID;                          //Identifies the triangle
GLfloat x1, y1;                     //First point of the triangle
GLfloat x2, y2;                     //Second point of the triangle
GLfloat x3, y3;                     //Third point of the triangle
string fill;                        //Color of the triangle

public:
//CONSTRUCTORS
Triangle();
Triangle(string, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, string);

//GETTERS
string getID();
GLfloat getX1();
GLfloat getY1();
GLfloat getX2();
GLfloat getY2();
GLfloat getX3();
GLfloat getY3();
string getFill();

//SETTERS
void setID(string);
void setX1(GLfloat);
void setY1(GLfloat);
void setX2(GLfloat);
void setY2(GLfloat);
void setX3(GLfloat);
void setY3(GLfloat);
void setFill(string);

//Draws a triangle at the position specified by its attributes.
void drawTriangle();
};

#endif //TRIANGLE_H
