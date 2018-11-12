#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char data[10];
  char instituicao[61];
  char pais[20];
  struct _artigo *artigo;
  struct _autor *prox_autor;
} autor;

autor *lista;

//--------------------------------------------
artigo* cria_artigo();
autor* cria_autor(autor *primeiro_autor);
int fimdoprograma(autor* aux_autor);
void free_all(autor* primeiro); 
void free_all_artigo(artigo* partigo);

int main(void)
{

  int menu, t = 1;
  autor *primeiro_autor; /*apontará sempre pro primeiro autor*/
  autor *aux_autor; /*ponteiro auxiliar para percorrer a struct*/
  artigo *primeiro_artigo;
  char name[41];
  
  if((primeiro_autor = (autor*) malloc(sizeof(autor))) == 0){
    printf("Memoria insuficiente\n");
    return 1;
  }

  printf("CADASTRE O PRIMEIRO AUTOR:\n\n");

  printf("Digite o nome do autor: \n");
  scanf("%s", primeiro_autor->nome);
  getchar();

  printf("Digite a data de nascimento:\n");
  scanf("%s", primeiro_autor->data);
  getchar();

  printf("Digite a instituicao: \n");
  scanf("%s", primeiro_autor->instituicao);
  getchar();

  printf("Digite o pais: \n");
  scanf("%s", primeiro_autor->pais);

  primeiro_autor->prox_autor = NULL;
  
  if((primeiro_artigo = (artigo*) malloc(sizeof(autor))) == 0){
    printf("Memoria insuficiente\n");
    return 1;
  }


  printf("\n\nCADASTRE O PRIMEIRO ARTIGO:\n\n");

  printf("Digite o titulo do artigo: \n");
  scanf("%s", primeiro_artigo->titulo);
  getchar();

  printf("Digite o nome do evento: \n");
  scanf("%s", primeiro_artigo->evento);
  getchar();

  printf("Digite o numero do volume: \n");
  scanf("%d", &(primeiro_artigo->volume));

  printf("Digite quantidade de paginas: \n");
  scanf("%d", &(primeiro_artigo->qtd_pagina));

  printf("Digite o ano de publicação: \n");
  scanf("%d", &(primeiro_artigo->ano_pub));

  printf("Digite o nome da cidade: \n");
  scanf("%s", primeiro_artigo->cidade);
  getchar();

  printf("Digite o pais de origem: \n");
  scanf("%s", primeiro_artigo->pais);
  getchar();

  (primeiro_artigo->prox_artigo) = NULL;
  
  primeiro_autor->artigo = primeiro_artigo;

  aux_autor = primeiro_autor; /*ponteiro auxiliar aponta para o primeiro autor*/

  while (t) {
    
    printf("\nMenu\n1- Cadastrar novo autor\n2- Cadastrar novo Artigo\n3- Fim\n");
    scanf("%d", &menu);

    switch (menu){
      case 1:
             while ((aux_autor->prox_autor) != NULL) aux_autor = (aux_autor->prox_autor);
             (aux_autor->prox_autor) = cria_autor(aux_autor);
             aux_autor = aux_autor->prox_autor;
             aux_autor->prox_autor = NULL;
             break;
      case 2:/* verifica se existe autor com o nome dado*/
             printf("Digite o nome do autor desejado: \n");
             scanf("%s", name);
             getchar();

             aux_autor = primeiro_autor;

             while(1){
                 if (!(strcmp ((aux_autor->nome), name))) break;
                 aux_autor = aux_autor->prox_autor;

                 if (aux_autor == NULL){
                     printf("\nAutor nao existe\n");
                     return 0;
                 }
             }
             
             aux_autor->artigo = cria_artigo();
             break;
      case 3: t=0;
             
             /* chama fim do programa que salva a lista no arquivo, se não consegue retorna 1*/
             if(fimdoprograma(primeiro_autor) == 1) {
                 printf("Não foi possivel salvar o arquivo\n");
                 return 1;
             } 

             free_all(primeiro_autor);
             
             break;
  
    }/* FIM SWITCH */
  } /* FIM WHILE */

 
  return 0; 
}/*FIM DA MAIN*/








