# include "State.h"
#include "stdio.h"
#include <iostream>

#define STOP  0
#define START 1
#define puse  2
input_t input=0;  // input 0(PLAY):  >  input 1(PUSE): ||>  input 3(STOP): #
typedef enum input_t{
    START=0;
    PUSE=1;
    STOP=3;
}
class MusicPlayer;
class State {
public:
    State();
    virtual void entry(MusicPlayer* player){};
    virtual void exit(MusicPlayer* player){};
    virtual void Input(MusicPlayer* player){};
};

class MusicPlayer : public State {
public:
    MusicPlayer *currentState, *pereviusState;
    MusicPlayer();
    void TransitionToNewState(State *state);
    void TransitionToPerevius();
    void Input(MusicPlayer* player) override {
       // currentState->Input(this);
       //std::cin >> input;
        std::cout<< input;
        currentState->Input(this);
    };
   
};

class startState : public State {
public:
    startState();
    void entry(MusicPlayer* player) override{
        printf("Start music !");
    };
    void exit(MusicPlayer* player)override{
        
    };
    void Input(MusicPlayer* player) override{
        switch(input){
            case START:
                break;
            case PUSE:
                break;
            case STOP:
                break;
        }
    };
   
};

class stopState : public State {
public:
    stopState();
    void grtInctance(void);
    void entry(MusicPlayer* player) override{
        printf("music is stop !");
    };
    void exit(MusicPlayer* player)override{
       
    };
    void Input(MusicPlayer* player) override{
        switch(input){
            case START:
                 TransitionToNewState(playState::getInctance());
                break;
            case PUSE:
                 TransitionToPerevius();
                break;
            case STOP:
                TransitionToPerevius();
                break;
        }
    };
   
};
class puseState :public State{
    
public:
    puseState();
    void entry(MusicPlayer* player) override{
        printf("music is puse !");
    };
    void exit(MusicPlayer* player)override{
    
    };
    void Input(MusicPlayer* player) override{
        switch(input){
            case START:
                break;
            case PUSE:
                break;
            case STOP:
                break;
        }
    };
};

class playState :public State{
    
public:
    playState();
    void entry(MusicPlayer* player) override{
        printf("music is puse !");
    };
    void exit(MusicPlayer* player)override{
    
    };
    void Input(MusicPlayer* player) override{
        switch(input){
            case START:
                break;
            case PUSE:
                break;
            case STOP:
                break;
        }
    };
};

int main(){
   // while (1) {
        //scanf("%d",&input);
        std::cin>>input;
        printf("number is: %d!",input);
        printf("Hello");
   // }
   
    return 0;
}
