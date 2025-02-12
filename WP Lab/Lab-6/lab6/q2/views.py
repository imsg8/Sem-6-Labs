from django.shortcuts import render
from django.core.files.storage import FileSystemStorage
from .forms import MagazineCoverForm
from django.conf import settings

def create_magazine_cover(request):
    if request.method == 'POST' and request.FILES:
        form = MagazineCoverForm(request.POST, request.FILES)
        if form.is_valid():
            # Save the uploaded image
            image = form.cleaned_data['image']
            fs = FileSystemStorage()
            filename = fs.save(image.name, image)
            image_url = fs.url(filename)  # This gives the relative URL

            # Get other form data
            background_color = form.cleaned_data['background_color']
            text = form.cleaned_data['text']
            font_size = form.cleaned_data['font_size']
            font_color = form.cleaned_data['font_color']

            context = {
                'image_url': image_url,
                'background_color': background_color,
                'text': text,
                'font_size': font_size,
                'font_color': font_color
            }

            return render(request, 'magazine_cover.html', context)
    else:
        form = MagazineCoverForm()

    return render(request, 'magazine_cover.html', {'form': form})

