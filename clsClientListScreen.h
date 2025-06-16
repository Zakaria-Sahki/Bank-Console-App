#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;


class clsClientListScreen : protected clsScreen {

private:

    static void PrintClientRecord(clsBankClient Client) {

        cout << setw(8) << left << "" << "| " << left << setw(15) << Client.AccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.Phone;
        cout << "| " << left << setw(20) << Client.Email;
        cout << "| " << left << setw(10) << Client.PinCode;
        cout << "| " << left << setw(12) << Client.AccountBalance;
    }

public:

    static void ShowClientList() {

        if (!CheckAccessRights(clsUser::enPermissions::pListClient)) {

            return;
        }
        
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "client List Screen";
        string SubTitle = "(" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl << endl;
        cout << setw(8) << left << "" << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Account Balance" << endl;
        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else {

            for (clsBankClient Client : vClients) {

                PrintClientRecord(Client);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl;
    }

};

