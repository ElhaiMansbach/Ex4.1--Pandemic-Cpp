#include "Player.hpp"

using namespace pandemic;
using namespace std;

Player &Player::drive(City c)
{
    if (!board.Neighbors(current_city, c))
    {
        throw invalid_argument("Error!!!: There is no direct transition between these countries");
    }
    current_city = c;
    return *this;
}

Player &Player::fly_direct(City c)
{
    auto it = find(cards.begin(), cards.end(), c);

    if (find(cards.begin(), cards.end(), c) == cards.end())
    {
        throw invalid_argument("Error!!!: You do not have the card of the desired city");
    }
    int index = distance(cards.begin(), it);
    cards.erase(cards.begin() + index);
    current_city = c;
    return *this;
}

Player &Player::fly_charter(City c)
{
    auto it = find(cards.begin(), cards.end(), current_city);

    if (find(cards.begin(), cards.end(), current_city) == cards.end())
    {
        throw invalid_argument("Error!!!: You don't have the card of the desired city");
    }
    int index = distance(cards.begin(), it);
    cards.erase(cards.begin() + index);
    current_city = c;
    return *this;
}

Player &Player::fly_shuttle(City c)
{
    if (!board.is_research_stations(current_city) || !board.is_research_stations(c))
    {
        throw invalid_argument("Error!!!:There are no research stations in at least one of them");
    }
    current_city = c;
    return *this;
}

Player &Player::build()
{
    if (board.is_research_stations(current_city))
    {
        return *this;
    }
    else if (count(cards.begin(), cards.end(), current_city) == 0)
    {
        throw invalid_argument("Error!!!: You do not have the card to build");
    }
    else
    {
        auto it = find(cards.begin(), cards.end(), current_city);
        if (it != cards.end())
        {
            cards.erase(it);
        }
        board.research_stations.push_back(current_city);
    }
    return *this;
}

Player &Player::discover_cure(Color color)
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
    if (count < 5)
    {
        throw invalid_argument("Error!!!: You don't have enough cards in the required color");
    }
    int stop = 0;
    for (auto i = cards.begin(); i != cards.end() && stop < 4; ++i)
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

Player &Player::treat(City c)
{
    if (current_city != c)
    {
        throw invalid_argument{"Error!!!: You are not in the city " + get_city(c)};
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

string Player::role()
{
    return player_role;
}

Player &Player::take_card(City c)
{
    if (count(cards.begin(), cards.end(), c))
    {
        return *this;
    }
    cards.push_back(c);
    return *this;
}