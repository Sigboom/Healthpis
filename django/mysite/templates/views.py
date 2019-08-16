#!/usr/bin/env python
# coding=utf-8
from django.http import HttpResponse
def hello(request):
    return HttpResponse("Hello world")

