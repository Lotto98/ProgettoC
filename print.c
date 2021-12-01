#include <stdio.h>
#include <stdlib.h>
#include "print.h"

/*Controllo overflow, sommando il numero di parametri richiesti "index" con la posizione corrente dell'array "i".
  Se la somma è maggiore o uguale al dimensione dell'array allora il programma termina*/
int controllo_overflow_print(int max, int i, int index){
    if(i+index>=max){

        return 0;
    }
    else{
        
        return 1;
    }
}

/*stampa su console l'elaborato del file di input.*/
int print_on_console(int *instruction_file, int *error){

    /*Dichiarazione di i per scorrere l'array instruction_file.*/
    int i=1;

    /*Finchè i è minore della dimensione dell'array instruction_file l'esecuzione continua.*/
    while( i < instruction_file[0] )
    {

        /*tramite switch/case vengono gestiti vari casi di istruzioni*/    
        switch (instruction_file[i]){
        /*Documentazione avanzamento i:
          -  i + 1: passa all'istruzione successiva da eseguire.
          -  i + 2: salta una posizione e passa all'istruzione successiva.
          -  i + 3: salta due posizioni e passa all'istruzione successiva. */

            /*L'struzione stampata è HALT.*/
            case 0:
                
                printf("[%d] %s ",(i-1),HALT);

                i=i+1;
                break;

            /*L'struzione stampata è DISPLAY.*/
            case 1:

                printf("[%d] %s ",(i-1),DISPLAY);
                
                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 1) ){

                    *error=2;
                    return 0;
                }
                printf("R%d ", instruction_file[i+1]);

                i=i+2;
                break;

            /*L'struzione stampata è PRINT_STACK.*/    
            case 2:
                printf("[%d] %s ",(i-1),PRINT_STACK);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 1) ){

                    *error=2;
                    return 0;
                }
                printf("%d ", instruction_file[i+1]);

                i=i+2;
                break;

            /*L'struzione stampata è PUSH.*/    
            case 10:
                printf("[%d] %s ",(i-1),PUSH);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 1) ){

                    *error=2;
                    return 0;
                }
                printf("R%d ", instruction_file[i+1]);

                i=i+2;
                break;

            /*L'struzione stampata è POP.*/
            case 11:
                printf("[%d] %s ",(i-1),POP);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 1) ){

                    *error=2;
                    return 0;
                }
                printf("R%d ", instruction_file[i+1]);

                i=i+2;
                break;

            /*L'struzione stampata è MOV.*/
            case 12:
                printf("[%d] %s ",(i-1),MOV);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 2) ){

                    *error=2;
                    return 0;
                }
                printf("R%d ", instruction_file[i+1]);
                printf("%d ", instruction_file[i+2]);

                i=i+3;
                break;

            /*L'struzione stampata è CALL.*/    
            case 20:
                printf("[%d] %s ",(i-1),CALL);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 1) ){

                    *error=2;
                    return 0;
                }
                printf("%d ", instruction_file[i+1]);

                i=i+2;
                break;

            /*L'struzione stampata è RET.*/    
            case 21:
                printf("[%d] %s ",(i-1),RET);
                    
                i=i+1;
                break;

            /*L'struzione stampata è JMP.*/    
            case 22:
                printf("[%d] %s ",(i-1),JMP);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 1) ){

                    *error=2;
                    return 0;
                }
                printf("%d ", instruction_file[i+1]);
                    
                i=i+2;
                break;

            /*L'struzione stampata è JZ.*/    
            case 23:
                printf("[%d] %s ",(i-1),JZ);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 1) ){

                    *error=2;
                    return 0;
                }
                printf("%d ", instruction_file[i+1]);
                    
                i=i+2;
                break;

            /*L'struzione stampata è JPOS.*/    
            case 24:
                printf("[%d] %s ",(i-1),JPOS);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 1) ){

                    *error=2;
                    return 0;
                }
                printf("%d ", instruction_file[i+1]);
                    
                i=i+2;
                break;

            /*L'struzione stampata è JNEG.*/
            case 25:
                printf("[%d] %s ",(i-1),JNEG);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 1) ){

                    *error=2;
                    return 0;
                }
                printf("%d ", instruction_file[i+1]);
                    
                i=i+2;
                break;

            /*L'struzione stampata è ADD.*/
            case 30:
                printf("[%d] %s ",(i-1),ADD);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 2) ){

                    *error=2;
                    return 0;
                }
                printf("R%d ", instruction_file[i+1]);
                printf("R%d ", instruction_file[i+2]);
                    
                i=i+3;
                break;

            /*L'struzione stampata è SUB.*/
            case 31:
                printf("[%d] %s ",(i-1),SUB);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 2) ){

                    *error=2;
                    return 0;
                }
                printf("R%d ", instruction_file[i+1]);
                printf("R%d ", instruction_file[i+2]);
                    
                i=i+3;
                break;

            /*L'struzione stampata è MUL.*/
            case 32:
                printf("[%d] %s ",(i-1),MUL);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 2) ){

                    *error=2;
                    return 0;
                }
                printf("R%d ", instruction_file[i+1]);
                printf("R%d ", instruction_file[i+2]);
                    
                i=i+3;
                break;

            /*L'struzione stampata è DIV_NUMBER.*/
            case 33:
                printf("[%d] %s ",(i-1),DIV);

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_print(instruction_file[0], i, 2) ){

                    *error=2;
                    return 0;
                }
                printf("R%d ", instruction_file[i+1]);
                printf("R%d ", instruction_file[i+2]);
                    
                i=i+3;
                break;

            /*Nel caso in cui non venga processata nessuna istruzione allora ritorna 0, interrompendo il programma.*/
            default:

                printf("Errore alla riga %d.\n",i-1);
                *error=0;
                return 0;

                break;
        }

        printf("\n");
    }

    /*Flusso di output per stampa su subsystem Linux su Windows.*/
    fflush(stdout);
    return 1;
}