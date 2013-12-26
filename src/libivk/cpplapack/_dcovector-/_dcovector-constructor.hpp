//============================================================================
/*! _dcovector constructor */
inline _dcovector::_dcovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dcovector::_dcovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =0;
  Array =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dcovector::_dcovector() "
            << "A new 0x0 vector at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _dcovector copy constructor */
inline _dcovector::_dcovector(const _dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dcovector::_dcovector(const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =vec.Array;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dcovector::_dcovector(const _dcovector&) "
            << "A vector pointing to " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! _dcovector destructor */
inline _dcovector::~_dcovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dcovector::~_dcovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dcovector::~_dcovector() "
            << "A _dcovector is going to be destructed." << std::endl;
#endif//CPPL_DEBUG

  //////// do nothing ////////
}
