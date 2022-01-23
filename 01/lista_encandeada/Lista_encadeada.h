#define TAMATRIZ 7

typedef struct celula *Apontador;

typedef struct estado{
  int x;
  int y;
  int valor;
} Estado;

typedef struct celula {
    Estado estado;
    Apontador Prox;
}Celula;

typedef struct matriz{
  int matriz[TAMATRIZ][TAMATRIZ];
} Matriz;


//typedef struct ListaEncadeada *ListaEncadeada;

typedef struct{
    Apontador Primeiro, Ultimo;
    int Tamanho = 0;
} ListaEncadeada;

typedef struct {
    ListaEncadeada fila[TAMATRIZ][TAMATRIZ];
}Memoria;


ListaEncadeada inicializa();
void FLVazia(ListaEncadeada*);
bool Vazia(ListaEncadeada*);
void Insere(Estado, ListaEncadeada*);
void Insere(Estado, ListaEncadeada*, int posicao);
void Imprime(ListaEncadeada*);
Estado createEstado(int, int, int);