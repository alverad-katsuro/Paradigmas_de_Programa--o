-- Alfredo Gabriel de Sousa Oliveira - 202004940020
-- https://github.com/alverad-katsuro/Paradigmas_de_Programa--o

-- Trabalho final da disciplina PLP 2021.3
-- Entrega dia 21/02
-- Sugestão - faça um esquema no papel para ajudar o raciocínio
--
-- Observe que o TIPO das funçõe pode ser inferido pelo compilador
-- mas é recomendável sempre especificar o tipo por questão de
-- legibilidade, e para maior consciência do programador no
-- desenvolvimento (veja os exemplos logo abaixo e complete 
-- onde for solicitado)
-- --------------------------------------------------------

-- 1) Aplicação parcial de funções. Considere as duas versões
-- abaixo da função "potencia"/"pot":

--a)
potencia :: (Int,Float) -> Float
potencia (exp, base) =  
    if exp == 0 
    then 1.0 
    else base * potencia (exp-1,base)


pot :: Int -> Float -> Float
pot exp base =  
    if exp == 0 
    then 1.0 
    else base * pot (exp-1) base

-- Explique a diferença entre as duas DECLARAÇÕES DE TIPO das funções
-- Qual a consequência dessas definições em termos de seu uso?

-- Resposta: A primeira função deixa explicito que os parametros de entrada compoem uma tupla, o que impede uma avaliação preguiçosa.
-- Já na segunda função, é declarado como entrada primeiro um inteiro e em seguida um float, de modo que não seja necessário definir
-- os dois ao mesmo tempo, visto que a função tem caracteristicas lazy. A conseguencia dessa definição é a possibilidade de chamar a função
-- em dois momentos, ou seja, supondo que o valor da base dependa de outra função, e o expoente sempre seja 2, é possivel deixar a função
-- esperando com o expoente ja definido enquanto aguarda o calculo da base.

-- explique o significado, e forma de uso, de: 
pot5 = pot 5

-- Resposta: Na declaração acima, foi atribuido o valor do expoente da função pot e armazenado o estado da mesma na variavel pot5
-- para chamar a função, passando o segundo argumento, é necessário chamar no interpretador/programa da seguinte maneira
-- pot5 7 -> sendo 7 uma valor arbitrario qualquer.

-- é possível fazer o mesmo com a função "potencia" ?

-- Resposta: Não é possivel, visto que é necessario passar uma tupla, com dois valores, como parametro.


-- Crie um exemplo de aplicação parcial de função envolvendo
-- uma função aplicFuncLst, que receba como parâmetros uma 
-- função f e uma lista, e aplique f a cada elemento da lista.
-- Na sequência, crie  um exemplo de aplicação parcial


-- aplicFuncLst :: fun -> [Float] -> Float

aplicFuncLst :: (Float -> Float) -> [Float] -> [Float]
aplicFuncLst fun [] = []
aplicFuncLst fun (x:xs) = [fun x] ++ aplicFuncLst fun xs


resultado = aplicFuncLst pot5 [5,1,2,3,4]      


-- 2) Desenvolva uma função que calcule o valor do enésimo elemento 
-- da sequência de Fibonacci     n   0  1  2  3  4  5  6  7
--                           fin n [ 0, 1, 1, 2, 3, 5, 8, 13... ]
-- a) usando if

modulo_fibonacci :: Int -> Int -> Int -> Int -> Int
modulo_fibonacci posicao contador ant atual = if (contador == 0)
                                        then modulo_fibonacci posicao (contador + 1) 0 1
                                        else if (contador == posicao)
                                        then atual + ant 
                                        else modulo_fibonacci posicao (contador + 1) atual (ant + atual)

fibonacci :: Int -> Int                                  
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci x = modulo_fibonacci (x - 1) 0 0 0

-- b) usando pattern matching
-- Teste as funções, calculando o fibonacci de 30, 32, etc.
-- Houve problema de desempenho? Crie uma segunda função,
-- fibonacci, que solucione esse problema. Uma soleção seria
-- criar uma "lista infinita" da sequencia de Fibonacci?
maior :: [Int] -> Int
maior [x] = x
maior (x:xs) = if (x > maior xs) then x
               else maior xs

mod_fibo :: Int -> Int -> [Int] -> [Int]
mod_fibo posicao contador lista = if (contador == 0) then mod_fibo posicao (contador + 2) [0, 1]
                                  else if (contador == posicao) then lista ++ [lista!!(contador - 2) + lista!!(contador - 1)]
                                  else mod_fibo posicao (contador + 1) (lista ++ [lista!!(contador - 2) + lista!!(contador - 1)])

mod_output :: [Int] -> [Int] -> [Int]
mod_output (x:xs) lista = if (xs /= []) then lista!!x:(mod_output xs lista)
                          else [lista!!x]

fibo :: [Int] -> [Int]
fibo [0] = [0]
fibo [1] = [1]
fibo (x:xs) = do
                let maior_da_lista = maior ([x] ++ xs)
                if (maior_da_lista < 2) then mod_output (x:xs) (x:xs)
                else do 
                  let fibo_list = mod_fibo maior_da_lista 0 []
                  mod_output (x:xs) fibo_list
                      

-- 3) Considere as funções abaixo apresentadas em aula  

