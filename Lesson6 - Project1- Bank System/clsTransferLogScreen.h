#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <vector>

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:
    static void PrintTransferLogRecordLine(clsBankClient::stTransferLog TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.s_AccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.d_AccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.s_Balance;
        cout << "| " << setw(10) << left << TransferLogRecord.d_Balance;
        cout << "| " << setw(8) << left << TransferLogRecord.User;


    }
public:

	static void ShowTransferLogScreen()
	{
		vector<clsBankClient::stTransferLog> TransferLog;
		TransferLog = clsBankClient::GetTransferLogList();

		string Title = "\tLogin Register List Screen";
		string SubTitle = "\t\t(" + to_string(TransferLog.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (TransferLog.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTransferLog Record : TransferLog)
            {

                PrintTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
	
};

