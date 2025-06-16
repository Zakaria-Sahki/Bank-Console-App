#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindClientScreen : protected clsScreen {

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

public:

	static void ShowFindClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {
			
			return;
		}
		
		_DrawScreenHeader("Find Client Screen");

		cout << "\nPlease enter account number: ";
		string AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			
			cout << "\nAccount Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if (!Client.IsEmpty()) {
			
			cout << "\nClient Found :-)" << endl;
		}
		else {
			
			cout << "\nClient was not found :-(" << endl;
		}
		_PrintClient(Client);
	}

};

