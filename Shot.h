#ifndef SHOT_H
#define SHOT_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#endif

#include "Circle.h"
#include "Utils.h"
#include <string>
using namespace std;

class Shot {
  Circle circle;        // Circle that is rendered when shooting
  GLfloat centerX;      // Coordinate X of the shot's center
  GLfloat centerY;      // Coordinate Y of the shot's center
  GLfloat centerZ;      // Coordinate Y of the shot's center
  GLfloat carAngle;     // Angle of the car when shooted
  GLfloat cannonAngle;  // Angle of the cannon when shooted
  GLfloat cannonZAngle; // Angle of the cannon when shooted

public:
  // CONSTRUCTORS
  Shot();
  Shot(Circle &, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

  // GETTERS
  Circle getCircle();
  GLfloat getCenterX();
  GLfloat getCenterY();
  GLfloat getCenterZ();
  GLfloat getCarAngle();
  GLfloat getCannonAngle();
  GLfloat getCannonZAngle();

  // SETTERS
  void setCircle(Circle);
  void setCenterX(GLfloat);
  void setCenterY(GLfloat);
  void setCenterZ(GLfloat);
  void setCarAngle(GLfloat);
  void setCannonAngle(GLfloat);
  void setCannonZAngle(GLfloat);
};

#endif // SHOT_H
