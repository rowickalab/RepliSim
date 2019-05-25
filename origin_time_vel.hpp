//lognormal distribution for generating positive time and speed values


static double rand_gaus(void){
  double x, y, rr, u;
  double (*rnd01)() = rand0_1;
  /* loop until we have a point in the unit circle */
  while ( 1 ) {
    x = rnd01() * 2 - 1;
    y = rnd01() * 2 - 1;
    rr = x * x + y * y;
    if ( rr < 1 ) break;
  }
/* by now rr should be distributed uniformly between 0 and 1 */
/* alternatively, rr can be replaced by rand01() */
  u = -2 * log(rr);
  return x * sqrt( u / rr );
}


//this function finds the set of origins with corresponding time and velocity.


vector <double> xtv_assigner_(vector <int> *chromosomes, vector <double> *genomeFiringTime, int t_sd, double v,double sd, int EXP_TIME){

  
  vector<double> XVT; //this vector contains all the origins with corresponding time and velocity
  for (int k = 0; k < chromosomes-> size(); k++){ // number of origins
    //double (*rnd01)() = rand0_1;
    //double p_rand = rnd01();           //uncomment if competence is one for all the origins
    //if (p_rand <= compet-> at(k)){
      
      double (*rndgus)() = rand_gaus;
      double (*rnd01)() = rand0_1;
      
      double _v = 0;
      double v_ = 0;

      while((_v <=0) || (v_<=0)){

        double v1 = rndgus();
        double v2 = rndgus();
        _v = (v +  v1*(sd )) ;
        v_ = (v +  v2*(sd ));
      }//while _v
//generate time
      int j1 = 0; // to use only one time distribution

      double time = 0;
      while (time <= 0){
        double t = rndgus();
        double r = rnd01();
        time = genomeFiringTime->at(k)*60 + t*t_sd;
        //if (time < 300) {double p_rnd = rnd01();  time = 60 + (int)(60 * 5* p_rnd) + t*t_sd; 
      //time = (60) * 60 + t*t_sd;
      //cout << "genome firint time: " << time << "  600 +  "  << 60 * 5* p_rnd << endl;
        
      }


//~~~~~~~~~~~~~
      double rd = rnd01();
      if (time < EXP_TIME && time > 0 ){
          XVT.push_back(chromosomes-> at(k));
          XVT.push_back(time);
          XVT.push_back(_v);
          XVT.push_back(v_);
      }
    //}//if p_rand loop
  }//sum over k
    //cout << "XVT size is: " << XVT.size() << endl;
    return (XVT);

}

