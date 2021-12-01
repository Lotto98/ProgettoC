#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filereader.h"
#include "print.h"
#include "execute.h"

/*Esecuzione del programma con gestione di tutti gli errori passati come parametro tramite *error. */
int main(int argc, char *argv[]){
  /*Documentazione array instructions:
  *instructions = array utilizzato per contenere tutte le istruzioni.*/
  int *instructions=NULL;

  /*Documentazione errori:
  error_file_reader = errore che ricorre solamente in file_reader.
  error_print = errore che ricorre solamente nell'esecuzione della chiamata di print.
  errore_execute = errore che ricorre solamente nell'esecuzione della chiamata di execute.*/
  int error_file_reader=1;
  int error_print=1;
  int error_execute=1;

  /*Gestione dei parametri di input.*/
  if (argc <3){

    printf("Errore: troppi pochi parametri.\n");
    return 0;
  }
  if(argc>3){

    printf("Attenzione: troppi parametri. Il programma continuerà l'esecuzione senza prendere in considerazione gli argomenti in eccesso.\n");
    printf("\n");
  }
  
  /*Gestione file_reader.*/
  instructions=file_reader(argv[2],&error_file_reader);

  if(instructions==NULL){

    if(error_file_reader==-1){

      printf("Errore nell'apertura del file in \"file_reader\". Il nome del file potrebbe essere errato.\n");
    }

    if(error_file_reader==2){

      printf("Errore in \"file_reader\". Il numero di linee non corrisponde al numero scritto all'inizio del file di input.\n");
    }

    if(error_file_reader==0){

      printf("Errore di allocazione. Array instructions non allocato in \"file_reader\".\n");
    }

    if(error_file_reader==3){

      printf("Errore in \"file_reader\": Il file è vuoto.\n");
    }

    return 0;
  }
  
  /*Gestione stampa/esegui del programma.*/
  if( (!strcmp(argv[1], "stampa")) || (!strcmp(argv[1], "Stampa")) || (!strcmp(argv[1], "STAMPA")) || (!strcmp(argv[1], "print")) || (!strcmp(argv[1], "Print")) || (!strcmp(argv[1], "PRINT")) ){

    if(instructions[0]==1){

      printf("Nessuna istruzione da stampare.\n");
      return 0;
    }

    printf("\nStampa:\n");

    if( !print_on_console(instructions, &error_print) ){

      if(error_print==0){

        printf("Errore: codice macchina non riconosciuto in \"print_on_console\".\n");
      }

      if(error_print==2){


        printf("Errore: parametro di un'istruzione mancante in \"print_on_console\".\n");
      }

      free(instructions);
      return 0;
    }
  }
  else{
      if ( (!strcmp(argv[1], "esegui")) || (!strcmp(argv[1], "Esegui")) || (!strcmp(argv[1], "ESEGUI")) || (!strcmp(argv[1], "execute")) || (!strcmp(argv[1], "Execute")) || (!strcmp(argv[1], "EXECUTE")) ){

        if(instructions[0]==1){

          printf("Nessuna istruzione da eseguire.\n");
          return 0;
        }

        printf("\nEsecuzione:\n");

        if( !execute(instructions, &error_execute) ){

          if(error_execute==0){

            printf("Errore: codice macchina non riconosciuto in \"execute\".\n");
          }

          if(error_execute==2){

            printf("Errore in \"assembly\".\n");
          }

          if(error_execute==3){

            printf("Errore: parametro di un'istruzione mancante in \"execute\".\n");
          }

          free(instructions);
          return 0;
        }
      }
      else{
        free(instructions);

        printf("Errore: il parametro 1 non è corretto.\n");
        return 0;
      }
  }

  /*Free dell'array instructions.*/
  free(instructions);

  /*Flusso di output per stampa su subsystem Linux su Windows.*/
  fflush(stdout);
  return 0;
}