#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
#include <GL/freeglut.h> // Facilita a criação de código e portabilidade do código OpenGL
#include<time.h>
//#include <iostream.h>

#include "player.h"
#include "textures.h"

const int tam = 200;
const int largura = 400;
const int altura = 400;

int map [largura][altura];
int width, height, channels;
unsigned char *ht_map = SOIL_load_image ("mapa.png",
                                          &width, &height, &channels,
                                          SOIL_LOAD_RGB);



float camPosZ=0;
float camModo;
float camPosX;

int floor=0;
int drawdist = 10;


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




static void drawBoxWall(GLfloat size, GLenum type){
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    glBegin(type);
        glNormal3fv(&n[i][0]);
        glTexCoord2f(0,0);glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2f(0,1);glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(1,1);glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(1,0);glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

void APIENTRY glutSolidCubeWall (GLdouble size){
  drawBoxWall(size, GL_QUADS);
}


void wall(double thickness)    // function to create the walls with given thickness
{
    glPushMatrix();
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(1.0,thickness,1.0);
    glutSolidCubeWall(1.0);
    glPopMatrix();
}

float frame=1;

void switch_frame(){
  if (frame==0)
    frame=1;
  else
    frame=0;
}

void duck(){
  glBindTexture(GL_TEXTURE_2D, loadPinto());
  glTranslated(0.0, 0.1, 0.0);
  glutSolidCubeWall(0.1);
  glTranslated(0.0, 0.1, 0.0);
  glutSolidCubeWall(0.05);
  glBindTexture(GL_TEXTURE_2D, loadPe());
  glTranslated(-frame/40, -0.2, -0.02);
  glutSolidCubeWall(0.03);
  glTranslated(2*frame/40, 0.0, 0.04);
  glutSolidCubeWall(0.03);

  switch_frame();
}



void draw_room(float posx, float posy, int esquerda, int direita, int cima, int baixo){


  //printf("E: %d , D: %d , C: %d B: %d \n",esquerda,direita,cima,baixo);

  glPushMatrix();



  float altura=0.55;



  //glTranslated(0.08,0.08,0.08);
  //gluLookAt(10.0-camPosZ,10.0,10.0,4.0,0.0,0.0,0.0,1.0,0.0);


  if(getFacing()==1){
    gluLookAt( getX(), altura+camPosZ/5*1, getY()-camPosZ/5*3,
               getX(), altura, getY()+1,
               0.0, 1.0, 0.0);
    //printf("Olhando para direita");
  }

  if(getFacing()==2){

    gluLookAt( getX()+camPosZ/5*3, altura+camPosZ/5*1, getY(),
               getX()-1, altura, getY(),
               0.0, 1.0, 0.0);


    //printf("Olhando para baixo");
  }

  if(getFacing()==3){
    gluLookAt( getX(), altura+camPosZ/5*1, getY()+camPosZ/5*3,
               getX(), altura, getY()-1,
               0.0, 1.0, 0.0);
    //printf("Olhando para esquerda");
  }

  if(getFacing()==0){
    gluLookAt( getX()-camPosZ/5*3, altura+camPosZ/5*1, getY(),
               getX()+1, altura, getY(),
               0.0, 1.0, 0.0);
    //printf("Olhando para cima");
  }


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, loadWall());
  glPolygonMode(GL_FRONT, GL_FILL);


  // //glTranslated(posx,posy,0);
  glTranslated(posx,0,posy);
  glPushMatrix();
  glTranslated(0.6,0.38,0.5);


  if(posx==getI() && posy==getJ() && camPosZ!=0){ //desenha personagem

    if(getFacing()==1){
      glPushMatrix();
      glRotated(-90.0,0.0,1.0,0.0);



      duck();

      glPopMatrix();
      glBindTexture(GL_TEXTURE_2D, loadWall());
    }
    if(getFacing()==0){

      duck();
      glBindTexture(GL_TEXTURE_2D, loadWall());
    }
    if(getFacing()==2){
      glPushMatrix();
      glRotated(-180.0,0.0,1.0,0.0);
      duck();
      glPopMatrix();
      glBindTexture(GL_TEXTURE_2D, loadWall());
    }
    if(getFacing()==3){
      glPushMatrix();
      glRotated(90.0,0.0,1.0,0.0);
      duck();
      glPopMatrix();
      glBindTexture(GL_TEXTURE_2D, loadWall());
    }


  }
  glRotated(30,0,1,0);

  glPopMatrix();

  glPushMatrix();
  glTranslated(0.25,0.42,0.35);
  glPopMatrix();
  glPushMatrix();
  glTranslated(0.4,0,0.4);
  glPopMatrix();

  if(floor!=0){

    glBindTexture(GL_TEXTURE_2D, loadFloor());
    wall(0.02); // CHAO
    glBindTexture(GL_TEXTURE_2D, loadWall());
  }else{
    wall(0.02); // CHAO
  }



  glTranslated(0.0,0.99,0.0);
  if(camPosZ==0)
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



  glDisable(GL_TEXTURE_2D);



  //glFlush();

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
  if(camPosZ==0)
    camPosZ=1;
  else
    camPosZ=0;

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



  int i=getI();
  int j=getJ();

  int drawXmin = i - drawdist;
  int drawXmax = i + drawdist;
  int drawYmin = j -drawdist;
  int drawYmax = j + drawdist;



  if (drawXmin<0){
    drawXmin=0;
  }
  if (drawYmin<0){
    drawXmin=0;
  }
  if(drawXmax>=height){
    drawXmax=height-1;
  }
  if(drawXmax>=width){
    drawXmax=width-1;
  }




  for(i=drawXmin; i<drawXmax; i++){
    for(j=drawYmin; j<drawYmax; j++){
      if(map[i][j]!=0){
          draw_room(i,j,check_inbouds(i,j-1),check_inbouds(i,j+1),check_inbouds(i-1,j),check_inbouds(i+1,j));
      }
    }
  }
  glFlush();
  glutSwapBuffers();
}


