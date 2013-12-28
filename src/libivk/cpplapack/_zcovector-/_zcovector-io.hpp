//=============================================================================
/*! operator() for const object */
inline std::complex<double>& _zcovector::operator()(const long& i) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zcovector::operator()(const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || L<=i ){
    std::cerr << "[ERROR] _zcovector::operator()(const long&) const"
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
inline std::ostream& operator<<(std::ostream& s, const _zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const _zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<vec.L; i++){
    s << " " << vec.Array[i] << std::endl;
  }
  
  vec.destroy();
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void _zcovector::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zcovector::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "zcovector" << " " << L << std::endl;
  for(long i=0; i<L; i++){
    s << operator()(i) << std::endl;
  }
  
  s.close();
  destroy();
}
