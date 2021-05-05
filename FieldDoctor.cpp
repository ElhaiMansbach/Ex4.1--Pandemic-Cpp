#include "FieldDoctor.hpp"

using namespace std;
using namespace pandemic;

Player &FieldDoctor::treat(City c)
{
    if (!board.Neighbors(current_city, c))
    {
        throw invalid_argument{"Error!!!: You are not in one of the neighboring cities"};
    }
    else if (board.get_disease_level(c) <= 0)
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