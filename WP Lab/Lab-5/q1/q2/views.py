from django.shortcuts import render
from datetime import datetime

def check_eligibility(request):
    eligibility = ""
    if request.method == "POST":
        emp_id = request.POST.get('emp_id')
        doj = request.POST.get('doj')
        doj_date = datetime.strptime(doj, '%Y-%m-%d')
        experience_years = (datetime.now() - doj_date).days // 365
        if experience_years > 5:
            eligibility = "YES"
        else:
            eligibility = "NO"
    return render(request, 'in.html', {'eligibility': eligibility})
