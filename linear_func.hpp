
double linearFunction_(int deltaL){


  double a = 0.000319528263;
  double b = 4.00596309;
 


  double newVel = (a *(double)deltaL + b )*1000/60;    // *1000/60 to give vel in b/sec
  //if (newVel > 48.33){cout  << "newvel: " << newVel << endl;}
  return newVel;

}

