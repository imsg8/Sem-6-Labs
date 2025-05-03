from django.shortcuts import render, redirect
from .forms import WorksForm
from .models import Works, Lives

def insert_works(request):
    if request.method == 'POST':
        form = WorksForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('insert_works')  # Redirect to the same page after submission
    else:
        form = WorksForm()

    return render(request, 'works_app/insert_works.html', {'form': form})

def people_in_company(request):
    if request.method == 'POST':
        company_name = request.POST.get('company_name')
        people = Works.objects.filter(company_name=company_name)
        return render(request, 'works_app/people_in_company.html', {'people': people, 'company_name': company_name})
    return render(request, 'works_app/people_in_company.html')
