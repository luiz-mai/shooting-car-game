#include "Car.h"

Car::Car(){
        XMLDocument car;

        vector<Rectangle> wheels;
        vector<Rectangle> bodyRectangles;
        vector<Triangle> bodyTriangles;
        vector<Circle> bodyCircles;
        Rectangle cannon;

        car.LoadFile("car.svg");
        XMLElement* svgElement = car.FirstChildElement("svg");

        for(XMLElement* rectElement = svgElement->FirstChildElement("rect"); rectElement != NULL; rectElement = rectElement->NextSiblingElement("rect"))
        {
                Rectangle* rect = new Rectangle(
                        rectElement->Attribute("id"),
                        rectElement->FloatAttribute("x"),
                        rectElement->FloatAttribute("y"),
                        rectElement->FloatAttribute("width"),
                        rectElement->FloatAttribute("height"),
                        rectElement->Attribute("fill")
                        );

                if(rect->getID() == "FrontWheels") {
                        vector<Rectangle>::iterator it;
                        it = wheels.begin();
                        wheels.insert(it, *rect);
                } else if(rect->getID() == "BackHeels") {
                        wheels.push_back(*rect);
                } else if(rect->getID() == "Cannon") {
                        this->setCannon(*rect);
                } else{
                        bodyRectangles.push_back(*rect);
                }
        }
        this->setBodyRectangles(bodyRectangles);
        this->setWheels(wheels);

        for(XMLElement* circleElement = svgElement->FirstChildElement("circle"); circleElement != NULL; circleElement = circleElement->NextSiblingElement("circle"))
        {
                Circle* circle = new Circle(
                        circleElement->Attribute("id"),
                        circleElement->IntAttribute("r"),
                        circleElement->IntAttribute("cx"),
                        circleElement->IntAttribute("cy"),
                        circleElement->Attribute("fill")
                        );

                bodyCircles.push_back(*circle);
        }
        this->setBodyCircles(bodyCircles);

        for(XMLElement* triangleElement = svgElement->FirstChildElement("polygon"); triangleElement != NULL; triangleElement = triangleElement->NextSiblingElement("polygon"))
        {
                float pointsArray[6];
                int pointPos = 0;
                string s = triangleElement->Attribute("points");
                string delim = " ";

                int i = 0;
                int pos = s.find(delim);
                while (pos != string::npos) {
                        string s2 = s.substr(i, pos-i);
                        string delim2 = ",";

                        int i2 = 0;
                        int pos2 = s2.find(delim2);
                        while (pos2 != string::npos) {
                                pointsArray[pointPos++] = atof(s2.substr(i2, pos2-i2).c_str());
                                i2 = ++pos2;
                                pos2 = s2.find(delim2, pos2);

                                if (pos2 == string::npos)
                                        pointsArray[pointPos++] = atof(s2.substr(i2, s2.length()).c_str());
                        }
                        i = ++pos;
                        pos = s.find(delim, pos);

                        if (pos == string::npos) {
                                string s2 =  s.substr(i, s.length());
                                string delim2 = ",";

                                int i2 = 0;
                                int pos2 = s2.find(delim2);
                                while (pos2 != string::npos) {
                                        pointsArray[pointPos++] = atof(s2.substr(i2, pos2-i2).c_str());
                                        i2 = ++pos2;
                                        pos2 = s2.find(delim2, pos2);

                                        if (pos2 == string::npos)
                                                pointsArray[pointPos++] = atof(s2.substr(i2, s2.length()).c_str());
                                }
                        }

                }
                Triangle* triangle = new Triangle(
                        triangleElement->Attribute("id"),
                        pointsArray[0],
                        pointsArray[1],
                        pointsArray[2],
                        pointsArray[3],
                        pointsArray[4],
                        pointsArray[5],
                        triangleElement->Attribute("fill")
                        );
                bodyTriangles.push_back(*triangle);

        }
        this->setBodyTriangles(bodyTriangles);
        this->setWidth(200);
        this->setHeight(200);
        this->setTheta(0);
        this->setCannonAngle(0);
        this->setWheelsAngle(0);
        this->setMoving(false);
        this->setAxisWidth(58.5);
        this->setBackwardCount(0);

        return;
}

