//=============================================================================
/*! operator() for object */
inline __zhecomplex _zhematrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zhematrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || N<=i || N<=j ){
    std::cerr << "[ERROR] _zhematrix::operator()(long, long) const"
              << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //if(i>=j){ return __zhecomplex( Array[i+N*j], i, j ); }
  //else { return __zhecomplex( Array[j+N*i], i, j ); }
  if(i>=j){ return __zhecomplex( Darray[j][i], i, j ); }
  else { return __zhecomplex( Darray[i][j], i, j ); }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const _zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const _zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.N; i++){
    for(long j=0; j<mat.N; j++){
      if(i>j){ s << " " << mat(i,j) << " "; }
      else if(i==j){ s << " " << std::real(mat(i,i)) << " "; }
      else{ s << "{" << std::conj(mat(j,i)) << "} "; }
    }
    s << std::endl;
    
#ifdef  CPPL_DEBUG
    if(std::fabs(std::imag(mat(i,i))) > CPPL_EPS){
      std::cerr << "[WARNING] operator<<(std::ostream&, const _zhematrix&)"
                << std::endl
                << "The " << i << "th diagonal component of the zhematrix"
                << "is not a real number." << std::endl;
    }
#endif//CPPL_DEBUG
  }
  
  mat.destroy();
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void _zhematrix::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zhematrix::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "zhematrix" << " " << N << std::endl;
  for(long i=0; i<N; i++){
    for(long j=0; j<=i; j++ ){
      s << operator()(i,j) << " ";
    }
    s << std::endl;
    
#ifdef  CPPL_DEBUG
    if(std::fabs(std::imag(operator()(i,i))) > CPPL_EPS){
      std::cerr << "[WARNING] _zhematrix::write(const char*)" << std::endl
                << "The " << i << "th diagonal component of the zhematrix"
                << "is not a real number." << std::endl;
    }
#endif//CPPL_DEBUG
  }
  
  s.close();
  destroy();
}
