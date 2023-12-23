#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

// Structure of the Store's Book
struct Book{
    char name[MAX];
    char author[MAX];
    int ISBN;
    int quantity;
    struct Book* next;
};

// Structure of the Customer's Order Book
struct B{
    int ISBN;
    int quantity;
    struct B* next;
};

// Structure of the Customer
struct Customer{
    int id;
    char name[MAX];
    int phone;
    struct B* books;
};

// Structure of the Order Array
struct Order{
    int capacity;
    struct Customer* A[10];// Consists Customer Pointer
    int lastIndex;
};




// Function to create a New Book of the Store
struct Book* createBook(){
    struct Book* temp = (struct Book*)malloc(sizeof(struct Book));
    temp->next = NULL;
    return temp;
}


// Function to Check if the Specific Book is AVAILABLE in the Store or not
int available(struct Book* root, int ISBN){
    struct Book* temp = root;
    while(temp != NULL){// going to the node where the book is present
        if(temp->ISBN == ISBN){
            return 1;
        }
        temp = temp->next;
    }
    return 0; 
}


// Function to RESTOCK the Existing Book in the Store
struct Book* restock(struct Book* root, int ISBN, int quantity){
    struct Book* temp = root;
    while(temp != NULL){// going to the node where the book is present
        if(temp->ISBN == ISBN){// if book found with valid ISBN
            temp->quantity += quantity;
            return root;
        }
        temp = temp->next;
    }
    return root;
}


// Function to ADD New Book in the Store
struct Book* add(struct Book* root, char name[], char author[], int ISBN, int quantity){

    if(root == NULL){// if root is empty; initializing the root; adding first book in the list
        struct Book* B = createBook();
        if(B != NULL){
            strcpy(B->name, name);
            strcpy(B->author, author);
            B->ISBN = ISBN;
            B->quantity = quantity;
            B->next = NULL;
            printf("\n!! '%s' added Succesfully in the Store!!", name);
            return B;
        }
        else{// allocation failed
            printf("\n!! Failed to add Book at the moment !!");
            return NULL;
        }
    }

    else{
        struct Book* temp = root;

        if(available(root, ISBN) == 0){// if book is not available in store, but other books are present
            // initializing my new book
            struct Book* B = createBook();
            if(B != NULL){
                strcpy(B->name, name);
                strcpy(B->author, author);
                B->ISBN = ISBN;
                B->quantity = quantity;

                while(temp->next != NULL){// going to the end node of the list
                    temp = temp->next;
                }
                temp->next = B;// adding new book to the end of the list
                B->next = NULL;
                printf("\n!! '%s' added Succesfully in the Store!!", name);
            }
            else{// allocation failed
                printf("\n!! Failed to add Book at the moment !!");
            }
        }
        return root;
    }
}

// Function to REMOVE Existing Book from the Store
struct Book* removeBook(struct Book* root, int ISBN) {
    if(root == NULL){ // Empty list
        printf("No Books available in the Store to be Removed");
    } 

    else if(root->next == NULL && root->ISBN == ISBN){ // List with single book
        free(root);
        root = NULL;
    } 
    
    else{ // List with multiple books
        struct Book* temp = root;

        if(temp->ISBN == ISBN){ // Removing first book of the list
            root = temp->next;
            free(temp);
        } 
        else{
            struct Book* prev = NULL;

            while(temp != NULL && temp->ISBN != ISBN){ // Runs until book with ISBN is found
                prev = temp;
                temp = temp->next;
            }

            if(temp == NULL){ // if Book with ISBN not found return root;
                printf("\n !! No book with ISBN %d exists in the store !!", ISBN);
                return root;
            }

            prev->next = temp->next;
            free(temp);
        }
    }
    return root;
}



// Function to print all the books available in the store
void print(struct Book* root){
    if(root== NULL){
        printf("No Books available in the Store at the moment");
    }
    else{
        printf("\nFollowing are the Books available in the store: \n");
        printf("\nFormat:   BOOK-NAME    AUTHOR    ISBN    COPIES-LEFT\n");
        struct Book* temp = root;
        while(temp != NULL){
            printf("\n%s----%s---%d---%d ", temp->name, temp->author, temp->ISBN, temp->quantity);
            temp = temp->next;
        }
    }
}

// Function to ADD New Book to the Customer's Order BookList
struct B* addBook(struct B* books, int ISBN, int quantity){
    
    if(books == NULL){
        struct B* newBook = (struct B*)malloc(sizeof(struct B));
        newBook->ISBN = ISBN;
        newBook->quantity = quantity;
        newBook->next = NULL;
        return newBook;
    }
    else{
        struct B* temp = books;
        struct B* newBook = (struct B*)malloc(sizeof(struct B));
        newBook->ISBN = ISBN;
        newBook->quantity = quantity;
        newBook->next = NULL;

        while(temp->next != NULL){
            temp = temp->next;
        }
        
        temp->next = newBook;
    }
    return books;
}

// Function to return LENGTH of Array 
int length(struct Order o){
    return o.lastIndex+1;
}

// Function to Check if Customer ID entered is ELIGIBLE / VALID
int eligible(struct Order o, int id){
    int len = length(o);
    if(o.lastIndex == -1){
        return 1;
    }
    for(int i = 0; i<len; i++){
        if(o.A[i]->id == id){
            return 0;
        }
    }
    return 1;
}

