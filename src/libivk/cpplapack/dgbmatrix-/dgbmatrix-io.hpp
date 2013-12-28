//=============================================================================
/*! operator() for non-const object */
inline double& dgbmatrix::operator()(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::operator()(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j || i-j>KL || j-i>KU ){
    std::cerr << "[ERROR] dgbmatrix::operator()(long, long)" << std::endl
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
inline double dgbmatrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j || i-j>KL || j-i>KU ){
    std::cerr << "[ERROR] dgbmatrix::operator()(long, long)" << std::endl
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
inline void dgbmatrix::set(const long& i, const long& j, const double& v) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::set(const long&, const long&, const double&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j || i-j>KL || j-i>KU ){
    std::cerr << "[ERROR] dgbmatrix::set(long&, long&, double&)" << std::endl
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
inline std::ostream& operator<<(std::ostream& s, const dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const dgbmatrix&)"
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
inline void dgbmatrix::write(const char *filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "dgbmatrix" << " "
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
inline void dgbmatrix::read(const char* filename)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::read(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ifstream s( filename );
  if(!s){
    std::cerr << "[ERROR] dgbmatrix::read(const char*) " << std::endl
              << "The file \"" << filename << "\" can not be opened."
              << std::endl;
    exit(1);
  }

  std::string id;
  s >> id;
  if( id != "dgbmatrix" ){
    std::cerr << "[ERROR] dgbmatrix::read(const char*) " << std::endl
              << "The type name of the file \"" << filename
              << "\" is not dgbmatrix." << std::endl
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
    std::cerr << "[ERROR] dgbmatrix::read(const char*) " << std::endl
              << "There is something is wrong with the file \""
              << filename << " ." << std::endl
              << "Most likely, there is not enough data components, "
              << "or a linefeed code or space code is missing "
              << "at the end of the last line." << std::endl;
    exit(1);
  }
  
  s.close();
}
