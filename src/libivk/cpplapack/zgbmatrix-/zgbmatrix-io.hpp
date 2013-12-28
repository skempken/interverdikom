//=============================================================================
/*! operator() for non-const object */
inline std::complex<double>& zgbmatrix::operator()(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::operator()(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j || i-j>KL || j-i>KU ){
    std::cerr << "[ERROR] zgbmatrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //return Array[KU+i+(KL+KU)*j];
  return Darray[j][KU-j+i];
}

//=============================================================================
/*! operator() for const object */
inline std::complex<double> zgbmatrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j || i-j>KL || j-i>KU ){
    std::cerr << "[ERROR] zgbmatrix::operator()(long, long)" << std::endl
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
/*! set value for const object */
inline void zgbmatrix::set(const long& i, const long& j, const std::complex<double>& v) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::set(const long&, const long&, const std::complex<double>&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j || i-j>KL || j-i>KU ){
    std::cerr << "[ERROR] zgbmatrix::set(long&, long&, std::complex<double>&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //Array[KU+i+(KL+KU)*j] =v;
  Darray[j][KU-j+i] =v;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.M; i++){
    for(long j=0; j<mat.N; j++){
      if( i-j>mat.KL || j-i>mat.KU ){ s << " x"; }
      else{ s << " " << mat(i,j); }
    }
    s << std::endl;
  }
  
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void zgbmatrix::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::write(const char*) const"
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
}

//=============================================================================
inline void zgbmatrix::read(const char* filename)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::read(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ifstream s( filename );
  if(!s){
    std::cerr << "[ERROR] zgbmatrix::read(const char*) " << std::endl
              << "The file \"" << filename << "\" can not be opened."
              << std::endl;
    exit(1);
  }

  std::string id;
  s >> id;
  if( id != "zgbmatrix" ){
    std::cerr << "[ERROR] zgbmatrix::read(const char*) " << std::endl
              << "The type name of the file \"" << filename
              << "\" is not zgbmatrix." << std::endl
              << "Its type name was " << id << " ." << std::endl;
    exit(1);
  }
  
  s >> M >> N >> KL >> KU;
  resize(M, N, KL, KU);
  for(long i=0; i<M; i++){
    for(long j=max(0,i-KL); j<min(N,i+KU+1); j++){
      s >> operator()(i,j);
    }
  }
  if(s.eof()){
    std::cerr << "[ERROR] zgbmatrix::read(const char*) " << std::endl
              << "There is something is wrong with the file \""
              << filename << " ." << std::endl
              << "Most likely, there is not enough data components, "
              << "or a linefeed code or space code is missing "
              << "at the end of the last line." << std::endl;
    exit(1);
  }
  
  s.close();
}
