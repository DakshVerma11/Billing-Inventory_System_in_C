#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <hpdf.h>

#define MAX_ITEMS 500
#define MAX_CUSTOMERS 100
#define MAX_LEN 50

//Text Formating
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN "\x1B[36m"

//Window Effects
#define RESETSAVE "\x1B[3J"
#define SCREENSAVE "\x1B[?47h"
#define CLEARALL "\x1B[2J"
#define SCREENRESTORE "\x1B[?47l"

//CURSOR
#define CURSORHIDE "\x1B[?25l"
#define CURSORSHOW "\x1B[?25h"
#define CURSORTOP "\x1B[H"
#define CURSORSAVE "\x1B[s"
#define CURSORRESTORE "\x1B[u"

typedef struct {
    int item_id;
    char item_name[MAX_LEN];
    int stock;
    float price;
    char category[MAX_LEN];
    char subcategory[MAX_LEN];
} InventoryItem;

typedef struct {
    int customer_id;
    char customer_name[MAX_LEN];
    char phone_number[MAX_LEN];
} Customer;


void loadInventory(InventoryItem inventory[], int *num_items) {
    FILE *inventoryFile = fopen("inventory.csv", "r");
    if (inventoryFile == NULL) {
        printf(BOLD RED"Error opening inventory file!\n"RESET);
        return;
    }

    // Read the additional fields Category and Subcategory
    while ((*num_items < MAX_ITEMS) && fscanf(inventoryFile, "%d,%[^,],%d,%f,%[^,],%[^\n]\n", 
        &inventory[*num_items].item_id, inventory[*num_items].item_name, 
        &inventory[*num_items].stock, &inventory[*num_items].price, 
        inventory[*num_items].category, inventory[*num_items].subcategory) == 6) {
        (*num_items)++;
    }

    fclose(inventoryFile);
}

void loadCustomers(Customer customers[], int *num_customers) {
    FILE *customerFile = fopen("customers.csv", "r");
    if (customerFile == NULL) {
        printf(BOLD RED"Error opening customers file!\n"RESET);
        return;
    }

    while ((*num_customers < MAX_CUSTOMERS) && fscanf(customerFile, "%d,%[^,],%[^\n]\n", &customers[*num_customers].customer_id,
                  customers[*num_customers].customer_name, customers[*num_customers].phone_number) != EOF) {
        (*num_customers)++;
    }

    fclose(customerFile);
}


void updateInventory(InventoryItem inventory[], int *num_items) {
    FILE *inventoryFile = fopen("inventory.csv", "a");
    if (inventoryFile == NULL) {
        printf(BOLD RED"Error opening file!\n"RESET);
        return;
    }

    printf("Enter item ID: ");
    scanf("%d", &inventory[*num_items].item_id);
    printf("Enter item Name: ");
    scanf(" %[^\n]", inventory[*num_items].item_name);
    printf("Enter item Stock and price: ");
    scanf("%d %f", &inventory[*num_items].stock, &inventory[*num_items].price);
    printf("Enter item Category and Subcategory: ");
    scanf(" %[^\n] %[^\n]", inventory[*num_items].category, inventory[*num_items].subcategory);

    fprintf(inventoryFile, "%d,%s,%d,%.2f,%s,%s\n", inventory[*num_items].item_id, inventory[*num_items].item_name,
        inventory[*num_items].stock, inventory[*num_items].price, inventory[*num_items].category, inventory[*num_items].subcategory);
    (*num_items)++;

    fclose(inventoryFile);
}


void displayInventory(InventoryItem inventory[], int num_items) {
    printf("\n=== Inventory ===\n");
    printf("ID                 Item Name\t        Stock\t      Price\t           Category\t         Subcategory\n");
    for (int i = 0; i < num_items; i++) {
        printf("%3d %20s %20d %20.2f %20s %20s\n", inventory[i].item_id, inventory[i].item_name,
            inventory[i].stock, inventory[i].price, inventory[i].category, inventory[i].subcategory);
    }
}


void registerCustomer(Customer customers[], int *num_customers) {
    FILE *customerFile = fopen("customers.csv", "a");
    if (customerFile == NULL) {
        printf(BOLD RED"Error opening customers file!\n"RESET);
        return;
    }

    printf("Enter customer Name : ");
    scanf(" %[^\n]",customers[*num_customers].customer_name);
    printf("Enter Phone Number  : ");
    scanf(" %s",customers[*num_customers].phone_number);

    customers[*num_customers].customer_id = *num_customers + 1;

    fprintf(customerFile, "%d,%s,%s\n", customers[*num_customers].customer_id,
            customers[*num_customers].customer_name, customers[*num_customers].phone_number);
    (*num_customers)++;

    fclose(customerFile);
}

