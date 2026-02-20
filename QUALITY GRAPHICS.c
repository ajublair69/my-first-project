#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_BALANCE 0000

typedef struct {
    int accountNumber;
    char name[5000];
    char item[5000];
    double balance;
} Customer;

void saveAccount(Customer c);
Customer loadAccount(int accNumber, int *found);
void printStatement(Customer c);
void updateAccount(Customer c);

int main() {
    int choice, found;
    double amount;
    Customer customer;

    while (1) {
         printf("\n====== QUALITY GRAPHICS ======\n");
        printf("1. MAKE AN ORDER AT QUALITY GRAPHICS\n");
        printf("2. DEPOSITE MONEY AT QUALITY GRAPHICS\n");
        printf("3. ORDERS COLLECTED AT QUALITY GRAPHICS\n");
        printf("4. PRINT ACCOUNT STATEMENT\n");
        printf("5. Exit\n");
        printf("CHOOSE OPTIONS: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1: {
            // Open new account
            printf("Create An Order Number: ");
            scanf("%d", &customer.accountNumber);

            printf("Enter Customer Name: ");
            scanf("%s", &customer.name);
            printf("Enter  Items Ordered : ");
            scanf("%s", &customer.item);

            
            customer.balance = amount;

            saveAccount(customer);
            printf("Order Made successfully!\n");
        }
        break;

        case 2: {
            // Deposit
            printf("Enter account number: ");
            int acc; scanf("%d", &acc);

            customer = loadAccount(acc, &found);
            if (!found) {
                printf("Account not found!\n");
                break;
            }

            printf("Enter amount to deposit: ");
            scanf("%lf", &amount);

            if (amount > 0) {
                customer.balance += amount;
                updateAccount(customer);
                printf("Deposit successful.\n");
            } else {
                printf("Invalid deposit amount.\n");
            }
        }
        break;

        case 3: {
            // Withdrawal
            printf("Enter account number: ");
            int acc; scanf("%d", &acc);

            customer = loadAccount(acc, &found);
            if (!found) {
                printf("Account not found!\n");
                break;
            }

            printf("Enter amount to withdraw: ");
            scanf("%lf", &amount);

            if (amount <= 0) {
                printf("Invalid withdrawal amount.\n");
                break;
            }

            if (customer.balance -amount < MIN_BALANCE) {
                printf("? Withdrawal denied! Balance cannot go below 10,000 UGX.\n");
            } else {
                customer.balance -= amount;
                updateAccount(customer);
                printf(" Order Withdrawn successful.\n");
            }
        }
        break;

        case 4: {
            // Print statement
            printf("Enter account number: ");
            int acc; scanf("%d", &acc);

            customer = loadAccount(acc, &found);
            if (!found) {
                printf("Account not found!\n");
                break;
            }

            printStatement(customer);
        }
        break;

        case 5:
            printf("Thank you for using quality grahics system.\n");
            return 0;

        default:
            printf("Invalid option.\n");
        }
    }
    return 0;
}

/* ===========================
   SAVE NEW ACCOUNT TO FILE
   =========================== */
void saveAccount(Customer c) {
    FILE *f = fopen("accounts.txt", "a");
    fprintf(f, "%d %s %.2f %s\n", c.accountNumber, c.name, c.balance,c.item);
    fclose(f);
}

/* ===========================
   UPDATE EXISTING ACCOUNT
   =========================== */
void updateAccount(Customer c) {
    FILE *f = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Customer t;

    while (fscanf(f, "%d %s %lf %s", &t.accountNumber, t.name, &t.balance,t.item) != EOF) {
        if (t.accountNumber == c.accountNumber) {
            fprintf(temp, "%d %s %.2f %s\n", c.accountNumber, c.name, c.balance,c.item);
        } else {
            fprintf(temp, "%d %s %.2f %s\n", t.accountNumber, t.name, t.balance,c.item);
        }
    }

    fclose(f);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}

/* ===========================
   LOAD ACCOUNT FROM FILE
   =========================== */
Customer loadAccount(int accNumber, int *found) {
    FILE *f = fopen("accounts.txt", "r");
    Customer c;
    *found = 0;

    if (!f) {
        printf("No accounts found.\n");
        return c;
    }

    while (fscanf(f, "%d %s %lf %s", &c.accountNumber, c.name, &c.balance,c.item) != EOF) {
        if (c.accountNumber == accNumber) {
            *found = 1;
            break;
        }
    }

    fclose(f);
    return c;
}

/* ===========================
   PRINT STATEMENT
   =========================== */
void printStatement(Customer c) {
    printf("\n===== ACCOUNT STATEMENT =====\n");
    printf("Name: %s\n", c.name);
    printf("Account Number: %d\n", c.accountNumber);
    printf("Items Ordered Are:%s\n",c.item);
    printf("Total Money Paid: %.2f UGX\n", c.balance);
    printf("===========DESIGNED BY AJU BLAIR==================\n");
}

