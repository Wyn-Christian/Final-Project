void displayOrders(Order (*arrayOrders)[], int numOrder)
{
  printf("\t\tSIMPLE RESTAURANT SYSTEM\n\n");
  printf("\t%-10s %-20s %s\n\n", "Code", "Name", "Price");
  Order current;
  char name[100];
  for (int i = 0; i < numOrder; i++)
  {
    current = (*arrayOrders)[i];

    strcpy(name, current.name);
    arrangeName(name);

    printf("%d.]     %-10s %-20s %.f\n", i + 1, current.code, name, current.price);
  }
}

int getIndexCode(char *answer, Order (*arrayOrders)[], int numOrder)
{
  int index = 0;
  for (int i = 0; i < numOrder; i++)
  {
    if (!strcmp(answer, (*arrayOrders)[i].code))
      return index;

    index += 1;
  }
  return -1;
}

float displayResult(Order (*arrayOrders)[], int index, int quantity)
{
  Order currentOrder = (*arrayOrders)[index];
  char tempName[100];
  float amount = (float)quantity * currentOrder.price;
  strcpy(tempName, currentOrder.name);
  arrangeName(tempName);
  printf("\nHere is the result: ");
  printf("\n\t        Name: %s", tempName);
  printf("\n\t       Price: %.f", currentOrder.price);
  printf("\n\t    Quantity: %d", quantity);
  printf("\n\tTotal Amount: %.f", amount);
  return amount;
}

void promptOrder(Order (*arrayOrders)[], int numOrder,
                 int *index, int *result, char *answer,
                 int *quantity)
{
  do
  {
    system("cls");
    displayOrders(arrayOrders, numOrder);
    if (*index == -1)
    {
      FLUSH;
      printf("\nThe code you enter doesn't exist...\nPlease Try Again...");
    }

    if (!(*result))
    {
      FLUSH;
      printf("\nPlease Enter Valid Input...\n ");
    }
    printf("\n\nEnter Code: ");
    (*result) = scanf("%s", answer);
    if ((int)answer[0] > 64 && (int)answer[0] < 91)
    {
      *index = getIndexCode(answer, arrayOrders, numOrder);
    }
    else
    {
      (*result) = 0;
    }

  } while (!(*result) || (*index) == -1);

  *quantity = 0;
  do
  {
    if (!(*result))
    {
      FLUSH;
      system("cls");
      displayOrders(arrayOrders, numOrder);
      printf("\n\nEnter Code: %s", answer);
      printf("\n\nPlease enter valid input...");
    }
    printf("\nEnter Quantity: ");
    *result = scanf("%d", quantity);

  } while (!result);
}

void updateHistory(QueueOrder *currentOrder)
{
  FILE *file = fopen(historyOrdersFile, "a");
  char tempName[100];
  strcpy(tempName, currentOrder->name);
  arrangeName(tempName);
  fprintf(file, "%-10s %-19s %-10d %-9.f %-14.f\n",
          currentOrder->code, tempName, currentOrder->quantity, currentOrder->price, currentOrder->amount);
  fclose(file);
}

int getIndex(char *code, Receipt (*arrayReceipt)[], int totalOrders)
{
  int result = 0;
  for (int i = 0; i < totalOrders; i++)
  {
    if (!strcmp(code, (*arrayReceipt)[i].code))
      return result;

    result += 1;
  }
  result = -1;
}

void updateSalesReceipt(QueueOrder *currentOrder,
                        Receipt (*current)[],
                        Receipt (*arrayReceipt)[],
                        int *totalOrders)
{
  int index = getIndex(currentOrder->code, arrayReceipt, *totalOrders);
  if (index != -1)
  {
    (*arrayReceipt)[index]
        .quantity += currentOrder->quantity;
    (*arrayReceipt)[index].amount += currentOrder->amount;
    (*current)[index]
        .quantity += currentOrder->quantity;
    (*current)[index].amount += currentOrder->amount;
  }
  else
  {
    int i = (*totalOrders);
    strcpy((*arrayReceipt)[i].code, currentOrder->code);
    strcpy((*arrayReceipt)[i].name, currentOrder->name);
    (*arrayReceipt)[i]
        .price = currentOrder->price;
    (*arrayReceipt)[i]
        .quantity = currentOrder->quantity;
    (*arrayReceipt)[i].amount = currentOrder->amount;

    strcpy((*current)[i].code, currentOrder->code);
    strcpy((*current)[i].name, currentOrder->name);
    (*current)[i]
        .price = currentOrder->price;
    (*current)[i]
        .quantity = currentOrder->quantity;
    (*current)[i].amount = currentOrder->amount;
    (*totalOrders) += 1;
  }
  return;
}

