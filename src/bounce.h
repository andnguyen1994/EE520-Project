#ifndef __BOUNCE_AGENT__H
#define __BOUNCE_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BounceController : public Process, public AgentInterface {

    public:
    BounceController() : Process(), AgentInterface(), counter(0) {}

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

class Bounce : public Agent {
    public:
    Bounce(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BounceController c;
};

DECLARE_INTERFACE(Bounce)

#endif