import os
import sys
import logging
import numpy as np
from sklearn import metrics as sklmetrics

# HOMEBREW MODULES
import cad_io
import cad_classifier
import grid_search

def main(data_path, location_path, out_path):
    
    tmpPath='/Users/tom/tmp'
    test_size = 1000
    
    if(not os.path.isdir(tmpPath)):
        os.makedirs(tmpPath)

    # Setup logging
    log_nr = 0
    log_file = "pipeline_"+str(log_nr)+".log"

    while(os.path.isfile(tmpPath+"/"+log_file)):
        log_nr += 1
        log_file = "pipeline_"+str(log_nr)+".log"

    logging.basicConfig(level=logging.DEBUG,
                        format='%(asctime)s %(name)-12s %(levelname)-8s %(message)s',
                        datefmt='%d-%m %H:%M:%S',
                        filename=tmpPath + '/pipeline.log',
                        filemode='w')
    console = logging.StreamHandler(sys.stdout)
    console.setLevel(logging.INFO)
    formatter = logging.Formatter('%% %(asctime)s %(message)s')
    console.setFormatter(formatter)
    logging.getLogger('').addHandler(console)
    logger = logging.getLogger('main.py')
    
    ##### Read Data
    logger.info("Reading data")
    data_X, data_y = cad_io.load_data(data_path)
    locations = cad_io.load_locations(location_path)
    subjects = get_subjects(locations)
    
    ##### Split data
    logger.info("Splitting data")
    train_X, test_X, train_y, test_y, train_perm, test_perm = cad_io.split_data(data_X, data_y, test_size)
    
    ##### Initialising classifier
    logger.info("Initialising classifier")
    params = {'n_jobs': 1, 'verbose': 1}
    classifier = cad_classifier.create_tree_classifier(**params)
    
    ##### Grid search
    logger.info("Starting grid search")
    params = grid_search.grid_search(classifier, train_X, train_y)
    logger.info("Found parameters: " + str(params))
    
    ##### Train classifier
    logger.info("Training classifier with found parameters")
    params['n_jobs'] = 4
    params['verbose'] = 10
    classifier.set_params(**params)
    classifier.fit(train_X,train_y)
    
    ##### Evaluate on testset
    logger.info("Classifying test data")
    predicted_y = classifier.predict_proba(data_X)      # Predict on whole set
    predicted_y = predicted_y[:,1]
        
    ##### Compute ROC and FROC
    logger.info("Evaluating performance")
    # Zero prediction
    fpr,tpr, thresholds = sklmetrics.roc_curve(data_y,np.zeros(len(data_X)), pos_label=1)     # Evaluate on whole set
    zero_auc_score = sklmetrics.auc(fpr,tpr)
    
    # Random prediction
    fpr,tpr, thresholds = sklmetrics.roc_curve(data_y,np.random.sample(size=len(data_X)), pos_label=1)    # Evaluate on whole set
    rand_auc_score = sklmetrics.auc(fpr,tpr)
    
    fpr,tpr, thresholds = sklmetrics.roc_curve(data_y, predicted_y, pos_label=1)    # Evaluate on whole set
    auc_score = sklmetrics.auc(fpr,tpr)
    logger.info("AUC score: " + str(auc_score))
    logger.info("Zero baseline: " + str(zero_auc_score))
    logger.info("Random baseline: " + str(rand_auc_score))

    logger.info("Confusion matrix (> 0.5): ")    
    cm = sklmetrics.confusion_matrix(data_y, predicted_y > 0.5)       # Evaluate on whole set
    logger.info(cm)

    # TODO: Calculate FROC
        
    ##### Write predictions
    logger.info("Writing predictions to file")
    if(not cad_io.write_predictions(locations,predicted_y,out_path)):
        sys.exit(-1)
    
    import code
    code.interact(local=locals())

if __name__ == "__main__":
    # data_path = sys.argv[1]
    data_path = '/Users/tom/Documents/workspace/cadmi/data/examples/features.csv'
    location_path = '/Users/tom/Documents/workspace/cadmi/data/examples/labelsCoordinates.txt'
    out_path = '/Users/tom/Documents/workspace/cadmi/data/examples/predictions.txt'
    main(data_path, location_path, out_path)
    sys.exit()