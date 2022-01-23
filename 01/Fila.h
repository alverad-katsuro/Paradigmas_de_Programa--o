#define TAMATRIZ 40
#define MAXTAM 900
typedef int TipoApontador;

// Memo --> guarda o estado atual, ou seja, o valor e a cordenada em um dado espaço
typedef struct Memo{
  int x;
  int y;
  int valor;
} Memo;

// Struct Fila
typedef struct {
    Memo Item[MAXTAM];
    TipoApontador Frente, Tras;
}Fila;

// Matriz de entrada, visto que não é possivel passar int[][] como parametro o mesmo foi envolvido em um struct
typedef struct matriz{
  int matriz[TAMATRIZ][TAMATRIZ];
} Matriz;

// Memoria, usa uma matriz de filas a fim de guarda os melhores caminhos para cada posição visitada
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
