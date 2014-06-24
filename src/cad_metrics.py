# HOMEBREW MODULES
import cad_io

# subjects: list of [0, subjNr - 1]
def froc(labels, predictions, subjects, pos_label=1, misses=0):

    #counts of postive and negative labels
    db = []
    pos = 0 + misses
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
    thresh = []
    tp = 0.0
    fp = [0.0] * (max(subjects) + 1)
    tpf = 1.0

    # Given sorted list, set threshold equal to prediction
    # TP and FP count is monotonically increasing, by looking at positive values below threshold
    for i in xrange(len(db)):
        thresh.append(db[i][0])
        if db[i][1] == pos_label:
            tp += 1.0
        else:
            fp[db[i][2]] += 1.0         # Add false positive for subject dp[i][2]
            
        if pos != 0.0:
            tpf = tp/pos        

        xy_arr.append([sum(fp)/len(fp), tpf])

    return xy_arr, thresh
    
    
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

def cut_curve(xy_arr, thresh, fp_limit):
    
    for i in xrange(len(xy_arr)):
        if xy_arr[i][0] > fp_limit:
            return thresh[i]

def dist(x,y,z, x_,y_,z_):
    
    return ((x - x_)**2 + (y - y_)**2 + (z - z_)**2) ** 0.5
    
    
def analyse_candidates(data_y, train_location_path, annotation_location_path, sub_perm=None):
    
    ##### Read Data
    cand_x,cand_y,cand_z = cad_io.parse_locations(train_location_path)
    cand_locations = cad_io.load_locations(train_location_path)
    
    if sub_perm is not None:
        cand_x = cand_x[sub_perm]
        cand_y = cand_y[sub_perm]
        cand_z = cand_z[sub_perm]
        cand_locations = cand_locations[sub_perm]

    cand_subjects = cad_io.get_subjects(cand_locations)
    
    ann_x,ann_y,ann_z = cad_io.parse_locations(annotation_location_path)
    ann_locations = cad_io.load_locations(annotation_location_path)    
    ann_subjects = cad_io.get_subjects(ann_locations)

    tp = 0
    duplicates = 0
    fn = 0
    
    dist_lim = 10
    for s in xrange(max(ann_subjects)+1):
        print "Subject %d" % (s+1)
        ann_subs = ann_subjects == s
        cand_subs = cand_subjects == s

        p_count = sum(ann_subs)
        nr_samples = sum(cand_subs)

        cand_x_sub = cand_x[cand_subs]
        cand_y_sub = cand_y[cand_subs]
        cand_z_sub = cand_z[cand_subs]
        cand_labels = data_y[cand_subs]
        
        ann_x_sub = ann_x[ann_subs] * 0.5
        ann_y_sub = ann_y[ann_subs] * 0.5
        ann_z_sub = ann_z[ann_subs] * 0.5

        # Loop over annotations
        for i in xrange(p_count):
                    
            sub_tp = 0
            for j in xrange(nr_samples):
                d = dist(ann_x_sub[i], ann_y_sub[i], ann_z_sub[i], cand_x_sub[j], cand_y_sub[j], cand_z_sub[j])
                
                if d <= dist_lim and cand_labels[j] == 1:
                    sub_tp += 1

            if sub_tp > 0:
                tp += 1
                duplicates += sub_tp - 1
                # print 'Candidate'
                # print "(%d,%d,%d)" % (cand_x_sub[sub_j], cand_y_sub[sub_j], cand_z_sub[sub_j])
            else:
                fn += 1
                    
    
    print "Analysis done."
    print "True Positives / False Negatives: %d / %d" % (tp, fn)
    
    print "Duplicate True Positives: %d" % duplicates

    return tp, fn

