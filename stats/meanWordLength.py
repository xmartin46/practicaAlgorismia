lacaPath = 'D:\\code\\practicaAlgorismia'
martinPath = ''
rogerPath = ''
path = lacaPath

file = open(path + '\\algorithms\\20doc\\documentBasic.txt', 'r')

nwords = 0
accumWordLen = 0
for line in file:
    for word in line.split(" "):
        nwords += 1
        accumWordLen += len(word)

print("nWords: " + str(nwords), end='\n')
print("nChars: " + str(accumWordLen), end='\n')
print("mean Word Length: " + str(accumWordLen/nwords))