all:
	gcc -o find src/kmpalgo.c src/myStruct.c src/readwrite.c src/main.c src/parseArguments.c
report:
	./find --words parameters/inputWords.txt --input parameters/inputFile.txt --output parameters/output.txt
verbose:
	./find --words parameters/inputWords.txt --input parameters/inputFile.txt -o parameters/output.txt --verbose
exclude:
	./find --words parameters/inputWords.txt --input parameters/inputFile.txt -o parameters/output.txt --exclude txt
fileList:
	./find --report parameters/output.txt --show aria 2
printPositions:
	./find --report parameters/output.txt --show aria --file test/directory1/directoryFile2.txt
printReport:
	./find -w parameters/inputWords.txt -i parameters/inputFile.txt