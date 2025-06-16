#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "Global.h"
#include "clsUser.h"
using namespace std;

class clsBankClient : public clsPerson {

private:

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
	enMode _Mode;
	struct stTransferLogRecord;

	static clsBankClient _ConvertLineToClientObject(string Line, string seperator = "#//#") {

		vector<string> vClientData;
		vClientData = clsString::Split(Line, seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#") {
		
		vector <string> vTransferLogRecordLine = clsString::Split(Line, Seperator);
		stTransferLogRecord TrnsferLogRecord;

		TrnsferLogRecord.DateTime = vTransferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTransferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTransferLogRecordLine[2];
		TrnsferLogRecord.Amount = stof(vTransferLogRecordLine[3]);
		TrnsferLogRecord.SourceBalanceAfter = stof(vTransferLogRecordLine[4]);
		TrnsferLogRecord.DestinationBalanceAfter = stof(vTransferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTransferLogRecordLine[6];

		return TrnsferLogRecord;
	}

	static clsBankClient _GetEmptyClientObject() {

		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;

	}

	static  vector <clsBankClient> _LoadClientsDataFromFile()
	{

		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();

		}

		return vClients;

	}

	static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsBankClient C : vClients) {

				if(C._MarkedForDelete == false){

					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;
				}

			}

			MyFile.close();

		}

	}

	void _Update() {
		
		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {
			
			if (C.AccountNumber() == AccountNumber()) {
				
				C = *this;
				break;
			}
		}

		_SaveCleintsDataToFile(_vClients);
	}

	void _AddNew() {

		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#") {

		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;

		return TransferLogRecord;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#") {

		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}


public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber,
		string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber() {

		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {

		_PinCode = PinCode;
	}

	string GetPinCode() {

		return _PinCode;
	}

	_declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance) {

		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance() {

		return _AccountBalance;
	}

	_declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	static clsBankClient Find(string AccountNumber) {

		vector<clsBankClient> vClients;
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in); // Read Mode

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber) {

					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {

		vector<clsBankClient> vClients;
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in); // Read Mode

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode) {

					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {

		clsBankClient Client = Find(AccountNumber);
		return !Client.IsEmpty();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults Save() {
		
		switch (_Mode) {
			
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
			break;

		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;

		case enMode::AddNewMode:

			//This will add new record to file or database
			if (clsBankClient::IsClientExist(_AccountNumber)) {
				
				return enSaveResults::svFaildAccountNumberExists;
			}
			else {
				
				_AddNew();

				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient &C : _vClients) {
			
			if (C.AccountNumber() == _AccountNumber){
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveCleintsDataToFile(_vClients);

		*this = _GetEmptyClientObject();
		return true;
	}

	static vector<clsBankClient> GetClientsList() {
		
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances() {
		
		vector<clsBankClient> vClients = clsBankClient::GetClientsList();
		double TotalBalances = 0;

		for (clsBankClient C : vClients) {
			
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount) {
		
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {
		
		if (Amount > _AccountBalance) {
			
			return false;
		}
		else {
			
			_AccountBalance -= Amount;
			Save();
		}
		return true;
	}

	bool Transfer(float Amount, clsBankClient &DestinationClient, string UserName) {
		
		if (Amount > AccountBalance) {
			
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		return true;
	}

	struct stTransferLogRecord {

		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float SourceBalanceAfter;
		float DestinationBalanceAfter;
		string UserName;
	};

	static vector <stTransferLogRecord> GetTransferLogList() {
		
		vector <stTransferLogRecord> vTransferLogRecords;
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			stTransferLogRecord TransferRecord;
			while (getline(MyFile, Line)) {
			
				TransferRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLogRecords.push_back(TransferRecord);
			}
			MyFile.close();
		}
		return vTransferLogRecords;
	}
};