//        -------- GERAÇAO ALEATORIA -----------



typedef struct elemento{
  int valor;
  int percorrido;
}elemento;

void inicializa (elemento matrx[altura][largura]){
  int i,j;
  int aux;
  for (i=0;i<height;i++){
    for(j=0;j<width;j++){

      aux=rand()%100;

      if(aux>50)
        matrx[i][j].valor=1;
      else
        matrx[i][j].valor=0
        ;
      matrx[i][j].percorrido=0;
    }
  }
  matrx[0][0].valor=1;
  matrx[height-1][width-1].valor=1;
}

void imprime (elemento matrx[altura][largura]){
  int i,j;
  for (i=0;i<height;i++){
    for(j=0;j<width;j++){
      printf("%d ",matrx[i][j].valor);
    }
    printf("\n");
  }
}

//TAD Pilha

typedef struct coord{
  int a;
  int b;
}coord;

int topo=0;

coord pilha;

void pushpilha(int a, int b, coord pilha []){
  if(topo == tam){
    printf("A pilha esta cheia");
  }
  else{
    pilha[topo].a = a;
    pilha[topo].b = b;
    topo++;
  }
}

void poppilha(coord pilha []){
  if(topo == 0){
      printf("A pilha esta vazia");
  }
  else{
    topo--;
  }
}

void imprimePilha(coord pilha[]){
  int i;
  printf("\n");
  for(i=0;i<topo;i++){
    printf("Passo %d: [x=%d,y=%d]\n",i+1,pilha[i].b,pilha[i].a);
  }
}

int flag=0;

int validaXY(int x, int y){
 if(x>=0 && x<height && y>=0 && y<width){
   return 1;
 }
 return 0;
}

void verifica(elemento matrx [altura][largura],int i,int j, int xde, int yde,coord pilha []){

  pushpilha(i,j,pilha);
  matrx[i][j].percorrido=1;

  if (i==xde && j==yde){
    flag=1;
    printf("\nExiste caminho possivel:");
    imprimePilha(pilha);
  }

  if(validaXY(i+1,j) && matrx [i+1][j].percorrido==0 && matrx [i+1][j].valor==1 && flag==0){
    verifica (matrx,i+1,j,xde,yde,pilha);
  }
  if(validaXY(i,j+1) && matrx [i][j+1].percorrido==0 && matrx [i][j+1].valor==1 && flag==0){
    verifica (matrx,i,j+1,xde,yde,pilha);
  }
  if(validaXY(i-1,j) && matrx [i-1][j].percorrido==0 && matrx [i-1][j].valor==1 && flag==0){
    verifica (matrx,i-1,j,xde,yde,pilha);
  }
  if(validaXY(i,j-1) && matrx [i][j-1].percorrido==0 && matrx [i][j-1].valor==1 && flag==0){
    verifica (matrx,i,j-1,xde,yde,pilha);
  }
  poppilha(pilha);
}



void generate_random(){
  int i,j;
  srand(time(NULL));
  elemento matriz [altura][largura];

  while (flag!=1){
    printf("Gerando Matriz\n");
    coord pilha[tam];
    inicializa(matriz);
    //imprime(matriz);
    verifica(matriz,0,0,height-1,width-1,pilha);
  }
  for(i=0;i<height;i++){
    for (j=0;j<width;j++){
      map[i][j]=matriz[i][j].valor;
    }
  }
  map[0][0]=3;
  map[height-1][width-1]=2;

  map_print();
  player_restart();
  flag=0;
}


void changefloor(){
  if(floor==0){
    floor=1;
    drawdist=5;
  }else{
    floor=0;
    drawdist=10;
  }


}
