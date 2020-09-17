# Collector
## Introduction
This is a proof of concept of a tool to store learning resources (in url form). Analyses the contents of the url using the NLP process of Named Entity Extraction. This process extracts tokens of contextual importance (following a model), these tokens then are stored in a Inverted Index database.

The NLP extraction process uses MIT's [MIT Information Extraction](https://github.com/mit-nlp/MITIE) library. And the Inverted Index database is implemented using Google's [leveldb](https://github.com/google/leveldb/).

## Building
Copy from the [mit-nlp/mitie](https://github.com/mit-nlp/MITIE) repository the folders dlib and mitielib
and paste them in them in the nlp/external directory. Don't forget to fetch their models.

leveldb is fetched by CMake

 tip: use vector-of-bools CMakeTools for VSCode
```shell
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```
## Running

```shell
$ ./build/thecollector # from the project root folder
>add ./sample_txt/IIC.txt
  [adding]: 'add'  url: ./sample_txt/IIC.txt
Saving URL
Addding token: 'I2C
Addding token: 'SDA
Addding token: 'SCL
Addding token: 'Arduino
Addding token: 'Pioneer
>search I2C
  [searching]: 'search'  term: I2C
./sample_txt/IIC.txt
```

## Current State
This is a standalone executable that takes input with an internal command loop. A proper implementation of this project would be a web service with a front-end, and a more robust database.

Another feature that is currently missing is a way to input online urls. One stupid solution that would kinda work for this is to use some off-the-shelf html2text program, I tried `lynx --dump --force-html --nolist --nonumbers` and it worked nicely. Though that would require a argv interface. 


One of the minor goals of this project was to learn to build a modular CMake project, in this point its a failure,  just look at the top CMakeLists.txt

