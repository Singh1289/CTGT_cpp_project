/*
Program to create a digital wallet where users can add and spend virtual currency. The program should ensure that the amount spent does not exceed the available balance. Provide an Object Oriented Implementation. Wallet should support features such as add money, spend money, handle different types of transactions, currency conversion, user authentication and checking the balance. 
*/

#include <iostream>
#include <fstream>
#include <cctype>
#include <conio.h>
#include <string>
#include <time.h>
#include <iomanip>
#include <cstring> 

using namespace std;

enum transactionType
{
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER
};
// global vaiable to create id
int ID = 1102;
string transactionTypeStr[] = {"Deposit", "Withdrawal", "Transfer"};

// transaction class
class Transaction
{
    // data members
public:
    int userID;
    string type;
    double amount;
    string time;
    string to_user;

    // constructors
    Transaction()
    {
        userID = 0;
        type = "";
        amount = 0.0;
        time = "";
        to_user = "";
    }

    // parametries constructor
    Transaction(int userId, transactionType t, double amt, const time_t tmm, string to_user = "")
    {
        time_t currentTime = tmm;
        tm *localTime1 = localtime(&currentTime);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime1);

        userID = userId;
        type = transactionTypeStr[t];
        amount = amt;
        time = buffer;
        this->to_user = to_user;
    }

    ~Transaction() {}
};

// user class
class User
{
    // data members
private:
    int user_id;
    char userName[25];
    char password[25];
    double balance;

public:
    // default constructor
    User()
    {
        user_id = 0;
        strcpy(userName, "");
        strcpy(password, "");
        balance = 0.0;
    }
    // parametries constructor
    User(const char *userName, const char *password, double balance = 0.0)
    {
        user_id = ID++;
        strcpy(this->userName, userName);
        strcpy(this->password, password);
        this->balance = balance;
    }
    // getter setters
    void setUserName(const char *userName)
    {
        strcpy(this->userName, userName);
    }

    void setPassword(const char *password)
    {
        strcpy(this->password, password);
    }

    const char *getUserName()
    {
        return userName;
    }

    const char *getPassword()
    {
        return password;
    }

    int getUserId()
    {
        return user_id;
    }

    void setUserId(const int userId)
    {
        this->user_id = userId;
    }

    double getBalance()
    {
        return balance;
    }

    // function: on login it verify the user is it valid or not  
    bool authenticate(const char *userName, const char *password)
    {
        ifstream file("user.dat", ios::binary);
        if (file.is_open())
        {
            User temp;
            while (file.read(reinterpret_cast<char *>(&temp), sizeof(temp)))
            {
                if (strcmp(temp.userName, userName) == 0 && strcmp(temp.password, password) == 0)
                {
                    this->setPassword(temp.password);
                    this->setUserName(temp.userName);
                    this->setUserId(temp.getUserId());
                    this->balance = temp.getBalance();
                    file.close();
                    return true;
                }
            }
            file.close();
            return false;
        }
        else
        {
            cout << "Unable to open file";
            return 0;
        }
    }

    // function to validate the sender .. 
    // function check user detail in file  
    // if user doesnot exist then return false 
    bool findReceiver(const char *name, int id)
    {
        ifstream file("user.dat", ios::binary);
        if (file.is_open())
        {
            User temp;
            while (file.read(reinterpret_cast<char *>(&temp), sizeof(temp)))
            {
                if (strcmp(temp.userName, name) == 0 && temp.user_id == id)
                {
                    this->setPassword(temp.password);
                    this->setUserName(temp.userName);
                    this->setUserId(temp.getUserId());
                    this->balance = temp.getBalance();
                   // this->printUser();
                    return true;
                }
            }
            file.close();
            return false;
        }
        else
        {
            cout << "Unable to open file";
            return false;
        }
    }

    // it user is not in data base 
    // sign up the user and create a new user and save it in the binary file or data base
    void sign_up(const char *userName, const char *password)
    {
        User temp(userName, password);
        ofstream file("user.dat", ios::binary | ios::app);
        if (file.is_open())
        {
            file.write(reinterpret_cast<char *>(&temp), sizeof(temp));
            file.close();
            cout << "\nUser Id: " << temp.user_id << endl;
            cout << "User signed up successfully!" << endl;
        }
        else
        {
            cout << "\nUnable to open file" << endl;
        }
    }

    // function use to deposit amount and log the tranction in the file
    void deposit(double amount)
    {
        balance += amount;
        time_t now = (time_t)time(0);
        Transaction trans(this->getUserId(), DEPOSIT, amount, now);
        logTransaction(trans);
        cout << "Transaction done successfully." << endl;
    }

