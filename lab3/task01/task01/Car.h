#pragma once
#include "stdafx.h"
#include "Definition.h"

class CCar
{
public:
	CCar();

	CarInfo GetInfo() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(const Transmission & gear);
	bool SetSpeed(const int & speed);

private:
	int	m_speed;
	Transmission m_gear;
	bool m_engineLaunched;
	Direction m_direction;

	bool CheckBound(const Transmission & value, const Border & rangeValues)const;
	bool CheckBound(const int & value, const Border & rangeValues)const;

	void SetDirection();
};

