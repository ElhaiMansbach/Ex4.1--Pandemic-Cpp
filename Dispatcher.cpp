#include "Dispatcher.hpp"

using namespace std;
using namespace pandemic;

Player &Dispatcher::fly_direct(City c)
{
    if (board.is_research_stations(current_city))
    {
        current_city = c;
        return *this;
    }
    else
    {
        return Player::fly_direct(c);
    }
}