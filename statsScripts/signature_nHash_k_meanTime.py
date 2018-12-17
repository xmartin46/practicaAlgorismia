import subprocess
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

file = open(path + '\\data\\signature_nHash_k_meanTime.csv', 'w')
file.write('NumberOfHashFunctions, k, JaccardSimilarity' + '\n')


# n = number of hash functions applied to create signature matrix

functs = [1, 25, 50, 100, 250, 500, 750, 1000]
for n in functs:
    print(str(n))
    numRep = 0
    pairsFile = open(path + '\\algorithms\\pairsOfDocsSelec.txt', 'r')
    npairs = 0
    finTimes = [0 for n in range(16)]

    for pairs in pairsFile.readlines():
        times = [0 for n in range(16)]
        pairs = pairs.rstrip('\n').split(" ")

        for numRep in range(5):
            # k = size of shingles
            for k in range(16):
                out = subprocess.check_output([path + '\\algorithms\\signatureMinHashSimilarity.exe', str(k), str(pairs[0]), str(pairs[1]), str(1), str(1), str(n)])
                time = float(out.decode("utf-8"))
                time *= 1000
                times[k] += time
                if numRep == 4:
                    times[k] /= 5
                    finTimes[k] += times[k]
    for k in range(16):
        finTimes[k] /= 5
        out = str(n) + ', ' + str(k) + ', ' + str(finTimes[k])
        file.write(out + '\n')    
    pairsFile.close()
file.close()




    