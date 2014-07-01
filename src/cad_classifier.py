from sklearn import linear_model,ensemble,metrics

# HOMEBREW MODULES
import cad_metrics    
    
# Modify classifiers so gridsearch works with AUC or FROC.

class AUCTreeClassifier(ensemble.RandomForestClassifier):

    def score(self, X, y):
        probas = self.predict_proba(X)
        probas = probas[:,1]
        subjects = [x.image for x in y]
        curve, _ = cad_metrics.froc(y, probas, subjects, pos_label=1)
        return cad_metrics.fp_mean(curve)
        
        # fpr, tpr, thresholds = metrics.roc_curve(y, probas)
        # return metrics.auc(fpr, tpr)

    def do_predict(self, X):
        probas = self.predict_proba(X)
        probas = probas[:,1]
        return probas

def create_tree_classifier(**params):
    return AUCTreeClassifier(**params)


class AUCRidgeClassifier(linear_model.RidgeClassifier):
    
    def score(self, X, y):
        probas = self.decision_function(X)
        subjects = [x.image for x in y]
        curve, _ = cad_metrics.froc(y, probas, subjects, pos_label=1)
        return cad_metrics.fp_mean(curve)
        
    def do_predict(self, X):
        return self.decision_function(X)
        
def create_ridge_classifier(**params):
    return AUCRidgeClassifier(**params)