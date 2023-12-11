// Name: Zaheer Safi
// Date: 09/04/2023
// CS_251 Project_1 : Building a Library Managment System

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void printMenu();
void Add_Entries(vector<string> & titles, vector<string> & ISBN_num, vector<int> & status);
void Display_library(const vector<string> titles, const vector<string> ISBN_num, const vector<string> status_string);
void Clear_library (vector<string> & titles, vector<string> & ISBN_num, vector<int> & status, vector<string> status_string,
                    int & total_books, int & In_library, int & checked_out, int & on_loan, int & unknown, int & other);
void Load_library(vector<string> & titles, vector<string> & ISBN_num, vector<int> & status);
void Output_library(vector<string> & titles, vector<string> & ISBN_num, vector<int> & status);
void Checkout_status(const vector<int> & status, int total_books, int In_library, int checked_out, int on_loan, int unknown, int other);
void Search_library(const vector<string> & titles, const vector<string> & ISBN_num, const vector<string> & status_string);
void vector_status_to_string(vector<int> & status, vector<string> & status_string);
void remove_library (vector<string> & titles, vector<string> & ISBN_num, vector<int> & status, vector<string> status_string, 
                    int & total_books, int & In_library, int & checked_out, int & on_loan, int & unknown, int & other);
void Invalid_ISBNs (vector<string> & titles, vector<string> & ISBN_num, vector<string> & status_string);


int main()
{
    string command; // store the command
    
    vector<string> titles; // vector to hold the titles
    vector<string> ISBN_num; // vecotr to hold the ISBN numbers
    vector <int> status; // vector to hold the status of the book
    vector <string> status_string; // interpret the status numbers in to string for ouput (eg. 0 means in library)

    // to track the status of the entires in the libray managment system
    int total_books = 0;
    int In_library = 0;
    int checked_out = 0;
    int on_loan = 0;
    int unknown = 0;
    int other = 0;
    

    
    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do 
    {
        
        printMenu();
        
        // take the command from the uer
        cout << endl << "Enter a command (case does not matter): ";
        getline(cin, command);
        cout << endl;
        
        // run the functions according to user commad input
        if ((command == "a" || command == "A"))
        {
            Add_Entries(titles, ISBN_num, status);
        }
        
        else if ((command == "d" || command == "D"))
        {
            vector_status_to_string(status, status_string); // change the status integer to status string required for display function
            Display_library(titles, ISBN_num, status_string);
            status_string.clear(); // clear it if recalled
        }
        
        else if ((command == "c" || command == "C"))
        {
            vector_status_to_string(status, status_string);
            Clear_library (titles, ISBN_num, status, status_string, total_books, In_library, checked_out, on_loan, unknown, other);
        }
        
        else if ((command == "l" || command == "L"))
        {
            Load_library(titles, ISBN_num, status);
        }
        
        else if ((command == "o" || command == "O"))
        {
            Output_library(titles, ISBN_num, status);
        }
        
        else if ((command == "p" || command == "P"))
        {
            Checkout_status(status, total_books, In_library, checked_out, on_loan, unknown, other);
        }
       
        else if ((command == "s" || command == "S"))
        {
            vector_status_to_string(status, status_string);
            Search_library(titles, ISBN_num, status_string);
            status_string.clear();
        }
        
        else if ((command == "r" || command == "R"))
        {
            vector_status_to_string(status, status_string);
            remove_library(titles, ISBN_num, status, status_string, total_books, In_library, checked_out, on_loan, unknown, other);
            status_string.clear();
        }
        
        else if ((command == "i" || command == "I"))
        {
            vector_status_to_string(status, status_string);
            Invalid_ISBNs(titles, ISBN_num, status_string);
            status_string.clear();
        }
        cout << endl;

    } while (!(command == "x" || command == "X"));

    return 0;
}

// function to print the options for the user
void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}

