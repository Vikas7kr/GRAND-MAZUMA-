

#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define MIN_BALANCE 50 //for minimum balance amount

class InsufficientFunds
{
};

/*
^ACCOUNT CLASS^,EVERY MEMBER FUNCTION DEFINED INSIDE THE CLASS.
BASIC OPERATION IN ACCOUNTS OF USER IS DONE USING DATA MEMBER AND MEMBER FUNTIONS IN THIS CLASS. 
*/

class Account
{
private:
    long accountNumber;
    string first_name;
    string last_name;
    float balance;
    static long Next_acc_no;

public:
    Account() {}
    Account(string fname, string lname, float bal)
    {
        Next_acc_no++;
        accountNumber = Next_acc_no;
        first_name = fname;
        last_name = lname;
        balance = bal;
    }
    long getAcc_no() { return accountNumber; }
    string getFirst_n() { return first_name; }
    string getLast_n() { return last_name; }
    float getBal() { return balance; }

    void Deposit(float amount)
    {
        balance += amount;
    }
    void Withdraw(float amount)
    {
        if (balance - amount < MIN_BALANCE)
            throw InsufficientFunds();
        balance -= amount;
    }
    static void setL_acc(long acc_no)
    {
        Next_acc_no = acc_no;
    }
    static long getlL_acc() { return Next_acc_no; }
    friend ofstream &operator<<(ofstream &ofs, Account &acc);
    friend ifstream &operator>>(ifstream &ifs, Account &acc);
    friend ostream &operator<<(ostream &os, Account &acc);
};
long Account::Next_acc_no = 0; //static variable

//OPERATOR OVERLOADING

ofstream &operator<<(ofstream &ofs, Account &acc)
{
    ofs << acc.accountNumber << endl;
    ofs << acc.first_name << endl;
    ofs << acc.last_name << endl;
    ofs << acc.balance << endl;
    return ofs;
}

ifstream &operator>>(ifstream &ifs, Account &acc)
{
    ifs >> acc.accountNumber;
    ifs >> acc.first_name;
    ifs >> acc.last_name;
    ifs >> acc.balance;
    return ifs;
}

ostream &operator<<(ostream &os, Account &acc)
{
    os << "Account Number : " << acc.getAcc_no() << endl;
    os << "First Name : " << acc.getFirst_n() << endl;
    os << "Last Name : " << acc.getLast_n() << endl;
    os << "Balance : " << acc.getBal() << endl;
    return os;
}

/*
^BANK CLASS^, ALL MEMBER FUNCTION DEFINED OUTSIDE OF THE CLASS.
BANK CLASS IS USED FOR ACCESSING DATA FROM ACCOUNT CLASS, AND DOING MAJOR FUNCTIONS REQUIRED
IN BANKING SYSTEM.
*/

class Bank
{
private:
    map<long, Account> accounts;

public:
    Bank();
    Account OpenAccount(string fname, string lname, float balance);
    Account BalanceEnqi(long accountNumber);
    Account Deposit(long accountNumber, float amount);
    Account Withdraw(long accountNumber, float amount);
    void CloseAccount(long accountNumber);
    void ShowAllAccount();
    ~Bank();
};

int main()
{
    Account acc;
    Bank b;
    int choice;
    string fname, lname;
    long ano;
    float bal;
    float amount;
    cout << "**********************************************************\n";
    cout << "         ^ WELCOME TO GRAND MAZUMA BANKING SYSTEM ^      " << endl;

    do //ALL OPERATIONS
    {
        cout << "\n\tSelect one option below ";
        cout << "\n\t1 Open an Account";
        cout << "\n\t2 Balance Enquiry";
        cout << "\n\t3 Deposit";
        cout << "\n\t4 Withdrawal";
        cout << "\n\t5 Close an Account";
        cout << "\n\t6 Show All Accounts";
        cout << "\n\t7 Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter First Name : ";
            cin >> fname;
            cout << "Enter Last Name : ";
            cin >> lname;
            cout << "Enter Initial Balance : ";
            cin >> bal;
            acc = b.OpenAccount(fname, lname, bal);
            cout << endl
                 << "** Congratulation Account is Created **" << endl;
            cout << acc;
            break;

        case 2:
            cout << "Enter Bank Account Number : ";
            cin >> ano;
            acc = b.BalanceEnqi(ano);
            cout << "\nYour Account Details : " << endl;
            cout << acc;
            break;

        case 3:
            cout << "Enter Bank Account Number : ";
            cin >> ano;
            cout << "\nEnter Amount : ";
            cin >> amount;
            acc = b.Deposit(ano, amount);
            cout << "\nAmount Deposited " << endl;
            cout << acc;
            break;

        case 4:
            cout << "Enter Bank Account Number : ";
            cin >> ano;
            cout << "\n Enter Amount : ";
            cin >> amount;
            acc = b.Withdraw(ano, amount);
            cout << "\nAmount Withdrawn " << endl;
            cout << acc;
            break;

        case 5:
            cout << "Enter Bank Account Number : ";
            cin >> ano;
            b.CloseAccount(ano);
            int a;
            cout << "\nYou are sure you want to delete account ?" << endl;
            cout << " Press '1' to delete your account " << endl;
            cout << " Press '0' to cancel" << endl;
            cin >> a;
            if (a == 1)
            {
                cout << endl
                     << " Account is Closed " << endl;
            }
            else
                break;
            break;

        case 6:
            b.ShowAllAccount();
            break;

        case 7:
            break;

        default:
            cout << "\nEnter correct choice";
            exit(0);
        }
    } while (choice != 7);
    cout<<"Thank you for using GRAND-MAZUMA"<<endl;
    cout << "\n\n**************************";
    return 0;
}

Bank::Bank()
{
    Account account;
    ifstream infile;
    infile.open("Bank.txt");
    if (!infile)
    {
        return;
    }
    while (!infile.eof())
    {
        infile >> account;
        accounts.insert(pair<long, Account>(account.getAcc_no(), account));
    }
    Account::setL_acc(account.getAcc_no());
    infile.close();
}

Account Bank::OpenAccount(string fname, string lname, float balance)
{
    ofstream outfile;
    Account account(fname, lname, balance);
    accounts.insert(pair<long, Account>(account.getAcc_no(), account));

    outfile.open("Bank.txt", ios::trunc);
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
    return account;
}

Account Bank::BalanceEnqi(long accountNumber)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    return itr->second;
}

Account Bank::Deposit(long accountNumber, float amount)
{
    map<long, Account>::iterator itr;
    itr = accounts.find(accountNumber);
    itr->second.Deposit(amount);
    return itr->second;
}

Account Bank::Withdraw(long accountNumber, float amount)
{
    map<long, Account>::iterator itr;
    itr = accounts.find(accountNumber);
    itr->second.Withdraw(amount);
    return itr->second;
}

void Bank::CloseAccount(long accountNumber)
{
    map<long, Account>::iterator itr;
    itr = accounts.find(accountNumber);
    cout << "Account deletetion request for account \n"
         << itr->second;
    accounts.erase(accountNumber);
}

void Bank::ShowAllAccount()
{
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        cout << "Account " << itr->first << endl
             << itr->second << endl;
    }
}

Bank ::~Bank()
{
    ofstream outfile;
    outfile.open("Bank.txt", ios::trunc);
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
}
