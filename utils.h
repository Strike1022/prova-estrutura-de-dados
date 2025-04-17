#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de cores ANSI (suportado em alguns terminais)
#define RED_TEXT "\033[31m"
#define RESET_TEXT "\033[0m"

#define MAX_NOME 50

// Estruturas de dados
// Estrutura para armazenar as notas de cada avaliação
typedef struct {
    float ap1;  // Nota da primeira atividade prática
    float ap2;  // Nota da segunda atividade prática
    float ap3;  // Nota da terceira atividade prática
    float np;   // Nota da prova
} Avaliacao;

typedef struct {
    int matricula;          // Matrícula do aluno
    char nome[MAX_NOME];    // Nome do aluno
    Avaliacao *avaliacoes;  // Ponteiro para o array de avaliações
    int num_avaliacoes;     // Número de avaliações
    float nf;               // Nota final
    int status;             // 0: Reprovado, 1: Aprovado
} Aluno;


// Protótipos das funções em utils.c
Aluno *carregar_alunos(const char *nome_arquivo, int *num_alunos);
Aluno *realocar_memoria_aluno(Aluno *alunos, int novo_tamanho);
Avaliacao* realocar_memoria_avaliacao(Avaliacao *avaliacoes, int novo_tamanho);
void adicionar_avaliacoes(Aluno *aluno, Avaliacao avaliacao);
void ordenar_alunos(Aluno *alunos, int num_alunos);
void listar_alunos(const Aluno *alunos, int num_alunos);
void liberar_memoria(Aluno *alunos, int num_alunos);
void calcular_notas(Aluno *aluno);

#endif
