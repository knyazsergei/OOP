#include "stdafx.h"
#include "Driver.h"
#include <sstream>

void parseCommand(const std::string & commandStr, CCar & car)
{
	std::istringstream command(commandStr);
	std::string firstArg;
	command >> firstArg;
	if (firstArg == "Info")
	{
		PrintInfoAboutCar(car.GetInfo());
	}
	else if (firstArg == "EngineOn")
	{
		PrintResultEngineOnCommand(car.TurnOnEngine());
	}
	else if (firstArg == "EngineOff")
	{
		//PrintResultEngineOffCommand(car.TurnOffEngine());
	}
	else if (firstArg == "SetGear")
	{
		std::string secondArg;
		command >> secondArg;
		//PrintResultSetGearCommand(car.SetGear(static_cast<Transmission>(std::atoi(strValue.c_str()))));
	}
	else if (firstArg == "SetSpeed")
	{
		std::string secondArg;
		command >> secondArg;
		//PrintResultSetSpeedCommand(car.SetSpeed(std::atoi(strValue.c_str())));
	}
	else
	{
		PrintHelp();
	}
}

int main()
{
	CCar car;
	std::string line;
	while (getline(std::cin, line), line != "")
	{
		parseCommand(line, car);
	}
	return 0;
}

