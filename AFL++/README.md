# Table of Contents

## How to Clone AFLplusplus

 - The next step is to go to the AFLplusplus [Github Repo](https://github.com/AFLplusplus/AFLplusplus) and hit the green
 "Code" button, and copy the HTTPS link to clone the repository.
- In your terminal - Terminal for Mac and PowerShell for Windows - write
`git clone https://github.com/AFLplusplus/AFLplusplus` to clone AFLpluslplus onto your computer.

# Phase 1: The First Fuzz

Estimated Time: 45 Minutes

## How to Run AFL++ on Exercise 1

This is completed in the target container Docker CLI:

1. Create a build directory (standard practice to name it build)
    - `mkdir build`
2. Change directory into build
    - `cd build`
3. Add AFL++ tooling to the compiler for your executable:
    - `CC=/AFLplusplus/afl-clang-fast CXX=/AFLplusplus/afl-clang-fast++ cmake ..`
    - Informational Note: `afl-clang-fast/++` is just one example of compilers you can use with AFL++ - different compilers have different advantages. You can use any of the compilers within the `/AFLplusplus` directory, and the `CXX` variable name is always the same as the `CC` variable, with `++` appended to the end. You can read more about the different compilers and their advantages within the [AFL++ docs](https://github.com/AFLplusplus/AFLplusplus/tree/stable/instrumentation).
4. Make the files in build
    - `make`
5. If you do not already have a seed directory, follow this process to create and populate one using the `dd` command.  If you do have such a directory, skip to step 7.
    - `cd ..`  
    - `mkdir seeds`  
    - `for i in {0..4}; do dd if=/dev/urandom of=seed_$i bs=64 count=10; done`  
    - `cd ..`  
    - `cd build`

You can read more about the `dd` command at this [Stack Exchange post](https://unix.stackexchange.com/questions/33629/how-can-i-populate-a-file-with-random-data).

6. Once you have a seed directory, enter the following command:
    - `/AFLplusplus/afl-fuzz -i [full path to your seeds directory] -o out -m none -d -- [full path to the executable]`

Congratulations, you are now running AFL++ on your target code! There should be a UI in terminal which shows you various statistics about the fuzzing process - look for the number of crashes detected.

## Analyzing the Crashes

- Once there is at least 1 crash shown in the UI of AFL++, hit `Ctrl + C` to exit AFL++. You can find the inputs that caused the program to crash by traversing to the `out/default/crashes` directory.
- You can use a bugger, such as `gdb` or `llvm`, to figure out what part of the input actually caused the program to crash. There are also other directories in `out/default` that show you some information gathered during the fuzzing process - feel free to explore them.

## Conclusion

Through this module, you have learned the basics of fuzzing. We walked through a basic introduction to fuzzing, and important software to download. We also discussed using AFL++ and Docker, and some example exercises to fuzz. One of the most important parts of this module is understanding the errors that you ran into while going through our tutorial. Although many potential errors are accounted for in our explanations, knowing where these exercises come from is half the battle of understanding how to fuzz because it will provide a foundation for fuzzing much more complex programs, such as flight controller software. If you want to spend more time learning about this, go back through the errors you ran into and things that were missed while walking through the practice exercises.

Fuzzing is used consistently in industries like aviation, finance, healthcare, energy, automotive, and more, as security regulations increase across all industries. If you want to learn more about the practical applications of fuzzing in industry, check out these articles:

- [Making fuzzing smarter](https://cybersecurity.springeropen.com/articles/10.1186/s42400-018-0002-y): This paper discusses fuzzing and how it can be made more efficient, smarter, and more state-of-the-art.
- [Ethereum Network Vulnerability](https://autobahn.security/post/fuzzing-blockchain-2): how advanced fuzz testing discovered a serious DOS vulnerability in the Ethereum network.
- [Different types of fuzzing](https://patricegodefroid.github.io/public_psfiles/Fuzzing-101-CACM2020.pdf): This article discussed a few different types of fuzzing - blackbox, whitebox, and grammar-based - and the effectiveness of each.
- In general...[a list of bugs you can find by fuzzing](https://www.code-intelligence.com/blog/what-bugs-can-you-find-with-fuzzing)