// Function to CREATE a New Customer
struct Customer* createCustomer(struct Order o){
    struct Customer* temp = (struct Customer*)malloc(sizeof(struct Customer));
    char name[MAX];
    int phone;
    int ID;

    printf("\n\nEnter your [Unique] ID: ");
    scanf("%d", &ID);

    while(eligible(o, ID) == 0){// Taking unique ID if not entered Unique one
        printf("!! ID already taken !!");
        printf("\n\nEnter your [Unique] ID: ");
        scanf("%d", &ID);
    }
    printf("Enter your name: ");
    scanf(" %[^\n]", name);

    printf("Enter your Phone No.: ");
    scanf("%d", &phone);

    temp->id = ID;
    strcpy(temp->name, name);
    temp->phone = phone;

    return temp;
}

// Function to INITIALIZE the Order Array
void init(struct Order *o, int size){
    o->lastIndex = -1;
    o->capacity = size;
}


// Function to Check whether the Order Array IS FULL 
int isFull(struct Order o){
    if(o.lastIndex == o.capacity-1){
        return 1;
    }
    return 0;
}

// Function to Check whether the Order Array IS EMPTY
int isEmpty(struct Order o){
    if(o.lastIndex == -1){
        return 1;
    }
    return 0;
}

// Function to DELETE the Order Array Element
int delete(struct Order *o, int index){
    if(index>=0 && index<=o->lastIndex){
        for(int i = index; i<=o->lastIndex; i++){
            o->A[i] = o->A[i+1];
        }
        o->lastIndex--;
    }
    else{
        printf("Index out of bound");
    }
}

// Function to ADD Customer Pointer to the 'Orders' Array
void addCustomer(struct Order* o, struct Customer* c){
    if(isFull(*o) == 1){
        printf("Array is full\n");
    }
    else{
        o->lastIndex++;
        o->A[o->lastIndex] = c;
    }
}

// Function to Calculate the length of the Books Linked list
int BLength(struct Book* root){
    int count;
    struct Book* temp = root;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

// Function to ADD Orders of the Customer to the 'Orders' Array
void addOrder(struct Order *orders, struct Book* root){
    print(root);

    struct Customer* customer = createCustomer(*orders);
    int count;
    int ISBN;
    int quantity;

    addCustomer(orders, customer);// Adding Customer Pointer to Orders Array

    struct B* books = NULL;
    
    printf("\nNo. of books to be ordered: ");
    scanf("%d", &count);
    while(count>BLength(root)){
        printf("\nEnter valid no. of books: ");
        scanf("%d", &count);
    }

    for(int i = 0; i<count; i++){// Ordered BookList of the Customer
        printf("Enter the ISBN of the book to be ordered: ");
        scanf("%d", &ISBN);
        while(available(root, ISBN) == 0){
            print(root);
            printf("\nEnter a valid ISBN from above list: ");
            scanf("%d", &ISBN);
        }
        printf("Enter the No. of Copies to be ordered: ");
        scanf("%d", &quantity);

        books = addBook(books, ISBN, quantity);// Updating BookList of the Customer
    }
    customer->books = books;// Adding BookList Pointer to Customer's Node
    printf("\n!! Order Created Successfully !!");
}

// Function to print the Pending Orders of the Customer
void printOrders(struct Order o){
    if(o.lastIndex == -1){
        printf("\n!! No orders Pending !!");
    }
    else{
        for(int i = 0; i<length(o); i++){
            struct Customer* customer = o.A[i];
            struct B* temp = customer->books;
            printf("\n\nID of the Customer: %d", customer->id);
            printf("\nNAME of the Customer: %s", customer->name);
            printf("\nPHONE of the Customer: %d", customer->phone);
            while(temp != NULL){
                printf("\n\nBook ISBN: %d", temp->ISBN);
                printf("\nNo. of Copies: %d", temp->quantity);
                temp = temp->next;
            }
            printf("\n--------------------------------------------------------");
        }
    }
}

// Function to Check Execution STATUS of Customer Orders
void status(struct Order o){
    if(o.lastIndex == -1){
        printf("!! Orders are Executed !!");
    }
    else{
        printf("!! Orders are Pending !!");
    }
}


// Function to EXECUTE pending orders of the customer
struct Book* execute(struct Order* o, struct Book* root){
    if(o->lastIndex == -1){
        printf("!! No Orders Pending to be Executed !!");
        return root;
    }
    struct Book* temp = root;
    struct Customer* cust = NULL;
    struct B* prev = NULL;
    while(o->lastIndex != -1){// Runs untill every customer's orders gets exeuted
        cust = o->A[0];
        struct B* book = cust->books;
        while(book != NULL){// Travesing Customers book orders untill book pointer of the customer is NULL
            while(temp->ISBN != book->ISBN){// Traversing to the node of the Books where the book with ISBN is located
                temp = temp->next;
            }
            if(temp->quantity >= book->quantity){// If we have sufficient quantities to be executed we will delete it from the store
                temp->quantity -= book->quantity;
            }
            prev = book;
            book = book->next;
            free(prev);// Freeing memory of the books demanded by the customer
        }
        free(o->A[0]);// Freeing memory occupied by the Customer
        delete(o, 0);// Deleting the customer pointer from the Orders Array
    }
    printf("!! Orders Executed Successfully !!");
    return root;
}



