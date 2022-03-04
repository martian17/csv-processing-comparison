# csv-processing-comparison

## Usage
First create a test csv file using datagen.cpp
```bash
c++ datagen.cpp && ./a.out
```

A 1.7gb file named `test.csv` will be created. Here's the first 10 lines of `test.csv`
```
field1,field2
0.163905,0.917459
0.701493,0.483015
0.493611,0.814333
0.504735,0.58633
0.801685,0.932856
0.496236,0.328614
0.667945,0.693764
0.868341,0.0403233
0.375637,0.789386
```

Next, test out indivisual processing files
```bash
c++ stddev.onepass.cpp && ./a.out
```
