#include "stdafx.h"
#include "Definition.h"
#include "Car.h"
#include <sstream>

void PrintHelp()
{
	std::cout << "Info - show car information" << std::endl;
	std::cout << "EngineOn - switch on engine" << std::endl;
	std::cout << "EngineOff - switch off engine" << std::endl;
	std::cout << "SetGear <value> - set gear value" << std::endl;
	std::cout << "SetSpeed <value> - set speed value" << std::endl;
}

bool parseCommand(const std::string & commandStr, CCar & car)
{
	std::istringstream command(commandStr);
	std::string firstArg;
	command >> firstArg;

	if (firstArg == "Info")
	{
		auto info = car.GetInfo();
		std::cout << "Engine is " << (info.conditionEngine ? "working" : "offen") << std::endl
			<< "Diraction: " << static_cast<int>(info.dir) << std::endl
			<< "Gear: " << static_cast<int>(info.gear) << std::endl
			<< "Speed: " << info.speed << std::endl;
	}
	else if (firstArg == "EngineOn")
	{
		return car.TurnOnEngine();
	}
	else if (firstArg == "EngineOff")
	{
		return car.TurnOffEngine();
	}
	else if (firstArg == "SetGear")
	{
		int secondArg;
		command >> secondArg;
		return car.SetGear(static_cast<Transmission>(secondArg));
	}
	else if (firstArg == "SetSpeed")
	{
		int secondArg;
		command >> secondArg;
		return car.SetSpeed(secondArg);
	}
	else
	{
		PrintHelp();
	}
	return true;
}

int main()
{
	CCar car;
	std::string line;
	while (getline(std::cin, line), line != "")
	{
		if (!parseCommand(line, car))
		{
			std::cout << "Problem with command\n";
		}
	}
	return 0;
}

