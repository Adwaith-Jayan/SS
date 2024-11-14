
#include <stdio.h>
#include <string.h>


struct ProcessInfo
{
   char pid[5];
   int arrival_time;
   int burst_time;
   int priority;
   int rem;
};


struct Table
{
   char pid[5];
   int arrival_time;
   int burst_time;
   int completion_time;
   int turn_time;
   int waiting_time;
};

void display(struct Table t[],int n)
{
   printf("\nPID\t Arrival Time\t Burst Time\t Completion Time\t Turn Around Time\t Waiting Time\n");
   for(int i=0;i<n;i++)
   {
      printf("%s\t",t[i].pid);
      printf("%d\t\t\t",t[i].arrival_time);
      printf("%d\t\t\t",t[i].burst_time);
      printf("%d\t\t\t",t[i].completion_time);
      printf("%d\t\t\t",t[i].turn_time);
      printf("%d\n",t[i].waiting_time);
   }
   printf("\n");
}

void swap(struct ProcessInfo* a,struct ProcessInfo* b)
{
   struct ProcessInfo temp=*a;
   *a=*b;
   *b=temp;
}



void sort_fcfs(struct ProcessInfo p[],int n)
{
   for(int i=0;i<n;i++)
   {
      for(int j=0;j<n-i-1;j++)
      {
         if(p[j].arrival_time > p[j+1].arrival_time)
            swap(&p[j],&p[j+1]);
      }
   }
}

void FCFS()
{
   int n;
   printf("Enter no of proccess: ");
   scanf("%d",&n);
   struct ProcessInfo p[n];
   printf("Enter PID,Arrival Time,Burst Time\n");
   for(int i=0;i<n;i++)
   {
      printf("P[%d]:",i);
      scanf("%s",p[i].pid);
      scanf("%d",&p[i].arrival_time);
      scanf("%d",&p[i].burst_time);
   }
   sort_fcfs(p,n);
   struct Table fcfs[n];
   int systime=0;
   float avg_tt=0,avg_wt=0;
   for(int i=0;i<n;i++)
   {
      if(p[i].arrival_time <= systime)
      {
         strcpy(fcfs[i].pid,p[i].pid);
         fcfs[i].arrival_time=p[i].arrival_time;
         fcfs[i].burst_time=p[i].burst_time;
         fcfs[i].completion_time=fcfs[i].burst_time+systime;
         fcfs[i].turn_time=fcfs[i].completion_time - fcfs[i].arrival_time;
         fcfs[i].waiting_time= fcfs[i].turn_time - fcfs[i].burst_time;
         avg_tt+=fcfs[i].turn_time;
         avg_wt+=fcfs[i].waiting_time;
         systime+=fcfs[i].burst_time;
      }
   }
   printf("\n\n\tFCFS\n");
   display(fcfs,n);
   printf("Avg turn around time= %f\n",avg_tt/n);
   printf("Avg waiting Time= %f\n",avg_wt/n);
}

void sort_sjf(struct ProcessInfo a[],int n)
{
    for(int i=0;i<n;i++)
    {
       for(int j=0;j<n-i-1;j++)
       {
          if(a[j].burst_time > a[j+1].burst_time && a[j].arrival_time!=0)
             swap(&a[j],&a[j+1]);
       }
    }
}

