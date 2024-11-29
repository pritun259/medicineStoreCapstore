#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to hold medicine details
typedef struct
{
    char name[100];
    char manufacturer[100];
    float purchasePrice;
    float sellingPrice;
    int stockQuantity;
} Medicine;

// Structure to hold sales record
typedef struct
{
    char name[100];
    int quantitySold;
    float sellingPrice;
    float purchasePrice;
    float totalSale;
} Sale;

// Global variables
Medicine medicines[100];
Sale sales[100];
int medicineCount = 0;
int salesCount = 0;

// Function declarations
int login();
void addMedicine();
void purchaseRecordDetail();
void manageStock();
void displayMedicines();
void searchMedicine();
void deleteMedicine();
void returnMedicine();
void sellMedicine();
void salesTrack();
void loadMedicinesFromFile();
void saveMedicinesToFile();
void saveSalesToFile();

// Main function
int main()
{
    int choice;
    printf("==== Pharmacy Inventory and Sales Management ====\n");

    if (!login())
    {
        printf("Invalid login! Exiting program...\n");
        return 0;
    }

    loadMedicinesFromFile(); // Load medicines from file on startup

    while (1)
    {
        printf("\n==== Main Menu ====\n");
        printf("1. Add Medicine\n");
        printf("2. Purchase Record Detail\n");
        printf("3. Manage Stock\n");
        printf("4. Display Medicines\n");
        printf("5. Search Medicine\n");
        printf("6. Delete Medicine\n");
        printf("7. Return Medicine\n");
        printf("8. Sell Medicine\n");
        printf("9. Sales Track\n");
        printf("10. Log Out\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addMedicine();
            break;
        case 2:
            purchaseRecordDetail();
            break;
        case 3:
            manageStock();
            break;
        case 4:
            displayMedicines();
            break;
        case 5:
            searchMedicine();
            break;
        case 6:
            deleteMedicine();
            break;
        case 7:
            returnMedicine();
            break;
        case 8:
            sellMedicine();
            break;
        case 9:
            salesTrack();
            break;
        case 10:
            printf("Logging out...\n");
            saveMedicinesToFile(); // Save medicines to file on exit
            saveSalesToFile();     // Save sales to file
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

// Function to load medicines from a file
void loadMedicinesFromFile()
{
    FILE *file = fopen("medicines.txt", "r");

    if (file == NULL)
    {
        printf("No existing data found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%s,%s,%f,%f,%d\n",
                  medicines[medicineCount].name,
                  medicines[medicineCount].manufacturer,
                  &medicines[medicineCount].purchasePrice,
                  &medicines[medicineCount].sellingPrice,
                  &medicines[medicineCount].stockQuantity) != EOF)
    {
        medicineCount++;
    }
    fclose(file);
    printf("Loaded %d medicines from file.\n", medicineCount);
}

// Function to save medicines to a file
void saveMedicinesToFile()
{
    FILE *file = fopen("medicines.txt", "w");

    if (file == NULL)
    {
        printf("Error saving data to file!\n");
        return;
    }

    for (int i = 0; i < medicineCount; i++)
    {
        fprintf(file, "%s,%s,%.2f,%.2f,%d\n",
                medicines[i].name,
                medicines[i].manufacturer,
                medicines[i].purchasePrice,
                medicines[i].sellingPrice,
                medicines[i].stockQuantity);
    }

    fclose(file);
    printf("Medicines saved to file.\n");
}

// Function to save sales data to a file
void saveSalesToFile()
{
    FILE *file = fopen("sales.txt", "w");

    if (file == NULL)
    {
        printf("Error saving sales data to file!\n");
        return;
    }

    for (int i = 0; i < salesCount; i++)
    {
        fprintf(file, "%s,%d,%.2f,%.2f,%.2f\n",
                sales[i].name,
                sales[i].quantitySold,
                sales[i].sellingPrice,
                sales[i].purchasePrice,
                sales[i].totalSale);
    }

    fclose(file);
}

// Function to perform login
int login()
{
    char username[50], password[50];

    printf("LOGIN:\n");
    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    return (strcmp(username, "pritun") == 0 && strcmp(password, "259") == 0);
}

// Function to add medicine
void addMedicine()
{
    if (medicineCount >= 100)
    {
        printf("Medicine inventory is full!\n");
        return;
    }

    Medicine newMedicine;
    printf("Enter medicine name: ");
    getchar();
    fgets(newMedicine.name, sizeof(newMedicine.name), stdin);
    newMedicine.name[strcspn(newMedicine.name, "\n")] = 0;

    printf("Enter manufacturer: ");
    fgets(newMedicine.manufacturer, sizeof(newMedicine.manufacturer), stdin);
    newMedicine.manufacturer[strcspn(newMedicine.manufacturer, "\n")] = 0;

    printf("Enter purchase price: ");
    scanf("%f", &newMedicine.purchasePrice);

    printf("Enter selling price: ");
    scanf("%f", &newMedicine.sellingPrice);

    printf("Enter stock quantity: ");
    scanf("%d", &newMedicine.stockQuantity);

    medicines[medicineCount++] = newMedicine;
    printf("Medicine added successfully!\n");

    saveMedicinesToFile();
}

// Function to view purchase record detail
void purchaseRecordDetail()
{
    printf("==== Purchase Record Detail ====\n");
    for (int i = 0; i < medicineCount; i++)
    {
        printf("Name: %s, Manufacturer: %s, Purchase Price: %.2f, Selling Price: %.2f, Stock: %d\n",
               medicines[i].name, medicines[i].manufacturer, medicines[i].purchasePrice,
               medicines[i].sellingPrice, medicines[i].stockQuantity);
    }
}

// Function to manage stock
void manageStock()
{
    char name[100];
    int quantity;

    printf("Enter medicine name to update stock: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < medicineCount; i++)
    {
        if (strcmp(medicines[i].name, name) == 0)
        {
            printf("Enter quantity to add: ");
            scanf("%d", &quantity);
            medicines[i].stockQuantity += quantity;
            printf("Updated stock for %s to %d\n", medicines[i].name, medicines[i].stockQuantity);

            saveMedicinesToFile();
            return;
        }
    }

    printf("Medicine not found!\n");
}

// Function to display all medicines
void displayMedicines()
{
    printf("==== Medicine Inventory ====\n");
    for (int i = 0; i < medicineCount; i++)
    {
        printf("Name: %s, Manufacturer: %s, Purchase Price: %.2f, Selling Price: %.2f, Stock: %d\n",
               medicines[i].name, medicines[i].manufacturer, medicines[i].purchasePrice,
               medicines[i].sellingPrice, medicines[i].stockQuantity);
    }
}

// Function to search for medicine
void searchMedicine()
{
    char query[100];
    printf("Enter medicine name or manufacturer to search: ");
    getchar();
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = 0;

    printf("Search Results:\n");
    for (int i = 0; i < medicineCount; i++)
    {
        if (strstr(medicines[i].name, query) || strstr(medicines[i].manufacturer, query))
        {
            printf("Name: %s, Manufacturer: %s, Purchase Price: %.2f, Selling Price: %.2f, Stock: %d\n",
                   medicines[i].name, medicines[i].manufacturer, medicines[i].purchasePrice,
                   medicines[i].sellingPrice, medicines[i].stockQuantity);
        }
    }
}

// Function to delete a medicine
void deleteMedicine()
{
    char name[100];
    printf("Enter medicine name to delete: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < medicineCount; i++)
    {
        if (strcmp(medicines[i].name, name) == 0)
        {
            for (int j = i; j < medicineCount - 1; j++)
            {
                medicines[j] = medicines[j + 1];
            }
            medicineCount--;
            printf("Medicine %s deleted.\n",medicines[i].name);

            saveMedicinesToFile();
            return;
        }
    }

    printf("Medicine not found!\n");
}

// Function to return a medicine
void returnMedicine()
{
    char name[100];
    int quantity;

    printf("Enter medicine name to return: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter quantity to return: ");
    scanf("%d", &quantity);

    for (int i = 0; i < medicineCount; i++)
    {
        if (strcmp(medicines[i].name, name) == 0)
        {
            medicines[i].stockQuantity += quantity;
            printf("Returned %d units of %s. Stock updated.\n", quantity, medicines[i].name);

            saveMedicinesToFile();
            return;
        }
    }

    printf("Medicine not found!\n");
}

// Function to sell a medicine
void sellMedicine()
{
    char name[100];
    int quantity;

    printf("Enter medicine name to sell: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter quantity to sell: ");
    scanf("%d", &quantity);

    for (int i = 0; i < medicineCount; i++)
    {
        if (strcmp(medicines[i].name, name) == 0)
        {
            if (medicines[i].stockQuantity >= quantity)
            {
                medicines[i].stockQuantity -= quantity;

                // Recording the sale
                Sale newSale = {
                    .quantitySold = quantity,
                    .sellingPrice = medicines[i].sellingPrice,
                    .purchasePrice = medicines[i].purchasePrice,
                    .totalSale = medicines[i].sellingPrice * quantity};
                strcpy(newSale.name, name);

                sales[salesCount++] = newSale;

                printf("Sold %d units of %s for %.2f.\n", quantity, name, newSale.totalSale);

                saveMedicinesToFile();
                saveSalesToFile();
                return;
            }
            else
            {
                printf("Not enough stock for this sale!\n");
                return;
            }
        }
    }

    printf("Medicine not found!\n");
}

// Function to track sales
void salesTrack()
{
    printf("==== Sales Track ====\n");
    for (int i = 0; i < salesCount; i++)
    {
        printf("Name: %s, Quantity Sold: %d, Selling Price: %.2f, Purchase Price: %.2f, Total Sale: %.2f\n",
               sales[i].name, sales[i].quantitySold, sales[i].sellingPrice,
               sales[i].purchasePrice, sales[i].totalSale);
    }
}