#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
COORD coord={0,0};

 void gotoxy(int x,int y)
 {
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
struct subscriber
{
char phonenumber[20];
char name[50];
float amount,data,call,sms;
}s;
void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();
int main()
{
    char password[30],po[30];
	char choice;
system("color E0");


	system("cls");

	gotoxy(34,15);
	printf("WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM");

	Sleep(2000);
	getch();
    system("cls");
    char j[]="32321212";
    int x;

    do
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\t\t\t\tBACKSPACE WILL WORK BUT NOT SHOWS\n");
    	printf("\t\t\t\tpassword :");
        int p=0;
        do
	    {
        	po[p]=getch();
        	if(po[p]=='\b')
        	{
				p=p-2;
       		}
        	else
        	{
      			password[p]=po[p];
  			}

        	if(password[p]!='\r')
           	{
		    	printf("*");
           	}
        	p++;
        }while(password[p-1]!='\r');
		password[p-1]='\0';
		x = strcmp(password,j);
if(x!=0)
{
    printf("\nInvalid Password");
    getch();
}
    }while(!(x==0));



if(x==0)
{
	printf("\nLOGIN SUCCESSFULL\n\n\n");
	printf("PRESS ANY KEY TO CONTINUE");
getchar();
}

	while (1)
	{
		system("cls");
        gotoxy(30,12);
		printf("A : For adding new records.");
		gotoxy(30,13);
		printf("L : For list of records.");
		gotoxy(30,14);
		printf("M : For modifying records.");
		gotoxy(30,15);
		printf("P : For payment.");
		gotoxy(30,16);
		printf("S : For searching records.");
		gotoxy(30,17);
		printf("D : For deleting records.");
		gotoxy(30,18);
		printf("E : For exit.");
		gotoxy(30,20);
		printf("Your's Choice:");
		choice=getch();
		choice=toupper(choice);
		switch(choice)
		{
			case 'P':
				payment();break;
			case 'A':
				addrecords();break;
			case 'L':
				listrecords();break;
			case 'M':
				modifyrecords();break;
			case 'S':
				searchrecords();break;
			case 'D':
				deleterecords();break;
			case 'E':
				system("cls");
				gotoxy(52,12);
				printf("THANK YOU");
				gotoxy(46,15);
				printf("FOR USING OUR SERVICE");
				Sleep(2000);
				exit(0);
				break;
			default:
				system("cls");
				gotoxy(50,12);
				printf("Incorrect Input");
				gotoxy(48,15);
				printf("Any key to continue");
				getch();
		}
	}
}
void addrecords()
{
	FILE *f;
	char test,p[20];
	int i;
	while(1)
	{

		do
        {
            i=0;
            f=fopen("f.DAT","ab+");
            fseek(f,0,SEEK_SET);
          		system("cls");
		printf("\n\t\t================================\n\t\t\tADD RECORDS\n\t\t================================");
        printf("\nEnter phone number:");
		scanf("%s",&p);
		while(fread(&s,sizeof(s),1,f)==1)
        {
            if(strcmp(s.phonenumber,p)==0)
            {
              i=1;
              printf("Phonenumber is already present in Database");
              getch();
            }
            }

        }while(i==1);
        strcpy(s.phonenumber,p);
		printf("Enter name:");
		fflush(stdin);
		scanf("%[^\n]",&s.name);
		printf("Enter Data used (In Gb):");
		scanf("%f",&s.data);
		printf("Enter Total Hour of Talking:");
		scanf("%f",&s.call);
		printf("Enter Total SMS Send :");
		scanf("%f",&s.sms);
		s.amount=s.data*5+s.sms*1+s.call*10;
		fseek(f,0,SEEK_END);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		printf("1 record successfully added");
		printf("\n Press esc key to exit, any other key to add other record:");
		fclose(f);
		test=getche();
		if(test==27)
			break;

	}

}
void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("f.DAT","rb"))==NULL)
		exit(0);
	system("cls");
	printf("\n\t\t================================\n\t\t\tLIST OF RECORDS\n\t\t================================");
	printf("\nPhone Number\t\tUser Name\t\t\tCall Hour\tData used\tSMS SEND\tTotal Amount\n");
	for(i=0;i<120;i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\t%.2f hour   \t%.2f Gb   \t%.0f   \t\tRs. %.2f /-",s.phonenumber,s.name,s.call,s.data,s.sms,s.amount);
	}
	printf("\n");
	for(i=0;i<120;i++)
		printf("-");

