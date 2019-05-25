

vector<int > fibersFromExperiment_(){

  ofstream infile ("all_fibers.txt");


//in this part the experimental fibet data is provided to be used for optimization. 
  vector<int > fibersFromExperiment;

  ifstream expFibs;
  expFibs.open("/data/store/razie/yeast/ExperimentalDNA_fiber_data/DNA_fiber_txt_format/Yeast_S_wt_30min.txt");
  if (! expFibs.is_open()) {cout <<"fiber data failed to open!!"<< endl;}

  string l_x;
  vector<int> X_v;
  while (getline(expFibs,l_x)){

    istringstream is_x(l_x);

      do{
          string sub_str;
          is_x >> sub_str;
          double sub_int;
          sub_int = atof(sub_str.c_str());
          X_v.push_back((int)((sub_int)*1000));
      }while(is_x);
    X_v.pop_back();
  }
  fibersFromExperiment = X_v; 
  sort(X_v.begin() , X_v.end() );
  int max_fib_len_exp = X_v.at(X_v.size()-1);
  int size_fibs_exp = X_v.size();
  //for (int i = 0; i< size_fibs_exp; i++){
    //cout << X_v.at(i) << endl;
  //}

return fibersFromExperiment; 
}
