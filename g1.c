
#include <stdio.h>
#include <stdlib.h>
#include<string.h>


int authenticate(); 		//defining some function
void Book_display();
void displayMenu();		

typedef struct user{		//defining the structure for storing username and password
	char user_name[100];
	char password[100];
} User;

int authenticate(const char *username, const char *password) //Function to authenticate user, to check if the username and password match or not
{
	FILE *fptr;
	int x=0;
	fptr=fopen("users.txt","r"); 		//opening the file containing data about the users
	if (fptr==NULL)
	{
		printf("Error opening the file");		//error statement if the file is empty
		exit(1);
	}
	
	struct user User;			//defining a structure
	
	while(fscanf(fptr,"%s %s", User.user_name,User.password)==2)		//statement fscanf returns the number of entities. Here, if username and password is correctly read, 2 is returned.
	{

		if (strcmp(User.user_name,username)==0 && strcmp(User.password,password)==0)		//comparing entered password and username with the entities present in the 2 lists.
		{
			x=1;
		}
	}
	fclose(fptr);		//fclose general function
	printf("%d\n",x);		//printing the x value
	return x;		//returns 1 if the username and password matches.
}


			
void displayMenu() //interface for the library system.
{
    	printf("\n==== Welcome to university Library ====\n");
    	printf("0. Display all books\n");
    	printf("1. Update a Book\n");
    	printf("2. Borrow a Book\n");
   	printf("3. Return a Book\n");
    	printf("4. Search a Book\n");
    	printf("5. Exit\n");
    	printf("=============================\n");
}

void display_2() //Interface for searching books.
{
	printf("=========Search a book========\n");
	printf("1: Author\n");
	printf("2: publisher\n");
	printf("3: Title\n");
	printf("4: Department\n");
	printf("5: Exit\n");
	printf("==============================\n");
}

void display_3() //Interface for updation.
{
	printf("===========BOOK LIST CHANGE===========\n");
	printf("1.Add a Book\n");
	printf("2.Delete a Book\n");
	printf("3.Update a Book\n");
	printf("4.Exit\n");
	printf("======================================\n");
}
	

typedef struct book    //It is the structure used for the file books.
{     
	char title[50];
	char id[10];
	char author[50];
	char publisher[25];
	int no;
}BOOK;


typedef struct bookis{			//structure used to store issued books.
	char id[10];
	int isno;
}BOOKIS;

typedef struct userno{  		//structure which stores number of books taken by a user.
	char username[30];
	int no_issued;
	
}USERNO;


int scan_userno(USERNO userno[1000])			//function used to scan a file into a structure. Here, 'userissued.txt' which stores the number of books taken by a user.
{
	FILE *fptr3;
	char line[500];
	int n=0;
	fptr3=fopen("userissued.txt","r");
	while (fgets(line, sizeof(line), fptr3) != NULL)
    	{
    		sscanf(line,"%s %d",userno[n].username,&userno[n].no_issued);
    		n++;
    	}
    	fclose(fptr3);
    	return n; //Total number ofusers
}



int scan_bookis(BOOKIS bookis[1000])			//function used to scan a file into a structure. Here, 'bookissued.txt' which contains information about all books.
{
	FILE *fptr3;
	char line[500];
	int n=0;
	fptr3=fopen("bookissued.txt","r");
	while (fgets(line, sizeof(line), fptr3) != NULL)
    	{
    		sscanf(line,"%s %d",bookis[n].id,&bookis[n].isno);
    		n++;
    	}
    	fclose(fptr3);
    	return n; //Return the total number of books in the file 
}



int display_books() //This function scans the file and displays the list of all the books in the terminal.
{

    	FILE *fptr;
    	char line[500];
    	BOOK book;

    	// Open the file for reading
    	fptr = fopen("file.txt", "r");

    	if (fptr == NULL) 
    	{
        	printf("Error opening file\n");
        	exit(1); // Exit the program 
    	}
	
    	// Read data from the file into the structure
    	while (fgets(line, sizeof(line), fptr) != NULL)			//Check for a line in the file.
    	{
    		if (sscanf(line,"%s %[^\t] %[^\t] %[^\t] %d",book.id,book.title,book.author,book.publisher,&book.no))	
    	//Here, the file is read line by line. The data is seperated by tab space. We recognize the alloted tab spaces and split details regarding a book, i.e, ID, Title, Author, Publisher, Book Number.	
    		{	
        		printf("ID: %s, Title: %s, Author: %s, publisher: %s, available copies: %d\n", book.id, book.title,book.author, book.publisher,book.no);	//This statement is to print the split data.
        	}
    	}

    	// Close the file
    	fclose(fptr);

    return 0;
}



