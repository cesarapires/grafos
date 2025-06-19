/*
* Aluno: César Augusto Pires
* Matrícula: 202210116
* Aluno: Gustavo Ribeiro de Figueiredo
* Matrícula: 202210846
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

const int MAX_CASAS = 100005;

vector<int> vizinhos[MAX_CASAS];
string presente_em_casa[MAX_CASAS];
int pai[MAX_CASAS];
int profundidade[MAX_CASAS];

void dfs(int casa_atual, int casa_pai, int nivel) {
    pai[casa_atual] = casa_pai;
    profundidade[casa_atual] = nivel;

    for (int vizinho : vizinhos[casa_atual]) {
        if (vizinho != casa_pai) {
            dfs(vizinho, casa_atual, nivel + 1);
        }
    }
}

int contar_presentes_distintos(int casa_a, int casa_b) {
    unordered_set<string> presentes;

    // Subimos até igualar as profundidades
    while (profundidade[casa_a] > profundidade[casa_b]) {
        presentes.insert(presente_em_casa[casa_a]);
        casa_a = pai[casa_a];
    }

    while (profundidade[casa_b] > profundidade[casa_a]) {
        presentes.insert(presente_em_casa[casa_b]);
        casa_b = pai[casa_b];
    }

    // Subimos juntos até encontrar ancestral comum
    while (casa_a != casa_b) {
        presentes.insert(presente_em_casa[casa_a]);
        presentes.insert(presente_em_casa[casa_b]);
        casa_a = pai[casa_a];
        casa_b = pai[casa_b];
    }

    // Inserir o presente da casa ancestral comum
    presentes.insert(presente_em_casa[casa_a]);

    return presentes.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int total_casas, total_perguntas;
    cin >> total_casas >> total_perguntas;

    for (int i = 1; i <= total_casas; ++i) {
        cin >> presente_em_casa[i];
    }

    for (int i = 0; i < total_casas - 1; ++i) {
        int casa1, casa2;
        cin >> casa1 >> casa2;
        vizinhos[casa1].push_back(casa2);
        vizinhos[casa2].push_back(casa1);
    }

    dfs(1, 0, 0); // Começamos da casa 1 como raiz

    for (int i = 0; i < total_perguntas; ++i) {
        int casa_a, casa_b;
        cin >> casa_a >> casa_b;
        cout << contar_presentes_distintos(casa_a, casa_b) << "\n";
    }

    return 0;
}
