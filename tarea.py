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

########################################################

wordsGraph = {}

file = open("words_length_4")

for word in file :
  wordsGraph[word.rstrip()] = {
    "adjList" : [],
    "visited" : False
  }

file.close()

for word in wordsGraph.keys() :
  for _word in wordsGraph.keys() :
    if canTransformInto(word,_word) and word != _word :
      wordsGraph[word]["adjList"].append(_word)

########################################################

q = queue.Queue()
q.enqueue((start, 1))

wordsGraph[start]["visited"] = True

chainLength = 0

while not q.empty() :
  current = q.dequeue()

  if current[0] == target :
    chainLength = current[1]
    break

  for word in wordsGraph[current[0]]["adjList"] :
    if not wordsGraph[word]["visited"] :
      q.enqueue((word, current[1] + 1))
      wordsGraph[word]["visited"] = True

########################################################

print(time.time() - startTime)
print(chainLength)