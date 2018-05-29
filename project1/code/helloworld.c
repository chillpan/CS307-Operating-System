#include <linux/kernel.h>

asmlinkage long sys_helloworld(void){
      printk("Hello world\n");
      return 0;
}