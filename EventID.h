#ifndef EVENTID_H
#define EVENTID_H
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>
#include "SimConnect.h"
#include "PMDG_NGX_SDK.h"
#using <System.dll>

using namespace System;
using namespace System::IO;
using namespace System::IO::Ports;
using namespace System::Threading;
using namespace std;

int     quit = 0;
HANDLE  hSimConnect = NULL;
bool    AircraftRunning = false;
PMDG_NGX_Control Control;
HRESULT hr;
static enum EVENT_ID {
	EVENT_SIM_START,	// used to track the loaded aircraft

	EVENT_LOGO_LIGHT_SWITCH,
	EVENT_FLIGHT_DIRECTOR_SWITCH,
	EVENT_HEADING_SELECTOR,

	//EFIS CAPTIAN

	EVENT_EFIS_CPT_BARO,
	EVENT_EFIS_CPT_MINIMUMS,
	EVENT_EFIS_CPT_MODE,
	EVENT_EFIS_CPT_RANGE,
	EVENT_EFIS_CPT_MODE_CTR,
	EVENT_EFIS_CPT_RANGE_TFC,
	EVENT_EFIS_CPT_MINIMUMS_RST,
	EVENT_EFIS_CPT_BARO_STD,
	EVENT_EFIS_CPT_BARO_IN_HPA,
	EVENT_EFIS_CPT_MINIMUMS_RADIO_BARO,
	EVENT_EFIS_CPT_FPV,
	EVENT_EFIS_CPT_MTRS,
	EVENT_EFIS_CPT_VOR_ADF_SELECTOR_L,
	EVENT_EFIS_CPT_VOR_ADF_SELECTOR_R,
	EVENT_EFIS_CPT_WXR,
	EVENT_EFIS_CPT_STA,
	EVENT_EFIS_CPT_WPT,
	EVENT_EFIS_CPT_ARPT,
	EVENT_EFIS_CPT_DATA,
	EVENT_EFIS_CPT_POS,
	EVENT_EFIS_CPT_TERR,

	//MCP

	EVENT_KEYBOARD_A,
	EVENT_KEYBOARD_B,
	EVENT_KEYBOARD_C,
	EVENT_KEYBOARD_D
};
void TestID(int i)
{
	cout << "" << endl << i << endl;
}
void InitilizeControls()
{
	
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_LOGO_LIGHT_SWITCH, "#69754");			//EVT_OH_LIGHTS_LOGO
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_FLIGHT_DIRECTOR_SWITCH, "#70010");		//EVT_MCP_FD_SWITCH_L
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_HEADING_SELECTOR, "#70022");			//EVT_MCP_HEADING_SELECTOR

	//EFIS CAPTAIN

	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_MINIMUMS, "#69987");			//EVT_EFIS_CPT_MINIMUMS	
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_BARO, "#69997");				//EVT_EFIS_CPT_BARO
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_MINIMUMS_RST, "#69989");		//EVT_EFIS_CPT_MINIMUMS_RST
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_BARO_STD, "#69999");			//EVT_EFIS_CPT_BARO_STD

	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_BARO_IN_HPA, "#69998");		//EVT_EFIS_CPT_BARO_IN_HPA
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_MINIMUMS_RADIO_BARO, "#69988");//EVT_EFIS_CPT_MINIMUMS_RADIO_BARO

	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_MODE, "#69991");				//EVT_EFIS_CPT_MODE
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_RANGE, "#69993");				//EVT_EFIS_CPT_RANGE
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_MODE_CTR, "#69992");			//EVT_EFIS_CPT_MODE_CTR
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_RANGE_TFC, "#69994");			//EVT_EFIS_CPT_RANGE_TFC
	
	
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_FPV, "#69995");				//EVT_EFIS_CPT_FPV
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_MTRS, "#69996");				//EVT_EFIS_CPT_MTRS

	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_VOR_ADF_SELECTOR_L, "#69990");	//EVT_EFIS_CPT_VOR_ADF_SELECTOR_L
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_VOR_ADF_SELECTOR_R, "#70000");	//EVT_EFIS_CPT_VOR_ADF_SELECTOR_R
	
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_WXR, "#70001");		//EVT_EFIS_CPT_WXR
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_STA, "#70002");		//EVT_EFIS_CPT_STA
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_WPT, "#70003");		//EVT_EFIS_CPT_WPT
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_ARPT, "#70004");		//EVT_EFIS_CPT_ARPT
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_DATA, "#70005");		//EVT_EFIS_CPT_DATA
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_POS, "#70006");		//EVT_EFIS_CPT_POS
	hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_EFIS_CPT_TERR, "#70007");		//EVT_EFIS_CPT_TERR

	//MCP


	//EFIS F/O

}
#endif /*EVENTID_H*/