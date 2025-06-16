#pragma once
#include <iostream>
#include <vector>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;


class clsUpdateCurrencyRateScreen : protected clsScreen {

private:

	static void _PrintCurrency(clsCurrency Currency) {

		cout << "\nCurrency Card: " << endl;
		cout << "_________________________________" << endl;
		cout << "\nCountry      : " << Currency.Country() << endl;
		cout << "Currency Code: " << Currency.CurrencyCode() << endl;
		cout << "Currency Name: " << Currency.CurrencyName() << endl;
		cout << "Rate(1$)     : " << Currency.Rate() << endl;
		cout << "_________________________________" << endl;
	}

	static float _ReadRate() {
		
		float NewRate = 0;
		cout << "\nEnter New Rate: ";
		NewRate = clsInputValidate::ReadFloatNumber();

		return NewRate;
	}

public:

	static void ShowUpdateCurrencyRateScreen() {
		
		_DrawScreenHeader("Update Currency Screen");

		cout << "Please enter Currency Code: ";
		string CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			
			cout << "\nCurrency is not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		cout << "\nAre you sure you want to update the rate of this currency y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			
			cout << "\nUpdate Currency Rate: " << endl;
			cout << "____________________________________" << endl;

			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully :-)" << endl;
			_PrintCurrency(Currency);
		}

	}

};

