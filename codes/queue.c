
Queue *CreateQueue(void)
{
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->front = NULL;
  q->rear = NULL;
  return q;
}

Queue *EnqueueOrder(Queue *q, Order currentOrder, int quantity, float amount)
{
  printf("\nTESTING enqueue executed");
  QueueOrder *temp = (QueueOrder *)malloc(sizeof(QueueOrder));

  /* Store the current order */
  strcpy(temp->code, currentOrder.code);
  strcpy(temp->name, currentOrder.name);
  temp->price = currentOrder.price;
  temp->quantity = quantity;
  temp->amount = amount;
  temp->next = NULL;

  printf("\nTESTING1 %s %s %.f %d %.f",
         temp->code, temp->name, temp->price,
         temp->quantity, temp->amount);

  if (q->front == NULL && q->rear == NULL)
  {
    q->front = temp;
    q->rear = temp;
    printf("\nTESTING temp = %d", temp);
    printf("\nTESTING front = %d", q->front);

    return q;
  }

  q->rear->next = temp;
  q->rear = temp;
  printf("\nTESTING temp = %d", temp);
  printf("\nTESTING front = %d", q->front);
  printf("\nTESTING rear = %d", q->rear);
  return q;
}

Queue *DequeueOrder(Queue *q)
{
  printf("\nTESTING deQueue executed");
  QueueOrder *temp = q->front;

  printf("\nTESTING2 %s %s %.f %d %.f",
         q->front->code, q->front->name, q->front->price, q->front->quantity, q->front->amount);

  if (q->front == NULL)
    return q;
  if (q->front == q->rear)
    q->front = q->rear = NULL;
  else
    q->front = q->front->next;

  free(temp);
  return q;
}
