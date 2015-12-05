## Matematica Discreta - Exercicio 12
Repositorio do exercicio 12 da disciplina de Matematica Discreta da Escola Politecnica de Pernambuco - UPE

#Autores
Hugo de Albuquerque Fonseca <hugoalbuquerque0@gmail.com> <br />
Otacilio Saraiva Maia Neto <otacilio.n97@gmail.com>

#Objetivo
Este exercicio tem como objetivo simular uma rede de Petri com paralelismo e imprimi-la utilizando a biblioteca grafica Allegro.

#Entrada de texto
Para simular a Rede de Petri utilizando este codigo, necessita-se alimenta-lo com um arquivo de entrada. O arquivo nao deve conter nenhum texto, e deve ser formatado _exatamente_ como proposto na tabela abaixo:

Linha          | Descricao
-------------- | --------------------------------------------
1              | Quantidade de Lugares
2              | Quantidade de Transicoes
3              | Quantidade de Lugares com pelo menos um Token
4              | Quantidade de Arcos Lugar -> Transicao
5              | Quantidade de Arcos Transicao -> Lugar
6,...,x        | Descricao Lugar/Token
x+1,...,y      | Descricao do arco Lugar/Quantidade/Transicao
y+1,...,z      | Descricao do arco Transicao/Quantidade/Lugar

Exemplo de input:
```
2
2
1
2
2
0 4
0 1 0
1 2 1
0 1 1
1 1 0
```
Isso gera uma Rede de Petri com o seguinte formato:


![Exemplo](http://puu.sh/lKHeK/0e3d3a6e48.png "Exemplo - Rede de Petri")
(Imagem temporaria!)
