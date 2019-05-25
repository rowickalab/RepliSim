// this code gives the  genome wide T_1/2 from Hawkin data  

vector < vector <double> > Exp_t_half_(){

  vector < vector <double> > genome;
  ifstream datafile_x;

  bool verbos = 1;

  datafile_x.open("meanRepTYabuki.txt");
  if (! datafile_x.is_open()) {cout <<"exp_t_half.txt failed to open!!"<< endl;}

  string line_x;

  while (getline(datafile_x,line_x)){
     vector<double> X_vec;
     istringstream is_x(line_x);

     do{
         string sub_str;
         is_x >> sub_str;
         int sub_int;
         sub_int = atof(sub_str.c_str()); // atoi for string to int and atof for string to double 
         X_vec.push_back(sub_int);
      }while(is_x);
      X_vec.pop_back();
      genome.push_back(X_vec);

      if (verbos ==0){
          for (int s = 0; s<X_vec.size(); s++){
            cout << "X_vec at " << s << " is " << X_vec.at(s) << endl;
          }
          cout << "x_vec size: " << X_vec.size() << " and genome vec size is: " << genome.size() << endl;
      }


  } // while getline loop

  if (verbos ==0){
      cout << " genome vec size is: " << genome.size() << endl;
  }

  return genome;

}

