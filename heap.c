#include <stdio.h>
#include "heap.h"


int insert(int dist, int p, int last, int heap[][2]){ //Insere um novo elemento na heap
  heap[last][0] = dist;
  heap[last][1] = p;
  return checaHeapPai(last, heap);
}

//target is the process to be removed
int extract(int heap[][2], int last){ //Extrai o menor elemento da heap;
  int ans;
  ans = heap[1][1];
  heap[1][1] = heap[last][1];
  heap[1][0] = heap[last][0];
  checaHeapFilho(1, heap, last);
  return ans;
}


void checaHeapFilho(int i, int heap[][2], int last){ //Corrige a heap do elemento i até o nível necessário
  int smallest = i;
  int tmp[2];
  if(valido(leftson(i), last) && heap[leftson(i)][0] < heap[smallest][0]) smallest = leftson(i);
  if(valido(rightson(i), last) && heap[rightson(i)][0] < heap[smallest][0]) smallest = rightson(i);

  if(smallest != i){
    tmp[0] = heap[smallest][0];
    tmp[1] = heap[smallest][1];
    heap[smallest][0] = heap[i][0];
    heap[smallest][1] = heap[i][1];
    heap[i][0] = tmp[0];
    heap[i][1] = tmp[1];
    checaHeapFilho(smallest, heap, last);
  }
  return;
}

int checaHeapPai(int i, int heap[][2]){ //Corrige a heap do elemento i até o nivel necessario
  int tmp[2];

  if(i == 1) return i; //Caso for a raiz, retorna
  if(heap[dad(i)][0] > heap[i][0]){ //Se o pai for maior que o elemento considerado, troca e chama para o pai
    tmp[0] = heap[dad(i)][0];
    tmp[1] = heap[dad(i)][1];
    heap[dad(i)][0] = heap[i][0];
    heap[dad(i)][1] = heap[i][1];
    heap[i][0] = tmp[0];
    heap[i][1] = tmp[1];
  }
  checaHeapPai(dad(i), heap);
  return i;
}
