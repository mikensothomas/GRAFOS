#include <stdio.h>
#include <stdlib.h>

typedef struct Grafo {
    int num_cidades;         // Número total de cidades
    int **matriz_adjacencia; // Matriz de adjacência para conexões
} Grafo;

// Função para criar o grafo
Grafo* criar_grafo(int num_cidades) {
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    g->num_cidades = num_cidades;

    g->matriz_adjacencia = (int **)malloc(num_cidades * sizeof(int *));
    for (int i = 0; i < num_cidades; i++) {
        g->matriz_adjacencia[i] = (int *)calloc(num_cidades, sizeof(int));
    }

    return g;
}

// Função para inserir conexão
void inserir_conexao(Grafo *g, int origem, int destino) {
    if (origem >= 0 && origem < g->num_cidades && destino >= 0 && destino < g->num_cidades) {
        g->matriz_adjacencia[origem][destino] = 1;
    } else {
        printf("Cidades invalidas.\n");
    }
}

// Função para remover conexão
void remover_conexao(Grafo *g, int origem, int destino) {
    if (origem >= 0 && origem < g->num_cidades && destino >= 0 && destino < g->num_cidades) {
        g->matriz_adjacencia[origem][destino] = 0; // Remove a conexão
    } else {
        printf("Cidades invalidas.\n");
    }
}

// Função para buscar conexões
void buscar_conexoes(Grafo *g, int cidade) {
    if (cidade >= 0 && cidade < g->num_cidades) {
        printf("Conexoes partindo da cidade %d:\n", cidade);
        for (int i = 0; i < g->num_cidades; i++) {
            if (g->matriz_adjacencia[cidade][i] == 1) {
                printf(" - Para a cidade %d\n", i);
            }
        }
    } else {
        printf("Cidade invalida.\n");
    }
}

// Função para imprimir o grafo
void imprimir_grafo(Grafo *g) {
    printf("Matriz de Adjacencia:\n");
    for (int i = 0; i < g->num_cidades; i++) {
        for (int j = 0; j < g->num_cidades; j++) {
            printf("%d ", g->matriz_adjacencia[i][j]);
        }
        printf("\n");
    }
}

// Função para liberar a memória do grafo
void liberar_grafo(Grafo *g) {
    for (int i = 0; i < g->num_cidades; i++) {
        free(g->matriz_adjacencia[i]);
    }
    free(g->matriz_adjacencia);
    free(g);
}

// Função para exportar o grafo para um arquivo DOT
void exportar_para_dot(Grafo *g, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "digraph G {\n");
    for (int i = 0; i < g->num_cidades; i++) {
        for (int j = 0; j < g->num_cidades; j++) {
            if (g->matriz_adjacencia[i][j] == 1) {
                fprintf(file, "  %d -> %d;\n", i, j);
            }
        }
    }
    fprintf(file, "}\n");

    fclose(file);
    printf("Exportado para o arquivo %s\n", filename);
}

int main() {
    int num_cidades, opcao, origem, destino;
    printf("Digite o numero de cidades: ");
    scanf("%d", &num_cidades);

    Grafo *g = criar_grafo(num_cidades);

    do {
        printf("\nMenu:\n");
        printf("1. Inserir conexao\n");
        printf("2. Remover conexao\n");
        printf("3. Buscar conexoes\n");
        printf("4. Imprimir grafo\n");
        printf("5. Exportar para DOT\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a cidade de origem e destino: ");
                scanf("%d %d", &origem, &destino);
                inserir_conexao(g, origem, destino);
                break;
            case 2:
                printf("Digite a cidade de origem e destino: ");
                scanf("%d %d", &origem, &destino);
                remover_conexao(g, origem, destino);
                break;
            case 3:
                printf("Digite a cidade para buscar conexoes: ");
                scanf("%d", &origem);
                buscar_conexoes(g, origem);
                break;
            case 4:
                imprimir_grafo(g);
                break;
            case 5:
                exportar_para_dot(g, "grafo.dot");
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida.\n");
        }
    } while (opcao != 6);

    liberar_grafo(g);
    return 0;
}