//=============================================================================
/*! operator() for const object */
inline double& _drovector::operator()(const long& i) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _drovector::operator()(const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || L<=i ){
    std::cerr << "[ERROR] _drovector::operator()(const long&) const"
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
inline std::ostream& operator<<(std::ostream& s, const _drovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const _drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<vec.L; i++){ s << " " << vec.Array[i]; }
  s << std::endl;
  
  vec.destroy();
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void _drovector::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _drovector::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "drovector" << " " << L << std::endl;
  for(long i=0; i<L; i++){
    s << operator()(i) << " ";
  }
  s << std::endl;
  
  s.close();
  destroy();
}
