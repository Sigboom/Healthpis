from django.shortcuts import render
from django.http import HttpResponse
from withdb import models
import hashlib
import json

def get_md5(str):
    md5=hashlib.md5()
    md5.update(str.encode('utf-8'))
    return md5.hexdigest()

def index(request):
    return render(request, 'users.html')

def register(request):
    print('register')
    if not request.method == 'POST':
        return HttpResponse(json.dumps({'code': 0, 'msg': '请求类型错误'}), content_type="application/json")
    
    data = json.loads(request.body)
    username = data["username"]
    pw = data["pw"]
    err = None

    if len(username) > 20 or len(pw) > 20:
        err = '用户密码长度过长'

    if len(username) < 4 or len(pw) < 6:
        err = '用户密码长度过短（不应短与8位）'

    if not err == None:
        return HttpResponse(json.dumps({'code': 0, 'msg': err}), content_type="application/json")

    md5_pw = get_md5(pw)[0:20]
    save_success = True
    msg = 'success'
    try:
        models.UserInfo.objects.create(username=username, password=md5_pw)
    except BaseException as e:
        save_success = False
        with open('./log.log', 'a') as f:
            f.write('username = %s, pw = %s, error = %s\n' % (username, pw, e))

    print(save_success, msg, '------------')
    if save_success:
        return HttpResponse(json.dumps({'code': 0, 'msg': msg}), content_type="application/json")
    else:
        return HttpResponse(json.dumps({'code': 0, 'msg': '发生未知错误'}), content_type="application/json")

def getusers(request):
    user_list = models.UserInfo.objects.using('userdb').all()
    list = []

    for i in user_list:
        list.append({
            'username': i.username,
            'id': i.id
        })

    result = {'code': 0, 'data': list}
    return HttpResponse(json.dumps(result), content_type="application/json")




