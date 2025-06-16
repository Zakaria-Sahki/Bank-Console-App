#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsString.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen {

private:

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

public:

    static void ShowAddNewClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {

            return;
        }

        _DrawScreenHeader("Add New Client Screen");

        cout << "\nPlease enter an Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nAccount number is already used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();

        switch (SaveResult) {

        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount added successfuly." << endl;
            _PrintClient(NewClient);
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;

        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }

    }

};