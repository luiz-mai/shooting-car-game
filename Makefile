all: tinyxml classes compila executa

tinyxml:
	@g++ tinyxml2.cpp -c

classes:
	@g++ Utils.cpp -c
	@g++ Triangle.cpp -c
	@g++ Rectangle.cpp -c
	@g++ Circle.cpp -c
	@g++ Car.cpp -c
	@g++ Shot.cpp -c

compila: tinyxml2.o Triangle.o Rectangle.o Circle.o Utils.o Car.o Shot.o
	 @g++ trab3.cpp Triangle.o Circle.o Rectangle.o Utils.o Car.o Shot.o tinyxml2.o -o trabalhocg -lglut -lGLU -lGL
	#@g++ trab3.cpp Triangle.o Circle.o Rectangle.o Utils.o Car.o Shot.o tinyxml2.o glm.o glm_util.o glmimg.o -o trabalhocg -framework GLUT -framework OpenGL -Wno-deprecated-declarations

executa:
	./trabalhocg

clean:
	@rm *.o
	@rm trabalhocg
	@echo "Arquivos removidos com sucesso"
