#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include <cmath>
#include <GL/freeglut.h>
#include "Utils.h"
using namespace std;

class Circle {
  string ID;
  GLfloat radius;
  GLfloat centerX;
  GLfloat centerY;
  string fill;

public:
  Circle();
  Circle(string, GLfloat, GLfloat, GLfloat, string);

  string getID();
  GLfloat getRadius();
  GLfloat getCenterX();
  GLfloat getCenterY();
  string getFill();

  void setID(string);
  void setRadius(GLfloat);
  void setCenterX(GLfloat);
  void setCenterY(GLfloat);
  void setFill(string);

  void drawCircle();
};

#endif //CIRCLE_H
