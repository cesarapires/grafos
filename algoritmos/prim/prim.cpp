#include <iostream>
#include <vector>
#include <queue>
#include <climits> // Adicionado para usar INT_MAX


using namespace std;

struct Aresta {
    int destino;
    int peso;
};

struct Comparador {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second; // menor peso primeiro
    }
};

void prim(int inicio, const vector<vector<Aresta>>& listaAdjacencia) {
    int quantidadeVertices = listaAdjacencia.size();
    vector<bool> visitado(quantidadeVertices, false);
    vector<int> custo(quantidadeVertices, INT_MAX);
    vector<int> pai(quantidadeVertices, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, Comparador> filaPrioridade;

    custo[inicio] = 0;
    filaPrioridade.push({inicio, 0});

    while (!filaPrioridade.empty()) {
        int verticeAtual = filaPrioridade.top().first;
        filaPrioridade.pop();

        if (visitado[verticeAtual]) continue;
        visitado[verticeAtual] = true;

        for (const Aresta& vizinho : listaAdjacencia[verticeAtual]) {
            if (!visitado[vizinho.destino] && vizinho.peso < custo[vizinho.destino]) {
                custo[vizinho.destino] = vizinho.peso;
                pai[vizinho.destino] = verticeAtual;
                filaPrioridade.push({vizinho.destino, custo[vizinho.destino]});
            }
        }
    }

    int pesoTotal = 0;
    cout << "Arestas da Árvore Geradora Minima:\n";
    for (int i = 0; i < quantidadeVertices; i++) {
        if (pai[i] != -1) {
            cout << pai[i] << " - " << i << " (peso " << custo[i] << ")\n";
            pesoTotal += custo[i];
        }
    }
    cout << "Peso total da AGM: " << pesoTotal << endl;
}

int main() {
    int quantidadeVertices = 5;
    vector<vector<Aresta>> listaAdjacencia(quantidadeVertices);

    listaAdjacencia[0].push_back({1, 2});
    listaAdjacencia[0].push_back({3, 6});
    listaAdjacencia[1].push_back({0, 2});
    listaAdjacencia[1].push_back({2, 3});
    listaAdjacencia[1].push_back({3, 8});
    listaAdjacencia[1].push_back({4, 5});
    listaAdjacencia[2].push_back({1, 3});
    listaAdjacencia[2].push_back({4, 7});
    listaAdjacencia[3].push_back({0, 6});
    listaAdjacencia[3].push_back({1, 8});
    listaAdjacencia[3].push_back({4, 9});
    listaAdjacencia[4].push_back({1, 5});
    listaAdjacencia[4].push_back({2, 7});
    listaAdjacencia[4].push_back({3, 9});

    prim(0, listaAdjacencia);

    return 0;
}
