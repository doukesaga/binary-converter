#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

// function prototypes
string decimalToBinary(string);
string binaryToDecimal(string);
string decimalToHex(string);
string hexToDecimal(string);
bool numCheck(string);
void menu(unsigned = 50);
//test

// adt
enum Readability {
	convertDecimalToBinary = 1,
	convertBinaryToDecimal,
	convertDecimalToHex,
	convertHexToDecimal,
	exitProgram = 9,
};

int main() {
	// project constraints
	const unsigned BIN_CAP = 8, HEX_CAP = 4;

	// menu variables
	string uxIn = "";   		  // store user string input
	int uxOut = 0;			  	  // store validated user input as integer
	const int MENU_WIDTH = 70;    // menu size

	while (uxOut != exitProgram) {
		// load menu
		menu(MENU_WIDTH); 		// 1.1

		// get and validate input from user
		cout << "Enter your option: ";
		getline(cin, uxIn);
		if (numCheck(uxIn)) {
			// switch data type
			stringstream ux;
			ux << uxIn;
			ux >> uxOut;

			// branch off to submenu
			if (uxOut >= convertDecimalToBinary && uxOut <= convertHexToDecimal) {
				switch(uxOut) {
				case convertDecimalToBinary: 	// 1.2
					// ask the user for a decimal number
					cout << "Enter the decimal to be converted to binary: ";
					getline(cin, uxIn);

					// check if user typed a negative number
					uxIn[0] == '-' ? cout << "negative detected." : cout << decimalToBinary(uxIn);
					break;

				case convertBinaryToDecimal:	// 1.3
					// ask the user for a binary number
					cout << "Enter the binary to be converted to decimal: ";
					getline(cin, uxIn);

					// cap the length of the binary number
					uxIn.length() > BIN_CAP ? cout << "the length is capped at " << BIN_CAP << " bits" : cout << binaryToDecimal(uxIn);
					break;

				case convertDecimalToHex:		// 1.4
					// ask the user for a decimal number
					cout << "Enter the decimal to be converted to hexadecimal: ";
					getline(cin, uxIn);

					// check if user typed a negative number
					uxIn[0] == '-' ? cout << "negative detected." : cout << decimalToHex(uxIn);
					break;

				case convertHexToDecimal:		// 1.5
					// ask the user for a hexadecimal
					cout << "Enter the hexadecimal to be converted to decimal: ";
					getline(cin, uxIn);

					// cap the length of the hexadecimal
					uxIn.length() > HEX_CAP ? cout << "the length is capped at " << HEX_CAP << " digits" : cout << hexToDecimal(uxIn);
					break;
				}

				// reset user input
				uxOut = 0;
			}
			else if (uxOut == exitProgram) {
				cout << "ending the program";
			}
			else {
				cout << "selection is unavailable.";
			}
		}
	}

	return 0;
}

/*
 * description: decimalToBinary() converts decimal to binary
 * input:  string containing a decimal value
 * output: string containing a binary result
 */

string decimalToBinary(string decimal) {	// 1.2
	//	check if input is a number
	if (!numCheck(decimal)) {
		return "";
	}

	// switch data type
	stringstream stou;
	unsigned decimalUints;
	stou << decimal;
	stou >> decimalUints;

	// convert decimal to binary
	string binary = "";

	do {
		binary.insert(0, 1, '0' + decimalUints % 2);
		decimalUints /= 2;
	} while (decimalUints > 0);

	binary.insert(0, "\tDECIMAL: " + decimal + "\n\tBINARY : ");

	return binary;
}


/*
 * description: binaryToDecimal() converts binary to decimal
 * input:  string containing a binary value
 * output: string containing a decimal result
 */

string binaryToDecimal(string binary) {		// 1.3
	//	check if input is a number
	if (!numCheck(binary)) {
		return "";
	}

	// check if input is a binary number
	for (unsigned i = 0; i < binary.length(); i++) {
		if (binary[i] != '0' && binary[i] != '1') {
			return "non binary input detected.";
		}
	}

	// convert binary to decimal
	unsigned sum = 0, base = 2, exponent = binary.length() - 1;
	for (unsigned i = 0; i < binary.length(); i++, exponent--) {
		if (binary[i] == '1') {
			sum += pow(base, exponent);
		}
	}

	// switch data type
	stringstream utos;
	utos << sum;
	string decimal = "\tBINARY : " + binary + "\n\tDECIMAL: " + utos.str();

	return decimal;
}

/*
 * description: hexToDecimal() converts decimal to hexadecimal
 * input:  string containing a decimal value
 * output: string containing a hexadecimal result
 */

