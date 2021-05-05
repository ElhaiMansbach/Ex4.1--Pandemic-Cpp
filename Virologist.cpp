#include "Virologist.hpp"

using namespace std;
using namespace pandemic;

Player &Virologist::treat(City c)
{
    if (find(cards.begin(), cards.end(), c) == cards.end())
    {
        throw invalid_argument("Error!!!: You don't have the card of the desired city");
    }
    auto it = find(cards.begin(), cards.end(), c);
    int index = distance(cards.begin(), it);
    cards.erase(cards.begin() + index);

    if (board.get_disease_level(c) <= 0)
    {
        throw invalid_argument("Error!!!: There is no disease in the city");
    }
    else if (board.is_cure_discoverd(c) == true)
    {
        board.set_disease_level(c, 0);
    }
    else
    {
        int num = board.get_disease_level(c);
        num--;
        board.set_disease_level(c, num);
    }
    return *this;
}