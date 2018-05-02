# Pi-Miniature-Calculation
### 1. Main algorithm ：
### [Chudnovsky algorithm](https://en.wikipedia.org/wiki/Chudnovsky_algorithm)

### 2. Description
- **The Chudnovsky algorithm is a fast method for calculating the digits of π.** 
- **It was published by the Chudnovsky brothers in 1989, and was used in the world record calculations of 2.7 trillion digits of π in December 2009, 5 trillion digits in August 2010, 10 trillion digits in October 2011, 12.1 trillion digits in December 2013 and 22.4 trillion digits of π in November 2016.** 
- **The time complexity of the algorithm is `O(N*log(N)^3)` where N as N digits of Pi.**

### 3. TestCase (No optimizations On my old laptop)
- **N = 10, Time elapsed = 0.006s**
- **N = 100, Time elapsed = 0.019s**
- **N = 1000, Time elapsed = 0.197s**
- **N = 10000, Time elapsed = 2.599s**
- **N = 100000, Time elapsed = 40.793s**
- **N = 1000000, Time elapsed = 700.538s**

### 4. Program implements
- **[Fast Fourier transform](https://en.wikipedia.org/wiki/Fast_Fourier_transform)**
- **[Newton's method](https://en.wikipedia.org/wiki/Newton%27s_method)**
- **[Binary_splitting method](https://en.wikipedia.org/wiki/Binary_splitting)**

### 5. Editorial:
- **[FFT based multiplication of large numbers](http://numbers.computation.free.fr/Constants/Algorithms/fft.html)**
- **[Binary splitting method](http://numbers.computation.free.fr/Constants/Algorithms/splitting.html#Brent76)**
- **[Newton's method and high order iterations](http://numbers.computation.free.fr/Constants/Algorithms/newton.html)**
