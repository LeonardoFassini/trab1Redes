#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.c"

#define MAX 1123
#define INF 112345

void readConfig(char s[], char a[], int *id, char ip[][MAX], char port[][MAX]){
  int j = 0;
  int i;

  for(i = 0; s[i] != ' '; i++) a[j++] = s[i];
  a[j] = '\0';
  *id = atoi(a);
  while(s[i] == ' ') i++;
  j = 0;
  for(; s[i] != ' '; i++) port[*id][j++] = s[i];
  port[*id][j] = '\0';
  while(s[i] == ' ') i++;
  j= 0;
  for(; s[i] != '\n'; i++) ip[*id][j++] = s[i];
  ip[*id][j] = '\0';
}

void readEnlace(char s[], char a[], int *line, int *column, int *cost){
  int j = 0;
  int i;

  for(i = 0; s[i] != ' '; i++) a[j++] = s[i];
  a[j] = '\0';
  *line = atoi(a);
  while(s[i] == ' ') i++;
  j = 0;
  for(; s[i] != ' '; i++) a[j++] = s[i];
  a[j] = '\0';
  *column = atoi(a);
  while(s[i] == ' ') i++;
  j= 0;
  for(; s[i] != '\n'; i++) a[j++] = s[i];
  a[j] = '\0';
  *cost = atoi(a);
}

int dijkstra(int eg[][MAX], int s, int t, int heap[][2], int vid[], int count){
  int dist[MAX], vis[MAX], i, last = 0, current, pai[MAX], j;
  for(i = 1; i <= count; i++){ dist[i] = INF; vis[i] = 0; }
  dist[s] = 0;
  pai[s] = s;
  insert(dist[s], s, ++last, heap);
  while(last > 0){
    current = extract(heap, last--);
    if(vis[current]) continue;
    vis[current] = 1;
    for(int i = 1; i <= count; i++){
      if(eg[current][i] != -1 && !vis[i] && (dist[i] > dist[current] + eg[current][i])){
	dist[i] = dist[current] + eg[current][i];
	pai[i] = current;
	insert(dist[i], i, ++last, heap);
      }
    }
    if(current == t){
      while(pai[current] != s)
	current = pai[current];
      return current;
      //return dist[t];
    }
  }
  while(pai[current] != s)
    current = pai[current];
  return current;
  //return dist[t];
}

int main(void){
  int myid, line, column, cost, eg[MAX][MAX], id, vid[MAX], count = 0, i, heap[MAX][2], j;
  char s[MAX], a[MAX], ip[MAX][MAX], port[MAX][MAX];
  FILE *p;
  
  scanf("%d", &myid);
  p = fopen("roteador.config", "r");
  memset(vid, 0, sizeof(vid));
  memset(eg, -1, sizeof(eg));
  while(fgets(s, 100, p) != NULL){ //Leitura dos ids, ips e sockets dos roteadores.
    count++;
    readConfig(s, a, &id, ip, port);
    vid[id] = 1;
  }
  for(i = 1; i <= count; i++){
    if(vid[i] != 0)
      printf("%d %s %s\n", i, ip[i], port[i]);
  }
  printf("\n");
  p = fopen("enlaces.config", "r");
  while(fgets(s, 100, p) != NULL){ //Leitura dos enlaces e seus pesos.
    readEnlace(s, a, &line, &column, &cost);
    eg[line][column] = cost;
    eg[column][line] = cost;
    printf("%d %d %d\n", line, column, cost);
  }
  printf("\n");
  for(i = 1; i <= count; i++) //Rode dijkstra
    printf("%d->%d %d\n", myid, i, dijkstra(eg, myid, i, heap, vid, count));  
}
