#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
#include <GL/freeglut.h> // Facilita a criação de código e portabilidade do código OpenGL
//#include <iostream.h>

#include "player.h"



const int largura = 400;
const int altura = 400;
int map [largura][altura];
int width, height, channels;
unsigned char *ht_map = SOIL_load_image ("mapa.png",
                                          &width, &height, &channels,
                                          SOIL_LOAD_RGB);



float camPosZ=0;
float camPosX=0;



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

void wall(double thickness)    // function to create the walls with given thickness
{
    glPushMatrix();
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(1.0,thickness,1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}



void draw_room(float posx, float posy, int esquerda, int direita, int cima, int baixo){


  //printf("E: %d , D: %d , C: %d B: %d \n",esquerda,direita,cima,baixo);

  glPushMatrix();



  float altura=0.8;



  //glTranslated(0.08,0.08,0.08);
  //gluLookAt(10.0-camPosZ,10.0,10.0,4.0,0.0,0.0,0.0,1.0,0.0);


  if(getFacing()==1){
    gluLookAt( getX(), altura, getY(),
               getX(), altura, getY()+1,
               0.0, 1.0, 0.0);
    //printf("Olhando para direita");
  }

  if(getFacing()==2){

    gluLookAt( getX(), altura, getY(),
               getX()-1, altura, getY(),
               0.0, 1.0, 0.0);


    //printf("Olhando para baixo");
  }

  if(getFacing()==3){
    gluLookAt( getX(), altura, getY(),
               getX(), altura, getY()-1,
               0.0, 1.0, 0.0);
    //printf("Olhando para esquerda");
  }

  if(getFacing()==0){
    gluLookAt( getX(), altura, getY(),
               getX()+1, altura, getY(),
               0.0, 1.0, 0.0);
    //printf("Olhando para cima");
  }



  // //glTranslated(posx,posy,0);
  glTranslated(posx,0,posy);
  glPushMatrix();
  glTranslated(0.6,0.38,0.5);
  glRotated(30,0,1,0);
  //glutSolidTeapot(0.08);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.25,0.42,0.35);
  glPopMatrix();
  glPushMatrix();
  glTranslated(0.4,0,0.4);
  glPopMatrix();

  wall(0.02); // CHAO

  glTranslated(0.0,0.99,0.0);
  wall(0.02);  //TETO
  glTranslated(0.0,-0.99,0.0);
  glPushMatrix();
  glRotated(-90.0,1.0,0.0,0.0);
  if(!esquerda)
    wall(0.02); // P DIRETA
  glTranslated(0.0,-1.0,0.0);// parede esquerda
  if(!direita)
    wall(0.02);//ESQUERDA
  glPopMatrix();
  glRotated(90.0,0.0,0.0,1.0);
  if(!cima)
    wall(0.02); // P FUNDO
  glTranslated(0.0,-1.0,0.0);
  if(!baixo)
    wall(0.02); // paraede frente





  glPopMatrix();





  glFlush();





}


int check_inbouds(int i, int j){

  if (i<0 || i>=height){ // out of bounds
      return 0;
  }
  if (j<0 || j>=width){
    return 0;
  }
  if(map[i][j]==0){
    return 0;
  }

  return 1;

}


void sobeCameraZ(){
  camPosZ+=0.1;
}
void desceCameraZ(){
  camPosZ-=0.1;
}

void sobeCameraX(){
  camPosX+=0.1;
}
void desceCameraX(){
  camPosX-=0.1;
}







void desenhaLabirinto(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //teste

  //glPushMatrix();

  // gluLookAt(  10.0+camPosX, 10.08+camPosZ, 10.0,
  //             1.0, 0.8, 4.0,
  //             0.0, 1.0, 0.0);
  //
  //
  // glPopMatrix();

  int i,j;
  for(i=0; i<height; i++){
    for(j=0; j<width; j++){
      if(map[i][j]!=0){
          draw_room(i,j,check_inbouds(i,j-1),check_inbouds(i,j+1),check_inbouds(i-1,j),check_inbouds(i+1,j));
      }
    }
  }

  glutSwapBuffers();
}
