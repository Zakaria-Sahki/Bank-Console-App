#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;


class clsTransferScreen : protected clsScreen {

private:

	static string ReadAccountNumber(string Message) {
		
		cout << endl << Message;
		string AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
		
			cout << "\nAccount Number is not found, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static void PrintClientCard(clsBankClient Client) {
		
		cout << "\nClient Card: " << endl;
		cout << "_____________________________" << endl;
		cout << "\nFull Name  : " << Client.FullName() << endl;
		cout << "Acc. Number: " << Client.AccountNumber() << endl;
		cout << "Balance   : " << Client.AccountBalance << endl;
		cout << "_____________________________" << endl;
	}

	static float ReadAmount(clsBankClient SourceClient) {
		
		cout << "\nEnter transfer amount? ";
		float Amount = clsInputValidate::ReadFloatNumber();

		while (Amount > SourceClient.AccountBalance) {
			
			cout << "\nAmount Exceeds the available Balance, Enter another Amount? ";
			Amount = clsInputValidate::ReadFloatNumber();
		}
		return Amount;
	}

public:

	static void ShowTransferScreen() {
	
		_DrawScreenHeader("Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(ReadAccountNumber("Please enter account number to transfer from: "));
		PrintClientCard(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(ReadAccountNumber("Please enter account number to transfer To: "));
		PrintClientCard(DestinationClient);

		float Amount = ReadAmount(SourceClient);

		cout << "\nAre you sur you want to perform this operation? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName)) {
				
				cout << "\nTransfer Done Successfully." << endl;
			}
			else {

				cout << "\nTransfer Faild." << endl;
			}
		}
		PrintClientCard(SourceClient);
		PrintClientCard(DestinationClient);
	}

};

