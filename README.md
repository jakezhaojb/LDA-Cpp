LDA
===

>**Designer:** Junbo Zhao, Wuhan University, Working in Tsinghua National lab of intelligent images and documents processing.      
**Contact:** zhaojunbo1992chasing@gmail.com +86-18672365683

**Introduction**     
This package implements Linear Discriminative Analysis (LDA), in C++ and with the assistance of LAPACK. For LDA, it is a useful tool in machine learning and pattern recognition because it can significantly improve the capacity of your classifiers. Furthermore, a traditional framework is exploiting PCA + LDA in a cascaded structure, and PCA source code is available in another repository of mine.

**Configuration**    
To run the project, you should pre-configure LAPACK interfaces in your Visual C++ environment. It will be quite easy if you follow the website: http://icl.eecs.utk.edu/lapack-for-windows/clapack/index.html#libraries      
Find the "Part2: Using CLAPACK subroutines in a Visual (Studio) C/C++ Project" section in chapter "Running CLAPACK under Windows", and please follow the instructions strictly. Moreover, files will not be included in the repository if they can be derived from the former website (namely some .dll and .lib files).    

**Platform**     
This program is tested on VS2010, 32bit, Win7 system. I cannot guarantee it could be adopted on other platforms. If you can successfully compile the source code on some other platforms, please feel free to contact me！     

**Usage**     
1. Considering LDA is a supervised learning, other than a feature.txt (Storing the feature matrix), you should place a label.txt in the project. Note that two sample .txt files, storing feature matrix and label vector respectively, are involved in the repository, you should view them carefully first.     
2. Open lda.cpp to see how to exploit LDA.

