from django.shortcuts import render
from .models import Vote
from django.db.models import Count

def vote_view(request):
    if request.method == 'POST':
        selected_choice = request.POST.get('choice')
        if selected_choice:
            Vote.objects.create(choice=selected_choice)

    total_votes = Vote.objects.count()
    if total_votes > 0:
        results = {
            choice: Vote.objects.filter(choice=choice).count() * 100 / total_votes
            for choice, _ in Vote.CHOICES
        }
    else:
        results = {choice: 0 for choice, _ in Vote.CHOICES}

    return render(request, 'vote.html', {'results': results})
