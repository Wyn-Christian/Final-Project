

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

void buyOrders(Order (*arrayOrders)[], Receipt (*arrayReceipt)[], int numOrder, int totalOrders)
{
  system("cls");
  displayOrders(arrayOrders, numOrder);

  puts("\t\tPress any key to RETURN");
  char some = getch();
}