vector<Rectangle> Car::getWheels(){
        return this->wheels;
}

vector<Rectangle> Car::getBodyRectangles(){
        return this->bodyRectangles;
}

vector<Triangle> Car::getBodyTriangles(){
        return this->bodyTriangles;
}

vector<Circle> Car::getBodyCircles(){
        return this->bodyCircles;
}

Rectangle Car::getCannon(){
        return this->cannon;
}

vector<Shot> Car::getShotsVector(){
        return this->shotsVector;
}

GLfloat Car::getCircleRadius(){
        return this->circleRadius;
}

GLfloat Car::getWidth(){
        return this->width;
}

GLfloat Car::getHeight(){
        return this->height;
}

GLfloat Car::getTheta(){
        return this->theta;
}

GLfloat Car::getCenterX(){
        return this->centerX;
}

GLfloat Car::getCenterY(){
        return this->centerY;
}

GLfloat Car::getSpeed(){
        return this->speed;
}

GLfloat Car::getShotSpeed(){
        return this->shotSpeed;
}

GLfloat Car::getWheelsAngle(){
        return this->wheelsAngle;
}

GLfloat Car::getCannonAngle(){
        return this->cannonAngle;
}

GLfloat Car::getAxisWidth(){
        return this->axisWidth;
}

int Car::getBackwardCount(){
        return this->backwardCount;
}

GLfloat Car::getIncrementalNumber(){
        return this->incrementalNumber;
}

bool Car::getMoving(){
        return this->moving;
}

string Car::getColor(){
        return this->color;
}

void Car::setWheels(vector<Rectangle> wheels){
        this->wheels = wheels;
        return;
}

void Car::setBodyRectangles(vector<Rectangle> bodyRectangles){
        this->bodyRectangles = bodyRectangles;
        return;
}

void Car::setBodyTriangles(vector<Triangle> bodyTriangles){
        this->bodyTriangles = bodyTriangles;
        return;
}


void Car::setBodyCircles(vector<Circle> bodyCircles){
        this->bodyCircles = bodyCircles;
        return;
}

void Car::setCannon(Rectangle cannon){
        this->cannon = cannon;
        return;
}

void Car::setShotsVector(vector<Shot> shotsVector){
        this->shotsVector = shotsVector;
        return;
}

void Car::setCircleRadius(GLfloat circleRadius){
        this->circleRadius = circleRadius;
        return;
}


void Car::setWidth(GLfloat width){
        this->width = width;
        return;
}

void Car::setHeight(GLfloat height){
        this->height = height;
        return;
}

void Car::setTheta(GLfloat theta){
        this->theta = theta;
        return;
}

void Car::setCenterX(GLfloat centerX){
        this->centerX = centerX;
        return;
}

void Car::setCenterY(GLfloat centerY){
        this->centerY = centerY;
        return;
}

void Car::setSpeed(GLfloat speed){
        this->speed = speed;
        return;
}

void Car::setShotSpeed(GLfloat shotSpeed){
        this->shotSpeed = shotSpeed;
        return;
}

void Car::setWheelsAngle(GLfloat wheelsAngle){
        if(abs(wheelsAngle) < 45)
                this->wheelsAngle = wheelsAngle;
        return;
}

void Car::setCannonAngle(GLfloat cannonAngle){
        if(abs(cannonAngle) < 45)
                this->cannonAngle = cannonAngle;
        return;
}

void Car::setAxisWidth(GLfloat axisWidth){
        this->axisWidth = axisWidth;
        return;
}

void Car::setIncrementalNumber(float incrementalNumber){
        this->incrementalNumber = incrementalNumber;
        return;
}

void Car::setBackwardCount(int backwardCount){
        this->backwardCount = backwardCount;
        return;
}

void Car::setMoving(bool moving){
        this->moving = moving;
        return;
}

void Car::setColor(string color){
        this->color = color;
        return;
}

