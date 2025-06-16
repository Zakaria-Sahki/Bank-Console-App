#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString {

private:

	string _Value;

public:

	clsString() {
		
		_Value = "";
	}

	clsString(string Value) {
	
		_Value = Value;
	}

	void SetValue(string Value) {
		
		_Value = Value;
	}

	string GetValue() {
		
		return _Value;
	}

	_declspec(property(get = GetValue, put = SetValue)) string Value;

	static short CountWords(string S1) {

		string delim = " "; // delimiter
		short Counter = 0;
		short pos = 0;
		string sWord; // define a string variable

		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delim)) != std::string::npos) {

			sWord = S1.substr(0, pos); // store the word
			if (sWord != "") {
				Counter++;
			}
			//erase() until positon and move to next word.
			S1.erase(0, pos + delim.length());
		}

		if (S1 != "") {

			Counter++; // it counts the last word of the string
		}

		return Counter;
	}

	short CountWords() {
		
		return CountWords(_Value);
	}

	static void PrintFirstLetterOfEachWord(string Text) {

		bool isFirstLetter = true;
		cout << "\nFirst letters of this string: \n";
		for (short i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ' && isFirstLetter) {
				cout << Text[i] << endl;
			}
			isFirstLetter = Text[i] == ' ' ? true : false;
		}
	}

	void PrintFirstLetterOfEachWord() {
		
		PrintFirstLetterOfEachWord(_Value);
	}

	static string UpperFirstLetterOfEachWord(string Text) {

		bool isFirstLetter = true;
		for (short i = 0; i < Text.length(); i++) {

			if (Text[i] != ' ' && isFirstLetter) {

				Text[i] = toupper(Text[i]);
			}
			isFirstLetter = Text[i] == ' ' ? true : false;
		}
		return Text;
	}

	void UpperFirstLetterOfEachWord() {
		
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string S1) {

		bool isFirstLetter = true;
		for (short i = 0; i < S1.length(); i++) {

			if (S1[i] != ' ' && isFirstLetter) {

				S1[i] = tolower(S1[i]);
			}
			isFirstLetter = S1[i] == ' ' ? true : false;
		}
		return S1;
	}

	void LowerFirstLetterOfEachWord() {
		
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(string S1) {

		for (short i = 0; i < S1.length(); i++) {

			S1[i] = toupper(S1[i]);
		}
		return S1;
	}

	void UpperAllString() {
	
		_Value = UpperAllString(_Value);
	}

	static string LowerAllString(string S1) {

		for (short i = 0; i < S1.length(); i++) {

			S1[i] = tolower(S1[i]);
		}
		return S1;
	}

	void LowerAllString() {
		
		_Value = LowerAllString(_Value);
	}

	static string InvertAllStringLettersCase(string S1) {

		for (short i = 0; i < S1.length(); i++) {

			S1[i] = InvertLetterCase(S1[i]);
		}
		return S1;
	}

	void InvertAllStringLettersCase() {
		
		_Value = InvertAllStringLettersCase(_Value);
	}

	static short CountCapitalLetters(string S1) {

		short Counter = 0;
		for (short i = 0; i < S1.length(); i++) {

			if (isupper(S1[i]))
				Counter++;
		}

		return Counter;
	}

	short CountCapitalLetters() {
		
		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetters(string S1) {

		short Counter = 0;
		for (short i = 0; i < S1.length(); i++) {

			if (islower(S1[i]))
				Counter++;
		}

		return Counter;
	}

	short CountSmallLetters() {
		
		return CountSmallLetters(_Value);
	}

	static short CountSpecificeLetter(string S1, char Letter, bool MatchCase = true) {

		short Counter = 0;
		for (short i = 0; i < S1.length(); i++) {

			if (MatchCase) {

				if (S1[i] == Letter)
					Counter++;
			}
			else {

				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}
		}
		return Counter;
	}

	short CountSpecificeLetter(char Letter, bool MatchCase) {
		
		return CountSpecificeLetter(_Value, Letter, MatchCase);
	}

	static short CountVowels(string S1) {

		short Counter = 0;
		for (short i = 0; i < S1.length(); i++) {

			if (isVowel(S1[i]))
				Counter++;
		}
		return Counter;
	}

	short CountVowels() {
		
		return CountVowels(_Value);
	}

	static void PrintVowels(string S1) {

		cout << "\nVowels in string are: ";

		for (short i = 0; i < S1.length(); i++) {

			if (isVowel(S1[i]))
				cout << S1[i] << "  ";
		}
		cout << endl;
	}

	void PrintVowels() {
		
		PrintVowels(_Value);
	}

	static void PrintEachWordInString(string S1) {

		string delimt = " "; // delimiter
		cout << "\nYour string words are: " << endl << endl;
		short pos = 0;
		string sWord; // define a string variable

		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delimt)) != std::string::npos) {

			sWord = S1.substr(0, pos); // store the word
			if (sWord != "") {

				cout << sWord << endl;
			}
			S1.erase(0, pos + delimt.length()); // erase() until positon and move to next word.
		}

		if (S1 != "")
			cout << S1 << endl; // it print last word of the string
	}

	void PrintEachWordInString() {
		
		PrintEachWordInString(_Value);
	}

	static vector <string> Split(string S1, string delim) {

		vector <string> vString;
		short pos = 0;
		string sWord; // define a string variable

		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delim)) != std::string::npos) {

			sWord = S1.substr(0, pos); // store the word
			if (sWord != "") {
				vString.push_back(sWord);
			}
			//erase() until positon and move to next word.
			S1.erase(0, pos + delim.length());
		}

		if (S1 != "") {

			vString.push_back(S1); // it adds the last word of the string
		}

		return vString;
	}

	vector <string> Split(string delim) {
		
		return Split(_Value, delim);
	}

	static string TrimLeft(string S1) {

		for (short i = 0; i < S1.length(); i++) {

			if (S1[i] != ' ') {

				return S1.substr(i, S1.length() - i);
			}
		}
		return "";
	}

	void TrimLeft() {
		
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string S1) {

		for (short i = S1.length() - 1; i >= 0; i--) {

			if (S1[i] != ' ') {

				return S1.substr(0, i + 1);
			}
		}
		return "";
	}

	void TrimRight() {

		_Value = TrimRight(_Value);
	}

	static string Trim(string S1) {

		return TrimLeft(TrimRight(S1));
	}

	void Trim() {
		
		_Value = Trim(_Value);
	}

	static string ReverseWordsInString(string S1) {

		vector <string> vString;
		string S2 = "";
		string Delim = " ";
		vString = Split(S1, Delim);

		// declare iterator
		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin()) {

			--iter;

			S2 = S2 + *iter + Delim;

		}
		S2 = S2.substr(0, S2.length() - Delim.length()); //remove last space.

		return S2;
	}

	void ReverseWordsInString() {
		
		_Value = ReverseWordsInString(_Value);
	}

	static string ReplaceWordInStringUsingBuiltInFunction(string S1, string StringToReplace, string ReplaceTo) {

		short pos = S1.find(StringToReplace);
		while (pos != std::string::npos) {

			S1 = S1.replace(pos, StringToReplace.length(), ReplaceTo);
			pos = S1.find(StringToReplace); //find next
		}

		return S1;
	}

	void ReplaceWordInStringUsingBuiltInFunction(string StringToReplace, string ReplaceTo) {
	
		_Value = ReplaceWordInStringUsingBuiltInFunction(_Value, StringToReplace, ReplaceTo);
	}

	static string RemovePunctuationsFromString(string S1) {

		string S2 = "";
		for (short i = 0; i < S1.length(); i++) {

			if (!ispunct(S1[i])) {

				S2 += S1[i];
			}
		}
		return S2;
	}

	void RemovePunctuationsFromString() {
		
		_Value = RemovePunctuationsFromString(_Value);
	}

	static short Length(string S1) {
		
		return S1.length();
	}

	short Length() {
		
		return _Value.length();
	}

	static bool isVowel(char Ch1) {

		Ch1 = tolower(Ch1);
		return (Ch1 == 'a' || Ch1 == 'e' || Ch1 == 'i' || Ch1 == 'o' || Ch1 == 'u');
	}

	static char InvertLetterCase(char char_01) {

		return isupper(char_01) ? tolower(char_01) : toupper(char_01);
	}


};

