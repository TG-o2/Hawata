# Product CRUD Setup Guide

This document explains how to configure and use the Product CRUD (Create, Read, Update, Delete) functionality in the Hawata Smart Port Fishing Desktop Application.

## Overview

The Product CRUD functionality allows you to manage fishing products in the system with the following features:
- Add new products with details (code, fish type, catch date/time, quantity, status, price)
- Display all products in a table view
- Update existing product information
- Delete products from the system
- All data is stored in an Oracle SQL database

## Database Setup

### 1. Database Configuration

The application connects to an Oracle database. You need to configure the connection parameters in `appwindow.cpp`:

```cpp
bool appwindow::connectToDatabase()
{
    m_database = QSqlDatabase::addDatabase("QOCI");  // Oracle database driver
    
    // Update these parameters based on your SQL Developer configuration
    m_database.setHostName("localhost");  // Your Oracle host
    m_database.setDatabaseName("hwata");  // Your service name/SID
    m_database.setUserName("system");     // Your database username
    m_database.setPassword("password");   // Your database password
    
    // ...
}
```

### 2. Database Schema

The application will automatically create the following table if it doesn't exist:

```sql
CREATE TABLE products (
    product_id NUMBER PRIMARY KEY,
    product_code VARCHAR2(100) NOT NULL,
    fish_type VARCHAR2(100) NOT NULL,
    catch_date TIMESTAMP,
    catch_time TIMESTAMP,
    quantity NUMBER NOT NULL,
    status NUMBER NOT NULL,
    price NUMBER(10,2) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE SEQUENCE product_seq START WITH 1 INCREMENT BY 1;
```

### 3. Product Status Values

The `status` field uses the following numeric values:
- 0 = In Stock
- 1 = Reserved
- 2 = Available
- 3 = Unavailable
- 4 = Sold

## UI Components

### Product Tab (🐟 Product Restock)

The Product Restock tab has 3 pages:

#### Page 1: Add New Product
- **Product Code** (`firstNameEdit_5`): Unique identifier for the product
- **Type of Fish** (`firstNameEdit_3`): Species/type of fish
- **Date of Catch** (`dateTimeEdit_5`): When the fish was caught
- **Fish Caught Time** (`dateTimeEdit_6`): Specific time of catch
- **Quantity** (`firstNameEdit_4`): Amount in stock
- **Status** (`role_option_4`): Dropdown with options (In Stock, Reserved, Available, Unavailable, Sold)
- **Price** (`firstNameEdit_6`): Product price
- **Buttons**:
  - "Add Product" (`checkProductButton_2`): Saves the product to database

#### Page 2: Display/Manage Products
- **Table View** (`tableView_5`): Displays all products with columns:
  - ID, Code, Fish Type, Catch Date, Quantity, Status, Price, Created At
- **Buttons**:
  - "Check Products" (`checkProductButton`): Loads and displays all products
  - "Update" (`pushButton_24`): Updates the selected product
  - "Export PDF" (`pushButton_23`): (Future feature)

#### Page 3: Delete Products
- **Delete Button** (`pushButton_25`): Deletes the selected product after confirmation

## Usage Instructions

### Adding a Product

1. Navigate to the Product Restock tab
2. Go to the "Add New Product" page
3. Fill in all required fields:
   - Product Code
   - Type of Fish
   - Catch Date and Time
   - Quantity (must be a positive number)
   - Status (select from dropdown)
   - Price (must be a valid number)
4. Click "Add Product" button
5. A success message will appear if the product was added successfully

### Viewing Products

1. Navigate to the Product Restock tab
2. Click the "Check Products" button
3. The table will display all products from the database
4. You can browse through the list to see all product details

### Updating a Product

1. Navigate to the display page (click "Check Products")
2. Select a product row in the table
3. Edit the values directly in the table cells (Code, Fish Type, Quantity, Price)
4. Click the "Update" button
5. A confirmation message will appear if the update was successful

### Deleting a Product

1. Navigate to the display page (click "Check Products")
2. Select a product row in the table
3. Click the "Delete" button
4. Confirm the deletion in the dialog box
5. The product will be removed from the database

## Error Handling

The system provides error messages for:
- Database connection failures
- Missing required fields
- Invalid data types (non-numeric quantity or price)
- Database operation errors (INSERT, UPDATE, DELETE failures)

## Prerequisites

### Build Requirements
- Qt 6.x with the following modules:
  - Qt6::Widgets
  - Qt6::Charts
  - Qt6::Sql
- Oracle Client libraries (for QOCI driver)
- C++17 compiler
- CMake 3.16+

### Runtime Requirements
- Access to an Oracle database
- Valid database credentials
- Oracle Client installed (for QOCI driver to work)

## Troubleshooting

### Database Connection Issues

If you see "Failed to connect to database" error:
1. Verify Oracle database is running
2. Check connection parameters in `connectToDatabase()`
3. Ensure Oracle Client is installed
4. Verify QOCI driver is available: Check Qt installation includes SQL drivers

### Missing QOCI Driver

If QOCI driver is not available:
- Install Oracle Instant Client
- Ensure Qt was built with Oracle support
- On Linux: Set `LD_LIBRARY_PATH` to include Oracle libraries
- On Windows: Ensure Oracle libraries are in PATH

### Field Mapping Issues

If fields don't seem to work correctly, verify the UI field mappings in `appwindow.ui`:
- Product Code: `firstNameEdit_5`
- Fish Type: `firstNameEdit_3`
- Quantity: `firstNameEdit_4`
- Price: `firstNameEdit_6`
- Catch Date: `dateTimeEdit_5`
- Catch Time: `dateTimeEdit_6`
- Status: `role_option_4`

## Future Enhancements

Potential features to add:
- [ ] Search functionality by product code or fish type
- [ ] Filter by status
- [ ] Sort by different columns
- [ ] Export to PDF functionality
- [ ] Import products from CSV
- [ ] Product images/photos
- [ ] Stock alert notifications
- [ ] Sales tracking

## Code Structure

### Files Modified/Added
- `product.h` - Product class definition
- `product.cpp` - Product class implementation
- `appwindow.h` - Added product methods and database connection
- `appwindow.cpp` - Implemented CRUD operations
- `CMakeLists.txt` - Added product files and Qt SQL module

### Key Classes
- `Product` - Data model for products
- `appwindow` - Main application window with CRUD handlers

### Database Methods
- `connectToDatabase()` - Establishes database connection
- `createProductTable()` - Creates table and sequence if needed
- `loadProductsFromDB()` - Loads products from database
- `displayProducts()` - Populates table view with products

### CRUD Handlers
- `on_checkProductButton_2_clicked()` - Create (Add Product)
- `on_checkProductButton_clicked()` - Read (Display Products)
- `on_pushButton_24_clicked()` - Update Product
- `on_pushButton_25_clicked()` - Delete Product

## Support

For issues or questions, please refer to the main README.md or contact the development team.
