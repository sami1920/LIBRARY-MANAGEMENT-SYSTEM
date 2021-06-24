#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//A WHOLE LIBRARY MANAGEMENT SYSTEM

//This global variable is set for helping in the functionality of issue a book
int issue_book = 0;
int issueBookID;
int return_book = 0;
int returnBookID;

//This class is for keeping the record of books in the library
class Books{
public:
    int ID;
    string book_name;
    string book_type;
    string book_author;
    bool availaibe;

    Books()
    {
        availaibe = true;
    }
    void PrintBookInfo()
    {
        cout << "Unique ID:\t" << ID << endl;
        cout << "Name:\t" << book_name << endl;
        cout << "Type:\t" << book_type << endl;
        cout << "Author's name:\t" << book_author << endl << endl;
    }
    //This function can chamge any attribute of a book except its unque ID
    void ChangeAttributes()
    {
        int choice;
        string new_attribute;
        cout << "Press 1 to change name of the book.\n";
        cout << "Press 2 to change type of the book.\n";
        cout << "Press 3 to change author's name of the book.\n";
        cin >> choice;

        if(choice == 1)
        {
            cout << "Enter the new name:\t";
            cin >> new_attribute;
            book_name = new_attribute;
        }
        if(choice == 2)
        {
            cout << "Enter the new type:\t";
            cin >> new_attribute;
            book_type = new_attribute;
        }
        if(choice == 3)
        {
            cout << "Enter the new author's name:\t";
            cin >> new_attribute;
            book_author = new_attribute;
        }
    }
    void makeAvailable()
    {
        availaibe = true;
    }
    void check_avaialability()
    {
        if(availaibe)
            cout << "Available.";
        else
            cout << "Unavailable.";
    }
    void makeUnAvailable()
    {
        availaibe = false;
    }
};

