// Gennnaro Punzo CS-210 Project 2

#include <Python.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

int main() {

	// Declare Variables
	int userSelection = 0;
	string userItem;

	cout << "\t\tWelcome!" << endl;

	// Begin loop that terminates upon user entering 4
	while (userSelection != 4) {

		// Prompt menu and get input
		cout << endl << "1: Display List of All Purchased Items" << endl;
		cout << "2: Display Number of Times Purchased For a Specific Item" << endl;
		cout << "3: Display a Histogram of Purchased Items" << endl;
		cout << "4: Quit" << endl;
		cout << "Please enter your selection as a number 1, 2, 3, or 4." << endl;
		cin >> userSelection;
		cout << endl;
		// Validate userSelection
		while (cin.fail()) {
			cout << "Error: Invalid Entry" << endl << "Please enter your selection as a number 1, 2, 3, or 4." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> userSelection;
			cout << endl;
		}

		// exit upon user entering 4
		if (userSelection == 4) {
			cout << "Goodbye." << endl;
			break;
		}

		// Start switch
		switch (userSelection) {

		case 1:
			// Call PrintList function defined in Python
			CallProcedure("PrintList");
			break;

		case 2:
			// Call PrintItem function defined in Python and get item
			cout << "Which item would you like to look up?" << endl;;
			cin >> userItem;
			userItem[0] = toupper(userItem[0]);
			callIntFunc("PrintItem", userItem);
			break;

		case 3:
			CallProcedure("GenerateFile");
			// Declare necessary variables
			string itemName;
			int itemQuantity;

			// Create file object to read from a file
			ifstream inFile;
			// Open "frequency.dat' using the input file
			inFile.open("frequency.dat");

			// Prompt error if file cannot be opened
			if (!inFile) {
				cout << "Error: cannot open file." << endl;
			}

			// With file open, output name and one "*" for each time it was purchased
			else {
				cout << "_____________" << endl;
				while (inFile >> itemName >> itemQuantity) {
					cout << setw(12) << left << itemName;
					cout << "|";
					for (int i = 0; i < itemQuantity; ++i) {
						cout << "*";
					}
					cout << endl;
				}
				cout << "-------------" << endl;
			}

			// Close file
			inFile.close();
		}
	}

	return 0;
}