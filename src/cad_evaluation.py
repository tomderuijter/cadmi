import numpy as np
from sklearn import grid_search as skl_grid_search
from sklearn import cross_validation as skl_cross_validation
from sklearn.base import clone

# HOMEBREW MODULES
import cad_metrics
import cad_io

def cross_validation(classifier, data_X, data_y, subjects):
    '''
    Evaluate a dataset by splitting the data per subject and 
    averaging over the FROC scores per subject.
    '''
    
    sort_perm = np.argsort(subjects)
    data_X = data_X[sort_perm]
    data_y = data_y[sort_perm]
    subjects = subjects[sort_perm]
    
    cv = skl_cross_validation.LeaveOneLabelOut(labels=subjects)
    predictions = []

    for train_index, test_index in cv:        
        train_X = data_X[train_index]
        train_y = data_y[train_index]
        test_X = data_X[test_index]
        test_y = data_y[test_index]
        
        estimator = clone(classifier)
        estimator.fit(train_X, train_y)
        
        predicted_y = estimator.do_predict(test_X)
        predictions = np.concatenate((predictions,predicted_y),axis=0)
    
    predictions = cad_io.undo_permutation(predictions, sort_perm)
    
    return predictions

def grid_search(classifier, train_X, train_y, subjects): 

    tuned_parameters = [{
        'n_estimators': [20,25,30,35,40,45,50,100,200],
        'max_depth': [None,3,5,7,9,11,13,15,17,19]
    }]

    score = ('AUC', None) # Ugly hack so SKLearn supports AUC. See above.

    print "# Tuning hyper-parameters for %s" % score[0]
    print
        
    skl_cross_validation.LeaveOneLabelOut(labels=subjects)
    clf = skl_grid_search.GridSearchCV(classifier, tuned_parameters, cv=5, n_jobs=1, verbose=10)#, score_func=score[1])
    clf.fit(train_X, train_y)

    print "Best parameters set found on development set:"
    print
    print clf.best_estimator_
    print
    print "Grid scores on development set:"
    print
    for params, mean_score, scores in clf.grid_scores_:
            print "\t%0.3f (+/-%0.03f) for %r" % (mean_score, scores.std() / 2, params)

    return clf.best_params_, clf.best_score_