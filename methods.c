#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ColorEffects.c"

char customer_name[30];
char customer_phone[10];

int count;

struct Items
{
  int num;
  char name[30];
  float price;
}items[35];

struct cart
{
  int num;
  char name[30];
  float price;
  int quantity;
  float total_price;
  struct cart *next;
};

typedef struct cart cart;
cart  *start;

void init_items(struct Items *g,char *a, char *b)
{
  FILE *fp1,*fp2;
  int i=0;
  float cost;

  fp1 = fopen(a, "r");
  fp2 = fopen(b, "r");

  if(fp1 == NULL && fp2 == NULL)
  {
     perror("Error opening file or the File doesn't exist\n");
     exit(1);
  }

  while(fgets(g[i].name, 30, fp1)!=NULL && fscanf(fp2,"%f",&cost)!=EOF)
  {
      g[i].name[strlen(g[i].name)-1] = '\0';
      g[i].price=cost;
      g[i].num=i+1;
      i++;
  }

  fclose(fp1);
  fclose(fp2);
  return;
}

void lines()
{
    SetColor(6);
    for(int i=0;i<115;i++)
        printf("-");
    printf("\n");
}

void header()
{
  printf("\n");
  SetColor(6);
  lines();
  printf("\t\t\t\t\tSuperMarket Billing Software\n");
  lines();
}

void menu()
{
  SetColor(6);
  printf("\n  Item Code.\t     Item Name\t\t   Price/Unit in INR\n");
  lines();
}

void print(struct Items *g, int n)
{
  int i;
  system("cls");
  header();
  menu();
  SetColor(8);
  for(i = 0; i < n; ++i)
  {
      if(strlen(g[i].name)>15)
      printf(" %d\t\t%s\t\t%0.2f\n",g[i].num,g[i].name,g[i].price);
      else
      printf(" %d\t\t%s\t\t\t%0.2f\n",g[i].num,g[i].name,g[i].price);
  }
  printf("\n");
  SetColor(15);
  printf("\n\t\tPress any key to return......\n");
  getch();
  return;
}

void login()
{
  header();
  SetColor(15); printf("\n\tEnter Customer Name : "); SetColor(11);
  scanf("%[^\n]s",customer_name);
  SetColor(15); printf("\nEnter Customer Phone Number : "); SetColor(11);
  scanf("%s",customer_phone);
  printf("\n");
  SetColor(15);
}

int options()
{
  int ch;
  system("cls");
  header();
  SetColor(8);
  printf("\n\t\tChoose an Option from below:\n\n");
  SetColor(15);  printf("\t\t1");  SetColor(8);  printf(" : View Inventory\n");
  SetColor(15);  printf("\t\t2");  SetColor(8);  printf(" : Add Item\n");
  SetColor(15);  printf("\t\t3");  SetColor(8);  printf(" : Delete Item\n");
  SetColor(15);  printf("\t\t4");  SetColor(8);  printf(" : View Bill\n");
  SetColor(15);  printf("\t\t5");  SetColor(8);  printf(" : Print Bill\n");
  SetColor(15);  printf("\t\t6");  SetColor(8);  printf(" : Exit\n\n\t\t");
  scanf("%d",&ch);
  return ch;
}

cart* getnode()
{
  cart *temp;
  int n;
  temp = (cart *)malloc(sizeof(cart));
  if(temp==NULL)
  {
    perror("\n\t\tDMA Failed\n");
    exit(1);
  }
  SetColor(8);
  printf("\n\n\t\tEnter the Item Code : ");
  while(1)
  {
    scanf("%d",&n);
    if(n>0 && n<=35)
      break;
    else
    {
      SetColor(4);
      printf("\t\tInvalid Item Code | Please Enter Again\n\t\t\t\t      ");
      SetColor(8);
    }
  }
  temp->num=n;
  strcpy(temp->name,items[n].name);
  temp->price = items[n].price;
  printf("\n\t    Enter Required Quantity : ");
  scanf("%d",&temp->quantity);
  temp->total_price = temp->price * temp->quantity;
  temp->next = NULL;
  return temp;
}

