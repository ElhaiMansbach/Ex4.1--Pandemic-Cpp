#pragma once
#include "City.hpp"
#include "Color.hpp"
#include <map>
#include <iostream>
#include <vector>

namespace pandemic
{
    class Board
    {
    public:
        static std::map<City, std::vector<City>> connections;
        std::map<City, int> disease_level;
        std::vector<City> research_stations;
        std::map<Color, bool> cure;

        //public:
        Board();

        int &operator[](const City c);
        friend std::ostream &operator<<(std::ostream &out, const Board &board);
        bool is_clean();
        void remove_cures();

        bool Neighbors(City &c1, City &c2);
        bool is_research_stations(City c);
        bool is_cure_discoverd(City c);
        Color city_color(City c);
        int get_disease_level(City c);
        void set_disease_level(City c, int num);
        bool get_cure(Color c);
        //void set_cure(Color c, bool b);
    };
}