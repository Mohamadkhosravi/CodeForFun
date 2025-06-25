# include "State.h"
#include "stdio.h"
#include <iostream>
using namespace std;

enum input_t {
    INPUT_START = 0,
    INPUT_PAUSE = 1,
    INPUT_STOP  = 2
};

class MusicPlayer;


class State {
public:
    virtual void enter(MusicPlayer* player) {}
    virtual void exit(MusicPlayer* player) {}
    virtual void handleInput(MusicPlayer* player, input_t input) {}
    virtual ~State() {}
};

class MusicPlayer {
private:
    State* currentState;
    State* previousState;

public:
    MusicPlayer(State* initialState);
    void transitionTo(State* newState);
    void transitionToPrevious();
    void handleInput(input_t input);
};


class PlayingState : public State {
public:
    static PlayingState& getInstance() {
        static PlayingState instance;
        return instance;
    }

    void enter(MusicPlayer* player) override {
        cout << " Playing music...\n";
    }

    void handleInput(MusicPlayer* player, input_t input) override {
        if (input == INPUT_PAUSE)
            player->transitionTo(&PausedState::getInstance());
        else if (input == INPUT_STOP)
            player->transitionTo(&StoppedState::getInstance());
    }
};

class PausedState : public State {
public:
    static PausedState& getInstance() {
        static PausedState instance;
        return instance;
    }

    void enter(MusicPlayer* player) override {
        cout << " Music paused.\n";
    }

    void handleInput(MusicPlayer* player, input_t input) override {
        if (input == INPUT_START)
            player->transitionTo(&PlayingState::getInstance());
        else if (input == INPUT_STOP)
            player->transitionTo(&StoppedState::getInstance());
    }
};

class StoppedState : public State {
public:
    static StoppedState& getInstance() {
        static StoppedState instance;
        return instance;
    }

    void enter(MusicPlayer* player) override {
        cout << "⏹ Music stopped.\n";
    }

    void handleInput(MusicPlayer* player, input_t input) override {
        if (input == INPUT_START)
            player->transitionTo(&PlayingState::getInstance());
    }
};


MusicPlayer::MusicPlayer(State* initialState) {
    currentState = initialState;
    previousState = nullptr;
    currentState->enter(this);
}

void MusicPlayer::transitionTo(State* newState) {
    if (currentState)
        currentState->exit(this);
    previousState = currentState;
    currentState = newState;
    currentState->enter(this);
}

void MusicPlayer::transitionToPrevious() {
    if (previousState) {
        State* temp = currentState;
        currentState = previousState;
        previousState = temp;
        currentState->enter(this);
    }
}

void MusicPlayer::handleInput(input_t input) {
    currentState->handleInput(this, input);
}

int main() {
    MusicPlayer player(&StoppedState::getInstance());
    int val;

    while (true) {
        cout << "\n Input command (0=Start, 1=Pause, 2=Stop): ";
        cin >> val;

        if (val < 0 || val > 2) {
            cout << " Invalid input. Try again.\n";
            continue;
        }

        player.handleInput(static_cast<input_t>(val));
    }

    return 0;
}
