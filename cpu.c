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
22BR14613@linuxserver:~/S5/SS/ex1$ ls
1.c  a.out  bankers.c  cpu.c  CPU.c  disk.c  scheduling.c
22BR14613@linuxserver:~/S5/SS/ex1$ cd ..
22BR14613@linuxserver:~/S5/SS$ ls
ex1  ex2  ex3
22BR14613@linuxserver:~/S5/SS$ cd ex2
22BR14613@linuxserver:~/S5/SS/ex2$ ls
a.out  assmlist.txt  input.txt  length.txt  objectcode.txt  optab.txt  output.txt  pass1.c  pass2  symtab.txt  temp
22BR14613@linuxserver:~/S5/SS/ex2$ cd pass2/
22BR14613@linuxserver:~/S5/SS/ex2/pass2$ ls
a.out  assmlist.txt  input.txt  length.txt  objectcode.txt  optab.txt  output.txt  pass1.c  pass2.c  symtab.txt
22BR14613@linuxserver:~/S5/SS/ex2/pass2$ cat pass2.c
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char t1[20],t2[20],t3[20],t4[10],address[10],label[10],opcode[10],operand[10],length[10],size[10],a[10],ad[10],st_addr[10];
int s=-1,o=-1,i,j;

FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6;

struct SYNTAB
{
    char label[10];
    char addr[10];
} ST[30];

struct OPTAB
{
    char opcode[10];
    char hexcode[10];
} OT[30];

void read_optab()
{
    while(1)
    {
        o++;
        fscanf(fp3,"%s %s",OT[o].opcode,OT[o].hexcode);
        if (getc(fp3) == EOF)
        {
            break;
        }
    }
}

void read_symtab()
{
    while (1)
    {
        s++;
        fscanf(fp2, "%s %s", ST[s].label, ST[s].addr);
        if (getc(fp2) == EOF)
        {
            break;
        }
    }
}

