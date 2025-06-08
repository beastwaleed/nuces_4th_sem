#include <iostream> 
#include <unistd.h> 
using namespace std; 
int main()  
{ 
int num; 
cout<<"Please enter any digit\n"; 
cin>>num; 
if(num>0) 
{ 
fork();

cout<<"The number is positive\n"; 
} 
else if(num<0) 
{ 
fork(); 
cout<<"The number is Negative\n"; 
} 
else 
{ 
fork(); 
cout<<"The number is Zero\n"; 
}   

return 0;
} 