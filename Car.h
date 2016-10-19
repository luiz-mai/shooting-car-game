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
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

class Car {
        vector<Rectangle> wheels;
        vector<Rectangle> bodyRectangles;
        vector<Triangle> bodyTriangles;
        vector<Circle> bodyCircles;
        Rectangle cannon;

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

public:
    Car();

    vector<Rectangle> getWheels();
    vector<Rectangle> getBodyRectangles();
    vector<Triangle> getBodyTriangles();
    vector<Circle> getBodyCircles();
    Rectangle getCannon();
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

    void setWheels(vector<Rectangle>);
    void setBodyRectangles(vector<Rectangle>);
    void setBodyTriangles(vector<Triangle>);
    void setBodyCircles(vector<Circle>);
    void setCannon(Rectangle);
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

    void drawCar(GLfloat, bool, vector<Circle>);
};

#endif //CAR_H
