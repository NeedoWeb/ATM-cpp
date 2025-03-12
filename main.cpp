#include <iostream>
#include <iomanip>
#include <map>
#include <string>

using namespace std;

class User {
private:
    string username;
    string pin;

public:
    User(const string& user, const string& p) : username(user), pin(p) {}

    string getUsername() const {
        return username;
    }

    bool validatePin(const string& inputPin) const {
        return pin == inputPin;
    }
};

class ATM {
private:
    double balance;
    map<string, double> exchangeRates;
    User* currentUser ; // Pointer to the current user

public:
    ATM() : balance(0.0), currentUser (NULL) { // Use NULL instead of nullptr
        // Initialize some exchange rates
        exchangeRates["USD"] = 1.0; // Base currency
        exchangeRates["EUR"] = 0.85; // 1 USD = 0.85 EUR
        exchangeRates["GBP"] = 0.75; // 1 USD = 0.75 GBP
        exchangeRates["INR"] = 74.0; // 1 USD = 74 INR
    }

    void login(User& user) {
        string inputPin;
        cout << "Enter PIN for user " << user.getUsername() << ": ";
        cin >> inputPin;

        if (user.validatePin(inputPin)) {
            currentUser  = &user; // Set the current user
            cout << "Login successful!\n";
        } else {
            cout << "Invalid PIN. Login failed.\n";
        }
    }

    void deposit(double amount) {
        if (currentUser  == NULL) { // Check if user is logged in
            cout << "Please log in to deposit money.\n";
            return;
        }
        if (amount <= 0) {
            cout << "Deposit amount must be positive.\n";
            return;
        }
        balance += amount;
        cout << fixed << setprecision(2) << "Deposited: $" << amount << "\n";
    }

    void withdraw(double amount, const string& currency) {
        if (currentUser  == NULL) { // Check if user is logged in
            cout << "Please log in to withdraw money.\n";
            return;
        }
        if (exchangeRates.find(currency) == exchangeRates.end()) {
            cout << "Invalid currency!\n";
            return;
        }

        if (amount <= 0) {
            cout << "Withdrawal amount must be positive.\n";
            return;
        }

        double amountInUSD = amount / exchangeRates[currency];
        if (amountInUSD > balance) {
            cout << "Insufficient funds!\n";
        } else {
            balance -= amountInUSD;
            cout << fixed << setprecision(2) << "Withdrew: " << amount << " " << currency << "\n";
        }
    }

    void checkBalance(const string& currency) {
        if (currentUser  == NULL) { // Check if user is logged in
            cout << "Please log in to check your balance.\n";
            return;
        }
        if (exchangeRates.find(currency) == exchangeRates.end()) {
            cout << "Invalid currency!\n";
            return;
        }

        double convertedBalance = balance * exchangeRates[currency];
        cout << fixed << setprecision(2) << "Current balance: " << convertedBalance << " " << currency << "\n";
    }
};

int main() {
    // Create a user for testing
    User user("needoweb", "1234");
    ATM atm;

    // Login process
    atm.login(user);

    int choice;
    double amount;
    string currency;

    do {
        cout << "\nATM Menu:\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Cash\n";
        cout << "3. Withdraw Cash\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter currency (USD, EUR, GBP, INR): ";
                cin >> currency;
                atm.checkBalance(currency);
                break;
            case 2:
                cout << "Enter amount to deposit: ";
                cin >> amount;
                atm.deposit(amount);
                break;
            case 3:
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                cout << "Enter currency (USD, EUR, GBP, INR): ";
                cin >> currency;
                atm.withdraw(amount, currency);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
