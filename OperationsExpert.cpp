#include "OperationsExpert.hpp"

using namespace std;
using namespace pandemic;

Player &OperationsExpert::build()
{
    if (board.is_research_stations(current_city))
    {
        return *this;
    }
    board.research_stations.push_back(current_city);
    return *this;
}