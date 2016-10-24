#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
#include <GL/freeglut.h>


float player_posx=0.5;
float player_posy=0.5;
int facing=1;


void move_fwd(){

  if(facing==1){
    player_posy+=1;
  }
  if(facing==2){
    player_posx-=1;
  }
  if(facing==3){
    player_posy-=1;
  }
  if(facing==0){
    player_posx+=1;
  }
}

void move_bkwd(){

  if(facing==1){
    player_posy-=1;
  }
  if(facing==2){
    player_posx+=1;
  }
  if(facing==3){
    player_posy+=1;
  }
  if(facing==0){
    player_posx-=1;
  }
}

void turn_left(){

  printf("Estava em: %d\n",facing);
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
  printf("Foi para: %d\n",facing);


}


void turn_right(){
  printf("Estava em: %d\n",facing);
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
  printf("Foi para: %d\n",facing);
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
