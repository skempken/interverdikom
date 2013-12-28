//============================================================================
/*! dssmatrix constructor without arguments */
inline dssmatrix::dssmatrix()
  : m(M), n(N), cap(CAP), vol(VOL), array(Array), indx(Indx), jndx(Jndx)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::dssmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =N =0;
  CAP =VOL =0;
  Array =NULL;
  Indx =Jndx =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dssmatrix::dssmatrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dssmatrix copy constructor */
inline dssmatrix::dssmatrix(const dssmatrix& mat)
  : m(M), n(N), cap(CAP), vol(VOL), array(Array), indx(Indx), jndx(Jndx)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::dssmatrix(const dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M; N =mat.N;
  CAP =mat.CAP;
  VOL =mat.VOL;
  Array =new double[CAP];
  Indx =new long[CAP];
  Jndx =new long[CAP];
  
  //////// copy ////////
  dcopy_(VOL, mat.Array, 1, Array, 1);
  for(long i=0; i<VOL; i++){
    Indx[i] =mat.Indx[i];
    Jndx[i] =mat.Jndx[i];
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dssmatrix::dssmatrix(const dssmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dssmatrix constructor to cast _dssmatrix */
inline dssmatrix::dssmatrix(const _dssmatrix& mat)
  : m(M), n(N), cap(CAP), vol(VOL), array(Array), indx(Indx), jndx(Jndx)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::dssmatrix(const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  M =mat.M; N =mat.N;
  CAP =mat.CAP;
  VOL =mat.VOL;
  Array =mat.Array;
  Indx =mat.Indx;
  Jndx =mat.Jndx;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dssmatrix::dssmatrix(const _dssmatrix&) "
            << "A new matrix pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dssmatrix constructor with size specification */
inline dssmatrix::dssmatrix(const long& _m, const long& _n, const long& _c)
  : m(M), n(N), cap(CAP), vol(VOL), array(Array), indx(Indx), jndx(Jndx)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::dssmatrix(const long&, const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 || _c<0 ){
    std::cerr << "[ERROR] dssmatrix::dssmatrix"
              << "(const long&, const long&, const long&)" << std::endl
              << "Matrix sizes and the length of arrays "
              << "must be positive integers. " << std::endl
              << "Your input was (" << _m << "," << _n << "," << _c << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //////// initialize ////////
  M =_m; N =_n;
  CAP =_c;
  VOL =0;
  Array =new double[CAP];
  Indx =new long[CAP];
  Jndx =new long[CAP];
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dssmatrix(const long&, const long&, const long&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dssmatrix constructor with filename */
inline dssmatrix::dssmatrix(const char* filename)
  : m(M), n(N), cap(CAP), vol(VOL), array(Array), indx(Indx), jndx(Jndx)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::dssmatrix(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  Array =NULL;
  
  //// read ////
  read(filename);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dssmatrix::dssmatrix(const char*) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dssmatrix destructor */
inline dssmatrix::~dssmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::~dssmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dssmatrix::~dssmatrix() "
            << "A matrix at " << Array << " is going to be deleted."
            << std::endl;
#endif//CPPL_DEBUG
  
  //////// delete Array ////////
  delete [] Array;
  delete [] Indx;
  delete [] Jndx;
}
