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
        fclose(f);
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

void particao(Aluno *v, int esq, int dir, int *i, int *j){

    Aluno aux;
    *i = esq;
    *j = dir;

    Aluno pivo = v[(*i+*j)/2];

    while(*i <= *j){
        while(v[*i].matricula < pivo.matricula){
            (*i)++;
        }
        while(v[*j].matricula > pivo.matricula){
            (*j)--;
        }
        if(*i <= *j){
            aux = v[*i];
            v[*i] = v[*j];
            v[*j] = aux;
            (*i)++;
            (*j)--;
        }
    }
}

void quickSort(Aluno *v, int esq, int dir){
    int i,j;
    particao(v, esq, dir, &i, &j);

    if(esq < j){
        quickSort(v, esq, j);
    }
    if(dir > i){
        quickSort(v, i, dir);
    }

}



int main(){

    int qtdAlunosCarregados;
    clock_t tempoInicio, tempoFim;
    double tempo_gasto;
    
    qtdAlunosCarregados = carregaAlunos(alunos);
    
    tempoInicio = clock();

    quickSort(alunos, 0, qtdAlunosCarregados - 1);
    
    tempoFim = clock();
    
    tempo_gasto = ((double) (tempoFim - tempoInicio)) / CLOCKS_PER_SEC;
    
    printf("Tempo gasto: %lf s\n", tempo_gasto);
    
    salvaAlunosOrdenados(alunos, qtdAlunosCarregados);

    return 0;
}
