from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_protect

def register(request):
    return render(request, 'register.html')

@csrf_protect 
def success(request):
    if request.method == 'POST':
        username = request.POST.get('username')
        email = request.POST.get('email', 'N/A')
        contact = request.POST.get('contact', 'N/A')

        return render(request, 'success.html', {
            'username': username,
            'email': email,
            'contact': contact
        })
    return HttpResponse("Invalid request", status=400)
