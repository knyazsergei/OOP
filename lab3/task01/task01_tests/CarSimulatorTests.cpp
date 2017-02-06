#include "stdafx.h"
#include <boost/test/unit_test.hpp>
#include "../task01/Car.h"


BOOST_AUTO_TEST_SUITE(Car_full_test)
BOOST_AUTO_TEST_CASE(SetGear_failed_when_engine_offed)
{
	CCar UAZ;
	UAZ.SetGear(Transmission::First);
	BOOST_CHECK(UAZ.TurnOnEngine() != 0);
}

BOOST_AUTO_TEST_CASE(Engine_turn_off_failed_when_selected_not_neutral_gear)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	UAZ.SetGear(Transmission::First);
	BOOST_CHECK(UAZ.TurnOffEngine() != 0);
}

BOOST_AUTO_TEST_CASE(Failed_not_sequential_switching)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	BOOST_CHECK(!UAZ.SetGear(Transmission::Second));
}

BOOST_AUTO_TEST_CASE(Ñorrect_selection_of_the_first_gear)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	UAZ.SetGear(Transmission::First);
	UAZ.SetSpeed(25);
	BOOST_CHECK(UAZ.SetGear(Transmission::Second));
}

BOOST_AUTO_TEST_CASE(SetGear_failed_reverse_speed_speed_is_positive)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	UAZ.SetGear(Transmission::First);
	UAZ.SetSpeed(10);
	BOOST_CHECK(!UAZ.SetGear(Transmission::Reverse));
}

BOOST_AUTO_TEST_CASE(Normal_engine_shutdown)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	UAZ.SetGear(Transmission::Neutral);
	UAZ.SetSpeed(0);

	BOOST_CHECK(UAZ.TurnOffEngine());
}

BOOST_AUTO_TEST_CASE(Exceeding_the_maximum_speed_can_not_be)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	UAZ.SetGear(Transmission::First);
	UAZ.SetSpeed(30);
	UAZ.SetGear(Transmission::Third);
	UAZ.SetSpeed(50);
	UAZ.SetGear(Transmission::Fifth);
	UAZ.SetSpeed(150);

	BOOST_CHECK(!UAZ.SetSpeed(151));
}

BOOST_AUTO_TEST_SUITE_END()