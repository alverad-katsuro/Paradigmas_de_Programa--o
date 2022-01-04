#include <stdio.h>
#include "Fila.cpp"

// Algoritmo base, isto é, teste de conceito a fim de facilitar o desenvolvimento da busca global.
// Nele há a busca gulosa, que busca o minimo local.
Fila* busca_gulosa(int x, int y,int matriz[TAMATRIZ][TAMATRIZ]) {
  Fila* fila; 
  Memo estado_atual = createMemo(x, y, matriz[x][y]);
  printf("y: %d x: %d\n", y, x);
  if (x < TAMATRIZ - 1  && y < TAMATRIZ - 1) {
    if (matriz[y][x+1] < matriz[y+1][x]) {
      x++;
      fila = busca_gulosa(x, y, matriz);
      furarFila(estado_atual, fila);
      return fila;
    } else {
      y++;
      fila = busca_gulosa(x, y, matriz);
      furarFila(estado_atual, fila);
      return fila;
    }    
  } else if (x < TAMATRIZ - 1) {
    x++;
    fila = busca_gulosa(x, y, matriz);
    furarFila(estado_atual, fila);
    return fila;
  } else if (y < TAMATRIZ - 1) {
    y++;
    fila = busca_gulosa(x, y, matriz);
    furarFila(estado_atual, fila);
    return fila;
  } else {
    fila = inicializa();
    furarFila(estado_atual, fila);
    return fila;
  }
}

// Calcula o custo de um caminho
int custoCaminho(Fila fila){
  int custo = 0;
  while (!isEmpty(&fila)){
    Memo memo = Dequeue(&fila);
    custo += memo.valor;
  }
  return custo;
}

// Realiza a busca global, usando a Memoria para armazenar o melhor caminho a partir das coordenadas x e y
Fila busca_global(int x, int y, Matriz* matriz, Memoria* memoria) {
  Fila fila_x = *inicializa(); 
  Fila fila_y = *inicializa();
  Memo estado_atual = createMemo(x, y, matriz->matriz[y][x]);
  if (x < TAMATRIZ - 1) {
    fila_x = busca_global(x + 1, y, matriz, memoria);
    furarFila(estado_atual, &fila_x);    
  }
  if (y < TAMATRIZ - 1) {
    fila_y = busca_global(x, y + 1, matriz, memoria);
    furarFila(estado_atual, &fila_y);    
  }
  //printf("%d %d\n",x,y);
  if (x == y && x == TAMATRIZ - 1){
    if (isEmpty(&memoria->fila[y][x])) {
      printf("Entro\n");
      Enqueue(estado_atual, &memoria->fila[x][y]);
      return memoria->fila[x][y];
    }
    return memoria->fila[x][y];
  }
  if (isEmpty(&fila_x)){
    if (isEmpty(&memoria->fila[y][x])) {
      memoria->fila[y][x] = fila_y;
      return fila_y;
    } else {
      if (custoCaminho(fila_y) < custoCaminho(memoria->fila[y][x])) {
        memoria->fila[y][x] = fila_y;
        return fila_y;
      } else {
        return memoria->fila[y][x];
      }
    }
  } else if (isEmpty(&fila_y)){
    if (isEmpty(&memoria->fila[y][x])) {
      memoria->fila[y][x] = fila_x;
      return fila_x;
    } else {
      if (custoCaminho(fila_x) < custoCaminho(memoria->fila[y][x])) {
        memoria->fila[y][x] = fila_x;
        return fila_x;
      } else {
        return memoria->fila[y][x];
      }
    }
  } else if (custoCaminho(fila_x) < custoCaminho(fila_y)) {
    if (isEmpty(&memoria->fila[y][x])) {
      memoria->fila[y][x] = fila_x;
      return fila_x;
    } else {
      if (custoCaminho(fila_x) < custoCaminho(memoria->fila[y][x])) {
        memoria->fila[y][x] = fila_x;
        return fila_x;
      } else {
        return memoria->fila[y][x];
      }
    }
  } else {
    if (isEmpty(&memoria->fila[y][x])) {
      memoria->fila[y][x] = fila_y;
      return fila_y;
    } else {
      if (custoCaminho(fila_y) < custoCaminho(memoria->fila[y][x])) {
        memoria->fila[y][x] = fila_y;
        return fila_y;
      } else {
        return memoria->fila[y][x];
      }
    }
  }
  
}

// Chama a função que calcula o custo global recursivamente e exibe os resultados
void showPath(int x, int y, Matriz* matriz){
  Memoria memoria = instancia_memoria();
  Fila fila = busca_global(x, y, matriz, &memoria);
  showQueue(&fila);
  printf("O custo do caminho é: %d\n", custoCaminho(fila));
}

int main(int argc, char const *argv[]){

  int matriz_ext[TAMATRIZ][TAMATRIZ] = {
    { 5, 9,  6,  4, 3, 8, 7 }, 
    { 4, 1,  3,  5, 6, 8, 7 }, 
    { 3, 1,  4,  5, 6, 8, 7 }, 
    { 1, 3,  4,  5, 6, 8, 7 }, 
    { 1, 3,  4,  5, 6, 8, 7 }, 
    { 1, 3,  4,  5, 2, 7, 8 }, 
    { 1, 3,  4,  5, 6, 7, 8 }
  };

  Matriz matriz;
  for (int i = 0; i < TAMATRIZ; i++) {
    for (int k = 0; k < TAMATRIZ; k++) {
      matriz.matriz[i][k] = matriz_ext[i][k];
    }
  }
  //Fila* fila = busca_gulosa(0, 0, matriz);
  //showQueue(fila);
  showPath(0, 0, &matriz);
}
