#ifndef __MY_DUDE_AGENT__H
#define __MY_DUDE_AGENT__H 

#include "enviro.h"

using namespace enviro;

class MyDudeController : public Process, public AgentInterface {

    public:
    MyDudeController() : Process(), AgentInterface(), f(0), tau(0), firing(false), damage(0), bigCount(10), smallCount(25) {}

    void init() {
        watch("keydown", [&](Event &e) {
            if ( e.value()["client_id"] == get_client_id() ) {
                auto k = e.value()["key"].get<std::string>();
                if ( k == "f" && !firing ) {
                    Agent& bullet = add_agent("BigBullet", 
                    x() + 80*cos(angle()), 
                    y() + 80*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    bullet.apply_force(40,0);
                    firing = true;
                } else if (k == " " && !firing) {
                    Agent& bullet = add_agent("SmallBullet", 
                    x() + 50*cos(angle()), 
                    y() + 50*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    bullet.apply_force(50,0);
                    std::cout<<"hello \n";
                    firing = true;
                }else if ( k == "w" ) {
                        f = magnitude;              
                } else if ( k == "s" ) {
                        f = -magnitude;  
                } else if ( k == "a" ) {
                        tau = -magnitude;
                } else if ( k == "d" ) {
                        tau = magnitude;
                }
            }
        });
        watch("keyup", [&](Event &e) {
            if ( e.value()["client_id"] == get_client_id() ) {
                auto k = e.value()["key"].get<std::string>();
                if ( k == " " || k == "f" ) {
                    firing = false;
                } else if ( k == "w" || k == "s" ) {
                    f = 0;               
                } else if ( k == "a" ) {
                    tau = 0;
                } else if ( k == "d" ) {
                    tau = 0;
                } 
            }
        });
        notice_collisions_with("BigBullet", [&](Event &e) {
            int ID = e.value()["id"];
            Agent& b = find_agent(ID);
            std::cout<<"hello \n";
            omni_apply_force(b.vx()*5*damage, b.vy()*5*damage);
            damage += 6;
            remove_agent(ID);
        });

        notice_collisions_with("SmallBullet", [&](Event &e) {
            int ID = e.value()["id"];
            Agent& b = find_agent(ID);
            omni_apply_force(b.vx()*damage, b.vy()*damage);
            damage += 2;
            remove_agent(ID);
        });

        notice_collisions_with("wall", [&](Event &e){
            damage = 1;
            //teleport
        });
    }
    void start() {}
    void update() {
        apply_force(f,tau);
        }
    void stop() {}

    double f, tau;
    double const magnitude = 200;
    bool firing;
    int damage;
    int smallCount;
    int bigCount;
    int ricCount;
    const json BULLET_STYLE = { 
                   {"fill", "black"}, 
                   {"stroke", "#888"}, 
               };



};

class MyDude : public Agent {
    public:
    MyDude(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    MyDudeController c;
};

DECLARE_INTERFACE(MyDude)

#endif