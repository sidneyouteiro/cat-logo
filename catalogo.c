#include <stdio.h>
#include <stdlib.h>

typedef struct _artigo{
  char titulo[51];
  char evento[51];
  int volume, qtd_pagina, ano_pub;
  char cidade[31];
  char pais[21];
  struct _artigo *prox_artigo;
} artigo;

typedef struct _autor {
  char nome[41];
  char data[7];
  char instituicao[61];
  char pais[20];
  struct _artigo *artigo;
  struct _autor *prox_autor;
} autor;

artigo* cria_artigo(autor* autores){
  artigo *point_artigo;
  autores->artigo=point_artigo;
  point_artigo=(artigo*)malloc(sizeof(artigo));
  if(!point_artigo) return NULL;
  printf("Digite o título: \n");
  gets(point_artigo->titulo);

  printf("Digite o nome do evento: \n");
  gets(point_artigo->evento);

  printf("Digite o numero do volume: \n");
  scanf("%d",&point_artigo->volume);

  printf("Digite o título: \n");
  scanf("%d",&point_artigo->qtd_pagina);

  printf("Digite o ano de publicação: \n");
  scanf("%d",&point_artigo->ano_pub);

  printf("Digite o nome da cidade: \n");
  gets(point_artigo->cidade);

  printf("Digite o país de origem: \n");
  gets(point_artigo->pais);
  point_artigo->prox_artigo=NULL;
  return point_artigo;
}

autor* cria_autor(autor*pri){
  while((pri->prox_autor)!=N //completa esse null e bota o ) depois dele
  autor* autores; // ta faltando algo antes do autor
  if((autores=(autor*)malloc(sizeof(autor)))==0){  // autores nao declarado
    printf("memoria insuficiente\n");
    return NULL;
  }

  printf("Digite o nome do autor: \n");
  gets(autores->nome);

  printf("Digite a data :\n");
  gets(autores->data);

  printf("Digite a instituicao: \n");
  gets(autores->instituicao);

  printf("Digite o país: \n");
  gets(autores->pais);

  autores->prox_autor=NULL;
  autores->artigo=NULL;
  return autores;

}

void verifica(autor* prim){
  char name[41];
  scanf("%s",name);
  autor*aut;
  aut=prim;
  while(1){
    if((aut->nome)==name) break;
    aut=aut->prox_autor;
    if(aut==NULL){
      printf("Autor nao existe");
      return NULL;  //ta reclamando que função void nao tem retorno, mas é um warning
    }
  }
  aut->artigo=cria_artigo(autores); //autores nao declarado
}


int main(){
  int menu, eh_inicio = 1;
  autor *autor_aux;
  artigo *artigo_aux;
  autor *primautor;
  primautor=cria_autor(); //tu escreveu essa função com argumentos, mas tu ta rodando ela sem 
  while (1) {
    printf("Menu\n1-Autor\n2-Artigo\n3-Fim\n");
    scanf("%d",&menu);

    switch (menu) {
      case 1:

        cria_autor(primautor);
        break;
      case 2:verifica(primautor);
            break;
      case 3:return 0;
    }
  }
}
