//=============================================================================
/*! operator() for non-const object */
inline double& drovector::operator()(const long& i)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::operator()(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || L<=i ){
    std::cerr << "[ERROR] drovector::operator()(const long&)"
              << std::endl
              << "The required component is out of the vector size."
              << std::endl
              << "Your input was (" << i << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  return Array[i];
}

//=============================================================================
/*! operator() for const object */
inline double drovector::operator()(const long& i) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::operator()(const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || L<=i ){
    std::cerr << "[ERROR] drovector::operator()(const long&) const"
              << std::endl
              << "The required component is out of the vector size."
              << std::endl
              << "Your input was (" << i << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  return Array[i];
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! set value for const object */
inline void drovector::set(const long& i, const double& v) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::set(const long&, const double&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || L<=i ){
    std::cerr << "[ERROR] drovector::set(const long&, const double&) const"
              << std::endl
              << "The required component is out of the vector size."
              << std::endl
              << "Your input was (" << i << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  Array[i] =v;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<vec.L; i++){ s << " " << vec.Array[i]; }
  s << std::endl;
  
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void drovector::write(const char *filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "drovector" << " " << L << std::endl;
  for(long i=0; i<L; i++){
    s << operator()(i) << " ";
  }
  s << std::endl;
  
  s.close();
}

//=============================================================================
inline void drovector::read(const char *filename)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] drovector::read(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ifstream s( filename );
  if(!s){
    std::cerr << "[ERROR] drovector::read(const char*) " << std::endl
              << "The file \"" << filename << "\" can not be opened."
              << std::endl;
    exit(1);
  }

  std::string id;
  s >> id;
  if( id != "drovector" ){
    std::cerr << "[ERROR] drovector::read(const char*) " << std::endl
              << "The type name of the file \"" << filename
              << "\" is not drovector." << std::endl
              << "Its type name was " << id << " ." << std::endl;
    exit(1);
  }
  
  s >> L;
  resize(L);
  for(long i=0; i<L; i++) { s >> operator()(i); }
  if(s.eof()){
    std::cerr << "[ERROR] drovector::read(const char*) " << std::endl
              << "There is something is wrong with the file \""
              << filename << " ." << std::endl
              << "Most likely, there is not enough data components, "
              << "or a linefeed code or space code is missing "
              << "at the end of the last line." << std::endl;
    exit(1);
  }
  
  s.close();
}
