#include <iostream> 
#include <unistd.h> 
 
using namespace std; 
 
int main()  
{ 
    int pid = fork();   
 
    if (pid > 0)  
    {     
        for (int i = 1; i <= 4; i++)  
        { 
 
             
                fork();  

                cout << "i = " << i << ", I am a process and my id is " << getpid() << "\n"; 
} 
}  
else if (pid == 0)  
{ 
}  
cout << "i = " << 1 << ", I am a process and my id is " << getpid() << "\n"; 
return 0; 
} 