void add_items()
{
  cart *temp = start;
  if(start==NULL)
  {
    start = getnode();
    return;
  }
  while(temp->next!=NULL)
  {
    temp=temp->next;
  }
  temp->next = getnode();
  count++;
  return;
}

void view_cart()
{
  cart *temp = start;
  if(start==NULL)
  {
    SetColor(4);
    printf("\n\t\t\tCART IS EMPTY\n");
    return;
  }
  SetColor(6);
  printf("\n Item Code.\t     Item Name\t\t\t\tPrice\t\tQuantity\tTotal Cost\n");
  for(int i=0;i<100;i++)
      printf("-");
  printf("\n");
  SetColor(15);
  for(temp=start; temp!=NULL; temp=temp->next)
  {
    if(strlen(temp->name)>15)
    printf("  %d\t\t%s\t\t\t%0.2f\t\t%d\t\t%0.2f\n",temp->num,temp->name,temp->price,temp->quantity,temp->total_price);
    else
    printf("  %d\t\t%s\t\t\t\t%0.2f\t\t%d\t\t%0.2f\n",temp->num,temp->name,temp->price,temp->quantity,temp->total_price);

  }
  return;
}

void bill()
{
  float sum = 0;
  int num = 0, count =0;
  cart *temp = start;
  if(start==NULL)
  {
    SetColor(4);
    printf("\n\t\t\tCART IS EMPTY\n");
    getch();
    return;
  }
  SetColor(6);
  printf("\n Item No.\tItem Code.\t     Item Name\t\t\t\tPrice\t\tQuantity\tTotal Cost\n");
  lines();
  SetColor(15);
  for(temp=start; temp!=NULL; temp=temp->next)
  {
    num++;
    sum = sum + temp->total_price;
    count = count + temp->quantity;
    if(strlen(temp->name)>15)
    printf("    %d\t\t  %d\t\t%s\t\t\t%0.2f\t\t%d\t\t%0.2f\n",num,temp->num,temp->name,temp->price,temp->quantity,temp->total_price);
    else
    printf("    %d\t\t  %d\t\t%s\t\t\t\t%0.2f\t\t%d\t\t%0.2f\n",num,temp->num,temp->name,temp->price,temp->quantity,temp->total_price);
  }
  SetColor(6);
  lines();
  SetColor(8); printf("\tTotal No of Items : "); SetColor(15); printf("%d",count);
  SetColor(8); printf("\t\t\t\t\t\t Total Bill Amount : "); SetColor(15); printf("%0.2f  INR\n",sum);
  lines(); SetColor(15); printf("\t\t\t\t\t Thank You | Visit Again \n");
  lines();
  getch();
  return;
}

void delete_items()
{
  int n,flag;
  cart *temp1 = start, *temp2;
  if(start==NULL)
  {
    getch();
    return;
  }
  SetColor(8);
  printf("\n\n\t\tEnter the Item Code : ");
  while(1)
  {
    scanf("%d",&n);
    if(n>0 && n<=35)
    {
      flag=0;
      for(temp1=start; temp1!=NULL; temp1=temp1->next)
      {
        if(start->num==n)
        {
          temp1=start;
          start=start->next;
          free(temp1);
          flag=1;
          break;
        }
        else if(temp1->next->num == n)
        {
          temp2 = temp1;
          temp1 = temp1->next;
          temp2->next = temp1->next;
          free(temp1);
          flag=1;
          break;
        }
      }
      if(flag==0)
      {
        SetColor(4);
        printf("\t\t\tItem not in Cart\n\t\t\t\t");
        getch();
        SetColor(8);
        break;
      }
      else
        break;
    }
    else
    {
      SetColor(4);
      printf("\t\tInvalid Item Code | Please Enter Again\n\t\t\t\t");
      SetColor(8);
    }
  }
  return;
}
