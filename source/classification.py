# -*- coding: utf-8 -*-
"""
Created on Fri May 23 13:53:33 2014

@author: wieke
"""

from numpy import genfromtxt, recfromcsv, float32
from sklearn.ensemble import ExtraTreesClassifier
from sklearn.neighbors import KNeighborsClassifier

path_wieke = "/home/wieke/git-workspace/cadmi/data/features.csv"

data = genfromtxt(path_wieke, dtype=float32, delimiter=",",comments="#")

labels = data[:,0]

features = data[:,1:]

forest = ExtraTreesClassifier()
kNN = KNeighborsClassifier()
