#include "stdafx.h"
#include "Driver.h"
#include "Definition.h"

void PrintHelp()
{
	std::cout << "Info - show car information" << std::endl;
	std::cout << "EngineOn - switch on engine" << std::endl;
	std::cout << "EngineOff - switch off engine" << std::endl;
	std::cout << "SetGear <value> - set gear value" << std::endl;
	std::cout << "SetSpeed <value> - set speed value" << std::endl;
}

void PrintInfoAboutCar(const InfoAboutCar & indicators)
{
	std::cout << "Engine: " << (indicators.conditionEngine ? "runing" : "not runing") << std::endl;
	std::cout << "Speed: " << indicators.speed << std::endl;
	std::cout << "Gear: " << static_cast<int>(indicators.gear) << std::endl;
	std::cout << "Diraction: " << DIRECTION_NAME.find(indicators.dir)->second << std::endl;
}


void PrintResultEngineOnCommand(const int & value)
{

}

void HandlerCommands(const std::string & commandControl, const std::string & strValue, CCar & car)
{
	if (commandControl == "Info")
	{
		PrintInfoAboutCar(car.GetInfo());
	}
	else if (commandControl == "EngineOn")
	{
		//PrintResultEngineOnCommand(car.TurnOnEngine());
	}
	else if (commandControl == "EngineOff")
	{
		//PrintResultEngineOffCommand(car.TurnOffEngine());
	}
	else if (commandControl == "SetGear")
	{

		//PrintResultSetGearCommand(car.SetGear(static_cast<Transmission>(std::atoi(strValue.c_str()))));
	}
	else if (commandControl == "SetSpeed")
	{
		//PrintResultSetSpeedCommand(car.SetSpeed(std::atoi(strValue.c_str())));
	}
	else
	{
		PrintHelp();
	}
}
