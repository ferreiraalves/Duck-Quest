#include<stdio.h>
#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
#include <GL/freeglut.h> // Facilita a criação de código e portabilidade do código OpenGL
//#include <iostream.h>

//BIBLIOTECAS


#include "mapa.h"
#include "setup.h"
#include "player.h"
#include "textures.h"

// NOVIDADE: callback de "keyboard"
void teclaPressionada(unsigned char key, int x, int y) {
    //printf("%d -> %c\n",key,key);
    // vê qual tecla foi pressionada
    switch(key)
    {
        case 119: //tecla "w"

            move_fwd();
            break;

        case 115: //tecla "a"
            move_bkwd();
            break;

        case 97: //tecla "a"
            turn_left();
            break;

        case 100: //tecla "d"
            turn_right();
            break;

        case 99: //tecla "c"
            sobeCameraZ();
            break;

        case 114: //tecla "r"
            player_restart();
            break;

        case 103: //tecla "g"
            generate_random();
            break;

        case 113: //tecla "q"
            changefloor();


        default:
            break;
    }
    glutPostRedisplay();
}






int main(int argc,char **argv) {

  map_init();
  map_print();

  printf("\nControles: \n");

  printf("\nW: Da um passo para frente");
  printf("\nS: Da um passa para tras");
  printf("\nA: Vira para a esquerda");
  printf("\nD: Vira para a direita");
  printf("\n");
  printf("\nC: Camera");
  printf("\nR: Reset");
  printf("\nQ: Muda Piso");
  printf("\nG: Gera novo labirinto (pode demorar)");
  printf("\n");
  printf("\n");

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(0,0);


  glutCreateWindow("Duck Quest");




  init_setup();



  glutDisplayFunc(desenhaLabirinto);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glClearColor(0.1,0.1,0.1,0.0);
  glViewport(0,0,640,480);

  glutKeyboardFunc(teclaPressionada);

  glutMainLoop();


  return 0;
}
