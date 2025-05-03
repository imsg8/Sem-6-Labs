from django.shortcuts import render
from django.http import HttpResponseRedirect

def input_form(request):
    return render(request, 'input_form.html')

def result(request):
    if request.method == 'POST':
        name = request.POST.get('name')
        marks = int(request.POST.get('marks'))

        cgpa = marks / 50.0

        request.session['name'] = name
        request.session['cgpa'] = cgpa

        return HttpResponseRedirect('/result/')
    
    return render(request, 'input_form.html')

def result_page(request):
    name = request.session.get('name', 'Unknown')
    cgpa = request.session.get('cgpa', 0)
    
    return render(request, 'result.html', {'name': name, 'cgpa': cgpa})
