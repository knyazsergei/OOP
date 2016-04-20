#pragma once
#include "stdafx.h"

enum class Transmission
{
	Reverse,	// задн€€
	Neutral,	// нейтральна€
	First,		// перва€
	Second,		// втора€
	Third,		// треть€
	Fourth,		// четверта€
	Fifth		// п€та€
};

enum class Direction
{
	Forward,	// вперед
	Backward,	// назад
	Stand		// стоим
};

enum class WasErrorEngineOff
{
	EngineOff,				// двигатель выключен
	EngineWasOff,			// двигатель уже выключен
	EngineNotOffWithGear,	// двигатель не может быть выключен, т.к. включена передача 
	EngineNotOffWithSpeed	// двигатель не может быть выключен, т.к. скорость не нулева€

};

enum class WasErrorSetGear
{
	GearOn,						// передача включена
	GearNotOnReverse,			// задн€€ передача не включена
	GearNotOnWithReverseSpeed,	// положительна€ передача не может быть включена
	GearNot,					// нет такой передачи
	GearNotOnWithSpeed			// скорость не соответсвует диапазону
};

enum class WasErrorSetSpeed
{
	SpeedOn,						// скорость установлена
	SpeedNotWithEngine,				// скорость не установлена, из-за не включенного двигател€
	SpeedNotAddWithNeutralGear,		// скорость не удалось повысить, т.к. установлена нейтральна€ передача
	SpeedNotRange					// скорость не в диапазоне
};

struct Border
{
	int bottomBound;	// нижн€€ граница
	int upperBound;		// верхн€€ граница
};

struct InfoAboutCar
{
	bool conditionEngine;	// состо€ние двигател€
	Direction dir;			// направление
	int speed;				// скорость
	Transmission gear;		// передача
};


// ƒ»јѕј«ќЌ — ќ–ќ—“≈…
static const Border REVERSE_GEAR_SPEED = { 0, 20 };
static const Border FIRST_GEAR_SPEED = { 0, 30 };
static const Border SECOND_GEAR_SPEED = { 20, 50 };
static const Border THIRD_GEAR_SPEED = { 30, 60 };
static const Border FOURTH_GEAR_SPEED = { 40, 90 };
static const Border FIFTH_GEAR_SPEED = { 50, 150 };
static const Border NEUTRAL_GEAR_SPEED = { 0, FIFTH_GEAR_SPEED.upperBound };

static const Border GEAR_RANGE = { -1, 5 };

static const std::map<Transmission, Border> SPEED_RANGE =
{
	{ Transmission::Reverse, REVERSE_GEAR_SPEED },
	{ Transmission::Neutral, NEUTRAL_GEAR_SPEED },
	{ Transmission::First, FIRST_GEAR_SPEED },
	{ Transmission::Second, SECOND_GEAR_SPEED },
	{ Transmission::Third, THIRD_GEAR_SPEED },
	{ Transmission::Fourth, FOURTH_GEAR_SPEED },
	{ Transmission::Fifth, FIFTH_GEAR_SPEED }
};

const std::map<Direction, std::string> DIRECTION_NAME =
{
	{ Direction::Forward, "forward" },
	{ Direction::Backward, "backward" },
	{ Direction::Stand, "stand in place" }
};