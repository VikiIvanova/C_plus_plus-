/*Искаме да създадем статична структура от данни построена върху масив, 
която за константно време по индекс ни връща стойността на първия елемент 
намиращ се вляво от този индекс и имащ стойност по - голяма или равна от елемента на дадения индекс.
Пример:
[1, 4, 3, 8, 12, 7]
getMinLeft(0) -> -1 // няма по - голям елемент от 1 в негово ляво
getMinLeft(2) -> 4 // 4 е първия елемент по - голям от arr[2] = 3
getMinLeft(5) -> 12 // 12 е първия елемент по - голям от arr[5] = 7*/

#include <iostream>
#include <stack>
#include <vector>

class firstLeftGreaterElement
{
    private:
    std::vector<int> data;
    void init(const std::vector<int>& v)
    {
        std::stack<int> monotonicStack;
        data.resize(v.size());
        for(size_t i = 0; i < v.size(); ++i)
        {
            while(!monotonicStack.empty() && monotonicStack.top() < v[i])
            {
                monotonicStack.pop();
            }
            data[i] = monotonicStack.empty() ? -1 : monotonicStack.top();
            monotonicStack.push(v[i]);
        }
    }
    public:
    firstLeftGreaterElement(const std::vector<int>& v)
    {
        init(v);
    }
    int getFisrtLeftGreaterElement(size_t idx) const
    {
        return data[idx];
    }
};

int main()
{
    std::vector<int> example {4, 7, 2, 3, 12, 6, 4, 13};
    std::vector<int> example2 {1, 4, 3, 8, 12, 7};

    firstLeftGreaterElement f(example);
    firstLeftGreaterElement s(example2);

    for(size_t i = 0; i < example.size(); ++i)
    {
        std::cout << f.getFisrtLeftGreaterElement(i) << " ";
    }
    std::cout << std::endl;

    std::cout << s.getFisrtLeftGreaterElement(0) << " " << s.getFisrtLeftGreaterElement(2) << " " << s.getFisrtLeftGreaterElement(5);

    return 0;
}