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

void preencher(int *vetor, int tam){
    for(int i = 0; i < tam; i++){
        scanf("%d", &vetor[i]);
    }
}

void bolha(Aluno *vetor, int tam){
    int j;
    Aluno aux;
    for(int i = tam - 1; i > 0; i--){
        for(j = 0; j < i; j++){
            if(vetor[j].matricula > vetor[j + 1].matricula){
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void bolhaMelhorada(int *vetor, int tam){
    int j, aux;
    int trocou;
    for(int i = tam - 1; i > 0; i--){
        trocou = 0;
        for(j = 0; j < i; j++){
            if(vetor[j] > vetor[j + 1]){
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                trocou = 1;
            }
        }
        if(!trocou){
            break;
        }
    }
}

void imprimeVetor(int *vetor, int tam){
    for(int i = 0; i < tam; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main(int argc, char** argv){
    
    int qtdAlunosCarregados;
    clock_t tempoInicio, tempoFim;
    double tempo_gasto;
    
    qtdAlunosCarregados = carregaAlunos(alunos);
    
    tempoInicio = clock();

    bolha(alunos, qtdAlunosCarregados);
    
    tempoFim = clock();
    
    tempo_gasto = ((double) (tempoFim - tempoInicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo gasto: %lf s\n", tempo_gasto);
    
    salvaAlunosOrdenados(alunos, qtdAlunosCarregados);

    return 0;
}
