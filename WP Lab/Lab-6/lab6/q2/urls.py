from django.urls import path
from . import views

urlpatterns = [
    path('', views.create_magazine_cover, name='create_magazine_cover'),
]
