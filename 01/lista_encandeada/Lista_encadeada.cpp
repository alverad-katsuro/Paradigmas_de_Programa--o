#include <stdio.h>
#include <cstdlib>
#include "Lista_encadeada.h"


ListaEncadeada inicializa(){
    ListaEncadeada Lista;
    Lista.Primeiro = (Apontador) malloc(sizeof(Celula));
    Lista.Ultimo = Lista.Primeiro;
    return Lista;
}

ListaEncadeada* inicializa_ponteiro(){
    ListaEncadeada* Lista = (ListaEncadeada*) malloc(sizeof(ListaEncadeada));
    Lista->Primeiro = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    return Lista;
}

bool Vazia(ListaEncadeada *lista){
  if (lista->Primeiro == lista->Ultimo){
    return true;
  }else{
    return false;
  }
}

void FLVazia(ListaEncadeada *lista){
    lista->Primeiro = (Apontador) malloc(sizeof(Celula));
    lista->Ultimo = lista->Primeiro;
    lista->Primeiro->Prox = NULL;
    lista->Tamanho = 0;
    lista->Primeiro->estado = *((Estado *) malloc(sizeof(Estado)));
}

void Insere(Estado estado, ListaEncadeada *lista){
  if (Vazia(lista)){
    lista->Primeiro->estado = estado;
    lista->Ultimo = (Apontador) malloc(sizeof(Celula));
    lista->Primeiro->Prox = lista->Ultimo;
    lista->Tamanho++;
  } else {
    Apontador novo;
    novo = (Apontador) malloc(sizeof(Celula));
    lista->Ultimo->estado = estado;
    lista->Ultimo->Prox = novo;
    lista->Ultimo = novo;
    lista->Tamanho++;
  }
}

void Insere(Estado estado, ListaEncadeada *lista, int posicao){
  if (posicao >= 0) {
    if (Vazia(lista) || lista->Tamanho <= posicao) {
      Insere(estado, lista);
    } else {
      Apontador novo = (Apontador) malloc(sizeof(Celula));
      if (posicao == 0) {
        novo->Prox = lista->Primeiro;
        novo->estado = estado;
        lista->Primeiro = novo;      
      } else {
        Apontador apontador = lista->Primeiro;
        for (int i = 1; i < posicao; i++) {
          apontador = apontador->Prox;
        }
        printf("rentro%d\n", posicao);
        novo->Prox = apontador->Prox;
        novo->estado = estado;
        apontador->Prox = novo;
      }
      lista->Tamanho++;
    }
  }
}

void Imprime(ListaEncadeada *lista){
  if (!Vazia(lista)) {
    Apontador apontador = lista->Primeiro;
    printf("O tamanho da lista é %d\n", lista->Tamanho);
    int i = 0;
    while (apontador != lista->Ultimo) {
      printf("O valor do index %d é %d\n", i, apontador->estado.valor);
      apontador = apontador->Prox;
      i++;
    }
  }
}

Apontador pop_first(ListaEncadeada *lista){
  Apontador item;
  if (!Vazia(lista)) {
   item = lista->Primeiro;
   lista->Primeiro = lista->Primeiro->Prox;
  }
  lista->Tamanho--;
  return item; 
}

Apontador pop_last(ListaEncadeada *lista){
  Apontador apontador = lista->Primeiro;
  if (!Vazia(lista)) {
    if (lista->Tamanho >= 2) {    
      for (int i = 1; i < lista->Tamanho - 1; i++) {
        apontador = apontador->Prox;
      }
      Apontador item = apontador->Prox;
      Apontador novo = (Apontador) malloc(sizeof(Celula));
      apontador->Prox = novo;
      lista->Ultimo = novo;
      lista->Tamanho--;
      return item;
    } else if (lista->Tamanho == 1) {
      FLVazia(lista);
    }
  }
  lista->Tamanho--;
  return apontador; 
}

Estado createEstado(int x, int y, int valor){
  Estado memo;
  memo.x = x;
  memo.y = y;
  memo.valor = valor;
  return memo;
}