fclose(f);
getch();
}
void deleterecords()
{
	FILE *f,*t;
	int i=1,flag=1;
	char phonenumber[20];
	if((t=fopen("t.DAT","w+"))==NULL)
	exit(0);
	if((f=fopen("f.DAT","rb"))==NULL)
	exit(0);
	rewind(f);
	system("cls");
	printf("\n\t\t================================\n\t\t\tDELETE RECORDS\n\t\t================================");
	printf("\nEnter the phone number to be deleted from the Database:");
	fflush(stdin);
	scanf("%[^\n]",phonenumber);
    while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)!=0)
		{
fwrite(&s,sizeof(s),1,t);

			}
			if(strcmp(s.phonenumber,phonenumber)==0)
			flag=0;

			}
    fclose(f);
	fclose(t);
	remove("f.DAT");
	rename("t.DAT","f.DAT");
if(flag==0){
	system("cls");
	printf("The Number %s Successfully Deleted!!!!",phonenumber);
	getch();
}
else{

	system("cls");
    printf("Number is Not Found in our Database");
getch();
}
}
void searchrecords()
{
	FILE *f;
	char phonenumber[20];
	int flag=1;
	f=fopen("f.DAT","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("cls");
	printf("\n\t\t================================\n\t\t\tSEARCH RECORDS\n\t\t================================");
	printf("\nEnter Phone Number to search in our database:");
	scanf("%s", phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{	system("cls");
			printf(" Record Found ");
			printf("\n\nPhonenumber: %s\nName: %s\nData Used: %0.2f Gb\nCall Hour: %0.2f Hour\nSMS send: %.0f\nAmount: Rs.%0.2f",s.phonenumber,s.name,s.data,s.call,s.sms,s.amount);
			flag=0;
			break;
		}
		}
			if(flag==1)
    {
    printf("Number is Not Found in our Database");
        getch();
    }
    getch();
	fclose(f);
}
void modifyrecords()
{
	FILE *f;
	char phonenumber[20],ch;
	int flag=0;
	long int size=sizeof(s);
	if((f=fopen("f.DAT","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("\n\t\t================================\n\t\t\tMODIFY RECORDS\n\t\t================================");
	printf("\nEnter phone number of the subscriber to modify:");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
		    while(1)
            {
                system("cls");
            printf("Enter The Choice Which You Want To Modify\n");
		    printf("P: Phonenumber\n");
		    printf("N: Name\n");
		    printf("C: Call Hour\n");
		    printf("D: Data Used\n");
		    printf("S: SMS Used\n");
		    printf("E: Exit From Modifing Reacord\n");
		    printf("YOUR CHOICE");
		    ch=getch();
		ch=toupper(ch);
		system("cls");
		switch(ch)
		{
    case 'P':
        printf("\n Enter modified phone number:");
			scanf("%s",&s.phonenumber);
			break;
    case 'N':
        printf("\n Enter modified name: ");
			fflush(stdin);
			scanf("%[^\n]",&s.name);
			break;
    case 'C':
        printf("\n Enter modified Call Hour: ");
			scanf("%f",&s.call);
			break;
    case 'D':
        printf("\n Enter modified Data used: ");
			scanf("%f",&s.data);
			break;
    case 'S':
            printf("\n Enter modified SMS send: ");
			scanf("%f",&s.sms);
			break;
			}
			if(ch=='E')
                break;
            }
            label:
			s.amount=s.data*5+s.sms*1+s.call*10;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			printf("\n Data is Modified Successfully");
			getch();
			flag=1;
			break;
		}
		}
	if(flag==0)
    {
    printf("Number is Not Found in our Database");
        getch();
    }
	fclose(f);
}
void payment()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	float amt;
	int i,flag=0;
	if((f=fopen("f.DAT","rb+"))==NULL)
		exit(0);
	system("cls");
	fflush(stdin);
	printf("\n\t\t================================\n\t\t\tPAYMENT\n\t\t================================");
	printf("\nEnter phone number of the subscriber for payment:");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("cls");
			printf("\n\t\t================================\n\t\t\tPAYMENT\n\t\t================================");
			printf("\n Phone No.: %s",s.phonenumber);
			printf("\n Name: %s",s.name);
			printf("\n Current amount: %f",s.amount);
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\nEnter amount of payment :");
			fflush(stdin);
			scanf(" %f",&amt);
			s.amount=s.amount-amt;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			system("cls");
	printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
	flag=1;
			break;
		}

	}
		if(flag==0)
    {
    printf("Number is Not Found in our Database");
        getch();
    }
	fclose(f);
}
