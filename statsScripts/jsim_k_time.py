import subprocess

lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

pairsFile = open(path + '\\algorithms\\pairsOfDocsSelec.txt', 'r')

for pairs in pairsFile.readlines():

    pairs = pairs.rstrip('\n').split(" ")
    file = open(path + '\\data\\jsim_time_' + str(pairs[0]) + '_' + str(pairs[1]) + '.csv', 'w')
    file.write('k, Time elapsed' + '\n')

    times = [0 for n in range(16)]

    for numRep in range(5):
        # k = size of shingles
        for k in range(16):
            out = subprocess.check_output([path + '\\algorithms\\jSim.exe', str(k), str(pairs[0]), str(pairs[1]), str(1), str(1)])
            time = float(out.decode("utf-8"))
            time *= 1000
            times[k] += time

            if numRep == 4:
                times[k] /= 5
                out = str(k) + ', ' + str(times[k])
                file.write(out + '\n')

    file.close()
pairsFile.close()


