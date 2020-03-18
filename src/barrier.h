#ifndef __BARRIER_AGENT__H
#define __BARRIER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BarrierController : public Process, public AgentInterface {

    public:
    BarrierController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class Barrier : public Agent {
    public:
    Barrier(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BarrierController c;
};

DECLARE_INTERFACE(Barrier)

#endif