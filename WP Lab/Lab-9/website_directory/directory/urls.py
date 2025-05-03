# directory/urls.py

from django.urls import path
from . import views

urlpatterns = [
    path('', views.category_list, name='category_list'),
    path('category/<int:category_id>/pages/', views.page_list, name='page_list'),
    path('add/category/', views.add_category, name='add_category'),
    path('add/page/', views.add_page, name='add_page'),
]
