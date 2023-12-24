Project: Billing System

-----------------------------------------------------------------------------------------------------------------------------------------------------------------


Description:
The Billing System project aims to create a C program that manages inventory, customer records, and generates bills for purchases made by customers.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------


Project Outline:

Part 1: Inventory Management
 - Maintain a central CSV file detailing the inventory with fields such as item ID, item name, stock, and price.
 - Implement functionalities to update, add, or delete inventory using specific commands.

Part 2: Customer Management
a) Login:
- Input phone number or Customer ID to retrieve additional customer data (e.g., Customer name, phone no, address) from the customer record CSV file.

b) Registration:
- Input Customer name, phone no, address, and generate a unique customer ID.
- Save all customer information in a CSV file (append for registration purposes).

Part 3: Purchase and Billing
- Allow customers to add unique item IDs of the items they want to purchase.
- The program automatically calculates the bill by retrieving prices from the inventory CSV file.

Part 4: Billing Generation
- Generate a bill with the following format:
***************************************************
Customer: <customer_name>
ID: <cust_ID>
Date:
Time:

Sr   Item_Name    Quantity   Price
1    <item1>      <quantity1>   <quantity*item_price>
2    <item2>      <quantity2>   <quantity*item_price>
...
Total                              <total price>
****************************************************


-----------------------------------------------------------------------------------------------------------------------------------------------------------------

Code:
- Provided C code that includes functionalities for managing inventory, customer registration, generating bills, and overall system management.
Certainly! Here's a guide on how to use the provided C code for the Billing System:

### Steps to Use the Billing System Code:

#### 1. Compilation:
- Open a C compiler or an Integrated Development Environment (IDE) that supports C programming.
- Create a new project or source file.
- Copy the provided C code into the source file.

#### 2. File Setup:
- Create two CSV files: `inventory.csv` and `customers.csv`.
- Ensure these files have the appropriate headers and data in the correct format (e.g., item ID, item name, stock, price in `inventory.csv`; customer ID, name, phone number in `customers.csv`).

#### 3. Compilation and Execution:
- Compile the code using the C compiler or IDE.
- Run the compiled executable file.

#### 4. Menu Navigation:
- Upon execution, the program will display a menu interface with options:
    - Update Inventory
    - Display Inventory
    - Register Customer
    - Generate Bill
    - Exit

#### 5. Functionality Overview:

- **Update Inventory**:
    - Select option 1 to update the inventory.
    - Input item details such as ID, name, stock, price, category, and subcategory as prompted.

- **Display Inventory**:
    - Choose option 2 to view the current inventory with details like item ID, name, stock, price, category, and subcategory.

- **Register Customer**:
    - Option 3 allows registration of new customers.
    - Enter customer details like name and phone number.

- **Generate Bill**:
    - Option 4 initiates the bill generation process.
    - Provide the customer ID or phone number.
    - Enter the item IDs and quantities the customer wants to purchase.
    - The program will calculate the bill based on item prices and quantities.
    - Confirmation will be asked to generate a bill file.

- **Exit**:
    - Option 5 allows you to exit the program.

#### 6. Handling Files:
- Ensure to save inventory and customer data appropriately upon exiting the program.
- The program will update the `inventory.csv` and `customers.csv` files with new data or modifications.

#### 7. Debugging and Testing:
- Debug and test the program for various scenarios, including:
    - Invalid inputs or edge cases.
    - Proper file I/O handling.
    - Correct bill generation and file creation.

#### 8. Further Customizations:
- Modify the code as needed for additional functionalities or specific project requirements.
- Enhance the user interface or add more features based on your project specifications.

#### 9. Documentation and Error Handling:
- Document the code for future reference and maintain proper error handling for various scenarios.

#### 10. Project Maintenance:
- Keep track of any updates, enhancements, or modifications made to the code for future maintenance.



-----------------------------------------------------------------------------------------------------------------------------------------------------------------

Notes:
- Ensure proper handling of file I/O, error messages, and input validations.
- Test the code thoroughly for various scenarios including edge cases.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------


Potential Enhancements:
- Implement a user-friendly interface.
- Add functionalities for order history and reporting.
- We tried to output a pdf instead of a .txt file but the code didn't work. 
We tried to utilit libhpdf (Haru PDF) to perform this task but the porgram gave out Segmentation Error: Core Dumped while writing the pdf.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Credits:
Coder - Daksh Verma
Visual - Bhavay Vashisth
