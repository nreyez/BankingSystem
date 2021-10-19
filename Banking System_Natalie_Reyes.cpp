/*******************************************************************************************
 ConsoleApplication1.cpp : Defines the entry point for the console application.
 Author : Natalie A. Reyes
 Created : April 2019
 The project 1 program will help in the management of a private bank.
 *******************************************************************************************/


#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
//global variables
const int totalCapacity = 100;
int actual_number_of_accounts = 0;

struct account_information
{
	int serial;
	int account_number;
	string first_name;
	string last_name;
	float balance;
	bool flag;
};

void printOptionsMenu();
// printOptionsMenu - prints (show on the screen) the options menu
int getArrayIndexOfAccount(int, account_information[]);
// getArrayIndexOfAccount - returns the index of the account in the array if found; otherwise; the function returns - 1
void depositMoney(int, float, account_information[]);
//update the balance and will save the transactions information (including the date and time) in the file that has the same name as the account number.
void withdrawMoney(int, float, account_information[]);
//withdrawMoney- The function will check the balance before processing the transaction. 
void transferMoney(int, int, float, account_information[]);
//transferMoney- The function will check the balance (i.e. the balance in the account to transfer the money from) before processing the transaction.
void showTransactions(int, account_information[]);
//showTransactions- The function will display on the screen all transactions using the saved transactions information in the file that has the same name as theaccount number.
void openAccount(account_information[]);
//openAccount- The function will add a new record to the array of accounts and accounts.txt as well as create a new file and update the transactions information with the opening balance.
void closeAccount(int, account_information[]);
//closeAccount-  checks the balance before flagging the account as deleted
void sortBalances(account_information[]);
//sortBalances- The function will sort and display the accounts (without changing the original array) from largest balance to smallest.
void sortNames(account_information[]);
//sortNames- The function will sort and display the accounts (without changing the original array) in alphabetical order using the account owner’s name.



int main()
{
	//Variable Declaration Section
	float amount = 0;
	int users_choice = 0;
	int account_number = 0, account_number1 = 0;
	int returned_index = -1, returned_index1 = -1;
	ifstream myFile;
	account_information array_of_accounts[totalCapacity];

	//Instructions Section
	myFile.open("accounts.txt");
	//open the file & check that the file opened successfully
	if (myFile.fail())
	{
		cout << "Error: Failed to open accounts.txt file." << endl;
		exit(1);
	}
	else
	{
		while (!myFile.eof())
		{
			myFile >> array_of_accounts[actual_number_of_accounts].serial;
			myFile >> array_of_accounts[actual_number_of_accounts].account_number;
			myFile >> array_of_accounts[actual_number_of_accounts].first_name;
			myFile >> array_of_accounts[actual_number_of_accounts].last_name;
			myFile >> array_of_accounts[actual_number_of_accounts].balance;
			myFile >> array_of_accounts[actual_number_of_accounts].flag;
			actual_number_of_accounts++;
		}
		myFile.close();
	}
	do
	{
		printOptionsMenu();
		cin >> users_choice;
		switch (users_choice)
		{
		case 1:
			cout << "Please enter account number" << endl;
			cin >> account_number;
			returned_index = getArrayIndexOfAccount(account_number, array_of_accounts);
			if (returned_index == -1)
			{
				cout << "Account does not exist." << endl;
			}
			else
			{
				cout << "Please enter amount to be deposited." << endl;
				cin >> amount;
				depositMoney(returned_index, amount, array_of_accounts);
			
			}
			break;
		case 2:
			cout << "Please enter account number" << endl;
			cin >> account_number;
			returned_index = getArrayIndexOfAccount(account_number, array_of_accounts);
			if (returned_index == -1)
			{
				cout << "Account does not exist." << endl;
			}
			else
			{
				cout << "Please enter amount to be withdrawn." << endl;
				cin >> amount;
				withdrawMoney(returned_index, amount, array_of_accounts);
				
			}
			break;
		case 3:
			cout << "Please enter account number" << endl;
			cin >> account_number;
			cout << "Please enter the the account number you wish to transfer to." << endl;
			cin >> account_number1;
			returned_index = getArrayIndexOfAccount(account_number, array_of_accounts);
			returned_index1 = getArrayIndexOfAccount(account_number1, array_of_accounts);
			if (returned_index != -1 && returned_index1 != -1)
			{
				cout << "Please enter amount you wish to transfer." << endl;
				cin >> amount;
				transferMoney(returned_index, returned_index1, amount, array_of_accounts);	
			}
			else
			{
				
				cout << "One of the accounts does not exist." << endl;
				
			}
			break;
		case 4:
			cout << "Please enter account number" << endl;
			cin >> account_number;
			returned_index = getArrayIndexOfAccount(account_number, array_of_accounts);
			if (returned_index == -1)
			{
				cout << "Account does not exist." << endl;
			}
			else
			{
				showTransactions(returned_index, array_of_accounts);


			}
			break;
		case 5:
			openAccount(array_of_accounts);
			break;
		case 6:
			cout << "Please enter account number" << endl;
			cin >> account_number;
			returned_index = getArrayIndexOfAccount(account_number, array_of_accounts);
			closeAccount(returned_index, array_of_accounts);
			break;
		case 7:
			sortBalances(array_of_accounts);
			break;
		case 8:
			sortNames(array_of_accounts);
			break;
		case 9:
			//quit
			break;
		default:
			cout << "Error: Invalid Input" << endl;
			break;
		}
	} while (users_choice != 9);



	
	/*for (int i = 0; i < actual_number_of_accounts; i++)
	{
		cout << array_of_accounts[i].serial << " ";
		cout << array_of_accounts[i].account_number << " ";
		cout << array_of_accounts[i].first_name << " ";
		cout << array_of_accounts[i].last_name << " ";
		cout << array_of_accounts[i].balance << " ";
		cout << array_of_accounts[i].flag << endl;
	}
	cout << actual_number_of_accounts<<endl;*/
	//save the array to the account.txt
	return 0;
}

