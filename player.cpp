#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
#include <GL/freeglut.h>
#include "mapa.h"

float player_posx=0.5;
float player_posy=0.5;
int facing=1;

int player_i=0;
int player_j=0;


void player_restart();

void move_fwd(){

  if(facing==1 && check_inbouds(player_i,player_j+1)){
    player_posy+=1;
    player_j+=1;
  }
  if(facing==2 && check_inbouds(player_i-1,player_j)){
    player_posx-=1;
    player_i-=1;
  }
  if(facing==3&& check_inbouds(player_i,player_j-1)){
    player_posy-=1;
    player_j-=1;
  }
  if(facing==0 && check_inbouds(player_i+1,player_j)){
    player_posx+=1;
    player_i+=1;
  }


  if(player_i==getHeight()-1 && player_j==getWidth()-1){
    printf("\n");
    printf("\n\nPARABENS VOCE.......... VOLTOU PARA O INICIO\n\n");
    printf("\n");
    printf("\n");
    player_restart();
  }
}

void move_bkwd(){

  if(facing==1 && check_inbouds(player_i,player_j-1)){
    player_posy-=1;
    player_j-=1;
  }
  if(facing==2 && check_inbouds(player_i+1,player_j)){
    player_posx+=1;
    player_i+=1;
  }
  if(facing==3 && check_inbouds(player_i,player_j+1)){
    player_posy+=1;
    player_j+=1;
  }
  if(facing==0&& check_inbouds(player_i-1,player_j) ){
    player_posx-=1;
    player_i-=1;
  }

  if(player_i==getHeight()-1 && player_j==getWidth()-1){
    printf("\n");
    printf("\n\nPARABENS VOCE.......... VOLTOU PARA O INICIO\n\n");
    printf("\n");
    printf("\n");
    player_restart();
  }


}

void turn_left(){

  //printf("Estava em: %d\n",facing);
  if(facing==0){
    facing=3;
  }
  else if(facing==1){
    facing=0;
  }
  else if(facing==2){
    facing=1;
  }
  else if(facing==3){
    facing=2;
  }
  //printf("Foi para: %d\n",facing);


}

void turn_right(){
  //printf("Estava em: %d\n",facing);
  if(facing==0){
    facing=1;
  }
  else if(facing==1){
    facing=2;
  }
  else if(facing==2){
    facing=3;
  }
  else if(facing==3){
    facing=0;
  }
  //printf("Foi para: %d\n",facing);
}

float getX(){
  return player_posx;
}

float getY(){
  return player_posy;
}

float getFacing(){
  return facing;
}

int getI(){
  return player_i;
}

int getJ(){
  return player_j;
}

void moveI(int aux){
  player_i+=aux;
}

void moveJ(int aux){
  player_j+=aux;
}


void player_restart(){

  player_posx=0.5;
  player_posy=0.5;
  facing=1;

  player_i=0;
  player_j=0;

}
