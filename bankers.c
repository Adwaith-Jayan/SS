#include <stdio.h>

int n,m;
int max[10][10];
int allocation[10][10];
int need[10][10];
int available[5];

void issafe()
{
   int safe=0;
   int seq[n];
   int k=0;
   int work[m];
   int flag[n];
   for(int i=0;i<n;i++)
      flag[i]=0;
   for(int i=0;i<m;i++)
      work[i]=available[i];
   printf("Need matrix\n");
   for(int i=0;i<n;i++)
     for(int j=0;j<m;j++)
        need[i][j]=max[i][j]-allocation[i][j];
   for(int i=0;i<n;i++)
   {
     for(int j=0;j<m;j++)
     {
        printf("%d  ",need[i][j]);
     }
     printf("\n");
   }

   int rem=n;
   while(rem>0)
   {
      for(int i=0;i<n;i++)
      {
         int possible=0;
         for(int j=0;j<m;j++)
         {
            if(need[i][j]<=work[j]  && flag[i]==0)
            {
               possible=1;
               work[j]+=allocation[i][j];
               flag[i]=1;
            }
            else
               break;
         }
         if(possible)
         {
            rem--;
            seq[k++]=i;
         }

      }
   }
   printf("It is in safe state\n");
   for(int i=0;i<n;i++)
      printf("P%d  ",seq[i]);
   printf("\n");
}
void main()
{
   printf("Enter the no of process: ");
   scanf("%d",&n);
   printf("Enter the no of resource types: ");
   scanf("%d",&m);
   printf("Enter the max required: \n");
   for(int i=0;i<n;i++)
      for(int j=0;j<m;j++)
         scanf("%d",&max[i][j]);
   printf("Enter the allocation matrix: \n");
   for(int i=0;i<n;i++)
      for(int j=0;j<m;j++)
         scanf("%d",&allocation[i][j]);
   printf("Enter availabe resource: ");
   for(int i=0;i<m;i++)
      scanf("%d",&available[i]);

   issafe();
}
