/*
* Aluno: César Augusto Pires
* Matrícula: 202210116
* Aluno: Gustavo Ribeiro de Figueiredo
* Matrícula: 202210846
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int MAX = 210; // 2 * X + origem + destino
const int INF = INT_MAX;

int capacidade[MAX][MAX], fluxo[MAX][MAX];
vector<int> adj[MAX];

int bfs(int origem, int destino, vector<int>& pai) {
    fill(pai.begin(), pai.end(), -1);
    pai[origem] = origem;
    queue<pair<int, int>> fila;
    fila.push({origem, INF});

    while (!fila.empty()) {
        int atual = fila.front().first;
        int fluxo_min = fila.front().second;
        fila.pop();

        for (int vizinho : adj[atual]) {
            if (pai[vizinho] == -1 && capacidade[atual][vizinho] - fluxo[atual][vizinho] > 0) {
                pai[vizinho] = atual;
                int novo_fluxo = min(fluxo_min, capacidade[atual][vizinho] - fluxo[atual][vizinho]);
                if (vizinho == destino)
                    return novo_fluxo;
                fila.push({vizinho, novo_fluxo});
            }
        }
    }

    return 0;
}

int edmonds_karp(int origem, int destino) {
    int total = 0;
    vector<int> pai(MAX);
    int novo_fluxo;

    while ((novo_fluxo = bfs(origem, destino, pai)) > 0) {
        total += novo_fluxo;
        int atual = destino;
        while (atual != origem) {
            int anterior = pai[atual];
            fluxo[anterior][atual] += novo_fluxo;
            fluxo[atual][anterior] -= novo_fluxo;
            atual = anterior;
        }
    }

    return total;
}

int main() {
    while (true) {
        int X;
        cin >> X;
        if (X == -1) break;

        int origem = 0;
        int destino = 2 * X + 1;

        memset(capacidade, 0, sizeof(capacidade));
        memset(fluxo, 0, sizeof(fluxo));
        for (int i = 0; i < MAX; i++) adj[i].clear();

        for (int i = 1; i <= X; i++) {
            int cap;
            cin >> cap;
            int in = i;
            int out = i + X;

            capacidade[in][out] = cap;
            adj[in].push_back(out);
            adj[out].push_back(in);
        }

        int Y;
        cin >> Y;
        for (int i = 0; i < Y; i++) {
            int u, v, p;
            cin >> u >> v >> p;

            int u_out = u + X;
            int v_in = v;

            capacidade[u_out][v_in] += p;
            adj[u_out].push_back(v_in);
            adj[v_in].push_back(u_out);
        }

        int E, S;
        cin >> E >> S;

        for (int i = 0; i < E + S; i++) {
            int u;
            cin >> u;
            if (i < E) {
                // origem → u_in
                capacidade[origem][u] = INF;
                adj[origem].push_back(u);
                adj[u].push_back(origem);
            } else {
                // u_out → destino
                capacidade[u + X][destino] = INF;
                adj[u + X].push_back(destino);
                adj[destino].push_back(u + X);
            }
        }

        cout << edmonds_karp(origem, destino) << "\n";
    }

    return 0;
}
