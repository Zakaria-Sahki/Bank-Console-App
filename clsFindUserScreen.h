#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;


class clsFindUserScreen : protected clsScreen {

private:

    static void _PrintUser(clsUser User) {

        cout << "\nUser Card: " << endl;
        cout << "-------------------------------------" << endl;
        cout << "First Name : " << User.FirstName << endl;
        cout << "Last Name  : " << User.LastName << endl;
        cout << "Full Name  : " << User.FullName() << endl;
        cout << "Email      : " << User.Email << endl;
        cout << "Phone      : " << User.Phone << endl;
        cout << "UserName   : " << User.UserName << endl;
        cout << "Password   : " << User.Password << endl;
        cout << "Permissions: " << User.Permissions << endl;
        cout << "-------------------------------------" << endl;
    }

public:

	static void ShowFindUserScreen() {

		_DrawScreenHeader("Find User Screen");

		cout << "\nPlease enter UserName: ";
		string UserName = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(UserName)) {

			cout << "\nUserName is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty()) {

			cout << "\nUser Found :-)" << endl;
		}
		else {

			cout << "\nUser was not found :-(" << endl;
		}
		_PrintUser(User);
	}

};

