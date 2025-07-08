#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure to store loan information
struct Loan {
    string type;
    double amount;
    int duration;
    double remainingBalance;
};

// Add Loan structure to the User struct
struct User {
    string firstName;
    string middleName;
    string lastName;
    int age;
    char gender;
    string nationality;
    string birthday;
    string email;
    long cpnumber;
    string sourceOfFunds; 
    string username;
    string password;
    int pin;
    double balance; 
    Loan loan;     
    vector<string> transactionHistory;
    vector<Loan> loans;
};

// Check PIN number of digits
int count_digits(int number){
  if (number == 0){
    return 1;
  }
  
  int digits = 0;
  
  while (number != 0){
    number = number / 10;
    digits++;
  }
  return digits;
}

// To create a new account
void createAccount(User &user) {
    
    cout << "First Name: ";
    getline(cin, user.firstName);
    cout << "Middle Name: ";
    cin >> user.middleName;
    cout << "Last Name: ";
    cin >> user.lastName;
    cout << "Age: ";
    cin >> user.age;
    if (user.age < 18) {
        cout << "Sorry, you must be at least 18 years old to open an account." << endl;
        cout << "Exiting program. You are below the legal age to use this application." << endl;
        exit(0);
    }
    
    cout << "Gender (M/F): ";
    cin >> user.gender;
    cout << "Nationality: ";
    cin >> user.nationality;
    cout << "Birthday (MM/DD/YYYY): ";
    cin >> user.birthday;
    cout << "Email: ";
    cin >> user.email;
    cout << "Cellphone number: ";
    cin >> user.cpnumber;

    cout << "Main Source of Funds (e.g., Salary, Allowance): ";
    cin.ignore(); 
    getline(cin, user.sourceOfFunds);

    user.balance = 0; // Initialize balance to 0
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "***********************************************************" << endl;
    cout << "               ACCOUNT CREATED SUCCESSFULLY!               " << endl;
    cout << "***********************************************************" << endl;
    cout << endl << "-----------------------------------------------------------" << endl;
    cout << "? Set Your Unique Username, Password, and PIN" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "\n? Create a new username: ";
    cin >> user.username;
    cout << "|                                                         |";
    cout << endl << "***********************************************************" << endl;
    cout << "NOTE: CREATE A STRONG PASSWORD! \n(You can include symbols, capitalized letters, and special \ncharacters to increase security)" << endl;
    cout << "***********************************************************\n" << endl;
    cout << "? Create a new alphanumeric password: ";
    cin >> user.password;
  
   while(user.password.length() < 8){
   if(user.password.length() < 8){
       cout << "Invalid password. Please Try Again.";
       cout << "\n\n";
       cout << ">Create a new alphanumeric password: ";
       cin >> user.password;
   }
}
    do {
    cout << "? Create a new 4-digit PIN: ";

    // Check if the input is an integer and has exactly 4 digits
    while (!(cin >> user.pin) || cin.peek() != '\n' || count_digits(user.pin) != 4) {
        cout << "\nInvalid PIN. Please enter exactly 4 digits.";
        cout << "\n\n";
        cin.clear();
        cin.ignore(123, '\n');
        cout << "? Create a new 4-digit PIN: ";
    }

    char nextChar;
    if (cin.get(nextChar) && nextChar != '\n') {
        cout << "\nInvalid PIN. Please enter exactly 4 digits.";
        cout << "\n\n";
        cin.ignore(123, '\n'); // Ignore extra characters
    }

} while (count_digits(user.pin) != 4);
}

// To login to the account
bool login(User &user, string username, string password, int pin) {
    return (user.username == username && user.password == password && user.pin == pin);
}

// To deposit money
void deposit(User &user, double amount) {
    user.balance += amount;
    user.transactionHistory.push_back("Deposit: +?" + to_string(amount));
    cout << "Deposit successful. Your new balance is: ?" << user.balance << endl;
}

// To view account balance
void viewBalance(User &user) {
    cout << "-----------------------------------------------------------" << endl;
    cout << "Your current balance is: ?" << user.balance << endl;
}

// To transfer money
void transfer(User &user, User &recipient, double amount) {
    if (user.balance >= amount) {
        user.balance -= amount;
        recipient.balance += amount;
        user.transactionHistory.push_back("Transfer to " + to_string(recipient.cpnumber) + ": -?" + to_string(amount));
        recipient.transactionHistory.push_back("Transfer from " + to_string(user.cpnumber) + ": +?" + to_string(amount));
        cout << "Transfer successful. Your new balance is: ?" << user.balance << endl;
    } else {
        cout << "Insufficient funds to complete the transfer." << endl;
    }
}

