#include<stdio.h>
#include<cstdio>
#include<stdlib.h>
#include "SOIL/SOIL.h"
//#include <iostream.h>

const int largura = 400;
const int altura = 400;
int map [largura][altura];
int width, height, channels;
unsigned char *ht_map = SOIL_load_image ("mapa.png",
                                          &width, &height, &channels,
                                          SOIL_LOAD_RGB);

/*
const largura 400;
const altura 400;
int width, height;
int map [largura][altura];


unsigned char* readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];

    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    return data;
}
*/

void map_init(){
  int i,j;
  for (i=0;i<width;i++){
    for(j=0;j<height;j++){
      if(ht_map[(i*width+j)*3]<200 && ht_map[(i*width+j)]<200 && ht_map[(i*width+j)*3+2]<200){
      //if(ht_map[i][j][0]==0 && ht_map[i][j][1]==0 && ht_map[i][j][2]==0)
        map[i][j]=0;
      }
      else{
        map[i][j]=1;
      }
    }
  }
}


void map_print(){
  FILE* out = fopen("out.txt", "w");
  int i,j;
  for(j=0;j<height;j++){
    for (i=0;i<width;i++){
      if (map[i][j]==0)
        fprintf(out,"x ");
      else
        fprintf(out,"  ");

        //fprintf(out,"%d",map[i][j]);
    }

    fprintf(out,"\n");
  }
}

int main(){
  map_init();
  map_print();
  return 0;
}
