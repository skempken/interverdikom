//============================================================================
/*! zrovector constructor */
inline _zrovector::_zrovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zrovector::_zrovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =0;
  Array =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zrovector::zrovector() "
            << "A new 0x0 vector at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _zrovector copy constructor */
inline _zrovector::_zrovector(const _zrovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zrovector::_zrovector(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =vec.Array;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zrovector::_zrovector(const _zrovector&) "
            << "A vector pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! _zrovector destructor */
inline _zrovector::~_zrovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zrovector::~_zrovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zrovector::~_zrovector() "
            << "A _zrovector is going to be destructed." << std::endl;
#endif//CPPL_DEBUG
  //////// do nothing ////////
}
