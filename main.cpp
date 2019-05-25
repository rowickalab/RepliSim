/// this code optimizes the DNA replication simulation
using namespace std;


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <valarray>
#include<cstdlib>
#include<ctime>
#include <algorithm>    // std::sort
#include <numeric>
#include <omp.h>
#include <stdio.h>
//=====================
#include "linear_func.hpp"         ///****************
#include "DNA_replication_simulation_fork_position.hpp"
#include "rand_0__1.hpp"
#include "origin_time_vel.hpp"
#include "parameters.hpp"
#include "histogram.hpp"
#include "akando.hpp"            ///**************
#include "Experimental_genome_origins.hpp"
#include "Experimental_t_half.hpp"
#include "normalized_p_from_KStest.hpp"
#include "fibers_from_exp.hpp"
#include "competence_from_time_course_efficiency.hpp"
//=====================
#define N 10000   // number of itterations (cell population)
#define N_gen_alg  1  //number of itterations for genetic algorithm
#define window  1
//===========================
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

int main(){

 ofstream outputParams ("outputParameters.txt");   // this is the potput file for desired values!

  bool verbos = 0;
//========================
  vector < vector <int> > genome_orig = Exp_genome_Oris_();
  cout << "genime origin size: " << genome_orig.size() << endl;
  vector <vector <double> > genome_firing_time = Exp_t_half_();
  vector <vector < double > > XT_vec;
  vector <int> temp_fibs;
  vector <double> all_pos_;
  vector <double > alltimes;
  double percentage_rep_genome;


  if (verbos == 1){
    cout << "genome_firing_time size: " << genome_firing_time.size() << "  and Oris are: " << endl;
    for (int k =0; k < genome_firing_time.size(); k++){
      for (int l =0; l < genome_firing_time.at(k).size(); l++){
        cout << "  " << genome_firing_time[k][l] ;
      }
      cout << endl;
    }
  } 

  vector<int > fibersFromExp = fibersFromExperiment_(); // unit for this data set is:" hundred*base-pairs". for instance if it is 51, it means that it is 51*100 base-pairs.
  sort(fibersFromExp.begin() , fibersFromExp.end() );
  if (verbos == 1){
    for (int i = 0; i< fibersFromExp.size(); i++){
      cout << "fibersFromExp[0][" << i << "]: " << fibersFromExp.at(i) << "  " ;
    }
    cout << "~~~~~~~~~~~~~" << endl;
  }
  int max_fiber_len_exp = fibersFromExp.at(fibersFromExp.size()-1);
  int num_val_exp = fibersFromExp.size();  //this is the total number of fibers from experiment

//============================================================================
  Parameters params;
  vector <int> chr_lengths = params.chromosome_len_(); vector <int> *ptr_chr_lengths; ptr_chr_lengths = &chr_lengths;
  vector < int > exp_ts = params.exp_t_();   vector <int> *ptr_exp_ts;  ptr_exp_ts = &exp_ts; 
  //vector <int> mean_firing_time = params.mean_t_late_();    vector <int> *ptr_mean_firing_time;   ptr_mean_firing_time = &mean_firing_time;
  vector <int> time_sd = params.stand_devi_t_late_();    vector <int> *ptr_time_sd; ptr_time_sd = &time_sd;
  vector < double > vels = params.velocity_();   vector <double> *ptr_vels;  ptr_vels = &vels;
  vector <double> v_sd = params.v_sd_(); vector <double> *ptr_v_sd; ptr_v_sd = &v_sd;
//=============================================================================
  int genome_size = std::accumulate(chr_lengths.begin(), chr_lengths.end(), 0);
  int vel;
  double v; 
  int t_sd;
  int EXP_TIME;
  double vel_sd;
  int t_end;  
  int temp_var;
  int num_val;
  const string chr_id[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI"};
  long int allrepdist =0;
  double genomePercent;
  int genomeRep;
  int genomeincomp;
  double chrPercent;
  int chrRep;
  int chrincomp;
  int total_n_oris = 0;
  int replicated_oris = 0;
  double diff_p = 0;
  double aa =1;
//===============================================================================
// this part is doing loops over parameters for optimization
  for (int n_ga = 0; n_ga < N_gen_alg; n_ga++ ){
//~~~~~~~~~~~~~~
    vector <vector <double> > allforkPos;
//~~~~~~~~~~~~~~
    vector<vector<int> > ef(16, vector<int>());
    for (int jj =0; jj < ef.size(); jj++){
      for (int ji =0; ji < genome_orig.at(jj).size(); ji++  ){
        ef.at(jj).push_back(0);
      }
    }
//~~~~~~~~~~~~~~
    total_n_oris = 0;
    replicated_oris = 0;
    double aa =1;
    allrepdist =0;
    total_n_oris = 0;
    replicated_oris = 0;
    aa =1;
    //cout << n_ga << "th in gen alg." << endl;
//~~~~~~~~~~~~~~~
    t_sd = ptr_time_sd->at((rand0_1() * (int)(ptr_time_sd->size() )) )+ ( rand0_1() * (int)(60));   //time in seconds
    EXP_TIME = ptr_exp_ts->at( (rand0_1() * (int)(ptr_exp_ts->size() )) )*60 + ( rand0_1() * (int)(60));   //to give time in seconds
    v = ptr_vels->at((rand0_1() * (int)(ptr_vels->size() )) ) +rand0_1();
    vel_sd = ptr_v_sd->at( (rand0_1() * (int)(ptr_v_sd->size() )) )+rand0_1();
//~~~~~~~~~~~~~~~
    genomePercent = 0;    
    genomeRep =0;
    genomeincomp = 0;
    int numActiveOris =0;
    for (int j =0; j < N; j++){ // number of itterations (cell population)
      chrPercent = 0;
      chrRep = 0;
      chrincomp = 0;
      for(int i = 0; i < genome_orig.size(); i++){                   //loop over chromosoms
        total_n_oris = total_n_oris + genome_orig.at(i).size();
        //cout << j+1 << "th itteration" << endl;
        vector <double> XVT;
        vector <int> chromosome;
        vector <double> compet;
        vector <double> genomeFiringTime = genome_firing_time.at(i);
        chromosome = genome_orig.at(i);
        if (verbos == 1){
          cout << "genomeFiringTime: " ;
          for (int k =0; k < genomeFiringTime.size(); k++){
            cout << genomeFiringTime.at(k) << "  ";
          }
          cout << endl;
        }
        XVT = xtv_assigner_(&chromosome, &genomeFiringTime,t_sd, v, vel_sd, EXP_TIME); // this function assigns parameters to origins of replication for each chromosome! 
        //cout << "XVT size: " << XVT.size() << endl;
        if (XVT.size()>0){
          XT_vec.push_back(XVT);
          if (verbos == 0){
            for (int hj=0; hj< 1; hj++ ) { //XT_vec[0].size(); hj++ ){
              if (XT_vec[0][hj] <0 ){
                cout << "XT_vec["<< 0 << "][" << hj<<"] is " << XT_vec[0][hj] << " at " << i << "th chr."<< endl;
              }
            }
          }
        }
        XVT.clear();
        if (verbos == 1){
          cout << i+1 <<"th chromosome " << endl;
        }
        vector <double> fibs;
        vector <vector <double> > replic;
        vector <double> tempForkPos;
        if (XT_vec.size() > 0){
          // assigned parameters go through DNA_Relication function to give the fork position at time = EXP_TIME.
          replic = replication_fun_(&XT_vec, ptr_chr_lengths->at(i), EXP_TIME ); //cout << fibs.size() << endl;
          //all_pos_.insert(all_pos_.end(), replic.at(1).begin(), replic.at(1).end());//all_pos.push_back(replic.at(1));
          tempForkPos = replic.at(0);
          //std::sort (tempForkPos.begin(), tempForkPos.end());
        }
 
        XT_vec.clear();
        //cout<< "rep_percntg.size: " << rep_percntg.size() << endl; 
        if (tempForkPos.size() > 0){

          vector <double> tempForkPosall;
          for (int v1 =0; v1 < tempForkPos.size()/2; v1++){//cout << "tempforkpos length: " << tempForkPos.at(2*v1+1)-tempForkPos.at(2*v1) << "  ";
            int aq = tempForkPos.at(2*v1+1)-tempForkPos.at(2*v1);
            allrepdist = allrepdist + aq;
            all_pos_.push_back(aq);
            int interv = aq/window;
            int br =0;
            for (int v2 =0; v2 <interv +1; v2++ ){
              tempForkPosall.push_back(tempForkPos.at(2*v1) + br* window);
              br++;
            }       
          }
        }
      }//loop over i, number of chromosomes
      chrPercent = chrPercent;
      genomePercent = genomePercent + chrPercent;
      genomeRep = genomeRep +  chrRep /16;
      genomeincomp = genomeincomp + chrincomp/16;
    }//sum over j: number of itterations
    for (int t1 =0; t1 < ef.size(); t1++){
      //cout << "ef: "<< "  ";
      for (int s1 =0; s1 < ef.at(t1).size(); s1++){
        if (ef[t1][s1] > N/100){
          //cout << ef[t1][s1] << "  ";
          numActiveOris = numActiveOris +1;
        }
      }
      //cout << endl;
    }
    cout << "total_n_oris:  " << total_n_oris/N << endl;
    cout << "replicated_oris:  " << replicated_oris/N <<  endl;
    cout << "genomePercent: " << (double)allrepdist/N/genome_size << endl;
    cout << "genomeRep: " << genomeRep << endl;
    cout << "genomeincomp: " << genomeincomp << endl;
    cout << "numActiveOris: " << numActiveOris << endl;    //total number of active origins 
//=============================================
    vector<int> all_pos(all_pos_.begin(), all_pos_.end());
    std::sort (all_pos.begin(), all_pos.end());
    all_pos_.clear(); 
    int max_val =  max(all_pos.at(all_pos.size()-1) , fibersFromExp.at(fibersFromExp.size()-1) );
    Histogram hist_sim ( all_pos.size(), max_val , &all_pos); // num_val is the total number of data to be binned; max_val is the maximum value of data;
    vector <double> sim_fibs = hist_sim.binningFunc();
    vector<double> *ptr_sim_fibs;  ptr_sim_fibs = &sim_fibs;
//~~~~~~~~~~~~~~~~~~~
    Histogram hist_exp (num_val_exp, max_val , &fibersFromExp);
    vector <double> exp_fibs = hist_exp.binningFunc();
    vector <double> *ptr_exp_fibs; ptr_exp_fibs = &exp_fibs;
//~~~~~~~~~~~~~~~~~~~
    if (verbos ==1){
      for (int cv =0; cv < all_pos.size(); cv++){
        cout << all_pos.at(cv) << "   ";
      }
    }
    num_val = all_pos.size();   // num_val is the total number of data to be binned; max_val is the maximum value of data;
    double sqrdiff =0;
    for (int rs = 0; rs < ptr_exp_fibs->size(); rs++){
      sqrdiff = pow(abs((ptr_sim_fibs->at(rs) - ptr_exp_fibs->at(rs))) , 2) + sqrdiff;
    }
    sqrdiff = sqrt(sqrdiff);
//=============================================
    int num_val = all_pos.size();
    int n1 = all_pos.size(); //cout << "n1: " << n1 << endl;
    outputParams << t_sd/(double)(60) << "  " <<  EXP_TIME/(double)(60) << "  " << v << "  " << vel_sd <<  "  "  << numActiveOris << "  " <<replicated_oris/N  << "  "  << sqrdiff << endl; 
    alltimes.clear();
    all_pos.clear();
    allrepdist =0;
  } //loop over N_gen_alg
//====================================

  return 0;
}














