#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"

extern int a();

int main()
{
    printf("Hello World!\n");
    printf("你好世界！\n");
    a();
    system("pause");    // 防止运行后自动退出，需头文件stdlib.h
    return 0;
}