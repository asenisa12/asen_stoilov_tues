from django.template.loader import get_template
from django.shortcuts import render

def home(request):
	return render(request,"home.html");