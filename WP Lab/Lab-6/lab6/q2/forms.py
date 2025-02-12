from django import forms

class MagazineCoverForm(forms.Form):
    image = forms.ImageField(label="Choose Image")
    background_color = forms.CharField(label="Background Color", max_length=7, widget=forms.TextInput(attrs={'placeholder': '#FFFFFF'}))
    text = forms.CharField(label="Text for Cover", max_length=200)
    font_size = forms.IntegerField(label="Font Size", min_value=10, max_value=72, initial=36)
    font_color = forms.CharField(label="Font Color", max_length=7, widget=forms.TextInput(attrs={'placeholder': '#000000'}))
