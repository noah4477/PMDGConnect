#include "Background.h"



void StartSimConnect()
{
	printf("\nConnected to Flight Simulator!");

	// 1) Set up data connection

	// Associate an ID with the PMDG data area name
	hr = SimConnect_MapClientDataNameToID(hSimConnect, PMDG_NGX_DATA_NAME, PMDG_NGX_DATA_ID);

	// Define the data area structure - this is a required step
	hr = SimConnect_AddToClientDataDefinition(hSimConnect, PMDG_NGX_DATA_DEFINITION, 0, sizeof(PMDG_NGX_Data), 0);

	// Sign up for notification of data change.  
	// SIMCONNECT_CLIENT_DATA_REQUEST_FLAG_CHANGED flag asks for the data to be sent only when some of the data is changed.
	hr = SimConnect_RequestClientData(hSimConnect, PMDG_NGX_DATA_ID, DATA_REQUEST, PMDG_NGX_DATA_DEFINITION,
		SIMCONNECT_CLIENT_DATA_PERIOD_ON_SET, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG_CHANGED, 0, 0, 0);


	// 2) Set up control connection

	// First method: control data area
	Control.Event = 0;
	Control.Parameter = 0;

	// Associate an ID with the PMDG control area name
	hr = SimConnect_MapClientDataNameToID(hSimConnect, PMDG_NGX_CONTROL_NAME, PMDG_NGX_CONTROL_ID);

	// Define the control area structure - this is a required step
	hr = SimConnect_AddToClientDataDefinition(hSimConnect, PMDG_NGX_CONTROL_DEFINITION, 0, sizeof(PMDG_NGX_Control), 0);

	// Sign up for notification of control change.  
	hr = SimConnect_RequestClientData(hSimConnect, PMDG_NGX_CONTROL_ID, CONTROL_REQUEST, PMDG_NGX_CONTROL_DEFINITION,
		SIMCONNECT_CLIENT_DATA_PERIOD_ON_SET, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG_CHANGED, 0, 0, 0);

	// Second method: Create event IDs for controls that we are going to operate
	InitilizeControls();

	// 3) Request current aircraft .air file path
	hr = SimConnect_RequestSystemState(hSimConnect, AIR_PATH_REQUEST, "AircraftLoaded");
	// also request notifications on sim start and aircraft change
	hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_START, "SimStart");


	// 4) Assign keyboard shortcuts
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_KEYBOARD_A);
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_KEYBOARD_B);
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_KEYBOARD_C);
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_KEYBOARD_D);

	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_KEYBOARD, EVENT_KEYBOARD_A);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_KEYBOARD, EVENT_KEYBOARD_B);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_KEYBOARD, EVENT_KEYBOARD_C);
	hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_KEYBOARD, EVENT_KEYBOARD_D);

	hr = SimConnect_SetNotificationGroupPriority(hSimConnect, GROUP_KEYBOARD, SIMCONNECT_GROUP_PRIORITY_HIGHEST);

	hr = SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT0, "shift+ctrl+a", EVENT_KEYBOARD_A);
	hr = SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT0, "shift+ctrl+b", EVENT_KEYBOARD_B);
	hr = SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT0, "shift+ctrl+c", EVENT_KEYBOARD_C);
	hr = SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT0, "shift+ctrl+d", EVENT_KEYBOARD_D);

	hr = SimConnect_SetInputGroupState(hSimConnect, INPUT0, SIMCONNECT_STATE_ON);


	// 5) Main loop
	while (quit == 0)
	{
		// receive and process the NGX data
		SimConnect_CallDispatch(hSimConnect, MyDispatchProc, NULL);

		Sleep(1);
	}

	hr = SimConnect_Close(hSimConnect);
}