#include <stdio.h>
#include "BS.h"

void main(){
    int start = 0;

    while(start != 1){//    START
        printf("\nPress 1 to start the store: ");
        scanf(" %d", &start);
    }

    printf("\n\n\t\tWelcome to the BookStore created by Ekansh Mahajan\t\t");
    struct Book *Books = NULL;
    struct Order Orders;
    init(&Orders, 5);

    while(start != 0){//    MAIN MENU Functions

        printf("\n\n\n\nMAIN MENU:");
        printf("\nPress 1 to be the Shop Owner");
        printf("\nPress 2 to be a Customer");
        printf("\nPress 0 to Exit the Store\n");
        scanf("%d", &start);

        if(start == 1){//   OWNER SIDE Functions

            while(start != 99){
                printf("\n\n\n\nOwner's MENU:");
                printf("\nPress 1 to ADD NEW books");
                printf("\nPress 2 to RESTOCK the book");
                printf("\nPress 3 to REMOVE the book from the Store");
                printf("\nPress 4 to PRINT the books");
                printf("\nPress 5 to PRINT the PENDING Orders");
                printf("\nPress 6 to EXECUTE pending Orders");
                printf("\nPress 99 to Return back at MAIN MENU\n");
                scanf(" %d", &start);

                if(start == 1){ // ADD NEW BOOK
                    char name[MAX];
                    char author[MAX];
                    int ISBN;
                    int quantity;

                    int num;
                    printf("\nNumber of Books to be added: ");
                    scanf("%d", &num);
                    for(int i = 0; i<num; i++){
                        
                        printf("\n\nEnter the Name of the Book: ");
                        scanf(" %[^\n]", name); //  ' %[^\n]' is used to tell scanf to read characters until a newline (\n) character is encountered

                        printf("Enter the Author of the Book: ");
                        scanf(" %[^\n]", author);

                        printf("Enter the [Unique] ISBN of the Book: ");
                        scanf("%d", &ISBN);

                        while(available(Books, ISBN) == 1){ // checking if the book with entered ISBN already exists in the store 0->No 1->Yes
                            printf("\n!! Entered ISBN already exists !! ");
                            printf("\nEnter the [Unique] ISBN of the Book: ");
                            scanf("%d", &ISBN);
                        }

                        printf("Enter the quantity of the Book: ");
                        scanf("%d", &quantity);

                        Books = add(Books, name, author, ISBN, quantity);
                    }
                }
                else if(start == 2){ // RESTOCK
                    int ISBN;
                    int quantity;
                    print(Books);
                    int num;
                    printf("\n\nNumber of Books to be restocked: ");
                    scanf("%d", &num);
                    for(int i = 0; i<num; i++){
                        printf("\nEnter the ISBN of the book to be restocked: ");
                        scanf("%d", &ISBN);

                        while(available(Books, ISBN) == 0){// checking if the book with entered ISBN already exists in the store 0->No 1->Yes
                            printf("\n!! Enter the valid ISBN !! :");
                            scanf("%d", &ISBN);
                        }

                        printf("\nEnter the quantity: ");
                        scanf("%d", &quantity);

                        Books = restock(Books, ISBN, quantity);
                    }
                }

                else if(start == 3){// REMOVE Store Books
                    int i;
                    int num;

                    print(Books);

                    printf("\n\nNumber of Books to be removed: ");
                    scanf("%d", &num);
                    for(int i = 0; i<num; i++){
                        printf("\nEnter the ISBN to be Removed: ");
                        scanf("%d", &i);
                        Books = removeBook(Books, i);
                    }
                }
                else if(start == 4){ // PRINT Store Books
                    print(Books);
                }
                else if(start == 5){ // PRINT Customer Orders
                    printOrders(Orders);
                }
                else if(start == 6){ // EXECUTE Customer Orders
                    Books = execute(&Orders, Books);
                }
                else if(start == 99){// RETURN Back to Main Menu
                    break;
                }
                else{// Invalid Command
                    printf("\nEnter a Valid Command !!");
                }
            }
        }


        else if(start == 2){//  CUSTOMER SIDE Functions
            int i;
            printf("\nPress 1 to Create an ORDER");
            printf("\nPress 2 to Check Execution of Orders\n");
            printf("\nPress 99 to Return back at MAIN MENU\n\n");
            scanf("%d", &i);

            if(i == 1){// CREATE Order
                addOrder(&Orders, Books);
            }
            else if(i == 2){// Check STATUS of Orders
                status(Orders);
            }
            else if(i == 99){// RETURN Back to Main Menu
                break;
            }
            else{// Invalid Command
                printf("\nEnter a Valid Command !!");
            }
        }


        else if(start == 0){// EXIT Store
            printf("\n!!    Thanks for Visting    !!");
            break;
        }


        else{// Invalid Command
            printf("\nEnter a Valid Command !!");
        }
    }
}