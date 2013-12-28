//=============================================================================
/*! operator() for non-const object */
inline double& dgematrix::operator()(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator()(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dgematrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //return Array[i+M*j];
  return Darray[j][i];
}

//=============================================================================
/*! operator() for const object */
inline double dgematrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dgematrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //return Array[i+M*j];
  return Darray[j][i];
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! set value for const object */
inline void dgematrix::set(const long& i, const long& j, const double& v) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::set(const long&, const long&, const double&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] dgematrix::set(long&, long&, double&) const"
              << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //Array[i+M*j] =v;
  Darray[j][i] =v;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<mat.M; i++){
    for(long j=0; j<mat.N; j++){
      s << " " << mat(i,j);
    }
    s << std::endl;
  }
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void dgematrix::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE

  std::ofstream s(filename, std::ios::trunc);
  
  s << "dgematrix" << " " << M << " " << N << std::endl;
  for(long i=0; i<M; i++){
    for(long j=0; j<N; j++ ){
      s << operator()(i,j) << " ";
    }
    s << std::endl;
  }
  
  s.close();
}

//=============================================================================
inline void dgematrix::read(const char* filename)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::read(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ifstream s( filename );
  if(!s){
    std::cerr << "[ERROR] dgematrix::read(const char*) " << std::endl
              << "The file \"" << filename << "\" can not be opened."
              << std::endl;
    exit(1);
  }

  std::string id;
  s >> id;
  if( id != "dgematrix" ){
    std::cerr << "[ERROR] dgematrix::read(const char*) " << std::endl
              << "The type name of the file \"" << filename
              << "\" is not dgematrix." << std::endl
              << "Its type name was " << id << " ." << std::endl;
    exit(1);
  }
  
  s >> M >> N;
  resize(M, N);
  for(long i=0; i<M; i++){
    for(long j=0; j<N; j++ ){
      s >> operator()(i,j);
    }
  }
  if(s.eof()){
    std::cerr << "[ERROR] dgematrix::read(const char*) " << std::endl
              << "There is something is wrong with the file \""
              << filename << " ." << std::endl
              << "Most likely, there is not enough data components, "
              << "or a linefeed code or space code is missing "
              << "at the end of the last line." << std::endl;
    exit(1);
  }
  
  s.close();
}
