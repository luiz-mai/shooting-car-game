#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>
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

class Circle {
  string ID;       // Identifies the circle
  GLfloat radius;  // Circle's radius
  GLfloat centerX; // Coordinate X of the circle's center
  GLfloat centerY; // Coordinate Y of the circle's center
  string fill;     // Color of the circle
  GLfloat opacity;

public:
  // CONSTRUCTORS
  Circle();
  Circle(string, GLfloat, GLfloat, GLfloat, string, GLfloat opacity = 0.2);

  // GETTERS
  string getID();
  GLfloat getRadius();
  GLfloat getCenterX();
  GLfloat getCenterY();
  string getFill();

  // SETTERS
  void setID(string);
  void setRadius(GLfloat);
  void setCenterX(GLfloat);
  void setCenterY(GLfloat);
  void setFill(string);

  // Draws a circle at the position specified by its attributes.
  void drawCircle();
};

#endif // CIRCLE_H
