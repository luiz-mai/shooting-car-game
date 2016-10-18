#include "Utils.h"

void Utils::checkColor(string fill){
	if(fill == "blue")
		glColor3f(0.0, 0.0, 1.0);
	else if(fill == "red")
		glColor3f(1.0, 0.0, 0.0);
	else if(fill == "green")
		glColor3f(0.0, 1.0, 0.0);
	else if(fill == "cyan")
		glColor3f(0.0, 1.0, 1.0);
	else if(fill == "magenta")
		glColor3f(1.0, 0.0, 1.0);
	else if(fill == "yellow")
		glColor3f(1.0, 1.0, 0.0);
	else if(fill == "wine")
		glColor3f(0.3647, 0.0, 0.0);
	else if(fill == "white")
		glColor3f(1.0, 1.0, 1.0);
	else if(fill == "black")
		glColor3f(0.0, 0.0, 0.0);
	return;
}
