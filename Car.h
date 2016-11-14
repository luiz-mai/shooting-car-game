#ifndef CAR_H
#define CAR_H

#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#endif

#include "Circle.h"
#include "Rectangle.h"
#include "Shot.h"
#include "Triangle.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

class Car {
  vector<Rectangle> wheels; // Contains the rectangles of the car's body.
  vector<Rectangle>
      bodyRectangles; // Contains all the rectangles of the car's body.
  vector<Triangle>
      bodyTriangles;          // Contains all the triangles of the car's body.
  vector<Circle> bodyCircles; // Contains all the circles of the car's body.
  Rectangle cannon;           // Car's cannon.
  vector<Shot> shotsVector;   // Contains all the shots of the car.

  GLfloat circleRadius; // Radius of the circle that contains the car.
  GLfloat width;        // SVG's width
  GLfloat height;       // SVG's height
  GLfloat zHeight;
  GLfloat theta;       // Angle of the car
  GLfloat centerX;     // Coordinate X of the center of the car
  GLfloat centerY;     // Coordinate Y of the center of the car
  GLfloat speed;       // Speed of the car
  GLfloat shotSpeed;   // Shooting speed of the car
  GLfloat wheelsAngle; // Angle of the front wheels of the car (-45 ~ 45)
  GLfloat cannonAngle; // Angle of the cannon of the car (-45 ~ 45)
  GLfloat axisWidth;   // Width of the car axis

  int backwardCount;       // Counter used when the foes colide.
  int direction;           // Movement's direction (1:forward / -1: backward)
  float incrementalNumber; // Counter used to "roll" the wheels
  bool moving;             // Determines if the car is moving or not
  string color;            // Car's color

public:
  // CONSTRUCTOR
  Car();

  // GETTERS
  vector<Rectangle> getWheels();
  vector<Rectangle> getBodyRectangles();
  vector<Triangle> getBodyTriangles();
  vector<Circle> getBodyCircles();
  Rectangle getCannon();
  vector<Shot> getShotsVector();
  GLfloat getCircleRadius();
  GLfloat getWidth();
  GLfloat getHeight();
  GLfloat getZHeight();
  GLfloat getTheta();
  GLfloat getCenterX();
  GLfloat getCenterY();
  GLfloat getSpeed();
  GLfloat getShotSpeed();
  GLfloat getWheelsAngle();
  GLfloat getCannonAngle();
  GLfloat getAxisWidth();
  int getBackwardCount();
  int getDirection();
  float getIncrementalNumber();
  bool getMoving();
  string getColor();

  // SETTERS
  void setWheels(vector<Rectangle>);
  void setBodyRectangles(vector<Rectangle>);
  void setBodyTriangles(vector<Triangle>);
  void setBodyCircles(vector<Circle>);
  void setCannon(Rectangle);
  void setShotsVector(vector<Shot>);
  void setCircleRadius(GLfloat);
  void setWidth(GLfloat);
  void setHeight(GLfloat);
  void setZHeight(GLfloat);
  void setTheta(GLfloat);
  void setCenterX(GLfloat);
  void setCenterY(GLfloat);
  void setSpeed(GLfloat);
  void setShotSpeed(GLfloat);
  void setWheelsAngle(GLfloat);
  void setCannonAngle(GLfloat);
  void setAxisWidth(GLfloat);
  void setBackwardCount(int);
  void setDirection(int);
  void setIncrementalNumber(float);
  void setMoving(bool);
  void setColor(string);

  // Does all the transformations and draws the car.

  void drawCar();
  void drawCarBody();
  void drawCarAxis();
  void drawCarWheels();
  void drawCarCannon();

  // Does all the transformations and draw the car.
  void drawShots();

  // Sets the new position of the car when moving forward.
  // PARAMETER: (GLdouble) current time
  void moveForward(GLdouble);

  // Sets the new position of the car when moving backward.
  // PARAMETER: (GLdouble) current time.
  void moveBackward(GLdouble);

  // Adds a new shot to the car shot's vector.
  void addShot();

  // Detects if the car colided with any car inside a vector of Cars.
  // PARAMETER: (vector<Car>) vector containing all the cars that must be
  // checked.
  // RETURN: true - colided / false - didn't colided.
  bool detectFoeColision(vector<Car>);

  // Detects if the car colided with a specific car.
  // PARAMETER: (Car) car that must be checked.
  // RETURN: true - colided / false - didn't colided.
  bool detectCarColision(Car);

  // Detects if the car colided with the inner and outer tracks.
  // PARAMETER: (vector<Circle>) vector containing all the tracks.
  // PARAMETER: (GLfloat) radius of the outer track.
  // RETURN: true - colided / false - didn't colided
  bool detectTrackColision(vector<Circle>, GLfloat);

  // Updates the position of the shots
  // PARAMETER: (GLdouble) current time.
  void updateShots(GLdouble);

  // Moves the foes with a kind of AI.
  // PARAMETER: (GLdouble) current time.
  // PARAMETER: (GLfloat) radius of the foes movement.
  void foeMove(GLdouble, GLfloat);
};

#endif // CAR_H
