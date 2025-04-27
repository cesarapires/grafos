#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Cor {BRANCO, CINZA, PRETO};

struct Vertice {
    Cor cor;
    int distancia;
    int pai;
};

void buscaEmLargura(int inicio, const vector<vector<int>>& listaAdjacencia, vector<Vertice>& vertices) {
    int quantidadeVertices = listaAdjacencia.size();
    queue<int> fila;

    vertices[inicio].cor = CINZA;
    vertices[inicio].distancia = 0;
    vertices[inicio].pai = -1;

    fila.push(inicio);

    while (!fila.empty()) {
        int verticeAtual = fila.front();
        fila.pop();

        for (int vizinho : listaAdjacencia[verticeAtual]) {
            if (vertices[vizinho].cor == BRANCO) {
                vertices[vizinho].cor = CINZA;
                vertices[vizinho].distancia = vertices[verticeAtual].distancia + 1;
                vertices[vizinho].pai = verticeAtual;
                fila.push(vizinho);
            }
        }

        vertices[verticeAtual].cor = PRETO;
    }
}

int main() {
    int quantidadeVertices = 6;
    vector<vector<int>> listaAdjacencia(quantidadeVertices);

    listaAdjacencia[0] = {1, 2};
    listaAdjacencia[1] = {0, 3, 4};
    listaAdjacencia[2] = {0, 4};
    listaAdjacencia[3] = {1, 5};
    listaAdjacencia[4] = {1, 2, 5};
    listaAdjacencia[5] = {3, 4};

    vector<Vertice> vertices(quantidadeVertices);

    for (int i = 0; i < quantidadeVertices; i++) {
        vertices[i].cor = BRANCO;
        vertices[i].distancia = -1;
        vertices[i].pai = -1;
    }

    buscaEmLargura(0, listaAdjacencia, vertices);

    for (int i = 0; i < quantidadeVertices; i++) {
        cout << "Vertice: " << i << ", Distancia: " << vertices[i].distancia << ", Pai: ";
        if (vertices[i].pai == -1) {
            cout << "Nulo";
        } else {
            cout << vertices[i].pai;
        }
        cout << endl;
    }

    return 0;
}
