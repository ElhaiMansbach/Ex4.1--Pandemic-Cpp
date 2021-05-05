#include "Board.hpp"
#include <map>
#include <algorithm>

using namespace std;
using namespace pandemic;

Board::Board()
{
    int n = City::Algiers;
    while (n <= City::Washington)
    {
        this->disease_level.insert({(City)n, 0});
        n++;
    }

    this->cure = map<Color, bool> {
        {Color::Blue, false},
        {Color::Yellow, false},
        {Color::Black, false},
        {Color::Red, false}};
}

int &Board::operator[](const City c)
{
    return disease_level[c];
}

ostream &pandemic::operator<<(ostream &out, const Board &b)
{
    out << "Level of disease:" << endl;
    for (const auto &e : b.disease_level)
    {
        out << get_city(e.first) << ":\t" << e.second << endl;
    }
    out << "Cure discovered:" << endl;
    for (auto c : b.cure)
    {
        if (c.second)
        {
            out << color_string(c.first) << endl;
        }
    }
    out << "Research stations:" << endl;
    for (const auto &e : b.research_stations)
    {
        out << get_city(e) << endl;
    }
    return out;
}

bool Board::is_clean()
{
    for (auto &c : disease_level)
    {
        if (c.second > 0)
        {
            return false;
        }
    }
    return true;
}

void Board::remove_cures()
{
    this->cure = map<Color, bool> {
        {Color::Blue, false},
        {Color::Yellow, false},
        {Color::Black, false},
        {Color::Red, false}};
}

bool Board::Neighbors(City &c1, City &c2)
{
    if (count(Board::connections[c1].begin(), Board::connections[c1].end(), c2))
    {
        return true;
    }
    return false;
}

bool Board::is_research_stations(City c)
{
    if (count(research_stations.begin(), research_stations.end(), c))
    {
        return true;
    }
    return false;
}

bool Board::is_cure_discoverd(City c)
{
    return cure[city_color(c)];
}

Color Board::city_color(City c)
{
    return cities_colors.at(c);
}

int Board::get_disease_level(City c)
{
    return disease_level[c];
}

void Board::set_disease_level(City c, int num)
{
    disease_level[c] = num;
}

bool Board::get_cure(Color c)
{
    return cure[c];
}

map<City, vector<City>> Board::connections{
    {Algiers, {Madrid, Paris, Istanbul, Cairo}},
    {Atlanta, {Chicago, Miami, Washington}},
    {Baghdad, {Tehran, Istanbul, Cairo, Riyadh, Karachi}},
    {Bangkok, {Kolkata, Chennai, Jakarta, HoChiMinhCity, HongKong}},
    {Beijing, {Shanghai, Seoul}},
    {Bogota, {MexicoCity, Lima, Miami, SaoPaulo, BuenosAires}},
    {BuenosAires, {Bogota, SaoPaulo}},
    {Cairo, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh}},
    {Chennai, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta}},
    {Chicago, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal}},
    {Delhi, {Tehran, Karachi, Mumbai, Chennai, Kolkata}},
    {Essen, {London, Paris, Milan, StPetersburg}},
    {HoChiMinhCity, {Jakarta, Bangkok, HongKong, Manila}},
    {HongKong, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei}},
    {Istanbul, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow}},
    {Jakarta, {Chennai, Bangkok, HoChiMinhCity, Sydney}},
    {Johannesburg, {Kinshasa, Khartoum}},
    {Karachi, {Tehran, Baghdad, Riyadh, Mumbai, Delhi}},
    {Khartoum, {Cairo, Lagos, Kinshasa, Johannesburg}},
    {Kinshasa, {Lagos, Khartoum, Johannesburg}},
    {Kolkata, {Delhi, Chennai, Bangkok, HongKong}},
    {Lagos, {SaoPaulo, Khartoum, Kinshasa}},
    {Lima, {MexicoCity, Bogota, Santiago}},
    {London, {NewYork, Madrid, Essen, Paris}},
    {LosAngeles, {SanFrancisco, Chicago, MexicoCity, Sydney}},
    {Madrid, {London, NewYork, Paris, SaoPaulo, Algiers}},
    {Manila, {Taipei, SanFrancisco, HoChiMinhCity, Sydney}},
    {MexicoCity, {LosAngeles, Chicago, Miami, Lima, Bogota}},
    {Miami, {Atlanta, MexicoCity, Washington, Bogota}},
    {Milan, {Essen, Paris, Istanbul}},
    {Montreal, {Chicago, Washington, NewYork}},
    {Moscow, {StPetersburg, Istanbul, Tehran}},
    {Mumbai, {Karachi, Delhi, Chennai}},
    {NewYork, {Montreal, Washington, London, Madrid}},
    {Osaka, {Taipei, Tokyo}},
    {Paris, {Algiers, Essen, Madrid, Milan, London}},
    {Riyadh, {Baghdad, Cairo, Karachi}},
    {SanFrancisco, {LosAngeles, Chicago, Tokyo, Manila}},
    {Santiago, {Lima}},
    {SaoPaulo, {Bogota, BuenosAires, Lagos, Madrid}},
    {Seoul, {Beijing, Shanghai, Tokyo}},
    {Shanghai, {Beijing, HongKong, Taipei, Seoul, Tokyo}},
    {StPetersburg, {Essen, Istanbul, Moscow}},
    {Sydney, {Jakarta, Manila, LosAngeles}},
    {Taipei, {Shanghai, HongKong, Osaka, Manila}},
    {Tehran, {Baghdad, Moscow, Karachi, Delhi}},
    {Tokyo, {Seoul, Shanghai, Osaka, SanFrancisco}},
    {Washington, {Atlanta, NewYork, Montreal, Miami}}};

