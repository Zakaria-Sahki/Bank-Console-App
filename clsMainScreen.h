#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"

#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"


using namespace std;

class clsMainScreen : protected clsScreen {

private:

    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eExit = 10
    };

    static short _ReadMainMenueOption() {
        
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter number between 1 and 10 ? ");
        return Choice;
    }

    static void _GoBackToMainMenue()
    {
        cout << "\n\nPress any key to go back to Main Menue...";
        system("pause>0");
        ShowMainMenue();
    }

    static void ShowAllClientsScreen() {
        
        clsClientListScreen::ShowClientList();
    }

    static void ShowAddNewClientsScreen() {
    
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void ShowDeleteClientScreen() {
    
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void ShowUpdateClientScreen() {
        
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void ShowFindClientScreen() {
        
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void ShowTransactionsMenue() {
        
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void ShowManageUsersMenue() {
        
        //cout << "\nManage users menue screen will be here..." << endl;
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    static void ShowLoginRegisterScreen() {
    
        //cout << "Login Register Screen will be here..." << endl;
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void ShowCurrenciesMenue() {
        
        clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
    }

    static void _Logout() {
        
        /*cout << "\nLogin screen will be here..." << endl;*/
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eLoginRegister:
            system("cls");
            ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eCurrencyExchange:
            system("cls");
            ShowCurrenciesMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _Logout();

            break;
        }

    }

public:

	static void ShowMainMenue()
    {
        system("cls");
        _DrawScreenHeader("Main Menue");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tMain Menue Screen\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";


        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }

};

