# C++Primer第五版 习题答案

本文当作我学习C++的一个记录，这里的习题答案并不是标准答案，仅仅是我的理解，如有错误，请大家指出，谢谢！  
参考的文章会在文末列出。  
使用的系统为：ubuntu 14.04，编译器：gcc version 4.8.4（`建议使用gcc5`），编译时记得带上参数：-std=c++11，如下所示：  
```sh
$ g++ -o main main.cpp -std=c++11
$ g++ -o main main.cpp helloworld.cpp -std=c++11
```
使用正则表达式regex时，建议使用 gcc4.9 及以上版本；使用 std::hexfloat 时，建议使用 gcc5 及以上版本；使用 #define NDEBUG 与 assert() 时，需要使用`-D NDEBUG`参数编译。  
[github地址（用于放置最新的源码）](https://github.com/smzztx/cpplearn)  
[CSDN目录地址](https://blog.csdn.net/shamozhizhoutx/article/details/81264498)  

## 目录
 - [第一章 开始（getting started）](https://blog.csdn.net/shamozhizhoutx/article/details/81264840)
- [第Ⅰ部分 C++基础]
	- [第二章 变量和基本类型（variables and basic types）](https://blog.csdn.net/shamozhizhoutx/article/details/81431681)
	- [第三章 字符串、向量和数组（Strings, Vectors, and Arrays）](https://blog.csdn.net/shamozhizhoutx/article/details/81590540)
	- [第四章 表达式（Expressions）](https://blog.csdn.net/shamozhizhoutx/article/details/81879200)
	- [第五章 语句（Statements](https://blog.csdn.net/shamozhizhoutx/article/details/82082116)
	- [第六章 函数（Functions）](https://blog.csdn.net/shamozhizhoutx/article/details/82263038)
	- [第七章 类（Classes](https://blog.csdn.net/shamozhizhoutx/article/details/82291127)
- [第Ⅱ部分 C++标准库]
	- [第八章 IO库（The IO Library）](https://blog.csdn.net/shamozhizhoutx/article/details/82560019)
	- [第九章 顺序容器（Sequential Containers）](https://blog.csdn.net/shamozhizhoutx/article/details/82731081)
	- [第十章 泛型算法（Generic Algorithms）](https://blog.csdn.net/shamozhizhoutx/article/details/82833776)
	- [第十一章 关联容器（Generic Algorithms）](https://blog.csdn.net/shamozhizhoutx/article/details/82964192)
	- [第十二章 动态内存（Dynamic Memory）](https://blog.csdn.net/shamozhizhoutx/article/details/83056020)
- [第Ⅲ部分 类设计者的工具]
	- [第十三章 拷贝控制（Copy Control）](https://blog.csdn.net/shamozhizhoutx/article/details/84206577)
	- [第十四章 操作重载与类型转换（Overloaded Operations and Conversions）](https://blog.csdn.net/shamozhizhoutx/article/details/90543341)
	- [第十五章 面向对象程序设计（Object-Oriented Programming）](https://blog.csdn.net/shamozhizhoutx/article/details/90543021)
	- [第十六章 模板与泛型编程（Templates and Generic Programming）](https://blog.csdn.net/shamozhizhoutx/article/details/90524494)
- [第Ⅳ部分 高级主题]
	- [第十七章 标准库特殊设施（Specialized Library Facilities）](https://blog.csdn.net/shamozhizhoutx/article/details/90523788)
	- [第十八章 用于大型程序的工具（Tools for Large Programs）](https://blog.csdn.net/shamozhizhoutx/article/details/90521446)
	- [第十九章 特殊工具与技术（Specialized Tools and Techniques）](https://blog.csdn.net/shamozhizhoutx/article/details/90490237)

---------
最刚开始看的时候参考的是 [MISAYAONE](https://blog.csdn.net/misayaaaaa/article/details/53786215) ，后来发现github上有两个项目非常不错 [Mooophy的Cpp-Primer](https://github.com/Mooophy/Cpp-Primer) 和 [pezy的CppPrimer](https://github.com/pezy/CppPrimer) ，高级部分开始，能参考的代码就比较少了，接着又找到了两篇 [huangmingchuan的Cpp_Primer_Answers](https://github.com/huangmingchuan/Cpp_Primer_Answers
) 和 [听枫烨阁](https://blog.csdn.net/chxw098/article/details/39973555) ，我这里的习题题目大多来源于前者。碰到不会做的题目就照着写，难免有相同的地方，如有侵权马上删除。
