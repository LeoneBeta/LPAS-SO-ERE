/*Exercício de Sistemas Operacionais: Criar um interpretador LPAS (Linguagem de Programação para Aritmética
Simpes), fornecendo a opção para o usuário criar um programa, possuindo algumas linhas de comandos, assim o 
interpretador o executa, dando também opção para edição do programa, e a sua visualiação.

Este interpretador está limitado á 30 comandos por programa, com um total de 5 programas.
Feito com Linguagem C.

Aluno: Leone Furtado Siqueira */

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#define MAX 30 

//Struct do programa
typedef struct{
    char linhaProg[MAX][17];
}TPrograma;

//Struct para armazenamento caso o usuário forneca uma letra.
typedef struct{
    char letra[1];
    int valor;
}TElemento;

//Limitando o número de programas podendo ser criados a 5.
TPrograma prog[5];

//Verifica se a string fornecida está vazia, sendo sinal de que chegou ao fim do programa
int verificaString(char string[]){
    char str[1] = "\n";
    if(strcmp(string,str))
        return 1;   //chegou no fim do programa
    return 0;       //mais um comando inserido
}

//Retira o \n ao final da string
void retiraEnter(char string[]){
	int tamanho = strlen(string) - 1;
	if (string[tamanho] == '\n') {
		string[tamanho] = '\0';
	}else {
		while (getc(stdin) != '\n')
			continue;
	}
}

/*Essa função faz a leitura de uma linha do programa, assim coletando a instrução nela contido,
também faz a leitura do valor fornecido para determinado comando, ou até mesmo se foi fornecido uma letra*/
void identificaInstrucao(char comando[], char instrucao[], int *n, TElemento **e, int pos, int *valid, char letra[1]){
    int i = 0,j = 0;
    char valorString[5], READ[4] = "READ";

    //Copia o comando o separando da linha
    do{
        instrucao[i] = comando[i];
        i++;
    }while(comando[i] != ' ');
    i++;

    /*Verifica se o caractere a frente do comando é um número, se sim, ele transforma esse número do tipo char
    em um tipo int*/
    if(comando[i] == '0' || comando[i] == '1' || comando[i] == '2' || comando[i] == '3' || comando[i] == '4' ||
    comando[i] == '5' || comando[i] == '6' || comando[i] == '7' || comando[i] == '8' || comando[i] == '9'){
        do{
            valorString[j] = comando[i];
            i++;
            j++;
        }while(comando[i] != '\0');
        *n = atoi(valorString);
        *valid = 0;
    }
    /*Caso o caractere a frente do comando for uma letra, ele armazena essa letra para uso futuro*/
    else{
        if(strncmp(instrucao,READ,4) == 0){
            e[pos-1]->letra[0] = comando[i];
            letra[0] = comando[i];
        }else
            letra[0] = comando[i];
        *valid = 1;
    }
}

//Verifica a instrução da linha atual e a executa
void executaInstrucao(char instrucao[], int *registrador, int *n, TElemento **e, int pos, int *valid, char letra[1]){
    char LOAD[4] = "LOAD",STORE[5] = "STORE",ADD[4] = "ADD",
         SUB[4] = "SUB",MUL[4] = "MUL",DIV[4] = "DIV" ,
         READ[4] = "READ",WRITE[5] = "WRITE",HALT[4] = "HALT";
         int i;

    /*Uma sequência de IFs verifica qual o comando da instrução, assim o executando, essa sequência é feita
    para que caso o programa encontre a instrução, o mesmo não faz verificações desnecessárias.*/
    if(strncmp(instrucao,READ,4) == 0){
        scanf("%d",&e[pos-1]->valor);
        *n = e[pos-1]->valor;
        pos++;
    }else{
        if(strncmp(instrucao,LOAD,4) == 0){
            //Utilizando uma variável de controle para identificação do comando, sendo um Número, ou uma Letra
            if(*valid == 0){
                *registrador = *n;
            }else{
                for(i=0;i<pos;i++){                    //Caso for uma Letra, o programa percorre o vetor onde
                    if(e[i]->letra[0] == letra[0]){    //está armazenados tais valores em busca da letra fornecida
                        *registrador = e[i]->valor;    //assim utilizando seu valor
                        break;
                    }
                }
            }
        }else{     
            if(strcmp(instrucao,STORE) == 0){
                *n = (*registrador);
            }else{
                if(strncmp(instrucao,ADD,3) == 0){
                    if(*valid == 0)
                        *registrador = *registrador + *n;
                    else{
                        for(i=0;i<pos;i++){
                            if(e[i]->letra[0] == letra[0]){
                                *registrador = *registrador + e[i]->valor;
                                break;
                            }
                        }
                    }
                }else{
                    if(strncmp(instrucao,SUB,3) == 0){
                        if(*valid == 0)
                            *registrador = *registrador - *n;
                        else{
                            for(i=0;i<pos;i++){
                                if(e[i]->letra[0] == letra[0]){
                                    *registrador = *registrador - e[i]->valor;
                                    break;
                                }
                            }
                        }
                    }else{
                        if(strncmp(instrucao,MUL,3) == 0){
                            if(*valid == 0)
                                *registrador = (*registrador) * (*n);
                            else{
                                for(i=0;i<pos;i++){
                                    if(e[i]->letra[0] == letra[0]){
                                        *registrador = (*registrador) * (e[i]->valor);
                                        break;
                                    }
                                }
                            }
                        }else{
                            if(strncmp(instrucao,DIV,3) == 0){
                                if(*valid == 0)
                                    *registrador = (*registrador) / (*n);
                                else{
                                    for(i=0;i<pos;i++){
                                        if(e[i]->letra[0] == letra[0]){
                                            *registrador = (*registrador) / (e[i]->valor);
                                            break;
                                        }
                                    }
                                }
                            }else{
                                if(strncmp(instrucao,WRITE,5) == 0){
                                    if(*valid == 0)
                                        printf("%d",*n);
                                    else{
                                        for(i=0;i<pos;i++){
                                            if(e[i]->letra[0] == letra[0]){
                                                printf("%d",e[i]->valor);
                                                break;
                                            }
                                        }
                                    }    
                                }//WRITE
                            }//DIV
                        }//MULL
                    }//SUB
                }//ADD
            }//STORE
        }//LOAD
    }//READ
}

