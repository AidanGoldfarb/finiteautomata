#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct states{
    int* state_arr;
    int size;
}state_t;


typedef struct nfa_s{
    state_t* (*transition_func)(int cur_state, char input);
    int initial_state;
    int cur_state;
    int* final_states;
    int num_final_states;
}nfa_t;

state_t* tf_zero(int cur_state, char input);
bool contains(int* arr, int element, int sz);




nfa_t* nfa_for_zero(){
    int num_final_states = 1;

    nfa_t* nfa = (nfa_t *)malloc(sizeof(nfa_t));
    nfa->final_states = (int*)malloc(num_final_states*sizeof(int));
    nfa->final_states[0] = 1;
    nfa->num_final_states = 1;
    nfa->transition_func = tf_zero;
    nfa->initial_state = 0;
    nfa->cur_state = 0;
    
    return nfa;
}

state_t* tf_zero(int cur_state, char input){
     switch(input){
        case 'a':
            if( cur_state == 0 ){
                printf("a in state 0\n");
                int num_states = 2;
                state_t* states = malloc(sizeof(state_t));
                states->state_arr = malloc(num_states*sizeof(int));
                states->state_arr[0] = 0;
                states->state_arr[1] = 1;
                states->size = num_states;
                return states;
            }
            break;
        case 'b':
            if( cur_state == 0 ){
                printf("b in state 0\n");
                int num_states = 1;
                state_t* states = malloc(sizeof(state_t));
                states->state_arr = malloc(num_states*sizeof(int));
                states->state_arr[0] = 0;
                states->size = num_states;
                return states;
            }
            else if( cur_state == 1 ){
                printf("b in state 1\n");
                int num_states = 1;
                state_t* states = malloc(sizeof(state_t));
                states->state_arr = malloc(num_states*sizeof(int));
                states->state_arr[0] = -1;
                states->size = 0;
                return states;
            }
            else{
                int num_states = 1;
                state_t* states = malloc(sizeof(state_t));
                states->state_arr = malloc(num_states*sizeof(int));
                states->state_arr[0] = -1;
                states->size = num_states;
                return states;
            }
            break;
        default: ;
            state_t* states = malloc(sizeof(state_t));
            states->size = 0;
            return states;
     }
    state_t* states = malloc(sizeof(state_t));
    states->size = 0;
    return states;
}

bool run_nfa(nfa_t* nfa, char* input, int cur_state){
    bool res = false;
    char token = input[0];
    if(token == '\0'){
        res = contains(nfa->final_states,cur_state,nfa->num_final_states);
    }
    while(token != '\0'){
        state_t* states = tf_zero(cur_state, token);
        input++;
        token = input[0];
        for(int i = 0; i<states->size; i++){
            int state = states->state_arr[i];
            res |= run_nfa(nfa,input,state);
        }
        
    }
    return res;
}

bool contains(int* arr, int element, int sz){
    for(int i = 0; i<sz; i++){
        if(arr[i] == element){
            printf("found %d in final states\n", element);
            return true;
        }
    }
    printf("did not find %d in final states\n", element);
    return false;
}

int main(void){
    nfa_t* nfa = nfa_for_zero();
    bool res = run_nfa(nfa,"aaba",0);
    printf("%d\n", res);
}