void printOptionsMenu()
{
	cout << "---------------------------------------------------------------------------------------------------- " << endl;
	cout << "Please choose one of the following options : " << endl;
	cout << "1. Deposit Money" << endl;
	cout << "2. Withdraw Money " << endl;
	cout << "3. Transfer Money " << endl;
	cout << "4. Show Transactions " << endl;
	cout << "5. Open an Account " << endl;
	cout << "6. Close an Account" << endl;
	cout << "7. Sort Accounts from largest balance to smallest " << endl;
	cout << "8. Sort Accounts in alphabetical order using the account owners name " << endl;
	cout << "9. Quit Program" << endl;
	cout << "---------------------------------------------------------------------------------------------------- " << endl;
}

int getArrayIndexOfAccount(int temp_account_number, account_information temp_array_of_accounts[])
{
	for (int i = 0; i < actual_number_of_accounts; i++)
	{
		if (temp_account_number == temp_array_of_accounts[i].account_number)
		{
			//account found and return index
			return i;
		}
		//continue the search
	}
	return -1;
	return 0;
}

void depositMoney(int temp_account_index, float temp_amount, account_information temp_array_of_accounts[])
{
	temp_array_of_accounts[temp_account_index].balance += temp_amount;
	ofstream logfile;
	string filename = to_string(temp_array_of_accounts[temp_account_index].account_number) + ".txt";
	logfile.open(filename, ios::app);
	logfile << "Deposit Transaction of $" << temp_amount << " at " << time(0) << endl;
	logfile.close();
}

void withdrawMoney(int temp_account_index, float temp_amount, account_information temp_array_of_accounts[])
{
	if (temp_array_of_accounts[temp_account_index].balance >= temp_amount)
	{
		temp_array_of_accounts[temp_account_index].balance -= temp_amount;
		ofstream logfile;
		string filename = to_string(temp_array_of_accounts[temp_account_index].account_number) + ".txt";
		logfile.open(filename, ios::app);
		logfile << "Withdraw Transaction of $" << temp_amount << " at " << time(0) << endl;
		logfile.close();
	}
	else
	{
		cout << "Error: insufficient funds" << endl;
	}

}

