#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS 100

typedef enum {
  ENTRY,
  UPDATE,
  EXIT
} OperationType;

typedef struct {
  int day;
  int month;
  int year;
  char name[50];
  int quantity;
  OperationType type;
} ProductHistory;

typedef struct {
  char name[50]; // Product Name
  int quantity; //quantity in stock
  int price; // product price 
  char expiration[11]; // expiry date in "YYYY-MM-DD" format
} Product;

Product products[MAX_PRODUCTS];
int num_products = 0;
ProductHistory history[MAX_PRODUCTS];
int num_history_entries = 0;
////// add_product allows the user to add a product
void add_product() {
  char name ;
  int quantity;
  int price;
  char expiration;
  // Ask the user to enter product information
  printf("Enter the product name : ");
  scanf("%s", name);
  printf("Enter the quantity of products : ");
  scanf("%d", &quantity);
  printf("Enter the product price: ");
  scanf("%f", &price);
  printf("Enter the expiration date in YYYY-MM-DD format : ");
  scanf("%s", expiration);
  // Check if the product already exists in stock
  int product_index = -1;
  for (int i = 0; i < num_products; i++) {
    if (strcmp(products[i].name, name) == 0) {
      product_index = i;
      break;
    }
  }

  // If the product already exists, add the quantity to the existing stock
   // Otherwise, add the product to the stock
  if (product_index != -1) {
    products[product_index].quantity += quantity;
  } else {
    products[num_products].name = name;
    products[num_products].quantity = quantity;
    products[num_products].price = price;
    strcpy(products[num_products].expiration, expiration);
    num_products++;
  }

  // Add the entry to the history
  time_t current_time = time(NULL);
  struct tm *tm_struct = localtime(&current_time);
  history[num_history_entries].day = tm_struct->tm_mday;
  history[num_history_entries].month = tm_struct->tm_mon + 1;
  history[num_history_entries].year = tm_struct->tm_year + 1900;
  strcpy(history[num_history_entries].name, name);
  history[num_history_entries].quantity = quantity;
  history[num_history_entries].type = ENTRY;
  num_history_entries++;
}

////// remove_product allows the user to delete a product
void remove_product() {
  char name;
  printf("Enter product name : ");
  scanf("%s", name);
  // Find the product in stock
  int product_index = -1;
  for (int i = 0; i < num_products; i++) {
    if (strcmp(products[i].name, name) == 0) {
      product_index = i;
      break;
    }
  }

  // If the product exists in stock, delete it
  if (product_index >= 0) {
    // Move all subsequent products one index to the left to fill the space left by the deleted product
    for (int i = product_index; i < num_products - 1; i++) {
      products[i] = products[i + 1];
    }
    (*num_products)--;  // Decrement the number of products in stock
  // Add the entry to the history
  time_t current_time = time(NULL);
  struct tm *tm_struct = localtime(&current_time);
  history[num_history_entries].day = tm_struct->tm_mday;
  history[num_history_entries].month = tm_struct->tm_mon + 1;
  history[num_history_entries].year = tm_struct->tm_year + 1900;
  strcpy(history[num_history_entries].name, name);
  history[num_history_entries].quantity = products[product_index].quantity;
  history[num_history_entries].type = EXIT;
  num_history_entries++;
} else {
  printf("The product does not exist in stock.\n");
}
}

///// modify_product allows the user to update the quantity of a product
  void modify_product() {
    char name;
    int new_quantity
  // Ask the user to enter product information
  printf("Enter product name : ");
  scanf("%s", name);
  printf("Enter the new quantity of product : ");
  scanf("%d", &new_quantity);
  // Find the product in stock
  int product_index = -1;
  for (int i = 0; i < num_products; i++) {
    if (strcmp(products[i].name, name) == 0) {
      product_index = i;
      break;
    }
  }

  // Modify the quantity of the product if it exists
  if (product_index != -1) {
    products[product_index].quantity = new_quantity;

    // Add the entry to the history
    time_t current_time = time(NULL);
    struct tm *tm_struct = localtime(&current_time);
    history[num_history_entries].day = tm_struct->tm_mday;
    history[num_history_entries].month = tm_struct->tm_mon + 1;
    history[num_history_entries].year = tm_struct->tm_year + 1900;
    strcpy(history[num_history_entries].name, name);
        history[num_history_entries].quantity = new_quantity - products[product_index].quantity;
    history[num_history_entries].type = UPDATE;
    num_history_entries++;
  } else {
    printf("The product does not exist in stock.\n");
  }
}