class Admin{
private:
    //using association
    Books* books;
    Books* IssueBooks;
    int no_of_issue_books;
    int no_of_books;
public:
    void LoadBooks()
    {
        ifstream fin("BookList.txt");
        fin >> no_of_books;

        books = new Books[no_of_books];
        for(int i=0; i<no_of_books; i++)
        {
            fin >> books[i].ID >> books[i].book_name >> books[i].book_type >> books[i].book_author;
            books[i].makeAvailable();
        }
        fin.close();
    }
    void LoadIssueBooks()
    {
        ifstream fin("IssueBookList.txt");
        fin >> no_of_issue_books;

        IssueBooks = new Books[no_of_issue_books];
        for(int i=0; i<no_of_issue_books; i++)
            fin >> IssueBooks[i].ID >> IssueBooks[i].book_name >> IssueBooks[i].book_type >> IssueBooks[i].book_author;
        fin.close();
    }
    //This function prints all information about current books
    void Print()
    {
        for(int i=0; i<no_of_books; i++)
            books[i].PrintBookInfo();
    }
    //This function is used to change any attribute of a specific book
    void ChangeBook()
    {
        int tempID, check = -1;
        cout << "Enter the unique ID of the book to change its attribute:\t";
        cin >> tempID;

        for(int i=0; i<no_of_books; i++)
            if(tempID == books[i].ID)
                check = i;
        if(check != -1)
        {
            books[check].ChangeAttributes();
            cout << "CONGRATS! Specific attribute changed.\n";
        }
        else if(check = -1)
        {
            cout << "OOPS! Error while matching the ID.\n";
            return;
        }

        ofstream fout("BookList.txt");
        fout << no_of_books << endl;
        for(int i=0; i<no_of_books; i++)
            fout << books[i].ID << " " << books[i].book_name << " " << books[i].book_type << " " << books[i].book_author << endl;

        fout.close();
    }
    //This function is used to add a newvok to the record
    void AddBook()
    {
        ifstream fin("BookList.txt");
        fin >> no_of_books;

        books = new Books[no_of_books+1];
        for(int i=0; i<no_of_books; i++)
        {
            fin >> books[i].ID >> books[i].book_name >> books[i].book_type >> books[i].book_author;
        }
        fin.close();

        no_of_books += 1;

        cout << "Enter the ID of the new book:\t";
        cin >> books[no_of_books-1].ID;

        cout << "Enter the name of the new book:\t";
        cin >> books[no_of_books-1].book_name;

        cout << "Enter the type of the new book:\t";
        cin >> books[no_of_books-1].book_type;

        cout << "Enter the author's name of the new book:\t";
        cin >> books[no_of_books-1].book_author;

        ofstream fout("BookList.txt");
        fout << no_of_books << endl;
        for(int i=0; i<no_of_books; i++)
            fout << books[i].ID << " " << books[i].book_name << " " << books[i].book_type << " " << books[i].book_author << endl;

        fout.close();
    }
    //This function adds a book in the issue books list
    void AddIssueBook(int counter)
    {
        ifstream fin("IssueBookList.txt");
        fin >> no_of_issue_books;

        IssueBooks = new Books[no_of_books+1];
        for(int i=0; i<no_of_books; i++)
        {
            fin >> IssueBooks[i].ID >> IssueBooks[i].book_name >> IssueBooks[i].book_type >> IssueBooks[i].book_author;
        }
        fin.close();

        no_of_issue_books += 1;

        IssueBooks[no_of_issue_books-1].ID = books[counter].ID;
        IssueBooks[no_of_issue_books-1].book_name = books[counter].book_name;
        IssueBooks[no_of_issue_books-1].book_type = books[counter].book_type;
        IssueBooks[no_of_issue_books-1].book_author = books[counter].book_author;
        
        ofstream fout("IssueBookList.txt");
        fout << no_of_issue_books << endl;
        for(int i=0; i<no_of_issue_books; i++)
            fout << IssueBooks[i].ID << " " << IssueBooks[i].book_name << " " << IssueBooks[i].book_type << " " << IssueBooks[i].book_author << endl;

        fout.close();
    }
    //This function is used for removing a book
    void RemoveBook()
    {
        ifstream fin("BookList.txt");
        fin >> no_of_books;

        Books *temp = new Books[no_of_books];
        for(int i=0; i<no_of_books; i++)
        {
            fin >> temp[i].ID >> temp[i].book_name >> temp[i].book_type >> temp[i].book_author;
        }
        fin.close();

        no_of_books -= 1;
        int tempID;

        cout << "Enter the ID of the book you want to remove:\t";
        cin >> tempID;

        //allocated books array with decrement of 1
        books = new Books[no_of_books];

        for(int i=0, j=0; i<no_of_books+1; i++)
        {
            if(temp[i].ID != tempID)
            {
                books[j].ID = temp[i].ID;
                books[j].book_name = temp[i].book_name;
                books[j].book_type = temp[i].book_type;
                books[j].book_author = temp[i].book_author;
                j++;
            }
        }

        ofstream fout("BookList.txt");
        fout << no_of_books << endl;
        for(int i=0; i<no_of_books; i++)
            fout << books[i].ID << " " << books[i].book_name << " " << books[i].book_type << " " << books[i].book_author << endl;

        fout.close();
    }
    void RemoveIssueBook()
    {
        ifstream fin("IssueBookList.txt");
        fin >> no_of_issue_books;

        Books *temp = new Books[no_of_issue_books];
        for(int i=0; i<no_of_issue_books; i++)
        {
            fin >> temp[i].ID >> temp[i].book_name >> temp[i].book_type >> temp[i].book_author;
        }
        fin.close();

        no_of_issue_books -= 1;

        //allocated books array with decrement of 1
        IssueBooks = new Books[no_of_issue_books];

        for(int i=0, j=0; i<no_of_issue_books+1; i++)
        {
            if(temp[i].ID != returnBookID)
            {
                books[j].ID = temp[i].ID;
                books[j].book_name = temp[i].book_name;
                books[j].book_type = temp[i].book_type;
                books[j].book_author = temp[i].book_author;
                j++;
            }
        }

        ofstream fout("IssueBookList.txt");
        fout << no_of_issue_books << endl;
        for(int i=0; i<no_of_issue_books; i++)
            fout << IssueBooks[i].ID << " " << IssueBooks[i].book_name << " " << IssueBooks[i].book_type << " " << IssueBooks[i].book_author << endl;

        fout.close();
    }
    //This function is used to make a book unavailable
    void UnAvailable()
    {
        int tempID;
        cout << "Enter the ID of the book you want to make unavailable:\t";
        cin >> tempID;

        bool check = false;
        for(int i=0; i<no_of_books; i++)
            if(tempID == books[i].ID)
                check = true;

    if(check)
    {
        books[tempID].makeUnAvailable(); 
        cout << "\nBook with ID " << tempID << " is unavailable now.\n";
    }
    else
        cout << "\nOOPS! Entered ID is incorect.\n";
    }
    void Available()
    {
        int tempID;
        cout << "Enter the ID of the book you want to make available:\t";
        cin >> tempID;

        bool check = false;
        for(int i=0; i<no_of_books; i++)
            if(tempID == books[i].ID)
                check = true;

        if(check)
        {
            books[tempID].makeAvailable(); 
            cout << "\nBook with ID " << tempID << " is available now.\n";
        }
        else
            cout << "\nOOPS! Entered ID is incorect.\n";
    }
    //This function is for issuing the books
    void Notification(int& issue_book, int& issueBookID, int& return_book, int& returnBookID)
    {
        int choice;
        if(issue_book == 1)
        {
            cout << "The user wants a book with ID " << issueBookID << " to be issued.\n";
            cout << "Press 1 to issue the book.\nPress 2 to deny the request.\n";
            cin >> choice;

            int check = -1;
            for(int i=0; i<no_of_books; i++)
                if(books[i].ID == issueBookID)
                    check = i;

            if(choice == 1 && books[check].availaibe == true)
            {
                //adding that book in the issue books list
                AddIssueBook(check);

                //removing the book from the book list
                ifstream fin("BookList.txt");
                fin >> no_of_books;

                Books *temp = new Books[no_of_books];
                for(int i=0; i<no_of_books; i++)
                {
                    fin >> temp[i].ID >> temp[i].book_name >> temp[i].book_type >> temp[i].book_author;
                }
                fin.close();

                no_of_books -= 1;

                //allocated books array with decrement of 1
                books = new Books[no_of_books];

                for(int i=0, j=0; i<no_of_books+1; i++)
                {
                    if(temp[i].ID != issueBookID)
                    {
                        books[j].ID = temp[i].ID;
                        books[j].book_name = temp[i].book_name;
                        books[j].book_type = temp[i].book_type;
                        books[j].book_author = temp[i].book_author;
                        j++;
                    }
                }

                ofstream fout("BookList.txt");
                fout << no_of_books << endl;
                for(int i=0; i<no_of_books; i++)
                    fout << books[i].ID << " " << books[i].book_name << " " << books[i].book_type << " " << books[i].book_author << endl;

                fout.close();

                issue_book = -1;
            }
            else if(choice == 1 && books[check].availaibe == false)
                issue_book = -2;
        }
        if(return_book == 1)
        {
            cout << "* The book with the ID " << returnBookID << " is returned. Please check the updated files.\n";

            //Adding the book in book list
            LoadIssueBooks();
            ifstream fin("BookList.txt");
            fin >> no_of_books;

            books = new Books[no_of_books+1];
            for(int i=0; i<no_of_books; i++)
            {
                fin >> books[i].ID >> books[i].book_name >> books[i].book_type >> books[i].book_author;
            }
            fin.close();


            no_of_books += 1;

            int check = -1;
            for(int i=0; i<no_of_issue_books; i++)
                if(IssueBooks[i].ID == returnBookID)
                    check = i;


            books[no_of_books-1].ID = IssueBooks[check].ID;
            books[no_of_books-1].book_name = IssueBooks[check].book_name;
            books[no_of_books-1].book_type = IssueBooks[check].book_type;
            books[no_of_books-1].book_author = IssueBooks[check].book_author;

            ofstream fout("BookList.txt");
            fout << no_of_books << endl;
            for(int i=0; i<no_of_books; i++)
                fout << books[i].ID << " " << books[i].book_name << " " << books[i].book_type << " " << books[i].book_author << endl;

            fout.close();

            //removing the book from issue book list
            RemoveIssueBook();

            return_book = 0;
            returnBookID = 0;
        }
    }    
};

