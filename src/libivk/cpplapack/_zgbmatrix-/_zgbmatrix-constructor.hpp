//============================================================================
/*! _zgbmatrix constructor */
inline _zgbmatrix::_zgbmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgbmatrix::_zgbmatrix()"
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
  std::cerr << "# [NOTE] _zgbmatrix::_zgbmatrix() "
            << "A new 0x0:0,0 matrix at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _zgbmatrix copy constructor */
inline _zgbmatrix::_zgbmatrix(const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgbmatrix::_zgbmatrix(const _zgbmatrix&)"
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
  std::cerr << "# [NOTE] _zgbmatrix::_zgbmatrix(const _zgbmatrix&) "
            << "A new matrix at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! _zgbmatrix destructor */
inline _zgbmatrix::~_zgbmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgbmatrix::~_zgbmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zgbmatrix::~_zgbmatrix() "
            << "A _zgematrix is is going to be destructed." << std::endl;
#endif//CPPL_DEBUG
  
  //////// no nothing ////////
}
