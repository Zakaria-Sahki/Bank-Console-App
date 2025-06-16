#pragma once
#include<iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>
using namespace std;

class clsTotalBalancesScreen : protected clsScreen {

private:

	static void PrintClientRecordBalanceLine(clsBankClient Client) {

        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;
	}

public:

	static void ShowTotalBalances() {
		
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "Total Balance Screen";
        string SubTitle = "\n\t\t\t\t\t\t     (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << endl << setw(8) << left << "" << "________________________________________________________________________________________________\n";

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients) {

                PrintClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;
        cout << "\n\t\t\t ( " << clsUtil::NumberToText(TotalBalances) << ")" << endl;

	}
};
