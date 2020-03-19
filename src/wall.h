#ifndef __WALL_AGENT__H
#define __WALL_AGENT__H 

#include "enviro.h"

using namespace enviro;

//Static element that encompasses map. Players lose when they hit the wall
class WallController : public Process, public AgentInterface {

    public:
    WallController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class Wall : public Agent {
    public:
    Wall(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    WallController c;
};

DECLARE_INTERFACE(Wall)

#endif