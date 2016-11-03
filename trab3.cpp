/*****************************************************************************************
**																						**
**						UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO							**
**							   Luiz Felipe Ferreira Mai               **
**																						**
**						   Trabalho 3 de Computação Gráfica								**
**																						**
*****************************************************************************************/

#include "trab3.h"

using namespace std;

//VARIÁVEIS GLOBAIS
Trab3 trab;
int i_status[1000];
vector<Circle> trackVector;
vector<Car> foesVector;
Circle* outerTrack;
Rectangle* startTrack;
Car* player;
int biggestRadius = 0, smallestRadius = 99999;
int width, height;
int arenaCenterX = 0, arenaCenterY = 0;
GLfloat foeSpeed;
GLfloat foeShootingSpeed;
GLfloat foeShootingFrequency;
GLfloat shootingTime = 0;
int movingBackward = 0;
// Text variable
static char str[2000];
void * timer_font = GLUT_BITMAP_9_BY_15;
void * end_font = GLUT_BITMAP_TIMES_ROMAN_24;
time_t start = time(0);
int seconds, minutes;
int gameState = 0;
GLfloat lastX = 9999, lastY = 9999;
int main(int argc, char** argv) {

								player = new Car();

								//Abre o arquivo de config e seta o centro do carro.
								string arenaFullPath = trab.getArenaPath(argc, argv);
								trackVector = trab.arenaReading(trab, arenaFullPath, trackVector);

								//Define tamanho e título da janela
								width = 2*biggestRadius;
								height = 2*biggestRadius;

								//Inicializações
								glutInit(&argc, argv);
								glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
								glutInitWindowSize(width,height);
								glutInitWindowPosition(100,100);
								glutCreateWindow("Trabalho 4 de Computacao Grafica");
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
								if(gameState == 0) {
																trab.printCronometer(60,70);
																//Desenha a pista
																for(vector<Circle>::iterator it = trackVector.begin(); it != trackVector.end(); ++it) {
																								(*it).drawCircle();
																}
																//Desenha a pista de largada/chegada
																startTrack->drawRectangle();
																//Desenha o carro
																player->drawCar();


																//Desenha todos os inimigos
																for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
																								(*it).drawCar();
																}
																//Desenha os tiros
																player->drawShots();
																for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
																								(*it).drawShots();
																}

								} else{
																trab.printEndMessage(width/2, height/2);
								}
								glutSwapBuffers();
								glFlush();
								return;
}

