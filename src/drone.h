#ifndef __DRONE_AGENT__H
#define __DRONE_AGENT__H 

#include "enviro.h"

using namespace enviro;

//Default drone state. Drone will rotate until it detects a dude
class Searching : public State, public AgentInterface{
    public:
        Searching() : State("Searching") {}
    private:
    void entry(const Event& e) {
        rotate = rand()%2 ? 1 : -1;
    }
    //if a dude is found, changes state to Found
    void during() { 
        apply_force(0,200*rotate);
        if(sensor_reflection_type(0) == "MyDude"){  
            emit(Event(AgentInterface::id()+"FOUND"));
        }
    }
    void exit(const Event& e) {}

    int rotate;
};

//Drone State. Drone will move towards the found dude
class Found : public State, public AgentInterface{
    public:
    Found() : State("Found"), count(0), speedA(50), speedL(100) {}
    private:
    void entry(const Event& e) {
        a = x()+sensor_value(0)*cos(angle());
        b = y()-sensor_value(0)*sin(angle());
    }
    //using the 3 sensors, moves towards the dude and once it goes to target location, goes to default
    void during() { 
        double minDist = 10000;
        double ang = 0;
        if(sensor_reflection_type(0) == "MyDude"){
            minDist = sensor_value(0);
        }
        if(sensor_reflection_type(1) == "MyDude" && sensor_value(1) < minDist){
            ang = 0.324;
            minDist = sensor_value(1);
        }
        if(sensor_reflection_type(2) == "MyDude" && sensor_value(2) < minDist){
            ang = -0.324;
            minDist = sensor_value(2);
        }
        if(minDist != 10000){
            a = x()+minDist*cos(angle()+ang);
            b = y()+minDist*sin(angle()+ang);    
        }
        move_toward(a,b,speedL,speedA);
        if(abs(x() - a) <=5  && abs(y() - b)<=5 || sensor_value(0) <= 15){
            emit(Event(AgentInterface::id()+"SEARCH"));
        }
        if(count++ >= 300){
            speedL += 30;
            speedA += 10;
            count = 0;
            std::cout<<speedL << speedA << "\n";
        }
    }
    void exit(const Event& e) {}

    double a,b;
    int count, speedA, speedL;
};

//Drone that follows users and will cause the player to lose a life if there is a collision
class DroneController : public StateMachine, public AgentInterface {

    public:
    DroneController() : StateMachine(){
        StateMachine::set_initial(searching);
        StateMachine::add_transition("FOUND", searching, found);
    }

    void init() {
        StateMachine::add_transition(AgentInterface::id()+"FOUND", searching, found);
        StateMachine::add_transition(AgentInterface::id()+"SEARCH", found, searching);
        StateMachine::init();
    }

    Searching searching;
    Found found;

};

class Drone : public Agent {
    public:
    Drone(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    DroneController c;
};

DECLARE_INTERFACE(Drone)

#endif