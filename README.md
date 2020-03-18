# EE520-Project

===

## Overview
This project is a multiplayer game that supports up to four players. The goal of the game is to push opponents into the perimeter of the map or into a chaser drone. Each player spawns with 10 big projectiles and 25 small projectiles each replenishing at a certain rate. Each type of projectile does a certain amount of damage and certain amount of knockback. The more damage a player has taken, the more knockback the projectiles will do. Players should navigate the arena and use the barriers strategically to push others and to protect against being pushed. Powerups will spawn at random locations on the map. 

===

## Instructions

1. Create a local version of this repository using the git clone command.
2. In terminal/command line, navigate to the folder with the repository.
3. In command line, assuming that docker is installed, type the following command:

```bash 
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.6 bash
``` 

4. Now type the following commands to start the app:

```bash
esm start
make
enviro
```

5. Each player should navigate to https://localhost in his/her web browser


### Controls
- W: Move forward
- S: Move backwards
- D: Rotate clockwise
- A: Rotate counter-clockwise

- J: Fire small projectile
- K: Fire big projectile
- L: Drop a mine

- Spacebar: Boost

### Powerups
- R: Reload big projectile to 10 and small projectile to 25
- A: Increase linear and rotational speed
- M: Add 5 Mines to arsenal
- B: Add a boost

===

## Issues and challenges
Intially each powerup was it's own agent type but I wanted to consolidate this into one. I had trouble finding a way to let agents access class variables of another. I ended up making the power up emit an event with the ID of the MyDude that bumped into it and "PU" and passed the type of powerup stored as an int. The MyDude agent has a listener for it's own ID_PU and handles the different type values.

## Sources
