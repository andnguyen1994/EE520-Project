#ifndef __SYSTEM_CONTROLLER_AGENT__H
#define __SYSTEM_CONTROLLER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class SystemControllerController : public Process, public AgentInterface {

    public:
    SystemControllerController() : Process(), AgentInterface(), color({"blue","green","yellow", "orange"}),x({500,500,-500,-500}), y({500,-500, 500, -500}) {}

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
    void update() {}
    void stop() {}

    std::vector<int> x;
    std::vector<int> y;
    std::vector<string> color;
    int count;
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