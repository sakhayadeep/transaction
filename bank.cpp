#include <iostream>
#include <map>

using namespace std;

int LAST_ACC_NUM = 0;
void createAccount();
void loginAccount();
int main();

class Account{
    string userName;
    int accNum;
    string password;
    double balance;

  public:
      Account(string name, string pass, double amount)
      {
          userName = name;
          accNum = ++LAST_ACC_NUM;
          password = pass;
          balance = amount;
      }
      void menu();
      void deposit();
      void withdraw();
      void showDetails();
      bool authenticate(string pass)
      {
          if(pass == password)
            return true;
          else
            return false;
      }

};

void Account::menu()
{
    int choice;

    cout<<"\n**********WELCOME "<<userName<<"**********";
    cout<<"\n1. Deposit";
    cout<<"\n2. Withdraw";
    cout<<"\n3. Show account details";
    cout<<"\n4. Back to main menu";
    cout<<"\n5. Exit";
    cout<<"\nEnter your choice : ";
    cin>>choice;

    switch(choice)
    {
        case 1 : deposit();
                 break;
        case 2 : withdraw();
                 break;
        case 3 : showDetails();
                 break;
        case 4 : main();
                 break;
        case 5 : exit(0);
        default: cout<<"!!!INVALID CHOICE!!!"<<endl;
    }

    menu();
}

void Account::deposit()
{
    double amount;

    cout<<"\nEnter the amount to deposit : ";
    cin>>amount;

    balance += amount;

    cout<<amount<<" added to your account. Thank you for using our service."<<endl;

}

void Account::withdraw()
{
    double amount;

    cout<<"\nEnter the amount to withdraw : ";
    cin>>amount;

    if(amount <= balance)
    {
        balance -= amount;
        cout<<endl<<amount<<" withdrawn from your account. Thank you for using our service."<<endl;
    }
    else
    {
        cout<<"\nInsufficient balance. Unable to withdraw.";
        cout<<"\nTransaction canceled"<<endl;
    }

}

void Account::showDetails()
{
    cout<<"\nUser name : "<<userName;
    cout<<"\nAccount number : "<<accNum;
    cout<<"\nThe current balance in your account is "<<balance<<endl;
}

map<string, Account*> accounts;

int main()
{
    int choice;

    cout<<"\n************MENU**************";
    cout<<"\n1. Create account";
    cout<<"\n2. Login to your account";
    cout<<"\n3. Exit";
    cout<<"\nEnter your choice : ";
    cin>>choice;

    switch(choice)
    {
        case 1 :    createAccount();
                    break;
        case 2 :    loginAccount();
                    break;
        case 3 :    exit(0);
        default:    cout<<"\n!!!INVALID CHOICE!!!\n";
                    main();
    }
    return 0;
}

void createAccount()
{
    string name, pass;
    double amount = 0.0;
    int trial = 3;

    cout<<"\nEnter your details";

    userNameLabel:
    cin.ignore();
    cout<<"\nUser name : ";
    getline(cin, name);

    if(accounts.find(name) != accounts.end())
    {
        cout<<"\nUser name is already taken!!";
        cout<<"\nTry again";
        if(trial--)
            goto userNameLabel;
        else
            main();
    }

    cout<<"password : ";
    getline(cin, pass);

    cout<<"Enter amount to deposit [default 0.0] : ";
    if(cin.peek() == '\n')
        amount = 0.0;
    else
        cin>>amount;

    Account acc(name, pass, amount);
    accounts.insert(make_pair(name, &acc));

    acc.menu();
}

void loginAccount()
{
    string name, pass;

    cout<<"\nEnter User name : ";
    cin.ignore();
    getline(cin, name);

    if(accounts.find(name) == accounts.end())
    {
        cout<<"\nUsername "<<name<<" does not exist!";
        main();
    }
    else{
        int trial = 3;
        while(trial--)
        {
            cout<<"\nEnter password : ";
            getline(cin, pass);
            if(accounts[name]->authenticate(pass))
                accounts[name]->menu();
            else
                cout<<"\nWrong password! try again";
        }
        main();
    }
}