//////search_product allows users to find a product and display its information
void search_product() {
  char name;
  // Ask the user to enter product information
  printf("Entrez le nom du produit : ");
  scanf("%s", name);
  // Find the product in stock
  int product_index = -1;
  for (int i = 0; i < num_products; i++) {
    if (strcmp(products[i].name, name) == 0) {
      product_index = i;
      break;
    }
  }

  // Show product information if it's there
  if (product_index != -1) {
    printf("names : %d\n", products[product_index].name);
    printf("Quantity in stock : %d\n", products[product_index].quantity);
    printf("the price of the product : %d\n", products[product_index].price);
    printf("Expiration date : %s\n", products[product_index].expiration);
  } else {
    printf("The product was not found in stock.\n");
  }
}

//////  display_history allows users to display the product history
void display_history() {
  int current_month = 0;
  int current_year = 0;
  time_t current_time = time(NULL);
  struct tm *tm_struct = localtime(&current_time);
  current_month = tm_struct->tm_mon + 1;
  current_year = tm_struct->tm_year + 1900;

  // Browse history and view current month's entries
  printf("Inputs and outputs of the current month :\n");
  for (int i = 0; i < num_history_entries; i++) {
    if (history[i].month == current_month && history[i].year == current_year) {
            printf("%s %d %s le %d/%d/%d\n", history[i].type == ENTRY ? "Addition of" : "Withdrawal of", history[i].quantity, history[i].name, history[i].day, history[i].month, history[i].year);
    }
  }

  // Browse history and view entries by month for the current year
  printf("\nEntries and exits per month for the current year :\n");
  for (int month = 1; month <= 12; month++) {
    printf("month %d:\n", month);
    for (int i = 0; i < num_history_entries; i++) {
      if (history[i].month == month && history[i].year == current_year) {
        printf("%s %d %s le %d/%d/%d\n", history[i].type == ENTRY ? "Addition of" : "Withdrawal of", history[i].quantity, history[i].name, history[i].day, history[i].month, history[i].year);
      }
    }
  }
}


////// archive_history allows users to archive product history
void archive_history() {
  ProductHistory *history;
  int num_entries ;
  printf("give the number of entries");
  gets(num_entries);

  // Open the file in write mode
  FILE *file = fopen("history.txt", "w");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  // Go through the history and save each entry to the file
  for (int i = 0; i < num_entries; i++) {
    fprintf(file, "%d/%d/%d,%s,%d,%d\n", history[i].day, history[i].month, history[i].year, history[i].name, history[i].quantity, history[i].type);
  }

  // Ferme
   fclose(file);

}

int main() {
  // Affichez le menu de l'application
  printf("--- Stock Manager ---\n");
  printf("To add a product write 1\n");
   printf("To Delete a product write 2\n");
  printf("To modify a product write 3\n");
  printf("To search for a product write 4\n");
  printf("To show history write 5\n");
  printf("To Archive history write 6\n");
  printf("To exit write 7\n");

  int choice;
  printf("Entrez votre choix : ");
  scanf("%d", &choice);

  // Call the appropriate function according to the user's choice
  switch (choice) {
    case 1:
      add_product();
      break;
   case 2:
      remove_product();
      break;
    case 3:
      modify_product();
      break;
    case 4:
      search_product();
      break;
    case 5:
      display_history();
      break;
    case 6:
      archive_history();
      break;
    case 7:
      return 0;
    default:
      printf("Invalid choice\n");
      break;
  }

  return 0;
}
