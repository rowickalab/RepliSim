


static double rand0_1(){

  static unsigned long s1 = 5318008, s2 = 11547776, s3 = 1040032;

  #define TAUS(s,a,b,c,d) (((s &c) <<d) & 0xffffffffUL) ^ ((((s <<a) & 0xffffffffUL)^s) >>b)
  s1 = TAUS(s1, 13, 19, 4294967294UL, 12);
  s2 = TAUS(s2,  2, 25, 4294967288UL, 4);
  s3 = TAUS(s3,  3, 11, 4294967280UL, 17);
  #undef TAUS
  return (s1^s2^s3)/4294967296.0;

}

