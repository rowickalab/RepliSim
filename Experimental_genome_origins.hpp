// this code gives the  genome wide origins from Hawkin data  
vector < vector <int> > Exp_genome_Oris_(){

  vector < vector <int> > genome;
  ifstream datafile_x;

  bool verbos = 1;

  datafile_x.open("OriYabuki.txt");
  if (! datafile_x.is_open()) {cout <<"exp_origin_of_replication.txt failed to open!!"<< endl;}

  string line_x;

  while (getline(datafile_x,line_x)){
     vector<int> X_vec;
     istringstream is_x(line_x);

     do{
         string sub_str;
         is_x >> sub_str;
         int sub_int;
         sub_int = atoi(sub_str.c_str());
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

