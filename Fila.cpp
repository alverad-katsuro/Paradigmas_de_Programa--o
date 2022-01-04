#include "Fila.h"
#include <iostream>

using namespace std;

Fila* inicializa(){
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    EmptyNow(fila);
    return fila;
}

Fila inicializa(int x){
    Fila fila;
    EmptyNow(&fila);
    return fila;
}

void EmptyNow(Fila *Fila){
    Fila->Frente = 0;
    Fila->Tras = 0;
}

bool isEmpty(Fila *Fila){
    return (Fila->Frente == Fila->Tras);
}

bool isFull(Fila *Fila){
    if ((Fila->Tras + 1) % MAXTAM == Fila->Frente){
        cout << "Fila Cheia" <<endl;
        return 1;
    } else {
        return 0;
    }
}

Memo createMemo(int x, int y, int valor){
  Memo memo;
  memo.x = x;
  memo.y = y;
  memo.valor = valor;
  return memo;
}

bool Enqueue(int x, int y, int valor, Fila *Fila){
    if (isFull(Fila)){
        return 0;
    } else {
        Fila->Item[Fila->Tras] = createMemo(x, y, valor);
        Fila->Tras = (Fila->Tras + 1) % MAXTAM;
    }
    return 1;
}

bool Enqueue(Memo memo, Fila *Fila){
    if (isFull(Fila)){
        return 0;
    } else {
        Fila->Item[Fila->Tras] = memo;
        Fila->Tras = (Fila->Tras + 1) % MAXTAM;
    }
    return 1;
}

Memo Dequeue(Fila *Fila){
    if(isEmpty(Fila)){
        cout << "Fila está vazia" << endl;
        Memo a;
        return a;
    } else {
        int idx = Fila->Frente;
        Fila->Frente = (Fila->Frente + 1) % MAXTAM;
        return Fila->Item[idx];
    }
}
int lenght(Fila *Fila){
    if (isEmpty(Fila)){
        return 0;
    }
    else{
        return Fila->Tras;
    }
}

bool furarFila(Memo x, Fila *Fila){
    if (isEmpty(Fila) || isFull(Fila)){
        return 0;
    } else {
        for (int i = Fila->Tras; i >= Fila->Frente; i--){
          Fila->Item[i + 1] = Fila->Item[i];
        }
        Fila->Tras++;
        Fila->Item[Fila->Frente] = x;
    }
    return 1;

}

bool showQueue(Fila *Fila){
    if (isEmpty(Fila)){
        return 0;
    }
    TipoApontador index = Fila->Frente;
    while (true){
      cout << "x: " << Fila->Item[index].x << " y: " << Fila->Item[index].y << /*" valor: " << Fila->Item[index].valor << */ endl; 
      index += 1;
      if (index == Fila->Tras){
          break;
      }
    }
    return 1;
}

bool showQueue(int index, Fila *Fila){
    if (isEmpty(Fila)){
        return 0;
    }
    TipoApontador apontador = Fila->Frente;
    cout << "Posição: " << index << " x: " << Fila->Item[index+apontador].x << " y: " << Fila->Item[index+apontador].y << endl; 
    return 1;
}

Memoria instancia_memoria(){
  Memoria memoria;
  for (int i = 0; i < TAMATRIZ; i++) {
    for (int k = 0; k < TAMATRIZ; k++) {
      memoria.fila[i][k] = inicializa(1);
    }
  }
  return memoria;
}