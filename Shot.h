#ifndef SHOT_H
#define SHOT_H

#include <GL/freeglut.h>
#include <string>
#include "Utils.h"
#include "Circle.h"
using namespace std;

class Shot {
Circle circle;                      //Circle that is rendered when shooting
GLfloat centerX;                    //Coordinate X of the shot's center
GLfloat centerY;                    //Coordinate Y of the shot's center
GLfloat carAngle;                   //Angle of the car when shooted
GLfloat cannonAngle;                //Angle of the cannon when shooted

public:
//CONSTRUCTORS
Shot();
Shot(Circle&, GLfloat, GLfloat, GLfloat, GLfloat);

//GETTERS
Circle getCircle();
GLfloat getCenterX();
GLfloat getCenterY();
GLfloat getCarAngle();
GLfloat getCannonAngle();

//SETTERS
void setCircle(Circle);
void setCenterX(GLfloat);
void setCenterY(GLfloat);
void setCarAngle(GLfloat);
void setCannonAngle(GLfloat);

};

#endif //SHOT_H
