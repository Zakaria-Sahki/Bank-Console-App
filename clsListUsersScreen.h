#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
using namespace std;


class clsListUsersScreen : protected clsScreen {

private:

    static void _PrintUserRecordLine(clsUser User) {

        cout << setw(8) << left << "" << "| " << left << setw(15) << User.UserName;
        cout << "| " << left << setw(25) << User.FullName();
        cout << "| " << left << setw(12) << User.Phone;
        cout << "| " << left << setw(20) << User.Email;
        cout << "| " << left << setw(10) << User.Password;
        cout << "| " << left << setw(12) << User.Permissions;
    }


public:

    static void ShowUsersList() {


        vector<clsUser> vUsers = clsUser::GetUsersList();
        string Title = "Users List Screen";
        string SubTitle = "(" + to_string(vUsers.size()) + ") User(s).";
        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl << endl;
        cout << setw(8) << left << "" << "| " << left << setw(15) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions" << endl;
        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else {

            for (clsUser User : vUsers) {

                _PrintUserRecordLine(User);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl;
    }

};

