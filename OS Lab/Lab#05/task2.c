#include <iostream> 
#include<stdio.h> 
#include <unistd.h> 
using namespace std; 
int main()  
{ 
int p1=fork(); 
int p2=fork(); 
if(p1==0&&p2==0) 
{ 
} 
cout<<"I am process "<< getpid() << ".\n"; 
else if(p1>0 && p2>0) 
{ 
} 
cout<<"I am process "<< getpid() << ".\n"; 
else if(p1>0 && p2==0) 
{ 
} 
cout<<"I am process "<< getpid() << ".\n"; 
else 
cout<<"I am process "<< getpid() << ".\n"; 
return 0; 
} 