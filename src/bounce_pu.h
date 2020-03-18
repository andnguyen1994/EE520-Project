#ifndef __BOUNCE_PU_AGENT__H
#define __BOUNCE_PU_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BouncePUController : public Process, public AgentInterface {

    public:
    BouncePUController() : Process(), AgentInterface() {}

    void init() {
        label("B", -5, 5 );
    }
    void start() {}
    void update() {}
    void stop() {}

};

class BouncePU : public Agent {
    public:
    BouncePU(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BouncePUController c;
};

DECLARE_INTERFACE(BouncePU)

#endif