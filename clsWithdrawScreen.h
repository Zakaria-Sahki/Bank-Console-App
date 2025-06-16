#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;

class clsWithdrawScreen : protected clsScreen {

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

    static string _ReadAccountNumber() {

        string AccountNumber = "";
        cout << "\nPlease enter Account Number: ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:

    static void ShowWithdrawScreen() {
    
        _DrawScreenHeader("Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            
            cout << "\nClient with [ " << AccountNumber << " ] not found, please enter another one: ";
            cout << endl;
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        double Amount = 0;
        cout << "\nPlease enter withdraw amount: ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sur you want to perform this transaction? y/n?  ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            
            if (Client1.Withdraw(Amount)) {
                
                cout << "\nAmount Withdrew Successfuly." << endl;
                cout << "\nNew Balance Is: " << Client1.AccountBalance << endl;
            }
            else {
                
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmount to withdraw is: " << Amount << endl;
                cout << "\nYou Balance is: " << Client1.AccountBalance;
            }
        }
        else {
            
            cout << "\nOperation was Cancelled." << endl;
        }
    }

};

