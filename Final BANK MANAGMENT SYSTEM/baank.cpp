#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>

using namespace std;

class Customer {
    string name;
    int age;
    string address;
    string phoneNumber;
    string customerId;

public:
    void getDetails();
    void updateDetails();
    void showDetails() const;
    string getCustomerID() const;
};

void Customer::getDetails() {
    cin.ignore(); // Clear the input buffer
    cout << "Enter Customer Name: ";
    getline(cin, name);
    cout << "Enter Customer Age: ";
    cin >> age;
    cin.ignore(); // Ignore newline character
    cout << "Enter Customer Address: ";
    getline(cin, address);
    cout << "Enter Customer Phone Number: ";
    getline(cin, phoneNumber);
    cout << "Enter Customer ID: ";
    getline(cin, customerId);
}

void Customer::updateDetails() {
    cout << "Enter Updated Customer Name: ";
    getline(cin, name);
    cout << "Enter Updated Customer Age: ";
    cin >> age;
    cin.ignore(); // Ignore newline character
    cout << "Enter Updated Customer Address: ";
    getline(cin, address);
    cout << "Enter Updated Customer Phone Number: ";
    getline(cin, phoneNumber);
    cout << "Enter Updated Customer ID: ";
    getline(cin, customerId);
}

void Customer::showDetails() const {
    cout << "Customer Name: " << name << endl;
    cout << "Customer Age: " << age << endl;
    cout << "Customer Address: " << address << endl;
    cout << "Customer Phone Number: " << phoneNumber << endl;
    cout << "Customer ID: " << customerId << endl;
}

string Customer::getCustomerID() const {
    return customerId;
}

class Account {
    Customer customer;
    int accountNumber;
    double balance;
    char accountType;

public:
    void openAccount();
    void closeAccount();
    void updateAccount();
    void showAccount() const;
    void deposit(double);
    void withdraw(double);
    int getAccountNumber() const;
    double getBalance() const;
    void writeAccountToFile() const;
    void readAccountFromFile(int);
};

void Account::openAccount() {
    customer.getDetails();
    cout << "Enter Account Number: ";
    cin >> accountNumber;
    cout << "Enter Initial Balance: ";
    cin >> balance;
    cout << "Enter Account Type (C/S): ";
    cin >> accountType;
    accountType = toupper(accountType);
    cout << "Account Opened Successfully!" << endl;
    writeAccountToFile(); // Save account details to file
}

void Account::closeAccount() {
    balance = 0;
    cout << "Account Closed Successfully!" << endl;
    writeAccountToFile(); // Save updated account details to file
}

void Account::updateAccount() {
    customer.updateDetails();
    // Update other account information if needed
    writeAccountToFile(); // Save updated account details to file
}

void Account::showAccount() const {
    cout << "Account Number: " << accountNumber << endl;
    customer.showDetails();
    cout << "Account Type: " << accountType << endl;
    cout << "Account Balance: " << balance << endl;
}

void Account::deposit(double amount) {
    balance += amount;
    cout << "Deposit of $" << amount << " successful!" << endl;
    writeAccountToFile(); // Save updated account details to file
}

void Account::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        cout << "Withdrawal of $" << amount << " successful!" << endl;
        writeAccountToFile(); // Save updated account details to file
    } else {
        cout << "Insufficient balance!" << endl;
    }
}

int Account::getAccountNumber() const {
    return accountNumber;
}

double Account::getBalance() const {
    return balance;
}

void Account::writeAccountToFile() const {
    ofstream outFile("accounts.txt", ios::app);
    if (outFile.is_open()) {
        outFile << accountNumber << " " << customer.getCustomerID() << " " << balance << " " << accountType << endl;
        outFile.close();
    } else {
        cout << "Error: Unable to write to file." << endl;
    }
}

void Account::readAccountFromFile(int accNum) {
    ifstream inFile("accounts.txt");
    if (inFile.is_open()) {
        int accNo;
        string custID;
        double bal;
        char accType;
        bool found = false;

        while (inFile >> accNo >> custID >> bal >> accType) {
            if (accNo == accNum) {
                accountNumber = accNo;
                balance = bal;
                accountType = accType;

                // Fetch customer details from a separate file or database using custID
                // Here, it is assumed that customer details are stored separately
                // and the customer object is updated accordingly.

                cout << "Account loaded successfully!" << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Account number not found." << endl;
        }

        inFile.close();
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

int main() {
    char choice;
    Account account;
    double amount;
    int accountNumber;

    do {
        cout << "\n======================\n";
        cout << "BANK MANAGEMENT SYSTEM";
        cout << "\n======================\n";
        cout << "\n::MAIN MENU::\n";
        cout << "\n1. OPEN ACCOUNT";
        cout << "\n2. DEPOSIT AMOUNT";
        cout << "\n3. WITHDRAW AMOUNT";
        cout << "\n4. CLOSE ACCOUNT";
        cout << "\n5. DISPLAY ACCOUNT DETAILS";
        cout << "\n6. UPDATE ACCOUNT";
        cout << "\n7. EXIT";
        cout << "\n\nSelect Your Option (1-7): ";
        cin >> choice;

        switch (choice) {
            case '1':
                account.openAccount();
                break;
            case '2':
                cout << "\nEnter The account No. : ";
                cin >> accountNumber;
                cout << "\nEnter the amount to deposit: ";
                cin >> amount;
                account.readAccountFromFile(accountNumber);
                account.deposit(amount);
                break;
            case '3':
                cout << "\nEnter The account No. : ";
                cin >> accountNumber;
                cout << "\nEnter the amount to withdraw: ";
                cin >> amount;
                account.readAccountFromFile(accountNumber);
                account.withdraw(amount);
                break;
            case '4':
                cout << "\nEnter The account No. : ";
                cin >> accountNumber;
                account.readAccountFromFile(accountNumber);
                account.closeAccount();
                break;
            case '5':
                cout << "\nEnter The account No. : ";
                cin >> accountNumber;
                account.readAccountFromFile(accountNumber);
                account.showAccount();
                break;
            case '6':
                cout << "\nEnter The account No. : ";
                cin >> accountNumber;
                account.readAccountFromFile(accountNumber);
                account.updateAccount();
                break;
            case '7':
                cout << "\nThanks for using the bank management system.";
                break;
            default:
                cout << "\nInvalid option! Please try again.";
        }

    } while (choice != '7');

    return 0;
}

