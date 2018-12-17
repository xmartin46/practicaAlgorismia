import subprocess
lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

file = open(path + '\\data\\lsh_time.csv', 'w')
file.write('t, k, time' + '\n')


# n = number of hash functions applied to create signature matrix

thres = [0.0, 0.2, 0.42, 0.64, 0.8, 1.0]
for t in thres:
    numRep = 0
    npairs = 0
    # nHashFunctions
    n = 500

    # k = size of shingles
    for k in range(16):
        out = subprocess.check_output([path + '\\algorithms\\lhs.exe', str(k), str(1), str(1), str(n), str(t)])
        time = float(out.decode("utf-8"))*1000
        out = str(t) + ', ' + str(k) + ', ' + str(time)
        print(out)
        file.write(out + '\n')   
         
file.close()




    