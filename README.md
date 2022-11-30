# C++Primer第五版 习题答案

本文当作我学习C++的一个记录，这里的习题答案并不是标准答案，仅仅是我的理解，如有错误，请大家指出，谢谢！  
参考的文章会在文末列出。  
使用的系统为：ubuntu 14.04，编译器：gcc version 4.8.4（`建议使用gcc5`），编译时记得带上参数：-std=c++11，如下所示：  
```sh
$ g++ -o main main.cpp -std=c++11
$ g++ -o main main.cpp helloworld.cpp -std=c++11
```
使用 gcc4.8.4 碰到的问题：
- 正则表达式regex时（建议使用 gcc4.9 及以上版本）；
- std::hexfloat 时（建议使用 gcc5 及以上版本）；
- 使用 #define NDEBUG 与 assert() 时，需要使用`-D NDEBUG`参数编译；
- std::string中insert， gcc不能编译通过，[链接](ch09_Sequential_Containers/ex43.cpp)。  

[github地址（用于放置最新的源码）](https://github.com/smzztx/cpplearn)  
[CSDN目录地址](https://blog.csdn.net/shamozhizhoutx/article/details/81264498)  

## 目录
 - [第一章 开始（getting started）](ch01_Getting_Started/README.md)
- [第Ⅰ部分 C++基础]
	- [第二章 变量和基本类型（variables and basic types）](ch02_Variables_and_Basic_Types/README.md)
	- [第三章 字符串、向量和数组（Strings, Vectors, and Arrays）](ch03_Strings_Vectors_and_Arrays/README.md)
	- [第四章 表达式（Expressions）](ch04_Expressions/README.md)
	- [第五章 语句（Statements）](ch05_Statements/README.md)
	- [第六章 函数（Functions）](ch06_Functions/README.md)
	- [第七章 类（Classes）](ch07_Classes/README.md)
- [第Ⅱ部分 C++标准库]
	- [第八章 IO库（The IO Library）](ch08_The_IO_Library/README.md)
	- [第九章 顺序容器（Sequential Containers）](ch09_Sequential_Containers/README.md)
	- [第十章 泛型算法（Generic Algorithms）](ch10_Generic_Algorithms/README.md)
	- [第十一章 关联容器（Generic Algorithms）](ch11_Associative_Containers/README.md)
	- [第十二章 动态内存（Dynamic Memory）](ch12_Dynamic_Memory/README.md)
- [第Ⅲ部分 类设计者的工具]
	- [第十三章 拷贝控制（Copy Control）](ch13_Copy_Control/README.md)
	- [第十四章 操作重载与类型转换（Overloaded Operations and Conversions）](ch14_Overloaded_Operations_and_Conversions/README.md)
	- [第十五章 面向对象程序设计（Object-Oriented Programming）](ch15_ObjectOriented_Programming/README.md)
	- [第十六章 模板与泛型编程（Templates and Generic Programming）](ch16_Templates_and_Generic_Programming/README.md)
- [第Ⅳ部分 高级主题]
	- [第十七章 标准库特殊设施（Specialized Library Facilities）](ch17_Specialized_Library_Facilities/README.md)
	- [第十八章 用于大型程序的工具（Tools for Large Programs）](ch18_Tools_for_Large_Programs/README.md)
	- [第十九章 特殊工具与技术（Specialized Tools and Techniques）](ch19_Specialized_Tools_and_Techniques/README.md)

---
## 参考
最刚开始看的时候参考的是 [MISAYAONE](https://blog.csdn.net/misayaaaaa/article/details/53786215) ，后来发现github上有两个项目非常不错 [Mooophy的Cpp-Primer](https://github.com/Mooophy/Cpp-Primer) 和 [pezy的CppPrimer](https://github.com/pezy/CppPrimer) ，高级部分开始，能参考的代码就比较少了，接着又找到了两篇 [huangmingchuan的Cpp_Primer_Answers](https://github.com/huangmingchuan/Cpp_Primer_Answers
) 和 [听枫烨阁](https://blog.csdn.net/chxw098/article/details/39973555) ，我这里的习题题目大多来源于前者。碰到不会做的题目就照着写，难免有相同的地方，如有侵权马上删除。  
这里推荐一本参考书，《C++ Primer习题集》，大致看了下，讲的比较详细，我也是看[评论](https://blog.csdn.net/shamozhizhoutx/article/details/83056020#comments_23214236)才知道的。  