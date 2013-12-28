//============================================================================
/*! _dssmatrix constructor without arguments */
inline _dssmatrix::_dssmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dssmatrix::_dssmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =N =0;
  CAP =VOL =0;
  Array =NULL;
  Indx =Jndx =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dssmatrix::_dssmatrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _dssmatrix copy constructor */
inline _dssmatrix::_dssmatrix(const _dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dssmatrix::_dssmatrix(const _dssmatrix&)"
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
  std::cerr << "# [NOTE] _dssmatrix::_dssmatrix(const _dssmatrix&) "
            << "A matrix pointing at " << Array << " has been made.";
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! _dssmatrix destructor */
inline _dssmatrix::~_dssmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dssmatrix::~_dssmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dssmatrix::~_dssmatrix() "
            << "A _dssmatrix is going to be destructed." << std::endl;
#endif//CPPL_DEBUG
  
  //////// do nothing ////////
}
