#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <GL/freeglut.h>
#include "Utils.h"
using namespace std;

class Rectangle {
  string ID;
  GLfloat beginX;
	GLfloat beginY;
	GLfloat width;
	GLfloat height;
	string fill;

public:
  Rectangle();
  Rectangle(string, GLfloat, GLfloat, GLfloat, GLfloat, string);

  string getID();
  GLfloat getBeginX();
  GLfloat getBeginY();
  GLfloat getWidth();
  GLfloat getHeight();
  string getFill();

  void setID(string);
  void setBeginX(GLfloat);
  void setBeginY(GLfloat);
  void setWidth(GLfloat);
  void setHeight(GLfloat);
  void setFill(string);

  void drawRectangle();
};

#endif //RECTANGLE_H
