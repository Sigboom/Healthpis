#使用Django记录
##基本安装：
```sh
# 安装Django
pip install django

#安装uwsgi
pip install uwsgi
```
##安装配置mysql

```sh
#在本机中安装mysql
brew install mysql 

#安装python 与MySQL 的链接模块（使用anaconda会安装在anaconda环境中）
pip install pymysql
```
- 在\_\_init__.py中添加

```
import pymysql

pymysql.install_as_MySQLdb()
```
- 修改setting.py文件配置
找到DATABASES,修改为

```py
#根据具体安装mysql配置修改参数
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql',
        'NAME': 'achievements',
        'USER': 'root',
        'PASSWORD': 'root',
        'HOST': '127.0.0.1',
        'PORT': 3306,
    }
}
```

- 会出现问题，参考[文章](https://blog.csdn.net/weixin_33127753/article/details/89100552)
- 进入anaconda环境中的mysql文件下（一般在\<env_name>/lib/\<python_version>/site-packages/django/db/backends/mysql）
- 注释掉base.py文件下

```py
if version < (1, 3, 3):
     raise ImproperlyConfigured("mysqlclient 1.3.3 or newer is required; you have %s" % Database.__version__)
```
修改operations.py文件

```py
if query is not None:
    query = query.decode(errors='replace')
return query
# 修改为：
if query is not None:
    query = query.encode(errors='replace')
return query
```
- 出现"cryptography is required for sha256_password or caching_sha2_password"问题

```sh
pip install cryptography
```
- 出现"Unknown database '*******'", 在mysql中创建相关database

```sh
#记得更新数据库
python manage.py makemigrations 
python manage.py migrate
```
##部署使用安装：
```py
pip install nginx
```

##其他常用命令
###使用anaconda
```sh
#创建虚拟环境
conda create -n <env_name> python=<python_version>
# python_version => 2.7/3.6...

#删除虚拟环境
#已在当前环境无法直接删除
conda remove -n <env_name> --all

#复制（克隆环境）
conda create -n <new_env_name> --clone <old_env_name>

#复制+删除=>重命名

#查看当前已有环境
conda env list

#激活（使用）环境
conda activate <env_name>
```
###使用Django
```sh
#创建工程
django-admin startproject <project_name>

#运行Django(在工程目录中)
python manage.py runserver
```