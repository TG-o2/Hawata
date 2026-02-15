-- ================================================
-- Hawata Product Management Database Schema
-- ================================================
-- This script creates the necessary tables and sequences
-- for the Product CRUD functionality in SQL Developer
-- ================================================

-- Drop existing objects (optional - use with caution)
-- DROP SEQUENCE product_seq;
-- DROP TABLE products;

-- Create products table
CREATE TABLE products (
    product_id NUMBER PRIMARY KEY,
    product_code VARCHAR2(100) NOT NULL,
    fish_type VARCHAR2(100) NOT NULL,
    catch_date TIMESTAMP,
    catch_time TIMESTAMP,
    quantity NUMBER NOT NULL,
    status NUMBER NOT NULL CHECK (status IN (0, 1, 2, 3, 4)),
    price NUMBER(10,2) NOT NULL CHECK (price >= 0),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT chk_quantity CHECK (quantity > 0)
);

-- Create sequence for auto-incrementing product_id
CREATE SEQUENCE product_seq 
START WITH 1 
INCREMENT BY 1 
NOCACHE 
NOCYCLE;

-- Create index on product_code for faster lookups
CREATE INDEX idx_product_code ON products(product_code);

-- Create index on fish_type for filtering
CREATE INDEX idx_fish_type ON products(fish_type);

-- Create index on status for filtering
CREATE INDEX idx_status ON products(status);

-- Insert sample data (optional)
INSERT INTO products (product_id, product_code, fish_type, catch_date, catch_time, quantity, status, price, created_at)
VALUES (product_seq.NEXTVAL, 'FISH-001', 'Salmon', CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, 50, 2, 25.99, CURRENT_TIMESTAMP);

INSERT INTO products (product_id, product_code, fish_type, catch_date, catch_time, quantity, status, price, created_at)
VALUES (product_seq.NEXTVAL, 'FISH-002', 'Tuna', CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, 30, 0, 35.50, CURRENT_TIMESTAMP);

INSERT INTO products (product_id, product_code, fish_type, catch_date, catch_time, quantity, status, price, created_at)
VALUES (product_seq.NEXTVAL, 'FISH-003', 'Cod', CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, 100, 2, 18.75, CURRENT_TIMESTAMP);

-- Commit the changes
COMMIT;

-- ================================================
-- Status Values Reference:
-- ================================================
-- 0 = In Stock
-- 1 = Reserved
-- 2 = Available
-- 3 = Unavailable
-- 4 = Sold
-- ================================================

-- View all products
SELECT * FROM products ORDER BY product_id;

-- View products by status
SELECT product_id, product_code, fish_type, quantity, 
       CASE status
           WHEN 0 THEN 'In Stock'
           WHEN 1 THEN 'Reserved'
           WHEN 2 THEN 'Available'
           WHEN 3 THEN 'Unavailable'
           WHEN 4 THEN 'Sold'
       END as status_text,
       price
FROM products
ORDER BY product_id;
