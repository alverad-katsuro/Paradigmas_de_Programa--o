-- Alfredo Gabriel de Sousa Oliveira - 202004940020
-- https://github.com/alverad-katsuro/Paradigmas_de_Programa--o

-- Este primeiro exercício tem por objetivo que cada um(a)
-- instale o GHC - ambiente interativo e o compilador - na 
-- plataforma empregada (Windows, Linux...)
-- e execute funções simples (algumas para serem completadas)
-- entrega dia 09/02 
-- sugestão - faça um esquema no papel para ajudar o raciocínio
-- --------------------------------------------------------


-- Retornar o menor elemento de uma lista 
--                     cabeça     cauda
-- [3,5,7,1,9,0,4,3]     3     [5,7,11,9,10,4,32] 

menor [x] = x
menor (x:xs) = if (x < menor xs)   
               then x
               else menor xs
              
-- Remover elemento n de uma lista 

remover n (x:xs) = if (n == x)
                   then xs
                   else  [x] ++ (remover n xs)     

-- ordenacao por selecao
-- obs lazy avaluation
ordena [] = []
ordena ns = [menor ns] ++ ordena (remover (menor ns) ns)
            
-- ver a alternativa abaixo para a mesma função            
-- observar o recurso "where" abaixo que pode tornar algumas 
-- expressões mais compactas e portanto mais legíveis
 
ordena2 [] = []
ordena2 ns = [menor ns] ++ ordena2 ys
            where
              ys = remover (menor ns) ns
              
          
-- observar as duas alternativas para cálculo do fatorial

fat n = if (n == 0)
        then 1
        else n * fat (n-1)

-- a segunda alternativa usa o princípio de casamento 
-- de padrões (pattern matching)
fatorial 0 = 1
fatorial n = n * fatorial (n-1)


-- completar (função para inverter a ordem dos elementos de uma lista
inverter [] = []
inverter (x:xs) = if xs == []
                  then [x]
                  else inverter xs ++ [x]


-- completar: função para inserir um elemento na k-ésima 
-- posição de uma lista (supor que na lista há o número mínimo de
-- elementos para tornar a inserção possível)

inserir n 0 ls = n:ls   -- se a posição é 0 inserir n na cabeça da lista
inserir n k (x:xs) = if (k == 0)
                          then [n] ++ [x] ++ xs
                          else [x] ++ inserir n (k - 1) xs 

-- completar: função para inserir o elemento n na última 
-- posição da lista ls 

inserirfim n [] = [n]
inserirfim n (l:ls) = [l] ++ ls ++ [n]

-- completar, para a mesma função, a versão com "where"
insfim n [] = [n]
insfim n (l:ls) = l:ys 
                    where
                       ys = (ls ++ [n])


