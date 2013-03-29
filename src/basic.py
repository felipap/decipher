#!/usr/bin/env python3

# A basic 1:1 matcher written in Python3.
# by Felipe Aragão Pires, 2013.

from string import ascii_lowercase as ALPHABET

MSGS_FILE = '../msgs.txt'
DICT_FILE = '../dict/words.eng.small.txt'

def getmsgs():
	with open(MSGS_FILE) as file:
		lines = [line.replace('\n','') for line in file.readlines()]
		msgs = [list(map(int, [w for w in line.split(',') if w])) for line in lines]
	return msgs


dictionary = [w.replace('\n', '') for w in open(DICT_FILE).readlines()]


def match(map):
	word = ''.join(map[k] for k in msgs[0])
	if word in dictionary:
		print('\t', word)

def combine(map, symbols, alphabet):
	# print "map: %s, symbols: %s, alphabet: %s" % (map, symbols, alphabet)

	if not symbols:
		match(map)
		return

	s = symbols[0]
	nmap = map.copy()
	# Try to match s against all letters in the current alphabet.
	for index, letter in enumerate(alphabet):
		nmap[s] = letter
		combine(nmap, symbols[1:], alphabet[:index]+alphabet[index+1:])


if __name__ == '__main__':
	msgs = getmsgs()
	word = msgs[0]
	combine(dict(), list(set(word)), ALPHABET)
