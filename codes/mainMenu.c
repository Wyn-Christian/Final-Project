/* 
  The `displayMainMenu` function display the main menu
  while it tracks the modifications of the datas
  throughout the program, those datas are the following:
    * arrayOrders
    * arrayReceipts
    * currentNumOrders
 */

void displayMainMenu(Order (*arrayOrders)[],
                     Receipt (*arrayReceipts)[],
                     int *currentNumOrders, int *totalOrders)
{
  // Clear screen
  // system("cls");

  // Display the MAIN menu
  printf("\n\t\tSIMPLE RESTAURANT FKU\n");
  char menu[5][100] = {
      "Manage Order",
      "Buy Order",
      "Sales Receipt",
      "EXIT"};

  for (int i = 0; i < 4; i++)
    printf("\n\t\t%d.] %s\n", (i + 1), menu[i]);

  // Propmt user to choose
  char choice;
  printf("\n\t\tEnter Choice: ");
  choice = getchar();

  // Analyze the `choice` data
  switch (choice)
  {
  case '1':
    // if 1, then call the `manageOrders` function from `codes/manageOrders.c` file
    manageOrders(arrayOrders, currentNumOrders);

    displayMainMenu(arrayOrders,
                    arrayReceipts, currentNumOrders,
                    totalOrders);

  case '2':
    // if 2, then call the `buyOrders` function from `codes/buyOrders.c` file
    buyOrders(arrayOrders, arrayReceipts,
              *currentNumOrders, *totalOrders);

    displayMainMenu(arrayOrders,
                    arrayReceipts, currentNumOrders,
                    totalOrders);
  case '3':
    // if 3, then call the `displaySalesReceipts` function from `codes/displayReceipts.c` file
    displaySalesReceipt(arrayReceipts, *totalOrders);

    displayMainMenu(arrayOrders,
                    arrayReceipts, currentNumOrders,
                    totalOrders);
  case '4':
    // if 4, displays the time and date and stop executing the program
    system("cls");
    printSlash();
    printTime();
    printSlash();
    exit(0);
  default:
    // if its invalid input, display the error and return to Main
    puts("Error, invalid input. try again");
    displayMainMenu(arrayOrders,
                    arrayReceipts, currentNumOrders,
                    totalOrders);
  }
} // displayMainMenu Function