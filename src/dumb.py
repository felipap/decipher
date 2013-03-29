
from itertools import permutations
from string import ascii_lowercase as ALPHABET

cSize = lambda word: len(set(word))

WORDS = r'/home/felipe/Desktop/words.txt'
def getDictionary():
	words = []
	with open(WORDS) as file:
		for word in file.readlines():
			words.append(word.replace('\n', ''))
	return words

def isCompatible(a, b):
	for char in a:
		if char in b:
			if b[char] != a[char]:
				return False
	for char in b:
		if char in a:
			if a[char] != b[char]:
				return False
	return True

def toMap(word, pattern):
	D = dict()
	for index, char in enumerate(word):
		D[list(set(pattern))[index]] = char
	return D

class Pattern (list):
	@property
	def cSize(self):
		return set(self).__len__()

dictionary = getDictionary()

master_pattern = {'1': 'b', '2': 'a', '3': 'n'}
master_pattern = {'1': 'b', '2': 'a', '3': 't'}

word_patterns = [
	Pattern([1,2,3,2,3,2]),
	Pattern([4,5,6,3,5]),
	Pattern([13,14,3,15,16,13]),
	Pattern([8, 14, 8, 17, 13, 7]),
	Pattern([18, 13, 6, 6, 13]),
	Pattern([4,8,5,9,5,3,8,10,11,12,13,14])
]

def filterWords(patt, universe=False):
	matching_words = []
	if not universe:
		universe = (toMap(e, patt) for e in permutations(ALPHABET, patt.cSize))
	for D in universe:
		final_word = ''.join([D[char] for char in patt])
		if final_word in dictionary and isCompatible(master_pattern, D):
			print final_word, D
			matching_words.append(final_word)
	return matching_words

def filtesr_words(wcode,  u=None):
	matching_words = []
	if u is None:
		u = permutations(ALPHABET, cSize(wcode))
	for word in u:
		print word

p = filterWords(word_patterns[4])
print p