artigo* cria_artigo(){
  artigo *point_artigo;

  point_artigo = (artigo*) malloc(sizeof(artigo));

  if(!point_artigo) {
      printf("Erro de alocação.\n");
      return NULL;
  }

  printf("Digite o titulo: \n");
  scanf("%s", point_artigo->titulo);
  getchar();

  printf("Digite o nome do evento: \n");
  scanf("%s", point_artigo->evento);
  getchar();

  printf("Digite o numero do volume: \n");
  scanf("%d", &(point_artigo->volume));

  printf("Digite a quantidade de páginas: \n");
  scanf("%d", &(point_artigo->qtd_pagina));

  printf("Digite o ano de publicação: \n");
  scanf("%d", &(point_artigo->ano_pub));

  printf("Digite o nome da cidade: \n");
  scanf("%s", point_artigo->cidade);
  getchar();

  printf("Digite o pais de origem: \n");
  scanf("%s", point_artigo->pais);
  getchar();

  (point_artigo->prox_artigo) = NULL;

  return point_artigo;
}

autor* cria_autor(autor *aux_autor){
  while((aux_autor->prox_autor) != NULL){
    aux_autor = aux_autor->prox_autor;
  }

  autor* autores;

  if((autores= (autor*) malloc(sizeof(autor))) == 0){
    printf("memoria insuficiente\n");
    return NULL;
  }

  printf("Digite o nome do autor: \n");
  scanf("%s", autores->nome);

  printf("Digite a data de nascimento: \n");
  scanf("%s", autores->data);

  printf("Digite a instituição: \n");
  scanf("%s", autores->instituicao);

  printf("Digite o país: \n");
  scanf("%s", autores->pais);

  autores->prox_autor = NULL;
  autores->artigo = NULL;
  return autores;
}


int fimdoprograma(autor* aux_autor){
  
  FILE* txt;
  if((txt=fopen("lista.txt","w")) == NULL){
    printf("Nao foi possivel abrir o arquivo");
    return 1;
  }
  fputs("\t-----Catalogo-----",txt);

  while((aux_autor)!= NULL){
    fputs("\n\n",txt);
    fprintf(txt, "Nome do autor: %s", aux_autor->nome);
   
    fprintf(txt, "\nData de nascimento: %s", aux_autor->data);
   
    fprintf(txt, "\nInstituição: %s", aux_autor->instituicao);
   
    fprintf(txt, "\nPaís: %s", aux_autor->pais);

      while((aux_autor->artigo)!=NULL){
          fputs("\n\tArtigos: ",txt);
          fprintf(txt, "\nTítulo: %s", (aux_autor->artigo)->titulo);
          fprintf(txt, "\nEvento: %s", (aux_autor->artigo)->evento);
          fprintf(txt, "\nVolume: %d", (aux_autor->artigo)->volume);
          fprintf(txt, "\nNº de Páginas: %d", (aux_autor->artigo)->qtd_pagina);
          fprintf(txt, "\nAno de publicação: %d", (aux_autor->artigo)->ano_pub);
          fprintf(txt, "\nCidade: %s", (aux_autor->artigo)->cidade);
          fprintf(txt, "\nPaís: %s", (aux_autor->artigo)->pais);

          (aux_autor->artigo) = ((aux_autor->artigo)->prox_artigo);
      if ((aux_autor->artigo)!=NULL)break;
      }

      aux_autor = (aux_autor->prox_autor);
     if ((aux_autor)= NULL)break;
    }
  fclose(txt);
  return 0;
}



void free_all(autor* primeiro){
  int i=1;
  while(i && (primeiro->prox_autor)!=NULL){
   free_all(primeiro->prox_autor);
   i=0;
}  
  free_all_artigo(primeiro->artigo); 
  free(primeiro);
}

void free_all_artigo(artigo* partigo){
  int i=1;
  while(i && (partigo->prox_artigo)!=NULL){
   free_all_artigo(partigo->prox_artigo);
   i=0;
}  
  free(partigo);

}

