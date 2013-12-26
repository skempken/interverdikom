//============================================================================
/*! _dgbmatrix constructor */
inline _dgbmatrix::_dgbmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dgbmatrix::_dgbmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =0;
  N =0;
  KL =0;
  KU =0;
  Array =NULL;
  Darray =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dgbmatrix::_dgbmatrix() "
            << "A new 0x0:0,0 matrix at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _dgbmatrix copy constructor */
inline _dgbmatrix::_dgbmatrix(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dgbmatrix::_dgbmatrix(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  KL =mat.KL;
  KU =mat.KU;
  Array =mat.Array;
  Darray =mat.Darray;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dgbmatrix::_dgbmatrix(const _dgbmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! _dgbmatrix destructor */
inline _dgbmatrix::~_dgbmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dgbmatrix::~_dgbmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dgbmatrix::~_dgbmatrix() "
            << "A _dgematrix is is going to be destructed." << std::endl;
#endif//CPPL_DEBUG
  
  //////// no nothing ////////
}
