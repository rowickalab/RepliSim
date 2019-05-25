
#ifndef HISTOGRAM_H
#define HISTOGRAM_H



class Histogram {

    int num_val;
    int max_val;
    //vector < vector <int> > *fibers;
    vector <int > *fibers;
    public:
  Histogram(int, int ,  vector <int >*);
  vector <double> binningFunc();

};
//==========================
vector <double> Histogram::binningFunc(){
      int k_s = log2 (num_val) +1;                      // number of bins in Sturges method
      int k_r = 2*num_val^(1/3);                        // number of bins in Rice method
      int BIN_COUNT = max_val;                  //average of the two methods is used ad the total number of bins    ????????????????????
      double bin_len = max_val/1000; //cout << "bin_len " << bin_len << endl;               // this value gives the bin length
      //cout << "bin count is: " << BIN_COUNT << endl;
      vector <double> SimCounts(BIN_COUNT,0);
      //int ExpCounts [BIN_COUNT] = {};
      vector <double> NumBinCount;
      int bin;

      for (int i1 = 0; i1< fibers->size(); i1++){// cout << "fibers size is: " << fibers.size() << " and fibers' size at " << i1 << " is " << fibers[i1].size() << endl;  
        //for (int j1 = 0; j1 < (*fibers)[i1].size(); j1++){ //cout << "i1 and j1 are: " << i1 << "  ,  " << j1 << endl;
           int sample = (*fibers).at(i1);
           for (int binNum = 0; binNum < BIN_COUNT; binNum++)  { //cout << "binNum " <<  binNum << endl;
                 int rightEdge = bin_len + binNum*bin_len;
                 if (sample <= rightEdge) {
                    bin = binNum; //cout << "bin* " <<  bin << endl;
                    break;
                }
              //cout << "bin_len:  " << bin_len << endl;
           } //cout << "bin " << bin << " and SimCounts.at(bin) " << SimCounts.at(bin) << endl;
          SimCounts.at(bin)++;
          //cout << " SimCounts at " << bin << " is " << SimCounts.at(bin) << endl;
        //}
      }
      NumBinCount.push_back(SimCounts.at(0)/(double)num_val);
      for (int i =1; i < BIN_COUNT; i++ ){
      // cout << "SimCounts at " << i << " is: " << SimCounts.at(i)/num_val << endl;
        NumBinCount.push_back(NumBinCount.at(i-1)+(SimCounts.at(i))/(double)num_val);
        //cout << "(NumBinCount.at(i-1)+(SimCounts.at(i))/(double)num_val) " << NumBinCount.at(i-1)+(SimCounts.at(i))/(double)num_val << endl; 
      }
      return NumBinCount;
}

//========================

Histogram::Histogram(int a1, int a2 ,  vector <int > *a3){   //cunstructor. prototype for Histogram::Histogram.....
  num_val = a1;
  max_val = a2;
  fibers = a3;
}















#endif

