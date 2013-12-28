//=============================================================================
/*! operator() for const object */
inline std::complex<double>& _zgbmatrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgbmatrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j || i-j>KL || j-i>KU ){
    std::cerr << "[ERROR] _zgbmatrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //return Array[KU+i+(KL+KU)*j];
  return Darray[j][KU-j+i];
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.M; i++){
    for(long j=0; j<mat.N; j++){
      if( i-j>mat.KL || j-i>mat.KU ){ s << " x"; }
      else{ s << " " << mat(i,j); }
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
inline void _zgbmatrix::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgbmatrix::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "zgbmatrix" << " "
    << M << " " << N << " " << KL << " " << KU << std::endl;
  for(long i=0; i<M; i++){
    for(long j=max(0,i-KL); j<min(N,i+KU+1); j++){
      s << operator()(i,j) << " ";
    }
    s << std::endl;
  }
  
  s.close();
  destroy();
}
