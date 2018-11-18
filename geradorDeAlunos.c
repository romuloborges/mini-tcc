#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIVISOR 11.45 // O divisor serve para gerar o número com casas decimais
#define QUANTIDADE 360000

typedef struct aluno{
    int matricula;
    int cpf;
    int rg;
    char nome[30];
    float n1, n2, n3;
}Aluno;

void geraNome(char *nome){
    int i;
    
    for(i = 0; i < 29; i++){
        nome[i] = 'a' + rand() % 26;
    }
    nome[i] = '\0';
}

float geraNumeroReal(){
    float realAleatorio;
    
    realAleatorio = rand() % 10;
    realAleatorio = realAleatorio + realAleatorio / DIVISOR;
    
    return realAleatorio;
    
}

int main(){
    
    int matriculaAtual = 2017000000;
    int cpf = 160000000;
    int rg = 170000000;
    float numeroAleatorioTemporario = 0;
    
    char nome[30];
    
    FILE *f = fopen("alunos.txt", "w");
    
    if(f != NULL){
        
        srand(time(NULL));
        
        for(int i = 0; i < QUANTIDADE; i++){
            
            geraNome(nome);
            fprintf(f, "%s\n", nome);
            fprintf(f, "%d\n", matriculaAtual++);
            fprintf(f, "%d\n", cpf++);
            fprintf(f, "%d\n", rg++);
            fprintf(f, "%.2f %.2f %.2f\n", geraNumeroReal(), geraNumeroReal(), geraNumeroReal());
            
        }
    }else{
        exit(1);
    }
    
    fclose(f);
    
    f = NULL;
    
    return 0;
}
