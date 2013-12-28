//=============================================================================
/*! operator() for non-const object */
inline double& dcovector::operator()(const long& i)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::operator()(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || L<=i ){
    std::cerr << "[ERROR] dcovector::operator()(long&)"
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
inline double dcovector::operator()(const long& i) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::operator()(const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || L<=i ){
    std::cerr << "[ERROR] dcovector::operator()(long&) const"
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
inline void dcovector::set(const long& i, const double& v) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::set(const long&, const double&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || L<=i ){
    std::cerr << "[ERROR] dcovector::set(long&, double&) const"
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
inline std::ostream& operator<<(std::ostream& s, const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<vec.L; i++){
    s << " " << vec.Array[i] << std::endl;
  }
  
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void dcovector::write(const char *filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "dcovector" << " " << L << std::endl;
  for(long i=0; i<L; i++){
    s << operator()(i) << std::endl;
  }
  
  s.close();
}

//=============================================================================
inline void dcovector::read(const char *filename)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dcovector::read(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ifstream s(filename);
  if(!s){
    std::cerr << "[ERROR] dcovector::read(const char*) " << std::endl
              << "The file \"" << filename << "\" can not be opened."
              << std::endl;
    exit(1);
  }

  std::string id;
  s >> id;
  if( id != "dcovector" ){
    std::cerr << "[ERROR] dcovector::read(const char*) " << std::endl
              << "The type name of the file \"" << filename
              << "\" is not dcovector." << std::endl
              << "Its type name was " << id << " ." << std::endl;
    exit(1);
  }
  
  s >> L;
  resize(L);
  for(long i=0; i<L; i++) { s >> operator()(i); }
  if(s.eof()){
    std::cerr << "[ERROR] dcovector::read(const char*) " << std::endl
              << "There is something is wrong with the file \""
              << filename << " ." << std::endl
              << "Most likely, there is not enough data components, "
              << "or a linefeed code or space code is missing "
              << "at the end of the last line." << std::endl;
    exit(1);
  }
  
  s.close();
}
