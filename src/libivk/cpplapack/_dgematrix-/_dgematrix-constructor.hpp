//============================================================================
/*! _dgematrix constructor without arguments */
inline _dgematrix::_dgematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dgematrix::_dgematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =0;
  N =0;
  Array =NULL;
  Darray =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dgematrix::_dgematrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _dgematrix copy constructor */
inline _dgematrix::_dgematrix(const _dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dgematrix::_dgematrix(const _dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  M =mat.M;
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dgematrix::_dgematrix(const _dgematrix&) "
            << "A matrix pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dgematrix destructor */
inline _dgematrix::~_dgematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dgematrix::~_dgematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dgematrix::~_dgematrix() "
            << "A _dgematrix is going to be destructed." << std::endl;
#endif//CPPL_DEBUG
  //////// no nothig ////////
}
