#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <locale.h>
#include <stack>

using namespace std;

vector<bool> NUM; // Вектор для хранения информации о посещенных вершинах

void DFS_Matrix_NonRecursive(int start_vertex, const vector < vector < int>>& G) {
	stack<int> s;
	s.push(start_vertex);

	while (!s.empty()) {
		int v = s.top();
		s.pop();

		bool isIsolated = true;
		for (int i = 1; i < G.size(); ++i) {
			if (G[v][i] == 1) {
				isIsolated = false;
				break;
			}
		}
		if (isIsolated) continue; // Пропустить изолированные вершины

		if (!NUM[v]) {
			printf("%d ", v);
			NUM[v] = true;

			for (int i = G.size() - 1; i >= 1; --i) {
				if (G[v][i] == 1 && !NUM[i]) {
					s.push(i);
				}
			}
		}
	}
}

void DFS_Matrix(int v, const vector<vector<int>>& G) {
	bool isIsolated = true;
	for (int i = 1; i < G.size(); ++i) {
		if (G[v][i] == 1) {
			isIsolated = false;
			break;
		}
	}
	if (isIsolated) return;
	NUM[v] = true;
	printf("%d ", v);

	for (int i = 1; i < G.size(); ++i) {
		if (G[v][i] == 1 && !NUM[i]) {
			DFS_Matrix(i, G);
		}
	}
}

void DFS_List(int v, const vector < vector < int>>& adjacency_list) {
	if (adjacency_list[v].empty()) return; // Пропустить изолированные вершины

	NUM[v] = true;
	printf("%d ", v);

	for (const int& neighbor : adjacency_list[v]) {
		if (!NUM[neighbor]) {
			DFS_List(neighbor, adjacency_list);
		}
	}
}

void printList(const vector<vector<int>>& list) {
	printf("Список смежности:\n");
	for (int i = 1; i < list.size(); ++i) {
		printf("%d: ", i);
		for (const int& j : list[i]) {
			printf("%d ", j);
		}
		printf("\n");
	}
}

int swt = 0;

vector<vector<int>> generateAndPrintMatrix(int num_vertices, double edge_probability) {
	vector<vector<int>> adjacency_matrix(num_vertices + 1, vector<int>(num_vertices + 1, 0));
	int cont = 0;
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = i + 1; j <= num_vertices; ++j) {
			if (static_cast<double>(rand()) / RAND_MAX < edge_probability) {
				adjacency_matrix[i][j] = 1;
				adjacency_matrix[j][i] = 1;
				cont ++;
			}
		}
	}

	if (cont == 0) { 
		swt = 1;
	}
	printf("Матрица смежности:\n");
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = 1; j <= num_vertices; ++j) {
			printf("%d ", adjacency_matrix[i][j]);
		}
		printf("\n");
	}
	return adjacency_matrix;
}

vector<vector<int>> matrixToList(const vector<vector<int>>& matrix) {
	int num_vertices = matrix.size() - 1;
	vector<vector<int>> adjacency_list(num_vertices + 1);
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = 1; j <= num_vertices; ++j) {
			if (matrix[i][j] == 1) {
				adjacency_list[i].push_back(j);
			}
		}
	}
	return adjacency_list;
}

int main() {
	setlocale(LC_ALL, "RUS");
	int num_vertices;
	double edge_probability;

	printf("Введите количество вершин в графе: ");
	scanf("%d", &num_vertices);

	printf("Введите вероятность наличия ребра в графе (0 - 1): ");
	scanf("%lf", &edge_probability);

	srand(static_cast<unsigned int>(time(nullptr)));

	auto matrix = generateAndPrintMatrix(num_vertices, edge_probability);
	auto adjacency_list = matrixToList(matrix);
	if (swt == 1){
		printf("\nПервая вершина - изолированная\n");
	}
	else {
		printList(adjacency_list);

		NUM = vector<bool>(num_vertices + 1, false);
		printf("Обход в глубину для матрицы (рекурсивный): ");
		for (int i = 1; i <= num_vertices; ++i) {
			if (!NUM[i]) {
				DFS_Matrix(i, matrix);
			}
		}
		printf("\n");

		NUM = vector<bool>(num_vertices + 1, false);
		printf("Обход в глубину для матрицы (не рекурсивный): ");
		for (int i = 1; i <= num_vertices; ++i) {
			if (!NUM[i]) {
				DFS_Matrix_NonRecursive(i, matrix);
			}
		}
		printf("\n");

		NUM = vector<bool>(num_vertices + 1, false);
		printf("Обход в глубину для списка: ");
		for (int i = 1; i <= num_vertices; ++i) {
			if (!NUM[i]) {
				DFS_List(i, adjacency_list);
			}
		}
		printf("\n");
	}
	return 0;
}


