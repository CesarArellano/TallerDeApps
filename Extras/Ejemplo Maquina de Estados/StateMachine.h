//
//  StateMachine.h
//  
//
//  Created by Arturo Angeles on 13/11/2019.
//

#ifndef StateMachine_h
#define StateMachine_h

// Importar bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Definicion de tipo de dato con etiquetas de la maquina de estados.
// PancakeMakerState
typedef enum stateType{
    IDLE,
    HEATING_PAN,
    COOKING,
    TURN,
    WRAP,
    READY,
    EXIT,
    STATE_NUM
}PancakeMakerState;

// Declaracion de estructura de pares {etiqueta,funciones}

typedef struct StateMachine{
    PancakeMakerState state;
    void (*process)(PancakeMakerState *state);
}PancakeMakerStateMachine;

// Prototipos de funciones ejecutables por la maquina de estados


void wait_command(PancakeMakerState *state);
void heat_pan(PancakeMakerState *state);
void place_mix(PancakeMakerState *state);
void turn_cake(PancakeMakerState *state);
void wrapping(PancakeMakerState *state);
void ready_to_go(PancakeMakerState *state);
void exit_m(PancakeMakerState *state);

// Funciones de ejecucion de maquina de estados


PancakeMakerStateMachine machine_initialiser(void);
void pancake_maker_on(PancakeMakerStateMachine machine);
void print_process_bar(size_t time);

#endif /* StateMachine_h */
