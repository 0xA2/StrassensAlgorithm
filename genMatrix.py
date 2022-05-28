import sys
from random import randint

def genPair(rows,cols, filename):

	with open(filename, "w") as m:
		m.write(str(rows) + " "  + str(cols) + "\n")
		for i in range(0,rows):
			for j in range(0,cols):
				m.write(str(randint(1,9)) + " ")
			m.write("\n")
		m.write(str(rows) + " "  + str(cols) + "\n")
		for i in range(0,rows):
			for j in range(0,cols):
				m.write(str(randint(1,9)) + " ")
			m.write("\n")


def main():

	if len(sys.argv) != 4:
		print ("Usage: $ python getMatrixPair.py [ROWS] [COLS] [OUTPUTFILE]\nWhere ROWS and COLS are the numbers of rows and columns of the matrices.")

	try:
		rows = int(sys.argv[1], 10)
		cols = int(sys.argv[2], 10)
		filename = sys.argv[3]
		genPair(rows, cols, filename)
	except:
		print ("Invalid Option\n")
		print ("Usage: $ python getMatrixPair.py [NUMBER]\nWhere [NUMBER] is the number of rows and columns of the matrices.")

if __name__ == "__main__":
	main()
