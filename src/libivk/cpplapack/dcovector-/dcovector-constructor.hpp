//============================================================================
/*! dcovector constructor */
inline dcovector::dcovector()
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::dcovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =0;
  Array =NULL;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dcovector::dcovector() "
            << "A new 0x0 vector at " << Array
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dcovector copy constructor */
inline dcovector::dcovector(const dcovector& vec)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::dcovector(const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =new double[L];
  
  //////// copy ////////
  dcopy_(L, vec.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dcovector::dcovector(const dcovector&) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dcovector constructor to cast _dcovector */
inline dcovector::dcovector(const _dcovector& vec)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::dcovector(const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  //////// initialize ////////
  L =vec.L;
  Array =vec.Array;
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dcovector::dcovector(const _dcovector&) "
            << "A new vector pointing at " << Array << " has been made."
            << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dcovector constructor with size specification */
inline dcovector::dcovector(const long& _l)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::dcovector(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _l<0 ){
    std::cerr << "[ERROR] dcovector::dcovector(const long&)" << std::endl
              << "Vector size must be positive integers. " << std::endl
              << "Your input was (" << _l << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //////// initialize ////////
  L =_l;
  Array =new double[L];
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dcovector::dcovector(const long&) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

//============================================================================
/*! dcovector constructor with filename */
inline dcovector::dcovector(const char* filename)
  : l(L), array(Array)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::dcovector(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  Array =NULL;
  
  //// read ////
  read(filename);
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dcovector::dcovector(const char*) "
            << "A new vector at " << Array << " has been made." << std::endl;
#endif//CPPL_DEBUG
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//============================================================================
/*! dcovector destructor */
inline dcovector::~dcovector()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::~dcovector()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dcovector::~dcovector "
            << "A vector at " << Array
            << " is going to be deleted." << std::endl;
#endif//CPPL_DEBUG
  //////// delete Array ////////
  delete [] Array;
}
