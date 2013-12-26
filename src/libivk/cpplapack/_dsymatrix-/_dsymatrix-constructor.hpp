//============================================================================
/*! _dsymatrix constructor without arguments */
inline _dsymatrix::_dsymatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dsymatrix::_dsymatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  N =0;
  Array =NULL;
  Darray =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dsymatrix::_dsymatrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _dsymatrix copy constructor */
inline _dsymatrix::_dsymatrix(const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dsymatrix::_dsymatrix(const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dsymatrix::_dsymatrix(const _dsymatrix&) "
            << "A matrix pointing at " << Array 
            << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dsymatrix destructor */
inline _dsymatrix::~_dsymatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dsymatrix::~_dsymatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dsymatrix::~_dsymatrix() "
            << "A _dsymatrix is going to be destructed." << std::endl;
#endif//CPPL_DEBUG
  
  //////// no nothig ////////
}
