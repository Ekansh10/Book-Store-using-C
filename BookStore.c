#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a book
struct Book {
    char title[100];
    char author[100];
    char ISBN[13];
    int quantity;
};

// Structure to represent a customer order
struct Order {
    char bookTitle[100];
    int quantity;
    struct Order* next;
};

// Function to add a new book to the inventory
void addBook(struct Book** inventory, char title[], char author[], char ISBN[], int quantity) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    strcpy(newBook->ISBN, ISBN);
    newBook->quantity = quantity;
    newBook->next = *inventory; // Link the new book to the existing inventory
    *inventory = newBook; // Update the inventory pointer to the new book
    printf("Book added successfully.\n");
}

// Function to place a customer order
void placeOrder(struct Order** orders, char bookTitle[], int quantity) {
    struct Order* newOrder = (struct Order*)malloc(sizeof(struct Order));
    strcpy(newOrder->bookTitle, bookTitle);
    newOrder->quantity = quantity;
    newOrder->next = *orders;
    *orders = newOrder;
    printf("Order placed successfully.\n");
}

// Function to update inventory based on customer orders
void updateInventory(struct Book* inventory, struct Order* orders) {
    struct Order* currentOrder = orders;
    while (currentOrder != NULL) {
        struct Book* currentBook = inventory;
        while (currentBook != NULL) {
            if (strcmp(currentOrder->bookTitle, currentBook->title) == 0) {
                if (currentBook->quantity >= currentOrder->quantity) {
                    currentBook->quantity -= currentOrder->quantity;
                } else {
                    printf("Error: Insufficient stock for book '%s'.\n", currentOrder->bookTitle);
                }
                break;
            }
            currentBook = currentBook + 1;
        }
        currentOrder = currentOrder->next;
    }
}

// Function to display the current inventory
void displayInventory(struct Book* inventory) {
    printf("Current Inventory:\n");
    struct Book* currentBook = inventory;
    while (currentBook != NULL) {
        printf("Title: %s, Author: %s, ISBN: %s, Quantity: %d\n", currentBook->title, currentBook->author, currentBook->ISBN, currentBook->quantity);
        currentBook = currentBook + 1;
    }
}

int main() {
    struct Book* inventory = NULL;
    struct Order* orders = NULL;
    
    // Adding books to inventory
    addBook(&inventory, "Book1", "Author1", "ISBN1", 10);
    addBook(&inventory, "Book2", "Author2", "ISBN2", 15);
    
    // Placing customer orders
    placeOrder(&orders, "Book1", 5);
    placeOrder(&orders, "Book2", 8);
    
    // Updating inventory based on orders
    updateInventory(inventory, orders);
    
    // Displaying current inventory
    displayInventory(inventory);
    
    // Freeing allocated memory
    free(inventory);
    struct Order* currentOrder = orders;
    while (currentOrder != NULL) {
        struct Order* temp = currentOrder;
        currentOrder = currentOrder->next;
        free(temp);
    }
    
    return 0;
}
