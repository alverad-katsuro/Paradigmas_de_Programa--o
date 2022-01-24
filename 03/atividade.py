#Usado para clonar list
from copy import copy, deepcopy
#Usado para gerar varias matrizes de teste
from random import randint
#Para fins de curiosidade get time
from time import time

#Função que remove a linha 0 a fim de realizar o deslocamento no eixo y
def remove_linha(matriz: list) -> list:
  try:
    if (matriz.pop(0)):
      return matriz
    else:
      return []
  except IndexError:  
    return []

#Função que remove a coluna 0 a fim de realizar o deslocamento no eixo x
def remove_coluna(matriz: list, posicao = 0) -> list:
  try:
    matriz[posicao].pop(0)
    try:
      if (len(matriz[posicao + 1]) != len(matriz[posicao])):
        return remove_coluna(matriz, posicao + 1)
    except IndexError:
      return matriz
  except IndexError:
    return matriz

#Função que localiza o eixo x durante a execução a fim de gravar o caminho na memoria evitar recalculo
def acha_x(matriz, memoria) -> int:
  return len(memoria[0]) - len(matriz[0])

#Função que localiza o eixo y durante a execução
def acha_y(matriz, memoria) -> int:
  return len(memoria) - len(matriz)

#Função que realiza a busca global recursivamente
def busca_global(matriz) -> list:
  #Verifica se ja foi calculado consultando a memoria auxiliar
  if (len(memoria[acha_y(matriz, memoria)][acha_x(matriz, memoria)]) == 0):
    #Verifica se pode deslocar no eixo x
    if(acha_x(matriz, memoria) < len(memoria[0]) - 1):
      #Verifica se pode deslocar no eixo y
      if(acha_y(matriz, memoria) < len(memoria[0]) - 1):
        #Verifica se o caminho da direita e menor ou igual ao de baixo
        if (sum(busca_global(remove_coluna(deepcopy(matriz)))) <= sum(busca_global(remove_linha(deepcopy(matriz))))):
          #Retorna o caminho da direita caso true
          return [matriz[0][0]] + busca_global(remove_coluna(deepcopy(matriz)))
        else:
          #Retorna o caminho de baixo caso false
          return [matriz[0][0]] + busca_global(remove_linha(deepcopy(matriz)))
      else:
        #Caso y==6 retorna o caminho da direita
        return [matriz[0][0]] + busca_global(remove_coluna(deepcopy(matriz)))
    #Verifica se pode deslocar no eixo y
    elif((acha_y(matriz, memoria) < len(memoria[0]) - 1)):
      #Verifica se pode deslocar no eixo x
      if(acha_x(matriz, memoria) < len(memoria[0]) - 1):
        #Verifica se o caminho de baixo e menor ou igual ao da direita
        if (sum(busca_global(remove_coluna(deepcopy(matriz)))) >= sum(busca_global(remove_linha(deepcopy(matriz))))):
          #Retorna o caminho de baixo caso true
          return [matriz[0][0]] + busca_global(remove_linha(deepcopy(matriz)))
        else:
          #Retorna o caminho da direita caso false
          return [matriz[0][0]] + busca_global(remove_coluna(deepcopy(matriz)))
      else:
        #Caso x==6 retorna o caminho de baixo
        return [matriz[0][0]] + busca_global(remove_linha(deepcopy(matriz)))
    else:
      #Caso seja a extremidade retorna o item(mais a direita e mais a baixo)
      return [matriz[0][0]]
  else:
    #Retorna o item ja calculado na memoria auxiliar
    return memoria[acha_y(matriz, memoria)][acha_x(matriz, memoria)]

def chama_busca(matriz):
  print(sum(busca_global(matriz)))

#Matriz da atividade
c = [[ 1, 5, 7],
     [ 1, 5, 2],
     [ 100, 1, 1]]

#Matriz da atividade
m = [ [ 4, 5, 7, 0, 1, 1,13],
      [ 3, 5, 2, 1, 6, 1, 4],
      [ 1, 3, 9,11, 9, 0, 3],
      [17, 3, 8, 4, 1, 1,14],
      [ 2, 0, 9, 5,11, 0, 4],
      [ 6, 4, 0, 2, 1, 1, 3],
      [ 7,13, 2, 0, 7, 1, 2] ]

#Define o tamanho da memoria -> OBS: se a matriz for x != y, então a memoria recebe o maior valor entre x e y
tamanho_da_matriz = 9

#Cria a memoria
memoria = [[[] for k in range(tamanho_da_matriz)] for k in range(tamanho_da_matriz)]

#Cria a matriz teste
def teste_matrix_x_por_x(dimensao):
  matriz_teste = [[randint(0,10) for k in range(dimensao)] for k in range(dimensao)]
  a = time()
  chama_busca(matriz_teste)
  print(f"Tempo de busca: {time() - a}")

#Chama o teste, para valores diferente alterar tamanho_da_matriz linha 95
#teste_matrix_x_por_x(tamanho_da_matriz)

tamanho_da_matriz = 3
#Cria a memoria
memoria = [[[] for k in range(tamanho_da_matriz)] for k in range(tamanho_da_matriz)]
a = time()
print("Matriz m2")
chama_busca(c)
print(f"Tempo de busca: {time() - a}")

tamanho_da_matriz = 7
#Cria a memoria
memoria = [[[] for k in range(tamanho_da_matriz)] for k in range(tamanho_da_matriz)]
a = time()
print("Matriz m")
chama_busca(m)
print(f"Tempo de busca: {time() - a}")