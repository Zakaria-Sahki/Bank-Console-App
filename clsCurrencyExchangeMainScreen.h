#pragma once
#include <iostream>
#include <iomanip>
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen {

private: 

    enum enCurrenciesMainMenueOptions {

        eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrencyRate = 3, eCurrencyCalculator = 4, eMainMenue = 5
    };

    static short _ReadCurrencyExchangeMenueOption() {

        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter number between 1 and 5 ? ");
        return Choice;
    }

    static void _ShowListCurrenciesScreen() {
        
        //cout << "\n List Currencies Screen will be here..." << endl;
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen() {
    
        //cout << "\n Find Currency Screen will be here..." << endl;
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen() {
        
        //cout << "\n Update Rate Screen will be here..." << endl;
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen() {
    
        //cout << "\n Currency Calculator Screen will be here..." << endl;
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _GoBackToCurrenciesMenue() {
        
        cout << "\n\nPress any key to go back to Currencies Menue...";
        system("pause>0");
        ShowCurrenciesMenue();
    }

    static void _PerformCurrenciesMainMenueOptions(enCurrenciesMainMenueOptions CurrencyExchangeOption) {
    
        switch (CurrencyExchangeOption) {

        case clsCurrencyExchangeMainScreen::eListCurrencies:
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrenciesMenue();
            break;

        case clsCurrencyExchangeMainScreen::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenue();
            break;

        case clsCurrencyExchangeMainScreen::eUpdateCurrencyRate:
            system("cls");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenciesMenue();
            break;

        case clsCurrencyExchangeMainScreen::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenue();
            break;



        case clsCurrencyExchangeMainScreen::eMainMenue:

            break;

        default:
            break;
        }
    }

public:

	static void ShowCurrenciesMenue() {
		
        system("cls");
        _DrawScreenHeader("Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformCurrenciesMainMenueOptions((enCurrenciesMainMenueOptions)_ReadCurrencyExchangeMenueOption());
	}

};

