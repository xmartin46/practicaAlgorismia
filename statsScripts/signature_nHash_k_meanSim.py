import subprocess
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

file = open(path + '\\data\\signature_nHash_k_meanSim_jenkinsFunc.csv', 'w')
file.write('NumberOfHashFunctions, k, JaccardSimilarity' + '\n')


# n = number of hash functions applied to create signature matrix

# functs = [1, 25, 50] + [x for x in range(100, 1001, 50)]
functs = [1, 25, 50, 100, 250, 500, 750, 1000]
for n in functs:
    print(str(n))
    numPair = 0
    pairsFile = open(path + '\\algorithms\\pairsOfDocsSelec.txt', 'r')
    sims = [0 for n in range(16)]
    for pairs in pairsFile.readlines():

        pairs = pairs.rstrip('\n').split(" ")
        # k = size of shingles
        for k in range(16):
            out = subprocess.check_output([path + '\\algorithms\\signatureMinHashSimilarity.exe', str(k), str(pairs[0]), str(pairs[1]), str(0), str(1), str(n)])
            sims[k] += float(out.decode("utf-8"))
            if numPair == 4:
                sims[k] /= 5
                out = str(n) + ', ' + str(k) + ', ' + str(sims[k])
                file.write(out + '\n')
        numPair += 1
    pairsFile.close()
file.close()




    