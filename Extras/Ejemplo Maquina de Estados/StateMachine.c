//
//  StateMachine.c
//  
//
//  Created by Arturo Angeles on 13/11/2019.
//

#include "StateMachine.h"

// Este documento incluye el ejemplo de una maquina de estados.

int main(void){
    
    // Inicializacion de variable de estado al estado inicial.
    static PancakeMakerState machine_state= IDLE;
    
    // Instancia de pares {Label,funcion} de la maquina de estados.
    /*
        machine es una dupla de tipo PancakeMakerStateMachine con la
        funcion que ejecuta.
     
     */
    PancakeMakerStateMachine machine[]= {
        {IDLE,wait_command},
        {HEATING_PAN,heat_pan},
        {COOKING,place_mix},
        {TURN,turn_cake},
        {WRAP,wrapping},
        {READY,ready_to_go},
        {EXIT,exit_m}
    };

// Implementacion del ciclo infinito de la maquina de estados
    for(;;){
        // Validacion de seguridad para mantenerse dentro de los estados validos
        if(machine_state > STATE_NUM){
            puts("Error");
            return 0;
        }
        else{
            // Manda Ejecutar la funcion machine.process() correspondiente a la etiqueta machine_state.
            
            (*machine[machine_state].process)(&machine_state);
            
        }
    }
    return 0; // se acabo.
    
}

// Implementacion de funciones de la maquina de estados.

void wait_command(PancakeMakerState *state){
    
    int opc;
    
    puts("Welcome to the Pancake Maker");
    getchar();
    puts("Would you like a cake?\n[1] yes\n[2] no");
    scanf("%d",&opc);
    
    if(opc == 1){
        puts("great!");
        (* state) = HEATING_PAN; // Asignacion de siguiente estado
        return;
    }
    if (opc==2) {
        puts(":(");
        (* state) = EXIT; // Asignacion de siguiente estado
        return;
    }
    else{
        puts("Did not get that :(");
        (* state) = IDLE; // Asignacion de siguiente estado
    }
    
    
}
void heat_pan(PancakeMakerState *state){
    
    system("clear");
    puts("Heating the Pan");
    
    print_process_bar(5);
    (* state) = COOKING; // Asignacion de siguiente estado
    
}
void place_mix(PancakeMakerState *state){
    
    system("clear");
    puts("Placing the Mix");
    print_process_bar(2);
    (* state) = TURN; // Asignacion de siguiente estado
    

    
}
void turn_cake(PancakeMakerState *state){
    system("clear");
    puts("One Side Ready! :D");
    print_process_bar(1);
    (* state) = WRAP; // Asignacion de siguiente estado

    
}
void wrapping(PancakeMakerState *state){
    system("clear");
    puts("Wrapping");
    print_process_bar(3);
    (* state) = READY; // Asignacion de siguiente estado

    
}
void ready_to_go(PancakeMakerState *state){
    system("clear");
    puts("Ready to go!!!");
    print_process_bar(1);
    (* state) = IDLE; // Asignacion del ultimo estado al estado inicial

    
}

void print_process_bar(size_t time){
    size_t temp;
    
    for(temp=0; temp<time; temp ++){
        printf(".");
        sleep(1);
    }
    
}

// funcion de escape de la maquina de estados
// Solo para FSM (Finite State Machines)

void exit_m(PancakeMakerState *state){
    puts("goodbye");
    sleep(2);
    exit(0);
    
}
