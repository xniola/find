## Description

The goal of this project is to develop the find application that allows the number of occurrences of a set of strings within a group of files to be identified. The Knuth-Morris and Pratt Algorithm should be used to determine the number of occurrences (and their location). At each run, the application will output the list of analyzed files with the occurrences of the string in the text along with information regarding the positions of the string. The same information produced in output may be saved to an external file.

The sources must be delivered in a .zipper or .tgz archive. Makefile or CMake scripts must be enclosed to support compilation.

## Report

For each word searched, the report will contain the following information:

```
_WORD <word1>\r\n
TOTAL <total_occurrences_word1>\r\n
FILE <absoluthepath_file1>\r\n
OCCURRENCES <total_occurrences_file1>\r\n
<line1> <char1>\r\n
...
<linen> <charn>\r\n
...
FILE <absoluthepath_filek>\r\n
OCCURRENCES <total_occurrences_filek>\r\n
<line1> <char1>\r\n
...
<linem> <charm>\r\n _
```

The file will end with a blank line (\r\n).

The words are listed in the report in alphabetical order while for each word the files are presented in descending order by occurrence. In the case of multiple files with the same number of occurrences the files will be presented in alphabetical order (using absolute path).

For example, if we consider the files made available at the following link, located in the directory /home/loreti/Documents, the result of searching for the words aria, una and genius, the result will be:

```
_WORD aria\r\n
TOTAL 2\r\n
FILE /home/loreti/Documents/marzo1821.txt\r\n
OCCURRENCES 2\r\n
69 2\r\n
71 2\r\n
FILE /home/loreti/Documents/5maggio.txt\r\n
OCCURRENCES 0\r\n
WORD genio\r\n
TOTAL 1\r\n
FILE /home/loreti/Documents/5maggio.txt\r\n
OCCURRENCES 1\r\n
16 13\r\n
FILE /home/loreti/Documents/marzo1821.txt\r\n
OCCURRENCES 0\r\n
WORD una\r\n
TOTAL 5\r\n
FILE /home/loreti/Documents/marzo1821.txt\r\n
OCCURRENCES 4\r\n
28 15\r\n
32 1\r\n
34 1\r\n
49 4\r\n
FILE /home/loreti/Documents/5maggio.txt\r\n
OCCURRENCES 1\r\n
10 14\r\n
\r\n_
```

## Features
  
L'applicazione find può essere usata sia per generare dei report delle analisi che per estrarre informazioni da report generati in esecuzioni precedenti.

## Reports
  
To generate a new report, you need to indicate the words to be searched and the directories or files where to perform the search. The files and directories to be analyzed will be listed in a file, to be passed as input to the program, with the following structure:

```
_<path1> [r]\r\n
<path2> [r]\r\n
...
<pathk> [r]\r\n
\r\n_
```

Each <path> may be an absolute path or relative to a file or directory. In the second case, the optional r parameter will indicate whether subdirectories need to be parsed recursively. If not present only regular files in the directory will be parsed.

The list of words to be searched, however, will be passed to the program through a file of the form:

```
word1\r\n
word2\r\n
...
```
  
## Syntax
  
Program execution will take place with the following parameters:

```$ find (--words|-w) <wordfile> (--input|-i) <inputfile>```

In this case the report will be printed at the end of execution.

To save the report to a particular file you will need to add the parameter:

```--output|-o <outputfile>```

During the analysis phase, it will be possible to ignore files with specific extensions by adding the parameter:

```--exclude|-e <ext>```

Finally, to view the analysis process, the parameter can be added:

```--verbose|-v```


In this case for each file (or directory) analyzed it will be necessary to print messages indicating the start of processing, the end, and the time required for analysis. A possible pattern could be (the times given are not indicative):

```
Word processing start: air
Start directory processing: /home/loreti/Documents
Start processing file: /home/loreti/Documents/marzo1821.txt
End file processing: /home/loreti/Documents/marzo1821.txt (0.2 sec)
Start file processing: /home/loreti/Documents/5may.txt
End of file processing: /home/loreti/Documents/5maggio.txt (0.1 sec)
End word processing: air
```

## Report analysis
Once the report file has been generated, the find program can be used to retrieve the saved information. We could:

* Print the list of files where at least <n> times the word <word> is needed:

```$ find --report|-r <reportfile> --show <word> <n>```
If <n> is omitted, the value 1 is used.

* Print all locations where the word <word> is needed in the <file> file:

```$ find --report|-r <reportfile> --show <word> --file <file>```
If <word> is not needed in <file>, an appropriate message is printed on the screen.
