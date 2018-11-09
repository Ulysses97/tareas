import time
import importlib
queue = importlib.import_module("queue")

def canTransformInto(str1, str2) :
  if len(str1) == len(str2) :
    diffChars = 0
    for i in range(len(str1)) :
      if str1[i] != str2[i] :
        diffChars += 1
    return diffChars <= 1
  return False

startTime = time.time()

words = input()
start, target = words.split(' ')

words = {}

file = open("words_length_4")

for word in file :
  words[word.rstrip()] = False

file.close()

## BFS ##

words[start] = True

q = queue.Queue()
q.enqueue((start, 1))

chainLength = 0

while not q.empty() :
  current = q.dequeue()

  if current[0] == target :
    chainLength = current[1]
    break

  for word, visited in words.items() :
    if canTransformInto(current[0], word) and current[0] != word :
      if not visited :
        q.enqueue((word, current[1] + 1))
        words[word] = True

print(time.time() - startTime)
print(chainLength)
