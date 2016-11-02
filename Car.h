#ifndef CAR_H
#define CAR_H

#include <string>
#include <cmath>
#include <iostream>
#include <cstring>
#include <vector>
#include <GL/freeglut.h>
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Shot.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

class Car {
vector<Rectangle> wheels;
vector<Rectangle> bodyRectangles;
vector<Triangle> bodyTriangles;
vector<Circle> bodyCircles;
Rectangle cannon;
vector<Shot> shotsVector;

GLfloat circleRadius;
GLfloat width;
GLfloat height;
GLfloat theta;
GLfloat centerX;
GLfloat centerY;
GLfloat speed;
GLfloat shotSpeed;
GLfloat wheelsAngle;
GLfloat cannonAngle;

float incrementalNumber;
bool moving;
string color;

public:
Car();

vector<Rectangle> getWheels();
vector<Rectangle> getBodyRectangles();
vector<Triangle> getBodyTriangles();
vector<Circle> getBodyCircles();
Rectangle getCannon();
vector<Shot> getShotsVector();
GLfloat getCircleRadius();
GLfloat getWidth();
GLfloat getHeight();
GLfloat getTheta();
GLfloat getCenterX();
GLfloat getCenterY();
GLfloat getSpeed();
GLfloat getShotSpeed();
GLfloat getWheelsAngle();
GLfloat getCannonAngle();
float getIncrementalNumber();
bool getMoving();
string getColor();

void setWheels(vector<Rectangle>);
void setBodyRectangles(vector<Rectangle>);
void setBodyTriangles(vector<Triangle>);
void setBodyCircles(vector<Circle>);
void setCannon(Rectangle);
void setShotsVector(vector<Shot>);
void setCircleRadius(GLfloat);
void setWidth(GLfloat);
void setHeight(GLfloat);
void setTheta(GLfloat);
void setCenterX(GLfloat);
void setCenterY(GLfloat);
void setSpeed(GLfloat);
void setShotSpeed(GLfloat);
void setWheelsAngle(GLfloat);
void setCannonAngle(GLfloat);
void setIncrementalNumber(float);
void setMoving(bool);
void setColor(string);

void drawCar();
void drawShots();
void moveForward(GLdouble);
void moveBackward(GLdouble);
void addShot();
bool detectFoeColision(Car, GLfloat, GLfloat);
bool detectTrackColision(Circle, GLfloat, GLfloat, GLfloat);
void updateShots(GLdouble);
void randomMove(GLdouble, GLfloat, GLfloat);
};

#endif //CAR_H
