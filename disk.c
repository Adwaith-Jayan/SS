#include <stdio.h>
#include <stdlib.h>

int n,head,total;
int seq[10];

void FCFS()
{
   int thm=0;
   int current=head;
   for(int i=0;i<n;i++)
   {
      thm+=abs(current-seq[i]);
      current=seq[i];
   }
   printf("\nFCFS\n");
   printf("Total Head Movement=%d \n",thm);
   printf("HEAD MOVEMENT\n");
   printf("%d  ",head);
   for(int i=0;i<n;i++)
      printf("%d  ",seq[i]);
   printf("\n");
}

void sort(int a[])
{
   for(int i=0;i<n;i++)
     for(int j=0;j<n-i-1;j++)
     {
         if(a[j]>a[j+1])
         {
            int temp=a[j];
            a[j]=a[j+1];
            a[j+1]=temp;
         }
     }
}

int find(int a[])
{
   int i;
   for(i=0;i<n;i++)
   {
      if(a[i]>head)
         break;
   }
   return i;
}
void SCAN()
{
   int ch;
   int req[n];
   int thm=0;
   for(int i=0;i<n;i++)
      req[i]=seq[i];
   printf("1.Increasing Order\n");
   printf("2.Decreasing Order\n");
   printf("Enter choice: ");
   scanf("%d",&ch);
   if(ch==1)
   {
      sort(req);
      int index=find(req);
      int current=head;
      thm+=abs(head-(total-1));
      thm+=abs((total-1)-req[0]);
      printf("\nSCAN \n");
      printf("Total head Movement=%d\n",thm);

      printf("Head Movement\n");
      for(int i=index;i<n;i++)
         printf("%d  ",req[i]);
      for(int i=index-1;i>=0;i--)
         printf("%d  ",req[i]);
     printf("\n");
   }
   if(ch==2)
   {
      sort(req);
      int index=find(req);
      int current=head;
      thm+=head;
      thm+=abs(0-req[n-1]);
      printf("\nSCAN\n");
      printf("Total head Movement=%d\n",thm);

      printf("Head Movement\n");
      for(int i=index-1;i>=0;i--)
         printf("%d  ",req[i]);
      for(int i=index;i<n;i++)
         printf("%d  ",req[i]);
     printf("\n");
   }
}

void CSCAN()
{
   int ch;
   int req[n];
   int thm=0;
   int opt;
   for(int i=0;i<n;i++)
      req[i]=seq[i];
   printf("1.Increasing Order\n");
   printf("2.Decreasing Order\n");
   printf("Enter choice: ");
   scanf("%d",&opt);
   if(opt==1)
   {
      sort(req);
      int index=find(req);
      int current=head;
      thm=abs(head-(total-1));
      thm+=total-1;
      thm+=total-1-req[index];
      thm+=req[index-1];
      printf("\nCSCAN\n");
      printf("Head movement\n");
      for(int i=index;i<n;i++)
          printf("%d  ",req[i]);
      for(int i=0;i<index;i++)
          printf("%d  ",req[i]);
      printf("\n");
      printf("Total Head Movement=%d\n",thm);
   }
   if(opt==2)
   {
      sort(req);
      int index=find(req);
      int current=head;
      thm=abs(head);
      thm+=total-1;
      thm+=req[index];
      printf("\nCSCAN\n");
      printf("Head movement\n");
      for(int i=index-1;i>=0;i--)
          printf("%d  ",req[i]);
      for(int i=n-1;i>=index;i--)
          printf("%d  ",req[i]);
      printf("\n");
      printf("Total Head Movement=%d\n",thm);
   }

}
void main()
{
   int opt;
   printf("Enter no of disk cylinders: ");
   scanf("%d",&total);
   printf("Enter the no of disk queue elements: ");
   scanf("%d",&n);
   printf("Enter the request: ");
   for(int i=0;i<n;i++)
      scanf("%d",&seq[i]);
   printf("Enter the initial head postition: ");
   scanf("%d",&head);
   printf("1.FCFS \n2.SCAN \n3.C-SCAN \n4.Exit\n");
   do
   {
       printf("Enter choice: ");
       scanf("%d",&opt);
       switch(opt)
       {
          case 1:FCFS();
                 break;
          case 2:SCAN();
                 break;
          case 3:CSCAN();
                 break;
          case 4:break;
       }
   }while(opt!=4);
}
