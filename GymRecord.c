#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

//DEFINING THE FUNCTIONS
void display();
void add();
void search();
void modify();
void delete ();
void searchbyname();
void searchbymemid();
void searchbyphone();
void menu();

//Defining structure
struct gym
{
    int memid;
    char name[30];
    int age;
    char gender[10];
    int wegiht;
    char phone[30];
    char mail[30];

} s;

FILE *fp;
long sizeS = sizeof(s);

void gotoxy(int x, int y)
{
    //FUNCTION TO PLACE THE CURSOR AT THE SPECIFIED (X,Y) POSITION
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main()
{

    // MAKING PASSWORD LOGIN WITH 3 ATTEMPTS
    int i = 0, count = 0, countdown = 3;
    char pwd[30], ch;

    {
        system("cls");
        gotoxy(25, 2);
        printf("Welcome Nihal Phukan!");
        gotoxy(25, 4);
        printf("Enter the password : ");
    start:
        for (i = 0; i < 30; i++)
        {
            ch = getch();
            if (ch != 13)
            {
                pwd[i] = ch;
                printf("*");
            }
            else
            {
                break;
            }
        }
        pwd[i] = 0;

        printf("\n\n");
        if (strcmp(pwd, "password") == 0)
        {
            system("cls");
            printf("\n\n*** Log In Successful! ***");
            printf("\n\nPress any key to continue.......");
            getch();
            menu();
        }
        else
        {
            count++;
            if (count < 4)
            {
                system("cls");
                printf("\n\n\nINCORRECT PASSWORD!\n\n");
                printf("You have %d try remaining\n", countdown);
                printf("\nEnter the password: ");
                countdown--;
                goto start;
            }
            else
            {
                system("cls");
                printf("No more tries remaining!\n\n");
                printf("THE PROGRAM WILL NOW SHUT DOWN......");
                getch();
                exit(0);
            }
        }
    }
    return 0;
}

void menu()
{
    //MENU OF DIFFERENT OPERATIONS THAT CAN BE PERFORMED
    int choice;
    system("cls");
    gotoxy(15, 1);
    while (1)
    {
        system("cls");
        printf("\n***** GYM RECORD MANAGEMENT SYSTEM *****\n\n");
        printf("\t1. DISPLAY RECORDS\n\n\t2. ADD RECORD\n\n\t3. SEARCH RECORD\n\n\t4. MODIFY RECORD\n\n\t5. DELETE RECORD\n\n\t6. EXIT DATABASE\n\n\n");
        printf("Choose your option : ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            display();
            break;
        case 2:
            add();
            break;
        case 3:
            search();
            break;
        case 4:
            modify();
            break;
        case 5:
            delete ();
            break;
        case 6:
            system("cls");
            exit(0);
        default:
        {
            system("cls");
            printf("\n\nINVALID CHOICE!");
            printf("\nPress any key to go back........");
            getch();
        }
        }
    }
}

//Different menu operations

void display()
{
    system("cls");
    gotoxy(50, 2);
    printf("**** GYM MEMBER RECORDS ****\n\n");
    printf("%-15s %-30s %-15s %-15s %-15s %-15s %s\n", "MemberID", "Name", "Age", "Gender", "Weight", "PhoneNo", "Email ID");

    fp = fopen("gym.txt", "rb");
    while (fread(&s, sizeS, 1, fp) == 1)
    {
        printf("%-15d %-30s %-15d %-15s %-15d %-15s %s\n", s.memid, s.name, s.age, s.gender, s.wegiht, s.phone, s.mail);
    }
    gotoxy(0, 20);
    printf("Press any key to go back.......");
    getch();
    fclose(fp);
}
void add()
{
    system("cls");
    gotoxy(20, 2);
    printf("< == ADD MEMBER INFORMATION == >\n\n");
    fp = fopen("gym.txt", "ab");

    printf("Enter the memberID: ");
    scanf("%d", &s.memid);
    printf("\nEnter the name: ");
    fflush(stdin);
    gets(s.name);
    printf("\nEnter the age: ");
    scanf("%d", &s.age);
    printf("\nEnter the gender: ");
    fflush(stdin);
    gets(s.gender);
    printf("\nEnter the weight: ");
    scanf("%d", &s.wegiht);
    printf("\nEnter the phone number: ");
    fflush(stdin);
    gets(s.phone);
    printf("\nEnter the email id: ");
    fflush(stdin);
    gets(s.mail);
    system("cls");

    fwrite(&s, sizeS, 1, fp);
    printf("\n\nRecord Saved Succesfully....");
    gotoxy(0, 20);
    printf("Press any key to go back.......");
    getch();
    fclose(fp);
}
void search()
{
    int choice;
    while (1)
    {
        system("cls");
        gotoxy(20, 2);
        printf("< == SEARCH == >\n\n");
        printf("1. Search by Name\n2. Search by Member ID\n3. Search by Phone number\n4. Back");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            searchbyname();
            break;
        case 2:
            searchbymemid();
            break;
        case 3:
            searchbyphone();
            break;
        case 4:
            menu();
            break;
        default:
        {
            system("cls");
            printf("\n\nINVALID CHOICE!");
            gotoxy(0, 18);
            printf("\nPress any key to go back........");
            getch();
            search();
        }
        }
    }
}
void modify()
{
    system("cls");
    int id, temp = 0, choice;
    char name[30];
    gotoxy(20, 2);
    printf("< == MODIFY == >");
    printf("\n\n1. Modify using Member ID\n2. Modify using Name\n3. Back");
    printf("\n\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        system("cls");
        fp = fopen("gym.txt", "rb+");
        printf("Enter Member ID: ");
        scanf("%d", &id);

        while (fread(&s, sizeS, 1, fp) == 1)
        {

            if (id == s.memid)
            {
                system("cls");
                printf("\nRECORD FOUND!");
                temp = 1;
                printf("\n\nEnter the updated memberID: ");
                scanf("%d", &s.memid);
                printf("\nEnter the updated name: ");
                fflush(stdin);
                gets(s.name);
                printf("\nEnter the updated age: ");
                scanf("%d", &s.age);
                printf("\nEnter the updated gender: ");
                fflush(stdin);
                gets(s.gender);
                printf("\nEnter the updated weight: ");
                scanf("%d", &s.wegiht);
                printf("\nEnter the updated phone number: ");
                fflush(stdin);
                gets(s.phone);
                printf("\nEnter the updated email id: ");
                fflush(stdin);
                gets(s.mail);
                fseek(fp, -sizeS, 1);
                fwrite(&s, sizeS, 1, fp);
                fclose(fp);
                system("cls");
                
            }
        }

        if (temp == 0)
        {
            system("cls");
            printf("\nRecord not found!");
            gotoxy(0, 20);
            printf("Press any key to go back......");
            getch();
            modify();
        }
        else
        {
            printf("Record updated succesfully!");
            gotoxy(0, 20);
            printf("Press any key to go back......");
            getch();
            modify();
        }
        break;

    case 2:
        system("cls");
        fp = fopen("gym.txt", "rb+");
        printf("Enter the name: ");
        fflush(stdin);
        gets(name);

        while (fread(&s, sizeS, 1, fp) == 1)
        {
            if (strcmpi(name, s.name) == 0)
            {
                system("cls");
                printf("\nRECORD FOUND!");
                temp = 1;
                printf("\n\nEnter the updated memberID: ");
                scanf("%d", &s.memid);
                printf("\nEnter the updated name: ");
                fflush(stdin);
                gets(s.name);
                printf("\nEnter the updated age: ");
                scanf("%d", &s.age);
                printf("\nEnter the updated gender: ");
                fflush(stdin);
                gets(s.gender);
                printf("\nEnter the updated weight: ");
                scanf("%d", &s.wegiht);
                printf("\nEnter the updated phone number: ");
                fflush(stdin);
                gets(s.phone);
                printf("\nEnter the updated email id: ");
                fflush(stdin);
                gets(s.mail);
                fseek(fp, -sizeS, 1);
                fwrite(&s, sizeS, 1, fp);
                fclose(fp);
                system("cls");
                
            }
        }
        

        if (temp == 0)
        {
            system("cls");
            printf("\nRecord not found!");
            gotoxy(0, 20);
            printf("Press any key to go back......");
            getch();
            modify();
        }
        else
        {
            printf("\nRecord updated succesfully!");
            gotoxy(0, 20);
            printf("Press any key to go back......");
            getch();
            modify();
        }
        break;

    case 3:
        menu();
        break;

    default:
    {
        system("cls");
        printf("\n\nINVALID CHOICE!");
        gotoxy(0, 20);
        printf("\nPress any key to go back........");
        getch();
        modify();
    }
    }
}
void delete ()
{
    FILE *ft;
    system("cls");
    int id, temp = 0, choice;
    char name[30];
    gotoxy(20, 2);
    printf("< == DELETE == >");
    printf("\n\n1. Delete using Member ID\n2. Delete using Name\n3. Back");
    printf("\n\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        system("cls");
        fp = fopen("gym.txt", "rb");
        ft = fopen("temp.txt", "ab");
        printf("Enter Member ID: ");
        scanf("%d", &id);

        while (fread(&s, sizeS, 1, fp) == 1)
        {

            if (id == s.memid)
            {
                system("cls");
                printf("\n RECORD FOUND!");
                temp = 1;
            }
            else
            {
                fwrite(&s, sizeS, 1, ft);
            }
        }
        fclose(fp);
        fclose(ft);
        remove("gym.txt");
        rename("temp.txt", "gym.txt");

        if (temp == 0)
        {
            system("cls");
            printf("\nRecord not found!");
            gotoxy(0, 20);
            printf("Press any key to go back......");
            getch();
            delete ();
        }
        else
        {
            gotoxy(0, 18);
            printf("Record deleted succesfully!");
            gotoxy(0, 20);
            printf("Press any key to go back......");
            getch();
            delete ();
        }
        break;

    case 2:
        system("cls");
        fp = fopen("gym.txt", "rb");
        ft = fopen("temp.txt", "ab");
        printf("Enter the name: ");
        fflush(stdin);
        gets(name);

        while (fread(&s, sizeS, 1, fp) == 1)
        {
            if (strcmpi(name, s.name) == 0)
            {
                system("cls");
                printf("\nRECORD FOUND!");
                temp = 1;
            }
            else
            {
                fwrite(&s, sizeS, 1, ft);
            }
        }
        fclose(fp);
        fclose(ft);
        remove("gym.txt");
        rename("temp.txt", "gym.txt");

        if (temp == 0)
        {
            system("cls");
            printf("\nRecord not found!");
            gotoxy(0, 20);
            printf("Press any key to go back......");
            getch();
            delete ();
        }
        else
        {
            gotoxy(0, 18);
            printf("Record deleted succesfully!");
            gotoxy(0, 20);
            printf("Press any key to go back......");
            getch();
            delete ();
        }
        break;

    case 3:
        menu();
        break;

    default:
    {
        system("cls");
        printf("\n\nINVALID CHOICE!");
        gotoxy(0, 20);
        printf("\nPress any key to go back........");
        getch();
        delete ();
    }
    }
}

