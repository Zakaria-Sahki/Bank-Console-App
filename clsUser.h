#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include "clsBankClient.h"
#include "Global.h"
#include "clsUtil.h"
using namespace std;

int EncryptionKey = 5;

class clsUser : public clsPerson {

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;
	struct stLoginRegisterRecord;


	static clsUser _ConvertLineToUserObject(string Line, string seperator = "#//#") {

		vector<string> vUsersData;
		vUsersData = clsString::Split(Line, seperator);

		return clsUser(enMode::UpdateMode, vUsersData[0], vUsersData[1], vUsersData[2], vUsersData[3],
			vUsersData[4], clsUtil::DecryptText(vUsersData[5], EncryptionKey), stoi(vUsersData[6]));
	}

	static clsUser _GetEmptyUserObject() {

		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#") {

		string stUserRecord = "";
		stUserRecord += User.FirstName + Seperator;
		stUserRecord += User.LastName + Seperator;
		stUserRecord += User.Email + Seperator;
		stUserRecord += User.Phone + Seperator;
		stUserRecord += User.UserName + Seperator;
		stUserRecord += clsUtil::EncryptText(User.Password, EncryptionKey) + Seperator;
		stUserRecord += to_string(User.Permissions);
		return stUserRecord;
	}

	static  vector <clsUser> _LoadUsersDataFromFile() {

		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::out); //overwrite

		string DataLine;
		if (MyFile.is_open()) {

			for (clsUser User : vUsers) {

				if (User._MarkedForDelete == false) {

					DataLine = _ConverUserObjectToLine(User);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update() {

		vector <clsUser> _vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : _vUsers) {

			if (User.UserName == _UserName) {

				User = *this;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);
	}

	void _AddNew() {

		_AddDataLineToFile(_ConverUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string seperator = "#//#") {

		vector<string> LoginRegisterDataLine;
		LoginRegisterDataLine = clsString::Split(Line, seperator);

		stLoginRegisterRecord LoginRegisterRecord;

		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2], EncryptionKey);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

	string _PrepareLogInRecord(string Seperator = "#//#") {
		
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += clsUtil::EncryptText(Password, EncryptionKey) + Seperator;
		LoginRecord += to_string(Permissions);

		return LoginRecord;
	}

public:

	enum enPermissions {pAll = -1, pListClient = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8,
	pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegisterList = 128 };

	struct stLoginRegisterRecord {

		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName,
		string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone) {
	
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty() {
		
		return (_Mode == enMode::EmptyMode);
	}

	void SetUserName(string UserName) {
		
		_UserName = UserName;
	}

	string GetUserName() {
		
		return _UserName;
	}

	_declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password) {
		
		_Password = Password;
	}

	string GetPassword() {
	
		return _Password;
	}

	_declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions) {
		
		_Permissions = Permissions;
	}

	int GetPermissions() {
		
		return _Permissions;
	}

	_declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName) {

		vector<clsUser> vUsers;
		fstream MyFile;

		MyFile.open("Users.txt", ios::in); // Read Mode

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName) {

					MyFile.close();
					return User;
				}
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password) {

		vector<clsUser> vUsers;
		fstream MyFile;

		MyFile.open("Users.txt", ios::in); // Read Mode

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password) {

					MyFile.close();
					return User;
				}
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
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
			if (clsUser::IsUserExist(_UserName)) {

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

	static bool IsUserExist(string UserName) {
		
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	static clsUser GetAddNewUserObject(string UserName) {

		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete() {

		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : _vUsers) {

			if (User.UserName == _UserName) {
				User._MarkedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);

		*this = _GetEmptyUserObject();
		return true;
	}

	static vector<clsUser> GetUsersList() {

		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission) {

		if (this->Permissions == enPermissions::pAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	void RegisterLogIn() {
		
		string stDataLine = _PrepareLogInRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	static  vector <stLoginRegisterRecord> GetLoginRegisterList() {

		vector <stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);//read Mode

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				stLoginRegisterRecord LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}
			MyFile.close();
		}
		return vLoginRegisterRecord;
	}

};


