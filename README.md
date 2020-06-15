# MiniSearchEngine

Implemented a mini search engine in C++. Compile the project with
```
make
```

And run as
```
./minisearch -i input_file -k K.
```

input_file is a file based on which the queries will be executed. Some files are found in the dataset file. K is the number of results returned for each querry.

The program supports the following commands:
```
/search word1 word2...
```

Search is followed by the words we want to search for and returns the top K results.

```
/df
```

Prints each word and the number of times it appears

```
/tf id word
```

Prints the frequency of the word "word" in the document with id

In order to delete the created files run
```
make clean
```
