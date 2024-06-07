/* Collin Tran
 * ctt200001
 */
#include "Game.h"

//checks to see if a game is exactly the same as another
bool Game::equal(Game g){
    if(name == g.name && highscore == g.highscore && initials == g.initials && plays == g.plays){
        return true;
    }
    else {
        return false;
    }
}

//function checks to see if a game's name comes before specified term
bool Game::operator<(std::string term){
    //if so, returns true
    if(name < term){
        return true;
    }
    //otherwise, return false
    else {
        return false;
    }
}

//function checks to see if a game's name comes after specified term
bool Game::operator>(std::string term){
    //if so, return true
    if(name > term){
        return true;
    }
    //otherwise, returns false
    else {
        return false;
    }
}

//checks to see if a game's name contains a specified term
bool Game::operator==(std::string term){
    //if so, returns true
    if(name.find(term) != std::string::npos){
        return true;
    }
    //otherwise, returns false
    else {
        return false;
    }
}


/* The function prints the information of a specified game
 * The highscore, initials, plays, and revenue of the game are printed
 * Note that the name of the game isn't printed, other functions must do that themselves
 * The game's revenue is rounded to two decimal places
 * The functions returns an ostream
 */
std::ostream& operator<<(std::ostream &out, const Game &g) {
    out << "High Score: " << g.highscore << std::endl;
    out << "Initials: " << g.initials << std::endl;
    out << "Plays: " << g.plays << std::endl;
    out << std::setprecision(2) << std::fixed << "Revenue: $" << g.plays * 0.25 << std::endl;
    return out;
}
/* The functions checks if one game is "less" than another
 * Comparisons are made based on the name of the games and the string class
 * The string class determines the comparison
 * If this game's name comes before g's name, the function returns true
 * Otherwise, the function return false; this is also the case for duplicates
 */
bool Game::operator<(Game g) {
    //if this game's name comes before g's name, return true
    if(name < g.name) {
        return true;
    }
    //else return false
    else {
        return false;
    }
}

/* The functions checks if one game is "greater" than another
 * Comparisons are made based on the name of the games
 * The string class determines the comparison
 * If this game's name comes after g's name, the function returns true
 * Otherwise, the function return false; this is also the case for duplicates
 */
bool Game::operator>(Game g) {
    //if this game's name comes after g's name, return true
    if(name > g.name) {
        return true;
    }
    //else return false
    else {
        return false;
    }
}