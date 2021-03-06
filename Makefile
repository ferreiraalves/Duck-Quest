FONTES = *.cpp
OBJETOS = *.o 

all:	main clean run

main : $(OBJETOS)
	g++ $(OBJETOS) -o main -lGL -lglut -lGLU -lm -lSOIL


$(OBJETOS) : $(FONTES)
	g++ -c $(FONTES)

clean :
	-@ rm -f $(OBJETOS)

run:
	./main
