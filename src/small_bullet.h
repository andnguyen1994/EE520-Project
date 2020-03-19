#ifndef __SMALL_BULLET_AGENT__H
#define __SMALL_BULLET_AGENT__H 

#include "enviro.h"

using namespace enviro;

//small projectile that deals moderate damage and knockback
class SmallBulletController : public Process, public AgentInterface {

    public:
    SmallBulletController() : Process(), AgentInterface(), counter(0) {}

    //disappears if collision with wall, barrier, or big bullet
    void init() {
        notice_collisions_with("Wall", [&](Event &e) {
            remove_agent(id());
        });
        notice_collisions_with("Barrier", [&](Event &e) {
            remove_agent(id());
        });
        notice_collisions_with("BigBullet", [&](Event &e) {
            remove_agent(id());
        });
        notice_collisions_with("Drone", [&](Event &e) {
            remove_agent(id());
        });
    }
    void start() {}
    void update() {
        if ( counter++ > 20 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    int counter;

};

class SmallBullet : public Agent {
    public:
    SmallBullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    SmallBulletController c;
};

DECLARE_INTERFACE(SmallBullet)

#endif