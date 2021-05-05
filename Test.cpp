#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

using namespace pandemic;
using namespace std;

Board board;

TEST_CASE("Test board")
{
	CHECK(board.is_clean() == true);

	board[Algiers] = 1;
	board[Atlanta] = 2;
	board[Baghdad] = 1;
	board[Bangkok] = 3;
	board[Beijing] = 5;
	board[Bogota] = 4;
	board[BuenosAires] = 2;
	board[Cairo] = 1;
	board[Chennai] = 3;
	board[Chicago] = 1;
	board[Delhi] = 2;
	board[Essen] = 5;
	board[HoChiMinhCity] = 4;
	board[HongKong] = 1;
	board[Istanbul] = 3;
	board[Jakarta] = 2;
	board[Johannesburg] = 4;
	board[Karachi] = 4;
	board[KePasio] = 5;
	board[Khartoum] = 2;
	board[Kinshasa] = 3;
	board[Kolkata] = 1;

	CHECK(board[City::Algiers] == 1);
	CHECK(board[City::Atlanta] == 2);
	CHECK(board[City::Baghdad] == 1);
	CHECK(board[City::Bangkok] == 3);
	CHECK(board[City::Beijing] == 5);
	CHECK(board[City::Bogota] == 4);
	CHECK(board[City::BuenosAires] == 2);
	CHECK(board[City::Cairo] == 1);
	CHECK(board[City::Chennai] == 3);
	CHECK(board[City::Chicago] == 1);
	CHECK(board[City::Delhi] == 2);
	CHECK(board[City::Essen] == 5);
	CHECK(board[City::HoChiMinhCity] == 4);
	CHECK(board[City::HongKong] == 1);
	CHECK(board[City::Istanbul] == 3);
	CHECK(board[City::Jakarta] == 2);
	CHECK(board[City::Johannesburg] == 4);
	CHECK(board[City::Karachi] == 4);
	CHECK(board[City::KePasio] == 5);
	CHECK(board[City::Khartoum] == 2);
	CHECK(board[City::Kinshasa] == 3);
	CHECK(board[City::Kolkata] == 1);

	//Changes the level of the disease
	board[Algiers] = 2;
	board[Atlanta] = 1;
	board[Baghdad] = 3;
	board[Bangkok] = 4;
	board[Beijing] = 1;
	board[Bogota] = 2;
	board[BuenosAires] = 3;
	board[Cairo] = 0;
	board[Chennai] = 4;
	board[Chicago] = 6;
	board[Delhi] = 3;
	board[Essen] = 1;
	board[HoChiMinhCity] = 0;
	board[HongKong] = 2;
	board[Istanbul] = 4;
	board[Jakarta] = 1;
	board[Johannesburg] = 5;

	CHECK(board[City::Algiers] == 2);
	CHECK(board[City::Atlanta] == 1);
	CHECK(board[City::Baghdad] == 3);
	CHECK(board[City::Bangkok] == 4);
	CHECK(board[City::Beijing] == 1);
	CHECK(board[City::Bogota] == 2);
	CHECK(board[City::BuenosAires] == 3);
	CHECK(board[City::Cairo] == 0);
	CHECK(board[City::Chennai] == 4);
	CHECK(board[City::Chicago] == 6);
	CHECK(board[City::Delhi] == 3);
	CHECK(board[City::Essen] == 1);
	CHECK(board[City::HoChiMinhCity] == 0);
	CHECK(board[City::HongKong] == 2);
	CHECK(board[City::Istanbul] == 4);
	CHECK(board[City::Jakarta] == 1);
	CHECK(board[City::Johannesburg] == 5);

	CHECK(board.is_clean() == false);
}

TEST_CASE("Test OperationsExpert")
{
	OperationsExpert e{board, City::Algiers};
	CHECK_NOTHROW(e.drive(Madrid));
	CHECK_NOTHROW(e.drive(London));
	CHECK_NOTHROW(e.drive(NewYork));
	CHECK_NOTHROW(e.drive(Montreal));
	CHECK_NOTHROW(e.drive(Chicago));
	CHECK_NOTHROW(e.build());

	CHECK_THROWS(e.drive(Delhi));
	CHECK_THROWS(e.drive(Essen));
	CHECK_THROWS(e.drive(HoChiMinhCity));
	CHECK_THROWS(e.drive(Istanbul));
	CHECK_THROWS(e.drive(Bogota));

	e.take_card(City::Tokyo);
	CHECK_NOTHROW(e.fly_direct(City::Tokyo));
	CHECK_NOTHROW(e.drive(Seoul));
	CHECK_NOTHROW(e.drive(Shanghai));
	CHECK_NOTHROW(e.build());

	e.take_card(City::Shanghai);
	CHECK_NOTHROW(e.fly_charter(NewYork));
	CHECK_NOTHROW(e.drive(Montreal));
	CHECK_NOTHROW(e.drive(Washington));
	CHECK_NOTHROW(e.build());

	CHECK_NOTHROW(e.fly_shuttle(City::Shanghai));
	CHECK_NOTHROW(e.fly_shuttle(City::Chicago));
	CHECK_NOTHROW(e.fly_shuttle(City::Washington));

	CHECK_NOTHROW(e.drive(Atlanta));
	CHECK_THROWS(e.discover_cure(Color::Blue)); //There is no research station
	CHECK_NOTHROW(e.drive(Miami));
	CHECK_THROWS(e.discover_cure(Color::Yellow)); //There is no research station

	e.take_card(City::Miami);
	CHECK_NOTHROW(e.fly_charter(Algiers));
	CHECK_NOTHROW(e.treat(Algiers));
	CHECK(board[City::Algiers] == 1);
	CHECK_NOTHROW(e.drive(Cairo));
	CHECK_THROWS(e.treat(Cairo));
}

