#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen {

private:

    static 	void _PrintClient(clsBankClient Client) {

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

    static void _ReadClientInfo(clsBankClient& Client) {

        cout << "\nFirst Name: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nLast Name: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEmail: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nPhone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nPin Code: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nAccount Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber("Invald input, enter again.");
    }

public:

	static void ShowUpdateClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClient)) {

            return;
        }

        _DrawScreenHeader("Update Client Screen");
		
        cout << "\nPlease enter an Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nThis account not found, Please enter another account number: ";
            AccountNumber = clsInputValidate::ReadString();
        }


        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "Do you want to update this client? y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y') {
            
            cout << "\n\nUpdate Client Info:";
            cout << "\n__________________________________\n";
            _ReadClientInfo(Client);

            clsBankClient::enSaveResults SaveResults;

            SaveResults = Client.Save();

            switch (SaveResults) {

            case clsBankClient::svFaildEmptyObject:
                cout << "\n\nError account was not saved because it;s Empty." << endl;
                break;

            case clsBankClient::svSucceeded:

                cout << "\n\nAccount updated successfully. :-)" << endl;
                _PrintClient(Client);
                break;
            }
        }
	}

};
