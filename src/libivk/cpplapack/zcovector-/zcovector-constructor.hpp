//============================================================================
/*! zcovector constructor */
inline zcovector::zcovector()
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::zcovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =0;
  Array =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zcovector::zcovector() "
            << "A new 0x0 vector at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zcovector copy constructor */
inline zcovector::zcovector(const zcovector& vec)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::zcovector(const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =new std::complex<double>[L];
  
  //////// copy ////////
  zcopy_(L, vec.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zcovector::zcovector(const zcovector&) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zcovector constructor to cast _zcovector */
inline zcovector::zcovector(const _zcovector& vec)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::zcovector(const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =vec.Array;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zcovector::zcovector(const _zcovector&) "
            << "A new vector pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zcovector constructor with size specification */
inline zcovector::zcovector(const long& _l)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::zcovector(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _l<0 ){
    std::cerr << "[ERROR] zcovector::zcovector(const long&)" << std::endl
              << "Vector size must be positive integers. " << std::endl
              << "Your input was (" << _l << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //////// initialize ////////
  L =_l;
  Array =new std::complex<double>[L];
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zcovector::zcovector(const long&) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zcovector constructor with filename */
inline zcovector::zcovector(const char* filename)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::zcovector(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  Array =NULL;
  
  //// copy ////
  read(filename);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zcovector::zcovector(const char*) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! zcovector destructor */
inline zcovector::~zcovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zcovector::~zcovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zcovector::~zcovector "
            << "A vector at " << Array
            << " is going to be deleted." << std::endl;
#endif//CPPL_DEBUG
  
  //////// delete Array ////////
  delete [] Array;
}
