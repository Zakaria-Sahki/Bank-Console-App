#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <vector>

class clsTransferLogScreen : protected clsScreen {

private:

	static void PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLog) {
		
        cout << setw(8) << left << "" << "| " << left << setw(30) << TransferLog.DateTime;
        cout << "| " << left << setw(10) << TransferLog.SourceAccountNumber;
        cout << "| " << left << setw(10) << TransferLog.DestinationAccountNumber;
        cout << "| " << left << setw(10) << TransferLog.Amount;
        cout << "| " << left << setw(10) << TransferLog.SourceBalanceAfter;
        cout << "| " << left << setw(10) << TransferLog.DestinationBalanceAfter;
        cout << "| " << left << setw(10) << TransferLog.UserName;
	}

public:

	static void ShowTransferLogScreen() {
		
		vector<clsBankClient::stTransferLogRecord> vTransferLogRecords = clsBankClient::GetTransferLogList();

		string Title = "Transfer Log List Screen";
		string SubTitle = "(" + to_string(vTransferLogRecords.size()) + ") Record(s).";
		_DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl << endl;
        cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(10) << "S.Acct";
        cout << "| " << left << setw(10) << "D.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "D.Balance";
        cout << "| " << left << setw(10) << "User" << endl;
        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl;

        if (vTransferLogRecords.size() == 0)
            cout << "\t\t\t\tNo Transfer Logs Available In the System!";
        else {

            cout << endl;
            for (clsBankClient::stTransferLogRecord Record : vTransferLogRecords) {

                PrintTransferLogRecordLine(Record);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "______________________________________________________________________________________________________________________" << endl;

	}

};

