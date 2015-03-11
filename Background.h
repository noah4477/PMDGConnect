#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "EventID.h"


static enum DATA_REQUEST_ID {
	DATA_REQUEST,
	CONTROL_REQUEST,
	AIR_PATH_REQUEST
};

static enum INPUT_ID {
	INPUT0			// used to handle key presses
};

static enum GROUP_ID {
	GROUP_KEYBOARD		// used to handle key presses
};

bool NGX_FuelPumpLAftLight = true;
bool NGX_TaxiLightSwitch = false;
bool NGX_LogoLightSwitch = false;

// This function is called when NGX data changes
void ProcessNGXData(PMDG_NGX_Data *pS)
{
	// test the data access:
	// get the state of an annunciator light and display it
	
	if (pS->FUEL_annunLOWPRESS_Aft[0] != NGX_FuelPumpLAftLight)
	{
		NGX_FuelPumpLAftLight = pS->FUEL_annunLOWPRESS_Aft[0];
		if (NGX_FuelPumpLAftLight)
			printf("\nLOW PRESS LIGHT: [ON]");
		else
			printf("\nLOW PRESS LIGHT: [OFF]");
	}

	// get the state of switches and save it for later use
	if (pS->LTS_TaxiSw != NGX_TaxiLightSwitch)
	{
		NGX_TaxiLightSwitch = pS->LTS_TaxiSw;
		if (NGX_TaxiLightSwitch)
			printf("\nTAXI LIGHTS: [ON]");
		else
			printf("\nTAXI LIGHTS: [OFF]");
	}

	if (pS->LTS_LogoSw != NGX_LogoLightSwitch)
	{
		NGX_LogoLightSwitch = pS->LTS_LogoSw;
		if (NGX_LogoLightSwitch)
			printf("\nLOGO LIGHTS: [ON]");
		else
			printf("\nLOGO LIGHTS: [OFF]");
	}
}

void toggleTaxiLightSwitch()
{
	// Test the first control method: use the control data area.
	if (AircraftRunning)
	{
		bool New_TaxiLightSwitch = !NGX_TaxiLightSwitch;

		// Send a command only if there is no active command request and previous command has been processed by the NGX
		if (Control.Event == 0)
		{
			Control.Event = EVT_OH_LIGHTS_TAXI;		// = 69749
			if (New_TaxiLightSwitch)
				Control.Parameter = 1;
			else
				Control.Parameter = 0;
			SimConnect_SetClientData(hSimConnect, PMDG_NGX_CONTROL_ID, PMDG_NGX_CONTROL_DEFINITION,
				0, 0, sizeof(PMDG_NGX_Control), &Control);
		}
	}
	/*
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_CPT_BARO_SELECTOR, MOUSE_FLAG_LEFTSINGLE,
	SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_CPT_BARO_SELECTOR, MOUSE_FLAG_LEFTRELEASE,
	SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);*/
}

void toggleLogoLightsSwitch()
{
	// Test the second control method: send an event
	// use direct switch position
	bool New_LogoLightSwitch = !NGX_LogoLightSwitch;

	int parameter = New_LogoLightSwitch ? 1 : 0;
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_LOGO_LIGHT_SWITCH, parameter,
		SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
}

void toggleFlightDirector()
{
	// Test the second control method: send an event
	// use mouse simulation to toggle the switch
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_FLIGHT_DIRECTOR_SWITCH, MOUSE_FLAG_LEFTSINGLE,
		SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_FLIGHT_DIRECTOR_SWITCH, MOUSE_FLAG_LEFTRELEASE,
		SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
}

void slewHeadingSelector()
{
	// Test the second control method: send an event
	// use mouse simulation to slew a knob
	SimConnect_TransmitClientEvent(hSimConnect, 0, EVENT_HEADING_SELECTOR, MOUSE_FLAG_WHEEL_UP,
		SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
}

void CALLBACK MyDispatchProc(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
{
	switch (pData->dwID)
	{
	case SIMCONNECT_RECV_ID_CLIENT_DATA: // Receive and process the NGX data block
	{
		SIMCONNECT_RECV_CLIENT_DATA *pObjData = (SIMCONNECT_RECV_CLIENT_DATA*)pData;

		switch (pObjData->dwRequestID)
		{
		case DATA_REQUEST:
		{
			PMDG_NGX_Data *pS = (PMDG_NGX_Data*)&pObjData->dwData;
			ProcessNGXData(pS);
			break;
		}
		case CONTROL_REQUEST:
		{
			// keep the present state of Control area to know if the server had received and reset the command
			PMDG_NGX_Control *pS = (PMDG_NGX_Control*)&pObjData->dwData;
			Control = *pS;
			break;
		}
		}
		break;
	}

	case SIMCONNECT_RECV_ID_EVENT:
	{
		SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;
		switch (evt->uEventID)
		{
		case EVENT_SIM_START:	// Track aircraft changes
		{
			HRESULT hr = SimConnect_RequestSystemState(hSimConnect, AIR_PATH_REQUEST, "AircraftLoaded");
			break;
		}
		case EVENT_KEYBOARD_A:
		{
			toggleTaxiLightSwitch();
			break;
		}
		case EVENT_KEYBOARD_B:
		{
			toggleLogoLightsSwitch();
			break;
		}
		case EVENT_KEYBOARD_C:
		{
			toggleFlightDirector();
			break;
		}
		case EVENT_KEYBOARD_D:
		{
			slewHeadingSelector();

			break;
		}
		}
		break;
	}

	case SIMCONNECT_RECV_ID_SYSTEM_STATE: // Track aircraft changes
	{
		SIMCONNECT_RECV_SYSTEM_STATE *evt = (SIMCONNECT_RECV_SYSTEM_STATE*)pData;
		if (evt->dwRequestID == AIR_PATH_REQUEST)
		{
			if (strstr(evt->szString, "PMDG 737") != NULL)
				AircraftRunning = true;
			else
				AircraftRunning = false;
		}
		break;
	}

	case SIMCONNECT_RECV_ID_QUIT:
	{
		quit = 1;
		break;
	}

	default:
		printf("\nReceived:%d", pData->dwID);
		break;
	}
}
#endif /*BACKGROUND_H*/