TEST_CASE("Test Dispatcher")
{
	Board board1;

	board[Algiers] = 4;
	board[Atlanta] = 3;
	board[Baghdad] = 2;
	board[Bangkok] = 1;
	board[Beijing] = 0;
	board[Bogota] = 1;
	board[BuenosAires] = 2;
	board[Cairo] = 3;
	board[Chennai] = 4;
	board[Chicago] = 5;

	CHECK(board[City::Algiers] == 4);
	CHECK(board[City::Atlanta] == 3);
	CHECK(board[City::Baghdad] == 2);
	CHECK(board[City::Bangkok] == 1);
	CHECK(board[City::Beijing] == 0);
	CHECK(board[City::Bogota] == 1);
	CHECK(board[City::BuenosAires] == 2);
	CHECK(board[City::Cairo] == 3);
	CHECK(board[City::Chennai] == 4);
	CHECK(board[City::Chicago] == 5);

	board[Algiers] = 1;
	board[Atlanta] = 1;
	board[Baghdad] = 1;
	board[Beijing] = 1;
	board[BuenosAires] = 1;
	board[Cairo] = 1;
	board[Chennai] = 1;
	board[Chicago] = 1;

	CHECK(board[City::Algiers] == 1);
	CHECK(board[City::Atlanta] == 1);
	CHECK(board[City::Baghdad] == 1);
	CHECK(board[City::Beijing] == 1);
	CHECK(board[City::BuenosAires] == 1);
	CHECK(board[City::Cairo] == 1);
	CHECK(board[City::Chennai] == 1);
	CHECK(board[City::Chicago] == 1);

	Dispatcher e1{board1, City::Algiers};
	CHECK_NOTHROW(e1.drive(Paris));
	CHECK_NOTHROW(e1.drive(Essen));
	CHECK_NOTHROW(e1.drive(StPetersburg));
	CHECK_THROWS(e1.build());
	e1.take_card(City::StPetersburg);
	CHECK_NOTHROW(e1.build());

	CHECK_NOTHROW(e1.drive(Moscow));
	CHECK_NOTHROW(e1.drive(Tehran));
	CHECK_NOTHROW(e1.drive(Delhi));
	e1.take_card(City::Delhi);
	CHECK_NOTHROW(e1.build());

	CHECK_NOTHROW(e1.fly_direct(City::Tokyo));
	e1.take_card(City::Tokyo);
	CHECK_NOTHROW(e1.fly_charter(NewYork));
	e1.take_card(City::NewYork);
	CHECK_NOTHROW(e1.build());
	CHECK_NOTHROW(e1.fly_shuttle(City::StPetersburg));
	CHECK_NOTHROW(e1.fly_shuttle(City::Delhi));
	CHECK_NOTHROW(e1.fly_shuttle(City::NewYork));
}

TEST_CASE("Test Scientist")
{
	Board board2;

	board2[Washington] = 4;
	board2[Tokyo] = 1;
	board2[Tehran] = 3;
	board2[Taipei] = 1;
	board2[Sydney] = 2;

	CHECK(board2[City::Washington] == 4);
	CHECK(board2[City::Tokyo] == 1);
	CHECK(board2[City::Tehran] == 3);
	CHECK(board2[City::Taipei] == 1);
	CHECK(board2[City::Sydney] == 2);

	Scientist e2{board2, City::Washington, 4};
	e2.take_card(City::Washington);
	CHECK_NOTHROW(e2.build());
	CHECK_THROWS(e2.discover_cure(Color::Blue));
	CHECK_NOTHROW(e2.drive(Montreal));
	CHECK_NOTHROW(e2.drive(NewYork));
	CHECK_NOTHROW(e2.drive(London));

	e2.take_card(City::Tokyo);
	CHECK_NOTHROW(e2.fly_direct(City::Tokyo));
	CHECK_NOTHROW(e2.drive(Shanghai));
	e2.take_card(City::Shanghai);
	CHECK_NOTHROW(e2.fly_charter(NewYork));
}

TEST_CASE("Test Researcher")
{
	Board board3;

	board3[Washington] = 1;
	board3[Tokyo] = 1;
	board3[Tehran] = 2;
	board3[Taipei] = 1;
	board3[Sydney] = 2;

	CHECK(board3[City::Washington] == 1);
	CHECK(board3[City::Tokyo] == 1);
	CHECK(board3[City::Tehran] == 2);
	CHECK(board3[City::Taipei] == 1);
	CHECK(board3[City::Sydney] == 2);

	Researcher e3{board3, City::Washington};
	CHECK_NOTHROW(e3.drive(Montreal));
	CHECK_NOTHROW(e3.drive(NewYork));
	CHECK_NOTHROW(e3.drive(London));
	e3.take_card(City::Tokyo);

	CHECK_NOTHROW(e3.fly_direct(City::Tokyo));
	CHECK_NOTHROW(e3.drive(Seoul));
	CHECK_NOTHROW(e3.drive(Beijing));
}
