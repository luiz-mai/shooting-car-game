#include "Shot.h"

Shot::Shot(){
}

Shot::Shot(Circle& circle, GLfloat centerX, GLfloat centerY, GLfloat carAngle, GLfloat cannonAngle){
        this->circle = circle;
        this->centerX = centerX;
        this->centerY = centerY;
        this->carAngle = carAngle;
        this->cannonAngle = cannonAngle;
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

GLfloat Shot::getCarAngle(){
        return this->carAngle;
}

GLfloat Shot::getCannonAngle(){
        return this->cannonAngle;
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

void Shot::setCarAngle(GLfloat carAngle){
        this->carAngle = carAngle;
        return;
}

void Shot::setCannonAngle(GLfloat cannonAngle){
        this->cannonAngle = cannonAngle;
        return;
}
