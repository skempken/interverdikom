//============================================================================
/*! zhematrix constructor without arguments */
inline zhematrix::zhematrix()
  : n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zhematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  N = 0;
  Array =NULL;
  Darray =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zhematrix::zhematrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zhematrix copy constructor */
inline zhematrix::zhematrix(const zhematrix& mat)
  : n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zhematrix(const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  N =mat.N;
  Array =new std::complex<double>[N*N];
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*N]; }
  
  //////// copy ////////
  zcopy_(N*N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zhematrix::zhematrix(const zhematrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zhematrix constructor to cast _zhematrix */
inline zhematrix::zhematrix(const _zhematrix& mat)
  : n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zhematrix(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zhematrix::zhematrix(const _zhematrix&) "
            << "A new matrix pointing at " << Array
            << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zhematrix constructor with size specification */
inline zhematrix::zhematrix(const long& _n)
  : n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zhematrix(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _n<0 ){
    std::cerr << "[ERROR] zhematrix::zhematrix(const long)"
              << std::endl
              << "Matrix sizes must be positive integers. " << std::endl
              << "Your input was (" << _n << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //////// initialize ////////
  N =_n;
  Array =new std::complex<double>[N*N];
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*N]; }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zhematrix(long) "
            << "A new matrix at " << Array 
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zhematrix constructor with filename */
inline zhematrix::zhematrix(const char* filename)
  : n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zhematrix(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  Array =NULL;
  Darray =NULL;
  
  //// read ////
  read(filename);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zhematrix::zhematrix(const char*) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! zhematrix destructor */
inline zhematrix::~zhematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::~zhematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zhematrix::~zhematrix() "
            << "A matrix at " << Array << " is going to be deleted." << std::endl;
#endif//CPPL_DEBUG
  
  //////// delete Array ////////
  delete [] Array;
  delete [] Darray;
}