void updateSalesReceiptFile(Receipt (*arrayReceipt)[], int *totalOrders)
{
  FILE *file = fopen(orderReceiptsFile, "w");
  char tempName[100];
  fprintf(file, "%-17s %-10s %s\n\n", "Name", "Quantity", "Amount");
  // A loop that gives a first value to each array indexes
  for (int i = 0; i < *totalOrders; i++)
  {
    strcpy(tempName, (*arrayReceipt)[i].name);
    arrangeName(tempName);
    fprintf(file, "%-17s %-10d %.f\n", tempName, (*arrayReceipt)[i].quantity, (*arrayReceipt)[i].amount);
  }
  fclose(file);
}

void initializeCurrentReceipt(Receipt (*destination)[],
                              Receipt (*source)[], int *totalOrders)
{
  for (int i = 0; i < *totalOrders; i++)
  {
    strcpy((*destination)[i].code, (*source)[i].code);
    strcpy((*destination)[i].name, (*source)[i].name);
    (*destination)[i].price = (*source)[i].price;

    (*destination)[i].amount = 0;
    (*destination)[i].quantity = 0;
  }
}
int generateRandom(void)
{
  srand(time(NULL));
  int ran = (rand() % 999) + 1;
  return ran;
} // generateRandom Function

void createReceiptFile(Receipt (*currentReceipt)[], int *total, char *code)
{
  FILE *file;
  srand(time(NULL));
  int randomNum = generateRandom();

  char filename[50];
  sprintf(filename, "receipts/%03d.txt", randomNum);
  sprintf(code, "%03d", randomNum);
  file = fopen(filename, "w+");

  fprintf(file, "%-18s %-12s %-10s\n\n",
          "Name", "Quantity", "Amount");

  for (int i = 0; i < *total; i++)
  {
    if ((*currentReceipt)[i].quantity)
    {

      fprintf(file, "%-18s %-12d %-10.f\n", (*currentReceipt)[i].name, (*currentReceipt)[i].quantity, (*currentReceipt)[i].amount);
    }
  }

  fclose(file);
  return;
}

void storeAndDequeueAllOrder(Queue *q, Receipt (*arrayReceipt)[], int *totalOrders)
{
  if (q->front == NULL)
    return;

  QueueOrder *temp;
  Receipt currentReceipt[TOTAL];
  initializeCurrentReceipt(&currentReceipt, arrayReceipt, totalOrders);

  while (q->front != NULL)
  {
    temp = q->front;
    updateHistory(temp);
    updateSalesReceipt(temp, &currentReceipt,
                       arrayReceipt, totalOrders);
    updateSalesReceiptFile(arrayReceipt, totalOrders);
    q = DequeueOrder(q);
  }
  char code[5];
  createReceiptFile(&currentReceipt, totalOrders, code);
  printf("Here is your receipt code: %s", code);
  return;
}

void buyOrders(Order (*arrayOrders)[], Receipt (*arrayReceipt)[], int numOrder, int *totalOrders)
{
  char answer[10];
  int result = 1, index = 1, quantity = 0;
  Queue *queue = CreateQueue();
  do
  {
    promptOrder(arrayOrders, numOrder, &index,
                &result, answer, &quantity);

    float amount = displayResult(arrayOrders, index, quantity);

    if (promptUser("\n\nProceed to buy[Y/N]? "))
    {
      /* Enqueue the Order */
      queue = EnqueueOrder(queue, (*arrayOrders)[index], quantity, amount);
    }

  } while (promptUser("\nAnother Order[Y/N]? "));
  /* Store and Dequeue the orders */
  storeAndDequeueAllOrder(queue, arrayReceipt, totalOrders);

  puts("\n\t\tPress any key to RETURN");
  char some = getch();
}
