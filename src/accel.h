#ifndef __ACCEL_AGENT__H
#define __ACCEL_AGENT__H 

#include "enviro.h"

using namespace enviro;

class AccelController : public Process, public AgentInterface {

    public:
    AccelController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class Accel : public Agent {
    public:
    Accel(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    AccelController c;
};

DECLARE_INTERFACE(Accel)

#endif