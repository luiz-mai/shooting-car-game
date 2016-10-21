#include "Circle.h"


Circle::Circle(){
}

Circle::Circle(string id, GLfloat radius, GLfloat centerX, GLfloat centerY, string fill){
        this->ID = id;
        this->radius = radius;
        this->centerX = centerX;
        this->centerY = centerY;
        this->fill = fill;
}

string Circle::getID(){
        return this->ID;
}

GLfloat Circle::getRadius(){
        return this->radius;
}

GLfloat Circle::getCenterX(){
        return this->centerX;
}

GLfloat Circle::getCenterY(){
        return this->centerY;
}

string Circle::getFill(){
        return this->fill;
}

void Circle::setID(string ID){
        this->ID = ID;
        return;
}

void Circle::setRadius(GLfloat radius){
        this->radius = radius;
        return;
}

void Circle::setCenterX(GLfloat centerX){
        this->centerX = centerX;
        return;
}

void Circle::setCenterY(GLfloat centerY){
        this->centerY = centerY;
        return;
}

void Circle::setFill(string fill){
        this->fill = fill;
        return;
}

void Circle::drawCircle(){
        int i;
        int triangleAmount = 50; //# of triangles used to draw circle
        GLfloat twicePi = 2.0f * M_PI;

        GLfloat centerX = this->centerX;
        GLfloat centerY = this->centerY;
        GLfloat radius = this->radius;

        Utils utils;
        utils.checkColor(this->fill);

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(centerX, centerY); // center of circle
        for(i = 0; i <= triangleAmount; i++) {
                glVertex2f(
                        centerX + (radius * cos(i *  twicePi / triangleAmount)),
                        centerY + (radius * sin(i * twicePi / triangleAmount))
                        );
        }
        glEnd();
}
