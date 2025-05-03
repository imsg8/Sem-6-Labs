from django.db import models

class Vote(models.Model):
    CHOICES = [
        ('Good', 'Good'),
        ('Satisfactory', 'Satisfactory'),
        ('Bad', 'Bad'),
    ]
    choice = models.CharField(max_length=50, choices=CHOICES)
    votes = models.IntegerField(default=0)

    def __str__(self):
        return self.choice
