import matplotlib.pyplot as plt

def plotParabola(xList):
  y1List = []
  y2List = []
  for x in xList:
    y1 = x**2 - 2*x + 3 # y = x2  - 2x +3.
    y1List.append(y1)
    y2 = x**2 - 10*x # y = x2  -10x
    y2List.append(y2)
    

  plt.plot(xList,y1List, label = " y = x2  - 2x +3")
  plt.plot(xList,y2List, label = "y =  x2  - 10x")
  plt.title("Parabola Graph")
  plt.xlabel("X-Values")
  plt.ylabel("Y-Values")
  plt.show()
  return

plotParabola([0,1,2,3,4,5,6,7,])
