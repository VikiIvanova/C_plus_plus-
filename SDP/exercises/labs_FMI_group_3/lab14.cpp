#include <iostream>
#include <vector>
#include <unordered_map>

void printCharacterOccurences(std::string str)
{
    int charOccurencesArray[256] = {0};
    for (char c : str)
    {
        charOccurencesArray[(int)c]++;
    }
    for(int i = 0; i < 256; ++i)
    {
        if(charOccurencesArray[i] > 0)
        {
            std::cout << ((char)i) << ": " << charOccurencesArray[i] << std::endl;
        }
    }
    
    //with map
    std::unordered_map<char, int> charOccurences;
    for (char c : str)
    {
        if (charOccurences.find(c) != charOccurences.end())
        {
            //element is in the map
            charOccurences[c]++;
        }
        else
        {
            //element is not in the map
            charOccurences[c] = 1;
        }
    }

    std::unordered_map<char, int>::iterator iter = charOccurences.begin();
    while(iter != charOccurences.end())
    {
        std::pair<char, int> x = *iter;
        std::cout << x.first << ":" << x.second << std::endl;
        iter++;
    }
}

//count words
//lorem ipsum is simply dummy text of the printing and typesetting industry. lorem ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. it has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. it was popularised in the 1960s with the release of letraset sheets containing lorem ipsum passages, and more recently with desktop publishing software like aldus pagemaker including versions of lorem ipsum.

//
// Maps as configuration
//  - day of week names
//  - short day name to long day name

std::string fullDayOfWeek(std::string shortDayOfWeek)
{
    std::unordered_map<std::string, std::string> shortToFullDayOfWeek;
    shortToFullDayOfWeek["MON"] = "MONDAY";
    shortToFullDayOfWeek["TUE"] = "TUESDAY";
    shortToFullDayOfWeek["WED"] = "WEDNESDAY";
    shortToFullDayOfWeek["THU"] = "THURSDAY";
    shortToFullDayOfWeek["FRI"] = "FRIDAY";
    shortToFullDayOfWeek["SAT"] = "SATURDAY";
    shortToFullDayOfWeek["SUN"] = "SUNDAY";

    return shortToFullDayOfWeek[shortDayOfWeek];
}      

int main()
{
    printCharacterOccurences("lorem ipsum is simply dummy text of the printing");
    return 0;
}