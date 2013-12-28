//=============================================================================
/*! operator() for non-const object */
inline double& dsymatrix::operator()(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator()(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || N<=i || N<=j ){
    std::cerr << "[ERROR] dsymatrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  if( i >= j ) {
    //return Array[i+N*j];
    return Darray[j][i];
  } else {
    //return Array[j+N*i];
    return Darray[i][j];
  }
}

//=============================================================================
/*! operator() for const object */
inline double dsymatrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || N<=i || N<=j ){
    std::cerr << "[ERROR] dsymatrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  if( i >= j ) {
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
/*! set value for const object */
inline void dsymatrix::set(const long& i, const long& j, const double& v) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::set(const long&, const long&, const double&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || N<=i || N<=j ){
    std::cerr << "[ERROR] dsymatrix::set(long&, long&, double&) const"
              << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  if( i >= j ) {
    //Array[i+N*j] = v;
    Darray[j][i] =v;
  } else {
    //Array[j+N*i] = v;
    Darray[j][i] =v;
  }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.N; i++){
    for(long j=0; j<mat.N; j++){
      if( i >= j ) {
        s << " " << mat(i,j) << "  ";
      } else {
        s << "{" << mat(i,j) << "} ";
      }
    }
    s << std::endl;
  }
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void dsymatrix::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::write(const char*) const"
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
}

//=============================================================================
inline void dsymatrix::read(const char* filename)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::read(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ifstream s(filename);
  if(!s){
    std::cerr << "[ERROR] dsymatrix::read(const char*) " << std::endl
              << "The file \"" << filename << "\" can not be opened."
              << std::endl;
    exit(1);
  }

  std::string id;
  s >> id;
  if( id != "dsymatrix" ){
    std::cerr << "[ERROR] dsymatrix::read(const char*) " << std::endl
              << "The type name of the file \"" << filename
              << "\" is not dsymatrix." << std::endl
              << "Its type name was " << id << " ." << std::endl;
    exit(1);
  }
  
  s >> N;
  resize(N);
  for(long i=0; i<N; i++){
    for(long j=0; j<=i; j++ ){
      s >> operator()(i,j);
    }
  }
  if(s.eof()){
    std::cerr << "[ERROR] dsymatrix::read(const char*) " << std::endl
              << "There is something is wrong with the file \""
              << filename << " ." << std::endl
              << "Most likely, there is not enough data components, "
              << "or a linefeed code or space code is missing "
              << "at the end of the last line." << std::endl;
    exit(1);
  }
  
  s.close();
}
