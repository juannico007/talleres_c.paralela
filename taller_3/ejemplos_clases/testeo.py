import re
import os 
import pandas as pd

names = os.listdir('./')
#print(names)
#print()

def createDataframe():
	results_files = re.compile(r'result.*.csv')
	files = []
	
	for filename in names: 
		if results_files.search(filename) != None:
			files.append(filename)
			df = pd.read_csv("./" + filename)
			print(df)
	
