/* Collin Tran
 * ctt200001
 */
#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <iomanip>

class Game {
    public:
        //default constructor
        Game() {
            name = "";
            highscore = 0;
            initials = "";
            plays = 0;
        }
        //overloaded constructor: sets values of name, highscore,
        //initials and plays to specified values
        Game(std::string n, int h, std::string i, int p){
            name = n;
            highscore = h;
            initials = i;
            plays = p;
        }
        //checks to see if name has a match for term
        bool operator==(std::string term);
        //checks to see if a game's name comes before another
        bool operator<(Game g);
        //checks to see if a game's name comes after another
        bool operator>(Game g);
        //checks to see if a game's name comes before specified term
        bool operator<(std::string term);
        //checks to see if a game's name comes after specified term
        bool operator>(std::string term);
        //checks to see if a game is exactly the same as another
        bool equal(Game g);
        //prints game information
        friend std::ostream& operator<<(std::ostream &out, const Game &g);
        
        //game variables
        std::string name;
        int highscore;
        std::string initials;
        int plays;
};
#endif