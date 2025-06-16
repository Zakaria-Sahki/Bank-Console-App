#pragma once
#include <iostream>
#include <vector>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;



class clsFindCurrencyScreen : protected clsScreen {

private:

	enum enFindChoice {eFindByCode = 1, eFindByCountry = 2};

	static short _ReadFindChoice() {
		
		short Choice;
		cout << "Find By: [1] Code or [2] Country ? ";
		cin >> Choice;

		while (Choice > 2 || Choice < 1) {
			
			cout << "Find By: [1] Code or [2] Country ? "; 
			cin >> Choice;
		}
		return Choice;
	}

	static void _PrintCurrency(clsCurrency Currency) {

		cout << "\nCurrency Card: " << endl;
		cout << "_________________________________" << endl;
		cout << "\nCountry      : " << Currency.Country() << endl;
		cout << "Currency Code: " << Currency.CurrencyCode() << endl;
		cout << "Currency Name: " << Currency.CurrencyName() << endl;
		cout << "Rate(1$)     : " << Currency.Rate() << endl;
		cout << "_________________________________" << endl;
	}

	static void FindCurrencyByCode() {
	
		cout << "\nPlease Enter Currency Code: ";
		clsCurrency Currency = clsCurrency::FindByCode(clsInputValidate::ReadString());

		if (!Currency.IsEmpty()) {
			
			cout << "\nCurrency Found :-)" << endl;
			_PrintCurrency(Currency);
		}
		else {
			
			cout << "\nCurrency Not Found :-(" << endl;
		}

	}

	static void FindCurrencyByCountry() {

		cout << "\nPlease Enter Country Name: ";
		clsCurrency Currency = clsCurrency::FindByCountry(clsInputValidate::ReadString());

		if (!Currency.IsEmpty()) {

			cout << "\nCurrency Found :-)" << endl;
			_PrintCurrency(Currency);
		}
		else {

			cout << "\nCurrency Not Found :-(" << endl;
		}

	}


public:

	static void ShowFindCurrencyScreen() {
		
		_DrawScreenHeader("Find Currency Screen");
		
		enFindChoice FindChoice = enFindChoice(clsFindCurrencyScreen::_ReadFindChoice());

		switch (FindChoice) {

		case clsFindCurrencyScreen::eFindByCode:
			FindCurrencyByCode();
			break;
		case clsFindCurrencyScreen::eFindByCountry:
			FindCurrencyByCountry();
			break;
		}

	}
};