void transferMoney(int temp_account_index1, int temp_account_index2, float temp_amount, account_information temp_array_of_accounts[])
{
	if (temp_array_of_accounts[temp_account_index1].balance >= temp_amount)
	{

		temp_array_of_accounts[temp_account_index1].balance -= temp_amount;
		temp_array_of_accounts[temp_account_index2].balance += temp_amount;

		ofstream logfile1;
		string filename1 = to_string(temp_array_of_accounts[temp_account_index1].account_number) + ".txt";
		logfile1.open(filename1, ios::app);
		logfile1 << " Transfer from acount of $" << temp_amount << " at " << time(0) << endl;
		logfile1.close();

		//transaction to next account

		ofstream logfile2;
		string filename2 = to_string(temp_array_of_accounts[temp_account_index2].account_number) + ".txt";
		logfile2.open(filename2, ios::app);
		logfile2 << "Transfer into account $" << temp_amount << " at " << time(0) << endl;
		logfile2.close();
		//cout << "Please enter amount you wish to transfer." << endl;
		//cin >> amount;

		//transferMoney(account_number, account_number1, amount, array_of_accounts);

	}
	else
	{
		cout << "Error: insufficient funds" << endl;
	}
	
}

void showTransactions(int temp_account_index, account_information temp_array_of_accounts[])
{
	ifstream acctFile;
	string filename = to_string(temp_array_of_accounts[temp_account_index].account_number) + ".txt";
	acctFile.open(filename, ios::app);
	string transactionInfo;
	while (!acctFile.eof())
	{
		getline(acctFile, transactionInfo);
		
		//Get input 
		//acctFile >> transactionInfo;

		//Print input 
		cout << transactionInfo << endl;
	}

	//Close file 
	acctFile.close();
}

void openAccount(account_information temp_array_of_accounts[])
{
	if (actual_number_of_accounts + 1 <= totalCapacity)
	{
		string fname, lname;
		float openingBalance;
		int acctNumber;
		cout << "Please enter your first name." << endl;
		cin >> fname;
		cout << "Please enter your last name." << endl;
		cin >> lname;
		cout << "Please enter your opening account balance." << endl;
		cin >> openingBalance;
		cout << "Please enter a five digit account number." << endl;
		cin >> acctNumber;
		temp_array_of_accounts[actual_number_of_accounts].serial=actual_number_of_accounts + 1;
		temp_array_of_accounts[actual_number_of_accounts].account_number = acctNumber;
		temp_array_of_accounts[actual_number_of_accounts].first_name = fname;
		temp_array_of_accounts[actual_number_of_accounts].last_name = lname;
		temp_array_of_accounts[actual_number_of_accounts].balance = openingBalance;
		temp_array_of_accounts[actual_number_of_accounts].flag = 0;
		ofstream logfile;
		string fileName = to_string(temp_array_of_accounts[actual_number_of_accounts].account_number) + ".txt";
		logfile.open(fileName);
		logfile << "Opening account with a balnce of $" << openingBalance << " at " << time (0) << endl;
		logfile.close();
		actual_number_of_accounts++;
	}
	else
	{
		cout << "Error: FULL." << endl;
	}
}

void closeAccount(int temp_account_index, account_information temp_array_of_accounts [])
{
	
	if (temp_array_of_accounts[temp_account_index].balance == 0)
	{
		temp_array_of_accounts[temp_account_index].flag = 1;
		ofstream logfile;
		string filename = to_string(temp_array_of_accounts[temp_account_index].account_number) + ".txt";
		logfile.open(filename, ios::app);
		logfile << "This account was closed at " << time(0) << endl;
		logfile.close();
	}
	else
	{
		cout << "This account cannot be closed because the balance is not zero" << endl;
	}
}