void read_line()
{
    strcpy(t1,"");
    strcpy(t2,"");
    strcpy(t3,"");
    strcpy(t4,"");

    fscanf(fp1,"%s",t1);
    if (getc(fp1)!='\n')
    {
        fscanf(fp1,"%s",t2);
        if (getc(fp1)!='\n')
        {
            fscanf(fp1, "%s", t3);
            if (getc(fp1) != '\n')
            {
                fscanf(fp1, "%s", t4);
            }
        }
    }

    if (strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")!=0 && strcmp(t4,"") != 0)
    {
        strcpy(address, t1);
        strcpy(label, t2);
        strcpy(opcode, t3);
        strcpy(operand, t4);
    }
    else if (strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")!=0 && strcmp(t4,"")==0)
    {
        strcpy(address, t1);
        strcpy(label, "");
        strcpy(opcode, t2);
        strcpy(operand, t3);
    }
    else if (strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")==0 && strcmp(t4,"")==0)
    {
        if (strcmp(t1,"END")==0)
        {
            strcpy(address,"");
            strcpy(label,"");
            strcpy(opcode,t1);
            strcpy(operand,t2);
        }
        else
        {
            strcpy(address,t1);
            strcpy(label,"");
            strcpy(opcode,t2);
            strcpy(operand, "");
        }
    }
}

int main()
{
    fp1=fopen("output.txt", "r");
    fp2=fopen("symtab.txt", "r");
    fp3=fopen("optab.txt", "r");
    fp4=fopen("length.txt", "r");
    fp5=fopen("assmlist.txt", "w");
    fp6=fopen("objectcode.txt", "w");

    if (fp1==NULL||fp2==NULL||fp3==NULL||fp4==NULL||fp5==NULL||fp6==NULL)
    {
        printf("Error opening files\n");
        return 1;
    }

    fscanf(fp4,"%s\t%s\t",length,size);

    read_optab();
    read_symtab();

    fscanf(fp1,"%s\t%s\t%s\t",label,opcode,operand);
    strcpy(st_addr,operand);

    if (strcmp(opcode,"START")==0)
    {
        fprintf(fp5,"%s\t%s\t%s\t%s\n",address,label,opcode,operand);
        fprintf(fp6,"H^%s^00%s^0000%s\n",label,operand,length);
        fprintf(fp6,"T^00%s^F",operand);
        read_line();
    }

    while (strcmp(opcode,"END")!=0)
    {
        if (strcmp(opcode,"BYTE")==0)
        {
            if (operand[0]=='C')
            {
                fprintf(fp5,"%s\t%s\t%s\t%s\t",address,label,opcode,operand);
                for (i=2;operand[i]!='\'';i++)
                {
                    sprintf(ad,"%x",operand[i]);
                    fprintf(fp5,"%s",ad);
                    fprintf(fp6,"^%s",ad);
                }
                fprintf(fp5, "\n");
            }
            else if(operand[0] == 'X')
            {
                strncpy(ad,operand + 2,strlen(operand) - 3);
                fprintf(fp5,"%s\t%s\t%s\t%s\t%s\n",address,label,opcode,operand,ad);
                fprintf(fp6,"^%s",ad);
            }
        }
        else if(strcmp(opcode, "WORD")==0)
        {
            sprintf(a, "%06x", atoi(operand));
            fprintf(fp5, "%s\t%s\t%s\t%s\t%s\n", address, label, opcode, operand, a);
            fprintf(fp6, "^%s", a);
        }
        else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0)
        {
            fprintf(fp5, "%s\t%s\t%s\t%s\n", address, label, opcode, operand);
        }
	 else
        {
            i = 0;
            while (i <= o && strcmp(opcode, OT[i].opcode) != 0)
            {
                i++;
            }

            if (i > o)
            {
                printf("Error: Opcode %s not found in OPTAB\n", opcode);
            }
            else
            {
                j = 0;
                while (j <= s && strcmp(operand, ST[j].label) != 0)
                {
                    j++;
                }

                if (j > s)
                {
                    printf("Error: Operand %s not found in SYMTAB\n",operand);
                }
                else
                {
                    fprintf(fp5,"%s\t%s\t%s\t%s\t%s%s\n",address,label,opcode,operand,OT[i].hexcode,ST[j].addr);
                    fprintf(fp6,"^%s%s",OT[i].hexcode,ST[j].addr);
                }
            }
        }
        read_line();
    }

    fprintf(fp5,"%s\t%s\t%s\t%s\t%s\n","*",label,opcode,operand,"*");
    fprintf(fp6,"\nE^00%s\n",st_addr);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    fclose(fp6);

    return 0;
}

22BR14613@linuxserver:~/S5/SS/ex2/pass2$ ls
a.out  assmlist.txt  input.txt  length.txt  objectcode.txt  optab.txt  output.txt  pass1.c  pass2.c  symtab.txt
22BR14613@linuxserver:~/S5/SS/ex2/pass2$ cd ..
22BR14613@linuxserver:~/S5/SS/ex2$ ls
a.out  assmlist.txt  input.txt  length.txt  objectcode.txt  optab.txt  output.txt  pass1.c  pass2  symtab.txt  temp
22BR14613@linuxserver:~/S5/SS/ex2$ cd ..
22BR14613@linuxserver:~/S5/SS$ ls
ex1  ex2  ex3
22BR14613@linuxserver:~/S5/SS$ cd ex3
22BR14613@linuxserver:~/S5/SS/ex3$ ls
onepass  wrong
22BR14613@linuxserver:~/S5/SS/ex3$ cd onepass/
22BR14613@linuxserver:~/S5/SS/ex3/onepass$ ls
a.out  input.txt  onepass2.c  opcode.txt  output.txt  symtab.txt  wrong
22BR14613@linuxserver:~/S5/SS/ex3/onepass$ cat onepass2.c 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 10

int s = 0, i;
struct adr
{
    int addr;
    struct adr *next;
};

typedef struct
{
    char item[10];
    struct adr *link;
    int address;
} symbol;


struct adr *temps, *temps2;

symbol table[10];
void inittable()
{
    for (i = 0; i < 10; i++)
        strcpy(table[i].item, "");
}
int issymbolpresent(char *label)
{
    for (i = 0; i < 10; i++)
    {
    // printf("%d.",i);
        if (strcmp(table[i].item, label) == 0)
        {
            if (table[i].address == -1)
                return i; // address not present
            else
                return -1; // present
        }
    }
   // printf(";;");
    return -2; // not present
}

char *insertsymboladdress(char *label, int address)
{
    int f = 0;
    f = issymbolpresent(label);
    //printf("%d.",f);
    if (f == -2)
    {
        for (i = 0; i < 10; i++)
        {
            if (strcmp(table[i].item, "") == 0){
                f = i;
                break;
	    }
	printf("%d",i);
        }
        if (f != -2)
        {
            strcpy(table[f].item, label);
            table[f].address = address;
            table[f].link = NULL;
        }
    }
    else if (f != -1)
    {
        temps = table[f].link;
        table[f].address = address;
        char *mrecord = (char *)malloc(64);
        char from_address[10], to_address[10];
        sprintf(from_address, "%04x", address);

        mrecord[0] = '\0';
        while (temps != NULL)
        {
            strcat(mrecord, "T");
            sprintf(to_address, "%06x", temps->addr);
            strcat(mrecord, to_address);
            strcat(mrecord, "02");
            strcat(mrecord, from_address);
            strcat(mrecord, "\n");
            temps2 = temps;
            temps = temps->next;
            free(temps2);
        }
	//printf("mrcrd\n");
        return mrecord;
    }
    return NULL;
}

int addsymbol_no_address(char *label, int address)
{

    for (i = 0; i < 10; i++)
    {
        if (strcmp(table[i].item, "") == 0)
        {
            strcpy(table[i].item, label);
            table[i].address = -1;
            temps = (struct adr *)malloc(sizeof(struct adr));
            table[i].link = temps;
            temps->addr = address;
            temps->next = NULL;
            break;
        }
    }
    return (i != 10);
}

char *getconstant(char str1[])
{
    int p, i, l = strlen(str1);
    char *out = malloc(20), temp[5];
    out[0] = '\0';
    for (i = 2; i < l - 1; i++)
    {
        p = str1[i];
        sprintf(temp, "%x", p);
        strcat(out, temp);
    }
    return out;
}

char *getopcode(char opcode[])
{
    FILE *optable = fopen("opcode.txt", "r");
    char *value = malloc(10), code[10], line[20];
    while (fgets(line, sizeof(line), optable))
    {
        //printf("%s-- %s\n",line,opcode);
        sscanf(line, "%s %s", value, code);
        if (strcmp(code, opcode) == 0)
        {
            fclose(optable);
            return value;
        }
    }
    fclose(optable);
    return "ff";
}

int hex_int(char * num)
{
    int i, hex = 0,ln,val;
    ln = strlen(num);
    for(i=ln-1;i>=0;i--){
      if(num[i]>='0' && num[i]<='9')
	val = num[i]-'0';
      else if(num[i]>='a' && num[i]<='f')
        val = num[i]-87;
      else if(num[i]>='A' && num[i]<='F')
	val = num[i]-55;
      hex += (pow((double)16, (double)ln-i-1)) * val;
      //printf("%d,  %c\n",hex,num[i]);
    }
    return hex;
}

void onepass(FILE *input, FILE *output)
{
    inittable();
    char line[64], label[10], operand[10], opcode[10];
    char str1[10], str2[10], str3[10], locctr_str[10], start_str[10], tempstr[10];
    char text[64], header[20], end[10], object[10];
    int start, locctr, f, i, cnt = 0, flag = 0;
    char file[1024], *mrecord;
    file[0] = '\0';
    strcpy(header, "H");
    strcpy(label, "NONAME");
    fgets(line, sizeof(line), input);
    str3[0] = '\0';
    sscanf(line, " %s %s %s ", str1, str2, str3);
    if (str3[0] == '\0')
    {
        strcpy(opcode, str1);
        strcpy(operand, str2);
    }
    else
    {
        strcpy(label, str1);
        strcpy(opcode, str2);
        strcpy(operand, str3);
    }
    if (strcmp(opcode, "START") == 0)
    {
        start = hex_int(operand);
        locctr = start;
        strcpy(start_str, operand);
        sprintf(tempstr, "%06x", start);
        fgets(line, sizeof(line), input);
        strcat(header, label);
        strcat(header, tempstr);
    }
    else
        start = locctr = 0;

    strcpy(text, "T");
    strcat(text, tempstr);
    strcat(text, "00");
    strcpy(end, "E");
    strcat(end, tempstr);

    //printf("pass 1 do function\n");
    do
    {
        str3[0] = '\0';
        sscanf(line, " %s %s %s ", str1, str2, str3);
        if (strcmp(".", str1) == 0)
            continue;
        if (str3[0] == '\0')
        {   //printf("<>");
            strcpy(opcode, str1);
            strcpy(operand, str2);
            strcpy(label, "\t");
        }
        else
        {
            strcpy(label, str1);
            strcpy(opcode, str2);
            strcpy(operand, str3);
            int f = issymbolpresent(label);
            //printf("*");
            if (f == -1)
            {
                printf("Symbol already exist : [%s]\n", label);
                break;
            }
            else
            {
		//printf("%s",label);
                mrecord = insertsymboladdress(label, locctr);
                if (mrecord != NULL)
                {
                    flag = 1;
                }
            }
        }
	//printf("--\n");
        if (strcmp(opcode, "END") == 0)
        {
            //fprintf(output, "\t\tEND\t%s\n", start_str);
            break;
        }
        sprintf(locctr_str, "%X", locctr);
        // fprintf(output, "%s\t%s\t%s\t%s\n", locctr_str, str1, str2, str3);
        char op_num[3];
        strcpy(op_num, getopcode(opcode));

        if (strcmp(op_num, "ff") != 0)
        {
            strcpy(object, op_num);
            f = issymbolpresent(operand);
            if (f == -2)
            {
                addsymbol_no_address(operand, locctr + 1);
                strcat(object, "0000");
            }
            else if (f == -1)
            {
                for (i = 0; i < 10; i++)
                {
                    if (strcmp(table[i].item, operand) == 0)
                    {
                        sprintf(tempstr, "%06x", table[i].address);
                        strcat(object, tempstr);
                        break;
                    }
                }
            }
            if (f > -1)
            {
                strcat(object, "0000");
                temps = (struct adr *)malloc(sizeof(struct adr));
                temps2 = table[f].link;
                while (temps2->next != NULL)
                {
                    temps2 = temps2->next;
                }
                temps2->next = temps;
                temps->addr = locctr + 1;
                temps->next = NULL;
            }
            //strcat(text, object);
            cnt += 3;
	    if (cnt >= 60)
                {
                    sprintf(tempstr, "%02x", cnt);
                    text[7] = tempstr[0];
                    text[8] = tempstr[1];
                   // printf("[%s]\n", text);
                    strcat(file, text);
                    sprintf(tempstr, "%06x", locctr);
                    strcpy(text, "T");
                    strcat(text, tempstr);
                    strcat(text, "00");
                    cnt = 0;
                }
            locctr += 3;
            strcat(text, object);

        }

        else
        {
            if (strcmp(opcode, "WORD") == 0)
            {
                sprintf(tempstr, "%06d", atoi(operand));
                strcpy(object, tempstr);
                line[strlen(line) - 1] = '\0';
                cnt += 3;
		if (cnt >= 60)
                {
                    sprintf(tempstr, "%02x", cnt);
                    text[7] = tempstr[0];
                    text[8] = tempstr[1];
                   // printf("[%s]\n", text);
                    strcat(file, text);
		    sprintf(tempstr, "%06x", locctr);
                    strcpy(text, "T");
                    strcat(text, tempstr);
                    strcat(text, "00");
                    cnt = 0;
                }
                strcat(text, object);
                locctr += 3;
            }
            else if (strcmp(opcode, "RESW") == 0)
            {
                locctr += atoi(operand) * 3;
            }
            else if (strcmp(opcode, "RESB") == 0)
            {
                locctr += atoi(operand);
            }
            else if (strcmp(opcode, "BYTE") == 0)
            {
                int len = strlen(getconstant(operand));
                if (cnt + len >= 60)
                {
                    sprintf(tempstr, "%02x", cnt);
                    text[7] = tempstr[0];
                    text[8] = tempstr[1];
                   // printf("[%s]\n", text);
                    strcat(file, text);
                    strcpy(text, "T");
                    strcat(text, str1);
                    strcat(text, "00");
                    locctr += len / 2;
                    cnt = 0;
                }
                else
                {
                    strcat(text, getconstant(operand));
                    cnt += len;
                }
            }

            else
            {
                printf("FATAL ERROR!!");
                exit(0);
            }
        }
        if (flag)
        {
            //printf("%s", mrecord);
            if (cnt > 0)
            {
                sprintf(tempstr, "%02x", cnt);
                text[7] = tempstr[0];
                text[8] = tempstr[1];
                strcat(file, text);
                strcat(file, "\n");
                cnt = 0;
            }
            strcat(file, mrecord);
            sprintf(locctr_str, "%06x", locctr);
            strcpy(text, "T");
            strcat(text, locctr_str);
            strcat(text, "00");
            flag = 0;
        }
    } while (fgets(line, sizeof(line), input));
    printf("Total length : %d\n", locctr - start);
    if (cnt > 0)
    {
        sprintf(tempstr, "%02x", cnt);
        text[7] = tempstr[0];
        text[8] = tempstr[1];
        strcat(file, text);
        strcat(file, " ab \n");
        cnt = 0;
    }
    sprintf(tempstr, "%06x\n", locctr - start);
    strcat(header, tempstr);
    printf("%s", header);
    printf("%s", file);
    printf("%s\n", end);

    fprintf(output, "%s%s%s\n", header, file, end);

}

int main()
{
    FILE *input, *output, *symtable;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    onepass(input, output);
    fclose(input);
    fclose(output);
    char str[10];
    int i;
    // for (i = 0; i < 10; i++)
    // {
    //     printf("%s  --  %d\n", table[i].item, table[i].address);
    // }
    return 0;
}
22BR14613@linuxserver:~/S5/SS/ex3/onepass$ ls
a.out  input.txt  onepass2.c  opcode.txt  output.txt  symtab.txt  wrong
22BR14613@linuxserver:~/S5/SS/ex3/onepass$ cd ..
22BR14613@linuxserver:~/S5/SS/ex3$ ls
onepass  wrong
22BR14613@linuxserver:~/S5/SS/ex3$ cd ..
22BR14613@linuxserver:~/S5/SS$ ls
ex1  ex2  ex3
22BR14613@linuxserver:~/S5/SS$ cd ex1
22BR14613@linuxserver:~/S5/SS/ex1$ ls
1.c  a.out  bankers.c  cpu.c  CPU.c  disk.c  scheduling.c
22BR14613@linuxserver:~/S5/SS/ex1$ cat cpu.c 
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

