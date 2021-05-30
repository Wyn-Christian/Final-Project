/* 
  This is where manage destination functions

  The following functions are used for 
  managing destinations:
  * manageDestination()
    * addOrder()
    * editOrder()
    * deleteOrder()
    * displayOrder()
 */

// this function adds destination in the `destinationFile`
void addOrder(Order (*arrayOrders)[], int *total, bool hasBuffer)
{
  system("cls");

  //  checks if the buffer has some value
  if (hasBuffer)
    FLUSH;

  int result = 1;
  char tempCode[50];
  char tempOrder[50];
  float tempPrice;

  // Prompt the user the dest code
  printf("\n\nOrder Code: %02d", (*total + 1));

  // Prompt the user a new order
  do
  {
    if (!result)
    {
      FLUSH;
    }
    printf("\nEnter new order code (char)(num): ");
    result = scanf("%s", tempCode);

    printf("\nTESTING result = %d\n", result);
  } while (!result);

  result = 1;

  do
  {
    if (!result)
    {
      FLUSH;
    }
    printf("\nEnter new order name (camelCase): ");
    result = scanf("%s", tempOrder);
    printf("\nTESTING result = %d\n", result);

  } while (!result);

  result = 1;

  do
  {
    if (!result)
    {
      FLUSH;
    }
    printf("\nEnter new order price: ");
    result = scanf("%f", &tempPrice);

    printf("\nTESTING result = %d\n", result);
  } while (!result);

  printf("\n%s %s %.f", tempCode, tempOrder, tempPrice);

  // Request the user to proceed
  char answer;
  if (promptUser("\nSAVE this RECORD(y/n)?"))
  {
    int index = *total;
    // Append the data in the file
    FILE *file = fopen(ordersFile, "a");
    fprintf(file, "\n%-10s %-17s %-10.f", tempCode, tempOrder, tempPrice);
    fclose(file);

    // Store it in the struct information array
    strcpy((*arrayOrders)[index].code, tempCode);
    strcpy((*arrayOrders)[index].name, tempOrder);
    (*arrayOrders)[index].price = tempPrice;

    *total += 1;
  }

  // Prompt the user for another new record
  if (promptUser("\nAnother record(y/n)?"))
    return addOrder(arrayOrders, total, false);
  else
    // Return to Manage Destination menu
    return;

} // addOrder Function

void printHeaders(FILE *file)
{
  fprintf(file, "%-15s %-12s %s\n\n", "Code", "Name", "Price");
  for (int i = 0; i < 40; i++)
    fprintf(file, "-");
  fprintf(file, "\n\n");

  return;
}

int checkCode(Order (*orders)[], int total, char *code)
{
  int result = 0;
  for (int i = 0; i < total; i++)
  {
    if (!strcmp((*orders)[i].code, code))
      return result;
    result++;
  }
  return -1;
}

// It updates the existing category's price
void editOrder(Order (*arrayOrders)[], int total, bool hasBuffer)
{
  system("cls");
  // checks if the buffer has some irrelevant values
  if (hasBuffer)
  {
    FLUSH;
    printf("\nSorry, the code you enter doesn't exist...\nPlease Try Again...\n");
  }

  char code[5];
  int result = 1, index;
  do
  {
    if (!result)
    {
      FLUSH;
    }
    printf("\n\nEnter Order code: ");
    result = scanf("%s", code);
    if (!result)
      continue;
  } while (!result);

  if ((index = checkCode(arrayOrders, total, code)) == -1)
  {
    editOrder(arrayOrders, total, true);
  }

  // display the current ordere
  printf("\nCurrent order: %s", (*arrayOrders)[index].name);

  float newPrice;
  // Prompts the user a new price for the selected destination
  do
  {
    if (!result)
    {
      printf("\nPlease enter valid input...\n");
      FLUSH;
    }
    printf("\nEnter new order price(digit only): ");
    result = scanf("%f", &newPrice);

  } while (!result);

  // Ask the user to save the changes
  // If yes, then update the current category's price
  if (promptUser("\nSAVE changes[y/n]?"))
  {
    // store the new price
    (*arrayOrders)[index].price = newPrice;

    // Reprint all the data with the new update
    FILE *file = fopen(ordersFile, "w+");

    printHeaders(file);

    for (int i = 0; i < total; i++)
    {
      fprintf(file, "%-10s %-17s %-15.f\n", (*arrayOrders)[i].code, (*arrayOrders)[i].name, (*arrayOrders)[i].price);
    }
    fclose(file);
  }

  // Ask the user for another record
  if (promptUser("\nEdit another record[y/n]?"))
    return editOrder(arrayOrders, total, false);
  else
    // Return to Manage Destination menu
    return;

} // editOrder Function

