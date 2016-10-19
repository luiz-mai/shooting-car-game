#ifndef SHOT_H
#define SHOT_H

#include <GL/freeglut.h>
#include<string>
#include <iostream>
#include "Utils.h"
#include "Circle.h"
using namespace std;

class Shot{
    Circle circle;
    GLfloat centerX;
    GLfloat centerY;
    GLfloat shotAngle;

public:
    Shot();
    Shot(Circle, GLfloat, GLfloat, GLfloat);

    Circle getCircle();
    GLfloat getCenterX();
    GLfloat getCenterY();
    GLfloat getShotAngle();

    void setCircle(Circle);
    void setCenterX(GLfloat);
    void setCenterY(GLfloat);
    void setShotAngle(GLfloat);

    void drawShot(GLfloat, GLfloat);

};

#endif //SHOT_H
