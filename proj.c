#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "harupdf.h"

typedef struct {
  char name[100];
  int id;
  char phone_no[100];
  char previous_purchases[100];
  char address[100];
  char email[100];
} CustomerData;

typedef struct {
  int item_id;
  char name[100];
  int quantity;
  float price;
  char category[100];
} InventoryData;

void save_customer_data(CustomerData *customer_data, char *filename) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    exit(1);
  }

  // Write the header row.
  fprintf(fp, "Name,ID,Phone No.,Previous Purchases\n");

  // Write each data record.
  for (int i = 0; i < customer_data->num_customers; i++) {
    fprintf(fp, "%s,%d,%s,%s\n", customer_data[i].name, customer_data[i].id, customer_data[i].phone_no, customer_data[i].previous_purchases);
  }

  fclose(fp);
}

void save_inventory_data(InventoryData *inventory_data, char *filename) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    exit(1);
  }

  // Write the header row.
  fprintf(fp, "Item ID,Name,Quantity,Price\n");

  // Write each data record.
  for (int i = 0; i < inventory_data->num_inventory_items; i++) {
    fprintf(fp, "%d,%s,%d,%f\n", inventory_data[i].item_id, inventory_data[i].name, inventory_data[i].quantity, inventory_data[i].price);
  }

  fclose(fp);
}

void read_customer_data(CustomerData *customer_data, char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    exit(1);
  }

  // Read the header row.
  char line[1024];
  fgets(line, sizeof(line), fp);

  // Read each data record.
  int num_customers = 0;
  while (fgets(line, sizeof(line), fp) != NULL) {
    CustomerData customer;
    char *token = strtok(line, ",");
    while (token != NULL) {
      strcpy(customer.name, token);
      token = strtok(NULL, ",");
      customer.id = atoi(token);
      token = strtok(NULL, ",");
      strcpy(customer.phone_no, token);
      token = strtok(NULL, ",");
      strcpy(customer.previous_purchases, token);
      token = strtok(NULL, ",");
    }

    customer_data[num_customers] = customer;
    num_customers++;
  }

  fclose(fp);
}

void read_inventory_data(InventoryData *inventory_data, char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    exit(1);
  }

  // Read the header row.
  char line[1024];
  fgets(line, sizeof(line), fp);

  // Read each data record.
  int num_inventory_items = 0;
  while (fgets(line, sizeof(line), fp) != NULL) {
     InventoryData inventory_item;
    char *token = strtok(line, ",");
    while (token != NULL) {
      inventory_item.item_id = atoi(token);
      token = strtok(NULL, ",");
      strcpy(inventory_item.name, token);
      token = strtok(NULL, ",");
      inventory_item.quantity = atoi(token);
      token = strtok(NULL, ",");
      inventory_item.price = atof(token);
      token = strtok(NULL, ",");
    }

    inventory_data[num_inventory_items] = inventory_item;
    num_inventory_items++;
  }

  fclose(fp);
}

void record_customer_data(CustomerData *customer_data) {
  printf("Enter customer name: ");
  scanf("%s", customer_data->name);

  printf("Enter customer ID: ");
  scanf("%d", &customer_data->id);

  printf("Enter customer phone number: ");
  scanf("%s", customer_data->phone_no);

  printf("Enter customer previous purchases (comma-separated): ");
  scanf("%s", customer_data->previous_purchases);

  printf("Enter customer address: ");
  scanf("%s", customer_data->address);

  printf("Enter customer email: ");
  scanf("%s", customer_data->email);
}

void record_inventory_data(InventoryData *inventory_data) {
  printf("Enter item ID: ");
  scanf("%d", &inventory_data->item_id);

  printf("Enter item name: ");
  scanf("%s", inventory_data->name);

  printf("Enter item quantity: ");
  scanf("%d", &inventory_data->quantity);

  printf("Enter item price: ");
  scanf("%f", &inventory_data->price);

  printf("Enter item category: ");
  scanf("%s", inventory_data->category);
}

void generate_pdf_bill(CustomerData *customer_data, InventoryData *inventory_data, int num_items) {
  // Create a new PDF document
  HPDF_Doc doc = HPDF_New(NULL, NULL);

  // Add a page to the document
  HPDF_Page page = HPDF_AddPage(doc);

  // Set the font
  HPDF_SetFont(doc, "Helvetica", 12);

  // Print the customer information
  HPDF_TextOut(doc, page, 10, 10, "Customer Name: %s", customer_data->name);
  HPDF_TextOut(doc, page, 10, 20, "Customer ID: %d", customer_data->id);
  HPDF_TextOut(doc, page, 10, 30, "Phone No.: %s", customer_data->phone_no);
  HPDF_TextOut(doc, page, 10, 40, "Address: %s", customer_data->address);
  HPDF_TextOut(doc, page, 10, 50, "Email: %s", customer_data->email);

  // Print the item table header
  HPDF_TextOut(doc, page, 10, 70, "Item Name | Quantity | Price | Category");
  HPDF_TextOut(doc, page, 10, 80, "------- | -------- | -------- | --------");

  // Print the item table rows
  for (int i = 0; i < num_items; i++) {
    HPDF_TextOut(doc, page, 10, 90 + i * 10, "%s | %d | %f | %s", inventory_data[i].name, inventory_data[i].quantity, inventory_data[i].price, inventory_data[i].category);
  }

  // Calculate the total bill amount
  float total_bill_amount = 0;
  for (int i = 0; i < num_items; i++) {
    total_bill_amount += inventory_data[i].price * inventory_data[i].quantity;
  }

  // Print the total bill amount
  HPDF_TextOut(doc, page, 10, 100 + num_items * 10, "Total: %f", total_bill_amount);

  // Save the PDF document
  HPDF_SaveToFile(doc, "bill.pdf");

  // Free the PDF document
  HPDF_Free(doc);
}

/*
int main() {
  // Create a new customer data object
  CustomerData customer_data;

  // Record the customer data
  record_customer_data(&customer_data);

  // Create a new inventory data array
  InventoryData inventory_data[100];

  // Record the inventory data
  int num_items = 0;
  while (num_items < 100) {
    record_inventory_data(&inventory_data[num_items]);
    num_items++;

    // Ask the user if they want to continue adding items to the inventory
    char ch;
    printf("Do you want to add more items? (Y/N): ");
    scanf("%c", &ch);

    if (ch != 'Y' && ch != 'y') {
      break;
    }
  }

  // Generate the PDF bill
  generate_pdf_bill(&customer_data, inventory_data, num_items);

  return 0;
}
*/
