#ifndef __MINE_AGENT__H
#define __MINE_AGENT__H 

#include "enviro.h"

using namespace enviro;

//Projectile type that is plopped out behind dude. Stays until collided with or hits 500 ticks
class MineController : public Process, public AgentInterface {

    public:
    MineController() : Process(), AgentInterface(), counter(0) {}

    void init() {}
    void start() {}
    //removes agent upon 500 cycles.
    void update() {
        if(counter++ >= 500){
            remove_agent(id());
        }
    }
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