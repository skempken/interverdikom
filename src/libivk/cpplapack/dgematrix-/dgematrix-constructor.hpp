//============================================================================
/*! dgematrix constructor without arguments */
inline dgematrix::dgematrix()
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =0;
  N =0;
  Array =NULL;
  Darray =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::dgematrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dgematrix copy constructor */
inline dgematrix::dgematrix(const dgematrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix(const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =new double[M*N];
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// copy ////////
  dcopy_(M*N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::dgematrix(const dgematrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dgematrix constructor to cast _dgematrix */
inline dgematrix::dgematrix(const _dgematrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  M =mat.M;
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::dgematrix(const _dgematrix&) "
            << "A new matrix pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dgematrix constructor to cast dgbmatrix */
inline dgematrix::dgematrix(const dgbmatrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix(const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =new double[M*N];
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// copy ////////
  zero();
  for(long i=0; i<mat.M; i++){
    for(long j=max(0,i-mat.KL); j<min(N,i+mat.KU+1); j++){
      operator()(i,j) =mat(i,j);
    }
  }
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::dgematrix(const dgbmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dgematrix constructor to cast _dgbmatrix */
inline dgematrix::dgematrix(const _dgbmatrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =new double[M*N];
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// copy ////////
  zero();
  for(long i=0; i<mat.M; i++){
    for(long j=max(0,i-mat.KL); j<min(N,i+mat.KU+1); j++){
      operator()(i,j) =mat(i,j);
    }
  }
  
  mat.destroy();
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::dgematrix(const dgbmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dgematrix constructor to cast dsymatrix */
inline dgematrix::dgematrix(const dsymatrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix(const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.N;
  N =mat.N;
  Array =new double[N*N];
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// copy ////////
  zero();
  for(long i=0; i<mat.N; i++) {
    for(long j=0; j<mat.N; j++ ) {
      operator()(i,j) =mat(i,j);
    }
  }
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::dgematrix(const dsymatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dgematrix constructor to cast _dsymatrix */
inline dgematrix::dgematrix(const _dsymatrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.N;
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  //Darray =new double*[N];
  //for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// self copy to upper right ////////
  for(long i=0; i<mat.N; i++){ for(long j=0; j<i; j++){
    operator()(j,i) =operator()(i,j);
  }}
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::dgematrix(const _dsymatrix&) "
            << "A matrix at " << Array << " has been transformed into "
            << "dgematrix." << std::endl;
#endif//CPPL_DEBUG
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dgematrix constructor to cast dssmatrix */
inline dgematrix::dgematrix(const dssmatrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix(const dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =new double[M*N];
  Darray  =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// copy ////////
  zero();
  for(long c=0; c<mat.VOL; c++) {
    operator()(mat.Indx[c],mat.Jndx[c]) =mat.Array[c];
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::dgematrix(const dssmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dgematrix constructor to cast _dssmatrix */
inline dgematrix::dgematrix(const _dssmatrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix(const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =new double[M*N];
  Darray  =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }

  //////// copy ////////
  zero();
  for(long c=0; c<mat.VOL; c++){
    operator()(mat.Indx[c],mat.Jndx[c]) =mat.Array[c];
  }
  
  mat.destroy();
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::dgematrix(const _dssmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dgematrix constructor with size specification */
inline dgematrix::dgematrix(const long& _m, const long& _n)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 ){
    std::cerr << "[ERROR] dgematrix::dgematrix(const long, const long)"
              << std::endl
              << "Matrix sizes must be positive integers. " << std::endl
              << "Your input was (" << _m << "," << _n << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //////// initialize ////////
  M =_m;
  N =_n;
  Array =new double[M*N];
  Darray  =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix(long,long) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dgematrix constructor with filename */
inline dgematrix::dgematrix(const char* filename)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgematrix(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  Array =NULL;
  Darray =NULL;
  
  //// read ////
  read(filename);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::dgematrix(const char*) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dgematrix destructor */
inline dgematrix::~dgematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::~dgematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgematrix::~dgematrix() "
            << "A matrix at " << Array << " is going to be deleted." << std::endl;
#endif//CPPL_DEBUG
  //////// delete Array ////////
  delete [] Darray;
  delete [] Array;
}
