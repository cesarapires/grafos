
/*
* Aluno: César Augusto Pires
* Matrícula: 202210116
* Aluno: Gustavo Ribeiro de Figueiredo
* Matrícula: 202210846
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 105; // Número máximo de vértices

vector<pair<int, int>> grafo[MAXN]; // Grafo representado por lista de adjacências
int numVertices, numArestas; // numVertices = X, numArestas = Y

// Função de busca em largura (BFS) para verificar se existe um caminho com capacidade mínima
bool bfs(int origem, int destino, int capacidadeMinima) {
    vector<bool> visitado(MAXN, false); // Vetor para marcar os vértices visitados
    queue<int> fila; // Fila para BFS
    fila.push(origem); // Coloca a origem na fila
    visitado[origem] = true; // Marca a origem como visitada

    while (!fila.empty()) {
        int verticeAtual = fila.front(); fila.pop(); // Pega o próximo vértice da fila
        if (verticeAtual == destino) return true; // Se chegou no destino, retorna true

        // Explora os vizinhos do vértice atual
        for (auto &[vizinho, peso] : grafo[verticeAtual]) {
            if (!visitado[vizinho] && peso >= capacidadeMinima) { // Verifica se o vizinho pode ser visitado e se a capacidade é suficiente
                visitado[vizinho] = true; // Marca o vizinho como visitado
                fila.push(vizinho); // Coloca o vizinho na fila
            }
        }
    }

    return false; // Se não encontrou o destino, retorna false
}

// Função para encontrar a maior capacidade mínima de caminho entre dois vértices
int caminho_com_maior_capacidade(int origem, int destino) {
    int esquerda = 2, direita = 1000000, resultado = 2; // O mínimo de capacidade é 2 (1 passageiro + 1 motorista)
    
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2; // Calcula o ponto médio da capacidade
        if (bfs(origem, destino, meio)) { // Verifica se existe um caminho com a capacidade atual
            resultado = meio; // Se sim, guarda a capacidade atual
            esquerda = meio + 1; // Tenta aumentar a capacidade
        } else {
            direita = meio - 1; // Se não, diminui a capacidade
        }
    }

    return resultado; // Retorna a maior capacidade mínima encontrada
}

int main() {
    while (cin >> numVertices >> numArestas, numVertices || numArestas) { // Lê o número de vértices e arestas
        for (int i = 0; i <= numVertices; ++i) grafo[i].clear(); // Limpa o grafo para cada novo teste

        // Lê as arestas
        for (int i = 0; i < numArestas; ++i) {
            int vertice1, vertice2, peso;
            cin >> vertice1 >> vertice2 >> peso; // Lê a aresta entre vertice1 e vertice2 com o peso
            grafo[vertice1].emplace_back(vertice2, peso); // Adiciona a aresta ao grafo (direcionada)
            grafo[vertice2].emplace_back(vertice1, peso); // Adiciona a aresta ao grafo (grafo não direcionado)
        }

        int origem, destino, numPassageiros;
        cin >> origem >> destino >> numPassageiros; // Lê origem, destino e o número de passageiros

        int capacidadeMinima = caminho_com_maior_capacidade(origem, destino); // Encontra a maior capacidade mínima de caminho entre origem e destino
        int capacidadeUtil = capacidadeMinima - 1; // Capacidade útil (subtrai 1 para o motorista)

        int numeroDeViagens = ceil((double)numPassageiros / capacidadeUtil); // Calcula o número de viagens necessárias
        cout << numeroDeViagens << endl; // Exibe o resultado
    }

    return 0;
}