-- função que testa se x eh primo
-- COMPLETAR: ESPECIFICAR AQUI O TIPO DA FUNÇÃO
ehPrimo :: Int -> Bool
ehPrimo x = null [x' | x' <- [2..x-1], x `rem` x' == 0]

-- função que cria uma lista "infinita" com valores não menores que n
-- ESPECIFICAR AQUI O TIPO DA FUNÇÃO
from :: Int -> [Int]
from n = n : from (n+1)

-- função que acha o primeiro primo na lista
-- ESPECIFICAR AQUI O TIPO DA FUNÇÃO
primPrimo :: [Int] -> Int
primPrimo (n : ns) =
    if ehPrimo n then n else primPrimo ns

-- Desenvolva funções similares para: 
-- a) criar uma lista infinita de pares a partir de certo valor n (par);

filaPar :: Int -> [Int]
filaPar x = [x, x+2..]

-- b) criar a função que forneça o primeiro valor dessa lista que seja
-- múltiplo de 25
-- OBS: especificar os tipos das funções

achaMult :: Int -> [Int] -> [Int]
achaMult valor [] = []
achaMult valor (x:xs) = if (x `mod` valor == 0)
                        then [x]
                        else achaMult valor xs


-- Cite (usando um comentário no próprio código) o conceito de 
-- Haskell que permite a criação de uma lista infinita sem produzir
-- um ciclo infinito de chamadas. Explique esse conceito

-- O conceito e avaliação preguiçosa, nesse conceito o compilador/interpretador não irá processar toda a função, ela ira esperar 
-- alguma solicitação, ou seja, é possivel atribuir o conceito de algo infinito sem computar a expressão que possui um conceito infinito,
-- nesse sentido, ao declararmos x = [1,2..], temos todo o conjunto dos inteiros positivos, contudo o computador não ira calculalos
-- sem ser explicitamente pedido como seria o caso de "print (x)"

-- 4) Considere a função qsort abaixo, que usa como pivô a
-- cabeça da lista (sugestão: teste a mesma no GHC)

qsort :: [Int] -> [Int]
qsort [] = []
qsort (n : ns) =
   qsort [i | i <- ns, i < n]
   ++ [n]
   ++ qsort [i | i <- ns, i >= n]


-- Abaixo exploramos o conceito de função genérica
-- ao invés de usarmos o operador "<" usamos uma
-- função genérica precede  

genericSort :: (t -> t -> Bool) -> [t] -> [t]
genericSort precede =
   let
      sort [] = []
      sort (n : ns) =
         sort [i | i <- ns, i `precede` n]
            ++ [n]
            ++ sort [i | i <- ns, not (i `precede` n)]
   in sort

-- assim, para produzirmos uma função para ordenar inteiros
-- criamos uma instância da função genérica. Nesse caso,
-- o operador "<" tomará o lugar do "precede"

ordenaInt :: [Int] -> [Int]
ordenaInt = genericSort (<)    --  funciona? Sim

-- 4.a)Crie outra instância de genericSort, ordenaRac para ordenar 
-- uma lista de números racionais, isto é, aqueles que são escritos
-- em forma de fração. Por exemplo, a partir da lista
-- [ [1,2], [1,3], [1,5], [9,10], [1,10] ]
-- será retornada a lista ordenada abaixo (de formna ascendente)
-- [[1,10],[1,5],[1,3],[1,2],[9,10]]
-- OBS:  [1,10]  represente 1 décimo (1/10), etc.
--
-- defina a função "menorRac", que define se o primeiro precede
-- (é menor que) o segundo 

resto :: [Int] -> Int
resto [] = 1
resto (x:xs) = x

-- menorRac :: [Int] -> [Int] -> Bool   

menorRac :: [Int] -> [Int] -> Bool
menorRac (x:xs) (y:ys) = do
  let x_1 = (fromIntegral x ::Float) / (fromIntegral (resto xs) :: Float)
  let y_1 = (fromIntegral y ::Float) / (fromIntegral (resto ys) :: Float)
  x_1 < y_1
-- agora criar a função "ordenaRac" como instância de "genericSort"

-- ordenaRac :: [ [Int] ] -> [ [Int] ]

ordenaRac :: [ [Int] ] -> [ [Int] ]
ordenaRac = genericSort (menorRac)

-- 4.b) Agora considere uma lista que guarde as seguintes 
--  informações de n alunos: matrícula (Int), nome (String), 
--  e CRG (Float). Ex:
--  [[3,"Leôncio", 9.3],[9,"Paulina", 9.8],["Bernardo", 8.9] ...]
--
--  - defina a função "precedeAl", que define qual aluno vem
--  antes de acordo com sua matrícula (ord. ascendente). 
--  -- defina a função ordenaAl como instância de "genericSort"
--  para produzir a lista ordenada pela matrícula
--
--  - defina a função "precedeAl2", que define qual aluno vem
--  antes de acordo com seu CRG (ord. ascendente). 
--  Crie a função ordenaAl2 como instância de "genericSort"
--  para produzir a lista ordenada pelo CRG

menorMat :: (Int, String, Float) -> (Int, String, Float) -> Bool
menorMat (mat, nome, crg) (mat_2, nome_2, crg_2) = mat < mat_2

menorCrg :: (Int, String, Float) -> (Int, String, Float) -> Bool
menorCrg (mat, nome, crg) (mat_2, nome_2, crg_2) = crg < crg_2

precedeAl :: [(Int, String, Float)] -> [(Int, String, Float)]
precedeAl = genericSort (menorMat)

precedeAl2 :: [(Int, String, Float)] -> [(Int, String, Float)]
precedeAl2 = genericSort (menorCrg)
