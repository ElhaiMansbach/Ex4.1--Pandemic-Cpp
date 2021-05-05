#include "Scientist.hpp"

using namespace std;
using namespace pandemic;

Player &Scientist::discover_cure(Color color)
{
    if (!board.is_research_stations(current_city))
    {
        throw invalid_argument("Error!!!: There is no research station in the city");
    }
    if (board.get_cure(color) == true)
    {
        return *this;
    }
    int count = 0;
    for (auto e : cards)
    {
        if (board.city_color(e) == color)
        {
            count++;
        }
    }
    if (count < n)
    {
        throw invalid_argument("Error!!!: You don't have enough cards in the required color");
    }
    int stop = 0;
    for (auto i = cards.begin(); i != cards.end() && stop < n; ++i)
    {
        City c = *i;
        if (board.city_color(c) == color)
        {
            cards.erase(i);
            i--;
            stop++;
        }
    }
    board.cure[color] = true;
    return *this;
}