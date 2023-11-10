import matplotlib.pyplot as plt
def animalGraph(filename, animalList):
  xList=[]
  yList=[]
  for animal in animalList:
    count = 0
    with open(filename) as f:
      for line in f:
        line = line.rstrip("\r\n")
        if line == animal:
          count+=1
    xList.append(animal)
    yList.append(count)
    
  plt.bar(xList,yList)
  plt.title("Animal Graph")
  plt.xlabel("Animals")
  plt.ylabel("Amount of Animals")
  plt.show()


animalGraph("data.txt", ["dog","cat","hippo"]) 