#include "stdafx.h"
#include <boost/test/unit_test.hpp>
#include "..\task01\Car.h"


BOOST_AUTO_TEST_SUITE(Go_Ride)
BOOST_AUTO_TEST_CASE(EngineOnFailed)
{
	CCar Lancer;
	Lancer.SetGear(1);
	BOOST_CHECK(Lancer.TurnOnEngine() != 0);
}

BOOST_AUTO_TEST_CASE(EngineOffFailed)
{
	CCar Lancer;
	Lancer.TurnOnEngine();
	Lancer.SetGear(1);
	BOOST_CHECK(Lancer.TurnOffEngine() != 0);
}

BOOST_AUTO_TEST_CASE(SetGear_HigherSpeedRange_Failed)
{
	CCar Lancer;
	Lancer.TurnOnEngine();
	BOOST_CHECK(Lancer.SetGear(2) != 0);
}

BOOST_AUTO_TEST_CASE(SetGearComplete)
{
	CCar Lancer;
	Lancer.TurnOnEngine();
	Lancer.SetGear(1);
	Lancer.SetSpeed(25);
	BOOST_CHECK(Lancer.SetGear(2) == 0);
}

BOOST_AUTO_TEST_CASE(SetGear_ReverseGear_Failed)
{
	CCar Lancer;
	Lancer.TurnOnEngine();
	Lancer.SetGear(1);
	Lancer.SetSpeed(10);
	BOOST_CHECK(Lancer.SetGear(-1) != 0);
}

BOOST_AUTO_TEST_CASE(EngineOff_Complete)
{
	CCar Lancer;
	Lancer.TurnOnEngine();
	Lancer.SetGear(0);
	Lancer.SetSpeed(0);

	BOOST_CHECK(Lancer.TurnOffEngine() == 0);
}

BOOST_AUTO_TEST_CASE(SetMaxSpeed)
{
	CCar Lancer;
	Lancer.TurnOnEngine();
	Lancer.SetGear(1);
	Lancer.SetSpeed(30);
	Lancer.SetGear(3);
	Lancer.SetSpeed(50);
	Lancer.SetGear(5);
	Lancer.SetSpeed(150);

	BOOST_CHECK(Lancer.SetSpeed(151) != 0 && Lancer.GetInfo().speed == 150);
}

BOOST_AUTO_TEST_CASE(SetMaxGear)
{
	CCar Lancer;
	Lancer.TurnOnEngine();
	Lancer.SetGear(1);
	Lancer.SetSpeed(30);
	Lancer.SetGear(3);
	Lancer.SetSpeed(50);
	Lancer.SetGear(5);
	Lancer.SetSpeed(150);

	BOOST_CHECK(Lancer.SetGear(6) != 0 && Lancer.GetInfo().gear == 5);
}

BOOST_AUTO_TEST_SUITE_END()