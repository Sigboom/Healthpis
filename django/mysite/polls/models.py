from django.db import models

class Test(models.Model):
    a = models.CharField(max_length = 30)
    b = models.IntegerField()
