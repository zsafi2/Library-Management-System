#include <iostream>
#include <string>
#include <cctype>
#include <set>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>

using namespace std; 

string cleanToken(string s) 
{
    if (s.empty()) 
    {
        return s;
    }

    // Convert to lowercase
    for (char &c : s) 
    {
        c = tolower(c);
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

    if (s.empty() || !isalpha(s.front()) || !isalpha(s.back())) 
    {
        return "";
    }

    return s;
}

int main()
{
    string sentence;
    getline(cin, sentence);
    vector<string> query;
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
    for (string i : query)
    {
        cout << i << ",";
    }
    return 0;
}