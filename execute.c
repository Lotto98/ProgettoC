#include <stdio.h>
#include <stdlib.h>
#include "execute.h"

/*Controllo overflow, sommando il numero di parametri richiesti "index" con la posizione corrente dell'array "i".
  Se la somma è maggiore o uguale al dimensione dell'array allora il programma termina*/
int controllo_overflow_execute(int max, int i, int index){
    if(i+index>=max){

        return 0;
    }
    else{
        
        return 1;
    }
}

/*Funzione che comprende uno switch / case in grado di gestire l'esecuzione del programma.*/
int execute(int *instruction_file, int *error){

    /*Inizializzazione di SP ed IP. */
    unsigned int SP=0;
    int IP=1;

    /*Inizializzazione dei registri e dello stack.*/
    int registers[numb_regist];
    int stack[stack_dimension];
    
    /*Finchè IP è minore della dimensione dell'array istruzioni, l'esecuzione continua. 
    In posizione 0 è salvata la dimensione dell'array.*/
    while(IP < instruction_file[0]){ 

        /*Tramite switch/case vengono gestiti vari casi di istruzioni.*/    
        switch (instruction_file[IP]){
            /*Documentazione avanzamento IP(varia dal numero di parametri presenti nelle funzioni): 
              -  IP + 1: passa all'istruzione successiva da eseguire.
              -  IP + 2: salta una posizione e passa all'istruzione successiva.
              -  IP + 3: salta due posizioni e passa all'istruzione successiva.*/


            /*Istruzione HALT: Il programma termina.*/
            case 0:
                    
                return 1;
                break;

            /*Istruzione DISPLAY: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP viene incrementato secondo documentazione.*/
            case 1:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 1) ){

                    *error=3;
                    printf("Errore in \"DISPLAY\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                
                /*Gestione errore funzione */
                if( !display(registers, instruction_file[IP+1]) ){
                        
                    *error=2;
                    printf("Errore in \"DISPLAY\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                IP=IP+2;
                break;

            /*Istruzione PRINT_STACK: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP viene incrementato secondo documentazione.*/
            case 2:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 1) ){

                    *error=3;
                    printf("Errore in \"PRINT_STACK\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !print_stack(&SP, stack, instruction_file[IP+1]) ){

                    *error=2;
                    printf("Errore in \"PRINT_STACK\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                IP=IP+2;
                break;

            /*Istruzione PUSH: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP viene incrementato secondo documentazione.*/
            case 10:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 1) ){

                    *error=3;
                    printf("Errore in \"PUSH\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !push(&SP, stack, registers[instruction_file[IP+1]] ) ){

                    *error=2;
                    printf("Errore nella \"PUSH\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                IP=IP+2;
                break;

            /*Istruzione POP: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP viene incrementato secondo documentazione.*/
            case 11:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 1) ){

                    *error=3;
                    printf("Errore in \"POP\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !pop(&SP, stack, registers, instruction_file[IP+1]) ){
                        
                    *error=2;
                    printf("Errore in \"POP\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                IP=IP+2;
                break;
    
            /*Istruzione MOV: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP viene incrementato secondo documentazione.*/
            case 12:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 2) ){

                    *error=3;
                    printf("Errore in \"MOV\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !mov(registers, instruction_file[IP+1], instruction_file[IP+2]) ){
                    
                    *error=2;
                    printf("Errore in \"MOV\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }    
                    
                IP=IP+3;
                break;
    
            /*Istruzione CALL: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP non viene incrementato in quanto effettua una jmp salvando in memoria la posizione successiva alla sua chiamata.*/
            case 20:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 1) ){

                    *error=3;
                    printf("Errore in \"CALL\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !call(stack, &SP, &IP, instruction_file[IP+1]) ){
                    
                    *error=2;
                    printf("Errore nella \"CALL\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                break;
            
            /*Istruzione RET: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP non viene incrementato in quanto ritorna al valore salvato in memoria dalla funzione CALL.*/
            case 21:

                /*Gestione errore funzione */
                if( !ret(stack, &SP, &IP) ){
                        
                    *error=2;
                    printf("Errore in \"RET\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                    
                break;
        
            /*Istruzione JMP: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP non viene incrementato in quanto la funzione provvede a "saltare" alla posizione indicata.*/
            case 22:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 1) ){

                    *error=3;
                    printf("Errore in \"JMP\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !jmp(&IP, instruction_file[IP+1]) ){
                        
                    *error=2;
                    printf("Errore in \"JMP\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                break;
            
            /*Istruzione JZ: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP non viene incrementato in quanto la funzione provvede a "saltare" alla posizione indicata.*/
            case 23:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 1) ){

                    *error=3;
                    printf("Errore in \"JZ\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !jz(&IP, stack, &SP, instruction_file[IP+1]) ){
                        
                    *error=2;
                    printf("Errore in \"JZ\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                break;
        
            /*Istruzione JPOS: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP non viene incrementato in quanto la funzione provvede a "saltare" alla posizione indicata.*/
            case 24:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 1) ){

                    *error=3;
                    printf("Errore in \"JPOS\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !jpos(&IP, stack, &SP, instruction_file[IP+1]) ){
                        
                    *error=2;
                    printf("Errore in \"JPOS\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                break;
    
            /*Istruzione JNEG: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP non viene incrementato in quanto la funzione provvede a "saltare" alla posizione indicata.*/
            case 25:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 1) ){

                    *error=3;
                    printf("Errore in \"JNEG\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !jneg(&IP, stack, &SP, instruction_file[IP+1]) ){

                    *error=2;    
                    printf("Errore in \"JNEG\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                break;
        
            /*Istruzione ADD: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP viene incrementato secondo documentazione.*/
            case 30:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 2) ){

                    *error=3;
                    printf("Errore in \"ADD\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !add(stack, registers, &SP, instruction_file[IP+1], instruction_file[IP+2]) ){
                    
                    *error=2;
                    printf("Errore in \"ADD\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                    
                IP=IP+3;
                break;
            
            /*Istruzione SUB: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP viene incrementato secondo documentazione.*/
            case 31:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 2) ){

                    *error=3;
                    printf("Errore in \"SUB\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !sub(stack, registers, &SP, instruction_file[IP+1],instruction_file[IP+2]) ){
                        
                    *error=2;
                    printf("Errore in \"SUB\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                    
                IP=IP+3;
                break;
        
            /*Istruzione MUL: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP viene incrementato secondo documentazione.*/
            case 32:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 2) ){

                    *error=3;
                    printf("Errore in \"MUL\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !mul(stack, registers, &SP, instruction_file[IP+1], instruction_file[IP+2]) ){
                        
                    *error=2;
                    printf("Errore in \"MUL\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                    
                IP=IP+3;
                break;
            
            /*Istruzione DIV_NUMBER: Se non può essere eseguita, vengono stampati i seguenti messaggi d'errore.
              In caso contrario IP viene incrementato secondo documentazione.*/
            case 33:

                /*Gestione overflow istruzioni.*/
                if( !controllo_overflow_execute(instruction_file[0], IP, 2) ){

                    *error=3;
                    printf("Errore in \"DIV_NUMBER\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }

                /*Gestione errore funzione */
                if( !div_number(stack, registers, &SP, instruction_file[IP+1], instruction_file[IP+2]) ){
                        
                    *error=2;
                    printf("Errore nella \"DIV_NUMBER\", ");
                    printf("l'IP vale: %d.\n", (IP-1));
                    return 0;
                }
                    
                IP=IP+3;
                break; 
            
            /*Nel caso in cui non venga processata nessuna istruzione allora ritorna 0, interrompendo il programma.*/
            default:

                printf("Errore a IP = %d.\n",IP-1);
                *error=0;
                return 0;
                break;
        }
                
    }
    /*Flusso di output per stampa su subsystem Linux su Windows.*/
    fflush(stdout);
    return 1;
}