//This class is for keeping the record of all the registered users
class User
{
private:
    string user_name;
    string user_password;
public:
    //This function is for entering all information of a user
    void enterInformation()
    {
        cout << "Enter your user name :\t";
        cin >> user_name;

        cout << "Enter your password :\t";
        cin >> user_password;
    }
    //setter for setting values of username and password
    void Set_info(string a, string b)
    {
        user_name = a;
        user_password = b;
    }
    //function for entry of new user in the file
    void Writing_file(ofstream &obj)
    {
        obj << user_name << "\t" << user_password << endl;
    }
    //This function compares given username and password with the ones in the file
    bool Compare_Info(string a, string b)
    {
        if(user_name == a && user_password == b)
            return true;
        return false;
    }
    string GetUserName()
    {
        return user_name;
    }
};

//This class is for keeping record of current user
class CurrentUser{
private:
    User current_user;
    Books *books;
    int no_of_books;
public:
    void setCurrentUser(string a, string b)
    {
        current_user.Set_info(a,b);
    }
    //Loading all the books in the class
    void LoadBooks()
    {
        ifstream fin("BookList.txt");
        fin >> no_of_books;

        books = new Books[no_of_books];
        for(int i=0; i<no_of_books; i++)
            fin >> books[i].ID >> books[i].book_name >> books[i].book_type >> books[i].book_author;
        fin.close();
    }
    //User log in
    bool User_Log_in()
    {
        int no_of_users;
        string temp_name, temp_password;
        ifstream fin("UserList.txt");
        fin >> no_of_users;

        User *current_users = new User[no_of_users];
        for(int i=0; i<no_of_users; i++)
        {
            fin >> temp_name >> temp_password;
            current_users[i].Set_info(temp_name,temp_password);
        }

        fin.clear();

        cout << "Please enter your username :\t";
        cin >> temp_name;

        cout << "Please enter your password :\t";
        cin >> temp_password;

        bool check = false;
        for(int i=0; i<no_of_users; i++)
        {
            if(current_users[i].Compare_Info(temp_name,temp_password))
            {    
                check = true;
            }
        }

        if(check)
        {
            setCurrentUser(temp_name,temp_password);        
            cout << "CONGRATS!!! Logged in as username " << temp_name << "." << endl;
            return true;
        }
        else
        {
            cout << "OOPS! Your credentials doesn't match.\n";
            system("pause");
            system("cls");
            User_Log_in();
        }

        fin.close();
        delete[] current_users;

        return false;
    }
    //This function is for viewing all the current books by the user
    void ShowBooks()
    {
        LoadBooks();
        cout << "TOTAL BOOKS PRESENT IN THE LIBRARY:\t" << no_of_books << endl << endl;
        for(int i=0; i<no_of_books; i++)
            books[i].PrintBookInfo();
    }
    //Search a book by unique ID
    void SearchBook()
    {
        int tempID;
        cout << "Enter the ID of the book you want to search :\t";
        cin >> tempID;

        int check = -1;
        for(int i=0; i<no_of_books; i++)
            if(tempID == books[i].ID)
                check = i;

        if(check != -1)
        {
            books[check].PrintBookInfo();
            cout << "Current status :\t";
            books[check].check_avaialability();
        }
        else
            cout << "\nOOPS! This book is not present in the library.\n";
    }
    //This function performs the operation of issuing a book
    void IssueBook(int& issue_book, int& issueBookID)
    {
        int tempID;
        cout << "Enter the unique ID of the book you want to issue:\t";
        cin >> tempID;

        int check = -1;
        for(int i=0; i<no_of_books; i++)
            if(tempID == books[i].ID)
                check = i;
        
        if(check != -1)
        {
            issue_book = 1;
            issueBookID = tempID;
            cout << "\nATTENTION! Your request for issuing the book with ID " << books[check].ID << " has been sent to the librarian.\n";
        }
        else
            cout << "OOPS! This ID does not match with the present books.\n";
    }
    //This function removes a particular book
    void ReturnBook(int& return_book, int& returnBookID)
    {
        int tempID;
        cout << "Enter the unique ID of the book you want to return:\t";
        cin >> tempID;

        return_book = 1;
        returnBookID = tempID;
    }
    //This function is for checking the response of issue book
    void Notification(int& issue_book, int& issueBookID)
    {
        if(issue_book == -1)
        {
            cout << "\nCONGRATS! The book with ID " << issueBookID << " is issued. Kindly check the updated lists.\n";
            issue_book = 0;
            issueBookID = 0;
        }
        else if(issue_book == -2)
        {
            cout << "\nSORRY! The book with ID " << issueBookID << " is not available.\n";
            issue_book = 0;
            issueBookID = 0;
        }
        else if(issue_book == 0)
        {
            cout << "\nNo notifications yet.\n";
        }
    }
};

