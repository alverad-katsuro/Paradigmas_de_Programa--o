#define MAXTAM 1000
#define TAMATRIZ 7
typedef int TipoApontador;

typedef struct Memo{
  int x;
  int y;
  int valor;
} Memo;

typedef struct {
    Memo Item[MAXTAM];
    TipoApontador Frente, Tras;
}Fila;


typedef struct matriz{
  int matriz[TAMATRIZ][TAMATRIZ];
} Matriz;

typedef struct {
    Fila fila[TAMATRIZ][TAMATRIZ];
}Memoria;


Fila* inicializa();
void EmptyNow(Fila *);
bool isEmpty(Fila *);
bool isFull(Fila *);
bool Enqueue(int, int, Fila *);
bool Enqueue(Memo, Fila *);
Memo Dequeue(Fila *);
bool showQueue(Fila *);
bool furarFila(Fila *, int);
Memo createMemo(int, int, int);
