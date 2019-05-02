#include <windows.h>
#include <stdio.h>


//typedef与函数TestAdd类型相同的函数指针为TESTDLL
typedef int (_cdecl * TESTDLL)(int a, int b);


// 加载动态链接库(**.dll)并调用其对外接口TestAdd
void call()
{
    HINSTANCE hmod;
    hmod = LoadLibrary("add.dll");
    if(NULL == hmod)
    {
        printf("加载add.dll失败\n");
        return;
    }
    
    //定义一个与函数TestFuction类型相同的函数指针lpproc
    TESTDLL lpproc;
    //搜索add.dll中函数名为TestAdd的对外接口
    lpproc = (TESTDLL)GetProcAddress(hmod, "TestAdd");
    if(NULL == lpproc)
    {
        printf("GetProcAddress失败\n");
        return;
    }
    
    //在恰当的时候释放动态链接库**.dll
    FreeLibrary(hmod);
    
    int nResult = (*lpproc)(11, 22);
    printf("%d\n", nResult);
}

int main()
{
    call();

	printf("put any key to exit\n");
	getchar();
    return 0;
}



