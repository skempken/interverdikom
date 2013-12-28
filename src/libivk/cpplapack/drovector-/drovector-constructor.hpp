//============================================================================
/*! drovector constructor */
inline drovector::drovector()
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::drovector()"
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
/*! drovector copy constructor */
inline drovector::drovector(const drovector& vec)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::drovector(const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =new double[L];
  
  //////// copy ////////
  dcopy_(L, vec.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] drovector::drovector(const drovector&) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! drovector constructor to cast _drovector */
inline drovector::drovector(const _drovector& vec)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::drovector(const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =vec.Array;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] drovector::drovector(const _drovector&) "
            << "A new vector pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! drovector constructor with size specification */
inline drovector::drovector(const long& _l)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::drovector(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _l<0 ){
    std::cerr << "[ERROR] drovector::drovector(const long&)" << std::endl
              << "Vector size must be positive integers. " << std::endl
              << "Your input was (" << _l << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //////// initialize ////////
  L =_l;
  Array =new double[L];
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] drovector::drovector(const long&) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! drovector constructor with filename */
inline drovector::drovector(const char* filename)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::drovector(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  Array =NULL;
  
  //// read ////
  read(filename);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] drovector::drovector(const char*) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! drovector destructor */
inline drovector::~drovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::~drovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] drovector::~drovector "
            << "A vector at " << Array
            << " is going to be deleted." << std::endl;
#endif//CPPL_DEBUG
  //////// delete Array ////////
  delete [] Array;
}
