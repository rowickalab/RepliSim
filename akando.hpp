//this code is based on the local smoothing known as akando in python for bioinformatics  
//this code can be used for a two dimensional vector (2xn_i) 



void smooth_(vector <vector <int> > *fibersFromExp , int window){
  for (int es =0; es < fibersFromExp ->size(); es++){
    int K =0;
    for (int i = 0; i < window+1; i++){
      K = K + (*fibersFromExp)[es][i];
    }
    (*fibersFromExp)[es][0] = K/(window+1);

    for (int i = 1; i < window+1; i++){
      K = K + (*fibersFromExp)[es][i+window];
      (*fibersFromExp)[es][i] = K / (i+window+1);
    }

    for (int i = window+1; i < (*fibersFromExp)[es].size()-window; i++){
      K = K + (*fibersFromExp)[es][window+i] - (*fibersFromExp)[es][i-window-1];
      (*fibersFromExp)[es][i] = K / (2*window+1);
    }

    int j =0;
    for (int i= (*fibersFromExp)[es].size() -window; i < (*fibersFromExp)[es].size(); i++ ){
      K = K - (*fibersFromExp)[es][i - window -1];
      (*fibersFromExp)[es][i] = K / (2*window - j);
      j = j+1;
    }

  }

}