    // withdraw the amount and also create a log in file 
    bool withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            time_t now = (time_t)time(0);
            Transaction trans(this->getUserId(), WITHDRAWAL, amount, now);
            logTransaction(trans);
            cout << "Transaction done successfully." << endl;
            return true;
        }
        else
        {
            cout << "Insufficient balance!" << endl;
            return false;
        }
    }

    // function to transfer amount to one to another user 
    // also update the user account and sender account
    void transfer(User &to, double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            to.deposit(amount);
            to.updateUserInfo();
            time_t now = (time_t)time(0);
            Transaction trans(this->getUserId(), TRANSFER, amount, now, to.getUserName());
            logTransaction(trans);
            cout << "Transaction done successfully." << endl;
            return;
        }
        else
        {
            cout << "Insufficient balance!" << endl;
            return;
        }
    }


    // function is use for log the tranction in the file
    void logTransaction(Transaction &trans)
    {
        ofstream file("transaction_log.txt", ios::app);
        if (file.is_open())
        {
            file << left << setw(7) << trans.userID << setw(20) << trans.time
                 << setw(15) << trans.type
                 << setw(15) << trans.to_user
                 << fixed << setprecision(2) << setw(10) << trans.amount
                 << endl;
            file.close();
        }
        else
        {
            cout << "Error opening file for logging transaction!" << endl;
        }
    }

    // function print the user statement ... print all tranction details
    // by reading the text file and filter out according to the user id and print in formatted way
    void printStatement()
    {
        ifstream file("transaction_log.txt", ios::in);
        if (file.is_open())
        {
            cout << "---------------------------------------------------------------" << endl;
            cout << "Transaction Statement for User: " << this->getUserId()
                 << " Name: " << this->getUserName() << endl;
            cout << "---------------------------------------------------------------" << endl;
            cout << left << setw(7) << "UID" << setw(20) << "Time"
                 << setw(15) << "Type"
                 << setw(15) << "To"
                 << setw(10) << "Amount" << endl;
            cout << "---------------------------------------------------------------" << endl;

            string line;
            bool hasTransactions = false;
            while (getline(file, line))
            {
                istringstream ss(line);
                string uidStr, time, type, to, amount;
                // format the string properly

                ss >> uidStr;
                int uid = stoi(uidStr);

                string date, time_part;
                ss >> date >> time_part;
                time = date + " " + time_part;

                ss >> type;

                if (type == "Transfer")
                {
                    // Handle "To" for transfer type
                    ss >> to;
                    ss >> amount;
                }
                else
                {
                    to = "";
                    ss >> amount;
                }

                if (uid == this->getUserId())
                {
                    cout << left << setw(7) << uid << setw(20) << time
                         << setw(15) << type
                         << setw(15) << to
                         << setw(10) << amount << endl;
                    hasTransactions = true;
                }
            }

            if (!hasTransactions)
            {
                cout << "No transactions found for this user." << endl;
            }

            cout << "---------------------------------------------------------------" << endl;
            cout << "Account balance: " << fixed << setprecision(2) << this->getBalance() << endl;
            file.close();
        }
        else
        {
            cout << "Unable to connect server..!!" << endl;
        }
        cout << "---------------------------------------------------------------" << endl;
    }
private:
    // print user details use for debugging
    void printUser() const
    {
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "User Name: " << userName << endl;
        cout << "User ID: " << user_id << endl;
        cout << "Password: " << password << endl;
        cout << "Balance: " << balance << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    // print all user details use for debugging purposes
    void printBinaryFile() const
    {
        ifstream file("user.dat", ios::binary);
        if (file.is_open())
        {
            User temp;
            while (file.read(reinterpret_cast<char *>(&temp), sizeof(temp)))
            {
                temp.printUser();
            }
            file.close();
        }
    }
public:
    // this function use to update the current user object presistance in the file
    // next time user login it show the updated object details
    void updateUserInfo()
    {
        fstream file("user.dat", ios::binary | ios::in | ios::out);
        if (file.is_open())
        {
            User temp;
            while (file.read(reinterpret_cast<char *>(&temp), sizeof(temp)))
            {
                if (temp.user_id == this->user_id)
                {
                    temp.printUser();
                    temp.balance = this->balance;
                    int pos = file.tellg();
                    int block = sizeof(temp);
                    file.seekp(pos - block);
                    file.write(reinterpret_cast<char *>(&temp), sizeof(temp));
                    file.close();
                    cout << "\nUser updated successfully!";
                    return;
                }
            }
        }
    }
    // showing the current balance of the user in different currency
    void getBalanceInDiffCurrency()
    {
        cout << "---------------------------------------------" << endl;
        cout << "Currency Conversion" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Rupees (INR)       : " << right << fixed << setprecision(3) << setw(9) << this->getBalance() << endl;
        cout << "Dollar (USD)       : " << right << fixed << setprecision(3) << setw(9) << this->getBalance() * 0.012 << endl;
        cout << "Dollar (CAD)       : " << right << fixed << setprecision(3) << setw(9) << this->getBalance() * 0.016 << endl;
        cout << "Euro   (EUR)       : " << right << fixed << setprecision(3) << setw(9) << this->getBalance() * 0.011 << endl;
        cout << "---------------------------------------------" << endl;
    }

    ~User() {}
};

