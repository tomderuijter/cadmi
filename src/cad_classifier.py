from sklearn import ensemble, metrics

# HOMEBREW MODULES
import cad_metrics    
    
# Modify classifiers so gridsearch works with AUC or FROC.

class AUCTreeClassifier(ensemble.RandomForestClassifier):

    def __init__(**params):
        super(self)
        params['subjects']

    def score(self, X, y):
        probas = self.predict_proba(X)
        probas = probas[:,1]
        return cad_metrics(y,probas,subjects)  
            
        # fpr, tpr, thresholds = metrics.roc_curve(y, probas)
        # return metrics.auc(fpr, tpr)

def create_tree_classifier(**params):
    return AUCTreeClassifier(**params)

