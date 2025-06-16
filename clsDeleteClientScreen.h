#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen {

private:

    static void _PrintClient(clsBankClient Client) {

        cout << "\nClient Card: " << endl;
        cout << "-------------------------------------" << endl;
        cout << "First Name : " << Client.FirstName << endl;
        cout << "Last Name  : " << Client.LastName << endl;
        cout << "Full Name  : " << Client.FullName() << endl;
        cout << "Email      : " << Client.Email << endl;
        cout << "Phone      : " << Client.Phone << endl;
        cout << "Acc. Number: " << Client.AccountNumber() << endl;
        cout << "PinCode    : " << Client.PinCode << endl;
        cout << "Acc.Balance: " << Client.AccountBalance << endl;
        cout << "-------------------------------------" << endl;
    }

public:

	static void ShowDeleteClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {

            return;
        }
		
		_DrawScreenHeader("Delete Client Screen");

        cout << "\nPlease enter Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nAre you sure do you want to delete this clinet? y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y') {

            if (Client.Delete()) {

                cout << "\nClient deleted successfuly." << endl;
                _PrintClient(Client);
            }
            else {

                cout << "\nError client was not deleted." << endl;
            }
        }

	}

};
