#include <iostream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;


// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
string cleanToken(string s) 
{
    bool check = false;
    if (s.empty()) 
    {
        return "";
    }
    for (char &c : s)
    {
        if (isalpha(c))
        {
            check = true;
            break;
        }
    }
    if (check == false)
    {
        return "";
    }

    // Convert to lowercase
    for (char &c1 : s) 
    {
        c1 = tolower(c1);
    }

    // Remove punctuation from the beginning
    while (!s.empty() && ispunct(s.front())) 
    {
        s.erase(0, 1);
    }

    // Remove punctuation from the end
    while (!s.empty() && ispunct(s.back())) 
    {
        s.pop_back();
    }
    return s;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
set<string> gatherTokens(string text) 
{
    set<string> tokens;
    std::istringstream iss(text);
    std::string word;
    string clean;

    while (iss >> word) 
    {
        // Push the word into the set
        clean = cleanToken(word);
        if (!clean.empty())
        {
            tokens.insert(cleanToken(word));
        }
    }
    
    return tokens;  // TODO:  update this.
}

int buildIndex(string filename, map<string, set<string>>& index) 
{
    string URL;
    string data;
    int pages = 0;
    ifstream file(filename);

    // if the file was not available, show the message and return to the main menu
    if (!file.is_open()) {
        cout << "Invalid filename." << endl;
        return 0;
    }

    // loop until the end of file
    while (getline(file, URL) && getline(file, data)) 
    {
        set<string> data1 = gatherTokens(data);

        // Remove any empty strings from data1
        data1.erase("");

        // Insert each URL into the corresponding word's set
        for (const string& word : data1) 
        {
            index[word].insert(URL);
        }

        ++pages;
    }

    // Remove entries with an empty key (if any)
    index.erase("");

    return pages;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) 
{
    set<string> result;
    set<string> data;
    vector<string> query;
    set<string> result1;
    set<string> result2;

    std::istringstream iss(sentence);
    std::string word;
    string clean;
    bool first = false;

    while (iss >> word) 
    {
        if (first == false)
        {
            clean = cleanToken(word);
            if (!clean.empty())
            {
                query.push_back(cleanToken(word));
            }
            first = true;
        }
        
        else
        {
            if (word[0] == '+')
            {
                query.push_back("+");
            }
            else if(word[0] == '-')
            {
                query.push_back("-");
            }
            else
            {
                query.push_back(" ");
            }
            
            clean = cleanToken(word);
            if (!clean.empty())
            {
                query.push_back(cleanToken(word));
            }    
        }
    }
    
    for (int i = 0; i < query.size(); i++)
    {
        for (auto it = index.begin(); it != index.end(); ++it) 
        {
            string key = it->first;
            data = it->second;
            
            if (query.at(i) == key)
            {
                result.insert(data.begin(), data.end());
            }    
        }
    }

    // else if (query.size() == 3)
    // {
        
    //     if (query[1] == " ")
    //     {
    //         for (auto it = index.begin(); it != index.end(); ++it) 
    //         {
    //             string key = it->first;
    //             data = it->second;
                
    //             if (query[0] == key)
    //             {
    //                 result1 = data;
    //             }
    //             else if (query[2] == key)
    //             {
    //                 result2 = data;
    //             }
    //         }
    //         result.insert(result1.begin(), result1.end());
    //         result.insert(result2.begin(), result2.end());
    //     }       
        
    // }
    
    return result;
}


void searchEngine(string filename) 
{
    map<string, set<string>> index;
    string key;
    set<string> result;
    string sentence;

    int pages = buildIndex(filename, index);
    int words = 0;
    cout << "Stand by while building index..." << endl;
        
    for (auto it = index.begin(); it != index.end(); ++it) 
    {
        key = it->first;
        ++words;
    }
           
    cout << "Indexed " << pages << " pages containing " << words << " unique terms" << endl;
    cout << endl;
    cin.ignore();
    
    do
    {  
        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, sentence);
        
        if (sentence.empty())
        {
            break;
        }
        result = findQueryMatches(index, sentence);
        cout << "Found " << result.size() << " matching pages" << endl;
        
        for (string k : result)
        {
            cout << k << endl;
        }
        cout << endl;
    
    }while(true);
    cout << "Thank you for searching!" << endl;        
}