int scan_books(BOOK book[1000])								//This function is to scan informations about a book from a created file and made into a specific structure, for easy access.

{
	FILE *fptr;
	char line[500];
	int n=0;
	fptr=fopen("file.txt","r");
	while (fgets(line, sizeof(line), fptr) != NULL)
    	{
    		sscanf(line,"%s %[^\t] %[^\t] %[^\t] %d",book[n].id,book[n].title,book[n].author,book[n].publisher,&book[n].no);
    		n++;
    	}
    	fclose(fptr);
    	return n; //Return the total number of books in the file 
}
    		
int search_author()						//Function to search the desired author.
{
	BOOK book[1000];
	scan_books(book);
	char author[50];
	int i,n=0;
	printf("Enter the name of the author:");
	scanf("%s",author);
	for(i=0;i<scan_books(book);i++)							//scan_books returns the total number of books.
	{
		if(strcasecmp(author,book[i].author)==0)				//strcasecmp is 'not case-sensitive'. CAUTION! - This works only in linux operating systems.
		{	
			printf("Available book %d: ",++n);
			printf("ID: %s, Title: %s, Author: %s, publisher: %s, available copies: %d\n", book[i].id, book[i].title,book[i].author, book[i].publisher,book[i].no);
		}
	}
	if (n>0)
	{
	printf("These are the books available by the author.\n");
	}
	else
	
	{
		printf("The book by the author is not available\n");
	}
		
	return 1;
	
}

int search_publisher()								//To search the publisher.
{
	BOOK book[1000];
	scan_books(book);
	char publisher[50];
	int i,n=0;
	printf("Enter the name of the publisher:");
	scanf("%s",publisher);
	for(i=0;i<scan_books(book);i++)
	{
		if(strcasecmp(publisher,book[i].publisher)==0) //strcasecmp is used to compare two strings and the function is not case sensitive. CAUTION! - This works only in linux operating systems.
		{	
			printf("Available book %d: ",++n);
			printf("ID: %s, Title: %s, Author: %s, publisher: %s, available copies: %d\n", book[i].id, book[i].title,book[i].author, book[i].publisher,book[i].no);
		}
	}
	if (n>0)
	{
	printf("This are the books available by the publisher.\n");
	}
	else
	
	{
		printf("The book by the publisher is not available\n");
	}
		
	return 1;
}

int key_search(const char *substring, const char *string)					//function that makes searching books of interest easy!!! (part-of-name-searching!!)
{
	int sublen= strlen(substring);
	int stringlen=strlen(string);
	int i;
	
	for (i=0; i<=stringlen-sublen; i++)
	{
		if (strncmp(substring,string+i,sublen)==0)
		{
			return 1;
		}
	}
	return 0;
}
	
int search_book()											//Function to search book
{
	BOOK book[1000];
	scan_books(book);
	char book_name[100];
	int i,n=0;							//To show available book number.
	printf("Enter the name of the book or keyword that you want to search.\n");
	scanf("%s",book_name);
	for(i=0;i<scan_books(book);i++)
	{
		if(key_search(book_name,book[i].title)==1) //strcasecmp is used to compare two strings and the function is not case sensitive.
		{	
			printf("Available book %d: ",++n);
			printf("ID: %s, Title: %s, Author: %s, publisher: %s, available copies: %d\n", book[i].id, book[i].title,book[i].author, book[i].publisher,book[i].no);
		}
	}
	if (n>0)
	{
	printf("This are the books available.\n");
	}
	else
	
	{
		printf("The book by the publisher is not available\n");
	}
		
	return 1;
}

