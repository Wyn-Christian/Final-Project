// This function simply display the current data in the `arrayReceipt`
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