/*
* Aluno: César Augusto Pires
* Matrícula: 202210116
* Aluno: Gustavo Ribeiro de Figueiredo
* Matrícula: 202210846
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Aresta {
    int destino;
    int pedagio;
};

vector<vector<Aresta>> lerGrafo(int ligacoes, int& maiorPedagio) {
    int intersecoes, origem, destino, custoMaximo;
    cin >> intersecoes >> ligacoes >> origem >> destino >> custoMaximo;
    origem--; destino--;

    vector<vector<Aresta>> grafo(intersecoes);
    maiorPedagio = 0;

    for (int i = 0; i < ligacoes; ++i) {
        int de, para, custo;
        cin >> de >> para >> custo;
        de--; para--;
        grafo[de].push_back({para, custo});
        maiorPedagio = max(maiorPedagio, custo);
    }

    return grafo;
}

bool dijkstraComRestricao(const vector<vector<Aresta>>& grafo, int origem, int destino, int custoMaximo, int limitePedagio) {
    int n = grafo.size();
    vector<vector<long long>> distancia(n, vector<long long>(2, LLONG_MAX));
    distancia[origem][0] = 0;

    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> fila;
    fila.push({0, origem, 0});

    while (!fila.empty()) {
        auto [custoAtual, u, usouPedagioAlto] = fila.top();
        fila.pop();

        if (custoAtual > distancia[u][usouPedagioAlto]) continue;

        for (const auto& aresta : grafo[u]) {
            int v = aresta.destino;
            int w = aresta.pedagio;
            int novoEstado = usouPedagioAlto;

            if (w >= limitePedagio) novoEstado = 1;

            long long novoCusto = custoAtual + w;
            if (novoCusto < distancia[v][novoEstado]) {
                distancia[v][novoEstado] = novoCusto;
                fila.push({novoCusto, v, novoEstado});
            }
        }
    }

    return distancia[destino][1] <= custoMaximo;
}

int encontrarMaiorPedagioMinimo(const vector<vector<Aresta>>& grafo, int origem, int destino, int custoMaximo, int maiorPedagio) {
    int esquerda = 1, direita = maiorPedagio, resposta = -1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;

        if (dijkstraComRestricao(grafo, origem, destino, custoMaximo, meio)) {
            resposta = meio;
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return resposta;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int casosDeTeste;
    cin >> casosDeTeste;

    while (casosDeTeste--) {
        int intersecoes, ligacoes, origem, destino, custoMaximo;
        cin >> intersecoes >> ligacoes >> origem >> destino >> custoMaximo;
        origem--; destino--;

        int maiorPedagio = 0;
        vector<vector<Aresta>> grafo(intersecoes);

        for (int i = 0; i < ligacoes; ++i) {
            int de, para, custo;
            cin >> de >> para >> custo;
            de--; para--;
            grafo[de].push_back({para, custo});
            maiorPedagio = max(maiorPedagio, custo);
        }

        int resposta = encontrarMaiorPedagioMinimo(grafo, origem, destino, custoMaximo, maiorPedagio);
        cout << resposta << '\n';
    }

    return 0;
}