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
int i_status[1000];
vector<Circle> trackVector;
vector<Car> foesVector;
vector<Shot> shotsVector;
Circle* outerTrack;
Rectangle* startTrack;
Car* player;
int biggestRadius = 0;
bool colision = false;
int width, height;
int arenaCenterX = 0, arenaCenterY = 0;

int main(int argc, char** argv) {

								Trab3 trab;
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
								GLfloat playerRadius = player->getCircleRadius();
								for(vector<Shot>::iterator it = shotsVector.begin(); it != shotsVector.end(); ++it) {
																(*it).drawShot(playerRadius, player);
								}

								glutSwapBuffers();
								glFlush();
								return;
}

void idle(){

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
								if(i_status['w'] == 1 || i_status['W'] == 1) {
																player->setCenterX(player->getCenterX() + t*(player->getSpeed()*cos((player->getTheta()-90)*M_PI/180)));
																player->setCenterY(player->getCenterY() + t*(player->getSpeed()*sin((player->getTheta()-90)*M_PI/180)));
																player->setTheta(player->getTheta() + t*(player->getSpeed()*tan((player->getWheelsAngle())*M_PI/180)));
								}
								if(i_status['s'] == 1 || i_status['S'] == 1) {
																player->setCenterX(player->getCenterX() - t*(player->getSpeed()*cos((player->getTheta()-90)*M_PI/180)));
																player->setCenterY(player->getCenterY() - t*(player->getSpeed()*sin((player->getTheta()-90)*M_PI/180)));
																player->setTheta(player->getTheta() - t*(player->getSpeed()*tan((player->getWheelsAngle())*M_PI/180)));
								}

								//Angulação do carro
								c = 'a';
								if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() - 0.3);
								c = 'A';
								if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() - 0.3);
								c = 'd';
								if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() + 0.3);
								c = 'D';
								if(i_status[c] == 1) player->setWheelsAngle(player->getWheelsAngle() + 0.3);

								//Define as flags usadas pra representaçao do movimento nas rodas.
								if(i_status['w'] == 1 || i_status['W'] == 1 || i_status['s'] == 1 || i_status['S'] == 1) {
																player->setMoving(true);
								} else {
																player->setMoving(false);
								}

								//Movimentação dos tiros
								for(vector<Shot>::iterator it = shotsVector.begin(); it != shotsVector.end(); ++it) {
																GLfloat angle = (*it).getCarAngle() + (*it).getCannonAngle();
																(*it).setCenterX((*it).getCenterX() + t*player->getShotSpeed()*cos((angle-90)*M_PI/180));
																(*it).setCenterY((*it).getCenterY() + t*player->getShotSpeed()*sin((angle-90)*M_PI/180));
								}
								//Remove os tiros fora da tela
								shotsVector.erase(
																remove_if(shotsVector.begin(), shotsVector.end(), outOfScreen),
																shotsVector.end());

								//Detecta colisão com a pista
								for(vector<Circle>::iterator it = trackVector.begin(); it != trackVector.end(); ++it) {
																Circle c = (*it);
																player->detectTrackColision(c, biggestRadius, oldCenterX, oldCenterY);

								}

								//Detecta colisão com os inimigos
								for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
																Car foe = (*it);
																player->detectFoeColision(foe, oldCenterX, oldCenterY);
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

void keyUp(unsigned char key, int x, int y){
								i_status[key] = 0;
								return;
}

void keyPressed(unsigned char key, int x, int y){
								i_status[key] = 1;
								return;
}

void mouseClick(int button, int state, int x, int y){
								if(button == GLUT_LEFT_BUTTON) {
																//Cria um novo tiro e insere no vetor
																Circle* shotCircle = new Circle(
																								"Shot",
																								12,
																								0,
																								0,
																								"white"
																								);
																Shot* shot = new Shot(
																								*shotCircle,
																								player->getCenterX(),
																								player->getCenterY(),
																								player->getTheta(),
																								player->getCannonAngle()
																								);
																shotsVector.push_back(*shot);
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
								for(vector<Car>::iterator it = foesVector.begin(); it != foesVector.end(); ++it) {
																Car foe = (*it);
																foe.setSpeed(carroInimigoFileElement->FloatAttribute("velCarro"));
																foe.setShotSpeed(carroInimigoFileElement->FloatAttribute("velTiro"));
								}
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
																} else if(circle->getID() == "Inimigo") {
																								Car* foe = new Car();
																								foe->setCenterX(circle->getCenterX());
																								foe->setCenterY(circle->getCenterY());
																								foe->setCircleRadius(circle->getRadius());
																								foesVector.push_back(*foe);
																} else {
																								trackVector.push_back(*circle);
																}
																//Considerações para ajustar o tamanho da tela e posição dos elementos
																if(circle->getRadius() > biggestRadius) {
																								biggestRadius = circle->getRadius();
																								arenaCenterX = circle->getCenterX();
																								arenaCenterY = circle->getCenterY();
																}
								}

								return trackVector;
}
