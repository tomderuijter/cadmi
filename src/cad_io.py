import random
import numpy as np
from sklearn import cross_validation

# HOMEBREW MODULES
from PerImageFloat import PerImageFloat


def load_data (path):
    
    data = np.genfromtxt(path, dtype=np.float32, delimiter=",",comments="#")
    features = data[:,1:]
    labels = data[:,0]
    
    return features, labels
    
def load_locations (path):
    
    return np.genfromtxt(path, dtype=None, delimiter=",",comments="#")
    
def get_subjects (locations):
    
    subjects = []
    
    for i in xrange(len(locations)):
        parts = locations[i].split()
        subjects.append(int(parts[0][-2:]) - 1)
        
    return subjects
    
def add_subjects (data_y, subjects):
    
    assert len(subjects) == len(data_y)
    
    y = []
    for i in xrange(len(data_y)):
        y.append(PerImageFloat(data_y[i], subjects[i]))
    
    y = np.array(y, dtype=PerImageFloat)        # Necessary
    return y
    
def write_predictions (locations, predictions, path):
    print len(locations)
    print len(predictions)
    assert len(locations) == len(predictions)
    
    with open(path,'w') as f:
        for i in xrange(len(locations)) :
            f.write(locations[i] + " " + str(predictions[i]) + "\n")
        f.close()
        return True
    return False
    
def undo_permutation(data, permutation):
    inv_permutation = [-1] * len(permutation)
    for i in xrange(len(permutation)):
        inv_permutation[ permutation[i] ] = i
    
    data = np.array([data[i] for i in inv_permutation])
    
    return data

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
    
    train_X = np.array([features[i] for i in train_perm], dtype=PerImageFloat)
    test_X = np.array([features[i] for i in test_perm], dtype=PerImageFloat)
    train_y = np.array([labels[i] for i in train_perm], dtype=PerImageFloat)
    test_y = np.array([labels[i] for i in test_perm], dtype=PerImageFloat)
    
    return train_X, test_X, train_y, test_y, train_perm, test_perm

def count_positives (labels) :
    nr_positives = np.count_nonzero(labels)
    return nr_positives


if __name__ == "__main__":
    # path_wieke = "/home/wieke/git-workspace/cadmi/data/features.csv"
    path = "/Users/tom/Documents/workspace/cadmi/data/examples/features.csv"
    features,labels = load_data(path)