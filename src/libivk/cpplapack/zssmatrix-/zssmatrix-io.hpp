//=============================================================================
/*! operator() for const object */
inline std::complex<double> zssmatrix::operator()(const long& i, const long& j) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::operator()(const long&, const long&) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] zssmatrix::operator()(long, long)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ return Array[c]; }
  }
  
  //// (i,j) component not found ////
  std::cerr << "[ERROR] zssmatrix::operator()(long, long)" << std::endl
            << "The required component is out of the matrix size."
            << std::endl
            << "Your input was (" << i << "," << j << ")." << std::endl;
  exit(1);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! put value with isListed check and volume cheack */
inline void zssmatrix::put(const long& i, const long& j, const std::complex<double>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::put(const long&, const long&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] zssmatrix::put(long&, long&, std::complex<double>&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// in case (i,j) already exists ////
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ Array[c]=v; return; }
  }
  
  //// in case (i,j) doesnot exist ////
  if(VOL==CAP){ 
    expand(CPPL_SS_SECTOR);
#ifdef  CPPL_DEBUG
    std::cerr << "[NOTE] zssmatrix::put(long&, long&, std::complex<double>&) "
              << "The matrix volume was automatically expanded." << std::endl;
#endif//CPPL_DEBUG
  }
  
  Indx[VOL]=i; Jndx[VOL]=j; Array[VOL]=v;
  VOL++;
}

//=============================================================================
/*! put value without isListed check and volume cheack */
inline void zssmatrix::fput(const long& i, const long& j, const std::complex<double>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::fput(const long&, const long&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] zssmatrix::fput"
              << "(const long&, lconst ong&, const std::complex<double>&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
  
  if(VOL==CAP){ 
    std::cerr << "[ERROR] zssmatrix::fput"
              << "(const long&, const long&, const std::complex<double>&)" << std::endl
              << "There is no free space to set a new entry." << std::endl;
    exit(1);
  }
  
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){
      std::cerr << "[ERROR] zssmatrix::fput"
                << "(const long&, const long&, const std::complex<double>&)" << std::endl
                << "The required component is already listed." << std::endl
                << "Your input was (" << i << "," << j << ")." << std::endl;
      exit(1);
    }
  }
#endif//CPPL_DEBUG
  
  Indx[VOL]=i;  Jndx[VOL]=j;  Array[VOL]=v;
  VOL++;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! add value with isListed check and volume cheack */
inline void zssmatrix::add(const long& i, const long& j, const std::complex<double>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::add(const long&, const long&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] zssmatrix::add(long&, long&, std::complex<double>&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// in case (i,j) already exists ////
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ Array[c]+=v; return; }
  }
  
  //// in case (i,j) doesnot exist ////
  if(VOL==CAP){
    expand(CPPL_SS_SECTOR);
#ifdef  CPPL_DEBUG
    std::cerr << "[NOTE] zssmatrix::add(long&, long&, std::complex<double>&) "
              << "The matrix volume was automatically expanded." << std::endl;
#endif//CPPL_DEBUG
  }
  
  Indx[VOL]=i; Jndx[VOL]=j; Array[VOL]=v;
  VOL++;
}

//=============================================================================
/*! subtract value with isListed check and volume cheack */
inline void zssmatrix::sub(const long& i, const long& j, const std::complex<double>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::sub(const long&, const long&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] zssmatrix::sub(long&, long&, std::complex<double>&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// in case (i,j) already exists ////
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ Array[c]-=v; return; }
  }
  
  //// in case (i,j) doesnot exist ////
  if(VOL==CAP){
    expand(CPPL_SS_SECTOR);
#ifdef  CPPL_DEBUG
    std::cerr << "[NOTE] zssmatrix::sub(long&, long&, std::complex<double>&) "
              << "The matrix volume was automatically expanded." << std::endl;
#endif//CPPL_DEBUG
  }
  
  Indx[VOL]=i; Jndx[VOL]=j; Array[VOL]=-v;
  VOL++;
}

//=============================================================================
/*! multiply value with isListed check and volume cheack */
inline void zssmatrix::mult(const long& i, const long& j, const std::complex<double>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::mult(const long&, const long&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] zssmatrix::mult(long&, long&, std::complex<double>&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// in case (i,j) already exists ////
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ Array[c]*=v; return; }
  }
  
  //// in case (i,j) doesnot exist ////
  return;
}

