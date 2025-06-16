#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsString.h"


class clsCurrency {

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;
	enMode _Mode;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Seperator = "#//#") {
		
		vector<string> vCurrencyData = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#") {
		
		string stCurrencyRecord = "";

		stCurrencyRecord += Currency.Country() + Seperator;
		stCurrencyRecord += Currency.CurrencyCode() + Seperator;
		stCurrencyRecord += Currency.CurrencyName() + Seperator;
		stCurrencyRecord += to_string(Currency.Rate());

		return stCurrencyRecord;
	}

    static  vector <clsCurrency> _LoadCurrencysDataFromFile() {

        vector <clsCurrency> vCurrencys;

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

                vCurrencys.push_back(Currency);
            }

            MyFile.close();

        }

        return vCurrencys;

    }

    static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys) {

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open()) {

            for (clsCurrency C : vCurrencys) {

                DataLine = _ConvertCurrencyObjectToLine(C);
                MyFile << DataLine << endl;
            }

            MyFile.close();

        }

    }

    void _Update() {

        vector <clsCurrency> _vCurrencys;
        _vCurrencys = _LoadCurrencysDataFromFile();

        for (clsCurrency& C : _vCurrencys)
        {
            if (C.CurrencyCode() == CurrencyCode())
            {
                C = *this;
                break;
            }

        }

        _SaveCurrencyDataToFile(_vCurrencys);

    }

    static clsCurrency _GetEmptyCurrencyObject() {

        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {

		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string Country() {
		
		return _Country;
	}

	string CurrencyCode() {
		
		return _CurrencyCode;
	}

	string CurrencyName() {
		
		return _CurrencyName;
	}

	void UpdateRate(float Rate) {
		
		_Rate = Rate;
		_Update();
	}

	float Rate() {
		
		return _Rate;
	}

	bool IsEmpty() {
		
		return (enMode::EmptyMode == _Mode);
	}

	// What is that ??????????????????????????????????????????????????????????????????????????????
	static vector <clsCurrency> GetAllCurrencyList() {
		
		return _LoadCurrencysDataFromFile();
	}

	static clsCurrency FindByCode(string CurrencyCode) {

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in); // Read Mode

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode) {

					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {

		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in); // Read Mode

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country) {

					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {
		
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return !(Currency.IsEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList() {
		
		return _LoadCurrencysDataFromFile();
	}




	float ConvertToUSD(float Amount) {
	
		return float(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {
		
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD") {
			
			return AmountInUSD;
		}

		return float(AmountInUSD * Currency2.Rate());
	}
};

