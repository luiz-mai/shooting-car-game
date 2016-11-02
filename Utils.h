#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cmath>
#include <GL/freeglut.h>
using namespace std;

class Utils {

public:
void checkColor(string);
int randomInt(int, int);
GLfloat distance2P(GLfloat, GLfloat, GLfloat, GLfloat);
};

#endif //UTILS_H