// It removes the existing category and update the arrays
void deleteOrder(Order (*arrayOrders)[], int *total, bool hasBuffer)
{
  system("cls");
  // checks if the buffer has some irrelevant values
  if (hasBuffer)
  {
    FLUSH;
    printf("\nSorry, the code you enter doesn't exist...\nPlease Try Again...\n");
  }

  char code[5];
  int result = 1, index;
  do
  {
    if (!result)
    {
      FLUSH;
    }
    printf("\n\nEnter Order code: ");
    result = scanf("%s", code);
    if (!result)
      continue;
  } while (!result);

  if ((index = checkCode(arrayOrders, *total, code)) == -1)
  {
    deleteOrder(arrayOrders, total, true);
  }

  // Displays the selected category's name and price
  printf("\nOrder name: %s", (*arrayOrders)[index].name);
  printf("\nOrder price: %.f", (*arrayOrders)[index].price);

  // Ask the user to proceed to delete the selected category
  // if yes, then delete the selected category
  if (promptUser("\nAre you sure you want to delete this record[y/n]?"))
  {
    int totalNum = *total - 1;
    puts("\nDeleting this record...");

    // Reprint the `destinationsFile` headings
    FILE *file = fopen(ordersFile, "w+");
    printHeaders(file);

    // A loop that updates the `arrayOrders` array
    for (int i = 0; i < totalNum; i++)
    {
      if (i >= index)
      {
        // if i is greater than or equal than the index
        //  of the selected category, then store the
        //  current `i` data with the `next` index data
        int next = i + 1;
        strcpy((*arrayOrders)[i].code, (*arrayOrders)[next].code);
        strcpy((*arrayOrders)[i].name, (*arrayOrders)[next].name);
        (*arrayOrders)[i].price = (*arrayOrders)[next].price;
      }

      // print the data in the `destinationsFile`
      fprintf(file, "%-10s %-17s %-15.f\n", (*arrayOrders)[i].code, (*arrayOrders)[i].name, (*arrayOrders)[i].price);
    }

    // Decrement the current total number of categories
    *total -= 1;
    fclose(file);
  }

  // Ask the user to edit another record
  if (promptUser("\nDelete another record[y/n]?"))
    return deleteOrder(arrayOrders, total, false);
  else
    // Return to Manage Destination menu
    return;

} // editOrder Function

// Displays the current data in the `reportFile`
void displayOrder(Order (*arrayOrders)[], int total)
{
  system("cls");
  if (!total)
    printf("\nSorry, there's no available flight right now...");
  else
  {
    // Display the header
    printEquals();
    puts("\n\t\tList of Orders");
    printf("\n\t\t%-10s %-17s %5s\n\n", "Code", "Name", "Price");

    // Display all of the current data
    for (int i = 0; i < total; i++)
    {
      printf("\n\t\t%-10s %-17s %.f\n", (*arrayOrders)[i].code, (*arrayOrders)[i].name, (*arrayOrders)[i].price);
    }
    printEquals();
  }

  // Return to Manage Destination menu
  puts("\n\t\tPress any key to RETURN");
  char some = getch();
  return;
} // displayOrder Function

// The main function in this file
// It manage the information of `arrayCategories`
void manageOrders(Order (*arrayCategories)[], int *total)
{
  system("cls");
  FLUSH;

  char menu[5][100] = {
      "Add New Order",
      "Edit",
      "Delete",
      "Display all",
      "Return to MAIN"};

  // Display the menu
  printDash();
  printf("\n\t\tMANAGE DESTINATION\n\n");
  for (int i = 0; i < 5; i++)
    printf("\t\t%d.] %s\n\n", (i + 1), menu[i]);
  printDash();

  // Prompts the user to choose which category
  printf("\t\tEnter Choice: ");

  char choice;
  choice = getchar();

  // Analyze the `choice` stored value
  switch (choice)
  {
  case '1':
    // if '1', then invoke `addOrder` Function
    addOrder(arrayCategories, total, false);
    manageOrders(arrayCategories, total);
    break;
  case '2':
    // if '2', then invoke `editOrder` Function
    editOrder(arrayCategories, *total, false);
    manageOrders(arrayCategories, total);
    break;
  case '3':
    // if '3', then invoke `deleteOrder` Function
    deleteOrder(arrayCategories, total, false);
    manageOrders(arrayCategories, total);
    break;
  case '4':
    // if '4', then invoke `displayOrder` Function
    displayOrder(arrayCategories, *total);
    manageOrders(arrayCategories, total);
    break;
  case '5':
    // if '5', then return to MAIN
    break;
  default:
    puts("Error, invalid input. try again");
    manageOrders(arrayCategories, total);
  }

  return;
}
