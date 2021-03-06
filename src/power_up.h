#ifndef __POWER_UP_AGENT__H
#define __POWER_UP_AGENT__H 

#include "enviro.h"

using namespace enviro;

//Powerup object that players can pick up. Provides either movespeed, boosts, mines, reload, or heals
class PowerUpController : public Process, public AgentInterface {

    public:
    PowerUpController() : Process(), AgentInterface(), type(0) {}

    //upon creation, chooses a random type of powerup and on collision, alerts dude to what type of powerup to handle
    void init() {
        type = rand() % 5;
        label(powerups[type], -5, 5);
        notice_collisions_with("MyDude", [&](Event &e) {
            int ID = e.value()["id"];
            string eventID = "PU_" + std::to_string(ID);
            json j;
            j["type"] = type;
            emit(Event(eventID, j));
            remove_agent(id());
        });
    }
    void start() {}
    void update() {}
    void stop() {}

    int type; 
    std::vector<string> const powerups = {"R", "A", "M", "B", "H"};

};

class PowerUp : public Agent {
    public:
    PowerUp(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    PowerUpController c;
};

DECLARE_INTERFACE(PowerUp)

#endif