void generateBill(InventoryItem inventory[], int num_items, Customer customers[], int num_customers) {
    int customerIDorPhone;
    int customerIndex = -1;

    printf("Enter Customer ID or Phone Number: ");
    scanf("%d", &customerIDorPhone);

    // Search for the customer in the array based on ID or phone number
    for (int i = 0; i < num_customers; i++) {
        if (customerIDorPhone == customers[i].customer_id || atoi(customers[i].phone_number) == customerIDorPhone) {
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == -1) {
        printf(BOLD RED"Customer not found!\n"RESET);
        return;
    }

    int purchase[MAX_ITEMS]; 
    int quantity[MAX_ITEMS]; 
    int num_purchased_items = 0;
    float total_cost = 0.0;
    int item_id = 0;
    int quan = 0;
    int adviced[MAX_ITEMS];
    //Y = 0.67 X + (3344924.75)

    while (item_id != -1 && num_purchased_items < MAX_ITEMS) {
        printf("Enter the Item ID and quantity (or -1 to finish): ");
        scanf("%d", &item_id);
        purchase[num_purchased_items] = item_id;
        if (item_id != -1) {
            adviced[num_purchased_items] = 0.95*item_id+(36.3);
            scanf("%d", &quan);
            quantity[num_purchased_items++] = quan;
        }
    }
  char cho;
  int curr_num_purchased_items = num_purchased_items;
for (int i = 0; i < curr_num_purchased_items; i++) {
//Debugging
//printf("Advice : %d\n",adviced[i]);
    for (int j = 0; j < num_items; j++) {
        if (inventory[j].item_id - adviced[i] < 5 && inventory[j].item_id - adviced[i] > -5) {
            printf("Do you want to buy "BOLD GREEN"%s?\n(Y or N) : "RESET, inventory[j].item_name);
            scanf(" %c", &cho);
            if (cho == 'Y' || cho == 'y') {
                purchase[num_purchased_items] = inventory[j].item_id;
                quantity[num_purchased_items++] = 1;
            }
            break;
        }
    }
}


  time_t t = time(NULL);
  struct tm *tm = localtime(&t);

  // Format and print the current date and time
  char dateTime[50];
  
    printf("\n***************************************************\n");
    printf("Customer: %s\nCustomer ID: %d\n", customers[customerIndex].customer_name,customers[customerIndex].customer_id);
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", tm);
  printf("Bill Generated on: %s\n\n", dateTime);
  printf("Sr\tItem_Name\tQuantity\tPrice\n");

    for (int i = 0; i < num_purchased_items; i++) {
        int current_item_id = purchase[i];
        int current_quantity = quantity[i];
        for (int j = 0; j < num_items; j++) {
            if (inventory[j].item_id == current_item_id) {
                printf("%d\t%s\t\t%d\t\t%.2f\n", i + 1, inventory[j].item_name,
                       current_quantity, inventory[j].price * current_quantity);
                total_cost += inventory[j].price * current_quantity;
                break;
            }
        }
    }

    printf("\nTotal\t\t\t\t\t\t%.2f\n", total_cost);
    printf("****************************************************\n");
    char genfile;
    printf(BOLD GREEN"Confirm to generate Bill File (Y/N): "RESET);
    scanf(" %c",&genfile);
    
    
    
        if (genfile=='Y' || genfile=='y'){
        // The following code generates the bill file
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char filename[100];
	    sprintf(filename, "%d_%04d-%02d-%02d_%02d:%02d:%02d.pdf", customers[customerIndex].customer_id,
	            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
	            tm->tm_hour, tm->tm_min, tm->tm_sec);
	
	    // Create a new PDF document
	    HPDF_Doc pdf = HPDF_New(NULL, NULL);
		if (!pdf) {
		    printf("Error creating PDF document\n");
   		 return;
		}
	
	    // Create a new page
	    HPDF_Page page = HPDF_AddPage(pdf);
	    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
	
	    // Set font and font size
	    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
	    HPDF_Page_SetFontAndSize(page, font, 12);
	
	    // Write content to the PDF
	    HPDF_Page_BeginText(page);
	    HPDF_Page_MoveTextPos(page, 50, HPDF_Page_GetHeight(page) - 50);
	
	    // Write customer information
	    HPDF_Page_ShowText(page, "Customer: ");
	    HPDF_Page_ShowText(page, customers[customerIndex].customer_name);
	    HPDF_Page_ShowText(page, "\nCustomer ID: ");
	    HPDF_Page_ShowText(page, customers[customerIndex].customer_id);

	
	    // Write billing date
         	HPDF_Page_MoveTextPos(page, 0, -20);  // Move down for the billing date
		HPDF_Page_ShowText(page, "\nBilling Date: ");
		HPDF_Page_ShowText(page, dateTime);
		
		// Write a header for the items section
		HPDF_Page_MoveTextPos(page, 0, -20);  // Move down for the items section header
		HPDF_Page_ShowText(page, "\n\nItems Purchased:");
	 
	    // Write purchased items and their details
	    HPDF_Page_MoveTextPos(page, 0, -20);  // Move down for the items section
	    HPDF_Page_ShowText(page, "\n\nSr\tItem_Name\tQuantity\tPrice\n");
	
	    for (int i = 0; i < num_purchased_items; i++) {
	        int current_item_id = purchase[i];
	        int current_quantity = quantity[i];
	        for (int j = 0; j < num_items; j++) {
	            if (inventory[j].item_id == current_item_id) {
	                // Write item details to PDF
	                char itemDetails[100];
	                sprintf(itemDetails, "%d\t%s\t\t%d\t\t%.2f\n", i + 1, inventory[j].item_name,
	                        current_quantity, inventory[j].price * current_quantity);
	                HPDF_Page_ShowText(page, itemDetails);
	                total_cost += inventory[j].price * current_quantity;
	                break;
	            }
	        }
	    }
	
	    // Write total cost
	    HPDF_Page_MoveTextPos(page, 0, -20);  // Move down for the total cost
	    char totalCostText[50];
	    sprintf(totalCostText, "\nTotal\t\t\t\t\t\t%.2f\n", total_cost);
	    HPDF_Page_ShowText(page, totalCostText);
	
	    HPDF_Page_EndText(page);
	
	    // Save the PDF file
	    HPDF_SaveToFile(pdf, filename);
	
	    // Clean up and free resources
	    HPDF_Free(pdf);
	
	    printf(BOLD "\nBill generated successfully in file:" GREEN " %s\n\n" RESET, filename);
	    if (HPDF_OK != HPDF_SaveToFile(pdf, filename)) {
    	    	printf("Error saving PDF to file\n");
		}
	}
	
}

int main() {
    char command_code;
    system("clear");

    
   FILE *inventoryFile = fopen("inventory.csv", "r");
   FILE *customerFile = fopen("customers.csv", "r");

   InventoryItem inventory[MAX_ITEMS];
   Customer customers[MAX_CUSTOMERS];
   int num_items = 0;
   int num_customers = 0;

   if (inventoryFile == NULL) {
       inventoryFile = fopen("inventory.csv", "w");
       if (inventoryFile == NULL) {
           printf(BOLD RED"Error creating inventory file!\n"RESET);
       }
   } 
   /*
       while (fscanf(inventoryFile, "%d,%[^,],%d,%f,%[^,],%[^,]\n", &inventory[num_items].item_id,
                  inventory[num_items].item_name, &inventory[num_items].stock, &inventory[num_items].price, inventory[num_items].category, inventory[num_items].subcategory) == 6) {
           num_items++;
       }
       fclose(inventoryFile);
   */

   if (customerFile == NULL) {
       customerFile = fopen("customers.csv", "w");
       if (customerFile == NULL) {
           printf(BOLD RED"Error creating customers file!\n"RESET);
       }
   } 
   
    /*   while (fscanf(customerFile, "%d,%[^,],%[^,]\n", &customers[num_customers].customer_id,
                  customers[num_customers].customer_name, customers[num_customers].phone_number) == 3) {
           num_customers++;
       }
    fclose(customerFile);
      */
    
    loadInventory(inventory, &num_items);
    loadCustomers(customers, &num_customers);
    
    
    

    int choice;
    do {
       printf(BOLD GREEN"\n=== Billing System ===\n"RESET);
        printf(CYAN"1. Update Inventory\n"RESET);
        printf(CYAN"2. Display Inventory\n"RESET);
        printf(CYAN"3. Register Customer\n"RESET);
        printf(CYAN"4. Generate Bill\n"RESET);
        printf(CYAN"5. Exit\n"RESET);
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateInventory(inventory, &num_items);
                break;
            case 2:
                displayInventory(inventory, num_items);
                break;
            case 3:
                registerCustomer(customers, &num_customers);
                break;
            case 4:
                generateBill(inventory, num_items,customers,num_customers);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf(BOLD RED"Invalid choice! Please enter a valid option.\n"RESET);
                break;
        }
    } while (choice != 5 && choice != 4);
    

    inventoryFile = fopen("inventory.csv", "w");
    if (inventoryFile != NULL) {
        for (int i = 0; i < num_items; i++) {
            fprintf(inventoryFile, "%d,%s,%d,%.2f,%s,%s\n", inventory[i].item_id, inventory[i].item_name,
                    inventory[i].stock, inventory[i].price, inventory[i].category, inventory[i].subcategory);
        }
        fclose(inventoryFile);
    }

    customerFile = fopen("customers.csv", "w");
    if (customerFile != NULL) {
        for (int i = 0; i < num_customers; i++) {
            fprintf(customerFile, "%d,%s,%s\n", customers[i].customer_id,
                    customers[i].customer_name, customers[i].phone_number);
        }
        fclose(customerFile);
    }
    return 0;
   }
