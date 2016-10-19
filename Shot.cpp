#include "Shot.h"

Shot::Shot(){}

Shot::Shot(Circle circle, GLfloat centerX, GLfloat centerY, GLfloat shotAngle){
    this->circle = circle;
    this->centerX = centerX;
    this->centerY = centerY;
    this->shotAngle = shotAngle;
}

Circle Shot::getCircle(){
    return this->circle;
}

GLfloat Shot::getCenterX(){
    return this->centerX;
}

GLfloat Shot::getCenterY(){
    return this->centerY;
}

GLfloat Shot::getShotAngle(){
    return this->shotAngle;
}

void Shot::setCircle(Circle circle){
    this->circle = circle;
    return;
}

void Shot::setCenterX(GLfloat centerX){
    this->centerX = centerX;
    return;
}

void Shot::setCenterY(GLfloat centerY){
    this->centerY = centerY;
    return;
}

void Shot::setShotAngle(GLfloat shotAngle){
    this->shotAngle = shotAngle;
    return;
}

void Shot::drawShot(GLfloat playerRadius, GLfloat carWidth){


    glPushMatrix();

    glTranslatef(
        this->getCenterX(),
        this->getCenterY() - playerRadius,
        0
    );
    GLfloat scale = playerRadius/carWidth;
    glScalef(scale, scale, 1);

    //glRotatef(this->getShotAngle(), 0, 0, 1);
    glTranslatef(
        -this->getCircle().getCenterX(),
        -this->getCircle().getCenterY(),
        0
    );


    this->getCircle().drawCircle();

    glPopMatrix();
    return;
}
