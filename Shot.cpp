#include "Shot.h"

Shot::Shot(){
}

Shot::Shot(Circle& circle, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat carAngle, GLfloat cannonAngle, GLfloat cannonZAngle){
        this->circle = circle;
        this->centerX = centerX;
        this->centerY = centerY;
        this->centerZ = centerZ;
        this->carAngle = carAngle;
        this->cannonAngle = cannonAngle;
        this->cannonZAngle = cannonZAngle;
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

GLfloat Shot::getCenterZ(){
        return this->centerZ;
}

GLfloat Shot::getCarAngle(){
        return this->carAngle;
}

GLfloat Shot::getCannonAngle(){
        return this->cannonAngle;
}

GLfloat Shot::getCannonZAngle(){
        return this->cannonZAngle;
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

void Shot::setCenterZ(GLfloat centerZ){
        this->centerZ = centerZ;
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

void Shot::setCannonZAngle(GLfloat cannonZAngle){
        this->cannonZAngle = cannonZAngle;
        return;
}
