//============================================================================
/*! zrovector constructor */
inline zrovector::zrovector()
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::zrovector()"
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
/*! zrovector copy constructor */
inline zrovector::zrovector(const zrovector& vec)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::zrovector(const zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =new std::complex<double>[L];
  
  //////// copy ////////
  zcopy_(L, vec.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zrovector::zrovector(const zrovector&) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zrovector constructor to cast _zrovector */
inline zrovector::zrovector(const _zrovector& vec)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::zrovector(const _zrovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =vec.Array;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zrovector::zrovector(const _zrovector&) "
            << "A new vector pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zrovector constructor with size specification */
inline zrovector::zrovector(const long& _l)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::zrovector(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _l<0 ){
    std::cerr << "[ERROR] zrovector::zrovector(const long&)" << std::endl
              << "Vector size must be positive integers. " << std::endl
              << "Your input was (" << _l << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //////// initialize ////////
  L =_l;
  Array =new std::complex<double>[L];
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zrovector::zrovector(const long&) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! zrovector constructor with filename */
inline zrovector::zrovector(const char* filename)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::zrovector(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  Array =NULL;
  
  //// read ////
  read(filename);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zrovector::zrovector(const char*) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! zrovector destructor */
inline zrovector::~zrovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::~zrovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zrovector::~zrovector "
            << "A vector at " << Array
            << " is going to be deleted." << std::endl;
#endif//CPPL_DEBUG
  
  //////// delete Array ////////
  delete [] Array;
}
