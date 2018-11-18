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


void criaHeap(Aluno *vetor, int inicio, int fim){
    Aluno aux = vetor[inicio];
    int j = (inicio * 2) + 1; 
    while(j <= fim){
        if(j < fim){
            if(vetor[j].matricula < vetor[j + 1].matricula){
                j++;
            }
        }
        if(aux.matricula < vetor[j].matricula){ 
            vetor[inicio] = vetor[j]; 
            inicio = j;
            j = 2*inicio + 1;
        }else{
            j = fim + 1;
        }
    }
    vetor[inicio] = aux;
}

void heapSort(Aluno *vetor, int tam){
    int i;
    Aluno aux;
    for(i = ((tam - 1) / 2); i >= 0; i--){
        criaHeap(vetor, i, tam-1);
    }
    for(i = tam - 1; i >= 1; i--){
        aux = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = aux;
        criaHeap(vetor, 0, i - 1);
    }
}

int main(int argc, char** argv) {
    
    int qtdAlunosCarregados;
    clock_t tempoInicio, tempoFim;
    double tempo_gasto;
    
    qtdAlunosCarregados = carregaAlunos(alunos);
    
    tempoInicio = clock();
    
    heapSort(alunos, qtdAlunosCarregados);
    
    tempoFim = clock();
    
    tempo_gasto = ((double) (tempoFim - tempoInicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo gasto: %lf s\n", tempo_gasto);
    
    salvaAlunosOrdenados(alunos, qtdAlunosCarregados);

    return (EXIT_SUCCESS);
}
