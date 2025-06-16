
#include <iostream>
#include "clsMainScreen.h"
#include "clsUser.h"
#include "clsLoginScreen.h"
#include "clsCurrency.h"
using namespace std;


int main() {
 
    while (true) {
        
        if (!clsLoginScreen::ShowLoginScreen()) {
            
            break;
        }
    }
    return 0;
}


// Username   : User15
// Password   : AAAA
// Permissions: -1