#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen {

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

    static void ShowDeleteUserScreen() {

        _DrawScreenHeader("Delete User Screen");

        cout << "\nPlease enter UserName: ";
        string UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName)) {

            cout << "\nUserName is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        cout << "\nAre you sure do you want to delete this clinet? y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y') {

            if (User.Delete()) {

                cout << "\nUser deleted successfuly." << endl;
                _PrintUser(User);
            }
            else {

                cout << "\nError User was not deleted." << endl;
            }
        }

    }

};

