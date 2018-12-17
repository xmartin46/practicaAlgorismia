import subprocess
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

# n = number of hash functions applied to create signature matrix
# 1 25 50 100 250 500 750 1000
for n in [1, 25, 50, 100, 250, 500, 750, 1000]:
    file = open(path + '\\data\\MEAN_signature_' + str(n) + '_k_sim.csv', 'w')
    file.write('NumberOfHashFunctions, k, JaccardSimilarity' + '\n')

    print('NumberOfHashFunctions, k, JaccardSimilarity')

    # k = size of shingles
    for k in range(16):
        # number of samples to then compute mean
        nsamp = 5
        add = 0.0
        
        for s in range(nsamp):
            out = subprocess.check_output([path + '\\algorithms\\signatureMinhashSimilarity.exe', str(k), str(n)])
            out = out.decode("utf-8")
            # print(out + ' ')
            add += float(out)

        mean = add / nsamp
        # print('mean is ' + str(mean), end='\n')
        res = str(n) + ', ' + str(k) + ', ' + str(mean)
        print(res)
        file.write(res + '\n')

    file.close()