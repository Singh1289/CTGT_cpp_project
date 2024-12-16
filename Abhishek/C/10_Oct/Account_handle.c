#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Account_id = 120240;

// Define enum
typedef enum {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER
} TransactionType;

// Union for transaction details
typedef union {
    struct {
        double amount;
    } deposit;

    struct {
        double amount;
    } withdrawal;

    struct {
        double amount;
        int fromAcc;
        int toAcc;
    } transfer;
} TransactionDetails;

// Struct for transactions
typedef struct {
    int id;
    TransactionType type;
    TransactionDetails details;
} Transaction;

// Struct for accounts
typedef struct {
    int accountId;
    double balance;
    char name[50];
    char mobile[15];
} Account;

// Function to create a new transaction
Transaction* createTransaction(int id, TransactionType type, double amount, int fromAccount, int toAccount) {
    Transaction* newTransaction = (Transaction*)malloc(sizeof(Transaction));
    newTransaction->id = id;
    newTransaction->type = type;

    switch (type) {
        case DEPOSIT:
            newTransaction->details.deposit.amount = amount;
            break;
        case WITHDRAWAL:
            newTransaction->details.withdrawal.amount = amount;
            break;
        case TRANSFER:
            newTransaction->details.transfer.amount = amount;
            newTransaction->details.transfer.fromAcc = fromAccount;
            newTransaction->details.transfer.toAcc = toAccount;
            break;
    }
    return newTransaction;
}

// Helper function to find an account index by account ID
int findAccountIndex(Account* accounts, int accountCount, int accountId) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountId == accountId) {
            return i;
        }
    }
    return -1;
}

// Function to process transactions
void processTransaction(Transaction* transaction, Account* accounts, int accountCount) {
    int accountIndex, fromIndex, toIndex;
    switch (transaction->type) {
        case DEPOSIT:
            accountIndex = findAccountIndex(accounts, accountCount, transaction->id);
            if (accountIndex == -1) {
                printf("Account ID %d not found.\n", transaction->id);
                return;
            }
            accounts[accountIndex].balance += transaction->details.deposit.amount;
            printf("Deposit of %.2f to Account ID %d. New Balance: %.2f\n",
                   transaction->details.deposit.amount,
                   transaction->id,
                   accounts[accountIndex].balance);
            break;

        case WITHDRAWAL:
            accountIndex = findAccountIndex(accounts, accountCount, transaction->id);
            if (accountIndex == -1) {
                printf("Account ID %d not found.\n", transaction->id);
                return;
            }
            if (accounts[accountIndex].balance >= transaction->details.withdrawal.amount) {
                accounts[accountIndex].balance -= transaction->details.withdrawal.amount;
                printf("Withdrawal of %.2f from Account ID %d. New Balance: %.2f\n",
                       transaction->details.withdrawal.amount,
                       transaction->id,
                       accounts[accountIndex].balance);
            } else {
                printf("Withdrawal of %.2f from Account ID %d failed. Insufficient funds.\n",
                       transaction->details.withdrawal.amount,
                       transaction->id);
            }
            break;

        case TRANSFER:
            fromIndex = findAccountIndex(accounts, accountCount, transaction->details.transfer.fromAcc);
            toIndex = findAccountIndex(accounts, accountCount, transaction->details.transfer.toAcc);
            if (fromIndex == -1 || toIndex == -1) {
                printf("Invalid account ID(s) for transfer.\n");
                return;
            }
            if (accounts[fromIndex].balance >= transaction->details.transfer.amount) {
                accounts[fromIndex].balance -= transaction->details.transfer.amount;
                accounts[toIndex].balance += transaction->details.transfer.amount;
                printf("Transfer of %.2f from Account ID %d to Account ID %d. New Balance from Account ID %d: %.2f, Account ID %d: %.2f\n",
                       transaction->details.transfer.amount,
                       transaction->details.transfer.fromAcc,
                       transaction->details.transfer.toAcc,
                       transaction->details.transfer.fromAcc,
                       accounts[fromIndex].balance,
                       transaction->details.transfer.toAcc,
                       accounts[toIndex].balance);
            } else {
                printf("Transfer of %.2f from Account ID %d to Account ID %d failed. Insufficient funds.\n",
                       transaction->details.transfer.amount,
                       transaction->details.transfer.fromAcc,
                       transaction->details.transfer.toAcc);
            }
            break;
    }
}

// Function to generate a report of all accounts
void generateReport(Account* accounts, int accountCount) {
    printf("\nAccount Report:\n");
    for (int i = 0; i < accountCount; i++) {
        printf("Account ID: %d, Name: %s, Mobile: %s, Balance: %.2f\n",
               accounts[i].accountId, accounts[i].name, accounts[i].mobile, accounts[i].balance);
    }
}

// Function to create a new account
void createAccount(Account* accounts, int* accountCount) {
    printf("Enter Account Holder's Name: ");
    scanf(" %[^\n]", accounts[*accountCount].name);
    printf("Enter Mobile Number: ");
    scanf("%s", accounts[*accountCount].mobile);
    accounts[*accountCount].accountId = Account_id++;
    accounts[*accountCount].balance = 0.0;
    (*accountCount)++;
    printf("Account created successfully with Account No.: %d\n", accounts[*accountCount - 1].accountId);
}

int main() {
    int maxAccounts = 100;
    Account* accounts = (Account*)malloc(maxAccounts * sizeof(Account));
    int accountCount = 0;
    int choice;
    int toAccNum;
    while (1) {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n|     ~ W E L C O M E ~       |");
        printf("\n|1 : Create Account           |");
        printf("\n|2 : Deposit                  |");
        printf("\n|3 : Withdraw                 |");
        printf("\n|4 : Transfer                 |");
        printf("\n|5 : Generate Report          |");
        printf("\n|6 : Exit                     |");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\nWhat would you like to do: ");
        scanf("%d", &choice);

        if (choice == 6) {
            break;
        }

        switch (choice) {
            case 1:
                createAccount(accounts, &accountCount);
                break;

            case 2:
            case 3:
            case 4:
                if (accountCount == 0) {
                    printf("No accounts available. Please create an account first.\n");
                    break;
                }
                int accountId;
                printf("Enter Account number: ");
                scanf("%d", &accountId);

                double amount;
                Transaction* transaction = NULL;
                switch (choice) {
                    case 2:
                        printf("Enter Amount to Deposit: ");
                        scanf("%lf", &amount);
                        transaction = createTransaction(accountId, DEPOSIT, amount, -1, -1);
                        processTransaction(transaction, accounts, accountCount);
                        free(transaction);
                        break;

                    case 3:
                        printf("Enter Amount to Withdraw: ");
                        scanf("%lf", &amount);
                        transaction = createTransaction(accountId, WITHDRAWAL, amount, -1, -1);
                        processTransaction(transaction, accounts, accountCount);
                        free(transaction);
                        break;

                    case 4:
                        
                        printf("Enter Destination Account number: ");
                        scanf("%d", &toAccNum);
                        printf("Enter Amount to Transfer: ");
                        scanf("%lf", &amount);
                        transaction = createTransaction(accountId, TRANSFER, amount, accountId, toAccNum);
                        processTransaction(transaction, accounts, accountCount);
                        free(transaction);
                        break;
                }
                break;

            case 5:
                generateReport(accounts, accountCount);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    free(accounts);
    return 0;
}
