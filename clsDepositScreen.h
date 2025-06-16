#pragma once
#include <iostream>
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;


class clsDepositScreen : protected clsScreen {

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

    static string _ReadAccountNumber() {

        string AccountNumber = "";
        cout << "\nPlease enter Account Number: ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:

    static void ShowDepositScreen() {
        
        _DrawScreenHeader("Deposit Screen");

        string AccountNumber = _ReadAccountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
        
            cout << "\nClient with [ " << AccountNumber << " ] not found, please enter another one: ";
            cout << endl;
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        char Answer = 'n';
        cout << "\nAre you sur you want to perform this transaction? y/n? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y') {
            
            Client1.Deposit(Amount);
            cout << "\nAmount Deposited Successfuly." << endl;
            cout << "\nNew Balance Is: " << Client1.AccountBalance << endl;
        }
        else {
            
            cout << "\nOperation was cancelled." << endl;
        }
    }

};

