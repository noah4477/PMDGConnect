#include "DataFetch.h"

int __cdecl _tmain(int argc, _TCHAR* argv[])
{
	cout << "Trying to Connect to Microsoft Flight Simulator" << endl;

	for (int i = 0; i < 100; i++){
		if (SUCCEEDED(SimConnect_Open(&hSimConnect, "PMDG NGX Test", NULL, 0, 0, 0)))
		{
			StartSimConnect();
			cout << "Connected" << endl;
			i = 100;
		}
		else{
			Sleep(1);
		}
	}
	cout << "Unable To Connect" << endl;
	return 0;
}
