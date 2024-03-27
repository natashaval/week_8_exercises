# week_8_exercises

[UCL Week 8](https://github-pages.ucl.ac.uk/research-computing-with-cpp/08openmp/02_intro_openmp.html)  
[HackMd Week 8](https://hackmd.io/@comp0210-cpp-redesign/r154oOuTp)  
[Week 8 Solution](https://moodle.ucl.ac.uk/mod/url/view.php?id=6026769)  

Section 1

`OMP_NUM_THREADS=4 ./build/pi`
speedup is defined as (time using 1 thread) / (time using $n$ thread)
### Strong Scaling
n_cores | iterations | speedup
--- | --- | --- |
1 | 130 | -
2 | 66 | 1.96
4 | 35 | 5.14
8 | 17 | 7.65
12 | 12 | 10.83
16 | 13 | 10

### Weak Scaling (* scale N)
n_cores | iterations | speedup
--- | --- | --- |
1 | 130 | -
2 | 131 | 0.99
4 | 139 | 0.93
8 | 146 | 0.89
12 | 153 | 0.85
16 | 170 | 0.77