// function to add entires to the library which asks for the title of the book, ISBN number and stores it.
void Add_Entries(vector<string> & titles, vector<string> & ISBN_num, vector<int> & status)
{
    string book_name; // to take the input of book name
    string book_ISBN; // to take the input of ISBN number
    
    cout << "What is the book title? ";
    getline(cin, book_name);
    
    // the book name should not have any commas
    if (book_name.find(',') != std::string::npos) 
    {
        cout << endl;
        cout << "The book title cannot contain commas." << endl;
    }
    
    else
    {
        titles.push_back(book_name); // otherwise add to the titles vecotr
        
        cout << endl;
        
        cout << "What is the 13-digit ISBN (with hyphens)? ";
        getline(cin, book_ISBN);
        ISBN_num.push_back(book_ISBN); // add the ISBN number to the ISBN vectors

        status.push_back(0); // add a zero to the status vector which shows the book is In library
        
        // output that the book was added
        cout << "The Following Entry Was Added" << endl;
        cout << "-----------------------------" << endl;
        cout << book_name << " --- " << book_ISBN << " --- " << "In Library" << endl;
    }
}

// function to display all the availabe entires in the library with its status
void Display_library(const vector<string> titles, const vector<string> ISBN_num, const vector<string> status_string)
{
    cout << "Your Current Library" << endl;
    cout << "--------------------" << endl;
    
    // show entires if any are availabe in the library
    if (titles.size() > 0)
    {
        for (int i = 0; i < titles.size(); i++)
        {
            cout << titles[i] << " --- " << ISBN_num[i] << " --- " << status_string[i] << endl;
        }
    }
    
    // otherwise show this message
    else
    {
        cout << "The library has no books." << endl;
    }
}

// clear all the entries in the library
void Clear_library (vector<string> & titles, vector<string> & ISBN_num, vector<int> & status, vector<string> status_string,
                    int & total_books, int & In_library, int & checked_out, int & on_loan, int & unknown, int & other)
{
    // clear all the vectors
    titles.clear();
    ISBN_num.clear();
    status.clear();
    status_string.clear();

    total_books = 0;
    In_library = 0;
    checked_out = 0;
    on_loan = 0;
    unknown = 0;
    other = 0;
    
    // output the message
    cout << "Your library is now empty." << endl;
}

// load the entires from a file
void Load_library(vector<string> & titles, vector<string> & ISBN_num, vector<int> & status)
{
    string database_name; // veriable for the database name
    string line; // veriable to store each line read from the file
    int num_lines = 0; // veriable to track how many lines were read from the file

    cout << "What database to read from? ";
    getline(cin, database_name);
    
    // open the file
    ifstream file(database_name);
    
    // if the file was not availbe show the message and return to the main menu
    if (!file.is_open()) 
    {
        cout << endl;
        cout << "Could not find the database file." << endl;
        return;  
    }
    
    // loop until the end of file
    while (!file.eof()) 
    {
        // get the whole first line and hold it in the veriable line
        getline(file, line);
        
        // Find the position of the first comma
        size_t pos1 = line.find_first_of(',');
        
        // if there is no comma store the default values for it
        if (pos1 == string::npos) 
        {
            ISBN_num.push_back("000-0-00-000000-0"); // Default ISBN
            titles.push_back(line);
            status.push_back(0);
        }
        
        else
        {
            // add the title which should be mentioned before the first comma in the file
            titles.push_back(line.substr(0, pos1));
            
            // if there is no string after the first comma store the default values for ISBN number and the status 
            if ((pos1 + 1) == string::npos)
            {
                ISBN_num.push_back("000-0-00-000000-0"); // Default ISBN
                status.push_back(0); // default value (in Library)
            }
            
            // if there is string after the first comma
            else
            {
                // find the position of the second comma but this time the line starts from the first comma
                line = line.substr(pos1 + 2);
                size_t pos2 = line.find_first_of(',');
                
                // if there is no second comma store the ISBN number and default for the status
                if (pos2 == string::npos)
                {
                    ISBN_num.push_back(line);
                    status.push_back(0);
                }
                
                // otherwise if there is a second comma
                else
                {
                    ISBN_num.push_back(line.substr(0, pos2)); // store the value of ISBN after the first comma until the second one
                    
                    line = line.substr(pos2 + 2); // now the line starts after the second comma
                    status.push_back(stoi(line)); // change the number from string to a integer and store in the status
                }
            } 
        }
        
        ++num_lines;   
    }
    
    file.close(); // close the file
    cout << endl;
    
    cout << "Read in " << num_lines << " lines from the file." << endl; // output the number of lines that were read
}

