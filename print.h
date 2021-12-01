/*Definiti i nomi di tutte le istruzioni macchina.*/
#define HALT "HALT"
#define DISPLAY "DISPLAY"
#define PRINT_STACK "PRINT_STACK"
#define PUSH "PUSH"
#define POP "POP"
#define MOV "MOV"
#define CALL "CALL"
#define RET "RET"
#define JMP "JMP"
#define JZ "JZ"
#define JPOS "JPOS"
#define JNEG "JNEG"
#define ADD "ADD"
#define SUB "SUB"
#define MUL "MUL"
#define DIV "DIV"

/*Stampa i risultati su console.*/
int print_on_console(int *instruction_file, int* error);

/*Definita funzione per controllare overflow degli indici.*/
int controllo_overflow_print(int max, int i, int index);