// funtion validating the password string with one cap, small,number and special charactor
bool validate_password(const char *password)
{
    if (strlen(password) < 5)
        return false;

    bool hasDigit = false;
    bool hasSpecialChar = false;
    bool hasSmallChar = false;
    bool hasLargeChar = false;

    for (int i = 0; i < strlen(password); i++)
    {
        char c = password[i];
        if (islower(c))
            hasSmallChar = true;
        if (isupper(c))
            hasLargeChar = true;
        if (isdigit(c))
            hasDigit = true;
        if (c == '-' || c == '+' || c == '!' || c == '@' || c == '$' ||
            c == '_' || c == '%' || c == '&' || c == '*')
        {
            hasSpecialChar = true;
        }
    }

    return hasDigit && hasSpecialChar && hasSmallChar && hasLargeChar;
}

// Function to get password from user input at cosole and while typing password shows ****
/*
    when user hit backspace then last character popped out and also erase one * from the console
*/
void getPassword(char *password)
{
    char ch;
    int i = 0;
    while (true)
    {
        ch = getch();
        if (ch == 13)
        {
            password[i] = '\0';
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                password[--i] = '\0';
                cout << "\b \b";
            }
        }
        else if (i < 24)
        {
            password[i++] = ch;
            cout << "*";
        }
    }
}

int main()
{
    // declare variables
    char name[25], pass[25], receiverName[25];
    string to_user;
    int receiverID;
    double amount;
    User temp;
    User user;
     // menudriven wallet until user exit the code
    while (true)
    {
        memset(name, 0, sizeof(name));
        memset(pass, 0, sizeof(pass));
        // main menu for login
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout << "\n|      CTGT Digital Wallet      |";
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout << "\n|      ~ W E L C O M E ~        |";
        cout << "\n|1 : Sign Up                    |";
        cout << "\n|2 : Login                      |";
        cout << "\n|3 : Exit                       |";
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 3)
        {
            cout << "\n\n~~~~~ See you soon ~~~~~\n"
                 << endl;
            break;
        }

        switch (choice)
        {
        case 1:
            cout << "Enter your username: ";
            cin.ignore();
            cin.getline(name, 25);
            cout << "Enter your password (max 15 char): ";
            getPassword(pass);
            if (validate_password(pass))
            {
                user.sign_up(name, pass);
            }
            else
            {
                cout << "\nPassword must contain at least one uppercase letter, one lowercase letter, one digit, one special character and length in range 5-15." << endl;
            }
            break;
        case 2:
            cout << "Enter your username: ";
            cin.ignore();
            cin.getline(name, 25);

            cout << "Enter your password: ";
            getPassword(pass);

            if (user.authenticate(name, pass))
            {
                cout << "\nLogin successful!" << endl;
                //user.printUser();
                while (true)
                {
                    // main menu for user wallet
                    memset(receiverName, 0, sizeof(receiverName));
                    int choose;
                    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                    cout << "\n|      CTGT Digital Wallet      |";
                    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                    cout << "\n|1 : Depposit                   |";
                    cout << "\n|2 : Withdraw                   |";
                    cout << "\n|3 : Transfer                   |";
                    cout << "\n|4 : View Statement             |";
                    cout << "\n|5 : View Balance               |";
                    cout << "\n|6 : Logout                     |";
                    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    cout << "Enter your choice: ";
                    cin >> choose;

                    if (choose == 6)
                    {
                        user.updateUserInfo();
                        // user.printBinaryFile();
                        break;
                    }
                    switch (choose)
                    {
                    case 1:
                        cout << "Enter amount to deposit: ";
                        cin >> amount;
                        user.deposit(amount);
                        break;
                    case 2:
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        user.withdraw(amount);
                        break;
                    case 3:
                        cout << "Enter recipient user Name: ";
                        cin >> receiverName;
                        cout << "Enter recipient user ID: ";
                        cin >> receiverID;

                        if (temp.findReceiver(receiverName, receiverID))
                        {
                            cout << "Enter amount to transfer: ";
                            cin >> amount;
                            user.transfer(temp, amount);
                            cout << "Amount Transferred" << endl;
                        }
                        break;
                    case 4:
                        user.printStatement();
                        break;
                    case 5:
                        user.getBalanceInDiffCurrency();
                        break;
                    default:
                        cout << "Invalid choice" << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid credentials!" << endl;
            }
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    }
    return 0;
}