// To withdraw money
void withdraw(User &user, double amount) {
    if (user.balance >= amount) {
        user.balance -= amount;
        // Add transaction to history
        user.transactionHistory.push_back("Withdrawal: -?" + to_string(amount));
        cout << "Withdrawal successful. Your new balance is: ?" << user.balance << endl;
    } else {
        cout << "Insufficient funds to complete the withdrawal." << endl;
    }
}

// To pay bills
void payBills(User &user) {
    cout << "Select the type of bill you want to pay:" << endl;
    cout << "1. Electric Utilities" << endl;
    cout << "2. Water Utilities" << endl;
    cout << "3. Cable/Internet" << endl;
    cout << "4. Telecoms" << endl;
    cout << "5. Insurance" << endl;
    cout << "Enter your choice: ";

    int billChoice;
    cin >> billChoice;

    string billAccName;
    double billAmount;
    long billAccNum;

    switch (billChoice) {
        case 1:
            billAccName = "PeraByteElec";
            cout << billAccName << endl;
            cout << "Enter electricity bill amount: ?";
            cin >> billAmount;
            cout << "[1xxxxxxx. Ex. 10780125]" << endl;
            cout << "Enter 8-digit customer account number:";
            cin >> billAccNum;
            break;
        case 2:
            billAccName = "PerByteWater";
            cout << billAccName << endl;
            cout << "Enter water bill amount: ?";
            cin >> billAmount;
            cout << "[2xxxxxxx. Ex. 20780125]" << endl;
            cout << "Enter 8-digit contract account number:";
            cin >> billAccNum;
            break;
        case 3:
            billAccName = "PeraByteIntCab";
            cout << billAccName << endl;
            cout << "Enter cable/internet bill amount: ?";
            cin >> billAmount;
            cout << "[3xxxxxxx. Ex. 30780125]" << endl;
            cout << "Enter 8-digit account number:";
            cin >> billAccNum;
            break;
        case 4:
            billAccName = "PeraByteTelcom";
            cout << billAccName << endl;
            cout << "Enter telecommunications bill amount: ?";
            cin >> billAmount;
            cout << "[4xxxxxxx. Ex. 40780125]" << endl;
            cout << "Enter 8-digit account number:";
            cin >> billAccNum;
            break;
        case 5:
            billAccName = "PeraByteInsu";
            cout << billAccName << endl;
            cout << "Enter insurance bill amount: ?";
            cin >> billAmount;
            cout << "[5xxxxxxx. Ex. 50780125]" << endl;
            cout << "Enter 8-digit account number:";
            cin >> billAccNum;
            break;
        default:
            cout << "Invalid choice." << endl;
            return;
    }

    if (billAmount <= user.balance) {
        user.balance -= billAmount;
        cout << "Bill payment successful. Your new account balance is: ?" << user.balance << endl;
        user.transactionHistory.push_back("Bill Payment: " + (billAccName) + " - #" + to_string(billAccNum) + ": -?" + to_string(billAmount));
    } else {
        cout << "Insufficient funds to pay the bill." << endl;
    }
}


