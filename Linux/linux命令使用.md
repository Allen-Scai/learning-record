---
html:
    toc: true
print_background: true
---
# Linux 常用命令

# 系统相关

## shell

执行Shell命令的解释器在Unix/Linux系统中通常是Bash（Bourne Again SHell）。Bash是许多Unix/Linux发行版的默认Shell解释器，也是最常用的Shell之一。

Bash解释器的可执行文件通常位于`/bin/bash`或`/usr/bin/bash`路径下。你可以使用`which`命令来查找Bash解释器的位置：

```shell
which bash
```

这将输出Bash解释器的完整路径。

除了Bash之外，还有其他Shell解释器可供选择，比如Korn Shell（ksh）、C Shell（csh）等。在不同的系统和发行版中，可能会有不同的默认Shell解释器。你可以使用`echo $SHELL`命令来查看当前用户的默认Shell解释器：

```shell
echo $SHELL
```

这将输出当前用户的默认Shell解释器的路径。

总之，Bash是一种常见的Shell解释器，它通常用于执行Shell命令。你可以使用`which`命令来查找Bash解释器的位置，并使用`echo $SHELL`命令来查看默认的Shell解释器。

## history

在Linux中，可以使用`!`符号来从历史记录（history）中选择并执行特定的命令。下面是几种常用的方法：

1. 执行最近使用的命令：

```shell
!!
```

这个命令会执行最近使用过的命令。

2. 执行特定序号的命令：

```shell
!序号
```

将`序号`替换为你想要执行的命令在历史记录中的序号。例如，要执行第3条命令，可以使用`!3`。

3. 执行包含特定关键字的命令：

```shell
!关键字
```

将`关键字`替换为你想要执行的命令中包含的关键字。例如，要执行包含`ssh`关键字的命令，可以使用`!ssh`。

4. 执行最近使用的以特定字符串开头的命令：

```shell
!字符串
```

将`字符串`替换为你想要执行的命令的开头字符串。例如，要执行最近使用的以`git`开头的命令，可以使用`!git`。

这些是在Linux中从历史记录中选择并执行命令的几种常用方法。通过这些方法，你可以方便地使用之前执行过的命令，提高工作效率。

# 1 Linux 网络配置

## 1.0 网络相关的配置文件

在CentOS中，网络接口相关的配置文件通常位于`/etc/sysconfig/network-scripts/`目录下。以下是一些常见的网络接口配置文件：

1. `/etc/sysconfig/network-scripts/ifcfg-<interface_name>`：这是每个接口的单独配置文件，其中`<interface_name>`是接口的名称。例如，`ifcfg-ens33`是eth0接口的配置文件。

2. `/etc/sysconfig/network`：这个文件包含全局网络配置，如默认网关、主机名等。

3. `/etc/resolv.conf`：这个文件包含DNS解析器的配置，包括DNS服务器的IP地址和搜索域。

注意：在CentOS 7及更高版本中，网络接口配置已经从`ifcfg-<interface_name>`文件移至`/etc/sysconfig/network-scripts/ifcfg-<interface_name>`文件。因此，如果您使用的是较新的CentOS版本，请确保使用正确的文件路径进行网络接口的配置。

更改完上述的文件之后，如果未生效，可以执行下列操作：

1. 重新启动系统
2. 重启网络服务：`sudo systemctl restart network`

## 1.1 添加和删除接口的IPv6地址

- 接口查看：ifconfig -a
- 路由查看：route -n
- 配置接口IP：ifconfig eth1 3.1.1.2
- **如何查看某个接口的 MAC 地址：cat /sys/class/net/eth0/address，其中的 eth0 是要查看的接口，address 是其对应的地址**

- 检查是否有 ipv6 模块：
 lsmod | grep ipv6 （不一定能看到）
 如果没有加载：modprobe ipv6

要删除和添加Linux接口上的IPv6地址，可以使用ip命令。

- 要**删除IPv6地址**，使用以下命令：

```shell
sudo ip addr del <IPv6地址>/<子网前缀长度> dev <接口名称>
```

例如，要删除eth0接口上的IPv6地址2001:db8::1/64：

```shell
sudo ip addr del 2001:db8::1/64 dev eth0
```

- 要**添加IPv6地址**，使用以下命令：

```shell
sudo ip addr add <IPv6地址>/<子网前缀长度> dev <接口名称>
```

例如，要添加eth0接口上的IPv6地址2001:db8::1/64：

