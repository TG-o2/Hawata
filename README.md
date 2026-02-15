Semestre 2 – ESPRIT Project:
Smart Port Fishing Desktop Application

This project focuses on developing a desktop application for a Smart Fishing Port.
The application is designed to assist port staff in managing port operations efficiently, including boats, fishing activities, and related services.

========Technologies Used========

-Programming Language: C++
-Framework: Qt (Qt Creator)
-Application Type: Desktop Application
-Database: Oracle SQL (via QOCI driver)

========Project Objectives========

-Design a modern and user-friendly desktop interface
-Manage fishing port operations digitally
-Apply object-oriented programming concepts in C++
-Use Qt tools (UI, signals & slots, widgets, layouts)

========Features Implemented========

**Product Management (CRUD Operations)**
- ✅ Create new products (fish inventory)
- ✅ Read/Display products in table view
- ✅ Update existing product information
- ✅ Delete products from inventory
- ✅ Oracle SQL database integration
- ✅ Input validation and error handling

**User Management**
- User account creation and management
- Role-based access (Admin, Manager, Employee)
- Password hashing with SHA-256

========Product CRUD Documentation========

For detailed information about the Product CRUD functionality:
- **PRODUCT_CRUD_SETUP.md** - Complete setup and usage guide
- **QUICK_REFERENCE.md** - Quick reference for developers
- **IMPLEMENTATION_SUMMARY.md** - Technical implementation details
- **database_schema.sql** - SQL script for database setup

========Getting Started========

**Prerequisites:**
- Qt 6.x (with Widgets, Charts, and Sql modules)
- Oracle Instant Client
- CMake 3.16+
- C++17 compatible compiler

**Build Instructions:**
```bash
mkdir build && cd build
cmake ..
make
```

**Database Setup:**
1. Install Oracle SQL Developer
2. Run `database_schema.sql` to create tables
3. Update database credentials in `appwindow.cpp`

See PRODUCT_CRUD_SETUP.md for detailed instructions.