void SJF()
{
   int n;
   printf("Enter no of proccess: ");
   scanf("%d",&n);
   struct ProcessInfo p[n];
   printf("Enter PID,Arrival Time,Burst Time\n");
   for(int i=0;i<n;i++)
   {
      printf("P[%d]:",i);
      scanf("%s",p[i].pid);
      scanf("%d",&p[i].arrival_time);
      scanf("%d",&p[i].burst_time);
   }
   struct Table t[n];
   int systime=0;
   float avg_tt=0,avg_wt=0;
   struct ProcessInfo sjf_sorted[n];
   for(int i=0;i<n;i++)
   {
      strcpy(sjf_sorted[i].pid,p[i].pid);
      sjf_sorted[i].arrival_time=p[i].arrival_time;
      sjf_sorted[i].burst_time=p[i].burst_time;
      sjf_sorted[i].priority=p[i].priority;
   }
   sort_sjf(sjf_sorted,n);
   for(int i=0;i<n;i++)
   {
      if(p[i].arrival_time <= systime)
      {
         strcpy(t[i].pid,sjf_sorted[i].pid);
         t[i].arrival_time=sjf_sorted[i].arrival_time;
         t[i].burst_time=sjf_sorted[i].burst_time;
         t[i].completion_time=t[i].burst_time+systime;
         t[i].turn_time=t[i].completion_time - t[i].arrival_time;
         t[i].waiting_time= t[i].turn_time - t[i].burst_time;
         avg_tt+=t[i].turn_time;
         avg_wt+=t[i].waiting_time;
         systime+=t[i].burst_time;
      }
   }
   printf("\n\n\tSJF\n");
   display(t,n);
   printf("Avg turn around time= %f\n",avg_tt/n);
   printf("Avg waiting Time= %f\n",avg_wt/n);
}


void priority_sort(struct ProcessInfo a[],int n)
{
   for(int i=0;i<n;i++)
   {
      for(int j=0;j<n-i-1;j++)
      {
         if(a[j].priority >= a[j+1].priority  && a[j].arrival_time >= a[j+1].arrival_time)
            swap(&a[j],&a[j+1]);
      }
    }
    printf("Sorted\n");
    for(int i=0;i<n;i++)
    {
        printf("%s\t",a[i].pid);
        printf("%d\t",a[i].arrival_time);
        printf("%d\n",a[i].priority);
    }

}


void Priority()
{
   int n;
   printf("Enter no of proccess: ");
   scanf("%d",&n);
   struct ProcessInfo p[n];
   printf("Enter PID,Arrival Time,Burst Time\n");
   for(int i=0;i<n;i++)
   {
      printf("P[%d]:",i);
      scanf("%s",p[i].pid);
      scanf("%d",&p[i].arrival_time);
      scanf("%d",&p[i].burst_time);
      scanf("%d",&p[i].priority);
   }
   int systime=0;
   struct ProcessInfo sorted[n];
   struct Table t[n];
   float avg_tt=0,avg_wt=0;
   for(int i=0;i<n;i++)
   {
      strcpy(sorted[i].pid,p[i].pid);
      sorted[i].arrival_time=p[i].arrival_time;
      sorted[i].burst_time=p[i].burst_time;
      sorted[i].priority=p[i].priority;
   }
   priority_sort(sorted,n);
   for(int i=0;i<n;i++)
   {
      if(p[i].arrival_time <= systime)
      {
         strcpy(t[i].pid,sorted[i].pid);
         t[i].arrival_time=sorted[i].arrival_time;
         t[i].burst_time=sorted[i].burst_time;
         t[i].completion_time=t[i].burst_time+systime;
         t[i].turn_time=t[i].completion_time - t[i].arrival_time;
         t[i].waiting_time= t[i].turn_time - t[i].burst_time;
         avg_tt+=t[i].turn_time;
         avg_wt+=t[i].waiting_time;
         systime+=t[i].burst_time;
      }
   }
   printf("\n\n\tPriority\n");
   display(t,n);
   printf("Avg turn around time= %f\n",avg_tt/n);
   printf("Avg waiting Time= %f\n",avg_wt/n);

}

