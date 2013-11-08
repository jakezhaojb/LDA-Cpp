//Designed by Junbo ZHAO
//2013.11.8

#include "lda.h"

bool fexist(string filename){
	ifstream fid(filename.c_str());
	return fid;
}

Matrix reverse(Matrix Mat, int option){
	Matrix res(Mat.Getrows(),Mat.Getcols());
	switch(option){
		case 1:{//On rows
			vector<vector<double>> data_t = res.Getdata();
			vector<vector<double>> data_Mat = Mat.Getdata();
			for(int i=0;i<Mat.Getrows();i++)
				data_t[i] = data_Mat[Mat.Getrows()-1-i];
			res.setdata(data_t);
			return res;
			   }
		case 2:{//On columns
			Matrix Mat1 = Mat.trans();
			Matrix res1 = reverse(Mat1,1);
			res = res1.trans();
			return res;
			   }
		default:{
			cerr<<"WRONG Input arguments"<<endl;
			exit(-1);
				}
	}
}

bool generalized_sym_eig(Matrix &MatA, Matrix &MatB, vector<double> &Eig,Matrix &Eigvec){
	//This function is only dealing with the cases of A and B both being symmetric.
	//Preparing for CLAPACK Opeartions
	if(!MatA.symm()||!MatB.symm()){
		cout<<"Matrix NOT Symmetric."<<endl;
		return false;
	}
	integer i,j,N,lwork,itype,info;
	N = MatA.Getcols();
	lwork = 3*N;
	itype = 1;
	doublereal *A = new doublereal[N*N]();
	doublereal *B = new doublereal[N*N]();
	doublereal *W = new doublereal[N]();
	doublereal *work = new doublereal[lwork]();
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			A[i*30+j] = MatA(j,i);
	}
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			B[i*30+j] = MatB(j,i);
	}

	dsygv_(&itype,"V","U",&N,A,&N,B,&N,W,work,&lwork,&info);
	
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			Eigvec(i,j) = A[i*N+j];
	Eigvec = reverse(Eigvec,2);
	Eigvec.writefile("eigvectors.txt");

	for(i=0;i<N;i++)
			Eig[i] = W[i];
	return true;
}


bool LDACalc(string datafile,string labelfile,string fea_resfile,string projection_mat_resfile){
	if(fexist(fea_resfile)&&fexist(projection_mat_resfile))
		return true;
	if(!fexist(datafile)||!fexist(labelfile))
		return false;
	Matrix Fea;
	Fea.readfile(datafile);
	ifstream label_fin(labelfile.c_str());
	vector<int> label;
	int temp;
	double size = Fea.Getrows();
	while(!label_fin.eof()){
		label_fin>>temp;
		label.push_back(temp);
	}

	//Sw computing
	Matrix Sw = zeros(Fea.Getcols(),Fea.Getcols());
	vector<bool> t_flag(label.size(),false);
	for(vector<int>::size_type n=0;n<label.size();n++){
		if(t_flag[n])
			continue;
		vector<int> id = findVec(label,label[n]);
		for(vector<int>::size_type j=0;j<id.size();j++)
			t_flag[id[j]] = true;
		Matrix fea = Fea.select(id,1);
		vector<vector<double>> tmdata(1,fea.mean(1));
		Matrix tmu(1,fea.Getcols());
		tmu.setdata(tmdata);
		fea = fea - ones(fea.Getrows(),1)*tmu;
		Sw = Sw + fea.trans()*fea;
	}
	Sw = Sw/size;

	//St computing
	vector<vector<double>> mdata(1,Fea.mean(1));
	Matrix mu(1,Fea.Getcols());
	mu.setdata(mdata);
	Matrix St = Fea.trans()*Fea/size-mu.trans()*mu;

	//Generalized Eigen problem.
	vector<double> D(30,0); 
	Matrix V(Sw.Getrows(),Sw.Getrows());
	if(generalized_sym_eig(St, Sw, D, V)){
		Matrix Fea_LDA = Fea * V;
		Fea_LDA.writefile(fea_resfile);
		V.writefile(projection_mat_resfile);
		return true;
	}
	else{
		cout<<"Eigen Module Malfunctions."<<endl;
		return false;
	}
}

void main(){
	if(LDACalc("feature.txt","label.txt","feature_LDA.txt","prjection_mat.txt"))
		cout<<"LDA Finished"<<endl;
	else 
		cout<<"LDA Failed"<<endl;
}

