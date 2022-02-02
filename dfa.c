#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int tf_automaton(int cur_state, char input);
bool contains(int* final_states, int cur_state);

typedef struct dfa_s{
    int (*transition_func)(int cur_state, char input);
    int initial_state;
    int cur_state;
    int* final_states;
}dfa_t;


dfa_t* dfa_for_automaton(){
    int num_final_states = 10;

    dfa_t* dfa = (dfa_t *)malloc(sizeof(dfa_t));
    dfa->final_states = (int*)malloc(num_final_states*sizeof(int));
    dfa->final_states[0] = 9;
    dfa->transition_func = tf_automaton;
    dfa->initial_state = 0;
    dfa->cur_state = 0;

    return dfa;
}

int tf_automaton(int cur_state, char input){
    switch(input){
        case 'a':
            if (cur_state == 0){
                return 1;
            }
            else if (cur_state == 5){
                return 6;
            }
            else{
                return -1;
            }
            break;
        case 'u':
            if (cur_state == 1){
                return 2;
            }
            else{
                return -1;
            }
            break;
        case 't':
            if (cur_state == 2){
                return 3;
            }
            else if (cur_state == 6){
                return 7;
            }
            else{
                return -1;
            }
            break;
        case 'o':
            if (cur_state == 3){
                return 4;
            }
            else if (cur_state == 7){
                return 8;
            }
            else{
                return -1;
            }
            break;
        case 'm':
            if (cur_state == 4){
                return 5;
            }
            else{
                return -1;
            }
            break;
        case 'n':
            if (cur_state == 8){
                return 9;
            }
            else{
                return -1;
            }
            break;
        default:
            return -1;
    }
}

bool run_dfa(dfa_t* dfa, char* input){
    while (input[0] != '\0'){
        int cur = input[0];
        dfa->cur_state = dfa->transition_func(dfa->cur_state,cur);
        if(dfa->cur_state == -1){
            return false;
        }
        input++;
    }
    if (contains(dfa->final_states,dfa->cur_state)){
        return true;
    }
    else{
        return false;
    }
}

bool contains(int* final_states, int cur_state){
    while(final_states != NULL){
        if (*final_states == cur_state){
            return true;
        }
        final_states++;
    }
    return false;
}

int main(void){
    dfa_t* dfa = dfa_for_automaton();
    bool res = run_dfa(dfa,"automaton");
    printf("%d\n", res);
}