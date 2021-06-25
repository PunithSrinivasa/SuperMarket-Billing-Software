#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<unistd.h>
#include "methods.c"

char item[] = "ItemList.txt";
char price[] = "ItemPrice.txt";

int main()
{
  int ch;
  int option;
  start = NULL;
  login();
  init_items(items,item,price);
  while(1)
  {
    ch=options();
    switch(ch)
    {
      case 1: print(items,35);
              break;

      case 2: while(1)
              {
                system("cls");
                header();
                SetColor(11);
                printf("\n\t\t\t\t\t\tADD ITEMS\n");
                view_cart();
                add_items();
                SetColor(8); printf("\n\n\t\t\t   Enter  ");   SetColor(15); printf("1");
                SetColor(8); printf(" : to Continue\n");  SetColor(15); printf("\t\t\t\t  2");
                SetColor(8); printf(" : to Return Back\n\t\t\t\t");
                scanf("%d",&option);
                if(option==2)
                  break;
              }
              break;

      case 3: while(1)
              {
                system("cls");
                header();
                SetColor(11);
                printf("\n\t\t\t\t\t\tDELETE ITEMS\n");
                view_cart();
                delete_items();
                SetColor(8); printf("\n\n\t\t\t   Enter  ");   SetColor(15); printf("1");
                SetColor(8); printf(" : to Continue\n");  SetColor(15); printf("\t\t\t\t  2");
                SetColor(8); printf(" : to Return Back\n\t\t\t\t");
                scanf("%d",&option);
                if(option==2)
                  break;
              }
              break;

      case 4: system("cls");
              header();
              SetColor(11);
              printf("\n\t\t\t\t\t\tVIEW ITEMS\n");
              view_cart();
              getch();
              break;


      case 5: system("cls");
              header();
              SetColor(11);
              printf("\n\t\t\t\t\t\tInvoice Memo\n");
              SetColor(8); printf("\n\tCustomer Name : "); SetColor(15); printf("%s",customer_name);
              SetColor(8); printf("\t\t\t\t\t\tPhone Number : "); SetColor(15); printf("%s\n",customer_phone);
              bill();
              break;

      case 6:exit(0);

      default: SetColor(4);
                printf("\t\tPlease enter an valid option\n");
                sleep(1);

    }
  }
  return 0;
}
