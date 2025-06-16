#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionsScreen : protected clsScreen {

private:

    enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eTransfer = 4, eTransferLog = 5, eShowMainMenue = 6 };

    static short _ReadTransactionsMenueOption() {
        
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter number between 1 and 6 ? ");
        return Choice;
    }

    static void _GoBackToTransactionsMenue() {

        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();
    }

    static void _ShowDepositScreen() {
        
        //cout << "\nDeposit Screen will be here..." << endl;
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithDrawScreen() {
    
        //cout << "\nWithdraw Screen will be here..." << endl;
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen() {
        
        //cout << "\nBalances Screen will be here..." << endl;
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _ShowTransferScreen() {
        
        //cout << "\nTransfer Screen Will be here..." << endl;
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen() {
        
        //cout << "Transfer Log Screen will be here..." << endl;
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
    {
        switch (TransactionMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            system("cls");
            _ShowWithDrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }


        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eTransfer:
        {
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eTransferLog:
        {
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowMainMenue:
        {

        }
        }
    }

public:

    static void ShowTransactionsMenue() {

        system("cls");

        if (!CheckAccessRights(clsUser::enPermissions::pTransactions)) {

            return;
        }

        _DrawScreenHeader("Transactions Menue Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tTransactions Menue Screen\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromTranactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
    }

};

