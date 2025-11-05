#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		short Tries = 3;
		bool LoginFaild = false;

		string Username, Password;

		do
		{
			if (LoginFaild)
			{
				Tries--;
				cout << "\nInvlaid Username/Password!\n";
				cout << "You have " << Tries << " Trial(s) to login.\n\n";

			}
			if (Tries == 0)
			{
				cout << "\n\nYou are Locked after 3 faild trails\n\n";
				return false;
			}


			cout << "Enter Username? ";
			cin >> Username;

			cout << "Enter Password? ";
			cin >> Password;

			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}


public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}
};