string decimalToHex(string decimal) {		// 1.4
	//	check if input is a number
	if (!numCheck(decimal)) {
		return "";
	}

	// switch data type
	stringstream stou;
	unsigned decimalUints = 0;
	stou << decimal;
	stou >> decimalUints;

	// convert decimal to hexadecimal
	string hexadecimal = "";

	do {
		switch(decimalUints % 16) {
		case 10: hexadecimal.insert(0, 1, 'A');
		break;
		case 11: hexadecimal.insert(0, 1, 'B');
		break;
		case 12: hexadecimal.insert(0, 1, 'C');
		break;
		case 13: hexadecimal.insert(0, 1, 'D');
		break;
		case 14: hexadecimal.insert(0, 1, 'E');
		break;
		case 15: hexadecimal.insert(0, 1, 'F');
		break;
		default: hexadecimal.insert(0, 1, '0' + decimalUints % 16);
		}

		decimalUints /= 16;
	} while (decimalUints > 0);

	hexadecimal.insert(0, "\tDECIMAL    : " + decimal + "\n\tHEXADECIMAL: ");

	return hexadecimal;
}

/*
 * description: hexToDecimal() converts hexadecimal to decimal
 * input:  string containing a hexadecimal value
 * output: string containing a decimal result
 */

string hexToDecimal(string hexadecimal) {		// 1.5
	// check if input is empty
	if (hexadecimal.length() == 0) {
		return "no input detected.";
	}

	// check for (0-9, a, b, c, d, e, f) and store as an integer
	unsigned decimals[hexadecimal.length()];
	unsigned decimalTotal = 0, base = 16, exponent = hexadecimal.length() - 1;

	for (unsigned i = 0; i < hexadecimal.length(); i++, exponent--) {
		// conversion table
		switch(toupper(hexadecimal[i])) {
		case '0': decimals[i] = 0;
			break;
		case '1': decimals[i] = 1;
			break;
		case '2': decimals[i] = 2;
			break;
		case '3': decimals[i] = 3;
			break;
		case '4': decimals[i] = 4;
			break;
		case '5': decimals[i] = 5;
			break;
		case '6': decimals[i] = 6;
			break;
		case '7': decimals[i] = 7;
			break;
		case '8': decimals[i] = 8;
			break;
		case '9': decimals[i] = 9;
			break;
		case 'A': decimals[i] = 10;
			break;
		case 'B': decimals[i] = 11;
			break;
		case 'C': decimals[i] = 12;
			break;
		case 'D': decimals[i] = 13;
			break;
		case 'E': decimals[i] = 14;
			break;
		case 'F': decimals[i] = 15;
			break;
		default:
			return "non hex input detected.";
		}

		// convert hexadecimal to decimal
		decimalTotal += (pow(base, exponent) * decimals[i]);
	}

	// switch data type
	stringstream utos;
	utos << decimalTotal;
	string decimal = "\tHEX    : " + hexadecimal + "\n\tDECIMAL: " + utos.str();

	return decimal;
}

/*
 * description: numCheck() validates integer values
 * input:  string value to check for digits
 * output: bool pass or fail status
 */

bool numCheck(string uxStr) {
	// check if input is empty
	if (uxStr.length() == 0) {
		cout << "no input detected. ";
		return false;
	}

	// check if input is a number
	for (unsigned i = 0; i < uxStr.length(); i++) {
		if (!isdigit(uxStr[i])) {
			cout << "invalid input. ";
			return false;
		}
	}

	return true;
}

/*
 * description: menu() displays user options
 * input:  optional integer with menu border size
 * output: n/a
 */

void menu(unsigned width) {
	// menu variables
	const int MENU_ENTRIES = 6, LAST = MENU_ENTRIES - 1;
	const char BORDER = '#', FILL_STYLE = ' ';
	string menuItems[MENU_ENTRIES] = {
			"Numeric Converter",
			"Decimal to Binary",
			"Binary to Decimal",
			"Decimal to Hex ",
			"Hex to Decimal ",
			"Exit Program "};

	// menu alignment and structure
	// m = item length, 2s = left/right sides, w = total width
	// s = (w - m) / 2
	cout << endl;
	for (unsigned item = 0; item < MENU_ENTRIES; item++) {
		// print border
		if (item == 0 || item == 1) {
			cout << setfill(BORDER) << setw(width) << BORDER << endl;
		}

		// print left menu numbers
		item == 0 ? cout << BORDER : item == LAST ? cout << exitProgram : cout << item;

		// print center-aligned entries
		cout << setfill(FILL_STYLE) << setw((width - menuItems[item].length()) / 2 + menuItems[item].length()) << menuItems[item] << setfill(FILL_STYLE) << setw((width - menuItems[item].length()) / 2);

		// print right menu numbers
		item == 0 ? cout << BORDER : item == LAST ? cout << exitProgram : cout << item;
		cout << endl;
	}
	// print border
	cout << setfill(BORDER) << setw(width) << BORDER << endl;
}
