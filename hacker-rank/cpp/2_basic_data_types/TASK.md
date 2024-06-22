# Basic Data Types

### Task
Print and format the input values.

### Input Format
Input consists of the following space-separated values: int, long, char, float, and double, respectively.

### Output Format
Print each element on a new line in the same order it was received as input. Note that the floating point value should be correct up to 3 decimal places and the double to 9 decimal places.

### Sample Input
```
3 12345678912345 a 334.23 14049.30493
```

### Sample Output
```
3
12345678912345
a
334.230
14049.304930000
```

### Explanation

Print int $3$,<br />
followed by long $12345678912345$,<br />
followed by char $a$,<br />
followed by float $334.23$,<br />
followed by double $14049.30493$.

#### Note
You can also use cin and cout instead of scanf and printf; however, if you are taking a million numbers as input and printing a million lines, it is faster to use scanf and printf. <br />
[StackOverflow: "Why is scanf faster than cin"?](https://stackoverflow.com/a/61716911/23174355)