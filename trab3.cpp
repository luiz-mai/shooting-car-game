/*****************************************************************************************
**																						**
**						UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO							**
**							   Luiz Felipe Ferreira Mai 								**
**																						**
**						   Trabalho 2 de Computação Gráfica								**
**																						**
*****************************************************************************************/

#include "trab3.h"

using namespace std;

int i_status[1000];
vector<Circle> circleVector;
vector<Shot> shotsVector;
Circle* outerTrack;
Rectangle* startTrack;
Car* car;
int biggestRadius = 0;
bool colision = false;
int width, height;
int arenaCenterX = 0, arenaCenterY = 0;
GLfloat carRadius;
bool moving;
int lastX;
bool shooting;


int main(int argc, char** argv) {

	Trab3 trab;
	car = new Car();

	//Abre o arquivo no caminho especificado pelo argumento
	string arenaFullPath = trab.getArenaPath(argc, argv);
	circleVector = trab.arenaReading(trab, arenaFullPath, circleVector);
	car->setCenterX(circleVector.front().getCenterX());
	car->setCenterY(circleVector.front().getCenterY());

	//Define tamanho e título da janela
	width = 2*biggestRadius;
	height = 2*biggestRadius;

	//Inicializações
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width,height);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Trabalho 3 de Computacao Grafica");
	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		arenaCenterX - biggestRadius, arenaCenterX + biggestRadius,
		arenaCenterY + biggestRadius, arenaCenterY - biggestRadius,
		-1, 1
	);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMotion);
	glutMainLoop();
	return 0;
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Desenha todos os inimigos
	for(vector<Circle>::iterator it = ++circleVector.begin(); it != circleVector.end(); ++it) {
    	(*it).drawCircle();
	}
	//Desenha a pista de largada/chegada
	startTrack->drawRectangle();

	car->drawCar(circleVector.front().getRadius(), moving);

	GLfloat playerRadius = circleVector.front().getRadius();
	GLfloat carWidth = car->getWidth();
	for(vector<Shot>::iterator it = shotsVector.begin(); it != shotsVector.end(); ++it) {
		(*it).drawShot(playerRadius, car);
	}

	glutSwapBuffers();
	glFlush();
	return;
}

void idle(){

	float oldCenterX =  car->getCenterX();
	float oldCenterY =  car->getCenterY();

	static GLdouble previousTime = 0;
    GLdouble currentTime;
    GLdouble t;

    // Elapsed time from the initiation of the game.
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    t = currentTime - previousTime; // Elapsed time from the previous frame.
    previousTime = currentTime; //Update previous time

	char c;
	if(i_status['w'] == 1 || i_status['W'] == 1){
		car->setCenterX(car->getCenterX() + t*(car->getSpeed()*cos((car->getTheta()-90)*M_PI/180)));
		car->setCenterY(car->getCenterY() + t*(car->getSpeed()*sin((car->getTheta()-90)*M_PI/180)));
		car->setTheta(car->getTheta() + t*(car->getSpeed()*tan((car->getWheelsAngle())*M_PI/180)));
	}

	if(i_status['s'] == 1 || i_status['S'] == 1){
		car->setCenterX(car->getCenterX() - t*(car->getSpeed()*cos((car->getTheta()-90)*M_PI/180)));
		car->setCenterY(car->getCenterY() - t*(car->getSpeed()*sin((car->getTheta()-90)*M_PI/180)));
		car->setTheta(car->getTheta() - t*(car->getSpeed()*tan((car->getWheelsAngle())*M_PI/180)));
	}
	c = 'a';
	if(i_status[c] == 1) car->setWheelsAngle(car->getWheelsAngle() - 0.3);
	c = 'A';
	if(i_status[c] == 1) car->setWheelsAngle(car->getWheelsAngle() - 0.3);
	c = 'd';
	if(i_status[c] == 1) car->setWheelsAngle(car->getWheelsAngle() + 0.3);
	c = 'D';
	if(i_status[c] == 1) car->setWheelsAngle(car->getWheelsAngle() + 0.3);

	if(i_status['w'] == 1 || i_status['W'] == 1 || i_status['s'] == 1 || i_status['S'] == 1){
		moving = true;
	} else {
		moving = false;
	}

	for(vector<Shot>::iterator it = shotsVector.begin(); it != shotsVector.end(); ++it) {
		GLfloat angle = (*it).getShotAngle();
		(*it).setCenterX((*it).getCenterX() + t*car->getShotSpeed()*cos((angle-90)*M_PI/180));
		(*it).setCenterY((*it).getCenterY() + t*car->getShotSpeed()*sin((angle-90)*M_PI/180));
	}

	//Detecta colisão
	for(vector<Circle>::iterator it = ++circleVector.begin(); it != circleVector.end(); ++it) {
    	Circle c = (*it);

    	if(c.getRadius() != biggestRadius ){
    		if(sqrt(pow((c.getCenterX() - car->getCenterX()),2) + pow((c.getCenterY() - car->getCenterY()),2))
    		 < c.getRadius() + carRadius){
    			car->setCenterX(oldCenterX);
    			car->setCenterY(oldCenterY);
    		}
    	} else {
    		if(sqrt(pow((c.getCenterX() - car->getCenterX()),2)+pow(c.getCenterY() - car->getCenterY(),2)) + carRadius
    			> biggestRadius){
    			car->setCenterX(oldCenterX);
    			car->setCenterY(oldCenterY);
    		}
    	}
	}

	glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y){
	i_status[key] = 0;
	return;
}

