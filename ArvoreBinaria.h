#ifndef ARVOREBINARIA_H_INCLUDED
#define ARVOREBINARIA_H_INCLUDED

struct ObjetoCandidato
{
    char *nome = NULL;
    char *num_cadidato = NULL;
    char *partido = NULL;
};

struct ObjetoEleitor
{
    char *nome = NULL;
    char *idade = NULL;
    char *municipio = NULL;
};

struct Arv_Candidato{
    char nome[100];
    char num_cadidato[4];
    char partido[10];
    int votos = 0;
    int fatorB;
    Arv_Candidato *pai, *arvE, *arvD;
};

struct Arv_Eleitores{
    char nome[100];
    char idade[3];
    char municipio[100];
    int fatorB;
    Arv_Eleitores *pai, *arvE, *arvD;
};

struct Lista {
 	char nome[100];
    char num_cadidato[4];
    char partido[10];
    int votos = 0;
 	Lista *prox;
};

Lista *inicializaLista ()
{
  return NULL;
}

Arv_Candidato* inicializaCandidato(void)
{
   return NULL;
}

Arv_Eleitores* inicializaEleitor(void){
    return NULL;
}

Arv_Candidato *insereArvoreCandidato(Arv_Candidato* Raiz, ObjetoCandidato elemento)
{
   Arv_Candidato *aux, *ant;
   Arv_Candidato *no = (Arv_Candidato*) malloc(sizeof(Arv_Candidato));

   strcpy(no->nome,elemento.nome);
   strcpy(no->num_cadidato,elemento.num_cadidato);
   strcpy(no->partido,elemento.partido);
   no->arvE = NULL;
   no->arvD = NULL;

   aux = Raiz;
   while (aux != NULL)
   {
     ant = aux;
     if (elemento.num_cadidato >= aux->num_cadidato)
        aux = aux->arvD;
        else
          aux = aux->arvE;
   }
   if (aux == Raiz)
   {
      no->pai = NULL;
      Raiz = no;
   }
   else
   {
     no->pai = ant;
     if (elemento.num_cadidato >= ant->num_cadidato)
        ant->arvD = no;
     else
        ant->arvE = no;
   }
   return (Raiz);
}

Arv_Eleitores *insereArvoreEleitores(Arv_Eleitores* Raiz,ObjetoEleitor elemento)
{
    Arv_Eleitores *aux, *ant;
    Arv_Eleitores *no = (Arv_Eleitores*) malloc(sizeof(Arv_Eleitores));

   strcpy(no->nome,elemento.nome);
   strcpy(no->municipio,elemento.municipio);
   strcpy(no->idade,elemento.idade);
   no->arvE = NULL;
   no->arvD = NULL;

   aux = Raiz;
   while (aux != NULL)
   {
     ant = aux;
     if (elemento.idade >= aux->idade)
        aux = aux->arvD;
        else
          aux = aux->arvE;
   }
   if (aux == Raiz)
   {
      no->pai = NULL;
      Raiz = no;
   }
   else
   {
     no->pai = ant;
     if (elemento.idade >= ant->idade)
        ant->arvD = no;
     else
        ant->arvE = no;
   }
   return (Raiz);
}

void pre_ordem_candidato(Arv_Candidato *Raiz, char *vet[], int i){
    if(Raiz != NULL){
        vet[i] = Raiz->nome;
        i++;
        pre_ordem_candidato(Raiz->arvE, vet, i);
        pre_ordem_candidato(Raiz->arvD, vet, i);
    }
}

void votacao(Arv_Candidato *Raiz, char *vet[], int i){
    if(Raiz != NULL){
        if(vet[i] == Raiz->nome){
            Raiz->votos++;
            //printf("candidato: %s | %d votos\n\n", Raiz->nome, Raiz->votos);
        }
        votacao(Raiz->arvE, vet, i);
        votacao(Raiz->arvD, vet, i);
    }
}

void pre_ordem_eleitor(Arv_Eleitores *Raiz, Arv_Candidato *RaizCandidato, char *vet[], int i){

    if(Raiz != NULL){
        i = rand() % 21 + 0;
        //printf("%s | %s\n", Raiz->nome, vet[i]);
        votacao(RaizCandidato, vet, i);
        pre_ordem_eleitor(Raiz->arvE, RaizCandidato, vet, i);
        pre_ordem_eleitor(Raiz->arvD, RaizCandidato, vet, i);
    }
}

void insereOrdenado(Lista **l, Arv_Candidato *Raiz){
    Lista* novo, *ant, *aux;
    aux = *l;
    ant = NULL;
    while(aux != NULL && aux->votos > Raiz->votos){
        ant = aux;
        aux = aux->prox;
    }
    novo = (Lista*) malloc(sizeof(Lista));
    novo->votos = Raiz->votos;
    strcpy(novo->nome, Raiz->nome);
    strcpy(novo->partido, Raiz->partido);
    strcpy(novo->num_cadidato, Raiz->num_cadidato);
    if(ant == NULL){
        novo->prox = (*l);
        (*l) = novo;
    }
    else{
        novo->prox = ant->prox;
        ant->prox = novo;
    }
}


