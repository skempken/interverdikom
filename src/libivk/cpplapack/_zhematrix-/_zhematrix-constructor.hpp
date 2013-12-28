//============================================================================
/*! _zhematrix constructor without arguments */
inline _zhematrix::_zhematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zhematrix::_zhematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  N =0;
  Array =NULL;
  Darray =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zhematrix::_zhematrix() "
            << "A new 0x0 matrix at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _zhematrix copy constructor */
inline _zhematrix::_zhematrix(const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zhematrix::_zhematrix(const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  N =mat.N;
  Array =mat.Array;
  Darray =mat.Darray;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zhematrix::_zhematrix(const _zhematrix&) "
            << "A matrix pointing at " << Array 
            << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! zhematrix destructor */
inline _zhematrix::~_zhematrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zhematrix::~_zhematrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zhematrix::~_zhematrix() "
            << "A _zhematrix is going to be destructed." << std::endl;
#endif//CPPL_DEBUG
  
  //////// no nothig ////////
}