// output all the entires in the library to anoter file instead of console
void Output_library(vector<string> & titles, vector<string> & ISBN_num, vector<int> & status)
{
    string database_name;
    cout << "What database to read from? ";
    getline(cin, database_name);
    
    // make a newfile with user input database_name
    ofstream file(database_name);
    
    // if the file did not open show the message and return to the menu
    if (!file.is_open()) 
    {
        cout << "Failed to open the CSV file." << endl;
        return;
    }
    
    // output every entry in the library with the specfic format
    for (int i = 0; i < titles.size(); i++)
    {
        file << titles[i] << ", " << ISBN_num[i] <<", " << status[i] << endl;
    }
    
    file.close(); // close file
}

void Checkout_status(const vector<int> & status, int total_books, int In_library, int checked_out, int on_loan, int unknown, int other)
{
    total_books = status.size(); // number of total books is equal to the number of values stored in the status
    
    // store the values in the veraibles accordingly
    for (int i : status) 
    {
        if (i == 0) 
        {
            In_library++;
        }
        
        else if (i == 1) 
        {
            checked_out++;
        }
        
        else if (i == 2)
        {
            on_loan++;
        }
        
        else if (i == 3)
        {
            unknown++;
        }
        
        else
        {
            other++;
        }   
    }

    // ouput the library stas
    cout << "Your Current Library's Stats" << endl;
    cout << "----------------------------" << endl;
    cout << "Total Books: " << total_books << endl;
    cout << "   In Library: " << In_library << endl;
    cout << "   Checked out: " << checked_out << endl;
    cout << "   On loan: " << on_loan << endl;
    cout << "   Unknown: " << unknown << endl;
    cout << "   Other: " << other << endl;
    
}

// function to search in the library
void Search_library(const vector<string> & titles, const vector<string> & ISBN_num, const vector<string> & status_string)
{
    
    // veriable for user choice to take the book name and books ISBN input
    string choice; 
    string Book_name;
    string Book_ISBN;
    int num = 0; // to find if any book entires were found matching the user input
    
    cout << "Would you like to search by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, choice);
    
    // if th user choses to search by book name
    if (choice == "1")
    {
        // take the input of book name
        cout << endl;
        cout << "Enter the book name: ";
        getline(cin, Book_name);
        cout << endl;
        
        // search in the book titles vector from right to left to find teh newest entry
        for (int i = titles.size() - 1; i >= 0; i--)
        {
            // if the book title in vector is the same as the user input show the message and break
            if (titles[i] == Book_name)
            {
                cout << "The Following Are Your Search Results" << endl;
                cout << "-------------------------------------" << endl;
                cout << titles[i] << " --- " << ISBN_num[i] << " --- " << status_string[i] << endl;
                num = 1;
                break;
            }
        }
    
        // if no entry was found according to the user input show the message
        if (num == 0)
        {
            cout << "The Following Are Your Search Results" << endl;
            cout << "-------------------------------------" << endl;
            cout << "No matching entry found in the library." << endl;
        }
    }
    
    // if the user chooses to search by ISBN numbers
    else if (choice == "2")
    {
        // take the ISBN number from the user
        cout << endl;
        cout << "Enter the book 13-digit ISBN (with dashes): " ;
        getline(cin, Book_ISBN);
        cout << endl;
        
        // search in the ISBN vector to find a match and print the message
        for (int i = ISBN_num.size() - 1; i >= 0; i--)
        {
            if (ISBN_num[i] == Book_ISBN)
            {
                cout << "The Following Are Your Search Results" << endl;
                cout << "-------------------------------------" << endl;
                cout << titles[i] << " --- " << ISBN_num[i] << " --- " << status_string[i] << endl;
                num = 1;
                break;
            }
        }
    
        // if the entry did not match output the message
        if (num == 0)
        {
            cout << "The Following Are Your Search Results" << endl;
            cout << "-------------------------------------" << endl;
            cout << "No matching entry found in the library." << endl;       
        }
    }

    // if the user inputs anything except the given options
    else
    {
        cout << endl;
        cout << "Invalid search by choice option." << endl;
    }
}

