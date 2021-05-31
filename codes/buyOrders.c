

void displayOrders(Order (*arrayOrders)[], int numOrder)
{
  printf("\t\tSIMPLE RESTAURANT FKU\n\n");
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

void storeAndDequeueAllOrder(Queue *q, Receipt (*arrayReceipt)[], int totalOrders)
{
  if (q->front == NULL)
    return;

  QueueOrder *temp;
  while (q->front != NULL)
  {
    temp = q->front;
    updateHistory(temp);
  }
}

void buyOrders(Order (*arrayOrders)[], Receipt (*arrayReceipt)[], int numOrder, int totalOrders)
{
  char answer[10];
  int result = 1, index = 1, quantity = 0;
  Queue *queue = CreateQueue();
  do
  {
    promptOrder(arrayOrders, numOrder, &index,
                &result, answer, &quantity);

    float amount = displayResult(arrayOrders, index, quantity);

    if (promptUser("\nProceed to buy[Y/N]? "))
    {
      /* Enqueue the Order */
      queue = EnqueueOrder(queue, (*arrayOrders)[index], quantity, amount);
    }

  } while (promptUser("\nAnother Order[Y/N]? "));
  /* Store and Dequeue the orders */

  puts("\n\t\tPress any key to RETURN");
  char some = getch();
}