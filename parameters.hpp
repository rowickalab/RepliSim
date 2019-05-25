
#ifndef PARAMETERS
#define PARAMETERS 


class Parameters {

  public:
  vector<int> mean_t_early_();
  vector<int> mean_t_late_();
  vector<int> stand_devi_t_early_();
  vector<int> stand_devi_t_late_();
  vector<double> velocity_();
  vector<int> exp_t_();
  vector<int> chromosome_len_();
  vector<double> v_sd_();
  vector<int> t_end_();

};

vector<int> Parameters::mean_t_early_(){
int mean_t_early[] = { 20*60}; //

vector<int> early_time (mean_t_early , mean_t_early + sizeof(mean_t_early) /sizeof(int));
return early_time;
}


vector<int> Parameters::mean_t_late_(){
int mean_t_late[] = { 27*60};//, 28*60, 29*60, 30*60, 31*60, 32*60 }; //, 24*60, 25*60, 26*60, 27*60, 28*60, 29*60, 30*60, 31*60, 32*60, 33*60}; /* mean of time */
vector<int> late_time (mean_t_late , mean_t_late + sizeof(mean_t_late) /sizeof(int));
return late_time;
}


vector<int> Parameters::stand_devi_t_late_(){
int stand_devi_t_late[] = {2*60, 2.5*60,  3*60,  3.5*60, 4*60,4.5*60, 5*60, 5.5*60,  6*60, 6.5*60, 7*60, 7.5*60, 8*60, 8.5*60, 9*60, 9.5*60, 10*60};
vector<int> late_sd (stand_devi_t_late , stand_devi_t_late + sizeof(stand_devi_t_late) /sizeof(int));
return late_sd;
}


vector<double> Parameters::velocity_(){
double vel[] ={ 14,14.5, 15,15.5, 16, 16.5,17,17.5, 18,18.5, 19,19.5, 20, 20.5, 21,21.5, 22,22.5, 23}; //21, 22, 23, 24, 25, 26, 27, 28, 29 ,30  };

vector<double> vels (vel , vel + sizeof(vel) /sizeof(vel[0]));
return vels;
}

vector <double> Parameters::v_sd_(){
  double vsd[] = {0,.5, 1, 2, 3, 4, 5, 6, 0,7, 8 ,0, 0, 0, 0, 0, 9, 10, 11, 12 };// 9, 10,11, 12 }; //{5};
  vector <double> vsds( vsd , vsd + sizeof(vsd) / sizeof(vsd[0]));
  return vsds;
}



vector<int> Parameters::exp_t_(){
int exp_t[] = {32, 33, 34, 35, 36, 37, 38, 39, 40, 41 };//30, 31, 32, 33, 34, 35};//, 31, 32, 33, 34, 35, 36, 37};

vector<int> exp_ts (exp_t , exp_t + sizeof(exp_t) /sizeof(int));
return exp_ts;
}



vector<int> Parameters::t_end_(){
int t_end[] = {24, 25, 26, 27 ,28, 29, 30, 31, 32};

vector<int> t_ends (t_end , t_end + sizeof(t_end) /sizeof(int));
return t_ends ;
}



vector<int> Parameters::chromosome_len_(){
int chr_len[] = {230218 , 813184 , 316620 , 1531933 , 576874 , 270161 , 1090940 , 562643 , 439888 , 745751 , 666816 , 1078177 , 924431 , 784333 , 1091291 , 948066 };

vector<int> chr_lens (chr_len , chr_len + sizeof(chr_len) /sizeof(int));
return chr_lens;
}










#endif



 











