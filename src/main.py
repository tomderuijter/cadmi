import os
import sys
import time
import logging
import datetime
import numpy as np
from sklearn import metrics as sklmetrics
from sklearn import ensemble as sklensemble
from sklearn import cross_validation as skl_cross_validation

# HOMEBREW MODULES
import cad_io
import cad_metrics
import cad_evaluation
import cad_classifier
import cad_preprocessing


def main(train_data_path, train_location_path, annotation_location_path, test_data_path=None, test_location_path=None, out_folder=None):
    
    tmpPath='/Users/tom/tmp'

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
    name_dict = cad_io.load_feature_names(train_data_path)
    locations = cad_io.load_locations(train_location_path)

    # Preprocess data - false positive removal
    sub_perm = None
    logger.info("Preprocessing data")
    sub_perm = cad_preprocessing.decision_rule_filter(data_X, name_dict)
    data_X, data_y, locations = cad_io.apply_permutation(data_X, data_y, locations, sub_perm)

    # Subsample negatives
    # sub_perm = cad_io.resample_negatives(data_y, .1)
    # data_X = data_X[sub_perm]
    # data_y = data_y[sub_perm]
    # locations = locations[sub_perm]

    # Piggyback subjects to labels
    subjects = cad_io.get_subjects(locations)
    data_y = cad_io.add_subjects(data_y, subjects)

    # Analyse candidate samples
    logger.info("Analysing data")
    hits,misses = cad_metrics.analyse_candidates(data_y, train_location_path, annotation_location_path, sub_perm)
    
    ##### Initialising classifier
    logger.info("Initialising classifier")
    # params = {'n_estimators': 100, 'max_depth': 15}
    # classifier = cad_classifier.create_tree_classifier(**params)
    params = {'alpha': 1., 'solver': 'lsqr', 'tol':1e-5}
    classifier = cad_classifier.create_ridge_classifier(**params)
    
    ##### Grid search
    # logger.info("Starting grid search")
    # params, best_score = cad_evaluation.grid_search(classifier, data_X, data_y, subjects)
    # logger.info("Found parameters: " + str(params))
    # logger.info("Parameter confidence: " + str(best_score))
    
    ##### Define classifier
    logger.info("Training classifier with found parameters")
    # params['n_jobs'] = 1
    # classifier.set_params(**params)
    
    ##### Load and evaluate test data
    if (test_data_path is not None) and (test_location_path is not None) and (out_folder is not None):
        logger.info("Loading test data")
        test_X, _ = cad_io.load_data(test_data_path)
        test_locations = cad_io.load_locations(test_location_path)
        logger.info("Training classifier")
        classifier.fit(data_X, data_y)
        logger.inf("Predicting scores on test data")
        predicted_y = classifier.predict_proba(test_X)      # Predict on whole set
        predicted_y = predicted_y[:,1]
        logger.info("Writing predictions to file")
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d_%H:%M:%S')
        out_path = out_folder+'predictions_'+st+'.txt'
        if not cad_io.write_predictions(test_locations,predicted_y,out_path):
            sys.exit(-1)   # IOError
                
    ##### Evaluate on cross validation
    if test_data_path is None:
        logger.info("Evaluating performance")
        # Remove this
        classifier.fit(data_X, data_y)
        predicted_y = classifier.do_predict(data_X)      # Predict on whole set
        
        # predicted_y = cad_evaluation.cross_validation(classifier, data_X, data_y, subjects)
                
        fpr, tpr, thresholds = sklmetrics.roc_curve(data_y, predicted_y, pos_label=1)
        print("AUC Score: "+ str(sklmetrics.auc(fpr, tpr)))
        
        curve, thresh = cad_metrics.froc(data_y, predicted_y, subjects, pos_label=1, misses=misses)
        score = cad_metrics.fp_mean(curve)
        logger.info("Score: " + str(score))
        
        thresh = cad_metrics.cut_curve(curve, thresh, 200)
        out_path = out_folder+'evaluation_locations.txt'
        if not cad_io.write_predictions(locations, np.array(predicted_y >= thresh ,dtype=int),out_path):
            sys.exit(-1)   # IOError
        
        import matplotlib.pyplot as plt
        curve = np.array(curve)
        plt.plot(curve[:,0],curve[:,1], linewidth=2)
        plt.axis([0,300,0,1])
        plt.show()

if __name__ == "__main__":
    # data_path = sys.argv[1]
   
    train_data_path = '/Users/tom/Documents/workspace/cadmi/data/examples/features_region_ex2.csv'
    train_location_path = '/Users/tom/Documents/workspace/cadmi/data/examples/coordinates_region_ex2.txt'
    annotation_location_path = '/Users/tom/Documents/workspace/cadmi/data/examples/example_annotations.txt'
    # test_data_path = '/Users/tom/Documents/workspace/cadmi/data/test/features.csv'
    # test_location_path = '/Users/tom/Documents/workspace/cadmi/data/test/coordinates.txt'
    out_folder = '/Users/tom/Documents/workspace/cadmi/data/predictions/'
    main(train_data_path, train_location_path, annotation_location_path, out_folder=out_folder) #test_data_path=test_data_path, test_location_path=test_location_path, out_folder=out_folder)
    sys.exit()