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
    
    md = MyData(data_X,labels)

    md.constrain(lambda x: x.GreyValues_average < 0.08)
    md.constrain(lambda x: x.GreyValues_average > 0.4)
    
    md.constrain(lambda x: x.VerticalMean_average > 0.15)
    
    md.constrain(lambda x: x.Blobness1_average < 0.38)
    md.constrain(lambda x: x.Blobness1_average > 0.65)
    
    md.constrain(lambda x: x.Blobness2_average < 0.35)
    md.constrain(lambda x: x.Blobness2_average > 0.65)

    # md.constrain(lambda x: np.logical_and(x.Blobness2_average > 0.43, x.Blobness2_average > 0.5))
        
    md.constrain(lambda x: x.Blobness3_average < 0.365)
    md.constrain(lambda x: x.Blobness3_average > 0.65)
    # md.constrain(lambda x: np.logical_and(x.Blobness3_average > 0.43, x.Blobness3_average > 0.5125))

    md.constrain(lambda x: x.Blobness4_average < 0.35)
    md.constrain(lambda x: x.Blobness4_average > 0.65)

    md.constrain(lambda x: x.Vesselness_average > 0.25)
    
    md.constrain(lambda x: x.Volume > 200)
    # md.constrain(lambda x: x.Surface > 80)
    md.constrain(lambda x: x.minDim > 10)
    # md.constrain(lambda x: x.maxDim > 10)
    md.constrain(lambda x: x.Ratio1 > 3.5)
    md.constrain(lambda x: x.Ratio2 > 2.5)
    md.constrain(lambda x: x.Compactness1 < 0.15)
    md.constrain(lambda x: x.Compactness2 < 0.1)
    md.constrain(lambda x: x.Sphericity < 0.775)
    md.constrain(lambda x: x.Curvature_average < 0.4)
    md.constrain(lambda x: x.Curvature_average > 0.74)

    md.constrain(lambda x: x.MeanCurvature_average < 0.482)
    md.constrain(lambda x: x.MeanCurvature_average > 0.5)

    md.constrain(lambda x: x.Curvedness_average < 0.82)
    
    md.constrain(lambda x: np.logical_and(x.Blobness2_average < 0.36, x.Curvedness_average < 0.9))
    md.constrain(lambda x: np.logical_and(np.logical_and(x.Blobness2_average > 0.43, x.Blobness2_average < 0.54), x.Curvedness_average < 0.975))
    md.constrain(lambda x: np.logical_and(np.logical_and(x.Blobness2_average > 0.41, x.Blobness2_average < 0.54), np.logical_and(x.MeanCurvature_average > 0.497, x.MeanCurvature_average < 0.502)))

    md.constrain(lambda x: np.logical_and(np.logical_and(x.Blobness2_average > 0.42, x.Blobness2_average < 0.56), x.VerticalMean_average < 0.0225))
    md.constrain(lambda x: np.logical_and(np.logical_and(x.Blobness3_average > 0.44, x.Blobness3_average < 0.58), x.VerticalMean_average < 0.0225))
    md.constrain(lambda x: np.logical_and(np.logical_and(x.Blobness2_average > 0.49, x.Blobness2_average < 0.51), x.VerticalMean_average < 0.025))
    
    sub_perm = np.logical_not(md.fp)

    return sub_perm
