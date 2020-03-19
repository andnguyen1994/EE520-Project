#ifndef __MY_DUDE_AGENT__H
#define __MY_DUDE_AGENT__H 

#include "enviro.h"

using namespace enviro;

//Player controlled guy that can rotate, move, and shoot different projectiles.
class MyDudeController : public Process, public AgentInterface {

    public:
    MyDudeController() : Process(), AgentInterface(), boostCount(1), mineCount(0), magnitude(300), f(0), tau(0), firing(false), damage(0), bigCount(10), smallCount(25), bigReload(0), smallReload(0) {}

    //Sets up listeners for key events and establishes collisions with different agents
    void init() {
        watch("keydown", [&](Event &e) {
            if ( e.value()["client_id"] == get_client_id() ) {
                auto k = e.value()["key"].get<std::string>();
                if ( k == "k" && !firing && bigCount > 0) {
                    Agent& bullet = add_agent("BigBullet", 
                    x() + 80*cos(angle()), 
                    y() + 80*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    bullet.apply_force(40,0);
                    bigCount--;
                    firing = true;
                } else if (k == "j" && !firing && smallCount > 0) {
                    Agent& bullet = add_agent("SmallBullet", 
                    x() + 50*cos(angle()), 
                    y() + 50*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    bullet.apply_force(70,0);
                    smallCount--;
                    firing = true;
                } else if (k == "l" && !firing && mineCount > 0) {
                    Agent& bullet = add_agent("Mine", 
                    x() - 50*cos(angle()), 
                    y() - 50*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    mineCount--;
                    firing = true;
                } else if ( k == "w" ) {
                        f = magnitude;              
                } else if ( k == "s" ) {
                        f = -magnitude;  
                } else if ( k == "a" ) {
                        tau = -magnitude;
                } else if ( k == "d" ) {
                        tau = magnitude;
                }else if ( k == " " && boostCount > 0) {
                        apply_force(magnitude*20,tau);
                        boostCount--;
                }
            }
        });
        watch("keyup", [&](Event &e) {
            if ( e.value()["client_id"] == get_client_id() ) {
                auto k = e.value()["key"].get<std::string>();
                if ( k == "j" || k == "k" || k == "l" ) {
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

        notice_collisions_with("Mine", [&](Event &e) {
            int ID = e.value()["id"];
            Agent& b = find_agent(ID);
            omni_apply_force(-vx()*damage*20, -vy()*damage*20);
            damage += 20;
            remove_agent(ID);
        });

        notice_collisions_with("Wall", [&](Event &e){
            damage = 1;
            bigCount = 10;
            smallCount = 25;
            boostCount = 1;
            double x = rand() % 2 ? 500 : -500;
            double y = rand() % 2 ? 500 : -500;
            teleport(x,y,0);
        });

        notice_collisions_with("Drone", [&](Event &e){
            damage = 1;
            bigCount = 10;
            smallCount = 25;
            boostCount = 1;
            double x = rand() % 2 ? 500 : -500;
            double y = rand() % 2 ? 500 : -500;
            teleport(x,y,0);
        });

        watch("PU_"+std::to_string(id()), [&](Event& e){
            int t = e.value()["type"];
            switch (t) {
                case 0 :
                    smallCount = 25;
                    bigCount = 10;
                    break;
                case 1 :
                    magnitude += 100;
                    break;
                case 2 :
                    mineCount += 5;
                    break;
                case 3 :
                    boostCount += 2;
                    break;
                case 4:
                    damage = damage <= 10 ? 1 : damage - 10;
                    break;
            }
        });
    }
    void start() {}
    
    //Reloads the ammo on a timer and also handles movement.
    void update() {
        apply_force(f,tau);
        if(smallReload++ >= 10 && smallCount < 25) {
            smallCount++;
            smallReload = 0;
        }
        if(bigReload++ >= 30 && bigCount < 10){
            bigCount++;
            bigReload = 0;
        }
        label(std::to_string(bigCount), 0,0 );
    }
    void stop() {}

    int bigReload;
    int smallReload;
    double f, tau, magnitude;
    bool firing;
    int damage;
    int smallCount;
    int bigCount;
    int mineCount;
    int boostCount;
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