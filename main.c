#include "utils.h"


int main(int argc, char *argv[]) {

    // Verifica se o número correto de argumentos foi passado
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <notas.csv>\n", argv[0]);
        return 1;
    }

    // Nome do arquivo CSV passado como argumento
    const char *nome_arquivo_alunos = argv[1];

    // Carrega os alunos do arquivo CSV
    int num_alunos = 0;
    Aluno *alunos = carregar_alunos(nome_arquivo_alunos, &num_alunos);
    if (!alunos) {
        return 1;
    }

    // Ordena os alunos por nota final (NF) e lista os alunos
    ordenar_alunos(alunos, num_alunos);
    listar_alunos(alunos, num_alunos);

    /* 
        ATENÇÃO: Essa função deve ser implementada
    */    
    // Libera a memória alocada para os alunos
    liberar_memoria(alunos, num_alunos);
    return 0;
}
