#ifndef __ARM1_AGENT__H
#define __ARM1_AGENT__H 

#include "enviro.h"

using namespace enviro;

class arm1Controller : public Process, public AgentInterface {

    public:
    arm1Controller() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class arm1 : public Agent {
    public:
    arm1(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    arm1Controller c;
};

DECLARE_INTERFACE(arm1)

#endif