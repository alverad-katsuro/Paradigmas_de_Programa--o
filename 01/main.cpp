#include <stdio.h>
#include "lista_encandeada/Lista_encadeada.cpp"

// Alfredo Gabriel de Sousa Oliveira - 202004940020
// https://github.com/alverad-katsuro/Paradigmas_de_Programa--o
// Algoritmo base, isto é, teste de conceito a fim de facilitar o desenvolvimento da busca global.
// Nele há a busca gulosa, que busca o minimo local.
void busca_gulosa(int x, int y, int matriz[TAMATRIZ][TAMATRIZ]) {
  printf("y: %d x: %d\n", y, x);
  if (x < TAMATRIZ - 1  && y < TAMATRIZ - 1) {
    if (matriz[y][x+1] < matriz[y+1][x]) {
      x++;
      busca_gulosa(x, y, matriz);
    } else {
      y++;
      busca_gulosa(x, y, matriz);
    }    
  } else if (x < TAMATRIZ - 1) {
    x++;
    busca_gulosa(x, y, matriz);
  } else if (y < TAMATRIZ - 1) {
    y++;
    busca_gulosa(x, y, matriz);
  }
}

// Calcula o custo de um caminho
int custoCaminho(ListaEncadeada* fila){
  Apontador apontador = fila->Primeiro;
  int custo = apontador->estado.valor;
  for (int i = 1; i < fila->Tamanho; i++) {
    custo += apontador->estado.valor;
    apontador = apontador->Prox;
  }
  return custo;
}

// Realiza a busca global, usando a Memoria para armazenar o melhor caminho a partir das coordenadas x e y
ListaEncadeada busca_global(int x, int y, Matriz* matriz, Memoria* memoria) {
  if (Vazia(&memoria->fila[y][x])) {
    ListaEncadeada fila_x = inicializa(); 
    ListaEncadeada fila_y = inicializa();
    Estado estado_atual = createEstado(x, y, matriz->matriz[y][x]);
    if (x < TAMATRIZ - 1) {
      fila_x = busca_global(x + 1, y, matriz, memoria);
      Insere(estado_atual, &fila_x, 0);    
    }
    if (y < TAMATRIZ - 1) {
      fila_y = busca_global(x, y + 1, matriz, memoria);
      Insere(estado_atual, &fila_y, 0);    
    }
    if (x == y && x == TAMATRIZ - 1){
      if (Vazia(&memoria->fila[y][x])) {
        Insere(estado_atual, &memoria->fila[y][x]);    
      }
      return memoria->fila[y][x];
    }
    if (Vazia(&fila_x)){
      if (Vazia(&memoria->fila[y][x])) {
        memoria->fila[y][x] = fila_y;
        return memoria->fila[y][x];
      } else {
        if (custoCaminho(&fila_y) < custoCaminho(&memoria->fila[y][x])) {
          memoria->fila[y][x] = fila_y;
        } 
        return memoria->fila[y][x];
      }
    } else if (Vazia(&fila_y)){
      if (Vazia(&memoria->fila[y][x])) {
        memoria->fila[y][x] = fila_x;
        return memoria->fila[y][x];
      } else {
        if (custoCaminho(&fila_x) < custoCaminho(&memoria->fila[y][x])) {
          memoria->fila[y][x] = fila_x;
        }
        return memoria->fila[y][x];
      }
    } else if (custoCaminho(&fila_x) < custoCaminho(&fila_y)) {
      if (Vazia(&memoria->fila[y][x])) {
        memoria->fila[y][x] = fila_x;
        return memoria->fila[y][x];
      } else {
        if (custoCaminho(&fila_x) < custoCaminho(&memoria->fila[y][x])) {
          memoria->fila[y][x] = fila_x;
        }
        return memoria->fila[y][x];
      }
    } else {
      if (Vazia(&memoria->fila[y][x])) {
        memoria->fila[y][x] = fila_y;
        return memoria->fila[y][x];
      } else {
        if (custoCaminho(&fila_y) < custoCaminho(&memoria->fila[y][x])) {
          memoria->fila[y][x] = fila_y;
        }
        return memoria->fila[y][x];
      }
    }
  } else {
    return memoria->fila[y][x];
  }
}

Memoria instancia_memoria(){
  Memoria memoria;
  for (int i = 0; i < TAMATRIZ; i++) {
    for (int k = 0; k < TAMATRIZ; k++) {
      memoria.fila[i][k] = inicializa();
    }
  }
  return memoria;
}

void Imprime_caminho(int custo, ListaEncadeada *lista){
  if (!Vazia(lista)) {
    Apontador apontador = pop_last(lista);
    Imprime_caminho(apontador->estado.valor + custo, lista);
    printf("x %d y %d custo: %d\n", apontador->estado.x, apontador->estado.y ,apontador->estado.valor);
  } else {
    printf("O custo do caminho é: %d\n", custo);
  }
}

void Imprime_caminho(ListaEncadeada *lista){
  if (!Vazia(lista)) {
    Apontador apontador = pop_last(lista);
    Imprime_caminho(apontador->estado.valor, lista);
    printf("x %d y %d custo: %d\n", apontador->estado.x, apontador->estado.y ,apontador->estado.valor);
  }
}

// Chama a função que calcula o custo global recursivamente e exibe os resultados
void showPath(int x, int y, Matriz* matriz){
  Memoria memoria = instancia_memoria();
  ListaEncadeada fila = busca_global(x, y, matriz, &memoria);
  Imprime_caminho(&fila);
}

int main(int argc, char const *argv[]){
  // Matriz de entrada
  int matriz_ext[TAMATRIZ][TAMATRIZ] = {
    {5, 9, 6, 4, 3, 8, 7}, 
    {4, 1, 3, 5, 6, 8, 7}, 
    {3, 1, 4, 5, 6, 8, 7}, 
    {1, 3, 4, 5, 6, 8, 7}, 
    {1, 3, 4, 5, 6, 8, 7}, 
    {1, 3, 4, 5, 2, 7, 8}, 
    {1, 3, 4, 5, 6, 7, 8}
  };

  // Instanciando a matriz (struct)
  Matriz matriz;
  for (int i = 0; i < TAMATRIZ; i++) {
    for (int k = 0; k < TAMATRIZ; k++) {
      matriz.matriz[i][k] = matriz_ext[i][k];
    }
  }
  // Funções teste (rodam a gulosa)
  //busca_gulosa(0, 0, matriz_ext);
  // Chamada da função da atividade
  showPath(0, 0, &matriz);
}
