#include<stdio.h>
#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
//#include <iostream.h>


void wall(double thickness)    // function to create the walls with given thickness
{
    glPushMatrix();
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(1.0,thickness,1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}


void displaySolid(){    //function to create a 3d room
  GLfloat mat_ambient[]={0.7f,0.7f,0.7f,0.1f};
  GLfloat mat_diffuse[]={0.5f,0.5f,0.5f,1.0f};
  GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
  GLfloat mat_shininess[]={50.0f};
  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
  GLfloat light_Intensity[]={0.7f,0.7f,0.7f,1.0f};
  GLfloat light_Position[]={2.0f,6.0f,3.0f,0.0f};
  glLightfv(GL_LIGHT0,GL_POSITION,light_Position);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light_Intensity);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double winlet=1.0;
  glOrtho(-winlet*64/48,winlet*64/48.0,-winlet*64/48,winlet*64/48,0.6,100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2.3,1.38,2.0,0.0,0.25,0.0,0.0,1.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glTranslated(0.08,0.08,0.08);
  glPushMatrix();
  glTranslated(0.6,0.38,0.5);
  glRotated(30,0,1,0);
  glutSolidTeapot(0.08);
  glPopMatrix();
  glPushMatrix();
  glTranslated(0.25,0.42,0.35);
  glPopMatrix();
  glPushMatrix();
  glTranslated(0.4,0,0.4);
  glPopMatrix();
  wall(0.2);
  glPushMatrix();
  glRotated(-90.0,1.0,0.0,0.0);
  wall(0.02);
  glPopMatrix();
  glRotated(90.0,0.0,0.0,180.0);
  wall(0.02);
  glPopMatrix();
  glFlush();
}










// ---------- TADS MAPA




const int largura = 400;
const int altura = 400;
int map [largura][altura];
int width, height, channels;
unsigned char *ht_map = SOIL_load_image ("mapa.png",
                                          &width, &height, &channels,
                                          SOIL_LOAD_RGB);

void map_init(){
  int i,j;

  for (i=0;i<height;i++){
    for(j=0;j<width;j++){
      if(ht_map[(i*width+j)*3]==0 && ht_map[(i*width+j)*3+1]==0 && ht_map[(i*width+j)*3+2]==0){
        map[i][j]=0;
      }
      else if(ht_map[(i*width+j)*3]==255 && ht_map[(i*width+j)*3+1]==255 && ht_map[(i*width+j)*3+2]==255){
        map[i][j]=1;
      }else if (ht_map[(i*width+j)*3]==255 && ht_map[(i*width+j)*3+1]==0 && ht_map[(i*width+j)*3+2]==0){
        map[i][j]=2;
      }else {
        map[i][j]=3;
      }
    }
  }
}


void map_print(){
  int i,j;
  for (i=0;i<height;i++){
    for(j=0;j<width;j++){
      if (map[i][j]==0)
        printf("x ");
      else
        printf("  ");

      //printf("%d ",map[i][j]);

    }
    printf("\n");
  }
}

// ---------- TADS MAPA







// ---------- TADS GLUT

// NOVIDADE: callback para o evento "reshape"
void redimensionada(int width, int height) {
    if (height == 0) height = 1; //

    double ratio = (double)width / (double)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    bounds = (Bounds){-ratio,ratio,-1.0,1.0};
//   printf("%f ",bounds.left);
//-ratio, ratio, -1, 1, -1, 1);//
    glOrtho(bounds.left,bounds.right, bounds.bottom,bounds.top, -1.0, 1.0);

/*  if (width<=height){
    gluOrtho2D(0.0, janelaw, 0.0, janelah*height/width);
  }else{
    gluOrtho2D(0.0, janelaw*width/height/2, 0.0, janelah);
  }*/

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// NOVIDADE: callback de "keyboard"
void teclaPressionada(unsigned char key, int x, int y) {
    //printf("%d -> %c\n",key,key);
    // vê qual tecla foi pressionada
    switch(key){
        case 27: // Tecla ESC, sai do jogo
            auxiliarEstado = estadojogo;
            estadojogo = 4;
            glutPostRedisplay();
            break;

        default:
            break;
    }
}

void mousePressionado(int botao, int estado, int x, int y) {
    if ((botao == GLUT_LEFT_BUTTON) && (estado == GLUT_UP)) {
        printf("%d e %d\n", x, y);
        if (estadojogo == 4) {
            if ((y > 0) && (y < 600)) {
                if ((x > 0) && (x < 400)) {
                    exit(0);
                } else if ((x > 400) && (x < 1000)) {
                    estadojogo = auxiliarEstado;
                }
            }
        }

        if (estadojogo == 6 || estadojogo == 7) {
            if ((y > 0) && (y < 600)) {
                if ((x > 0) && (x < 400)) {
                    estadojogo = 0;
                    setup();
                } else if ((x > 400) && (x < 1000)) {
                    if (estadojogo == 6) estadojogo = auxiliarEstado;
                    if (estadojogo == 7) exit(0);
                }
            }
        }
    }
}





// ----------- TADS GLUT




int main(int argc, char *argv[]) {
  /*glutInit(&argc, argv);
  map_init();
  map_print();


  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(600, 400);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("TP2");

  glutReshapeFunc(redimensionada);
  glutKeyboardFunc(teclaPressionada);
  glutMouseFunc(mousePressionado);
*/

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(0,0);
  glutCreateWindow("the pot");
  glutDisplayFunc(displaySolid);
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
