#ifndef SHOT_H
#define SHOT_H

#include <GL/freeglut.h>
#include <string>
#include "Utils.h"
#include "Circle.h"
using namespace std;

class Shot {
Circle circle;
GLfloat centerX;
GLfloat centerY;
GLfloat carAngle;
GLfloat cannonAngle;

public:
Shot();
Shot(Circle&, GLfloat, GLfloat, GLfloat, GLfloat);

Circle getCircle();
GLfloat getCenterX();
GLfloat getCenterY();
GLfloat getCarAngle();
GLfloat getCannonAngle();

void setCircle(Circle);
void setCenterX(GLfloat);
void setCenterY(GLfloat);
void setCarAngle(GLfloat);
void setCannonAngle(GLfloat);

};

#endif //SHOT_H
