from django.db import models

class MagazineCover(models.Model):
    image = models.ImageField(upload_to='magazine_covers/')  # The 'upload_to' is the subfolder within the 'media/' directory
    background_color = models.CharField(max_length=7)  # Example field for background color
    text = models.TextField()
    font_size = models.IntegerField()
    font_color = models.CharField(max_length=7)

