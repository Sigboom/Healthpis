#使用Django记录
##基本安装：
```py
# 安装Django
pip install django

#安装uwsgi
pip install uwsgi
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