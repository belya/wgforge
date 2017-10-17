from pygtrie import StringTrie
import numpy as np
import time

def time_test(length):
  array = np.random.random_integers(-2**31 - 1, 2**31, length)

  trie = StringTrie()

  for number in array:
    if not trie.has_key(bin(number)):
      trie[bin(number)] = 0  
    trie[bin(number)] += 1

  time1 = time.time()
  for number in np.random.choice(array, 10000):
    trie[bin(number)]
  time2 = time.time()
  print("Access to array of length {} took {} ms".format(length, (time2-time1)*1000))

for length in range(10, 100000, 10000):
  time_test(length)