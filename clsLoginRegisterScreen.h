#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsLoginRegisterScreen : protected clsScreen {

private:

	static void PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord User) {

		cout << setw(8) << left << "" << "| " << left << setw(35) << User.DateTime;
		cout << "| " << left << setw(20) << User.UserName;
		cout << "| " << left << setw(20) << User.Password;
		cout << "| " << left << setw(10) << User.Permissions;
	}

public:

	static void ShowLoginRegisterScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegisterList)) {
			
			return;
		}
	
		vector<clsUser::stLoginRegisterRecord> vUsers = clsUser::GetLoginRegisterList();


		string Title = "Login Register List Screen";
		string SubTitle = "(" + to_string(vUsers.size()) + ") Record(s).";
		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "____________________________________________________________________________________________________________" << endl << endl;
		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions" << endl;
		cout << setw(8) << left << "" << "____________________________________________________________________________________________________________" << endl;

		if (vUsers.size() == 0)
			cout << "\t\t\t\tNo Logins Available In the System!";
		else {

			for (clsUser::stLoginRegisterRecord User : vUsers) {

				PrintLoginRegisterRecordLine(User);
				cout << endl;
			}
		}
		cout << setw(8) << left << "" << "____________________________________________________________________________________________________________" << endl;

	}

};