//=============================================================================
/*! divide value with isListed check and volume cheack */
inline void zssmatrix::div(const long& i, const long& j, const std::complex<double>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::div(const long&, const long&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] zssmatrix::div(long&, long&, std::complex<double>&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  //// in case (i,j) already exists ////
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){ Array[c]/=v; return; }
  }
  
  //// in case (i,j) doesnot exist ////
  return;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! delete the entry of a component */
inline void zssmatrix::del(const long& i, const long& j)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::del(const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( i<0 || j<0 || M<=i || N<=j ){
    std::cerr << "[ERROR] zssmatrix::del(long&, long&, std::complex<double>&)" << std::endl
              << "The required component is out of the matrix size."
              << std::endl
              << "Your input was (" << i << "," << j << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long c=0; c<VOL; c++){
    if(Indx[c]==i && Jndx[c]==j){
      VOL--;
      Indx[c]=Indx[VOL];  Jndx[c]=Jndx[VOL];  Array[c]=Array[VOL];
      return;
    }
  }
  
  std::cerr << "[WARNING] zssmatrix::del(long&, long&, std::complex<double>&) "
            << "The required component was not listed. "
            << "Your input was (" << i << "," << j << ")." << std::endl;
}

//=============================================================================
/*! delete the entry of an element */
inline void zssmatrix::fdel(const long& c)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::fdel(const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( c<0 || c>VOL ){
    std::cerr << "[ERROR] zssmatrix::fdel(const long&)" << std::endl
              << "The required element is out of the matrix volume."
              << std::endl
              << "Your input was (" << c << ")." << std::endl;
    exit(1);
  }
  
  std::cerr << "# [NOTE] zssmatrix::fdel(const long&) "
            << "The (" << Indx[c] << "," << Jndx[c]
            << ") component is going to be deleted." << std::endl;
#endif//CPPL_DEBUG
  
  VOL--;
  Indx[c]=Indx[VOL];  Jndx[c]=Jndx[VOL];  Array[c]=Array[VOL];
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline std::ostream& operator<<(std::ostream& s, const zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator<<(std::ostream&, const zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long c;
  for(long i=0; i<mat.M; i++){
    for(long j=0; j<mat.N; j++){
      c=0;
      while(c<mat.VOL){
        if(mat.Indx[c]==i && mat.Jndx[c]==j){ break; }
        c++;
      }
      if(c!=mat.VOL){ s << mat.Array[c] << " "; }
      else{ s << "x "; }
    }
    s << std::endl;
  }
  
  return s;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
inline void zssmatrix::write(const char* filename) const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::write(const char*) const"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ofstream s(filename, std::ios::trunc);
  
  s << "zssmatrix" << " " << M << " " << N << " " << CAP << std::endl;
  for(long c=0; c<VOL; c++){
    s << Indx[c] << " " << Jndx[c] << " " << Array[c] << std::endl;
  }
  s.close();
}

//=============================================================================
inline void zssmatrix::read(const char *filename)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::read(const char*)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::ifstream s( filename );
  if(!s){
    std::cerr << "[ERROR] zssmatrix::read(const char*) " << std::endl
              << "The file \"" << filename << "\" can not be opened."
              << std::endl;
    exit(1);
  }

  std::string id;
  s >> id;
  if( id != "zssmatrix" ){
    std::cerr << "[ERROR] zssmatrix::read(const char*) " << std::endl
              << "The type name of the file \"" << filename
              << "\" is not zssmatrix." << std::endl
              << "Its type name was " << id << " ." << std::endl;
    exit(1);
  }
  
  s >> M >> N >> CAP;
  resize(M, N, CAP);
  
  long pos, tmp; 
  while(!s.eof() && VOL<CAP){
    s >> Indx[VOL] >> Jndx[VOL] >> Array[VOL];
    pos =s.tellg(); s >> tmp; s.seekg(pos);
    VOL++;
  }
  
  if(!s.eof()){
    std::cerr << "[ERROR] zssmatrix::read(const char*) " << std::endl
              << "There is something is wrong with the file \""
              << filename << " ." << std::endl
              << "Most likely, there are too many data components "
              << "over the context." << std::endl;
    exit(1);
  }
  s.close();
}
