#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsPeriod.h"
using namespace std;

class clsInputValidate {

public:

	static bool IsNumberBetween(short Number, short From, short To) {
		
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(int Number, int From, int To) {

		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(float Number, float From, float To) {

		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(double Number, double From, double To) {

		return (Number >= From && Number <= To);
	}

	static bool IsValideDate(clsDate Date) {

		return clsDate::IsValidDate(Date);
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To) {

		//Date>=From && Date<=To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualToDate2(Date, From))
			&& (clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualToDate2(Date, To))) {
			
			return true;
		}

		//Date>=To && Date<=From
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualToDate2(Date, To))
			&& (clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualToDate2(Date, From))) {
		
			return true;
		}

		return false;
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
		
		int Number;
		while (!(cin >> Number)) {
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
		
		short Number;
		while (!(cin >> Number)) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
		
		double Number;
		while (!(cin >> Number)) {
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n") {
		
		int Number = ReadIntNumber();
		while (!IsNumberBetween(Number, From, To)) {
			
			cout << ErrorMessage << endl;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n") {

		double Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To)) {
			
			cout << ErrorMessage << endl;
			Number = ReadDblNumber();
		}
		return Number;
	}

	static int ReadPositiveNumber(string ErrorMessage) {
		
		int Number = ReadIntNumber();
		while (Number <= 0) {
			
			cout << ErrorMessage << endl;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static int ReadNegativeNumber(string ErrorMessage) {

		int Number = ReadIntNumber();
		while (Number >= 0) {

			cout << ErrorMessage << endl;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static string ReadString() {
		
		string S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
		
		float Number = 0;
		while (!(cin >> Number)) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n") {
		
		short Number = ReadShortNumber();
		while (!IsNumberBetween(Number, From, To)) {

			cout << ErrorMessage << endl;
			Number = ReadShortNumber();
		}
		return Number;
	}

};