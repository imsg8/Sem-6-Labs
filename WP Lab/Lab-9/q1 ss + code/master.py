Step 2: Define models

In the models.py file of the directory app, define the Category and Page models:

# directory/models.py

from django.db import models

class Category(models.Model):
    name = models.CharField(max_length=100)
    number_of_visits = models.IntegerField(default=0)
    number_of_likes = models.IntegerField(default=0)

    def __str__(self):
        return self.name

class Page(models.Model):
    category = models.ForeignKey(Category, on_delete=models.CASCADE)
    title = models.CharField(max_length=200)
    url = models.URLField()
    views = models.IntegerField(default=0)

    def __str__(self):
        return self.title

Explanation:

    Category has a name, number_of_visits, and number_of_likes.
    Page has a foreign key reference to Category, with attributes like title, url, and views.

Step 3: Migrate the models

Now, we need to create the database tables by running Django migrations:

python manage.py makemigrations
python manage.py migrate

Step 4: Create forms

To allow users to add categories and pages, we will create forms. In the forms.py file of the directory app, define forms for Category and Page:

# directory/forms.py

from django import forms
from .models import Category, Page

class CategoryForm(forms.ModelForm):
    class Meta:
        model = Category
        fields = ['name', 'number_of_visits', 'number_of_likes']

class PageForm(forms.ModelForm):
    class Meta:
        model = Page
        fields = ['category', 'title', 'url', 'views']

Step 5: Create views to handle form submission

Now, let’s create views to handle the form submission and display data. Open views.py and add the following code:

# directory/views.py

from django.shortcuts import render, redirect
from .models import Category, Page
from .forms import CategoryForm, PageForm

def category_list(request):
    categories = Category.objects.all()
    return render(request, 'directory/category_list.html', {'categories': categories})

def page_list(request, category_id):
    category = Category.objects.get(id=category_id)
    pages = Page.objects.filter(category=category)
    return render(request, 'directory/page_list.html', {'category': category, 'pages': pages})

def add_category(request):
    if request.method == 'POST':
        form = CategoryForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('category_list')
    else:
        form = CategoryForm()
    return render(request, 'directory/add_category.html', {'form': form})

def add_page(request):
    if request.method == 'POST':
        form = PageForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('category_list')
    else:
        form = PageForm()
    return render(request, 'directory/add_page.html', {'form': form})

Step 6: Create URLs

Now, set up the URLs for the views. In the urls.py file of the directory app, add:

# directory/urls.py

from django.urls import path
from . import views

urlpatterns = [
    path('', views.category_list, name='category_list'),
    path('category/<int:category_id>/pages/', views.page_list, name='page_list'),
    path('add/category/', views.add_category, name='add_category'),
    path('add/page/', views.add_page, name='add_page'),
]

Then, include these URLs in the urls.py of the main website_directory project:

# website_directory/urls.py

from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', include('directory.urls')),
]

Step 7: Create templates

Next, we’ll need some basic HTML templates to display the content and forms.
category_list.html

<!-- directory/templates/directory/category_list.html -->

<!DOCTYPE html>
<html>
<head>
    <title>Website Directory</title>
</head>
<body>
    <h1>Website Directory</h1>
    <a href="{% url 'add_category' %}">Add Category</a><br><br>
    <h2>Categories</h2>
    <ul>
        {% for category in categories %}
            <li>
                <a href="{% url 'page_list' category.id %}">{{ category.name }}</a>
                (Visits: {{ category.number_of_visits }}, Likes: {{ category.number_of_likes }})
            </li>
        {% endfor %}
    </ul>
</body>
</html>

page_list.html

<!-- directory/templates/directory/page_list.html -->

<!DOCTYPE html>
<html>
<head>
    <title>{{ category.name }} - Pages</title>
</head>
<body>
    <h1>Pages in {{ category.name }}</h1>
    <a href="{% url 'add_page' %}">Add Page</a><br><br>
    <ul>
        {% for page in pages %}
            <li>
                <a href="{{ page.url }}" target="_blank">{{ page.title }}</a> (Views: {{ page.views }})
            </li>
        {% endfor %}
    </ul>
</body>
</html>

add_category.html

<!-- directory/templates/directory/add_category.html -->

<!DOCTYPE html>
<html>
<head>
    <title>Add Category</title>
</head>
<body>
    <h1>Add Category</h1>
    <form method="POST">
        {% csrf_token %}
        {{ form.as_p }}
        <button type="submit">Save</button>
    </form>
</body>
</html>

add_page.html

<!-- directory/templates/directory/add_page.html -->

<!DOCTYPE html>
<html>
<head>
    <title>Add Page</title>
</head>
<body>
    <h1>Add Page</h1>
    <form method="POST">
        {% csrf_token %}
        {{ form.as_p }}
        <button type="submit">Save</button>
    </form>
</body>
</html>

Step 8: Admin interface

To manage categories and pages easily, register your models in admin.py:

# directory/admin.py

from django.contrib import admin
from .models import Category, Page

admin.site.register(Category)
admin.site.register(Page)

Step 9: Run the server