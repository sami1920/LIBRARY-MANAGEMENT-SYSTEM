# LIBRARY-MANAGEMENT-SYSTEM

It consists of two panels: Librarian and the student panel.

LIBRARIAN PANEL:
1.Current username of librarian is "admin" and password is "0000" which can be changed.
2.This program allows the librarian to keep the record of all the books in the file "BookList.txt".
3.Librarian can add, remove, edit the attributes of books.
4.It gives a notification area to librarian in which updates of issued and returned books are managed.
5.Librarian has the option to allow/deny the issue of a book by checking the avaialability of that book.
6.Any change including password and attribute of a book also updates the files.
7.The username and password of the librarian is saved in a file named "Admin.txt".

STUDENT PANEL:
1.A student can create a new account at the library.
2.Every student must enter correct username and password before logging in.
3.Username and password of every student is stored in a file named "UserList.txt".
4.A student can print list of all current boks in library with details and current status of availability.
5.A student can search for a book using its unique ID.
6.When a book is asked to be issued by its unique ID, the request is sent to the librarian.
7.If the librarian approves the request, then that book is removed from "BookList.txt" and added to list of issued books in a file named "IssueBookList.txt".
8.If a user wants to return a book by its unique ID, the book is removed from "IssueBookList.txt" and added to "BookList.txt".
9.When librarian approves request for issuing a book, the student gets a notification.

NOTE:
1.All the data regarding books and users is dynamilcally allocated and less memory is consumed to make the software more faster.
2.Code is properly indented and the panel is USER-FRIENDLY and easy to use.
3.All of the code is readable and can be CHANGED according to the need.
4.INTERFACE is colored for better view.

Prepared by: THE MIND HACKERS
1.Muhammad Sami Shafique
2.Faiq Hassan
3.Abdullah Ahmad

