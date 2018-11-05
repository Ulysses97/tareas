
class Node :
  def __init__(self, value) :
    self.value = value
    self.next = None

class Queue :
  def __init__(self) :
    self.first = None
    self.last = None

  def empty(self) :
    return self.first == None

  def enqueue(self, value) :
    if self.first == None :
      self.first = self.last = Node(value)
    else :
      self.last.next = Node(value)
      self.last = self.last.next

  def dequeue(self) :
    aux = self.first
    if self.first == self.last :
      self.first = None
      self.last = None
    else :
      self.first = self.first.next
    return aux.value

  def contains(self, value) :
    temp = self.first
    while temp != None :
      if temp.value == value :
        return True
      else :
        temp = temp.next
    return False
