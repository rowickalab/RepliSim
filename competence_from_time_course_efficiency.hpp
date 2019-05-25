//this code reads the efficiency from time course efficiency in Hawkins paper. these values are derived from experiment. competence is estimated based on the fact that comp. > effic.
/*
static double rand0_1(){

  static unsigned long s1 = 5318008, s2 = 11547776, s3 = 1040032;

  #define TAUS(s,a,b,c,d) (((s &c) <<d) & 0xffffffffUL) ^ ((((s <<a) & 0xffffffffUL)^s) >>b)
  s1 = TAUS(s1, 13, 19, 4294967294UL, 12);
  s2 = TAUS(s2,  2, 25, 4294967288UL, 4);
  s3 = TAUS(s3,  3, 11, 4294967280UL, 17);
  #undef TAUS
  return (s1^s2^s3)/4294967296.0;

}
*/


vector < vector <double> > competence_(){

  vector < vector <double> > competence;
  ifstream datafile_x;

  bool verbos = 1;

  
  datafile_x.open("allcompetsdNTPexp.txt");
  if (! datafile_x.is_open()) {cout <<"competence failed to open!!"<< endl;}

  string line_x;

  while (getline(datafile_x,line_x)){
     vector<double> X_vec;
     istringstream is_x(line_x);

     do{
        string sub_str;
        is_x >> sub_str;
        double sub_int;
        sub_int = atof(sub_str.c_str());

        X_vec.push_back(sub_int);
      }while(is_x);
      X_vec.pop_back();
      competence.push_back(X_vec);

      if (verbos ==0){
          for (int s = 0; s<X_vec.size(); s++){
            cout << "X_vec at " << s << " is " << X_vec.at(s) << endl;
          }
          cout << "x_vec size: " << X_vec.size() << " and competence vec size is: " << competence.size() << endl;
      }


  } // while getline loop

  if (verbos ==0){
      cout << " competence vec size is: " << competence.size() << endl;
  }

  return competence;

}

