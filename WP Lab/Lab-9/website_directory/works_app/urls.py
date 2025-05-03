from django.contrib import admin
from django.urls import path, include
from works_app import views  # Import views from works_app

urlpatterns = [
    path('admin/', admin.site.urls),
    path('insert/', views.insert_works, name='insert_works'),
    path('search/', views.people_in_company, name='people_in_company'),
    path('', views.home, name='home'),  # This will map the root path to the 'home' view
]
