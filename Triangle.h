#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include <cmath>
#include <GL/freeglut.h>
#include "Utils.h"
using namespace std;

class Triangle{
    string ID;
    GLfloat x1, y1;
    GLfloat x2, y2;
    GLfloat x3, y3;
    string fill;

public:

    Triangle();
    Triangle(string, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, string);

    string getID();
    GLfloat getX1();
    GLfloat getY1();
    GLfloat getX2();
    GLfloat getY2();
    GLfloat getX3();
    GLfloat getY3();
    string getFill();

    void setID(string);
    void setX1(GLfloat);
    void setY1(GLfloat);
    void setX2(GLfloat);
    void setY2(GLfloat);
    void setX3(GLfloat);
    void setY3(GLfloat);
    void setFill(string);

    void drawTriangle();
};

#endif //TRIANGLE_H