// change all the values in status vecot to status string vecotr
void vector_status_to_string(vector<int> & status, vector<string> & status_string)
{
    // add to status_string vecotr according to the number the status vecotr
    for(int i : status)
    {
        if (i == 0)
            status_string.push_back("In Library");
        else if (i == 1)
            status_string.push_back("Checked Out");
        else if (i == 2)
            status_string.push_back("On Loan");
        else if (i == 3)
            status_string.push_back("Unknown State");
        else
            status_string.push_back("Invalid State");        
    }
}

// remove an item from the library
void remove_library (vector<string> & titles, vector<string> & ISBN_num, vector<int> & status, vector<string> status_string, 
                    int & total_books, int & In_library, int & checked_out, int & on_loan, int & unknown, int & other)
{
    // veriable for user choice to take the book name and books ISBN input
    string choice;
    string Book_name;
    string Book_ISBN;
    int num = 0; // veriable to find if any matching entreis were found
    
    cout << "Would you like remove by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, choice);
    
    // if the user to choses to remove entry by book name
    if (choice == "1")
    {
        cout << "Enter the book name: ";
        getline(cin, Book_name);
        cout << endl;
        
        // search in the book title vecotr
        for (int i = titles.size() - 1; i >= 0; i--)
        {
            if (titles[i] == Book_name)
            {
                cout << "The Following Entry Was Removed From The Library" << endl;
                cout << "------------------------------------------------" << endl;
                cout << titles[i] << " --- " << ISBN_num[i] << " --- " << status_string[i] << endl;
                
                // remove the item from each vetor and the total of books
                titles.erase(titles.begin() + i);
                ISBN_num.erase(ISBN_num.begin() + i);
                status.erase(status.begin() + i);
                status_string.erase(status_string.begin() + i);
                --total_books;
                
                // find the status of the book and reduce accordingly
                if (status[i] == 0)
                    --In_library;
                else if (status[i] == 1)
                    --checked_out;
                else if (status[i] == 2)
                    --on_loan;
                else if (status[i] == 3)
                    --unknown;
                else
                    --other;
                
                num = 1; // book removed
                break; // break
            }
        }
    
        // book name was not in the book titles vecotr
        if (num == 0)
        {
            cout << "The Following Entry Was Removed From The Library" << endl;
            cout << "------------------------------------------------" << endl;
            cout << "No matching entry found in the library." << endl;
        }
    }
    
    // user to choses to search by ISBN numbers do the same thing as search in book tiltes vector
    else if (choice == "2")
    {
        cout << "Enter the book 13-digit ISBN (with dashes): " ;
        getline(cin, Book_ISBN);
        cout << endl;
        
        for (int i = ISBN_num.size() - 1; i >= 0; i--)
        {
            if (ISBN_num[i] == Book_ISBN)
            {
                cout << "The Following Entry Was Removed From The Library" << endl;
                cout << "------------------------------------------------" << endl;
                cout << titles[i] << " --- " << ISBN_num[i] << " --- " << status_string[i] << endl;
                
                titles.erase(titles.begin() + i);
                ISBN_num.erase(ISBN_num.begin() + i);
                status.erase(status.begin() + i);
                status_string.erase(status_string.begin() + i);
                --total_books;
                
                if (status[i] == 0)
                    --In_library;
                else if (status[i] == 1)
                    --checked_out;
                else if (status[i] == 2)
                    --on_loan;
                else if (status[i] == 3)
                    --unknown;
                else
                    --other;
                
                num = 1;
                break;
            }
        }
    
        if (num == 0)
        {
            cout << "The Following Entry Was Removed From The Library" << endl;
            cout << "------------------------------------------------" << endl;
            cout << "No matching entry found in the library." << endl;       
        }
    }

    // if wrong option was selected
    else
    {
        cout << endl;
        cout << "Invalid remove by choice option." << endl;
    }
}

