#include "lista_encandeada/Lista_encadeada.cpp"

int main(int argc, char const *argv[])
{
  ListaEncadeada* lista = inicializa_ponteiro();
  Insere(createEstado(1,1,1), lista);
  Insere(createEstado(1,1,2), lista);
  Insere(createEstado(1,1,3), lista);
  Insere(createEstado(1,1,10), lista, 0);
  Insere(createEstado(1,1,40), lista);
  Imprime(lista);
  printf("\n%d\n\n", pop_last(lista)->estado.valor);
  Imprime(lista);
  Insere(createEstado(1,1,400), lista,0);
  printf("\n%d\n\n", pop_first(lista)->estado.valor);
  Imprime(lista);
  return 0;
}
