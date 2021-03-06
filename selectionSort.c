#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct aluno{
    int matricula;
    int cpf;
    int rg;
    char nome[30];
    float n1, n2, n3;
}Aluno;

static Aluno alunos[360000];

int carregaAlunos(Aluno *alunos){
    int i;
    int limite;
    FILE *f = fopen("alunos360Ordenados.txt", "r");
    
    if(f != NULL){
        fscanf(f, "%d\n", &limite);
        for(i = 0; i < limite; i++){
            fscanf(f, "%s\n", alunos[i].nome);
            setbuf(stdin, NULL);
            fscanf(f, "%d\n", &alunos[i].cpf);
            fscanf(f, "%d\n", &alunos[i].rg);
            fscanf(f, "%d\n", &alunos[i].matricula);
            fscanf(f, "%f %f %f\n", &alunos[i].n1, &alunos[i].n2, &alunos[i].n3);
            setbuf(stdin, NULL);
        }
    }else{
        exit(1);
    }
    return limite;
}

void selectionSort(Aluno *vetor, int quantidade){
    int i, menor, j;
    Aluno aux;
    
    for(i = 0; i < quantidade; i++){
        menor = i;
        for(j = i + 1; j < quantidade; j++){
            if(vetor[j].matricula > vetor[menor].matricula)
                menor = j;
        }
        if(i != menor){
            aux = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = aux;
        }
    }
    
}

void imprimeAlunos(Aluno *alunos, int quantidade){
    int i;
    for(i = 0; i < quantidade; i++){
        printf("Aluno: %s | Matrícula: %d | Notas: %.2f %.2f %.2f\n", alunos[i].nome, alunos[i].matricula, alunos[i].n1, alunos[i].n2, alunos[i].n3);
    }
}

void salvaAlunosOrdenados(Aluno *alunos, int quantidade){
    FILE *f = fopen("alunosOrdenados.txt", "w");
    
    if(f != NULL){
        fprintf(f, "%d\n", quantidade);
        for(int i = 0; i < quantidade; i++){
            fprintf(f, "%s\n", alunos[i].nome);
            fprintf(f, "%d\n", alunos[i].cpf);
            fprintf(f, "%d\n", alunos[i].rg);
            fprintf(f, "%d\n", alunos[i].matricula);
            fprintf(f, "%.2f %.2f %.2f\n", alunos[i].n1, alunos[i].n2, alunos[i].n3);
        }
    }else{
        exit(1);
    }
    
    fclose(f);
}

int main(){
    int qtdAlunosCarregados;
    clock_t tempoInicio, tempoFim;
    double tempo_gasto;
    
    qtdAlunosCarregados = carregaAlunos(alunos);

    tempoInicio = clock();
    
    selectionSort(alunos, qtdAlunosCarregados);
    
    tempoFim = clock();
    
    tempo_gasto = ((double) (tempoFim - tempoInicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo: %lf s\n", tempo_gasto);
    
    salvaAlunosOrdenados(alunos, qtdAlunosCarregados);
    
    return 0;
}
