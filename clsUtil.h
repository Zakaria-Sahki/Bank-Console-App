#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsUtil {


public:

	enum enCharType {SmallLetter = 1, CapitalLetter = 2, Digit = 3, MixChar = 4, SpecialCharacter = 5};

	static int RandomNumber(int From, int To) {

		int randNum = rand() % (To - From + 1) + From;
		return randNum;
	}

	static void Srand() {
		
		srand((unsigned)time(NULL));
	}

	static char GetRandomCharacter(enCharType CharType) {

		if (CharType == enCharType::MixChar) {
			
			CharType = enCharType(RandomNumber(1, 3));
		}

		switch (CharType) {

		case enCharType::SmallLetter:
			return char(RandomNumber(97, 122));
			break;

		case enCharType::CapitalLetter:
			return char(RandomNumber(65, 90));
			break;

		case enCharType::Digit:
			return char(RandomNumber(48, 57));
			break;

		case enCharType::SpecialCharacter:
			return char(RandomNumber(33, 47));
			break;
		
		default:
			cout << "Incorrect choose!" << endl;
			break;
		}
	}

	static string GenerateWord(enCharType CharType, short length) {

		string Word = "";
		for (int i = 1; i <= length; i++) {

			Word = Word + GetRandomCharacter(CharType);
		}

		return Word;
	}

	static string GenerateKey(enCharType CharType) {

		string Key = "";

		Key = GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4);

		return Key;
	}

	static void GenerateKeys(enCharType CharType, int NumberOfKeys) {

		for (int i = 1; i <= NumberOfKeys; i++) {

			cout << "Key[" << i << "]: " << GenerateKey(CharType) << endl;

		}

	}

	static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To) {

		for (int i = 0; i <= arrLength - 1; i++) {
			arr[i] = RandomNumber(From, To);
		}
	}

	static void FillArrayWithRandomKeys(string arr[100], enCharType CharType, int arrLength) {

		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateKey(CharType);

	}

	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short LengthOfWord) {
		
		for (short i = 0; i < arrLength; i++) {
			
			arr[i] = GenerateWord(CharType, LengthOfWord);
		}
	}

	static string Tabs(short Number) {

		string S = "";
		for (short i = 0; i < Number; i++) {

			S += '\t';
		}
		return S;
	}

	static string EncryptText(string Text, short EncryptionKey) {

		for (int i = 0; i <= Text.length(); i++) {

			Text[i] = char((int)Text[i] + EncryptionKey);

		}
		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey) {

		for (int i = 0; i <= Text.length(); i++) {

			Text[i] = char((int)Text[i] - EncryptionKey);

		}
		return Text;
	}

	static void Swap(int& A, int& B) {

		int Tmp;
		Tmp = A;
		A = B;
		B = Tmp;
	}

	static void Swap(double &A, double &B) {
	
		double Tmp;
		Tmp = A;
		A = B;
		B = Tmp;
	}

	static void Swap(string& A, string& B) {
		
		string Tmp;
		Tmp = A;
		A = B;
		B = Tmp;
	}

	static void Swap(clsDate &Date1, clsDate &Date2) {
		
		clsDate TmpDate;
		TmpDate = Date1;
		Date1 = Date2;
		Date2 = TmpDate;
	}

	static void ShuffleArray(int arr[100], int arrLength) {

		for (int i = 0; i < arrLength; i++) {

			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static void ShuffleArray(string arr[100], int arrLength) {
		
		for (int i = 0; i < arrLength; i++) {
			
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static string NumberToText(int Number) {

		if (Number == 0) {

			return "";
		}
		if (Number >= 1 && Number <= 19) {

			string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"
			, "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

			return arr[Number] + " ";
		}
		if (Number >= 20 && Number <= 99) {

			string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

			return arr[Number / 10] + " " + NumberToText(Number % 10);
		}
		if (Number >= 100 && Number <= 199) {

			return "One Hundred " + NumberToText(Number % 100);
		}
		if (Number >= 200 && Number <= 999) {

			return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}
		if (Number >= 1000 && Number <= 1999) {

			return "One Thousand " + NumberToText(Number % 1000);
		}
		if (Number >= 2000 && Number <= 999999) {

			return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}
		if (Number >= 1000000 && Number <= 1999999) {

			return "One Million " + NumberToText(Number % 1000000);
		}
		if (Number >= 2000000 && Number <= 999999999) {

			return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}
		if (Number >= 1000000000 && Number <= 1999999999) {

			return "One Billion " + NumberToText(Number % 1000000000);
		}
		else {

			return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}
	}
};

