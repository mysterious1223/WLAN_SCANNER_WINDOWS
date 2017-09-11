#include <windows.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

using namespace std;

int main()
{
	// open wlan handle

	// Enum Devices

	// Select Device

	// Config device? Mac - Power

	// Scan area
	DWORD version;
	HANDLE CHandle;
	DWORD result = WlanOpenHandle(
	1, NULL, &version, &CHandle
	);

	if (result == ERROR_SUCCESS)
	{
		printf(" WLAN HANDLE OPENED !\n");

	}
	else
	{
		printf("Failed");
		system("PAUSE");
		return 0;
	}
	
	result = NULL;

	WLAN_INTERFACE_INFO_LIST* interfaces = NULL;

	interfaces = new WLAN_INTERFACE_INFO_LIST;

	result = WlanEnumInterfaces(
	CHandle, NULL, &interfaces
	);
	if (result == ERROR_SUCCESS)
	{
		printf(" ENUMERATION WORKED !\n");

	}
	else
	{
		printf("ENUM Failed\n");
		system("PAUSE");
		return 0;
	}

	

	for (int i = 0; i < interfaces->dwNumberOfItems; i++)
	{
		printf("INDEX : [%d], name : [%ws]\n", interfaces->dwIndex, interfaces->InterfaceInfo[i].strInterfaceDescription);
		

		

	}

	int opt = 0;
	printf("SELECT a DEVICE: ");

	cin >> opt;

	printf("You selected [%ws]\n", interfaces->InterfaceInfo[opt].strInterfaceDescription);

	GUID option = interfaces->InterfaceInfo[opt].InterfaceGuid;


	// scanning begin?

	// WlanScan -> raw data, WlanGetAvailableNetworkList

	

	while (true)
	{

		result = NULL;
		WLAN_AVAILABLE_NETWORK_LIST* netlist = NULL;
		netlist = new WLAN_AVAILABLE_NETWORK_LIST;
		result = WlanGetAvailableNetworkList(
			CHandle, &option, 0, NULL, &netlist
		);

		if (result == ERROR_SUCCESS)
		{
			printf(" Scanning WORKED !\n");

		}
		else
		{
			printf("Scanning Failed\n");
			system("PAUSE");
			return 0;
		}

		for (int i = 0; i < netlist->dwNumberOfItems; i++)
		{
			printf("[%d] : ", i);
			for (int j = 0; j < netlist->Network[i].dot11Ssid.uSSIDLength; j++)
				printf("%c", netlist->Network[i].dot11Ssid.ucSSID[j]);
			// need to loop through it

			printf(", strength : [%d]", netlist->Network[i].wlanSignalQuality);


			printf("\n");
			//system("PAUSE");

		}
		
		Sleep(2000);
		system("CLS");
		// setting up device speed -  WlanQueryInterface
	}
	//DWORD result = WlanEnumInterfaces();
	system("PAUSE");
	return 0;
}