int search_department()											//In our library list, the book are categorised into different sections. This shows all the books available under a section.
{
	int choice_4;			
	do
	{
		printf("=======DEPARTMENT SEARCH=========\n");				//USER INTERFACE
		printf("1.Chemistry\n");
		printf("2.Physics\n");
		printf("3.Mathematics\n");
		printf("4.Biology\n");
		printf("5.Computer science\n");
		printf("6.English literature\n");
		printf("7. Exit\n");
		printf("=================================\n");
		
		printf("Enter your choice:");					
		scanf("%d",&choice_4);
		BOOK book[1000];
		int i;
		for (i=0;i<scan_books(book);i++)
		{
			switch(choice_4)							
			{
				case 1:
					if ((book[i].id)[0]=='C')
					{
						printf("ID: %s, Title: %s, Author: %s, publisher: %s, available copies: %d\n", book[i].id, book[i].title,book[i].author, book[i].publisher,book[i].no);
					}
					break;
				case 2:
					if ((book[i].id)[0]=='P')
					{
						printf("ID: %s, Title: %s, Author: %s, publisher: %s, available copies: %d\n", book[i].id, book[i].title,book[i].author, book[i].publisher,book[i].no);
					}
					break;
				case 3:
					if ((book[i].id)[0]=='M')
					{
						printf("ID: %s, Title: %s, Author: %s, publisher: %s, available copies: %d\n", book[i].id, book[i].title,book[i].author, book[i].publisher,book[i].no);
					}
					break;
					
				case 4:
					if ((book[i].id)[0]=='L')
					{
						printf("ID: %s, Title: %s, Author: %s, publisher: %s, available copies: %d\n", book[i].id, book[i].title,book[i].author, book[i].publisher,book[i].no);
					}
					break;
				case 5:
					if ((book[i].id)[0]=='P')
					{
						printf("ID: %s, Title: %s, Author: %s, publisher: %s, available copies: %d\n", book[i].id, book[i].title,book[i].author, book[i].publisher,book[i].no);
					}
					break;
				case 6:
					if ((book[i].id)[0]=='E')
					{
						printf("ID: %s, Title: %s, Author: %s, publisher: %s, available copies: %d\n", book[i].id, book[i].title,book[i].author, book[i].publisher,book[i].no);
					}
					break;
				case 7:
					break;
				default:
					printf("Invalid choice\n");
			}
		}
	}
	while(choice_4 !=7);
}
			




void addBook() {				//Function to add books into the library accessible only for the admin 
    FILE *fptr;
    BOOK book;
     // Use this structure to store the input values
    BOOK *b = &book;  // Use a pointer to the newBook structure

    printf("Enter Book ID: ");
    scanf("%s", b->id);  // Use %d for integer input

    printf("Enter Title: ");
    scanf("%s", b->title);

    printf("Enter Author: ");
    scanf("%s", b->author);

    printf("Enter Publisher: ");
    scanf("%s", b->publisher);

    printf("Enter Number of Copies: ");
    scanf("%d", &b->no);

    fptr = fopen("file.txt", "a");
    if (fptr == NULL) {
        perror("Error opening the file");
        exit(1);
    }

    fprintf(fptr, "%s\t%s\t%s\t%s\t%d\n", b->id, b->title, b->author, b->publisher, b->no);
    

    fclose(fptr);
    printf("Book added successfully!\n");
}


