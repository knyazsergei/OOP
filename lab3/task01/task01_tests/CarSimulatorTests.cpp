#include "stdafx.h"
#include <boost/test/unit_test.hpp>
#include "../task01/Car.h"


BOOST_AUTO_TEST_SUITE(Car_full_test)
BOOST_AUTO_TEST_CASE(EngineOnFailed)
{
	CCar UAZ;
	UAZ.SetGear(Transmission::First);
	BOOST_CHECK(UAZ.TurnOnEngine() != 0);
}

BOOST_AUTO_TEST_CASE(EngineOffFailed)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	UAZ.SetGear(Transmission::First);
	BOOST_CHECK(UAZ.TurnOffEngine() != 0);
}

BOOST_AUTO_TEST_CASE(SetGear_HigherSpeedRange_Failed)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	BOOST_CHECK(!UAZ.SetGear(Transmission::Second));
}

BOOST_AUTO_TEST_CASE(SetGearComplete)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	UAZ.SetGear(Transmission::First);
	UAZ.SetSpeed(25);
	BOOST_CHECK(UAZ.SetGear(Transmission::Second) == 0);
}

BOOST_AUTO_TEST_CASE(SetGear_ReverseGear_Failed)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	UAZ.SetGear(Transmission::First);
	UAZ.SetSpeed(10);
	BOOST_CHECK(!UAZ.SetGear(Transmission::Reverse));
}

BOOST_AUTO_TEST_CASE(EngineOff_Complete)
{
	CCar UAZ;
	UAZ.TurnOnEngine();
	UAZ.SetGear(Transmission::Neutral);
	UAZ.SetSpeed(0);

	BOOST_CHECK(UAZ.TurnOffEngine());
}

BOOST_AUTO_TEST_CASE(SetMaxSpeed)
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