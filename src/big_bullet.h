#ifndef __BIG_BULLET_AGENT__H
#define __BIG_BULLET_AGENT__H 

#include "enviro.h"

using namespace enviro;

//Large projectile that player can shoot. Does significant damage and knockback
class BigBulletController : public Process, public AgentInterface {

    public:
    BigBulletController() : Process(), AgentInterface(), counter(0) {}

    void init() {}
    void start() {}
    //stays in play for 30 cycles
    void update() {
        if ( counter++ > 30 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    int counter;

};

class BigBullet : public Agent {
    public:
    BigBullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BigBulletController c;
};

DECLARE_INTERFACE(BigBullet)

#endif