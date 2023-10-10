****

## 16.5 类的构造函数和析构函数

### 16.5.1 构造函数

1. 类的构造函数是类的一种特殊的成员函数，它会**在每次创建类的新对象时执行**。
2. **构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void**。构造函数可用于为某些成员变量设置初始值。

下面的实例有助于更好地理解构造函数的概念：

```cpp{.line-numbers}
#include <iostream>
 
using namespace std;
 
class Line
{
   public:
      void setLength( double len );
      double getLength( void );
      Line();  // 这是构造函数
 
   private:
      double length;
};
 
// 成员函数定义，包括构造函数
Line::Line(void)
{
    cout << "Object is being created" << endl;
}
 
void Line::setLength( double len )
{
    length = len;
}
 
double Line::getLength( void )
{
    return length;
}
// 程序的主函数
int main( )
{
   Line line;
 
   // 设置长度
   line.setLength(6.0); 
   cout << "Length of line : " << line.getLength() <<endl;
 
   return 0;
}

/*输出结果
Object is being created
Length of line : 6
*/
```

3. 带参数的构造函数
默认的构造函数没有任何参数，但如果需要，构造函数也可以带有参数。

```cpp{.line-numbers}
class Line
{
   public:
      void setLength( double len );
      double getLength( void );
      Line(double len);  // 这是构造函数
 
   private:
      double length;
};
 
// 成员函数定义，包括构造函数
Line::Line( double len)
{
    cout << "Object is being created, length = " << len << endl;
    length = len;
}
 
void Line::setLength( double len )
{
    length = len;
}
 
double Line::getLength( void )
{
    return length;
}
```

4. 使用初始化列表来初始化字段
使用初始化列表来初始化字段：

```cpp{.line-numbers}
/*
len是传入的参数，用len来初始化类的成员length
*/
Line::Line( double len): length(len)
{
    cout << "Object is being created, length = " << len << endl;
}

/*
上述操作等价于下面的赋值
*/
Line::Line( double len)
{
    length = len;
    cout << "Object is being created, length = " << len << endl;
}

/*
假设有一个类 C，具有多个字段 X、Y、Z 等需要进行初始化，
同理可以使用上面的语法，只需要在不同的字段使用逗号进行分隔，如下所示：
*/
C::C( double a, double b, double c): X(a), Y(b), Z(c)
{
  ....
}
```

#### 16.5.1.1 初始化成员容易犯错的地方

C++ 初始化类成员时，是按照声明的顺序初始化的，而不是按照出现在初始化列表中的顺序。

```cpp{.line-numbers}
class CMyClass {
    CMyClass(int x, int y);
    int m_x;
    int m_y;
    int m_z;
};

CMyClass::CMyClass(int x, int y) : m_y(y), m_x(m_y)
{
};
```

- 乍一看以为上面的代码将会首先做 `m_y=y`，然后做 `m_x=m_y`，最后它们有相同的值。
- **但是编译器先初始化 m_x，然后是 m_y。也就是先 `m_x = m_y`；然后`m_y = y`**，因为它们是按这样的顺序声明的。结果是 `m_x` 将有一个不可预测的值，因为`m_y`未初始化之前是一个未确定的值。
- 有两种方法避免上述情况
  1. 一个是总是按照你希望它们被初始化的顺序声明成员
  2. 第二个是，如果你决定使用初始化列表，总是按照它们声明的顺序罗列这些成员。这将有助于消除混淆。

- 再看下面的实例：

```cpp{.line-numbers}
class CMyClass {
    CMyClass(int x, int y);
    int m_x;
    int m_y;
    int m_z;
};

CMyClass::CMyClass(int x, int y，int z) : m_y(y), m_z(z), m_x(x), 
{
};
```

- 上面的例子，类的成员能够被正确地初始化，初始化的顺序是定义时候的顺序，因为各个成员之间的初始化没有什么相关性，因此互相不影响。

### 16.5.2 析构函数

1. 类的析构函数是类的一种特殊的成员函数，它会在每次删除所创建的对象时执行。
2. **析构函数的名称与类的名称是完全相同的**，只是<font color=red>在前面加了个波浪号（~）作为前缀，它不会返回任何值，也不能带有任何参数</font>。析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源。

下面的实例有助于更好地理解析构函数的概念：