// Function to calculate the ISBN-13 check digit
void Invalid_ISBNs (vector<string> & titles, vector<string> & ISBN_num, vector<string> & status_string)
{
    vector<string> ISBN_no_hyphen; // vector to store the ISBN numbers after the hyphens are remvoed
    int invalid_entries = 0; // to find if there is a invalid Entry

    cout << "The Following Library Entries Have Invalid Data" << endl;
    cout << "-----------------------------------------------" << endl;
    
    // if the ISBN number vector is empty
    if (ISBN_num.empty())
    {
        cout << "The library has no books." << endl;
    }
    
    else
    {
        // remove the hyphen from the ISBN numbers and add to the vector introduced above
        for (string i : ISBN_num)
        {
            string hyphen_removed = "";
            for (char c : i)
            {
                if (c != '-')
                {
                    hyphen_removed += c;
                }  
            }
            ISBN_no_hyphen.push_back(hyphen_removed);
        }
        
        for (int j = 0; j < ISBN_no_hyphen.size(); j++)
        {
            int check1 = 0; // veriable to hold the multiplication of every number in the odd position by 1
            int check2 = 0; // veriable to hold the multiplication of every number in the even position by 3
            int check = 0; // veriable to check the validilty

            // if the ISBN numbers has 13 digits we need to apply the check digits method on it
            if (ISBN_no_hyphen[j].size() == 13)
            {
                // check the status if it is invalid the ISBN number doesnt need to be checked
                if (status_string[j] == "Invalid State")
                {
                    cout << titles[j] << " --- " << ISBN_num[j] << " --- " << "Invalid State" << endl;
                    invalid_entries = 1; // invalid entry found
                }
                
                else
                {
                    // multiplication of every number in the odd position by 1 and adding it
                    int check1 = (ISBN_no_hyphen[j][0] - '0') + (ISBN_no_hyphen[j][2] - '0') + (ISBN_no_hyphen[j][4] - '0') 
                            + (ISBN_no_hyphen[j][6] - '0') + (ISBN_no_hyphen[j][8] - '0') + (ISBN_no_hyphen[j][10] - '0');

                    // multiplication of every number in the even position by 3 and adding it
                    int check2 = ((ISBN_no_hyphen[j][1] - '0') + (ISBN_no_hyphen[j][3] - '0') + (ISBN_no_hyphen[j][5] - '0') 
                            + (ISBN_no_hyphen[j][7] - '0') + (ISBN_no_hyphen[j][9] - '0') + (ISBN_no_hyphen[j][11] - '0')) * 3;
                    
                    // applying the check digit method
                    int check = 10 - ((check1 + check2) % 10);
                    
                    // according to the method if the value turned out to be ten change i to zero 
                    if (check == 10)
                    {
                        check = 0;
                    }
                    
                    // if the last value in the ISBN number is no equal to check digit it is invalid entry ouput it
                    if (check != (ISBN_no_hyphen[j][12] - '0'))
                    {
                        cout << titles[j] << " --- " << ISBN_num[j] << " --- " << status_string[j] << endl;
                        invalid_entries = 1; // invalid entry found
                    }
                }
            }
                
            // if the ISBN is not 13 digits output it as ivalid entry
            else
            {
                cout << titles[j] << " --- " << ISBN_num[j] << " --- " << status_string[j] << endl;
                invalid_entries = 1;
            }
        }
        
        // if no invalid entries were found
        if (invalid_entries == 0)
        {
            cout << "The library has no invalid entries." << endl;
        }
    }   
}