//=============================================================================
/*! operator() for non-const object */
inline __zhecomplex zhematrix::operator()(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::operator()(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || N<=i || N<=j ){
    std::cerr << "[ERROR] zhematrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //if(i>=j){ return __zhecomplex( Array[i+N*j], i, j ); }
  //else{ return __zhecomplex( Array[j+N*i], i, j ); }
  if(i>=j){ return __zhecomplex( Darray[j][i], i, j ); }
  else{ return __zhecomplex( Darray[i][j], i, j ); }
}

//=============================================================================
/*! operator() for const object */
inline std::complex<double> zhematrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || N<=i || N<=j ){
    std::cerr << "[ERROR] zhematrix::operator()(long, long) const" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //if(i>=j){ return Array[i+N*j]; }
  //else{ return std::conj(Array[j+N*i]); }
  if(i>=j){ return Darray[j][i]; }
  else{ return std::conj(Darray[i][j]); }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! set value for const object */
inline void zhematrix::set(const long& i, const long& j, 
                           const std::complex<double>& v) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::set(const long&, const long&, const std::complex<double>&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || N<=i || N<=j ){
    std::cerr << "[ERROR] zhematrix::set"
              << "(long&, long&, std::complex<double>&) const" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //if(i>=j){ Array[i+N*j] = v; }
  //else{ Array[j+N*i] = std::conj(v); }
  if(i>=j){ Darray[j][i] = v; }
  else{ Darray[i][j] = std::conj(v); }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const zhematrix&)"
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
      std::cerr << "[WARNING] operator<<(std::ostream&, const zhematrix&)"
                << std::endl
                << "The " << i << "th diagonal component of the zhematrix"
                << "is not a real number." << std::endl;
    }
#endif//CPPL_DEBUG
  }
  
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void zhematrix::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::write(const char*) const"
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
      std::cerr << "[WARNING] zhematrix::write(const char*)" << std::endl
                << "The " << i << "th diagonal component of the zhematrix"
                << "is not a real number." << std::endl;
    }
#endif//CPPL_DEBUG
  }
  
  s.close();
}

//=============================================================================
inline void zhematrix::read(const char* filename)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::read(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ifstream s(filename);
  if(!s){
    std::cerr << "[ERROR] zhematrix::read(const char*) " << std::endl
              << "The file \"" << filename << "\" can not be opened."
              << std::endl;
    exit(1);
  }

  std::string id;
  s >> id;
  if( id != "zhematrix" ){
    std::cerr << "[ERROR] zhematrix::read(const char*) " << std::endl
              << "The type name of the file \"" << filename
              << "\" is not zhematrix." << std::endl
              << "Its type name was " << id << " ." << std::endl;
    exit(1);
  }
  
  s >> N;
  resize(N);
  for(long i=0; i<N; i++){
    for(long j=0; j<=i; j++ ){
      s >> Darray[j][i];
      //s >> operator()(i,j); //NG
    }
  }
  if(s.eof()){
    std::cerr << "[ERROR] zhematrix::read(const char*) " << std::endl
              << "There is something is wrong with the file \""
              << filename << " ." << std::endl
              << "Most likely, there is not enough data components, "
              << "or a linefeed code or space code is missing "
              << "at the end of the last line." << std::endl;
    exit(1);
  }
  
  s.close();
}
