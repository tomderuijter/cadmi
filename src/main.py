import os
import sys
import time
import logging
import datetime
import numpy as np
from sklearn import metrics as sklmetrics
from sklearn import ensemble as sklensemble

# HOMEBREW MODULES
import cad_io
import cad_classifier
import cad_metrics
import grid_search


def main(train_data_path, train_location_path, test_data_path=None, test_location_path=None, out_folder=None):
    
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
    logger.info("Reading training data")
    data_X, data_y = cad_io.load_data(train_data_path)
    locations = cad_io.load_locations(train_location_path)
    subjects = cad_io.get_subjects(locations)
    data_y = cad_io.add_subjects(data_y, subjects)
    
    ##### Split data
    logger.info("Splitting data")
    if test_data_path is None:
        train_X, test_X, train_y, test_y, train_perm, test_perm = cad_io.split_data(data_X, data_y, test_size)
    else:
        train_X = data_X
        train_y = data_y
    
    ##### Initialising classifier
    logger.info("Initialising classifier")
    params = {'n_jobs': 1, 'verbose': 1}
    classifier = cad_classifier.create_tree_classifier(**params)
    
    ##### Grid search
    logger.info("Starting grid search")
    params, best_score = grid_search.grid_search(classifier, train_X, train_y)
    logger.info("Found parameters: " + str(params))
    logger.info("Parameter confidence: " + str(best_score))
    
    ##### Train classifier
    logger.info("Training classifier with found parameters")
    params['n_jobs'] = 1
    params['verbose'] = 10
    classifier.set_params(**params)
    classifier.fit(train_X, train_y)
    
    ##### Load test data
    if (test_data_path is not None) and (test_location_path is not None):
        test_X, _ = cad_io.load_data(test_data_path)
        test_locations = cad_io.load_locations(test_location_path)
    else:
        test_locations = locations
    
    ##### Evaluate on test set
    logger.info("Classifying test data")
    predicted_y = classifier.predict_proba(test_X)      # Predict on whole set
    predicted_y = predicted_y[:,1]
        
    ##### Compute ROC and FROC
    if 'test_y' in locals():
        logger.info("Evaluating performance")
        
        # Zero prediction
        curve = cad_metrics.froc(test_y, np.zeros(len(data_X)), subjects, pos_label=1)
        zero_score = cad_metrics.fp_mean(curve)
    
        # Random prediction
        curve = cad_metrics.froc(test_y, np.random.sample(size=len(test_X)), subjects, pos_label=1)
        rand_score = cad_metrics.fp_mean(curve)
    
        # Actual prediction
        curve = cad_metrics.froc(test_y, predicted_y, subjects, pos_label=1)
        score = cad_metrics.fp_mean(curve)

        logger.info("Score: " + str(score))
        logger.info("Zero baseline: " + str(zero_score))
        logger.info("Random baseline: " + str(rand_score))

        logger.info("Confusion matrix (> 0.5): ")    
        cm = sklmetrics.confusion_matrix(data_y, predicted_y > 0.5)       # Evaluate on whole set
        logger.info(cm)

    ##### Write predictions
    if out_folder is not None:
        logger.info("Writing predictions to file")
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d_%H:%M:%S')
        out_path = out_folder+'predictions_'+st+'.txt'
        if not cad_io.write_predictions(test_locations,predicted_y,out_path):
            sys.exit(-1)   # IOError
        
    import matplotlib.pyplot as plt
    curve = np.array(curve)
    line, = plt.plot(curve[0:100,0],curve[0:100,1], linewidth=2)
    plt.show()
        
    # import code
    # code.interact(local=locals())

if __name__ == "__main__":
    # data_path = sys.argv[1]
    train_data_path = '/Users/tom/Documents/workspace/cadmi/data/examples/features.csv'
    train_location_path = '/Users/tom/Documents/workspace/cadmi/data/examples/coordinates.txt'
    test_data_path = '/Users/tom/Documents/workspace/cadmi/data/test/features.csv'
    test_location_path = '/Users/tom/Documents/workspace/cadmi/data/test/coordinates.txt'
    out_folder = '/Users/tom/Documents/workspace/cadmi/data/predictions/'
    main(train_data_path, train_location_path, test_data_path=test_data_path, test_location_path=test_location_path, out_folder=out_folder)
    sys.exit()