#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "SerialPort.h"
using namespace std;

char* CStr(string input){
	char *Input = new char[input.size() + 1];
	copy(input.begin(), input.end(), Input);
	Input[input.size()] = '\n';
	return Input;
}

