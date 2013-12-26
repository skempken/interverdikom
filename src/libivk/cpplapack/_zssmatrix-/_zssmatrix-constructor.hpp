//============================================================================
/*! _zssmatrix constructor without arguments */
inline _zssmatrix::_zssmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zssmatrix::_zssmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =N =0;
  CAP =VOL =0;
  Array =NULL;
  Indx =Jndx =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zssmatrix::_zssmatrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _zssmatrix copy constructor */
inline _zssmatrix::_zssmatrix(const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zssmatrix::_zssmatrix(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M; N =mat.N;
  CAP =mat.CAP;
  VOL =mat.VOL;
  Array =mat.Array;
  Indx =mat.Indx;
  Jndx =mat.Jndx;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zssmatrix::_zssmatrix(const _zssmatrix&) "
            << "A matrix pointing at " << Array << " has been made.";
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! _zssmatrix destructor */
inline _zssmatrix::~_zssmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zssmatrix::~_zssmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zssmatrix::~_zssmatrix() "
            << "A _zssmatrix is going to be destructed." << std::endl;
#endif//CPPL_DEBUG
  
  //////// do nothing ////////
}
