//============================================================================
/*! drovector constructor */
inline _drovector::_drovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _drovector::_drovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =0;
  Array =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] drovector::drovector() "
            << "A new 0x0 vector at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! _drovector copy constructor */
inline _drovector::_drovector(const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _drovector::_drovector(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =vec.Array;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _drovector::_drovector(const _drovector&) "
            << "A vector pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! _drovector destructor */
inline _drovector::~_drovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _drovector::~_drovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _drovector::~_drovector() "
            << "A _drovector is going to be destructed." << std::endl;
#endif//CPPL_DEBUG
  
  //////// do nothing ////////
}
