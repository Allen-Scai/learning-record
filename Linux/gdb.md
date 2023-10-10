# 1 初步分析和导出 core dump 文件

## 1.1 在设备上初步分析 core dump

以下是具体步骤：

1. cd flash/core
2. tar -zxvf d-plane...tar.gz
3. cd etc/dump/
4. gzip -cd d-plane..gz > coredump 【coredump是导出的文件名字，可随便取】
5. gdb /usr/local/sbin/d-plane coredump
6. bt【查看调用栈】
7. info local
8. p 变量

# 2 gdb 解 core_dump 文件的时候，一些奇怪问题

## 2.1 命名有 11.log 文件，生成core 或 core_out 文件不可用呢？

可以先通过 `ls -a`，看看core文件的大小是多少，如果是 `0` 的话，大概率是生成 core 的时候，没有权限读取相关文件导致的。
可能是在 `gzip -cd xx.11.log > core` 之前，没有先执行 `chmod 777 ./*`，获得对文件的操作权限。如下所示：

![](images/2023-08-09-20-15-88.png)

## 2.2 有关 slab 的问题

如下所示的调用栈，和`dp_slab_cpu_cache_recycle`有关：
由于`dp_slab_cpu_cache_recycle`是一个公共的API，因此上层谁调用的很不好追溯，这个时候就要根据复现的时候的业务情况进行排查。

![](images/2023-08-09-20-17-16.png)

假设出现 bug 的时候，打了 ftp，https，udp 流量等，建议针对每一种流量，分开分别打流，看看是否会出现问题。如果某一种流量场景下，能够较为稳定地触发问题，那么出现问题的原因，大概率与该流量场景涉及到的业务处理有关。
例如此 [BUG](https://bug.hillstonenet.com/jquery.cgi?id=374337):

根据我们的推测，让 QA 针对性地复现，出现了下面的情况：

![](images/2023-08-09-20-22-37.png)
![](images/2023-08-10-10-22-71.png)

**在`dp_alloc_pinhole()`里面用到了 pinhole_slab，因此下一步可以打印出 pinhole_slab，看看是否和 出现问题的 slab 地址一样**

`gdb` 调试得到如下结果：
**发现出现问题的 slab 是 pinhole_slab，由此可以判断和 ALG 有关系**
![](images/2023-08-10-17-18-50.png)
![](images/2023-08-10-17-18-56.png)

- 根据最新的复现情况可以发现：
  1. 与 `ftp` 相关的流量，与本 BUG 强相关

# 3 常见指令的用法

## 3.1 print 的使用方法

1. 直接 print 一个变量

   - 比如现在挂在了 0x1 这个位置上，怀疑有一个变量 val 走到这里了，可以直接 `p val`，看看这个变量打出来的地址是否是 0x1，如果是的话，这个变量可能是导致问题的原因
   - 利用 print，打印某个地址对应的变量。比如 `p 0x2001`，但是不一定能 print 出来。如果`0x2001`对应的类型是 `int*`，那么可以使用 `p (int*)0x2001`这样的方式，看看能不能打出来变量。
  
2. 打印当前处理的 core
   `p dp_current_core_id`

## 3.2 list 的用法

1. 利用 list 打印出最关键的，crash 的地方，如下所示：

11.log文件中的调用栈内容：
![](images/2023-08-09-20-09-94.png)

用 `list *0xadafe0` 打印出来后，在下面这个地方最终产生了问题：
![](images/2023-08-09-20-10-77.png)
