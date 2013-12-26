//============================================================================
/*! _zcovector constructor */
inline _zcovector::_zcovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zcovector::_zcovector()"
            << std::endl;
#endif//CPPL_VERBOSE

  //////// initialize ////////
  L =0;
  Array =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zcovector::_zcovector() "
            << "A new 0x0 vector at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _zcovector copy constructor */
inline _zcovector::_zcovector(const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zcovector::_zcovector(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =vec.Array;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zcovector::_zcovector(const _zcovector&) "
            << "A vector pointing to " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! _zcovector destructor */
inline _zcovector::~_zcovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zcovector::~_zcovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zcovector::~_zcovector() "
            << "A _zcovector is going to be destructed." << std::endl;
#endif//CPPL_DEBUG

  //////// do nothing ////////
}
