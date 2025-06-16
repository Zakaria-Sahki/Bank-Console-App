#pragma once
#include <iostream>
#include "clsUtil.h"
#include "Global.h"
#include "clsUser.h"
#include "clsDate.h"
using namespace std;

class clsScreen {

private:

	static void _PrintUserName() {
		
		cout << endl << clsUtil::Tabs(4) << "   User: " << CurrentUser.UserName << endl;
	}

	static void _PrintLocalDate() {
		
		cout << clsUtil::Tabs(4) << "   Date: " << clsDate::DateToString(clsDate::GetSystemDateForAge()) << endl;
	}

protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "") {

		cout << clsUtil::Tabs(4) << "   _______________________________________________" << endl << endl;
		cout << clsUtil::Tabs(6) << "    " << Title << endl;
		if (SubTitle != "") {
			
			cout << clsUtil::Tabs(6) << "    " << SubTitle << endl;
		}
		cout << clsUtil::Tabs(4) << "   _______________________________________________" << endl << endl;
		_PrintUserName();
		_PrintLocalDate();
		cout << endl;
	}

	static bool CheckAccessRights(clsUser::enPermissions Permissions) {
		
		if (CurrentUser.CheckAccessPermission(Permissions)) {
			
			return true;
		}
		else {
			
			cout << clsUtil::Tabs(4) << "   _______________________________________________" << endl << endl;
			cout << clsUtil::Tabs(5) << "Access Denied! Contact your Admin." << endl;
			cout << clsUtil::Tabs(4) << "   _______________________________________________" << endl;
			return false;
		}
	}

};

