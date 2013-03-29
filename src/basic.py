#!/usr/bin/env python3

# A basic 1:1 matcher written in Python3.
# by Felipe Aragão Pires, 2013.

from string import ascii_lowercase as ALPHABET
from functools import reduce

MSGS_FILE = 'msgs.txt'
DICT_FILE = 'dict/cracklib-small'

def getmsgs():
	with open(MSGS_FILE) as file:
		lines = [line.replace('\n','') for line in file.readlines()]
		msgs = [list(map(int, [w for w in line.split(',') if w])) for line in lines]
	return msgs


def getDict():
	return [w.replace('\n', '') for w in open(DICT_FILE).readlines()]


def match(map):
	words = []
	for msg in msgs:
		word = ''.join(map[k] for k in msg)
		if word in dictionary:
			words.append(word)
			continue
		break
	else:
		print('\t', words)


def combine(map, symbols, alphabet):
	if not symbols:
		match(map)
		return
	nmap = map.copy()
	# Try to match s against all letters in the current alphabet.
	for index, letter in enumerate(alphabet):
		nmap[symbols[0]] = letter
		combine(nmap, symbols[1:], alphabet[:index]+alphabet[index+1:])


if __name__ == '__main__':
	msgs = getmsgs()
	dictionary = getDict()
	symbols = set()
	for msg in msgs:
		symbols.update(set(msg))
	combine({}, list(symbols), ALPHABET)
