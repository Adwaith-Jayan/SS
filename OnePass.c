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
