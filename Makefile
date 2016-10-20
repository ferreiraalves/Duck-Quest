FONTES = *.c
OBJETOS = *.o 

all:	main clean run

main : $(OBJETOS)
	gcc $(OBJETOS) -o main -lGL -lglut -lGLU -lm -lSOIL


$(OBJETOS) : $(FONTES)
	gcc -c $(FONTES)

clean :
	-@ rm -f $(OBJETOS)

run:
	./main
