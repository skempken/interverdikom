//============================================================================
/*! _zgematrix constructor without arguments */
inline _zgematrix::_zgematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgematrix::_zgematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =0;
  N =0;
  Array =NULL;
  Darray =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zgematrix::_zgematrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _zgematrix copy constructor */
inline _zgematrix::_zgematrix(const _zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgematrix::_zgematrix(const _zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zgematrix::_zgematrix(const _zgematrix&) "
            << "A matrix pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! zgematrix destructor */
inline _zgematrix::~_zgematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgematrix::~_zgematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zgematrix::~_zgematrix() "
            << "A _zgematrix is going to be destructed." << std::endl;
#endif//CPPL_DEBUG
  
  //////// no nothig ////////
}
