#pragma once
#include "stdafx.h"
#include "Car.h"
#include "Definition.h"

void PrintInfoAboutCar(const InfoAboutCar & indicators);
void PrintResultEngineOnCommand(const int & value);
void PrintResultEngineOffCommand(const int & value);
void PrintResultSetGearCommand(const int & value);
void PrintResultSetSpeedCommand(const int & value);
void PrintHelp();

void CarDriver();