void Car::drawCar(){
        bool moving = this->getMoving();
        GLfloat playerRadius = this->getCircleRadius();
        float randomAngle = this->getIncrementalNumber();
        if(moving) {
                if(randomAngle >=45) {
                        this->setIncrementalNumber(0);
                } else {
                        this->setIncrementalNumber(randomAngle + 0.5);
                }
        }

        vector<Circle> bodyCircles = this->getBodyCircles();
        vector<Rectangle> bodyRectangles = this->getBodyRectangles();
        vector<Rectangle> wheels = this->getWheels();

        glPushMatrix();
        glTranslatef(
                this->getCenterX(),
                this->getCenterY(),
                0
                );


        glRotatef(this->getTheta(), 0, 0, 1);
        glScalef(
                2*playerRadius/this->getWidth(),
                2*playerRadius/this->getHeight(),
                1
                );

        glTranslatef(
                -this->getWidth()/2,
                -this->getHeight()/2,
                0
                );
        for(vector<Rectangle>::iterator it = wheels.begin(); it != wheels.end(); ++it) {

                glPushMatrix();
                if((*it).getID() == "FrontWheels") {
                        glTranslatef(
                                (*it).getBeginX() + (*it).getWidth()/2,
                                (*it).getBeginY() + (*it).getHeight()/2,
                                0
                                );
                        glRotatef(this->getWheelsAngle(), 0, 0, 1);
                        if(moving) {
                                glRotatef(randomAngle, 1, 0, 0);
                        }
                        glTranslatef(
                                -(*it).getBeginX() - (*it).getWidth()/2,
                                -(*it).getBeginY() - (*it).getHeight()/2,
                                0
                                );
                }
                (*it).drawRectangle();
                glPopMatrix();
        }

        string carColor = this->getColor();
        string darkerColor = "dark" + carColor;

        for(vector<Rectangle>::iterator it = bodyRectangles.begin(); it != bodyRectangles.end(); ++it) {
                if((*it).getID() == "Body1") {
                        (*it).setFill(carColor);
                } else if((*it).getID() == "Body2") {
                        (*it).setFill(darkerColor);
                }

                (*it).drawRectangle();
        }

        for(vector<Circle>::iterator it = bodyCircles.begin(); it != bodyCircles.end(); ++it) {
                if((*it).getID() == "Body1") {
                        (*it).setFill(carColor);
                } else if((*it).getID() == "Body2") {
                        (*it).setFill(darkerColor);
                }
                (*it).drawCircle();
        }

        for(vector<Triangle>::iterator it = bodyTriangles.begin(); it != bodyTriangles.end(); ++it) {
                if((*it).getID() == "Body1") {
                        (*it).setFill(carColor);
                } else if((*it).getID() == "Body2") {
                        (*it).setFill(darkerColor);
                }
                (*it).drawTriangle();
        }

        glTranslatef(
                this->getCannon().getBeginX() + this->getCannon().getWidth()/2,
                this->getCannon().getBeginY() + this->getCannon().getHeight(),
                0
                );

        glRotatef(this->getCannonAngle(), 0, 0, 1);

        glTranslatef(
                -this->getCannon().getBeginX() - this->getCannon().getWidth()/2,
                -this->getCannon().getBeginY() - this->getCannon().getHeight(),
                0
                );

        this->getCannon().drawRectangle();


        glPopMatrix();
        return;
}


void Car::drawShots(){

        vector<Shot> carShots = this->getShotsVector();

        for(vector<Shot>::iterator it = carShots.begin(); it != carShots.end(); ++it) {
                glPushMatrix();
                glTranslatef(
                        (*it).getCenterX(),
                        (*it).getCenterY(),
                        0
                        );


                glRotatef((*it).getCarAngle(), 0, 0, 1);
                glScalef(
                        2*this->getCircleRadius()/this->getWidth(),
                        2*this->getCircleRadius()/this->getHeight(),
                        1
                        );

                glTranslatef(
                        -this->getWidth()/2,
                        -this->getHeight()/2,
                        0
                        );

                glTranslatef(
                        this->getCannon().getBeginX() + this->getCannon().getWidth()/2,
                        this->getCannon().getBeginY() + this->getCannon().getHeight(),
                        0
                        );

                glRotatef((*it).getCannonAngle(), 0, 0, 1);

                glTranslatef(
                        0,
                        -this->getCannon().getHeight(),
                        0
                        );
                (*it).getCircle().drawCircle();

                glPopMatrix();
        }
        return;

}