// To manage account
void manageAccount(User &user) {
    cout << "-----------------------------------------------------------" << endl;
    cout << "Select an option for account management:" << endl;
    cout << "1. View Information" << endl;
    cout << "2. Update Information" << endl;
    cout << "3. Change Password" << endl;
    cout << "4. Change Username" << endl;
    cout << "5. Change PIN" << endl;
    cout << "6. Close Account" << endl;
    cout << "Enter your choice: ";

    int accountChoice;
    cin >> accountChoice;

    switch (accountChoice) {
        case 1: {
            // Displaying user information
            cout << "-----------------------------------------------------------" << endl;
            cout << "User Information:" << endl;
            cout << "First Name: " << user.firstName << endl;
            cout << "Middle Name: " << user.middleName << endl;
            cout << "Last Name: " << user.lastName << endl;
            cout << "Age: " << user.age << endl;
            cout << "Gender: " << user.gender << endl;
            cout << "Nationality: " << user.nationality << endl;
            cout << "Birthday: " << user.birthday << endl;
            cout << "Email: " << user.email << endl;
            cout << "Cellphone number: " << user.cpnumber << endl;
            cout << "Source of Funds: " << user.sourceOfFunds << endl;
            break;
        }
        case 2: {
            // Updating user information
            cout << "-----------------------------------------------------------" << endl;
            cout << "Enter updated information:" << endl;
            cout << "First Name: ";
            cin >> user.firstName;
            cout << "Middle Name: ";
            cin >> user.middleName;
            cout << "Last Name: ";
            cin >> user.lastName;
            cout << "Age: ";
            cin >> user.age;
            cout << "Gender (M/F): ";
            cin >> user.gender;
            cout << "Nationality: ";
            cin >> user.nationality;
            cout << "Birthday (MM/DD/YYYY): ";
            cin >> user.birthday;
            cout << "Email: ";
            cin >> user.email;
            cout << "Cellphone number: ";
            cin >> user.cpnumber;
            cout << "Source of Funds: ";
            cin.ignore();
            getline(cin, user.sourceOfFunds);
            cout << "Information updated successfully." << endl;
            break;
        }
        case 3: {
            // Changing password
            cout << "-----------------------------------------------------------" << endl;
            string newPassword;
            cout << "Enter your current password: ";
            string currentPassword;
            cin >> currentPassword;
        
            if (currentPassword == user.password) {
                cout << "Enter a new password: ";
                cin >> newPassword;
                user.password = newPassword;
                
            while(newPassword.length() < 8){
            if(newPassword.length() < 8){
                cout << "Invalid password. Please Try Again.";
                cout << "\n\n";
                cout << "Enter a new pasword: ";
                cin >> newPassword;
            }
        }
                cout << "Password changed successfully." << endl;

                // Require the user to log in again after changing the password
                cout << "-----------------------------------------------------------" << endl;
                cout << "Please log in again with your new password." << endl;
                cout << "Username: ";
                cin >> user.username;
                cout << "Password: ";
                cin >> user.password;
                cout << "PIN: ";
                cin >> user.pin;

                // Check login credentials
                if (!login(user, user.username, newPassword, user.pin)) {
                    cout << "Invalid login credentials. Exiting program." << endl;
                    exit(0);
                }
            } else {
                cout << "Incorrect current password. Password change aborted." << endl;
            }
            break;
        }
        case 4: {
            // Changing username
            cout << "-----------------------------------------------------------" << endl;
            string newUsername;
            cout << "Enter your current username: ";
            string currentUsername;
            cin >> currentUsername;
            
            if (currentUsername == user.username) {
                cout << "Enter a new username: ";
                cin >> newUsername;
                user.username = newUsername;
                
         
                cout << "Username changed successfully." << endl;

                // Require the user to log in again after changing the password
                cout << "-----------------------------------------------------------" << endl;
                cout << "Please log in again with your new password." << endl;
                cout << "Username: ";
                cin >> user.username;
                cout << "Password: ";
                cin >> user.password;
                cout << "PIN: ";
                cin >> user.pin;

                // Check login credentials
                if (!login(user, newUsername, user.password, user.pin)) {
                    cout << "Invalid login credentials. Exiting program." << endl;
                    exit(0);
                }
            } else {
                cout << "Incorrect current password. Password change aborted." << endl;
            }
            
             
            break;
        }
        case 5: {
            // Changing PIN
            cout << "-----------------------------------------------------------" << endl;
            cout << "Enter your current PIN: ";
            int currentPIN;
            
            if(!(cin >> currentPIN)){
                cout << "Incorrect current PIN. PIN change aborted." << endl;
                cin.clear();
                cin.ignore(123, '\n');
                bool login(User &user, string username, string password, int pin);
            }
            
            else if(currentPIN == user.pin) {
            do {
                cout << "Enter your new PIN: ";

            // Check if the input is an integer and has exactly 4 digits
            while (!(cin >> user.pin) || cin.peek() != '\n' || count_digits(user.pin) != 4) {
                cout << "\nInvalid PIN. Please enter exactly 4 digits.";
                cout << "\n\n";
                cin.clear();
                cin.ignore(123, '\n');
                cout << "Enter your new PIN: ";
        }

            char nextChar;
            if (cin.get(nextChar) && nextChar != '\n') {
                cout << "\nInvalid PIN. Please enter exactly 4 digits.";
                cout << "\n\n";
                cin.ignore(123, '\n'); // Ignore extra characters
        }

    }           while (count_digits(user.pin) != 4);

                int newPIN = user.pin;
                cout << "PIN changed successfully." << endl;

                // Require the user to log in again after changing the PIN
                cout << "-----------------------------------------------------------" << endl;    
                cout << "Please log in again with your new PIN." << endl;
                cout << "Username: ";
                cin >> user.username;
                cout << "Password: ";
                cin >> user.password;
                cout << "PIN: ";
                cin >> user.pin;

                // Check login credentials
                if (!login(user, user.username, user.password, newPIN)) {
                    cout << "Invalid login credentials. Exiting program." << endl;
                    exit(0);
                }
            } else {
                cout << "Incorrect current PIN. PIN change aborted." << endl;
                bool login(User &user, string username, string password, int pin);
          }
            break;
        }
            
        case 6: {
            cout << "-----------------------------------------------------------" << endl;
            cout << "Are you sure you want to close your account? (Y/N): ";
            char closeChoice;
            cin >> closeChoice;
            if (closeChoice == 'Y' || closeChoice == 'y') {
                cout << "Account closed successfully. Thank you for using PeraByte!" << endl;
            
                exit(0);
            } else {
                cout << "Account closure canceled." << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice." << endl;
            break;
    }
}

// To view transaction history
void viewTransactionHistory(const User &user) {
    cout << "Transaction History:" << endl;
    for (const string &transaction : user.transactionHistory) {
        cout << transaction << endl;
    }
}

// To apply for Loan
void applyForLoan(User &user, const string &loanType) {
    double loanAmount;
    int loanDuration;

    cout << "Enter the amount for your " << loanType << ": ?";
    cin >> loanAmount;

    cout << "Enter the duration for your " << loanType << " (in months): ";
    cin >> loanDuration;

    // Fixed interest rate 
    double interestRate = 0.0083; // 9.96%
    user.balance += loanAmount;

    user.transactionHistory.push_back("Loaned Amount: +?" + to_string(loanAmount));

    // Calculate total repayment amount (including interest)
    double interestAmount= loanAmount * (interestRate * loanDuration);
    double totalRepayment = loanAmount +  interestAmount;

    Loan newLoan = {loanType, loanAmount, loanDuration, totalRepayment};
    user.loans.push_back(newLoan);

    // Display loan details
    cout << "***********************************************************" << endl;
    cout << "LOAN APPLICATION APPROVED." << endl;
    cout << "***********************************************************" << endl;
    cout << "Loan details:" << endl;
    cout << "Loan Type: " << loanType << endl;
    cout << "Loan Amount: ?" << loanAmount << endl;
    cout << "Annual Interest Rate: " << (interestRate * 12 * 100) << "%" <<  endl;
    cout << "Interest Amount: ?" << interestAmount << endl;
    cout << "Loan Duration: " << loanDuration << " months" << endl;
    cout << "Monthly Payment: ?" << (totalRepayment/loanDuration) << endl;
    cout << "Total Accrued Amount (Loan Amount + Interest Amount):\n?" << totalRepayment << endl;
    cout << endl << "Successful Loan Application." << endl;
    cout << "Your new account balance is: ?" << user.balance << endl;
}

void loanServices(User &user) {
    cout << "-----------------------------------------------------------" << endl;
    cout << "Loan Services:" << endl;
    cout << "1. Apply for Personal Loan (Simple Interest Loan)" << endl;
    cout << "2. View Loan Details" << endl;
    cout << "3. Make Loan Repayment" << endl;
    cout << "Enter your choice: ";

    int loanChoice;
    cin >> loanChoice;

    double totalRemainingBalance = 0.0; 

    switch (loanChoice) {
        case 1:
            applyForLoan(user, "Personal Loan");
            break;
        case 2:
            
            cout << "Loan Details:" << endl;
            for (const Loan &loan : user.loans) {
                cout << "Loan Type: " << loan.type << endl;
                cout << "Loan Amount: ?" << loan.amount << endl;
                cout << "Loan Duration: " << loan.duration << " months" << endl;
                totalRemainingBalance += loan.remainingBalance; 
                cout << "-------------------------" << endl;
            }
            cout << "Total Remaining Loan Balance: ?" << totalRemainingBalance << endl; 
            break;
        case 3:
           
                double repaymentAmount;
                
                cout << "Enter the repayment amount: ?";
                cin >> repaymentAmount;

                if (repaymentAmount <= user.balance) {
                    user.balance -= repaymentAmount;
                
                    user.transactionHistory.push_back("Repayment for Loan: -?" + to_string(repaymentAmount));

                    // Distribute repayment among all loans
                    for (Loan &loan : user.loans) {
                        if (repaymentAmount >= loan.remainingBalance) {
                            repaymentAmount -= loan.remainingBalance;
                            loan.remainingBalance = 0;
                        } else {
                            loan.remainingBalance -= repaymentAmount;
                            repaymentAmount = 0;
                            break;
                        }
                    }

                    cout << "Loan repayment successful. Your new account balance is: ?" << user.balance << endl;
                } else {
                    cout << "Insufficient funds to make loan repayment." << endl;
                }
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
}


int main() {
    User user;
    int maxAttempts = 3;

    cout << "------------------- WELCOME TO PERABYTE! ------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "? Open a Checking Account with PeraByte." << endl;
    cout << "? Experience seamless transactions and flexible loan\n services, allowing you to borrow up to ?900,000 at an\n annual interest rate as low as 9.96%." << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "? Register here to create a PeraByte Account" << endl;
    cout << "? Tell us something about yourself [PERSONAL INFORMATION?] " << endl;
    cout << "-----------------------------------------------------------" << endl;
    
    // Create account
    createAccount(user);

    // Login
    string username, password;
    int pin;
    bool loggedIn = false;
    
    while(!loggedIn){
    for (int attempts = 1; attempts <= maxAttempts; ++attempts) {
        cout << endl << "-----------------------------------------------------------" << endl;
        cout << "               Please login to proceed.               " << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        cout << "PIN: ";
        cin >> pin;

        // Check login credentials
        if (login(user, username, password, pin)) {
            loggedIn = true;
            break;
        } else {
            cout << "Invalid credentials. Please try again. Remaining Attempts: " << (maxAttempts - attempts) << endl;
        }
    }

    if (loggedIn) {
        cout << "***********************************************************" << endl;
        cout << "               WELCOME TO PeraByte!               " << endl;
        cout << "Hi, " << user.firstName << "!" << endl;
        cout << "0" << user.cpnumber << endl;
        cout << "***********************************************************" << endl;

        bool done = false;
        while (!done) {
            cout << "Select an option:" << endl;
            cout << "1. Deposit" << endl;
            cout << "2. View Account Balance" << endl;
            cout << "3. Transfer Funds" << endl;
            cout << "4. Withdraw" << endl;
            cout << "5. Pay Bills" << endl;
            cout << "6. Manage Account" << endl; 
            cout << "7. View Transaction History" << endl;
            cout << "8. Loan Services" << endl;
            cout << "9. Logout" << endl;

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    double amount;
                    cout << "-----------------------------------------------------------" << endl;
                    cout << "Enter amount to deposit: ?";
                    cin >> amount;
                    deposit(user, amount);
                    break;
                }
                case 2:
                    viewBalance(user);
                    break;
                case 3: {
                    User recipient;
                    cout << "-----------------------------------------------------------" << endl;
                    cout << "Enter recipient's cellphone number: ";
                    cin >> recipient.cpnumber; 
                    double transferAmount;
                    cout << "Enter amount to transfer: ?";
                    cin >> transferAmount;
                    transfer(user, recipient, transferAmount);
                    break;
                }
                case 4: {
                    double withdrawAmount;
                    cout << "-----------------------------------------------------------" << endl;
                    cout << "Enter amount to withdraw: ?";
                    cin >> withdrawAmount;
                    withdraw(user, withdrawAmount);
                    break;
                }
                case 5:
                    payBills(user);
                    break;
                case 6:
                    manageAccount(user); 
                    break;
                case 7:
                    viewTransactionHistory(user); 
                    break;
                case 8:
                    loanServices(user);
                    break;
                case 9:
                    cout << endl << "***********************************************************" << endl;
                    cout << "            THANK YOU FOR USING PeraByte!????•???•????          " << endl;
                    cout << "                  Logged out successfully.                 " << endl;
                    cout << "***********************************************************" << endl;
                    done = true;
                    loggedIn = false;
                    break;
                default:
                    cout << "Invalid choice." << endl;
            }

            if (!done) {
                char isDone;
	        	cout << "-----------------------------------------------------------" << endl;
                cout << "Proceed to next procedure (1. BACK TO MENU/2. LOGOUT): ";
                cin >> isDone;
                
                do{
                    if(isDone != '2' && isDone != '1'){
                        cout << "Invalid choice. Please try again: ";
                        cin >> isDone;
                    }
                } while(isDone != '2' && isDone != '1');
                
                if (isDone == '1') {
                    cout << "-----------------------------------------------------------" << endl;
                } else if (isDone == '2'){
                    cout << endl << "***********************************************************" << endl;
                    cout << "            THANK YOU FOR USING PeraByte!????•???•????          " << endl;
                    cout << "                  Logged out successfully.                 " << endl;
                    cout << "***********************************************************" << endl;
                    done = true;
                    loggedIn = false;
                }
            }
        }

    } else {
        cout << "Maximum login attempts reached. Exiting program." << endl;
    cout << endl << "------------------- WELCOME TO PERABYTE! ------------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "? Open a Checking Account with PeraByte." << endl;
    cout << "? Experience seamless transactions and flexible loan\n services, allowing you to borrow up to ?900,000 at an\n annual interest rate as low as 9.96%." << endl;
    cout << "-----------------------------------------------------------" << endl;
    }
}
    return 0;
}



