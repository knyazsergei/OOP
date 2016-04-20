#include "stdafx.h"
#include "Car.h"
#include <iostream>

CCar::CCar()
	: m_engineLaunched(false)
	, m_direction(Direction::Stand)
	, m_gear(Transmission::Neutral)
	, m_speed(0)
{
}


InfoAboutCar CCar::GetInfo() const
{
	InfoAboutCar indicators;
	indicators.conditionEngine = m_engineLaunched;
	indicators.dir = m_direction;
	indicators.gear = m_gear;
	indicators.speed = m_speed;
	return indicators;
}

void CCar::SetDirection()
{
	if (m_gear == Transmission::Reverse && m_speed > 0)
	{
		m_direction = Direction::Backward;
	}
	else if (m_gear != Transmission::Neutral && m_speed > 0)
	{
		m_direction = Direction::Forward;
	}
	else if (m_speed == 0)
	{
		m_direction = Direction::Stand;
	}
}

bool CCar::CheckBound(const Transmission & value, const Border & rangeValues)
{
	int intValue = static_cast<int>(value);
	return CheckBound(intValue, rangeValues);
}

bool CCar::CheckBound(const int & value, const Border & rangeValues)
{
	return (value >= rangeValues.bottomBound && value <= rangeValues.upperBound);
}

bool CCar::TurnOnEngine()
{
	if (!m_engineLaunched)
	{
		m_engineLaunched = true;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_engineLaunched)
	{
		m_engineLaunched = false;
		return true;
	}
	return false;
}

bool CCar::SetGear(const Transmission & gear)
{
	if ((gear == Transmission::Reverse && m_direction != Direction::Forward)||
	    (gear != Transmission::Reverse && m_direction != Direction::Backward)||
		(CheckBound(gear, GEAR_RANGE))||
		(CheckBound(m_speed, SPEED_RANGE.at(gear))))
	{
		m_gear = gear;
	}
	return false;
}

bool CCar::SetSpeed(const int & speed)
{
	if ((m_engineLaunched) &&
		!(m_gear == Transmission::Neutral && speed > m_speed) &&
		!CheckBound(speed, SPEED_RANGE.at(m_gear)))
	{
		m_speed = speed;
		SetDirection();
		return true;
	}
	return false;
}