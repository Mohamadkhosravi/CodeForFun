# include "State.h"
#include "stdio.h"
#include <iostream>

#define STOP  0
#define START 1
#define puse  2
char input=0;
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
    void TransitionToPperevius(State *state);
    void Input(MusicPlayer* player) override {
       // currentState->Input(this);
       //std::cin >> input;
        std::cout<< input;*/
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
        printf("music Started ");
    };
    void Input(MusicPlayer* player) override{
        
    };
   
};

class stopState : public State {
public:
    stopState();
    void entry(MusicPlayer* player) override{
        printf("music is stop !");
    };
    void exit(MusicPlayer* player)override{
        printf("music is not stop !");
    };
    void Input(MusicPlayer* player) override{
    };
   
};
class puseState :public State{
    
public:
    puseState();
    void entry(MusicPlayer* player) override{
        printf("music is puse !");
    };
    void exit(MusicPlayer* player)override{
        printf("music is not puse !");
    };
    void Input(MusicPlayer* player) override{
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
