from django.shortcuts import render

# Create your views here.
def info_enter(request):
    if request.method=="POST":

        name=request.POST.get('Name')
        dob=request.POST.get('DOB')
        add=request.POST.get('address')
        num=request.POST.get('contact_number')
        email=request.POST.get('email')
        eng=request.POST.get('english_marks')
        phy=request.POST.get('physics_marks')
        chem=request.POST.get('chemistry_marks')
        print(request.POST.get('temp'))
        tot=(int(eng)+int(phy)+int(chem))/300
        tot=tot*100

        student_data = {
            'name': name,
            'dob': dob,
            'add': add,
            'no': num,
            'email': email,
            'eng': eng,
            'phy': phy,
            'chem': chem,
            'per': tot,
            'stu_data':True
        }
        return render(request,'index.html',context=student_data)
    return render(request,'index.html',context={'stu_data':False})