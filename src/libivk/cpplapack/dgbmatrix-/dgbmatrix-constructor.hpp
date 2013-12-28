//============================================================================
/*! dgbmatrix constructor */
inline dgbmatrix::dgbmatrix()
  : m(M), n(N), kl(KL), ku(KU), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::dgbmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =0;
  N =0;
  KL=0;
  KU=0;
  Array =NULL;
  Darray =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgbmatrix::dgbmatrix() "
            << "A new 0x0:0,0 matrix at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dgbmatrix copy constructor */
inline dgbmatrix::dgbmatrix(const dgbmatrix& mat)
  : m(M), n(N), kl(KL), ku(KU), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::dgbmatrix(const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  KL=mat.KL;
  KU=mat.KU;
  Array =new double[(KL+KU+1)*N];
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*(KL+KU+1)]; }
  
  //////// copy ////////
  dcopy_((KL+KU+1)*N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgbmatrix::dgbmatrix(const dgbmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dgbmatrix constructor to cast _dgbmatrix */
inline dgbmatrix::dgbmatrix(const _dgbmatrix& mat)
  : m(M), n(N), kl(KL), ku(KU), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::dgbmatrix(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  M =mat.M;
  N =mat.N;
  KL =mat.KL;
  KU =mat.KU;
  Array =mat.Array;
  Darray =mat.Darray;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgbmatrix::dgbmatrix(const dgbmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dgbmatrix constructor with size specification */
inline dgbmatrix::dgbmatrix(const long& _m, const long& _n,
                            const long& _kl, const long& _ku)
  : m(M), n(N), kl(KL), ku(KU), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::dgbmatrix(const long&, const long&, const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 || _kl<0 || _ku<0 || _m<_kl || _n<_ku ){
    std::cerr << "[ERROR] dgbmatrix::dgbmatrix"
              << "(const long, const long, const long const long)"
              << std::endl
              << "It is impossible to make a matrix you ordered. "
              << std::endl
              << "Your input was ("
              << _m << "," << _n << ","<< _ku << "," << _kl << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //////// initialize ////////
  M =_m;
  N =_n;
  KL =_kl;
  KU =_ku;
  Array =new double[(KL+KU+1)*N];
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*(KL+KU+1)]; }

#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgbmatrix::dgbmatrix"
            << "(const long&, const long&, const long&,const long&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dgbmatrix constructor with filename */
inline dgbmatrix::dgbmatrix(const char* filename)
  : m(M), n(N), kl(KL), ku(KU), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::dgbmatrix(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  Array =NULL;
  Darray =NULL;
  
  //// read ////
  read(filename);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgbmatrix::dgbmatrix(const char*) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dgbmatrix destructor */
inline dgbmatrix::~dgbmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::~dgbmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgbmatrix::~dgbmatrix() "
            << "A matrix at " << Array
            << " is going to be deleted." << std::endl;
#endif//CPPL_DEBUG

  //////// delete Array ////////
  delete [] Array;
  delete [] Darray;
}