void RoundRobin(){
        int total=0;
        int slice;
          int n;
   printf("Enter no of proccess: ");
   scanf("%d",&n);
   struct ProcessInfo p[n];
        printf("Enter PID,Arrival Time,Burst Time\n");
   for(int i=0;i<n;i++)
   {
      printf("P[%d]:",i);
      scanf("%s",p[i].pid);
      scanf("%d",&p[i].arrival_time);
      scanf("%d",&p[i].burst_time);
   }

        printf("Enter the time slice\n");
        scanf("%d",&slice);
         for(int i=0;i<n-1;i++){
                for(int j=0;j<n-i-1;j++){
                        if(p[j].arrival_time>p[j+1].arrival_time){
                                struct ProcessInfo temp=p[j];
                                p[j]=p[j+1];
                                p[j+1]=temp;
                        }
                }
        }
        int remain,time,flag;
        float avg_wt=0,avg_tt=0;
        for(int i=0;i<n;i++){
                p[i].rem=p[i].burst_time;
        }
        remain=n;
        int ready[30],count=0;
        printf("PID | At | Bt | COMP | TURN | WAIT\n");
        for(time=0,i=0;remain!=0;){
                if( p[i].rem<=slice && p[i].rem>0){
                        time+=p[i].rem;
                        p[i].rem=0;
                        flag=1;
                }
                else if(p[i].rem>0){
                        time=time+slice;
                        p[i].rem-=slice;
                }
                if(p[i].rem==0 && flag==1){
                        remain--;
                        flag=0;
                        avg_tt+=(time-p[i].at);
                        avg_wt+=(time-p[i].at-p[i].bt);
                        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arival_time,p[i].burst_time,time,(time-p[i].arrival_time),(time-p[i].arrival_time-p[i].burst_time));
                }
                int m=0;
                for(int j=0;j<n;j++){
                        if(p[j].arrival_time<=time && p[j].rem!=0){
                                ready[m++]=j;
                        }
                }
                if(m>0){
                        count=(count+1)%m;
                        i=ready[count];
                }
                else{
                        time++;
                }
        }
         printf("Avg waiting time=%f\nAvg turnaround time=%f\n",avg_wt/n,avg_tt/n);

}


/*void RoundRobin()
{
   int n;
   printf("Enter no of proccess: ");
   scanf("%d",&n);
   struct ProcessInfo p[n];
   printf("Enter PID,Arrival Time,Burst Time\n");
   for(int i=0;i<n;i++)
   {
      printf("P[%d]:",i);
      scanf("%s",p[i].pid);
      scanf("%d",&p[i].arrival_time);
      scanf("%d",&p[i].burst_time);
   }

   int rem=n;
   int quantum;
   int systime=0;
   float avg_tt=0,avg_wt=0;
   struct Table t[n];
   for(int i=0;i<n;i++)
   {
      strcpy(t[i].pid,p[i].pid);
      t[i].arrival_time=p[i].arrival_time;
      t[i].burst_time=p[i].burst_time;
   }
   printf("Enter Time Slice: ");
   scanf("%d",&quantum);
   while(rem>0)
   {
      for(int i=0;i<n;i++)
      {
         if(t[i].burst_time>0)
         {
            p[i].burst_time-=quantum;
            systime+=quantum;
            if(p[i].burst_time<=0)
            {
               t[i].completion_time=systime+quantum;
               t[i].turn_time=t[i].completion_time - t[i].arrival_time;
               t[i].waiting_time=t[i].turn_time - t[i].burst_time;
               rem--;
            }
          }
      }
   }
   for(int i=0;i<n;i++)
   {
      avg_tt+=t[i].turn_time;
      avg_wt+=t[i].waiting_time;
   }
   printf("\n\n\tRound Robin\n");
   display(t,n);
   printf("Avg turn around time= %f\n",avg_tt/n);
   printf("Avg waiting Time= %f\n",avg_wt/n);

}*/

void main()
{
    int opt;
    do
    {
       printf("1.FCFS\n2.SJF\n3.Priority\n4.Round Robin\n5.Exit\n");
       printf("Enter option: ");
       scanf("%d",&opt);
       switch(opt)
       {
          case 1:FCFS();
                 break;
          case 2:SJF();
                 break;
          case 3:Priority();
                 break;
          case 4:RoundRobin();
                 break;
          case 5:break;
       }
    }while(opt!=5);
}

