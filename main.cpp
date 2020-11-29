#include <iostream>
#include <queue>
#include <stack>
#include <list>

using namespace std;


struct Leksema {
    char type; // '(' ')' '+' '-' '*' '/'  0 - число
    double val; // Значение число
};

int getRang(char Ch) {
    if (Ch == '*' || Ch == '/') return 2;
    if (Ch == '+' || Ch == '-') return 1;
    else return 0;
}

stack<Leksema> mystack;
// qu2eue <Leksema> myqueue;
list<Leksema> myqueue;


int main() {
    char Ch;
    double x;
    int fl = 1;
    cout << "Formula: ";
    Leksema item{};
    while (true) {
        Ch = cin.peek();
        if (Ch == '\n') break;
        if ((Ch == '-' && fl) || Ch == '.' || (Ch >= '0' && Ch <= '9')) // Унарный минус или число
        {
            cin >> x;
            item.type = 0;
            item.val = x;
            myqueue.push_back(item);
            fl = 0;
            continue;
        }
        if (Ch == '-' || Ch == '+' || Ch == '*' || Ch == '/') // Знак операции
        {

            while (true) {
                int rang = 0;
                if (!mystack.empty()) rang = getRang(mystack.top().type);
                if (rang < getRang(Ch) || mystack.empty()) {
                    item.type = Ch;
                    mystack.push(item);
                    break;
                }
                myqueue.push_back(mystack.top());
                mystack.pop();

            }
            fl = 1;

        }
        if (Ch == '(') {
            item.type = Ch;
            mystack.push(item);
            fl = 1;
        }
        if (Ch == ')') {
            if (mystack.empty()) {
                cerr << "\nError () ";
                return 0;
            }
            bool flag = true;
            while (!mystack.empty()) {
                if (mystack.top().type != '(') {
                    myqueue.push_back(mystack.top());
                    mystack.pop();
                } else {
                    mystack.pop();
                    flag = false;
                    break;
                }

            }
            if (flag) // Ошибка скобка не найдена
            {
                cerr << "\nError () ";
                return 0;
            }
            fl = 0;

        }
        cin.get();
    }
    while (!mystack.empty()) {
        myqueue.push_back(mystack.top());
        mystack.pop();
    }

    for (auto pos : myqueue) if (pos.type) cout << pos.type << ' '; else cout << pos.val << ' ';

    while (!myqueue.empty()) {
        if (myqueue.front().type == 0) // Операнд число
        {
            mystack.push(myqueue.front());
            myqueue.pop_front();
        } else // Операнд знак операции
        {
            double x, y, Rez;
            if (mystack.empty()) {
                cerr << "\nError!!!";
                return 0;
            }

            if (mystack.top().type) // Операнд не число
            {
                cerr << "\nError!!!";
                return 0;
            }
            y = mystack.top().val;

            mystack.pop();
            if (mystack.size() == 0) {
                cerr << "\nError!!!";
                return 0;
            }

            if (mystack.top().type) // Операнд не число
            {
                cerr << "\nError!!!";
                return 0;
            }
            x = mystack.top().val;
            mystack.pop();
            switch (myqueue.front().type) {
                case '+':
                    Rez = x + y;
                    break;
                case '-':
                    Rez = x - y;
                    break;
                case '*':
                    Rez = x * y;
                    break;
                case '/':
                    Rez = x / y;
                    break;
                default:
                    cerr << "\nError!!!";
                    return 0;
            }
            myqueue.pop_front();
            item.type = 0;
            item.val = Rez;
            mystack.push(item);

        }
    }
    cout << "\nRez=" << mystack.top().val;

    return 0;
}