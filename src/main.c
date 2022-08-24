#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"
#include "bTree.h"


extern int test1();
extern int test2();
extern int ltest();

int main()
{
    ltest();
    system("pause");    // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}