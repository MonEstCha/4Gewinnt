// player.h
#ifndef AI_H // include guard
#define AI_H

#include "fourwins_field.h"

/**class player 
{
public:
    // player(int id);
private:
    int player_id;
};*/

class ai
{
public:
    static ai* create_ai(int depth);
    int depth_of_recursion;
private:
    ai(int depth); // calls the constructor ai(int depth);
    static ai* ai_instance;
};
    
class hi
{
public:
    static hi* create_hi(); // calls the constructor hi();
private:
    hi();
    static hi* hi_instance;
};
    

#endif /* AI_H */
