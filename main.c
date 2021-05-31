#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
// Some pre-proccessed codes
#define FLUSH while (getchar() != '\n')

// This is the file path of the .txt files
#define ordersFile "assets/orders.txt"
#define historyOrdersFile "assets/historyOrders.txt"
#define orderReceiptsFile "assets/orderReceipt.txt"

// the database root file
// #define databaseRootFile "database/"

#define TOTAL (100)         // size of an arrays
#define MAXTRANSACTION (16) // For non reservation per transaction

// This is our external files
#include "codes/structs.h"        // Just a collection of structs
#include "codes/designs.c"        // Some UI designs
#include "codes/queue.c"          // Queue Functions
#include "codes/utilities.c"      // some reusable functios
#include "codes/manageOrders.c"   // 1.] Manage orders
#include "codes/buyOrders.c"      // 2.] Buy Orders
#include "codes/displayReceipt.c" // 3.] Display Receipt
#include "codes/mainMenu.c"       // The MAIN menu

int main(void)
{
  Order allOrders[TOTAL];       // to track the current data in `ordersFile`
  Receipt orderReceipts[TOTAL]; // To track the sales receipt

  // To track the numbers of categories in the `ordersFile`
  unsigned int numOrders = 0;
  // To track the total order in the `salesReceipt` array
  unsigned int totalOrders = 0;

  // Get the information in the `ordersFile`
  readAllOrders(&numOrders, &allOrders);

  // Initialize the values in `salesReceipt` array with 0
  initialize(&allOrders, &orderReceipts, &numOrders,
             &totalOrders);

  // Start the main program
  displayMainMenu(&allOrders, &orderReceipts,
                  &numOrders, &totalOrders);

  return 0;
} // main Function
