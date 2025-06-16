#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen {

private:

	static float _ReadAmount() {
		
		float Amount = 0;
		cout << "\nEnter Amount to Exchange: ";
		Amount = clsInputValidate::ReadFloatNumber();

		return Amount;
	}

	static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:") {

		cout << endl << Title << endl;
		cout << "_________________________________" << endl;
		cout << "\nCountry          : " << Currency.Country() << endl;
		cout << "Currency Code    : " << Currency.CurrencyCode() << endl;
		cout << "Currency Name    : " << Currency.CurrencyName() << endl;
		cout << "Rate(1$)         : " << Currency.Rate() << endl;
		cout << "_________________________________" << endl;
	}

	static clsCurrency _GetCurrency(string Message) {

		string CurrencyCode;
		cout << Message << endl;

		CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {

			cout << "\nCurrency was not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}

	static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2) {
		
		_PrintCurrencyCard(Currency1, "Convert From: ");

		float AmountInUSD = Currency1.ConvertToUSD(Amount);

		cout << endl << Amount << " " << Currency1.CurrencyCode() 
			<< " = " << AmountInUSD << " USD" << endl;

		if (Currency2.CurrencyCode() == "USD") {
			
			return;
		}

		cout << "\nConverting from USD to: " << endl;
		_PrintCurrencyCard(Currency2, "To: ");

		float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

		cout << endl << Amount << " " << Currency1.CurrencyCode() 
			<< " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode() << endl;
	}

public:

	static void ShowCurrencyCalculatorScreen() {
		
		char Continue = 'n';

		do {

			system("cls");
			_DrawScreenHeader("Currency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease enter Currency1 Code: ");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease enter Currency2 Code: ");
			float Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

			cout << "\nDo you want to perrform another calculation? y/n? ";
			cin >> Continue;

		} while (Continue == 'Y' || Continue == 'y');

	}

};

