//============================================================================
/*! zgematrix constructor without arguments */
inline zgematrix::zgematrix()
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =0;
  N =0;
  Array =NULL;
  Darray =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::zgematrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zgematrix copy constructor */
inline zgematrix::zgematrix(const zgematrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix(const zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =new std::complex<double>[M*N];
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }

  //////// copy ////////
  zcopy_(M*N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::zgematrix(const zgematrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zgematrix constructor to cast _zgematrix */
inline zgematrix::zgematrix(const _zgematrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix(const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  M =mat.M;
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::zgematrix(const _zgematrix&) "
            << "A new matrix pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zgematrix constructor to cast zgbmatrix */
inline zgematrix::zgematrix(const zgbmatrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix(const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =new std::complex<double>[M*N];
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// copy ////////
  zero();
  for(long i=0; i<mat.M; i++){
    for(long j=max(0,i-mat.KL); j<min(N,i+mat.KU+1); j++){
      operator()(i,j) =mat(i,j);
    }
  }
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::zgematrix(const zgbmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zgematrix constructor to cast _zgbmatrix */
inline zgematrix::zgematrix(const _zgbmatrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix(const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =new std::complex<double>[M*N];
  Darray =new std::complex<double>*[N];
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
  std::cerr << "# [NOTE] zgematrix::zgematrix(const zgbmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zgematrix constructor to cast zhematrix */
inline zgematrix::zgematrix(const zhematrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.N;
  N =mat.N;
  Array =new std::complex<double>[N*N];
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// copy ////////
  zero();
  for(long i=0; i<mat.N; i++){
    for(long j=0; j<mat.N; j++ ){
      operator()(i,j) =mat(i,j);
    }
  }
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::zgematrix(const zhematrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zgematrix constructor to cast _zhematrix */
inline zgematrix::zgematrix(const _zhematrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.N;
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  //Darray =new std::complex<double>*[N];
  //for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// self copy to upper right ////////
  for(long i=0; i<mat.N; i++){ for(long j=0; j<i; j++){
    operator()(j,i) =std::conj(operator()(i,j));
  }}
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::zgematrix(const _zhematrix&) "
            << "A matrix at " << Array << " has been transformed into "
            << "zgematrix." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zgematrix constructor to cast zssmatrix */
inline zgematrix::zgematrix(const zssmatrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix(const zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =new std::complex<double>[M*N];
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// copy ////////
  zero();
  for(long c=0; c<mat.VOL; c++) {
    operator()(mat.Indx[c],mat.Jndx[c]) =mat.Array[c];
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::zgematrix(const zssmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zgematrix constructor to cast _zssmatrix */
inline zgematrix::zgematrix(const _zssmatrix& mat)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =new std::complex<double>[M*N];
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
  //////// copy ////////
  zero();
  for(long c=0; c<mat.VOL; c++){
    operator()(mat.Indx[c],mat.Jndx[c]) =mat.Array[c];
  }
  
  mat.destroy();
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::zgematrix(const _zssmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zgematrix constructor with size specification */
inline zgematrix::zgematrix(const long& _m, const long& _n)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 ){
    std::cerr << "[ERROR] zgematrix::zgematrix(const long, const long)"
              << std::endl
              << "Matrix sizes must be positive integers. " << std::endl
              << "Your input was (" << _m << "," << _n << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //////// initialize ////////
  M =_m;
  N =_n;
  Array =new std::complex<double>[M*N];
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*M]; }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix(long,long) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zgematrix constructor with filename */
inline zgematrix::zgematrix(const char* filename)
  : m(M), n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgematrix(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  Array =NULL;
  Darray =NULL;
  
  //// read ////
  read(filename);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::zgematrix(const char*) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! zgematrix destructor */
inline zgematrix::~zgematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::~zgematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgematrix::~zgematrix() "
            << "A matrix at " << Array << " is going to be deleted." << std::endl;
#endif//CPPL_DEBUG
  //////// delete Array ////////
  delete [] Array;
  delete [] Darray;
}
