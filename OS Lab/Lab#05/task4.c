#include <iostream> 
#include <unistd.h> 
using namespace std; 
int main()  
{ 
int p1 = fork(); 
if (p1 == 0)  
{ 
cout << "Child1  my pid is " << getpid() << ", and my parent  pid is " << getppid() << endl;

}  
else if (p1 < 0)  
{ 
     cout << "fork fail for children 1\n"; 

}  
else  
{ 
    int p2 = fork(); 

    if (p2 == 0)  
    { 
        cout << "Child2 having pid " << getpid() << ", and my parent pid is " << getppid() << endl;       
    }  
    else if (p2 > 0)  
    { 
         cout << "Parent P PID is " << getpid() << ", and i have two children with pids " << p1 << " and " << p2 << endl; 
    }  
    else  
    { 
                 cout << "fork fail for children 2\n"; 
    } 
} 
return 0; 
}