#pragma once
#include "stdafx.h"
#include "Definition.h"

class CCar
{
public:
	CCar();

	InfoAboutCar GetInfo() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(const Transmission & gear);
	bool SetSpeed(const int & speed);

private:
	int	m_speed;
	Transmission m_gear;
	bool m_engineLaunched;
	Direction m_direction;

	bool CheckBound(const Transmission & value, const Border & rangeValues);
	bool CheckBound(const int & value, const Border & rangeValues);

	void SetDirection();
};