void Car::addShot(){
        Circle shotCircle = Circle("Shot", 12, 0, 0, "yellow");
        Shot shot = Shot(shotCircle,this->getCenterX(),this->getCenterY(),this->getTheta(),this->getCannonAngle());
        this->shotsVector.push_back(shot);
        return;
}



bool Car::detectTrackColision(vector<Circle> trackVector, GLfloat biggestRadius){
        for(vector<Circle>::iterator it = trackVector.begin(); it != trackVector.end(); ++it) {

                if((*it).getRadius() != biggestRadius ) {
                        if(sqrt(pow(((*it).getCenterX() - this->getCenterX()),2) + pow(((*it).getCenterY() - this->getCenterY()),2))
                           < (*it).getRadius() + this->getCircleRadius()) {
                                return true;
                        }
                } else {
                        if(sqrt(pow(((*it).getCenterX() - this->getCenterX()),2)+pow((*it).getCenterY() - this->getCenterY(),2)) + this->getCircleRadius()
                           > biggestRadius) {
                                return true;
                        }
                }
        }
        return false;
}

bool Car::detectFoeColision(vector<Car> foesVector){
        for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
                if(sqrt(pow(((*it).getCenterX() - this->getCenterX()),2) + pow(((*it).getCenterY() - this->getCenterY()),2))
                   < (*it).getCircleRadius() + this->getCircleRadius()) {
                        return true;
                }
        }
        return false;
}

bool Car::detectCarColision(Car car){
        if(sqrt(pow((car.getCenterX() - this->getCenterX()),2) + pow((car.getCenterY() - this->getCenterY()),2))
           < car.getCircleRadius() + this->getCircleRadius()) {
                return true;
        }

        return false;
}

void Car::updateShots(GLdouble t){
        vector<Shot> playerShotsVector = this->getShotsVector();
        for(vector<Shot>::iterator it = playerShotsVector.begin(); it != playerShotsVector.end(); ++it) {
                GLfloat angle = (*it).getCarAngle() + (*it).getCannonAngle();
                (*it).setCenterX((*it).getCenterX() + t*this->getShotSpeed()*cos((angle-90)*M_PI/180));
                (*it).setCenterY((*it).getCenterY() + t*this->getShotSpeed()*sin((angle-90)*M_PI/180));
        }
        this->setShotsVector(playerShotsVector);
        return;
}

void Car::moveForward(GLdouble t){
        this->setCenterX(this->getCenterX() + t*(this->getSpeed()*cos((this->getTheta()-90)*M_PI/180)));
        this->setCenterY(this->getCenterY() + t*(this->getSpeed()*sin((this->getTheta()-90)*M_PI/180)));
        this->setTheta(this->getTheta() + t*(this->getSpeed()*tan((this->getWheelsAngle())*M_PI/180)));
}

void Car::moveBackward(GLdouble t){
        this->setCenterX(this->getCenterX() - t*(this->getSpeed()*cos((this->getTheta()-90)*M_PI/180)));
        this->setCenterY(this->getCenterY() - t*(this->getSpeed()*sin((this->getTheta()-90)*M_PI/180)));
        this->setTheta(this->getTheta() - t*(this->getSpeed()*tan((this->getWheelsAngle())*M_PI/180)));
}
void Car::foeMove(GLdouble t, GLfloat threshold, int direction){
        Utils utils;
        if(utils.randomInt(0,20) == 19)
                this->setCannonAngle(utils.randomInt(-45,45));


        this->setWheelsAngle((-1)*asin(this->getAxisWidth()/threshold)*180/M_PI);
        if(direction == 1) {
                this->moveForward(t);
        } else {
                this->moveBackward(t);
        }


}
