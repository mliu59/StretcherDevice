#include <iostream>
#include <string>
#include <stdlib.h>
#include "SerialPort.h"
#include "functions.h"

using namespace std;


char incomingData[MAX_DATA_LENGTH];
char *port = (char*)"\\\\.\\COM4";

int main() {
	SerialPort arduino(port);
	if (arduino.isConnected()) {
		cout << "Connection Successful." << endl;
	}
	else {
		cout << "Connection Failed." << endl;
	}

	while (arduino.isConnected()) {

		char output[MAX_DATA_LENGTH];
		output[0] = '~';

		cout << "Enter Command [*Com Symbol (S/F/R)**Distance (in mm)]: ";
		string data;
		cin >> data;

		char* command = CStr(data);
		arduino.writeSerialPort(command, MAX_DATA_LENGTH);
		delete[] command;

		bool fin = FALSE;

		while (!fin) {
			arduino.readSerialPort(output, MAX_DATA_LENGTH);
			if (output[0] != '~'){
				cout << "received: " << output << endl;
				fin = TRUE;
		//		arduino.writeSerialPort(confirm, MAX_DATA_LENGTH);
			}
		}

	}
	return 0;


}