// Different Search Functions

void searchbyname()
{
    system("cls");
    char name[30], temp = 0;
    printf("Enter the name: ");
    fflush(stdin);
    gets(name);

    fp = fopen("gym.txt", "rb");
    system("cls");
    printf("%-15s %-30s %-15s %-15s %-15s %-15s %s\n", "MemberID", "Name", "Age", "Gender", "Weight", "PhoneNo", "Email ID");
    while (fread(&s, sizeS, 1, fp) == 1)
    {
        if (strcmpi(name, s.name) == 0)
        {
            temp = 1;
            printf("%-15d %-30s %-15d %-15s %-15d %-15s %s\n", s.memid, s.name, s.age, s.gender, s.wegiht, s.phone, s.mail);
        }
    }
    fclose(fp);
    if (temp == 0)
    {
        system("cls");
        printf("\nRecord not found!");
        gotoxy(0, 20);
        printf("Press any key to go back......");
        getch();
    }
    else
    {
        gotoxy(0, 18);
        printf("Record found succesfully!");
        gotoxy(0, 20);
        printf("Press any key to go back......");
        getch();
    }
}

void searchbymemid()
{
    system("cls");
    int id, temp = 0;
    printf("Enter Member ID: ");
    scanf("%d", &id);

    fp = fopen("gym.txt", "rb");
    system("cls");
    printf("%-15s %-30s %-15s %-15s %-15s %-15s %s\n", "MemberID", "Name", "Age", "Gender", "Weight", "PhoneNo", "Email ID");
    while (fread(&s, sizeS, 1, fp) == 1)
    {
        if (id == s.memid)
        {
            temp = 1;
            printf("%-15d %-30s %-15d %-15s %-15d %-15s %s\n", s.memid, s.name, s.age, s.gender, s.wegiht, s.phone, s.mail);
        }
    }
    fclose(fp);
    if (temp == 0)
    {
        system("cls");
        printf("\nRecord not found!");
        gotoxy(0, 20);
        printf("Press any key to go back......");
        getch();
    }
    else
    {
        gotoxy(0, 18);
        printf("Record found succesfully!");
        gotoxy(0, 20);
        printf("Press any key to go back......");
        getch();
    }
}
void searchbyphone()
{
    system("cls");
    char phone[30], temp = 0;
    printf("Enter Phone no: ");
    fflush(stdin);
    gets(phone);

    fp = fopen("gym.txt", "rb");

    while (fread(&s, sizeS, 1, fp) == 1)
    {
        if (strcmpi(phone, s.phone) == 0)
        {
            system("cls");
            temp = 1;
            printf("%-15s %-30s %-15s %-15s %-15s %-15s %s\n", "MemberID", "Name", "Age", "Gender", "Weight", "PhoneNo", "Email ID");
            printf("%-15d %-30s %-15d %-15s %-15d %-15s %s\n", s.memid, s.name, s.age, s.gender, s.wegiht, s.phone, s.mail);
            break;
        }
    }
    fclose(fp);
    if (temp == 0)
    {
        system("cls");
        printf("\nRecord not found!");
        gotoxy(0, 20);
        printf("Press any key to go back......");
        getch();
    }
    else
    {
        gotoxy(0, 18);
        printf("Record found succesfully!");
        gotoxy(0, 20);
        printf("Press any key to go back......");
        getch();
    }
}
