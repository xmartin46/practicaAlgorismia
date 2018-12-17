import subprocess
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

# n = number of hash functions applied to create signature matrix
pairsFile = open(path + '\\algorithms\\pairsOfDocsSelec.txt', 'r')

for pairs in pairsFile.readlines():

    pairs = pairs.rstrip('\n').split(" ")
    file = open(path + '\\data\\jsim_' + str(pairs[0]) + '_' + str(pairs[1]) + '.csv', 'w')
    file.write('k, Jaccard Similarity' + '\n')
    # k = size of shingles
    for k in range(16):
        out = subprocess.check_output([path + '\\algorithms\\jSim.exe', str(k), str(pairs[0]), str(pairs[1]), str(0)])
        out = str(k) + ', ' + (out.decode("utf-8"))
        file.write(out + '\n')

    file.close()



for n in [1, 25, 50, 100, 250, 500, 750, 1000]:

    file = open(path + '\\data\\signature_sim' + str(pairs[0]) + '_' + str(pairs[1]) + '.csv', 'w')
    file.write('NumberOfHashFunctions, k, JaccardSimilarity' + '\n')

    print('NumberOfHashFunctions, k, JaccardSimilarity')

    # k = size of shingles
    for k in range(16):
        out = subprocess.check_output([path + '\\algorithms\\signatureMinhashSimilarity.exe', str(k), str(pairs[0]), str(pairs[1]), str(0), str(n)])
        out = str(n) + ', ' + str(k) + ', ' + (out.decode("utf-8"))
        print(out)
        file.write(out + '\n')

    file.close()

    