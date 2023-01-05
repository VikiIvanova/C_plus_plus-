/*Имате даден браузър, който винаги отваря даден homepage в началото. 
Можете да посещавате други url-и, да се връщате в историята даден брой стъпки 
или да се предвижвате напред в историята даден брой стъпки.

Имплементирайте класът BrowserHistory:

BrowserHistory(string homepage) Initializes the object with the homepage of the browser.
void visit(string url) Visits url from the current page. It clears up all the forward history.
string back(int steps) Move steps back in history. If you can only return x steps in the history and steps > x, 
you will return only x steps. Return the current url after moving back in history at most steps.
string forward(int steps) Move steps forward in history. If you can only forward x steps in the history and steps > x,
 you will forward only x steps. Return the current url after forwarding in history at most steps.*/

#include<list>
#include<string>

class BrowserHistory
{
    std::list<std::string> history;
    std::list<std::string>::iterator it;

    public:
    BrowserHistory(std::string homepage)
    {
        history.push_back(homepage);
        it = history.begin();
    }

    void visit(std::string url)
    {
        auto next = it;
        next++;
        history.erase(next, history.end());
        history.push_back(url);
        it++;
    }

    std::string back(int steps)
    {
        while(it != history.begin() && steps--)
        {
            it--;
        }
        return *it;
    }

    std::string forward(int steps)
    {
        while(it != --history.end() && steps--)
        {
            it++;
        }
        return *it;
    }
};