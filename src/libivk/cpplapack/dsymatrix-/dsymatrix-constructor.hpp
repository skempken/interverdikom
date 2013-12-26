//============================================================================
/*! dsymatrix constructor without arguments */
inline dsymatrix::dsymatrix()
  : n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsymatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  N = 0;
  Array =NULL;
  Darray =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dsymatrix::dsymatrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dsymatrix copy constructor */
inline dsymatrix::dsymatrix(const dsymatrix& mat)
  : n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsymatrix(const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  N =mat.N;
  Array =new double[N*N];
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*N]; }
  
  //////// copy ////////
  dcopy_(N*N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dsymatrix::dsymatrix(const dsymatrix&) "
            << "A new matrix at " << Array 
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dsymatrix constructor to cast _dsymatrix */
inline dsymatrix::dsymatrix(const _dsymatrix& mat)
  : n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsymatrix(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dsymatrix::dsymatrix(const _dsymatrix&) "
            << "A new matrix pointing at " << Array
            << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dsymatrix constructor with size specification */
inline dsymatrix::dsymatrix(const long& _n)
  : n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsymatrix(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _n<0 ){
    std::cerr << "[ERROR] dsymatrix::dsymatrix(const long)"
              << std::endl
              << "Matrix sizes must be positive integers. " << std::endl
              << "Your input was (" << _n << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //////// initialize ////////
  N =_n;
  Array =new double[N*N];
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*N]; }

#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dsymatrix(long) "
            << "A new matrix at " << Array 
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dsymatrix constructor with filename */
inline dsymatrix::dsymatrix(const char* filename)
  : n(N), array(Array), darray(Darray)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsymatrix(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  Array =NULL;
  Darray =NULL;
  
  //// copy ////
  read(filename);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dsymatrix::dsymatrix(const char*) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dsymatrix destructor */
inline dsymatrix::~dsymatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::~dsymatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dsymatrix::~dsymatrix() "
            << "A matrix at " << Array << " is going to be deleted." << std::endl;
#endif//CPPL_DEBUG
  //////// delete Array ////////
  delete [] Array;
  delete [] Darray;
}