```cpp{.line-numbers}
#include <iostream>
 
using namespace std;
 
class Line
{
   public:
      void setLength( double len );
      double getLength( void );
      Line();   // 这是构造函数声明
      ~Line();  // 这是析构函数声明
 
   private:
      double length;
};
 
// 成员函数定义，包括构造函数
Line::Line(void)
{
    cout << "Object is being created" << endl;
}
Line::~Line(void)
{
    cout << "Object is being deleted" << endl;
}
 
void Line::setLength( double len )
{
    length = len;
}
 
double Line::getLength( void )
{
    return length;
}
```

### 16.5.2 拷贝构造函数

拷贝构造函数是一种特殊的构造函数，它在创建对象时，是使用同一类中之前创建的对象来初始化新创建的对象。拷贝构造函数通常用于：

1. 通过使用另一个同类型的对象来初始化新创建的对象
2. 复制对象把它作为参数传递给函数
3. 复制对象，并从函数返回这个对象

```cpp
/*函数名和类名一样*/
/*函数的参数是一个已经实例化的对象引用*/
classname (const classname &obj) {
   // 构造函数的主体
}
```

#### 16.5.2.1 关于为什么当类成员中含有指针类型成员且需要对其分配内存时，一定要有总定义拷贝构造函数？

- 默认的拷贝构造函数实现的只能是浅拷贝，即直接将原对象的数据成员值依次复制给新对象中对应的数据成员，并没有为新对象另外分配内存资源。**这样，如果对象的数据成员是指针，两个指针对象实际上指向的是同一块内存空间。**

- 在某些情况下，浅拷贝回带来数据安全方面的隐患。
当类的数据成员中有指针类型时，我们就必须定义一个特定的拷贝构造函数，该拷贝构造函数不仅可以实现原对象和新对象之间数据成员的拷贝，而且可以为新的对象分配单独的内存资源，这就是深拷贝构造函数。

- 如何防止默认拷贝发生
声明一个私有的拷贝构造函数，这样因为拷贝构造函数是私有的，如果用户试图按值传递或函数返回该类的对象，编译器会报告错误，从而可以避免按值传递或返回对象。

**当出现类的等号赋值时，会调用拷贝函数，在未定义显示拷贝构造函数的情况下，系统会调用默认的拷贝函数——即浅拷贝**，它能够完成成员的一一复制。**当数据成员中没有指针时，浅拷贝是可行的。但当数据成员中有指针时，如果采用简单的浅拷贝，则两类中的两个指针将指向同一个地址，当对象快结束时，会调用两次析构函数，而导致指针悬挂现象。**所以，这时，必须采用深拷贝。

**深拷贝与浅拷贝的区别就在于深拷贝会在堆内存中另外申请空间来储存数据，从而也就解决了指针悬挂的问题。简而言之，当数据成员中有指针时，必须要用深拷贝。**

## 16.6 内联函数

内联函数inline：引入内联函数的目的是为了解决程序中函数调用的效率问题，程序在编译器编译的时候，编译器将程序中出现的内联函数的调用表达式用内联函数的函数体进行替换，而对于其他的函数，都是在运行时候才被替代。用空间代换时间的做法。所以内联函数一般都是1-5行的小函数。在使用内联函数时要留神：

1. 在内联函数内不允许使用循环语句和开关语句；
2. 内联函数的定义必须出现在内联函数第一次调用之前；
3. 类结构中所在的类说明内部定义的函数是内联函数。

## 16.7 友元函数与友元类

**类的友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员**。<font color=red>尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数。</font>

- 友元可以是一个函数，该函数被称为友元函数；
- 友元也可以是一个类，该类被称为友元类，在这种情况下，整个类及其所有成员都是友元。
- **友元函数没有 this 指针**

如果要声明函数为一个类的友元，需要在类定义中该函数原型前使用关键字 `friend`，如下所示：

```cpp{.line-numbers}

class Box_friend
{
    public:
    int demo;
}

class Box
{
   double width;
public:
   double length;
   friend void printWidth( Box box );
   /*声明类 Box_friend为类Box的友元类*/
   friend class Box_friend;
   void setWidth( double wid );
}
```

## 16.8 类中特殊成员变量的初始化问题

- 常量变量：必须通过构造函数参数列表进行初始化。
- 引用变量：必须通过构造函数参数列表进行初始化。
- 普通静态变量：要在类外通过`::`初始化。
- 静态整型常量：可以直接在定义的时候初始化。
- 静态非整型常量：不能直接在定义的时候初始化。要在类外通过"::"初始化。
