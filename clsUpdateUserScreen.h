#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsUpdateUserScreen : protected clsScreen {

private:

    static void _ReadUserInfo(clsUser& User) {

        cout << "\nFirst Name: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nLast Name: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEmail: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nPhone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nPassword: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nPermissions: ";
        User.Permissions = ReadPermissionsToSet();
    }

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

    static int ReadPermissionsToSet() {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {

            Permissions += clsUser::enPermissions::pListClient;
        }


        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {

            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {

            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {

            Permissions += clsUser::enPermissions::pUpdateClient;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {

            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {

            Permissions += clsUser::enPermissions::pTransactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {

            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nShow Login Register? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {

            Permissions += clsUser::enPermissions::pLoginRegisterList;
        }
        return Permissions;
    }

public:

    static void ShowUpdateUserScreen() {

        _DrawScreenHeader("Update User Screen");

        cout << "\nPlease enter UserName: ";
        string UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName)) {

            cout << "\nThis UserName not found, Please enter another one: ";
            UserName = clsInputValidate::ReadString();
        }


        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        cout << "\nDo you want to update this User? y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y') {

            cout << "\n\nUpdate User Info:";
            cout << "\n__________________________________\n";
            _ReadUserInfo(User);

            clsUser::enSaveResults SaveResults;

            SaveResults = User.Save();

            switch (SaveResults) {

            case clsUser::svFaildEmptyObject:
                cout << "\n\nError User was not saved because it's Empty." << endl;
                break;

            case clsUser::svSucceeded:

                cout << "\n\nUser updated successfully. :-)" << endl;
                _PrintUser(User);
                break;
            }
        }
    }

};

