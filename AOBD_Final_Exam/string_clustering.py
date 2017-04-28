import sys
import os.path
import pandas as pd
import numpy as np
import json
import string
from fuzzywuzzy import fuzz
from sklearn.cluster import KMeans
filename = sys.argv[1]
column = sys.argv[2]
no_clusters = sys.argv[3]
def clustering(X):
    global df
    n = int(no_clusters)
    km = KMeans(n_clusters= n, init='k-means++', n_init=10, max_iter=300, tol=0.0001, precompute_distances='auto', verbose=0, random_state=None, copy_x=True, n_jobs=1)
    km.fit(X)
    data = df['data']
    preds = km.labels_
    clabels = np.unique(preds)
    for i in range(clabels.shape[0]):
        if clabels[i] < 0:
            continue
        cmem_ids = np.where(preds == clabels[i])[0]
        cmembers = []
        for cmem_id in cmem_ids:
            cmembers.append(data[cmem_id])
        with open("Cluster.txt", "a") as myfile:
            myfile.write("Cluster#%d: %s \n" % (i, ", ".join(cmembers)))
        myfile.close()

def normalise():
    global df
    if column in df.columns:
        exclude = set(string.punctuation)
        def compute_similarity(s1, s2):
            return 1.0 - (0.01 * max(fuzz.ratio(s1, s2),fuzz.token_sort_ratio(s1, s2),fuzz.token_set_ratio(s1, s2)))
        def handle_strings(x):
            x = x.upper()
            x = ''.join(ch for ch in x if ch not in exclude)
            return x
        df['data'] = df[column]
        df['data'] = df.data.apply(handle_strings)
        X = np.zeros((len(df.data), len(df.data)))
        for i in range(len(df.data)):
            for j in range(len(df.data)):
                if X[i, j] == 0.0:
                    X[i, j] = compute_similarity(df.data[i],df.data[j])
                X[j, i] = X[i, j]
        clustering(X)
    else:
        print("Column doesn't exist")

def main():
    if os.path.isfile(filename):
        global df
        df=pd.read_json(filename)
        normalise()
    else:
        print("File doesnot exist")

if __name__=="__main__":
    main()
