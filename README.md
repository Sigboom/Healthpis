# Healthpis
making a project to control pis.

##开始一个工程（18.7.15）
1. 开发一个master和多个（可以上万）server的相互传输状态数据的程序 
- 基础数据使用脚本文件

##实现一部分功能（18.7.18）
1. 单机master文件传输
2. master多进程处理多机pi请求
3. printf => DBG
4. 日志实现master-client日志记录

##尝试使用Django框架来完成一些事情
1. 希望能对我的毕设有些帮助
		
2. 这是实现的基本目录结构

		├── __init__.py
		├── __pycache__
		│   ├── __init__.cpython-37.pyc
		│   ├── admin.cpython-37.pyc
		│   ├── models.cpython-37.pyc
		│   └── views.cpython-37.pyc
		├── admin.py
		├── apps.py
		├── migrations
		│   ├── 0001_initial.py
		│   ├── __init__.py
		│   └── __pycache__
		│       ├── 0001_initial.cpython-37.pyc
		│       └── __init__.cpython-37.pyc
		├── models.py
		├── tests.py
		└── views.py
3. views.py内实现对窗口事件的处理
4. models.py对后台数据库存储的定义
5. tests.py存放一些测试