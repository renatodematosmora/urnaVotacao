#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include "ArvoreBinaria.h";

using namespace std;

int main(){
    FILE *arq_eleitores;
    FILE *arq_candidatos;
    FILE *arq_resultado;
    arq_resultado = fopen("resultado.txt","w");
    Arv_Candidato *RaizCandidato, *aux;
    Arv_Eleitores *RaizEleitor;

    ObjetoCandidato Candidato;
    ObjetoEleitor Eleitor;

    Lista *L;
    char conteudo[2];
    char linha[200];
    char *vet[21];
    int i = 0;

    RaizCandidato = inicializaCandidato();
    RaizEleitor = inicializaEleitor();
    L = inicializaLista();

    //abertura do arquivo de candidatos e inserção na arvore de candidatos.
    arq_candidatos = fopen("1_Candidatos.txt","r");
    if(!arq_candidatos){
        printf("Erro ao abrir o arquivo!!");
        exit(0);
    }
    fgets(linha,100,arq_candidatos);
    while(!feof(arq_candidatos)){
        fgets(linha,200,arq_candidatos);
        Candidato.nome = strtok(linha, ";");
        Candidato.num_cadidato = strtok(NULL, ";");
        Candidato.partido = strtok(NULL, "\n");
        RaizCandidato = insereArvoreCandidato(RaizCandidato, Candidato);
    }
    fclose(arq_candidatos);
    //abertura do arquivo de candidatos e inserção na arvore de candidatos.
    arq_eleitores = fopen("Eleitores.txt","r");
    if(!arq_eleitores){
        printf("Erro ao abrir o arquivo!!");
        exit(0);
    }
    fgets(linha,100,arq_eleitores);
    while(!feof(arq_eleitores)){
        fgets(linha,200,arq_eleitores);
        Eleitor.nome = strtok(linha, ";");
        Eleitor.idade = strtok(NULL, ";");
        Eleitor.municipio = strtok(NULL, "\n");
        int idadeEleitor = atoi(Eleitor.idade);
        if(idadeEleitor >= 16){
            RaizEleitor = insereArvoreEleitores(RaizEleitor, Eleitor);
        }
    }
    fclose(arq_eleitores);

    //printf("-=-=-=-=-Candidatos-=-=-=-=-\n");
    pre_ordem_candidato(RaizCandidato, vet, i);
    printf("-=-=-=-=-Eleitores-=-=-=-=-\n");
    srand(time(NULL));
    pre_ordem_eleitor(RaizEleitor, RaizCandidato, vet, i);
    printf("-=-=-=-=-Resultado da Eleicao-=-=-=-=-\n");
    resultado_eleicao(RaizCandidato, &L);
    boletim_urna(arq_resultado, L);



    if(!arq_resultado){
        printf("Erro ao abrir o arquivo!!");
        exit(0);
    }

    fclose(arq_resultado);
}