void keyPressed(unsigned char key, int x, int y){
	i_status[key] = 1;
	return;
}

void mouseClick(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		Circle* shotCircle = new Circle(
			"Shot",
			12,
			0,
			0,
			"white"
		);
		Shot* shot = new Shot(
			*shotCircle,
			car->getCenterX(),
			car->getCenterY(),
			car->getTheta() + car->getCannonAngle()
		);
		shotsVector.push_back(*shot);

		cout << car->getTheta() << " / " << shot->getShotAngle() << endl;
	}
}

void mouseMotion(int x, int y){
	int centerX = width/2;
	if(x > centerX){
		car->setCannonAngle(45*(x-centerX)/centerX);
	} else if (x < centerX){
		car->setCannonAngle(-45*(centerX-x)/centerX);
	}
	return;
}


//----------------------------MÉTODOS DA CLASSE--------------------------------

Trab3::Trab3(){}


string Trab3::getArenaPath(int argc, char** argv){
	XMLDocument configs;
	string configFile;
	if(argc == 1){
		configFile =  "config.xml";
	} else {
		string path = argv[1];
		configFile =  path + "config.xml";
	}
	configs.LoadFile(configFile.c_str());
	XMLElement* aplicationElement = configs.FirstChildElement("aplicacao");
	XMLElement* arenaFileElement = aplicationElement->FirstChildElement("arquivoDaArena");
	XMLElement* carroFileElement = aplicationElement->FirstChildElement("carro");
	car->setSpeed( carroFileElement->FloatAttribute("velCarro"));
	car->setShotSpeed( carroFileElement->FloatAttribute("velTiro"));
	string arenaPath = arenaFileElement->Attribute("caminho");
	string arenaFilename = arenaFileElement->Attribute("nome");
	string arenaExtension = arenaFileElement->Attribute("tipo");
	return arenaPath + arenaFilename + "." + arenaExtension;
}

vector<Circle> Trab3::arenaReading(Trab3 trab, string arenaFullPath, vector<Circle> circleVector){
	//Leitura do arquivo da Arena
	XMLDocument arena;
	arena.LoadFile(arenaFullPath.c_str());
	XMLElement* svgElement = arena.FirstChildElement("svg");

	startTrack = trab.rectangleReading(svgElement);
	circleVector = trab.circleReading(svgElement, circleVector);
	return circleVector;
}

Rectangle* Trab3::rectangleReading(XMLElement* svgElement){
	//Leitura da pista de largada/chegada
	XMLElement* rectElement = svgElement->FirstChildElement("rect");
	Rectangle* rect = new Rectangle(
		rectElement->Attribute("id"),
		rectElement->FloatAttribute("x"),
		rectElement->FloatAttribute("y"),
		rectElement->FloatAttribute("width"),
		rectElement->FloatAttribute("height"),
		rectElement->Attribute("fill")
	);
	return rect;
}

vector<Circle> Trab3::circleReading(XMLElement* svgElement, vector<Circle> circleVector){
	//Leitura das pistas e jogadores
	for(XMLElement* circleElement = svgElement->FirstChildElement("circle"); circleElement != NULL; circleElement = circleElement->NextSiblingElement("circle"))
	{
		Circle* circle = new Circle(
			circleElement->Attribute("id"),
			circleElement->FloatAttribute("r"),
			circleElement->FloatAttribute("cx"),
			circleElement->FloatAttribute("cy"),
			circleElement->Attribute("fill")
		);

		//Garante que o jogador sempre será o primeiro do vector
		if(circle->getID() == "Jogador"){
			vector<Circle>::iterator it;
			it = circleVector.begin();
			circleVector.insert(it, *circle);
			carRadius = circle->getRadius();
		} else {
			circleVector.push_back(*circle);
		}
		//Considerações para ajustar o tamanho da tela e posição dos elementos
		if(circle->getRadius() > biggestRadius){
			biggestRadius = circle->getRadius();
			arenaCenterX = circle->getCenterX();
			arenaCenterY = circle->getCenterY();
		}
	}

	return circleVector;
}
