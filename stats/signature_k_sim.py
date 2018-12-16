import subprocess
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

# n = number of hash functions applied to create signature matrix
for n in range(0, 1001, 50):
    if n == 0: n = 1
    file = open(path + '\\data\\signature_' + str(n) + '_k_sim.csv', 'w')
    file.write('NumberOfHashFunctions, k, JaccardSimilarity' + '\n')

    print('NumberOfHashFunctions, k, JaccardSimilarity')

    # k = size of shingles
    for k in range(21):
        out = subprocess.check_output([path + '\\algorithms\\signatureMinhashSimilarity.exe', str(k), str(n)])
        out = str(n) + ', ' + str(k) + ', ' + (out.decode("utf-8"))
        print(out)
        file.write(out + '\n')

    file.close()