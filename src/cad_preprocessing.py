import numpy as np

class MyData:

    def __init__(self, data, labels):
        self.data = data
        self.labels = labels
        self.fp = np.zeros((data.shape[0]),dtype=bool)
        
    def __getattr__(self,name):
        return self.data[:,self.labels[name]]
    
    def constrain(self,c):
        self.fp = np.logical_or(self.fp,c(self))

def decision_rule_filter(data_X,labels):
    '''Labels is a dictionary of column names to an index'''
        
    '''These constraints work very well with solid_v2'''
    md = MyData(data_X,labels)

    md.constrain(lambda x: x.GreyValues_average < 0.08)
    md.constrain(lambda x: x.GreyValues_average > 0.4)
    md.constrain(lambda x: x.GreyValues_median > 0.4)

    md.constrain(lambda x: x.VerticalMean_average > 0.2)
    md.constrain(lambda x: x.VerticalMean_median > 0.2)
    md.constrain(lambda x: x.VerticalMean_sd > 0.2)
    # md.constrain(lambda x: x.VerticalMean_min > 0.1)

    md.constrain(lambda x: x.Blobness1_average < 0.28)
    md.constrain(lambda x: x.Blobness1_average > 0.65)
    md.constrain(lambda x: x.Blobness1_median > 0.65)

    md.constrain(lambda x: x.Blobness2_average < 0.26)
    md.constrain(lambda x: x.Blobness2_average > 0.65)
    md.constrain(lambda x: x.Blobness2_median > 0.65)
        
    md.constrain(lambda x: x.Blobness3_average < 0.35)
    md.constrain(lambda x: x.Blobness3_average > 0.67)

    md.constrain(lambda x: x.Blobness4_average < 0.3)
    md.constrain(lambda x: x.Blobness4_average > 0.65)
    md.constrain(lambda x: x.Blobness4_median < 0.3)

    md.constrain(lambda x: x.minDim > 10)
    md.constrain(lambda x: x.Ratio1 > 3)

    # TODO: Take another look at compactness1 vs. other variables

    # md.constrain(lambda x: x.Sphericity < 0.75)

    md.constrain(lambda x: x.Curvature_average < 0.2)
    md.constrain(lambda x: x.Curvature_average > 0.8)

    md.constrain(lambda x: x.MeanCurvature_average < 0.47)
    md.constrain(lambda x: x.MeanCurvature_average > 0.5)

    md.constrain(lambda x: x.Curvedness_average < 0.85)
    md.constrain(lambda x: x.Curvedness_average > 1.0)
    md.constrain(lambda x: x.Curvedness_median < 0.95)
    md.constrain(lambda x: x.Curvedness_sd > 0.25)

    md.constrain(lambda x: np.logical_and(x.Curvature_average < 0.51, x.Curvature_average > 0.49))
    
    md.constrain(lambda x: x.DistanceToLungMembrane_average < 0.02)

    md.constrain(lambda x: x.DistanceToSliceCenter_average < 0.06)
    md.constrain(lambda x: x.DistanceToSliceCenter_average > 0.33)

    md.constrain(lambda x: np.logical_and(x.GreyValues_average < 0.09, x.Blobness1_average > 0.32))
    md.constrain(lambda x: np.logical_and(x.GreyValues_average < 0.12, np.logical_and(x.Curvature_average < 0.51, x.Curvature_average > 0.49)))
    
    md.constrain(lambda x: np.logical_and(x.VerticalMean_average < 0.1, x.Curvedness_median < 0.99))
    md.constrain(lambda x: np.logical_and(x.VerticalMean_average < 0.1, x.Curvedness_sd > 0.2))

    '''

    md.constrain(lambda x: np.logical_and(np.logical_and(x.Blobness2_average > 0.43, x.Blobness2_average < 0.54), x.Curvedness_average < 0.975))
    md.constrain(lambda x: np.logical_and(np.logical_and(x.Blobness2_average > 0.41, x.Blobness2_average < 0.54), np.logical_and(x.MeanCurvature_average > 0.497, x.MeanCurvature_average < 0.502)))

    md.constrain(lambda x: np.logical_and(np.logical_and(x.Blobness2_average > 0.45, x.Blobness2_average < 0.53), x.VerticalMean_average < 0.0225))
    # md.constrain(lambda x: np.logical_and(np.logical_and(x.Blobness3_average > 0.45, x.Blobness3_average < 0.53), x.VerticalMean_average < 0.0225))
    md.constrain(lambda x: np.logical_and(np.logical_and(x.Blobness2_average > 0.49, x.Blobness2_average < 0.51), x.VerticalMean_average < 0.025))
    '''   
    sub_perm = np.logical_not(md.fp)

    return sub_perm
