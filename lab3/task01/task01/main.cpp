#include "stdafx.h"
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

void parseCommand(const std::string & commandStr, CCar & car)
{
	std::istringstream command(commandStr);
	std::string firstArg;
	command >> firstArg;

	if (firstArg == "Info")
	{
		auto info = car.GetInfo();
		std::cout 
			<< "Engine is " << (info.conditionEngine ? "working" : "offen") << std::endl
			<< "Diraction: " << static_cast<int>(info.dir) << std::endl
			<< "Gear: " << static_cast<int>(info.gear) << std::endl
			<< "Speed: " << info.speed << std::endl;
	}
	else if (firstArg == "EngineOn")
	{
		std::cout << (car.TurnOnEngine() ? "Ok" : "The problem with the engine running") << std::endl;
	}
	else if (firstArg == "EngineOff")
	{
		std::cout << (car.TurnOffEngine() ? "Ok" : "The problem with the engine off") << std::endl;
	}
	else if (firstArg == "SetGear")
	{
		int secondArg;
		command >> secondArg;
		std::cout << (car.SetGear(static_cast<Transmission>(secondArg)) ? "Ok" : "The problem with the gear shift") << std::endl;
	}
	else if (firstArg == "SetSpeed")
	{
		int secondArg;
		command >> secondArg;
		std::cout << (car.SetSpeed(secondArg)) ? "Ok" : "A problem with speed change") << std::endl;

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
	return EXIT_SUCCESS;
}

