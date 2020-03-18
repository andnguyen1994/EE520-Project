#ifndef __SYSTEM_CONTROLLER_AGENT__H
#define __SYSTEM_CONTROLLER_AGENT__H 

#include "enviro.h"

using namespace enviro;

//TODO: Add ready button?
class SystemControllerController : public Process, public AgentInterface {

    public:
    SystemControllerController() : Process(), AgentInterface(), timer(0){}

    void init() {
        watch("connection", [&](Event e) {
            if ( ! e.value()["client_id"].is_null() ) {
                std::cout << "Connection from " << e.value() << "\n";
                Agent& a = add_agent("MyDude", x[count%4], y[count%4], 0, {{"fill",color[count%4]},{"stroke","black"}});
                a.set_client_id(e.value()["client_id"]);
                count++;
            }
        });
    }
    void start() {}
    void update() {
        if(timer++ >= 200){
            int rx = rand() % 500;
            int ry = rand() % 500;
            rx = rand() % 2 ? -rx : rx;
            ry = rand() % 2 ? -ry : ry;
            add_agent("PowerUp", rx, ry, 0, {{"fill","violet",{"stroke","black"}}});
            timer = 0;
        }
    }
    void stop() {}

    std::vector<int> const x = {500,-500,-500,500};
    std::vector<int> const y = {500,-500, 500, -500};
    std::vector<string> const color = {"blue","green","yellow", "orange"};
    int count;
    int timer;
};

class SystemController : public Agent {
    public:
    SystemController(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    SystemControllerController c;
};

DECLARE_INTERFACE(SystemController)

#endif