#include <windows.h>
#include <stdio.h>


//typedef�뺯��TestAdd������ͬ�ĺ���ָ��ΪTESTDLL
typedef int (_cdecl * TESTDLL)(int a, int b);


// ���ض�̬���ӿ�(**.dll)�����������ӿ�TestAdd
void call()
{
    HINSTANCE hmod;
    hmod = LoadLibrary("add.dll");
    if(NULL == hmod)
    {
        printf("����add.dllʧ��\n");
        return;
    }
    
    //����һ���뺯��TestFuction������ͬ�ĺ���ָ��lpproc
    TESTDLL lpproc;
    //����add.dll�к�����ΪTestAdd�Ķ���ӿ�
    lpproc = (TESTDLL)GetProcAddress(hmod, "TestAdd");
    if(NULL == lpproc)
    {
        printf("GetProcAddressʧ��\n");
        return;
    }
    
    //��ǡ����ʱ���ͷŶ�̬���ӿ�**.dll
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



