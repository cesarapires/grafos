### Problema

Um supermercado, localizado na cidade de Drummondville (Québec, Canadá), iniciou suas atividades recentemente e tem se destacado pela preocupação com o bem-estar de seus empregados. A empresa pretende comprar um ônibus para o transporte dos funcionários. Por ser uma cidade de pequeno porte, todas as ruas de Drummondville são de mão-dupla.  O supermercado, desejando reduzir os custos, quer saber qual é o número mínimo de viagens que um motorista deve fazer para sair de um ponto A, levar os funcionários para um ponto B, considerando um total de C funcionários a serem transportados. Existe uma capacidade máxima permitida para o transporte de passageiros em cada rua de Drummonville. Essa última restrição é uma exigência recente da prefeitura, para preservar a arquitetura histórica da cidade e conservar mais as vias de circulação.

Como exemplo, suponha que as ruas, com as suas devidas intersecções e limite máximo de passageiros, sejam apresentadas abaixo:

(1,2): máximo de 30 pessoas;(1,3): máximo de 20 pessoas;(1,4): máximo de 10 pessoas;(2,4): máximo de 40 pessoas;(2,5): máximo de 80 pessoas;(3,4): máximo de 13 pessoas;(3,6): máximo de 13 pessoas;(4,7): máximo de 25 pessoas;(5,7): máximo de 12 pessoas;(6,7): máximo de 35 pessoas.

Considerando A = 1, B = 7 e C = 97, então o supermercado gastaria pelo menos 5 viagens para levar todos os seus funcionários ao destino, levando em conta uma aquisição de um ônibus que carregue até 25 pessoas.

### Entrada

A entrada do problema pode conter um ou mais casos de teste. Para cada caso de teste, a primeira linha contém dois inteiros: o número de intersecções da cidade, X, e o número de ruas da cidade, denotada por Y. As próximas Y linhas contém, cada uma, três inteiros: u, v e p, correspondendo à intersecção u que liga à intersecção v, com limite máximo de pessoas dentro de um veículo de transporte dado por p. Na linha subsequente, considera-se os valores de A, B e C, respectivamente. O fim de todos os casos de teste é dado pela sequência de dois zeros.

### Saída

Para cada caso de teste, imprima o número mínimo de viagens necessárias para transportar os funcionários do supermercaso.
