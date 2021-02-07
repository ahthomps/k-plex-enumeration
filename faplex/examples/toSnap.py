
import sys


def graph2snap(graphFilePath, snapFilePath):
    graphFile = open(graphFilePath, "r")
    snapFile = open(snapFilePath, "w")
    node = 0

    graphFile.readline()
    line = graphFile.readline()

    while line:
        line = line.rstrip()
        neighbors = line.split(" ") if line else []
    
        for neighbor in neighbors:
            if int(neighbor) > node:
                snapFile.write("{} {}\n".format(node, neighbor))

        line = graphFile.readline()
        node = node + 1

def main():
    graphFilePath = ""
    snapFilePath = ""

    if len(sys.argv) == 1:
        print("./toSnap graphFile [snapFile]")
        exit(1)
    elif len(sys.argv) == 2:
        graphFilePath = sys.argv[1]
        snapFilePath = graphFilePath[graphFilePath.rfind("/") + 1:graphFilePath.rfind(".")] + ".txt"
    elif len(sys.argv) == 3:
        graphFilePath = sys.argv[1]
        snapFilePath = sys.argv[2]
    else:
        print("redundant arguments")
        print("./toSnap graphFile [snapFile]")
        exit(1)

    graph2snap(graphFilePath, snapFilePath)

    print(graphFilePath, snapFilePath)


main()
