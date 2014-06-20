from sklearn import linear_model,ensemble, metrics

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

def create_tree_classifier(**params):
    return AUCTreeClassifier(**params)


class AUCLogisticRegression(linear_model.LogisticRegression):
    
    def score(self, X, y):
        probas = self.predict_proba(X)
        probas = probas[:,1]
        subjects = [x.image for x in y]
        curve, _ = cad_metrics.froc(y, probas, subjects, pos_label=1)
        return cad_metrics.fp_mean(curve)
        
def create_logistic_regressor(**params):
    return AUCLogisticRegression(**params)