void idle(){
								if(gameState == 0) {
																float oldCenterX =  player->getCenterX();
																float oldCenterY =  player->getCenterY();

																//Efetua a medição do tempo decorrido
																static GLdouble previousTime = 0;
																GLdouble currentTime;
																GLdouble t;
																currentTime = glutGet(GLUT_ELAPSED_TIME);
																t = currentTime - previousTime;
																previousTime = currentTime;

																//Movimentação do carro
																char c;
																//Define as flags usadas pra representaçao do movimento nas rodas.
																if(i_status['w'] == 1 || i_status['W'] == 1 || i_status['s'] == 1 || i_status['S'] == 1) {
																								lastX = player->getCenterX();
																								lastY = player->getCenterY();
																								player->setMoving(true);
																								if(i_status['w'] == 1 || i_status['W'] == 1) {
																																player->moveForward(t);
																								}
																								if(i_status['s'] == 1 || i_status['S'] == 1) {
																																player->moveBackward(t);
																								}
																								if(player->getCenterY() + player->getCircleRadius() > startTrack->getBeginY() && lastY < startTrack->getBeginY()) {
																																gameState = 1;
																								}
																} else {
																								player->setMoving(false);
																}


																//Angulação do carro
																c = 'a';
																if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() - 1.5);
																c = 'A';
																if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() - 1.5);
																c = 'd';
																if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() + 1.5);
																c = 'D';
																if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() + 1.5);



																//Movimentação dos tiros do jogador
																vector<Shot> playerShotsVector = player->getShotsVector();
																player->updateShots(t);
																//Remove os tiros fora da tela
																playerShotsVector.erase(
																								remove_if(playerShotsVector.begin(), playerShotsVector.end(), outOfScreen),
																								playerShotsVector.end());

																//Remove os tiros fora da tela
																foesVector.erase(
																								remove_if(foesVector.begin(), foesVector.end(), detectEnemyShotColision),
																								foesVector.end());

																shootingTime += foeShootingFrequency*t;
																if(shootingTime >= 1) {
																								for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
																																(*it).addShot();
																								}
																								shootingTime = 0;
																}
																//Detecta colisão com os inimigos
																if(player->detectFoeColision(foesVector) || player->detectTrackColision(trackVector, biggestRadius)) {
																								player->setCenterX(oldCenterX);
																								player->setCenterY(oldCenterY);
																}

																Utils utils;
																for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
																								vector<Shot> foeShotsVector = (*it).getShotsVector();
																								for(vector<Shot>::iterator it2 = foeShotsVector.begin(); it2 != foeShotsVector.end(); ++it2) {
																																if(utils.distance2P((*it2).getCenterX(), (*it2).getCenterY(), player->getCenterX(), player->getCenterY()) < player->getCircleRadius()) {
																																								//gameState = -1;
																																}
																								}
																}

																for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {

																								int index = it - foesVector.begin();
																								vector<Car> otherFoes = foesVector;
																								otherFoes.erase(otherFoes.begin() + index);

																								vector<Shot> foeShotsVector = (*it).getShotsVector();
																								(*it).updateShots(t);
																								//Remove os tiros fora da tela
																								foeShotsVector.erase(
																																remove_if(foeShotsVector.begin(), foeShotsVector.end(), outOfScreen),
																																foeShotsVector.end());

																								GLfloat threshold = smallestRadius + (biggestRadius-smallestRadius)/2;

																								if((*it).detectTrackColision(trackVector, biggestRadius) || (*it).detectCarColision(*player) || (*it).detectFoeColision(otherFoes)) {
																																Utils utils;
																																(*it).foeMove(t, threshold, -1);
																																(*it).setBackwardCount(utils.randomInt(20, 100));
																								} else if ((*it).getBackwardCount() > 0) {
																																(*it).foeMove(t, threshold, -1);
																																(*it).setBackwardCount((*it).getBackwardCount()-1);
																								} else {
																																(*it).foeMove(t, threshold, 1);
																								}
																}



								}

								glutPostRedisplay();
}

bool outOfScreen(Shot shot)
{
								return shot.getCenterX() < arenaCenterX - biggestRadius ||
															shot.getCenterX() > arenaCenterX + biggestRadius ||
															shot.getCenterY() < arenaCenterY - biggestRadius ||
															shot.getCenterY() > arenaCenterY + biggestRadius;
}

bool detectEnemyShotColision(Car car){
								Utils utils;
								vector<Shot> playerShotsVector = player->getShotsVector();
								for(vector<Shot>::iterator it = playerShotsVector.begin(); it != playerShotsVector.end(); ++it) {
																if(utils.distance2P(car.getCenterX(), car.getCenterY(), (*it).getCenterX(), (*it).getCenterY()) < car.getCircleRadius()) {
																								int index = it - playerShotsVector.begin();
																								playerShotsVector.erase(playerShotsVector.begin() + index);
																								player->setShotsVector(playerShotsVector);
																								return true;
																}
								}
								return false;
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
								if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
																//Cria um novo tiro e insere no vetor
																player->addShot();
								}
}

void mouseMotion(int x, int y){
								//Determina a angulação do canhão.
								//Canto esquerdo da tela: -45 / Canto direito da tela: +45
								int centerX = width/2;
								if(x > centerX) {
																player->setCannonAngle(45*(x-centerX)/centerX);
								} else if (x < centerX) {
																player->setCannonAngle(-45*(centerX-x)/centerX);
								}
								return;
}


//----------------------------MÉTODOS DA CLASSE--------------------------------

Trab3::Trab3(){
}


