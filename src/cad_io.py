import random
import numpy as np
from sklearn import cross_validation


def load_data (path):
    
    data = np.genfromtxt(path, dtype=np.float32, delimiter=",",comments="#")
    features = data[:,1:]
    labels = data[:,0]
    
    return features, labels

def split_data (features, labels, test_size):
    '''
    Splits a full dataset into a train and a testing dataset.
    The testing data contains at least 10 positive samples.
    '''
    random.seed(1234123412341234)           # Random seed is fixed, rather than storing data separately
    
    permutation = range(len(labels))
    random.shuffle(permutation)
    train_perm = permutation[:-test_size]
    test_perm = permutation[-test_size:]
    
    train_X = np.array([features[i] for i in train_perm])
    test_X = np.array([features[i] for i in test_perm])
    train_y = np.array([labels[i] for i in train_perm])
    test_y = [labels[i] for i in test_perm]
    
    return train_X, test_X, train_y, test_y
    
    # return cross_validation.train_test_split(features, labels, test_size=test_size, random_state=1234123412341234)

def count_positives (labels) :
    nr_positives = np.count_nonzero(labels)
    return nr_positives


if __name__ == "__main__":
    # path_wieke = "/home/wieke/git-workspace/cadmi/data/features.csv"
    path = "/Users/tom/Documents/workspace/cadmi/data/examples/features.csv"
    labels,features = load_data(path)

    train_perm, test_perm = split_data(labels,features,1000)
    count_positives(labels,train_perm)
    count_positives(labels,test_perm)