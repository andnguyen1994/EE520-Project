#ifndef __MINE_AGENT__H
#define __MINE_AGENT__H 

#include "enviro.h"

using namespace enviro;

//maybe use an event emitter
class MineController : public Process, public AgentInterface {

    public:
    MineController() : Process(), AgentInterface(), counter(0) {}

    void init() {
        notice_collisions_with("Wall", [&](Event &e) {
            if(counter++ >= 5){
                remove_agent(id());
            }
        });
        notice_collisions_with("Barrier", [&](Event &e) {
            if(counter++ >= 5){
                remove_agent(id());
            }
        });
    }
    void start() {}
    void update() {}
    void stop() {}

    int counter;
};

class Mine : public Agent {
    public:
    Mine(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    MineController c;
};

DECLARE_INTERFACE(Mine)

#endif