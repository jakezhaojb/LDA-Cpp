#ifndef _LDA_H_
#define _LDA_H_

#include "matrix.h"
#include "f2c.h"
#include "clapack.h"

using namespace std;

bool LDACalc(string datafile,
	     string labelfile,
	     string fea_resfile,
	     string projection_mat_resfile);

bool generalized_sym_eig(Matrix &MatA, Matrix &MatB, vector<double> &Eig, Matrix &Eigvec);
inline bool fexist(string filename);

template<typename T>
vector<int> findVec(vector<T> vec, T num){
	vector<int> res;
	for(vector<T>::size_type i=0;i<vec.size();i++){
		if(abs(vec[i]-num)<1e-3)
			res.push_back(i);
	}
	return res;
}


#endif
