# C++ 笔记

## 1. 编译命令

程序 g++ 是将 gcc 默认语言设为 C++ 的一个特殊的版本，链接时它自动使用 C++ 标准库而不用 C 标准库。

```sh
## 利用 gcc 命令编译：(指定文件名)
gcc main.cpp -lstdc++ -o main

## 利用 g++ 命令编译：(不指定文件名)
g++ helloworld.cpp

## 运行程序：
./a.out
Hello, world!

## 利用 g++ 命令编译：(指定文件名)
g++ helloworld.cpp -o helloworld

## 运行程序：
./helloworld
Hello, world!

## 编译多个 C++ 代码文件：
g++ runoob1.cpp runoob2.cpp -o runoob
```

## 2. 命名空间
为了解决合作开发时的命名冲突问题，C++ 引入了命名空间（Namespace）的概念。
```cpp
// 变量定义
namespace Li{                       // 小李的变量定义
    FILE fp = NULL;
}

namespace Han{                      // 小韩的变量定义
    FILE fp = NULL
}

// 通过域解析操作符 :: 使用定义的变量
Li::fp = fopen("one.txt", "r");     // 使用小李定义的变量 fp
Han::fp = fopen("two.txt", "rb+");  // 使用小韩定义的变量 fp

// 通过 using 关键字声明命名空间中的一个变量
using Li::fp;
fp = fopen("one.txt", "r");         // 使用小李定义的变量 fp

// 通过 using 关键字声明整个命名空间
using namespace Li;
fp = fopen("one.txt", "r");         // 使用小李定义的变量 fp
```
完整的实例：
```cpp
#include <stdio.h>

//将类定义在命名空间中
namespace Diy{
    class Student{          // 类
    public:
        char *name;         // 类的成员变量，也叫 属性
        int age;
        float score;
  
    public:
        void say(){         // 类的成员函数，也叫 方法
            printf("%s的年龄是 %d，成绩是 %f\n", name, age, score);
        }
    };
}

int main(){
    // 通过类名创建对象，这个过程叫类的实例化，也称对象是类的一个实例
    Diy::Student stu1;     
    stu1.name = "小明";
    stu1.age = 15;
    stu1.score = 92.5f;
    stu1.say();

    return 0;
}
```

## 3. C++ 头文件和 std 命名空间

函数内部声明：
```cpp
#include <iostream>

void func(){
    // 必须重新声明
    using namespace std;
    cout<<"Hello World！"<<endl;
    func2();
}

int main(){
    // 声明标准库命名空间 std
    using namespace std;
    cout<<"Hello World！"<<endl;
    func1();

    return 0;
}
```
函数外部声明：（全局）
```cpp
#include <iostream>
// 声明标准库命名空间 std
using namespace std;
void func(){
    cout<<"Hello World！"<<endl;
}
int main(){
    cout<<"Hello World！"<<endl;
    func();
    return 0;
}
```

