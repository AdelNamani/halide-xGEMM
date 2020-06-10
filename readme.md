# xGEMM implementation with Halide

This program is an implementation of a BLAS (Basic Linear Algebra Subprograms) routine from the third level which is the general matrix-matrix multiplication "xGEMM", of the form ``` alpha*A*B + beta*C``` using Halide.

## Prerequisites
### Linux
You'll need the Halide to run this project, you can either:
- Download the binaries directly from here [https://github.com/halide/Halide/releases](https://github.com/halide/Halide/releases), get [halide-linux-64-gcc53](https://github.com/halide/Halide/releases/download/release_2019_08_27/halide-linux-64-gcc53-800-65c26cba6a3eca2d08a0bccf113ca28746012cc3.tgz) or [halide-linux-32-gcc53](https://github.com/halide/Halide/releases/download/release_2019_08_27/halide-linux-32-gcc53-800-65c26cba6a3eca2d08a0bccf113ca28746012cc3.tgz) depending on your architecture and then extract it.
- Build Halide using LLVM : 
	- ### Acquiring & building LLVM 
		- ```git clone https://github.com/llvm/llvm-project.git --depth 1 -b release/10.x```
		- ``` mkdir llvm-build```
		- ``` cd llvm-build ```
			``` 
			cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../llvm-install \
	        -DLLVM_ENABLE_PROJECTS="clang;lld;clang-tools-extra" \
	        -DLLVM_TARGETS_TO_BUILD="X86;ARM;NVPTX;AArch64;Mips;Hexagon" \
	        -DLLVM_ENABLE_TERMINFO=OFF -DLLVM_ENABLE_ASSERTIONS=ON \
	        -DLLVM_ENABLE_EH=ON -DLLVM_ENABLE_RTTI=ON -DLLVM_BUILD_32_BITS=OFF \
	        ../llvm-project/llvm 
	        ```
        
        - ``` cmake --build . --target install ```
        - ``` export LLVM_CONFIG=<path to llvm>/llvm-install/bin/llvm-config```

- ### Acquiring & building Halide 
	- Start by cloning the repository ```git clone https://github.com/halide/Halide.git```  
	- Run `make` in the root directory. 

More information can be found at [https://github.com/halide/Halide](https://github.com/halide/Halide)

## Usage
First clone this repository : 

- ```git clone https://github.com/AdelNamani/halide-xGEMM.git```
- ``` cd halide-xGEMM```

To run the program you just need to run the ```script.sh``` with the path of Halide as a parameter. For example:

- With relative path : ```$ ./script.sh -p ../Halide```
- With absolute path : ```$ ./script.sh -p /mnt/c/Users/DELL/code/Halide```

This script will compile both programs and run them, if everything is okay and the multiplication is giving the correct results we will have this output:
```
Compiling halide_xGEMM.cpp ...
Compiling test_halide_xGEMM.c ...
Executing halide_xGEMM ...
Multiplication done ...
Saving to bin/data/results.txt ...
Saved successfully !
Executing test_halide_xGEMM ...
Reading and checking results ...
The multiplication with Halide is working well.
```

## Testing with different data
If you want to test with different matrices, you just have to change their initialization in the code, respecting these two constraints:

- Dimensions must be of the form : A(n,m) B(m,l) C(n,l)
- Same matrices must be in the Halide program and the C program that test the results

For example :
```C
int  a[2][4] = {
{0, 1, 2, 3},
{4, 5, 6, 7}
};

int  b[4][5] = {
{0, 1, 2, 3, 5},
{4, 5, 6, 7, 5},
{8, 9, 10, 11, 5},
{8, 9, 10, 11, 5}
};
  
int  c[2][5] = {
{0, 1, 2, 3, 1},
{4, 5, 6, 7, 1},
};
```