void deleteBook()											//Function to delete the books which is only accessible to the admin of the library.
{
    FILE *fptr, *tempFile;
    char bookID[10];

    printf("Enter the ID of the book to be deleted: ");
    scanf("%s", bookID);

    fptr = fopen("file.txt", "r");
    tempFile = fopen("temp.txt", "w");

    if (fptr == NULL || tempFile == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    BOOK book[1000];
    
    for(int i=0;i<scan_books(book);i++)
    {
    
        if (strcmp(book[i].id, bookID) != 0)
        {
            fprintf(tempFile, "%s\t%s\t%s\t%s\t%d\n", book[i].id,book[i].title, book[i].author, book[i].publisher, book[i].no);
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("file.txt");
    rename("temp.txt", "file.txt");

    printf("Book deleted successfully!\n");



}

void updateBook()										//Function to update the existing books, which is only accessible to the admin of the library.
{
    FILE *fptr, *tempFile;
    char bookID[10];

    printf("Enter the ID of the book you want to update:");
    scanf("%s", bookID);

    fptr = fopen("file.txt", "r");
    tempFile = fopen("temp.txt", "w");

    if (fptr == NULL || tempFile == NULL)
    {
        perror("Error opening file!");
        exit(1);
    }

    BOOK book[1000];

    int totalBooks = scan_books(book);
   

    for (int i = 0; i < totalBooks; i++)
    {	
    	int num=0;
        if (strcmp(book[i].id, bookID) == 0)
        {
            printf("Enter new Number of copies: ");
            scanf("%d", &num);
        }

        fprintf(tempFile, "%s\t%s\t%s\t%s\t%d\n", book[i].id, book[i].title, book[i].author, book[i].publisher, (book[i].no+num));
    }

    fclose(fptr);
    fclose(tempFile);

    remove("file.txt");
    rename("temp.txt", "file.txt");

    printf("Book updated successfully!\n");
}



int differentiate(char *line) 					//Function to identify whether the person accessing is a Faculty (F), Admin (A) or a Student (S). Necessary returning values are assigned (0,1,2 respectively).

{
	if (line[0] == 'F')
	{
		return 0;
	}
	else if (line[0] == 'A')
	{
		return 1;
	}
	else if (line[0] == 'S')
	{
		return 2;
	}
	else 
	{
		return -1; //if any error happens 
		}
}

int issue(char *username)							//For issueing a book which holds a big part in library management system. 
{
	   FILE *fptr1;
        BOOK book[1000];
        FILE *fptr2,*fptr3,*fptr4,*fptr5;
        BOOKIS bookis[1000];
        USERNO userno[1000]; 
        
    fptr1 = fopen("file.txt", "r");				//pointer 1 to open file.txt containing all the informations associated with the books.
    if(fptr1 == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fptr3 = fopen("temp.txt", "w");				//pointer 2 to open temp.txt which is an empty file. This can be used to store a temporary texts which can be used to store updated booklist after issueing.
    if(fptr3 == NULL)
    {
	printf("Error opening file!\n");
	exit(1);
    }
    
    fptr4 = fopen("temp3.txt", "w");				//pointer 3 to open temp3.txt which is an empty file used to store updated books which are issued.
    if(fptr4 == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fptr5 = fopen("temp2.txt", "w");				//pointer 4 to open temp2.txt which is an empty file used to store books taken by the user.
    if(fptr5 == NULL)
    {
	printf("Error opening file!\n");
	exit(1);
    }

    	int n=0,key=0,no=0;
	char idd[20];
	char id[10],t[50],a[50],p[25];
	char id1[10], id2[10];
	int isno1, isno2, trial=0;
	
	printf("Dear loving user, enter id of the book which you want to take: ");
	scanf("%s", idd);
	
	for(int i=0;i<scan_books(book);i++)									//For scanning books in the structure. 
	{
		
//here clarify if his structure is book or books
		if(strcmp(book[i].id,idd)==0)									//For comparing the ID with the ID entered.
		{
		printf("Entered ID number found, Book requested is - %s\n",book[i].title);
			for (int l=0; l<scan_userno(userno);l++)
			{
			if (strcmp(username, userno[l].username)==0)						//if loop to ensure that the user does not take more than 5 books.
			{
			if (userno[l].no_issued <6)
			{
			if(book[i].no<3)
			{
				if(differentiate(username)==0)// 0 value is returned for faculty
				{
				
					if(book[i].no>0)
					{	
						for (int k=0; k<scan_userno(userno);k++)
						{
							
							if (strcmp(username, userno[k].username)==0)					//if loop to store the necessary details regarding the borrower. 
							{
								isno2=++userno[k].no_issued;
								strcpy(id2,userno[k].username);
							}
							else
							{
								fprintf(fptr4,"%s %d\n",userno[k].username,userno[k].no_issued);
							}
						}
						fprintf(fptr5,"%s %d\n",id2, isno2);	
						
						printf("Book issued\n");
						printf("You should return your book within %d days\n",(2*no+7));
						trial=0;
						key=1;
						no=--book[i].no;					//For updating the database with the new updated number of issued books.
						strcpy(id,book[i].id);
						strcpy(t,book[i].title);
						strcpy(a,book[i].author);
						strcpy(p,book[i].publisher);
						for (int j=0; j<scan_bookis(bookis);j++)					//To update the number of the particular book issued.		
						{
							if (strcmp(bookis[j].id,idd)==0)
							{
								isno1=++bookis[j].isno;
								
								strcpy(id1,bookis[j].id);
							}
							else
							{
								fprintf(fptr5,"%s %d\n",bookis[j].id,bookis[j].isno);
							}
						}
						fprintf(fptr5,"%s %d\n",id1, isno1);
						
				
						
					}
					else
					{	
						printf("Sorry,book is not available");				//Prints s'Sorry statment' if the user does not satisfy the particular requirements set by the library management.
						trial=1;
					}
				}
				else
				{
					printf("Sorry, you dont have permission to take this book as availablility is limited to faculty only.");			
					trial=1;
				}
			}
			//Above written code ensures that less than 3 copies will be issued only to Faculties. The below codes are same as above. The only difference is that if the number of copies is greater than 3, everyone can issue it. 
			
			
			else
			{
				if(book[i].no>0)
					{
						printf("Book issued\n");
						key=1;
						trial=0;
						no=--book[i].no;
						printf("You should return your book within %d days\n",(2*no+7));
						for (int j=0; j<scan_bookis(bookis);j++)
						{
							if (strcmp(bookis[j].id,idd)==0)
							{
								isno1=++bookis[j].isno;
								
								strcpy(id1,bookis[j].id);
							}
							else
							{
								fprintf(fptr5,"%s %d\n",bookis[j].id,bookis[j].isno);
							}
						}
						fprintf(fptr5,"%s %d\n",id1, isno1);
						for (int k=0; k<scan_userno(userno);k++)
						{
							if (strcmp(username, userno[k].username)==0)
							{
								isno2=++userno[k].no_issued;
								strcpy(id2,userno[k].username);
							}
							else
							{
								fprintf(fptr4,"%s %d\n",userno[k].username,userno[k].no_issued);
							}
						}
						fprintf(fptr4,"%s %d\n",id2, isno2);	
						
						
						strcpy(id,book[i].id);
						strcpy(t,book[i].title);
						strcpy(a,book[i].author);
						strcpy(p,book[i].publisher);
            				}
            			else
            			{
						printf("Sorry,book is not available");
						trial=1;
				}
				remove("userissued.txt");							//It removes the initial 'userissue.txt' file and updated with the 'temp3.txt' file. Similarly, with the 'bookissued.txt' file. 
    				rename("temp3.txt", "userissued.txt");
    				remove("bookissued.txt");
				rename("temp2.txt","bookissued.txt");
            		}
            		}
            		else
            		printf("You are not allowed to take book.\n");
            		trial=1;
            		}
            		}
            	}
            	else
            	{
            	fprintf(fptr3, "%s\t%s\t%s\t%s\t%d\n", book[i].id, book[i].title, book[i].author, book[i].publisher, book[i].no);
            	}
            	
            }
        fprintf(fptr3,"%s\t%s\t%s\t%s\t%d\n",id,t,a,p,no);
        
        fclose(fptr3);									//Files are closed for now.
	fclose(fptr1); 											
	fclose(fptr4);
	fclose(fptr5);
	
	if (trial==0)	
	{
   	remove("file.txt");
    	rename("temp.txt","file.txt");						//The file changes if and only if the book is issued.
    	}
        if (key==0)
    	{
    		printf("The book is not available\n");
    	}
    	return 0;
  
  
	    

}
	
	
int book_return(BOOK book[1000], char* username) //const char* username)					
												//Function to update the number of copies after a borrower returns his/her lended book.
{
	FILE *fptr1;
	FILE *fptr2, *fptr3,*fptr4;
	
	char ID[10],id[10],id1[10],id2[10],t[50],a[50],p[25];
	USERNO userno[1000];
	BOOKIS bookis[1000];

	int i,n=0,no,isno2,isno1;
	fptr1=fopen("file.txt","r");
	fptr2=fopen("temp.txt","w");
	fptr3=fopen("temp2.txt","w");
	fptr4=fopen("temp4.txt","w");
	scan_books(book);
	printf("Enter the ID of book you are going tho written:");
	scanf("%s",ID);
	for (i=0; i<scan_books(book);i++)
	{
		if(strcmp(book[i].id,ID)==0)
		{
			printf("Your book is successfully returned.\n");
			no=++book[i].no;										//Update the copies to the database.
			strcpy(id,book[i].id);
			strcpy(t,book[i].title);
			strcpy(a,book[i].author);
			strcpy(p,book[i].publisher);
			for (int k=0; k<scan_userno(userno);k++)
			{
			if (strcmp(username, userno[k].username)==0)
			{												//Updates the book issued by the user.
				isno2=--userno[k].no_issued;	
				strcpy(id2,userno[k].username);
			}
			else
			{
				fprintf(fptr4,"%s %d\n",userno[k].username,userno[k].no_issued);
			}
			}
			fprintf(fptr4,"%s %d\n",id2, isno2);
			for (int j=0; j<scan_bookis(bookis);j++)
			{
				if (strcmp(bookis[j].id,ID)==0)									//Updates the number of particular book issued.
				{
					isno1=--bookis[j].isno;
					
					strcpy(id1,bookis[j].id);
				}
				else
				{
					fprintf(fptr3,"%s %d\n",bookis[j].id,bookis[j].isno);
				}
			}
			fprintf(fptr3,"%s %d\n",id1, isno1);

		}
		else
		{
		fprintf(fptr2, "%s\t%s\t%s\t%s\t%d\n", book[i].id, book[i].title, book[i].author, book[i].publisher, book[i].no);
		}
	
		
	}
	fprintf(fptr2,"%s\t%s\t%s\t%s\t%d\n",id,t,a,p,no);
	
	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);
	fclose(fptr4);
	remove("file.txt");
	rename("temp.txt","file.txt");
	remove("bookissued.txt");
	rename("temp2.txt","bookissued.txt");
	remove("userissued.txt");
	rename("temp4.txt","userissued.txt");
}

	

int main() 
{
    	char username[50];
	char password[50];
	BOOK book[1000];
	printf("\n\n===============================\n");
	printf("==WELCOME TO UNIVERSITY LIBRARY==\n");
	printf("===============================\n");
	printf("Enter user name:");
	scanf("%s",username);
	printf("Enter password:");
	scanf("%s",password);
	//printf("%d\n",authenticate(username,password));
	if (authenticate(username,password))
	{
	int choice;

	do 
	{
		displayMenu();		

		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) 
		{	
			case 0:
				printf("Display all books\n");
				display_books();
				break;
				
			case 1:
				int choice_3;
				if (differentiate(username)==1)						//Only allows admin to make changes in the system.
				{	
					
					do
					{
						display_3();
						printf("Enter your choice:");
						scanf("%d",&choice_3);
		        			
		        			switch(choice_3)
		        			{
		        				case 1:
		        					addBook();
		        					break;
		        				case 2:
		        					deleteBook();
		        					break;
		        				case 3:
		        					updateBook();
		        					break;
		        				case 4: 
		        					printf("Exiting....\n");
		        					break;
		        				default:
		        					printf("Invalid choice. Please enter a valid choice\n");
		        					break;
		        			}
		        		}
		        		while (choice_3 !=4);							//Does not terminate unless '4' is typed.
		        	
                		}
                		else
                		{
                			printf("You are not allowed for this operation.\n");
                		}
                
                		// Add your code for adding a book
                		break;

			case 2:
				printf("Option 2: Borrow a Book\n");
				issue(username);
				break;

			case 3:
                		printf("Option 3: Return a Book\n");
                		book_return(book,username);
               			break;

            		case 4:
                		printf("Option 4: Search a book\n");
                		
                		scan_books(book);
                		int choice_2;
                		do
                		{
                			display_2();
                	
                			printf("Enter your choice:");
                			scanf("%d",&choice_2);
                			switch (choice_2)
                			{
                				case 1:
                					search_author();
                					break;
                				case 2:
                					search_publisher();
                					break;
                				case 3:
                					search_book();
                					break;
                				case 4:
                					search_department();
                					break;
                				case 5:
                					printf("Existing search\n");
                					break;
                				default:
                					printf("Invalid choice. Please enter a valid option.\n");
                					break;
                			}
                		}
                		while(choice_2 !=5);
                		break;
                			
                			

            		case 5:
                		printf("Exiting the Library System. Goodbye!\n");
                		break;

            		default:
                		printf("Invalid choice. Please enter a valid option.\n");
                		break;
        	}

    	}
    	while (choice != 5);
	}
	
	
	
	
	else
	{
	printf("You are not registered.\n");
	}
    return 0;
}

// We have worked hard for it. 
	
