from django.urls import path

from . import views

urlpatterns = [
    path('', views.current_time, name='current_time'),
]
