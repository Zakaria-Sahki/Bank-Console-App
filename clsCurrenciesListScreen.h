#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <vector>
using namespace std;


class clsCurrenciesListScreen : protected clsScreen {

private:

    static void PrintCurrencyRecord(clsCurrency Currency) {

        cout << setw(8) << left << "" << "| " << left << setw(30) << Currency.Country();
        cout << "| " << left << setw(7) << Currency.CurrencyCode();
        cout << "| " << left << setw(45) << Currency.CurrencyName();
        cout << "| " << left << setw(10) << Currency.Rate();
    }

public:

    static void ShowCurrenciesListScreen() {

        vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
        string Title = "Currencies List Screen";
        string SubTitle = "(" + to_string(vCurrencies.size()) + ") Currency.";
        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl << endl;
        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(7) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)" << endl;
        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl;

        if (vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Currency Available In the System!";
        else {

            for (clsCurrency Currency : vCurrencies) {

                PrintCurrencyRecord(Currency);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl;
    }

};