void User_Registeration()
{
    int no_of_users;
    string temp_name, temp_password;
    ifstream fin("UserList.txt");
    fin >> no_of_users;

    User *current_users = new User[no_of_users+1];
    for(int i=0; i<no_of_users; i++)
    {
        fin >> temp_name >> temp_password;
        current_users[i].Set_info(temp_name,temp_password);
    }
    current_users[no_of_users].enterInformation();
    no_of_users += 1;

    ofstream fout("UserList.txt");
    fout << no_of_users << endl;

    for(int i=0; i<no_of_users; i++)
        current_users[i].Writing_file(fout);

    cout << "CONGRATS! New user added to the file.\n";

    fin.close();
    //deleting current users array for less consumption of memory
    delete[] current_users;
}

void Admin_Registeration()
{
    string admin_name;
	string password;
    ifstream fin("Admin.txt");
	fin >> admin_name >> password;

    cout << "Enter the new password:\t";
    cin >> password;

    ofstream fout("Admin.txt");
    fout << admin_name << endl << password << endl;
    
    cout << "CONGRATS! Password is changed.\n";

    fin.close();
    fout.close();
}

bool Admin_log_in()
{
    string user_name, admin_password;
    string temp_user, temp_password;

    //Opening the file for admin information
    ifstream fin("Admin.txt");
    fin >> user_name >> admin_password;
    fin.close();

    cout << "Enter username of the admin please:\t";
    cin >> temp_user;

    cout << "Enter password of the admin please:\t";
    cin >> temp_password;

    if(temp_user == user_name && temp_password == admin_password)
    {
        return true;
        cout << "WELCOME TO THE ADMIN PANEL !!!";
    }
    else
    {
        cout << "\nOOPS! Username or password is incorrect !!!\n\n";
        system("pause");
        system("cls");
        Admin_log_in();
    }
    return false;
}

