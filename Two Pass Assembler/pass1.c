// Implementing Pass1 Algorithm of two pass assembler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SearchSymbol(char* symb,FILE *f)
{
   rewind(f);
   int found=0;
   char line[100];
   char label[50];
   char value[50];
   while(fgets(line,sizeof(line),f))
   {
       sscanf(line,"%s %s",label,value);
       if(strcmp(symb,label)==0)
       {
          found=1;
          break;
       }
   }
   if(found)
       return 1;
   return 0;
}


int SearchOP(char* opcode)
{
   FILE* f;
   f=fopen("optab.txt","r");
   int found=0;
   char line[100];
   char op[50];
   char value[50];
   while(fgets(line,sizeof(line),f))
   {
      sscanf(line,"%s %s",op,value);
      if(strcmp(opcode,op)==0)
      {
         found=1;
         break;
      }
      else if(strcmp(opcode,"RESW")==0)
      {
         found=1;
         break;
      }
      else if (strcmp(opcode,"WORD")==0)
      {
         found=1;
         break;
      }
      else if(strcmp(opcode,"BYTE")==0)
      {
         found=1;
          break;
      }
      else if(strcmp(opcode,"RESB")==0)
      {
         found=1;
         break;
      }
   }
   fclose(f);
   if(found)
      return 1;
   return 0;
}



void main()
{
   FILE* f1,*f2,*f3,*f4,*f6,*f5;
   f1=fopen("input.txt","r");
   f2=fopen("optab.txt","r");
   f3=fopen("symtab.txt","w+");
   f4=fopen("intermediatefile.txt","w");
   f5=fopen("littab.txt","w");
   f6=fopen("length.txt","w");

   int start,length;
   int symbol_error=0,op_error=0;
   int locctr=0x0;
   char label[50],opcode[50],operand[50];
   char line[150];
   char pgm[40];

   sscanf(fgets(line,sizeof(line),f1),"%s %s %s",label,opcode,operand);
   strcpy(pgm,label);
   fprintf(f4,"*\t%s\t%s\t%s\n",label,opcode,operand);
   if(strcmp(opcode,"START")==0)
      start=strtol(operand,NULL,16);
   locctr+=start;
   sscanf(fgets(line,sizeof(line),f1),"%s %s %s",label,opcode,operand);
   while(strcmp(opcode,"END")!=0)
   {
      if(strcmp(label,"*")!=0)
      {
         if(SearchSymbol(label,f3))
         {
            symbol_error=1;
            break;
         }
         else
         {
            fprintf(f3,"%s\t%X\n",label,locctr);
         }
      }
      if(opcode[0]=='=')
          fprintf(f5,"%s\t%X\t%ld\n",opcode,locctr,strlen(opcode)-3);
      if(SearchOP(opcode)==0)
         op_error=1;
      if(strcmp(label,"*")==0)
      {
         fprintf(f4,"%X\t*\t%s\t%s\n",locctr,opcode,operand);
      }
      else
      {
         fprintf(f4,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
      }
      if(strcmp(opcode,"RESW")==0)
      {
           locctr+=0x3 * strtol(operand,NULL,16);
      }
      else if(strcmp(opcode,"RESB")==0)
          locctr+=strtol(operand,NULL,16);

      else
          locctr+=0x3;
      sscanf(fgets(line,sizeof(line),f1),"%s %s %s",label,opcode,operand);
   }
   fprintf(f4,"*\t*\t%s\t%X\n",opcode,start);

   fclose(f1);
   fclose(f2);
   fclose(f3);
   fclose(f4);
   if(symbol_error)
      printf("Error: Duplicate Symbol\n");
   else if(op_error)
       printf("Error: Ivalid OPCODE\n");
   else
   {
       length=locctr-start;
       fprintf(f6,"%X\n",length);
       printf("Length= %X\n",length);
       f1=fopen("intermediatefile.txt","r");
       f2=fopen("symtab.txt","r");
       printf("Intermediate File\n");
       char l[100];
       while(fgets(l,sizeof(l),f1))
          printf("%s",l);
       printf("\nSymbol Table\n");
       while(fgets(l,sizeof(l),f2))
          printf("%s",l);
   fclose(f1);
   fclose(f2);
   }
   fclose(f5);
   fclose(f6);
}
