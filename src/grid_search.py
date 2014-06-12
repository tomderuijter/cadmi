from sklearn import grid_search as skl_grid_search

# HOMEBREW MODULES
import metrics

def grid_search(classifier, train_X, train_y): 

    tuned_parameters = [{
        'n_estimators': [3,5],#[3,5,7,9,11,13,15,17,19,21,23,25,30,35,40],
        'max_depth': [None]#[None,3,5,7,9,11,13,15,17,19]
    }]

    score = ('AUC', None) # Ugly hack so SKLearn supports AUC. See above.

    print "# Tuning hyper-parameters for %s" % score[0]
    print

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