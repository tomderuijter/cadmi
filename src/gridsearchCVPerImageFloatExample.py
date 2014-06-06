from __future__ import print_function

from sklearn import datasets
from sklearn.cross_validation import train_test_split
from sklearn.grid_search import GridSearchCV
from sklearn.svm import SVC
import numpy as np
from PerImageFloat import PerImageFloat

print(__doc__)

digits = datasets.load_digits()
n_samples = len(digits.images)
X = digits.images.reshape((n_samples, -1))
y_original = digits.target


# Hier bouw ik de y array op. De waarde van het image field heb ik maar random bepaald.
y = []
pos = 0
for element in y_original:
    y.append(PerImageFloat(element, pos))
    pos += 1
    
# Deze is heel belangrijk, als de dbtype niet vast staat maakt die er np.float64 objecten van!
y = np.array(y, dtype=PerImageFloat)

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.5, random_state=0)


tuned_parameters = [{'kernel': ['rbf'], 'gamma': [1e-3, 1e-4],
                     'C': [1, 10, 100, 1000]},
                    {'kernel': ['linear'], 'C': [1, 10, 100, 1000]}]


# Zelf een domme score functie gemaakt omdat die anders niet met de PerImageFloats om kan gaan. 
# Maar dat maakt voor ons toch niet uit. Het printen werkt dus de informatie komt er.
def scorefunc(x,y):
    print(y[0].image)
    return 0.5

print()

clf = GridSearchCV(SVC(C=1), tuned_parameters, cv=5, score_func=scorefunc)
clf.fit(X_train, y_train)

print("Best parameters set found on development set:")
print()
print(clf.best_estimator_)
print()
print("Grid scores on development set:")
print()
for params, mean_score, scores in clf.grid_scores_:
    print("%0.3f (+/-%0.03f) for %r"
          % (mean_score, scores.std() / 2, params))
print()

print("Detailed classification report:")
print()
print("The model is trained on the full development set.")
print("The scores are computed on the full evaluation set.")
print()
y_true, y_pred = y_test, clf.predict(X_test)
#print(classification_report(y_true, y_pred))       #Classification report werkt niet met de PerImageFloat
print()