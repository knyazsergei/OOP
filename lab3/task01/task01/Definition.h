#pragma once
#include "stdafx.h"

enum class Transmission
{
	Reverse,
	Neutral,
	First,	
	Second,	
	Third,	
	Fourth,	
	Fifth	
};

enum class Direction
{
	Forward,
	Backward,
	Stand	
};


struct Border
{
	int bottomBound;
	int upperBound;	
};

struct CarInfo
{
	bool engineCondition;
	Direction dir;			
	int speed;			
	Transmission gear;	
};


// Speed range
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