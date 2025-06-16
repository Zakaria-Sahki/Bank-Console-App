
#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"

#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;

class clsManageUsersScreen : protected clsScreen {

private:

    enum enManageUsersMenueOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };

    static short _ReadManageUsersMenueOption() {
        
        cout << setw(37) << left << "" << "Choose what do you want to do ? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1,6, "Invalid input enter anohter one: ");
        return Choice;
    }

    static void GoBackToManageUsersMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowManageUsersMenue();

    }

    static void ShowListUsersScreen() {
        
        //cout << "\nList Users Screen will be here..." << endl;
        clsListUsersScreen::ShowUsersList();

    }

    static void ShowAddNewUserScreen() {
    
        //cout << "\nAdd New User Screen will be here..." << endl;
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void ShowDeleteUserScreen() {
        
        //cout << "\nDelete User Screen will be here..." << endl;
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void ShowUpdateUserScreen() {
    
        //cout << "\nUpdate User Screen will be here..." << endl;
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void ShowFindUserScreen() {
    
        //cout << "\nFind User Screen will be here..." << endl;
        clsFindUserScreen::ShowFindUserScreen();
    }



    static void _PerfromManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
    {
        switch (ManageUsersMenueOption)
        {
        case enManageUsersMenueOptions::eListUsers:
        {
            system("cls");
            ShowListUsersScreen();
            GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eAddNewUser:
        {
            system("cls");
            ShowAddNewUserScreen();
            GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eDeleteUser:
        {
            system("cls");
            ShowDeleteUserScreen();
            GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eUpdateUser:
        {
            system("cls");
            ShowUpdateUserScreen();
            GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eFindUser:
        {
            system("cls");

            ShowFindUserScreen();
            GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eMainMenue:
        {

        }
        }
    }

public:

	static void ShowManageUsersMenue() {
		
        system("cls");

        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers)) {

            return;
        }

        _DrawScreenHeader("Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tManage Users Menue \n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersMenueOption());
	}

};

