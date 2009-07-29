"""
  ACS-VRP-V1
  CSV Table Generator
  
  Giuliano Vilela, Jose C. Becceneri
  Curso de Inverno 2009 - INPE
"""

from time import time
from math import sqrt
from sys import stdout
from subprocess import Popen, PIPE
from itertools import imap, ifilter


cl_args = [
   ("numAnts"          , [10,30,60])
 , ("minSuccessAnts"   , [5000,10000])
 , ("ranking"          , [0, 1])
 , ("rankListMaxSize"  , [5, 10])
 , ("rankListMaxDelta" , [50,100])
 , ("heuristicWeight"  , [2,3,5])
 , ("evaporationRate"  , [0.2, 0.9])
 , ("explotationFactor", [0.2, 0.5])
]

instance = "augerat-a/A-n32-k5.vrp"
result   = "resultados/res-A-n32-k5-2.csv"
program  = "./acs-vrp"
trials   = 4


flush = stdout.flush
fst = lambda (x,_) : x
snd = lambda (_,y) : y

def product(*args):
  pools = map(tuple, args)
  result = [[]]
  
  for pool in pools:  
   result = [x + [y] for x in result for y in pool]
   
  return result

def mean(vals):
  return sum(vals) / float(len(vals))

def stdev(vals):
  meanv = mean(vals)
  diffs = sum((x - meanv) ** 2 for x in vals) 
  return sqrt(diffs / len(vals))


if __name__ == '__main__':
  pl = product(*map(snd, cl_args))
  nparams = len(pl)
  
  result_file = open(result, 'w')
  
  for i, params in zip(xrange(nparams), pl):
    print "%d/%d:" % (i+1, nparams),
    flush()
    
    cmd = program + " " + instance
    pnames = map(fst, cl_args)
    
    for pname, pvalue in zip(pnames, params):
      cmd += " --%s=%s" % (pname, str(pvalue))
    
    times, results = [], []
    
    for _ in xrange(trials):
      t1 = time()
      
      process = Popen(cmd, stdout = PIPE, shell = True)
      stdout = process.stdout
      val = int(stdout.read())
      process.wait()
      
      t2 = time()
      
      times.append(t2 - t1)
      results.append(val)
    
    print "%.2fs" % (sum(times),)
    
    csv_line = params + [mean(times),
                         min(results), max(results),
                         mean(results), stdev(results)]
    
    result_file.write(", ".join(map(str,csv_line)) + "\n")
    
  result_file.close()
