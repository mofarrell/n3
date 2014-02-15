"""
def generate():
  for i in xrange(x):

"""
def f(a,b,c):
  datMod = 7
  arr = []
  baseX = 0
  baseY = 0
  baseZ = 0
  scale = .25
  for i in xrange(8*a):
    x = baseX
    y = baseY
    z = baseY
    if (i % 7) == 0:
      #All 0
      x = x
    elif (i % 7) == 1:
      x += scale
    elif (i % 7) == 2:
      y += scale
    elif (i % 7) == 3:
      z += scale
    elif (i % 7) == 4:
      x += scale
      y += scale
    elif (i % 7) == 5:
      x += scale
      z += scale
    else:
      y += scale
      z += scale
      baseX += scale
      baseY += scale
      baseZ += scale

    print "(", x, " ",  y, " ", z, ")"


f(5,5,5)
"""
datMod = 8
baseX = 0
baseY = 0
baseZ = 0
for i in xrange(100):
  x = baseX + (((i/8)) % 8)
  y = baseY + (((i + 3)/8) % 8) 
  z = baseZ + (((i + 6)/8) % 8)
  print "(",  x, " ",  y, " ", z, ")"
"""