```shell
sudo ip addr add 2001:db8::1/64 dev eth0
```

请注意，**以上命令需要root权限或sudo权限才能执行**。确保将<IPv6地址>替换为要添加或删除的实际IPv6地址，<子网前缀长度>替换为子网前缀的长度（如64位），<接口名称>替换为要添加或删除IPv6地址的实际接口名称（如eth0）。

使用ip命令添加或删除IPv6地址后，可以使用ip命令或ifconfig命令来验证更改是否生效。

## 1.2 Linux 添加 IPv6 路由

要在Linux上添加和删除IPv6路由，可以使用ip命令。

- 要**添加IPv6路由**，使用以下命令：

```shell
sudo ip -6 route add <IPv6网络>/<子网前缀长度> via <下一跳地址> [dev <接口名称>]
```

例如，要添加到2001:db8::/64网络的IPv6路由，通过下一跳地址2001:db8::1，通过eth0接口，**其中 dev 可选**：

```shell
sudo ip -6 route add 2001:db8::/64 via 2001:db8::1 [dev eth0]
```

- 要删除IPv6路由，使用以下命令：

```shell
sudo ip -6 route del <IPv6网络>/<子网前缀长度> via <下一跳地址> dev <接口名称>
```

例如，要删除到2001:db8::/64网络的IPv6路由，通过下一跳地址2001:db8::1，通过eth0接口：

```shell
sudo ip -6 route del 2001:db8::/64 via 2001:db8::1 dev eth0
```

请注意，以上命令需要root权限或sudo权限才能执行。确保将<IPv6网络>替换为要添加或删除的实际IPv6网络，<子网前缀长度>替换为子网前缀的长度（如64位），<下一跳地址>替换为实际的下一跳地址，<接口名称>替换为实际的接口名称（如eth0）。

使用ip命令添加或删除IPv6路由后，可以使用ip命令或route命令来验证更改是否生效。

## 1.3 Linux 接口的开启与关闭

在Linux中，可以使用ifconfig命令来关闭一个接口。ifconfig命令用于配置网络接口的参数，包括启用或禁用接口。

要关闭一个接口，可以按照以下步骤进行操作：

1. 打开终端：在Linux系统中，打开终端或控制台窗口。

2. 查看接口列表：输入ifconfig命令，查看当前系统中的网络接口列表。接口通常以"eth"或"wlan"开头，例如eth0、wlan0等。

