log_content = open("log.txt", "r")
operation = ["ADD", "SOUS", "MULT"]

line = log_content.readline()
type_operation = line
type_operation.rstrip()
print(type_operation)
erreur = 0
nb_ligne = 0

line = log_content.readline()
while line != '':
    line.rstrip()
    chaine = line.split(',')
    result = int(chaine[0])
    a = int(chaine[1])
    b = int(chaine[2])
    verif = 0
    if(type_operation == "ADD\n"):
        verif = a + b
    elif(type_operation == "SOUS\n"):
        verif = a - b
    elif(type_operation == "MULT\n"):
        verif = a * b
        
    if (verif != result):
        erreur = erreur + 1
        print("R= ", result)
        print("V= ", verif)
    line = log_content.readline()
    nb_ligne = nb_ligne + 1
print("Erreur: %d / %d" %(erreur, nb_ligne))

log_content.close()