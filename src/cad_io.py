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
    
def load_feature_names (path):

    with open(path, 'r') as f:
        first_line = f.readline()
     
    first_line = first_line[2:] # Remove '# '
    name_list = first_line.split(",")
    name_list = name_list[1:]   # Remove 'labels'
    
    name_dict = {}
    for i in xrange(len(name_list)):
        name_dict[name_list[i]] = i
    
    return name_dict
    
def load_locations (path):
    
    return np.genfromtxt(path, dtype=None, delimiter=",",comments="#")
    
def parse_locations (path):

    data = np.genfromtxt(path, dtype=np.float32, delimiter=" ",comments="#")

    x = data[:,1]
    y = data[:,2]
    z = data[:,3]
    
    return x,y,z
    
def get_subjects (locations):
    
    subjects = []
    
    for i in xrange(len(locations)):
        parts = locations[i].split()
        subjects.append(int(parts[0][-2:]) - 1)
        
    return np.array(subjects, dtype=int)
    
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
    
    
def apply_permutation(data_X, data_y, locations, perm):

    data_X = data_X[perm]
    data_y = data_y[perm]
    locations = locations[perm]
    return data_X,data_y,locations


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

def indices(a, func):
    return [i for (i, val) in enumerate(a) if func(val)]

def resample_negatives (data_y, factor):
    '''Downsamples without replacement from the negative set. Keeps <factor> percent of negatives.'''
    
    negs = indices(data_y, lambda x: x == 0)
    np.random.shuffle(negs)
    pos = indices(data_y, lambda x: x != 0)

    perm = pos + negs   # Python arrays
    end_index = int(len(negs)*factor + len(pos))
    sub_perm = perm[:end_index]

    np.random.shuffle(sub_perm)
    return sub_perm
    

# if __name__ == "__main__":
    # path_wieke = "/home/wieke/git-workspace/cadmi/data/features.csv"
    # path = "/Users/tom/Documents/workspace/cadmi/data/examples/features.csv"
    # features,labels = load_data(path)