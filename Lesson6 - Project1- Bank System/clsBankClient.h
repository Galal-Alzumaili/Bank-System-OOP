#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsUser.h"
#include "clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMpde = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector <string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Sperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Sperator;
		stClientRecord += Client.LastName + Sperator;
		stClientRecord += Client.Email + Sperator;
		stClientRecord += Client.Phone + Sperator;
		stClientRecord += Client.AccountNumber() + Sperator;
		stClientRecord += Client.PinCode + Sperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static vector <clsBankClient> _LoadClientDataFromFile()
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out); // OverWrite mode

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient& c : vClients)
			{
				if (c.MarkedForDeleted() == false)
				{
					// we only write records that are not marked for delete.
					DataLine = _ConvertClientObjectToLine(c);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
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

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMpde, "", "", "", "", "", "", 0);
	}

	// this for save transfer log
	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#")
	{
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

	void _RegisterTanserLog(double Amount, clsBankClient DestinationClient, string UserName)
	{

		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	struct stTransferLog;

	static stTransferLog _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		vector<string> vRecord;
		vRecord = clsString::Split(Line, Seperator);

		stTransferLog TransferLogRecord;
		TransferLogRecord.DateTime = vRecord[0];
		TransferLogRecord.s_AccountNumber = vRecord[1];
		TransferLogRecord.d_AccountNumber = vRecord[2];
		TransferLogRecord.Amount = stof(vRecord[3]);
		TransferLogRecord.s_Balance = stof(vRecord[4]);
		TransferLogRecord.d_Balance = stof(vRecord[5]);
		TransferLogRecord.User = vRecord[6];

		return TransferLogRecord;
	}

public:

	struct stTransferLog
	{
		string DateTime;
		string s_AccountNumber;
		string d_AccountNumber;
		float Amount;
		float s_Balance;
		float d_Balance;
		string User;

	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMpde);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	// Only Read Property
	string AccountNumber()
	{
		return _AccountNumber;
	}

	// Set Property
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	// Get Property
	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	// Set Property
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	// Get Property
	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec (property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;
	/*
	No UI Related code inside object.
	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}
	*/
	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClient;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

				vClient.push_back(Client);
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vClient;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // Read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				vClient.push_back(Client);
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	enum enSaveResults {svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMpde:
		{
			if (IsEmpty())
				return enSaveResults::svFaildEmptyObject;
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}

		case enMode::AddNewMode:
		{
			// This will add new record to file or database
			if (clsBankClient::svFaildEmptyObject(_AccountNumber))
				return enSaveResults::svFaildAccountNumberExists;

			else
			{
				_AddNew();

				// We need to set the mode to update after add new 
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	bool Delete()
	{
		vector<clsBankClient> _vClients;
		_vClients = _LoadClientDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientDataFromFile();
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
			return false;
		else
		{
			_AccountBalance -= Amount;
			Save();
		}
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient& Client : vClients)
			TotalBalances += Client.AccountBalance;

		return TotalBalances;
	}


	bool Transfer (float Amount, clsBankClient& DestinationClient, string UserName )
	{
		if (Amount > AccountBalance)
			return false;

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTanserLog(Amount, DestinationClient, UserName);
		return true;
	}

	static vector<stTransferLog> GetTransferLogList()
	{
		vector<stTransferLog> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			stTransferLog TransferLogRecord;

			while (getline(MyFile, Line))
			{
				TransferLogRecord = _ConvertTransferLogLineToRecord(Line);

				vLoginRegisterRecord.push_back(TransferLogRecord);
			}

			MyFile.close();
		}

		return vLoginRegisterRecord;
	}

};

