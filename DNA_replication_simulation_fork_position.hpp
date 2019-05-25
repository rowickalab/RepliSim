// this code simulate the progretion of fork.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <valarray>
#include <cmath>

#define RES 1

//#define EXP_TIME 9*60   //in sec 
#define GLU_LEN 1
int min_exp_fib = 0;  // = 500/Res;
int max_exp_fib = 2000000;  // = min_exp_fib/Res;

using namespace std;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this function return the firing sites in a vector called firing_vec_pos. the sites are derived from a different function
vector<int> firing_vec_pos_(int firing_positions[] ){

  bool verbos = 1;

  //int firing_positions[] = {31164,70372, 124472, 147401, 176270 };     ////here is where we assign firing positions.
  vector<int> firing_vec_pos (firing_positions , firing_positions + sizeof(firing_positions) /sizeof(int));

  if(verbos==1){
    cout << "firing_vec_pos size is: " << firing_vec_pos.size() << endl ;
  }

  return firing_vec_pos;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this fuction returns the time of firings in a vector called firing_vec_time
vector<int> firing_vec_time_(int firing_times[] ){
  //int fork_velocity = 73;  // unit is bp/s

  //int firing_times[] = {1698*fork_velocity , 1734*fork_velocity , 1686*fork_velocity , 1374*fork_velocity , 1314*fork_velocity };     ////here is where we asign firing time corresponding to each pos.
  vector<int> firing_vec_time (firing_times , firing_times + sizeof(firing_times) /sizeof(int));

  return firing_vec_time;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

map<int , int> firing_map_(vector<int> pos_vec, vector<int> time_vec){
  map<int , int> m;
    for(int i = 0; i < pos_vec.size(); i++){
      m[pos_vec.at(i)] = time_vec.at(i);
    }
  return m;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this function checks the consistancy of the firing pos and times. This is done by comparign the successive times and check if consideeering the distance between them, the two times are possible. if not, the b igger time is removed from the firing time table.
vector<double> firing_vecs_(vector<int> *firing_pos , vector<int> *firing_time , vector<double> *firing_speed){

  bool verbos=1;

  if(verbos==0){
    cout << "firing pos size is: " << firing_pos->size() << endl;
    for(int ii = 0; ii < firing_pos->size(); ii++){
      cout << "firing pos is: " << firing_pos->at(ii) << endl;
      cout << "firing time is: " << firing_time->at(ii) << endl;
    }

    for(int gg = 0; gg < firing_speed->size(); gg++){
        //cout << "firing speed is: " << firing_speed->at(gg) << endl;
    }
  }


  vector<int> temp_vec_pos;
  vector<int> temp_vec_time;
  vector<double> temp_vec_speed;
  int temp_size = 2;
  int firing_size = firing_pos->size();

  if (firing_size ==1){
    temp_vec_pos.push_back(firing_pos->at(0));
    temp_vec_time.push_back(firing_time->at(0));
    temp_vec_speed.push_back(firing_speed->at(0));
    temp_vec_speed.push_back(firing_speed->at(1));
  }
  else  if (firing_size == 2){

    int i = 1;   int j;
    int delta_pos = firing_pos->at(i) - firing_pos->at(i-1);
    int delta_time = firing_time->at(i) - firing_time->at(i-1);
    double v_s;
    int t_min = min(firing_time->at(i) , firing_time->at(i-1));
    int t_max = max(firing_time->at(i) , firing_time->at(i-1));
    if (t_min == firing_time->at(i)){
      v_s = firing_speed->at(2*i); j = i;}
    else{
      v_s = firing_speed->at(2*i-1); j = i;}
    double delta_t_prime = (double)delta_pos/v_s;
    if ( abs(v_s *delta_time)  <  delta_pos ){
      temp_vec_pos.push_back(firing_pos->at(0));
      temp_vec_time.push_back(firing_time->at(0));
      temp_vec_speed.push_back(firing_speed->at(0));
      temp_vec_speed.push_back(firing_speed->at(1));
      temp_vec_pos.push_back(firing_pos->at(1));
      temp_vec_time.push_back(firing_time->at(1));
      temp_vec_speed.push_back(firing_speed->at(2));
      temp_vec_speed.push_back(firing_speed->at(3));

    }
    else{
      temp_vec_pos.push_back(firing_pos->at(j));
      temp_vec_time.push_back(firing_time->at(j));
      temp_vec_speed.push_back(firing_speed->at(2*j));
      temp_vec_speed.push_back(firing_speed->at(2*j+1));
    }
  } else {

    if(verbos == 0){
      cout << "initial value for firing_size is: " << firing_size << endl;
      cout << "initial value for temp_size is: " << temp_size << endl;
    }

    for (int i = 1; i < firing_size; i++){
      int delta_pos = firing_pos->at(i) - firing_pos->at(i-1);
      int delta_time = firing_time->at(i) - firing_time->at(i-1);

    if(verbos==0 ){

      cout << "In consistancy, delta_pos and delta_time are:  " << delta_pos << "  and  " << delta_time << endl;
      cout << "firing speed " << 2*i-1 << "th and " << 2*i << "th componets are: " << firing_speed->at (2*i-1) << " and  " << firing_speed->at (2*i) << endl; 
    }
//~~~~~~~~~~~
    double v_s;
    int t_min = min(firing_time->at(i) , firing_time->at(i-1));
    int t_max = max(firing_time->at(i) , firing_time->at(i-1));

    if(verbos==0){
      cout << "In consistancy, t_min and t_max are:  " << t_min << "  and  " << t_max <<   "  firing_speed.at(2*i-1) " << firing_speed->at(2*i-1) << endl;
    }

    if (t_min == firing_time->at(i)){   
      v_s = firing_speed->at(2*i);
    }
    else{   
      v_s = firing_speed->at(2*i-1);
    }



    double delta_t_prime = (double)delta_pos/v_s;

    if(verbos==0){

      cout << "v_time_smaller is: " << v_s << endl;
      cout << "delta_t_prime is: " << delta_t_prime << endl;
    }

    if(verbos == 0){
      cout << i << "th delta_pos is: " << delta_pos << endl;
      cout << i << "th delta_time is: " << delta_time << endl;
      cout << "i is: " << i << " delta_t_prime+ t_min is: " << delta_t_prime+ t_min << "  and t_max  is : " << t_max <<  ",  abs(v_s *delta_time): " << abs(v_s *delta_time) << ",  delta_pos: " << delta_pos << endl;   
    }
  
    if ( abs(v_s *delta_time)  <  delta_pos ){ 
      if(i == 1){
        temp_vec_pos.push_back(firing_pos->at(i-1));
        temp_vec_time.push_back(firing_time->at(i-1));
        temp_vec_speed.push_back(firing_speed->at(2*(i-1)));
        temp_vec_speed.push_back(firing_speed->at(2*(i-1)+1));
        if(verbos==0){
         cout << "0th component of temp_vec_pos is: " << temp_vec_pos.at(0) << endl;
         cout << "0th component of temp_vec_time is: " << temp_vec_time.at(0) << endl;
        }

      }
      else if (i == firing_pos->size()-1){ 
        if (verbos == 0){
          cout << "firing_speed->size() " << firing_speed->size() <<  " firing_pos->at(i-1): " << firing_pos->at(i) << " and i is: " << i << endl;
          cout << "firing_pos->at(i-1) " << firing_pos->at(i-1) << endl;
          cout << "firing_pos->at(i-2) " << firing_pos->at(i-2) << endl;
          cout << "firing_time->at(i-1) " << firing_time->at(i-1) << endl;
          cout << "firing_speed->at(2*(i-1)) " << firing_speed->at(2*(i-1)) << endl;
          cout << "firing_speed->at(2*(i-1)+1) " << firing_speed->at(2*(i-1)+1) << endl;
        }     
        if(firing_pos->at(i-1) != firing_pos->at(i-2)){    
          temp_vec_pos.push_back(firing_pos->at(i-1));
          temp_vec_time.push_back(firing_time->at(i-1));   
          temp_vec_speed.push_back(firing_speed->at(2*(i-1)));   
          temp_vec_speed.push_back(firing_speed->at(2*(i-1)+1));  
          if(verbos==0){
            cout << "temp_vec_pos.size() " << temp_vec_pos.size() << endl;
            cout << "temp_vec_time.size() " << temp_vec_time.size() << endl;  
            //cout << i-2 <<"th component of temp_vec_pos is: " << temp_vec_pos.at(i-2) << endl;
            //cout << i-2 << "th component of temp_vec_time is: " << temp_vec_time.at(i-2) << endl;
          }
        } 

        temp_vec_pos.push_back(firing_pos->at(i));
        temp_vec_time.push_back(firing_time->at(i));
        temp_vec_speed.push_back(firing_speed->at(2*i));
        temp_vec_speed.push_back(firing_speed->at(2*(i)+1)); //cout << "kharrrrrrrrrrrr" << endl;

      }
      else{ //cout << "khar 2 " << endl;  
        if(firing_pos->at(i-1) != firing_pos->at(i-2)){
          temp_vec_pos.push_back(firing_pos->at(i-1));
          temp_vec_time.push_back(firing_time->at(i-1));
          temp_vec_speed.push_back(firing_speed->at(2*(i-1)));
          temp_vec_speed.push_back(firing_speed->at(2*(i-1)+1));
          if(verbos==0){     
            cout << i-1 <<"th firing  pos is:" << firing_pos->at(i-1) << endl;
          }
        }

      }

    }  // if ( abs(v_s *delta_time)  <=  delta_pos ) loop
    else{ //cout << "kahr 1" << endl;
      if (i == firing_pos->size()-1){
        if(verbos==0){
          cout << "i is: " << i << " and firing time at " << i << " is: " << firing_time->at(i) << " and firing time at " << i-1 << " is " << firing_time->at(i-1) << " firing_pos->at(i-1) " << firing_pos->at(i-1) << " firing_pos->at(i-2) " << firing_pos->at(i-2) << endl;
        }
        if (firing_time->at(i) > firing_time->at(i-1) ){
          if (firing_pos->at(i-1) != firing_pos->at(i-2)){
            temp_vec_pos.push_back(firing_pos->at(i-1));
            temp_vec_time.push_back(firing_time->at(i-1));
            temp_vec_speed.push_back(firing_speed->at(2*(i-1)));
            temp_vec_speed.push_back(firing_speed->at(2*(i-1)+1));
            if(verbos==0){
              cout << "delta_pos condition does not hold, the " << i-1 << "th pos and time components in temp vec are: " << firing_pos->at(i-1) << " and " << firing_time->at(i-1) << endl;
            }
          }
        }
        else{
          if (firing_pos->at(i) != firing_pos->at(i-1)){
            if(verbos==0){
              cout << "i is: " << i << "and firing time at i is: " << firing_time->at(i) << endl;
            }
            temp_vec_pos.push_back(firing_pos->at(i));
            temp_vec_time.push_back(firing_time->at(i));
            temp_vec_speed.push_back(firing_speed->at(2*(i)));
            temp_vec_speed.push_back(firing_speed->at(2*(i)+1));
          }
        }
      }
      else{
        if (firing_time->at(i) > firing_time->at(i-1) ){// looop
          if (i != 1){
            if (firing_pos->at(i-1) != firing_pos->at(i-2)){
              temp_vec_pos.push_back(firing_pos->at(i-1));
              temp_vec_time.push_back(firing_time->at(i-1));
              temp_vec_speed.push_back(firing_speed->at(2*(i-1)));
              temp_vec_speed.push_back(firing_speed->at(2*(i-1)+1));
   
            }
          }
          firing_pos->at(i) = firing_pos->at(i-1);
          firing_time->at(i) = firing_time->at(i-1);
          firing_speed->at(2*i) = firing_speed->at(2*(i-1));
          firing_speed->at(2*i+1) = firing_speed->at(2*(i-1)+1);
        }//looop
      }

    }//end loop else abs(v_s *delta_time)  <=  delta_pos condition



    if(verbos==0){
      cout << "temp_vec_time.size is:" << temp_vec_time.size() << endl;
      cout << "temp_vec_pos.size is:" << temp_vec_pos.size() << endl;
      cout << "firing_vec.size is:" << firing_pos->size() << endl;
      for (int i = 0; i < firing_pos->size(); i++){
        cout << "firing_pos at " << i << " is " << firing_pos->at(i) << endl;
      }
    }


  } /// for loop over firing_pos/time


  if (temp_vec_time.size() < 1){
    temp_vec_pos.push_back(firing_pos->at(0));
    temp_vec_time.push_back(firing_time->at(0));
    temp_vec_speed.push_back(firing_speed->at(0));
    temp_vec_speed.push_back(firing_speed->at(1));
  }

  if(verbos==0){
    cout << "temp_vec_time.size is:" << temp_vec_time.size() << endl;
    cout << "temp_vec_pos.size is:" << temp_vec_pos.size() << endl;
    cout << "firing_vec.size is:" << firing_pos->size() << endl;
    for (int i = 0; i < firing_pos->size(); i++){
      cout << "firing_pos at " << i << " is " << firing_pos->at(i) << endl;
    }
    for (int jb =0; jb< temp_vec_pos.size(); jb++){
      cout << "temp_vec pos at " << jb << " is " << temp_vec_pos.at(jb) << endl;      
    }
  }



  //cout << "after the while loop" << endl;
   if(verbos== 0){
      for (int ss = 0; ss < temp_vec_pos.size(); ss++){
        cout << "temp_vec_pos's " << ss << "component is: " << temp_vec_pos.at(ss) << endl;
      }
    }

    temp_size = temp_vec_pos.size();
    firing_size = firing_pos->size();

    *firing_pos = temp_vec_pos;
    *firing_time = temp_vec_time;
    *firing_speed = temp_vec_speed;
    temp_vec_pos.clear();
    temp_vec_time.clear();
    temp_vec_speed.clear();
    //cout << "temp_size is:  " << temp_size << endl;
    //cout << "firing_size is: " << firing_size << endl;


  }  //while(firing_size == temp_size);  ///while loop end

////////////    a final check of consistancy  ///////
    int aa;   // the component to be eliminated;
    int initsize = firing_pos->size();
    int newsize =0;
    if (initsize > 2 ){
      do{
        newsize = firing_pos->size();
        for (int jig = 1; jig < firing_pos->size(); jig++){
          double vel;
          if (firing_time->at(jig) > firing_time->at(jig-1) ) {vel =  firing_speed->at(2*(jig-1)+1); aa = jig; } else { vel =  firing_speed->at(2*(jig)); aa = jig-1; }
          if ( (firing_pos->at(jig) - firing_pos->at(jig-1)) < ( abs( (firing_time->at(jig) - firing_time->at(jig-1)))* vel ) ){
            firing_pos->erase(firing_pos->begin() + aa);
            firing_time->erase(firing_time->begin() + aa);
            firing_speed->erase(firing_speed->begin() + 2*aa);
            firing_speed->erase(firing_speed->begin() + 2*aa+1);
          }
        initsize = firing_pos->size();
      }
    }while (initsize != newsize);

    for (int jig = 1; jig < firing_pos->size(); jig++){
      double vel;
      if (firing_time->at(jig) > firing_time->at(jig-1) ) {vel =  firing_speed->at(2*(jig-1)+1); aa = jig; } else { vel =  firing_speed->at(2*(jig)); aa = jig-1; }
      if ( (firing_pos->at(jig) - firing_pos->at(jig-1)) < ( abs( (firing_time->at(jig) - firing_time->at(jig-1)))* vel ) ){
        cout << "deltax: " << (firing_pos->at(jig) - firing_pos->at(jig-1)) << " deltaxprime: " << abs( (firing_time->at(jig) - firing_time->at(jig-1)))* vel << " vle: " << vel << endl;
        cout << "@@@@@@@@@@@@@@@@final consistant firing pos & time at " << jig << " are " << firing_pos->at(jig) << " and " << firing_time->at(jig) << endl;
        cout << "@@@@@@@@@@@@@@@@final consistant firing pos & time at " << jig << " are " << firing_pos->at(jig-1) << " and " << firing_time->at(jig-1) << endl;
        cout << "@@@@@@@@@@@@@@@@final consistant firing speed att " << 2*jig << " are " << firing_speed->at(2*jig) << " and " << firing_speed->at(2*(jig-1)+1) << endl;

      }
    }
}
////////////


  vector<double> firing_pos_time_speed;
  firing_pos_time_speed.reserve( firing_pos->size() + firing_time->size() + firing_speed->size() );
  firing_pos_time_speed.insert(firing_pos_time_speed.end(), firing_pos->begin() , firing_pos->end() );
  firing_pos_time_speed.insert(firing_pos_time_speed.end(), firing_time->begin() , firing_time->end() );
  firing_pos_time_speed.insert(firing_pos_time_speed.end(), firing_speed->begin() , firing_speed->end() );

  if(verbos==0){
    cout << "firing_pos_time_speed size is: " << firing_pos_time_speed.size() << endl;
  }



////////////
  return firing_pos_time_speed;

}    /// function end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// after all the consistant times and positiond are selected from the possible pos and times, fork progression is done by this function. the output is a text file which contains the corresponding time for each positoon.
vector <vector <int> > progresion_function_(vector<int> *consistant_firing_pos , vector<int> *consistant_firing_time , vector<double> *consistant_firing_speed, int chr_length, int EXP_TIME){ 

  vector <vector <int> > allpos;
  bool verbos = 0;
  vector <int> pos_at_exp_time; // since we need the fibers, we don't care about the sequence they belong to. However, we can get it from the other codes.
  vector <int> distance_traveled;   ///*******************
  int x0 =  consistant_firing_pos->at(0);
  double t0 =  consistant_firing_time->at(0);
  double v0 =  consistant_firing_speed->at(0);
  if (verbos == 1){
    cout << "x0 = " << x0 << " and t0 = " << t0 << " and v0 = " << v0 << endl;
  }

  if ((x0-v0*(EXP_TIME-t0)) >= 1 ){
    pos_at_exp_time.push_back((x0-v0*(EXP_TIME-t0) /(int)1) );
    if (verbos == 1){if (x0-v0*(EXP_TIME-t0) < 1 ){cout << "X0: " << (x0-v0*(EXP_TIME-t0))/(int)1 << "  "<< endl;} }
  }
  else{
    pos_at_exp_time.push_back(1);
    if (verbos == 1){cout << "X0: " << 1 << "  ";}
  } 
  if(verbos==1){
    for (int rre = 0; rre < consistant_firing_speed->size(); rre++){
        cout << rre << "th comp of velocity vector is:  " << consistant_firing_speed->at(rre) << endl;
    }

    cout << "consistant_firing_pos.size() is: " << consistant_firing_pos->size() << endl;
  }
//cout << "EXP_TIME "<< EXP_TIME << endl;

  for (int k = 0; k < consistant_firing_pos->size()-1; k++){

    double _v = consistant_firing_speed->at(2*k+2);
    double v_ = consistant_firing_speed->at(2*k+1);
    int x1 =  consistant_firing_pos->at(k);
    int x2 =  consistant_firing_pos->at(k+1);

  
   
 

    double t1 =  consistant_firing_time->at(k);
    double t2 =  consistant_firing_time->at(k+1);

  if (verbos == 1){
      cout << "for k = " << k << "  ~~~ v_ and _v re:    " << v_ << "  and  " << _v << " x1: " << x1 << " x2: " << x2 << " t1: " << t1 << " t2: " << t2 << endl;
    }

    int delta_x_ = x2 - x1;
    int delta_t = t2 - t1;
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    int X1 = (EXP_TIME - t1)* v_; //cout << "X1: " << X1 << endl;
    int X2 = (EXP_TIME - t2) * _v;  // cout << "X2: " << X2 << endl;
    if ((X1 + X2) < delta_x_-2){
      pos_at_exp_time.push_back(x1+X1);
      pos_at_exp_time.push_back(x2-X2);
      if (verbos == 1){
        if (x1+X1 ==0 || x2-X2 ==0){
          cout << "  X" << k << ": " << x1+X1  << "   " <<endl; 
          cout << " and X" << k+1 << ": " << x2-X2 << "   ";
        }
      }
    }
  }
    double t_end = consistant_firing_time->at( consistant_firing_time->size() -1 );
    double v = consistant_firing_speed->at(consistant_firing_speed->size()-1);
    int x = consistant_firing_pos->at(consistant_firing_pos->size()-1);
    int X = (EXP_TIME - t_end) * v;
    if (x+X < chr_length){
      pos_at_exp_time.push_back(x+X);
      if (verbos ==1){cout << x+X << endl;}
    } else{
      pos_at_exp_time.push_back(chr_length);
      if (verbos ==1){cout << chr_length << endl;}
    }
    
    if (verbos == 1){
      cout << "v is: " << v << " and last pos is: " << pos_at_exp_time.at(pos_at_exp_time.size()-1) << endl; 
    }
  if (verbos == 1){
    cout << "pos_at_exp_time: "<< endl;
    for (int i3 = 0; i3 < pos_at_exp_time.size(); i3++){
      cout << "   " << pos_at_exp_time.at(i3) ;
    }
    cout << endl;
  }
  
  allpos.push_back(distance_traveled);
  allpos.push_back(pos_at_exp_time);   
  return allpos;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this function loops over  all the lines in XT.txt file and for each line it calls the consistancy and progression function and finds the times for each line in the XT.txt file.  



vector<vector<int> > pos_at_exp_time_derivation(vector<vector<double> > *XT_vec_vec,int chr_length, int EXP_TIME ){

vector<vector<int> > pos_at_exp_time_matrix;

bool verbos = 0;
   
      
     
//=======================
fstream outputfile;
//outputfile.open("x_t_results.txt" , std::fstream::out);



//string line_xt;     // in here the goal is to get each line and split it into sub-stings which are the psitions and corresponding times of firing sites. So inside the while loop we define a vector correspond to each line of the "XT.txt" file and then extract the X and T  from this vector as "firing_time" and "firing_pos" vectors. 


for (int ah = 0; ah < XT_vec_vec->size(); ah++){

  if(verbos==1){
    cout << "xt_vec size is: " << (*XT_vec_vec)[ah].size() << endl;

    for (int sz =0; sz < (*XT_vec_vec)[ah].size(); sz++){
      cout << "and components are: " << (*XT_vec_vec)[ah][sz] << endl;
    }
  }

  vector<int> firing_pos;
  vector<int> firing_time;
  vector<double> firing_speed;

  for(int ih =0; ih< ((*XT_vec_vec)[ah].size())/4; ih++){
    firing_pos.push_back((*XT_vec_vec)[ah][ih*4]/RES);
    firing_time.push_back((*XT_vec_vec)[ah][ih*4+1]);
    firing_speed.push_back((*XT_vec_vec)[ah][ih*4+2]/RES);
    firing_speed.push_back((*XT_vec_vec)[ah][ih*4+3]/RES);

  }

  if(verbos== 1){
    for(int ii = 0; ii < firing_speed.size(); ii++){
        cout << "~~~~~~firing speed is: " << firing_speed.at(ii) << endl;
    }
  }

  if(verbos==1){
    for(int gg = 0; gg < firing_pos.size(); gg++){
      cout << "~~~~~~firing time is: " << firing_time.at(gg) << endl;
      cout << "~~~~~~firing pos issssssssssss: " << firing_pos.at(gg) << endl;
    }
  }

  //vector<int> firing_pos = firing_vec_pos_(firing_positions[] );
  //vector<int> firing_time = firing_vec_time_(firing_times[] );
                  
  vector <double> firing_pos_time_speed = firing_vecs_( &firing_pos , &firing_time, &firing_speed);                    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  int firing_pos_size = firing_pos_time_speed.size()/4;

  if(verbos==1){
    cout << "number of firing times (and positions) is: " << firing_pos_size <<  endl;
  }

  vector<int> consistant_firing_time;
  vector<int> consistant_firing_pos;
  vector<double> consistant_firing_speed;
  for(int i=0; i<firing_pos_size; i++){
    consistant_firing_pos.push_back(firing_pos_time_speed.at(i));
    consistant_firing_time.push_back(firing_pos_time_speed.at(i+firing_pos_size));
    consistant_firing_speed.push_back(firing_pos_time_speed.at(2*(firing_pos_size+i)));
    consistant_firing_speed.push_back(firing_pos_time_speed.at(1+2*(firing_pos_size+i)));
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int jj =consistant_firing_pos.size();
  int kk = firing_pos.size();
  int ll =0;
  if (verbos==1){
    cout << "jj and kk are: " << jj << " and " << kk << " and consistant firing pos size is: " << consistant_firing_pos.size() << endl;
  }
do{
kk = consistant_firing_pos.size();

  for(int i=0; i<jj-1; i++){
    if (i >= jj)  goto finished; 
    if ((consistant_firing_pos.at(i+1)-consistant_firing_pos.at(i))-consistant_firing_speed.at(2*i)*abs(consistant_firing_time.at(i+1)-consistant_firing_time.at(i))< 0) {//jj != kk
      if (verbos==1){
        for (int ij = 0; ij < consistant_firing_pos.size(); ij++){
          cout << "consistant_firing_pos is: " << consistant_firing_pos.at(ij)<< "  " << consistant_firing_time.at(ij) << "  " ;
          cout << consistant_firing_speed.at(2*ij) << "  " << consistant_firing_speed.at(2*ij+1)  << endl; 
        } 
      }
      vector <double> firing_pos_time_speed = firing_vecs_( &consistant_firing_pos , &consistant_firing_time, &consistant_firing_speed);
      int firing_pos_size = firing_pos_time_speed.size()/4;
      if (verbos== 1){
        cout << "number of firing times (and positions) is: " << firing_pos_size <<  endl;
      }
      consistant_firing_time.clear();
      consistant_firing_pos.clear();
      consistant_firing_speed.clear();
      for(int i1=0; i1<firing_pos_size; i1++){
        consistant_firing_pos.push_back(firing_pos_time_speed.at(i1));
        consistant_firing_time.push_back(firing_pos_time_speed.at(i1+firing_pos_size));
        consistant_firing_speed.push_back(firing_pos_time_speed.at(2*(firing_pos_size+i1)));
        consistant_firing_speed.push_back(firing_pos_time_speed.at(1+2*(firing_pos_size+i1)));
      }
      jj =consistant_firing_pos.size();
      if (verbos== 1){
        //cout << "jj and kk and i  in the loop are: " << jj << " and " << kk << " and " << i <<  endl;
      }
    }// (jj != kk )loop
  }// i loop
  //cout << "jj and kk and i  in the loop are: " << jj << " and " << kk << " and " <<  endl;
ll = consistant_firing_pos.size();
}while(kk != ll);

  finished:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (verbos==1){
    cout << "consistant number of firing times (and positions) is: " << consistant_firing_time.size() <<  endl;
  }


  if(verbos ==1){
    for(int jjj = 0; jjj < consistant_firing_pos.size(); jjj++){
      cout << "consistant firing components are: " << "(" << consistant_firing_pos.at(jjj) << " , " << consistant_firing_time.at(jjj) << ")";
      cout << "  " << endl;
    }
  }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (verbos ==1 ){
    for(int i=0; i<consistant_firing_pos.size()-1; i++){
      if (abs(consistant_firing_pos.at(i+1) - consistant_firing_pos.at(i)) - consistant_firing_speed.at(2*i) * abs(consistant_firing_time.at(i+1) - consistant_firing_time.at(i)) < 0) {
        cout << "sth is wrong about consistancy!" << endl;
      }
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  vector <vector <int> > pos_at_exp_time = progresion_function_(&consistant_firing_pos , &consistant_firing_time, &consistant_firing_speed, chr_length, EXP_TIME); 
  
  if (verbos==1){
    cout << "pos_at_exp_time size: " << pos_at_exp_time.size() << endl;
  }
  
  pos_at_exp_time_matrix.push_back(consistant_firing_time);
  pos_at_exp_time_matrix.push_back(consistant_firing_pos); 
  pos_at_exp_time_matrix.push_back(pos_at_exp_time.at(1));
  if (verbos==1){
    cout << "doing " << ah << "th line in statistical analysis" << endl;
  }
  //cout << "consistant_firing_pos.size(): " << consistant_firing_pos.size() << endl;
}   
  //cout << "pos_at_exp_time_matrix.at(0).size(): " << pos_at_exp_time_matrix.at(0).size() << endl;
  return pos_at_exp_time_matrix;          

}// end of time_matrix_derivation function


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector <double> >  replication_fun_(vector <vector <double> > *XT_vec_vec,int chr_length, int EXP_TIME){
  bool verbos = 0;
  vector<vector<int> > pos_at_exp_time_matrix = pos_at_exp_time_derivation(XT_vec_vec, chr_length, EXP_TIME);
  if (verbos == 1 ){
    for (int i1 = 0; i1 <1; i1++){
      for (int i2 = 0; i2 < pos_at_exp_time_matrix[i1].size()/2-1; i2++ ){
        cout << "-end: " << pos_at_exp_time_matrix[i1][i2*2] << "   +end: " << pos_at_exp_time_matrix[i1][i2*2+1] <<  endl;
      }
    }
  }
  vector <int> forkPos = pos_at_exp_time_matrix.at(2);
  if (verbos == 1){
    for (int g=0; g < forkPos.size(); g++){cout << forkPos.at(g) <<  "  " ;}
    cout << endl;
  }
  vector <double> forkPos_ (forkPos.begin(), forkPos.end() );
  vector <vector <double> > output;

//-----------------------------------------------------------------------------------------------------------------------------------
  output.push_back(forkPos_);
  return (output);


}
















