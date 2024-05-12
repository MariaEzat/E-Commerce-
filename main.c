#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct product product;
typedef struct category category;
typedef struct supermarket supermarket;

struct product
{
    char name[20];
    int quantity;
    int price;
};

struct category
{
    char name[20];
    int id;
    product *p;
    int numproduct;
};

struct supermarket
{
    category *cat;
    int numcategory;
};

void gotoxy(int x, int y)
{
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw_border()
{
    gotoxy(39, 10);
    printf("%c", 201);
    for (int i = 0; i < 35; i++)
    {
        printf("%c", 205);
    }
    printf("%c", 187);

    for (int i = 11; i < 17; i++)
    {
        gotoxy(39, i);
        printf("%c", 186);
        for (int j = 0; j < 35; j++)
        {
            printf(" ");
        }
        printf("%c", 186);
    }

    gotoxy(39, 17);
    printf("%c", 200);
    for (int i = 0; i < 35; i++)
    {
        printf("%c", 205);
    }
    printf("%c", 188);
}

void ShowConsoleCursor(int showcursor)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showcursor;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void initialize(supermarket *Market)
{
    Market->numcategory = 0;
    Market->cat = malloc(sizeof(category));
}

void Display(supermarket *Market)
{
    for (int i = 0; i < Market->numcategory; i++)
    {
        category *categ = &(Market->cat[i]);

        printf("**********%s***************\n", categ->name);
        for (int j = 0; j < Market->cat[i].numproduct; j++)
        {
            printf("Name:%s\n", Market->cat[i].p[j].name);
            printf("Quantity:%d\n", Market->cat[i].p[j].quantity);
            printf("The Price of one piece:%d\n", Market->cat[i].p[j].price);
            printf("Total Price:%d\n", Market->cat[i].p[j].price * Market->cat[i].p[j].quantity);
            printf("\n");
        }
    }
}

void Add_category(supermarket *Market)
{
    category catt;
    printf("Enter The Name of Category:\n");
    scanf("%s", catt.name);


    /*catt.p = malloc(catt.numproduct * sizeof(product));
    printf("Do You need to Add Products in This Category ? Yes OR No \n");
    char answer[5];
    scanf("%s",answer);

     if(answer=='Yes');
     {
         printf("Enter The Number of Products:\n");
         scanf("%d", &catt.numproduct);
         for (int i = 0; i < catt.numproduct; i++)
         {
             char prodName[30];
             int prodQuantity;
             int prodPrice;

             printf("Enter Product Name:\n");
             scanf("%s", prodName );
             printf("Enter Quantity:\n");
             scanf("%d", &prodQuantity);
             printf("Enter Price:\n");
             scanf("%d", &prodPrice);
             product prod;
             strcpy(prod.name,prodName);
             prod.price = prodPrice;
             prod.quantity = prodQuantity;
             //catt->p[catt->numproduct - 1] = prod;
         }

     }*/

    catt.p=malloc(0*sizeof(product));

    Market->cat = realloc(Market->cat, (Market->numcategory + 1) * sizeof(category)); // Reallocate memory for new category
    Market->cat[Market->numcategory] = catt;
    Market->numcategory++;
    printf("Category added successfully");
}

void Add_product(supermarket *Market)
{
    char prodName[30];
    int prodQuantity;
    int prodPrice;

        printf("Enter Product Name: ");
        scanf("%s", prodName);

        printf("Enter Quantity: ");
        scanf("%d", &prodQuantity);

        printf("Enter Price: ");
        scanf("%d", &prodPrice);

    int categoryIndex;
    printf("Enter the category index to add the product to: ");
    for(int i=0;i<Market->numcategory;i++)
    {
        printf("%d) %s\n",i+1,Market->cat[i].name);
    }
    scanf("%d", &categoryIndex);
    categoryIndex--;

    if (categoryIndex >= 0 && categoryIndex < Market->numcategory)
    {
        category *categ = &(Market->cat[categoryIndex]);

        categ->numproduct++;
        categ->p = realloc(categ->p, categ->numproduct * sizeof(product));

       product prod;
       strcpy(prod.name,prodName);
       prod.price = prodPrice;
       prod.quantity = prodQuantity;
       categ->p[categ->numproduct - 1] = prod;
        printf("Product added successfully\n");

    }
    else
    {
        printf("Invalid category index\n");
    }
}

int main()
{
    HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
    int postion=1;
    char ch;
    supermarket Market;
    initialize(&Market);
    ShowConsoleCursor(0);

    draw_border();

    do
    {
        SetConsoleTextAttribute(console,15);

        gotoxy(40,11);
        printf("1)Add Category ");

        gotoxy(40,12);
        printf("2)Display Categories and Products  ");

        gotoxy(40,13);
        printf("3)Add Product    ");

        gotoxy(40,14);
        printf("4)Delete Product              ");

        gotoxy(40,15);
        printf("5)Move Product to another Category");

        gotoxy(40,16);
        printf("6)Exit      ");





        switch(postion)
        {
        case 1:
            SetConsoleTextAttribute(console,240);
            gotoxy(40,11);
            printf("1)Add Category ");
            break;
        case 2:
            SetConsoleTextAttribute(console,240);
            gotoxy(40,12);
            printf("2)Display Categories and Products  ");
            break;
        case 3:
            SetConsoleTextAttribute(console,240);
            gotoxy(40,13);
            printf("3)Add Product    ");
            break;
        case 4:
            SetConsoleTextAttribute(console,240);
            gotoxy(40,14);
            printf("4)Delete Product              ");
            break;

        case 5:
            SetConsoleTextAttribute(console,240);
            gotoxy(40,15);
            printf("5)Move Product to another Category");
            break;
        case 6:
            SetConsoleTextAttribute(console,240);
            gotoxy(40,16);
            printf("6)Exit      ");
            break;
        }
        ch=getch();
        if(ch==-32)
        {
            ch=getch();
        }
        if(ch==72)
        {
            postion--;
            if(postion==0)
            {
                postion=6;
            }
        }
        if(ch==80)
        {
            postion++;
            if(postion==7)
            {
                postion=1;
            }
        }


        switch(ch)
        {
        case 13:
            switch(postion)
            {
            case 1:
                SetConsoleTextAttribute(console,15);
                system("cls");
                Add_category(&Market);
                _getch();
                system("cls");
                draw_border();
                break;
            case 2:
                SetConsoleTextAttribute(console,15);
                system("cls");
                Display(&Market);
                _getch();
                system("cls");
                draw_border();
                break;
            case 3:
                SetConsoleTextAttribute(console,15);
                system("cls");
                Add_product(&Market);
                _getch();
                system("cls");
                draw_border();
                break;
            case 4:
                SetConsoleTextAttribute(console,15);
                system("cls");
                getch();
                draw_border();
                break;
            case 5:
                SetConsoleTextAttribute(console,15);
                system("cls");
                getch();
                draw_border();
                break;

            case 6:
                SetConsoleTextAttribute(console,15);
                system("cls");
                return 0;

            }
        }
   }
    while(1);
    return 0;
}

