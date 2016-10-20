#include<stdio.h>
#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
//#include <iostream.h>







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




// ----------- TADS GLUT




int main(int argc, char const *argv[]) {
  glutInit(&argc, argv);
  map_init();
  map_print();


  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(600, 400);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("TP2");

  glutReshapeFunc(redimensionada);
  glutKeyboardFunc(teclaPressionada);





  return 0;
}
