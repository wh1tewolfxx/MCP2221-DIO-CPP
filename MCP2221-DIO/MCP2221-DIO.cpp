// MCP2221_Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Add includes
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "MCP2221-DIO.h"


//Define Macros
#define DEFAULT_VID                     0x04D8
#define DEFAULT_PID                     0x00DD
#define MCP2221_LIB        1	//for projects importing the .lib, use the MCP2221_LIB preprocessor definition

//Define Constants
static const int OFF = 0;
static const int ON = 1;

static const int CURRENT_SETTINGS_ONLY = 0;
static const int PWRUP_DEFAULTS_ONLY = 1;
static const int BOTH = 2;

//Define strings
wchar_t libVersion[64];
wchar_t manufacturerString[30];
wchar_t productString[30];
wchar_t serialNumber[30];
wchar_t factorySerialNumber[30];
wchar_t HW_REV[2];
wchar_t FW_REV[2];

//Stores result from executing MCP2221(A) methods.
int result = 0;

//Stores handle pointer from MCP2221(A).
void* mcpHandle = NULL;

//Device index.
unsigned int mcpIndex = 0;

//Devices connected.
unsigned int numberOfDevices = 0;

//Array to store data about each GPIO pin.
//GP0 - GP3
unsigned char pinFunctions[4] = "";
unsigned char pinDirections[4] = "";
unsigned char outputValues[4] = "";
unsigned char inputValues[4] = "";


int main()
{
	
	result = Mcp2221_GetLibraryVersion(libVersion); //Get Library Version.

	if (result == E_NO_ERR)
	{
		std::wcout << "Library Version: " << libVersion << "\n";
		
		result = Mcp2221_GetConnectedDevices(DEFAULT_VID, DEFAULT_PID, &numberOfDevices); //Get Connected Devices using Defualt VID and PID.

		if (result == E_NO_ERR)
		{
			std::cout << "Number of Devices: " << numberOfDevices << "\n";
			if (numberOfDevices > 0)
			{
				
				mcpHandle = Mcp2221_OpenByIndex(DEFAULT_VID, DEFAULT_PID, mcpIndex); //Get Device handle by Index.
				if (result == E_NO_ERR)
				{
					
					result = Mcp2221_GetManufacturerDescriptor(mcpHandle, manufacturerString); //Get Manufacture Descriptor.
					if (result == E_NO_ERR)
					{
						std::wcout << "Manufacturer: " << manufacturerString << "\n";
					}

					
					result = Mcp2221_GetProductDescriptor(mcpHandle, productString); //Get Product Descriptor.
					if (result == E_NO_ERR)
					{
						std::wcout << "Product: " << productString << "\n";
					}

					
					result = Mcp2221_GetSerialNumberDescriptor(mcpHandle, serialNumber); //Get SN.
					if (result == E_NO_ERR)
					{
						std::wcout << "SerialNumber: " << serialNumber << "\n";
					}

					
					result = Mcp2221_GetFactorySerialNumber(mcpHandle, factorySerialNumber); //Get Factory SN.
					if (result == E_NO_ERR)
					{
						std::wcout << "FactorySerialNumber: " << factorySerialNumber << "\n";
					}

					
					result = Mcp2221_GetHwFwRevisions(mcpHandle, HW_REV, FW_REV); //Get HW/FW Revisions.
					if (result == E_NO_ERR)
					{
						std::wcout << "Hardware Revisions: " << HW_REV << "\n";
						std::wcout << "Software Revisions: " << FW_REV << "\n";
					}

					
					result = Mcp2221_GetLastError(); //Check for any errors before entering IO Loop.
					if (result == E_NO_ERR)
					{
						//Enter GPIO Loop
						while (result == E_NO_ERR) {

							
							result = Mcp2221_GetGpioValues(mcpHandle, inputValues); //Get GPIO values and store in input array.

							//Check specific index for High Value. i.e. index 1 = GP1
							if (inputValues[1] == ON) {
								//std::cout << "GP1 High" << std::endl;
								outputValues[0] = ON; //Set index 0 in output value array high.
								
								result = Mcp2221_SetGpioValues(mcpHandle, outputValues); //Set GPIO output values using output value array.

							}
							else {
								//std::cout << "GP1 Low" << std::endl;
								outputValues[0] = OFF; //Set index 0 GPIO output value array low.
								
								result = Mcp2221_SetGpioValues(mcpHandle, outputValues); //Set GPIO output values using output value array.
							}
						}
					}
					else
					{
						std::cout << "ERROR >> Mcp2221_GetLastError() returned: " << result << "\n";
					}
				}				
			}
			else
			{
				std::cout << "ERROR >> NO DEVICES CONNECTED !\n" << "\n";
			}
		}
		else
		{
			std::cout << "ERROR >> Mcp2221_GetConnectedDevices() returned: " << result << "\n";
		}
	}
	Mcp2221_Close(mcpHandle);
}