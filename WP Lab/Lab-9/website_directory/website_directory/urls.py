"""
URL configuration for website_directory project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/5.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
# website_directory/urls.py

# website_directory/urls.py
from django.contrib import admin
from django.urls import path, include
from works_app import views  # Import views from works_app

urlpatterns = [
    path('admin/', admin.site.urls),
    path('insert/', views.insert_works, name='insert_works'),
    path('search/', views.people_in_company, name='people_in_company'),
    path('', views.home, name='home'),  # Maps the root path to the home view
]

