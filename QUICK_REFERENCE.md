# Product CRUD - Quick Reference

## Database Connection Setup

**Location:** `appwindow.cpp` -> `connectToDatabase()`

```cpp
m_database.setHostName("localhost");      // Change to your Oracle host
m_database.setDatabaseName("hwata");      // Change to your database/SID
m_database.setUserName("your_username"); // Your database username
m_database.setPassword("your_password"); // Your database password
```

## SQL Script to Run

Run `database_schema.sql` in SQL Developer to create:
- `products` table
- `product_seq` sequence
- Sample data (3 products)

## UI Field Mapping

| Field Purpose | Widget Name | Type | Location in UI |
|--------------|-------------|------|----------------|
| Product Code | `firstNameEdit_5` | QLineEdit | Add Product page |
| Fish Type | `firstNameEdit_3` | QLineEdit | Add Product page |
| Quantity | `firstNameEdit_4` | QLineEdit | Add Product page |
| Price | `firstNameEdit_6` | QLineEdit | Add Product page |
| Catch Date | `dateTimeEdit_5` | QDateTimeEdit | Add Product page |
| Catch Time | `dateTimeEdit_6` | QDateTimeEdit | Add Product page |
| Status | `role_option_4` | QComboBox | Add Product page |
| Products Table | `tableView_5` | QTableView | Display page |

## Button Handlers

| Button | Object Name | Function | Action |
|--------|------------|----------|---------|
| Add Product | `checkProductButton_2` | `on_checkProductButton_2_clicked()` | INSERT into DB |
| Check Products | `checkProductButton` | `on_checkProductButton_clicked()` | SELECT from DB |
| Update | `pushButton_24` | `on_pushButton_24_clicked()` | UPDATE in DB |
| Delete | `pushButton_25` | `on_pushButton_25_clicked()` | DELETE from DB |

## Product Status Enum

```cpp
0 = In Stock
1 = Reserved
2 = Available
3 = Unavailable
4 = Sold
```

## Build Requirements

```bash
# CMakeLists.txt includes:
find_package(Qt6 REQUIRED COMPONENTS Widgets Charts Sql)
target_link_libraries(Sign_up PRIVATE Qt6::Widgets Qt6::Charts Qt6::Sql)
```

## Common SQL Queries

```sql
-- View all products
SELECT * FROM products ORDER BY product_id;

-- Add a product (manually)
INSERT INTO products VALUES (product_seq.NEXTVAL, 'CODE', 'Fish Type', 
    CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, 10, 2, 19.99, CURRENT_TIMESTAMP);

-- Update a product
UPDATE products SET quantity = 20, price = 22.99 WHERE product_id = 1;

-- Delete a product
DELETE FROM products WHERE product_id = 1;

-- Reset sequence
ALTER SEQUENCE product_seq RESTART START WITH 1;
```

## Testing Checklist

- [ ] Database connection works
- [ ] Can add a new product
- [ ] Products display in table
- [ ] Can update a product
- [ ] Can delete a product
- [ ] Form validates required fields
- [ ] Form validates numeric fields
- [ ] Status dropdown works
- [ ] Date/time pickers work
- [ ] Table refreshes after operations

## Troubleshooting

**"Failed to connect to database"**
→ Check Oracle is running, verify credentials in `connectToDatabase()`

**"QOCI driver not loaded"**
→ Install Oracle Instant Client, ensure Qt has Oracle support

**Field values not saving**
→ Verify UI field names match in appwindow.cpp

**Sequence error**
→ Run `CREATE SEQUENCE product_seq START WITH 1 INCREMENT BY 1;`