int interpretador(){
    int i,j,menu,linha,sair,idProg;
    char str[1] = "\n",instrucao[6], letra[1];
    int *pRegist, *pValid, *pN, n, tam = 1, valid, registrador;
    char HALT[4] = "HALT";
    TElemento *e;

    //Quantidade de letras fornecidas no lugar de valores é dinamico, podendo fornecer inúmeras letras.
    e = (TElemento*)malloc(tam*sizeof(TElemento));

    pRegist = &registrador;
    pValid = &valid;
    pN = &n;

    //Menu do programa
    do{
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\nMáquina de Execução LPAS");
        printf("\n1. Editar Programa");
        printf("\n2. Exibir Programa");
        printf("\n3. Executar Programa");
        printf("\n4. Sair\n");
        printf("\nEscolha: ");
        scanf("%d",&menu);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        switch(menu){
        case 1:
            system("clear");
            printf("\nID do programa:  1 a 5 - ");
            scanf("%d",&idProg);
            i = 0;
            //Verificar se o programa pedido esta em branco, se sim, começar um do zero, se não, printar o
            //programa desejado e pedir a linha para edição
            if(strlen(prog[idProg-1].linhaProg[i]) < 1){   //Faz um programa do zero
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nForneça os comandos");
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\nPressione Enter numa linha vazia para finalizar\n");
                i=0;
                do{
                    setbuf(stdin,NULL);
                    fgets(prog[idProg-1].linhaProg[i],17,stdin);
                    if(!verificaString(prog[idProg-1].linhaProg[i]))
                        break;
                    else{
                        retiraEnter(prog[idProg-1].linhaProg[i]);
                        i++;
                    }
                }while(i<MAX);
            }else{                                  //Printa o programa para edição
                for(i=0;i<MAX;i++){
                    if(strlen(prog[idProg-1].linhaProg[i])< 1)
                        break;
                    printf("\n%d. %s",i+1,prog[idProg-1].linhaProg[i]);
                }
                i=0;
                do{
                    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~");
                    printf("\nID da linha: ");
                    scanf("%d",&linha);
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~");
                    setbuf(stdin,NULL);
                    printf("\nNovo Comando: \n");
                    setbuf(stdin,NULL);
                    printf("%d. ",linha);
                    fgets(prog[idProg-1].linhaProg[linha-1],17,stdin);
                    if(!verificaString(prog[idProg-1].linhaProg[linha-1]))
                        break;
                    else{
                        retiraEnter(prog[idProg-1].linhaProg[linha-1]);
                        i++;
                    }
                    printf("\nDeseja editar mais uma linha?");
                    printf("\n0. Sim ... 1. Não\n");
                    scanf("%d",&sair);
                }while(sair!=1);
            }  
            break;
        
        //Exibe o programa pedido
        case 2:
            system("clear");
            printf("\nID do programa:  1 a 5 - ");
            scanf("%d",&idProg);
            for(i=0;i<MAX;i++){
                if(!verificaString(prog[idProg-1].linhaProg[i]))
                   break;
                printf("\n%d. %s",i+1,prog[idProg-1].linhaProg[i]);
            }
            break;
        
        //Executa o programa
        case 3:
            system("clear");
            printf("\nID do programa:  1 a 5 - ");
            scanf("%d",&idProg);
            for(i=0;i<6;i++)
                instrucao[i] = 0;
            i=0;
            registrador = 0;
            do{
                for(j=0;j<6;j++)
                    instrucao[j] = '\0';
                if(!verificaString(prog[idProg-1].linhaProg[i]))
                   break;

                identificaInstrucao(prog[idProg-1].linhaProg[i],instrucao,pN,&e,tam,pValid,letra);
                e = realloc(e,tam);

                if(strncmp(instrucao,HALT,4) == 0)
                   break;
                   
                executaInstrucao(instrucao,pRegist,pN,&e,tam,pValid,letra);
                i++;
            }while(i<MAX);
        }
    }while(menu!= 4);
    free(e);
}

int main(){
    setlocale(LC_ALL,"portuguese");
    interpretador();
    return 0;
}
