/*
  some necessary utilities functions

  The following functions are executed first
  before the MAIN program starts:
  * readAllDest()
    * scanOrder()
    * recordOrder()
  * initialize()

  Some function globally used:
  *promptUser()

 */

// This function Reads the current data in the `ordersFile`
// It returns (1 or 0) signifying either true or false
int scanOrder(FILE *file, Order *current, int *total)
{
  // Read the file and check if its valid; return number (1 / 0)
  int result;

  // A pre-loop that checks if the current line is
  // in the right line to scan the data.
  while ((result = fscanf(file, "%s %s %f", &current->code, &current->name, &current->price)) == 2)
  {
    // if its not in the right line, recurse (invoke its own function)
    return scanOrder(file, current, total);
  }

  // Check the result of `fscanf`
  if (result == EOF)
  {
    // if its EOF, then close the file and return 0/false
    fclose(file);
    return 0;
  }
  else if (result != 3)
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
} // scanOrder Function

// it stores the current destination from `scanOrder` function
// in the categories(array of struct)
void recordOrder(Order *order, int *index,
                 Order (*orders)[])
{
  int i = *index;

  // STORE IT in the categories with respect to their index
  strcpy(((*orders)[i]).code, order->code);
  strcpy(((*orders)[i]).name, order->name);
  (*orders)[i].price = order->price;
  *index += 1;
  return;
} // recordOrder function

// This function will try to analyze and store
// the data in `ordersFile` to `orders` array
void readAllOrders(int *total, Order (*orders)[])
{
  *total = 0;
  FILE *file = fopen(ordersFile, "r");
  if (!file)
  {
    printf("\aError opening %s file\n", ordersFile);
    exit(0);
  }

  int i = 0;
  Order currentOrder;
  // A loop that calls the previous two function
  // its job is to keep reading until
  // either produce error or done scanning
  while (scanOrder(file, &currentOrder, total))
  {
    recordOrder(&currentOrder, &i, orders);
  }

  return;
} // readAllOrders Function

// This function initialize the values of the `arrayCategories` array
//   and overwrite/create the `historyOrdersFile` with headers only
void initialize(Order (*arrayOrders)[],
                Receipt (*arrayReceipts)[], int *total,
                int *totalOrders)
{
  // A loop that gives a first value to each array indexes
  for (int i = 0; i < *total; i++)
  {
    strcpy((*arrayReceipts)[i].code, (*arrayOrders)[i].code);
    strcpy((*arrayReceipts)[i].name, (*arrayOrders)[i].name);
    (*arrayReceipts)[i].quantity = 0;
    (*arrayReceipts)[i].amount = 0;
    *totalOrders += 1;
  }

  // overwrite the `historyOrdersFile` with headers only
  FILE *file = fopen(historyOrdersFile, "w");
  fprintf(file, "%-13s %-14s %-14s\n\n", "Code", "Name", "Price Amout");
  fclose(file);
} // initialize Function

int promptUser(char *question)
{
  int result = 0;
  bool isAnswer = false;

  char answer[1];
  do
  {

    printf(question);
    result = scanf("%s", answer);
    if (!result)
    {
      FLUSH;
      printf("\nInvalid input, please try again...");
    }
    char tempHolder[1];
    strcpy(tempHolder, answer);

    if (strcmp(tempHolder, "y") == 0 || strcmp(tempHolder, "Y") == 0)
    {
      isAnswer = true;
      return 1;
    }

    if (strcmp(tempHolder, "n") == 0 || strcmp(tempHolder, "N") == 0)
    {
      isAnswer = true;
      return 0;
    }
    FLUSH;
  } while (!result || !isAnswer);
}
