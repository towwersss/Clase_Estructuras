#include <iostream>
#include <stack>
using namespace std;
#include <queue>
#include <bits/stdc++.h>
stack<int> sortStack(stack<int> &input);

int main()
{
  int var;
  stack<int> o;
  stack<int> b;
  
  for(int i=0;i<11;i++){
      var=rand() % 10;
      o.push(var);
     cout<<o.top()<<endl;
    }
      cout<<endl;
 
  b=sortStack(o);
  while(!b.empty()) {
        std::cout << b.top();
    b.pop();
    
    }   
}


stack<int> sortStack(stack<int> &input)
{
    stack<int> tmpStack;
 
    while (!input.empty())
    {
        // pop out the first element
        int tmp = input.top();
        input.pop();
 
        // while temporary stack is not empty and top
        // of stack is greater than temp
        while (!tmpStack.empty() && tmpStack.top() > tmp)
        {
            // pop from temporary stack and push
            // it to the input stack
            input.push(tmpStack.top());
            tmpStack.pop();
        }
 
        // push temp in temporary of stack
        tmpStack.push(tmp);
    }
 
    return tmpStack;
}
