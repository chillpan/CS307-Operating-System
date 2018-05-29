#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>

#define SYS_Helloworld   332  
//same as defined before

int main(){
   long int s = syscall(SYS_Helloworld);
   printf("System call : sys_helloworld returned %li \n",s);
   for (int i = 0 ; i < 10 ; i++)
     syscall(SYS_Helloworld);
   return 0;
}
