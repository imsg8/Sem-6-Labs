from django.db import models

class Emp(models.Model):
    name = models.CharField(max_length=100)
    email = models.EmailField()
    years = models.PositiveIntegerField()

    def __str__(self):
        return self.name
