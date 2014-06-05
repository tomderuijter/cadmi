from sklearn import ensemble, metrics

    
####################### HACK
# Modify classifiers so gridsearch works with AUC.

class AUCTreeClassifier(ensemble.RandomForestClassifier):

        def score(self, X, y):
                probas = self.predict_proba(X)
                probas = probas[:,1]
                fpr, tpr, thresholds = metrics.roc_curve(y, probas)
                return metrics.auc(fpr, tpr)

def create_tree_classifier(**params):
        return AUCTreeClassifier(**params)