void AdminMenu()
{
    Admin Librarian;
	Librarian.LoadBooks();
    int choice;
    cout << "\n\t\t\t\t---$$$---WELCOME TO LIBRARIAN PANEL---$$$---\n\n\n";

    if(Admin_log_in())
    {
        cout << "\n\n\tPRESS 0:\tPRINT Information of a book.\n"
                "\tPRESS 1:\tCHANGE a specific attribute of all books.\n"
                "\tPRESS 2:\tADD a book.\n"
                "\tPRESS 3:\tREMOVE a book.\n"
                "\tPRESS 4:\tNOTIFICATIONS.\n"
                "\tPRESS 5:\tMake a book AVAILABLE\n"
                "\tPRESS 6:\tMake a book UNAVAILABLE.\n"
                "\tPRESS 7:\tCHANGE Password or Username.\n"
                "\tPRESS 8:\tEXIT\n\n";
        cin >> choice;

        switch(choice)
        {
        case 0:
            Librarian.Print();
            break;
        case 1:
            Librarian.ChangeBook();
            break;
        case 2:
            Librarian.AddBook();
            break;
        case 3:
            Librarian.RemoveBook();
            break;
        case 4:
            Librarian.Notification(issue_book,issueBookID,return_book,returnBookID);
            break;
        case 5:
            Librarian.Available();
            break;
        case 6:
            Librarian.UnAvailable();
            break;
        case 7:
            Admin_Registeration();
            break;
        case 8:
            return;
        }
        AdminMenu();
    }
}

void UserMenuPart(CurrentUser& User)
{
    int choice;
    cout << "\n\n\tPRESS 0:\tSHOW all books.\n"
            "\tPRESS 1:\tSEARCH book.\n"
            "\tPRESS 2:\tNOTIFICATIONS.\n"
            "\tPRESS 3:\tISSUE a book.\n"
            "\tPRESS 4:\tRETURN a book.\n"
            "\tPRESS 5:\tEXIT\n\n";
    cin >> choice;

    switch(choice)
    {
    case 0:
        User.ShowBooks();
        break;
    case 1:
        User.SearchBook();
        break;
    case 2:
        User.Notification(issue_book,issueBookID);
        break;
    case 3:
        User.IssueBook(issue_book,issueBookID);
        break;
    case 4:
        User.ReturnBook(return_book,returnBookID);
        break;
    case 5:
        return;
    }
    UserMenuPart(User);
}

void MemberMenu()
{
    int choice;
    cout << "\n\t\t\t---$$$---WELCOME TO THE USER MENU---$$$---\n\n";

    cout << "\tPRESS 0 to SIGN-IN\n"
            "\tPRESS 1 to LOG-IN\n"
            "\tPRESS 2 to EXIT\n";
    cin >> choice;

    switch(choice)
    {
        case 0:
            User_Registeration();
            break;
        case 2:
            return;
        case 1:
            CurrentUser User;
            User.LoadBooks();
            if(User.User_Log_in())
            {
                UserMenuPart(User);
            }
            break;
    }
    MemberMenu();
}

int main()
{
	int choice;
    cout << "\t\t---$$$---LIBRARY MANAGEMENT SYSTEM---$$$---\t\t";
    cout << "\n\nPRESS 1:\tLIBRARIAN PANEL.\n"
            "PRESS 2:\tUSER PANEL.\n\n";
    cin >> choice;

    while(choice != 0)
    {
        if(choice == 1)
            AdminMenu();
        if(choice == 2)
            MemberMenu();
        cin >> choice;
    }

	system("pause");

 	return 0;
}