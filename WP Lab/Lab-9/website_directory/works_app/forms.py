from django import forms
from .models import Works

class WorksForm(forms.ModelForm):
    class Meta:
        model = Works
        fields = ['person_name', 'company_name', 'salary']
        widgets = {
            'salary': forms.NumberInput(attrs={'placeholder': 'Salary', 'step': '0.01'}),
        }