void resultado_eleicao(Arv_Candidato *Raiz, Lista **l){
    if(Raiz != NULL){
        printf("%s | %d\n", Raiz->nome, Raiz->votos);
        insereOrdenado(&(*l), Raiz);
        resultado_eleicao(Raiz->arvE, &(*l));
        resultado_eleicao(Raiz->arvD,&(*l));
    }
}

void boletim_urna(FILE *arq_resultado, Lista *l){
    //char conteudo[2];
    Lista* p = l;
    //criação do arquivo de resultados da eleição.
    arq_resultado = fopen("resultado.txt","w");
    if(!arq_resultado){
        printf("Erro ao abrir o arquivo!!");
        exit(0);
    }
    fputs("CANDIDATO", arq_resultado);
    fputc(';', arq_resultado);
    fputs("PARTIDO", arq_resultado);
    fputc(';', arq_resultado);
    fputs("TOTAL VOTOS", arq_resultado);
    fputc('\n', arq_resultado);
    while(l!=NULL)
    {
         fprintf(arq_resultado,"%s;%s;%d\n",l->nome, l->partido, l->votos);
         l=l->prox;
    }
    fclose(arq_resultado);
}

/*
//PROCEDIMENTOS PARA ARVORE AVL
ArvB* rotacao_direita(ArvB* Raiz){
    ArvB* aux = Raiz->arvE;
    if(aux->arvD != NULL){
        Raiz->arvE = aux->arvD;
    }
    else{
        Raiz->arvE = NULL;
    }
    aux->arvD = Raiz;
    return aux;
}

ArvB* rotacao_esquerda(ArvB* Raiz){
    ArvB* aux = Raiz->arvD;
    if(aux->arvE != NULL){
        Raiz->arvD = aux->arvE;
    }
    else{
        Raiz->arvD = NULL;
    }
    aux->arvE = Raiz;
    return aux;
}

int Altura (ArvB* Raiz)
{
	int Alt_Esq, Alt_Dir;
	if (Raiz == NULL)
        return 0;
	else
	{
		Alt_Esq = Altura (Raiz->arvE);
		Alt_Dir = Altura (Raiz->arvD);
		if (Alt_Esq > Alt_Dir)
		{
			return (1 + Alt_Esq);
		}
		else
		{
			return (1 + Alt_Dir);
		}
	}
}

int Calcula_fatorB(ArvB* Raiz)
{
    if(Raiz == NULL)
        return 0;
    return (Altura(Raiz->arvE)- Altura(Raiz->arvD));
}

ArvB* rotacao_dupla_direita (ArvB* Raiz)
{
       ArvB* aux1= Raiz->arvE;
       ArvB* aux2= aux1->arvD;

       if(aux2->arvE != NULL)
           aux1->arvD= aux2->arvE;
       else aux1->arvD = NULL;

       if(aux2->arvD != NULL)
           Raiz->arvE = aux2->arvD;
       else Raiz->arvE = NULL;

       aux2->arvE = aux1;
       aux2->arvD = Raiz;

       return aux2;
}

ArvB* rotacao_dupla_esquerda (ArvB* Raiz)
{
       ArvB* aux1 = Raiz->arvD;
       ArvB* aux2 = aux1->arvE;

       if(aux2->arvE != NULL)
          Raiz->arvD = aux2->arvE;
       else Raiz->arvD = NULL;

       if(aux2->arvD != NULL)
          aux1->arvE = aux2->arvD;
       else aux1->arvE = NULL;

       aux2->arvE = Raiz;
       aux2->arvD = aux1;

       return aux2;
}

ArvB* CorrigeAVL(ArvB* noArv)
{
	if(noArv != NULL)
	{
		noArv->fatorB = Calcula_fatorB(noArv);
		if(noArv->fatorB == 2)
		{
			noArv->arvE->fatorB = Calcula_fatorB(noArv->arvE);
			if(noArv->arvE->fatorB > 0)
			   noArv = rotacao_direita(noArv);
			else
			   noArv =  rotacao_dupla_direita(noArv);

		}
		else if(noArv->fatorB == -2)
		{
			noArv->arvD->fatorB = Calcula_fatorB(noArv->arvD);
			if(noArv->arvD->fatorB < 0)
			   noArv  = rotacao_esquerda(noArv);
			else
			   noArv =  rotacao_dupla_esquerda(noArv);
        }
		noArv->arvE = CorrigeAVL(noArv->arvE);
		noArv->arvD = CorrigeAVL(noArv->arvD);
    }
    return noArv;
}
*/
#endif // ARVOREBINARIA_H_INCLUDED
