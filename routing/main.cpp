#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
/* Dislay function, used to display output in desired form*/
void display1(int time, char s, char d, char via, int cost);
void display2(char s, char d, char via, int cost);

/*Structure to store routing table*/
struct node {
  unsigned dist[20];
  unsigned from[20];
} rt[10];

int main(int argc, char **argv) {
  FILE *config_file;      /* configuration file */
  FILE *changConfig_file; /* configuration change file */
  config_file = fopen(argv[1], "r");
  changConfig_file = fopen(argv[2], "r");
  

  int k, cost, time = 0;

  /* Read in data */
  char str1 = fgetc(config_file);
  int num_nodes = atoi(&str1);

  double inf = 1000;
  int dmat[5][5];
  char Router[num_nodes];

  /*setting initial value in dmat to unlimited distance*/
  for (int i = 0; i < num_nodes; i++) {
    for (int j = 0; j < num_nodes; j++) {
      dmat[i][j] = inf;
    }
  }

  printf("\n#START  \n");
  /*Extracting Router ID*/
  for (int r = 0; r < num_nodes; ++r) {
    if (feof(config_file) != 1) {
      fgetc(config_file);
      char str2 = fgetc(config_file);
      Router[r] = str2;
    }
  }

  int num_links = 0;
  /*Extracting Link Info*/
  if (feof(config_file) != 1) {
    fgetc(config_file);
    char a = fgetc(config_file);
    num_links = atoi(&a);
  }

  for (int l = 0; l < num_links; ++l) {
    fgetc(config_file);
    char s = fgetc(config_file); /*Source*/
    fgetc(config_file);
    char d = fgetc(config_file); /*Distination*/
    fgetc(config_file);
    char c = fgetc(config_file); /*cost of the link*/
    cost = atoi(&c);
    /*printf("\nsource: %c destination: %c cost: %i \n",s,d,cost);*/
    for (int i = 0; i < num_nodes; i++) {
      /*save link cost in rt data structure*/
      if (s == Router[i]) {
        for (int j = 0; j < num_nodes; j++) {
          if (d == Router[j]) {
            dmat[i][i] = 0;
            rt[i].dist[j] = cost;
            rt[i].from[j] = j;
            rt[j].dist[i] = cost;
            rt[j].from[i] = i;

            /*displaying 2 way link info*/
            display1(time, s, d, Router[rt[i].from[j]], cost);
            display1(time, d, s, Router[rt[j].from[i]], cost);
          }
        }
      }
    }
  }

  printf("\n");

for(int i =0; i < num_nodes;i++){
    for (int j=0; j < num_nodes; j++){
      if(rt[i].dist[j] == 0){
        rt[i].dist[j] = 99;
        
      }
    }
  }
  // those dist router itself set to 0
  for(int i =0; i < num_nodes;i++){
    for (int j=0; j < num_nodes; j++){
      rt[i].dist[i] = 0;
    }
  }

  cout << endl;

  int flag;
  /*Updating the table*/
  do {
    flag = 0;
    for (int l = 0; l < num_links; ++l) {
      fgetc(config_file);
      char s = fgetc(config_file); /*Source*/
      fgetc(config_file);
      char d = fgetc(config_file); /*Distination*/
      fgetc(config_file);
      char c = fgetc(config_file); /*cost of the link*/
      cost = atoi(&c);
      for (int i = 0; i < num_nodes; i++) {
        for (int j = i+1; j < num_nodes; j++) {
          for (k = 0; k < num_nodes; k++) {
          /* Finding minimum cost*/
            if ((rt[i].dist[j]) > (rt[i].dist[k] + rt[k].dist[j])) {
              rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
              rt[j].dist[i] = rt[i].dist[j];
              rt[i].from[j] = k;
              rt[j].from[i] = k;
              cost = rt[i].dist[j];
              flag = 1;
              display1(time, s, d, Router[rt[i].from[j]], cost);
              display1(time, d, s, Router[rt[j].from[i]], cost);
          }
        }
      }
      time++;
    }
  }
  } while (flag);  
  cout<<endl;

  printf("\n\n#INITIAL  \n");
  for (int i = 0; i < num_nodes; i++) {
    for (int j = 0; j < num_nodes; j++) {
      if (rt[i].dist[j] != 0) {
        display2(Router[i], Router[j], Router[rt[i].from[j]], rt[i].dist[j]);
      }
    }
    cout<<endl;
  }
  
  time=0;

  /*Checking for link change info*/
  printf("\n\n#UPDATE  \n");
  char c = fgetc(changConfig_file);
  int c_link = atoi(&c);

  for (int j = 0; j < c_link; j++) { /*Extracting link change infor from change config file*/
    fgetc(changConfig_file);
    char s = fgetc(changConfig_file);
    fgetc(changConfig_file);
    char d = fgetc(changConfig_file);
    fgetc(changConfig_file);
    c = fgetc(changConfig_file);
    cost = atoi(&c);

    for (int i = 0; i < num_nodes; i++) {
      if (s == Router[i]) {
        for (int j = 0; j < num_nodes; j++) {
          if (d == Router[j]) {
            dmat[i][i] = 0;
            rt[i].dist[j] = cost;
            rt[i].from[j] = j;
            rt[j].dist[i] = cost;
            rt[j].from[i] = i;

            /* Display change in link*/
            display1(time, s, d, Router[rt[i].from[j]], cost);
            display1(time, d, s, Router[rt[j].from[i]], cost);
          }
        }
      }
    }
  }

  int flag2;
  do {
    flag2 = 0;
    for (int i = 0; i < num_nodes; i++) {
      for (int j = 0; j < num_nodes; j++) {
        for (k = 0; k < num_nodes; k++) {
          if ((rt[i].dist[j]) > (rt[i].dist[k] + rt[k].dist[j])) {
            rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
            rt[i].from[j] = k;
            flag2 = 1;
          }
        }
      }
    }
  } while (flag2);
  /*Displaying final route*/
  printf("\n\n#FINAL  \n");
  for (int i = 0; i < num_nodes; i++) {
    for (int j = 0; j < num_nodes; j++) {
      if (rt[i].dist[j] != 0) {
        display2(Router[i], Router[j], Router[rt[i].from[j]], rt[i].dist[j]);
      }
    }
    cout<<endl;
  }

  printf("\n");
  

  printf("\n\n");
  fclose(config_file);
  fclose(changConfig_file);
  return (0);
}
/* Display1 and display2 functions are used to display link information at
 different time stamp. At the input, they take source id s, destination id d,
 intermidiate router id 'via', and link cost*/

void display1(int time, char s, char d, char via, int cost) {
  printf("\nt=%d distance from %c to %c via %c is %d", time, s, d, via, cost);
}

void display2(char s, char d, char via, int cost) { printf("\nRouter %c: %c is %d through %c ", s, d, cost, via); }