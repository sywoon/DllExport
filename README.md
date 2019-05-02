# DllExport
windows导出dll的两种方式


## 函数声明加前缀
```
  创建dll：
__declspec(dllexport)
  extern "C" __declspec(dllexport) int TestAdd(int a, int b)
  {
	return a+b;
  }
  
  exe中使用：
  方式1： 获取进程地址
    HINSTANCE hmod = LoadLibrary("add.dll");
    lpproc = (TESTDLL)GetProcAddress(hmod, "TestAdd");
    FreeLibrary(hmod);
    
    int nResult = (*lpproc)(11, 22);
  
  方式2： 通过静态lib方式
    #pragma comment(lib, "add.lib")
    TestAdd(10, 20);  直接用函数名调用
  
  创建dll和exe：
    ::dll 
    cl /c add.c /D DLL_EXPORTS /D _USING_V110_SDK71_ 
    link add.obj /dll /out:add.dll

    ::exe  动态dll方式
    cl /D _USING_V110_SDK71_ main_dll.c
    link add.obj main_dll.obj /out:main_dll.exe

    ::exe  静态lib方式
    cl /D _USING_V110_SDK71_ main_lib.c
    link add.obj main_lib.obj /out:main_lib.exe
  
  具体查看demo1
```


## 模块定义文件
```
.def
    LIBRARY add
    EXPORTS
        TestAdd    ;TestAdd @1
  
  创建dll和exe：
    ::dll 
    cl /c add.c  /D _USING_V110_SDK71_ 
    link add.obj /dll /def:add.def /out:add.dll

    ::exe  动态dll方式
    cl /D _USING_V110_SDK71_ main_dll.c
    link add.obj main_dll.obj /out:main_dll.exe

    ::exe  静态lib方式
    cl /D _USING_V110_SDK71_ main_lib.c
    link add.obj main_lib.obj /out:main_lib.exe
    
  vs中设置def：
    Linker->Input->Module Definition File
```
导出函数 可以添加序号[doc](https://docs.microsoft.com/zh-cn/previous-versions/visualstudio/visual-studio-2008/e7tsx612(v=vs.90))



## def和dllexport的区别
```
  1. 可以在.def文件中的导出函数名后加@n，表示要导出函数的序号为n
    （在进行函数调用时，这个序号将发挥其作用）
    是否加后缀  通过GetProcAddress(hmod, "TestAdd")方式 都可行
    
  2. 若通过dllexport方式
    当用于其他语言 vb delphi等 就获取不了地址了 需要额外加参数
    __declspec(dllexport) int __stdcall Add()
    会转换为Add@0

    Declare Function Add Lib "add.dll" Alias "TestAdd@0" () As Long
    @后面的数由于参数类型不同而可能不同
```
