string Trab3::getArenaPath(int argc, char** argv){
								//Retorna o caminho do arquivo da arena
								//Seta as configurações do carro
								XMLDocument configs;
								string configFile;
								if(argc == 1) {
																configFile =  "config.xml";
								} else {
																string path = argv[1];
																configFile =  path + "config.xml";
								}
								configs.LoadFile(configFile.c_str());
								XMLElement* aplicationElement = configs.FirstChildElement("aplicacao");
								XMLElement* arenaFileElement = aplicationElement->FirstChildElement("arquivoDaArena");
								XMLElement* carroFileElement = aplicationElement->FirstChildElement("carro");
								player->setSpeed( carroFileElement->FloatAttribute("velCarro"));
								player->setShotSpeed( carroFileElement->FloatAttribute("velTiro"));
								XMLElement* carroInimigoFileElement = aplicationElement->FirstChildElement("carroInimigo");
								foeSpeed = carroInimigoFileElement->FloatAttribute("velCarro");
								foeShootingSpeed = carroInimigoFileElement->FloatAttribute("velTiro");
								foeShootingFrequency = carroInimigoFileElement->FloatAttribute("freqTiro");
								string arenaPath = arenaFileElement->Attribute("caminho");
								string arenaFilename = arenaFileElement->Attribute("nome");
								string arenaExtension = arenaFileElement->Attribute("tipo");
								return arenaPath + arenaFilename + "." + arenaExtension;
}

vector<Circle> Trab3::arenaReading(Trab3 trab, string arenaFullPath, vector<Circle> trackVector){
								//Leitura do arquivo da Arena
								XMLDocument arena;
								arena.LoadFile(arenaFullPath.c_str());
								XMLElement* svgElement = arena.FirstChildElement("svg");
								startTrack = trab.rectangleReading(svgElement);
								trackVector = trab.circleReading(svgElement, trackVector);
								return trackVector;
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

vector<Circle> Trab3::circleReading(XMLElement* svgElement, vector<Circle> trackVector){
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
																if(circle->getID() == "Jogador") {
																								player->setCenterX(circle->getCenterX());
																								player->setCenterY(circle->getCenterY());
																								player->setCircleRadius(circle->getRadius());
																								player->setColor(circle->getFill());
																} else if(circle->getID() == "Inimigo") {
																								Car* foe = new Car();
																								foe->setCenterX(circle->getCenterX());
																								foe->setCenterY(circle->getCenterY());
																								foe->setCircleRadius(circle->getRadius());
																								foe->setColor(circle->getFill());
																								foe->setSpeed(foeSpeed);
																								foe->setShotSpeed(foeShootingSpeed);
																								GLfloat initialAngle = atan(((arenaCenterY - foe->getCenterY())/(foe->getCenterX() - arenaCenterX)))*180/M_PI;
																								if(foe->getCenterX() < arenaCenterX) {
																																foe->setTheta(180-initialAngle);
																								} else {
																																foe->setTheta(-initialAngle);
																								}
																								foesVector.push_back(*foe);
																} else {
																								trackVector.push_back(*circle);
																								if(circle->getRadius() > biggestRadius) {
																																biggestRadius = circle->getRadius();
																																arenaCenterX = circle->getCenterX();
																																arenaCenterY = circle->getCenterY();
																								}
																								if(circle->getRadius() < smallestRadius) {
																																smallestRadius = circle->getRadius();
																								}
																}
																//Considerações para ajustar o tamanho da tela e posição dos elementos

								}

								return trackVector;
}

void Trab3::printCronometer(GLfloat x, GLfloat y){
								//Create a string to be printed
								char *tmpStr;
								int seconds_since_start = difftime( time(0), start);
								minutes = seconds_since_start / 60;
								seconds = seconds_since_start % 60;
								sprintf(str, "%02d:%02d", minutes, seconds);
								//Define the position to start printing
								glRasterPos2f(x, y);
								//Print  the first Char with a certain font
								//glutBitmapLength(font,(unsigned char*)str);
								tmpStr = str;
								//Print each of the other Char at time
								while( *tmpStr ) {
																glutBitmapCharacter(timer_font, *tmpStr);
																tmpStr++;
								}
}

void Trab3::printEndMessage(GLfloat x, GLfloat y){
								//Create a string to be printed
								char *tmpStr;
								if(gameState == 1) {
																sprintf(str, "You win!");

								} else if(gameState == -1) {
																sprintf(str, "GAME OVER!");
								}
								//Define the position to start printing
								glRasterPos2f(x, y);
								//Print  the first Char with a certain font
								//glutBitmapLength(font,(unsigned char*)str);
								tmpStr = str;
								//Print each of the other Char at time
								while( *tmpStr ) {
																glutBitmapCharacter(end_font, *tmpStr);
																tmpStr++;
								}
}
