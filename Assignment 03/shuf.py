#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

    def chooseline(self):
        return random.choice(self.lines)

def main():
	version_msg = "%prog 2.0"
	usage_msg = """%prog [OPTION]... FILE

	Output randomly selected lines from FILE."""

	parser = OptionParser(version=version_msg, usage=usage_msg)
	parser.add_option("-n", "--head-count", action="store", dest="COUNT", default="untilEOF", help="output at most COUNT lines")
	parser.add_option("-e", "--echo", action="store_true", dest="ECHO", help="treat each ARG as an input line")
	parser.add_option("-r", "--repeat", action="store_true", dest="REPEAT", help="output lines can be repeated")
	    
	options, args = parser.parse_args(sys.argv[1:]) 

	if len(args)==0:
		args.append(sys.stdin.readline().rstrip('\n'))
	elif args[0]=="-": 
		args[0]=sys.stdin.readline().rstrip('\n')

	for k in range(len(args)):	
		input_file = args[k]
		try:
			generator = randline(input_file)
		except IOError as err:
			errno, strerror = err.args
			print("I/O error({0}): {1}".format(errno, strerror))

		if options.ECHO==True:
			for i in range(len(args)):
				args[i]=args[i]+"\n"
			generator.lines=args

		try:
			if options.COUNT=="untilEOF":
				if options.REPEAT==True:			
					numlines=sys.maxsize
				else:	
					numlines=int(len(generator.lines))
			else:
				numlines = int(options.COUNT)
		except:
			parser.error("invalid NUMLINES: {0}".
				     format(options.COUNT))

		if numlines < 0:
			parser.error("negative count: {0}".
				     format(options.COUNT))
		    
		list=[]
		i=0
		while i < numlines:
			found=False
			output=generator.chooseline()
			if options.REPEAT==None:
				for j in range(len(list)):
					if list[j]==output:
						found=True
						break
				if found==False:
					list.append(output)
				if len(generator.lines) <= i:
					break

			if found==False:
				sys.stdout.write(output)
				i += 1
    


if __name__ == "__main__":
    main()
