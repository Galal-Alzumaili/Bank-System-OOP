#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsListCurrenciesScreen.h";
#include "clsFindCurrencyScreen.h";
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculator.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
    enum enCurrencyExchangeMenueOptions {
        eListCurrencies = 1, eFindCurrency = 2,
        eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenue = 5
    };

    static short ReadCuurencyExchangeMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _GoBackToCurrencyExchangeMenue()
    {
        cout << "\n\nPress any key to go back to Cuurency Exchange Menue...";
        system("pause>0");
        ShowCurrencyExchangeScreen();

    }

    static void _ShowListCurrenciesScreen()
    {
        //cout << "List Currencies Screen Will be here soon...\n";
        clsListCurrenciesScreen::ShowListCurrencies();
    }

    static void _ShowFindCurrencyScreen()
    {
        //cout << "Find Currency Screen Will be here soon...\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        //cout << "Update Rate Screen Will be here soon...\n";
        clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculator::ShowCurrencyCalculatorScreen();

    }



    static void _PerformCurrencyExchangeMenueOption(enCurrencyExchangeMenueOptions CurrencyMenueOption)
    {
        switch (CurrencyMenueOption)
        {
        case enCurrencyExchangeMenueOptions::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeMenueOptions::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeMenueOptions::eUpdateRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeMenueOptions::eCurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeMenueOptions::eMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }


    }

public:

    static void ShowCurrencyExchangeScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Currency Exchange Main Menue");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyExchangeMenueOption((enCurrencyExchangeMenueOptions)ReadCuurencyExchangeMenueOption());
    }
};

