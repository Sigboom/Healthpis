import time
from django.http import HttpResponse

def index(request):
    return render(request, 'hello.html')

def current_time(request):
    return HttpResponse("Current time is: " + time.strftime('%Y-%m-%d: %H:%M:%S'))
