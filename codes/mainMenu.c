/* 
  The `displayMainMenu` function display the main menu
  while it tracks the modifications of the datas
  throughout the program, those datas are the following:
    * arrayOrders
    * arrayReceipts
    * currentNumOrders
 */
void adminMenu(Order (*arrayOrders)[], int *currentNumOrder)
{
  char username[50] = {"admin"};
  char password[50] = {"password"};
  char choice1[50];
  char choice2[50];
  char answer;

  // Loop while username and password is not satisfied
  do
  {
    system("cls");
    printf("\n\n\t\tEnter username: ");
    scanf("%s", &choice1);
    printf("\n\n\t\tEnter password: ");
    scanf("%s", &choice2);
  } while ((!strcmp(username, choice1) && !strcmp(password, choice2)) == 0);

  manageOrders(arrayOrders, currentNumOrder);
  return;
}

void cashierMainMenu(Order (*arrayOrders)[],
                     Receipt (*arrayReceipts)[],
                     int *currentNumOrders, int *totalOrders)
{
  // Clear screen
  system("cls");

  // Display the MAIN menu
  printf("\n\t\tCASHIER MAIN MENU\n");
  char menu[5][100] = {
      "Buy Order",
      "Sales Receipt",
      "Go back to main menu"};

  for (int i = 0; i < 3; i++)
    printf("\n\t\t%d.] %s\n", (i + 1), menu[i]);

  // Propmt user to choose
  char choice;
  printf("\n\t\tEnter Choice: ");
  choice = getchar();

  // Analyze the `choice` data
  switch (choice)
  {

  case '1':
    // if 1, then call the `buyOrders` function from `codes/buyOrders.c` file
    buyOrders(arrayOrders, arrayReceipts,
              *currentNumOrders, totalOrders);

    cashierMainMenu(arrayOrders,
                    arrayReceipts, currentNumOrders,
                    totalOrders);
  case '2':
    // if 2, then call the `displaySalesReceipts` function from `codes/displayReceipts.c` file
    salesRecieptsMenu(arrayReceipts, *totalOrders);

    cashierMainMenu(arrayOrders,
                    arrayReceipts, currentNumOrders,
                    totalOrders);
  case '3':
    // if 3, go back to main menu.
    return;
  default:
    // if its invalid input, display the error and return to Main
    printf("\t\n\tError, invalid input. try again");

    cashierMainMenu(arrayOrders,
                    arrayReceipts, currentNumOrders,
                    totalOrders);
  }
} // displayMainMenu Function

void mainMenu(Order (*arrayOrders)[],
              Receipt (*arrayReceipts)[],
              int *currentNumOrders, int *totalOrders)
{
  char menu[5][100] = {
      "Admin",
      "Cashier",
      "EXIT"};
  system("cls");
  printf("\n\t\tWELCOME TO OUR RESTAURANT\n");

  for (int i = 0; i < 3; i++)
  {
    printf("\n\t\t%d.] %s\n", (i + 1), menu[i]);
  }
  char choice;
  printf("\n\t\tEnter Choice: ");
  choice = getchar();

  switch (choice)
  {
  case '1':
    // If '1', prompt the admin menu.
    adminMenu(arrayOrders, currentNumOrders);
    mainMenu(arrayOrders, arrayReceipts, currentNumOrders, totalOrders);

  case '2':
    // If '2', go to the cashier menu.
    cashierMainMenu(arrayOrders, arrayReceipts, currentNumOrders, totalOrders);
    mainMenu(arrayOrders, arrayReceipts, currentNumOrders, totalOrders);

  case '3':
    // If '3', print the time and proponents then end the program.
    system("cls");
    printSlash();
    printTime();
    printSlash();
    exit(0);

  default:
    // Print error, invalid input.
    printf("\t\t\nError, invalid input. try again");
    mainMenu(arrayOrders,
             arrayReceipts, currentNumOrders,
             totalOrders);
    FLUSH;
  }
}
