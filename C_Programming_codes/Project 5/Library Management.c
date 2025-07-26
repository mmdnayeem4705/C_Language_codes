#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to store book details
struct Book {
    int id;
    char title[50];
    char author[50];
};

// Function prototypes
void addBook();
void displayBooks();
void searchBook();
void deleteBook();

FILE *fp;

int main() {
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Delete Book by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add a book to the file
void addBook() {
    struct Book book;

    // Open the file in append mode
    fp = fopen("library.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &book.id);
    printf("Enter book title: ");
    getchar();  // Clear newline character from input buffer
    fgets(book.title, sizeof(book.title), stdin);
    book.title[strcspn(book.title, "\n")] = 0;  // Remove trailing newline character
    printf("Enter author name: ");
    fgets(book.author, sizeof(book.author), stdin);
    book.author[strcspn(book.author, "\n")] = 0;  // Remove trailing newline character

    // Write the book to the file
    fwrite(&book, sizeof(book), 1, fp);

    fclose(fp);

    printf("Book added successfully!\n");
}

// Function to display all books
void displayBooks() {
    struct Book book;

    // Open the file in read mode
    fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    printf("\nAll Books:\n");
    printf("ID\tTitle\t\tAuthor\n");
    printf("------------------------------------------\n");

    while (fread(&book, sizeof(book), 1, fp)) {
        printf("%d\t%s\t\t%s\n", book.id, book.title, book.author);
    }

    fclose(fp);
}

// Function to search for a book by ID
void searchBook() {
    struct Book book;
    int searchId, found = 0;

    // Open the file in read mode
    fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    printf("Enter the book ID to search: ");
    scanf("%d", &searchId);

    while (fread(&book, sizeof(book), 1, fp)) {
        if (book.id == searchId) {
            printf("\nBook Found!\n");
            printf("ID: %d\n", book.id);
            printf("Title: %s\n", book.title);
            printf("Author: %s\n", book.author);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }

    fclose(fp);
}

// Function to delete a book by ID
void deleteBook() {
    struct Book book;
    int deleteId, found = 0;

    // Open the file in read mode
    fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    FILE *tempFile;
    tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Error opening temporary file!\n");
        fclose(fp);
        return;
    }

    printf("Enter the book ID to delete: ");
    scanf("%d", &deleteId);

    while (fread(&book, sizeof(book), 1, fp)) {
        if (book.id == deleteId) {
            found = 1;
            printf("Book with ID %d deleted successfully!\n", deleteId);
        } else {
            fwrite(&book, sizeof(book), 1, tempFile);
        }
    }

    if (!found) {
        printf("Book not found!\n");
    }

    fclose(fp);
    fclose(tempFile);

    // Delete the old file and rename the temp file to original file name
    remove("library.dat");
    rename("temp.dat", "library.dat");
}
