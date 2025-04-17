
#include "utils.h"

void calcular_notas(Aluno *aluno) {
    if (aluno->num_avaliacoes < 2) {
        aluno->nf = 0;
        aluno->status = 0;
        return;
    }

    float media_ap1 = (aluno->avaliacoes[0].ap1 + aluno->avaliacoes[0].ap2 + aluno->avaliacoes[0].ap3) / 3.0;
    float media_ap2 = (aluno->avaliacoes[1].ap1 + aluno->avaliacoes[1].ap2 + aluno->avaliacoes[1].ap3) / 3.0;

    float media1 = media_ap1 * 0.4 + aluno->avaliacoes[0].np * 0.6;
    float media2 = media_ap2 * 0.4 + aluno->avaliacoes[1].np * 0.6;

    aluno->nf = (media1 + media2) / 2.0;
    aluno->status = aluno->nf >= 6.0 ? 1 : 0;
}

Aluno* realocar_memoria_aluno(Aluno *alunos, int novo_tamanho) {
    return (Aluno*) realloc(alunos, novo_tamanho * sizeof(Aluno));
}

Avaliacao* realocar_memoria_avaliacao(Avaliacao *avaliacoes, int novo_tamanho) {
    return (Avaliacao*) realloc(avaliacoes, novo_tamanho * sizeof(Avaliacao));
}

void liberar_memoria(Aluno *alunos, int num_alunos) {
    for (int i = 0; i < num_alunos; i++) {
        free(alunos[i].avaliacoes);
    }
    free(alunos);
}

void adicionar_avaliacoes(Aluno *aluno, Avaliacao avaliacao) {
    aluno->avaliacoes = realocar_memoria_avaliacao(aluno->avaliacoes, aluno->num_avaliacoes + 1);
    if (aluno->avaliacoes != NULL) {
        aluno->avaliacoes[aluno->num_avaliacoes] = avaliacao;
        aluno->num_avaliacoes++;
    }
}

Aluno *carregar_alunos(const char *nome_arquivo, int *num_alunos) {
    printf("Abrindo arquivo: %s\n", nome_arquivo);
    FILE *arquivo = fopen(nome_arquivo, "r"); 
    if (!arquivo) { 
        perror("Erro ao abrir arquivo de alunos");
        return NULL;
    }

    Aluno *alunos = NULL;
    char linha[256];
    fgets(linha, sizeof(linha), arquivo);
    printf("Cabeçalho: %s\n", linha);

    while (fgets(linha, sizeof(linha), arquivo)) {
        Aluno novo_aluno;
        Avaliacao avaliacao1;
        Avaliacao avaliacao2;
        if (sscanf(linha, "%d,%[^,],%f,%f,%f,%f,%f,%f,%f,%f",
                   &novo_aluno.matricula, novo_aluno.nome,
                   &avaliacao1.ap1, &avaliacao1.ap2, &avaliacao1.ap3, &avaliacao1.np,
                   &avaliacao2.ap1, &avaliacao2.ap2, &avaliacao2.ap3, &avaliacao2.np) == 10) {

            alunos = realocar_memoria_aluno(alunos, (*num_alunos + 1));
            if (!alunos) {
                perror("Erro ao alocar memória para alunos");
                fclose(arquivo);
                return NULL;
            }

            novo_aluno.avaliacoes = NULL;
            novo_aluno.num_avaliacoes = 0;

            adicionar_avaliacoes(&novo_aluno, avaliacao1);
            adicionar_avaliacoes(&novo_aluno, avaliacao2);

            calcular_notas(&novo_aluno);

            alunos[*num_alunos] = novo_aluno;
            printf("Aluno lido: %%s | Matricula: %%d\n", novo_aluno.nome, novo_aluno.matricula);
            (*num_alunos)++;

        } else {
            fprintf(stderr, "Erro ao ler linha do arquivo de alunos: %s", linha);
        }
    }

    fclose(arquivo);
    return alunos;
}

void ordenar_alunos(Aluno *alunos, int num_alunos) {
    for (int i = 0; i < num_alunos - 1; i++) {
        for (int j = 0; j < num_alunos - i - 1; j++) {
            if (alunos[j].nf < alunos[j + 1].nf) {
                Aluno temp = alunos[j];
                alunos[j] = alunos[j + 1];
                alunos[j + 1] = temp;
            }
        }
    }
}

void listar_alunos(const Aluno *alunos, int num_alunos) {
    if (num_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("\n");
    printf("%-10s | %-30s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-8s | %-10s\n",
           " Matrícula", "Nome", "AV1:AP1", "AV1:AP2", "AV1:AP3", "NP1", "AV2:AP1", "AV2:AP2", "AV2:AP3", "NP2", "NF", "Status");
    printf("-----------|--------------------------------|----------|----------|----------|----------|----------|----------|----------|----------|----------|------------\n");

    for (int i = 0; i < num_alunos; i++) {
        if (alunos[i].status == 0) {
            printf(RED_TEXT);
        }
        printf("%-10d | %-30s | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-8.2f | %-10s",
                alunos[i].matricula,
                alunos[i].nome,
                alunos[i].avaliacoes[0].ap1,
                alunos[i].avaliacoes[0].ap2,
                alunos[i].avaliacoes[0].ap3,
                alunos[i].avaliacoes[0].np,
                alunos[i].avaliacoes[1].ap1,
                alunos[i].avaliacoes[1].ap2,
                alunos[i].avaliacoes[1].ap3,
                alunos[i].avaliacoes[1].np,
                alunos[i].nf,
                alunos[i].status == 1 ? "Aprovado" : "Reprovado");
        if (alunos[i].status == 0) {
            printf(RESET_TEXT);
        }
        printf("\n");
    }
    printf("\n");
}
