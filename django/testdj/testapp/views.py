from django.shortcuts import render
from django.http import HttpResponse

def hello(response):
    return HttpResponse("Hello World!")

# Create your views here.
