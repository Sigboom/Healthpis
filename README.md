# Sigheath
making a project to control servers.

##重新开始一个工程（19.10.25）
###前言
1. 由于一些原因，主要是因为我比较懒，没有进行整理。原来的项目目标没有实现，只留下好多散乱的代码，这段时间想整理一下这些代码，并使用C++来进行代码重写
2. 实现的目标是能够实现对服务器状态的实时监控，以保证服务器的平稳运行
3. 找了一个小伙伴，希望能一起实现
4. (19.11.08)本应该是交工的日子，中间出现了一些事情，导致功能没有完成。


###大体结构描述
1. <a href="#doctor">Doctor类</a>：命令运行与实现的类，构造模式与责任链模式进行维护。
	- sigDoctor Doctor类的实例化对象根节点
2. <a  href="#mediCentre">mediCentre类</a>：数据及工具包的调用接口。
	- baseTools类：基础的函数工具包，baseTools来实现配置文件的读取
	- sigNet类：做基类，实现了Socket网络函数的相关封装，并做为两端基类
3. <a href="#manager">manager类</a>：manager端实现链接servers，并接收server相关系统信息
4. <a href="#server">server类</a>：server端检查本机情况，链接并发送相关系统信息

###文件结构
<table>
	<tr><td>README.md</td></tr>
	<tr><th>build【未实现】</th><td>Makefile</td></tr>
	<tr><th>lib</th><td>libsigToolkit.so</td></tr>
	<tr><th>unitTest【未实现】</th></tr>
	<tr><th rowspan="4">manager</th><th>conf</th><td>manager.conf</td></tr>
	<tr><td>Makefile</td></tr>
	<tr><td bgcolor="lightblue">Sigpital.cpp【main】</td></tr>
	<tr><td>myDoctor.cpp</td></tr>
	<tr><th rowspan="2">server</th><th>script</th></tr>
	<tr><td>Makefile</td></tr>
	<tr><th rowspan="11">sigToolkit</th><th>build</th><td>Makefile</td></tr>
	<tr><th>include:基础文件头</th><td>[*.h]</td></tr>
	<tr><th rowspan="7">src</td><td bgcolor="lightgreen">baseTools.cpp</td></tr>
	<tr><td bgcolor="lightgreen">sigNet.cpp【基类】</td></tr>
	<tr><td bgcolor="lightgreen">doctor.cpp</td></tr>
	<tr><td bgcolor="lightgreen">mediCentre.cpp</td></tr>
	<tr><td bgcolor="green">confException.cpp</td></tr>
	<tr><td bgcolor="green">doctorException.cpp</td></tr>
	<tr><td bgcolor="green">serverException.cpp</td></tr>
</table>

###sigToolkit

<a name="doctor" ><font color="black">
####Doctor类
</font></a>

1. 使用构造模式：拥有list队列，拥有addDoctor方法。
2. 使用责任链模式：拥有nextDoctor指针及相关方法。

<a name="mediCentre"><font color="black">
####mediCentre类
</font></a>

1. 读取配置文件（构造方法）【已实现】

<table>
	<tr><th rowspan="3">sigNet类</th><td rowspan="2">做网络链接基类</td><td>基本的网络套接字创建函数</td></tr>
	<tr><td>网络套接字链接函数</td></tr>
	<tr><td>提供文件收发函数</td></tr>
	<tr><th rowspan="2">baseTools类</th><td>提供配置文件读写函数</td></tr>
	<tr><td>字符串切分函数</td></tr>
</table>

####配置优化点
1. 将配置文件加载到内存替代每次都读内存【STL boost】
2. 使用责任链模式，将数据统一存储在mediCentre，Doctor可增量开发
3. 使用动态链接库进行封装，分层开发。

<a name="manager"><font color="black">
###manager类
</font></a>

1. 进程控制
2. 调用相应接口控制业务逻辑

####配置与优化点
1. 使用lambda表达式与该智能指针将要析构时可以赋值操作的性质，替换使用move()【智能指针（unique_ptr）】
2. 使用try-catch机制简化代码异常判断流程。【异常处理】

<a name="server"><font color="black">
###server类
</font></a>
