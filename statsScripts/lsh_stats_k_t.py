import subprocess
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

file = open(path + '\\data\\lsh_stats.csv', 'w')
file.write('threshold, k, numCandidatePairs, trueCopyPairsDetected, falsePositivePairs, falseNegativePairs' + '\n')


# n = number of hash functions applied to create signature matrix
n = 500
thres = [0.0, 0.2, 0.42, 0.64, 0.8, 1.0]
for t in thres:
    # k = size of shingles
    for k in range(16):
        out = subprocess.check_output([path + '\\algorithms\\lsh.exe', str(k), str(0), str(1), str(n), str(t)])
        atts = out.decode("utf-8")
        out = str(t) + ', ' + str(k) + ', ' + atts
        print(out)
        file.write(out + '\n')   
         
file.close()




    