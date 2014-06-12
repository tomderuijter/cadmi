# subjects: list of [0, subjNr - 1]
def froc(labels, predictions, subjects, pos_label=1):

    #counts of postive and negative labels
    db = []
    pos = 0
    neg = 0
    
    # Count labels
    for i in xrange(len(labels)):
        if labels[i] == pos_label:
            pos+=1
        else:    
            neg+=1

        db.append([predictions[i], labels[i], subjects[i]])

    db.sort(lambda x,y: x[0] < y[0] and 1 or -1)    # Sort on ascending prediction scores

    # Construct FROC 
    xy_arr = []
    tp = 0.0
    fp = [0.0] * (max(subjects) + 1)
    tpf = 0.0

    # Given sorted list, set threshold equal to prediction
    # TP and FP count is monotonically increasing, by looking at positive values below threshold
    for i in xrange(len(db)):
        if db[i][1] == pos_label:
            tp += 1.0
        else:
            fp[db[i][2]] += 1.0         # Add false positive for subject dp[i][2]
            
        if pos != 0.0:
            tpf = tp/pos        

        xy_arr.append([sum(fp)/len(fp), tpf])

    return xy_arr
    
def auc(xy_arr, fp_limit=5):
    
    xy_arr = filter(lambda x: x[0] < fp_limit, xy_arr)      # Only consider up to a specified amount of false positives
    
    # Area Under Curve
    auc = 0.0
    prev_x = 0
    for x,y in xy_arr:
        if x != prev_x:
            auc += (x - prev_x) * y
            prev_x = x
            
    return auc



def fp_mean(xy_arr):
# Assertion: xy_arr is sorted on x
    
    measuring_points = [0.125,0.25,0.5,1.0,2.0,4.0,8.0]
    total = 0.0
    
    for m in measuring_points:
        
        xy_prev = [0.0, 0.0]
        exact = False
        for xy in xy_arr:
            
            if m == xy[0]:
                exact = True
                xy_prev = xy
            
            elif m < xy[0]:
                if exact:
                    total += xy_prev[1]
                else:
                    total += ((xy_prev[1] - xy[1])/(xy[0] - xy_prev[0])) * (m-xy_prev[0]) + xy_prev[1]              

                break

            else:
                xy_prev = xy
            
    return total / len(measuring_points)
