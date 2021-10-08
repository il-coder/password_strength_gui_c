#include<stdio.h>
#include<string.h>
#include<stdlib.h>

static char commonPassword[28][15]={"password","Password","guest","hello","user","12345678","1234567890","012345678","123456","username","0123456","01234567","1234567","123456789","abcd1234","qwerty","111111","abc123","password1","iloveyou","dragon","monkey","123123","qwertyuiop","666666","1234"};

static char ans[400]="Remarks : ";
static char s[4][100]={"\r\nNo Numbers in given password","\r\nNo Symbols in given password","\r\nNo Small Case Letter in given passsword","\r\nNo Capital Case Letter in given password"};
    static char s1[4][100]={"\r\nPerfect Numbers in given password","\r\nPerfect Symbols in given password","\r\nPerfect Small Case Letter in given passsword","\r\nPerfect Capital Case Letter in given password"};
    static char s2[4][100]={"\r\nSufficient Numbers in given password","\r\nSufficient Symbols in given password","\r\nSufficient Small Case Letter in given passsword","\r\nSufficient Capital Case Letter in given password"};
    static char s3[4][100]={"\r\nExcess Numbers in given password","\r\nExcess Symbols in given password","\r\nExcess Small Case Letter in given passsword","\r\nExcess Capital Case Letter in given password"};
    static char str[550]="Strength : ";


void perform(char *pass)
{
    int len=0,nn=0,ns=0,nsl=0,ncl=0,strength=0,flag=0,flag1=0,p[4];
    strcpy(str,"Strength : ");
    strcpy(ans,"Remarks : ");
    for(int i=0;i<26;i++)
    {
        if(strcmp(pass,&commonPassword[i][0])==0 || strcmp(pass,strupr(&commonPassword[i][0]))==0 || strcmp(pass,strlwr(&commonPassword[i][0]))==0 || strcmp(pass,strrev(&commonPassword[i][0]))==0)
        {
            flag=1;
            flag1=1;
            break;
        }
    }

    if(flag1==0)
    {
        for(int i=0;pass[i]!='\0';i++)
        {
            flag=1;
            char temp=pass[0];
            if(pass[i]!=temp)
            {
                flag=0;
                break;
            }
        }
    }

    if(flag==1)
    {
            strcat(ans,"\r\nVery Commonly used password.");
            strength=0;
    }
    else if(flag==0)
    {
        len=strlen(pass);
        for(int i=0;pass[i]!='\0';i++)
        {
            if(pass[i]>=48 && pass[i]<=57)
            {
                nn++;
            }
            if( (pass[i]>=32 && pass[i]<=47) || (pass[i]>=58 && pass[i]<=64) || (pass[i]>=91 && pass[i]<=96) || (pass[i]>=123 && pass[i]<=126) )
            {
                ns++;
            }
            if(pass[i]>=97 && pass[i]<=122)
            {
                nsl++;
            }
            if(pass[i]>=65 && pass[i]<=90)
            {
                ncl++;
            }
        }

        if(len<8)
            {
                strength -= 3;
                strcat(ans,"\r\nBad length");
            }
        else if (len>=8 && len<10)
            {
                strength += 1;
                strcat(ans,"\r\nSufficient Length");
            }
        else if (len>=10 && len<12)
            {
                strength += 3;
                strcat(ans,"\r\nGood length");
            }
        else if (len>=12 && len<15)
            {
                strength += 6;
                strcat(ans,"\r\nAlmost best length");
            }
        else if (len>=15)
            {
                strength += 8;
                strcat(ans,"\r\nBest length");
            }

        p[0] = (nn*100)/len;
        p[1] = (ns*100)/len;
        p[2] = (nsl*100)/len;
        p[3] = (ncl*100)/len;
        for(int i=0;i<4;i++)
        {
            if(p[i]==0)
            {
                strength -= 2;
                strcat(ans,s[i]);
            }
            else if(p[i]>=25 && p[i]<=35)
            {
                strength += 2;
                strcat(ans,s1[i]);
            }
            else if(p[i]>35)
            {
                strength += 1;
                strcat(ans,s3[i]);
            }
            else
            {
                strength += 1;
                strcat(ans,s2[i]);
            }
        }
    }
    if(strength<3)
        strcat(str,"Very Weak Password\r\n\r\n");
    else if(strength>=3 && strength<6)
        strcat(str,"Weak Password\r\n\r\n");
    else if(strength>=6 && strength<=8)
        strcat(str,"Average Password\r\n\r\n");
    else if(strength>8 && strength<=10)
        strcat(str,"Strong Password\r\n\r\n");
    else if(strength>10)
        strcat(str,"Very Strong Password\r\n\r\n");
    strcat(str,ans);
}