3. 关闭接口：输入以下命令来关闭指定的接口：

   ```shell
   `sudo ifconfig <接口名> down``
   ```

   其中，<接口名>是要关闭的接口的名称，例如eth0或wlan0。需要使用sudo命令以管理员权限运行该命令。

4. 验证接口状态：再次使用ifconfig命令来验证接口是否已成功关闭。如果接口已关闭，将不再显示在接口列表中。

请注意，关闭一个接口将导致该接口无法进行网络通信。如果需要重新启用接口，可以使用以下命令：

```shell
sudo ifconfig <接口名> up
```

这将重新启用指定的接口，并使其能够进行网络通信。同样，需要使用sudo命令以管理员权限运行该命令。

# 2 实验室 Linux 设备的 DNS 配置

- <font color=greenDNS 服务器：10.160.31.231
   通过 /etc/resolv.conf 可以直接修改默认的DNS服务器
   如果该文件不存在，则创建它</font>

   可以直接在 etc/sysconfig/network-scripts下面找到对应网络接口的配置
   例如 **etc/sysconfig/network-scripts/ifconfig-eth0 就是0号网卡的配置文件**
   若遇到 无法修改网络配置文件，则要先在相关的文件夹下输入 **su root**，键入管理员密码后才能修改相关的配置文件。

# 3 Linux 文件操作

   在某个文件中查询某个字段：先输入`\`，其后再跟所需要查询的字符串即可，“n”可以切换到查询到的下一个字符串【注意要在在命令行模式下进行操作】

## 3.1 一些零散的指令

|指令|用法|作用|
|-|-|-|
|file|file file_name|能看到文件的编码，属性等等|
|chown|change owner|修改所属用户与组|
|chmod|change mode|修改用户的权限|

## 3.2 查找文件

**find 指令基本用法：`find 目录 -name FileName 指定目录进行查找文件`**

- `find . -name FileName` 在当前文件夹下查找文件，【.】表示当前文件夹

- `find ./ -name Filename` 在当前目录的子目录下查找文件

- `find ./ -name test\*`  模糊查询，用 * 代替未知字段

- `find path -mmin/-mctime -20`  查询最近20分钟/天更改过的文件【注：-mmin 分钟计时；-mctime 天计时】

## 3.3 删除文件/文件夹

1. `rm` 指令

- `rm -f FileName  删除文件`

- `rm -rf FileName  递归删除文件，即删除目录及其下面所有的文件`

2. `rmdir` 指令

- `rmdir dictionary  删除目录，但是只有其为空的时候才能够被删除`

3. `mv` 指令
   1. 在Linux中，mv命令用于移动或重命名文件和目录
      `mv <source> <destination>`, `<source>`是要移动的文件或目录的路径，<destination>是目标位置的路径。使用该命令后，源文件或目录将被移动到目标位置。

   例如，将文件 file.txt 移动到目录 destination/ 下：
      `mv file.txt destination/`

   2. mv指令也可用于**重命名文件**(实际上就是移动文件到当前目录下，并且修改名字)

# 4 vim工具的使用

- **给当前行标线和列标线：**
   在 ~/.vimrc文件中【没有则创建】添加语句【set cursorline】即可一直生效；或者在vim的命令模式下输入【set cursorline】仅在此次编辑生效

要在Vim编辑器中添加一个设置，以便在编辑时显示一个十字光标定位到当前字符，并且可以自定义该十字光标的颜色，您可以按照以下步骤进行操作：

 1. 打开Vim配置文件：

    ```shell
    vim ~/.vimrc
    ```

    如果您的配置文件不存在，则可以创建一个新文件。

 2. 在配置文件中添加以下设置行：

    ```shell
    " 启用光标行和光标列
    set cursorline
    set cursorcolumn

    " 设置光标行和光标列的颜色
    highlight CursorLine cterm=underline gui=underline
    highlight CursorColumn cterm=underline gui=underline
    ```

     - `set cursorline`：启用光标行高亮显示。
     - `set cursorcolumn`：启用光标列高亮显示。
     - `highlight CursorLine`：设置光标行的颜色。
     - `highlight CursorColumn`：设置光标列的颜色。

 3. 保存并关闭文件。

 4. 重新启动Vim或重新加载配置文件：

    ```shell
    :source ~/.vimrc
    ```

 现在，当您在Vim中编辑文件时，将会显示一个十字光标定位到当前字符，并且您可以根据需要自定义该十字光标的颜色。请注意，这些设置可能会因您使用的Vim版本或颜色主题而有所不同。

- **让文件打开就带有行数**
   在~/.vimrc文件中加入**set nu**

- **建立索引**
   使用命令**cscope -R**，可以建立当前及子目录的索引，如果加上**q**,也就是quick的意思，会加速索引查询的速度，即**cscope -Rq**

   vim跳转到函数定义处
   跳转到函数定义处，首先需要有tag文件，生成tag文件的方式为：
   在要包含所有代码的目录（其实可以直接在根目录）执行：
   ctags -R
   然后用vim打开代码，在任意一个调用函数的行，把光标放在被调用的函数名上，摁下组合键：
   Ctrl + ]
   即可跳转到该函数的定义处。
   如果要调回刚才看的地方，只要再摁下组合键：
   Ctrl + o 或者 Ctrl + t

## 4.1 vimdiff 的使用

当您使用 Vim 编辑器时，`vimdiff` 命令可以用于比较和显示两个文件的差异。以下是 `vimdiff` 的具体用法示例：

1. 比较两个文件的差异：

   ```shell
   vimdiff file1.txt file2.txt
   ```

   这个命令将会打开 Vim 编辑器，并以分屏的方式显示 `file1.txt` 和 `file2.txt` 两个文件的差异。

2. 移动光标：

   - 使用方向键或 `h`、`j`、`k`、`l` 键来在两个窗口之间移动光标。

   - 示例：

     ```shell
     h     # 光标向左移动
     l     # 光标向右移动
     j     # 光标向下移动
     k     # 光标向上移动
     ```

3. 查看差异：

   - 在光标所在的位置，使用 `]c` 命令跳转到下一个差异处。

   - 使用 `[c` 命令跳转到上一个差异处。

   - 示例：

     ```shell
     ]c     # 跳转到下一个差异
     [c     # 跳转到上一个差异
     ```

4. 同步两个文件的滚动：

   - 在光标所在的位置，使用 `Ctrl + w`，然后按 `z` 键来打开或关闭两个窗口的滚动同步。

   - 示例：

     ```shell
     Ctrl + w, z     # 打开或关闭窗口滚动同步
     ```

5. 合并差异：

   - 在光标所在的位置，使用 `do` 命令将当前差异中的内容拷贝到另一个文件。

   - 使用 `dp` 命令将当前差异中的内容拷贝到当前文件。

   - 示例：

     ```shell
     do     # 将当前差异中的内容拷贝到另一个文件
     dp     # 将当前差异中的内容拷贝到当前文件
     ```

6. 保存和退出：

   - 使用 `:w` 命令保存更改。

   - 使用 `:qa` 命令退出 `vimdiff`。

   - 示例：

     ```shell
     :w      # 保存更改
     :qa     # 退出 vimdiff
     ```

这些示例涵盖了 `vimdiff` 的主要用法，您可以根据需要进行调整和扩展。在比较文件差异时，您还可以使用 Vim 编辑器的其他功能，如搜索、替换等。您可以使用 `:help vimdiff` 命令在 Vim 中获取更多关于 `vimdiff` 的帮助信息。

## 4.2 vim 中替换字符串

在 Vim 中，你可以使用替换命令 `:s` 或者 `%s` 来替换字符串。下面是替换字符串的基本语法：

```shell
:s/要替换的字符串/替换后的字符串/[选项]

#在 Vim 替换命令中，你可以使用多种字符作为分隔符，只要它们不在要替换的字符串中出现即可。以下是一些常见的分隔符选项：

- `/`：斜杠是最常见的分隔符，也是默认的分隔符。例如：`:s/foo/bar/`。
- `#`：井号也是常用的分隔符。例如：`:s#foo#bar#`。
- `~`：波浪号也可以作为分隔符。例如：`:s~foo~bar~`。
- `@`：at 符号也可以作为分隔符。例如：`:s@foo@bar@`。
- `!`：感叹号也是可用的分隔符。例如：`:s!foo!bar!`。
- `:`：冒号也可以作为分隔符。例如：`:s:foo:bar:`。

这只是一些常见的分隔符选项，你也可以选择其他字符作为分隔符，只要它们不在要替换的字符串中出现即可。选择一个你喜欢的字符作为分隔符，以确保替换命令的可读性和清晰度。
```

其中，`要替换的字符串` 是你想要替换的文本，`替换后的字符串` 是替换后的文本内容。可选的选项可以用来指定替换的范围、标志和其他参数。

以下是一些常用的选项：

- `g`：在每一行上进行全局替换，而不仅仅是每行的第一个匹配。
- `c`：在替换之前进行确认，每次替换时都会要求确认。
- `i`：忽略大小写，进行大小写不敏感的替换。
- `e`：忽略不存在的匹配项，不显示错误信息。
- `n`：只显示匹配项的数量，不进行实际替换。

以下是一些示例：
**注意 `s`表示仅在当前行进行替换；`%s`表示在整个文件中进行替换**

- `:s/foo/bar/`：将当前行中的第一个 `foo` 替换为 `bar`。
- `:%s/foo/bar/g`：在整个文件中进行全局替换，将所有的 `foo` 替换为 `bar`。
- `:%s/foo/bar/gc`：进行全局替换，并在每次替换时进行确认。
- `:%s/foo/bar/gi`：进行全局替换，忽略大小写。

## 4.2 把正常执行的 shell 命令导入到vim中

导入命令执行结果到文件里  `:r !命令`
`r` 代表写入；`!命令`：表示命令执行的结果，就相当于我们在终端里直接输入命令一样
比如：我们正在编写一个111文件(vim 111)，我们想要把当前的时间写入进来；我们需要退出当前编辑的文件，然后在终端输入date命令，把结果复制，然后在vim 111进入文件，进行粘贴，想一想都麻烦！

但是如果我们在当前编辑的111文件内，直接执行`:r!date`；就能把时间直接打印到当前光标处！如下所示

# 5 tcpdump 的使用

tcpdump是一个常用的网络抓包工具，用于捕获和分析网络数据包。以下是tcpdump命令的详细使用方法：

基本语法：

```shell
tcpdump [选项] [过滤表达式]
```

常用选项：

- `-i <接口>`：指定要监听的网络接口。
- `-c <数目>`：设置捕获数据包的数量限制。
- `-w <文件名>`：将捕获的数据包写入文件。
- `-r <文件名>`：从文件中读取数据包进行分析。
- `-A`：以ASCII文本形式显示数据包内容。
- `-X`：以十六进制和ASCII混合形式显示数据包内容。
- `-n`：禁用对IP地址和端口的解析，直接显示数字形式。
- `-v`：显示详细的输出信息。
- `-vv`：更详细的输出信息。
- `-vvv`：非常详细的输出信息。

常用过滤表达式：

- `host <IP地址>`：捕获与指定IP地址有关的数据包。
- `port <端口号>`：捕获与指定端口号有关的数据包。
- `src <源IP地址>`：捕获源IP地址为指定地址的数据包。
- `dst <目标IP地址>`：捕获目标IP地址为指定地址的数据包。
- `tcp`：捕获TCP协议的数据包。
- `udp`：捕获UDP协议的数据包。
- `icmp`：捕获ICMP协议的数据包。

示例用法：

1. 监听指定接口的所有数据包：

```shell
sudo tcpdump -i eth0
```

2. 指定过滤条件，仅捕获源或目标IP地址为指定地址的数据包：

```shell
sudo tcpdump host 192.168.0.1
sudo tcpdump src 192.168.0.1
sudo tcpdump dst 192.168.0.1
```

3. 捕获指定端口号的数据包：

```shell
sudo tcpdump port 80
```

4. 将捕获的数据包写入文件：

```shell
sudo tcpdump -w capture.pcap
```

5. 从文件中读取数据包进行分析：

```shell
sudo tcpdump -r capture.pcap
```

这只是tcpdump命令的一些常用用法，它还有更多选项和过滤表达式可以使用。你可以查看tcpdump的man手册（`man tcpdump`）来获取更多详细信息和示例。

# 6 安装想要的 python 环境

## 6.1 下载，安装，编译

在CentOS中，要下载和安装Python 3.7，您可以按照以下步骤进行操作：

1. 打开终端或登录到CentOS服务器的控制台。

2. 确保您的系统已连接到互联网。

3. 使用以下命令更新系统软件包列表：

   ```shell
   sudo yum update
   ```

4. 安装必要的依赖包，以便能够编译和构建Python源代码：

   ```shell
   sudo yum groupinstall "Development Tools"
   sudo yum install openssl-devel bzip2-devel libffi-devel
   ```

5. 下载Python 3.7的源代码。您可以在Python官方网站上找到最新的Python 3.7源代码包下载链接。使用wget命令下载：

   ```shell
   wget https://www.python.org/ftp/python/3.7.12/Python-3.7.12.tgz
   ```

6. 解压缩下载的源代码包：

   ```shell
   tar -xf Python-3.7.12.tgz
   ```

7. 进入解压缩后的目录：

   ```shell
   cd Python-3.7.12
   ```

8. 配置和编译Python源代码：

   ```shell
   ./configure --enable-optimizations
   make -j$(nproc)
   ```

9. 安装Python 3.7：

   ```shell
   sudo make altinstall
   ```

10. 安装完成后，您可以使用以下命令验证Python 3.7是否成功安装：

    ```shell
    python3.7 --version
    ```

现在，您已成功在CentOS中下载和安装了Python 3.7。您可以使用python3.7命令来运行Python 3.7解释器。

## 6.2 切换 python3 为当前用户的默认版本

要将Python 3.7设置为默认版本，您可以使用以下步骤：

1. 打开终端或登录到CentOS服务器的控制台。

2. 使用以下命令打开.bashrc文件（或者是.zshrc等其他shell的配置文件）：

   ```shell
   vi ~/.bashrc
   ```

3. 在文件的末尾添加以下行：

   ```shell
   alias python=python3.7
   alias pip=pip3.7
   ```

   这将创建名为`python`和`pip`的别名，它们将指向Python 3.7的可执行文件和pip工具。

4. 保存并关闭文件。

5. 重新加载.bashrc文件，以使更改生效：

   ```shell
   source ~/.bashrc
   ```

   如果您使用的是其他shell的配置文件，请相应地使用适当的命令重新加载它。

现在，当您在终端中使用`python`命令时，它将默认使用Python 3.7版本。同样，`pip`命令也将使用与Python 3.7关联的pip工具。您可以使用以下命令验证Python版本：

```shell
python --version
```

请注意，这种方法只会在当前用户的环境中将Python 3.7设置为默认版本。其他用户可能仍然使用系统默认版本的Python。
