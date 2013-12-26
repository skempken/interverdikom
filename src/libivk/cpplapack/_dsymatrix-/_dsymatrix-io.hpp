//=============================================================================
/*! operator() for object */
inline double& _dsymatrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dsymatrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || N<=i || N<=j ){
    std::cerr << "[ERROR] _dsymatrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  if( i >= j ){
    //return Array[i+N*j];
    return Darray[j][i];
  } else {
    //return Array[j+N*i];
    return Darray[i][j];
  }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.N; i++){
    for(long j=0; j<mat.N; j++){
      if( i >= j ){
        s << " " << mat(i,j) << "  ";
      } else {
        s << "{" << mat(i,j) << "} ";
      }
    }
    s << std::endl;
  }
  
  mat.destroy();
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void _dsymatrix::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dsymatrix::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "dsymatrix" << " " << N << std::endl;
  for(long i=0; i<N; i++){
    for(long j=0; j<=i; j++ ){
      s << operator()(i,j) << " ";
    }
    s << std::endl;
  }
  
  s.close();
  destroy();
}
