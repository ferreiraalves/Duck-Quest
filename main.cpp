#include<stdio.h>
#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
#include <GL/freeglut.h> // Facilita a criação de código e portabilidade do código OpenGL
//#include <iostream.h>

//BIBLIOTECAS


#include "mapa.h"
#include "setup.h"

int main(int argc,char **argv) {

  map_init();
  map_print();


  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Cancer Dungeon");


  init_setup();



  glutDisplayFunc(desenhaLabirinto);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glClearColor(0.1,0.1,0.1,0.0);
  glViewport(0,0,640,480);



  glutMainLoop();





  return 0;
}
