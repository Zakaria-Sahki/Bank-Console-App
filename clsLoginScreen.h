#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include "Global.h"
using namespace std;

class clsLoginScreen : protected clsScreen {

private:

	static bool _Login() {
		
		bool LoginFaild = false;
		string UserName = "", Password = "";
		short FaildLoginCount = 0;

		do {

			if (LoginFaild) {

				FaildLoginCount++;
				cout << "\nInvalid Username/Password, try again\n";
				cout << "You have " << (3- FaildLoginCount) << " Trials to login." << endl << endl;
			}

			if (FaildLoginCount == 3) {
				
				cout << "\nYou are locked after 3 faild trails." << endl << endl;
				return false;
			}

			cout << "Please enter Username: ";
			cin >> UserName;
			cout << "Please enter Password: ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);
		
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen() {
		
		system("cls");
		_DrawScreenHeader("Login Screen");
		return _Login();
	}

};

