// This function simply display the current data in the `arrayReceipt`

// It checks if the current file path is not existing
//   returns  1 or 2; signifying `true` or `false`
int checkFilePath(char *sampleFilePath)
{
  FILE *fp = fopen(sampleFilePath, "r");
  if (!fp)
    return 0;

  fclose(fp);
  return 1;
} // checkFilePath Function

// This function Reads the current data in the `ordersFile`
// It returns (1 or 0) signifying either true or false
int scanReceiptOrder(FILE *file, Receipt *current, int *total)
{
  // Read the file and check if its valid; return number (1 / 0)
  int result;

  // A pre-loop that checks if the current line is
  // in the right line to scan the data.
  while ((result = fscanf(file, "%s %f %d %f", &current->name, &current->price, &current->quantity, &current->amount)) == 1)
  {
    // if its not in the right line, recurse (invoke its own function)
    return scanReceiptOrder(file, current, total);
  }

  // Check the result of `fscanf`
  if (result == EOF)
  {
    // if its EOF, then close the file and return 0/false
    fclose(file);
    return 0;
  }
  else if (result != 4)
  {
    // if its invalid, then display error and exit
    printf("\aError reading data\n");
    exit(0);
  }
  else
  {
    // if its valid, then increment the numCategories
    // and return 1 or true
    *total += 1;
    return 1;
  }
} // scanReceiptOrder Function

// it stores the current prder from `scanOrder` function
// in the categories(array of struct)
void recordReceiptOrder(Receipt *current, int *index,
                        Receipt (*receiptOrders)[])
{
  int i = *index;

  // STORE IT in the categories with respect to their index
  strcpy(((*receiptOrders)[i]).name, current->name);
  (*receiptOrders)[i].price = current->price;
  (*receiptOrders)[i].quantity = current->quantity;
  (*receiptOrders)[i].amount = current->amount;

  *index += 1;
  return;
} // recordOrder function

// This function will try to analyze and store
// the data in `receiptOrdersFile` to `orders` array
void readAllReceiptOrders(FILE *file, Receipt (*receipt)[], int *total)
{
  *total = 0;

  int i = 0;
  Receipt currentOrder;
  // A loop that calls the previous two function
  // its job is to keep reading until
  // either produce error or done scanning
  while (scanReceiptOrder(file, &currentOrder, total))
  {
    recordReceiptOrder(&currentOrder, &i, receipt);
  }

  return;
} // readAllOrders Function

void displayReceiptOrders(Receipt (*currentOrders)[], int total)
{
  char tempName[100];
  system("cls");

  printDash();
  printf("\t\t%-20s %-10s %-10s %s\n\n", "Name", "Price", "Quantity", "Total Amount");
  for (int i = 0; i < total; i++)
  {
    strcpy(tempName, (*currentOrders)[i].name);
    arrangeName(tempName);

    printf("\t\t%-20s %-10.f %-10d %-9.f\n\n", tempName,
           (*currentOrders)[i].price, (*currentOrders)[i].quantity,
           (*currentOrders)[i].amount);
  }
  printDash();
}

void codeReceipt(void)
{
  int result = 1, code;
  do
  {
    system("cls");
    // check input validity
    if (!result)
    {
      printf("\nPlease enter valid code\n");
      FLUSH;
    }
    // Prompt the user to enter the code
    printf("\nEnter order code: ");
    result = scanf("%d", &code);

  } while (!result);
  char codeFilePath[100];
  sprintf(codeFilePath, "%s%03d.txt", receiptsFile, code);

  if (!checkFilePath(codeFilePath))
    printf("\n\t\tThe Code (%03d) doesn't exist\n", code);
  else
  {
    int total = 0;
    Receipt ReceiptOrders[TOTAL];
    FILE *receiptFile = fopen(codeFilePath, "r");
    // Read the file
    readAllReceiptOrders(receiptFile, &ReceiptOrders, &total);

    fclose(receiptFile);
    // Display the Data
    displayReceiptOrders(&ReceiptOrders, total);
  }
  puts("\t\tPress any key to RETURN");
  char some = getch();
  return;
}

void displaySalesReceipt(Receipt (*arrayReceipt)[], int total)
{
  system("cls");

  char tempName[100];
  // Checks if the `total` (current total orders) don't have any data
  if (total == 0)
  {
    printf("\nSorry, there's nothing to see here... \n");
  }
  else
  {
    // display the current sales receipt from `arrayReceipt` array
    printDash();
    printf("\t\t%-20s %-10s %s\n\n", "Name", "Quantity", "Total Amount");
    for (int i = 0; i < total; i++)
    {
      strcpy(tempName, (*arrayReceipt)[i].name);
      arrangeName(tempName);
      printf("\t\t%-20s %-10d %-9.f\n\n", tempName,
             (*arrayReceipt)[i].quantity, (*arrayReceipt)[i].amount);
    }
    printDash();
  }
  puts("\t\tPress any key to RETURN");
  char some = getch();
  // Return to MAIN
  return;
} // displaySalesReceipt Function

void salesRecieptsMenu(Receipt (*arrayReceipt)[], int total)
{
  system("cls");

  char menu[3][100] = {
      "Enter Code",
      "Display Current Total Receipt",
      "Exit"};

  printf("\n\t\tSIMPLE RESTAURANT SYSTEM\n");

  for (int i = 0; i < 3; i++)
    printf("\n\t\t%d.] %s\n", (i + 1), menu[i]);

  // Propmt user to choose
  char choice = ' ';
  printf("\n\t\tEnter Choice: ");
  choice = getchar();

  // Analyze the `choice` data
  switch (choice)
  {
  case '1':
    codeReceipt();
    salesRecieptsMenu(arrayReceipt, total);

  case '2':
    displaySalesReceipt(arrayReceipt, total);
    salesRecieptsMenu(arrayReceipt, total);
  case '3':
    return;

  default:
    // if its invalid input, display the error and return to Main
    puts("Error, invalid input. try again");

    salesRecieptsMenu(arrayReceipt, total);
  }
}