void sortBalances(account_information temp_array_of_accounts[])
{
	account_information local_array_of_accounts[totalCapacity];

	for (int i = 0; i < actual_number_of_accounts; i++) 
	{
		local_array_of_accounts[i].serial = temp_array_of_accounts[i].serial;
		local_array_of_accounts[i].account_number = temp_array_of_accounts[i].account_number;
		local_array_of_accounts[i].first_name = temp_array_of_accounts[i].first_name;
		local_array_of_accounts[i].last_name = temp_array_of_accounts[i].last_name;
		local_array_of_accounts[i].balance = temp_array_of_accounts[i].balance;
		local_array_of_accounts[i].flag = temp_array_of_accounts[i].flag;


	}
	for (int i = 0; i < actual_number_of_accounts; i++)
	{
		for (int j = 0; j < actual_number_of_accounts - 1; j++)
		{

			if (local_array_of_accounts[j].balance < local_array_of_accounts[j + 1].balance) //here
			{
				float temp_balance = local_array_of_accounts[j].balance;
				local_array_of_accounts[j].balance = local_array_of_accounts[j + 1].balance;
				local_array_of_accounts[j + 1].balance = temp_balance;
				int temp_serial = local_array_of_accounts[j].serial;
				local_array_of_accounts[j].serial = local_array_of_accounts[j + 1].serial;
				local_array_of_accounts[j + 1].serial = temp_serial;
				string temp_first_name = local_array_of_accounts[j].first_name;
				local_array_of_accounts[j].first_name = local_array_of_accounts[j + 1].first_name;
				local_array_of_accounts[j + 1].first_name = temp_first_name;
				string temp_last_name = local_array_of_accounts[j].last_name;
				local_array_of_accounts[j].last_name = local_array_of_accounts[j + 1].last_name;
				local_array_of_accounts[j + 1].last_name = temp_last_name;
				int temp_account_number = local_array_of_accounts[j].account_number;
				local_array_of_accounts[j].account_number = local_array_of_accounts[j + 1].account_number;
				local_array_of_accounts[j + 1].account_number = temp_account_number;
				bool temp_flag = local_array_of_accounts[j].flag;
				local_array_of_accounts[j].flag = local_array_of_accounts[j + 1].flag;
				local_array_of_accounts[j + 1].flag = temp_flag;
			}
		}
	}
	for (int i = 0; i < actual_number_of_accounts; i++) 
	{
		cout << local_array_of_accounts[i].serial << " ";
		cout << local_array_of_accounts[i].account_number << " ";
		cout << local_array_of_accounts[i].first_name << " ";
		cout << local_array_of_accounts[i].last_name << " ";
		cout << local_array_of_accounts[i].balance << " ";
		cout << local_array_of_accounts[i].flag << endl;
	}
}
void sortNames(account_information temp_array_of_accounts[])
{
	account_information local_array_of_accounts[totalCapacity];

	for (int i = 0; i < actual_number_of_accounts; i++)
	{
		local_array_of_accounts[i].serial = temp_array_of_accounts[i].serial;
		local_array_of_accounts[i].account_number = temp_array_of_accounts[i].account_number;
		local_array_of_accounts[i].first_name = temp_array_of_accounts[i].first_name;
		local_array_of_accounts[i].last_name = temp_array_of_accounts[i].last_name;
		local_array_of_accounts[i].balance = temp_array_of_accounts[i].balance;
		local_array_of_accounts[i].flag = temp_array_of_accounts[i].flag;


	}
	for (int i = 0; i < actual_number_of_accounts; i++)
	{
		for (int j = 0; j < actual_number_of_accounts - 1; j++)
		{

			if (local_array_of_accounts[j].first_name > local_array_of_accounts[j + 1].first_name)
			{
				string temp_first_name = local_array_of_accounts[j].first_name;
				local_array_of_accounts[j].first_name = local_array_of_accounts[j + 1].first_name;
				local_array_of_accounts[j + 1].first_name = temp_first_name;
				string temp_last_name = local_array_of_accounts[j].last_name;
				local_array_of_accounts[j].last_name = local_array_of_accounts[j + 1].last_name;
				local_array_of_accounts[j + 1].last_name = temp_last_name;
				float temp_balance = local_array_of_accounts[j].balance;
				local_array_of_accounts[j].balance = local_array_of_accounts[j + 1].balance;
				local_array_of_accounts[j + 1].balance = temp_balance;
				int temp_serial = local_array_of_accounts[j].serial;
				local_array_of_accounts[j].serial = local_array_of_accounts[j + 1].serial;
				local_array_of_accounts[j + 1].serial = temp_serial;
				int temp_account_number = local_array_of_accounts[j].account_number;
				local_array_of_accounts[j].account_number = local_array_of_accounts[j + 1].account_number;
				local_array_of_accounts[j + 1].account_number = temp_account_number;
				bool temp_flag = local_array_of_accounts[j].flag;
				local_array_of_accounts[j].flag = local_array_of_accounts[j + 1].flag;
				local_array_of_accounts[j + 1].flag = temp_flag;
			}
		}
	}
	for (int i = 0; i < actual_number_of_accounts; i++)
	{
		cout << local_array_of_accounts[i].serial << " ";
		cout << local_array_of_accounts[i].account_number << " ";
		cout << local_array_of_accounts[i].first_name << " ";
		cout << local_array_of_accounts[i].last_name << " ";
		cout << local_array_of_accounts[i].balance << " ";
		cout << local_array_of_accounts[i].flag << endl;
	}
}